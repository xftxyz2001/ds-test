#include "HString.h"

/// <summary>
/// DEBUG
/// </summary>
/// <returns></returns>

void op(Char *l)
{
    while (l = l->next)
    {
        printf("%c", l->ch);
    }
    printf("\n");
}

Char *get_line_to_charlist()
{
    char c;
    Char *list = char_create();
    Char *list_head = list;
    list->next = NULL;
    while ((c = _getche()) != 13)
    {
        _insert_char(list, c);
        list = list->next;
    }
    // printf("end");
    return list_head;
}

Char *char_create()
{
    return (Char *)malloc(sizeof(Char));
}

void _insert_char(Char *c, char ch)
{
    Char *temp = char_create();
    temp->ch = ch; //创建新的节点并赋值
    temp->next = c->next;
    c->next = temp;
}

Char *_reverse_char(Char *head)
{
    Char *p1 = head->next; //指向第一个元素
                           // printf("aaa");
    if (p1->next == NULL)  //如果传入表只有一个节点
    {
        // printf("bbb");
        head->next = p1;
        return head;
    }
    // printf("ccc");
    Char *p2 = p1->next; //传入的表至少含有两个元素
    p1->next = NULL;
    while (p2->next != NULL) //如果还存在后继
    {
        Char *p3 = p2->next; //将本节点后继保存下来
        p2->next = p1;       //将本节点的上一个节点改为本节点的后继
        p1 = p2;             // p1后移指向本节点
        p2 = p3;             //本节点后移指向本节点的后继
    }
    p2->next = p1; //如果p2是最后一个节点了，那么直接将p2的后继改为上一个节点，此时p2即为新链表的表头
    head->next = p2;
    return head;
}

HString *str_create()
{
    HString *s = (HString *)malloc(sizeof(HString));
    s->tail = char_create();
    s->tail->next = NULL;
    s->head = s->tail;
    s->length = 0;
    return s;
}

/// <summary>
/// 将一个字符串转为链表
/// </summary>
/// <param name="str"></param>
/// <param name="head"></param>
/// <returns>链表长度</returns>
long _to_char_list(char *str, Char *list)
{
    long len = 0;
    list->next = NULL;
    while (*str != '\0')
    {
        _insert_char(list, *str);
        list = list->next;
        str++;
        len++;
    }
    return len;
}

long len_char_list(Char *list)
{
    long len = 0;
    while ((list = list->next) != NULL)
    {
        len++;
    }
    return len;
}

Char *get_list_end(Char *list)
{
    while (list->next != NULL)
    {
        list = list->next;
    }
    return list;
}

int str_assign_charlist(HString *s, Char *list)
{
    if (s == NULL || s->length != 0)
    {
        *s = *str_create();
    }
    s->length += len_char_list(list);
    // printf("%d", s->length);
    s->tail->next = list->next;
    s->tail = get_list_end(list);
    return 1;
}

int str_assign(HString *s, char *value)
{
    if (s == NULL || s->length != 0)
    {
        *s = *str_create();
    }
    long len = 0;
    Char *list = char_create();
    s->length += _to_char_list(value, list);
    s->tail->next = list->next;
    s->tail = get_list_end(list);
    return 1;
}

int str_insert_charlist(HString *s, long position, Char *list)
{
    if (s == NULL)
    {
        *s = *str_create();
    }
    if (position < 0)
    {
        position = 0;
    }
    if (position > s->length)
    {
        position = s->length;
    }

    return 0;
}

