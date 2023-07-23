#include "shell.h"

/**
 * ask_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @passed_args: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int ask_history(var_list *passed_args)
{
	print_Mylinked_list(passed_args->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @passed_args: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(var_list *passed_args, char *str)
{
	char *myPtr, c;
	int ret;

	myPtr = _strchr(str, '=');
	if (!myPtr)
		return (1);
	c = *myPtr;
	*myPtr = 0;
	ret = delete_node_at_An_index(&(passed_args->alias),
		get_node_at_this_index(passed_args->alias, prefix_of_node(passed_args->alias, str, -1)));
	*myPtr = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @passed_args: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(var_list *passed_args, char *str)
{
	char *myPtr;

	myPtr = _strchr(str, '=');
	if (!myPtr)
		return (1);
	if (!*++myPtr)
		return (unset_alias(passed_args, str));

	unset_alias(passed_args, str);
	return (add_node_at_end(&(passed_args->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(my_list *node)
{
	char *ptr = NULL, *nPtr = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (nPtr = node->str; nPtr <= ptr; nPtr++)
		_putchar(*nPtr);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * ask_alias - mimics the alias builtin_commands (man alias)
 * @passed_args: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int ask_alias(var_list *passed_args)
{
	int i = 0;
	char *nPt = NULL;
	my_list *node = NULL;

	if (passed_args->arg_count == 1)
	{
		node = passed_args->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; passed_args->argv_array[i]; i++)
	{
		nPt = _strchr(passed_args->argv_array[i], '=');
		if (nPt)
			set_alias(passed_args, passed_args->argv_array[i]);
		else
			print_alias(prefix_of_node(passed_args->alias, passed_args->argv_array[i], '='));
	}

	return (0);
}
