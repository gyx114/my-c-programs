#include <stdio.h>
int main()
{

    int give_money;
    scanf("%d", &give_money);
    int cnt = 0;
    cnt += give_money / 2;
    int rest_money = give_money % 2;
    int gai = cnt;
    int ping = cnt;

    while (!(gai < 4 && ping < 2))
    {
        int add_drink = 0;
        add_drink += gai / 4;

        add_drink += ping / 2;
        ping = ping % 2 + add_drink;
        gai = gai % 4 + add_drink;
        cnt += add_drink;
    }

    printf("%d %d %d %d", cnt, ping, gai, rest_money);

    return 0;
}