%include "SYSINF.INC"

org DBR_NEWPOS
bits 16

CPU 586

%include "BPBFAT.INC"
Start:

;临时变量块，位于引导代码头部
struc Temp
	.Reserved			resb	DBR_NEWPOS
	.qwFATStart			resq	1	;FAT表开始LBA
	.qwRootEntryStart	resq	1	;根目录表开始LBA
	.qwDataStart		resq	1	;数据区开始LBA
	.wLoaderOffset		resw	1	;引导程序偏移位置
	.wLoaderSegment		resw	1	;引导程序段
	.wBytesPerCluster	resw	1	;每簇字节数
	.ReadPacket:
	.cbSizeOfPacket		resb	1	;包的大小
	.bReserved			resb	1	;保留1字节
	.wBlocks			resw	1	;读取块的数量
	.wBufferOffset		resw	1	;缓冲区偏移
	.wBufferSegment		resw	1	;缓冲区段
	.qwLBA				resq	1	;64位绝对LBA
	.EndOfPacket:
endstruc

%define	MOVER_SIZE		(DBR_Continue-$$)

;先把本体从0:BOOT_ORG转移至0:DBR_NEWPOS
xor ax,ax							;对齐各个段
mov es,ax
mov ss,ax
mov ds,ax
mov sp,BOOT_ORG						;设置好堆栈
mov si,BOOT_ORG+MOVER_SIZE			;源：引导开始
mov di,DBR_NEWPOS+MOVER_SIZE		;目标：DBR的新家
mov cx,DBR_SIZE-MOVER_SIZE			;字节数：DBR的尺寸
rep movsb							;转移到目标
jmp 0x0000:DBR_Continue

DBR_Continue:						;此处从DBR_Continue开始
.Init:								;必要的初始化
	mov ah,0x41						;判断是否支持扩展读硬盘功能
	mov dl,[BPB.bDrivers]
	mov bx,0x55AA
	int 0x13
	jc INT13ExNotOK
	cmp bx,0xAA55
	jnz INT13ExNotOK

	xor edx,edx						;edx为LBA高32位
	mov ebp,edx						;ebp清零，用来替代立即数0
	mov eax,[BPB.dwHiddenSecs]		;eax为LBA低32位
	movzx ecx,word[BPB.wReservedSecs];ecx高位清零，低位是保留扇区数，DBR第二部分在保留扇区内
	mov [Temp.qwLBA],eax			;准备读取第二扇区
	mov [Temp.qwLBA+4],edx
	push ax							;保存好已经设置的寄存器
	push cx
	push dx
	mov word[Temp.wBlocks],1
	mov dword[Temp.wBufferOffset],SecondPart
	
.LookForNextPart:					;开始找第二扇区
	inc dword[Temp.qwLBA]			;从DBR的位置+1开始找DBR第二个扇区
	jnz .ReadNextPartSec
	inc dword[Temp.qwLBA+4]			;这里处理LBA的高位
.ReadNextPartSec:
	call ReadSector					;读取扇区
	cmp word[SecondPart.BootFlag],FLAG_BOOTALBE;判断是否为可用的第二扇区
	jz .SecPartLoaded				;是的话跳出继续引导
	loop .LookForNextPart			;否则循环查找下一个扇区
	
	mov si,.NoNextPartText			;运行到这里意味着没找到合法的第二扇区。
	mov cx,.NoNextPartTextLen
	jmp ErrAndReboot
.NoNextPartText		db	"Part of the boot sectors is missing."
.NoNextPartTextLen		equ	$-.NoNextPartText
	
.SecPartLoaded:						;找到第二扇区后跳到此处继续运行
	pop dx
	pop cx
	pop ax							;恢复之前设置的寄存器
	add eax,ecx						;分区前扇区数加保留扇区数
	adc edx,ebp
	mov [Temp.qwFATStart],eax		;eax:edx为64位的FAT表LBA
	mov [Temp.qwFATStart+4],edx
	movzx cx,byte[BPB.bNbFATs]		;FAT数量计数
	movzx ebx,word[BPB.wSecsPerFAT]	;准备跳过所有FAT表
