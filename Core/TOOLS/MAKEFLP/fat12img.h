#ifndef	_FAT12_IMAGE_GENERATOR_
#define	_FAT12_IMAGE_GENERATOR_

#ifndef	FAT12IMG_EXTRN
#ifdef	__cplusplus
#define	FAT12IMG_EXTRN	extern "C"
#else
#define	FAT12IMG_EXTRN	extern
#endif
#endif

#include<stdio.h>

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

#pragma pack(push,1)

#define	FLOPPY_SECS_PER_FAT		9
#define	FLOPPY_BYTES_PER_SEC	0x200
#define	FLOPPY_BYTES_PER_CLUS	FLOPPY_BYTES_PER_SEC
#define	FLOPPY_MAX_ROOT			0xE0
#define	FLOPPY_DBR_SECS			1
#define	FLOPPY_FAT_SECS			9
#define	FLOPPY_FAT_COUNT		2
#define	FLOPPY_ROOT_SECS		(FLOPPY_MAX_ROOT>>4)
#define	FLOPPY_HEADS			2
#define	FLOPPY_SECS_PER_TRACK	18
#define	FLOPPY_TRACKS			80
#define	FLOPPY_SIZE				(FLOPPY_TRACKS*FLOPPY_HEADS*FLOPPY_SECS_PER_TRACK*FLOPPY_BYTES_PER_SEC)
#define	FLOPPY_CLUS_MAX			0xFEF
#define	FLOPPY_CLUS_MIN			2
#define	FLOPPY_CLUS_END			0xFFF
#define	FLOPPY_VALID_CLUS(c)	((c)>=FLOPPY_CLUS_MIN&&(c)<=FLOPPY_CLUS_MAX)
#define	MEDIA_FDD				0xF0

//文件目录项的值
#define	ATTR_NORMAL			0x00
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

//不合法的文件名字符：\ / * ? " < > |
#define	VALIDCHR(c)			((c)!= '\\'&&(c)!= '/'&&(c)!= '*'&&(c)!= '?'&&(c)!= '\"'&&(c)!= '<'&&(c)!= '>'&&(c)!= '|'&&(c)>0x20&&(c)<0x80)
#define	VALIDWCHR(c)		((c)!=L'\\'&&(c)!=L'/'&&(c)!=L'*'&&(c)!=L'?'&&(c)!=L'\"'&&(c)!=L'<'&&(c)!=L'>'&&(c)!=L'|'&&(c)>0x20&&(c)<0x80)

#define	MAKETIME(h,m,s)		((((s)/2)&0x1F)|(((m)&0x3F)<<5)|(((h)&0x1F)<<11))
#define	MAKEDATE(y,m,d)		((((d)&0x1F))|(((m)&0x0F)<<5)|(((y)&0x7F)<<9))

#define	DIRITEM_LASTLONGNAME	0x40				//最后一个长文件名标记位，如果这个长文件名项的“bOrder”逻辑与这个值非零，则表示这是最后一个长文件名项。
#define	DIRITEM_LONGNAMELEN		0x100				//长文件名最大长度
#define	DIRITEM_CHARSPERITEM	(5+6+2)				//长文件名项每项字符数（13？M$怎么想的，这个数字不吉利）
#define	DIRITEM_MAXSHORTALIAS	1000000				//短文件名最大别名数
typedef	struct										//FAT的长文件名目录项结构体
{
	BYTE	bOrder;									//长文件名顺序
	WCHAR	wNamePart1[5];							//5个字符的长文件名的一部份
	BYTE	bAttribute;								//属性，必须为ATTR_LONGNAME
	BYTE	bType;									//类型，为0则表示这是长文件名的一部份，其他值保留为将来扩展时用。
	BYTE	bChksum;								//校验和
	WCHAR	wNamePart2[6];							//6个字符的长文件名的一部份
	WORD	wFirstClusLO;							//必须为0
	WCHAR	wNamePart3[2];							//2个字符的长文件名的一部份
}FAT_LONGNAME;

FAT12IMG_EXTRN	FILE		*pErrStream;										//输出错误的文件流

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

FAT12IMG_EXTRN	void NewFAT12(void);												//初始化FAT表
FAT12IMG_EXTRN	void NewRoot(void);													//初始化根目录区
FAT12IMG_EXTRN	void NewData(void);													//初始化数据区

FAT12IMG_EXTRN	WORD ReadFAT12Item(WORD wIndex);									//读FAT表
FAT12IMG_EXTRN	void WriteFAT12Item(WORD wIndex,WORD wValue);						//写FAT表

FAT12IMG_EXTRN	WORD FindFreeClus(void);											//寻找空闲簇
FAT12IMG_EXTRN	WORD AllocateNewCluster(WORD wParentCluster);						//给簇链分配新的簇

