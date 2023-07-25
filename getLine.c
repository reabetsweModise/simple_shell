#include "shell.h"

/**
 * input_buf -This Function buffers chained commands
 * @info:This parameter struct
 * @buf:This parameter address of buffer
 * @len:This parameter address of len var
 *
 * Return: bytes read
 */
	ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t status_returned = 0;
	size_t length_pointer = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		status_returned = getline(buf, &length_pointer, stdin);
#else
		status_returned = _getline(info, buf, &length_pointer);
#endif
		if (status_returned > 0)
		{
			if ((*buf)[status_returned - 1] == '\n')
			{
				(*buf)[status_returned - 1] = '\0'; /* remove trailing newline */
				status_returned--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = status_returned;
				info->cmd_buf = buf;
			}
		}
	}
	return (status_returned);
}

/**
 * get_input -This Function gets a line minus the newline
 * @info:This parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t current_pos, j, len;
	ssize_t status_returned = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	status_returned = input_buf(info, &buf, &len);
	if (status_returned == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = current_pos; /* init new iterator to current buf position */
		p = buf + current_pos; /* get pointer for return */

		check_chain(info, buf, &j, current_pos, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		current_pos = j + 1; /* increment past nulled ';'' */
		if (current_pos >= len) /* reached end of buffer? */
		{
			current_pos = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (status_returned); /* return length of buffer from _getline() */
}

/**
 * read_buf -This Function reads a buffer
 * @info: parameter struct
 * @buf:This parameter buffer
 * @current_pos:This parameter size
 *
 * Return: status_returned
 */
ssize_t read_buf(info_t *info, char *buf, size_t *current_pos)
{
	ssize_t status_returned = 0;

	if (*current_pos)
		return (0);
	status_returned = read(info->readfd, buf, READ_BUF_SIZE);
	if (status_returned >= 0)
		*current_pos = status_returned;
	return (status_returned);
}

/**
 * _getline -This Function gets the next line of input from STDIN
 * @info:This parameter struct
 * @ptr:This parameter address of pointer to buffer, preallocated or NULL
 * @length:This parameter size of preallocated ptr buffer if not NULL
 *
 * Return: cmd_status
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t current_pos, len;
	size_t cmd_length;
	ssize_t status_returned = 0, cmd_status = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		cmd_status = *length;
	if (current_pos == len)
		current_pos = len = 0;

	status_returned = read_buf(info, buf, &len);
	if (status_returned == -1 || (status_returned == 0 && len == 0))
		return (-1);

	c = _strchr(buf + current_pos, '\n');
	cmd_length = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, cmd_status, cmd_status ?
			cmd_status + cmd_length : cmd_length + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (cmd_status)
		_strncat(new_p, buf + current_pos, cmd_length - current_pos);
	else
		_strncpy(new_p, buf + current_pos, cmd_length - current_pos + 1);

	cmd_status += cmd_length - current_pos;
	current_pos = cmd_length;
	p = new_p;

	if (length)
		*length = cmd_status;
	*ptr = p;
	return (cmd_status);
}

/**
 * sigintHandler -This Function blocks ctrl-C
 * @sig_num:This parameter the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

