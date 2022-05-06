#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <wingdi.h>
#include <time.h>
#include "FileHandle.h"
#define MAX_STUDENT_ARRAY 20

typedef struct tagRGBQUAD3
{
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    // BYTE    rgbReserved;
} RGBQUAD3;

typedef struct _bf
{
    BITMAPFILEHEADER bmpFileHeader; //文件头
    BITMAPINFOHEADER bmpInfo;       //信息头
    long size;                      //像素个数
    int colorson;
    RGBQUAD3 *colors; //调色板
    RGBQUAD3 *rgb;    //像素数据(BGRR)
} xf_bmpFile;

/**
 * @brief Student链表节点
 */
typedef struct stu
{
    int age;
    char sex; // 0女 1男
    int no;
    double score;
    struct stu *next;
} Student_Struct;

/**
 * @brief 这是一个结构体数组，数组长度MAX_STUDENT_ARRAY
 */
typedef Student_Struct Student_Array[MAX_STUDENT_ARRAY];

Student_Struct *create_Student_list(int n);

void Student_List_info_write(FILE *fp, Student_Struct *head);

void Student_Array_info_write(FILE *fp, Student_Array arr);

void output_Student_list(Student_Struct *s);

void output_Student_Array(Student_Array as);

Student_Struct *Student_List_info_read(FILE *fp);

void Student_list_cat(Student_Struct *a, Student_Struct *b);

void Student_list_del(Student_Struct *ss);

int Student_list_get_len(Student_Struct *sp);

void Student_list_revise(Student_Struct *ss);

xf_bmpFile *BMPFILE_read(FILE *bmp);

void BMPFILE_write(FILE *fp, xf_bmpFile *bmpFile);

void init_xf_bmpFile(xf_bmpFile *bmp, long w, long h);

//#pragma pack(1) //设置系统默认的对齐参数为1，否则结构体实际占用内存大小与理论不一致
/**
 * @brief BMP文件头14
 */
// typedef struct tagBITMAPFILEHEADER
//{
//	WORD bfType;	  // (2Byte)位图文件的类型，必须为BM(0-1字节）
//	DWORD bfSize;	  // (4Byte)位图文件的大小，以字节为单位（2-5字节）
//	WORD bfReserved1; // (2Byte)位图文件保留字，必须为0(6-7字节）
//	WORD bfReserved2; // (2Byte)位图文件保留字，必须为0(8-9字节）
//	DWORD bfOffBits;  // (4Byte)位图数据的起始位置（10-13字节），以相对于位图文件头的偏移量表示，以字节为单位
// } BITMAPFILEHEADER;

/**
 * @brief 位图信息头40
 */
// typedef struct tagBITMAPINFOHEADER
//{
//	DWORD biSize;		   //本结构所占用字节数（14-17字节）
//	DWORD biWidth;		   //位图的宽度，以像素为单位（18-21字节）
//	DWORD biHeight;		   //位图的高度，以像素为单位（22-25字节）
//	WORD biPlanes;		   //目标设备的级别，必须为1(26-27字节）
//	WORD biBitCount;	   //每个像素所需的位数，必须是1（双色），（28-29字节）
//						   // 4(16色），8(256色）或24（真彩色）之一
//	DWORD biCompression;   //位图压缩类型，必须是 0（不压缩），（30-33字节）
//						   // 1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
//	DWORD biSizeImage;	   //位图的大小，以字节为单位（34-37字节）
//	DWORD biXPelsPerMeter; //位图水平分辨率，每米像素数（38-41字节）
//	DWORD biYPelsPerMeter; //位图垂直分辨率，每米像素数（42-45字节)
//	DWORD biClrUsed;	   //位图实际使用的颜色表中的颜色数（46-49字节） 设为0的话，则说明使用所有调色板项，即2 biBitCount种颜色
//	DWORD biClrImportant;  //位图显示过程中重要的颜色数（50-53字节）
// } BITMAPINFOHEADER;

// typedef struct tagRGBQUAD
//{
//	BYTE rgbRed;
//	BYTE rgbGreen;
//	BYTE rgbBlue;
// } RGBQUAD;
