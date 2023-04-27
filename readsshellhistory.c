#include "shell.h"

/**
 * get_history_file - history file is gotten
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */
char *get_history_file(info_t *info)
{
	char *dir, *file_path;
	size_t dir_len, file_len;

	dir = _getenv(info, "HOME=");
	if (!dir)
	{
		return (NULL);
	}

	dir_len = _strlen(dir);
	file_len = _strlen(HIST_FILE);

	file_path = malloc(sizeof(char) * (dir_len + file_len + 2));
	if (!file_path)
	{
		return (NULL);
	}

	_strncpy(file_path, dir, dir_len);
	file_path[dir_len] = '/';
	_strncpy(file_path + dir_len + 1, HIST_FILE, file_len);
	file_path[dir_len + file_len + 1] = '\0';

	return (file_path);
}

/**
 * write_history - shell history to a file is written
 * @info: the parameter struct
 *
 * Return: success (1), failure (-1)
 */
int write_history(info_t *info)
{
	int file_descp;
	char *filename;
	list_t *node;

	filename = get_history_file(info);
	if (!filename)
	{
		return (-1);
	}

	file_descp = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(filename);
	if (file_descp < 0)
	{
		return (-1);
	}

	for (node = info->history; node; node = node->next)
	{
		if (_putsfd(node->str, file_descp) < 0 || _putfd('\n', file_descp) < 0)
		{
			close(file_descp);
			return (-1);
		}
	}

	if (_putfd(BUF_FLUSH, file_descp) < 0)
	{
		close(file_descp);
		return (-1);
	}

	close(file_descp);
	return (1);
}

/**
 * read_history - history of file will be read by this function
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	char *filename = get_history_file(info);

	if (!filename)
	{
		return (0);
	}

	FILE *file = fopen(filename, "r");

	free(filename);
	if (!file)
	{
		return (0);
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int linecount = 0;

	while ((read = getline(&line, &len, file)) != -1)
	{
		if (read > 0 && line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
			build_history_list(info, line, linecount++);
		}
	}
	free(line);
	fclose(file);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
	{
		delete_at_index(&(info->history), 0);
	}
	renumber_history(info);

	return (info->histcount);
}

/**
 * build_history_list - function that adds entry to a history linked list
 * @info: parameter struct
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always(0)
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	node_add_end(&(info->history), buf, linecount);

	return (0);
}

/**
 * renumber_history - function renumbering history linked list after changes
 * @info: pointer to the info_t struct
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node;

	int count = 0;

	for (node = info->history; node != NULL; node = node->next)
	{
		node->num = count++;
	}

	info->histcount = count;

	return (count);
}
