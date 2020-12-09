#include "constants.h"

unsigned short page_table[PAGETABLESIZE];

//Page Table Functions
int frame(int pageno)
{
    return page_table[pageno] & 0xff;
}

int dirtybit(int pageno)
{
    return (page_table[pageno] >> 9) & 1;
}

int validbit(int pageno)
{
    return (page_table[pageno] >> 8) & 1;
}

int count(int pageno)
{
    return (page_table[pageno] >> 10) & 3;
}

void incCount(int pageno)
{
    if (count(pageno) == 3)
        return;

    unsigned short c = (count(pageno) + 1);

    unsigned short pe = page_table[pageno];

    pe = pe & ~(3 << 10);
    pe = pe | (c << 10);
    page_table[pageno] = pe;
}

void resetCount(int pageno)
{
    page_table[pageno] = page_table[pageno] & 0x3FF;
}

void setDirtybit(int pageno, int bit)
{
    if (bit == 0)
        page_table[pageno] = page_table[pageno] & ~(1 << 9);
    if (bit == 1)
        page_table[pageno] = page_table[pageno] | (bit << 9);
}

void setValidbit(int pageno, int bit)
{
    if (bit == 0)
        page_table[pageno] = page_table[pageno] & ~(1 << 8);
    if (bit == 1)
        page_table[pageno] = page_table[pageno] | (bit << 8);
}

void setFrame(int pageno, int frame)
{
    unsigned short off = ~(0xff) & page_table[pageno];
    page_table[pageno] = off | frame;
}

void printTable()
{
    printf("C D V F\n");
    for (int i = 0; i < PAGETABLESIZE; i++)
    {
        printf("%d %d %d %d\n", count(i), dirtybit(i), validbit(i), frame(i));
    }
}
