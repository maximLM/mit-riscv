#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"

#define BUF_SIZE 256

void exec_command(char* buf, char *argv[], int argc, int cur_size)
{
    if (!cur_size) {
        return;
    }
    int pid = fork();
    if (pid == 0)
    {
        char *new_argv[MAXARG];
        // memcpy(new_argv, argv + 1, argc - 1);
        for (int i = 0; i < argc - 1; ++i) {
            new_argv[i] = argv[i + 1];
        }
        new_argv[argc - 1] = buf;
        new_argv[argc] = 0;
        // printf(new_argv[0]);
        // printf(new_argv[1]);
        // printf(new_argv[2]);
        exec(argv[1], new_argv);
    }
}

int main(int argc, char *argv[])
{
    
    char buf[BUF_SIZE];
    if (argc <= 1)
    {
        exit(0);
    }

    int cur_size = 0;
    while (read(0, buf + cur_size, 1) > 0)
    {
        if (buf[cur_size] == '\n')
        {
            buf[cur_size] = 0;
        }
        else
        {
            cur_size++;
            continue;
        }
        exec_command(buf, argv, argc, cur_size);
        cur_size = 0;
    }

    exit(0);
}
