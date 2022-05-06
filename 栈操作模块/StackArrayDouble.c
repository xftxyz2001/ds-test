#include "stack.h"
#include "StackArrayDouble.h"

void Init_StackArrayDouble(StackArrayDouble *s)
{
    s->top = -1;
}

void Clear_StackArrayDouble(StackArrayDouble *s)
{
    free(s);
}

int IsEmpty_StackArrayDouble(StackArrayDouble *s)
{
    return s->top == -1 ? 1 : 0;
}

int IsFull_StackArrayDouble(StackArrayDouble *s)
{
    return s->top == Stack_Size - 1 ? 1 : 0;
}

int Push_StackArrayDouble(StackArrayDouble *s, double x)
{
    if (IsFull_StackArrayDouble(s))
        return 0;
    s->top++;
    s->elem[s->top] = x;
    return 1;
}

int Pop_StackArrayDouble(StackArrayDouble *s, double *x)
{
    if (IsEmpty_StackArrayDouble(s))
        return 0;
    *x = s->elem[s->top];
    s->top--;
    return 1;
}

int GetTop_StackArrayDouble(StackArrayDouble *s, double *x)
{
    if (IsEmpty_StackArrayDouble(s))
        return 0;
    *x = s->elem[s->top];
    return 1;
}

void Init_DoubleStackArrayDouble(DoubleStackArrayDouble *s)
{
    s->top[0] = -1;
    s->top[1] = Double_Stack_Size;
}

void Clear_DoubleStackArrayDouble(DoubleStackArrayDouble *s)
{
    free(s);
}

int IsEmpty_DoubleStackArrayDouble(DoubleStackArrayDouble *s, int sl)
{
    return sl == 0 ? (s->top[0] == -1 ? 1 : 0) : (s->top[1] == Double_Stack_Size ? 1 : 0);
}

int IsFull_DoubleStackArrayDouble(DoubleStackArrayDouble *s)
{
    return s->top[0] + 1 == s->top[1] ? 1 : 0;
}

int Push_DoubleStackArrayDouble(DoubleStackArrayDouble *s, int sl, double x)
{
    if (IsFull_DoubleStackArrayDouble(s))
        return 0;
    sl == 0 ? s->top[0]++ : s->top[1]--;
    s->elem[s->top[sl]] = x;
    return 1;
}

int Pop_DoubleStackArrayDouble(DoubleStackArrayDouble *s, int sl, double *x)
{
    if (IsEmpty_DoubleStackArrayDouble(s, sl))
        return 0;
    *x = s->elem[s->top[sl]];
    sl == 0 ? s->top[0]-- : s->top[1]++;
    return 1;
}

int GetTop_DoubleStackArrayDouble(DoubleStackArrayDouble *s, int sl, double *x)
{
    if (IsEmpty_DoubleStackArrayDouble(s, sl))
        return 0;
    *x = s->elem[s->top[sl]];
    return 1;
}
