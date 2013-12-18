#include"global.h"
#include"entry.h"
#include"video.h"

void main()
{
	SwitchToTextMode();
	Print(OSNAME" is loading.\r\n");
	DPrint("sizeof(char):%d\n", sizeof(char));
	DPrint("sizeof(short):%d\n", sizeof(short));
	DPrint("sizeof(int):%d\n", sizeof(int));
	DPrint("sizeof(long):%d\n", sizeof(long));
	for(;;);
}
