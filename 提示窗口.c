
// 编译指令：
//  gcc -mwindows   提示窗口.c -fexec-charset=GBK -o 提示窗口.exe

#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void create_box(char *message)
{
    MessageBoxA(NULL, message, "管宇轩提醒", MB_OK);
}

char *messages[] = {"快来打瓦", "记得刷每日商店", "给我发枪", "谁还有多余资金", "我方还剩艺人", "叫妈妈"};

int main()
{
    system("@echo off");
    srand(time(0));

    for (int i = 0; i < 20; i++)
    {
        char *message = messages[rand() % 6];
        create_box(message);
    }

    return 0;
}