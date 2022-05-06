#include <graphics.h>

#define MENU_W 400
#define MENU_H 400
#define MENU_NUMBER 4
#define JIANJV 100
#define START_X 90

//ģ
int PopMode();
int EatMode();
int SandboxMode();

LPCTSTR menus[MENU_NUMBER] = {L"ģʽ", L"Զģʽ", L"ɳģʽ", L"˳Ϸ"};

bool _inr(int x, int y, int w, int h, int x0, int y0)
{
    if (x0 > x && x0 < x + w && y0 > y && y0 < y + h)
    {
        return 1;
    }
    return 0;
}

int inWhichRectangle(int x, int y)
{
    for (int i = 0; i < MENU_NUMBER; i++)
    {
        if (_inr(START_X, i * JIANJV, textwidth(menus[i]), textheight(menus[i]), x, y))
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    MOUSEMSG mm;

    initgraph(MENU_W, MENU_H);
    settextstyle(50, 0, L"");
    for (int i = 0; i < MENU_NUMBER; i++)
    {
        outtextxy(START_X, i * JIANJV, menus[i]);
    }

    while (true)
    {

        if (PeekMouseMsg(&mm))
        {
            if (mm.mkLButton || mm.mkRButton)
            {
                int wr = inWhichRectangle(mm.x, mm.y);
                if (wr == 0)
                {
                    closegraph();
                    PopMode();
                    initgraph(MENU_W, MENU_H);
                    settextstyle(50, 0, L"");
                    for (int i = 0; i < MENU_NUMBER; i++)
                    {
                        outtextxy(START_X, i * JIANJV, menus[i]);
                    }
                    continue;
                }
                else if (wr == 1)
                {
                    closegraph();
                    EatMode();
                    initgraph(MENU_W, MENU_H);
                    settextstyle(50, 0, L"");
                    for (int i = 0; i < MENU_NUMBER; i++)
                    {
                        outtextxy(START_X, i * JIANJV, menus[i]);
                    }
                    continue;
                }
                else if (wr == 2)
                {
                    closegraph();
                    // Sleep(1000);
                    SandboxMode();
                    initgraph(MENU_W, MENU_H);
                    settextstyle(50, 0, L"");
                    for (int i = 0; i < MENU_NUMBER; i++)
                    {
                        outtextxy(START_X, i * JIANJV, menus[i]);
                    }
                    continue;
                }
                else if (wr == 3)
                {
                    break;
                }
            } // end click
        }     // end mouse
    }         // end while
    closegraph();
    //_itoa_s();
    return 0;
}