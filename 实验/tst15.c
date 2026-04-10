#include <stdio.h>

struct range
{
    int start;
    int stop;
};

int max(int a, int b);

int main()
{
    int n;
    scanf("%d", &n);

    struct range arr[n];

    scanf("%d %d", &(arr[0].start), &(arr[0].stop));
    int cnt = 1;
    int a, b;
    for (int i = 1; i < n; i++)
    {
        scanf("%d %d", &a, &b);
        if (a <= arr[cnt - 1].stop)
        {
            arr[cnt - 1].stop = max(arr[cnt - 1].stop, b);
        }
        else
        {
            arr[cnt].start = a;
            arr[cnt].stop = b;
            cnt++;
        }
    }

    for (int i = 0; i < cnt; i++)
    {
        printf("%d %d\n", arr[i].start, arr[i].stop);
    }

    return 0;
}

int max(int a, int b)
{
    int max = a;
    if (b > a)
        max = b;

    return max;
}