#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(2, "kek\n");
        exit(1);

    }
    int myTicks = atoi(argv[1]);
    if (myTicks < 0)
    {
        fprintf(2, "ticks must be non-negative\n");
        exit(1);
    }

    sleep(myTicks);


    exit(0);
}
