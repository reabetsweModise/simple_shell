#include "shell.h"

/**
 * list_len -This Function determines length of linked list
 * @h:This parameter pointer to first node
 *
 * Return: size of list
 */
	size_t list_len(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * list_to_strings -This Function returns an array of strings of the list->str
 * @head:This parameter pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t first_counter = list_len(head), second_counter;
	char **strs;
	char *str;

	if (!head || !first_counter)
		return (NULL);
	 strs = malloc(sizeof(char *) * (first_counter + 1));
	if (!strs)
		return (NULL);
	for (first_counter = 0; node; node = node->next, first_counter++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (second_counter = 0; second_counter < first_counter; second_counter++)
				free(strs[second_counter]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[first_counter] = str;
	}
	strs[first_counter] = NULL;
	return (strs);
}


/**
 * print_list -This Function prints all elements of a list_t linked list
 * @h:This parameter pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t index = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * node_starts_with -This Function returns node whose string starts with prefix
 * @node:This parameter pointer to list head
 * @prefix:This parameter string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *my_pointer = NULL;

	while (node)
	{
		my_pointer = starts_with(node->str, prefix);
		if (my_pointer && ((c == -1) || (*my_pointer == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index -This Function gets the index of a node
 * @head:This parameter pointer to list head
 * @node:This parameter pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t loop_count = 0;

	while (head)
	{
		if (head == node)
			return (loop_count);
		head = head->next;
		loop_count++;
	}
	return (-1);
}