HString *str_rearrangement(HString *s)
{
    HString *hb, *hs, *hn, *ho;
    hb = str_create();
    hs = str_create();
    hn = str_create();
    ho = str_create();
    Char *list = s->head;
    Char *lbh, *lb = char_create(); //其实可以用数组的，但是没必要
    lbh = lb;
    Char *lsh, *ls = char_create();
    lsh = ls;
    Char *lnh, *ln = char_create();
    lnh = ln;
    Char *loh, *lo = char_create();
    loh = lo;
    lb->next = NULL;
    ls->next = NULL;
    ln->next = NULL;
    lo->next = NULL;
    while (list->next != NULL)
    {
        list = list->next;
        if (list->ch >= BIG_START && list->ch < BIG_START + 26)
        {
            _insert_char(lb, list->ch);
            lb = lb->next;
        }
        else if (list->ch >= SMALL_START && list->ch < SMALL_START + 26)
        {
            _insert_char(ls, list->ch);
            ls = ls->next;
        }
        else if (list->ch >= NUMBER_START && list->ch < NUMBER_START + 10)
        {
            _insert_char(ln, list->ch);
            ln = ln->next;
        }
        else
        {
            _insert_char(lo, list->ch);
            lo = lo->next;
        }
    }
    str_assign_charlist(hb, lbh);
    str_assign_charlist(hs, lsh);
    str_assign_charlist(hn, lnh);
    str_assign_charlist(ho, loh);

    str_cat(hb, hs);
    str_cat(hb, hn);
    str_cat(hb, ho);
    return hb;
}

HString *str_cat(HString *a, HString *b)
{
    if (b->length == 0)
    {
        return a;
    }
    a->tail->next = b->head->next;
    a->tail = b->tail;
    a->length = a->length + b->length;
    return a;
}

char *to_string(HString *hs)
{
    char *res = malloc(sizeof(char) * (hs->length + 1));
    char *p = res;
    Char *lp = hs->head;
    while (lp->next != NULL)
    {
        lp = lp->next;
        *p++ = lp->ch;
    }
    *p = '\0';
    return res;
}

int get_long_word(HString *s, HString *long_word)
{
    int count = 0;
    Char *s_list = char_create();
    Char *lw = char_create();
    Char *temp = char_create();
    Char *temp_head = temp;
    lw->next = NULL;
    temp->next = NULL;
    s_list = s->head;
    // printf("\\\\");
    while (s_list->next != NULL)
    {
        s_list = s_list->next;
        // printf("%c", s_list->ch);
        if (s_list->ch == ' ')
        {
            // printf("///");
            // op(lw);
            // op(temp_head);
            if (_long_char(lw, temp_head) == 0)
            {
                count++;
            }
            else if (_long_char(lw, temp_head) < 0)
            {
                lw = temp_head;
                count = 1;
            }
            temp = char_create();
            temp_head = temp;
            // lw->next = NULL;
            temp->next = NULL;
        }
        else
        {
            _insert_char(temp, s_list->ch);
            // printf("%c", s_list->ch);
            temp = temp->next;
        }
    }
    HString *tmp = str_create();
    str_assign_charlist(tmp, lw);
    str_cat(long_word, tmp);
    return count;
}

int get_short_word(HString *s, HString *short_word)
{
    int count = 0;
    int flag = 1;
    Char *s_list = char_create();
    Char *lw = char_create();
    Char *temp = char_create();
    Char *temp_head = temp;
    lw->next = NULL;
    temp->next = NULL;
    s_list = s->head;
    // printf("\\\\");
    while (s_list->next != NULL)
    {
        s_list = s_list->next;
        // printf("%c", s_list->ch);
        if (s_list->ch == ' ')
        {
            // printf("//1/:");
            // op(lw);
            // printf("//2/:");
            // op(temp_head);
            if (flag)
            {
                lw = temp_head;
                count = 1;
                flag = 0;
            }
            if (_short_char(lw, temp_head) == 0)
            {
                count++;
            }
            else if (_short_char(lw, temp_head) > 0)
            {
                lw = temp_head;
                // printf("///");
                // op(lw);
                count = 1;
            }
            temp = char_create();
            temp_head = temp;
            // lw->next = NULL;
            temp->next = NULL;
        }
        else
        {
            _insert_char(temp, s_list->ch);
            // printf("%c", s_list->ch);
            temp = temp->next;
        }
    }
    // printf("///");
    HString *tmp = str_create();
    str_assign_charlist(tmp, lw);
    str_cat(short_word, tmp);
    return count;
}

/*
int get_short_word(HString* s, HString* short_word)
{
    int count = 0;
    return 0;
}*/

