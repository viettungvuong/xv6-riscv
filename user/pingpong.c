#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char buf[512] = {0};
    int pc[2], cp[2];
    pipe(pc);
    pipe(cp); // pipe for both directions

    int child = fork(); // create child

    if (child != 0) // parent sends byte to child
    {
        close(pc[0]);
        close(cp[1]);

        write(pc[1], "ping", strlen("ping"));
        read(cp[0], buf, sizeof(buf));
        printf("%d: received %s\n", getpid(), buf);
    }
    else // parent reads byte from child
    {
        close(pc[1]);
        close(cp[0]);

        read(pc[0], buf, sizeof(buf));
        printf("%d: received %s\n", getpid(), buf);

        write(cp[1], "pong", strlen("pong"));
    }

    exit(0);
}