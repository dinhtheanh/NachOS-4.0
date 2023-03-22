#include "syscall.h"

int main()
{
    char bufferRecv[5];
    char bufferRead[5];
    char filename[32];
    char filename2[32];
    char *ip = "127.0.0.1";
    int port = 1234;
    int fileID, byteReadFile, byteSend, byteRecv, socketID, state;
    int i = 0;

    // for (i; i < 1024; i++){
    //     bufferRecv[i] = 0;
    //     bufferRead[i] = 0;
    // }

    socketID = SocketTCP();
    PrintString("Please input the file you want to read: \n");
    ReadString(filename, 32);
    fileID = Open(filename, 0);
    byteReadFile = Read(bufferRead, 5, fileID);
    state = Connect(socketID, ip, port);
    if (state != -1){
        byteSend = Send(socketID, bufferRead, byteReadFile);
        byteRecv =  Receive(socketID, bufferRecv, byteSend);
        Close(socketID);
    }
    Close(fileID);
    PrintString(bufferRead);
    PrintString("Please input the file you want to read: \n");
    ReadString(filename2, 32);
    fileID = Open(filename2, 0);
    PrintString(bufferRecv);
    Write(bufferRecv, byteRecv, fileID);
    Close(fileID);


    Halt();
}
