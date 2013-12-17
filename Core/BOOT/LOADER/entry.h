//#############################################################################
//
//entry.h:
//给entry.asm的函数、变量提供声明。
//
//#############################################################################

#ifndef	_ENTRY_HEADER_INCLUDE_
#define	_ENTRY_HEADER_INCLUDE_

#include"global.h"

NASMEXTRN	void	start(void);

NASMEXTRN	char	stack[STACKSIZE];
NASMEXTRN	char	HaltMessage[];

#endif
