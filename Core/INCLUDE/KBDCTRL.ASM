%define	_KBDCTRL_ASM_

%include"ASMCOM.INC"
%include"KBDCTRL.INC"
%include"KEYBOARD.INC"

global	_KBDInput		;�Ӽ��̶�ȡһ���ֽ�
global	_KBDOutput		;���һ���ֽڵ�����
global	_KBDReadStatus	;�Ӽ��̿�������ȡһ���ֽ�
global	_KBDSendCommand	;���һ���ֽڵ����̿�����

segment _TEXT
_KBDInput:				;BYTE KBDInput(void);
	in al,KBD_CTRLPORT
	test al,1
	jz _KBDInput		;�ȼ��̷����ֽڹ���
	
	in al,KBD_KBDPORT	;��ȡ
	ret

_KBDOutput:				;void KBDOutput(BYTE);
	push bp
	mov bp,sp
	
.WaitForKeyboard:
	in al,KBD_CTRLPORT
	test al,2
	jnz .WaitForKeyboard;�ȼ��̴������ֽ�

	mov al,[ARG(0)]
	out KBD_KBDPORT,al	;�������ֽ�

	pop bp
	ret

_KBDReadStatus:			;BYTE KBDReadStatus(void);
	in al,KBD_CTRLPORT
	ret

_KBDSendCommand:		;void KBDSendCommand(BYTE);
	push bp
	mov bp,sp
	
	mov al,[ARG(0)]
	out KBD_CTRLPORT,al	;�������ֽ�
	
	pop bp
	ret



