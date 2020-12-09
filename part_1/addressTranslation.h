//Logical to Physical Translation functions
int get_frameOffset(int logical_address)
{
    return logical_address & 0xff;
}

int get_page(int logical_address)
{
    return (logical_address & 0xff00) >> 8;
}

int extractLogicalAddress(int logical_address)
{
    int laddress = (get_page(logical_address) << 8) | get_frameOffset(logical_address);
    return laddress;
}

int makePhysicalAddress(int frame, int offset)
{
    int paddress = (frame << 8) | offset;
    return paddress;
}