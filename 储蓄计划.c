#include <stdio.h>
int main()
{
    int budget[12];
    const int give = 300;
    for (int i = 0; i < 12; i++)
    {
        scanf("%d", budget + i);
    }

    int free_money = 0;
    int save_money = 0;
    int standard = 1;
    for (int i = 0; i < 12; i++)
    {
        free_money += give;
        if (free_money >= budget[i])
        {
            save_money += ((free_money - budget[i]) / 100) * 100;
            free_money = (free_money - budget[i]) % 100;
        }
        else
        {
            printf("-%d", i + 1);
            standard = 0;
            break;
        }
    }

    double money = (save_money) * 1.2 + free_money;

    if (standard)
    {
        printf("%d", (int)money);
    }

    return 0;
}
