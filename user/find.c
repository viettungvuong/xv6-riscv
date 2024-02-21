#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int match(char *s, char *p)
{
    if (!*p)
        return !*s;
    if (*(p + 1) != '*')
        return *s == *p || (*p == '.' && *s != '\0') ? match(s + 1, p + 1) : 0;
    else
        return *s == *p || (*p == '.' && *s != '\0') ? match(s, p + 2) || match(s + 1, p) : match(s, p + 2);
}

void find(char *path, char *filename)
{
    char current[512];
    int fd;
    struct dirent de;
    struct stat st;

    fd = open(path, 0);

    if (fd < 0)
    {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if (st.type != T_DIR)
    {
        fprintf(2, "find: %s is not a directory\n", path);
        close(fd);
        return;
    }
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof current)
    {
        printf("find: path too long\n");
        close(fd);
        return;
    }

    char *ptr;
    strcpy(current, path);
    ptr = current + strlen(current);
    *ptr++ = '/';

    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
        if (de.inum == 0)
            continue;
        if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
            continue;

        memmove(ptr, de.name, DIRSIZ);
        ptr[DIRSIZ] = 0;

        if (stat(current, &st) < 0)
        {
            fprintf(2, "find: cannot stat %s\n", current);

            continue;
        }

        if (st.type == T_FILE && match(de.name, filename))
        {
            printf("%s\n", current);
        }
        else if (st.type == T_DIR)
        {
            find(current, filename); // recursion next into this directory
            break;
        }
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(2, "Usage: find path filename\n");
        exit(1);
    }
    if (strcmp(argv[1], ".") == 0)
    {
        find(".", argv[2]);
    }
    else
    {
        find(argv[1], argv[2]);
    }
    exit(0);
}
