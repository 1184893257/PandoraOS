%include "SYSINF.INC"

org DBR_NEWPOS
bits 16

CPU 586	;尽量保证兼容性

%include "BPBFAT32.INC"

%define FATBuffer	(DBR_NEWPOS + 1024)	;FAT缓冲区地址, 缓存一个扇区(前1024字节用于: 第一个512字节是DBR, 后512字节是BSS数据和栈)
%define rootEntries	2000h				;根目录缓冲区地址, 缓存一个簇(扇区大小小于5K的就不会覆盖FATBuffer)

struc PARAMS							;参数表
	.IVRTable		resd	0x100			;中断向量表，256个表项，每个表项4字节
	.BIOSData		resb	0x200			;BIOS数据区，占512个字节
	.DBR:								;我们的DBR在这
	.CurFATSect		resd	1
	.DAP:								;硬盘数据传输包
	.DAPSize		resb	1			;数据包大小
	.DAPReserved	resb	1			;保留字节			
	.DAPBlocks		resw	1			;块的数量
	.DAPBufferPtr	resd	1			;缓冲区指针
	.DAPLBA			resq	1			;数据包指定的块地址
endstruc

Start:

;先把本体从0:BOOT_ORG转移至0:DBR_NEWPOS
cli
xor ax,ax						;对齐各个段
mov es,ax
mov ss,ax
mov ds,ax
mov sp,FATBuffer				;设置好堆栈
mov si,BOOT_ORG					;准备把本体转移到低位内存运行
mov di,DBR_NEWPOS
mov cx,DBR_SIZE>>1
rep movsw						;通过减少拷贝的次数来提高拷贝的速度
sti
jmp 0x0000:DBR_Continue

DBR_Continue:					;此处从DBR_Continue开始
mov ah,0x41
mov bx,


LOADER_SYS		db	LODR_FILENAME		;LOADER.SYS的8.3格式的名字

times DBR_SIZE-($-Start)-2	db 0
dw	FLAG_BOOTALBE

FSInfo:








times DBR_SIZE-($-FSInfo)-2	db 0
dw	FLAG_BOOTALBE

SecContinue:




times DBR_SIZE-($-SecContinue)-2	db 0
dw	FLAG_BOOTALBE
