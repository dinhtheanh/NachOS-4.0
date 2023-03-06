// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "main.h"
#include "syscall.h"
#include "ksyscall.h"
//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// If you are handling a system call, don't forget to increment the pc
// before returning. (Or else you'll loop making the same system call forever!)
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	is in machine.h.
//----------------------------------------------------------------------

#define MaxFileLength 32

void
ExceptionHandler(ExceptionType which)
{	
    int type = kernel->machine->ReadRegister(2);

    DEBUG(dbgSys, "Received Exception " << which << " type: " << type << "\n");

    switch (which) {
    case SyscallException:
      switch(type) {
      case SC_Halt:
	DEBUG(dbgSys, "Shutdown, initiated by user program.\n");

	SysHalt();

	ASSERTNOTREACHED();
	break;
	
	case SC_Create:
			{
			int virtAddr;
			char* filename;
			DEBUG('a',"\n SC_Create call ...");
			DEBUG('a',"\n Reading virtual address of filename");
			// Lấy tham số tên tập tin từ thanh ghi r4
			virtAddr = kernel->machine->ReadRegister(4);
			DEBUG ('a',"\n Reading filename.");
			// MaxFileLength là = 32
			filename = User2System(virtAddr, MaxFileLength+1);
			if (filename == NULL)
			{
			printf("\n Not enough memory in system");
			DEBUG('a',"\n Not enough memory in system");
			kernel->machine->WriteRegister(2,-1); // trả về lỗi cho chương
			// trình người dùng
			delete filename;
			{
	  /* set previous programm counter (debugging only)*/
	  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
	  
	  /* set next programm counter for brach execution */
	  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
	}

			return;
			}
			DEBUG('a',"\n Finish reading filename.");
			//DEBUG('a',"\n File name : '"<<filename<<"'");
			// Create file with size = 0
			// Dùng đối tượng fileSystem của lớp OpenFile để tạo file,
			// việc tạo file này là sử dụng các thủ tục tạo file của hệ điều
			// hành Linux, chúng ta không quản ly trực tiếp các block trên
			// đĩa cứng cấp phát cho file, việc quản ly các block của file
			// trên ổ đĩa là một đồ án khác
			if (!kernel->fileSystem->Create(filename))
			{
			printf("\n Error create file '%s'",filename);
			kernel->machine->WriteRegister(2,-1);
			delete filename;
			{
	  /* set previous programm counter (debugging only)*/
	  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
	  
	  /* set next programm counter for brach execution */
	  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
	}
			return;
			}
			kernel->machine->WriteRegister(2,0); // trả về cho chương trình
			// người dùng thành công
			delete filename;
			{
	  /* set previous programm counter (debugging only)*/
	  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
	  
	  /* set next programm counter for brach execution */
	  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
	}

	
			return;
			break;
 		}	
      case SC_Add:
	DEBUG(dbgSys, "Add " << kernel->machine->ReadRegister(4) << " + " << kernel->machine->ReadRegister(5) << "\n");
	
	/* Process SysAdd Systemcall*/
	int result;
	result = SysAdd(/* int op1 */(int)kernel->machine->ReadRegister(4),
			/* int op2 */(int)kernel->machine->ReadRegister(5));

	DEBUG(dbgSys, "Add returning with " << result << "\n");
	/* Prepare Result */
	kernel->machine->WriteRegister(2, (int)result);
	
	/* Modify return point */
	{
	  /* set previous programm counter (debugging only)*/
	  kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	  /* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	  kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);
	  
	  /* set next programm counter for brach execution */
	  kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg)+4);
	}

	return;
	
	ASSERTNOTREACHED();

	break;

      default:
	cerr << "Unexpected system call " << type << "\n";
	break;
      }
      break;
    case SC_Open:
	{
		int bufAddr = machine->ReadRegister(4); 
		int type = machine->ReadRegister(5);
		char *buf;

		// if already opened 10 files
		if (fileSystem->index > 10)
		{
			machine->WriteRegister(2, -1);
			delete[] buf;
			break;
		}
				
		// if open stdin or stdout, number of openfiles dont increase
		buf = User2System(bufAddr, MaxFileLength + 1);
		if (strcmp(buf, "stdin") == 0)
		{
			printf("Stdin mode\n");
			machine->WriteRegister(2, 0);
			delete[] buf;
			break;
		}
		if (strcmp(buf, "stdout") == 0)
		{
			printf("Stdout mode\n");
			machine->WriteRegister(2, 1);
			delete[] buf;
			break;
		}

		// if opening file succeed
		// should not use OpenFile* temp to store = fileSystem->openfile[fileSystem->index]
		// cause, i dont have a method to destroy this pointer correctly
		if ((fileSystem->openfile[fileSystem->index] = fileSystem->Open(buf, type)) != NULL)
		{

			printf("\nOpen file success '%s'\n", buf);
			machine->WriteRegister(2, fileSystem->index - 1);
		}
		else 
		{
			printf("Can not open file '%s'", buf);
			machine->WriteRegister(2, -1);
		}
		delete[] buf;
		break;

	}
	case SC_Close:
	{
		int no = machine->ReadRegister(4);
		int i = fileSystem->index;

		// opened [i] files, and want to close file No.[no] (no > i) --> go wrong
		if (i < no)
		{
			printf("Close file failed \n");
			machine->WriteRegister(2, -1);
			break;
		}

		fileSystem->openfile[no] == NULL;
		delete fileSystem->openfile[no];
		machine->WriteRegister(2, 0);
		printf("Close file success\n");
		break;
		}
    default:
      cerr << "Unexpected user mode exception" << (int)which << "\n";
      break;
    }
    ASSERTNOTREACHED();
}
