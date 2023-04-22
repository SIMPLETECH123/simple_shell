#include "shell.h"

/**
 * process_inputs - Func takes in user
 * input and parses for multiple cmds
 * Makes a link list and contain all
 * commands and queues it for
 * process.
 * @cmd: Pointer to str input from user
 * @sev: Pointer to the shell env vars
 * Return: Nothing
 **/

void process_inputs(char *cmd, sev_t *sev)
{
  char *token01 = NULL;

  token01 = _strtok(cmd, "\n");
  while (token01)
    {
      add_node(&sev->cmd_q, NULL, _strdup(token01, &sev->mem));
      token01 = _strtok(NULL, "\n");
    }
  reverse_list(&sev->cmd_q);
}

/**
 * check_alias - Func checks if alias
 * exists
 * @sev: Pointer to struct contain
 * shell vars
 * Return: NULL
 **/

void checker_alias(sev_t *sev)
{
  char *input = NULL;
  list_t *alias = sev->alias;
  int fnd = 1;

  if (sev->p_input && alias)
    {
      while (fnd)
	{
	  input = sev->p_input[0];
	  fnd = 0;
	  for (alias = sev->alias; alias; alias = alias->next)
	    {
	      if (!_strcmp(alias->key, input))
		{
		  sev->p_input[0] = alias->value;
		  sev->input = alias->value;
		  fnd = 1;
		}
	      if (!_strcmp(alias->key, alias->value))
		fnd = 0;
	    }
	  if (!fnd)
	    break;
	}
    }
}

/**
 * dis_banner - Func displays the shell
 * banner
 * @ia_mode: Pointer to interactive mode
 * flag
 * Return - Nothing
 **/

void dis_banner(int ia_mode)
{
  if (!ia_mode)
    return;
  NEWLINE;
  write(STDOUT_FILENO, "AUTHORS:\n", 9);
  write(STDOUT_FILENO, "\tTimilehin Caleb <@gmail.com>\n", 40);
  write(STDOUT_FILENO, "\tSamuel Philip <sammyp791.sp37@gmail.com>\n\n", 40);
  write(STDOUT_FILENO, "=======================", 23);
  write(STDOUT_FILENO, "=======================\n", 24);
  write(STDOUT_FILENO, "     WELCOME TO  ", 26);
  write(STDOUT_FILENO, "  THE SHELL    \n", 22);
  write(STDOUT_FILENO, "=======================", 23);
  write(STDOUT_FILENO, "=======================\n", 24);
  NEWLINE;
}
