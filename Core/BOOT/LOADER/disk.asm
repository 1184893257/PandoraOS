;##############################################################################
;
;disk.asm
;LOADERר��Ӳ���������ṩӲ�̵Ķ�д����
;
;##############################################################################

%include"aglobal.inc"

global	_bDiskInt13Ex

segment	_TEXT

;bool CheckInt13ExAvailable(void);
proc	_CheckInt13ExAvailable
	push bx
	mov byte[_bDiskInt13Ex],0	;INT13��չ���ܼ��=false
	mov ah,0x41					;���INT13��չ����
	mov bx,0x55AA
	mov dl,0x80
	int 0x13
	jc .ExChecked
	cmp bx,0xAA55
	jnz .ExChecked
	mov byte[_bDiskInt13Ex],1	;INT13��չ���ܼ��=true
.ExChecked:
	movzx ax,byte[_bDiskInt13Ex];����INT13��չ���ܼ����
	pop bx
endproc

;int CheckDiskType(byte bDriver);
proc	_CheckDiskType
	mov ax,0x15ff				;����������
	mov cx,0xffff
	mov dl,[arg(0)]
	int 0x13
	shr ax,8
endproc
;���أ�
;0:û���������
;1:û��change-line֧�ֵ�����
;2:��change-line֧�ֵ�����
;3:Ӳ��

;void CHSToLBA_FDD(WORD C,WORD H,WORD S,WORD CMax,WORD HMax,WORD SMax,DWORD* pLBAOut);
proc	_CHSToLBA
	;LBA=����+��ͷ*ÿ�ŵ�������+ÿ�ŵ�������*��ͷ��*�����-1
	movzx eax,word[arg(5)]
	movzx edx,word[arg(4)]		;����32λ�˷���ÿ�ŵ�������*��ͷ��
	mul edx
	movzx edx,word[arg(0)]		;ÿ�ŵ�������*��ͷ��*�����
	mul edx
	push edx					;�����ջ
	push eax
	movzx eax,word[arg(5)]
	mul word[arg(1)]			;��ͷ*ÿ�ŵ�������
	shl edx,16
	or eax,edx
	xor edx,edx
	add [esp],eax				;�ӵ���ջ�е�ֵ
	adc [esp+4],edx
	movzx eax,word[arg(2)]		;������
	dec ax						;��ȥ1
	add [esp],eax
	adc [esp+4],edx				;�ӵ���ջ�е�ֵ
	mov cx,bx
	mov bx,[arg(6)]				;ȡpLBAOut
	pop dword[bx]				;������ջ�е�ֵ
	pop dword[bx+4]
	mov bx,cx					;�ָ�bx
endproc




segment	_DATA

segment	_BSS
_bDiskInt13Ex		resb	1

