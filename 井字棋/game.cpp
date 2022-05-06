#include "game.h"

void cbinit(chessboard *cbp)
{
    for (int i = 0; i < 9; i++)
    {
        cbp->chessboard[i] = 0;
    }
    cbp->isWhoDown = 1;
    // MessageBox()
}

//判断点击的是哪个位置
int inWhichRectangle(int x, int y)
{
    if (y < HM / 3)
    {
        if (x < WM / 3)
            return 0;
        else if (x < WM / 3 * 2)
            return 1;
        else if (x < WM)
            return 2;
    }
    else if (y < HM / 3 * 2)
    {
        if (x < WM / 3)
            return 3;
        else if (x < WM / 3 * 2)
            return 4;
        else if (x < WM)
            return 5;
    }
    else if (y < HM)
    {
        if (x < WM / 3)
            return 6;
        else if (x < WM / 3 * 2)
            return 7;
        else if (x < WM)
            return 8;
    }
    return -1;
}

void drawchessboard(chessboard cb)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (cb.chessboard[i * 3 + j] == 1)
            {
                setfillcolor(BLUE);
                fillrectangle(WM / 3 * j, HM / 3 * i, WM / 3 * (j + 1), HM / 3 * (i + 1));
            }
            else if (cb.chessboard[i * 3 + j] == -1)
            {
                setfillcolor(GREEN);
                fillrectangle(WM / 3 * j, HM / 3 * i, WM / 3 * (j + 1), HM / 3 * (i + 1));
            }
        }
    }
}

int gameover(chessboard cb)
{
    int mayWin = cb.chessboard[4];
    if (cb.chessboard[0] == mayWin && cb.chessboard[8] == mayWin ||
        cb.chessboard[1] == mayWin && cb.chessboard[7] == mayWin ||
        cb.chessboard[2] == mayWin && cb.chessboard[6] == mayWin ||
        cb.chessboard[3] == mayWin && cb.chessboard[5] == mayWin)
        return mayWin;
    else if (cb.chessboard[0] == cb.chessboard[1] && cb.chessboard[2] == cb.chessboard[1])
        return cb.chessboard[1];
    else if (cb.chessboard[0] == cb.chessboard[3] && cb.chessboard[6] == cb.chessboard[3])
        return cb.chessboard[3];
    else if (cb.chessboard[2] == cb.chessboard[5] && cb.chessboard[8] == cb.chessboard[5])
        return cb.chessboard[5];
    else if (cb.chessboard[6] == cb.chessboard[7] && cb.chessboard[8] == cb.chessboard[7])
        return cb.chessboard[7];
    for (int i = 0; i < 9; i++)
        if (cb.chessboard[i] == 0)
            return 0; //存在空的棋盘游戏未结束
    return 2;         //游戏以平局方式结束
}

int main()
{
    MOUSEMSG mm;
    chessboard cb; //创建棋盘
    int win;       //赢家
    initgraph(WM, HM);
    cbinit(&cb); //初始化棋盘
    while (true)
    {
        if (PeekMouseMsg(&mm))
        {
            if (mm.mkLButton && cb.isWhoDown == 1) //左
            {
                int r = inWhichRectangle(mm.x, mm.y);
                if (cb.chessboard[r] == 0)
                {
                    cb.chessboard[r] = cb.isWhoDown;
                    cb.isWhoDown = -cb.isWhoDown;
                }
                drawchessboard(cb);
            }
            if (mm.mkRButton && cb.isWhoDown == -1)
            {
                int r = inWhichRectangle(mm.x, mm.y);
                if (cb.chessboard[r] == 0)
                {
                    cb.chessboard[r] = cb.isWhoDown;
                    cb.isWhoDown = -cb.isWhoDown;
                }
                drawchessboard(cb);
            }
        }

        if (win = gameover(cb))
        {
            if (win == 1)
                outtextxy(WM / 3, HM / 3, L"蓝色Win！");
            else if (win == -1)
                outtextxy(WM / 3, HM / 3, L"绿色Win！");
            else
                outtextxy(WM / 3, HM / 3, L"平局！");
            while (true)
            {
                if (PeekMouseMsg(&mm))
                {
                    if (mm.mkLButton || mm.mkRButton)
                    {
                        cbinit(&cb);
                        clearrectangle(0, 0, WM, HM);
                        break;
                    }
                }
            }
        }
    }
    closegraph();
    return 0;
}
