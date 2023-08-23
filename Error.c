#include "shell.h"

/**
 * error_env - error message for env in get_env.
 * @datahsh: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_env(data_shell *datahsh)
{
	int length;
	char *error;
	char *in_str;
	char *msg;

	in_str = aux_itoa(datahsh->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(datahsh->av[0]) + _strlen(in_str);
	length += _strlen(datahsh->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(in_str);
		return (NULL);
	}

	_strcpy(error, datahsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, in_str);
	_strcat(error, ": ");
	_strcat(error, datahsh->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(in_str);

	return (error);
}

/**
 * error_path_126 - error message for path and failure denied permission.
 * @datahsh: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126(data_shell *datahsh)
{
	int length;
	char *in_str;
	char *error;

	in_str = aux_itoa(datahsh->counter);
	length = _strlen(datahsh->av[0]) + _strlen(in_str);
	length += _strlen(datahsh->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(in_str);
		return (NULL);
	}
	_strcpy(error, datahsh->av[0]);
	_strcat(error, ": ");
	_strcat(error, in_str);
	_strcat(error, ": ");
	_strcat(error, datahsh->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(in_str);
	return (error);
}
