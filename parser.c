#include "shell.h"

/**
 * is_cmd -This Function determines if a file is an executable command
 * @info:This parameter the info struct
 * @path:This parameter path to the file
 *
 * Return: 1, 0 otherwise
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars -This Function duplicates characters
 * @pathstr:This parameter the PATH string
 * @start:This parameter starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int first_counter = 0, second_counter = 0;

	for (second_counter = 0, first_counter = start;
			first_counter < stop; first_counter++)
		if (pathstr[first_counter] != ':')
			buf[second_counter++] = pathstr[first_counter];
	buf[second_counter] = 0;
	return (buf);
}

/**
 * find_path -This Function finds this cmd in the PATH string
 * @info:This parameter the info struct
 * @pathstr:This parameter the PATH string
 * @cmd:This parameter the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int first_counter = 0, current_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[first_counter] || pathstr[first_counter] == ':')
		{
			path = dup_chars(pathstr, current_pos, first_counter);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[first_counter])
				break;
			current_pos = first_counter;
		}
		first_counter++;
	}
	return (NULL);
}

