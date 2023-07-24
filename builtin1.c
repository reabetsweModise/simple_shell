#include "shell.h"

/**
 * _myhistory -This Function displays the history list,
 * one command by line, preceded
 *  with line numbers, starting at 0.
 * @info:This parameter structure containing potential arguments.
 * Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
	int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias -This Function sets alias to string
 * @info:This parameter struct
 * @str:This parameter  string alias
 *
 * Return: 0 (success), 1 (error)
 */
int unset_alias(info_t *info, char *str)
{
	char *pointer, h;
	int my_ret;

	pointer = _strchr(str, '=');
	if (!pointer)
		return (1);
	h = *pointer;
	*pointer = 0;
	my_ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*pointer = h;
	return (my_ret);
}

/**
 * set_alias -This Function sets alias to string
 * @info:This parameter struct
 * @str:This parameter the string alias
 *
 * Return:0 success, 1 error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias -This Function prints an alias string
 * @node:This parameter the alias node
 * Return: 0 success, 1 error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias -This Function mimics the alias builtin (man alias)
 * @info:This parameter Structure containing potential arguments.
 * Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int h = 0;
	char *pointer = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (h = 1; info->argv[h]; h++)
	{
		pointer = _strchr(info->argv[h], '=');
		if (pointer)
			set_alias(info, info->argv[h]);
		else
		print_alias(node_starts_with(info->alias, info->argv[h], '='));
	}
	return (0);
}


