#include "shell.h"

/**
 * input_buff - will buffer the chained commands
 * @inf: parameter struct
 * @buf: buffer address
 * @len: len var address
 *
 * Return: bytes read
 */
ssize_t input_buff(info_t *inf, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* when nothing is left in buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(inf, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove the trailing newline */
				r--;
			}
			inf->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(inf, *buf, inf->histcount++);
			if (_strchr(*buf, ';'))
			{
				*len = r;
				inf->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - get line and minus newline
 * @inf: theb parameter is struct
 *
 * Return: the bytes read
 */
ssize_t get_input(info_t *inf)
{
	static char *buf; /* this ';' command chain buffer */
	static size_t j, len;
	ssize_t r = 0;
	char **buff_p = &(inf->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buff(inf, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* there are commands left in the chain buffer */
	{
		j = j; /* init new iterator to current buf position */
		p = buf + j; /* get pointer for return */

		void int_chain(int inf, char *buf, size_t *j, size_t len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (chain(inf, buf, &j))
				break;
			j++;
		}

		j = j + 1; /* increment past nulled ';'' */
		if (j >= len) /* reached end of buffer? */
		{
			j = len = 0; /* reset position and length */
			inf->cmd_buf_type = CMD_NORM;
		}

		*buff_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buff_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @inf: parameter struct
 * @buf: buffer
 * @j: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *inf, char *buf, size_t *j)
{
	ssize_t r = 0;

	if (*j > 0)
		return (0);

	r = read(inf->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*j = r;

	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: number of bytes read, or -1 if EOF or error
 */
int _getline(info_t *inf, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;

	if (j == len)
		j = len = 0;

	r = read_buf(inf, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _relloc(p, s, s ? s + k : k + 1);

	if (!new_p)
		return (p ? (free(p), -1) : -1);

	if (s)
		_strncat(new_p, buf + j, k - j);
	else
		_strncpy(new_p, buf + j, k - j + 1);

	s += k - j;
	j = k;
	p = new_p;

	if (length)
		*length = s;

	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
