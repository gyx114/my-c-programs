#include <stdio.h>
#include <math.h>

int main()
{

    int max_weight, n;
    scanf("%d %d", &max_weight, &n);
    int weight_i[n];
    int value_i[n];
    int is_selected[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", weight_i + i);
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d", value_i + i);
    }
    int good_weight = 0;
    int good_value = 0;
    int good_choice[n];
    int tmp;
    for (int i = 0; i < pow(2, n); i++)
    {
        int current_weight = 0;
        int current_value = 0;
        tmp = i;
        for (int j = n - 1; j >= 0; j--)
        {
            is_selected[j] = tmp % 2;
            tmp /= 2;
        }

        for (int i = 0; i < n; i++)
        {
            current_value += value_i[i] * is_selected[i];
            current_weight += weight_i[i] * is_selected[i];
        }

        if (current_weight > max_weight)
            continue;

        else
        {
            if (current_value > good_value)
            {
                good_value = current_value;
                good_weight = current_weight;
                for (int i = 0; i < n; i++)
                {
                    good_choice[i] = is_selected[i];
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (good_choice[i] == 1)
            printf("%d ", i + 1);
    }

    printf("%d %d", good_weight, good_value);

    return 0;
}