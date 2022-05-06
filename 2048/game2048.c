#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <math.h>

#define GRAPH_WIDTH 900  //屏幕宽度
#define GRAPH_HEIGHT 600 //屏幕高度
#define GAME_SIZE 4      //游戏窗格能容纳的卡片数

typedef struct _cb
{
    int cb[4][4];  //棋盘存储2的n次方
    int remainder; //剩余的空格子
} * CB;

int my_color[12] = {BLACK, BLUE, GREEN, CYAN, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
                    LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, RED};

LOGFONT font; //字体
int score = 0;
int hscore = 0;

void outtextxycenter(int x, int y, LPCTSTR str)
{
    outtextxy(x - textwidth(str) / 2, y - textheight(str) / 2, str);
}

void set_score(int x)
{
    score += x;
    font.lfHeight = 50;
    settextstyle(&font);
    clearrectangle(GRAPH_HEIGHT + 5, GRAPH_HEIGHT / 3 - textheight(L"0") / 2, GRAPH_WIDTH, GRAPH_HEIGHT / 3 + 30);
    TCHAR Temp[10] = TEXT("");
    _stprintf_s(Temp, TEXT("%d"), score);
    outtextxycenter(GRAPH_HEIGHT + (GRAPH_WIDTH - GRAPH_HEIGHT) / 2, GRAPH_HEIGHT / 3, Temp);
}

void set_hscore()
{
    font.lfHeight = 30;
    settextstyle(&font);
    clearrectangle(GRAPH_HEIGHT + 5, GRAPH_HEIGHT / 3 + 80 - textheight(L"0") / 2, GRAPH_WIDTH, GRAPH_HEIGHT / 3 + 80 + 20);
    TCHAR Temp[10] = TEXT("");
    _stprintf_s(Temp, TEXT("%d"), hscore);
    outtextxycenter(GRAPH_HEIGHT + (GRAPH_WIDTH - GRAPH_HEIGHT) / 2, GRAPH_HEIGHT / 3 + 80, Temp);
}

void info_init()
{
    gettextstyle(&font);
    font.lfHeight = 100;
    settextstyle(&font);
    outtextxycenter(GRAPH_HEIGHT + (GRAPH_WIDTH - GRAPH_HEIGHT) / 2, GRAPH_HEIGHT / 8, L"2048");

    font.lfHeight = 50;
    settextstyle(&font);
    outtextxycenter(GRAPH_HEIGHT + (GRAPH_WIDTH - GRAPH_HEIGHT) / 2, GRAPH_HEIGHT / 4, L"分数");
    set_score(0);

    font.lfHeight = 30;
    settextstyle(&font);
    outtextxycenter(GRAPH_HEIGHT + (GRAPH_WIDTH - GRAPH_HEIGHT) / 2, GRAPH_HEIGHT / 3 + 50, L"历史最高分");
    set_hscore();

    font.lfHeight = 30;
    settextstyle(&font);
    outtextxycenter(GRAPH_HEIGHT + (GRAPH_WIDTH - GRAPH_HEIGHT) / 2, GRAPH_HEIGHT / 2 + 30, L"游戏规则:");

    font.lfHeight = 8;
    settextstyle(&font);
    LPCTSTR strs[10] = {L"2048游戏共有16个格子，初始时数字是2。",
                        L"1,按下W，所有格子会向上运动。",
                        L"2,按下A，所有格子会向左运动。",
                        L"3,按下S，所有格子会向下运动。",
                        L"4,按下D，所有格子会向右运动。",
                        L"5,相同数字的两个格子碰撞时数字会相加。",
                        L"6,每次运动后空白处会随机生成一个格子。",
                        L"7,当界面不可运动时，游戏结束；",
                        L"8,当界面中最大数字是2048时，游戏胜利。",
                        L"游戏结束或胜利时,按任意键开始下一轮。"};
    for (int i = 0; i < 10; i++)
    {
        outtextxy(GRAPH_HEIGHT + 5, GRAPH_HEIGHT / 2 + 20 * (i + 3), strs[i]);
    }
    outtextxy(GRAPH_HEIGHT, GRAPH_HEIGHT - 20, L"            软件工程二班 庞晓宇 2020118100");
}

