#ifndef _NICE_LOG_H_
#define _NICE_LOG_H_

#include "int.h"

enum nlog_level
{
    N_FATAL,
    N_ERROR,
    N_WARN,
    N_INFO,
    N_DEBUG,
    N_VBOSE,

    N_LOG_LEVEL_LEN
};

void nlog_set_level(enum nlog_level level);
void nlog_msg(enum nlog_level level, const char* file, i32 line, const char* format, ...);
void nlog_set_name(const char* name);

/*
 * nlogf() will log the file name and line number with the message
 * nlog() will just log a message
 */
#define nlogf(level, format, ...) nlog_msg(level, __FILE_NAME__, __LINE__, format, ##__VA_ARGS__)
#define nlog(level, format, ...) nlog_msg(level, NULL, 0, format, ##__VA_ARGS__)
#define vbose(format, ...) nlog_msg(N_VBOSE, NULL, 0, format, ##__VA_ARGS__)
#define vbosef(format, ...) nlog_msg(N_VBOSE, __FILE_NAME__, __LINE__, format, ##__VA_ARGS__)
#define debug(format, ...) nlog_msg(N_DEBUG, NULL, 0, format, ##__VA_ARGS__)
#define debugf(format, ...) nlog_msg(N_DEBUG, __FILE_NAME__, __LINE__, format, ##__VA_ARGS__)
#define info(format, ...) nlog_msg(N_INFO, NULL, 0, format, ##__VA_ARGS__)
#define infof(format, ...) nlog_msg(N_INFO, __FILE_NAME__, __LINE__, format, ##__VA_ARGS__)
#define warn(format, ...) nlog_msg(N_WARN, NULL, 0, format, ##__VA_ARGS__)
#define warnf(format, ...) nlog_msg(N_WARN, __FILE_NAME__, __LINE__, format, ##__VA_ARGS__)
#define error(format, ...) nlog_msg(N_ERROR, NULL, 0, format, ##__VA_ARGS__)
#define errorf(format, ...) nlog_msg(N_ERROR, __FILE_NAME__, __LINE__, format, ##__VA_ARGS__)
#define fatal(format, ...) nlog_msg(N_FATAL, __FILE_NAME__, __LINE__, format, ##__VA_ARGS__)

#endif // _NICE_LOG_H_
