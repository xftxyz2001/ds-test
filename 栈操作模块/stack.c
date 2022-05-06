#include "stack.h"
#include "StackArrayChar.h"
#include "StackArrayDouble.h"

int main()
{
    int num, r;
    char c;
    char e[Length_Input_Expression];
    menu();
    SetConsoleTitle(L"栈结构实验程序");
    while ((c = _getch()) != 27)
    {
        // menu();
        // scanf_s("%d", &c);
        system("cls");
        switch (c - '0')
        {
        default:
            printf("输入有误，请重新输入！\n");
            Sleep(300);
            system("cls");
            menu();
            continue;
            // case 0:
            // printf("程序已退出！\n");
            // return 0;
        case 1:
            SetConsoleTitle(L"系统随机展示");
            show();
            c = _getch();
            system("cls");
            break;
        case 2:
            SetConsoleTitle(L"中缀表达式转后缀表达式[逆波兰式]");
            // printf("请输入表达式：\n");
            do
            {
                SetConsoleTitle(L"中缀表达式转后缀表达式[逆波兰式]---请输入表达式");
                printf(">>>");
                scanf_s("%s", e, Length_Input_Expression);
                printf("ans=%s\n", to_Reverse_Polish_notation(e));
                // printf("\n");
                SetConsoleTitle(L"中缀表达式转后缀表达式[逆波兰式]---按任意键以继续！(ESC退出此模块)");
            } while (_getch() != 27);
            system("cls");
            break;
        case 3:
            SetConsoleTitle(L"进制转换");
            // printf("格式【10进制数字 转换到的进制数】：\n");
            do
            {
                SetConsoleTitle(L"进制转换:格式【10进制数字 转换到的进制数】---请输入表达式");
                printf(">>>");
                scanf_s("%d %d", &num, &r);
                printf("ans=%s\n", to_r(num, r));
                // printf("按任意键以继续！(ESC退出此模块)\n");
                SetConsoleTitle(L"进制转换:格式【10进制数字 转换到的进制数】---按任意键以继续！(ESC退出此模块)");
            } while (_getch() != 27);
            system("cls");
            break;
        case 4:
            SetConsoleTitle(L"表达式计算");
            // printf("请输入表达式：\n");
            do
            {
                SetConsoleTitle(L"表达式计算---请输入表达式");
                printf(">>>");
                scanf_s("%s", e, Length_Input_Expression);
                // printf("ans=%.2f\n", calculateExpression(e));
                printf("ans=%g\n", calculateExpression(e));
                // printf("按任意键以继续！(ESC退出此模块)\n");
                SetConsoleTitle(L"表达式计算---按任意键以继续！(ESC退出此模块)");
            } while (_getch() != 27);
            system("cls");
            break;
        }
        menu();
        SetConsoleTitle(L"栈结构实验程序");
    }
    printf("程序已退出！\n");
    return 0;
}

void menu()
{
    printf("==================================================================================================================\n");
    printf("==================================================1.系统随机展示==================================================\n");
    printf("========================================2.中缀表达式转后缀表达式[逆波兰式]========================================\n");
    printf("====================================================3.进制转换====================================================\n");
    printf("===============================================4.表达式计算[+-*/^()]==============================================\n");
    printf("==================================================ESC.退出程序====================================================\n");
    printf("==================================================================================================================\n::");
}

void show()
{
    int num = 0, jz = 0;
    int jinzhi[3] = {2, 8, 16};
    char *bds;
    srand((unsigned int)time(NULL));
    system("cls");
    printf("    (1)假设表达式由单字母变量和双目四则运算算符构成。试写一个算法，将一个通常书写形式且书写正确的表达式转换为逆波兰式。\n");
    for (int i = 0; i < create_number; i++)
    {
        bds = createExpression();
        printf("表达式 %s 的逆波兰式为: %s\n", bds, to_Reverse_Polish_notation(bds));
    }
    printf("\n");

    printf("    (2)编写算法，利用栈的基本操作，将一个十进制整数n转换为r进制。\n");
    for (int i = 0, newline = 0; i < create_number; i++)
    {
        num = rand() % 1000;
        jz = rand() % 3;
        printf("%3d转化为%2d进制:%10s\t\t", num, jinzhi[jz], to_r(num, jinzhi[jz]));
        if (++newline % 3 == 0)
        {
            printf("\n");
        }
    }
    printf("\n\n");

    printf("    (3)编写一个复杂表达式的计算程序。\n");
    // 1 2 3 4 * + 5 + + 6 * 7 8 * 9 * +
    // printf("表达式 %s 的逆波兰式为: %s\n", "6/7*15/3/2*1-12*26/30", to_Reverse_Polish_notation("6/7*15/3/2*1-12*26/30"));
    // printf("表达式 %s 的计算结果为： %d\n", "6/7*15/3/2*1-12*26/30", calculateExpression("6/7*15/3/2*1-12*26/30"));
    for (int i = 0; i < create_number; i++)
    {
        bds = createExpression();
        // printf("表达式 %s 的计算结果为: %.2f\n", bds, calculateExpression(bds));
        printf("表达式 %s 的计算结果为: %g\n", bds, calculateExpression(bds));
    }
    printf("\n");
    printf("注：表达式由系统随机生成，可能出现无法计算出值的情况。系统生成的表达式不包含括号和浮点数，但函数实现了带括号的浮点数四则运算，可以通过手动输入表达式体验。%% & |运算将截取两操作数整数部分进行运算。\n");
    printf("按任意键以继续！\n");
}

