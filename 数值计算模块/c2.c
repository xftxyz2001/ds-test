#include <stdio.h>
#include <math.h>
#define EPS 0.01
#define MAX_COUNT 500

double f1(double x)
{
    return (-x * x * x - 2 * x * x - 1) / 2;
}

double f2(double x)
{
    return x * x * x - 2 * x * x + 4 * x + 1;
}

double ff2(double x)
{
    return 3 * x * x - 4 * x + 4;
}

double f3(double x)
{
    return x * x * x - 6 * x - 1;
}

double f4(double x)
{
    return x * x * x - 2 * x * x + 7 * x - 4;
}

double f5(double x)
{
    return x * x - 4 * x + 4;
}

double dhtr(double a, double b, double eps, int m, double (*f)(double))
{
    double fa, x, fx;
    fa = (*f)(a);
    x = (a + b) / 2;
    while (fabs(a - b) > eps && m--)
    {
        x = (a + b) / 2;
        fx = (*f)(x);
        fx *fa < 0 ? (b = x) : (a = x);
    }
    return x;
}

double dhtr2(double x0, double eps, int m, double (*f)(double))
{
    double x1;
    x1 = (*f)(x0);
    while (fabs(x1 - x0) > eps && m-- > 0)
    {
        x0 = x1;
        x1 = (*f)(x0);
    }
    return x1;
}

double newt(double x0, double eps, int m, double (*f)(double), double (*ff)(double))
{
    double x1;
    x1 = x0 - (*f)(x0) / (*ff)(x0);
    while (fabs(x1 - x0) > eps || fabs((*f)(x0)) > eps && m--)
    {
        x0 = x1;
        x1 = x0 - (*f)(x0) / (*ff)(x0);
    }
    return x1;
}

double newt2(double x0, double x1, double eps, int m, double (*f)(double))
{
    double x2, f0, f1, f2;
    f0 = (*f)(x0);
    f1 = (*f)(x1);
    x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
    while ((fabs(x2 - x1) > eps || fabs(f1) > eps) && m--)
    {
        f2 = (*f)(x2);
        x0 = x1;
        x1 = x2;
        f0 = f1;
        f1 = f2;
        x2 = x1 - f1 * (x1 - x0) / (f1 - f0);
    }
    return x2;
}

double gss(double a, double b, double eps, int m, double (*f)(double))
{
    double fc, fd, c, d;
    c = a + 0.382 * (b - a);
    d = a + 0.618 * (b - a);
    fc = (*f)(c);
    fd = (*f)(d);
    while (d - c >= eps && m--)
    {
        if (fc > fd)
        {
            a = c;
            c = d;
            d = a + 0.618 * (b - a);
        }
        else
        {
            b = d;
            d = c;
            c = a + 0.382 * (b - a);
        }
        fc = (*f)(c);
        fd = (*f)(d);
    }
    return fc < fd ? c : d;
}

int main()
{
    printf("用不动点迭代法求解x3+2x2+2x+1=0的结果x=%.10f\n", dhtr2(1, EPS, MAX_COUNT, f1));
    printf("用牛顿迭代法求x3-2x2+4x+1=0在x=0附近的一个实根x=%.10f\n", newt(0, EPS, MAX_COUNT, f2, ff2));
    printf("用二分法求x3-6x-1=0在x=2附近的一个实根x=%.10f\n", dhtr(1, 3, EPS, MAX_COUNT, f3));
    printf("用弦截法求x3-2x2+7x-4=0的一个实根x=%.10f\n", newt2(0, 1, 1e-6, MAX_COUNT, f4));
    printf("用黄金值搜索法求f(x)=x2-4x+4在[0,4]之间的最小值min=%.10f\n", gss(0, 4, EPS, MAX_COUNT, f5));
    return 0;
}
