// 7-2 纸牌排序 30分
// 小诺诺喜欢玩纸牌比大小的游戏。现在有一副牌中的若干张纸牌，需要按牌面的数字从大到小的顺序排列，
// 若数字大小相同则按花色从大到小（黑桃>红桃>梅花>方块）排列。牌面为A、J、Q、K分别用1、11、12、13表示；
// 花色中的黑桃、红桃、梅花、方块分别用英文单词"spade"、"heart"、"club"、"diamond"表示。

// 输入格式:
// 测试数据有多组，首先输入测试的组数T （0<T<10），然后是T组测试数据；每组测试输入一行，
// 按“花色 数字”的格式输入若干张牌，花色可能为"spade"、"heart"、"club"、"diamond"之一，数字为1~13。
// 输入的数据之间可能有若干（至少1个）空格，在行的首尾也可能有若干空格，但每组输入数据的总长度不会超过1000个字符。

// 输出格式:
// 每组测试输出一行，按描述中的排序规则从大到小输出牌的信息，数据之间都以一个空格分隔。

// 输入样例:
// 2
//  diamond 1 club 1  heart 1  spade 3 diamond 2 club 3 heart 2
// diamond 13 club 13 heart 13    spade 12

// 输出样例:
// spade 3 club 3 heart 2 diamond 2 heart 1 club 1 diamond 1
// heart 13 club 13 diamond 13 spade 12

#include <stdio.h>

int main(int argc, char const *argv[])
{
    char has[52];
    char *pai[52] = {"spade 13", "heart 13", "club 13", "diamond 13",
                     "spade 12", "heart 12", "club 12", "diamond 12",
                     "spade 11", "heart 11", "club 11", "diamond 11",
                     "spade 10", "heart 10", "club 10", "diamond 10",
                     "spade 9", "heart 9", "club 9", "diamond 9",
                     "spade 8", "heart 8", "club 8", "diamond 8",
                     "spade 7", "heart 7", "club 7", "diamond 7",
                     "spade 6", "heart 6", "club 6", "diamond 6",
                     "spade 5", "heart 5", "club 5", "diamond 5",
                     "spade 4", "heart 4", "club 4", "diamond 4",
                     "spade 3", "heart 3", "club 3", "diamond 3",
                     "spade 2", "heart 2", "club 2", "diamond 2",
                     "spade 1", "heart 1", "club 1", "diamond 1"};
    int n = 0;
    char re[1000];
    scanf("%d", &n);
    getchar();
    while (n > 0)
    {
        // 初始化
        int huase = 0;
        int shuzi = 0;
        for (size_t i = 0; i < 52; i++)
        {
            has[i] = 0;
        }
        // 读取一组输入
        gets(re);
        // 分析输入
        char *rep = re;
        while (*rep != '\0')
        {
            shuzi = 0;
            switch (*rep)
            {
            case 's':
                huase = 0;
                sscanf(rep + 6, "%d", &shuzi);
                (shuzi / 10 > 0) ? (rep += 8) : (rep += 7);
                break;
            case 'h':
                huase = 1;
                sscanf(rep + 6, "%d", &shuzi);
                (shuzi / 10 > 0) ? (rep += 8) : (rep += 7);
                break;
            case 'c':
                huase = 2;
                sscanf(rep + 5, "%d", &shuzi);
                (shuzi / 10 > 0) ? (rep += 7) : (rep += 6);
                break;
            case 'd':
                huase = 3;
                sscanf(rep + 8, "%d", &shuzi);
                (shuzi / 10 > 0) ? (rep += 10) : (rep += 9);
                break;
            default:
                rep++;
                break;
            }
            if (shuzi != 0)
            {
                has[(13 - shuzi) * 4 + huase] = 1;
            }
        }
        // 输出
        int start = 0;
        for (size_t i = 0; i < 52; i++)
        {
            if (has[i])
            {
                if (start)
                {
                    printf(" ");
                }
                start = 1;
                printf("%s", pai[i]);
            }
        }
        if (n != 1)
        {
            printf("\n");
        }
        n--;
    }

    return 0;
}