HString *bignumber_create(int n)
{
    HString *hs = str_create();
    Char *list = char_create();
    Char *list_head = list;
    list->next = NULL;
    for (int i = 0; i < n; i++)
    {
        int num = rand() + 1;
        while (num)
        {
            _insert_char(list, (num % 10) + '0');
            list = list->next;
            num /= 10;
        }
    }
    list_head = _reverse_char(list_head); //
    str_assign_charlist(hs, list_head);
    return hs;
}

HString *word_create()
{
    char *dic[190] = {
        "foot ", "head ", "face ", "hair ", "nose ", "mouth ", "eye ", "ear ", "arm ", "hand ", "finger ", "leg ", "tail ",
        "red ", "blue ", "yellow ", "green ", "white ", "black ", "pink ", "purple ", "orange ", "brown ",
        "pen ", "pencil ", "case ", "ruler ", "book ", "bag ", "comicbook ", "postcard ", "newspaper ", "schoolbag ",
        "eraser ", "crayon ", "sharpener ", "story ", "book ", "notebook ", "Chinesebook ", "Englishbook ",
        "mathbook ", "magazine ", "dictionary ", "cat ", "dog ", "pig ", "duck ", "rabbit ", "horse ", "elephant ",
        "ant ", "fish ", "bird ", "eagle ", "beaver ", "snake ", "mouse ", "squirrel ", "kangaroo ", "monkey ", "panda ",
        "bear ", "lion ", "tiger ", "fox ", "zebra ", "deer ", "giraffe ", "goose ", "hen ", "turkey ", "lamb ", "sheep ",
        "goat ", "cow ", "donkey ", "squid ", "lobster ", "shark ", "seal ", "spermwhale ", "killerwhale ", "friend ",
        "boy ", "girl ", "mother ", "father ", "sister ", "brother ", "uncle ", "man ", "woman ", "Mr. ", "Miss ",
        "lady ", "mom ", "dad ", "parents ", "grandparents ", "grandma ", "grandmother ", "grandpa ", "grandfather ",
        "aunt ", "cousin ", "son ", "daughter ", "baby ", "kid ", "classmate ", "queen ", "visitor ", "neighbor ",
        "principal ", "universitystudent ", "penpal ", "tourist ", "people ", "robot ", "rice ", "bread ", "beef ",
        "milk ", "water ", "egg ", "fish ", "tofu ", "cake ", "hotdog ", "hamburger ", "Frenchfries ", "cookie ",
        "biscuit ", "jam ", "noodles ", "meat ", "chicken ", "pork ", "mutton ", "vegetable ", "salad ", "soup ",
        "ice ", "icecream ", "coke ", "juice ", "tea ", "coffee ", "breakfast ", "lunch ", "dinner ", "supper ",
        "meal ", "teacher ", "student ", "doctor ", "nurse ", "driver ", "farmer ", "singer ", "writer ", "actor ",
        "actress ", "artist ", "TVreporter ", "engineer ", "accountant ", "policeman ", "salesperson ",
        "cleaner ", "baseballplayer ", "salesclerk ", "police ", "apple ", "banana ", "pear ", "orange ",
        "watermelon ", "grape ", "eggplant ", "greenbeans ", "tomato ", "potato ", "peach ", "strawberry ",
        "cucumber ", "onion ", "carrot ", "cabbage "};
    HString *hs = str_create();
    // printf("%s", dic[1]);
    str_assign(hs, dic[rand() % 190]);
    // printf("aaa");
    return hs;
}

int str_cmp(HString *a, HString *b)
{
    return _cmp_char(a->head, b->head);
}

int _cmp_char(Char *a, Char *b)
{
    while (a->next != NULL && b->next != NULL)
    {
        a = a->next;
        b = b->next;
        if (a->ch != b->ch)
        {
            return a->ch - b->ch;
        }
    }
    if (a->next == NULL && b->next == NULL)
    {
        return 0;
    }
    // else if (a->next = NULL)
    else if (a->next == NULL)
    {
        return -(b->ch);
    }
    else
    {
        return a->ch;
    }
}

long str_long(HString *a, HString *b)
{
    return _long_char(a->head, b->head);
}

