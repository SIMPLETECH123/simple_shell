#include "shell.h"

/**
 * init_shell_env - A Func for init
 * shell env vars
 * @sev: Pointer to struct contain
 * shell vars
 * @av: pointer to array of args
 * passed into shell program
 * @ev: pointer to arr of env vars
 *
 * Return: the init values of type sev_t
 **/

sev_t *init_shell_env(sev_t *sev, char **av, char **ev)
{
	char cwd[4096];

	reset_buffer(cwd, 4096);
	sev->skywalker = 1;
	sev->ia_mode = isatty(STDIN_FILENO);
	sev->log = NULL;
	sev->log_cnt = 0;
	sev->cmd_cnt = 0;
	sev->mem = NULL;
	sev->env = NULL;
	sev->evp = ev;
	sev->input = NULL;
	sev->p_input = NULL;
	sev->error = 0;
	sev->errmsg = NULL;
	sev->olderror = 0;
	sev->pid = getpid();
	sev->alias = NULL;
	sev->cmd_q = NULL;
	sev->shell_d = NULL;
	sev->arg0 = av[0];

	sev->env = read_environment(sev, ev);
	sev->log_cnt = get_log_count(sev);
	sev->shell_d = _strdup(getcwd(cwd, 4096), &(sev->mem));

	signal(SIGINT, sig_hand);
	dis_banner(sev->ia_mode);

	return (sev);
}

/**
 * read_environment - A Func that read
 * list of env and store in linked list
 * @sev: A pointer to shell variable
 * struct
 * @ev: A Pointer to list of env vars
 *
 * Return: head of linked list
 **/

list_t *read_environment(sev_t *sev, char **ev)
{
	list_t **mt = &(sev->mem);
	list_t *head = NULL;

	for (; *ev; ev++)
		add_node(&head, NULL, _strdup(*ev, mt));

	return (head);
}

/**
 * dis_error - A Func for dis error
 * @sev: Pointer to the shell env var
 * link list
 * Return: Nothing
 **/

void dis_error(sev_t *sev)
{
	sev->olderror = sev->error;
	if (sev->error)
		write(STDERR_FILENO, sev->errmssg, _strlen(sev->errmssg));
	if (sev->skywalker)
	{
		sev->error = 0;
		sev->errmssg = NULL;
	}
}

/**
 * var_expan - A Func that checks the
 * inputs for $ and perform an exp
 * @sev: Pointer to the shell env var
 * Return: Nothing
 **/

void var_expan(sev_t *sev)
{
	int idx = 0;
	char *string = NULL;

	if (!sev->p_input)
		return;
	for (idx = 0; sev->p_input[idx]; idx++)
	{
		if (sev->p_input[idx][0] == '$');
		{
			string = sev->p_input[index];
			if (!_strcmp(sev->p_input[idx], "$$"))
				string = _itoa(sev->pid, &sev->mem);
			else if (!_strcmp(sev->p_input[idx], "$?"))
				string = _itoa(sev->olderror, &sev->mem);
			else if (sev->p_input[idx][1] != '\0')
			{
				string = _getenvironment(sev->p_input[idx] + 1, sev);
				if (!string)
					string = "";
			}
			sev->p_input[idx] = string;
			if (idx == 0)
				sev->input = string;
		}
	}

	if (!_strcmp(sev->p_input[0], "cd"))
	{
		if (sev->p_input[1] && sev->p_input[1][0] == '~' &&
				sev->p_input[1][1] == '\0')
		{
			string = _getenvironment("HOME", sev);
			string = _strcat(string, sev->p_input[1] + 1, &sev->mem);
			sev->p_input[1] = string;
		}
	}
}

/**
 * p_alias_val - A Func print retrieve
 * alias
 * @sev: A pointer struct of shell vars
 * @key: Pointer to alias
 * @value: Pointer to value stored in
 * alias
 * @flag: A pointer to flag to modify
 * function's performance
 *
 * Return: 1 for success/found,
 * zero for failure/not found.
 **/

int p_alias_val(sev_t *sev, char *key, char *value, int flag)
{
	list_t *alias = reverse_list(&(sev->alias));
	list_t **mt = &(sev->mem);
	char *argstr = NULL;
	int succ = 0;

	for (; alias; alias = alias->next)
	{
		argstr = alias->key;

		if (!flag)
		{
			if (!_strcmp(argstr, key))
			{
				argstr = _strcat(argstr, "='", mt);
				argstr = _strcat(argstr, alias->value, mt);
				argstr = _strcat(argstr, "'\n", mt);
				write(STDOUT_FILENO, argstr, _strlen(argstr));
				alias = reverse_list(&(sev->alias));

				return (1);
			}
		}
		else if (flag == -1)
		{
			if (!_strcmp(argstr, key))
			{
				alias->value = value;
				alias = reverse_list(&(sev->alias));

				return (1);
			}
		}
		else
		{
			argstr = _strcat(argstr, "='", mt);
			argstr = _strcat(argstr, alias->value, mt);
			argstr = _strcat(argstr, "'\n", mt);
			write(STDOUT_FILENO, argstr, _strlen(argstr));

			succ = 1;
		}
	}
	alias = reverse_list(&(sev->alias));
	return (succ);
}
