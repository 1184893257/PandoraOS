%define	_INTR_ASM_

%include"ASMCOM.INC"
%include"INTR.INC"

global	_GetVector	;DWORD	GetVector(BYTE);
global	_SetVector	;void	SetVector(BYTE,DWORD);
global	_SendEOI	;void	SendEOI(BYTE);
global	_SetMask	;void	SetMask(BYTE);
global	_GetMask	;BYTE	GetMask(BYTE);
global	_ClearMask	;void	ClearMask(BYTE);

segment _TEXT

;DWORD	GetVector(BYTE);
_GetVector:			;取得中断向量的函数
	push bp
	mov bp,sp
	push es
	push bx

	xor ax,ax
	mov es,ax
	mov bh,ah		;bh=0
	mov bl,[ARG(0)]	;取得中断号
	shl bx,2		;乘4
	mov ax,[es:bx]	;返回向量低16位=偏移
	mov dx,[es:bx+2];高16位=段

	pop bx
	pop es
	pop bp
	ret

;void	SetVector(BYTE,DWORD);
_SetVector:			;设置中断向量的函数
	push bp
	mov bp,sp
	push es
	push bx

	xor ax,ax
	mov es,ax
	mov bh,ah		;bh=0
	mov bl,[ARG(0)]	;取得中断号
	shl bx,2		;乘4

	cli				;改写中断要关中断
	mov eax,[ARG(1)];取得中断偏移
	mov [es:bx],eax	;写入偏移
	sti

	pop bx
	pop es
	pop bp
	ret

;void	SendEOI(BYTE);
_SendEOI:			;回应8259中断已结束
	push bp
	mov bp,sp

	mov al,[ARG(0)]
	cmp al,7
	ja .Ack8_15
.Ack0_7:
	or al,PIC_SPECEOI
	out PIC_MODE,al	;回应特定中断的EOI

	pop bp
	ret
.Ack8_15:
	or al,PIC_SPECEOI
	out PIC2_MODE,al;回应特定中断的EOI

	pop bp
	ret

;void	SetMask(BYTE);
_SetMask:
	push bp
	mov bp,sp

	mov dl,1		;DL用作屏蔽位
	
	mov cl,[ARG(0)]	;读取中断号
	cmp cl,7
	ja .Mask8_15
.Mask0_7:			;设置PIC1的屏蔽
	shl dl,cl		;设置屏蔽位
	in al,PIC_MASK	;读入旧的屏蔽位
	or al,dl		;屏蔽
	out PIC_MASK,al	;设置新的屏蔽位

	pop bp
	ret
.Mask8_15:			;设置PIC2的屏蔽
	rol dl,cl		;设置屏蔽位
	in al,PIC2_MASK	;读入旧的屏蔽位
	or al,dl		;屏蔽
	out PIC2_MASK,al;设置新的屏蔽位

	pop bp
	ret

;BYTE	GetMask(BYTE);
_GetMask:
	push bp
	mov bp,sp

	mov dl,1		;DL用作屏蔽位
	
	mov cl,[ARG(0)]	;读取中断号
	cmp cl,7
	ja .Mask8_15
.Mask0_7:			;设置PIC1的屏蔽
	shl dl,cl		;设置屏蔽位
	in al,PIC_MASK	;读入屏蔽位
	and al,dl		;取得屏蔽位

	pop bp
	ret
.Mask8_15:			;设置PIC2的屏蔽
	rol dl,cl		;设置屏蔽位
	in al,PIC2_MASK	;读入屏蔽位
	and al,dl		;取得屏蔽位

	pop bp
	ret

;void	ClearMask(BYTE);
_ClearMask:
	push bp
	mov bp,sp

	mov dl,0xFE		;DL用作屏蔽位
	
	mov cl,[ARG(0)]	;读取中断号
	cmp cl,7
	ja .Mask8_15
.Mask0_7:			;设置PIC1的屏蔽
	rol dl,cl		;设置屏蔽位
	in al,PIC_MASK	;读入旧的屏蔽位
	and al,dl		;去掉屏蔽
	out PIC_MASK,al	;设置新的屏蔽位

	pop bp
	ret
.Mask8_15:			;设置PIC2的屏蔽
	rol dl,cl		;设置屏蔽位
	in al,PIC2_MASK	;读入旧的屏蔽位
	and al,dl		;去掉屏蔽
	out PIC2_MASK,al;设置新的屏蔽位

	pop bp
	ret

