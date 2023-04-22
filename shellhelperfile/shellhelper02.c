#include "shell.h"

/**
 * _getenvironment - A func to get env
 * var.
 * @envar: Pointer to target env var
 * @sev: Pointer to struct contain
 * shell vars
 *
 * Description: Func takes a list of
 * env vars and returns env var
 * if found.
 * Return: env var if found; otherwise,
 * NULL
 **/

char *_getenvironment(char *envar, sev_t *sev)
{
	ssize_t t = 0;
	char *fnd = NULL, *str;
	list_t *env = sev->env;

	if (envar && *envar)
	{
		for (; env; env = env->next)
		{
			str = env->value;
			for (t = 0; envar[t] && str[t]; t++)
				if (envar[t] != str[t])
					break;
			if (!envar[t] && str[t] == '=')
			{
				fnd = _strdup(str, &sev->mem);

				return (_strpbrk(fnd, EQUAL) + 1);
			}
		}
	}

	return (NULL);
}

/**
 * pathfind - A func that determine if
 * a command is in path.
 * @sev: Pointer to shell env var struct
 * Return: Path to exec or NULL
 **/

char *pathfind(sev_t *sev)
{
	char *fpath = NULL, *ev_path = _getenvironment("PATH", sev);
	char *cmd = NULL;
	char **pathlist = NULL;
	DIR *pp = NULL;

	if (sev->p_input && sev->p_input[0])
		cmd = sev->p_input[0];
	if (!_strcmp(cmd, "."))
		return (NULL);
	pp = opendir(sev->p_input[0]);

	if (pp)
	{
		closedir(pp);
		sev->error = 126;
		perdenied(sev);

		return (NULL);
	}

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (!access(cmd, F_OK))
		{
			if (!access(cmd, X_OK))
				return (cmd);
			sev->error = 126;
			perdenied(sev);
		}
		else
		{
			if (!sev->error)
			{
				sev->error = 127;

				fnotfound(sev);
			}
		}
		return (NULL);
	}

	if (ev_path)
		pathlist = make_array_str(ev_path, COLON, sev);
	else
	{
		sev->error = 127;
		fnotfound(sev);

		return (NULL);
	}
	if (!pathlist || !*pathlist)
	{
		sev->error = 127;
		fnotfound(sev);

		return (NULL);
	}
	for (; *pathlist; pathlist++)
	{
		fpath = _strcat(*pathlist, FSLASH, &(sev->mem));
		fpath = _strcat(fpath, sev->p_input[0], &(sev->mem));

		if (!access(fpath, X_OK))
		{
			sev->error = 0;

			return (fpath);
		}
		if (!access(fpath, F_OK))
		{
			sev->error = 126;
			perdenied(sev);
		}
		else
		{
			if (!sev->error)
			{
				sev->error = 127;
				fnotfound(sev);
			}
		}
	}
	return (NULL);
}

/**
 * cl_sev - Func that go through and free
 * link lists in the sev
 * @sev: Pointer to the shell env var link list
 * Return: Nothing
 **/

void cl_sev(sev_t *sev)
{
	free_list(&sev->mem, 1);
	free_list(&sev->log, 0);
	free_list(&sev->env, 0);
	free_list(&sev->alias, 0);
	free_list(&sev->cmd_q, 0);
}

/**
 * make_evp_array - A Func that makes the env var
 * array from the in memo copy.
 * @sev: pointer to shell env variable link list
 * Return: Pointer to the constucted env array
 **/

char **make_evp_array(sev_t *sev)
{
	char **evp = NULL;
	int entrs = 0, s = 0;
	list_t *walker = sev->env;

	while (walker)
	{
		entrs++;
		walker = walker->next;
	}
	evp = malloc(sizeof(char *) * (entrs + 1));
	if (!evp)
		return (NULL);
	add_node(&sev->mem, NULL, evp);
	walker = sev->env;

	for (s = 0; walker; s++)
	{
		evp[s] = (char *)walker->value;
		walker = walker->next;
	}

	evp[s] = NULL;

	return (evp);
}

/**
 * _setenv_help - A Func that set data
 * pointer in node
 * @sev: Pointer to struct containing
 * shell variables
 * @tofind: The string to find
 * @strtoappend: The str to append
 * Return: 1 if success, 0 if fail
 **/

int _setenv_help(sev_t *sev, char *tofind, char *strtoappend)
{
	list_t *env = sev->env;
	list_t **mt = &sev->mem;
	char *evstr = NULL;
	unsigned int s = 0;

	for (; env; env = env->next)
	{
		evstr = env->value;
		for (s = 0; s < _strlen(tofind); s++)
			if (tofind[s] != evstr[s])
				break;

		if (!tofind[s])
		{
			tofind = _strcat(tofind, "=", mt);
			tofind = _strcat(tofind, strtoappend, mt);

			env->value = _strdup(tofind, mt);
			return (1);
		}
	}
	return (0);
}
