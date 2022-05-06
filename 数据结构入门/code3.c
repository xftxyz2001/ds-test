// 7-1 小明的晚饭 20分
// 小明最近很用功学习，所以经常忘记吃饭。小明决定给自己放个假去大吃一顿，到了吃饭的地方后，小明陷入了沉思，
// 因为他很纠结不知道吃什么,所以他全都要。小明的食量是无限的并且是个贪心的人，所以他想吃完自己支付范围内所有最贵的饭。
// 他从最贵的饭店开始吃，若剩下的钱不足以吃当前最贵的饭店，则往下寻找较贵的饭店。直到钱财为空或者已经吃不起最便宜的饭了。
// 当然小明是个有原则的人，他绝对不会重复吃已经吃过的餐厅。但是他学完习思考不出来该吃啥了，需要你的帮助
// (Hint:小明不做其他选择，只要贵的，即使贵的饭吃的少而便宜的饭能吃的多，他也会选择最贵的)

// 输入格式:
// 输入一个p表示小明拥有的钱(1<=n<=10000)，在输入一个n表示小明有n(1<=n<=100)种选择，接下来的n行，
// 每一行包含一个字符串表示饭店店名和在该饭店吃饭的价格。字符串长度不超过20。

// 输出格式:
// 输出小明能够吃到的饭，如果小明什么都吃不起，则输出“chitu”。

// 输入样例:
// 10 5
// McDonald's 2
// KFC 6
// Yifan 1
// Erfan 3
// Sanfan 4
// 结尾无空行

// 输出样例:
// KFC
// Sanfan
// 结尾无空行

#include <stdio.h>
#include <stdlib.h>

typedef struct Choose
{
    char name[20];
    int money;
} Choose;

int main(int argc, char const *argv[])
{
    int p = 0, n = 0; // p:小明拥有的的钱 n:小明的选择
    scanf("%d%d", &p, &n);
    Choose *choose = malloc(n * sizeof(Choose));
    for (size_t i = 0; i < n; i++)
    {
        scanf("%s%d", choose[i].name, &choose[i].money);
    }
    // 排序
    for (size_t i = 0; i < n; i++)
    {
        size_t max_money_index = i;
        for (size_t j = i + 1; j < n; j++)
        {
            if (choose[j].money > choose[max_money_index].money)
            {
                max_money_index = j;
            }
        }
        if (max_money_index != i)
        {
            Choose temp = choose[max_money_index];
            choose[max_money_index] = choose[i];
            choose[i] = temp;
        }
    }
    // for (size_t i = 0; i < n; i++)
    // {
    //     printf("%s %d\n", choose[i].name, choose[i].money);
    // }

    if (p < choose[n - 1].money)
    {
        printf("chitu\n");
        return 0;
    };
    for (int k = 0; p >= choose[n - 1].money && k < n; k++)
    {
        if (p < choose[k].money)
        {
            continue;
        }

        p -= choose[k].money;
        printf("%s\n", choose[k].name, choose[k].money);
    }

    return 0;
}
