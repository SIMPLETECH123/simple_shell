#include "s_shell.h"
/**
 * getlocat - function that get thr location of a path
 * @command: command
 * Return: path
 */
char *getlocat(char *command)
{
	char *path, *path_cp, *path_token, *file_path;
	int command_len, dir_len;
	struct stat buff;

	path = getenv("PATH");
	if (path)
	{
		path_cp = strdup(path);
		command_len = strlen(command);
		path_token = strtok(path_cp, ":");
		while (path_token != NULL)
		{
			dir_len = strlen(path_token);
			file_path = malloc(command_len + dir_len + 2);
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");
			/*test if path exist*/
			if (stat(file_path, &buff) == 0)
			{
				free(path_cp);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_cp);
		if (stat(command, &buff) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	return (NULL);
}
