#include "syscall.h"
#define maxlen 32
int
main()
{
    int len;
    char filename[maxlen + 1];
    /*Create a file*/
    if (Create("text.txt") == -1)
    {
    // xuất thông báo lỗi tạo tập tin
       // printf("Cannot create file!");
    }
    else
    {
    // xuất thông báo tạo tập tin thành công
       // printf("Create file successfully");
    }
    Halt();
} 