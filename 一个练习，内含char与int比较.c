


//本练习中有char与int的比较，例如我想比较4与5的大小，但是一个是'4'一个是int型的5
//核心思想就是利用ascll表中的连续排列来转化
//我们使用'4'-'0'的操作就能得到数字4了


#include <stdio.h>
int main(){

int a,b,c;
char d;
int num=0;
scanf("%d-%d-%d-%c",&a,&b,&c,&d);

num+=a*100000000+b*100000+c;
int tmp=num;
int x=0;

for (int i = 1; i < 10; i++)
{
  
    x+=(tmp%10)*(10-i);
    tmp/=10;
}

if (d=='X' && x%11==10)
{
 printf("Right");
}
else if (d=='X' && x%11!=10)
{
    printf("%d-%d-%d-%d",a,b,c,x%11);
}
else if (d!='X')
{
    if (x%11!=10 && (d - '0') == x%11) {
        printf("Right");
    } 
    else if(x%11==10){
        printf("%d-%d-%d-X", a, b, c);
    }
    else if(x%11!=10 && (d - '0') != x%11)
    {printf("%d-%d-%d-%d", a, b, c,x%11);}
}

 return 0;

}