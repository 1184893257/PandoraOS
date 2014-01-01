%ifndef	__DBR__INCLUDED___
%define	__DBR__INCLUDED___

BPB:
	.OpJMP:
		jmp					BootCodeStart	;跳轉指令
		times 3-($-$$)		nop				;三個字節的跳轉指令，不夠3字節用nop補齊
	.szOEM					db	OEM_NAME	;OEM名
		times 8-($-.szOEM)	db	" "			;OEM_NAME必須為8字節，不夠則用空格補齊
	
	; 以下部分务必保留原样
	.wBytesPerSec			dw	0			;每个扇区的字节数
	.bSecsPerCluster		db	0			;每个簇的扇区数
	.wReservedSecs			dw	0			;保留扇区数（DBR到FAT之间的扇区数，包括DBR）
	.bNbFATs				db	0			;FAT数目
				times	11	db	0			;用不上, 具体含义见FAT文档
	.dwHiddenSecs			dd	0			;隐藏扇区数，DBR前面的扇区数，也就是分区前的扇区数
				times	4	db	0			;用不上, 具体含义见FAT文档
	.dwSecsPerFAT			dd	0			;单个FAT占用扇区数
				times	4	db	0			;用不上, 具体含义见FAT文档
	.dwRootFirstCluster		dd	0			;根目录起始簇
				times	16	db	0			;用不上, 具体含义见FAT文档
	.wBIOSDriverID			db	0			;BIOS的设备ID
				times	25	db	0			;用不上, 具体含义见FAT文档

BootCodeStart:

%endif

