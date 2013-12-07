%ifndef __FAT_INFORMATION_INCLUDED__
%define	__FAT_INFORMATION_INCLUDED__

%define	OEM_NAME			"炫酷屌炸"		;OEM名字必须为8字节

%define	MEDIA_FDD			0xF0			;介质类型：软盘
%define	MEDIA_HDD			0xF8			;介质类型：硬盘

%define	CHS_MAX				0x00FBFFFF		;CHS寻址方式能寻址的最大扇区数。

%define	FS_FAT12			"FAT12   "		;文件系統，必须为8字节
%define	FS_FAT16			"FAT16   "
%define	FS_FAT32			"FAT32   "

%define	FLAG_EXT			0x29			;DBR扩展引导参数标识
%define	FLAG_BOOTALBE		0xAA55			;可引导标识

%define	LABEL_DEF			"NO NAME    "	;默认卷标名，必须为11字节

%define	SIZE_FILENAME		(8+3)
%define	SIZE_DIRENTRY		0x20

%define	FLOPPY_RESV_SECS	1
%define	FLOPPY_SEC_PER_CLS	1
%define	FLOPPY_SEC_PER_CYL	18
%define	FLOPPY_SEC_LEN		0x200
%define	FLOPPY_FAT_SECS		9
%define	FLOPPY_HEAD_COUNT	2
%define	FLOPPY_FAT_COUNT	2
%define	FLOPPY_CYL_PER_HEAD	80
%define	FLOPPY_SEC_COUNT	(FLOPPY_SEC_PER_CYL*FLOPPY_HEAD_COUNT*FLOPPY_CYL_PER_HEAD)
%define FLOPPY_ROOT_ITEMS	224
%define	FLOPPY_ROOT_LBA		(FLOPPY_RESV_SECS+FLOPPY_FAT_COUNT*FLOPPY_FAT_SECS)
%define	FLOPPY_FAT_ITEMS	0x600			;软盘的FAT表项数

%define	FLOPPY_FAT_BUFFER	0xA00			;软盘读取FAT的缓冲区
%define	FLOPPY_DIR_BUFFER	(FLOPPY_FAT_BUFFER+FLOPPY_FAT_SECS*FLOPPY_SEC_LEN)

%define	HDD_SEC_LEN			0x200
%define	HDD_DIR_BUFFER		0xA00
%define	HDD_FAT_BUFFER		0xA00

;FAT表的第一个表项永远是用来标示磁盘介质类型的。
;这个表项的低8位永远等于DBR中指定的介质类型（MEDIA_FDD、MEDIA_HDD）
;高位全部置1
;第二个表项永远是EOC（尾簇标识）。注意FAT16和FAT32的这个尾簇标识有新的用处。
;如果第二个表项最高位被设置为1，则这个介质是“干净的”。
;如果没有被设置为1，则这个介质是“脏的”，也就是没有合理完成写入文件的工作。这时候最好运行一下CHKDSK检查一下分区。
;如果倒数第二位被设置为1则说明这个介质出现了问題。任何读、写的操作都是不允许的。必须对分区进行修复检查，否则可能会导致数据丟失。
%define	FAT16_CLEAN			0x8000
%define	FAT16_ERROR			0x4000

%define	FAT32_CLEAN			0x08000000
%define	FAT32_ERROR			0x04000000

;FAT簇号的特殊值
%define	FAT12_IDLECLUSTER	0x000
%define	FAT12_RESERVED		0x001
%define	FAT12_MINVALIDCLUS	0x002
%define	FAT12_MAXVALIDCLUS	0xFEF
%define	FAT12_BADCLUS		0xFF7
%define	FAT12_EOC			0xFFF

%define	FAT16_IDLECLUSTER	0x0000
%define	FAT16_RESERVED		0x0001
%define	FAT16_MINVALIDCLUS	0x0002
%define	FAT16_MAXVALIDCLUS	0xFFEF
%define	FAT16_BADCLUS		0xFFF7
%define	FAT16_EOC			0xFFFF

%define	FAT32_IDLECLUSTER	0x00000000
%define	FAT32_RESERVED		0x00000001
%define	FAT32_MINVALIDCLUS	0x00000002
%define	FAT32_MAXVALIDCLUS	0x0FFFFFEF
%define	FAT32_BADCLUS		0x0FFFFFF7
%define	FAT32_EOC			0x0FFFFFFF

;文件目录项的值
%define	ATTR_READONLY		0x01
%define	ATTR_HIDE			0x02
%define	ATTR_SYSTEM			0x04
%define	ATTR_VOLUMELABEL	0x08
%define	ATTR_SUBDIR			0x10
%define	ATTR_ARCHIVE		0x20
%define	ATTR_LONGNAME		0x0F

%define	DIRITEM_DELETED		0xE5
%define	DIRITEM_FREE		0x00
%define	DIRITEM_DELETED_JPN	0x05;在日本，这个值等同于DIRITEM_DELETED

