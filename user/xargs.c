#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#include "kernel/stat.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "not enough arguments\n");
        exit(1);
    }

    char *args[MAXARG];
    int i = 0;

    while (read(0, &c, 1) > 0)
    {
        if (c == '\n')
        {
        }
        else
        {
            args[i++] = c;
        }
    }

    exit(0);
}
