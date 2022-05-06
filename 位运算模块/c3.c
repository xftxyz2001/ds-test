#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define NNN 8

int f1_countbin1(int num)
{
    int count = 0;
    while (num)
    {
        if (num & 1)
            count++;
        num >>= 1;
    }
    return count;
}

void f2_jiaohuan(int *a, int *b)
{
    // 01   10
    *a ^= *b; // 11   10
    *b ^= *a; // 11   01
    *a ^= *b; // 10   01
}

int f3_abs(int num)
{
    return (num ^ (num >> 63)) - (num >> 63);
}

int f4_setk1(int num, int k)
{
    return num | (1 << (k - 1));
}

int f5_getk(int num, int k)
{
    return (num >> (k - 1)) & 1;
}

int f6_add(int a, int b)
{
    int t = a;
    while (b)
    {
        t = a ^ b;        //计算出不进位和
        b = (a & b) << 1; //计算出进位放到b中
        a = t;
    }
    return a;
}

int AND(int A, int B)
{
    // return A & B;
    return A * B == 0 ? 0 : 1;
}

int OR(int A, int B)
{
    // return A | B;
    return A + B == 0 ? 0 : 1;
}

/*
int NOT(int A)
{
    return ~A;
}
*/

int XOR(int A, int B)
{
    // return A ^ B;
    return A == B ? 0 : 1;
}

void HALF_ADDER(int A, int B, int *Sum, int *Carry)
{
    *Sum = XOR(A, B);
    *Carry = AND(A, B);
}

void FULL_ADDER(int A, int B, int C, int *Sum, int *Carry)
{
    int Half_Carry, *phc = &Half_Carry;
    HALF_ADDER(A, B, Sum, phc);      //半加AB，sum为和，phc为进位。当AB均为1时phc为1
    HALF_ADDER(*Sum, C, Sum, Carry); //在和上次进位半加，sum为和，Carry为进位。
    *Carry = OR(*Carry, *phc);       //在任意一次相加出现进位，结果就需要进位。
}

void _NBIT_ADDER(int A[NNN], int B[NNN], int Sum[NNN], int *Carry)
{
    //从左往右分别是0123456......
    int i, temp;
    HALF_ADDER(A[NNN - 1], B[NNN - 1], &temp, Carry);
    Sum[NNN - 1] = temp;
    for (i = NNN - 2; i >= 0; i--)
    {
        FULL_ADDER(A[i], B[i], *Carry, &temp, Carry);
        Sum[i] = temp;
    }
}

int main(int argc, char const *argv[])
{
    int i, a = 0, b = 0, c = 0, d = 0, z = 0;
    int A[8] = {0}, B[8] = {0}, S[8] = {0};
    srand((unsigned int)time(NULL));

    a = rand() % 500;
    printf("1.%d的二进制表示中1的个数为%d\n", a, f1_countbin1(a));

    a = rand() % 500;
    b = rand() % 500;
    printf("2.交换两个数:交换前a=%d,b=%d;", a, b);
    f2_jiaohuan(&a, &b);
    printf("交换后a=%d,b=%d;\n", a, b);

    a = (rand() & 2 ? 1 : -1) * rand() % 500;
    printf("3.%d的绝对值为%d\n", a, f3_abs(a));

    a = rand() % 500;
    b = f3_abs(rand() % 5);
    printf("4.将%d的二进制表示中的第%d位置为1：%d\n", a, b, f4_setk1(a, b));

    a = rand() % 500;
    b = f3_abs(rand() % 5);
    printf("5.%d的二进制表示中第%d位的值：%d\n", a, b, f5_getk(a, b));

    a = rand() % 500;
    b = rand() % 500;
    printf("6.计算两个数之和：%d+%d=%d\n", a, b, f6_add(a, b));

    a = rand() % 2;
    b = rand() % 2;
    printf("7.半加器%d+%d=", a, b);
    HALF_ADDER(a, b, &c, &d);
    printf("%d，进位：%d\n", c, d);

    a = rand() % 2;
    b = rand() % 2;
    z = rand() % 2;
    printf("8.全加器(来自上位的进位%d)%d+%d=", z, a, b);
    FULL_ADDER(a, b, z, &c, &d);
    printf("%d，进位：%d\n", c, d);

    //为了使计算结果不溢出取首位为零
    for (i = 1; i < NNN; i++)
    {
        A[i] = rand() % 2;
        B[i] = rand() % 2;
    }
    printf("9.8位波纹进位加法器计算两个八位二进制数相加:\n");
    printf("A:");
    for (i = 0; i < NNN; i++)
        printf("%d", A[i]);
    printf("\t\tB:");
    for (i = 0; i < NNN; i++)
        printf("%d", B[i]);
    _NBIT_ADDER(A, B, S, &c);
    printf("\nA+B=");
    for (i = 0; i < NNN; i++)
        printf("%d", S[i]);
    printf("\n");
    return 0;
}
