%ifndef	_KEYBOARD_INCLUDED_
%define	_KEYBOARD_INCLUDED_

%define	KBDCMD_WRITELED	0xED	;改写LED，输出此命令之后要输出LED信息
%define	KBDCMD_ECHO		0xEE	;输出此命令之后要从键盘读取一个字节是否为0xEE
%define	KBDCMD_SETSCAN	0xF0	;设置扫描码集
%define	KBDCMD_GETID	0xF2	;输出此命令之后要从键盘读取两个字节的ID
%define	KBDCMD_SETRATE	0xF3	;输出此命令之后要再输出一个字节给键盘来设置键盘按键速率
%define	KBDCMD_OPENKBD	0xF4	;开放键盘
%define	KBDCMD_RESETKBD	0xF5	;重置键盘
%define	KBDCMD_SETDEF	0xF6	;键盘恢复到默认状态
%define	KBDCMD_AKNBREAK	0xF7	;所有键没有断码
%define	KBDCMD_AKEYMKBR	0xF8	;所有键有通码、断码，机打被禁止
%define	KBDCMD_AKEYMAKE	0xF9	;所有键只有通码，断码和机打被禁止
%define	KBDCMD_TPMATIC	0xFA	;允许通码、断码、机打
%define	KBDCMD_NOBREAK	0xFB	;没有断码
%define	KBDCMD_ONLYMKBR	0xFC	;只有通码和断码，机打被禁止
%define	KBDCMD_ONLYMAKE	0xFD	;只有通码，断码和机打被禁止
%define	KBDCMD_RESEND	0xFE	;要求键盘重新发送最后一个字节
%define	KBDCMD_RESTART	0xFF	;完全重启键盘

%define	KBDACK_OVERFLOW	0x00	;键盘缓冲区满
%define	KBDACK_POSTOK	0xAA	;自检成功
%define	KBDACK_ECHO		0xEE	;键盘回应
%define	KBDACK_BREAKPFX	0xF0	;BREAK前缀
%define	KBDACK_ACK		0xFA	;键盘受到命令之后回应
%define	KBDACK_POSTFAIL	0xFC	;自检失败
%define	KBDACK_INTRNL	0xFD	;内部错误
%define	KBDACK_RESEND	0xFE	;键盘要求主机重新发送
%define	KBDACK_OVERFLOW	0xFF	;键盘缓冲区满

%endif
