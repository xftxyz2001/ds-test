#include "FileHandle.h"

/**
 * @brief Create a Student list object
 *
 * @param n 创建的链表节点的个数
 * @return Student_Struct* 创建出的链表的头结点的指针
 */
Student_Struct *create_Student_list(int n)
{
    Student_Struct *sl = (Student_Struct *)malloc(sizeof(Student_Struct));
    int m = 0;
    sl->next = NULL;
    while (n-- > 0)
    {
        Student_Struct *temp = (Student_Struct *)malloc(sizeof(Student_Struct));
        temp->age = rand() % 50 + 10;
        temp->sex = rand() % 2;
        m += rand() % 10 + 1;
        temp->no = m;
        temp->score = rand() % 10000 / 100.0;
        temp->next = sl->next; //头插入方式
        sl->next = temp;
    }
    return sl;
}

/**
 * @brief 将一个链表写入文件
 *
 * @param fp 文件指针（文件在调用这个函数之前应该以写模式打开）
 * @param head 链表头结点的指针
 */
void Student_List_info_write(FILE *fp, Student_Struct *head)
{
    while (head = head->next)
    {
        fwrite(head, sizeof(Student_Struct), 1, fp);
    }
}

/**
 * @brief 将一个数组写入文件
 *
 * @param fp 文件指针（文件在调用这个函数之前应该以写模式打开）
 * @param arr 数组
 */
void Student_Array_info_write(FILE *fp, Student_Array arr)
{
    int n = 0;
    for (int i = 0; i < MAX_STUDENT_ARRAY; i++)
    {
        if (arr[i].no != 0)
        {
            n++;
        }
    }
    fwrite(arr, sizeof(Student_Struct), n, fp);
}

void output_Student_list(Student_Struct *s)
{
    printf("学号\t年龄\t性别\t成绩\n");
    while (s = s->next)
    {
        printf("%5d\t%3d\t%s\t%.2f\n", s->no, s->age, s->sex ? "男" : "女", s->score);
    }
}

void output_Student_Array(Student_Array sa)
{
    printf("学号\t年龄\t性别\t成绩\n");
    for (int i = 0; i < MAX_STUDENT_ARRAY; i++)
    {
        if (sa[i].no == 0)
        {
            break;
        }
        printf("%5d\t%3d\t%s\t%.2f\n", sa[i].no, sa[i].age, sa[i].sex ? "男" : "女", sa[i].score);
    }
}

Student_Struct *Student_List_info_read(FILE *fp)
{
    Student_Struct *ss = (Student_Struct *)malloc(sizeof(Student_Struct));
    Student_Struct *temp = (Student_Struct *)malloc(sizeof(Student_Struct));
    Student_Struct *sp = ss;
    while (true)
    {
        // printf("a");
        if (fread(temp, sizeof(Student_Struct), 1, fp) == 0)
            break;
        sp->next = temp;
        sp = temp;
        temp = (Student_Struct *)malloc(sizeof(Student_Struct));
    }
    sp->next = NULL;
    return ss;
}

void Student_list_cat(Student_Struct *a, Student_Struct *b)
{
    while (a->next)
    {
        a = a->next;
    }
    a->next = b->next;
}

void Student_list_del(Student_Struct *ss)
{
    Student_Struct *sp = ss;
    int c = 0;
    while (sp = sp->next)
    {
        c++;
    }
    c = rand() % c;
    while (c--)
    {
        ss = ss->next;
    }
    printf("删除了：");
    printf("%5d\t%3d\t%s\t%.2f\n", ss->next->no, ss->next->age, ss->next->sex ? "男" : "女", ss->next->score);
    ss->next = ss->next->next;
}

int Student_list_get_len(Student_Struct *sp)
{
    int c = 0;
    while (sp = sp->next)
    {
        c++;
    }
    return c;
}

void Student_list_revise(Student_Struct *ss)
{
    while (ss = ss->next)
    {
        ss->age = rand() % 2 == 0 ? rand() % 50 + 10 : ss->age;
        ss->score = rand() % 2 == 0 ? rand() % 10000 / 100.0 : ss->score;
    }
}

/**
 * @brief 读入一个bmp图片
 *
 * @param bmp 文件指针，在这之前文件需要以r打开
 * @return BMPFILE*
 */
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
        fread(bmpFile->colors, sizeof(RGBQUAD), 256, bmp); //读取调色板（如果有）
    }
    bmpFile->rgb = (RGBQUAD3 *)malloc(sizeof(RGBQUAD3) * bmpFile->size);
    fread(bmpFile->rgb, sizeof(RGBQUAD3), bmpFile->size, bmp); //读取像素数据
    // printf("ok");
    return bmpFile;
}

void BMPFILE_write(FILE *fp, xf_bmpFile *bmpFile)
{
    fwrite(&bmpFile->bmpFileHeader, sizeof(BITMAPFILEHEADER), 1, fp); // bmp文件头
    fwrite(&bmpFile->bmpInfo, sizeof(BITMAPINFOHEADER), 1, fp);       //位图信息头
    fwrite(bmpFile->rgb, sizeof(RGBQUAD3), bmpFile->size, fp);        //像素数据
}

void init_xf_bmpFile(xf_bmpFile *bmp, long w, long h)
{
    bmp->bmpFileHeader.bfType = (unsigned short)('M' << 8) | 'B';
    bmp->bmpFileHeader.bfReserved1 = 0;
    bmp->bmpFileHeader.bfReserved2 = 0;
    bmp->bmpFileHeader.bfOffBits = 54L;
    bmp->bmpFileHeader.bfSize = bmp->bmpFileHeader.bfOffBits + sizeof(RGBQUAD3) * w * h;
    // bmp->bmpFileHeader.bfSize = 720054L;

    bmp->bmpInfo.biSize = 40L;
    bmp->bmpInfo.biWidth = w;
    bmp->bmpInfo.biHeight = h;
    bmp->bmpInfo.biPlanes = 1;
    bmp->bmpInfo.biBitCount = 24;
    bmp->bmpInfo.biCompression = 0L;
    // bmp->bmpInfo.biSizeImage = 720000L;
    bmp->bmpInfo.biSizeImage = sizeof(RGBQUAD3) * w * h;
    bmp->bmpInfo.biXPelsPerMeter = 0L;
    bmp->bmpInfo.biYPelsPerMeter = 0L;
    bmp->bmpInfo.biClrUsed = 0L;
    bmp->bmpInfo.biClrImportant = 0L;

    bmp->size = w * h;
}