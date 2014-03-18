%include "SYSINF.INC"

org BOOT_ORG
bits 16

CPU 586	;¾¡Á¿±£Ö¤¼æÈÝÐÔ

%include "BPBFAT32.INC"
<<<<<<< HEAD

%define FATBuffer	(DBR_NEWPOS + 1024)	;FAT»º³åÇøµØÖ·, »º´æÒ»¸öÉÈÇø(Ç°1024×Ö½ÚÓÃÓÚ: µÚÒ»¸ö512×Ö½ÚÊÇDBR, ºó512×Ö½ÚÊÇBSSÊý¾ÝºÍÕ»)
%define rootEntries	2000h				;¸ùÄ¿Â¼»º³åÇøµØÖ·, »º´æÒ»¸ö´Ø(ÉÈÇø´óÐ¡Ð¡ÓÚ5KµÄ¾Í²»»á¸²¸ÇFATBuffer)

struc PARAMS							;²ÎÊý±í
	.IVRTable		resd	0x100			;ÖÐ¶ÏÏòÁ¿±í£¬256¸ö±íÏî£¬Ã¿¸ö±íÏî4×Ö½Ú
	.BIOSData		resb	0x200			;BIOSÊý¾ÝÇø£¬Õ¼512¸ö×Ö½Ú
	.DBR:								;ÎÒÃÇµÄDBRÔÚÕâ
	.CurFATSect		resd	1
	.DAP:								;Ó²ÅÌÊý¾Ý´«Êä°ü
	.DAPSize		resb	1			;Êý¾Ý°ü´óÐ¡
	.DAPReserved	resb	1			;±£Áô×Ö½Ú			
	.DAPBlocks		resw	1			;¿éµÄÊýÁ¿
	.DAPBufferPtr	resd	1			;»º³åÇøÖ¸Õë
	.DAPLBA			resq	1			;Êý¾Ý°üÖ¸¶¨µÄ¿éµØÖ·
endstruc

=======
>>>>>>> parent of c65bc61... å¼•å¯¼FAT32åˆ†åŒºä¸Šçš„DBRå®Œæˆäº†, å¯åœ¨å®žä½“æœºä¸­ä½¿ç”¨
Start:

%define	MOVER_SIZE		(DBR_Continue-$$)

;ÏÈ°Ñ±¾Ìå´Ó0:BOOT_ORG×ªÒÆÖÁ0:DBR_NEWPOS
cli
xor ax,ax						;¶ÔÆë¸÷¸ö¶Î
mov es,ax
mov ss,ax
mov ds,ax
mov sp,BOOT_ORG					;ÉèÖÃºÃ¶ÑÕ»
mov si,BOOT_ORG					;×¼±¸°Ñ±¾Ìå×ªÒÆµ½µÍÎ»ÄÚ´æÔËÐÐ
mov di,DBR_NEWPOS
mov cx,DBR_SIZE>>1
rep movsw						;Í¨¹ý¼õÉÙ¿½±´µÄ´ÎÊýÀ´Ìá¸ß¿½±´µÄËÙ¶È
sti
jmp 0x0000:DBR_Continue

DBR_Continue:					;´Ë´¦´ÓDBR_Continue¿ªÊ¼
<<<<<<< HEAD
mov ah,0x41
mov bx,


LOADER_SYS		db	LODR_FILENAME		;LOADER.SYSµÄ8.3¸ñÊ½µÄÃû×Ö

times DBR_SIZE-($-Start)-2	db 0
dw	FLAG_BOOTALBE

FSInfo:








times DBR_SIZE-($-FSInfo)-2	db 0
dw	FLAG_BOOTALBE

SecContinue:




times DBR_SIZE-($-SecContinue)-2	db 0
dw	FLAG_BOOTALBE
=======

times DBR_SIZE-($-$$)-2	nop
dw	FLAG_BOOTALBE
>>>>>>> parent of c65bc61... å¼•å¯¼FAT32åˆ†åŒºä¸Šçš„DBRå®Œæˆäº†, å¯åœ¨å®žä½“æœºä¸­ä½¿ç”¨
