#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char color[10];
    int number;
    int code;
} Card;

typedef struct
{
    Card card[52];
    int count;
} Group;

int cmpTo(Card a, Card b)
{
    if (a.number > b.number)
    {
        return 1;
    }
    else if (a.number < b.number)
    {
        return -1;
    }
    else if (a.code > b.code)
    {
        return 1;
    }
    else
    {
        // 判断至此花色不可能相同
        return -1;
    }
}

int swap(Card *a, Card *b)
{
    Card temp = *b;
    *b = *a;
    *a = temp;
}

int main(int argc, char const *argv[])
{
    // t:测试组数
    int t, i, j, k;
    int n[20] = {0};
    scanf("%d", &t);
    getchar();
    // Card card[t][20];
    Group *group = malloc(t * sizeof(Group));
    char line[1000];
    // Card temp;

    for (i = 0; i < t; i++)
    {
        gets(line);
        char *p = line;
        group[i].count = 0;
        // while (*p != '\0')
        // {
        // while (*p == ' ')
        //     p++;
        // if (*p == '\0')
        //     break;
        // sscanf(p, "%s%d", group[i].card->color, &group[i].card->number);

        // }
        // 记录当前组的牌的牌数.
        while (*p != '\0')
        {
            int shuzi = 0;
            int huase = 0;
            switch (*p)
            {
            case 's':
                huase = 4;
                strcat(group[i].card[group[i].count].color, "spade");
                sscanf(p + 6, "%d", &shuzi);
                (shuzi / 10 > 0) ? (p += 8) : (p += 7);
                break;
            case 'h':
                huase = 3;
                strcat(group[i].card[group[i].count].color, "heart");
                sscanf(p + 6, "%d", &shuzi);
                (shuzi / 10 > 0) ? (p += 8) : (p += 7);
                break;
            case 'c':
                huase = 2;
                strcat(group[i].card[group[i].count].color, "club");
                sscanf(p + 5, "%d", &shuzi);
                (shuzi / 10 > 0) ? (p += 7) : (p += 6);
                break;
            case 'd':
                huase = 1;
                strcat(group[i].card[group[i].count].color, "diamond");
                sscanf(p + 8, "%d", &shuzi);
                (shuzi / 10 > 0) ? (p += 10) : (p += 9);
                break;
            default:
                p++;
                break;
            }
            if (shuzi != 0)
            {
                group[i].card[group[i].count].code = huase;
                group[i].card[group[i].count].number = shuzi;
                group[i].count++;
            }
        }
    }
    int m, mm;
    for (i = 0; i < t; i++)
    {
        for (m = 0; m < group[i].count; m++)
        {
            int max = m;
            for (mm = m + 1; mm < group[i].count; mm++)
            {
                if (cmpTo(group[i].card[mm], group[i].card[max]) > 0)
                {
                    max = mm;
                }
            }
            if (max != m)
            {
                swap(&group[i].card[m], &group[i].card[max]);
            }
        }
    }

    for (i = 0; i < t; i++)
    {
        for (m = 0; m < group[i].count; m++)
        {
            printf("%s %d", group[i].card[m].color, group[i].card[m].number);
            if (m != group[i].count - 1)
            { //除了最后一张牌,其他的要用空格隔开
                printf(" ");
            }
        }
        if (i != t - 1)
        { //除了最后一组牌,之前的要换行.
            printf("\n");
        }
    }

    return 0;
}
