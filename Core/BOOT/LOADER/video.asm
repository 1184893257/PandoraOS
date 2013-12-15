;##############################################################################
;
;video.asm
;LOADER专用显示部分的驱动，负责帮助打印文本等信息。
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
	movzx ax,byte[arg(0)]	;读取参数
	int 0x10				;INT 0x10功能0：设置显示模式
endproc

proc	_SwitchToTextMode
	push word 3				;压入参数3
	call _SwitchVideoMode	;切换显示模式
endproc	2					;弹出参数恢复堆栈平衡

proc	_SwitchTo320x200
	push word 0x13			;压入参数0x13
	call _SwitchVideoMode	;切换显示模式
endproc	2					;弹出参数恢复堆栈平衡

proc	_Print			;打印字符串的函数
	push si				;保存si，因为TC使用si、di用作变量寄存器
	mov	si,[arg(0)]		;arg(0)是char*
	mov dx,7			;dx=7=图形模式下的（灰）白色
	mov ah,0x0E			;INT 0x10 AH=0x0E 打印字符功能
.ReadChar:
		lodsb			;读取一个字符
		or al,al		;判断是否结尾'\0'
		jz .EndOfString	;是的话跳出循环
		int 0x10		;否则显示
	jmp .ReadChar
.EndOfString:
	pop si
endproc


;显示十进制数字的函数
proc	_ShowDecU
	mov ax,[arg(0)]
	xor cx,cx			;cx用作计数器
.PushNums:				;先把每个数位都压入堆栈
	xor dx,dx			;清除除法高16位
	div word[Ten]		;ax除以10
	push dx				;压入余数
	inc cx				;位数加1
	or ax,ax			;判断是否除完
	jnz .PushNums		;不是的话继续除
	mov dx,7			;图形模式的颜色
.ShowNums:				;再把堆栈中的数位取回
	pop ax				;取回数字
	add al,'0'			;生成ASCII码
	mov ah,0x0E			;显示文本的功能
	int 0x10			;显示文本
	loop .ShowNums		;循环显示所有文本
endproc
;有符号版
proc	_ShowDec
	mov ax,[arg(0)]
	or ax,ax			;判断是否小于0
	jns .ContinueShow	;不小于零则继续显示
	neg ax				;否则ax取反
	push ax
	mov ax,0x0E00|'-'	;并且显示一个负号
	mov dx,7			;dx=图形模式颜色
	int 0x10
	pop ax
.ContinueShow:
	xor cx,cx			;cx用作计数器
.PushNums:				;先把每个数位都压入堆栈
	xor dx,dx			;清除除法高16位
	div word[Ten]		;ax除以10
	push dx				;压入余数
	inc cx				;位数加1
	or ax,ax			;判断是否除完
	jnz .PushNums		;不是的话继续除
	mov dx,7			;图形模式的颜色
.ShowNums:				;再把堆栈中的数位取回
	pop ax				;取回数字
	add al,'0'			;生成ASCII码
	mov ah,0x0E			;显示文本的功能
	int 0x10			;显示文本
	loop .ShowNums		;循环显示所有文本
endproc


;显示16进制数字的函数
;输入：
	;ax=数字
;返回：
	;ax=0
	;cx=0
	;dx=7
proc	_ShowHexU
	mov ax,[arg(0)]
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
;有符号版
proc	_ShowHex
	mov ax,[arg(0)]
	or ax,ax			;判断是否小于0
	jns .ContinueShow	;不小于零则继续显示
	neg ax				;否则ax取反
	push ax
	mov ax,0x0E00|'-'	;并且显示一个负号
	mov dx,7			;dx=图形模式颜色
	int 0x10
	pop ax
.ContinueShow:
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
Ten	dw	10				;用作除数的常数

