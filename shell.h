#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int is_cmd(info_t *, char *);
char *dupl_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int loophsh(char **);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *look_for(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_duplstr(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_charinstr(char *, char);

char **strspt(char *, char *);
char **strspt2(char *, char);

char *_memfill(char *, char, unsigned int);
void strfree(char **);
void *_ralloc(void *, unsigned int, unsigned int);

int ptrfree(void **);

int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

int _advatoi(char *);
void showerror(info_t *, char *);
int print_decimal(int, int);
char *convnum(long int, int, int);
void remcomments(char *);

int _exit(info_t *);
int _cd(info_t *);
int _help(info_t *);

int _hist(info_t *);
int _aliases(info_t *);

ssize_t _input(info_t *);
int _takeline(info_t *, char **, size_t *);
void intHandler(int);

void clsinfo(info_t *);
void putinfo(info_t *, char **);
void freeinfo(info_t *, int);

char *_openv(info_t *, const char *);
int _cuenv(info_t *);
int _setenv(info_t *);
int _unsetenv(info_t *);
int _env_list(info_t *);

char **take_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *get_hist_file(info_t *info);
int write_hist(info_t *info);
int read_hist(info_t *info);
int make_hist_list(info_t *info, char *buf, int linecount);
int re_number_hist(info_t *info);

list_t *_add_noode(list_t **, const char *, int);
list_t *_add_noode_end(list_t **, const char *, int);
size_t list_out_str(const list_t *);
int _delete_noode_from_index(list_t **, unsigned int);
void free_out_list(list_t **);

size_t _list_out_lenght(const list_t *);
char **_convert_list_to_strings(list_t *);
size_t _print_list(const list_t *);
list_t *_noode_starts_with(list_t *, char *, char);
ssize_t _get_noode_index(list_t *, list_t *);

int _is_chain(info_t *, char *, size_t *);
void _check_chain(info_t *, char *, size_t *, size_t, size_t);
int _repl_alias(info_t *);
int _repl_vars(info_t *);
int _replace_string(char **, char *);

#endif
