#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: The argument structure is used to maintain potential arguments.
 * constant function prototype specifies a function won't modify a variable.
 * Return: function terminates the program with a specified exit status.
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;
	int i = 0;

	if (info->argv[1]) /* If there is an exit argument */
	{
		exitcheck = _erratoi(info->argv[1]);
		while (info->argv[1][i])
		{
			if (info->argv[1][i] < '0' || info->argv[1][i] > '9')
			{
				info->status = 2;
				print_error(info, "Illegal number: ");
				_eputs(info->argv[1]);
				_eputchar('\n');
				return (1);
			}
			i++;
		}
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - The function changes the current working directory.
 * @info: A structure used for maintaining potential arguments.
 *	Used to maintain
 *	constant function prototype specifies a function won't modify a variable.
 * Return: Always (0)
 */
int _mycd(info_t *info)
{
	char *t, *dir, buffer[1024];
	int chdir_ret;

	t = getcwd(buffer, 1024);
	if (!t)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(t);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - function prints help information about shell built-ins.
 * @info: pointer refers to a struct containing function args
 *
 * Return: Always (0)
 */
int _myhelp(info_t *info)
{
	char **arg_array = info->argv;

	_puts("help call works. The function has not been implemented yet.\n");

	if (0) /* temporary att_unused workaround */
		_puts(*arg_array);

	return (0);
}
