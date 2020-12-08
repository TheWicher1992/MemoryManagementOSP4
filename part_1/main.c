#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "constants.h"
#include "pagetable.h"

char memory[TOTALFRAMES][PAGESIZE];
int address[TOTALADDRESSES];
int bit[TOTALADDRESSES];
int freeFrame[TOTALFRAMES];

void readAddresses()
{
    char *filename = "addresses.txt";

    FILE *file;

    file = fopen("addresses.txt", "r");
    for (int i = 0; i < TOTALADDRESSES; i++)
    {
        fscanf(file, "%x %d", &address[i], &bit[i]);
    }
}

void init()
{
    readAddresses();

    for (int i = 0; i < TOTALFRAMES; i++)
    {
        freeFrame[i] = 1;
    }

    for (int i = 0; i < PAGETABLESIZE; i++)
    {
        page_table[i] = 255;
    }

    printTable();
}

int main()
{
    init();
}
