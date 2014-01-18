%define	_KBDCTRL_ASM_

%include"ASMCOM.INC"
%include"KBDCTRL.INC"
%include"KEYBOARD.INC"

global	_KBDInput		;从键盘读取一个字节
global	_KBDOutput		;输出一个字节到键盘
global	_KBDReadStatus	;从键盘控制器读取一个字节
global	_KBDSendCommand	;输出一个字节到键盘控制器

segment _TEXT
_KBDInput:				;BYTE KBDInput(void);
	in al,KBD_CTRLPORT
	test al,1
	jz _KBDInput		;等键盘发送字节过来
	
	in al,KBD_KBDPORT	;读取
	ret

_KBDOutput:				;void KBDOutput(BYTE);
	push bp
	mov bp,sp
	
.WaitForKeyboard:
	in al,KBD_CTRLPORT
	test al,2
	jnz .WaitForKeyboard;等键盘处理完字节

	mov al,[ARG(0)]
	out KBD_KBDPORT,al	;输出这个字节

	pop bp
	ret

_KBDReadStatus:			;BYTE KBDReadStatus(void);
	in al,KBD_CTRLPORT
	ret

_KBDSendCommand:		;void KBDSendCommand(BYTE);
	push bp
	mov bp,sp
	
	mov al,[ARG(0)]
	out KBD_CTRLPORT,al	;输出这个字节
	
	pop bp
	ret




