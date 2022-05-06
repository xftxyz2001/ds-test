#pragma once

typedef struct
{
    double elem[Stack_Size];
    int top;
} StackArrayDouble;

typedef struct
{
    double elem[Double_Stack_Size];
    int top[2];
} DoubleStackArrayDouble;

void Init_StackArrayDouble(StackArrayDouble *s);

void Clear_StackArrayDouble(StackArrayDouble *s);

int IsEmpty_StackArrayDouble(StackArrayDouble *s);

int IsFull_StackArrayDouble(StackArrayDouble *s);

int Push_StackArrayDouble(StackArrayDouble *s, double x);

int Pop_StackArrayDouble(StackArrayDouble *s, double *x);

int GetTop_StackArrayDouble(StackArrayDouble *s, double *x);

void Init_DoubleStackArrayDouble(DoubleStackArrayDouble *s);

void Clear_DoubleStackArrayDouble(DoubleStackArrayDouble *s);

int IsEmpty_DoubleStackArrayDouble(DoubleStackArrayDouble *s, int sl);

int IsFull_DoubleStackArrayDouble(DoubleStackArrayDouble *s);

int Push_DoubleStackArrayDouble(DoubleStackArrayDouble *s, int sl, double x);

int Pop_DoubleStackArrayDouble(DoubleStackArrayDouble *s, int sl, double *x);

int GetTop_DoubleStackArrayDouble(DoubleStackArrayDouble *s, int sl, double *x);
