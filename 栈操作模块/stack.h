#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <Windows.h>

#define Stack_Size 200
#define Double_Stack_Size 400
#define Stack_Links_Size 10
#define Digits_per_operand_Size 7
#define Length_Expression 35
#define Length_Input_Expression 50
#define create_number 10
#define OPERATOR "^*/%+-&|"
#define OPERATOR_NUMBER 8

void menu();

void show();

char *createExpression();

char *to_Reverse_Polish_notation(char *Expression);

char *to_r(int num, int r);

double calculateExpression(char *Expression);