char *createExpression()
{
    char *res;
    char num_char[Digits_per_operand_Size];
    int flag = 1;
    int res_length = 0;
    char *yunsuanfu = OPERATOR;
    res = (char *)malloc(sizeof(char) * Length_Expression);
    while (1)
    {
        if (flag)
        {
            for (int i = 0; i < Digits_per_operand_Size; i++)
            {
                num_char[i] = '\0';
            }
            // double r_num = 0;
            _itoa_s(rand() % (10 * Digits_per_operand_Size) + 1, num_char, Digits_per_operand_Size, 10);
            // r_num = rand() / 10000.0;
            // RAND_MAX
            //_gcvt_s(num_char, Digits_per_operand_Size, r_num, Digits_per_operand_Size - 2);
            for (int i = 0; num_char[i]; i++)
            {
                res[res_length++] = num_char[i];
            }
            flag = 0;
        }
        else
        {
            res[res_length++] = yunsuanfu[rand() % OPERATOR_NUMBER];
            flag = 1;
        }
        if (res_length + 5 > Length_Expression && flag == 0)
        {
            break;
        }
    }
    res[res_length] = '\0';
    return res;
}

int getPriority(char ch)
{
    switch (ch)
    {
    default:
        // printf("error");
        return 0;
        // case '(':  //')'不入栈
        //	return 0;
    // case '~':
    //	return 1;
    case '^':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '+':
    case '-':
        return 3;
    case '&':
        return 4;
    case '|':
        return 5;
    }
}

double calculate(double a, double b, char c)
{
    switch (c)
    {
        // case '~':return ~(int)a;
    case '^':
        return pow(a, b);
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '%':
        return (int)a % (int)b;
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '&':
        return (int)a & (int)b;
    case '|':
        return (int)a | (int)b;
    }
    return 0;
}

/*int calculate(int a, int b, char c)
{
    int res;
    switch (c)
    {
    default:res = 0;
        break;
    case '+':res = a + b; break;
    case '-':res = a - b; break;
    case '*':res = a * b; break;
    case '/':res = a / b; break;
    }
    return res;
}*/

/*int isDigit(char ch)
{
    return (ch >= '0' && ch <= '9') ? 1 : 0;
}*/

int isDigit(char ch)
{
    return (ch >= '0' && ch <= '9' || ch == '.') ? 1 : 0;
}

