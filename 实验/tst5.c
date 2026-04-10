#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *multi(int min, char *a, int len_b, char *b);

int main()
{

	int n, m;
	scanf("%d", &n);
	char a[n + 1];
	scanf("%s", a);
	scanf("%d", &m);
	char b[m + 1];
	scanf("%s", b);
	char *ans;
	if (n < m)
	{
		ans = multi(n, a, m, b);
	}

	else
	{
		ans = multi(m, b, n, a);
	}

	for (int i = 0; i < (int)strlen(ans); i++)
	{
		printf("%c", ans[(int)strlen(ans) - 1 - i]);
	}

	free(ans);

	return 0;
}

char *multi(int min, char *a, int len_b, char *b)
{

	char **ans = (char **)malloc(min * sizeof(char *));
	for (int i = 0; i < min; i++)
	{
		ans[i] = (char *)malloc(sizeof(char) * 100);
	}
	int len_i[min];
	for (int i = 0; i < min; i++)
	{
		len_i[i] = 0;
	}

	for (int i = 0; i < min; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			ans[i][j] = '0';
		}
	}

	// 逐位计算乘法
	int jinwei = 0, remain = 0;
	int tmp1 = 0, tmp2 = 0, tmp = 0;
	int cnt = 0;
	for (int i = 0; i < min; i++)
	{
		// 每个外层循环都是新的一轮乘法，需要重置进位、计数器等！！！！
		jinwei = 0;
		cnt = 0;
		tmp = 0;
		remain = 0;
		for (int j = 0; j < len_b; j++)
		{

			tmp1 = a[min - 1 - i] - '0';
			tmp2 = b[len_b - 1 - j] - '0';
			tmp = tmp1 * tmp2 + jinwei;
			jinwei = tmp / 10;
			remain = tmp % 10;

			ans[i][i + cnt] = remain + '0';
			cnt++;
		}
		if (jinwei != 0)
		{
			ans[i][i + cnt] = jinwei + '0';
			cnt++;
		}
		len_i[i] = cnt + i;
	}

	int max_len = len_i[0];
	for (int i = 1; i < min; i++)
	{
		if (len_i[i] > max_len)
			max_len = len_i[i];
	}

	jinwei = 0;
	remain = 0;
	cnt = 0;
	char *finally = (char *)malloc(50);
	for (int i = 0; i < max_len; i++)
	{
		// 必须重置tmp！！！否则上一轮循环的残留tmp会干扰！！！
		tmp = 0;
		for (int j = 0; j < min; j++)
		{
			tmp += ans[j][i] - '0';
		}
		tmp += jinwei;
		jinwei = tmp / 10;
		remain = tmp % 10;
		finally[cnt++] = remain + '0';
	}

	while (jinwei != 0)
	{
		remain = jinwei % 10;
		jinwei /= 10;
		finally[cnt++] = remain + '0';
	}
	finally[cnt] = '\0';

	return finally;
}