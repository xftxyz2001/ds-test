#include "stack.h"
#include "StruckLinkNodeInt.h"

void Init_StruckLinkNodeInt(StruckLinkNodeInt *s)
{
    s->next = NULL;
}

void Clear_StruckLinkNodeInt(StruckLinkNodeInt *s)
{
    free(s);
}

int IsEmpty_StruckLinkNodeInt(StruckLinkNodeInt *s)
{
    return s->next == NULL ? 1 : 0;
}

int Push_StruckLinkNodeInt(StruckLinkNodeInt *s, int x)
{
    StruckLinkNodeInt *temp = (StruckLinkNodeInt *)malloc(sizeof(StruckLinkNodeInt));
    temp->data = x;
    temp->next = s->next;
    s->next = temp;
    return 1;
}

int Pop_StruckLinkNodeInt(StruckLinkNodeInt *s, int *x)
{
    if (IsEmpty_StruckLinkNodeInt(s))
        return 0;
    StruckLinkNodeInt *temp = s->next;
    *x = temp->data;
    s->next = temp->next;
    free(temp);
    return 1;
}

int GetTop_StruckLinkNodeInt(StruckLinkNodeInt *s, int *x)
{
    if (IsEmpty_StruckLinkNodeInt(s))
        return 0;
    *x = s->next->data;
    return 1;
}

void Init_StruckLinksInt(StruckLinksInt *s)
{
    for (int i = 0; i < Stack_Links_Size; i++)
    {
        s->links[i] = (StruckLinkNodeInt *)malloc(sizeof(StruckLinkNodeInt));
        s->links[i]->next = NULL;
    }
}

void Clear_StruckLinksInt(StruckLinksInt *s)
{
    free(s);
}

int IsEmpty_StruckLinksInt(StruckLinksInt *s, int sl)
{
    return s->links[sl]->next == NULL ? 1 : 0;
}

int Push_StruckLinksInt(StruckLinksInt *s, int sl, int x)
{
    StruckLinkNodeInt *temp = (StruckLinkNodeInt *)malloc(sizeof(StruckLinkNodeInt));
    temp->data = x;
    temp->next = s->links[sl]->next;
    s->links[sl]->next = temp;
    return 1;
}

int Pop_StruckLinksInt(StruckLinksInt *s, int sl, int *x)
{
    if (IsEmpty_StruckLinksInt(s, sl))
        return 0;
    StruckLinkNodeInt *temp = s->links[sl]->next;
    *x = temp->data;
    s->links[sl]->next = temp->next;
    free(temp);
    return 1;
}

int GetTop_StruckLinksInt(StruckLinksInt *s, int sl, int *x)
{
    if (IsEmpty_StruckLinksInt(s, sl))
        return 0;
    *x = s->links[sl]->next->data;
    return 1;
}
