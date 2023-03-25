#include "syscall.h"

int main()
{
    char bufferRecv[32];
    char bufferRead[32];
    char filename[32];
    char filename2[32];
    char *ip = "127.0.0.1";
    int port = 1234;
    int fileID, byteReadFile, byteSend, byteRecv, socketID, state = -1;
    int i;

    // for (i = 0; i < 1024; i++){
    //     bufferRecv[i] = 0;
    //     bufferRead[i] = 0;
    // }

    socketID = SocketTCP();
    PrintString("Please input the file you want to read: \n");
    ReadString(filename, 32);
    fileID = Open(filename, 0);
    byteReadFile = Read(bufferRead, 32, fileID);
    bufferRead[byteReadFile] = '\0';
    state = Connect(socketID, ip, port);
    if (state != -1){
        byteSend = Write(bufferRead, byteReadFile, socketID);
        //byteSend = Send(socketID, bufferRead, byteReadFile);
        //PrintInt(byteSend);
        byteRecv = Read(bufferRecv, byteSend, socketID);
        //byteRecv =  Receive(socketID, bufferRecv, byteSend);
        //PrintInt(state);
        Close(socketID);
    }
    Close(fileID);
    //PrintString(bufferRead);
    PrintString("Please input the file you want to write: \n");
    ReadString(filename2, 32);
    fileID = Open(filename2, 0);
    //PrintString(bufferRecv);
    Write(bufferRecv, byteRecv, fileID);
    Close(fileID);


    Halt();
}
