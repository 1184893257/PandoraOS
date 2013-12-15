;##############################################################################
;
;video.asm
;LOADER专用显示部分的驱动，负责帮助打印文本等信息。
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


;显示十进制数字的函数
proc	_ShowDec
	mov ax,[arg(0)]
	xor cx,cx		;cx用作计数器
.PushNums:			;先把每个数位都压入堆栈
	xor dx,dx		;清除除法高16位
	div word[Ten]	;ax除以10
	push dx			;压入余数
	inc cx			;位数加1
	or ax,ax		;判断是否除完
	jnz .PushNums	;不是的话继续除
	mov dx,7		;图形模式的颜色
.ShowNums:			;再把堆栈中的数位取回
	pop ax			;取回数字
	add al,'0'		;生成ASCII码
	mov ah,0x0E		;显示文本的功能
	int 0x10		;显示文本
	loop .ShowNums	;循环显示所有文本
endproc


;显示16进制数字的函数
;输入：
	;ax=数字
;返回：
	;ax=0
	;cx=0
	;dx=7
proc	_ShowHex
	mov cx,4			;4个数位
	mov dx,7			;图形模式下的颜色
.ShowNum:				;循环显示数位
	push ax				;保存AX
	shr ax,12			;取最高位
	cmp al,10			;判断是否小于10
	jb .LessThan10		;是的话跳过
	add al,'A'-'0'-10	;否则使其显示为A-F
.LessThan10:			;小于10
	add al,'0'			;则为0-9
	mov ah,0x0E			;显示字符的功能
	int 0x10			;中断
	pop ax				;取回AX
	shl ax,4			;设置下一个数位
	loop .ShowNum		;循环显示下一个数位
endproc


segment	_DATA
Ten	dw	10			;用作除数的常数

