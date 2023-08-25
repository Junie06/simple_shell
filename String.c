#include "shell.h"

int _strlen(const char *str);
char *_strcpy(char *dest, const char *str);
char *_strcat(char *dest, const char *str);
char *_strncat(char *dest, const char *str, size_t n);

/**
 * _strlen - Returns the length of a string.
 * @str: A pointer to the characters string that are passed as arguments.
 *
 * Return: The length of the character string.
 */
int _strlen(const char *str)
{
	int length = 0;

	if (!str)
		return (length);
	for (length = 0; str[length]; length++)
		;
	return (length);
}

/**
 * _strcpy - Copies the string pointed to by str, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @str: Pointer to the str of the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *str)
{
	size_t i;

	for (i = 0; str[i] != '\0'; i++)
		dest[i] = str[i];
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @str: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *_strcat(char *dest, const char *str)
{
	char *destTemp;
	const char *strTemp;

	destTemp = dest;
	strTemp =  str;

	while (*destTemp != '\0')
		destTemp++;

	while (*strTemp != '\0')
		*destTemp++ = *strTemp++;
	*destTemp = '\0';
	return (dest);
}

/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @str: Pointer to source string.
 * @n: n bytes to copy from str.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *str, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && str[i] != '\0'; i++)
		dest[dest_len + i] = str[i];
	dest[dest_len + i] = '\0';

	return (dest);
}
