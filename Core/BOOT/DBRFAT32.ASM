%include "SYSINF.INC"

org DBR_NEWPOS
bits 16

CPU 586	;¾¡Á¿±£Ö¤¼æÈİĞÔ

%include "BPBFAT32.INC"

%define EOC			0FFFFFF8h			;´ØÁ´µÄ½áÊø±êÖ¾
%define FATBuffer	(DBR_NEWPOS + 1024)	;FAT»º³åÇøµØÖ·, »º´æÒ»¸öÉÈÇø(Ç°1024×Ö½ÚÓÃÓÚ: µÚÒ»¸ö512×Ö½ÚÊÇDBR, ºó512×Ö½ÚÊÇBSSÊı¾İºÍÕ»)
%define rootEntries	2000h				;¸ùÄ¿Â¼»º³åÇøµØÖ·, »º´æÒ»¸ö´Ø(ÉÈÇø´óĞ¡Ğ¡ÓÚ5KµÄ¾Í²»»á¸²¸ÇFATBuffer)

Start:

;ÏÈ°Ñ±¾Ìå´Ó0:BOOT_ORG×ªÒÆÖÁ0:DBR_NEWPOS
cli
xor ax,ax						;¶ÔÆë¸÷¸ö¶Î
mov es,ax
mov ss,ax
mov ds,ax
mov sp,FATBuffer				;ÉèÖÃºÃ¶ÑÕ»
mov si,BOOT_ORG					;×¼±¸°Ñ±¾Ìå×ªÒÆµ½µÍÎ»ÄÚ´æÔËĞĞ
mov di,DBR_NEWPOS
mov cx,DBR_SIZE>>1
rep movsw						;Í¨¹ı¼õÉÙ¿½±´µÄ´ÎÊıÀ´Ìá¸ß¿½±´µÄËÙ¶È
sti
jmp 0x0000:DBR_Continue

curFATSect		dd	0					;µ±Ç°FAT_BufferÔÚFATÖĞµÄË÷Òı
endOfEntries	dw	rootEntries			;¸ùÄ¿Â¼»º³åÇø½áÊøµØÖ·(Reader.initÖĞ²¹¼ÓÒ»¸ö´ØµÄ´óĞ¡)
LOADER_SYS		db	LODR_FILENAME		;LOADER.SYSµÄ8.3¸ñÊ½µÄÃû×Ö

DBR_Continue:					;´Ë´¦´ÓDBR_Continue¿ªÊ¼
	call Reader.init

	;ÕÒ¸ùÄ¿Â¼ÏÂµÄLOADER.SYS
	mov eax, [BPB.dwRootFirstCluster]
readRootCluster:	;¶ÁÒ»¸ö´Ø
	mov [BSS.bufOffset], word rootEntries	;¶Á¸ùÄ¿Â¼Èë¿ÚµÄÊ±ºò, ¶Á´ØºÍ¶ÁFAT¶¼ÓÃ¶ÎµØÖ·0, Ö»ÉèÆ«ÒÆ¼´¿É
	call Reader.readClus
	mov di, rootEntries

findLoader:
	push di
	mov si, LOADER_SYS
	mov cx, 11
	repz cmpsb
	pop di		;pop²»Ó°Ïì±êÖ¾Î»
	jz foundLoader
	add di, 32
	cmp di, [endOfEntries]
	jb findLoader	;ÕÒ±éÕû¸ö´Ø

	call Reader.nextClus
	cmp eax, EOC
	jb readRootCluster	;¸ùÄ¿Â¼»¹ÓĞÊı¾İ

	;Õû¸ö¸ùÄ¿Â¼ÎÒ¶¼·­ÁË¸ö±é, Ã»ÕÒµ½LOADER.SYS
	mov al, '2'
	jmp ErrAndHlt

;ÕÒµ½ÁËLOADER.SYS
	;diÖ¸ÏòµÄÊÇLOADER.SYSµÄÄ¿Â¼Ïî
foundLoader:
	;ÕÒ³öLOADER.SYSµÄÊ×´Ø
	mov ax, [di + 20]	;´ØµÄ¸ßÁ½¸ö×Ö½Ú
	mov cl, 16
	shl eax, cl
	mov ax, [di + 26]	;´ØµÄµÍÁ½¸ö×Ö½Ú

	mov [BSS.bufSeg], word 0x7c0
	mov [BSS.bufOffset], word 0
readLoader:
	call Reader.readClus
	mov bx, [BSS.clusSize]
	add [BSS.bufOffset], bx
	jnc nextClus
	add [BSS.bufSeg], word 1000h	;´Ø´óĞ¡ÊÇ64KµÄÔ¼Êı, Òç³ö¾ÍÊÇ¶ÁÂú64KÁË, ËùÒÔ¶Î¼Ó1000h
nextClus:
	call Reader.nextClus
	cmp eax, EOC
	jb readLoader	;LOADER.SYS»¹ÓĞÊı¾İ

	jmp 0:0x7c00	;ºÃÁË, Ò»ÇĞ½»¸øLOADER.SYSÀ´×öÁË

;### ¶ÁÓ²ÅÌÏà¹ØµÄ²Ù×÷ ###
Reader:

;¸ù¾İBPB³õÊ¼»¯²¿·ÖÊı¾İ
.init:
	;³õÊ¼»¯BSSÖĞºã¶¨²»±äµÄÖµ
	mov [BSS.packet], word 16
	mov [BSS.LBAHigh], dword 0

	;¼ÆËã´Ø´óĞ¡, ĞŞÕıendOfEntries
	mov ax, [BPB.wBytesPerSec]
	movzx bx, byte [BPB.bSecsPerCluster]
	mul bx
	test dx, dx
	jnz .tooLarge
	mov [BSS.clusSize], ax
	add [endOfEntries], ax

	;¼ÆËãFAT±íÆğÊ¼ÉÈÇø
	movzx ecx, word [BPB.wReservedSecs]
	add ecx, [BPB.dwHiddenSecs]		;Ö»ÒªÊÇÖ÷·ÖÇø, Òş²ØÉÈÇøÊı¾Í»á±»³õÊ¼»¯Îª·ÖÇøµÄÆğÊ¼ÉÈÇø
	mov [BSS.FATStart], ecx

	;¼ÆËãÊı¾İÇøÆğÊ¼ÉÈÇø
	mov eax, [BPB.dwSecsPerFAT]
	movzx ebx, byte [BPB.bNbFATs]
	mul ebx
	add ecx, eax
	mov [BSS.dataStart], ecx

	;¶ÁFAT±íµÄµÚ0¸öÉÈÇø
	xor eax, eax
	jmp short .readFAT	;.readFAT ÓĞ ret

.tooLarge:
	mov al, '0'
	jmp ErrAndHlt

;È¡ÏÂÒ»¸ö´ØºÅ
	;eax µ±Ç°´ØºÅ
;·µ»Ø
	;eax ÏÂÒ»¸ö´ØºÅ
.nextClus:
	shl eax, 1
	shl eax, 1
	movzx ebx, word [BPB.wBytesPerSec]
	xor edx, edx
	div ebx
	mov cx, dx	;±£´æÉÈÇøÄÚÆ«ÒÆ
	cmp eax, [curFATSect]	;ÉÈÇøÒÑ»º´æ?
	je .hitCurrent
	mov [curFATSect], eax
	call .readFAT
.hitCurrent:
	mov si, cx
	mov eax, [FATBuffer + si]
	and eax, 0FFFFFFFh		;FAT32µÄ´ØºÅÆäÊµÖ»ÓĞ28Î»
	ret
.readFAT:	;eaxÊÇÒª¶ÁµÄFAT±íÄÚÉÈÇøË÷Òı
	mov [BSS.nSect], word 1
	mov [BSS.bufSeg], word 0
	mov [BSS.bufOffset], word FATBuffer
	add eax, [BSS.FATStart]
	mov [BSS.LBA], eax
	jmp short .readPacket	;.readPacketÓĞret

;¶ÁÈ¡Ò»¸ö´Ø
	;eax ´ØºÅ
	;Êı¾İ´æ´¢µ½ .bufSeg:.bufOffset
.readClus:
	push eax	;´ØºÅÓĞºÜ´óÓÃ´¦, ËùÒÔ»¹ÊÇ±£»¤ºÃËü
	sub	eax, 2
	movzx ebx, byte [BPB.bSecsPerCluster]
	mul ebx
	add eax, [BSS.dataStart]
	mov [BSS.LBA], eax
	mov [BSS.nSect], bx
	call .readPacket
	pop eax
	ret
.readPacket:
	mov dl, [BPB.wBIOSDriverID]
	mov ah, 42h
	mov si, BSS.packet
	int 13h
	jc .readErr
	ret

.readErr:
	mov al, '1'

;### ÏÔÊ¾´íÎóÂë ###
;ÔÚÆÁÄ»ÉÏÏÔÊ¾Ò»¸öÊı×ÖÈ»ºóµ±»úµÄº¯Êı
	;al, ´íÎóÂë(Ò»¸öASCII±íÊ¾µÄÊı×Ö)Å:
	; 0 ´Ø´óÓÚ32K
	; 1 ¶ÁÓ²ÅÌÊ±·¢Éú´íÎó
	; 2 Ã»ÕÒµ½LOADER.SYS
;·µ»Ø
	;µ±»ú
ErrAndHlt:
	mov bx,0x07					;ÑÕÉ«£ºÆÕÍ¨°×É«
	mov ah,0x0E					;¹¦ÄÜ£º´òÓ¡µ¥×Ö
	int 0x10					;´òÓ¡ÎÄ±¾
	cli							;¹ØÖĞ¶Ï
	hlt							;µ±»ú

times DBR_SIZE-($-$$)-2	nop
dw	FLAG_BOOTALBE

;·Å²»ÏÂÁË, Ö»ºÃ°ÑÊı¾İ¶ªºó±ßÁË
section .bss
BSS:
.FATStart		resd	1	;FAT±íµÄÆğÊ¼ÉÈÇø
.dataStart		resd	1	;Êı¾İÇøÆğÊ¼ÉÈÇø
.clusSize		resw	1	;´Ø´óĞ¡(²»³¬¹ı32K)

.packet:		;À©Õ¹13h¶ÁÓ²ÅÌµÄpacket
				resb	2	;db	10h, 0
.nSect			resw	1	;Òª¶ÁµÄÉÈÇø¸öÊı
.bufOffset		resw	1	;´æ´¢¶ÁÈ¡Êı¾İµÄÆ«ÒÆ
.bufSeg			resw	1	;´æ´¢¶ÁÈ¡Êı¾İµÄ¶Î
.LBA			resd	1	;Âß¼­ÉÈÇøºÅ, Ä¿Ç°Ö»ÓÃ32Î»(2TÒÔÏÂµÄ¶¼¹»ÁË)
.LBAHigh		resd	1	;Reader.initÖĞÇå0
