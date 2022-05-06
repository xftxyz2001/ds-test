// 6-3 变长动态数组 30分
// 在C/C++中，原生数组的空间大小是静态的。例如，声明int a[10]之后，数组a的大小就已经固定为10，因此在使用时，
// 常常以数据量的上限作为数组的长度，比如最多有可能要保存100,000个元素时，可以创建一个长度为100,000 的数组。
// 这样做的显著缺点就是，当实际数据量较小时，会造成大量的空间浪费。更合理的方法是因地制宜地对数组空间进行动态分配。
// 这里给出一种最简单的动态数组管理策略：

// 1.使用用户分配的一段连续的内存空间表示数组；
// 2.初始时，数组的容量为16；
// 3.(扩展) 当插入元素时，如果空间已满，将数组容量增加至原有的2倍，也就是将原有的空间释放，
// 分配一个大小为原有大小2倍的内存空间，并将原来的元素复制到新的空间中，例如原来的空间大小为16，现在增加到32；
// 4.(压缩) 删除数组中元素后，如果剩余元素的数量小于容量的1/4（向下取整）且数组的容量大于16时，删除掉原有的空间，
// 分配一个为原有容量一半的新的内存空间，并将原来的元素复制到新的空间中，例如原来的容量为64，但是删除元素后，
// 数组中只有15个元素，那么将容量压缩到32。
// 根据以上策略，实现下面的接口。这些接口以C++中容器std::vector为蓝本，接口的具体功能请看函数前的注释。
// 通过实现这些接口，你或许能够受到一些关于面向对象编程(OOP)的启发。

#include <stdio.h>
#include <stdlib.h>

typedef int Elem;

typedef enum bool
{
    false,
    true
} bool;

typedef struct DynamicArray
{
    size_t capacity; // 数组的容量，初始值和最小值均为16u
    size_t size;     // 数组中元素的个数
    Elem *data;      // 用于保存数组中元素的内存空间
} DynamicArray;

// 创建数组，初始容量为16。
DynamicArray *DynamicArray_new();

// 本题中，在位置pos前插入元素*v，也就是*v插入后，它是数组中的第pos个元素，下标从0开始。
// 注意，插入后的数组可能发生容量的倍增，假设内存分配总是合法的，不需要针对内存不足抛出异常。
// 例如：
//      1. pos = 10  ，表示在第10个元素前插入元素*v，插入后它前面有10个元素，原来的第10个元素在它后面
//      2. pos = 0   ，表示在数组的起始位置插入元素*v
//      3. pos = size，表示在数组的末尾插入元素*v
void DynamicArray_insert(DynamicArray *this, size_t pos, const Elem *v);

// 删除位置pos的元素，可以假定pos总是合法的，即pos=0,1,...,size - 1，删除后的数组不应该有空档。
// 注意，删除数组元素可能会导致容量变更。
// 例如：
//     size = 6, 数组中的元素为0,1,2,3,4,5。删除了pos=3的元素3之后，数组的元素变为0,1,2,4,5，size=5，数组第3个元素为4
Elem DynamicArray_erase(DynamicArray *this, size_t pos);

// 获取位置为pos的元素，假设pos总是合法的。
Elem DynamicArray_get(const DynamicArray *this, size_t pos);

// 将位置为pos的元素设置为*v，假设pos总是合法的。
void DynamicArray_set(DynamicArray *this, size_t pos, const Elem *v);

// 返回数组的容量。
size_t DynamicArray_capacity(const DynamicArray *this);

// 返回数组的元素个数。
size_t DynamicArray_size(const DynamicArray *this);

// 返回数组元素是否为空，为空则返回true，否则返回false。
bool DynamicArray_empty(const DynamicArray *this);

// 重设数组元素个数为new_size，注意，容量可能因此发生变更。
// 新的数组元素个数如果比原来的数组更多，将原有数组的元素复制到新数组对应位置即可。
// 新的数组元素个数如果比原来的数组更少，超出的部分截断即可。
// 例如：
//    1. 原数组为0,1,2,3,4,5，新数组大小为4，那么新数组变为0,1,2,3，size=4
//    2. 原数组为0,1,2,3，新数组大小为6，那么数组变为0,1,2,3,?,?，size=6，其中?表示任意值，即这些多出的元素
//       不需要初始化
void DynamicArray_resize(DynamicArray *this, size_t new_size);

