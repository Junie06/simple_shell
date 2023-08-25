#include "shell.h"

void signal_handle(int sig);
int execute(char **args, char **first);

/**
 * signal_handle - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void signal_handle(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, signal_handle);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execmd - Executes a command in a child process.
 * @args: An array of arguments.
 * @first: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last execmdd command.
 */
int execute(char **args, char **first)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (set_error(args, 126));
		else
			ret = (set_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret = (set_error(args, 126));
			env_free();
			free_args(args, first);
			free_aliaslist(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last execmdd command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, signal_handle);

	*exe_ret = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = run_file_commands(argv[1], exe_ret);
		env_free();
		free_aliaslist(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = args_handle(exe_ret);
		env_free();
		free_aliaslist(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = args_handle(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			env_free();
			free_aliaslist(aliases);
			exit(*exe_ret);
		}
	}

	env_free();
	free_aliaslist(aliases);
	return (*exe_ret);
}
