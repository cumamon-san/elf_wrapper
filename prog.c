#include <stdlib.h>
#include <unistd.h>

#include "log.h"

int main()
{
    DEBUG("Prog with payload. PID = %u", getpid());
    char buff[512];
    snprintf(buff, sizeof(buff), "ls -l /proc/%u/fd", getpid());
    system(buff);
    snprintf(buff, sizeof(buff), "ls -l /proc/%u/exe", getpid());
    system(buff);
    return 0;
}
