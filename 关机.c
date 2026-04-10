#include <stdio.h>
#include <windows.h>
#include <string.h>

int main()
{
    printf("输入多长时间后关机\n");
    printf("例如 3h代表3小时后关机，3min代表3分钟后关机，3h6min代表3小时6分钟后关机\n");
    printf("不输入默认3分钟关机\n");
    printf("输入-1解除关机\n");
    printf("输入多长时间后关机: ");

    char input[20] = {0};
    int if_not_shutdown = 0;
    int total_second = 0;

    if (scanf("%[^\n]", input) == 1)
    {
        printf("你输入的是: %s\n", input); // 调试信息

        // 首先检查是否是解除关机的命令
        if (strcmp(input, "-1") == 0)
        {
            if_not_shutdown = 1;
            printf("检测到取消关机命令\n");
        }
        else
        {
            int hour = 0, minute = 0;
            char temp[20];
            strcpy(temp, input);

            // 方法1：使用更灵活的解析
            if (strstr(temp, "h") != NULL && strstr(temp, "min") != NULL)
            {
                // 格式: XhYmin
                if (sscanf(temp, "%dh%dmin", &hour, &minute) == 2)
                {
                    total_second = hour * 3600 + minute * 60;
                    printf("解析为 %d小时%d分钟\n", hour, minute);
                }
            }
            else if (strstr(temp, "h") != NULL)
            {
                // 格式: Xh
                if (sscanf(temp, "%dh", &hour) == 1)
                {
                    total_second = hour * 3600;
                    printf("解析为 %d小时\n", hour);
                }
            }
            else if (strstr(temp, "min") != NULL)
            {
                // 格式: Xmin
                if (sscanf(temp, "%dmin", &minute) == 1)
                {
                    total_second = minute * 60;
                    printf("解析为 %d分钟\n", minute);
                }
            }
            else
            {
                // 无法识别的输入，使用默认值
                total_second = 180;
                printf("无法识别输入，使用默认3分钟\n");
            }
        }
    }
    else
    {
        total_second = 180;
        printf("使用默认3分钟\n");
    }

    if (if_not_shutdown)
    {
        printf("执行取消关机命令...\n");
        system("shutdown -a");
        printf("已取消关机计划\n");
    }
    else
    {
        char command[100];
        sprintf(command, "shutdown -s -f -t %d", total_second);
        printf("执行命令: %s\n", command);
        system(command);
        printf("已设置 %d 秒后关机\n", total_second);

        // 显示更友好的时间格式
        int hours = total_second / 3600;
        int minutes = (total_second % 3600) / 60;
        int seconds = total_second % 60;
        printf("相当于: ");
        if (hours > 0)
            printf("%d小时", hours);
        if (minutes > 0)
            printf("%d分钟", minutes);
        if (seconds > 0)
            printf("%d秒", seconds);
        printf("\n");
    }

    return 0;
}
