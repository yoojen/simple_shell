#include "shell.h"


/**
 * add_node_at_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
my_list *add_node_at_end(my_list **head, const char *strings, int num)
{
	my_list *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(my_list));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(my_list));
	new_node->num = num;
	if (strings)
	{
		new_node->str = _strdup(strings);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_node_list - prints only the str element of a my_list linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_node_list(const my_list *hed)
{
	size_t i = 0;

	while (hed)
	{
		_puts(hed->str ? hed->str : "(nil)");
		_puts("\n");
		hed = hed->next;
		i++;
	}
	return (i);
}

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
my_list *add_node(my_list **head, const char *str, int num)
{
	my_list *head_new;

	if (!head)
		return (NULL);
	head_new = malloc(sizeof(my_list));
	if (!head_new)
		return (NULL);
	_memset((void *)head_new, 0, sizeof(my_list));
	head_new->num = num;
	if (str)
	{
		head_new->str = _strdup(str);
		if (!head_new->str)
		{
			free(head_new);
			return (NULL);
		}
	}
	head_new->next = *head;
	*head = head_new;
	return (head_new);
}

/**
 * free_my_nodes - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_my_nodes(my_list **ptrOf_head)
{
	my_list *node, *head_node, *head_itself;

	if (!ptrOf_head || !*ptrOf_head)
		return;
	head_itself = *ptrOf_head;
	node = head_itself;
	while (node)
	{
		head_node = node->next;
		free(node->str);
		free(node);
		node = head_node;
	}
	*ptrOf_head = NULL;
}
/**
 * delete_node_at_An_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_An_index(my_list **head, unsigned int index)
{
	my_list *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}


