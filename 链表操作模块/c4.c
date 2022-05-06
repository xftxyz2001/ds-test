#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_SIZE_1 10
#define MIN_SIZE 3
#define MAX_SIZE (MAX_SIZE_1 + MIN_SIZE * 2)

typedef struct node
{
    int data;          //数据域,保存结点的值
    struct node *next; //指针域
} Node, *LinkList;     //结点的类型

typedef struct list
{
    struct node *data;
    struct list *next;     //指针域
} ListNode, *ListLinkList; //结点的类型

/**
 * @brief 随机函数：概率p%，可直接用于条件和循环判断
 *
 * @param p 概率
 * @return int yes or no
 */
int isProbability(int p)
{
    return (rand() % 100 < p) ? 1 : 0;
}

/**
 * @brief 为一个链表添加表头
 *
 * @param p
 * @return Node* 返回链表的头节点
 */
Node *add_LinkList_header(Node *p)
{
    Node *head;
    head = (Node *)malloc(sizeof(Node));
    head->next = p;
    return head;
}

/**
 * @brief Create a LinkList randInt head object
 * 以头插法创建一个元素递减的链表
 * @param size 链表长度
 * @return Node* 返回链表的头节点
 */
Node *create_LinkList_randInt_head(int size)
{
    int data, i;
    Node *head, *p;
    head = (Node *)malloc(sizeof(Node));
    head->next = NULL; //创建链表的表头结点head
    for (i = 0; i < size; i++)
    {
        data = rand() % 50 + 50 * i;      //生成数据
        p = (Node *)malloc(sizeof(Node)); //申请空间
        p->data = data;                   //数据域赋值
        p->next = head->next;             //新建立的节点的next指向原来的全部数据的首。
        head->next = p;                   //再将新建立的节点使用头节点指向。
    }
    return head;
}

/**
 * @brief Create a LinkList randInt head maySameData object
 * 以头插法创建一个元素递减并且可能含有相同元素的链表
 * @param size 链表长度
 * @return Node* 返回链表的头节点
 */
Node *create_LinkList_randInt_head_maySameData(int size)
{
    int data, i;
    static int lastData = 0; //默认第一个元素为0后期可改
    Node *head, *p;
    head = (Node *)malloc(sizeof(Node));
    head->next = NULL; //创建链表的表头结点head
    for (i = 0; i < size; i++)
    {
        data = (isProbability(50)) ? rand() % 50 + 50 * i : lastData; //生成数据
        lastData = data;
        p = (Node *)malloc(sizeof(Node)); //申请空间
        p->data = data;                   //数据域赋值
        p->next = head->next;             //新建立的节点的next指向原来的全部数据的首。
        head->next = p;                   //再将新建立的节点使用头节点指向。
    }
    return head;
}

/**
 * @brief Create a LinkList randIntIncrease tail object
 * 以尾插法创建一个元素递增的链表
 * @param size 链表长度
 * @return Node* 返回链表的头节点
 */
Node *create_LinkList_randIntIncrease_tail(int size)
{
    int data, i;
    Node *head, *p, *q;
    head = p = (Node *)malloc(sizeof(Node));
    p->next = NULL; /*  创建单链表的表头结点head  */
    for (i = 0; i < size; i++)
    {
        data = rand() % 50 + 50 * i;      //生成数据
        q = (Node *)malloc(sizeof(Node)); //申请空间
        q->data = data;                   //数据域赋值
        q->next = p->next;                // p是最后一个节点,而p–> next是最后一个节点的后继,q是新节点。
        p->next = q;                      //将q接到p后面。
        p = q;                            //将p后以至最后。
    }
    return head;
}

/**
 * @brief Create a LinkList randInt tail object
 * 以尾插法创建一个随机元素的链表
 * @param size 链表长度
 * @return Node* 返回链表的头节点
 */
Node *create_LinkList_randInt_tail(int size)
{
    int data, i;
    Node *head, *p, *q;
    head = p = (Node *)malloc(sizeof(Node));
    p->next = NULL; /*  创建单链表的表头结点head  */
    for (i = 0; i < size; i++)
    {
        data = rand();                    //生成数据，完全随机
        q = (Node *)malloc(sizeof(Node)); //申请空间
        q->data = data;                   //数据域赋值
        q->next = p->next;                // p是最后一个节点,而p–> next是最后一个节点的后继,q是新节点。
        p->next = q;                      //将q接到p后面。
        p = q;                            //将p后以至最后。
    }
    return head;
}

