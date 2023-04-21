#include "errors.h"

/**
 * helpfnotfound - A function that create error
 * mess for help
 * @sev: struct that contain shell vars
 * Description: The function create error mess
 * using args in sev.
 * Return: error mess
 **/

char *helpfnotfound(sev_t *sev)
{
  char *errmssg = NULL;
  char *mssg = "-JS: help: no help topics match `";

  errmssg = _strcat(mssg, sev->p_input[1], &sev->mem);
  errmssg = _strcat(errmssg, "'.  Try `help help'.\n", &sev->mem);
  sev->errmssg = errmssg;

  return (errmssg);
}

/**
 * illoptions - Function create error mess for cd
 * @sev: struct contain shell vars
 *
 * Description: The function Create error mess
 . using args in sev.
 * Return: error mess
 **/

char *illoptions(sev_t *sev)
{
  char *errmssg = NULL;
  char charttoprint[2];

  _chartostr(charttoprint, sev->p_input[1][1]);

  errmssg = _strcat(sev->arg0, COLON, &sev->mem);
  errmssg = _strcat(errmssg, SPACE, &sev->mem);
  errmssg = _strcat(errmssg, _itoa(sev->cmd_cnt, &sev->mem), &sev->mem);
  errmssg = _strcat(errmssg, COLON, &sev->mem);
  errmssg = _strcat(errmssg, SPACE, &sev->mem);
  errmssg = _strcat(errmssg, sev->input, &sev->mem);
  errmssg = _strcat(errmssg, COLON, &sev->mem);
  errmssg = _strcat(errmssg, SPACE, &sev->mem);
  errmssg = _strcat(errmssg, "Illegal option ", &sev->mem);
  errmssg = _strcat(errmssg, "-", &sev->mem);
  errmssg = _strcat(errmssg, charttoprint, &sev->mem);
  errmssg = _strcat(errmssg, "\n", &sev->mem);
  sev->errmssg = errmssg;

  return (errmssg);
}

/**
 * invalenv - Function to invalid env
 * @sev: the sev var
 * Return: str
 **/

char *invalenv(sev_t *sev)
{
  char *errmssg = "env: ";

  errmssg = _strcat(errmssg, sev->p_input[1], &sev->mem);
  errmssg = _strcat(errmssg, ": No such file or directory\n", &sev->mem);
  sev->errmssg = errmssg;

  return (errmssg);
}
