#include "shell.h"

/**
 * get_environment - returns the string array copy of our environ
 * @passed_args: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environment(var_list *passed_args)
{
	if (!passed_args->environ || passed_args->changed_env)
	{
		passed_args->environ = linked_to_strings(passed_args->my_env);
		passed_args->changed_env = 0;
	}

	return (passed_args->environ);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @passed_args: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string my_env var property
 * @value: the string my_env var value
 *  Return: Always 0
 */
int _setenv(var_list *passed_args, char *variables, char *pass_as_value)
{
	char *buf = NULL;
	my_list *node;
	char *p;

	if (!variables || !pass_as_value)
		return (0);

	buf = malloc(_strlen(variables) + _strlen(pass_as_value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, variables);
	_strcat(buf, "=");
	_strcat(buf, pass_as_value);
	node = passed_args->my_env;
	while (node)
	{
		p = starts_with(node->str, variables);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			passed_args->changed_env = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_at_end(&(passed_args->my_env), buf, 0);
	free(buf);
	passed_args->changed_env = 1;
	return (0);
}
/**
 * _unsetenv - Remove an environment variable
 * @passed_args: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string my_env var property
 */
int _unsetenv(var_list *passed_args, char *my_vars)
{
	my_list *node = passed_args->my_env;
	size_t i = 0;
	char *p;

	if (!node || !my_vars)
		return (0);

	while (node)
	{
		p = starts_with(node->str, my_vars);
		if (p && *p == '=')
		{
			passed_args->changed_env = delete_node_at_An_index(&(passed_args->my_env), i);
			i = 0;
			node = passed_args->my_env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (passed_args->changed_env);
}



