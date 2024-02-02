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
    char current_arg[512];
    int i = 0;

    while (read(0, &c, 1) > 0)
    {
        if (c == '\n')
        {
            current_arg[i] = 0;
            i = 0;

            if (fork() == 0)
            {
            }
        }
        else
        {
            current_arg[i++] = c;
        }
    }

    exit(0);
}
