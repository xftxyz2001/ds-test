#include "test.h"

int main(int argc, char const *argv[])
{
    char c; // ctrl
    double number = 0;

    srand((unsigned int)time(NULL));
    menu();
    SetConsoleTitle(L"字符串处理模块实验演示程序");
    while ((c = _getch()) != 27)
    {
        system("cls");
        switch (c - '0')
        {
        default:
            printf("输入有误，请重新输入！\n");
            Sleep(300);
            system("cls");
            menu();
            continue;
        case 0:
            SetConsoleTitle(L"系统随机展示");
            show();
            c = _getch();
            system("cls");
            break;
        case 1:
            SetConsoleTitle(L"单词统计");
            do
            {
                SetConsoleTitle(L"单词统计---请输入表达式[最后一个单词的空格不能省略]");
                printf(">>>");
                HString *s = str_create();
                str_assign_charlist(s, get_line_to_charlist());
                HStrings *long_words = hss_create();
                HStrings *short_words = hss_create();
                long nln = 0;
                long_words = get_long_words(s);
                short_words = get_short_words(s);
                system("cls");
                printf("::%s\n", to_string(s));
                while (long_words = long_words->next)
                {
                    printf("\t最长的单词(出现的次数)：%s(%d)\t", to_string(long_words->s), long_words->count);
                    if (++nln % 3 == 0)
                    {
                        printf("\n");
                    }
                }
                while (short_words = short_words->next)
                {
                    printf("\t最短的单词(出现的次数)：%s(%d)\t", to_string(short_words->s), short_words->count);
                    if (++nln % 3 == 0)
                    {
                        printf("\n");
                    }
                }
                printf("\n");
                SetConsoleTitle(L"单词统计---按任意键以继续！(ESC退出此模块)");
            } while (_getch() != 27);
            system("cls");
            break;
        case 2:
            SetConsoleTitle(L"字符串重排");
            do
            {
                SetConsoleTitle(L"字符串重排---请输入表达式");
                printf(">>>");
                printf(":::%s\n", rearrangement(get_line_to_charlist()));
                SetConsoleTitle(L"字符串重排---按任意键以继续！(ESC退出此模块)");
            } while (_getch() != 27);
            system("cls");
            break;
        case 3:
            SetConsoleTitle(L"最长相同子串");
            do
            {
                SetConsoleTitle(L"最长相同子串---请输入表达式");
                printf(">>>");
                HString *s = str_create();
                HString *sub = str_create();
                str_assign_charlist(s, get_line_to_charlist());
                long pos = find_max_sub_string(s, sub);
                // find_max_sub_string(s, sub);
                printf("ans=(%ld)%s\n", pos, to_string(sub));
                SetConsoleTitle(L"最长相同子串---按任意键以继续！(ESC退出此模块)");
            } while (_getch() != 27);
            system("cls");
            break;
        case 4:
            SetConsoleTitle(L"计算两个长整数的和");
            do
            {
                SetConsoleTitle(L"计算两个长整数的和---请输入表达式1");
                printf(">>>");
                HString *sa = str_create();
                str_assign_charlist(sa, get_line_to_charlist());
                SetConsoleTitle(L"计算两个长整数的和---请输入表达式2");
                printf(">>>");
                HString *sb = str_create();
                str_assign_charlist(sb, get_line_to_charlist());
                printf("ans=%s\n", to_string(big_number_mul(sa, sb)));
                SetConsoleTitle(L"计算两个长整数的和---按任意键以继续！(ESC退出此模块)");
            } while (_getch() != 27);
            system("cls");
            break;
        case 5:
            SetConsoleTitle(L"计算两个长整数的积");
            do
            {
                SetConsoleTitle(L"计算两个长整数的积---请输入表达式1");
                printf(">>>");
                HString *sa = str_create();
                str_assign_charlist(sa, get_line_to_charlist());
                SetConsoleTitle(L"计算两个长整数的积---请输入表达式2");
                printf(">>>");
                HString *sb = str_create();
                str_assign_charlist(sb, get_line_to_charlist());
                printf("ans=%s\n", to_string(big_number_mul(sa, sb)));
                SetConsoleTitle(L"计算两个长整数的积---按任意键以继续！(ESC退出此模块)");
            } while (_getch() != 27);
            system("cls");
            break;
        case 6:
            SetConsoleTitle(L"浮点数转字符串");
            do
            {
                SetConsoleTitle(L"浮点数转字符串---请输入表达式");
                printf(">>>");
                double num_double = 12.34;
                int jd = 1;
                scanf_s("%lf", &num_double);
                SetConsoleTitle(L"浮点数转字符串---请输入精度");
                scanf_s("%d", &jd);
                printf("ans=%s\n", double_to_string(num_double, jd));
                SetConsoleTitle(L"浮点数转字符串---按任意键以继续！(ESC退出此模块)");
            } while (_getch() != 27);
            system("cls");
            break;
        case 9:
            SetConsoleTitle(L"调试");
            // debug
            HString *sa = str_create();
            HString *sb = str_create();
            sa = bignumber_create(3);
            sb = bignumber_create(3);
            printf("%s * %s = ", to_string(sa), to_string(sb));
            printf("%s\n", to_string(big_number_mul(sa, sb)));
            break;
        }
        menu();
        SetConsoleTitle(L"字符串处理模块实验演示程序");
    }
    printf("程序已退出！\n");
    return 0;
}

