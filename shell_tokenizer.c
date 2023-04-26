#include "shell.h"

/**
 * str_to_word - converts string to words
 * @string: parameter 1
 * @deli: parameter 2
 * Return: Null on failure or address of the strings on success
 */

char **str_to_word(char *string, char *deli)
{
	int a, b;
	int c, d, num = 0;
	char **temp;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (deli == NULL)
		deli = " ";
	for (a = 0; string[a] != '\0'; a++)
		if (is_delim(string[a], deli) && (is_delim(string[a + 1], deli)
					|| !string[a + 1]))
			num++;
	if (num == 0)
		return (NULL);
	temp = malloc(sizeof(char *) * (1 + num));
	if (temp == NULL)
		return (NULL);
	for (a = 0, b = 0; b < num; b++)
		while (is_delim(string[a], deli))
			a++;
		c = 0;
		while (!is_delim(string[a + c], deli) && string[a + c])
			c++;
		temp[b] = malloc(sizeof(char) * (c + 1));
		if (temp[j] == NULL)
		{
			for (c = 0; c < b; c++)
				free(temp[c]);
			free(temp);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			temp[b][d] = string[a++];
		temp[b][d] = 0;
	}
	temp[b] = NULL;

	return (temp);
}

/**
 * str_to_word2 - converts string to words
 * @strng: parameter 1
 * @deli: parameter 2
 * Return: Null on failure or address of the strings on success
 */

char **str_to_word2(char *strng, char *deli)
{
	int i, j, k, m, len = 0;
	char **temp;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	for (i = 0; strng[i] != '\0'; i++)
		if ((strng[i] != deli && strng[i + 1] == deli) ||
			(strng[i] != deli && !strng[i + 1]) || strng[i + 1] == deli)
			len++;
	if (len == 0)
		return (NULL);
	temp = malloc(sizeof(char *) * (1 + len));
	if (temp == NULL)
		return (NULL);
	for (i = 0, j = 0; j < len; j++)
	{
		while (strng[i] == deli && strng[i] != deli)
			i++;
		k = 0;
		while (strng[i + k] != deli && strng[i + k]
				&& strng[i + k] != deli)
			k++;
		temp[j] = malloc(sizeof(char) * (k + 1));
		if (temp[j] == NULL)
		{
			for (k = 0; k < j; k++)
				free(temp[k]);
			free(temp);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			temp[j][m] = strng[i++];
		temp[j][m] = 0;
	}
	temp[j] = NULL;

	return (temp);
}
