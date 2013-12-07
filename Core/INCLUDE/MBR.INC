%ifndef	__MBR_INFORMATION_HEADER__
%define	__MBR_INFORMATION_HEADER__

;主引导分区结构
;每个分区表的结构都是DiskPartitionTable的结构
struc MainBootRecord
	.BootCode	resb	446	;引导指令
	.DPT1		resb	16	;主分区表1
	.DPT2		resb	16	;主分区表2
	.DPT3		resb	16	;主分区表3
	.DPT4		resb	16	;主分区表4
	.0xAA55		resw	1	;可引导签名
endstruc

;分区表结构
struc DiskPartitionTable
	.bDriverID	resb	1	;是否为活动分区，值小于MBR_ACTIVE为非活动分区
	.StartCHS	resb	3	;分区起始位置CHS
	.bFSType	resb	1	;文件系统类型
	.EndCHS		resb	3	;分区结束位置CHS
	.dwLBAStart	resd	1	;分区起始位置LBA
	.dwLBASize	resd	1	;分区大小LBA
endstruc

;文件系统类型支持的值
%define	MBR_ACTIVE						0x80	;活動分區驅動器號開始
%define	MBR_INACTIVE					0x00	;非活動分區

%define	FS_INVALID						0x00
%define	FS_FAT32						0x01
%define	FS_XENIX_ROOT					0x02
%define	FS_XENIX_USR					0x03
%define	FS_FAT16_IN32MB					0x04	;32MB以內
%define	FS_EXTENDED						0x05
%define	FS_FAT16						0x06
%define	FS_NTFS							0x07
%define	FS_AIX							0x08
%define	FS_AIX_BOOTABLE					0x09
%define	FS_OS_2_BOOTMGR					0x0A
%define	FS_FAT32_W95					0x0B
%define	FS_FAT32_W95_					0x0C
%define	FS_FAT16_W95					0x0E
%define	FS_EXTENDED_W95_A8GB			0x0F	;大於8GB
%define	FS_OPUS							0x10
%define	FS_HIDDEN_FAT12					0x11
%define	FS_COMPAQ_DIAGNOST				0x12
%define	FS_HIDDEN_FAT16_IN32MB			0x14
%define	FS_HIDDEN_FAT16					0x16
%define	FS_HIDDEN_NTFS					0x17
%define	FS_AST_WINDOW_SWAP				0x18
%define	FS_HIDDEN_FAT32					0x1B
%define	FS_HIDDEN_FAT32_LBA				0x1C
%define	FS_HIDDEN_LBA_VFAT_PART			0x1E
%define	FS_NEC_DOS						0x24
%define	FS_PART_MAGIC					0x3C
%define	FS_VENIX_80286					0x40
%define	FS_PPC_PREP_BOOT				0x41
%define	FS_SFS							0x42
%define	FS_QNX4_X						0x4D
%define	FS_QNX4_X_2ND_PART				0x4E
%define	FS_QNX4_X_3RD_PART				0x4F
%define	FS_ONTRACK_DM					0x50
%define	FS_ONTRACK_DM6_AUX				0x51
%define	FS_CP_M							0x52
%define	FS_ONTRACK_DM6_AUX_				0x53
%define	FS_ONTRACK_DM6					0x54
%define	FS_EZ_DRIVE						0x55
%define	FS_GOLDEN_BOW					0x56
%define	FS_PRIAM_EDISK					0x5C
%define	FS_SPEED_STOR					0x61
%define	FS_GNU_HURD_OR_SYS				0x63
%define	FS_NOVELL_NETWARE				0x64
%define	FS_NOVELL_NETWARE_				0x65
%define	FS_DISK_SECURE_MULT				0x70
%define	FS_PC_IX						0x75
%define	FS_OLD_MINIX					0x80
%define	FS_LINUX_SWAP					0x82
%define	FS_LINUX						0x83
%define	FS_OS_2_HIDDEN_C				0x84
%define	FS_LINUX_EXTENDED				0x85
%define	FS_NTFS_VOLUME_SET				0x86
%define	FS_NTFS_VOLUME_SET_				0x87
%define	FS_AMOEBA						0x93
%define	FS_AMOEBA_BBT					0x94
%define	FS_IBM_THINKPAD_HIDDEN			0xA0
%define	FS_BSD_386						0xA5
%define	FS_OPEN_BSD						0xA6
%define	FS_NEXTSTEP						0xA7
%define	FS_BSDI_FS						0xB7
%define	FS_BSDI_SWAP					0xB8
%define	FS_SOLARIS_BOOT_PART			0xBE
%define	FS_DRDOS_NOVELLDOS_SECURED_PART	0xC0
%define	FS_DRDOS_SEC					0xC1
%define	FS_DRDOS_SEC_					0xC4
%define	FS_DRDOS_SEC__					0xC6
%define	FS_SYRINX						0xC7
%define	FS_CP_M_CTOS					0xDB
%define	FS_DOS_ACCESS					0xE1
%define	FS_DOS_R_O						0xE3
%define	FS_SPEEDSTOR					0xE4
%define	FS_BEOS_FS						0xEB
%define	FS_SPEEDSTOR_					0xF1
%define	FS_DOS_3_3P_SECONDARY_PART		0xF2
%define	FS_SPEEDSTOR__					0xF4
%define	FS_LAN_STEP						0xFE
%define	FS_BBT							0xFF

%endif
