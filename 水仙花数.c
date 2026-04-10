// 水仙花数是指一个N位正整数（N>=3），它的每个位上的数字的N次幂之和等于它本身。例如：153 = 1^3 + 5^3+ 3^3。本题要求编写程序,计算所有N位水仙花数。
#include <stdio.h>
int main()
{

	// 核心：遍历所有的n位数，然后取出每一位，最后计算筛选

	int N;
	printf("请输入N（N>=3）：");
	scanf("%d", &N);
	if (N < 3)
	{
		printf("N必须大于等于3！\n");
		return 0;
	}
	int start = 1;
	for (int i = 1; i < N; i++)
	{
		start *= 10;
	}
	int end = start * 10 - 1;
	printf("%d位水仙花数有：\n", N);
	for (int num = start; num <= end; num++)
	{
		int sum = 0, temp = num;
		while (temp > 0)
		{
			int digit = temp % 10;
			int pow = 1;
			for (int j = 0; j < N; j++)
				pow *= digit;
			sum += pow;
			temp /= 10;
		}
		if (sum == num)
		{
			printf("%d\n", num);
		}
	}

	return 0;
}