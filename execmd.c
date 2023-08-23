#include "shell.h"

/**
 * execute_command - Executes a command using a child process.
 * @actual_command: The actual command to execute.
 * @argv: An array of arguments for the command.
 */
void execute_command(char *actual_command, char **argv)
{
	int status;

	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Fork error:");
		free(actual_command);
		return;
	}
	else if (pid == 0)
	{
		if (execve(actual_command, argv, environ) == -1)
		{
			perror("Error (childprocess)");
			free(actual_command);
		}
		_exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(actual_command);
	}
}

/**
 * execute_command_if_valid - Executes a command if it is valid and executable.
 * @argv: An array of arguments for the command.
 */
void execute_command_if_valid(char **argv)
{
	char *command = argv[0];
	char *actual_command = get_location(command);

	if (actual_command == NULL)
	{
		perror("Command not found");
		return;
	}

	if (access(actual_command, X_OK) != 0)
	{
		perror(actual_command);
		free(actual_command);
		return;
	}

	execute_command(actual_command, argv);
}

/**
 * execmd - Executes a command if valid and executable.
 * @argv: An array of arguments for the command.
 */
void execmd(char **argv)
{
	if (argv)
	{
		execute_command_if_valid(argv);
	}
}
