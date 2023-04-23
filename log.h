#ifndef LOG
#define LOG

#include "shell.h"

#define LOGFILE ".simple_shell_history"
#define MAXLOGSIZE 4096
#define MAXBUFREAD 1024

int add_log(sev_t *sev);
int write_log(sev_t *sev);
int get_log_count(sev_t *sev);

#endif
