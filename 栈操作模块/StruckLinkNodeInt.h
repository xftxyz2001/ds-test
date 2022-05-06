#pragma once

typedef struct nd
{
    int data;
    struct nd *next;
} StruckLinkNodeInt;

typedef struct n
{
    struct nd *links[Stack_Links_Size];
} StruckLinksInt;

void Init_StruckLinkNodeInt(StruckLinkNodeInt *s);

void Clear_StruckLinkNodeInt(StruckLinkNodeInt *s);

int IsEmpty_StruckLinkNodeInt(StruckLinkNodeInt *s);

int Push_StruckLinkNodeInt(StruckLinkNodeInt *s, int x);

int Pop_StruckLinkNodeInt(StruckLinkNodeInt *s, int *x);

int GetTop_StruckLinkNodeInt(StruckLinkNodeInt *s, int *x);

void Init_StruckLinksInt(StruckLinksInt *s);

void Clear_StruckLinksInt(StruckLinksInt *s);

int IsEmpty_StruckLinksInt(StruckLinksInt *s, int sl);

int Push_StruckLinksInt(StruckLinksInt *s, int sl, int x);

int Pop_StruckLinksInt(StruckLinksInt *s, int sl, int *x);

int GetTop_StruckLinksInt(StruckLinksInt *s, int sl, int *x);
