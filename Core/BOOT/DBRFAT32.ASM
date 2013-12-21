%include "SYSINF.INC"

org BOOT_ORG
bits 16

CPU 586	;尽量保证兼容性

%include "BPBFAT32.INC"
Start:

%define	MOVER_SIZE		(DBR_Continue-$$)

;先把本体从0:BOOT_ORG转移至0:DBR_NEWPOS
cli
xor ax,ax						;对齐各个段
mov es,ax
mov ss,ax
mov ds,ax
mov sp,BOOT_ORG					;设置好堆栈
mov si,BOOT_ORG					;准备把本体转移到低位内存运行
mov di,DBR_NEWPOS
mov cx,DBR_SIZE>>1
rep movsw						;通过减少拷贝的次数来提高拷贝的速度
sti
jmp 0x0000:DBR_Continue

DBR_Continue:					;此处从DBR_Continue开始

times DBR_SIZE-($-$$)-2	nop
dw	FLAG_BOOTALBE
