#include "syscall.h"
int
main()
{
    char filename[32];
    
    ReadString(filename, 32);
    if (Create(filename) != -1){
        PrintString("Successfully create file!\n");
    }
    else{
        PrintString("Unable to create file!\n");
    }

    Halt();
    /* not reached */
}