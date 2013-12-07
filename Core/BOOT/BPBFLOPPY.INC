%ifndef __BPB__INCLUDED___
%define __BPB__INCLUDED___

%include "SYSINF.INC"

;注：FAT12只用于软盘。
;Dos Boot Record，磁盘系统引导记录
BPB:
	.OpJMP:
		jmp					BootCodeStart			;跳转指令
		times 3-($-$$)		nop						;三个字节的跳转指令，不够3字节用nop补齐
	.szOEM					db	OEM_NAME			;OEM名
		times 8-($-.szOEM)	db	" "					;OEM_NAME必须为8字节，不够则用空格补齐
	.wBytesPerSec			dw	FLOPPY_SEC_LEN		;每扇区字节数
	.bSecsPerCluster		db	FLOPPY_SEC_PER_CLS	;每簇扇区数
	.wReservedSecs			dw	FLOPPY_RESV_SECS	;系统保留扇区数（整个分区除去FAT和文件数据以外的扇区数）
	.bNbFATs				db	FLOPPY_FAT_COUNT	;FAT表的总数
	.wMaxRootItems			dw	FLOPPY_ROOT_ITEMS	;根目录最大项数
	.wNbSecs 				dw	FLOPPY_SEC_COUNT	;分区扇区总数
	.bMediaType				db	MEDIA_FDD			;介质类型
	.wSecsPerFAT			dw	FLOPPY_FAT_SECS 	;每FAT扇区数
	.wSecsPerCylinder		dw	FLOPPY_SEC_PER_CYL	;每磁道扇区数
	.wHeads					dw	FLOPPY_HEAD_COUNT	;磁头数
	.dwHiddenSecs			dd	0x00000000 			;本分区前磁盘扇区数
	.dwTotalSecs32			dd	0x00000000			;保留不用
	.bDrivers 				db	0x00				;驱动器号
	.bCurrentHead			db	0x00				;当前磁头号

BPB_EX:												;BPB扩展
	.bExBoot				db	FLAG_EXT			;DBR扩展标识
	.dwPartitionID			dd	0x2B2B2B2B			;分区ID（随机数）
	.szVolumeLabel			db	LABEL_DEF			;卷标
	.szFSType 				db	FS_FAT12			;文件系统类型
BootCodeStart:

%endif