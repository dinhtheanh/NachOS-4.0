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

void IncreasePC()
{
	// set previous program counter to current programcounter
	kernel->machine->WriteRegister(PrevPCReg, kernel->machine->ReadRegister(PCReg));

	/* set programm counter to next instruction (all Instructions are 4 byte wide)*/
	kernel->machine->WriteRegister(PCReg, kernel->machine->ReadRegister(PCReg) + 4);

	/* set next programm counter for brach execution */
	kernel->machine->WriteRegister(NextPCReg, kernel->machine->ReadRegister(PCReg) + 4);
}

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

	case SC_Open:
	{
		int bufAddr = kernel->machine->ReadRegister(4); 
		int ftype = kernel->machine->ReadRegister(5);
		char *buf = User2System(bufAddr, MaxFileLength + 1);; 
		// buf là filename

			int OpenFileID = -1;
				for (int i = 2;i < 20;i++)
				{
					if (kernel->fileSystem->openf[i] == NULL)
					{
						OpenFileID = i;
						break;
					}
				}
		if (OpenFileID != -1)
		{
			// chỉ xử lý khi type = 0 or = 1
			if (ftype == 0 or ftype == 1)
			{
				
				// printf("%d \n", OpenFileID);
				if (OpenFileID == -1)
				{
					printf("\n Cannot open file ");
					DEBUG(dbgSys, "\n Can not open file ...");
					kernel->machine->WriteRegister(2, -1);
				}
				else
				{
					kernel->fileSystem->openf[OpenFileID] = kernel->fileSystem->Open(buf, type);
					DEBUG(dbgSys, "\n Open file Success ...");
					//printf("\n Successfully open file ");
					kernel->machine->WriteRegister(2, OpenFileID);
				}
			}	
			else if (ftype == 2) // stdin
			{
				kernel->machine->WriteRegister(2,0);
			}
			else // stdout
			{
				kernel->machine->WriteRegister(2,1);
			}
			delete[] buf;
			IncreasePC();
			return;
			break;
		}
		kernel->machine->WriteRegister(2, -1);
		delete[] buf;
		IncreasePC();
		return;
		break;
	}

	case SC_Close:
	{
		int fID = kernel->machine->ReadRegister(4);	// Lay id cua file tu thanh ghi so 4
		int index = kernel->fileSystem->index;

		// opened [i] files, and want to close file No.[no] (no > i) --> go wrong
		if (fID > index)
		{
			printf("Close file failed \n");
			kernel->machine->WriteRegister(2, -1);
			IncreasePC();
			return;
			break;
		} 
		if (fID >= 0 && fID <= kernel->fileSystem->index) //Chi xu li khi fid nam trong [0, 20]
		// va file phai co id nam trong cac id dang dc mo
		{
			if (kernel->fileSystem->openf[fID]) //neu mo file thanh cong
			{
				delete kernel->fileSystem->openf[fID]; //Xoa vung nho luu tru file
				kernel->fileSystem->openf[fID] = NULL; //Gan vung nho NULL
				kernel->machine->WriteRegister(2, 0);
				printf("\n Successfully close file ");
				IncreasePC();
				return;
				break;
			}
		}
		printf("\n Cannot close file ");
		kernel->machine->WriteRegister(2, -1);
		IncreasePC();
		return;
		break;
	}
    


      	default:
		cerr << "Unexpected system call " << type << "\n";
		break;
      	}
      break;
	default:
      cerr << "Unexpected user mode exception" << (int)which << "\n";
      break;
    }
    ASSERTNOTREACHED();
}
