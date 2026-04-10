#include <stdio.h>
#include <math.h>

int sigma(int len, int arr[len])
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int find(int len, int arr[len])
{
    int half = len / 2;
    if (len == 1)
        return 0;

    if (sigma(half, arr) < sigma(half, arr + half))
    {
        return find(half, arr);
    }

    else
    {
        return (half + find(half, arr + half));
    }
}

int main()
{

    int n;
    scanf("%d", &n);
    int len = (int)pow(2, n);
    int arr[len];
    for (int i = 0; i < len; i++)
    {
        scanf("%d", arr + i);
    }

    printf("%d", find(len, arr));

    return 0;
}
