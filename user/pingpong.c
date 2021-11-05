#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void check_status(int st, char* s, int pid)
{

    if (st == -1)
    {
        fprintf(2, s);
        fprintf(2, "\nst: %d", st);
        fprintf(2, "\npid: %d", pid);
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    int pipefd[2];
    int st = pipe(pipefd);
    check_status(st, "pipe", 12435);
    int pid = fork();
    if (pid == -1)
    {
        fprintf(2, "fork");
        exit(1);
    }
    char c = 'e';

    if (pid)
    {
        // parent
        st = write(pipefd[1], &c, 1);
        close(pipefd[1]);
        check_status(st, "write par", pid);
        wait(0);
        printf("%d: received pong\n", pid);
    }
    else
    {
        char c = 'e';
        st = read(pipefd[0], &c, 1);
        // printf("read:%d", st);
        close(pipefd[0]);
        check_status(st, "read child", pid);
        printf("%d: received ping\n", pid);
    }
    exit(0);
}