/**
 * @brief 生成一个自然数序列
 *
 * @param size 链表长度
 * @return Node* 返回链表的头节点
 */
Node *create_LinkList_IntIncrease_circle(int size)
{
    int i;
    Node *head, *p, *q;
    head = p = (Node *)malloc(sizeof(Node));
    p->next = NULL; /*  创建单链表的表头结点head  */
    for (i = 0; i < size; i++)
    {
        q = (Node *)malloc(sizeof(Node)); //申请空间
        q->data = i + 1;                  //数据域赋值
        q->next = p->next;                // p是最后一个节点,而p–> next是最后一个节点的后继,q是新节点。
        p->next = q;                      //将q接到p后面。
        p = q;                            //将p后以至最后。
    }
    p->next = head->next;
    return head;
}

/**
 * @brief 将传入的链表逆序
 *
 * @param head 需要逆序链表的头节点
 * @return Node* 返回逆序后的元素头节点
 */
Node *reverse_LinkList(Node *head)
{
    Node *p1 = head->next; //指向第一个元素
    if (p1->next == NULL)  //如果传入表只有一个节点
    {
        head->next = p1;
        return head;
    }
    Node *p2 = p1->next; //传入的表至少含有两个元素
    p1->next = NULL;
    while (p2->next != NULL) //如果还存在后继
    {
        Node *p3 = p2->next; //将本节点后继保存下来
        p2->next = p1;       //将本节点的上一个节点改为本节点的后继
        p1 = p2;             // p1后移指向本节点
        p2 = p3;             //本节点后移指向本节点的后继
    }
    p2->next = p1; //如果p2是最后一个节点了，那么直接将p2的后继改为上一个节点，此时p2即为新链表的表头
    head->next = p2;
    return head;
}

/**
 * @brief 输出一个数值链表的全部元素
 *
 * @param listName 链表的名字
 * @param head 表头
 */
void print_LinkList(char *listName, Node *head)
{
    Node *p;
    printf("链表%s的值如下:\n", listName);
    for (p = head->next; p != NULL; p = p->next)
        printf("%d; ", p->data);
    printf("\n");
}

/**
 * @brief 输出一个链表部分的全部元素
 *
 * @param head 子链表头
 */
void print_LinkList2_perPart(Node *head)
{
    static int count = 0;

    if (head == NULL || head->next == NULL)
    {
        printf("链表部分%d的值为：NULL\n", ++count);
        return;
    }
    Node *p;
    printf("链表部分%d的值为：", ++count);
    for (p = head->next; p != NULL; p = p->next)
        printf("%d; ", p->data);
    printf("\n");
}

/**
 * @brief 输出一个链表组的全部元素
 *
 * @param head 链表组表头
 */
void print_LinkList2(ListNode *head)
{
    ListNode *p;
    printf("链表组的值如下:\n");
    for (p = head->next; p != NULL; p = p->next)
    {
        print_LinkList2_perPart(p->data);
    }
}

/**
 * @brief 将La，Lb合并并返回合并后的链表
 *
 * @param La
 * @param Lb
 * @return Node* 返回链表的头节点
 */
