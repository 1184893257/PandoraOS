;显示16进制数字的函数
;输入：
	;ax=数字
;返回：
	;ax=0
	;cx=0
	;dx=7
ShowHex:
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
	ret					;返回
