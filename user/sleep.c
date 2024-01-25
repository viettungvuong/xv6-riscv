#include "kernel/types.h"
#include "user.h"

int main(int argc, char *argv[])
{
    // if the user forgets to enter the time
    if (argc < 2)
    {
        printf("error: incorrect number of arguments\n");
        exit(1);
    }

    int time = atoi(argv[1]);
    sleep(time);
    exit(0);
}