void show()
{
    double num;
    int jd;

    system("cls");
    printf("（1）找出字符串中最长、最短单词并统计词数。如果有多个最长或最短的单词，则将其全部输出。\n");
    for (int i = 0; i < create_number; i++)
    {
        jd = rand() % 200 + 10;
        HString *s = str_create();
        // HString* long_word = str_create();
        // HString* short_word = str_create();
        HStrings *long_words = hss_create();
        HStrings *short_words = hss_create();
        long nln = 0;
        // int len_long, len_short;
        while (jd--)
        {
            HString *temp = word_create();
            // printf("aaa");
            str_cat(s, temp);
        }
        printf("  %s\n", to_string(s));
        long_words = get_long_words(s);
        short_words = get_short_words(s);
        while (long_words = long_words->next)
        {
            printf("\t最长的单词(出现的次数)：%s(%d)\t", to_string(long_words->s), long_words->count);
            if (++nln % 3 == 0)
            {
                printf("\n");
            }
        }
        while (short_words = short_words->next)
        {
            printf("\t最短的单词(出现的次数)：%s(%d)\t", to_string(short_words->s), short_words->count);
            if (++nln % 3 == 0)
            {
                printf("\n");
            }
        }
        printf("\n");
        //	to_string(long_word), len_long, to_string(short_word), len_short);
    }
    printf("\n");

    printf("（2）对一个字符串重新排列，字母排在前面，数字排在后面，并不改变原来字母之间以及数字之间的字符顺序。\n");
    for (int i = 0; i < create_number; i++)
    {
        int sl = rand() % 40 + 10;
        Char *list = char_create();
        Char *lsave = list;
        list->next = NULL;
        for (int j = 0; j < sl; j++)
        {
            _insert_char(list, (char)(rand() % LAST + START));
            list = list->next;
        }
        printf("\t排列前：");
        op(lsave);
        printf("\t排列后：%s\n", rearrangement(lsave));
    }
    printf("\n");

    printf("（3）输入一行字符串，找出其中出现的相同且长度最长的字符串，输出它及其首字符的位置。\n");
    for (int i = 0; i < create_number; i++)
    {
        int sl = rand() % 300 + 60;
        long pos = 0;
        Char *list = char_create();
        Char *lsave = list;
        HString *s, *sub;
        list->next = NULL;
        for (int j = 0; j < sl; j++)
        {
            _insert_char(list, (char)(rand() % 26 + BIG_START));
            list = list->next;
        }
        printf("\t原始字符串：");
        op(lsave);
        s = str_create();
        sub = str_create();
        str_assign_charlist(s, lsave);
        pos = find_max_sub_string(s, sub);
        // find_max_sub_string(s, sub);
        printf("\t结果：(%ld)%s\n", pos, to_string(sub));
    }
    printf("\n");

    printf("（4）计算两个长整数的和。\n");
    for (int i = 0; i < create_number; i++)
    {
        HString *sa = str_create();
        HString *sb = str_create();
        sa = bignumber_create(6);
        sb = bignumber_create(6);
        // printf("%s + %s = \n", to_string(sa), to_string(sb));
        printf("%s + %s = ", to_string(sa), to_string(sb));
        printf("%s\n", to_string(big_number_add(sa, sb)));
    }
    printf("\n");

    printf("（5）计算两个长整数的积。\n");
    for (int i = 0; i < create_number; i++)
    {
        HString *sa = str_create();
        HString *sb = str_create();
        sa = bignumber_create(3);
        sb = bignumber_create(3);
        printf("%s * %s = ", to_string(sa), to_string(sb));
        printf("%s\n", to_string(big_number_mul(sa, sb)));
    }
    printf("\n");

    printf("（6）输入浮点数，然后将其转换为字符串输出。\n");
    for (int i = 0; i < create_number; i++)
    {
        num = rand() / 1000.0;
        jd = rand() % 10;
        printf("\t浮点数%10lf转化为字符串(精度：%d位):%12s\n", num, jd, double_to_string(num, jd));
    }
    printf("\n");
    printf("注：\n");
    printf("按任意键以继续！\n");
}

void menu()
{
    printf("=======================================================================================================\n");
    printf("==========================================（0）系统随机展示。==========================================\n");
    printf("========（1）找出字符串中最长、最短单词并统计词数。如果有多个最长或最短的单词，则将其全部输出。========\n");
    printf("==（2）对一个字符串重新排列，字母排在前面，数字排在后面，并不改变原来字母之间以及数字之间的字符顺序。==\n");
    printf("==========（3）输入一行字符串，找出其中出现的相同且长度最长的字符串，输出它及其首字符的位置。==========\n");
    printf("=======================================（4）计算两个长整数的和。=======================================\n");
    printf("=======================================（5）计算两个长整数的积。=======================================\n");
    printf("==============================（6）输入浮点数，然后将其转换为字符串输出。==============================\n");
    printf("===========================================（ESC）退出程序。===========================================\n::");
}
