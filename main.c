#include "s_shell.h"

/**
 * main - code to check
 * @argc:number of arguement
 * @argv:array of arguement
 * Return: 0 always.
 **/

int main(int argc, char **argv)
{
	/*printing a prompt*/
	char *prompt = "(myshell) $ ";
	char *prtline, *prtline_copy = NULL;
	const char *delim = " \n";
	size_t n = 0;
	ssize_t nchar_read;
	char *token;
	int i, token_num = 0;

	/* declaring void variable*/
	(void)argc;

	while (1)
	{
		printf("%s", prompt);
		/*read and print what user types out*/
		nchar_read = getline(&prtline, &n, stdin);
		/* check if the getline function
		 * failed or reached EOF or user use CTRL + D */
		if (nchar_read == -1)
		{
			printf("Exit shell...\n");
			return (-1);
		}
		prtline_copy = malloc(sizeof(char) * nchar_read);
		if (prtline_copy == NULL)
		{
			perror("tsh: memory allocation error");
			return (-1);
		}
		strcpy(prtline_copy, prtline);
		/* split sting into array of word*/
		token = strtok(prtline, delim);
		/*count number of token*/
		while (token != NULL)
		{
			token_num++;
			token = strtok(NULL, delim);
		}
		token_num++;
		/*allocate memory to store token*/
		argv = malloc(sizeof(char) * token_num);
		/* Store each token in the argv array */
		token = strtok(prtline_copy, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;
		/*execute the command*/
		execmd1(argv);
	}
	free(prtline_copy);
	free(prtline);
	return (0);
}