void cb_rand(CB cb)
{
    //当棋盘无空格子,该函数仍被调用,整明该方向无法移动,但存在其他方向可移动,此时不在生成新的元素.
    if (cb->remainder <= 0)
    {
        return;
    }
    int n = rand() % cb->remainder;
    for (int i = 0; i < GAME_SIZE; i++)
    {
        for (int j = 0; j < GAME_SIZE; j++)
        {
            if (cb->cb[i][j] == 0 && --n <= 0)
            {
                cb->cb[i][j] = (rand() % 10 == 0) ? 2 : 1;
                // cb->cb[i][j] = rand() % 2 + 1;
                cb->remainder--;
                return;
            }
        }
    }
}

//初始化,包含两个元素
void cb_init(CB cb)
{
    //全部初始化为空
    for (int i = 0; i < GAME_SIZE; i++)
    {
        for (int j = 0; j < GAME_SIZE; j++)
        {
            cb->cb[i][j] = 0;
        }
    }
    cb->remainder = 16;
    score = 0;
    //随机搞上两个元素
    cb_rand(cb);
    cb_rand(cb);
}

//获取指数对应的字符
LPCTSTR get_char_by_index(int x)
{
    switch (x)
    {
    default:
        return 0;
    case 1:
        return L"2";
    case 2:
        return L"4";
    case 3:
        return L"8";
    case 4:
        return L"16";
    case 5:
        return L"32";
    case 6:
        return L"64";
    case 7:
        return L"128";
    case 8:
        return L"256";
    case 9:
        return L"512";
    case 10:
        return L"1024";
    case 11:
        return L"2048";
    }
}

//重新绘制棋盘
void cb_draw(CB cb)
{
    clearrectangle(0, 0, GRAPH_HEIGHT, GRAPH_HEIGHT);
    gettextstyle(&font);
    font.lfHeight = 100;
    settextstyle(&font);
    for (int i = 0; i < GAME_SIZE; i++)
    {
        for (int j = 0; j < GAME_SIZE; j++)
        {
            if (cb->cb[i][j])
            {
                setfillcolor(my_color[cb->cb[i][j]]);
                fillrectangle(j * GRAPH_HEIGHT / GAME_SIZE, i * GRAPH_HEIGHT / GAME_SIZE,
                              (j + 1) * GRAPH_HEIGHT / GAME_SIZE, (i + 1) * GRAPH_HEIGHT / GAME_SIZE);
                outtextxycenter(j * GRAPH_HEIGHT / GAME_SIZE + GRAPH_HEIGHT / GAME_SIZE / 2,
                                i * GRAPH_HEIGHT / GAME_SIZE + GRAPH_HEIGHT / GAME_SIZE / 2,
                                get_char_by_index(cb->cb[i][j]));
            }
        }
    }
}

int moveLeft(CB cb)
{
    int i, j, score = 0, flag = -1;
    for (i = 0; i < GAME_SIZE; i++)
    {
        for (j = 0; j < GAME_SIZE; j++)
        {
            int cell = cb->cb[i][j]; // cell单词用的不太恰当，表示当前元素，你可以采用更有意义的命名
            if (cell != 0)
            {
                int k = j + 1;
                while (k < GAME_SIZE)
                {
                    int nextcell = cb->cb[i][k];
                    if (nextcell != 0)
                    {
                        if (cell == nextcell)
                        {
                            flag = 0; //相邻两个元素相同，就说明能移动，所以改变flag的值
                            cb->cb[i][j]++;
                            score += (int)pow(2, cb->cb[i][j]);
                            cb->cb[i][k] = 0;
                            //当元素被合并时,空格子加一
                            cb->remainder++;
                        }
                        k = GAME_SIZE;
                        break;
                    }
                    k++;
                }
            }
        }
    }

    //修改部分：for循环中的i或者j的循环条件

    for (i = 0; i < GAME_SIZE; i++)
    {
        for (j = 0; j < GAME_SIZE - 1; j++)
        {
            int cell = cb->cb[i][j];
            if (cell == 0)
            {
                int k = j + 1;
                while (k < GAME_SIZE)
                {
                    int nextcell = cb->cb[i][k];
                    if (nextcell != 0)
                    {
                        flag = 0; //
                        cb->cb[i][j] = nextcell;
                        cb->cb[i][k] = 0;
                        k = GAME_SIZE;
                    }
                    k++;
                }
            }
        }
    }
    if (flag != -1)
        return score;
    else
        return -1;
}

