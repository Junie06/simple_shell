#include "shell.h"

/**
 * construct_file_path - Constructs a file path by
 * concatenating a directory and a command.
 * @directory: The directory path.
 * @command: The command filename.
 * Return: A pointer to the constructed file path.
 */
char *construct_file_path(char *directory, char *command)
{
	int directory_length = _strlen(directory);
	int command_length = _strlen(command);
	char *file_path = malloc(directory_length + command_length + 2);

	if (file_path == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	_strcpy(file_path, directory);
	_strcat(file_path, "/");
	_strcat(file_path, command);
	_strcat(file_path, "\0");

	free(file_path);
	return (file_path);
}

/**
 * search_command_in_path - Searches for a command in the directories
 * specified by PATH.
 * @command: The command to search for.
 * Return: A pointer to the full file path of the command,
 * or NULL if not found.
 */
char *search_command_in_path(char *command)
{
	char *path = _getenv("PATH");

	if (path)
	{
		char *path_copy = _strdup(path);
		char *path_token = _strtok(path_copy, ":");
		struct stat buffer;

		while (path_token != NULL)
		{
			char *file_path = construct_file_path(path_token, command);

			if (stat(file_path, &buffer) == 0)
				return (file_path);
			free(file_path);
			path_token = _strtok(NULL, ":");
		}

		free(path_copy);
	}
	return (NULL);
}

/**
 * get_location - Retrieve the location of a command.
 * @command: The command to retrieve the location of.
 * Return: A pointer to the location of the command, or
 * NULL if not found.
 */
char *get_location(char *command)
{
	struct stat buffer;
	char *command_location = search_command_in_path(command);

	if (command_location == NULL && stat(command, &buffer) == 0)
	{
		command_location = _strdup(command);
	}

	return (command_location);
}
