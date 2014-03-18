%ifndef	__DBR__INCLUDED___
%define	__DBR__INCLUDED___

BPB:
	.OpJMP:
		jmp					BootCodeStart	;跳轉指令
		times 3-($-$$)		nop				;三個字節的跳轉指令，不夠3字節用nop補齊
	.szOEM					db	OEM_NAME	;OEM名
		times 8-($-.szOEM)	db	" "			;OEM_NAME必須為8字節，不夠則用空格補齊
	wBytesPerSec			dw	0			;每个扇区的字节数
	bSecsPerCluster			db	0			;每个簇的扇区数
	wReservedSecs			dw	0			;保留扇区数（DBR到FAT之间的扇区数，包括DBR）

	bNbFATs					db	0			;FAT数目
	dwReserved1				dd	0			;FAT16、FAT12的根目录项数和分区总扇区数，FAT32为0
	bMediaType				db	0			;介质类型
	wReserved2				dw	0			;FAT16、FAT12的每个FAT占用扇区数，FAT32为0
	wSecsPerCylinder		dw	0			;每磁道扇区数
	wHeads					dw	0			;磁头数
	dwHiddenSecs			dd	0			;隐藏扇区数，DBR前面的扇区数，也就是分区前的扇区数

	dwNbSecs				dd	0			;分区总扇区数
	dwSecsPerFAT			dd	0			;单个FAT占用扇区数
	wFATNotMirror			dw	0			;FAT是否不是镜像模式。一般为0（镜像模式，双FAT）
	wVersion				dw	0			;版本号
	dwRootFirstCluster		dd	0			;根目录起始簇

	wFSInfoSec				dw	0			;FSInfo扇区的位置
	wDBRBackupSec			dw	0			;DBR备份的位置
	bReserved3	times	12	db	0			;保留未用，全为0
	wBIOSDriverID			dw	0			;BIOS的设备ID

BPB_EX:										;DBR擴展
	.bExBoot				db	FLAG_EXT	;DBR擴展標識
	.dwPartitionID			dd	0x2B2B2B2B	;分區ID（隨機數）
	.szVolumeLabel			db	LABEL_DEF	;卷標
	.szFSType				db	FS_FAT32	;文件系統類型
BootCodeStart:

%endif

