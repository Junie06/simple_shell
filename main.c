#include "shell.h"

/**
 * print_prompt - Prints a prompt to the standard output.
 * @prompt: The prompt string to be printed.
 */

void print_prompt(char *prompt)
{
	ssize_t write_result = write(STDOUT_FILENO, prompt, _strlen(prompt));

	if (write_result == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_exit - Handles the exit command of the shell.
 * @command: The exit command string.
 */

void handle_exit(const char *command)
{
	ssize_t write_exit_result;
	char *status_str = _strchr(command, ' ');

	if (status_str != NULL)
	{
		int exit_status = atoi(status_str + 1);

		exit(exit_status);
	}
	else
	{
		write_exit_result = write(STDOUT_FILENO, "Exiting shell....\n",
				_strlen("Exiting shell....\n"));

		if (write_exit_result == -1)
			perror("write");
	}
}

/**
 * read_input - Reads a line of input from the standard input.
 * Return: A pointer to the read input line, or NULL on error.
 */

char *read_input()
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nchars_read = _getline(&lineptr, &n, stdin);

	if (nchars_read == -1)
	{
		handle_exit(lineptr);
		free(lineptr);
		return (NULL);
	}
	return (lineptr);
}

/**
 * split_tokens - Splits a line into tokens using a delimiter.
 * @lineptr: The line to be split into tokens.
 * @delim: The delimiter used for tokenizing.
 * @argv: A pointer to the array of tokenized strings.
 * @num_tokens: A pointer to store the number of tokens.
 */
void split_tokens(char *lineptr, const char *delim,
		char ***argv, int *num_tokens)
{
	char *token;
	int i;
	char *lineptr_copy = malloc(strlen(lineptr) + 1);

	if (lineptr_copy == NULL)
	{
		perror("tsh: memory allocation error");
		exit(EXIT_FAILURE);
	}
	_strcpy(lineptr_copy, lineptr);

	token = _strtok(lineptr, delim);

	while (token != NULL)
	{
		(*num_tokens)++;
		token = _strtok(NULL, delim);
	}
	(*num_tokens)++;

	*argv = malloc(sizeof(char *) * (*num_tokens));

	token = _strtok(lineptr_copy, delim);

	for (i = 0; token != NULL; i++)
	{
		(*argv)[i] = malloc(sizeof(char) * strlen(token) + 1);
		if ((*argv)[i] == NULL)
		{
			perror("tsh: memory allocation error");
			exit(EXIT_FAILURE);
		}
		_strcpy((*argv)[i], token);
		token = _strtok(NULL, delim);
	}
	(*argv)[*num_tokens - 1] = NULL;

	free(lineptr_copy);
}

/**
 * main - Entry point for the simple shell program.
 * @ac: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 * Return: Always returns 0.
 */

int main(int ac, char **argv)
{
	char *prompt = "$ ";
	char *lineptr = NULL;
	char **arguments = NULL;
	int num_tokens = 0, i;

	(void)ac, (void)**argv;

	while (1)
	{
		print_prompt(prompt);

		lineptr = read_input();
		if (lineptr == NULL)
		{
			break;
		}

		if (_strcmp(lineptr, "exit") == 0)
		{
			handle_exit(lineptr);
			free(lineptr);
			break;
		}

		split_tokens(lineptr, " \n", &arguments, &num_tokens);

		execmd(arguments);

		for (i = 0; i < num_tokens - 1; i++)
			free(arguments[i]);

		free(arguments);
		free(lineptr);
	}
	return (0);
}
