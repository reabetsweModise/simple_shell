#include "shell.h"

/**
 * _myenv -This Function prints the current environment
 * @info:This parameter Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
	int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv -This Function gets the value of an environ variable
 * @info:This parameter Structure containing potential arguments.
 * Used to maintain
 * @name:This parameter env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
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
 * _mysetenv -This Function initialize a new environment variable,
 *  or modify an existing one
 * @info:This parameter Structure containing potential arguments.
	Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv -This Function Remove an environment variable
 * @info:This parameter Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int index;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (index = 1; index <= info->argc; index++)
		_unsetenv(info, info->argv[index]);

	return (0);

}

/**
 * populate_env_list -This Function populates env linked list
 * @info:This parameter Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	llist_t *n = NULL;
	size_t index;

	for (index = 0; environ[index]; index++)
		add_node_end(&n, environ[index], 0);
	info->env = n;
	return (0);

}
