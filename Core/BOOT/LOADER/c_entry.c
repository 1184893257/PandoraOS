#include"global.h"
#include"entry.h"
#include"video.h"

void main()
{
	SwitchToTextMode();
	Print(OSNAME" is loading.\n");
	for(;;);
}