int moveRight(CB cb)
{
    int i, j, score = 0, flag = -1;
    for (i = 0; i < GAME_SIZE; i++)
    {
        for (j = GAME_SIZE - 1; j >= 0; j--)
        {
            int cell = cb->cb[i][j];
            if (cell != 0)
            {
                int k = j - 1;
                while (k >= 0)
                {
                    int nextcell = cb->cb[i][k];
                    if (nextcell != 0)
                    {
                        if (cell == nextcell)
                        {
                            flag = 0;
                            cb->cb[i][j]++;
                            score += (int)pow(2, cb->cb[i][j]);
                            cb->cb[i][k] = 0;
                            cb->remainder++;
                        }
                        k = -1;
                        break;
                    }
                    k--;
                }
            }
        }
    }

    //修改部分：for循环中的i或者j的循环条件

    for (i = 0; i < GAME_SIZE; i++)
    {
        for (j = GAME_SIZE - 1; j > 0; j--)
        {
            int cell = cb->cb[i][j];
            if (cell == 0)
            {

                int k = j - 1;
                while (k >= 0)
                {
                    int nextcell = cb->cb[i][k];
                    if (nextcell != 0)
                    {
                        flag = 0; //当前元素为0，说明能移动，改变flag的值
                        cb->cb[i][j] = nextcell;
                        cb->cb[i][k] = 0;
                        k = -1;
                    }
                    k--;
                }
            }
        }
    }
    if (flag != -1)
        return score;
    else
        return -1;
}

int moveDown(CB cb)
{
    int i, j, score = 0, flag = -1;
    for (i = GAME_SIZE - 1; i >= 0; i--)
    {
        for (j = 0; j < GAME_SIZE; j++)
        {
            int cell = cb->cb[i][j];

            if (cell != 0)
            {
                int k = i - 1;
                while (k >= 0)
                {
                    int nextcell = cb->cb[k][j];
                    if (nextcell != 0)
                    {
                        if (cb->cb[i][j] == cb->cb[k][j])
                        {
                            flag = 0;
                            cb->cb[i][j]++;
                            score += (int)pow(2, cb->cb[i][j]);
                            cb->cb[k][j] = 0;
                            cb->remainder++;
                        }
                        k = 0;
                        break;
                    }
                    k--;
                }
            }
        }
    }

    //修改部分：for循环中的i或者j的循环条件
    for (i = GAME_SIZE - 1; i > 0; i--)
    {
        for (j = 0; j < GAME_SIZE; j++)
        {
            int cell = cb->cb[i][j];
            if (cell == 0)
            {
                int k = i - 1;
                while (k >= 0)
                {
                    int nextcell = cb->cb[k][j];
                    if (nextcell != 0)
                    {
                        flag = 0;
                        cb->cb[i][j] = nextcell;
                        cb->cb[k][j] = 0;
                        k = 0;
                    }
                    k--;
                }
            }
        }
    }
    if (flag != -1)
        return score;
    else
        return -1;
}

