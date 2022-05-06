#include "FileHandle.h"

int main()
{
    FILE *fp; //祖传文件指针
    int m = 0, n = 0;

    srand((unsigned int)time(NULL)); //初始化随机数函数

    //第一题
    printf("(1)创建一个链表，用来记录若干学生数据（年龄、性别、学号、平均分等），并将学生数据保存到二进制或文本文件中。\n");
    Student_Struct *stus = create_Student_list(rand() % 10 + 2);
    printf("系统自动生成的学生信息如下：\n");
    output_Student_list(stus);

    fopen_s(&fp, "one.xf", "w");
    printf(">one.xf  ");

    Student_List_info_write(fp, stus);
    fclose(fp);
    printf("succeed.\n");

    //第二题
    printf("(2)用数组记录若干学生的数据，并将学生数据保存到二进制或文本文件中。\n");
    Student_Array stua;
    n = rand() % 10 + 2;
    int i = 0;
    for (; i < n; i++)
    {
        stua[i].age = rand() % 50 + 10;
        stua[i].sex = rand() % 2;
        m += rand() % 10 + 1;
        stua[i].no = m;
        stua[i].score = rand() % 10000 / 100.0;
    }
    stua[i].no = 0;
    printf("系统自动生成的学生信息如下：\n");
    output_Student_Array(stua);

    fopen_s(&fp, "two.xf", "w");
    printf(">two.xf  ");

    Student_Array_info_write(fp, stua);
    fclose(fp);
    printf("succeed.\n");

    //第三题
    printf("(3)由实验（1）创建的文件中读入全部学生数据，实现学生数据的增加、删出、查找和修改等操作，并将处理后的学生数据保存到文件中。\n");
    fopen_s(&fp, "one.xf", "r");
    Student_Struct *ss = Student_List_info_read(fp);
    fclose(fp);
    output_Student_list(ss);

    printf("插入如下数据：\n");
    Student_Struct *s_temp = create_Student_list(rand() % 3 + 2);
    output_Student_list(s_temp);
    printf("插入后：\n");
    Student_list_cat(ss, s_temp);
    output_Student_list(ss);

    n = rand() % (Student_list_get_len(ss) - 1);
    while (n--)
    {
        Student_list_del(ss);
    }
    output_Student_list(ss);

    printf("修改部分数据后：\n");
    Student_list_revise(ss);
    output_Student_list(ss);

    fopen_s(&fp, "three.xf", "w");
    printf(">three.xf  ");
    Student_List_info_write(fp, ss);
    fclose(fp);
    printf("succeed.\n");

    //第四题
    xf_bmpFile *bmp;
    unsigned long average_b = 0, average_g = 0, average_r = 0;
    printf("(4)打开一个BMP位图，计算并输出平均灰度值。程序默认打开test.bmp\n");
    fopen_s(&fp, "test.bmp", "rb");
    bmp = BMPFILE_read(fp);
    fclose(fp);
    for (int i = 0; i < bmp->size; i++)
    {
        average_b += bmp->rgb[i].rgbBlue;
        average_g += bmp->rgb[i].rgbGreen;
        average_r += bmp->rgb[i].rgbRed;
    }
    average_b /= bmp->size;
    average_g /= bmp->size;
    average_r /= bmp->size;
    printf("b:%ld\tg:%ld\tr:%ld\n", average_b, average_g, average_r);

    //第五题
    long width = 600, height = 400;
    printf("(5)从二进制文件中读入一副图像的原始数据，并保存为BMP文件。演示程序默认从bmp.src中读取图像原始数据，并保存成尺寸为%ld*%ld的bmp文件。\n", width, height);
    fopen_s(&fp, "bmp.src", "rb");
    xf_bmpFile *bmpdir = (xf_bmpFile *)malloc(sizeof(xf_bmpFile));
    bmpdir->rgb = (RGBQUAD3 *)malloc(sizeof(RGBQUAD3) * width * height);
    fread(bmpdir->rgb, sizeof(RGBQUAD3), width * height, fp);
    fclose(fp);
    init_xf_bmpFile(bmpdir, width, height);
    fopen_s(&fp, "bmp.bmp", "wb");
    BMPFILE_write(fp, bmpdir);
    fclose(fp);
    printf(">bmp.bmp\n");

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    //第六题
    // printf("(6)打开一个文本文件，通过菜单对其进行简单编辑，并将编辑后的结果保存到文件。\n");
    // fopen_s(&fp, "test.txt", "wr");

    // fclose(fp);
    printf("press any key delete temp file!");
    getchar();
    system("del.bat");
    return 0;
}
