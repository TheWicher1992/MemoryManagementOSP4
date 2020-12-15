#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "constants.h"
#include "pagetable.h"
#include "addressTranslation.h"
#include "enhancedChance.h"

void readAddresses(char *filename)
{

    FILE *file;

    file = fopen(filename, "r");
    for (int i = 0; i < TOTALADDRESSES; i++)
    {
        fscanf(file, "%X %d", &address[i], &bit[i]);
    }
}

void init(char *filename)
{
    readAddresses(filename);
    memory = (signed char **)malloc(sizeof(signed char *) * TOTALFRAMES);
    for (int i = 0; i < TOTALFRAMES; i++)
        memory[i] = (signed char *)malloc(sizeof(signed char) * PAGESIZE);

    for (int i = 0; i < PAGETABLESIZE; i++)
    {
        page_table[i] = 255;
    }

    // printTable();
}
int getFreeFrame();
void exec();

int main(int argc, char *argv[])
{
    init(argv[1]);
    exec();
}

void exec()
{
    printf("%s\t\t%s\t%s\t%s\t%s\n", "Logical", "Physical", "Read\\Write", "Value", "Page Fault");

    for (int i = 0; i < TOTALADDRESSES; i++)
    {
        total_access++;

        int logic_address = extractLogicalAddress(address[i]);
        int pageno = get_page(logic_address);
        int frame_off = get_frameOffset(logic_address);
        int physical_address = -1;
        char *rdwrt = bit[i] == 1 ? "Write" : "Read";
        char *fault;
        unsigned char value;
        int framen;

        if (validbit(pageno) == 1)
        {
            int frameno = frame(pageno);

            framen = frameno;
            physical_address = makePhysicalAddress(frameno, frame_off);
            fault = "NO";
            incCount(pageno);
            if (bit[i] == 1) //if write then set dirty flag
            {
                memory[frameno][frame_off] = memory[frameno][frame_off] / 2;
                setDirtybit(pageno, 1);
            }
            value = memory[frameno][frame_off];
        }
        else
        {
            total_page_faults++;
            incCount(pageno);
            int frameno = getFreeFrame();

            if (frameno < 0)
            {
                frameno = allocateFrame(pageno); //use page replacement algorithm
            }

            framen = frameno;
            physical_address = makePhysicalAddress(frameno, frame_off);
            setValidbit(pageno, 1);
            setFrame(pageno, frameno);
            fault = "YES";

            FILE *backingStore = fopen("BACKING_STORE_1.bin", "rb");
            fseek(backingStore, pageno * PAGESIZE, SEEK_SET);
            fread(memory[frameno], sizeof(signed char), PAGESIZE, backingStore);
            fclose(backingStore);

            if (bit[i] == 1) //IF Write then set dirtyflag
            {
                // printf("%x\n", memory[frameno][frame_off] >> 1);
                memory[frameno][frame_off] = memory[frameno][frame_off] / 2;
                setDirtybit(pageno, 1);
            }
            value = memory[frameno][frame_off];
        }

        printf("0x%x\t\t0x%x\t\t%s\t\t0x%x\t%s\n", logic_address, physical_address, rdwrt, value, fault);
    }

    float pageFaultRate = ((float)total_page_faults / (float)total_access) * 100.0;
    printf("Total Addresses Accessed: %d\nTotal Page Faults: %d\nPage Fault Rate: %f\n", total_access, total_page_faults, pageFaultRate);
}

int getFreeFrame()
{
    if (freeFrame == TOTALFRAMES - 1)
    {
        return -1;
    }

    return ++freeFrame;
}