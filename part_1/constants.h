#define PAGETABLESIZE 256
#define TOTALFRAMES 64
#define PAGESIZE 256
#define TOTALADDRESSES 10000
signed char **memory;
int address[TOTALADDRESSES];
int bit[TOTALADDRESSES];
int freeFrame = -1;
int total_page_faults = 0;
int total_access = 0;
