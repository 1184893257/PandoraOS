//#############################################################################
//
//entry.h:
//��entry.asm�ĺ����������ṩ������
//
//#############################################################################

#ifndef	_ENTRY_HEADER_INCLUDE_
#define	_ENTRY_HEADER_INCLUDE_

#include"global.h"

NASMEXTRN	void	start(void);

NASMEXTRN	char	stack[STACKSIZE];
NASMEXTRN	char	HaltMessage[];

#endif
