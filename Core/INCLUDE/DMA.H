#ifndef	_DMA_INCLUDED_
#define	_DMA_INCLUDED_

#define	DMA_CHANNEL0_ADDR	0x00
#define	DMA_CHANNEL0_COUNT	0x01
#define	DMA_CHANNEL1_ADDR	0x02
#define	DMA_CHANNEL1_COUNT	0x03
#define	DMA_CHANNEL2_ADDR	0x04
#define	DMA_CHANNEL2_COUNT	0x05
#define	DMA_CHANNEL3_ADDR	0x06
#define	DMA_CHANNEL3_COUNT	0x07

#define	DMA_STATUS			0x08	//In
#define	DMA_COMMAND			0x08	//Out
#define	DMA_REQUEST			0x09	//Out
#define	DMA_MASK			0x0A	//Out
#define	DMA_MODE			0x0B	//Out
#define	DMA_CLEARFF			0x0C	//Out
#define	DMA_TEMP			0x0D	//In
#define	DMA_RESET			0x0D	//Out
#define	DMA_CLEARMASK		0x0E	//Out
#define	DMA_WRITEALL		0x0F	//Out

#define	DMA_CHANNEL0_PAGE	0x87
#define	DMA_CHANNEL1_PAGE	0x83
#define	DMA_CHANNEL2_PAGE	0x81
#define	DMA_CHANNEL3_PAGE	0x82

#define	DMA2_CHANNEL4_PAGE	0x8F
#define	DMA2_CHANNEL5_PAGE	0x8B
#define	DMA2_CHANNEL6_PAGE	0x89
#define	DMA2_CHANNEL7_PAGE	0x8A

#define	DMA2_CHANNEL4_ADDR	0xC0	//16
#define	DMA2_CHANNEL4_COUNT	0xC2	//16
#define	DMA2_CHANNEL5_ADDR	0xC4	//16
#define	DMA2_CHANNEL5_COUNT	0xC6	//16
#define	DMA2_CHANNEL6_ADDR	0xC8	//16
#define	DMA2_CHANNEL6_COUNT	0xCA	//16
#define	DMA2_CHANNEL7_ADDR	0xCC	//16
#define	DMA2_CHANNEL7_COUNT	0xCE	//16

#define	DMA2_STATUS			0xD0	//In
#define	DMA2_COMMAND		0xD0	//Out
#define	DMA2_REQUEST		0xD2	//Out
#define	DMA2_MASK			0xD4	//Out
#define	DMA2_MODE			0xD6	//Out
#define	DMA2_CLEARFF		0xD8	//Out
#define	DMA2_TEMP			0xDA	//In
#define	DMA2_RESET			0xDA	//Out
#define	DMA2_CLEARMASK		0xDC	//Out
#define	DMA2_WRITEALL		0xDE	//Out

#define	DMA_CHANNEL0_COUNT_H	0x401
#define	DMA_CHANNEL1_COUNT_H	0x403
#define	DMA_CHANNEL2_COUNT_H	0x405
#define	DMA_CHANNEL3_COUNT_H	0x407

#define	DMA_CHAININT			0x40A	//In
#define	DMA_CHAINMODE			0x40A	//Out
#define	DMA_EXMODE				0x40B	//Out
#define	DMA_CHAINTERMCOUNTST	0x40C	//In

#define	DMA_CHANNEL0_PAGE_H		0x487
#define	DMA_CHANNEL1_PAGE_H		0x483
#define	DMA_CHANNEL2_PAGE_H		0x481
#define	DMA_CHANNEL3_PAGE_H		0x482

#define	DMA2_CHANNEL5_PAGE_H	0x48B
#define	DMA2_CHANNEL6_PAGE_H	0x489
#define	DMA2_CHANNEL7_PAGE_H	0x48A

#define	DMA2_CHANNEL5_COUNT_H	0x4C6
#define	DMA2_CHANNEL6_COUNT_H	0x4CA
#define	DMA2_CHANNEL7_COUNT_H	0x4CE

#define	DMA2_CHAINSTATUS		0x4D4	//In
#define	DMA2_CHAINMODE			0x4D4	//Out
#define	DMA2_EXMODE				0x4D6	//Out

#define	DMA_CHANNEL0_STOP		0x4E0
#define	DMA_CHANNEL1_STOP		0x4E4
#define	DMA_CHANNEL2_STOP		0x4E8
#define	DMA_CHANNEL3_STOP		0x4EC

#define	DMA2_CHANNEL5_STOP		0x4F4
#define	DMA2_CHANNEL6_STOP		0x4F8
#define	DMA2_CHANNEL7_STOP		0x4FC

//////////////////////////////////////////

#define	DMA_STATUS_0_FF			0x01
#define	DMA_STATUS_1_FF			0x02
#define	DMA_STATUS_2_FF			0x04
#define	DMA_STATUS_3_FF			0x08
#define	DMA_STATUS_0_REQUEST	0x10
#define	DMA_STATUS_1_REQUEST	0x20
#define	DMA_STATUS_2_REQUEST	0x40
#define	DMA_STATUS_3_REQUEST	0x80

#define DMA_COMMAND_M2M			0x01
#define	DMA_COMMAND_KEEPADDR_0	0x02
#define	DMA_COMMAND_BANCON		0x04
#define	DMA_COMMAND_COMPTIME	0x08
#define	DMA_COMMAND_LOOPPRIV	0x10
#define	DMA_COMMAND_EXWRITE		0x20
#define	DMA_COMMAND_DREQ_H		0x40
#define	DMA_COMMAND_DACK_H		0x80

#define	DMA_REQUEST_CHN0		0x00
#define	DMA_REQUEST_CHN1		0x01
#define	DMA_REQUEST_CHN2		0x02
#define	DMA_REQUEST_CHN3		0x03

#define	DMA_REQUEST_SET			0x04

#define	DMA_MASK_CHN0			0x00
#define	DMA_MASK_CHN1			0x01
#define	DMA_MASK_CHN2			0x02
#define	DMA_MASK_CHN3			0x03

#define	DMA_MASK_SET			0x04

#define	DMA_MODE_CHN0			0x00
#define	DMA_MODE_CHN1			0x01
#define	DMA_MODE_CHN2			0x02
#define	DMA_MODE_CHN3			0x03

#define	DMA_MODE_VERIFY			0x00
#define	DMA_MODE_WRITE			0x04	//д���ڴ�
#define	DMA_MODE_READ			0x08	//���ڴ��
#define	DMA_MODE_INVALID		0x0C

#define	DMA_MODE_AUTOINIT		0x10
#define	DMA_MODE_DECREMENT		0x20

#define	DMA_MODE_COMMAND		0x00
#define	DMA_MODE_SINGLE			0x40
#define	DMA_MODE_BLOCK			0x80
#define	DMA_MODE_INVALID		0xC0

#define	DMA_WRITEALL_MASK0		0x00
#define	DMA_WRITEALL_MASK1		0x01
#define	DMA_WRITEALL_MASK2		0x02
#define	DMA_WRITEALL_MASK3		0x03

#endif