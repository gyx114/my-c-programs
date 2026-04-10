#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_xiaoxie(char a)
{
    if (a >= 'a' && a <= 'z')
    {
        return 1;
    }
    return 0;
}

int compare_num(const void *a, const void *b)
{
    return *((char *)a) - *((char *)b);
}

int compare_alpha(const void *a, const void *b)
{
    char fst = *((char *)a);
    char snd = *((char *)b);
    if (is_xiaoxie(fst) && is_xiaoxie(snd))
    {
        return fst - snd;
    }
    else if (!is_xiaoxie(fst) && !is_xiaoxie(snd))
    {
        return fst - snd;
    }
    else if (is_xiaoxie(fst) && !is_xiaoxie(snd))
    {
        if (snd == fst + 'A' - 'a')
        {
            return -1;
        }
        else
        {
            return (fst + 'A' - 'a' - snd);
        }
    }
    else
    {
        if (fst == snd + 'A' - 'a')
        {
            return 1;
        }
        else
        {
            return fst - (snd + 'A' - 'a');
        }
    }
}

int main()
{

    int n;
    scanf("%d", &n);
    char str[n + 1];
    scanf("%s", str);
    int idx_of_nums[n];
    int idx_of_alphas[n];
    char nums[n];
    char alphas[n];

    int len = strlen(str);
    int sum_of_num = 0;
    int sum_of_alpha = 0;

    for (int i = 0; i < len; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            nums[sum_of_num] = str[i];
            idx_of_nums[sum_of_num++] = i;
        }
        else
        {
            alphas[sum_of_alpha] = str[i];
            idx_of_alphas[sum_of_alpha++] = i;
        }
    }

    qsort(nums, sum_of_num, sizeof(char), compare_num);
    qsort(alphas, sum_of_alpha, sizeof(char), compare_alpha);

    char ans[n + 1];
    for (int i = 0; i < sum_of_num; i++)
    {
        ans[idx_of_nums[i]] = nums[i];
    }
    for (int i = 0; i < sum_of_alpha; i++)
    {
        ans[idx_of_alphas[i]] = alphas[i];
    }
    ans[n] = '\0';
    printf("%s", ans);
    return 0;
}
