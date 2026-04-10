#include <stdio.h>
int main()
{
    short a;
    int b;
    long c;
    long long d;
    unsigned int e;

    scanf("%hd %d %ld %lld %u", &a, &b, &c, &d, &e);
    printf("%d\n%u\n%o\n%X\n%X", a, b, c, d, e);

    return 0;
}