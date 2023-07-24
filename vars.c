#include "shell.h"

/**
 * is_chain -This Function test if current char in buffer is a chain delimeter
 * @info:This parameter the parameter struct
 * @buf:This parameter the char buffer
 * @p:This parameter address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t loop_count_2 = *p;

	if (buf[loop_count_2] == '|' && buf[loop_count_2 + 1] == '|')
	{
		buf[loop_count_2] = 0;
		loop_count_2++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[loop_count_2] == '&' && buf[loop_count_2 + 1] == '&')
	{
		buf[loop_count_2] = 0;
		loop_count_2++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[loop_count_2] == ';') /* found end of this command */
	{
		buf[loop_count_2] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = loop_count_2;
	return (1);
}

/**
 * check_chain -This Function checks we
 * should continue chaining based on last status
 * @info:the parameter struct
 * @buf:This parameter the char buffer
 * @p:This parameter address of current position in buf
 * @i:This parameter starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t loop_count_2 = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			loop_count_2 = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			loop_count_2 = len;
		}
	}

	*p = loop_count_2;
}

/**
 * replace_alias -This Function replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_alias(info_t *info)
{
	int loop_count;
	list_t *node;
	char *p;

	for (loop_count = 0; loop_count < 10; loop_count++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars -This Function replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_vars(info_t *info)
{
	int loop_count = 0;
	list_t *node;

	for (loop_count = 0; info->argv[loop_count]; loop_count++)
	{
		if (info->argv[loop_count][0] != '$' || !info->argv[loop_count][1])
			continue;

		if (!_strcmp(info->argv[loop_count], "$?"))
		{
			replace_string(&(info->argv[loop_count]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[loop_count], "$$"))
		{
			replace_string(&(info->argv[loop_count]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[loop_count][1], '=');
		if (node)
		{
			replace_string(&(info->argv[loop_count]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[loop_count], _strdup(""));

	}
	return (0);
}

/**
 * replace_string -This Function replaces string
 * @old:This parameter address of old string
 * @new:This parameter new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

