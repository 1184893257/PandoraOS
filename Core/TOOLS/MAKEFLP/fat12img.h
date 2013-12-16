#ifndef	_FAT12_IMAGE_GENERATOR_
#define	_FAT12_IMAGE_GENERATOR_

#ifndef	FAT12IMG_EXTRN
#ifdef	__cplusplus
#define	FAT12IMG_EXTRN	extern "C"
#else
#define	FAT12IMG_EXTRN	extern
#endif
#endif

typedef	unsigned char	BYTE;
typedef	unsigned short	WORD;
typedef	unsigned long	DWORD;

typedef	signed int		INT;
typedef	unsigned int	UINT;

typedef unsigned short	wchar_t;
typedef			wchar_t	WCHAR;

typedef	int		BOOL;
#define	TRUE	1
#define	FALSE	0

#define	FLOPPY_SECS_PER_FAT		9
#define	FLOPPY_BYTES_PER_SEC	0x200
#define	FLOPPY_MAX_ROOT			0xE0
#define	FLOPPY_DBR_SECS			1
#define	FLOPPY_FAT_SECS			9
#define	FLOPPY_FAT_COUNT		2
#define	FLOPPY_ROOT_SECS		(FLOPPY_MAX_ROOT>>4)
#define	FLOPPY_HEADS			2
#define	FLOPPY_SECS_PER_TRACK	18
#define	FLOPPY_TRACKS			80
#define	FLOPPY_SIZE				(FLOPPY_TRACKS*FLOPPY_HEADS*FLOPPY_TRACKS*FLOPPY_BYTES_PER_SEC)
#define	FLOPPY_CLUS_MAX			0xFEF
#define	FLOPPY_CLUS_MIN			2
#define	FLOPPY_CLUS_END			0xFFF
#define	MEDIA_FDD				0xF0

//文件目录项的值
#define	ATTR_READONLY		0x01
#define	ATTR_HIDE			0x02
#define	ATTR_SYSTEM			0x04
#define	ATTR_VOLUMELABEL	0x08
#define	ATTR_SUBDIR			0x10
#define	ATTR_ARCHIVE		0x20
#define	ATTR_LONGNAME		0x0F

#define	DIRITEM_DELETED		0xE5
#define	DIRITEM_FREE		0x00
#define	DIRITEM_DELETED_JPN	0x05//在日本，这个值等同于DIRITEM_DELETED

#define	DIRITEM_SELF		".          "
#define	DIRITEM_PARENT		"..         "

typedef	struct				//FAT目录项结构体
{
	char	szFileName[8];	//8字节短文件名，第一个字节可以是DIRITEM_DELETED（已刪除）或DIRITEM_FREE（空闲可用）
	char	szExt[3];		//3字节扩展名
	BYTE	bAttribute;		//1字节属性
	BYTE	bReserved;		//保留
	BYTE	bCreateTimeMS;	//文件创建时间的毫秒数的10倍（值为0-199，实为0-1990毫秒，因为文件时间戳的秒数是以两秒为单位）
	WORD	wCreateTime;	//文件创建时间
	WORD	wCreateDate;	//文件创建日期
	WORD	wLastAccDate;	//最后访问日期
	WORD	wFirstClusHI;	//首簇号的高16位
	WORD	wWriteTime;		//最后写操作的时间
	WORD	wWriteDate;		//最后写操作的日期
	WORD	wFirstClusLO;	//首簇号的低16位
	DWORD	dwFileSize;		//文件大小
}FAT_DIRITEM;

#define	VALIDCHR(c)			((c)!= '\\'&&(c)!= '/'&&(c)!= '*'&&(c)!= '?'&&(c)!= '\"'&&(c)!= '<'&&(c)!= '>'&&(c)!= '|'&&(c)>0x20&&(c)<0x80)
#define	VALIDWCHR(c)		((c)!=L'\\'&&(c)!=L'/'&&(c)!=L'*'&&(c)!=L'?'&&(c)!=L'\"'&&(c)!=L'<'&&(c)!=L'>'&&(c)!=L'|'&&(c)>0x20&&(c)<0x80)

#define	MAKETIME(h,m,s)		((((s)/2)&0x1F)|(((m)&0x3F)<<5)|(((h)&0x1F)<<11))
#define	MAKEDATE(y,m,d)		((((d)&0x1F))|(((m)&0x0F)<<5)|(((y)&0x7F)<<9))

#define	DIRITEM_LASTLONGNAME	0x40//最后一个长文件名标记位，如果这个长文件名项的“bOrder”逻辑与这个值非零，则表示这是最后一个长文件名项。
#define	DIRITEM_LONGNAMELEN		0x100//长文件名最大长度
typedef	struct						//FAT的长文件名目录项结构体
{
	BYTE	bOrder;					//长文件名顺序
	WCHAR	wNamePart1[5];			//5个字符的长文件名的一部份
	BYTE	bAttribute;				//属性，必须为ATTR_LONGNAME
	BYTE	bType;					//类型，为0则表示这是长文件名的一部份，其他值保留为将来扩展时用。
	BYTE	bChksum;				//校验和
	WCHAR	wNamePart2[6];			//6个字符的长文件名的一部份
	WORD	wFirstClusLO;			//必须为0
	WCHAR	wNamePart3[2];			//2个字符的长文件名的一部份
}FAT_LONGNAME;

FAT12IMG_EXTRN	BYTE		g_bDefaultDBR[FLOPPY_BYTES_PER_SEC];				//默认DBR
FAT12IMG_EXTRN	BYTE		g_bFAT12[FLOPPY_SECS_PER_FAT*FLOPPY_BYTES_PER_SEC];	//FAT表
FAT12IMG_EXTRN	FAT_DIRITEM	g_RootDirs[FLOPPY_MAX_ROOT];						//根目录区
FAT12IMG_EXTRN	BYTE		g_bDataArea											//数据区
[
	FLOPPY_SIZE-
	(FLOPPY_DBR_SECS+
	FLOPPY_FAT_SECS*FLOPPY_FAT_COUNT+
	FLOPPY_ROOT_SECS)
	*FLOPPY_BYTES_PER_SEC
];

void NewFAT12();	//初始化FAT表
void NewRoot();		//初始化根目录区
void NewData();		//初始化数据区

WORD ReadFAT12Item(WORD wIndex);					//读FAT表
void WriteFAT12Item(WORD wIndex,WORD wValue);		//写FAT表

WORD FindFreeClus();								//寻找空闲簇
FAT_DIRITEM* FindFreeRootItem();					//寻找空闲根目录项
FAT_DIRITEM* FindFreeDirItem(WORD wDirClus);		//从子目录寻找空闲目录项

void* GetClusterPtr(WORD wCluster);					//通过簇号取得数据区簇指针

BYTE ShortNameCheckSum(BYTE *pFileName8_3);			//取得短文件名的校验和

BOOL GenShortName(char *szLongName,WCHAR *wLongNameOut,char *szShortOut,char *szExtOut);//生成一个短文件名
BOOL IsShortNameDupInRoot(char *szShort,char *szExt);//检查在根目录表短文件名是否重复
BOOL IsShortNameDupInDir(WORD wDirClus,char *szShort,char *szExt);//检查在目录表短文件名是否重复

FAT_DIRITEM* RootCreateItem(char *szFile,BYTE bAttr);//从根目录区创建目录项
FAT_DIRITEM* DirCreateItem(WORD wDirClus,char *szFile,BYTE bAttr);//从子目录创建目录项

#endif