Node *Merge_LinkList(Node *La, Node *Lb)
{
    Node *Lc, *pa, *pb, *pc;
    int count = 0;
    Lc = La; //使用La的表头充当合成链表的表头
    pc = La;
    pa = La->next;
    pb = Lb->next;
    while (pa != NULL && pb != NULL)
    {
        // printf("第%d次连接：\n", ++count);
        if (pa->data > pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        /*  将pa所指的结点合并,pa指向下一个结点  */
        else if (pa->data < pb->data)
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
        /*  将pb所指的结点合并,pb指向下一个结点  */
        else if (pa->data == pb->data)
        {
            Node *ptr;
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            ptr = pb;
            pb = pb->next;
            free(ptr);
        }
        /*  将pa所指的结点合并,pb所指结点删除  */
    }
    /*将剩余的结点链上*/
    if (pa != NULL)    // Lb中的全部节点全部插入到Lc中
        pc->next = pa; //将La中的剩余节点,接到Lc后
    else               // La中的全部节点全部插入到Lc中
        pc->next = pb; //将Lb中的剩余节点,接到Lc后
    free(Lb);
    return Lc;
}

/**
 * @brief 以第一个元素为基准，将小于该元素的结点全部放到前面，大于该结点的元素全部放到后面。
 *
 * @param head 需要处理的链表
 */
void moveLinkListByFirstData(Node *head)
{
    if (head == NULL || head->next == NULL || head->next->next == NULL) //空链表或只有一个元素不做处理
        return;
    Node *pbase = head->next, *pp, *pn;
    // pn是当前遍历节点，pp是基准的副本
    pp = pbase;
    pn = pbase->next;
    pbase->next = NULL; //清空基准的后继，防止基准无后继时链表产生循环
    while (pn != NULL)
    {
        if (pn->data < pbase->data)
        {
            head->next = pn;
            head = pn;
            pn = pn->next; // pn后移
        }
        else
        {
            pp->next = pn;
            pp = pn;         // pp后移
            pn = pn->next;   // pn后移
            pp->next = NULL; //将pp后继置为空，防止链表产生循环
        }
    }
    head->next = pbase; //将第一部分和第二部分连接起来
}

/**
 * @brief 将两个链表相交
 * 可能丢失部分元素
 * @param headA
 * @param headB
 */
void intersect_LinkList_mayLoseElements(Node *headA, Node *headB)
{
    //空链表不处理
    if (headA->next == NULL || headB->next == NULL)
        return;
    Node *pa, *pb;
    //随机两个链表连接
    if (rand() % 2)
    {
        pa = headA->next;
        pb = headB->next;
    }
    else
    {
        pb = headA->next;
        pa = headB->next;
    }
    int n = rand() % (MIN_SIZE + 1);
    int i;
    for (i = 0; i <= n; i++)
    {
        if (isProbability(50) && pa->next != NULL)
            pa = pa->next;
        if (isProbability(50) && pb->next != NULL)
            pb = pb->next;
    }
    pa->next = pb;
}

/**
 * @brief Get the Intersection Node object
 * 提前使用add_LinkList_header添加了头节点
 * @param headA
 * @param headB
 * @return Node* 返回相交部分链表的头节点
 */
Node *getIntersectionNode(Node *headA, Node *headB)
{
    if (headA->next == NULL || headB->next == NULL)
        return NULL;
    Node *pa = headA->next;
    Node *pb = headB->next;
    // Node* head;
    // int pend = 0;
    // head = (Node*)malloc(sizeof(Node));
    while (pa != pb)
    {
        /*
        if (pa == NULL)
        {
            pa = headB->next;
            pend++;
        }
        else
        {
            pa = pa->next;
        }
        if (pb == NULL)
        {
            pb = headA->next;
            pend++;
        }
        else
        {
            pb = pb->next;
        }
        */
        pa = (pa == NULL) ? headB->next : pa->next;
        pb = (pb == NULL) ? headA->next : pb->next;
    }
    // head->next = pa;
    return (pa == NULL) ? NULL : add_LinkList_header(pa);
}

/**
 * @brief 删除单链表中所有值重复的结点,使得所有结点的值都不相同。
 * 删除以L为头结点的单链表中所有值相同的结点
    与按值查找相类似,但比前面的算法更复杂。
基本思想：从单链表的第一个结点开始,对每个结点进行检查：检查链表中该结点的所有后继结点,只要有值和该结点的值相同,则删除之；然后检查下一个结点,直到所有的结点都检查。
 * @param L
 */
void Delete_Node_value(Node *L)
{
    if (L == NULL || L->next == NULL)
        return;
    Node *p, *q, *ptr;
    for (p = L->next; p != NULL; p = p->next) //检查链表中所有结点
    {
        q = p;
        ptr = p->next;
        while (ptr != NULL) //检查结点p的所有后继结点ptr
        {
            if (ptr->data == p->data)
            {
                q->next = ptr->next;
                free(ptr);
                ptr = q->next;
            }
            else
            {
                q = ptr;
                ptr = ptr->next;
            }
        }
    }
}

/**
 * @brief 删除一个排序链表的重复元素
 * 无返回值，直接将原链表的相同元素进行了移除
 * @param L 一个链表
 */
void Delete_Node_orderSameValue(Node *L)
{
    if (L == NULL || L->next == NULL)
        return;
    Node *p, *ptr;
    for (p = L->next; p != NULL; p = p->next)
    {
        // q = p;由于一旦出现不相等则之后都不会相等，所以不需要p的副本
        ptr = p->next;      //这里ptr是p的后继，不知道是不是null
        while (ptr != NULL) //检查结点p的所有后继结点ptr
        {
            if (ptr->data == p->data)
            {
                p->next = ptr->next;
                free(ptr);
                ptr = p->next;
            }
            else //如果出现不相等则之后都不会相等,直接移动p到下一个点位即可
            {    //由于中间相等的节点都已经删除，所以直接靠for的语句三移动p即可将p移动到ptr上
                break;
                // q = ptr;
                // ptr = ptr->next;
            }
        }
    }
}

/**
 * @brief 计算一个链表的长度
 *
 * @param head 待计算链表
 * @return int 需要计算链表的长度
 */
int length_LinkList(Node *head)
{
    int count;
    for (count = 0; head->next != NULL; count++, head = head->next)
        ;
    return count;
}

/**
 * @brief 删除给定链表的倒数第n个元素
 *
 * @param L 链表表头
 * @param n 待删除的节点，倒数第n个元素。
 * @return Node* 返回链表的头节点
 */
Node *Delete_Node_Last_n(Node *L, int n)
{
    //题目要求返回头节点事实上没有这个必要
    //进入函数之前已经检测过了，元素的个数一定是大于等于n的，及要删除的元素一定存在
    Node *p, *q;
    p = L;
    q = L;
    while (n-- && p != NULL)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        return NULL;
    }
    while (p->next != NULL)
    {
        p = p->next;
        q = q->next;
    }                  //移动完成后，要删除的节点即为q的后继，此时p空闲
    p = q->next;       // p即为要删除的节点
    q->next = p->next; //要删除节点p的后继接到q后，变为q的后继
    free(p);
    return L;
}

