#include "shell.h"



/**
 * linked_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **linked_to_strings(my_list *head)
{
	my_list *node = head;
	size_t i = linked_length(head), j;
	char **strings;
	char *ptr;

	if (!head || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		ptr = malloc(_strlen(node->str) + 1);
		if (!ptr)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		ptr = _strcpy(ptr, node->str);
		strings[i] = ptr;
	}
	strings[i] = NULL;
	return (strings);
}

/**
 * linked_length - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t linked_length(const my_list *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * print_Mylinked_list - prints all elements of a my_list linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_Mylinked_list(const my_list *head)
{
	size_t i = 0;

	while (head)
	{
		_puts(conversationof_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}


/**
 * get_node_at_this_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_at_this_index(my_list *head, my_list *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}

/**
 * prefix_of_node - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
my_list *prefix_of_node(my_list *node, char *my_prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, my_prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


