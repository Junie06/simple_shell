#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stddef.h>
#include <limits.h>

#define BUFFER_SIZE 1024

/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

void execmd(char **argv);
char *get_location(char *command);
char *_getenv(const char *name);
size_t _strcspn(const char *str, const char *charset);
int _putchar(char c);
void _puts(char *str);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);
char *_strdup(const char *str);
char *_strcat(char *dest, char *src);
char *_strchr(const char *str, int character);
int _strcmp(const char *s1, char *s2);
extern char **environ;
void execute_command(char *actual_command, char **argv);
void execute_command_if_valid(char **argv);
void execmd(char **argv);
char *construct_file_path(char *directory, char *command);
char *search_command_in_path(char *command);
char *get_location(char *command);
void print_prompt(char *prompt);
void handle_exit(const char *command);
char *read_input();
void split_tokens(char *lineptr, const char *delim,
		char ***argv, int *num_tokens);
char *input_func();
char *expand_line_buffer(char *line, size_t *line_length,
		size_t *line_capacity);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strtok(char *str, const char *delim);
int _isdigit(const char *s);
int _atoi(char *s);
int exit_shell(data_shell *datash);
int get_len(int n);
char *aux_itoa(int n);
char *error_env(data_shell *datash);
char *error_path_126(data_shell *datash);
char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str);
char *error_get_cd(data_shell *datash);
char *error_not_found(data_shell *datash);
char *error_exit_shell(data_shell *datash);
int get_error(data_shell *datash, int eval);
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
int check_syntax_error(data_shell *datash, char *input);
int (*get_builtin(char *cmd))(data_shell *);
int exec_line(data_shell *datash);
int is_cdir(char *path, int *i);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);

#endif