char *to_Reverse_Polish_notation(char *Expression)
{
    // int debug = 0;
    char *res, *res_p;
    char yunsuanfu;
    StackArrayChar *sc;
    res = (char *)malloc(sizeof(char) * Length_Expression * 2);
    res_p = res;
    sc = (StackArrayChar *)malloc(sizeof(StackArrayChar));
    Init_StackArrayChar(sc);
    while (*Expression)
    {

        // printf("%c", *Expression);
        //先判断是操作数
        while (isDigit(*Expression))
        {
            *res_p++ = *Expression++;
            if (!isDigit(*Expression))
            {
                /*
                if (*Expression == '\0')
                {
                    break;
                    //return res;
                }
                */
                *res_p++ = ' ';
                break;
            }
        }
        //操作符
        if (*Expression == '\0')
        {
            break;
        }
        else if (*Expression == '(')
        {
            Push_StackArrayChar(sc, *Expression++);
        }
        else if (*Expression == ')')
        {
            while (Pop_StackArrayChar(sc, &yunsuanfu))
            {
                if (yunsuanfu != '(')
                {
                    // printf(")read\n");
                    *res_p++ = yunsuanfu;
                    *res_p++ = ' ';
                }
                else
                {
                    break;
                }
            }
            Expression++;
        }
        else if (GetTop_StackArrayChar(sc, &yunsuanfu))
        {
            while (GetTop_StackArrayChar(sc, &yunsuanfu))
            {
                //优先级不可比较或表达式的运算符优先级高，压栈
                if (!getPriority(yunsuanfu) || getPriority(*Expression) < getPriority(yunsuanfu))
                {
                    Push_StackArrayChar(sc, *Expression++);
                    break;
                }
                else //表达式的运算符优先级不高于栈中的
                {
                    Pop_StackArrayChar(sc, res_p++);
                    *res_p++ = ' ';
                }
            } // end while
        }
        else
        {
            Push_StackArrayChar(sc, *Expression++);
        }
        // printf("%d:::::%s\n", ++debug, res);
    } // end while
    while (!IsEmpty_StackArrayChar(sc))
    {
        Pop_StackArrayChar(sc, res_p++);
        *res_p++ = ' ';
    }
    *res_p++ = '\0';
    return res;
}

char *to_r(int num, int r)
{
    char *res, *p;
    StackArrayChar *sc = (StackArrayChar *)malloc(sizeof(StackArrayChar));
    Init_StackArrayChar(sc);
    while (num != 0)
    {
        char ch;
        switch (num % r)
        {
        case 0:
            ch = '0';
            break;
        case 1:
            ch = '1';
            break;
        case 2:
            ch = '2';
            break;
        case 3:
            ch = '3';
            break;
        case 4:
            ch = '4';
            break;
        case 5:
            ch = '5';
            break;
        case 6:
            ch = '6';
            break;
        case 7:
            ch = '7';
            break;
        case 8:
            ch = '8';
            break;
        case 9:
            ch = '9';
            break;
        case 10:
            ch = 'a';
            break;
        case 11:
            ch = 'b';
            break;
        case 12:
            ch = 'c';
            break;
        case 13:
            ch = 'd';
            break;
        case 14:
            ch = 'e';
            break;
        case 15:
            ch = 'f';
            break;
        default:
            ch = 'n';
            break;
        } // end switch
        if (!Push_StackArrayChar(sc, ch))
        {
            return "error";
        }
        num /= r;
    }                                             // end while
    res = (char *)malloc(sizeof(char) * sc->top); // sc->top+1?
    for (p = res; Pop_StackArrayChar(sc, p); p++)
        ;
    /*
    for (p = res; Pop_StackArrayChar(sc, p); p++)
    {
        printf("%s\n", res);
    }
    */
    *p = '\0';
    return res;
}

double calculateExpression(char *Expression)
{
    double res, num = 0, a, b;
    int haveDot = 0; //小于0表示在小数点后面了
    char *e_rpn = to_Reverse_Polish_notation(Expression);
    StackArrayDouble *sd = (StackArrayDouble *)malloc(sizeof(StackArrayDouble));
    Init_StackArrayDouble(sd);
    while (*e_rpn != '\0')
    {
        while (isDigit(*e_rpn)) //两种情况，一种是数字，一种是.
        {
            if (*e_rpn == '.') //如果读到小数点，标记小数点
            {
                haveDot--; //标记小数点
                e_rpn++;
                continue;
            }
            if (haveDot < 0)
            {
                num += (*e_rpn - 48) * pow(10, haveDot--);
            }
            else
            {
                num = num * 10 + (*e_rpn - 48);
            }
            e_rpn++;
            if (!isDigit(*e_rpn))
            {
                Push_StackArrayDouble(sd, num);
                // printf("入栈%d\n", num);//
                // printf("%d\n", num);
                num = 0; //入栈操作后将num初始化
                haveDot = 0;
                e_rpn++;
                break;
            }
            //}
        }
        while (getPriority(*e_rpn)) //如果不是个运算符，get的返回值为0
        {
            // printf("%c ", *e_rpn);
            Pop_StackArrayDouble(sd, &a); //右操作数
            Pop_StackArrayDouble(sd, &b); //左操作数
            num = calculate(b, a, *e_rpn);
            // printf("运算%d%c%d=%d\n", b, *e_rpn, a, num);//
            Push_StackArrayDouble(sd, num);
            // printf("入栈%d\n", num);//
            num = 0; //入栈操作后将num初始化
            e_rpn += 2;
        }
    }
    GetTop_StackArrayDouble(sd, &res);
    return res;
}
