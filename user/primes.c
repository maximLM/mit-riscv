#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int main(int argc, char *argv[])
{
    int fd_buf1[2];
    int fd_buf2[2];
    int* fd1 = fd_buf1;
    int* fd2 = fd_buf2;

    pipe(fd1);
    int pid = fork();
    if (pid) {
        close(fd1[0]);
        for (int i = 2; i <= 35; ++i) {
            write(fd1[1], &i, 1);
        }
        close(fd1[1]);
    } else {
        while (pid == 0) {
            close(fd1[1]);
            pipe(fd2);
            int p;
            int st = read(fd1[0], &p, 1);
            if (st == 0) {
                break;
            }
            pid = fork();
            if (pid == 0) {
                int* tmp = fd1;
                fd1 = fd2;
                fd2 = tmp;
                continue;
            }
            printf("prime %d\n", p);
            while (1) {
                int x;
                int st = read(fd1[0], &x, 1);
                if (st == 0) {
                    break;
                }
                if (x % p) {
                    write(fd2[1], &x, 1);
                }
            }
            close(fd2[1]);
        }
    }
    wait(0);
    exit(0);
}
