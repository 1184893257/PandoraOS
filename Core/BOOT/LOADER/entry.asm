;##############################################################################
;
;entry.asm
;����loader.sys����ڵ㣬�ṩ����ڵ㺯��
;���Ը����μĴ������������ã�Ȼ�����c���ֵ���ڵ㡣
;
;##############################################################################

%include"aglobal.inc"

global	_start			;ȫ����ڵ�
global	_stack			;��ջ
global	_HaltMessage	;main����Ӧ�÷��أ�����������ӡ���ѵ���������Ϣ

extern	_main			;c�����main��ڵ�void main(void)

segment	_TEXT			;�����
resb 0x7C00				;����εĿ�ʼλ�ã�����ƫ����0x7C00��
_start:
	mov ax,DGROUP		;���ú����ݶ�
	mov ds,ax
	mov es,ax
	mov ss,ax			;���úö�ջ
	mov sp,STACKSIZE
	mov bp,sp
	call _main			;����c��main����

	cli					;����Ӧ�õ������������ж�
	mov ax,0x3			;�ָ����ı�ģʽ����ʾ�ı�
	int 0x10
	mov ax,_DATA		;�����������ݶ�
	mov ds,ax
	mov si,_HaltMessage	;��ʾ������Ϣ
	mov ah,0x0E			;��ӡ�ı��Ĺ���
	mov dx,7			;��ɫ
.LoopShow:
	lodsb				;�����ַ�
	or al,al			;�ж��Ƿ�Ϊ\0
	jz .LoopOver		;�Ǿ�����
	int 0x10			;������ʾ�ı�
	jmp .LoopShow		;ѭ����ӡ�ַ�
.LoopOver:
	cli
	hlt					;��������
	jmp .LoopOver		;Ϊ�˷�ֹNMI�������ٴε���


segment	_DATA
_HaltMessage	db "Now system is halted. You can turn off the power.",0



segment	_STACK
_stack	resb	STACKSIZE
