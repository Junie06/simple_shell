#include "shell.h"

char *_strchr(char *str, char cha);
int _strspn(char *str, char *accept);
int _strcmp(char *str1, char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);

/**
 * _strchr - Locates a character in a string.
 * @str: The string to be searched.
 * @char: The character to be located.
 *
 * Return: If char is found - a pointer to the first occurence.
 *         If char is not found - NULL.
 */
char *_strchr(char *str, char cha)
{
	int index;

	for (index = 0; str[index]; index++)
	{
		if (str[index] == cha)
			return (str + index);
	}

	return (NULL);
}

/**
 * _strspn - Gets the length of a prefix substring.
 * @str: The string to be searched.
 * @accept: The prefix to be measured.
 *
 * Return: The number of bytes in s which
 *         consist only of bytes from accept.
 */
int _strspn(char *str, char *accept)
{
	int bytes = 0;
	int index;

	while (*str)
	{
		for (index = 0; accept[index]; index++)
		{
			if (*str == accept[index])
			{
				bytes++;
				break;
			}
		}
		str++;
	}
	return (bytes);
}

/**
 * _strcmp - Compares two strings.
 * @str1: The first string to be compared.
 * @str2: The second string to be compared.
 *
 * Return: Positive byte difference if str1 > str2
 *         0 if str1 = str2
 *         Negative byte difference if str1 < str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	if (*str1 != *str2)
		return (*str1 - *str2);

	return (0);
}

/**
 * _strncmp - Compare two strings.
 * @str1: Pointer to a string.
 * @str2: Pointer to a string.
 * @n: The first n bytes of the strings to compare.
 *
 * Return: Less than 0 if str1 is shorter than str2.
 *         0 if str1 and str2 match.
 *         Greater than 0 if str1 is longer than str2.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; str1[i] && str2[i] && i < n; i++)
	{
		if (str1[i] > str2[i])
			return (str1[i] - str2[i]);
		else if (str1[i] < str2[i])
			return (str1[i] - str2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
