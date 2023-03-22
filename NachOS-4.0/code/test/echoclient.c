#include "syscall.h"

int main()
{   
    //message
    char msg[12] = "hello server";
    char msg2[13] = "hello server2";
    char msg3[13] = "hello server3";
    char msg4[13] = "hello server4";
    //buffer
    char recvmsg[12];
    char recvmsg2[13];
    char recvmsg3[13];
    char recvmsg4[13];
    //IDs
    int id = SocketTCP();
    int id2 = SocketTCP();
    int id3 = SocketTCP();
    int id4 = SocketTCP();
    //server's information
    int port = 1234;
    char *server_ip = "127.0.0.1";
    //state to check connection is successful or not
    int state;
    int state2;
    int state3;
    int state4;
    int byteSent, byteRead;

    //Client 1
    state = Connect(id, server_ip, port);
    if (state != -1)
    {
        byteSent = Send(id, msg, sizeof(msg));
        byteRead = Receive(id, recvmsg, byteSent);

        PrintString(recvmsg);
        PrintString("\n");
        Close(id);
    }

    //Client 2
    state2 = Connect(id2, server_ip, port);
    if (state2 != -1)
    {
        byteSent = Send(id2, msg2, sizeof(msg2));
        byteRead = Receive(id2, recvmsg2, byteSent);

        PrintString(recvmsg2);
        PrintString("\n");
        Close(id2);
    }

    //Client 3
    state3 = Connect(id3, server_ip, port);
    if (state3 != -1)
    {
        byteSent = Send(id3, msg3, sizeof(msg3));
        byteRead = Receive(id3, recvmsg3, byteSent);

        PrintString(recvmsg3);
        PrintString("\n");
        Close(id3);
    }

    //Client 4
    state4 = Connect(id4, server_ip, port);
    if (state4 != -1)
    {
        byteSent = Send(id4, msg4, sizeof(msg4));
        byteRead = Receive(id4, recvmsg4, byteSent);

        PrintString(recvmsg4);
        PrintString("\n");
        Close(id4);
    }

    Halt();
}