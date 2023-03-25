#define MAX_LENGTH 255

#define STDIN 0
#define STDOUT 1

int main(int argc, char* argv[])
{
	int RemoveFileId=0;
	int fileSize;
	// char c; //Ky tu de in ra
	char fileName[MAX_LENGTH];
	// int i; //Index for loop

	//PrintString(argv[1]);
    
	PrintString(" - Nhap vao ten file can xoa: ");
	ReadString(fileName, MAX_LENGTH);
    //Open(fileName, 0);
	// fileName = argv[1];
	RemoveFileId = Remove(fileName);
    if (RemoveFileId != -1)
        PrintString("Da xoa file\n");
    else
        PrintString("Chua xoa duoc\n");
    Halt();
}