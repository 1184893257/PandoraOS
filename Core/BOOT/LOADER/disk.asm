;##############################################################################
;
;disk.asm
;LOADER专用硬盘驱动，提供硬盘的读写功能
;
;##############################################################################

%include"aglobal.inc"

global	_bDiskInt13Ex

segment	_TEXT

;bool CheckInt13ExAvailable(void);
proc	_CheckInt13ExAvailable
	push bx
	mov byte[_bDiskInt13Ex],0	;INT13扩展功能检测=false
	mov ah,0x41					;检查INT13扩展功能
	mov bx,0x55AA
	mov dl,0x80
	int 0x13
	jc .ExChecked
	cmp bx,0xAA55
	jnz .ExChecked
	mov byte[_bDiskInt13Ex],1	;INT13扩展功能检测=true
.ExChecked:
	movzx ax,byte[_bDiskInt13Ex];返回INT13扩展功能检测结果
	pop bx
endproc

;int CheckDiskType(byte bDriver);
proc	_CheckDiskType
	mov ax,0x15ff				;检查磁盘类型
	mov cx,0xffff
	mov dl,[arg(0)]
	int 0x13
	shr ax,8
endproc
;返回：
;0:没有这个磁盘
;1:没有change-line支持的软盘
;2:有change-line支持的软盘
;3:硬盘

;void CHSToLBA_FDD(WORD C,WORD H,WORD S,WORD CMax,WORD HMax,WORD SMax,DWORD* pLBAOut);
proc	_CHSToLBA
	;LBA=扇区+磁头*每磁道扇区数+每磁道扇区数*磁头数*柱面号-1
	movzx eax,word[arg(5)]
	movzx edx,word[arg(4)]		;进行32位乘法，每磁道扇区数*磁头数
	mul edx
	movzx edx,word[arg(0)]		;每磁道扇区数*磁头数*柱面号
	mul edx
	push edx					;存入堆栈
	push eax
	movzx eax,word[arg(5)]
	mul word[arg(1)]			;磁头*每磁道扇区数
	shl edx,16
	or eax,edx
	xor edx,edx
	add [esp],eax				;加到堆栈中的值
	adc [esp+4],edx
	movzx eax,word[arg(2)]		;扇区号
	dec ax						;减去1
	add [esp],eax
	adc [esp+4],edx				;加到堆栈中的值
	mov cx,bx
	mov bx,[arg(6)]				;取pLBAOut
	pop dword[bx]				;弹出堆栈中的值
	pop dword[bx+4]
	mov bx,cx					;恢复bx
endproc




segment	_DATA

segment	_BSS
_bDiskInt13Ex		resb	1

