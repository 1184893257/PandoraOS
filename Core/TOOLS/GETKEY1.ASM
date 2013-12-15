org 0x100
bits 16

Start:
GetKey:
xor ax,ax
int 0x16

mov bx,ax

;显示16进制扫描码
mov al,ah
mov ah,0
call ShowHex

mov ax,0x0E09
int 0x10

mov ax,bx
;显示10进制扫描码
mov al,ah
mov ah,0
call ShowDec

;输出一个TAB
mov ax,0x0E09
int 0x10

;显示16进制ASCII码
mov ax,bx
mov ah,0
call ShowHex

;输出一个TAB
mov ax,0x0E09
int 0x10

;显示10进制ASCII码
mov ax,bx
mov ah,0
call ShowDec

;输出一个TAB
mov ax,0x0E09
int 0x10

;打印ASCII字符
mov al,bl
mov ah,0x0E
int 0x10

;换行
mov ax,0x0E0D
int 0x10
mov al,0x0A
int 0x10

mov ax,bx
cmp ah,0x01
jnz GetKey
int 0x20


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

