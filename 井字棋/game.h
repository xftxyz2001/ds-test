#pragma once
#include <graphics.h>
#include <conio.h>

#define WM 450
#define HM 450

typedef struct cb
{
    int chessboard[9];
    int isWhoDown; // 1 is left; 2 is right
} chessboard;

// int my_color[5] = { RED,GREEN,BLUE,YELLOW,WHITE };