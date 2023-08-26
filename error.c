#include "shell.h"

int len_num(int num);
char *_itoa(int num);
int set_error(char **args, int err);

/**
 * len_num - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int len_num(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * _itoa - Converts an integer to a string to enable manipulation.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = len_num(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}

/**
 * set_error - Writes a custom error message to
 * stderr that conforms to shell standard.
 * set_error - Writes a custom error message to stderr that
 * conforms to shell standards.
 * @args: An array of arguments passed to the function.
 * @err: The error value.
 *
 * Return: The error value.
 */
int set_error(char **args, int err)
{
	char *error;

	switch (err)
	{
		case -1:
			error = env_error(args);
			break;
		case 1:
			error = error1(args);
			break;
		case 2:
			if (*(args[0]) == 'e')
				error = error2_exit(++args);
			else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
				error = error2_syntax(args);
			else
				error = error2_cd(args);
			break;
		case 126:
			error = error_126(args);
			break;
		case 127:
			error = error_127(args);
			break;
	}
	write(STDERR_FILENO, error, _strlen(error));

	if (error)
		free(error);
	return (err);

}
