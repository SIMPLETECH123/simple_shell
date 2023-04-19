#include "s_shell.h"
/**
 * execmd1 - Using execve to execute the command
 * @argv:arguement
 **/

void execmd1(char **argv)
{
	char *command = NULL;

	if (argv)
	{
		/* get the command */
		command = argv[0];

		/* execute the command with execve */
		if (execve(command, argv, NULL) == -1)
		{
			perror("Error:");
		}
	}
}