%define	DIRITEM_SELF		".          "
%define	DIRITEM_PARENT		"..         "

struc FAT_DIRITEM				;FAT目录项结构体
	.szFileName		resb	8	;8字节短文件名，第一个字节可以是DIRITEM_DELETED（已刪除）或DIRITEM_FREE（空闲可用）
	.szExt			resb	3	;3字节扩展名
	.bAttribute		resb	1	;1字节属性
	.bReserved		resb	1	;保留
	.bCreateTimeMS	resb	1	;文件创建时间的毫秒数的10倍（值为0-199，实为0-1990毫秒，因为文件时间戳的秒数是以两秒为单位）
	.wCreateTime	resw	1	;文件创建时间
	.wCreateDate	resw	1	;文件创建日期
	.wLastAccDate	resw	1	;最后访问日期
	.wFirstClusHI	resw	1	;首簇号的高16位
	.wWriteTime		resw	1	;最后写操作的时间
	.wWriteDate		resw	1	;最后写操作的日期
	.wFirstClusLO	resw	1	;首簇号的低16位
	.dwFileSize		resd	1	;文件大小
endstruc
;日期格式：
;位0-4：	日期，值为1-31
;位5-8：	月份，值为1-12
;位9-15：	年，从1980开始，到2107年，共127年
;时间格式：
;位0-4：	秒数/2（值为0-29，实际表示0-58秒）
;位5-10：	分钟，值为0-59
;位11-15：	小时，值为0-23
;短文件名可使用的符号：$ % ' - _ @ ~ ` ! ( ) { } ^ # &

;FAT的目录项中支持长文件名，长文件名用特殊的目录项来取代，每个长文件名目录项支持13字符。
;校验和相同的长文件名目录项被认作同一个文件的长文件名。长文件名使用UNICODE编码。
;长文件名目录项按照顺序存储，指定了DIRITEM_LASTLONGNAME的长文件名目录项被人做最后一个长文件名目录项。
%define	DIRITEM_LASTLONGNAME	0x40;最后一个长文件名标记位，如果这个长文件名项的“bOrder”逻辑与这个值非零，则表示这是最后一个长文件名项。
struc FAT_LONGNAME					;FAT的长文件名目录项结构体
	.bOrder				resb	1	;长文件名顺序
	.wNamePart1			resw	5	;5个字符的长文件名的一部份
	.bAttribute			resb	1	;属性，必须为ATTR_LONGNAME
	.bType				resb	1	;类型，为0则表示这是长文件名的一部份，其他值保留为将来扩展时用。
	.bChksum			resb	1	;校验和
	.wNamePart2			resw	6	;6个字符的长文件名的一部份
	.wFirstClusLO		resw	1	;必须为0
	.wNamePart3			resw	2	;2个字符的长文件名的一部份
endstruc
;长文件名禁止使用的字符：+ , ; = [ ]
;长文件名使用UNICODE编码。
;校验和计算方式：
;//-----------------------------------------------------------------------------
;// ChkSum()
;// Returns an unsigned byte checksum computed on an unsigned byte
;// array. The array must be 11 bytes long and is assumed to contain
;// a name stored in the format of a MS-DOS directory entry.
;// Passed: pFcbName Pointer to an unsigned byte array assumed to be
;// 11 bytes long.
;// Returns:Sum An 8-bit unsigned checksum of the array pointed
;// to by pFcbName.
;//------------------------------------------------------------------------------
;unsigned char ChkSum (unsigned char *pFcbName)
;{
;	short FcbNameLen;
;	unsigned char Sum;
;	Sum=0;
;	for (FcbNameLen=11; FcbNameLen!=0; FcbNameLen--) {
;		// NOTE: The operation is an unsigned char rotate right
;		Sum = ((Sum & 1) ? 0x80 : 0) + (Sum >> 1) + *pFcbName++;
;	}
;	return (Sum);
;}
;每个长文件名都对应一个短文件名。
;如果你要创建一个文件並且你得到了长文件名，那么你必须创建对应的短文件名。
;短文件名合成方法：
;	把长文件名转换成全大写
;	把全大写的长文件名转换成OEM内码頁编码，非法字符换成下划线'_'
;	去掉所有长文件名前后的空格
;	去掉所有长文件名前的句点'.'
;	把长文件名前面的不是句点的8个字符作为基本的短文件名
;	从长文件名中找到最靠后的句点，如果找到句点则把句点后三个字符作为短文件名后缀

;	如果长文件名中没有非法字符，长文件名长度在8.3以內，生成的短文件名不与其它短文件名重复
;	那么这个短文件名就已经可以使用了
;	否则把文件名尾改成~n，注意~n可以从~1到~999999，选一个数字使其不与其它短文件名重复




%endif
