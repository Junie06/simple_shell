#ifndef _SHELL_H_
#define _SHELL_H_

#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
char *copy_path_dir(char *path);
int execute(char **args, char **first);
void free_list(list_t *head);
char *_itoa(int num);

/* Input Helpers */
void line_handle(char **line, ssize_t read);
void replace_environ(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int args_call(char **args, char **first, int *exe_ret);
int args_run(char **args, char **first, int *exe_ret);
int args_handle(int *exe_ret);
int args_check(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*_getbuiltin(char *command))(char **args, char **first);
int exit_shell(char **args, char **first);
int cd_shell(char **args, char __attribute__((__unused__)) **first);
int help_shell(char **args, char __attribute__((__unused__)) **first);
int env_shell(char **args, char __attribute__((__unused__)) **first);
int setenv_shell(char **args, char __attribute__((__unused__)) **first);
int unsetenv_shell(char **args, char __attribute__((__unused__)) **first);
int shell_alias(char **args, char __attribute__((__unused__)) **front);
void fix_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/* Builtin Helpers */
char **_copyenv(void);
void env_free(void);
char **_getenv(const char *var);

/* Error Handling */
int set_error(char **args, int err);
char *error_126(char **args);
char *error_127(char **args);
int error_open(char *file_path);
char *env_error(char **args);
char *error1(char **args);
char *error2_exit(char **args);
char *error2_cd(char **args);
char *error2_syntax(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_aliaslist(alias_t *head);
list_t *add_end_node(list_t **head, char *dir);
void free_list(list_t *head);

void env_help(void);
void setenv_help(void);
void unsetenv_env(void);
void history_help(void);
void all_help(void);
void alias_help(void);
void cd_help(void);
void exit_help(void);
void help2_help(void);

int run_file_commands(char *file_path, int *exe_ret);
int len_of_token(char *str, char *delim);
int token_count(char *str, char *delim);
ssize_t gain_new_len(char *line);
void log_oops(char *line, ssize_t *new_len);
char *get_pid(void);
char *env_value(char *beginning, int len);
int len_num(int num);

#endif
