#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for read/write buffers */
#define BUFFER_SIZE 1024
#define NW_BUFFER_SIZE 1024
#define FLUSH_BUFFER -1

/* for command chaining */
#define COMMAND_NORMAL	0
#define COMMAND_ORAL		1
#define COMMAND_AND_		2
#define CHAIN_COMMAND	3

/* for conversationof_number() */
#define LOWER_CONVERTER	1
#define UNSIGNED_CONVERTER	2

/* 1 if using system getline() */
#define GETLINE_USAGE 0
#define STRTOK_USAGE 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct linked_lst - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct linked_lst
{
	int num;
	char *str;
	struct linked_lst *next;
} my_list;

/**
 *struct pass_value - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@argument: a string generated from getline containing arguements
 *@argv_array: an array of strings generated from argument
 *@path_link: a string path for the current command
 *@arg_count: the argument count
 *@number_of_line: the error count
 *@number_of_err: the error code for exit()s
 *@flagOfLine: if on count this line of input
 *@file_name: the program filename
 *@my_env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL my_env
 *@history: the history node
 *@alias: the alias node
 *@changed_env: on if environ was changed
 *@status: the return status of the last exec'd command
 *@command_buffer: address of pointer to command_buffer, on if chaining
 *@command_buffer_type: CMD_type ||, &&, ;
 *@r_fd: the fd from which to read line input
 *@hist_len: the history line number count
 */
typedef struct pass_value
{
	char *argument;
	char **argv_array;
	char *path_link;
	int arg_count;
	unsigned int number_of_line;
	int number_of_err;
	int flagOfLine;
	char *file_name;
	my_list *my_env;
	my_list *history;
	my_list *alias;
	char **environ;
	int changed_env;
	int status;

	char **command_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
	int command_buffer_type; /* CMD_type ||, &&, ; */
	int r_fd;
	int hist_len;
} var_list;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin_commands - contains a builtin_commands string and related function
 *@type: the builtin_commands command flag
 *@f: the function
 */
typedef struct builtin_commands
{
	char *type;
	int (*f)(var_list *);
} builtin_t;


/* toem_shloop.c */
int hsh(var_list *, char **);
int get_builtinCmd(var_list *);
void get_command(var_list *);
void fork_command(var_list *);
/*toem_getline.c */
ssize_t allow_input_fr(var_list *);
int _getline(var_list *, char **, size_t *);
void sigintHandler(int);

/* toem_getinfo.c */
void clean_allInfo(var_list *);
void create_info_fr(var_list *, char **);
void remove_infFr(var_list *, int);
/* toem_tokenizer.c */
char **my_strtok_1(char *, char *);
char **my_strtok_2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
/* toem_parser.c */
int is_It_command(var_list *, char *);
char *make_duplication(char *, int, int);
char *return_pathname(var_list *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_getenv.c */
char **get_environment(var_list *);
int _unsetenv(var_list *, char *);
int _setenv(var_list *, char *, char *);

/* toem_lists1.c */
size_t linked_length(const my_list *);
char **linked_to_strings(my_list *);
size_t print_Mylinked_list(const my_list *);
my_list *prefix_of_node(my_list *, char *, char);
ssize_t get_node_at_this_index(my_list *, my_list *);

/* toem_vars.c */
int return_is_chain(var_list *, char *, size_t *);
void checkFor_Bchain(var_list *, char *, size_t *, size_t, size_t);
int change_placeOf_alias(var_list *);
int change_placeOf_vars(var_list *);
int change_placeOf_string(char **, char *);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfile(char c, int fd);
int _putsfile(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_history.c */
char *history_of_file_returns(var_list *passed_args);
int dispayFilehistory(var_list *passed_args);
int nread_history_infos(var_list *passed_args);
int return_history_listFr(var_list *passed_args, char *buf, int linecount);
int numberHistory(var_list *passed_args);

/* toem_lists.c */
my_list *add_node(my_list **, const char *, int);
my_list *add_node_at_end(my_list **, const char *, int);
size_t print_node_list(const my_list *);
int delete_node_at_An_index(my_list **, unsigned int);
void free_my_nodes(my_list **);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);



/* toem_builtin.c */
int make_exit(var_list *);
int change_dir(var_list *);
int ask_help(var_list *);

/* toem_builtin1.c */
int ask_history(var_list *);
int ask_alias(var_list *);


/* toem_memory.c */
int buffFree(void **);

/* toem_atoi.c */
int interactive(var_list *);
int bool_delimiter(char, char *);
int _isalpha(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void showOff_error(var_list *, char *);
int printDError(int, int);
char *conversationof_number(long int, int, int);
void getRidOfComment(char *);
/* toem_environ.c */
char *_getenv(var_list *, const char *);
int create_myenv(var_list *);
int create_mysetenv(var_list *);
int create_myunsetenv(var_list *);
int use_all_env_main(var_list *);

#endif

