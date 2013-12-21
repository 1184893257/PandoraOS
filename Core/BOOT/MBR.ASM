%include"SYSINF.INC"

org MBR_NEWPOS
bits 16

%define	MOVER_SIZE		(MBR_Continue-$$)

Start7C00:
cli
xor ax,ax
mov es,ax
mov ss,ax
mov ds,ax
mov sp,BOOT_ORG					;设置好堆栈
mov si,BOOT_ORG					;准备把本体转移到低位内存运行
mov di,DBR_NEWPOS
mov cx,DBR_SIZE>>1
rep movsw						;通过减少拷贝的次数来提高拷贝的速度
sti
jmp 0x0000:MBR_Continue

MBR_Continue:
mov ax,0
mov dl,[DPT.1]
cmp dl,0x80
jae FoundActivePartition
inc ax
mov dl,[DPT.2]
cmp dl,0x80
jae FoundActivePartition
inc ax
mov dl,[DPT.3]
cmp dl,0x80
jae FoundActivePartition
inc ax
mov dl,[DPT.4]
cmp dl,0x80
jae FoundActivePartition

mov si,NoActivePartPrompt
call PrintText
xor ax,ax
int 0x16
int 0x18						;调用INT 0x18让BIOS解决这个问题。

cli
hlt

FoundActivePartition:
;ax=分区号
;dl=驱动器

CheckINT13EX:
mov ah,0x41
mov bx,0x55AA
int 0x13						;检查是否支持扩展引导功能
jc NoINT13EX
cmp bx,0xAA55
jnz NoINT13EX






NoINT13EX:


%include"PrintText.inc"

NoActivePartPrompt:
	db	"There is no active partition in this hard disk. Only active partition is bootable.",0xD,0xA,0

times MBR_CODESIZE-($-$$) db 0	;填充字节
DPT:							;磁盘分区表
.1 times 16 db 0
.2 times 16 db 0
.3 times 16 db 0
.4 times 16 db 0
Signature dw 0xAA55
MBR_End:
