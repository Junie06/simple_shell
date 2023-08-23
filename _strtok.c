#include "shell.h"

/**
 * _strtok - Splits a string into tokens based on a delimiter.
 * @str: The string to be tokenized.
 * @delim: The delimiter used to split the string into tokens.
 *
 * Return: A pointer to the next token in the string,
 * or NULL if no more tokens are found.
 */

char *_strtok(char *str, const char *delim)
{
	static char *next_token;
	char *token_start;

	if (str != NULL)
	{
		next_token = str;
	}

	while (*next_token != '\0' && _strchr(delim, *next_token) != NULL)
	{
		next_token++;
	}

	if (*next_token == '\0')
	{
		return (NULL);
	}

	token_start = next_token;

	while (*next_token != '\0' && _strchr(delim, *next_token) == NULL)
	{
		next_token++;
	}

	if (*next_token != '\0')
	{
		*next_token = '\0';
		next_token++;
	}

	return (token_start);
}
