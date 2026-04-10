
// 题目描述
// 东东刚刚学完计算导论，老师给他安排了一个任务：开发一个文字处理程序。

// 程序最开始时输入一个字符串作为初始文档。可以认为文档开头是第 0 个字符。程序需要支持以下操作：

// 1 str：后接插入，在文档后面插入字符串 str，并输出文档的字符串。

// 2 a b：截取文档部分，只保留文档中从第 a 个字符起 b 个字符，并输出文档的字符串。

// 3 a str：插入片段，在文档中第 a 个字符前面插入字符串 str，并输出文档的字符串。

// 4 str：查找子串，查找字符串 str 在文档中第一次出现的下标并输出；如果找不到输出 -1。

// 为了简化问题，规定初始的文档和每次操作中的 str 都不含有空格或换行。

// 输入格式
// 第 1 行输入一个整数 q (q<=100) 表示操作次数。

// 第 2 行输入一行字符串。

// 紧接着 q 行，每行输入一个操作，操作格式如题目描述所述。

// 数据保证文档字符串以及操作中输入字符串的长度不超过 200。

// 输出格式
// 输出 q 行，分别对应着每个操作的操作结果。

// 测试样例
// 样例 1
// 输入:
// 4
// ILove
// 1 SDU
// 2 5 3
// 3 3 csCscs
// 4 cs
// 输出:
// ILoveSDU
// SDU
// SDUcsCscs
// 3







#include <stdio.h>
int get_lenth(char* str){
    int cnt=0;
    while (str[cnt]!='\0')
    {
        cnt++;
    }

    return cnt;
}



void operate(char* str){
    int a;
    scanf("%d", &a);
    char tmp[11451];
    int strlen, tmplen;
    switch (a) {
    case 1:
        scanf("%s", tmp);
        strlen = get_lenth(str);
        tmplen = get_lenth(tmp);
        for (int i = 0; i <= tmplen; i++) {
            str[strlen + i] = tmp[i];
        }
        printf("%s\n", str);
        break;
    case 2: {
        int start, len;
        scanf("%d %d", &start, &len);
        strlen = get_lenth(str);
        if (start < 0) start = 0;
        if (start + len > strlen) len = strlen - start;
        for (int i = 0; i < len; i++) {
            tmp[i] = str[start + i];
        }
        tmp[len] = '\0';
        for (int i = 0; i <= strlen; i++) {
            str[i] = '\0';
        }
        for (int i = 0; i <= len; i++) {
            str[i] = tmp[i];
        }
        printf("%s\n", str);
        break;
    }
    case 3:
        int x;
        scanf("%d",&x);
        scanf("%s",tmp);
        strlen=get_lenth(str);
        tmplen=get_lenth(tmp);
       for (int i = strlen; i >= x; i--) {
            str[i + tmplen] = str[i];
       }
       for (int i = 0; i < tmplen; i++)
       {
            str[x+i]=tmp[i];
       }
        printf("%s\n",str);   
       break;
    
    case 4: {
        int standard = 0;
        scanf("%s", tmp);
        strlen = get_lenth(str);
        tmplen = get_lenth(tmp);
        if (strlen < tmplen) printf("-1\n");
        else {
            for (int i = 0; i <= strlen - tmplen; i++) {
                int found = 1;
                for (int j = 0; j < tmplen; j++) {
                    if (str[i + j] != tmp[j]) { found = 0; break; }
                }
                if (found) { printf("%d\n", i); standard = 1; break; }
            }
            if (!standard) printf("-1\n");
        }
        break;
    }
    }



}







int main(){
int q;
char str[11451]={'\0'};

scanf("%d",&q);
scanf("%s",str);

for (int i = 0; i < q; i++)
{
   operate(str);
}



return 0;
}




