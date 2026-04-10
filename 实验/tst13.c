#include <stdio.h>
int find(int x, int len, int arr[len]);
int main()
{

    int n, m;
    scanf("%d %d", &n, &m);
    int arr1[n];
    int arr2[m];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", arr1 + i);
    }
    for (int i = 0; i < m; i++)
    {
        scanf("%d", arr2 + i);
    }

    for (int i = 0; i < m; i++)
    {
        printf("%d\n", find(arr2[i], n, arr1));
    }

    return 0;
}

// 二分查找
int find(int x, int len, int arr[len])
{
    int start = 0;
    int stop = len - 1;
    int mid;
    while (start <= stop)
    {
        mid = (start + stop) / 2;
        if (arr[mid] == x)
        {
            return mid;
        }
        else if (x > arr[mid])
        {
            start = mid + 1;
        }
        else
        {
            stop = mid - 1;
        }
    }
    return -1;
}