#include "s_shell.h"
/**
 * execmd1 - Using execve to execute the command
 * @argv:arguement
 **/

void execmd1(char **argv)
{
	char *command = NULL, *act_command = NULL;

	if (argv)
	{
		/* get the command */
		command = argv[0];
		/*generate pathbefore passing it*/
		act_command = getlocat(command);
		/* execute the command with execve */
		if (execve(act_command, argv, NULL) == -1)
		{
			perror("Error:");
		}
	}
}