/**
 * @brief Create a Palindrome LinkList object
 * 由一个普通的链表生成回文链表
 * @param L 普通的链表，基准
 * @return Node* 返回链表的头节点
 */
Node *create_Palindrome_LinkList(Node *L)
{
    //由一个普通的链表生成回文链表，最后一个元素也进行复制
    if (L == NULL || L->next == NULL)
        return L;
    int data[MAX_SIZE] = {0};
    int i;
    Node *p = L, *pnew;
    for (i = 0; p->next != NULL; i++)
    {
        //从第一个元素开始，如果下一个元素不是空，就往后移动并读出data
        p = p->next;
        data[i] = p->data;
    }
    //因为循环出来i指向最后一个数据的下一个数据
    for (i--; i >= 0; i--)
    {
        pnew = (Node *)malloc(sizeof(Node)); //申请空间
        pnew->data = data[i];                //数据域赋值
        pnew->next = p->next;                // p是最后一个节点,而p–> next是最后一个节点的后继,pnew是新节点。
        p->next = pnew;                      //将pnew接到p后面。
        p = pnew;                            //将p后以至最后。
    }
    return L;
}

/**
 * @brief 判断一个链表是否为回文链表
 *
 * @param head 待判断的链表
 * @return int 是回文链表返回1，否则返回0
 */
int is_Palindrome_LinkList(Node *head)
{
    if (head == NULL || head->next == NULL)
        return 1; //认为空链表是回文链表
    Node *slowPointer = head, *fastPointer = head;
    while (fastPointer->next != NULL && fastPointer->next->next != NULL)
    {
        slowPointer = slowPointer->next;       //慢指针移动一次
        fastPointer = fastPointer->next->next; //快指针移动两次
    }
    fastPointer = slowPointer->next; //中间元素或中间的右侧第一个元素
    slowPointer->next = NULL;        //结束前半部分
    slowPointer = head->next;        //并使前半部回到第一个节点
    fastPointer = add_LinkList_header(fastPointer);
    fastPointer = reverse_LinkList(fastPointer)->next; //并使后半部回到第一个节点
    while (slowPointer != NULL)
    {
        if (slowPointer->data != fastPointer->data)
        {
            return 0; //出现一个不相同的元素就证明不是回文链表。
        }
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next;
    }
    //执行到这一块了，证明后面一部分与前面分别对应相等。
    return 1;
}

/**
 * @brief 给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。
 * 函数无返回值，在原来链表的基础上进行修改
 * @param head
 */
void pairwise_interchange(Node *head)
{
    if (head == NULL || head->next == NULL)
        return;
    Node *ptr = head, *pr = head->next;
    while (pr != NULL && pr->next != NULL)
    {
        Node *pl = pr; //记录pl的位置
        pr = pr->next; // pr右移
        // printf("\n%d", pr->data);
        pl->next = pr->next; //与后边接起来
        pr->next = pl;       //左边移到右边
        ptr->next = pr;      //右边移到左边
        ptr = pl;            //左边跟过来,此处的pl其实是右边的节点
        pr = ptr->next;      // pr右移
    }
}

