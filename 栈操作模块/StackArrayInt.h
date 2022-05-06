#pragma once

typedef struct
{
    int elem[Stack_Size];
    int top;
} StackArrayInt;

typedef struct
{
    int elem[Double_Stack_Size];
    int top[2];
} DoubleStackArrayInt;

void Init_StackArrayInt(StackArrayInt *s);

void Clear_StackArrayInt(StackArrayInt *s);

int IsEmpty_StackArrayInt(StackArrayInt *s);

int IsFull_StackArrayInt(StackArrayInt *s);

int Push_StackArrayInt(StackArrayInt *s, int x);

int Pop_StackArrayInt(StackArrayInt *s, int *x);

int GetTop_StackArrayInt(StackArrayInt *s, int *x);

void Init_DoubleStackArrayInt(DoubleStackArrayInt *s);

void Clear_DoubleStackArrayInt(DoubleStackArrayInt *s);

int IsEmpty_DoubleStackArrayInt(DoubleStackArrayInt *s, int sl);

int IsFull_DoubleStackArrayInt(DoubleStackArrayInt *s);

int Push_DoubleStackArrayInt(DoubleStackArrayInt *s, int sl, int x);

int Pop_DoubleStackArrayInt(DoubleStackArrayInt *s, int sl, int *x);

int GetTop_DoubleStackArrayInt(DoubleStackArrayInt *s, int sl, int *x);
