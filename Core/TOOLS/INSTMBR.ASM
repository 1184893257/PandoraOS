org 0x100
bits 16

Start:
mov ax,0x0201		;读取主引导扇区
mov cx,0x0001		;柱面0扇区1
mov dx,0x0080		;磁头0硬盘0
mov bx,OldMBR		;缓冲区
int 0x13			;读取
mov si,OldMBR+0x1BE	;拷贝分区表
mov di,MBR+0x1BE
cld
mov cx,32
rep movsw
mov word[di],0xAA55	;产生可引导签名
mov ax,0x0301		;写入MBR
mov cx,0x0001		;柱面0扇区1
mov dx,0x0080		;磁头0硬盘0
mov bx,MBR			;缓冲区
int 0x13			;写入
int 0x20			;退出到DOS

MBR:
incbin "..\BOOT\DOC\MBR.BIN"	;自带MBR文件
OldMBR:				;缓冲区

