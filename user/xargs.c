#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#include "kernel/stat.h"

const MAX_ARGS = 256;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "not enough arguments\n");
        exit(1);
    }

    char *args[MAX_ARGS];
    int i = 0;

    while (read(0, &ch, 1) > 0)
    {
    }

    exit(0);
}
