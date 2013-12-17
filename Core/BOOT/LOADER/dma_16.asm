;##############################################################################
;
;dma.asm
;LOADERר��DMA����
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
;����ָ����DMAͨ����0-3��
;******************************************************************************
proc	_DMA_SetChannelMask0_3
	mov al,[arg(0)]
	and al,3
	or al,DMA_MASK_SET;����λ
	out DMA_MASK,al;�����DMA
endproc

;******************************************************************************
;void DMA_SetChannelMask4_7(BYTE bChannel);
;����ָ����MAͨ����4-7��
;******************************************************************************
proc	_DMA_SetChannelMask4_7
	mov al,[arg(0)]
	and al,3
	or al,DMA_MASK_SET;����λ
	out DMA2_MASK,al;�����DMA
endproc

;******************************************************************************
;void DMA_ClearChannelMask0_3(BYTE bChannel);
;��ָ����DMAͨ����0-3��
;******************************************************************************
proc	_DMA_ClearChannelMask0_3
	mov al,[arg(0)]
	and al,3	;�������λ
	out DMA_MASK,al;�����DMA
endproc

;******************************************************************************
;void DMA_ClearChannelMask4_7(BYTE bChannel);
;��ָ����DMAͨ����4-7��
;******************************************************************************
proc	_DMA_ClearChannelMask4_7
	mov al,[arg(0)]
	and al,3	;�������λ
	out DMA2_MASK,al;�����DMA
endproc


;******************************************************************************
;void DMA_ClearFlipFlop0_3(void);
;���FlipFlopλ��0-3��
;******************************************************************************
_DMA_ClearFlipFlop0_3:
	out DMA_CLEARFF,al;ֻ��Ҫһ��out����
	ret

;******************************************************************************
;void DMA_ClearFlipFlop4_7(void);
;���FlipFlopλ��4-7��
;******************************************************************************
_DMA_ClearFlipFlop4_7:
	out DMA2_CLEARFF,al;ֻ��Ҫһ��out����
	ret

;******************************************************************************
;void DMA_SetMode0_3(BYTE bMode);
;����ͨ��0-3��ģʽ
;******************************************************************************
proc	_DMA_SetMode0_3
	mov al,[bp+4]
	out DMA_MODE,al
endproc

;******************************************************************************
;void DMA_SetMode4_7(BYTE bMode);
;����ͨ��4-7��ģʽ
;******************************************************************************
proc	_DMA_SetMode4_7
	push bp
	mov bp,sp
	mov al,[bp+4]
	out DMA2_MODE,al
endproc

;******************************************************************************
;void DMA_SetChannelAddress(BYTE bChannel,DWORD dwAddress24);
;����DMAͨ�����ڴ��ַ��24λ���ܷ���16MB�ڴ棩
;******************************************************************************
proc	_DMA_SetChannelAddress
	push bp
	mov bp,sp
	push si
	mov si,[bp+4]
	mov dx,[_DMA_AddressPortList+si];ȡ��DMAͨ����Ӧ�ĵ�ַ�˿�
	mov al,[bp+6]	;�����ַ��8λ
	out dx,al
	mov al,[bp+7]	;�����ַ��8λ
	out dx,al
	mov dx,[_DMA_PagePortList+si];ȡ��DMAͨ����Ӧ��ҳ��˿�
	mov al,[bp+8]	;�����ַ��8λ
	out dx,al
	pop si
endproc

;******************************************************************************
;void DMA_SetChannelCount(BYTE bChannel,WORD wCount);
;����DMAͨ���ļ���
;******************************************************************************
proc	_DMA_SetChannelCount
	push bp
	mov bp,sp
	push si
	mov si,[bp+4]
	mov dx,[_DMA_CountPortList+si];ȡ��DMAͨ����Ӧ�ļ����˿�
	mov al,[bp+6]	;���������8λ
	out dx,al
	mov al,[bp+7]	;���������8λ
	out dx,al
	pop si
endproc

segment _DATA

;******************************************************************************
;BYTE DMA_AddressPortList[8];
;��ַ�˿ڱ�
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
;ҳ��˿ڱ�
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
;�����˿ڱ�
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
