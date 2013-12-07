%include "SYSINF.INC"

org DBR_NEWPOS
bits 16

%include "BPBFLOPPY.INC"
Start:

;先把本体从0:BOOT_ORG转移至0:DBR_NEWPOS
xor ax,ax						;对齐各个段
mov es,ax
mov ss,ax
mov ds,ax
mov si,BOOT_ORG					;源：引导开始
mov sp,si						;同时设置好堆栈
mov di,DBR_NEWPOS				;目标：DBR的新家
mov cx,DBR_SIZE					;字节数：DBR的尺寸
rep movsb						;转移到目标
jmp 0x0000:DBR_Continue

DBR_Continue:					;此处从DBR_Continue开始
.Read:							;读取整个FAT表
	mov di,[BPB.wSecsPerFAT]	;读取每FAT扇区数
	mov bx,FLOPPY_FAT_BUFFER	;读取到FLOPPY_FAT_BUFFER处
	mov bp,[BPB.wReservedSecs]	;定位开始扇区
.ReadAllFATItems:
	mov ax,bp					;设置LBA
	call ReadSector
	inc bp						;设置LBA
	add bx,[BPB.wBytesPerSec]	;设置缓冲区指針指针
	dec di						;计数减1（不用cx是因为ReadSector破坏cx）
	jnz .ReadAllFATItems

GetDataStartLBA:				;计算数据区的开始位置
	add bp,[BPB.wSecsPerFAT]	;bp指向根目录区起始位置
	mov ax,SIZE_DIRENTRY		;计算根目录区总大小
	mov cx,[BPB.wMaxRootItems]	;设置CX为最大根目录数为找引导文件做准备
	mul cx						;根目录最大个数乘每个目录项大小
	div word[BPB.wBytesPerSec]	;再除以每扇区字节数，为根目录区占用扇区数
	or dx,dx					;判断除法余数是否不为零
	jz .NoTail					;不是的话继续
	inc ax						;是的话判断根目录区要多占一个扇区
.NoTail:
	add ax,bp					;加上根目录区的开始位置
	mov [g_wDataStartLBA],ax	;就是数据区的开始位置了
	
FindLoader:
	mov ax,bp					;读取根目录区
	mov bx,FLOPPY_DIR_BUFFER	;读取到这一块缓冲区
	call ReadSector				;读扇区
	
	mov si,bx					;准备找引导文件
	mov cx,0x10					;一个扇区有0x10个表项
	call FindFile				;找引导文件
	jc FoundFile				;找到就跳转
	
	inc bp						;没找到则继续读取下一个扇区
	loop FindLoader				;循环寻找
	jmp LoadFailed				;读完所有根目录区都没有找到则认定引导失败。
	
FoundFile:						;找到了文件
	mov bp,[si+FAT_DIRITEM.wFirstClusLO];读取文件首簇（FAT12的簇号只有12位）
	cmp bp,FAT12_MAXVALIDCLUS	;簇号是否大于最大合法簇号
	ja LoadFailed				;是，失败退出
	cmp bp,FAT12_MINVALIDCLUS	;簇号是否低于最小合法簇号
	jb LoadFailed				;是，失败退出
	mov bx,LODR_ORG				;读取目标为LOADER.SYS的起始位置
ReadClusterChainToLoadLoader:	;开始读取簇链
	mov ax,bp					;设置簇号
	call ReadCluster			;读取簇
	
	movzx cx,byte[BPB.bSecsPerCluster];准备移动缓冲区指针
.LoopAddOffs:
	add bx,[BPB.wBytesPerSec]	;移动缓冲区指针
	loop .LoopAddOffs			;按照每簇扇区数移动
	
	mov si,bp					;读取下一个簇链
	shr si,1
	add si,bp					;FAT12的簇号所在内存位置的计算
	mov ax,[FLOPPY_FAT_BUFFER+si]
	test bp,1
	jz .FAT12Low
	shr ax,4
