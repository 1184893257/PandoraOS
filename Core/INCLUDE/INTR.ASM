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
_GetVector:			;ȡ���ж������ĺ���
	push bp
	mov bp,sp
	push es
	push bx

	xor ax,ax
	mov es,ax
	mov bh,ah		;bh=0
	mov bl,[ARG(0)]	;ȡ���жϺ�
	shl bx,2		;��4
	mov ax,[es:bx]	;����������16λ=ƫ��
	mov dx,[es:bx+2];��16λ=��

	pop bx
	pop es
	pop bp
	ret

;void	SetVector(BYTE,DWORD);
_SetVector:			;�����ж������ĺ���
	push bp
	mov bp,sp
	push es
	push bx

	xor ax,ax
	mov es,ax
	mov bh,ah		;bh=0
	mov bl,[ARG(0)]	;ȡ���жϺ�
	shl bx,2		;��4

	cli				;��д�ж�Ҫ���ж�
	mov eax,[ARG(1)];ȡ���ж�ƫ��
	mov [es:bx],eax	;д��ƫ��
	sti

	pop bx
	pop es
	pop bp
	ret

;void	SendEOI(BYTE);
_SendEOI:			;��Ӧ8259�ж��ѽ���
	push bp
	mov bp,sp

	mov al,[ARG(0)]
	cmp al,7
	ja .Ack8_15
.Ack0_7:
	or al,PIC_SPECEOI
	out PIC_MODE,al	;��Ӧ�ض��жϵ�EOI

	pop bp
	ret
.Ack8_15:
	or al,PIC_SPECEOI
	out PIC2_MODE,al;��Ӧ�ض��жϵ�EOI

	pop bp
	ret

;void	SetMask(BYTE);
_SetMask:
	push bp
	mov bp,sp

	mov dl,1		;DL��������λ
	
	mov cl,[ARG(0)]	;��ȡ�жϺ�
	cmp cl,7
	ja .Mask8_15
.Mask0_7:			;����PIC1������
	shl dl,cl		;��������λ
	in al,PIC_MASK	;����ɵ�����λ
	or al,dl		;����
	out PIC_MASK,al	;�����µ�����λ

	pop bp
	ret
.Mask8_15:			;����PIC2������
	rol dl,cl		;��������λ
	in al,PIC2_MASK	;����ɵ�����λ
	or al,dl		;����
	out PIC2_MASK,al;�����µ�����λ

	pop bp
	ret

;BYTE	GetMask(BYTE);
_GetMask:
	push bp
	mov bp,sp

	mov dl,1		;DL��������λ
	
	mov cl,[ARG(0)]	;��ȡ�жϺ�
	cmp cl,7
	ja .Mask8_15
.Mask0_7:			;����PIC1������
	shl dl,cl		;��������λ
	in al,PIC_MASK	;��������λ
	and al,dl		;ȡ������λ

	pop bp
	ret
.Mask8_15:			;����PIC2������
	rol dl,cl		;��������λ
	in al,PIC2_MASK	;��������λ
	and al,dl		;ȡ������λ

	pop bp
	ret

;void	ClearMask(BYTE);
_ClearMask:
	push bp
	mov bp,sp

	mov dl,0xFE		;DL��������λ
	
	mov cl,[ARG(0)]	;��ȡ�жϺ�
	cmp cl,7
	ja .Mask8_15
.Mask0_7:			;����PIC1������
	rol dl,cl		;��������λ
	in al,PIC_MASK	;����ɵ�����λ
	and al,dl		;ȥ������
	out PIC_MASK,al	;�����µ�����λ

	pop bp
	ret
.Mask8_15:			;����PIC2������
	rol dl,cl		;��������λ
	in al,PIC2_MASK	;����ɵ�����λ
	and al,dl		;ȥ������
	out PIC2_MASK,al;�����µ�����λ

	pop bp
	ret
