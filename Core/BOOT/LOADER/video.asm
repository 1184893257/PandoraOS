;##############################################################################
;
;video.asm
;LOADERר����ʾ���ֵ����������������ӡ�ı�����Ϣ��
;
;##############################################################################

%include"aglobal.inc"

global	_SwitchVideoMode	;void _cdecl SwitchVideoMode(BYTE bMode);
global	_SwitchToTextMode	;void _cdecl SwitchToTextMode();
global	_SwitchTo320x200	;void _cdecl SwitchTo320x200();
global	_Print				;void _cdecl Print(near char*);
global	_ShowDec			;void _cdecl ShowDec(signed int);
global	_ShowDecU			;void _cdecl ShowDecU(unsigned int);
global	_ShowHex			;void _cdecl ShowHex(signed int);
global	_ShowHexU			;void _cdecl ShowHexU(unsigned int);

segment	_TEXT
proc	_SwitchVideoMode
	movzx ax,byte[arg(0)]	;��ȡ����
	int 0x10				;INT 0x10����0��������ʾģʽ
endproc

proc	_SwitchToTextMode
	push word 3				;ѹ�����3
	call _SwitchVideoMode	;�л���ʾģʽ
endproc	2					;���������ָ���ջƽ��

proc	_SwitchTo320x200
	push word 0x13			;ѹ�����0x13
	call _SwitchVideoMode	;�л���ʾģʽ
endproc	2					;���������ָ���ջƽ��

proc	_Print			;��ӡ�ַ����ĺ���
	push si				;����si����ΪTCʹ��si��di���������Ĵ���
	mov	si,[arg(0)]		;arg(0)��char*
	mov dx,7			;dx=7=ͼ��ģʽ�µģ��ң���ɫ
	mov ah,0x0E			;INT 0x10 AH=0x0E ��ӡ�ַ�����
.ReadChar:
		lodsb			;��ȡһ���ַ�
		or al,al		;�ж��Ƿ��β'\0'
		jz .EndOfString	;�ǵĻ�����ѭ��
		int 0x10		;������ʾ
	jmp .ReadChar
.EndOfString:
	pop si
endproc


;��ʾʮ�������ֵĺ���
proc	_ShowDecU
	mov ax,[arg(0)]
	xor cx,cx			;cx����������
.PushNums:				;�Ȱ�ÿ����λ��ѹ���ջ
	xor dx,dx			;���������16λ
	div word[Ten]		;ax����10
	push dx				;ѹ������
	inc cx				;λ����1
	or ax,ax			;�ж��Ƿ����
	jnz .PushNums		;���ǵĻ�������
	mov dx,7			;ͼ��ģʽ����ɫ
.ShowNums:				;�ٰѶ�ջ�е���λȡ��
	pop ax				;ȡ������
	add al,'0'			;����ASCII��
	mov ah,0x0E			;��ʾ�ı��Ĺ���
	int 0x10			;��ʾ�ı�
	loop .ShowNums		;ѭ����ʾ�����ı�
endproc
;�з��Ű�
proc	_ShowDec
	mov ax,[arg(0)]
	or ax,ax			;�ж��Ƿ�С��0
	jns .ContinueShow	;��С�����������ʾ
	neg ax				;����axȡ��
	push ax
	mov ax,0x0E00|'-'	;������ʾһ������
	mov dx,7			;dx=ͼ��ģʽ��ɫ
	int 0x10
	pop ax
.ContinueShow:
	xor cx,cx			;cx����������
.PushNums:				;�Ȱ�ÿ����λ��ѹ���ջ
	xor dx,dx			;���������16λ
	div word[Ten]		;ax����10
	push dx				;ѹ������
	inc cx				;λ����1
	or ax,ax			;�ж��Ƿ����
	jnz .PushNums		;���ǵĻ�������
	mov dx,7			;ͼ��ģʽ����ɫ
.ShowNums:				;�ٰѶ�ջ�е���λȡ��
	pop ax				;ȡ������
	add al,'0'			;����ASCII��
	mov ah,0x0E			;��ʾ�ı��Ĺ���
	int 0x10			;��ʾ�ı�
	loop .ShowNums		;ѭ����ʾ�����ı�
endproc


;��ʾ16�������ֵĺ���
;���룺
	;ax=����
;���أ�
	;ax=0
	;cx=0
	;dx=7
proc	_ShowHexU
	mov ax,[arg(0)]
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
;�з��Ű�
proc	_ShowHex
	mov ax,[arg(0)]
	or ax,ax			;�ж��Ƿ�С��0
	jns .ContinueShow	;��С�����������ʾ
	neg ax				;����axȡ��
	push ax
	mov ax,0x0E00|'-'	;������ʾһ������
	mov dx,7			;dx=ͼ��ģʽ��ɫ
	int 0x10
	pop ax
.ContinueShow:
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
Ten	dw	10				;���������ĳ���

