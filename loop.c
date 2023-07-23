#include "shell.h"

/**
 * hsh - main shell loop
 * @passed_args: the parameter & return passed_args struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(var_list *passed_args, char **argv_line)
{
	ssize_t rs = 0;
	int rets_of_builtin = 0;

	while (rs != -1 && rets_of_builtin != -2)
	{
		clean_allInfo(passed_args);
		if (interactive(passed_args))
			_puts("$ ");
		_eputchar(FLUSH_BUFFER);
		rs = allow_input_fr(passed_args);
		if (rs != -1)
		{
			create_info_fr(passed_args, argv_line);
			rets_of_builtin = get_builtinCmd(passed_args);
			if (rets_of_builtin == -1)
				get_command(passed_args);
		}
		else if (interactive(passed_args))
			_putchar('\n');
		remove_infFr(passed_args, 0);
	}
	dispayFilehistory(passed_args);
	remove_infFr(passed_args, 1);
	if (!interactive(passed_args) && passed_args->status)
		exit(passed_args->status);
	if (rets_of_builtin == -2)
	{
		if (passed_args->number_of_err == -1)
			exit(passed_args->status);
		exit(passed_args->number_of_err);
	}
	return (rets_of_builtin);
}

/**
 * get_builtinCmd - finds a builtin_commands command
 * @passed_args: the parameter & return passed_args struct
 *
 * Return: -1 if builtin_commands not found,
 *			0 if builtin_commands executed successfully,
 *			1 if builtin_commands found but not successful,
 *			-2 if builtin_commands signals exit()
 */
int get_builtinCmd(var_list *passed_args)
{
	int i, built_in_ret = -1;
	builtin_t builtintbl[] = {
		{"exit", make_exit},
		{"unsetenv", create_myunsetenv},
		{"cd", change_dir},
		{"history", ask_history},
		{"env", create_myenv},
		{"setenv", create_mysetenv},
		{"alias", ask_alias},
		{"help", ask_help},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(passed_args->argv_array[0], builtintbl[i].type) == 0)
		{
			passed_args->number_of_line++;
			built_in_ret = builtintbl[i].f(passed_args);
			break;
		}
	return (built_in_ret);
}

/**
 * get_command - finds a command in PATH
 * @passed_args: the parameter & return passed_args struct
 *
 * Return: void
 */
void get_command(var_list *passed_args)
{
	char *pathOfFile = NULL;
	int i, j;

	passed_args->path_link = passed_args->argv_array[0];
	if (passed_args->flagOfLine == 1)
	{
		passed_args->number_of_line++;
		passed_args->flagOfLine = 0;
	}
	for (i = 0, j = 0; passed_args->argument[i]; i++)
		if (!bool_delimiter(passed_args->argument[i], " \t\n"))
			j++;
	if (!j)
		return;

	pathOfFile = return_pathname(passed_args, _getenv(passed_args, "PATH="), passed_args->argv_array[0]);
	if (pathOfFile)
	{
		passed_args->path_link = pathOfFile;
		fork_command(passed_args);
	}
	else
	{
		if ((interactive(passed_args) || _getenv(passed_args, "PATH=")
			|| passed_args->argv_array[0][0] == '/') && is_It_command(passed_args, passed_args->argv_array[0]))
			fork_command(passed_args);
		else if (*(passed_args->argument) != '\n')
		{
			passed_args->status = 127;
			showOff_error(passed_args, "not found\n");
		}
	}
}

/**
 * fork_command - forks a an exec thread to run cmd
 * @passed_args: the parameter & return passed_args struct
 *
 * Return: void
 */
void fork_command(var_list *passed_args)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(passed_args->path_link, passed_args->argv_array, get_environment(passed_args)) == -1)
		{
			remove_infFr(passed_args, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(passed_args->status));
		if (WIFEXITED(passed_args->status))
		{
			passed_args->status = WEXITSTATUS(passed_args->status);
			if (passed_args->status == 126)
				showOff_error(passed_args, "Permission denied\n");
		}
	}
}