FAT12IMG_EXTRN	FAT_DIRITEM* FindFreeRootItem(void);								//寻找空闲根目录项
FAT12IMG_EXTRN	FAT_DIRITEM* FindFreeDirItem(WORD wDirClus);						//从子目录寻找空闲目录项
FAT12IMG_EXTRN	FAT_DIRITEM* FindShortNameInRoot(char *szShort,char *szExt);		//在根目录表查找短文件名
FAT12IMG_EXTRN	FAT_DIRITEM* FindLongNameInRoot(WCHAR *wLongName);					//在根目录表查找长文件名
FAT12IMG_EXTRN	FAT_DIRITEM* FindShortNameInDir(WORD wDirClus,char *szShort,char *szExt);//在目录表查找短文件名
FAT12IMG_EXTRN	FAT_DIRITEM* FindLongNameInDir(WORD wDirClus,WCHAR *wLongName);		//在目录表查找长文件名
FAT12IMG_EXTRN	FAT_DIRITEM* FindShortNameInRootByCheckSum(BYTE);					//从根目录区找到这个校验和的原文件名
FAT12IMG_EXTRN	FAT_DIRITEM* FindShortNameInDirByCheckSum(WORD wCluster,BYTE);		//从目录找到这个校验和的原文件名

FAT12IMG_EXTRN	void*GetClusterPtr(WORD wCluster);									//通过簇号取得数据区簇指针
FAT12IMG_EXTRN	WORD GetClusterChainLength(WORD wCluster);							//检查簇链的长度

FAT12IMG_EXTRN	BYTE ShortNameCheckSum(BYTE *pFileName8_3);							//取得短文件名的校验和

FAT12IMG_EXTRN	BOOL ValidateName(WCHAR *wLongName);								//检查长文件名是否合法
FAT12IMG_EXTRN	BOOL GenShortName(char *szLongName,WCHAR *wLongNameOut,char *szShortOut,char *szExtOut);//生成一个短文件名
FAT12IMG_EXTRN	void GenShortNameAlias(char *szShort);								//取得另一个短文件名，假设原来的短文件名为XXXXXX~1，此函数将生成XXXXXX~2

FAT12IMG_EXTRN	BOOL CollectLongNameFromRoot(BYTE,WCHAR *wLongName);				//在根目录区从一个校验和找到所有长文件名组分，组成一个长文件名
FAT12IMG_EXTRN	BOOL CollectLongNameFromDir(WORD wCluster,BYTE,WCHAR *wLongName);	//在目录中从一个校验和找到所有长文件名组分，组成一个长文件名

FAT12IMG_EXTRN	BOOL IsFreeDirItem(FAT_DIRITEM*);									//判断目录项是否为空闲目录项

FAT12IMG_EXTRN	FAT_DIRITEM* ParseItem(	char *szFile,BYTE bAttr,					//从文件名产生短文件名项、长文件名项
										FAT_DIRITEM*(__cdecl*NewItem)(void),							//创建目录项的子程序
										FAT_DIRITEM*(__cdecl*FindLongName)(WCHAR *wLongName),			//查找长文件名的子程序
										FAT_DIRITEM*(__cdecl*FindShortName)(char *szShort,char *szExt));//查找短文件名的子程序
FAT12IMG_EXTRN	FAT_DIRITEM* RootCreateItem(char *szFile,BYTE bAttr);				//从根目录区创建目录项
FAT12IMG_EXTRN	FAT_DIRITEM* DirCreateItem(WORD wDirClus,char *szFile,BYTE bAttr);	//从子目录创建目录项

FAT12IMG_EXTRN	FAT_DIRITEM* CreateEmptyDir(WORD wParentClus,char *szName,BYTE bAttribute);	//创建空目录，返回目录在父目录的项
FAT12IMG_EXTRN	FAT_DIRITEM* CreateEmptyFile(WORD wParentClus,char *szName,BYTE bAttribute);//创建空文件，返回文件在父目录的项
FAT12IMG_EXTRN	DWORD WriteDataToEOF(FAT_DIRITEM* pFileItem,void *pData,DWORD dwDataSize);	//写数据到文件尾，返回实际写入的字节数。

FAT12IMG_EXTRN	void SetCreateTime		(FAT_DIRITEM *pItem,struct _timeb *pTime);	//设置目录项的创建时间
FAT12IMG_EXTRN	void SetLastAccessDate	(FAT_DIRITEM *pItem,struct _timeb *pTime);	//设置目录项的最后访问日期
FAT12IMG_EXTRN	void SetLastWriteTime	(FAT_DIRITEM *pItem,struct _timeb *pTime);	//设置目录项的最后写的时间

FAT12IMG_EXTRN	WORD GetNbFreeClusters(void);										//统计空闲簇数

FAT12IMG_EXTRN	BOOL WriteFloppy(char *szFile,char *szDBRFile);						//保存镜像到文件


#pragma pack(pop)

#endif
