#include <stdio.h>
#include <Windows.h>
#include <wingdi.h>

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

xf_bmpFile *BMPFILE_read(FILE *bmp)
{
    xf_bmpFile *bmpFile = (xf_bmpFile *)malloc(sizeof(xf_bmpFile));

    // BITMAPFILEHEADER abc;
    // fread(&bmpFile->bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, bmp); //读取bmp文件头

    fread(&bmpFile->bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, bmp);     //读取bmp文件头
    fread(&bmpFile->bmpInfo, sizeof(BITMAPINFOHEADER), 1, bmp);           //读取位图信息头
    bmpFile->size = bmpFile->bmpInfo.biWidth * bmpFile->bmpInfo.biHeight; //计算像素点数
    bmpFile->colorson = bmpFile->bmpFileHeader.bfOffBits == 1078;         //查看是有调色板
    if (bmpFile->colorson)
    {
        bmpFile->colors = (RGBQUAD3 *)malloc(sizeof(RGBQUAD3) * 256);
        fread(bmpFile->colors, sizeof(RGBQUAD3), 256, bmp); //读取调色板（如果有）
    }
    bmpFile->rgb = (RGBQUAD3 *)malloc(sizeof(RGBQUAD3) * bmpFile->size);
    fread(bmpFile->rgb, sizeof(RGBQUAD3), bmpFile->size, bmp); //读取像素数据
    // printf("ok");
    return bmpFile;
}

int main(int argc, char const *argv[])
{
    FILE *fp;
    xf_bmpFile *bmp;
    fopen_s(&fp, "a.bmp", "rb");
    bmp = BMPFILE_read(fp);
    fclose(fp);
    fopen_s(&fp, "bmp.src", "wb");
    fwrite(bmp->rgb, sizeof(RGBQUAD3), 600 * 400, fp);
    fclose(fp);
    return 0;
}
