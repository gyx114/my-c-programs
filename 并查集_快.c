#include <stdio.h>

typedef struct
{
    int val;
    int father;
} my_struct;

int find(int x, my_struct *nums);
void combine(int x, int y, int n, my_struct *nums);
void search(int x, int y, int n, my_struct *nums);

int main()
{

    int n, m;
    scanf("%d %d", &n, &m);
    my_struct nums[n];
    for (int i = 0; i < n; i++)
    {
        nums[i].val = i + 1;
        nums[i].father = i + 1;
    }

    for (int i = 0; i < m; i++)
    {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);

        if (op == 2)
        {
            search(x, y, n, nums);
        }
        else
        {
            combine(x, y, n, nums);
        }
    }

    return 0;
}

int find(int x, my_struct *nums)
{
    // 递归找根
    if (nums[x - 1].father != x)
    {
        nums[x - 1].father = find(nums[x - 1].father, nums);
    }
    return nums[x - 1].father;
}

void combine(int x, int y, int n, my_struct *nums)
{

    int x_dad = find(x, nums);
    int y_dad = find(y, nums);
    if (x_dad != y_dad)
    {
        nums[y_dad - 1].father = x_dad;
    }
}

void search(int x, int y, int n, my_struct *nums)
{

    if (find(x, nums) == find(y, nums))
    {
        printf("Y\n");
    }
    else
        printf("N\n");
}
