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
    int numArgs = 0;
    for (int i = 1; i < argc; i++)
    {
        args[numArgs++] = argv[i];
    }

    char current_arg[512];
    int i = 0;
    char ch;
    int current_in_args = 0;

    int pos = 0, argStart = 0;

    while (read(0, &ch, 1) > 0)
    {
        pos = 0, argStart = 0;

        if (ch == '\n')
        {
            current_arg[i] = 0;
            i = 0;

            // for (int i = 0; i < current_in_args; i++)
            // {
            //     args[current_in_args] = NULL;
            // }

            if (fork() == 0)
            {

                for (int j = 0; j < argc - 1; i++)
                {
                    int current_len = strlen(argv[j]);
                    args[current_in_args] = malloc(current_len + 1);
                    current_in_args++;
                    memcpy(args[current_in_args], argv[j], current_len + 1);
                }

                int n = strlen(current_arg);

                args[current_in_args] = malloc(n + 1);
                memcpy(args[current_in_args++], current_arg, n + 1);

                args[argc] = 0;

                exec(args[0], args);

                break;
            }
            else
            {
                wait(0);
            }
        }
        else
        {
            current_arg[i++] = ch;
        }
    }

    exit(0);
}
