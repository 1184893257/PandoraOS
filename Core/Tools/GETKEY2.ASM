org 0x100
bits 16

Start:
xor ax,ax
mov es,ax
cli
mov eax,[es:0x09*4]
mov [OldKBDInt],eax
mov word[es:0x09*4],KBDInt
mov [es:0x09*4+2],cs
sti
WaitKey:
hlt
cmp byte[ReadyToQuit],0
jz WaitKey
cli
mov eax,[OldKBDInt]
mov [es:0x09*4],eax
sti
int 0x20

OldKBDInt dd 0
KBDInt:				;键盘中断处理过程
	push ax
	in al,0x60
	cmp al,0x81
	jnz .GoOn
	inc byte[cs:ReadyToQuit]
.GoOn:
	mov ah,0
	push ax			;保存AX
	call ShowHex	;显示16进制扫描码
	call ShowSpace
	int 0x10	;再显示一个空格
	pop ax			;取回AX
	call ShowDec	;显示10进制扫描码
	call ShowCrLf

	mov al,0x61
	out 0x20,al
	pop ax
	iret
ReadyToQuit db 0

;输出一个换行符的函数
;返回：
	;ax=0x0E0A
%include "ShowCrLf.inc"

;显示数字的函数
;输入：
	;ax=数字
;输出：
	;dx=7
	;ax破坏(ah=0x0e,al=最后一个数字字符的ASCII码)
	;cx=0
%include "ShowDec.inc"

;显示16进制数字的函数
;输入：
	;ax=数字
;输出：
	;ax=0
	;cx=0
	;dx=7
%include "ShowHex.inc"

;输出空格的函数
;输出：
	;ax=ax,0x0E20
	;cx=0
	;dx=7
ShowSpace:
	mov ax,0x0E20
	mov dx,7
	int 0x10
	ret