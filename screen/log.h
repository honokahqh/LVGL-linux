#ifndef __LOG_H__
#define __LOG_H__
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>

#define App_Ver 10001
#define IsReleaseVer    0
#define LOG_NONE 0
#define LOG_ERROR 1
#define LOG_WARN 2
#define LOG_INFO 3
#define LOG_ALL 4 
#define LOG_LEVEL LOG_ALL

void terminal_printf(uint8_t level, const char *tag, const char *fmt, ...);
void file_write(uint8_t level, const char *tag, const char *fmt, ...);

#define log_printf(level, tag, fmt, ...) do { \
        terminal_printf(level, tag, fmt, ##__VA_ARGS__); \
        file_write(level, tag, fmt, ##__VA_ARGS__); \
    } while(0)

#if LOG_LEVEL >= LOG_ERROR
#define LOG_E(tag, fmt, ...) log_printf(LOG_ERROR, tag, fmt, ##__VA_ARGS__)
#else
#define LOG_E(tag, fmt, ...) file_write(LOG_ERROR, tag, fmt, ##__VA_ARGS__);
#endif

#if LOG_LEVEL >= LOG_WARN
#define LOG_W(tag, fmt, ...) log_printf(LOG_WARN, tag, fmt, ##__VA_ARGS__)
#else
#define LOG_W(tag, fmt, ...) file_write(LOG_ERROR, tag, fmt, ##__VA_ARGS__);
#endif

#if LOG_LEVEL >= LOG_INFO
#define LOG_I(tag, fmt, ...) log_printf(LOG_INFO, tag, fmt, ##__VA_ARGS__)
#else
#define LOG_I(tag, fmt, ...) file_write(LOG_ERROR, tag, fmt, ##__VA_ARGS__);
#endif 

#if LOG_LEVEL >= LOG_ALL
#define LOG_D(tag, fmt, ...) log_printf(LOG_ALL, tag, fmt, ##__VA_ARGS__)
#else
#define LOG_D(tag, fmt, ...) file_write(LOG_ERROR, tag, fmt, ##__VA_ARGS__);
#endif

#endif // __LOG_H__
