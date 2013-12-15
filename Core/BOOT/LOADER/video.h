#ifndef	_VIDEO_HEADER_IN_16_BIT_
#define	_VIDEO_HEADER_IN_16_BIT_

#include"global.h"

void	SwitchVideoMode(BYTE);
void	SwitchToTextMode(void);
void	SwitchTo320x200(void);
void	Print(char*);
void	ShowDec(signed int);
void	ShowDecU(unsigned int);
void	ShowHex(signed int);
void	ShowHexU(unsigned int);

#endif
