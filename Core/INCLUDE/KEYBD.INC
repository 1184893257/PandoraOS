%ifndef	__KEYBOARD_HEADER__
%define	__KEYBOARD_HEADER__

;按键定义的头文件，如果扫描码与SCANF_KEYUP的值逻辑与为真，为断码
;如果接收到SCAN_EXTEND信息，意味着按键是特殊按键

%define	SCANF_KEYUP			0x80

;普通按键
%define	SCAN_ESC			0x01
%define	SCAN_1				0x02
%define	SCAN_2				0x03
%define	SCAN_3				0x04
%define	SCAN_4				0x05
%define	SCAN_5				0x06
%define	SCAN_6				0x07
%define	SCAN_7				0x08
%define	SCAN_8				0x09
%define	SCAN_9				0x0A
%define	SCAN_0				0x0B
%define	SCAN_MINUS			0x0C;	-
%define	SCAN_EQUALS			0x0D;	=
%define	SCAN_BACK			0x0E
%define	SCAN_TAB			0x0F
%define	SCAN_Q				0x10
%define	SCAN_W				0x11
%define	SCAN_E				0x12
%define	SCAN_R				0x13
%define	SCAN_T				0x14
%define	SCAN_Y				0x15
%define	SCAN_U				0x16
%define	SCAN_I				0x17
%define	SCAN_O				0x18
%define	SCAN_P				0x19
%define	SCAN_LBRACKET		0x1A;	[
%define	SCAN_RBRACKET		0x1B;	]
%define	SCAN_ENTER			0x1C
%define	SCAN_LCRTL			0x1D
%define	SCAN_A				0x1E
%define	SCAN_S				0x1F
%define	SCAN_D				0x20
%define	SCAN_F				0x21
%define	SCAN_G				0x22
%define	SCAN_H				0x23
%define	SCAN_J				0x24
%define	SCAN_K				0x25
%define	SCAN_L				0x26
%define	SCAN_SEMICOLON		0x27;	;
%define	SCAN_APOSTROPHE		0x28;	'
%define	SCAN_GRAVE			0x29;	`
%define	SCAN_LSHIFT			0x2A
%define	SCAN_BACKSLASH		0x2B;	|
%define	SCAN_Z				0x2C
%define	SCAN_X				0x2D
%define	SCAN_C				0x2E
%define	SCAN_V				0x2F
%define	SCAN_B				0x30
%define	SCAN_N				0x31
%define	SCAN_M				0x32
%define	SCAN_COMMA			0x33;	,
%define	SCAN_DOT			0x34;	.
%define	SCAN_SLASH			0x35;	/
%define	SCAN_RSHIFT			0x36
%define	SCAN_NUMMULTIPLY	0x37;	*
%define	SCAN_LALT			0x38
%define	SCAN_SPACE			0x39
%define	SCAN_CAPSLOCK		0x3A
%define	SCAN_F1				0x3B
%define	SCAN_F2				0x3C
%define	SCAN_F3				0x3D
%define	SCAN_F4				0x3E
%define	SCAN_F5				0x3F
%define	SCAN_F6				0x40
%define	SCAN_F7				0x41
%define	SCAN_F8				0x42
%define	SCAN_F9				0x43
%define	SCAN_F10			0x44
%define	SCAN_NUMLOCK		0x45
%define	SCAN_SCROLLLOCK		0x46
%define	SCAN_NUM7			0x47
%define	SCAN_NUM8			0x48
%define	SCAN_NUM9			0x49
%define SCAN_NUMMINUS		0x4A;	-
%define	SCAN_NUM4			0x4B
%define	SCAN_NUM5			0x4C
%define	SCAN_NUM6			0x4D
%define	SCAN_NUMADD			0x4E;	+
%define	SCAN_NUM1			0x4F
%define	SCAN_NUM2			0x50
%define	SCAN_NUM3			0x51
%define	SCAN_NUM0			0x52
%define	SCAN_NUMDOT			0x53;	.
%define	SCAN_OEM_102		0x56
%define	SCAN_F11			0x57
%define	SCAN_F12			0x58
%define	SCAN_F13			0x64
%define	SCAN_F14			0x65
%define	SCAN_F15			0x66

%define	SCAN_EXTEND			0xE0
;以下按键的特殊性：
;通码：
	;SCAN_EXTEND
	;扫描码
;断码：
	;SCAN_EXTEND
	;扫描码|SCANF_KEYUP

%define	SCAN_NUMEQUAL		0x0D;	小键盘等号
%define	SCAN_PLAYPREV		0x10;	上一曲
%define	SCAN_PLAYNEXT		0x19;	下一曲
%define	SCAN_NUMENTER		0x1C;	小键盘Enter
%define	SCAN_RCTRL			0x1D;	右Ctrl
%define	SCAN_CALC			0x21;	计算器
%define	SCAN_PLAYPAUSE		0x22;	播放、暂停
%define	SCAN_PLAYSTOP		0x24;	停止播放
%define	SCAN_VOLUMEDOWN		0x2E;	调小音量
%define	SCAN_VOLUMEUP		0x30;	调大音量
%define	SCAN_WEBHOME		0x32;	网页主页
%define	SCAN_NUMSLASH		0x35;	小键盘撇号
%define	SCAN_RALT			0x38;	右Alt
%define	SCAN_WIN			0x5B;	徽标键
%define	SCAN_MENU			0x5D;	菜单键
%define	SCAN_POWER			0x5E;	电源
%define	SCAN_SLEEP			0x5F;	睡眠
%define	SCAN_FN				0x63;	笔记本电脑FN键
%define	SCAN_WEBSEARCH		0x65;	网页搜索
%define	SCAN_WEBFAVORITES	0x66;	网页收藏夹
%define	SCAN_WEBREFRESH		0x67;	网页刷新
%define	SCAN_WEBSTOP		0x68;	网页停止
%define	SCAN_WEBFORWARD		0x69;	网页前进
%define	SCAN_WEBBACK		0x6A;	网页后退
%define	SCAN_MYCOMPUTER		0x6B;	我的电脑
%define	SCAN_MAIL			0x6C;	邮件
%define	SCAN_MEDIASELECT	0x6D;	选歌

;以下按键的特殊性：
;通码：
	;SCAN_EXTEND
	;SCAN_LSHIFT
	;SCAN_EXTEND
	;扫描码
;断码：
	;SCAN_EXTEND
	;扫描码|SCANF_KEYUP
	;SCAN_EXTEND
	;SCAN_LSHIFT|SCANF_KEYUP

%define	SCAN_PRTSC			0x37
%define	SCAN_HOME			0x47
%define	SCAN_UP				0x48
%define	SCAN_PAGEUP			0x49
%define	SCAN_LEFT			0x4B
%define	SCAN_RIGHT			0x4D
%define	SCAN_END			0x4F
%define	SCAN_DOWN			0x50
%define	SCAN_PAGEDOWN		0x51
%define	SCAN_INSERT			0x52
%define	SCAN_DELETE			0x53

;极个别特殊按键
%define	SCAN_EXTEND1		0xE1

%define	SCAN_PAUSE			0x45
;通码：
	;SCAN_EXTEND1
	;SCAN_CTRL
	;SCAN_PAUSE
;断码：
	;SCAN_EXTEND1
	;SCAN_CTRL|SCANF_KEYUP
	;SCAN_PAUSE|SCANF_KEYUP
	
%define	SCAN_BREAK			0x46
;通码：
	;SCAN_CTRL
	;SCAN_EXTEND
	;SCAN_BREAK
;断码：
	;SCAN_CTRL|SCANF_KEYUP
	;SCAN_EXTEND
	;SCAN_BREAK|SCANF_KEYUP

%define	SCAN_SYSRQ			0x54
;通码：
	;SCAN_LALT
	;SCAN_SYSRQ
	;SCAN_EXTEND
	;SCAN_LSHIFT
	;SCAN_EXTEND
	;SCAN_PRTSC
;断码：
	;SCAN_SYSRQ|SCANF_KEYUP
	;SCAN_EXTEND
	;SCAN_PRTSC|SCANF_KEYUP
	;SCAN_EXTEND
	;SCAN_LSHIFT|SCANF_KEYUP
	;SCAN_LALT|SCANF_KEYUP


%endif
