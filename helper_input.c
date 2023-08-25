#include "shell.h"

char *get_args(char *line, int *exe_ret);
int args_call(char **args, char **first, int *exe_ret);
int args_run(char **args, char **first, int *exe_ret);
int args_handle(int *exe_ret);
int args_check(char **args);

/**
 * get_args - Gets a command from standard input.
 * @line: A buffer to store the command to improve perfomance.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	replace_environ(&line, exe_ret);
	line_handle(&line, read);

	return (line);
}

/**
 * args_call - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @first: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int args_call(char **args, char **first, int *exe_ret)
{
	int ret, index;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = args_run(args, first, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = args_run(args, first, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = args_run(args, first, exe_ret);
	return (ret);
}

/**
 * args_run - Calls the execution of a command.
 * @args: An array of arguments.
 * @first: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command on the shell history.
 */
int args_run(char **args, char **first, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **first);

	builtin = _getbuiltin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, first);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, first);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * args_handle - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int args_handle(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **first;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (args_check(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	first = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = args_call(args, first, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = args_call(args, first, exe_ret);

	free(first);
	return (ret);
}

/**
 * args_check - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2 as error status.
 *	   Otherwise - 0 as error status.
 */
int args_check(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (set_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (set_error(&args[i + 1], 2));
		}
	}
	return (0);
}
