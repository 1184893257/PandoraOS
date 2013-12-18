;##############################################################################
;
;entry.asm
;整个loader.sys的入口点，提供了入口点函数
;并对各个段寄存器进行了设置，然后调用c部分的入口点。
;
;##############################################################################

%include"aglobal.inc"

global	_start			;全局入口点
global	_stack			;堆栈
global	_HaltMessage	;main程序不应该返回，如果返回则打印“已当机”的消息

extern	_main			;c程序的main入口点void main(void)

segment	_TEXT			;代码段
resb 0x7C00				;代码段的开始位置，段内偏移在0x7C00处
_start:
	mov ax,DGROUP		;设置好数据段
	mov ds,ax
	mov es,ax
	mov ss,ax			;设置好堆栈
	mov sp,STACKSIZE
	mov bp,sp
	call _main			;调用c的main函数

	cli					;这里应该当机，不处理中断
	mov ax,0x3			;恢复到文本模式以显示文本
	int 0x10
	mov ax,_DATA		;重新设置数据段
	mov ds,ax
	mov si,_HaltMessage	;显示当机消息
	mov ah,0x0E			;打印文本的功能
	mov dx,7			;白色
.LoopShow:
	lodsb				;读入字符
	or al,al			;判断是否为\0
	jz .LoopOver		;是就跳出
	int 0x10			;否则显示文本
	jmp .LoopShow		;循环打印字符
.LoopOver:
	cli
	hlt					;结束当机
	jmp .LoopOver		;为了防止NMI，这里再次当机


segment	_DATA
_HaltMessage	db "Now system is halted. You can turn off the power.",0



segment	_STACK
_stack	resb	STACKSIZE
