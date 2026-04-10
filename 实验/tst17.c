#include <stdio.h>
#include <string.h>
#include <math.h>

int str_to_num(char *str);
int calc(int a, int b, char *op);
int main()
{

    int nums[100];
    char str[50];
    int sum_of_num = 0;

    while (scanf("%s", str) != EOF)
    {

        if (strcmp(str, "+") != 0 && strcmp(str, "-") != 0 && strcmp(str, "*") != 0 && strcmp(str, "/") != 0)
        {
            nums[sum_of_num++] = str_to_num(str);
        }
        else
        {
            nums[sum_of_num - 2] = calc(nums[sum_of_num - 2], nums[sum_of_num - 1], str);
            sum_of_num -= 1;
        }
    }

    printf("%d", nums[0]);

    return 0;
}

int str_to_num(char *str)
{
    int len = strlen(str);
    int ans = 0;
    int t = (int)pow(10, len - 1);
    for (int i = 0; i < len; i++)
    {
        ans += (str[i] - '0') * t;
        t /= 10;
    }
    return ans;
}

int calc(int a, int b, char *op)
{

    if (strcmp(op, "+") == 0)
        return a + b;
    if (strcmp(op, "-") == 0)
        return a - b;
    if (strcmp(op, "*") == 0)
        return a * b;
    if (strcmp(op, "/") == 0)
        return a / b;
}
