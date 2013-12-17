;##############################################################################
;
;dma.asm
;LOADER专用DMA驱动
;
;##############################################################################

%include"aglobal.inc"
%include"DMA.INC"

global	_DMA_AddressPortList	;BYTE DMA_AddressPortList[8];
global	_DMA_PagePortList		;BYTE DMA_PagePortList[8];
global	_DMA_CountPortList		;BYTE DMA_CountPortList[8];

global	_DMA_SetChannelMask0_3	;void DMA_SetChannelMask0_3(BYTE bChannel);
global	_DMA_SetChannelMask4_7	;void DMA_SetChannelMask4_7(BYTE bChannel);
global	_DMA_ClearChannelMask0_3;void DMA_ClearChannelMask0_3(BYTE bChannel);
global	_DMA_ClearChannelMask4_7;void DMA_ClearChannelMask4_7(BYTE bChannel);
global	_DMA_ClearFlipFlop0_3	;void DMA_ClearFlipFlop0_3(void);
global	_DMA_ClearFlipFlop4_7	;void DMA_ClearFlipFlop4_7(void);
global	_DMA_SetMode0_3			;void DMA_SetMode0_3(BYTE bMode);
global	_DMA_SetMode4_7			;void DMA_SetMode4_7(BYTE bMode);
global	_DMA_SetChannelAddress	;void DMA_SetChannelAddress(BYTE bChannel,DWORD dwAddress24);
global	_DMA_SetChannelCount	;void DMA_SetChannelCount(BYTE bChannel,WORD wCount);

segment _TEXT

;******************************************************************************
;void DMA_SetChannelMask0_3(BYTE bChannel);
;屏蔽指定的DMA通道（0-3）
;******************************************************************************
proc	_DMA_SetChannelMask0_3
	mov al,[arg(0)]
	and al,3
	or al,DMA_MASK_SET;屏蔽位
	out DMA_MASK,al;输出到DMA
endproc

;******************************************************************************
;void DMA_SetChannelMask4_7(BYTE bChannel);
;屏蔽指定的MA通道（4-7）
;******************************************************************************
proc	_DMA_SetChannelMask4_7
	mov al,[arg(0)]
	and al,3
	or al,DMA_MASK_SET;屏蔽位
	out DMA2_MASK,al;输出到DMA
endproc

;******************************************************************************
;void DMA_ClearChannelMask0_3(BYTE bChannel);
;打开指定的DMA通道（0-3）
;******************************************************************************
proc	_DMA_ClearChannelMask0_3
	mov al,[arg(0)]
	and al,3	;清除屏蔽位
	out DMA_MASK,al;输出到DMA
endproc

;******************************************************************************
;void DMA_ClearChannelMask4_7(BYTE bChannel);
;打开指定的DMA通道（4-7）
;******************************************************************************
proc	_DMA_ClearChannelMask4_7
	mov al,[arg(0)]
	and al,3	;清除屏蔽位
	out DMA2_MASK,al;输出到DMA
endproc


;******************************************************************************
;void DMA_ClearFlipFlop0_3(void);
;清除FlipFlop位（0-3）
;******************************************************************************
_DMA_ClearFlipFlop0_3:
	out DMA_CLEARFF,al;只需要一次out操作
	ret

;******************************************************************************
;void DMA_ClearFlipFlop4_7(void);
;清除FlipFlop位（4-7）
;******************************************************************************
_DMA_ClearFlipFlop4_7:
	out DMA2_CLEARFF,al;只需要一次out操作
	ret

;******************************************************************************
;void DMA_SetMode0_3(BYTE bMode);
;设置通道0-3的模式
;******************************************************************************
proc	_DMA_SetMode0_3
	mov al,[bp+4]
	out DMA_MODE,al
endproc

;******************************************************************************
;void DMA_SetMode4_7(BYTE bMode);
;设置通道4-7的模式
;******************************************************************************
proc	_DMA_SetMode4_7
	push bp
	mov bp,sp
	mov al,[bp+4]
	out DMA2_MODE,al
endproc

;******************************************************************************
;void DMA_SetChannelAddress(BYTE bChannel,DWORD dwAddress24);
;设置DMA通道的内存地址（24位，能访问16MB内存）
;******************************************************************************
proc	_DMA_SetChannelAddress
	push bp
	mov bp,sp
	push si
	mov si,[bp+4]
	mov dx,[_DMA_AddressPortList+si];取得DMA通道对应的地址端口
	mov al,[bp+6]	;输出地址低8位
	out dx,al
	mov al,[bp+7]	;输出地址中8位
	out dx,al
	mov dx,[_DMA_PagePortList+si];取得DMA通道对应的页面端口
	mov al,[bp+8]	;输出地址高8位
	out dx,al
	pop si
endproc

;******************************************************************************
;void DMA_SetChannelCount(BYTE bChannel,WORD wCount);
;设置DMA通道的计数
;******************************************************************************
proc	_DMA_SetChannelCount
	push bp
	mov bp,sp
	push si
	mov si,[bp+4]
	mov dx,[_DMA_CountPortList+si];取得DMA通道对应的计数端口
	mov al,[bp+6]	;输出计数低8位
	out dx,al
	mov al,[bp+7]	;输出计数高8位
	out dx,al
	pop si
endproc

segment _DATA

;******************************************************************************
;BYTE DMA_AddressPortList[8];
;地址端口表
;******************************************************************************
_DMA_AddressPortList:
	db	DMA_CHANNEL0_ADDR
	db	DMA_CHANNEL1_ADDR
	db	DMA_CHANNEL2_ADDR
	db	DMA_CHANNEL3_ADDR
	db	DMA2_CHANNEL4_ADDR
	db	DMA2_CHANNEL5_ADDR
	db	DMA2_CHANNEL6_ADDR
	db	DMA2_CHANNEL7_ADDR

;******************************************************************************
;BYTE DMA_PagePortList[8];
;页面端口表
;******************************************************************************
_DMA_PagePortList:
	db	DMA_CHANNEL0_PAGE
	db	DMA_CHANNEL1_PAGE
	db	DMA_CHANNEL2_PAGE
	db	DMA_CHANNEL3_PAGE
	db	DMA2_CHANNEL4_PAGE
	db	DMA2_CHANNEL5_PAGE
	db	DMA2_CHANNEL6_PAGE
	db	DMA2_CHANNEL7_PAGE

;******************************************************************************
;BYTE DMA_CountPortList[8];
;计数端口表
;******************************************************************************
_DMA_CountPortList:
	db	DMA_CHANNEL0_COUNT
	db	DMA_CHANNEL1_COUNT
	db	DMA_CHANNEL2_COUNT
	db	DMA_CHANNEL3_COUNT
	db	DMA2_CHANNEL4_COUNT
	db	DMA2_CHANNEL5_COUNT
	db	DMA2_CHANNEL6_COUNT
	db	DMA2_CHANNEL7_COUNT