.AddFatSecs:
	add eax,ebx
	adc edx,ebp
	loop .AddFatSecs				;跳过FAT表
	mov [Temp.qwRootEntryStart],eax	;eax:edx为64位的根目录表LBA
	mov [Temp.qwRootEntryStart+4],edx
	mov [Temp.qwLBA],eax			;接下来要从根目录区读取根目录项，所以预先设定读取LBA
	mov [Temp.qwLBA+4],edx
	mov bx,[BPB.wMaxRootItems]		;根目录表占用的扇区数与根目录表最大项数有关。
	shr bx,4						;每个根目录表项占用0x20字节，每个扇区0x200字节，则每个扇区有0x10个根目录项
	test byte[BPB.wMaxRootItems],0x0F;保险起见检查有没有多余的根目录项
	jz .GotDataLBA
	inc bx							;有的话根目录扇区数+1
.GotDataLBA:						;bx=根目录区占用扇区数
	add eax,ebx						;跳过根目录表
	adc edx,ebp
	mov [Temp.qwDataStart],eax		;eax:edx为64位的数据区LBA
	mov [Temp.qwDataStart+4],edx

.FindFile:							;刚才已经设置好了读取LBA，开始找文件
	mov dword[Temp.wBufferOffset],HDD_DIR_BUFFER
	mov word[Temp.wBlocks],1		;只读取一个扇区
	call ReadSector					;读取根目录扇区

	mov si,HDD_DIR_BUFFER			;读取扇区后从读取的地方找引导文件名
	mov cx,0x10
	call FindFile					;找文件
	jc SecondPart.FoundBootFile		;找到就继续引导
	inc dword[Temp.qwLBA]			;没找到，LBA递增，读取下一个根目录扇区
	jnz .IncreasedLBA
	inc dword[Temp.qwLBA+4]			;考虑到高位的进位
.IncreasedLBA:
	dec bx							;计数减一，这里的计数是剩余的根目录扇区的数量
	jnz .FindFile					;计数不为零则继续读取根目录区找文件
	call ReadErr					;计数为零还没找到文件，提示出错



	
;从目录中找文件的函数
	;si=文件目录表
	;cx=文件目录项数
;返回：
	;di=g_strLoaderFileName末尾
;如果找到：
	;cf=1
	;cx=剩余文件项数
	;si->文件目录表对应项数
;如果没找到：
	;cf=0
	;cx=0
	;si->文件目录表末尾
FindFile:
	push cx						;保存cx用于循环查找文件
		mov cx,SIZE_FILENAME	;准备进行字符串比较
		mov di,g_strLoaderFileName
		repz cmpsb				;比较字符串
		jcxz .FoundFile			;如果字符串匹配，认定找到文件
		add si,SIZE_DIRENTRY-SIZE_FILENAME
		add si,cx				;否则修改指针指向下一个文件目录项
	pop cx						;恢复cx用于循环
	loop FindFile				;循环查找文件
	clc							;如果没找到，CF=0
	ret							;返回
.FoundFile:						;如果找到
	pop cx						;恢复堆栈平衡（跳出来的时候cx还在堆栈）
	sub si,SIZE_FILENAME		;修改指针指向当前文件目录项
	stc							;找到的标志是CF=1
	ret							;返回

;读取磁盘的函数
	;填写ReadPacket
;返回：
	;ax=运行结果
	;dl=驱动器
	;si=ReadPacket地址
ReadSector:
	mov word[Temp.cbSizeOfPacket],Temp.EndOfPacket-Temp.ReadPacket
	mov dl,[BPB.bDrivers]
	mov si,Temp.ReadPacket
	mov ah,0x42
	int 0x13
	jc ReadErr
	ret

ReadErr:
	mov si,.ReadErr
	mov cx,.ReadErrLen
	jmp ErrAndReboot
.ReadErr		db	"Replace the disk and then press any key"
.ReadErrLen		equ	$-.ReadErr

INT13ExNotOK:
	mov si,.ReadErr
	mov cx,.ReadErrLen
	jmp ErrAndReboot
.ReadErr		db	"Unable To Read"
.ReadErrLen		equ	$-.ReadErr

;提示出错然后当机的函数
	;si=错误提示文本
	;cx=文本长度
;返回
	;当机
ErrAndReboot:
	mov bx,0x07						;颜色：普通白色
	mov ah,0x0E						;功能：打印单字
	.LoopShowText:
	lodsb
	int 0x10						;打印文本
	loop .LoopShowText
	sti
	xor ax,ax
	int 0x16
	int 0x18

g_strLoaderFileName	db	LODR_FILENAME

