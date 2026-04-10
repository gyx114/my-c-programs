#include <stdio.h>

typedef struct
{
    int val;
    int father;
} my_struct;

void connect_to_their_root(int n, int start, my_struct *nums);
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
        connect_to_their_root(n, 0, nums);
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

void connect_to_their_root(int n, int start, my_struct *nums)
{
    if (start == n)
        return;
    if (nums[start].father == nums[nums[start].father - 1].father)
    {
        connect_to_their_root(n, start + 1, nums);
    }
    else
    {
        nums[start].father = nums[nums[start].father - 1].father;
        connect_to_their_root(n, start, nums);
    }
}

void combine(int x, int y, int n, my_struct *nums)
{

    for (int i = 0; i < n; i++)
    {
        if (nums[i].father == nums[y - 1].father)
        {
            nums[nums[i].father - 1].father = nums[x - 1].father;
        }
    }
}

void search(int x, int y, int n, my_struct *nums)
{

    if (nums[x - 1].father == nums[y - 1].father)
    {
        printf("Y\n");
    }
    else
        printf("N\n");
}
