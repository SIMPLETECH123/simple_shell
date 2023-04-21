#include "../shell.h"

/* prototypes for shellhelper01.c file */
void sig_hand(int signum);
void dis_prompt(sev_t sev);
char *getcom(sev_t *sev);
char **make_array_str(char *s, const char *delim, sev_t *sev);
int actions(sev_t *sev);

/* prototypes for shellhelper02.c file */
char *_getenvironment(char *envar, sev_t *sev);
char *pathfind(sev_t *sev);
void cl_sev(sev_t *sev);
char **make_evp_array(sev_t *sev);
int _setenv_help(sev_t *sev, char *tofind, char *cwd);

/* prototypes for shellhelper03.c file */
sev_t *init_shell_env(sev_t *sev, char **av, char **ev);
list_t *read_environment(sev_t *sev, char **ev);
void dis_error(sev_t *sev);
void var_expan(sev_t *sev);
int p_alias_val(sev_t *sev, char *key, char *value, int flag);

/* prototypes for shellhelper04.c file */
void process_inputs(char *cmd, sev_t *sev);
void dis_banner(int ia_mode);
void checker_alias(sev_t *sev);
