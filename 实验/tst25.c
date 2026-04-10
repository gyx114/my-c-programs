#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(char *)a) - (*(char *)b);
}

void sort(char *alpha, char *alpha_sorted, int len);

int main()
{

    int n;
    scanf("%d", &n);
    char str[n + 1];
    scanf("%s", str);
    int cnt_alpha = 0;
    int cnt_num = 0;
    char alpha[n];
    char num[n];
    for (int i = 0; i < n; i++)
    {
        if (!(str[i] >= 48 && str[i] <= 57))
        {
            alpha[cnt_alpha] = str[i];
            cnt_alpha++;
        }
        else
        {
            num[cnt_num] = str[i];
            cnt_num++;
        }
    }

    char alpha_sorted[n];
    int t = 0;
    int s = 0;
    sort(alpha, alpha_sorted, cnt_alpha);
    qsort(num, cnt_num, sizeof(char), compare);
    for (int i = 0; i < n; i++)
    {
        if (!(str[i] >= 48 && str[i] <= 57))
        {
            str[i] = alpha_sorted[t];
            t++;
        }
        else
        {
            str[i] = num[s];
            s++;
        }
    }

    printf("%s", str);

    return 0;
}

void sort(char *alpha, char *alpha_sorted, int len)
{
    int cnt = 0;
    char standard[52] = {'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H', 'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z'};
    for (int i = 0; i < 52; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (alpha[j] == standard[i])
            {

                alpha_sorted[cnt] = alpha[j];
                cnt++;
            }
        }
    }
}