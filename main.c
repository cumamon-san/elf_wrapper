#include "elf_runner.h"

static const unsigned char data[] = {
#   include "payload.txt"
};

int main()
{
    run_data(data, sizeof(data));
    return 0;
}