/**
 * @brief 分割链表：给定一个头结点为root的链表,
 将链表分隔为k个连续的部分。
 每部分的长度应该尽可能的相等: 任意两部分的长度差距不能超过1，也就是说可能有些部分为null。
 这k个部分应该按照在链表中出现的顺序进行输出，
 并且排在前面的部分的长度应该大于或等于后面的长度。
 返回一个符合上述规则的链表的列表。
 * @param root 待分割链表的表头
 * @param k 分隔部分
 * @return 链表的列表
 */
ListNode *split_LinkList_To_Parts(Node *root, int k)
{
    //变量声明
    ListNode *head, *p, *q;
    int length, length_per, extra_parts_num;
    int i, j;
    /*
    Node* head, * p;
    head  = (Node*)malloc(sizeof(Node));
       //创建单链表的表头结点head
    for (i = 0; i < size; i++)
    {
        data = rand();						//生成数据，完全随机
        q = (Node*)malloc(sizeof(Node)); //申请空间
        q->data = data;						//数据域赋值
        q->next = p->next;					//p是最后一个节点,而p–> next是最后一个节点的后继,q是新节点。
        p->next = q;						//将q接到p后面。
        p = q;								//将p后以至最后。
    }
    */
    //初始化
    head = p = (ListNode *)malloc(sizeof(ListNode)); //创建链表的表头结点head
    p->next = NULL;
    length = length_LinkList(root); //计算链表的长度
    length_per = length / k;        //计算分隔后每部分的长度
    extra_parts_num = length % k;   //计算额外多出一个节点的有几部分
    for (i = 0; i < k; i++)
    {
        Node *part_list, *p_part_list, *q_part_list;
        part_list = p_part_list = (Node *)malloc(sizeof(ListNode)); //创建链表的表头结点head
        p_part_list->next = NULL;
        for (j = 0; j < length_per + ((i < extra_parts_num) ? 1 : 0); j++)
        {
            int data;
            // p_part_list = (Node*)malloc(sizeof(Node));★★★★★★★★★★
            q_part_list = (Node *)malloc(sizeof(Node));
            if (root->next != NULL)
            {
                root = root->next;
                data = root->data;
                q_part_list = (Node *)malloc(sizeof(Node));
                q_part_list->data = data;
                q_part_list->next = p_part_list->next;
                // printf("%d\t", q_part_list->data);//调试语句，至此程序正常运行
                p_part_list->next = q_part_list;
                // print_LinkList("cs",p_part_list);
                p_part_list = q_part_list;
            }
        }
        q = (ListNode *)malloc(sizeof(ListNode));
        q->data = part_list;
        q->next = p->next;
        p->next = q;
        p = q;
    }
    return head;
}

/**
 * @brief 约瑟夫环问题
 * @param n 总人数
 * @param m 被杀死报数
 * @param sequence 被杀害的顺序
 * @return int 最后的幸运儿
 */
int JosephusProblemSolution(int n, int m, Node *sequence)
{
    Node *all_people;
    Node *p, *q;
    int i;
    all_people = create_LinkList_IntIncrease_circle(n);
    // print_LinkList("",all_people);
    all_people = all_people->next;         //移动到第一个节点
    while (all_people->next != all_people) //不是只剩一个元素了
    {
        for (i = 1; i < m - 1; i++)
            all_people = all_people->next;
        p = all_people;
        q = all_people->next;
        all_people = q->next; //报数序列移动到杀掉的人之后
        p->next = q->next;    //将q脱离出来
        sequence->next = q;   //添加的被杀掉的序列中
        sequence = q;
    }
    sequence->next = NULL; //将顺序序列结尾
    //只剩一个元素了，就是幸运儿。
    return all_people->data;
}

/**
 * @brief 主函数，程序的入口
 *
 * @return int
 */
