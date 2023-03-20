#include "syscall.h"
#define maxlen 32
int main()
{
    char srcfname[maxlen];
    char desfname[maxlen];
    char buf[maxlen];
    int srcfid;
    int desfid;
    int readByte;

    PrintString("Nhap ten file source: \n");
    ReadString(srcfname, maxlen);
    PrintString("Nhap ten file destination: \n");
    ReadString(desfname, maxlen);
    srcfid = Open(srcfname, 0);
    desfid = Open(desfname, 0);
    if (srcfid == -1){
        PrintString("File source khong ton tai!\n");
        Halt();
    }
    else if (desfid == -1){
        PrintString("File destination khong ton tai! Dang tao file moi\n");
        Create(desfname);
        readByte = Read(buf, maxlen, srcfid);
        Write(buf, readByte, desfid);
        Close(desfid);
        Close(srcfid);
        PrintString("Copy thanh cong\n");
    }
    else{
        PrintString("Dang copy\n");
        PrintInt(srcfid);
        PrintString("\n");
        PrintInt(desfid);
        PrintString("\n");
        readByte = Read(buf, maxlen, srcfid);
        Write(buf, readByte, desfid);
        Close(desfid);
        Close(srcfid);
        PrintString("Copy thanh cong\n");
    }

    Halt();
}
