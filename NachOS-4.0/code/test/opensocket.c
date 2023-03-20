#include "syscall.h"

int
main(){
    int id = SocketTCP();
    int id2 = SocketTCP();
    PrintInt(id);
    PrintString("\n");
    PrintInt(id2);
    Halt();
}