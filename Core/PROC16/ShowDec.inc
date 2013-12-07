;显示数字的函数
;输入：
	;ax=数字
;返回：
	;ax破坏(ah=0x0e,al=最后一个数字字符的ASCII码)
	;cx=0
	;dx=7
ShowDec:
	xor cx,cx		;cx用作计数器
.PushNums:			;先把每个数位都压入堆栈
	xor dx,dx		;清除除法高16位
	div word[cs:.10];ax除以10
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
	ret				;返回
.10	dw	10			;用作除数的常数
