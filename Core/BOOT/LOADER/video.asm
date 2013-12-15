;##############################################################################
;
;video.asm
;LOADERר����ʾ���ֵ����������������ӡ�ı�����Ϣ��
;
;##############################################################################

%include"aglobal.inc"

global	_SwitchVideoMode
global	_SwitchToTextMode
global	_SwitchTo320x200
global	_Print
global	_ShowDec
global	_ShowHex

segment	_TEXT
proc	_SwitchVideoMode
	int 0x10
endproc

proc	_SwitchToTextMode
	mov ax, 3
	call _SwitchVideoMode
endproc

proc	_SwitchTo320x200
	mov ax, 0x13
	call _SwitchVideoMode
endproc

proc	_Print
	push si
	mov	si,[arg(0)]
	mov dx,7
	mov ah,0x0E
.ReadChar:
		lodsb
		or al,al
		jz .EndOfString
		int 0x10
	jmp .ReadChar
.EndOfString:
	pop si
endproc


;��ʾʮ�������ֵĺ���
proc	_ShowDec
	mov ax,[arg(0)]
	xor cx,cx		;cx����������
.PushNums:			;�Ȱ�ÿ����λ��ѹ���ջ
	xor dx,dx		;���������16λ
	div word[Ten]	;ax����10
	push dx			;ѹ������
	inc cx			;λ����1
	or ax,ax		;�ж��Ƿ����
	jnz .PushNums	;���ǵĻ�������
	mov dx,7		;ͼ��ģʽ����ɫ
.ShowNums:			;�ٰѶ�ջ�е���λȡ��
	pop ax			;ȡ������
	add al,'0'		;����ASCII��
	mov ah,0x0E		;��ʾ�ı��Ĺ���
	int 0x10		;��ʾ�ı�
	loop .ShowNums	;ѭ����ʾ�����ı�
endproc


;��ʾ16�������ֵĺ���
;���룺
	;ax=����
;���أ�
	;ax=0
	;cx=0
	;dx=7
proc	_ShowHex
	mov cx,4			;4����λ
	mov dx,7			;ͼ��ģʽ�µ���ɫ
.ShowNum:				;ѭ����ʾ��λ
	push ax				;����AX
	shr ax,12			;ȡ���λ
	cmp al,10			;�ж��Ƿ�С��10
	jb .LessThan10		;�ǵĻ�����
	add al,'A'-'0'-10	;����ʹ����ʾΪA-F
.LessThan10:			;С��10
	add al,'0'			;��Ϊ0-9
	mov ah,0x0E			;��ʾ�ַ��Ĺ���
	int 0x10			;�ж�
	pop ax				;ȡ��AX
	shl ax,4			;������һ����λ
	loop .ShowNum		;ѭ����ʾ��һ����λ
endproc


segment	_DATA
Ten	dw	10			;���������ĳ���

