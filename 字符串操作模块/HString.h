#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define NUMBER_START 48
#define BIG_START 65
#define SMALL_START 97
#define START 33
#define LAST 92

typedef struct ch
{
    char ch;
    struct ch *next;
} Char;

typedef struct
{
    Char *head;
    Char *tail;
    long length;
} HString;

typedef struct ss
{
    HString *s;
    int count;
    struct ss *next;
} HStrings;

void op(Char *l);

Char *get_line_to_charlist();

Char *char_create();

HString *str_create();

void _insert_char(Char *c, char ch);

Char *_reverse_char(Char *head);

long _to_char_list(char *str, Char *list);

long len_char_list(Char *list);

Char *get_list_end(Char *list);

int str_assign_charlist(HString *s, Char *list);

int str_assign(HString *s, char *value);

int str_insert_charlist(HString *s, long position, Char *list);

HString *str_rearrangement(HString *s);

HString *str_cat(HString *a, HString *b);

char *to_string(HString *hs);

int get_long_word(HString *s, HString *long_word);

int get_short_word(HString *s, HString *short_word);

HString *bignumber_create(int n);

HString *word_create();

int str_cmp(HString *a, HString *b);

int _cmp_char(Char *a, Char *b);

long str_long(HString *a, HString *b);

long _long_char(Char *a, Char *b);

long str_short(HString *a, HString *b);

long _short_char(Char *a, Char *b);

HStrings *get_short_words(HString *s);

HStrings *get_long_words(HString *s);

HStrings *hss_create();

void hss_insert(HStrings *hss, HString *s);

void hss_insert_charlist(HStrings *hss, Char *list);

void hss_insert_charlist_tail(HStrings *hss, Char *list, int count);

char *rearrangement(Char *list);

char *double_to_string(double number, int precision);

HString *big_number_add(HString *a, HString *b);

Char *big_number_f(Char *s);

void _mul10(HString *hs, int n);

HString *str_cpy(HString *s);

HString *big_number_mul(HString *a, HString *b);

long find_max_sub_string(HString *s, HString *sub);

HStrings *to_suffix_list(HString *s);

HStrings *_reverse_hss(HStrings *hss);

void sort_suffix_list(HStrings *s);

long cmp_len(HString *a, HString *b);
