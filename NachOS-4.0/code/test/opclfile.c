#include "syscall.h"
#define maxlen 32
int
main()
{
    int len;
    char filename[maxlen + 1];
    /*Create a file*/
    int OpenFileID = Open("text.txt", 0);
    if (OpenFileID != -1)
        Close(OpenFileID);
    Halt();
} 