long _long_char(Char *a, Char *b)
{
    long len;
    len = len_char_list(a) - len_char_list(b);
    if (len == 0)
    {
        return _cmp_char(a, b) == 0 ? 0 : 1;
    }
    return len;
}

long str_short(HString *a, HString *b)
{
    return _long_char(a->head, b->head);
}

long _short_char(Char *a, Char *b)
{
    long len;
    len = len_char_list(a) - len_char_list(b);
    if (len == 0)
    {
        return _cmp_char(a, b) == 0 ? 0 : -1;
    }
    return len;
}

HStrings *get_short_words(HString *s)
{
    HStrings *hss = hss_create();
    Char *s_list = char_create();
    Char *temp = char_create();
    Char *temp_head = temp;
    temp->next = NULL;
    s_list = s->head;
    while (s_list->next != NULL)
    {
        s_list = s_list->next;
        if (s_list->ch == ' ')
        {
            if (hss->count == 0 || len_char_list(temp_head) == hss->count)
            {
                hss_insert_charlist(hss, temp_head);
            }
            else if (len_char_list(temp_head) < hss->count)
            {
                hss = hss_create();
                hss_insert_charlist(hss, temp_head);
            }
            temp = char_create();
            temp_head = temp;
            temp->next = NULL;
        }
        else
        {
            _insert_char(temp, s_list->ch);
            temp = temp->next;
        }
    }
    return hss;
}

HStrings *get_long_words(HString *s)
{
    HStrings *hss = hss_create();
    Char *s_list = char_create();
    Char *temp = char_create();
    Char *temp_head = temp;
    temp->next = NULL;
    s_list = s->head;
    while (s_list->next != NULL)
    {
        s_list = s_list->next;
        if (s_list->ch == ' ')
        {
            if (hss->count == 0 || len_char_list(temp_head) == hss->count)
            {
                hss_insert_charlist(hss, temp_head);
            }
            else if (len_char_list(temp_head) > hss->count)
            {
                hss = hss_create();
                hss_insert_charlist(hss, temp_head);
            }
            temp = char_create();
            temp_head = temp;
            temp->next = NULL;
        }
        else
        {
            _insert_char(temp, s_list->ch);
            temp = temp->next;
        }
    }
    return hss;
}

HStrings *hss_create()
{
    HStrings *hss = (HStrings *)malloc(sizeof(HStrings));
    hss->count = 0; //创建的时候让头节点的count为0，插入过值之后更改为链表系列字符串长度
    hss->next = NULL;
    return hss;
}

void hss_insert(HStrings *hss, HString *s)
{
    if (hss->next == NULL) //证明是空的
    {
        hss->count = s->length;
    }
    while (hss->next != NULL)
    {
        hss = hss->next;
        if (str_cmp(hss->s, s) == 0)
        {
            hss->count++;
            return;
        }
    }
    //到这里没返回一定是新的单词
    HStrings *hss_new_node = (HStrings *)malloc(sizeof(HStrings));
    hss_new_node->count = 1;
    hss_new_node->s = s;
    hss_new_node->next = hss->next;
    hss->next = hss_new_node;
}

void hss_insert_charlist(HStrings *hss, Char *list)
{
    HString *hs = str_create();
    str_assign_charlist(hs, list);
    hss_insert(hss, hs);
}

void hss_insert_charlist_tail(HStrings *hss, Char *list, int count)
{
    HString *hs = str_create();
    str_assign_charlist(hs, list);
    HStrings *hss_new_node = (HStrings *)malloc(sizeof(HStrings));
    hss_new_node->count = count;
    hss_new_node->s = hs;
    while (hss->next != NULL)
    {
        hss = hss->next;
    }
    hss_new_node->next = hss->next;
    hss->next = hss_new_node;
}

char *rearrangement(Char *list)
{
    HString *hs = str_create();
    str_assign_charlist(hs, list);
    hs = str_rearrangement(hs);
    return to_string(hs);
}

