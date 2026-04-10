#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("no!");
        return 1;
    }

    if (strcmp(argv[1], "hello") == 0)
    {
        printf("hello world");
    }

    return 0;
}