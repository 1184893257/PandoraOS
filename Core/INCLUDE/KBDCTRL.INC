%ifndef	_KEYBOARD_CONTROLLER_INCLUDED_
%define	_KEYBOARD_CONTROLLER_INCLUDED_

%ifndef	_KBDCTRL_ASM_
extern	_KBDInput		;�Ӽ��̶�ȡһ���ֽ�
extern	_KBDOutput		;���һ���ֽڵ�����
extern	_KBDReadStatus	;�Ӽ��̿�������ȡһ���ֽ�
extern	_KBDSendCommand	;���һ���ֽڵ����̿�����
%endif

%define	KBD_KBDPORT		0x60
%define	KBD_CTRLPORT	0x64

%define	KBDCTRLCMD_DISABLEMOUSE	0xA7	;��ֹ���ӿ�
%define	KBDCTRLCMD_ENABLEMOUSE	0xA8	;�����ӿ�
%define	KBDCTRLCMD_MOUSETEST	0xA9	;���ӿڲ���
%define	KBDCTRLCMD_CTRLPOST		0xAA	;�������Լ�
%define	KBDCTRLCMD_KBDTEST		0xAB	;���̽ӿڲ���
%define	KBDCTRLCMD_DISABLEKBD	0xAD	;��ֹ���̽ӿ�
%define	KBDCTRLCMD_ENABLEKBD	0xAE	;�򿪼��̽ӿ�
%define	KBDCTRLCMD_GETVERSION	0xAF	;��ȡ�汾
%define	KBDCTRLCMD_READOUTPUT	0xD0	;������˿�
%define	KBDCTRLCMD_WRITEOUTPUT	0xD1	;д����˿�
%define	KBDCTRLCMD_KEYEMU		0xD2	;д���̻�����
%define	KBDCTRLCMD_MOUSEEMU		0xD3	;д��껺����
%define	KBDCTRLCMD_SENDTOMOUSE	0xD4	;��һ��������������
%define	KBDCTRLCMD_READTEST		0xE0

%define	KBDCTRLOUTPUT_A20		0x02	;����˿ڿ���A20λ

%endif