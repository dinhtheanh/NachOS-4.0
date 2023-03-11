#include "syscall.h"
int
main()
{
    char filename[32];
    ReadString(filename, 32);
    Create(filename);
    Halt();
    /* not reached */
}