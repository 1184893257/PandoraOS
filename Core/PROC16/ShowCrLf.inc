;输出一个换行符的函数
;返回：
	;ax=0x0E0A
ShowCrLf:
	mov ax,0x0E0D	;输出一个Cr
	int 0x10
	mov al,0x0A		;输出一个Lf
	int 0x10
	ret