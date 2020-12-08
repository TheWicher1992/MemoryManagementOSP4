//Logical to Physical Translation functions
int get_frameOffset(int logical_address)
{
    return logical_address & 0xff;
}

int get_page(int logical_address)
{
    return (logical_address & 0xff00) >> 8;
}
