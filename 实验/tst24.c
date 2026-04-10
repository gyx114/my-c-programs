#include <stdio.h>

#define N 1000
int matrix[N][N];

void rotate(int matrixSize, int matrixColSize);

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    rotate(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}


void rotate(int matrixSize, int matrixColSize)
{
    // TODO：在该函数内部完成对矩阵matrix的翻转
    //显然，矩阵转置好搞，只涉及交换对称元素
    //故先转置再反转


    //转置
    int tmp;
    
    
    for (int i = 1; i < matrixSize; i++)
    {
        for (int j = 0; j<i ; j++)  //注意，i=1开始，j<i，否则会导致转置两次，又转回去了(▼ヘ▼#)
        {
            tmp=matrix[i][j];
            matrix[i][j]=matrix[j][i];
            matrix[j][i]=tmp;

        }
        
    }
    
    //反转

    for (int i = 0; i < matrixSize/2; i++)
    {
        for (int j = 0; j < matrixColSize; j++)
        {
            tmp=matrix[j][i];
            matrix[j][i]=matrix[j][matrixSize-1-i];
            matrix[j][matrixSize-1-i]=tmp;
        }
        
    }
    

}