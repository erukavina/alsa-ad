#include "logging.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

void log_info(const char *format, ...) {
    va_list args;
    va_start(args, format);

    time_t rawtime;
    struct tm *info;
    char timestamp[20];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", info);

    fprintf(stdout, "[%s] [INFO] ", timestamp);
    vfprintf(stdout, format, args);
    fprintf(stdout, "\n");

    va_end(args);
}

void log_error(const char *format, ...) {
    va_list args;
    va_start(args, format);

    time_t rawtime;
    struct tm *info;
    char timestamp[20];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", info);

    fprintf(stderr, "[%s] [ERROR] ", timestamp);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");

    va_end(args);
}

void init_logging() {
    // Initialize logging configuration here if needed
}