int main()
{
    //变量声明区
    int n = 0;
    Node *la, *lb, *lc;

    //初始化随机数种子
    srand((unsigned int)time(NULL));

    printf("（1）假设两个按元素值递增有序排列的线性表A和B，均以单链表作为存储结构，请编写算法，将A表和B表归并成一个按元素值递减有序的排列的线性表C，并要求利用原表（即A表和B表的）结点空间存放表C。\n");
    la = create_LinkList_randIntIncrease_tail(rand() % MAX_SIZE_1 + 1);
    lb = create_LinkList_randIntIncrease_tail(rand() % MAX_SIZE_1 + 1);
    print_LinkList("A", la);
    print_LinkList("B", lb);
    la = reverse_LinkList(la);
    lb = reverse_LinkList(lb);
    lc = Merge_LinkList(la, lb);
    print_LinkList("C", lc);
    printf("\n");

    printf("（2）已知一个单链表，以第一个元素为基准，将小于该元素的结点全部放到前面，大于该结点的元素全部放到后面。不能申请新空间。\n");
    la = create_LinkList_randInt_tail(rand() % MAX_SIZE_1 + MIN_SIZE);
    print_LinkList("原链表", la);
    moveLinkListByFirstData(la);
    print_LinkList("操作后", la);
    printf("\n");

    printf("（3）编写一个程序，找到两个单链表相交的起始节点。\n");
    la = create_LinkList_randIntIncrease_tail(rand() % MAX_SIZE_1 + MIN_SIZE);
    lb = create_LinkList_randIntIncrease_tail(rand() % MAX_SIZE_1 + MIN_SIZE);
    if (isProbability(90)) //随机链接9成概率
    {
        intersect_LinkList_mayLoseElements(la, lb);
    }
    print_LinkList("A", la);
    print_LinkList("B", lb);
    if ((lc = getIntersectionNode(la, lb)) == NULL)
    {
        printf("链表A与链表B不相交。\n");
    }
    else
    {
        printf("链表A与链表B相交，");
        print_LinkList("相交的部分", lc);
    }
    printf("\n");

    printf("（4）给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。\n");
    la = create_LinkList_randInt_head_maySameData(rand() % MAX_SIZE_1 + MIN_SIZE);
    print_LinkList("删除前", la);
    Delete_Node_orderSameValue(la);
    print_LinkList("删除后", la);
    printf("\n");

    printf("（5）给定一个链表，删除链表的倒数第n个节点，并且返回链表的头结点。\n");
    la = create_LinkList_randIntIncrease_tail(rand() % MAX_SIZE_1 + MIN_SIZE);
    print_LinkList("删除前", la);
    n = length_LinkList(la); //虽然这里计算了链表的长度，但是删除函数并未用到，只是为了避免删除的节点不存在
    n = rand() % n + 1;
    printf("删除倒数第%d个节点\n", n);
    lb = Delete_Node_Last_n(la, n);
    if (lb == NULL)
    {
        printf("要删除的节点不存在\n");
    }
    else
    {
        print_LinkList("删除后", lb);
    }
    printf("\n");

    printf("（6）判断一个链表是否为回文链表。\n");
    if (isProbability(80)) //随机生成回文链表8成概率
    {
        //先生成一个稍微短一些的普通链表
        lb = create_LinkList_randInt_tail((rand() % MAX_SIZE_1 + MIN_SIZE) / 2);
        //然后将其回文化
        la = create_Palindrome_LinkList(lb);
    }
    else
    {
        //生成非回文链表
        la = create_LinkList_randInt_head(rand() % MAX_SIZE_1 + MIN_SIZE);
    }
    print_LinkList("A", la);
    printf("链表A%s回文链表.\n", is_Palindrome_LinkList(la) ? "是" : "不是");
    printf("\n");

    printf("（7）给定一个链表，两两交换其中相邻的节点，并返回交换后的链表。注意：不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。\n");
    la = create_LinkList_randInt_head(rand() % MAX_SIZE_1 + MIN_SIZE);
    print_LinkList("交换前", la);
    pairwise_interchange(la);
    print_LinkList("交换后", la);
    printf("\n");

    printf("（8）分割链表：给定一个头结点为root的链表, 编写一个函数以将链表分隔为k个连续的部分。每部分的长度应该尽可能的相等: 任意两部分的长度差距不能超过1，也就是说可能有些部分为null。这k个部分应该按照在链表中出现的顺序进行输出，并且排在前面的部分的长度应该大于或等于后面的长度。返回一个符合上述规则的链表的列表。\n");
    la = create_LinkList_randInt_tail(rand() % MAX_SIZE_1 + MIN_SIZE); //创建一个链表la，即题目要求的root
    print_LinkList("Root", la);
    n = rand() % MAX_SIZE_1 + MIN_SIZE;
    printf("分割成%d部分,", n);
    print_LinkList2(split_LinkList_To_Parts(la, n));
    printf("\n");

    printf("（9）实现约瑟夫环问题。(设总数为41，报3则删除)\n");
    la = create_LinkList_randInt_head(0); //此处的la为sequence
    n = JosephusProblemSolution(41, 3, la);
    print_LinkList("被杀掉的顺序", la);
    printf("最后的幸运儿是：%d\n", n);
    printf("\n");
    // Done.
    return 0;
}