int moveUp(CB cb)
{
    int i, j, score = 0, flag = -1;
    for (i = 0; i < GAME_SIZE; i++)
    {
        for (j = 0; j < GAME_SIZE; j++)
        {
            int cell = cb->cb[i][j];

            if (cell != 0)
            {
                int k = i + 1;
                while (k < GAME_SIZE)
                {
                    int nextcell = cb->cb[k][j];
                    if (nextcell != 0)
                    {
                        if (cell == nextcell)
                        {
                            flag = 0;
                            cb->cb[i][j]++;
                            score += (int)pow(2, cb->cb[i][j]);
                            cb->cb[k][j] = 0;
                            cb->remainder++;
                        }
                        k = GAME_SIZE;
                        break;
                    }
                    k++;
                } // end while
            }
        }
    }

    //修改部分：for循环中的i或者j的循环条件
    for (i = 0; i < GAME_SIZE - 1; i++)
    {
        for (j = 0; j < GAME_SIZE; j++)
        {
            int cell = cb->cb[i][j];
            if (cell == 0)
            {

                int k = i + 1;
                while (k < GAME_SIZE)
                {
                    int nextcell = cb->cb[k][j];
                    if (nextcell != 0)
                    {
                        flag = 0;
                        cb->cb[i][j] = nextcell;
                        cb->cb[k][j] = 0;
                        k = GAME_SIZE;
                    }
                    k++;
                }
            }
        }
    }
    if (flag != -1)
        return score;
    else
        return -1;
}

CB cb_cpy(CB cb)
{
    CB cbcpy = (CB)malloc(sizeof(struct _cb));
    cbcpy->remainder = cb->remainder;
    for (int i = 0; i < GAME_SIZE; i++)
    {
        for (int j = 0; j < GAME_SIZE; j++)
        {
            cbcpy->cb[i][j] = cb->cb[i][j];
        }
    }
    return cbcpy;
}

int gameover(CB cb)
{
    //出现2048直接胜利
    for (int i = 0; i < GAME_SIZE; i++)
    {
        for (int j = 0; j < GAME_SIZE; j++)
        {
            if (cb->cb[i][j] >= 11)
            {
                return 2;
            }
        }
    }
    if (cb->remainder > 0)
    {
        return 0;
    }
    //如果四个移动函数都返回-1即不能移动GameOver
    if (moveDown(cb_cpy(cb)) == -1 && moveUp(cb_cpy(cb)) == -1 && moveLeft(cb_cpy(cb)) == -1 && moveRight(cb_cpy(cb)) == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void cb_key_event_exc(CB cb)
{
    char ch;
    int scoretemp = 0;
    while (true)
    {
        ch = _getch();
        if (ch == 'W' || ch == 'w')
        {
            if ((scoretemp = moveUp(cb)) != -1)
            {
                set_score(scoretemp);
            }
            break;
        }
        else if (ch == 'A' || ch == 'a')
        {
            if ((scoretemp = moveLeft(cb)) != -1)
            {
                set_score(scoretemp);
            }
            break;
        }
        else if (ch == 'S' || ch == 's')
        {
            if ((scoretemp = moveDown(cb)) != -1)
            {
                set_score(scoretemp);
            }
            break;
        }
        else if (ch == 'D' || ch == 'd')
        {
            if ((scoretemp = moveRight(cb)) != -1)
            {
                set_score(scoretemp);
            }
            break;
        }
    }
}

int main()
{
    int overcode = 0;
    //初始化游戏窗口
    initgraph(GRAPH_WIDTH, GRAPH_HEIGHT);
    setbkmode(TRANSPARENT);
    info_init();
    srand((unsigned)time(NULL));

    //创建并初始化棋盘
    CB cb = (CB)malloc(sizeof(struct _cb));
    cb_init(cb);
    cb_draw(cb);

    //循环监听
    while (true)
    {
        //阻塞的方式处理键盘按键时间
        cb_key_event_exc(cb);

        //生成元素绘制,游戏结束判断与响应
        cb_rand(cb);
        cb_draw(cb);
        if (overcode = gameover(cb))
        {
            if (score > hscore)
            {
                hscore = score;
            }
            set_hscore();
            gettextstyle(&font);
            font.lfHeight = 100;
            settextstyle(&font);
            outtextxycenter(GRAPH_HEIGHT / 2, GRAPH_HEIGHT / 2, overcode == 2 ? L"!游戏胜利!" : L"游戏结束");
            system("pause");
            cb_init(cb);
            cb_draw(cb);
        }
    }
    //关闭窗口,退出游戏
    closegraph();
    return 0;
}