times HDD_SEC_LEN-($-$$)-2			hlt
.BootFlag	dw	FLAG_BOOTALBE

SecondPart:
.FoundBootFile:						;已经找到了引导文件
	mov eax,[Temp.qwFATStart]		;先读取FAT第一个扇区
	mov [Temp.qwLBA],eax			;把FAT第一扇区的LBA搬运到读取数据包处
	mov eax,[Temp.qwFATStart+4]
	mov [Temp.qwLBA+4],eax
	movzx edi,word[si+FAT_DIRITEM.wFirstClusLO];di=首簇号低16位，同时清空edi高位
	xor cx,cx						;cx指示当前读入的FAT扇区号，之所以读取FAT
	mov dword[Temp.wBufferOffset],HDD_FAT_BUFFER
	call ReadSector					;读取FAT第一个扇区
	mov dword[Temp.wLoaderOffset],BOOT_ORG;设置引导程序读取位置
	movzx bp,byte[BPB.bSecsPerCluster];bp=每簇扇区数

.ReadFromClus:
	mov [Temp.wBlocks],bp			;读取一个簇用到的扇区数
	mov eax,edi						;取得簇号
	dec ax
	dec ax							;簇号减去2
	mul bp							;乘上每簇扇区数
	shl edx,16						;dx的值为簇的相对扇区位置高16位
	or eax,edx						;合并到eax，此时eax为簇的相对扇区位置
	xor edx,edx						;edx为簇的相对扇区位置的高位
	add eax,[Temp.qwDataStart]		;相对位置加上数据区的扇区位置，为簇的绝对扇区位置。
	adc edx,[Temp.qwDataStart+4]	;高位
	mov [Temp.qwLBA],eax			;设置读取LBA
	mov [Temp.qwLBA+4],edx			;高位
	mov eax,[Temp.wLoaderOffset]	;取得读取目标位置
	mov [Temp.wBufferOffset],eax	;搬运到读取目标处
	call ReadSector					;读取引导文件的第一个簇
	push bp							;bp=每簇扇区数
	shl bp,9						;bp*0x200=每簇字节数
	add [Temp.wLoaderOffset],bp		;读取位置往后推
	jnc .CheckNextFATItem
	add word[Temp.wLoaderSegment],0x1000;跨段处理，段也往后偏移
.CheckNextFATItem:					;寻找下一个FAT簇号
	pop bp							;取回每簇扇区数
	;每个FAT扇区能存储0x100个簇号
	;cx=当前读取在内存中的FAT表扇区的扇区号，判断是否应该重新读取FAT表其它部分
	mov eax,edi						;先获取当前已经读取的簇的簇号。
	mov ah,0						;只保留簇号低8位，这样才能正确读取FAT表扇区中对应的簇号
	mov ax,[eax+eax+HDD_FAT_BUFFER]	;然后从FAT表得到下一个簇号
	cmp ax,FAT16_MINVALIDCLUS		;判断簇号是否合法
	jb ReadErr						;不合法则报错
	cmp ax,FAT16_MAXVALIDCLUS		;判断是否到末簇
	ja .FinishedReading				;是的话完成读取过程
	push ax							;保存起来
	cmp ah,cl						;判断当前簇号是否在当前FAT表内
	jz .ContinueCheckFATItem		;是的话继续读取簇号
	shr ax,8						;否则取得新的FAT表扇区号
	mov cl,al						;cx=当前读取在内存中的FAT表扇区的扇区号
	xor edx,edx						;高位
	add eax,[Temp.qwFATStart]		;加上FAT表的起始位置
	adc edx,[Temp.qwFATStart+4]		;高位
	mov [Temp.qwLBA],eax			;就是要读取的FAT的LBA
	mov [Temp.qwLBA+4],edx			;高位
	mov word[Temp.wBlocks],1		;读取一个块
	mov dword[Temp.wBufferOffset],HDD_FAT_BUFFER
	call ReadSector					;读取FAT表
	
.ContinueCheckFATItem:				;堆栈里压入了簇号
	pop di							;取出簇号
	jmp .ReadFromClus				;回去继续读取簇
	
.FinishedReading:					;读取完后开始引导
	jmp 0x0000:BOOT_ORG

times HDD_SEC_LEN*2-($-$$)-2		hlt
.BootFlag	dw	FLAG_BOOTALBE

