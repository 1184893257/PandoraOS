;##############################################################################
;
;disk.asm
;LOADERר��Ӳ���������ṩӲ�̵Ķ�д����
;
;##############################################################################

%include"aglobal.inc"

global	_bDiskInit
global	_bDiskInt13Ex

segment	_TEXT
proc	_InitDisk
	push bx
	mov word[_bDiskInit],0		;��ʼ��״̬=FALSE��INT13��չ���ܼ��=false
	mov ah,0x41
	mov bx,0x55AA
	mov dl,0x80
	int 0x13
	jc .ExChecked
	cmp bx,0xAA55
	jnz .ExChecked
	mov byte[_bDiskInt13Ex],1
.ExChecked:
	
	pop bx
endproc








segment	_DATA

segment	_BSS
_bDiskInit			db	0
_bDiskInt13Ex		db	0
