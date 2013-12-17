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

#endif
