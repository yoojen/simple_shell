#include "shell.h"

/**
 * clean_allInfo - initializes var_list struct
 * @passed_args: struct address
 */
void clean_allInfo(var_list *passed_args)
{
	passed_args->argument = NULL;
	passed_args->argv_array = NULL;
	passed_args->path_link = NULL;
	passed_args->arg_count = 0;
}

/**
 * remove_infFr - frees var_list struct fields
 * @passed_args: struct address
 * @all: true if freeing all fields
 */
void remove_infFr(var_list *passed_args, int all_args)
{
	ffree(passed_args->argv_array);
	passed_args->argv_array = NULL;
	passed_args->path_link = NULL;
	if (all_args)
	{
		if (!passed_args->command_buffer)
			free(passed_args->argument);
		if (passed_args->my_env)
			free_my_nodes(&(passed_args->my_env));
		if (passed_args->history)
			free_my_nodes(&(passed_args->history));
		if (passed_args->alias)
			free_my_nodes(&(passed_args->alias));
		ffree(passed_args->environ);
			passed_args->environ = NULL;
		buffFree((void **)passed_args->command_buffer);
		if (passed_args->r_fd > 2)
			close(passed_args->r_fd);
		_putchar(FLUSH_BUFFER);
	}
}


/**
 * create_info_fr - initializes var_list struct
 * @passed_args: struct address
 * @av: argument vector
 */
void create_info_fr(var_list *passed_args, char **argvs)
{
	int i = 0;

	passed_args->file_name = argvs[0];
	if (passed_args->argument)
	{
		passed_args->argv_array = my_strtok_1(passed_args->argument, " \t");
		if (!passed_args->argv_array)
		{
			passed_args->argv_array = malloc(sizeof(char *) * 2);
			if (passed_args->argv_array)
			{
				passed_args->argv_array[0] = _strdup(passed_args->argument);
				passed_args->argv_array[1] = NULL;
			}
		}
		for (i = 0; passed_args->argv_array && passed_args->argv_array[i]; i++)
			;
		passed_args->arg_count = i;

		change_placeOf_alias(passed_args);
		change_placeOf_vars(passed_args);
	}
}