/// <summary>
/// 浮点数转字符串
/// </summary>
/// <param name="number">待转化的数字</param>
/// <param name="precision">精度：保留小数点的位数</param>
/// <returns></returns>
char *double_to_string(double number, int precision)
{
    int integer = (int)number;
    double tail = number - integer;
    HString *hs = str_create();
    Char *list_inte = char_create();
    Char *list = list_inte;
    list_inte->next = NULL;
    while (integer)
    {
        _insert_char(list_inte, (integer % 10) + '0');
        list_inte = list_inte->next;
        integer /= 10;
    }
    list = _reverse_char(list); //
    list_inte = get_list_end(list);
    _insert_char(list_inte, '.');
    list_inte = list_inte->next;
    while (precision--)
    {
        tail *= 10;
        integer = (int)tail;
        tail -= integer;
        _insert_char(list_inte, integer + '0');
        list_inte = list_inte->next;
    }
    // op(list);
    str_assign_charlist(hs, list);
    // op(hs->head);
    return to_string(hs);
}

int _is0(Char *num_list)
{
    while (num_list = num_list->next)
    {
        if (num_list->ch != '0')
        {
            return 0;
        }
    }
    // printf("aaa");
    return 1;
}

HString *big_number_add(HString *a, HString *b)
{
    HString *res = str_create();
    Char *a_list = a->head;
    Char *b_list = b->head;
    Char *a_list_head;
    Char *a_list_temp;
    Char *b_list_temp;
    /*printf("\n");
    op(a_list);
    op(b_list);*/
    if (a->length < b->length)
    {
        Char *ttt = b_list;
        b_list = a_list;
        a_list = ttt;
    }
    a_list = _reverse_char(a_list);
    b_list = _reverse_char(b_list);
    a_list_head = a_list; //最终结果的头
    while (!_is0(b_list))
    {
        /*printf("\nb:");
        op(b_list);
        printf("\na:");
        op(a_list_head);*/
        b_list_temp = b_list;
        a_list_temp = a_list;
        while (b_list_temp->next != NULL)
        {
            b_list_temp = b_list_temp->next;
            /*if (b_list_temp->ch == '0')
            {

                continue;//不需要加
            }*/
            if (a_list_temp->next == NULL)
            {
                Char *new_temp = char_create();
                new_temp->ch = '0';
                new_temp->next = a_list_temp->next;
                a_list_temp->next = new_temp;
            }
            a_list_temp = a_list_temp->next;
            char a_list_ch_temp = a_list_temp->ch;
            a_list_temp->ch = (((b_list_temp->ch - '0') + (a_list_ch_temp - '0')) % 10) + '0'; //本位
            b_list_temp->ch = (((b_list_temp->ch - '0') + (a_list_ch_temp - '0')) / 10) + '0'; //进位
        }
        if (a_list->next != NULL)
        {
            a_list = a_list->next;
        }
    }
    // printf("\na:");
    // op(a_list_head);
    a_list_head = _reverse_char(a_list_head);
    a_list_head = big_number_f(a_list_head);
    str_assign_charlist(res, a_list_head);
    return res;
}

Char *big_number_f(Char *s)
{
    if (_is0(s))
    {
        return s;
    }
    while (s->next != NULL)
    {
        if (s->next->ch != '0')
        {
            return s;
        }
        s = s->next;
    }
    return s;
}

void _mul10(HString *hs, int n)
{
    while (n--)
    {
        _insert_char(hs->tail, '0');
        hs->tail = hs->tail->next;
        hs->length++;
    }
}

HString *str_cpy(HString *s)
{
    HString *hs;
    hs = str_create();
    str_assign(hs, to_string(s));
    return hs;
}

HString *big_number_mul(HString *a, HString *b)
{
    Char *z = char_create();
    z->next = NULL;
    _insert_char(z, '0');
    HString *sum = str_create();
    str_assign_charlist(sum, z);
    if (a->length < b->length)
    {
        HString *c = b;
        b = a;
        a = c;
    }
    Char *b_list = b->head;
    if (_is0(b_list))
    {
        return sum;
    }
    b_list = _reverse_char(b_list);
    while (b_list->next != NULL)
    {
        b_list = b_list->next;
        // printf("%c ", b_list->ch);
        int loop = b_list->ch - '0';
        for (int i = 0; i < loop; i++)
        {
            sum = big_number_add(str_cpy(sum), str_cpy(a));
        }
        _mul10(a, 1);
    }
    return sum;
}

