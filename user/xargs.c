int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "not enough arguments\n");
        exit(1);
    }

    char *args[MAXARG];
    for (int i = 0; i < argc - 1; i++)
    { // skip program name so have to add 1
        args[i] = argv[i + 1];
    }
}