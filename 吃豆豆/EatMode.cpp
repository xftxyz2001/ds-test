#include "SandboxMode.h"

typedef struct r_s
{
    int x;
    int y;
    int r;
    COLORREF color;
    struct c_s *next;
} * Rectangles;

int EatMode()
{
    // MOUSEMSG mm;
    int myx = WM / 2, myy = HM / 2, myv = 5;
    int w = 5, h = 5;
    int number = 0;         //画面中图形个数
    int count = 0, p = 100; //计数器，每p次循环增加一个图形
    int max_number = 10;    //当画面中图形个数大于这个数游戏结束
    int score = 0;
    // char score_char[10];

    CIRCLES cs = createCircle();
    cs->next = NULL;

    srand((unsigned int)time(NULL));
    initgraph(WM, HM);
    // fillrectangle(myx, myy, myx + w, myy + h);
    while (true)
    {
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
        if (GetAsyncKeyState('W'))
        {
            clearrectangle(myx - 1, myy - 1, myx + w + 1, myy + h + 1);
            myy -= myv;
            fillrectangle(myx, myy, myx + w, myy + h);
            if (deleteCircle(cs, myx, myy))
            {
                number--;
                score++;
            }
        }
        if (GetAsyncKeyState('S'))
        {
            clearrectangle(myx - 1, myy - 1, myx + w + 1, myy + h + 1);
            myy += myv;
            fillrectangle(myx, myy, myx + w, myy + h);
            if (deleteCircle(cs, myx, myy))
            {
                number--;
                score++;
            }
        }
        if (GetAsyncKeyState('A'))
        {
            clearrectangle(myx - 1, myy - 1, myx + w + 1, myy + h + 1);
            myx -= myv;
            fillrectangle(myx, myy, myx + w, myy + h);
            if (deleteCircle(cs, myx, myy))
            {
                number--;
                score++;
            }
        }
        if (GetAsyncKeyState('D'))
        {
            clearrectangle(myx - 1, myy - 1, myx + w + 1, myy + h + 1);
            myx += myv;
            fillrectangle(myx, myy, myx + w, myy + h);
            if (deleteCircle(cs, myx, myy))
            {
                // insertRectangle();
                number--;
                score++;
            }
        }
        if (count > p)
        {
            insertCircle(cs, rand() % WM, rand() % HM, rand() % (R_MAX - R_MIN) + R_MIN * 2);
            if (number++ > max_number)
            {
                settextstyle(50, 0, L"黑体");
                if (score > 50)
                {
                    outtextxy(10, 20, L"你真棒！！！");
                }
                outtextxy(WM / 3, HM / 3, L"游戏结束  最终得分：");
                char score_char[10];
                _itoa_s(score, score_char, 10, 10);
                int num = MultiByteToWideChar(0, 0, score_char, -1, NULL, 0);
                wchar_t *wide = new wchar_t[num];
                MultiByteToWideChar(0, 0, score_char, -1, wide, num);
                outtextxy(WM / 2, HM / 3 + 50, wide);
                while (true)
                {
                    if (GetAsyncKeyState(VK_ESCAPE))
                    {
                        closegraph();
                        return 0;
                    }
                }
            }
            // number++;
            count = 0;
        }
        clearLastCircles(cs);
        // getNextPositions(cs);
        drawCircles(cs);
        // clearLastRectangle(cs);
        // getNextPositions(cs);
        // drawRectangle(cs);
        Sleep(SLEEP_TIME / 2);
        count++;
    }
    closegraph();
    return 0;
}