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

#define	SECS_PER_FAT	9
#define	BYTES_PER_SEC	0x200

BYTE	g_bFAT12[SECS_PER_FAT*BYTES_PER_SEC];
/*
FAT12表：
字节：0 1 2 3 4 5 6 7 8
索引： 0 1   2 3   4 5
*/

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






