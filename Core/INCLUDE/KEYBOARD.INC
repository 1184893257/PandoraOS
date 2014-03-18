%ifndef	_KEYBOARD_INCLUDED_
%define	_KEYBOARD_INCLUDED_

%define	KBDCMD_WRITELED	0xED	;��дLED�����������֮��Ҫ���LED��Ϣ
%define	KBDCMD_ECHO		0xEE	;���������֮��Ҫ�Ӽ��̶�ȡһ���ֽ��Ƿ�Ϊ0xEE
%define	KBDCMD_SETSCAN	0xF0	;����ɨ���뼯
%define	KBDCMD_GETID	0xF2	;���������֮��Ҫ�Ӽ��̶�ȡ�����ֽڵ�ID
%define	KBDCMD_SETRATE	0xF3	;���������֮��Ҫ�����һ���ֽڸ����������ü��̰�������
%define	KBDCMD_OPENKBD	0xF4	;���ż���
%define	KBDCMD_RESETKBD	0xF5	;���ü���
%define	KBDCMD_SETDEF	0xF6	;���ָ̻���Ĭ��״̬
%define	KBDCMD_AKNBREAK	0xF7	;���м�û�ж���
%define	KBDCMD_AKEYMKBR	0xF8	;���м���ͨ�롢���룬���򱻽�ֹ
%define	KBDCMD_AKEYMAKE	0xF9	;���м�ֻ��ͨ�룬����ͻ��򱻽�ֹ
%define	KBDCMD_TPMATIC	0xFA	;����ͨ�롢���롢����
%define	KBDCMD_NOBREAK	0xFB	;û�ж���
%define	KBDCMD_ONLYMKBR	0xFC	;ֻ��ͨ��Ͷ��룬���򱻽�ֹ
%define	KBDCMD_ONLYMAKE	0xFD	;ֻ��ͨ�룬����ͻ��򱻽�ֹ
%define	KBDCMD_RESEND	0xFE	;Ҫ��������·������һ���ֽ�
%define	KBDCMD_RESTART	0xFF	;��ȫ��������

%define	KBDACK_OVERFLOW	0x00	;���̻�������
%define	KBDACK_POSTOK	0xAA	;�Լ�ɹ�
%define	KBDACK_ECHO		0xEE	;���̻�Ӧ
%define	KBDACK_BREAKPFX	0xF0	;BREAKǰ׺
%define	KBDACK_ACK		0xFA	;�����ܵ�����֮���Ӧ
%define	KBDACK_POSTFAIL	0xFC	;�Լ�ʧ��
%define	KBDACK_INTRNL	0xFD	;�ڲ�����
%define	KBDACK_RESEND	0xFE	;����Ҫ���������·���
%define	KBDACK_OVERFLOW	0xFF	;���̻�������

%endif