.FAT12Low:
	and ax,0xFFF				;已取得簇号->ax
	cmp ax,FAT12_MAXVALIDCLUS	;簇号是否大于最大合法簇号
	ja LoadOK					;是，载入完成
	cmp ax,FAT12_MINVALIDCLUS	;簇号是否低于最小合法簇号
	jb LoadFailed				;是，失败退出
	mov bp,ax					;设置簇链的簇号为下一个要读取的簇
	jmp ReadClusterChainToLoadLoader;继续载入簇链
	
LoadOK:							;载入完成，准备跳转
	xor ax,ax					;目标段为0
	mov es,ax					;对齐各个段
	mov ss,ax
	mov ds,ax
	mov sp,LODR_ORG				;设置好堆栈
	jmp 0x0000:LODR_ORG			;跳转到LOADER.SYS！
	
LoadFailed:						;如果载入失败
	mov si,.ErrText				;设置提示文本
	mov cx,.ErrTextLen			;设置字数
	jmp ErrAndHlt				;打印文本然后当机
	.ErrText		db	"Could not found LOADER.SYS. System halted.";找不到LOADER.SYS，系统已经当机
	.ErrTextLen		equ	$-.ErrText
	
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

;读取此盘的函数
	;ax=LBA
	;bx=缓冲区
;返回：
	;si=剩余重试次数
	;ax=int 0x13结果
	;cx=柱面:扇区号
	;dx=磁头:驱动器
ReadSector:
	mov si,3					;重试三次
	xor dx,dx
	div word[BPB.wSecsPerCylinder]
	inc dx						;dx=扇区
	mov cl,dl
	xor dx,dx
	div word[BPB.wHeads]		;ax=柱面，dx=磁头
	mov ch,al
	mov dh,dl
	mov dl,0					;驱动器0
.Retry:
	mov ax,0x0201				;读取一个扇区
	int 0x13					;读取
	jnc .ReadOK					;读取成功，跳转
	dec si
	jnz .Retry
	mov si,.ReadErr				;读取失败，报错退出
	mov cx,.ReadErrLen
	jmp ErrAndHlt
.ReadErr		db	"Unable to read from floppy. System halted."
.ReadErrLen		equ	$-.ReadErr
.ReadOK:						;读取OK：
	ret


;读取簇的函数
	;ax=簇号
	;bx=缓冲区
;返回：
	;si=剩余重试次数
	;ax=int 0x13结果
	;cx=0
	;dx=磁头:驱动器
ReadCluster:
	movzx cx,byte[BPB.bSecsPerCluster]
	sub ax,2					;簇号減去2
	mul cx						;再乘每簇扇区数
	add ax,[g_wDataStartLBA]	;再加上数据区的起始扇区
.ReadNextSec:					;为保险起见，按照每簇扇区数读取簇
	push cx
	push ax
	call ReadSector
	pop ax
	pop cx
	inc ax
	add bx,[BPB.wBytesPerSec]
	loop .ReadNextSec
	ret
	
;提示出错然后当机的函数
	;si=错误提示文本
	;cx=文本长度
;返回
	;当机
ErrAndHlt:
	mov bx,0x07					;颜色：普通白色
	mov ah,0x0E					;功能：打印单字
	.LoopShowText:
	lodsb
	int 0x10					;打印文本
	loop .LoopShowText
	cli							;关中断
	hlt							;当机

g_strLoaderFileName	db LODR_FILENAME
g_wDataStartLBA		dw (FLOPPY_RESV_SECS+FLOPPY_FAT_COUNT*FLOPPY_FAT_SECS+FLOPPY_ROOT_ITEMS*SIZE_DIRENTRY/FLOPPY_SEC_LEN)

%xdefine DBR_FILL_SIZE (DBR_SIZE-($-$$)-2)
times (DBR_FILL_SIZE>>1) db 0xFA,0xF4
%if DBR_FILL_SIZE&1
hlt
%endif
%undef DBR_FILL_SIZE
dw	FLAG_BOOTALBE
DBREnd:

