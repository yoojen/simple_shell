#include "shell.h"

/**
 * create_myenv - prints the current environment
 * @passed_args: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int create_myenv(var_list *passed_args)
{
	print_node_list(passed_args->my_env);
	return (0);
}

/**
 * create_mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @passed_args: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int create_mysetenv(var_list *passed_args)
{
	if (passed_args->arg_count != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(passed_args, passed_args->argv_array[1], passed_args->argv_array[2]))
		return (0);
	return (1);
}

/**
 * _getenv - gets the value of an environ variable
 * @passed_args: Structure containing potential arguments. Used to maintain
 * @name: my_env var name
 *
 * Return: the value
 */
char *_getenv(var_list *passed_args, const char *name)
{
	my_list *node = passed_args->my_env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}


/**
 * use_all_env_main - populates my_env linked list
 * @passed_args: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int use_all_env_main(var_list *passed_args)
{
	my_list *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_at_end(&node, environ[i], 0);
	passed_args->my_env = node;
	return (0);
}

/**
 * create_myunsetenv - Remove an environment variable
 * @passed_args: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int create_myunsetenv(var_list *passed_args)
{
	int i;

	if (passed_args->arg_count == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= passed_args->arg_count; i++)
		_unsetenv(passed_args, passed_args->argv_array[i]);

	return (0);
}



