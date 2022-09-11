#include "elf_wrapper.h"

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>
#include <unistd.h>

#include "log.h"

#define MFD_CLOEXEC 0x0001U
#define HANDLE_EINTR(x) ({                                  \
  typeof(x) eintr_wrapper_result;                           \
  do {                                                      \
    eintr_wrapper_result = (x);                             \
  } while (eintr_wrapper_result == -1 && errno == EINTR);   \
  eintr_wrapper_result;                                     \
})

static void fd_write(int fd, const unsigned char *data, size_t size)
{
    typeof(data) end = data + size;
    while(data < end) {
        ssize_t nwrite = HANDLE_EINTR(write(fd, data, end - data));
        if(nwrite < 0) {
            ERROR("write: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }
        data += nwrite;
    }
}

void run_data(const unsigned char *data, size_t size)
{
    int fd = HANDLE_EINTR(syscall(SYS_memfd_create, "NULL", MFD_CLOEXEC));
    if(fd < 0) {
        ERROR("memfd_create: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    fd_write(fd, data, size);

    char *const argv[] = { NULL };
    fexecve(fd, argv, __environ);
    ERROR("fexecve: %s", strerror(errno));
    exit(EXIT_FAILURE);
}
