//#############################################################################
//
//entry.h:
//��entry.asm�ĺ����������ṩ������
//
//#############################################################################

#ifndef	_ENTRY_HEADER_INCLUDE_
#define	_ENTRY_HEADER_INCLUDE_

#include"global.h"

void	start(void);

extern	char	stack[STACKSIZE];
extern	char	HaltMessage[];

#endif
