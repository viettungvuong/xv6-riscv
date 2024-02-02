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
                int current = 0;

                for (int j = 0; j < argc - 1; i++)
                {
                    int current_len = strlen(argv[j]);
                    args[current] = malloc(current_len + 1);
                    current++;
                    memcpy(args[current], argv[j], current_len + 1);
                }
            }
        }
        else
        {
            current_arg[i++] = c;
        }
    }

    exit(0);
}
