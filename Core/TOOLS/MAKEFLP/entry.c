//*****************************************************************************
//MAKEFLP
//  ENTRY.CPP: 程序的入口点和主要实现部分
//功能:
//  制造一个软盘镜像文件
//
//*****************************************************************************
#include<stdio.h>

typedef	unsigned char	BYTE;
typedef	unsigned short	WORD;
typedef	unsigned long	DWORD;

typedef	signed int		INT;
typedef	unsigned int	UINT;

typedef short	WCHAR;

#define	SECS_PER_FAT	9
#define	BYTES_PER_SEC	0x200
#define	MEDIA_FDD		0xFF0

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

#define	DIRITEM_LASTLONGNAME	0x40//最后一个长文件名标记位，如果这个长文件名项的“bOrder”逻辑与这个值非零，则表示这是最后一个长文件名项。
typedef	struct						//FAT的长文件名目录项结构体
{
	BYTE	bOrder;					//长文件名顺序
	WCHAR	wNamePart1[5]			//5个字符的长文件名的一部份
	BYTE	bAttribute;				//属性，必须为ATTR_LONGNAME
	BYTE	bType;					//类型，为0则表示这是长文件名的一部份，其他值保留为将来扩展时用。
	BYTE	bChksum;				//校验和
	WCHAR	wNamePart2[6];			//6个字符的长文件名的一部份
	WORD	wFirstClusLO;			//必须为0
	WCHAR	wNamePart3[2]			//2个字符的长文件名的一部份
}FAT_LONGNAME;

BYTE	g_bFAT12[SECS_PER_FAT*BYTES_PER_SEC]={0};
/*
FAT12表：
字节：0 1 2 3 4 5 6 7 8
索引： 0 1   2 3   4 5
*/

void	NewFAT12()
{
	memset(g_bFAT12,0,sizeof(g_bFAT12));
	WriteFAT12Item(0,MEDIA_FDD);
	WriteFAT12Item(1,0xFFF);
}

WORD	ReadFAT12Item(WORD wIndex)
{
	UINT uByteIndex;
	WORD wRead;
	uByteIndex=(UINT)(wIndex>>1)+(UINT)wIndex;
	wRead=
	 (WORD)(g_bFAT12[uByteIndex  ])	|
	((WORD)(g_bFAT12[uByteIndex+1])	<<8);
	if(wIndex)
		return wRead>>4;
	else
		return wRead&0xFFF;
}

void	WriteFAT12Item(WORD wIndex,WORD wValue)
{
	UINT uByteIndex;
	WORD wRead;
	uByteIndex=(UINT)(wIndex>>1)+(UINT)wIndex;
	wRead=
	 (WORD)(g_bFAT12[uByteIndex  ])	|
	((WORD)(g_bFAT12[uByteIndex+1])	<<8);
	if(wIndex)
		wRead=(wRead&0xF)|(wValue<<4);
	else
		wRead=(wRead&0xF000)|(wValue&0xFFF);
}




void PrintUsage()
{
	printf(
		"Usage:\n"
		"MAKEFLP OUT.img <-bxxxx> files\n"
		"  -b:[Optional]Write xxxx to the DBR sector\n");
}

int main(int argc,char** argv)
{
	if(argc<3)
	{
		PrintUsage();
		return -1;
	}
}






