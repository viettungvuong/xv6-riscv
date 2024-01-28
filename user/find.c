#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int match(char *s, char *p)
{
    if (!*p)
        return !*s;
    if (*(p + 1) != '*')
        return (*s == *p || (*p == '.' && *s != '\0')) && match(s + 1, p + 1);
    else
        return ((*s == *p || (*p == '.' && *s != '\0')) && match(s, p + 2)) || match(s + 1, p);
}

void find(int fd, char *dir, char *name)
{
    struct dirent de;
    char path[512];

    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        if (de.inum == 0) // empty slot
            continue;
        if (!strcmp(de.name, ".") || !strcmp(de.name, ".."))
            continue;

        memcpy(path, dir, strlen(dir));
        char *p = path + strlen(dir);
        *p++ = '/';
        memcpy(p, de.name, strlen(de.name));
        p += strlen(de.name);
        *p++ = 0;

        struct stat st;

        if (stat(path, &st) < 0)
        {
            printf("find: cannot stat %s\n", path);
            continue;
        }
        if (st.type == T_FILE && match(de.name, name))
        {
            printf("%s\n", path);
        }
        else if (st.type == T_DIR)
        {
            int sub = open(path, 0);
            if (sub < 0)
            {
                printf("find: cannot open %s\n", path);
                continue;
            }
            find(sub, path, name);
        }
        }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(2, "not enough arguments\n");
        exit(1);
    }

    char dir[DIRSIZ + 1];
    char name[DIRSIZ + 1];

    memcpy(dir, argv[1], strlen(argv[1]));
    memcpy(name, argv[2], strlen(argv[2]));

    int fd;
    struct stat st;

    if ((fd = open(dir, 0)) < 0)
    {
        fprintf(2, "find: cannot open %s\n", dir);
        exit(1);
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", dir);
        close(fd);
        exit(1);
    }

    if (st.type != T_DIR)
    {
        printf("%s is not a directory\n", dir);
    }
    else
    {
        find(fd, dir, name);
    }

    exit(0);
}