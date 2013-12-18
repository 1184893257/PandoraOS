#ifndef	_VIDEO_HEADER_IN_16_BIT_
#define	_VIDEO_HEADER_IN_16_BIT_

#include"global.h"

NASMEXTRN	void	SwitchVideoMode(BYTE);
NASMEXTRN	void	SwitchToTextMode(void);
NASMEXTRN	void	SwitchTo320x200(void);
NASMEXTRN	void	Print(char*);
NASMEXTRN	void	ShowDec(signed int);
NASMEXTRN	void	ShowDecU(unsigned int);
NASMEXTRN	void	ShowHex(signed int);
NASMEXTRN	void	ShowHexU(unsigned int);

// 支持%c %u %d %x %s %% \n
// 是调用Print、ShowXXX来实现的
// %x和%X都显示大写的16进制数
//不支持浮点数
//不支持数字宽度控制、\t也不支持
//在打印过程中,fmt中的字符会被改动(简单是有代价的)
//So, it's just for debug
void DPrint(char* fmt, ...);

#endif
