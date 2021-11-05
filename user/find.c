#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char *current_dir = ".";
char *parent_dir = "..";

void find(char *path, char *name)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0)
    {
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type)
    {
    case T_FILE:
        if (strcmp(de.name, name) == 0)
        {
            strcpy(buf, path);
            char *p = buf + strlen(path);
            *p++ = '/';
            memmove(p, de.name, DIRSIZ);
            printf(p);
        }
        break;

    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0 || !strcmp(de.name, current_dir) || !strcmp(de.name, parent_dir))
                continue;

            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if (!strcmp(de.name, name)) {
                printf(buf);
                printf("\n");
            }
            find(buf, name);
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        fprintf(2, "dude");
        exit(1);
    }
    char *path = argv[1];
    char *name = argv[2];
    find(path, name);
    exit(0);
}
