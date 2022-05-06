#pragma once

typedef struct
{
    char elem[Stack_Size];
    int top;
} StackArrayChar;

typedef struct
{
    char elem[Double_Stack_Size];
    int top[2];
} DoubleStackArrayChar;

void Init_StackArrayChar(StackArrayChar *s);

void Clear_StackArrayChar(StackArrayChar *s);

int IsEmpty_StackArrayChar(StackArrayChar *s);

int IsFull_StackArrayChar(StackArrayChar *s);

int Push_StackArrayChar(StackArrayChar *s, char x);

int Pop_StackArrayChar(StackArrayChar *s, char *x);

int GetTop_StackArrayChar(StackArrayChar *s, char *x);

void Init_DoubleStackArrayChar(DoubleStackArrayChar *s);

void Clear_DoubleStackArrayChar(DoubleStackArrayChar *s);

int IsEmpty_DoubleStackArrayChar(DoubleStackArrayChar *s, int sl);

int IsFull_DoubleStackArrayChar(DoubleStackArrayChar *s);

int Push_DoubleStackArrayChar(DoubleStackArrayChar *s, int sl, char x);

int Pop_DoubleStackArrayChar(DoubleStackArrayChar *s, int sl, char *x);

int GetTop_DoubleStackArrayChar(DoubleStackArrayChar *s, int sl, char *x);
