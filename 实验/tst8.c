#include <stdio.h>
#include <stdlib.h>

void move(int *nums, int len);
int is_equal(int *nums, int *nums_sorted, int len);
void operate();

int compare(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}

int main()
{

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        operate();
    }

    return 0;
}

void move(int *nums, int len)
{
    int tmp = nums[0];
    for (int i = 0; i < len - 1; i++)
    {
        nums[i] = nums[i + 1];
    }
    nums[len - 1] = tmp;
}

int is_equal(int *nums, int *nums_sorted, int len)
{

    for (int i = 0; i < len; i++)
    {
        if (nums[i] != nums_sorted[i])
            return 0;
    }

    return 1;
}

void operate()
{

    int len;
    scanf("%d", &len);

    int nums[len];
    int nums_sorted[len];
    for (int i = 0; i < len; i++)
    {
        scanf("%d", nums + i);
        nums_sorted[i] = nums[i];
    }

    qsort(nums_sorted, len, sizeof(int), compare);

    for (int i = 1; i <= len; i++)
    {
        move(nums, len);
        if (is_equal(nums, nums_sorted, len))
        {
            printf("Yes\n");
            return;
        }
    }
    printf("No\n");
}