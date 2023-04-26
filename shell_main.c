#include "shell.h"

/**
 * main - main function
 * @acc: argument count
 * @argv: argument vector
 * Return: Returns 0 on success and 1 on error
 */

int main(int acc, char **argv)
{
	info_t infor[] = { INFO_INIT };
	int dg = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (dg)
		: "r" (dg));

	if (acc == 2)
	{
		dg = open(argv[1] < O_RDONLY);
		if (dg == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argv[0]);
				_eputs(": 0: Can't open ");
				_eputs(argv[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infor->readfd = dg;
	}
	populate_env_list(infor);
	read_history(infor);
	hsh(infor, argv);

	return (EXIT_SUCCESS);
}
