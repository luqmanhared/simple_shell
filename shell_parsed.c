#include "shell.h"

/**
 * is_exec - main function
 * @infor: parameter 1
 * @pt: parameter 2
 * Return: Returns 1 if exec or 0 if not
 */

int is_exec(info_t *infor, char *pt)
{
	struct stat st;

	(void)infor;

	if (!pt || stat(pt, &st))
		return (0);
	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * char_dupl - main function
 * @strpt: parameter 1
 * @strt_p: parameter 2
 * @stop_p: parameter 3
 * Return: Returns address to the a buffer
 */

char char_dupl(char *strpt, int strt_p, int stop_p)
{
	static char buffer[1024];
	int index = 0;
	int x = 0;

	for (x = 0; index = strt_p; index < stop_p; index++)
		if (strpt[index] != ':')
			buffer[x++] = strpt[index];
	buffer[x] = 0;
	return (buffer);
}

/**
 * find_path -main function
 * @infor: parameter 1
 * @strpt: parameter 2
 * @command: parameter 3
 * Return: Returns the path of the command if found or NULL
 */

char *find_path(info_t *infor, char *strpt, char *command)
{
	int ind = 0;
	int current = 0;
	char *file;

	if (strpt == NULL)
		return (NULL);
	if ((_strlen(command) > 2) && start_with(command, "./"))
	{
		if (is_exec(infor, command))
			return (command);
	}
	while (1)
	{
		if (!strpt[ind] || strpt[ind] == ':')
		{
			file = char_dupl(strpt, current, ind);
			if (!*file)
				_strcat(file, command);
			else
			{
				_strcat(file, "/");
				_strcat(file, command);
			}
			if (is_exec(infor, file))
				return (file);
			if (!strpt[ind])
				break;
			current = ind;
		}
		ind++;
	}
	return (NULL);
}
