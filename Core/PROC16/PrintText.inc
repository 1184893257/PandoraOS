;打印文本的函数
;参数：
	;si=文本
;返回：
	;si=文本末尾
	;dx=7
	;ax=0x0E00
PrintText:
	mov ah,0x0E		;打印文本的功能
	mov dx,7		;图形模式颜色
.ShowChar:			;循环显示字符
	lodsb			;载入字符
	or al,al		;判断是否字符尾
	jz .EndOfString	;字符尾，跳出
	int 0x10		;否则显示字符
	jmp .ShowChar	;循环显示字符
.EndOfString:		;循环退出
	ret				;返回