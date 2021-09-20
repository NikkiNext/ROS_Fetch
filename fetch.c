#include <windows.h>
#include <stdio.h>

const char *Logo[11];

void osver()
{
    DWORD dwVersion = 0; 
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0; 
    DWORD dwBuild = 0;

    dwVersion = GetVersion();
 
    // Get the Windows version.

    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

    // Get the build number.

    if (dwVersion < 0x80000000)              
        dwBuild = (DWORD)(HIWORD(dwVersion));

    printf("Kernel: %d.%d (%d)\n", 
                dwMajorVersion,
                dwMinorVersion,
                dwBuild);
}

void uptime(){
	DWORD ticks = GetTickCount();
	DWORD milliseconds = ticks % 1000;
	ticks /= 1000;
	DWORD seconds = ticks % 60;
	ticks /= 60;
	DWORD minutes = ticks % 60;
	ticks /= 60;
	DWORD hours = ticks; // may exceed 24 hours.
	printf("Uptime:	%d hours, %02d minutes, %02d seconds\n", hours, minutes, seconds);
}

void resol(){
	DWORD xsize = GetSystemMetrics(SM_CXSCREEN);
	DWORD ysize = GetSystemMetrics(SM_CYSCREEN);
	printf("Resolution: %dx%02d\n", xsize, ysize);
}

void ros_logo(){
	
	Logo[0]="ooooooo   ooooooo";
	Logo[1]="ooooooo   ooooooo";
	Logo[2]="ooooooo   ooooooo";
	Logo[3]="ooooooo   ooooooo";
	Logo[4]="ooooooo   ooooooo";
	Logo[5]="                 ";
	Logo[6]="                 ";
	Logo[7]="ooooooo   ooooooo";
	Logo[8]="ooooooo   ooooooo";
	Logo[9]="ooooooo   ooooooo";
	Logo[10]="ooooooo   ooooooo";
	Logo[11]="ooooooo   ooooooo";
}



void brandString(int eaxValues)
{
	int a[10];
    if (eaxValues == 1) {
    __asm__("mov $0x80000002 , %eax\n\t");
    }
    else if (eaxValues == 2) {
        __asm__("mov $0x80000003 , %eax\n\t");
    }
    else if (eaxValues == 3) {
        __asm__("mov $0x80000004 , %eax\n\t");
    }
    __asm__("cpuid\n\t");
    __asm__("mov %%eax, %0\n\t":"=r" (a[0]));
    __asm__("mov %%ebx, %0\n\t":"=r" (a[1]));
    __asm__("mov %%ecx, %0\n\t":"=r" (a[2]));
    __asm__("mov %%edx, %0\n\t":"=r" (a[3]));
    printf("%s", &a[0]);
}

void getCpuID()
{
    __asm__("xor %eax , %eax\n\t");
    __asm__("xor %ebx , %ebx\n\t");
    __asm__("xor %ecx , %ecx\n\t");
    __asm__("xor %edx , %edx\n\t");
    printf("CPU: ");
    brandString(1);
    brandString(2);
    brandString(3);
    printf("\n");
}

void memory(){
	#define DIV 1048576
	
	MEMORYSTATUSEX statex;

  statex.dwLength = sizeof (statex);

  GlobalMemoryStatusEx (&statex);

	DWORD MemAll = statex.ullTotalPhys/DIV;
	DWORD MemUs = statex.ullTotalPhys/DIV-statex.ullAvailPhys/DIV;

  
  printf("Memory: %d Mb / %02d Mb\n", MemUs, MemAll);
}

void main(){
	int i;
	ros_logo();
	for (i=0; i<=sizeof(Logo)/sizeof(Logo[0]); i++)
    {
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
    	
    	printf(Logo[i]);   
		if (i>=0 && i<=5)
		{
			printf("   ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);	
		} 	
    	if (i==0)
    	{    		
    		printf("OS: ReactOS\n");
		}
		if (i==1)
    	{
    		osver();
		}
		if (i==2)
    	{
    		uptime();
		}
		if (i==3)
    	{
    		resol();
		}
		if (i==4)
    	{
    		getCpuID();
		}
		if (i==5)
    	{
    		memory();
		}
		if (i>5)
    	{
    		printf("\n");
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    }
    
}
