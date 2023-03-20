#include "syscall.h"
#define maxlen 32
int main()
{
    int len;
    char filename[maxlen + 1];
    char buf[32];
    /*Create a file*/
    int CloseStatus;
    int byteRead; // so byte thuc su doc duoc
    int OpenFileID = Open("text.txt", 0);
    if (OpenFileID != -1)
    {
        PrintString("Mo file thanh cong\n");
        // Write("Hello", 5, OpenFileID); // Lỗi không read xong write ngay được, chỉ read hoặc write được 1 lần duy nhất trong 1 ctrinh
        byteRead = Read(buf, 32, OpenFileID);
        PrintInt(byteRead);
        PrintString("\n");
        PrintString("Noi dung file la: \n");
        PrintString(buf);
        PrintString("\n");
        CloseStatus = Close(OpenFileID);
        if (CloseStatus == 0)
            PrintString("Dong file thanh cong\n");
    }
    Halt();
}