long find_max_sub_string(HString *s, HString *sub)
{
    long max_len = 0;
    long max_pos = 0;
    HStrings *ss = to_suffix_list(s);
    // while (ss = ss->next)
    //	printf("(%ld)%s\n", ss->count, to_string(ss->s));
    sort_suffix_list(ss);
    /*{
        HStrings* ttt = ss;
        while (ttt = ttt->next)
            printf("(%ld)%s\n", ttt->count, to_string(ttt->s));
        printf("\n");
    }*/
    Char *temp_sub_string_list = char_create();
    while (ss = ss->next)
    {
        if (ss->next == NULL)
        {
            break;
        }
        if (cmp_len(ss->s, ss->next->s) >= max_len)
        {
            max_len = cmp_len(ss->s, ss->next->s);
            // max_pos = ss->count;
            max_pos = ss->next->count;
            temp_sub_string_list = ss->s->head;
        }
    }
    Char *temp = temp_sub_string_list;
    for (int i = 0; i < max_len; i++)
    {
        temp = temp->next;
    }
    temp->next = NULL;
    str_assign_charlist(sub, temp_sub_string_list);
    return max_pos;
}

HStrings *to_suffix_list(HString *s)
{
    long pos = 0;
    Char *s_list = char_create();
    HStrings *hss = hss_create();
    s_list = s->head;
    do
    {
        if (s_list->next == NULL)
        {
            break;
        }
        // op(s_list);
        hss_insert_charlist_tail(hss, s_list, pos++);
    } while (s_list = s_list->next);
    // printf("///");
    // while (hss = hss->next)
    //	printf("(%ld)%s\n", hss->count, to_string(hss->s));
    return hss;
}

HStrings *_reverse_hss(HStrings *head)
{
    HStrings *p1 = head->next; //指向第一个元素
                               // printf("aaa");
    if (p1->next == NULL)      //如果传入表只有一个节点
    {
        // printf("bbb");
        head->next = p1;
        return head;
    }
    // printf("ccc");
    HStrings *p2 = p1->next; //传入的表至少含有两个元素
    p1->next = NULL;
    while (p2->next != NULL) //如果还存在后继
    {
        HStrings *p3 = p2->next; //将本节点后继保存下来
        p2->next = p1;           //将本节点的上一个节点改为本节点的后继
        p1 = p2;                 // p1后移指向本节点
        p2 = p3;                 //本节点后移指向本节点的后继
    }
    p2->next = p1; //如果p2是最后一个节点了，那么直接将p2的后继改为上一个节点，此时p2即为新链表的表头
    head->next = p2;
    return head;
}

void sort_suffix_list(HStrings *ss) //
{
    // ss = _reverse_hss(ss);
    HStrings *p, *q, *min, *r;
    p = ss;
    /*{
        HStrings* ttt = ss;
        while (ttt = ttt->next)
            printf("(%ld)%s\n", ttt->count, to_string(ttt->s));
        printf("\n");
    }*/
    while (p->next != NULL)
    {
        min = p;
        q = p->next;
        // printf("/o");
        while (q->next != NULL)
        {
            // printf("/i");
            if (str_cmp(min->next->s, q->next->s) > 0)
            {
                min = q;
            }
            q = q->next;
        }
        if (min != p)
        {
            r = min->next;
            min->next = min->next->next;
            r->next = p->next;
            p->next = r;
        }
        p = p->next;
    }
    /*{
        HStrings* ttt = ss;
        while (ttt = ttt->next)
            printf("(%ld)%s\n", ttt->count, to_string(ttt->s));
        printf("\n");
    }*/
}

long cmp_len(HString *a, HString *b)
{
    if (a->length > b->length)
    {
        return 0;
    }
    long len = 0;
    Char *a_list = a->head;
    Char *b_list = b->head;
    while (a_list = a_list->next)
    {
        b_list = b_list->next;
        if (a_list->ch != b_list->ch)
        {
            return len;
        }
        len++;
    }
    return len;
}
