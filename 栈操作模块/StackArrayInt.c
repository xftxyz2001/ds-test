#include "stack.h"
#include "StackArrayInt.h"

void Init_StackArrayInt(StackArrayInt *s)
{
    s->top = -1;
}

void Clear_StackArrayInt(StackArrayInt *s)
{
    free(s);
}

int IsEmpty_StackArrayInt(StackArrayInt *s)
{
    return s->top == -1 ? 1 : 0;
}

int IsFull_StackArrayInt(StackArrayInt *s)
{
    return s->top == Stack_Size - 1 ? 1 : 0;
}

int Push_StackArrayInt(StackArrayInt *s, int x)
{
    if (IsFull_StackArrayInt(s))
        return 0;
    s->top++;
    s->elem[s->top] = x;
    return 1;
}

int Pop_StackArrayInt(StackArrayInt *s, int *x)
{
    if (IsEmpty_StackArrayInt(s))
        return 0;
    *x = s->elem[s->top];
    s->top--;
    return 1;
}

int GetTop_StackArrayInt(StackArrayInt *s, int *x)
{
    if (IsEmpty_StackArrayInt(s))
        return 0;
    *x = s->elem[s->top];
    return 1;
}

void Init_DoubleStackArrayInt(DoubleStackArrayInt *s)
{
    s->top[0] = -1;
    s->top[1] = Double_Stack_Size;
}

void Clear_DoubleStackArrayInt(DoubleStackArrayInt *s)
{
    free(s);
}

int IsEmpty_DoubleStackArrayInt(DoubleStackArrayInt *s, int sl)
{
    return sl == 0 ? (s->top[0] == -1 ? 1 : 0) : (s->top[1] == Double_Stack_Size ? 1 : 0);
}

int IsFull_DoubleStackArrayInt(DoubleStackArrayInt *s)
{
    return s->top[0] + 1 == s->top[1] ? 1 : 0;
}

int Push_DoubleStackArrayInt(DoubleStackArrayInt *s, int sl, int x)
{
    if (IsFull_DoubleStackArrayInt(s))
        return 0;
    sl == 0 ? s->top[0]++ : s->top[1]--;
    s->elem[s->top[sl]] = x;
    return 1;
}

int Pop_DoubleStackArrayInt(DoubleStackArrayInt *s, int sl, int *x)
{
    if (IsEmpty_DoubleStackArrayInt(s, sl))
        return 0;
    *x = s->elem[s->top[sl]];
    sl == 0 ? s->top[0]-- : s->top[1]++;
    return 1;
}

int GetTop_DoubleStackArrayInt(DoubleStackArrayInt *s, int sl, int *x)
{
    if (IsEmpty_DoubleStackArrayInt(s, sl))
        return 0;
    *x = s->elem[s->top[sl]];
    return 1;
}
