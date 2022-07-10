#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define ERROR(fmt, args...) fprintf(stderr, "%s: " fmt "\n", __func__, ##args)
#define DEBUG(fmt, args...) fprintf(stdout, fmt "\n", ##args)
#define DEBUG_VAR(var, fmt) DEBUG(#var " = " fmt, (var))

#endif // LOG_H