// 删除数组。不要忘记释放原有数组的空间，否则会造成内存泄漏。
void DynamicArray_delete(DynamicArray *this);

int main()
{
    char line[100];
    DynamicArray *arr = NULL;
    size_t size;
    size_t pos;
    Elem v;

    while (gets(line))
    {
        switch (line[0])
        {
        case 'C': // 创建数组
            arr = DynamicArray_new();
            break;
        case 'D': // 删除数组
            DynamicArray_delete(arr);
            arr = NULL;
            break;
        case 'R': // resize
            sscanf(line + 2, "%lu", &size);
            DynamicArray_resize(arr, size);
            break;
        case 'c': // 输出capacity
            printf("%lu\n", DynamicArray_capacity(arr));
            break;
        case 's': // 输出size
            printf("%lu\n", DynamicArray_size(arr));
            break;
        case 'i': // 插入元素
            sscanf(line + 2, "%lu %d", &pos, &v);
            DynamicArray_insert(arr, pos, &v);
            break;
        case 'd': // 删除元素并输出
            sscanf(line + 2, "%lu", &pos);
            printf("%d\n", DynamicArray_erase(arr, pos));
            break;
        case 'G': // get元素并输出
            sscanf(line + 2, "%lu", &pos);
            printf("%d\n", DynamicArray_get(arr, pos));
            break;
        case 'S': // set元素
            sscanf(line + 2, "%lu %d", &pos, &v);
            DynamicArray_set(arr, pos, &v);
            break;
        case 'e': // 输出数组是否为empty
            printf("%s\n", DynamicArray_empty(arr) == true ? "true" : "false");
            break;
        default:
            // for (size_t i = 0; i < arr->size; i++)
            // {
            //     printf("%d,", DynamicArray_get(arr, i));
            // }
            // printf("\tsize:%d\tcap:%d\n", arr->size, arr->capacity);
            break;
        }
    }

    return 0;
}

/* 请在这里填写答案 */

// 创建数组，初始容量为16。
DynamicArray *DynamicArray_new()
{
    DynamicArray *da = malloc(sizeof(DynamicArray));
    da->data = malloc(16 * sizeof(Elem));
    da->capacity = 16u;
    da->size = 0u;
    return da;
}

// 本题中，在位置pos前插入元素*v，也就是*v插入后，它是数组中的第pos个元素，下标从0开始。
// 注意，插入后的数组可能发生容量的倍增，假设内存分配总是合法的，不需要针对内存不足抛出异常。
// 例如：
//      1. pos = 10  ，表示在第10个元素前插入元素*v，插入后它前面有10个元素，原来的第10个元素在它后面
//      2. pos = 0   ，表示在数组的起始位置插入元素*v
//      3. pos = size，表示在数组的末尾插入元素*v
void DynamicArray_insert(DynamicArray *this, size_t pos, const Elem *v)
{
    if (this->size + 1 > this->capacity) // 如果需要扩展
    {
        Elem *new_data = malloc(this->capacity * sizeof(Elem) * 2); // 分配空间
        this->capacity *= 2;                                        // 标记扩展
        size_t i = 0;
        for (; i < pos; i++) // i < pos pos这个元素不复制
        {
            new_data[i] = this->data[i];
        }
        for (; i < this->size; i++)
        {
            new_data[i + 1] = this->data[i];
        }
        // 释放空间
        free(this->data);
        this->data = new_data;
    }
    else
    {
        for (size_t i = this->size; i > pos; i--)
        {
            this->data[i] = this->data[i - 1];
        }
    }
    this->data[pos] = *v;
    this->size++;
}

