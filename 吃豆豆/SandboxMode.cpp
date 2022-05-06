#include "SandboxMode.h"

int my_color[C_SIZE] = {0xAA0000, 0x00AA00, 0xAAAA00, 0x0000AA, 0xAA00AA, 0x0055AA, 0xAAAAAA, 0x555555, 0xFF5555, 0x55FF55, 0xFFFF55, 0x5555FF, 0xFF55FF, 0x55FFFF, 0xFFFFFF};

void getNextPositions(CIRCLES cs)
{
    while (cs = cs->next)
    {
        if (cs->x + cs->vx >= WM - cs->r || cs->x + cs->vx <= 0 + cs->r)
        {
            cs->vx = -cs->vx;
            cs->color = (my_color[rand() % C_SIZE]);
        }
        cs->x = cs->x + cs->vx;

        if (cs->y + cs->vy >= HM - cs->r || cs->y + cs->vy <= 0 + cs->r)
        {
            cs->vy = -cs->vy;
            cs->color = (my_color[rand() % C_SIZE]);
        }
        cs->y = cs->y + cs->vy;
    }
}

void clearLastCircles(CIRCLES cs)
{
    while (cs = cs->next)
    {
        clearcircle(cs->x, cs->y, cs->r + 1);
    }
}

CIRCLES createCircle()
{
    return (CIRCLES)malloc(sizeof(struct c_s));
}

void insertCircle(CIRCLES cs, int x, int y, int r)
{
    CIRCLES temp = createCircle();
    temp->x = x;
    temp->y = y;
    temp->r = r;
    temp->vx = rand() % (V_MAX - V_MIN) + V_MIN;
    temp->vy = rand() % (V_MAX - V_MIN) + V_MIN;
    temp->color = (my_color[rand() % C_SIZE]);
    temp->next = cs->next;
    cs->next = temp; //头插入法
}

int deleteCircle(CIRCLES cs, int x, int y)
{
    CIRCLES cs_p = cs;
    while (cs = cs->next)
    {
        if ((cs->x - x) * (cs->x - x) + (cs->y - y) * (cs->y - y) <= cs->r * cs->r)
        {
            clearcircle(cs->x, cs->y, cs->r + 1);
            cs_p->next = cs->next;
            return 1;
        }
        cs_p = cs_p->next;
    }
    return 0;
}

void deleteAll(CIRCLES cs)
{
    CIRCLES temp = cs;
    while (cs = cs->next)
        clearcircle(cs->x, cs->y, cs->r + 1);
    temp->next = NULL;
}

void drawCircles(CIRCLES cs)
{
    while (cs = cs->next)
    {
        setfillcolor(cs->color);
        fillcircle(cs->x, cs->y, cs->r);
    }
}

int SandboxMode()
{
    MOUSEMSG mm;

    CIRCLES cs = createCircle();
    cs->next = NULL;

    srand((unsigned int)time(NULL));
    initgraph(WM, HM);

    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
        if (PeekMouseMsg(&mm))
        {
            if (mm.mkLButton) //创建新的图形
            {
                insertCircle(cs, mm.x, mm.y, rand() % (R_MAX - R_MIN) + R_MIN);
            }
            else if (mm.mkRButton) //删除
            {
                deleteCircle(cs, mm.x, mm.y);
            }
            else if (mm.mkMButton) //清空
            {
                deleteAll(cs);
            }
        }
        clearLastCircles(cs);
        getNextPositions(cs);
        drawCircles(cs);
        Sleep(SLEEP_TIME);
    }
    closegraph();
    return 0;
}
