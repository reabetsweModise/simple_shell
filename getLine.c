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
<<<<<<< HEAD
	ssize_t status_returned = 0;
	size_t length_pointer = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		status_returned = _getline(info, buf, &len_p);
=======
		ssize_t r = 0;
		size_t len_p = 0;

		if (!*len)
		{
			free(*buf);
			*buf = NULL;
			signal(SIGINT, sigintHandler);
#if USE_GETLINE
			r = getline(buf, &len_p, stdin);
#else
			r = _getline(info, buf, &len_p);
>>>>>>> e051fc4e5c4e172ac75d805024991e62181364c0
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
<<<<<<< HEAD
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				status_returned--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
=======
				if ((*buf)[r - 1] == '\n')
				{
					(*buf)[r - 1] = '\0';
					r--;
				}
				info->linecount_flag = 1;
				remove_comments(*buf);
				build_history_list(info, *buf, info->histcount++);
				{
					*len = r;
					info->cmd_buf = buf;
				}
			}
		}
		return (r);

>>>>>>> e051fc4e5c4e172ac75d805024991e62181364c0
}

/**
 * get_input -This Function gets a line minus the newline
 * @info:This parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
<<<<<<< HEAD
	static char *buf; /* the ';' command chain buffer */
	static size_t current_pos, j, len;
	ssize_t status_returned = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	status_returned = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
=======
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
>>>>>>> e051fc4e5c4e172ac75d805024991e62181364c0
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

<<<<<<< HEAD
	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
=======
	*buf_p = buf;
	return (r);
>>>>>>> e051fc4e5c4e172ac75d805024991e62181364c0
}

/**
 * read_buf -This Function reads a buffer
 * @info: parameter struct
 * @buf:This parameter buffer
 * @i:This parameter size
 *
 * Return: res
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
<<<<<<< HEAD
	ssize_t status_returned = 0;

	if (*i)
		return (0);
	status_returned = read(info->readfd, buf, READ_BUF_SIZE);
	if (status_returned >= 0)
		*i = status_returned;
	return (status_returned);
=======
	ssize_t my_res = 0;

	if (*i)
		return (0);

	my_res = read(info->readfd, buf, READ_BUF_SIZE);
	if (my_rs >= 0)
		*i = my_res;
	return (my_res);
>>>>>>> e051fc4e5c4e172ac75d805024991e62181364c0
}

/**
 * _getline -This Function gets the next line of input from STDIN
 * @info:This parameter struct
 * @ptr:This parameter address of pointer to buffer, preallocated or NULL
 * @length:This parameter size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
<<<<<<< HEAD
	static size_t current_pos, len;
	size_t cmd_length;
	ssize_t status_returned = 0, cmd_status = 0;
=======
	static size_t index, len;
	size_t K;
	ssize_t R = 0, S = 0;
>>>>>>> e051fc4e5c4e172ac75d805024991e62181364c0
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		S = *length;
	if (index == len)
		index = len = 0;

<<<<<<< HEAD
	status_returned = read_buf(info, buf, &len);
	if (status_returned == -1 || (status_returned == 0 && len == 0))
		return (-1);

	c = _strchr(buf + current_pos, '\n');
	cmd_length = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, cmd_status, cmd_status ?
			cmd_status + cmd_length : cmd_length + 1);
=======
	R = read_buf(info, buf, &len);
	if (R == -1 || (R == 0 && len == 0))
		return (-1);

	c = _strchr(buf + index, '\n');
	K = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, S, S ? S + K : K + 1);
>>>>>>> e051fc4e5c4e172ac75d805024991e62181364c0
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, K - i);
	else
		_strncpy(new_p, buf + i, K - i + 1);

	s += K - i;
	i = K;
	p = new_p;

	if (length)
		*length = S;
	*ptr = p;
	return (S);

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