// 删除位置pos的元素，可以假定pos总是合法的，即pos=0,1,...,size - 1，删除后的数组不应该有空档。
// 注意，删除数组元素可能会导致容量变更。
// 例如：
//     size = 6, 数组中的元素为0,1,2,3,4,5。删除了pos=3的元素3之后，数组的元素变为0,1,2,4,5，size=5，数组第3个元素为4
Elem DynamicArray_erase(DynamicArray *this, size_t pos)
{
    if (this->size == 0) // 假定没有元素可以删除了,不必要.
    {
        return 0;
    }

    Elem e_del = this->data[pos];
    if (this->size - 1 < this->capacity / 4 && this->capacity > 16) // 如果需要压缩
    {
        Elem *new_data = malloc(this->capacity * sizeof(Elem) / 2); // 分配空间
        this->capacity /= 2;                                        // 标记压缩
        size_t i = 0;
        for (; i < pos; i++)
        {
            new_data[i] = this->data[i];
        }
        for (; i < this->size; i++)
        {
            new_data[i] = this->data[i + 1];
        }
        // 释放空间
        free(this->data);
        this->data = new_data;
    }
    else // 如果不需要压缩，直接将后面元素移过来填补空位，如果删除的是最后一个元素，不做处理
    {
        // for (size_t i = pos + 1; i < this->size; i++)
        for (size_t i = pos + 1; i <= this->size; i++)
        {
            this->data[i - 1] = this->data[i];
        }
    }
    this->size--;
    return e_del;
}

// 获取位置为pos的元素，假设pos总是合法的。
Elem DynamicArray_get(const DynamicArray *this, size_t pos)
{
    return this->data[pos];
}

// 将位置为pos的元素设置为*v，假设pos总是合法的。
void DynamicArray_set(DynamicArray *this, size_t pos, const Elem *v)
{
    this->data[pos] = *v;
}

// 返回数组的容量。
size_t DynamicArray_capacity(const DynamicArray *this)
{
    return this->capacity;
}

// 返回数组的元素个数。
size_t DynamicArray_size(const DynamicArray *this)
{
    return this->size;
}

// 返回数组元素是否为空，为空则返回true，否则返回false。
bool DynamicArray_empty(const DynamicArray *this)
{
    return this->size == 0;
    // return this->size == 0 ? true: false;
}

// 重设数组元素个数为new_size，注意，容量可能因此发生变更。
// 新的数组元素个数如果比原来的数组更多，将原有数组的元素复制到新数组对应位置即可。
// 新的数组元素个数如果比原来的数组更少，超出的部分截断即可。
// 例如：
//    1. 原数组为0,1,2,3,4,5，新数组大小为4，那么新数组变为0,1,2,3，size=4
//    2. 原数组为0,1,2,3，新数组大小为6，那么数组变为0,1,2,3,?,?，size=6，其中?表示任意值，即这些多出的元素
//       不需要初始化
void DynamicArray_resize(DynamicArray *this, size_t new_size)
{
    // if (new_size <= this->size)
    // {
    //     this->size = new_size;
    if (new_size < this->capacity / 2 && this->capacity > 16)
    {
        Elem *new_data = malloc(this->capacity * sizeof(Elem) / 2); // 分配空间
        this->capacity /= 2;                                        // 标记压缩
        // 如果空间仍然过剩
        while (new_size < this->capacity / 2 && this->capacity > 16)
        {
            free(new_data);
            new_data = malloc(this->capacity * sizeof(Elem) / 2); // 分配空间
            this->capacity /= 2;                                  // 标记扩展
        }
    }
    // {
    //     this->size = new_size;
    // }
    else if (new_size > this->capacity)
    {
        // Elem *new_data = malloc(this->capacity * sizeof(Elem) * 2);
        Elem *new_data = malloc(this->capacity * sizeof(Elem) * 2); // 分配空间
        this->capacity *= 2;                                        // 标记扩展
        // 如果空间仍然不够
        while (new_size > this->capacity)
        {
            free(new_data);
            new_data = malloc(this->capacity * sizeof(Elem) * 2); // 分配空间
            this->capacity *= 2;                                  // 标记扩展
        }

        // Elem *new_data = malloc(this->capacity * sizeof(Elem) * 2); // 分配空间
        // this->capacity *= 2;                                        // 标记扩展
        for (size_t i = 0; i < this->size && i < this->capacity; i++)
        {
            new_data[i] = this->data[i];
        }
        // 释放空间
        free(this->data);
        this->data = new_data;
    }
    this->size = new_size;
}

// 删除数组。不要忘记释放原有数组的空间，否则会造成内存泄漏。
void DynamicArray_delete(DynamicArray *this)
{
    free(this->data);
    free(this);
}
