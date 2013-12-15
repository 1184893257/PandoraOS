//*****************************************************************************
//MAKEFLP
//  ENTRY.CPP: �������ڵ����Ҫʵ�ֲ���
//����:
//  ����һ�����̾����ļ�
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

typedef	struct				//FATĿ¼��ṹ��
{
	char	szFileName[8];	//8�ֽڶ��ļ�������һ���ֽڿ�����DIRITEM_DELETED���фh������DIRITEM_FREE�����п��ã�
	char	szExt[3];		//3�ֽ���չ��
	BYTE	bAttribute;		//1�ֽ�����
	BYTE	bReserved;		//����
	BYTE	bCreateTimeMS;	//�ļ�����ʱ��ĺ�������10����ֵΪ0-199��ʵΪ0-1990���룬��Ϊ�ļ�ʱ�����������������Ϊ��λ��
	WORD	wCreateTime;	//�ļ�����ʱ��
	WORD	wCreateDate;	//�ļ���������
	WORD	wLastAccDate;	//����������
	WORD	wFirstClusHI;	//�״غŵĸ�16λ
	WORD	wWriteTime;		//���д������ʱ��
	WORD	wWriteDate;		//���д����������
	WORD	wFirstClusLO;	//�״غŵĵ�16λ
	DWORD	dwFileSize;		//�ļ���С
}FAT_DIRITEM;

#define	DIRITEM_LASTLONGNAME	0x40//���һ�����ļ������λ�����������ļ�����ġ�bOrder���߼������ֵ���㣬���ʾ�������һ�����ļ����
typedef	struct						//FAT�ĳ��ļ���Ŀ¼��ṹ��
{
	BYTE	bOrder;					//���ļ���˳��
	WCHAR	wNamePart1[5]			//5���ַ��ĳ��ļ�����һ����
	BYTE	bAttribute;				//���ԣ�����ΪATTR_LONGNAME
	BYTE	bType;					//���ͣ�Ϊ0���ʾ���ǳ��ļ�����һ���ݣ�����ֵ����Ϊ������չʱ�á�
	BYTE	bChksum;				//У���
	WCHAR	wNamePart2[6];			//6���ַ��ĳ��ļ�����һ����
	WORD	wFirstClusLO;			//����Ϊ0
	WCHAR	wNamePart3[2]			//2���ַ��ĳ��ļ�����һ����
}FAT_LONGNAME;

BYTE	g_bFAT12[SECS_PER_FAT*BYTES_PER_SEC]={0};
/*
FAT12��
�ֽڣ�0 1 2 3 4 5 6 7 8
������ 0 1   2 3   4 5
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






