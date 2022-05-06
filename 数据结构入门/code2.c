// 6-2 多项式求值 20分
// 本题要求实现一个函数，计算阶数为n，系数为a[0] ... a[n]的多项式f(x)=∑[i=0]^n
//  (a[i]×x[i]) 在x点的值。

// 函数接口定义：
// double f( int n, double a[], double x );
// 其中n是多项式的阶数，a[]中存储系数，x是给定点。函数须返回多项式f(x)的值。

// 输入样例：
// 2 1.1
// 1 2.5 -38.7
// 结尾无空行

// 输出样例：
// -43.1
// 结尾无空行

#include <stdio.h>
#include <math.h>

#define MAXN 10

double f(int n, double a[], double x);

int main()
{
    int n, i;
    double a[MAXN], x;

    scanf("%d %lf", &n, &x);
    for (i = 0; i <= n; i++)
        scanf("%.1f", &a[i]);
    printf("%.1f\n", f(n, a, x));
    return 0;
}

double f(int n, double a[], double x)
{
    double ans = a[0];
    for (int i = 1; i <= n; i++)
    {
        ans += a[i] * pow(x, i);
    }

    return ans;
}