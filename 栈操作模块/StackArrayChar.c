#include "stack.h"
#include "StackArrayChar.h"

void Init_StackArrayChar(StackArrayChar *s)
{
    s->top = -1;
}

void Clear_StackArrayChar(StackArrayChar *s)
{
    free(s);
}

int IsEmpty_StackArrayChar(StackArrayChar *s)
{
    return s->top == -1 ? 1 : 0;
}

int IsFull_StackArrayChar(StackArrayChar *s)
{
    return s->top == Stack_Size - 1 ? 1 : 0;
}

int Push_StackArrayChar(StackArrayChar *s, char x)
{
    if (IsFull_StackArrayChar(s))
        return 0;
    s->top++;
    s->elem[s->top] = x;
    return 1;
}

int Pop_StackArrayChar(StackArrayChar *s, char *x)
{
    if (IsEmpty_StackArrayChar(s))
        return 0;
    *x = s->elem[s->top];
    s->top--;
    return 1;
}

int GetTop_StackArrayChar(StackArrayChar *s, char *x)
{
    if (IsEmpty_StackArrayChar(s))
        return 0;
    *x = s->elem[s->top];
    return 1;
}

void Init_DoubleStackArrayChar(DoubleStackArrayChar *s)
{
    s->top[0] = -1;
    s->top[1] = Double_Stack_Size;
}

void Clear_DoubleStackArrayChar(DoubleStackArrayChar *s)
{
    free(s);
}

int IsEmpty_DoubleStackArrayChar(DoubleStackArrayChar *s, int sl)
{
    return sl == 0 ? (s->top[0] == -1 ? 1 : 0) : (s->top[1] == Double_Stack_Size ? 1 : 0);
}

int IsFull_DoubleStackArrayChar(DoubleStackArrayChar *s)
{
    return s->top[0] + 1 == s->top[1] ? 1 : 0;
}

int Push_DoubleStackArrayChar(DoubleStackArrayChar *s, int sl, char x)
{
    if (IsFull_DoubleStackArrayChar(s))
        return 0;
    sl == 0 ? s->top[0]++ : s->top[1]--;
    s->elem[s->top[sl]] = x;
    return 1;
}

int Pop_DoubleStackArrayChar(DoubleStackArrayChar *s, int sl, char *x)
{
    if (IsEmpty_DoubleStackArrayChar(s, sl))
        return 0;
    *x = s->elem[s->top[sl]];
    sl == 0 ? s->top[0]-- : s->top[1]++;
    return 1;
}

int GetTop_DoubleStackArrayChar(DoubleStackArrayChar *s, int sl, char *x)
{
    if (IsEmpty_DoubleStackArrayChar(s, sl))
        return 0;
    *x = s->elem[s->top[sl]];
    return 1;
}
