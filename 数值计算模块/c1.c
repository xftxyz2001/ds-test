#include <stdio.h>
#include <math.h>
#define HUAFENGESHU 10
#define JIFENJINGDU 0.1
#define S_A_F12 0
#define S_B_F1 3
#define S_B_F2 2

//待积分函数
double f1(double x)
{
    return x / (1 + x * x);
}

double f2(double x)
{
    return 1 + x * x;
}

//矩形法
double rint1(double a,            //积分下限
             double b,            //积分上限
             int n,               //划分个数
             double (*f)(double)) //被积函数指针
{
    int i;
    double x = a, h = (b - a) / n, s = 0.0;
    for (i = 1; i < n; i++)
        s += (*f)(x += h) * h;
    return s;
}

//变步长矩形法
double rint2(double a,            //积分下限
             double b,            //积分上限
             double eps,          //积分精度要求
             double (*f)(double)) //被积函数指针
{
    int n = 1, i = 0;
    double x = a, h = b - a, s = (*f)(x)*h, s1 = 0.0, p = 0;
    do
    {
        s1 = 0.0;
        x = a;
        for (i = 1; i <= n; i++)
        {
            x += h;
            s1 += (*f)(x)*h; //计算每次二等分后的积分值
        }
        p = fabs(s1 - s);
        s = s1;
        n += n;
        h /= 2.0; //判断是否满足积分精度要求；继续对积分区间进行二等分
    } while (p >= eps);
    return s;
}

//梯形法
double tint1(double a,            //积分下限
             double b,            //积分上限
             int n,               //划分个数
             double (*f)(double)) //被积函数指针
{
    double x = a, h = (b - a) / n, s = 0.0, fa, fb;
    int i;
    for (i = 1; i < n; i++)
    {
        fa = (*f)(x + i * h);
        fb = (*f)(x + i * h + h); // ih+h
        s += (fa + fb) * h / 2;
    }
    return s;
}

//变步长梯形法
double tint2(double a,            //积分下限
             double b,            //积分上限
             double eps,          //积分精度要求
             double (*f)(double)) //被积函数指针
{
    //下面的代码是矩形的，还没来得及改。
    int n = 1, i = 0;
    double x = a, h = b - a, s = (*f)(x)*h, s1 = 0.0, p = 0, fa, fb;
    do
    {
        s1 = s;
        x = a;
        for (i = 1; i <= n; i++)
        {
            fa = (*f)(x + i * h);
            fb = (*f)(x + i * h + h); // ih+h
            s += (fa + fb) * h / 2;   //计算每次二等分后的积分值
        }
        p = fabs(s1 - s);
        n += n;
        h /= 2.0; //判断是否满足积分精度要求；继续对积分区间进行二等分
    } while (p >= eps);
    return s;
}

//辛普森法
double sint1(double a,            //积分下限
             double b,            //积分上限
             int n,               //划分个数
             double (*f)(double)) //被积函数指针
{
    double x = a, h = (b - a) / n, s = 0.0, fa, fb, fab;
    int i;
    for (i = 1; i < n; i++)
    {
        fa = (*f)(x + i * h);     // ih
        fb = (*f)(x + i * h + h); // ih+h
        fab = (fa + fb) / 2;      // ih+0.5h
        s += (fa + 4 * fab + fb) * h / 6;
    }
    return s;
}

double simp(double a, double b, double (*f)(double x))
{
    return ((b - a) / 6) * ((*f)(a) + 4 * (*f)((a + b) / 2) + (*f)(b));
}

//变步长辛普森法——待完善
double jf(double a, double b, double eps, double (*f)(double x))
{
    int i, k = 2;
    double m, n, h, d, s = simp(a, b, f), ep = eps + 1.0;
    h = (b - a) / 2;
    s = simp(a, b, f); //计算的第一次simp值
    while (ep >= eps)
    {
        m = a, n = a + h, d = 0;
        for (i = 0; i < k; i++)
        {
            d = d + simp(m, n, f); //新计算出的积分
            m = m + h;
            n = n + h;
        }
        ep = fabs(s - d);
        s = d;
        k = k * 2;
        h = h / 2;
    }
    return s;
}

