include "error.h"

/**
 * fnotfound - function that construct the error mess
 * for file not found
 * @sev: pointer to the shell environ var
 * Return: the constructed error mess
 **/

char *fnotfound(sev_t *sev)
{
char *errmssg = NULL;

 errmssg = _strcat(sev->arg0, COLON, &sev->mem);
 errmssg = _strcat(errmssg, SPACE, &sev->mem);
 errmssg = _strcat(errmssg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
 errmssg = _strcat(errmssg, COLON, &sev->mem);
 errmssg = _strcat(errmssg, SPACE, &sev->mem);
 errmssg = _strcat(errmssg, sev->input, &sev->mem);
 errmssg = _strcat(errmssg, COLON, &sev->mem);
 errmssg = _strcat(errmssg, SPACE, &sev->mem);
 errmssg = _strcat(errmssg, "not found", &sev->mem);
 errmssg = _strcat(errmssg, "\n", &sev->mem);
 sev->errmssg = errmssg;

 return (errmssg);
}

/**
 * illnum - function that constructs the error mess
 * for the illegal exit num.
 * @sev: pointer to the shell environ var
 * Return: the constructed error mess
 **/

char *illnum(sev_t *sev)
{
	char *errmssg = NULL;

 errmssg = _strcat(sev->arg0, COLON, &sev->mem);
 errmssg = _strcat(errmssg, SPACE, &sev->mem);
 errmssg = _strcat(errmssg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
 errmssg = _strcat(errmssg, COLON, &sev->mem);
 errmssg = _strcat(errmssg, SPACE, &sev->mem);
 errmssg = _strcat(errmssg, sev->input, &sev->mem);
 errmssg = _strcat(errmssg, COLON, &sev->mem);
 errmssg = _strcat(errmssg, SPACE, &sev->mem);
 errmssg = _strcat(errmssg, "Illegal number: ", &sev->mem);
 errmssg = _strcat(errmssg, sev->p_input[1], &sev->mem);
 errmssg = _strcat(errmssg, "\n", &sev->mem);
 sev->errmssg = errmssg;

 return (errmssg);
}

/**
 * perdenied - a function that constructs the permission.
 * denied mess
 * @sev: pointer to the shell environ var struct
 * Return: the constructed error mess
 **/

char *perdenied(sev_t *sev)
{
 char *errmssg = NULL;

  errmssg = _strcat(sev->arg0, COLON, &sev->mem);
  errmssg = _strcat(errmssg, SPACE, &sev->mem);
  errmssg = _strcat(errmssg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
  errmssg = _strcat(errmsg, COLON, &sev->mem);
  errmssg = _strcat(errmssg, SPACE, &sev->mem);
  errmssg = _strcat(errmssg, sev->input, &sev->mem);
  errmssg = _strcat(errmssg, COLON, &sev->mem);
  errmssg = _strcat(errmssg, SPACE, &sev->mem);
  errmssg = _strcat(errmssg, "Permission denied", &sev->mem);
  errmssg = _strcat(errmssg, "\n", &sev->mem);
  sev->errmssg = errmssg;

  return (errmssg);
}

/**
 * invaldir - a function that contructs invalid.
 * dir error mess
 * @sev: struct that contain shell vars
 * Description: the function creates error mess based.
 * on args based on sev.
 * Return: the constructed error mess
 **/

char *invaldir(sev_t *sev)
{
  char *errmssg = NULL;

  errmssg = _strcat(sev->arg0, COLON, &sev->mem);
  errmssg = _strcat(errmssg, SPACE, &sev->mem);
  errmssg = _strcat(errmssg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
  errmssg = _strcat(errmssg, COLON, &sev->mem);
  errmssg = _strcat(errmssg, SPACE, &sev->mem);
  errmssg = _strcat(errmssg, sev->input, &sev->mem);
  errmssg = _strcat(errmssg, COLON, &sev->mem);
  errmssg = _strcat(errmssg, SPACE, &sev->mem);
  errmssg = _strcat(errmssg, "can't cd to ", &sev->mem);
  errmssg = _strcat(errmssg, (sev->p_input)[1], &sev->mem);
  errmssg = _strcat(errmssg, "\n", &sev->mem);
  sev->errmssg = errmssg;

  return (errmssg);
}

/**
 * invalalias - a function that constructs invalid
 * alias error mess
 * @sev: struct that contain shell vars
 * @node: index of desired key
 *
 * Description: Function creates error mess based on
 * args based on sev.
 * Return: the constructed error mess
 **/

char *invalalias(sev_t *sev, int node)
{
  char *errmssg = NULL;
  int p = node;

  errmssg = _strcat("alias: ", (sev->p_input)[p++], &sev->mem);
  errmssg = _strcat(errmssg, " not found", &sev->mem);
  errmssg = _strcat(errmssg, "\n", &sev->mem);
  sev->errmssg = errmssg;

  return (errmssg);
}
