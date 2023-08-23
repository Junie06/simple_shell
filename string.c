#include "shell.h"

/**
 * _strcspn - Computes the length of a substring until
 * a charset character is encountered.
 * @str: The input string to search.
 * @charset: The charset of characters to search for.
 * Return: The length of the substring until a charset character is found.
 */

size_t _strcspn(const char *str, const char *charset)
{
	size_t length = 0;
	size_t charsetIndex = 0;

	while (str[length] != '\0')
	{
		while (charset[charsetIndex] != '\0')
		{
			if (str[length] == charset[charsetIndex])
			{
				return (length);
			}
			charsetIndex++;
		}
		length++;
	}

	return (length);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: on success 1
 * on error, -1 is returned, and errno is set appropriately
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string, followed by a new line, to stdout
 * @str: string to print
 */
void _puts(char *str)
{
	while (*str != '\0')
	{
		_putchar(*str++);
	}
}

/**
 * char *_strcpy - a function that copies the string pointer to by src
 * @dest: copy to
 * @src: copy from
 * Return: string
 */
char *_strcpy(char *dest, char *src)
{
	int l = 0;
	int x = 0;

	while (*(src + l) != '\0')
	{
		l++;
	}
	for ( ; x < l ; x++)
	{
		dest[x] = src[x];
	}
	dest[l] = '\0';
	return (dest);
}

/**
 * _strlen - returns the lenght of a string
 * @s: string
 * Return: length
 */
int _strlen(char *s)
{
	int longi = 0;

	while (*s != '\0')
	{
		longi++;
		s++;
	}

	return (longi);
}
