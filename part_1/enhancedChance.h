int getPageToSwap()
{
    //check for 0 0
    for (int i = 0; i < PAGETABLESIZE; i++)
    {
        if (count(i) == 0 && dirtybit(i) == 0 && frame(i) != 255)
            return i;
    }
    //check for 0 1 and reset count
    for (int i = 0; i < PAGETABLESIZE; i++)
    {
        if (count(i) == 0 && dirtybit(i) != 0 && frame(i) != 255)
            return i;
        resetCount(i);
    }
    //check for 0 0

    for (int i = 0; i < PAGETABLESIZE; i++)
    {
        if (count(i) == 0 && dirtybit(i) == 0 && frame(i) != 255)
            return i;
    }
    //check for 0 1
    for (int i = 0; i < PAGETABLESIZE; i++)
    {
        if (count(i) == 0 && dirtybit(i) != 0 && frame(i) != 255)
            return i;
    }
}

int allocateFrame(int pageno)
{
    int pageno1 = getPageToSwap(); //get page to swap

    int frameno = frame(pageno1); //get the frame to swap

    FILE *backingStore = fopen("BACKING_STORE_1.bin", "rb+");
    fseek(backingStore, pageno1 * PAGESIZE, SEEK_SET);

    fwrite(memory[frameno], 1, PAGESIZE, backingStore);
    fclose(backingStore);
    page_table[pageno1] = 255; //remove old frame

    return frameno;
}