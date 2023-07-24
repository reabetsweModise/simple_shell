#include "shell.h"


/**
 * hsh -This Function main shell loop
 * @info: the parameter & return info struct
 * @av:This parameter argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(info_t *info, char **av)
{
	ssize_t value_returned = 0;
	int builtin_return = 0;

	while (value_returned != -1 && builtin_return != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		value_returned = get_input(info);
		if (value_returned != -1)
		{
			set_info(info, av);
			builtin_return = find_builtin(info);
			if (builtin_return == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_return == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_return);
}

/**
 * find_builtin - This Function finds a builtin command
 * @info: the parameter & return info struct
 * Return: - 1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */

int find_builtin(info_t *info)
{
	int loop_count, builtin_return = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (loop_count = 0; builtintbl[loop_count].type; loop_count++)
		if (_strcmp(info->argv[0], builtintbl[loop_count].type) == 0)
		{
			info->line_count++;
			builtin_return = builtintbl[loop_count].func(info);
			break;
		}
	return (builtin_return);
}

/**
 * find_cmd -This Function finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int loop_count, second_counter;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (loop_count = 0, second_counter = 0; info->arg[loop_count]; loop_count++)
		if (!is_delim(info->arg[loop_count], " \t\n"))
			second_counter++;
	if (!second_counter)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd -This Function forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

