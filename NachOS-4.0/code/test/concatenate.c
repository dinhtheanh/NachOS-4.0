#include "syscall.h"
#include "copyright.h"

#define maxlen 32

int main(int argc, char* argv[]) {

    char src1fname[maxlen];
    char src2fname[maxlen];
    char desfname[maxlen];
    char buf[maxlen];
    char buf2[maxlen];
    int src1fid;
    int src2fid;
    int desfid;
    int readByte1;
    int readByte2;

    PrintString("Nhap ten file source 1: \n");
    ReadString(src1fname, maxlen);
    PrintString("Nhap ten file source 2: \n");
    ReadString(src2fname, maxlen);
    PrintString("Nhap ten file destination: \n");
    ReadString(desfname, maxlen);
    src1fid = Open(src1fname, 0);
    // desfid = Open(desfname, 0);

    if (src1fid == -1){
        PrintString("File source khong ton tai!\n");
        Halt();
    }
    else if (desfid == -1){
        PrintString("File destination khong ton tai! Dang tao file moi\n");
        Create(desfname);
        readByte1 = Read(buf, maxlen, src1fid);
        Close(src1fid);
        
    }
    else{
        readByte1 = Read(buf, maxlen, src1fid);
        //PrintInt(readByte1);
        //PrintString('\n');
        Close(src1fid);
    }
    src2fid = Open(src2fname, 0);

    if (src2fid == -1){
        PrintString("File source khong ton tai!\n");
        Halt();
    }
    else{
        readByte2 = Read(buf2, maxlen, src2fid);
        //PrintInt(readByte2);
        //PrintString('\n');
        Close(src2fid);   
    }
    desfid = Open(desfname,0);
    Write(buf,readByte1,desfid);
    Write(buf2,readByte2,desfid);
    Close(desfid);
    Halt();
    return 0;
}