//变步长辛普森法
double sint2(double a,            //积分下限
             double b,            //积分上限
             double eps,          //积分精度要求
             double (*f)(double)) //被积函数指针
{
    double fa = (*f)(a), fb = (*f)(b), h = b - a;
    double T = (fa + fb) * h / 2; // T 粗略的积分（梯形法）
    double x, S1 = T, S2, T2, ep; // S1 存储一次积分
    int n = 1;
    do
    {
        double p = 0.0;
        for (int k = 0; k <= n - 1; k++)
        {
            x = a + k * h + h / 2; //某次中间的x值
            p += (*f)(x);          //(*f)(x)某次中间的x值对应的y值
        }
        T2 = (T + h * p) / 2.0;
        S2 = (4.0 * T2 - T) / 3.0;
        ep = fabs(S2 - S1);
        T = T2;
        S1 = S2;
        n *= 2;
        h /= 2;
    } while (ep >= eps);
    return S2;
}

double cotes(double a,            //积分下限
             double b,            //积分上限
             int n,               //划分个数
             double (*f)(double)) //被积函数指针
{
    double x = a, h = (b - a) / n, s = 0.0, fa, fb, fab, f3ab, fa3b;
    int i;
    for (i = 1; i < n; i++)
    {
        fa = (*f)(x + i * h);
        fb = (*f)(x + i * h + h);
        f3ab = (3 * fa + fb) / 4;
        fab = (*f)(x + i * h + h / 2);
        fa3b = (fa + 3 * fb) / 4;
        s += (7 * (fa + fb) + 32 * (f3ab + fa3b) + 12 * fab) * h / 90;
    }
    return s;
}

int main()
{
    printf("使用矩形法进行求解:\n");
    printf("\t第一个函数的积分为：%.10f\n\t第二个函数的积分为：%.10f\n\n",
           rint1(S_A_F12, S_B_F1, HUAFENGESHU, f1), rint1(S_A_F12, S_B_F2, HUAFENGESHU, f2));
    printf("使用变步长矩形法进行求解:\n");
    printf("\t第一个函数的积分为：%.10f\n\t第二个函数的积分为：%.10f\n\n",
           rint2(S_A_F12, S_B_F1, JIFENJINGDU, f1), rint2(S_A_F12, S_B_F2, JIFENJINGDU, f2));

    printf("使用梯形法进行求解:\n");
    printf("\t第一个函数的积分为：%.10f\n\t第二个函数的积分为：%.10f\n\n",
           tint1(S_A_F12, S_B_F1, HUAFENGESHU, f1), tint1(S_A_F12, S_B_F2, HUAFENGESHU, f2));
    printf("使用变步长梯形法进行求解:\n");
    printf("\t第一个函数的积分为：%.10f\n\t第二个函数的积分为：%.10f\n\n",
           tint2(S_A_F12, S_B_F1, JIFENJINGDU, f1), tint2(S_A_F12, S_B_F2, JIFENJINGDU, f2));

    printf("使用辛普森法进行求解:\n");
    printf("\t第一个函数的积分为：%.10f\n\t第二个函数的积分为：%.10f\n\n",
           sint1(S_A_F12, S_B_F1, HUAFENGESHU, f1), sint1(S_A_F12, S_B_F2, HUAFENGESHU, f2));
    printf("使用变步长辛普森法进行求解:\n");
    printf("\t第一个函数的积分为：%.10f\n\t第二个函数的积分为：%.10f\n\n",
           sint2(S_A_F12, S_B_F1, JIFENJINGDU, f1), sint2(S_A_F12, S_B_F2, JIFENJINGDU, f2));
    printf("使用变步长辛普森法（自创）进行求解:\n");
    printf("\t第一个函数的积分为：%.10f\n\t第二个函数的积分为：%.10f\n\n",
           jf(S_A_F12, S_B_F1, JIFENJINGDU, f1), jf(S_A_F12, S_B_F2, JIFENJINGDU, f2));

    printf("使用Cotes（查阅资料）进行求解:\n");
    printf("\t第一个函数的积分为：%.10f\n\t第二个函数的积分为：%.10f\n\n",
           cotes(S_A_F12, S_B_F1, HUAFENGESHU, f1), cotes(S_A_F12, S_B_F2, HUAFENGESHU, f2));
    return 0;
}
