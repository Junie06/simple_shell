#include "shell.h"

void env_help(void);
void setenv_help(void);
void unsetenv_env(void);
void history_help(void);

/**
 * env_help - Displays information on the shellby builtin command 'env'.
 */
void env_help(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * setenv_help - Displays information on the shellby builtin command 'setenv'.
 */
void setenv_help(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * unsetenv_env - Displays information on the shellby builtin command
 * 'unsetenv' as a better implementation.
 */
void unsetenv_env(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, _strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, _strlen(msg));
}
