%ifndef __BPB__INCLUDED___
%define __BPB__INCLUDED___

%include "SYSINF.INC"


;Dos Boot Record，磁盘系统引导记录
BPB:
	.OpJMP:
		jmp					BootCodeStart			;跳转指令
		times 3-($-$$)		nop						;三个字节的跳转指令，不够3字节用nop补齐
	.szOEM					db	OEM_NAME			;OEM名
		times 8-($-.szOEM)	db	" "					;OEM_NAME必须为8字节，不够则用空格补齐
	.wBytesPerSec			dw	0					;每扇区字节数
	.bSecsPerCluster		db	0					;每簇扇区数
	.wReservedSecs			dw	0					;系统保留扇区数（整个分区除去FAT和文件数据以外的扇区数）
	.bNbFATs				db	0					;FAT表的总数
	.wMaxRootItems			dw	0					;根目录最大项数
	.wNbSecs 				dw	0					;分区扇区总数
	.bMediaType				db	MEDIA_HDD			;介质类型
	.wSecsPerFAT			dw	0				 	;每FAT扇区数
	.wSecsPerCylinder		dw	0					;每磁道扇区数
	.wHeads					dw	0					;磁头数
	.dwHiddenSecs			dd	0					;本分区前磁盘扇区数
	.dwTotalSecs32			dd	0					;保留不用
	.bDrivers 				db	0					;驱动器号
	.bCurrentHead			db	0					;当前磁头号

BPB_EX:												;BPB扩展
	.bExBoot				db	FLAG_EXT			;DBR扩展标识
	.dwPartitionID			dd	0x2B2B2B2B			;分区ID（随机数）
	.szVolumeLabel			db	LABEL_DEF			;卷标
	.szFSType 				db	FS_FAT12			;文件系统类型
BootCodeStart:

%endif