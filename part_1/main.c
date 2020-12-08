#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int *page_table;
int *frames;

void init()
{
    page_table = malloc(sizeof(int) * pow(2, 8));
}

int get_frameOffset(int logical_address)
{

    return logical_address & 0xff;
}

int get_page(int logical_address)
{
    return (logical_address & 0XFF00) >> 8;
}

int main()
{

    char *filename = "addresses.txt";
    int address[10], bit[10];
    FILE *file;
    file = fopen("addresses.txt", "r");
    for (int i = 0; i < 10; i++)
    {
        fscanf(file, "%d %d", &address[i], &bit[i]);
        printf("%d\n", address[i]);
        fflush(stdout);
    }

    fflush(stdout);
}
