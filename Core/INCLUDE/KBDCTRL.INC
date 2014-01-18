%ifndef	_KEYBOARD_CONTROLLER_INCLUDED_
%define	_KEYBOARD_CONTROLLER_INCLUDED_

%ifndef	_KBDCTRL_ASM_
extern	_KBDInput		;从键盘读取一个字节
extern	_KBDOutput		;输出一个字节到键盘
extern	_KBDReadStatus	;从键盘控制器读取一个字节
extern	_KBDSendCommand	;输出一个字节到键盘控制器
%endif

%define	KBD_KBDPORT		0x60
%define	KBD_CTRLPORT	0x64

%define	KBDCTRLCMD_DISABLEMOUSE	0xA7	;禁止鼠标接口
%define	KBDCTRLCMD_ENABLEMOUSE	0xA8	;打开鼠标接口
%define	KBDCTRLCMD_MOUSETEST	0xA9	;鼠标接口测试
%define	KBDCTRLCMD_CTRLPOST		0xAA	;控制器自检
%define	KBDCTRLCMD_KBDTEST		0xAB	;键盘接口测试
%define	KBDCTRLCMD_DISABLEKBD	0xAD	;禁止键盘接口
%define	KBDCTRLCMD_ENABLEKBD	0xAE	;打开键盘接口
%define	KBDCTRLCMD_GETVERSION	0xAF	;获取版本
%define	KBDCTRLCMD_READOUTPUT	0xD0	;读输出端口
%define	KBDCTRLCMD_WRITEOUTPUT	0xD1	;写输出端口
%define	KBDCTRLCMD_KEYEMU		0xD2	;写键盘缓冲区
%define	KBDCTRLCMD_MOUSEEMU		0xD3	;写鼠标缓冲区
%define	KBDCTRLCMD_SENDTOMOUSE	0xD4	;下一个命令输出给鼠标
%define	KBDCTRLCMD_READTEST		0xE0

%define	KBDCTRLOUTPUT_A20		0x02	;输出端口开启A20位

%endif
