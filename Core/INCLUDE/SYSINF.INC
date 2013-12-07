%ifndef	__SYSTEM_INFORMATION_HEADER__
%define	__SYSTEM_INFORMATION_HEADER__

%include "MBR.INC"
%include "FAT.INC"
%include "KEYBD.INC"

%define	NULL				0

%define	LODR_FILENAME		"LOADER  SYS"	;引导文件名
%define	CORE_FILENAME		"CORE    SYS"	;內核文件名

%define	BOOT_ORG			0x7C00			;引导扇区起点
%define	LODR_ORG			0x7C00			;引导文件起点
%define	CORE_ORG			0x400000		;內核文件起点

%define	SEC_SIZE			0x200			;软盘、硬盘、U盘扇区大小

%define	MBR_NEWPOS			0x600			;MBR自己移动后的新位置。
%define	MBR_SIZE			SEC_SIZE		;MBR扇区的大小

%define	DBR_NEWPOS			0x800			;DBR自己移动后的新位置
%define	DBR_SIZE			SEC_SIZE		;DBR扇区的大小

%define	DIR_BUFFER			0xA00			;临时读取根目录的缓冲区
%define	FAT_BUFFER			0xC00			;临时读取FAT表的缓冲区

%define	SCR_GRAPHBUFSEG		0xA000			;图形显存段
%define	SCR_MONOTEXTBUFSEG	0xB000			;单色文本显存段
%define	SCR_COLORTEXTBUFSEG	0xB800			;彩色文本显存段

%define	SCR_GRAPHBUF		(SCR_GRAPHBUFSEG<<4)		;图形显存物理地址
%define	SCR_MONOTEXTBUF		(SCR_MONOTEXTBUFSEG<<4)		;单色文本物理地址
%define	SCR_COLORTEXTBUF	(SCR_COLORTEXTBUFSEG<<4)	;彩色文本物理地址

%endif
