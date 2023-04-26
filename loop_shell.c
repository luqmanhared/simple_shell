#include "shell.h"

/**
 * hash - The main loop
 * @infor: The return info and parameter struct
 * @argv: The argument for the main function
 * Return: Returns 0 if success, 1 if error or error code
 */

int hash(info_t *infor, char **argv)
{
	ssize_t ret = 0;
	int ret_val = 0;

	while (ret != -1 && ret_val != -2)
	{
		clear_info(infor);
		if (interactive(infor))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		ret = get_input(infor);
		if (ret != -1)
		{
			set_info(infor, argv);
			ret_val = builtin_find(infor);
			if (ret_val == -1)
				find_command(infor);
		}
		else if (interactive(infor))
			_putchar('\n');
		free_info(infor, 0);
	}
	write_history(infor);
	free_info(infor, 1);
	if (!interactive(infor) && infor->status)
		exit(infor->status);
	if (ret_val == -2)
	{
		if (infor->err_num == -1)
			exit(infor->status);
		exit(infor->err_num);
	}
	return (ret_val);
}

/**
 * buitin_find - Helps to find buitin functions
 * @infor: The param and ret value struc
 * Return: Returns 1 if found but not successful
 *		0 if executed successfully
 *		2 if signals exit()
 *		-1 if not found
 */

int buitin_find(info_t *infor)
{
	int ret, ind = -1;
	builtin_table tbl[] = {
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

	for (ind = 0; tbl[ind].type; ind++)
		if (_strcmp(infor->argv[0], tbl[ind].type) == 0)
		{
			infor->line_count++;
			ret = tbl[ind].func(infor);
			break;
		}
	return (ret);
}

/**
 * find_command - Used to find a command
 * @infor: The param and ret struct
 * Return: Nothing
 */

void find_command(info_t *infor)
{
	char *file_path = NULL;
	int ind, x;

	infor->path = infor->argv[0];
	if (infor->linecount_flag == 1)
	{
		infor->line_count++;
		infor->linecount_flag = 0;
	}
	for (ind = 0; x = 0; infor->arg[ind]; ind++)
		if (!is_delim(infor->arg[i], " \t\n"))
			x++;
	if (x == NULL)
		return;

	file_path = find_path(infor, _getenv(infor, "PATH="), infor->argv[0]);
	if (file_path != NULL)
	{
		infor->path = file_path;
		fork_command(infor);
	}
	else
	{
		if ((interactive(infor) || _getenv(infor, "PATH=")
		|| infor->argv[0][0] == '/') && is_cmd(infor, infor->argv[0]))
			fork_command(infor);
		else if (*(infor->arg) != '\n')
		{
			infor->status = 127;
			print_error(infor, "not found\n");
		}
	}
}

/**
 * fork_command - Forks thread (exec) to run command
 * @infor: Struct type info_t
 * Return: Nothing
 */

void fork_command(info_t *infor)
{
	pid_t off_pid;

	off_pid = fork();
	if (off_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (off_pid == 0)
	{
		if (execve(infor->path, infor->argv, get_environ(infor)) == -1)
		{
			free_info(infor, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(infor->status));
		if (WIFEXITED(infor->status))
		{
			infor->status = WEXITSTATUS(infor->status);
			if (infor->status == 126)
				print_error(infor2, "Permission denied\n");
		}
	}
}
