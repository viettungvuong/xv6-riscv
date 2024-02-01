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
    for (i = 0; i < argc - 1; i++)
    { // skip program name so have to add 1
        args[i] = argv[i + 1];
    }
    // i--;

    int c;
    char buf[4096];
    char *ptr = &buf[0];
    int offset = 0;
    while (read(0, &c, 1) > 0)
    {
        if (c == ' ')
        {
            offset++;
            buf[offset] = 0;

            i++;
            args[i] = ptr;
            ptr = &buf[offset];
        }

        if (c == '\n')
        {
            i++;
            args[i] = ptr;
            ptr = &buf[offset];

            if (!fork())
            {
                exit(exec(args[0], args));
            }

            wait(0);
            i = argc - 1;
        }
        else
        {
            offset++;
            buf[offset] = c;
        }
    }

    exit(0);
}
