#define _GNU_SOURCE
#include "nlog.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define N_LOG_LEN 4096

/* Terminal colors */
#ifdef __linux__
#define FG_RED "\033[91m"
#define BG_RED "\033[101m"
#define FG_GREEN "\033[92m"
#define FG_ORANGE "\033[93m"
#define FG_DEFAULT "\033[39m"
#define BG_DEFAULT "\033[49m"
#define FG_BLACK "\033[30m"

#define C_DEFAULT FG_DEFAULT BG_DEFAULT
#define C_FATAL BG_RED FG_BLACK

#elif _WIN32

#define FG_RED ""
#define BG_RED ""
#define FG_GREEN "" 
#define FG_ORANGE ""
#define FG_DEFAULT ""
#define BG_DEFAULT ""
#define FG_BLACK ""

#define C_DEFAULT ""
#define C_FATAL ""

#endif // _WIN32

#define NLOG_STR_LEN 128

static char nlog_str[N_LOG_LEVEL_LEN][NLOG_STR_LEN] = {
    "%s[" FG_RED "FATAL" FG_DEFAULT "]",
    "%s[" FG_RED "ERROR" FG_DEFAULT "]",
    "%s[" FG_ORANGE "WARN" FG_DEFAULT "] ",
    "%s[" FG_GREEN "INFO" FG_DEFAULT "] ",
    "%s[DEBUG]",
    "%s[VBOSE]",
};

static const char* nlog_color[N_LOG_LEVEL_LEN] = {
    C_FATAL,            /* N_FATAL */
    FG_RED,             /* N_ERROR */
    FG_DEFAULT,         /* N_WARN */
    FG_DEFAULT,         /* N_INFO */
    FG_DEFAULT,          /* N_DEBUG */
    FG_DEFAULT          /* N_VBOSE */
};

static enum nlog_level nlevel = N_DEBUG;

void 
nlog_set_level(enum nlog_level level)
{
    nlevel = level;
}

void 
nlog_set_name(const char* name)
{
	for (u32 i = 0; i < N_LOG_LEVEL_LEN; i++)
	{
		char* strd = strdup(nlog_str[i]);
		snprintf(nlog_str[i], NLOG_STR_LEN, strd, name);
		free(strd);
	}
}

void 
nlog_msg(enum nlog_level level, const char* filename, i32 line, const char* format, ...)
{
    if (nlevel < level)
        return;

    char output[N_LOG_LEN];
    FILE* file = (level <= N_WARN) ? stderr : stdout;

    va_list args;
    va_start(args, format);

    vsprintf(output, format, args);

    va_end(args);

    if (filename)
        fprintf(file, "%s [%s:%d]:\t%s", nlog_str[level], filename, line, nlog_color[level]);
    else
        fprintf(file, "%s:\t%s", nlog_str[level], nlog_color[level]);

    fprintf(file, "%s%s%s", nlog_color[level], output, C_DEFAULT);

    fflush(file);
}
