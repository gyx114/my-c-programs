#include <stdio.h>
#include <stdlib.h>

int nums[10005] = {0};

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{

    int n;
    scanf("%d", &n);
    int max_idx = 0;
    for (int i = 0; i < n; i++)
    {
        int x;
        scanf("%d", &x);
        nums[x]++;
        if (nums[x] > nums[max_idx])
        {
            max_idx = x;
        }
        else if (nums[x] == nums[max_idx])
        {
            max_idx = min(max_idx, x);
        }
    }

    printf("%d", max_idx);
    return 0;
}