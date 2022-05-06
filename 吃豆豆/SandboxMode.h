#pragma once
#include <graphics.h>
#include <time.h>

#define WM 800
#define HM 500
#define V_MIN 1
#define V_MAX 5
#define R_MIN 10
#define R_MAX 30
#define C_SIZE 15
#define SLEEP_TIME 5

//#define DEBUG

typedef struct c_s
{
    int x;
    int y;
    int r;
    int vx;
    int vy;
    COLORREF color;
    struct c_s *next;
} * CIRCLES;

void getNextPositions(CIRCLES cs);

// void getNextPositionsWithoutColor(CIRCLES cs);

void clearLastCircles(CIRCLES cs);

CIRCLES createCircle();

void insertCircle(CIRCLES cs, int x, int y, int r);

int deleteCircle(CIRCLES cs, int x, int y);

void deleteAll(CIRCLES cs);

void drawCircles(CIRCLES cs);
