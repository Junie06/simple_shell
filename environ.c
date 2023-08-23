#include "shell.h"

/**
 * _getenv - Retrieves the value of an environment variable.
 * @name: The name of the environment variable.
 * Return: A pointer to the value of the environment variable, or NULL if not found.
 */
char *_getenv(const char *name)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		char *separator = _strchr(environ[i], '=');

		if (separator == NULL)
		{
			continue;
		}


		if (_strcmp(name, environ[i]) == 0)
		{
			char *value = malloc(strlen(separator + 1) + 1);

			if (value == NULL)
			{
				perror("Memory allocation error");
				return (NULL);
			}
			_strcpy(value, separator + 1);

			return (value);
		}
	}
	return (NULL);
}
