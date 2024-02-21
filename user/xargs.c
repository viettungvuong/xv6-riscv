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
    for (int i = 1; i < argc; i++) // bắt đầu từ 1 vì 0 là tên chương trình
    {
        args[numArgs++] = argv[i];
    }

    char current_arg[2048];
    char ch;

    int pos = 0, argStart = 0;

    while (1)
    {
        pos = 0, argStart = 0;
        int okay = 1;

        while (1)
        {
            if (read(0, &ch, 1) == 0)
            {
                okay = 0;
                break;
            }

            if (ch == '\n') // hết dòng => kết thúc arg
            {
                current_arg[pos++] = 0;
                args[numArgs++] = &current_arg[argStart]; // lưu argument đang đọc lại
                argStart = 0;

                break; // break để cho đọc dòng tiếp theo
            }
            else if (ch == ' ') // dấu cách => kết thúc arg
            {
                current_arg[pos++] = 0;
                args[numArgs++] = &current_arg[argStart];
                argStart = pos; // đánh dấu vị trí bắt đầu của arg mới
            }
            else
            {
                current_arg[pos++] = ch;
            }
        }

        if (okay == 0)
        {
            break;
        }

        int pid = fork();
        if (pid == 0)
        {
            exec(args[0], args);
        }
        else
        {
            wait(0);
        }
    }

    exit(0);
}
