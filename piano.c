#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

// 音符频率定义 (Hz) - 三个八度
#define C3 131
#define Db3 139
#define D3 147
#define Eb3 156
#define E3 165
#define F3 175
#define Gb3 185
#define G3 196
#define Ab3 208
#define A3 220
#define Bb3 233
#define B3 247

#define C4 262
#define Db4 277
#define D4 294
#define Eb4 311
#define E4 330
#define F4 349
#define Gb4 370
#define G4 392
#define Ab4 415
#define A4 440
#define Bb4 466
#define B4 494

#define C5 523
#define Db5 554
#define D5 587
#define Eb5 622
#define E5 659
#define F5 698
#define Gb5 740
#define G5 784
#define Ab5 831
#define A5 880
#define Bb5 932
#define B5 988

// 函数声明
void playNote(int frequency, int duration);
void printInstructions();

int main()
{
    char key;
    int exitFlag = 0;

    system("cls");
    printf("=== 简易钢琴程序 (扩展音域版) ===\n");
    printInstructions();

    while (!exitFlag)
    {
        if (_kbhit())
        {
            key = _getch();

            // 第一八度 (小写字母)
            switch (key)
            {
            case 'a':
                playNote(C3, 300);
                printf("C3 ");
                break;
            case 'w':
                playNote(Db3, 300);
                printf("C#3 ");
                break;
            case 's':
                playNote(D3, 300);
                printf("D3 ");
                break;
            case 'e':
                playNote(Eb3, 300);
                printf("D#3 ");
                break;
            case 'd':
                playNote(E3, 300);
                printf("E3 ");
                break;
            case 'f':
                playNote(F3, 300);
                printf("F3 ");
                break;
            case 't':
                playNote(Gb3, 300);
                printf("F#3 ");
                break;
            case 'g':
                playNote(G3, 300);
                printf("G3 ");
                break;
            case 'y':
                playNote(Ab3, 300);
                printf("G#3 ");
                break;
            case 'h':
                playNote(A3, 300);
                printf("A3 ");
                break;
            case 'u':
                playNote(Bb3, 300);
                printf("A#3 ");
                break;
            case 'j':
                playNote(B3, 300);
                printf("B3 ");
                break;

            // 第二八度 (数字键)
            case '1':
                playNote(C4, 300);
                printf("C4 ");
                break;
            case '2':
                playNote(Db4, 300);
                printf("C#4 ");
                break;
            case '3':
                playNote(D4, 300);
                printf("D4 ");
                break;
            case '4':
                playNote(Eb4, 300);
                printf("D#4 ");
                break;
            case '5':
                playNote(E4, 300);
                printf("E4 ");
                break;
            case '6':
                playNote(F4, 300);
                printf("F4 ");
                break;
            case '7':
                playNote(Gb4, 300);
                printf("F#4 ");
                break;
            case '8':
                playNote(G4, 300);
                printf("G4 ");
                break;
            case '9':
                playNote(Ab4, 300);
                printf("G#4 ");
                break;
            case '0':
                playNote(A4, 300);
                printf("A4 ");
                break;
            case '-':
                playNote(Bb4, 300);
                printf("A#4 ");
                break;
            case '=':
                playNote(B4, 300);
                printf("B4 ");
                break;

            // 第三八度 (大写字母)
            case 'A':
                playNote(C5, 300);
                printf("C5 ");
                break;
            case 'W':
                playNote(Db5, 300);
                printf("C#5 ");
                break;
            case 'S':
                playNote(D5, 300);
                printf("D5 ");
                break;
            case 'E':
                playNote(Eb5, 300);
                printf("D#5 ");
                break;
            case 'D':
                playNote(E5, 300);
                printf("E5 ");
                break;
            case 'F':
                playNote(F5, 300);
                printf("F5 ");
                break;
            case 'T':
                playNote(Gb5, 300);
                printf("F#5 ");
                break;
            case 'G':
                playNote(G5, 300);
                printf("G5 ");
                break;
            case 'Y':
                playNote(Ab5, 300);
                printf("G#5 ");
                break;
            case 'H':
                playNote(A5, 300);
                printf("A5 ");
                break;
            case 'U':
                playNote(Bb5, 300);
                printf("A#5 ");
                break;
            case 'J':
                playNote(B5, 300);
                printf("B5 ");
                break;

            case 'q':
            case 'Q':
                exitFlag = 1;
                printf("\n退出程序\n");
                break;
            case ' ':
                printf("\n"); // 换行
                break;
            default:
                break;
            }
            fflush(stdout); // 立即输出
        }
    }

    return 0;
}

// 播放音符
void playNote(int frequency, int duration)
{
    Beep(frequency, duration);
}

// 打印使用说明
void printInstructions()
{
    printf("\n=== 使用说明 ===\n");
    printf("第一八度 (低音):\n");
    printf("  C3 D3 E3 F3 G3 A3 B3\n");
    printf("  a  s  d  f  g  h  j\n");
    printf("  黑键: w e t y u\n\n");

    printf("第二八度 (中音):\n");
    printf("  C4 D4 E4 F4 G4 A4 B4\n");
    printf("  1  2  3  4  5  6  7  8  9  0  -  =\n");
    printf("  黑键: 2 4 7 9 -\n\n");

    printf("第三八度 (高音):\n");
    printf("  C5 D5 E5 F5 G5 A5 B5\n");
    printf("  A  S  D  F  G  H  J\n");
    printf("  黑键: W E T Y U\n\n");

    printf("空格键: 换行    Q键: 退出\n");
    printf("==========================\n\n");
    printf("开始演奏: ");
}