#ifndef	_DMA_FOR_LOADER_
#define	_DMA_FOR_LOADER_

#include"global.h"
#include"DMA.H"

NASMEXTRN	BYTE	DMA_AddressPortList[8];
NASMEXTRN	BYTE	DMA_PagePortList[8];
NASMEXTRN	BYTE	DMA_CountPortList[8];

NASMEXTRN	void	DMA_SetChannelMask0_3(BYTE bChannel);
NASMEXTRN	void	DMA_SetChannelMask4_7(BYTE bChannel);
NASMEXTRN	void	DMA_ClearChannelMask0_3(BYTE bChannel);
NASMEXTRN	void	DMA_ClearChannelMask4_7(BYTE bChannel);
NASMEXTRN	void	DMA_ClearFlipFlop0_3(void);
NASMEXTRN	void	DMA_ClearFlipFlop4_7(void);
NASMEXTRN	void	DMA_SetMode0_3(BYTE bMode);
NASMEXTRN	void	DMA_SetMode4_7(BYTE bMode);
NASMEXTRN	void	DMA_SetChannelAddress(BYTE bChannel,DWORD dwAddress24);
NASMEXTRN	void	DMA_SetChannelCount(BYTE bChannel,WORD wCount);

#endif
