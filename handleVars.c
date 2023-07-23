#include "shell.h"

/**
 * return_is_chain - test if current char in buffer is a chain delimeter
 * @passed_args: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int return_is_chain(var_list *passed_args, char *buffer, size_t *ptr)
{
	size_t j = *ptr;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		passed_args->command_buffer_type = COMMAND_ORAL;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		passed_args->command_buffer_type = COMMAND_AND_;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		passed_args->command_buffer_type = CHAIN_COMMAND;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}

/**
 * checkFor_Bchain - checks we should continue chaining based on last status
 * @passed_args: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checkFor_Bchain(var_list *passed_args, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (passed_args->command_buffer_type == COMMAND_AND_)
	{
		if (passed_args->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (passed_args->command_buffer_type == COMMAND_ORAL)
	{
		if (!passed_args->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * change_placeOf_alias - replaces an aliases in the tokenized string
 * @passed_args: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_placeOf_alias(var_list *passed_args)
{
	int j;
	my_list *node;
	char *p;

	for (j = 0; j < 10; j++)
	{
		node = prefix_of_node(passed_args->alias, passed_args->argv_array[0], '=');
		if (!node)
			return (0);
		free(passed_args->argv_array[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		passed_args->argv_array[0] = p;
	}
	return (1);
}

/**
 * change_placeOf_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_placeOf_string(char **last, char *new)
{
	free(*last);
	*last = new;
	return (1);
}

/**
 * change_placeOf_vars - replaces vars in the tokenized string
 * @passed_args: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int change_placeOf_vars(var_list *passed_args)
{
	int j = 0;
	my_list *node;

	for (j = 0; passed_args->argv_array[j]; j++)
	{
		if (passed_args->argv_array[j][0] != '$' || !passed_args->argv_array[j][1])
			continue;

		if (!_strcmp(passed_args->argv_array[j], "$?"))
		{
			change_placeOf_string(&(passed_args->argv_array[j]),
				_strdup(conversationof_number(passed_args->status, 10, 0)));
			continue;
		}
		if (!_strcmp(passed_args->argv_array[j], "$$"))
		{
			change_placeOf_string(&(passed_args->argv_array[j]),
				_strdup(conversationof_number(getpid(), 10, 0)));
			continue;
		}
		node = prefix_of_node(passed_args->my_env, &passed_args->argv_array[j][1], '=');
		if (node)
		{
			change_placeOf_string(&(passed_args->argv_array[j]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		change_placeOf_string(&passed_args->argv_array[j], _strdup(""));

	}
	return (0);
}



