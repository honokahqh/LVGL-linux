#include "log.h"

void terminal_printf(uint8_t level, const char *tag, const char *fmt, ...) {
    if (level <= LOG_LEVEL) {
        va_list args;
        va_start(args, fmt);
        printf("%s (%u) %s: ", level >= LOG_ALL ? "D" : 
                               level >= LOG_INFO ? "I" : 
                               level >= LOG_WARN ? "W" : 
                               level >= LOG_ERROR ? "E" : "?", 
                               custom_tick_get(), 
                               tag);
        vprintf(fmt, args);
        va_end(args);
    }
}

void file_write(uint8_t level, const char *tag, const char *fmt, ...) {
    FILE *file = fopen("/tmp/messages", "a");
    if (file) {
        va_list args;
        va_start(args, fmt);
        fprintf(file, "%s (%u) %s: ", level >= LOG_ALL ? "D" : 
                                       level >= LOG_INFO ? "I" : 
                                       level >= LOG_WARN ? "W" : 
                                       level >= LOG_ERROR ? "E" : "?", 
                                       custom_tick_get(), 
                                       tag);
        vfprintf(file, fmt, args);
        va_end(args);
        fclose(file);
    } else {
        printf("file /tmp/messages open failed\n");
    }
}
