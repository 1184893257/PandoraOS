#include"fat12img.h"
#include<ctype.h>
#include<stdio.h>
#include<memory.h>
#include<string.h>
#include<time.h>
#include<sys/timeb.h>
#include<windows.h>

BYTE	g_bDefaultDBR[FLOPPY_BYTES_PER_SEC]=
{
	0xEB,0x3C,0x90,'M', 'S', 'D', 'O', 'S', '5', '.', '0', 0x00,0x02,0x01,0x01,0x00,
	0x02,0xE0,0x00,0x40,0x0B,0xF0,0x09,0x00,0x12,0x00,0x02,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x29,0xE1,0x6C,0x87,0x2A,0x20,0x20,0x20,0x20,0x20,
	0x20,0x20,0x20,0x20,0x20,0x20,0x46,0x41,0x54,0x31,0x32,0x20,0x20,0x20,0x33,0xC9,
	0x8E,0xD1,0xBC,0xFC,0x7B,0x16,0x07,0xBD,0x78,0x00,0xC5,0x76,0x00,0x1E,0x56,0x16,
	0x55,0xBF,0x22,0x05,0x89,0x7E,0x00,0x89,0x4E,0x02,0xB1,0x0B,0xFC,0xF3,0xA4,0x06,
	0x1F,0xBD,0x00,0x7C,0xC6,0x45,0xFE,0x0F,0x38,0x4E,0x24,0x7D,0x20,0x8B,0xC1,0x99,
	0xE8,0x7E,0x01,0x83,0xEB,0x3A,0x66,0xA1,0x1C,0x7C,0x66,0x3B,0x07,0x8A,0x57,0xFC,
	0x75,0x06,0x80,0xCA,0x02,0x88,0x56,0x02,0x80,0xC3,0x10,0x73,0xED,0x33,0xC9,0xFE,
	0x06,0xD8,0x7D,0x8A,0x46,0x10,0x98,0xF7,0x66,0x16,0x03,0x46,0x1C,0x13,0x56,0x1E,
	0x03,0x46,0x0E,0x13,0xD1,0x8B,0x76,0x11,0x60,0x89,0x46,0xFC,0x89,0x56,0xFE,0xB8,
	0x20,0x00,0xF7,0xE6,0x8B,0x5E,0x0B,0x03,0xC3,0x48,0xF7,0xF3,0x01,0x46,0xFC,0x11,
	0x4E,0xFE,0x61,0xBF,0x00,0x07,0xE8,0x28,0x01,0x72,0x3E,0x38,0x2D,0x74,0x17,0x60,
	0xB1,0x0B,0xBE,0xD8,0x7D,0xF3,0xA6,0x61,0x74,0x3D,0x4E,0x74,0x09,0x83,0xC7,0x20,
	0x3B,0xFB,0x72,0xE7,0xEB,0xDD,0xFE,0x0E,0xD8,0x7D,0x7B,0xA7,0xBE,0x7F,0x7D,0xAC,
	0x98,0x03,0xF0,0xAC,0x98,0x40,0x74,0x0C,0x48,0x74,0x13,0xB4,0x0E,0xBB,0x07,0x00,
	0xCD,0x10,0xEB,0xEF,0xBE,0x82,0x7D,0xEB,0xE6,0xBE,0x80,0x7D,0xEB,0xE1,0xCD,0x16,
	0x5E,0x1F,0x66,0x8F,0x04,0xCD,0x19,0xBE,0x81,0x7D,0x8B,0x7D,0x1A,0x8D,0x45,0xFE,
	0x8A,0x4E,0x0D,0xF7,0xE1,0x03,0x46,0xFC,0x13,0x56,0xFE,0xB1,0x04,0xE8,0xC2,0x00,
	0x72,0xD7,0xEA,0x00,0x02,0x70,0x00,0x52,0x50,0x06,0x53,0x6A,0x01,0x6A,0x10,0x91,
	0x8B,0x46,0x18,0xA2,0x26,0x05,0x96,0x92,0x33,0xD2,0xF7,0xF6,0x91,0xF7,0xF6,0x42,
	0x87,0xCA,0xF7,0x76,0x1A,0x8A,0xF2,0x8A,0xE8,0xC0,0xCC,0x02,0x0A,0xCC,0xB8,0x01,
	0x02,0x80,0x7E,0x02,0x0E,0x75,0x04,0xB4,0x42,0x8B,0xF4,0x8A,0x56,0x24,0xCD,0x13,
	0x61,0x61,0x72,0x0A,0x40,0x75,0x01,0x42,0x03,0x5E,0x0B,0x49,0x75,0x77,0xC3,0x03,
	0x18,0x01,0x27,0x0D,0x0A,0x49,0x6E,0x76,0x61,0x6C,0x69,0x64,0x20,0x73,0x79,0x73,
	0x74,0x65,0x6D,0x20,0x64,0x69,0x73,0x6B,0xFF,0x0D,0x0A,0x44,0x69,0x73,0x6B,0x20,
	0x49,0x2F,0x4F,0x20,0x65,0x72,0x72,0x6F,0x72,0xFF,0x0D,0x0A,0x52,0x65,0x70,0x6C,
	0x61,0x63,0x65,0x20,0x74,0x68,0x65,0x20,0x64,0x69,0x73,0x6B,0x2C,0x20,0x61,0x6E,
	0x64,0x20,0x74,0x68,0x65,0x6E,0x20,0x70,0x72,0x65,0x73,0x73,0x20,0x61,0x6E,0x79,
	0x20,0x6B,0x65,0x79,0x0D,0x0A,0x00,0x00,0x49,0x4F,0x20,0x20,0x20,0x20,0x20,0x20,
	0x53,0x59,0x53,0x4D,0x53,0x44,0x4F,0x53,0x20,0x20,0x20,0x53,0x59,0x53,0x7F,0x01,
	0x00,0x41,0xBB,0x00,0x07,0x60,0x66,0x6A,0x00,0xE9,0x3B,0xFF,0x00,0x00,0x55,0xAA
};
BYTE		g_bFAT12[FLOPPY_SECS_PER_FAT*FLOPPY_BYTES_PER_SEC]={0};
FAT_DIRITEM	g_RootDirs[FLOPPY_MAX_ROOT];
BYTE		g_bDataArea
[
	FLOPPY_SIZE-
	(FLOPPY_DBR_SECS+
	FLOPPY_FAT_SECS*FLOPPY_FAT_COUNT+
	FLOPPY_ROOT_SECS)
	*FLOPPY_BYTES_PER_SEC
];

//-----------------------------------------------------------------------------
//NewFAT12����ʼ��FAT12��FAT��
//-----------------------------------------------------------------------------
void NewFAT12(void)
{
	memset(g_bFAT12,0,sizeof(g_bFAT12));
	WriteFAT12Item(0,MEDIA_FDD|0xF00);
	WriteFAT12Item(1,0xFFF);
}

//-----------------------------------------------------------------------------
//NewRoot����ʼ��FAT12�ĸ�Ŀ¼��
//-----------------------------------------------------------------------------
void NewRoot(void)
{
	memset(g_RootDirs,0,sizeof(g_RootDirs));
}

//-----------------------------------------------------------------------------
//NewData����ʼ��FAT12����������Ҳ����ȫ����գ�
//-----------------------------------------------------------------------------
void NewData(void)
{
	memset(g_bDataArea,0,sizeof(g_bDataArea));
}

//-----------------------------------------------------------------------------
//ReadFAT12Item����ȡFAT12��FAT��ı���
//-----------------------------------------------------------------------------
WORD ReadFAT12Item(WORD wIndex)
{
/*
	FAT12��
	�ֽڣ�0 1 2 3 4 5 6 7 8
	������ 0 1   2 3   4 5
*/
	UINT uPos;
	WORD wVal;
	uPos=(UINT)(wIndex>>1)+(UINT)wIndex;
	wVal=*(WORD*)(&g_bFAT12[uPos]);
	if(wIndex&1)
		return wVal>>4;
	else
		return wVal&0xFFF;
}

//-----------------------------------------------------------------------------
//WriteFAT12Item��д��FAT12��FAT��ı���
//-----------------------------------------------------------------------------
void WriteFAT12Item(WORD wIndex,WORD wValue)
{
	UINT uPos;
	WORD wVal;
	uPos=(UINT)(wIndex>>1)+(UINT)wIndex;
	wVal=*(WORD*)(&g_bFAT12[uPos]);
	*(WORD*)(&g_bFAT12[uPos])=
		(wIndex&1)?
			(wVal&0xF)|(wValue<<4):
			(wVal&0xF000)|wValue;
}

//-----------------------------------------------------------------------------
//FindFreeClus��Ѱ�ҿ��дغ�
//-----------------------------------------------------------------------------
WORD FindFreeClus(void)
{
	WORD i;
	for(i=FLOPPY_CLUS_MIN;i<=FLOPPY_CLUS_MAX;i++)
	{
		if(!ReadFAT12Item(i))//�ҵ����дغ��򷵻�
			return i;
	}
	return 0;
}

//-----------------------------------------------------------------------------
//FindFreeRootItem��Ѱ�ҿ��и�Ŀ¼��
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindFreeRootItem(void)
{
	WORD i;
	for(i=0;i<FLOPPY_MAX_ROOT;i++)
	{
		if(IsFreeDirItem(&g_RootDirs[i]))
			return &g_RootDirs[i];	
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//FindFreeDirItem��Ѱ�ҿ���Ŀ¼��
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindFreeDirItem(WORD wDirClus)
{
	WORD i;
	FAT_DIRITEM* pDir;
	while(FLOPPY_VALID_CLUS(wDirClus))
	{
		pDir=(FAT_DIRITEM*)GetClusterPtr(wDirClus);	//ȡ��Ŀ¼��ָ��
		if(!pDir)
			return NULL;
		for(i=0;i<16;i++)							//��Ŀ¼���ҿ���Ŀ¼��
		{
			if(IsFreeDirItem(&pDir[i]))
				return &pDir[i];					//�ҵ��򷵻�
		}
		wDirClus=ReadFAT12Item(wDirClus);			//����Ӵ����ҵ���һ��Ŀ¼���λ�ü�����
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//GetClusterPtr��ȡ�ô�����������Ӧ�غŵ�ָ��
//-----------------------------------------------------------------------------
void* GetClusterPtr(WORD wCluster)
{
	if(FLOPPY_VALID_CLUS(wCluster))
		return (void*)&g_bDataArea[(wCluster-FLOPPY_CLUS_MIN)*FLOPPY_BYTES_PER_SEC];
	else
		return NULL;
}

//-----------------------------------------------------------------------------
//GetClusterChainLength��ȡ�ô�������
//-----------------------------------------------------------------------------
WORD GetClusterChainLength(WORD wCluster)
{
	WORD wLen=0;//�������ȴ�0��ʼͳ��
	if(!wCluster)//����ǿ��д��򷵻�0
		return 0;
	while(FLOPPY_VALID_CLUS(wCluster))
	{
		wLen++;
		wCluster=ReadFAT12Item(wCluster);
	}
	return wLen;
}

//-----------------------------------------------------------------------------
//ShortNameCheckSum��ȡ�ö��ļ�����У��ͣ����ڳ��ļ���Ŀ¼��
//-----------------------------------------------------------------------------
BYTE ShortNameCheckSum(BYTE *pFileName8_3)
{
	unsigned	FcbNameLen=11;
	BYTE		Sum=0;
	while(FcbNameLen--)
		Sum=((Sum&1)?0x80:0)+(Sum>>1)+*pFileName8_3++;
	return Sum;
}

//-----------------------------------------------------------------------------
//ValidateName����鳤�ļ����Ƿ�Ϸ�
//-----------------------------------------------------------------------------
BOOL ValidateName(WCHAR *wLongName)
{
	UINT uIndex,uLen;
	uLen=wcslen(wLongName);
	if(uLen>DIRITEM_LONGNAMELEN)
		return FALSE;
	for(uIndex=0;uIndex<uLen;uIndex++)
	{
		if(	wLongName[uIndex]<0x20	||	//�����в��ɴ�ӡ�ַ��������пո�
			wLongName[uIndex]==L'\\'||	//�ļ����в�����·���ָ���'\'
			wLongName[uIndex]==L'/'	||	//�Լ�'/'
			wLongName[uIndex]==L'*'	||	//������ͨ���'*'
			wLongName[uIndex]==L'?'	||	//��'?'
			wLongName[uIndex]==L'\"'||	//�����а��˫����'"'
			wLongName[uIndex]==L'<'	||	//�������ض������'<'
			wLongName[uIndex]==L'>'	||	//��'>'
			wLongName[uIndex]==L'|')	//Ҳ�����йܵ�'|'
			return FALSE;
	}
	return TRUE;
}

//-----------------------------------------------------------------------------
//GenShortName������һ�������Ķ��ļ���
//-----------------------------------------------------------------------------
BOOL GenShortName(char *szLongName,WCHAR *wLongNameOut,char *szShortOut,char *szExtOut)
{
	WCHAR	*pChr;
	UINT	uChar,uChars,uChrOut;
	//�Ȱѳ��ļ���ת����UNICODE
	if(!OemToCharBuffW(szLongName,wLongNameOut,DIRITEM_LONGNAMELEN))
		return FALSE;
	//ȥ��ǰ��Ŀո�
	pChr=wLongNameOut;
	while(*pChr==L' ')pChr++;
	wcscpy(wLongNameOut,pChr);
	//ȥ������Ŀո�
	pChr=&wLongNameOut[wcslen(wLongNameOut)-1];
	while(*pChr==L' '||!*pChr)pChr--;
	pChr[1]=L'\0';
	if(!ValidateName(wLongNameOut))
		return FALSE;
	//������չ��
	szExtOut[0]=szExtOut[1]=szExtOut[2]=' ';//�Ȱ������չ������Ϊ3�ո�
	pChr=wcsrchr(wLongNameOut,L'.');//��ԭ���ļ����еľ��
	if(pChr++)//����ҵ����
	{//��Ϊ��չ���������ַ�������ǷǷ��ַ������纺�֣�����ʾ���ַ�_����
		uChars=pChr-wLongNameOut-1;
		*szExtOut++=(VALIDWCHR(*pChr))?toupper((char)*pChr++):'_';
		*szExtOut++=(VALIDWCHR(*pChr))?toupper((char)*pChr++):'_';
		*szExtOut++=(VALIDWCHR(*pChr))?toupper((char)*pChr++):'_';
		if((*--szExtOut)=='_')
		{
			*szExtOut=' ';
			if((*--szExtOut)=='_')
			{
				*szExtOut=' ';
				if((*--szExtOut)=='_')
					*szExtOut=' ';
			}
		}
	}
	else//���û�о����û����չ��
		uChars=wcslen(wLongNameOut);
	memset(szShortOut,' ',8);//��������ļ����ȳ�ʼ��Ϊȫ�ո�
	for(uChar=uChrOut=0;		//׼����ʼ�����ַ���
		uChar<uChars&&uChrOut<8;//ѭ��ֱ���Ѿ��õ����㹻�����ַ���
		uChar++)				//�����ӳ��ļ�����ȡ�ַ�
	{
		if(VALIDWCHR(wLongNameOut[uChar]))
			szShortOut[uChrOut++]=toupper(wLongNameOut[uChar]);//����ǺϷ��ַ���ת���ɴ�д
		else
			szShortOut[uChrOut++]='_';//�����滻��_
	}
	if(wLongNameOut[uChar])		//������ļ�������8�ֽ�
	{
		szShortOut[6]='~';		//��β�ĳ�~1
		szShortOut[7]='1';
	}
	return TRUE;
}

//-----------------------------------------------------------------------------
//GenShortNameAlias������һ�����ļ����ı���
//����ԭ���Ķ��ļ���ΪXXXXXX~1���˺���������XXXXXX~2
//-----------------------------------------------------------------------------
void GenShortNameAlias(char *szShort)
{
	UINT uIndex=8;
	DWORD dwAliasNum;
	while(uIndex--)//����������ԭ���ļ�����8���ַ�
	{
		if(szShort[uIndex]=='~')//����ҵ�~����
		{
			if(uIndex<7)//����~���ǵ�����һ���ַ�
			{
				dwAliasNum=atol(&szShort[uIndex+1])+1;//�������ʱ��~�����Ǵ�����
				if(dwAliasNum>999999)//�������+1�����µ��ļ��������ܴ���999999
				{
					for(uIndex=0;uIndex<6;uIndex++)
					{
						if(szShort[uIndex]<=' ')
							szShort[uIndex]='_';
					}
					szShort[6]='~';//���β�ĳ�~1
					szShort[7]='1';
					return;
				}
				else
				{
					char szNum[8];//����µ��ļ��������
					for(uIndex=0;uIndex<6;uIndex++)
					{
						if(szShort[uIndex]<=' ')
							szShort[uIndex]='_';
					}
					sprintf(szNum,"~%lu",dwAliasNum);
					if(dwAliasNum>=100000)			//�����6λ��
						memcpy(&szShort[1],szNum,7);//����7���ַ�
					else if(dwAliasNum>=10000)		//�����5λ��
						memcpy(&szShort[2],szNum,6);//����6���ַ�
					else if(dwAliasNum>=1000)		//�����4λ��
						memcpy(&szShort[3],szNum,5);//����5���ַ�
					else if(dwAliasNum>=100)		//�����3λ��
						memcpy(&szShort[4],szNum,4);//����4���ַ�
					else if(dwAliasNum>=10)			//�����2λ��
						memcpy(&szShort[5],szNum,3);//����3���ַ�
					else							//�������1λ��
						memcpy(&szShort[6],szNum,2);//����2���ַ�
					return;//�Ѿ������µ��ļ���������
				}
			}
			else//~�����һ���ַ�
			{
				for(uIndex=0;uIndex<6;uIndex++)
				{
					if(szShort[uIndex]<=' ')
						szShort[uIndex]='_';
				}
				szShort[6]='~';//���β�ĳ�~1
				szShort[7]='1';
				return;
			}
		}
		else//������������ַ�����~
		{
			if(!isdigit(szShort[uIndex]))//���Ҳ�������
			{
				for(uIndex=0;uIndex<6;uIndex++)
				{
					if(szShort[uIndex]<=' ')
						szShort[uIndex]='_';
				}
				szShort[6]='~';//���β�ĳ�~1
				szShort[7]='1';
				return;
			}
		}
	}
	//���е����˵���ļ���Ϊȫ����
	for(uIndex=0;uIndex<6;uIndex++)
	{
		if(szShort[uIndex]<=' ')
			szShort[uIndex]='_';
	}
	szShort[6]='~';//��β�ĳ�~1
	szShort[7]='1';
	return;
}

//-----------------------------------------------------------------------------
//FindShortNameInRoot���Ӹ�Ŀ¼���Ҷ�Ӧ�Ķ��ļ���
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindShortNameInRoot(char *szShort,char *szExt)
{
	char szName[8+3];
	UINT i;
	memcpy(szName,szShort,8);
	memcpy(szName+8,szExt,3);
	for(i=0;i<FLOPPY_MAX_ROOT;i++)			//����������Ŀ¼��
	{
		if(!IsFreeDirItem(&g_RootDirs[i]))	//�ж��Ƿ�Ϊ����Ŀ¼��
		{									//�������
			if(!memcmp(g_RootDirs[i].szFileName,szName,8))//�����ļ���һ��
				return &g_RootDirs[i];		//�������Ŀ¼��
		}
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//CollectLongNameFromRoot���ڸ�Ŀ¼����һ��У����ҵ����г��ļ�����֣����һ�����ļ���
//-----------------------------------------------------------------------------
BOOL CollectLongNameFromRoot(BYTE bCheckSum,WCHAR *wLongName)
{
	UINT	i,uIndex,uCharPos,uMaxItems=DIRITEM_LASTLONGNAME;
	WCHAR	wcOneItem[DIRITEM_CHARSPERITEM+1]={0};
	BOOL	bCollected[DIRITEM_LASTLONGNAME]={FALSE};//�ж��Ƿ��������
	BOOL	bAllTrue;
	bCollected[0]=TRUE;
#	define	pLong	((FAT_LONGNAME*)g_RootDirs)
	for(i=0;i<FLOPPY_MAX_ROOT;i++)			//����������Ŀ¼��
	{
		if(!IsFreeDirItem(&g_RootDirs[i]))	//�ж��Ƿ�Ϊ����Ŀ¼��
		{									//�������
			if(g_RootDirs[i].bAttribute==ATTR_LONGNAME)//����ǳ��ļ�����
			{
				if(bCheckSum==pLong[i].bChksum)//����У���ƥ��
				{
					uIndex=pLong[i].bOrder&0x3F;//ȡ�����
					if(pLong[i].bOrder&DIRITEM_LASTLONGNAME)//��������һ����
					{
						uMaxItems=uIndex;
						memcpy(&wcOneItem[0],pLong[i].wNamePart1,10);
						memcpy(&wcOneItem[5],pLong[i].wNamePart2,12);
						memcpy(&wcOneItem[11],pLong[i].wNamePart3,4);
						for(uCharPos=0;uCharPos<DIRITEM_CHARSPERITEM;uCharPos++)
						{
							if(wcOneItem[uCharPos]==0xFFFF)
							{
								wcOneItem[uCharPos]=0;
								break;
							}
						}
						wcscpy(&wLongName[(uIndex-1)*DIRITEM_CHARSPERITEM],wcOneItem);
					}
					else
					{
						memcpy(&wcOneItem[0],pLong[i].wNamePart1,10);
						memcpy(&wcOneItem[5],pLong[i].wNamePart2,12);
						memcpy(&wcOneItem[11],pLong[i].wNamePart3,4);
						memcpy(&wLongName[(uIndex-1)*DIRITEM_CHARSPERITEM],wcOneItem,DIRITEM_CHARSPERITEM*sizeof(WCHAR));
					}
					bCollected[uIndex]=TRUE;
					for(bAllTrue=TRUE,uCharPos=0;uCharPos<uMaxItems;uCharPos++)//����Ƿ�����
					{
						if(!bCollected[uCharPos])//û�����������
						{
							bAllTrue=FALSE;
							break;
						}
					}
					if(bAllTrue)
						return TRUE;//����������򷵻���
					
				}
			}
		}
	}
#	undef pLong
	return FALSE;//���û�м����򷵻ؼ�
}

//-----------------------------------------------------------------------------
//CollectLongNameFromDir����Ŀ¼�д�һ��У����ҵ����г��ļ�����֣����һ�����ļ���
//-----------------------------------------------------------------------------
BOOL CollectLongNameFromDir(WORD wCluster,BYTE bCheckSum,WCHAR *wLongName)
{
	UINT	i,uIndex,uCharPos,uMaxItems=DIRITEM_LASTLONGNAME,uDirLen;
	WCHAR	wcOneItem[DIRITEM_CHARSPERITEM+1]={0};
	BOOL	bCollected[DIRITEM_LASTLONGNAME]={FALSE};//�ж��Ƿ��������
	BOOL	bAllTrue;
	FAT_LONGNAME *pLong;
	if(!wCluster)
		return FALSE;
	pLong=(FAT_LONGNAME*)malloc(sizeof(FAT_LONGNAME)*(uDirLen=GetClusterChainLength(wCluster)*0x10));
	if(!pLong)
		return FALSE;
	uIndex=0;
	do										//�Ȱ�����Ŀ¼�ؼ���
	{
		memcpy(&pLong[uIndex],GetClusterPtr(wCluster),FLOPPY_BYTES_PER_SEC);
		uIndex+=FLOPPY_BYTES_PER_SEC;
		wCluster=ReadFAT12Item(wCluster);	//����һ��Ŀ¼��
	}
	while(FLOPPY_VALID_CLUS(wCluster));
	bCollected[0]=TRUE;
	for(i=0;i<uDirLen;i++)					//����������Ŀ¼��
	{
		if(!IsFreeDirItem((FAT_DIRITEM*)&pLong[i]))//�ж��Ƿ�Ϊ����Ŀ¼��
		{									//�������
			if(pLong[i].bAttribute==ATTR_LONGNAME)//����ǳ��ļ�����
			{
				if(bCheckSum==pLong[i].bChksum)//����У���ƥ��
				{
					uIndex=pLong[i].bOrder&0x3F;//ȡ�����
					if(pLong[i].bOrder&DIRITEM_LASTLONGNAME)//��������һ����
					{
						uMaxItems=uIndex;
						memcpy(&wcOneItem[0],pLong[i].wNamePart1,10);
						memcpy(&wcOneItem[5],pLong[i].wNamePart2,12);
						memcpy(&wcOneItem[11],pLong[i].wNamePart3,4);
						for(uCharPos=0;uCharPos<DIRITEM_CHARSPERITEM;uCharPos++)
						{
							if(wcOneItem[uCharPos]==0xFFFF)
							{
								wcOneItem[uCharPos]=0;
								break;
							}
						}
						wcscpy(&wLongName[(uIndex-1)*DIRITEM_CHARSPERITEM],wcOneItem);
					}
					else
					{
						memcpy(&wcOneItem[0],pLong[i].wNamePart1,10);
						memcpy(&wcOneItem[5],pLong[i].wNamePart2,12);
						memcpy(&wcOneItem[11],pLong[i].wNamePart3,4);
						memcpy(&wLongName[(uIndex-1)*DIRITEM_CHARSPERITEM],wcOneItem,DIRITEM_CHARSPERITEM*sizeof(WCHAR));
					}
					bCollected[uIndex]=TRUE;
					for(bAllTrue=TRUE,uCharPos=0;uCharPos<uMaxItems;uCharPos++)//����Ƿ�����
					{
						if(!bCollected[uCharPos])//û�����������
						{
							bAllTrue=FALSE;
							break;
						}
					}
					if(bAllTrue)
					{
						free(pLong);
						return TRUE;//����������򷵻���
					}
					
				}
			}
		}
	}
	free(pLong);
	return FALSE;//���û�м����򷵻ؼ�
}

//-----------------------------------------------------------------------------
//FindCheckSumOwnerInRoot���Ӹ�Ŀ¼���ҵ����У��͵�ԭ�ļ���
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindCheckSumOwnerInRoot(BYTE bCheckSum)
{
	UINT i;
	for(i=0;i<FLOPPY_MAX_ROOT;i++)
	{
		if(ShortNameCheckSum(g_RootDirs[i].szFileName)==bCheckSum)
			return &g_RootDirs[i];
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//FindCheckSumOwnerInDir����Ŀ¼�ҵ����У��͵�ԭ�ļ���
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindCheckSumOwnerInDir(WORD wCluster,BYTE bCheckSum)
{
	UINT i;
	FAT_DIRITEM* pDir;
	if(!wCluster)
		return NULL;
	do
	{
		pDir=(FAT_DIRITEM*)GetClusterPtr(wCluster);
		for(i=0;i<16;i++)
		{
			if(ShortNameCheckSum(pDir[i].szFileName)==bCheckSum)
				return &pDir[i];
		}
		wCluster=ReadFAT12Item(wCluster);
	}while(FLOPPY_VALID_CLUS(wCluster));
	return NULL;
}

//-----------------------------------------------------------------------------
//FindLongNameInRoot���Ӹ�Ŀ¼���Ҷ�Ӧ�ĳ��ļ���
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindLongNameInRoot(WCHAR *wLongName)
{
	WCHAR	wLongNameBuf[DIRITEM_LONGNAMELEN];
	BYTE	bCheckSum;
	UINT	i;
	for(i=0;i<FLOPPY_MAX_ROOT;i++)			//����������Ŀ¼��
	{
		if(!IsFreeDirItem(&g_RootDirs[i]))	//�ж��Ƿ�Ϊ����Ŀ¼��
		{									//�������
			if(g_RootDirs[i].bAttribute==ATTR_LONGNAME)//����ǳ��ļ�����
			{
				bCheckSum=((FAT_LONGNAME*)g_RootDirs)[i].bChksum;
				if(CollectLongNameFromRoot(bCheckSum,wLongNameBuf))
				{
					if(!wcscmp(wLongNameBuf,wLongName))
						return FindCheckSumOwnerInRoot(bCheckSum);
				}
			}
		}
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//FindShortNameInDir�������Ŀ¼����ļ����Ƿ��ظ�
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindShortNameInDir(WORD wDirClus,char *szShort,char *szExt)
{
	char szName[8+3];
	WORD i;
	FAT_DIRITEM* pDir;
	memcpy(szName,szShort,8);
	memcpy(szName+8,szExt,3);
	while(FLOPPY_VALID_CLUS(wDirClus))
	{
		pDir=(FAT_DIRITEM*)GetClusterPtr(wDirClus);	//ȡ��Ŀ¼��ָ��
		if(!pDir)
			return NULL;
		for(i=0;i<16;i++)							//��Ŀ¼���ҿ���Ŀ¼��
		{
			if(!IsFreeDirItem(&pDir[i]))			//�ж��Ƿ�Ϊ����Ŀ¼��
			{										//�������
				if(!memcmp(pDir[i].szFileName,szName,8))//�����ļ���һ��
					return &pDir[i];				//�������Ŀ¼��
			}
		}
		wDirClus=ReadFAT12Item(wDirClus);			//����Ӵ����ҵ���һ��Ŀ¼���λ�ü�����
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//FindShortNameInDir�������Ŀ¼����ļ����Ƿ��ظ�
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindLongNameInDir(WORD wDirClus,WCHAR *wLongName)
{
	WORD i;
	FAT_DIRITEM* pDir;
	FAT_LONGNAME* pLong;
	WCHAR wLongNameBuf[DIRITEM_LONGNAMELEN];
	while(FLOPPY_VALID_CLUS(wDirClus))
	{
		pDir=(FAT_DIRITEM*)GetClusterPtr(wDirClus);	//ȡ��Ŀ¼��ָ��
		if(!pDir)
			return NULL;
		for(i=0;i<16;i++)							//��Ŀ¼���ҿ���Ŀ¼��
		{
			if(!IsFreeDirItem((FAT_DIRITEM*)(pLong=(FAT_LONGNAME*)&pDir[i])))//�ж��Ƿ�Ϊ����Ŀ¼��
			{										//�������
				if(CollectLongNameFromDir(wDirClus,pLong->bChksum,wLongNameBuf))
				{
					if(!wcscmp(wLongNameBuf,wLongName))
						return FindCheckSumOwnerInDir(wDirClus,pLong->bChksum);
				}
			}
		}
		wDirClus=ReadFAT12Item(wDirClus);			//����Ӵ����ҵ���һ��Ŀ¼���λ�ü�����
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//IsFreeDirItem������ڸ�Ŀ¼����ļ����Ƿ��ظ�
//-----------------------------------------------------------------------------
BOOL IsFreeDirItem(FAT_DIRITEM* pDir)
{
	if(	(BYTE)(pDir->szFileName[0])==DIRITEM_FREE||
		(BYTE)(pDir->szFileName[0])==DIRITEM_DELETED||
		(BYTE)(pDir->szFileName[0])==DIRITEM_DELETED_JPN)
		return TRUE;
	else
		return FALSE;
}

//-----------------------------------------------------------------------------
//RootCreateItem���Ӹ�Ŀ¼������Ŀ¼��
//-----------------------------------------------------------------------------
FAT_DIRITEM* RootCreateItem(char *szFile,BYTE bAttr)
{
	return ParseItem(szFile,bAttr,FindFreeRootItem,FindLongNameInRoot,FindShortNameInRoot);
}

static WORD __wDirClus;
static FAT_DIRITEM* __DirGetItem(void);
static FAT_DIRITEM* __FindLongName(WCHAR *wLongName);
static FAT_DIRITEM* __FindShortName(char *szShort,char *szExt);
//-----------------------------------------------------------------------------
//DirCreateItem����Ŀ¼����Ŀ¼��
//-----------------------------------------------------------------------------
FAT_DIRITEM* DirCreateItem(WORD wDirClus,char *szFile,BYTE bAttr)
{
	__wDirClus=wDirClus;
	return ParseItem(szFile,bAttr,__DirGetItem,__FindLongName,__FindShortName);
}
FAT_DIRITEM* __DirGetItem(void)
{
	FAT_DIRITEM* pDirItem;
	if(pDirItem=FindFreeDirItem(__wDirClus))
		return pDirItem;
	else
	{
		WORD wFreeCluster;
		wFreeCluster=FindFreeClus();
		if(!wFreeCluster)
			return NULL;
		WriteFAT12Item(__wDirClus,wFreeCluster);
		WriteFAT12Item(wFreeCluster,FLOPPY_CLUS_END);
		pDirItem=(FAT_DIRITEM*)GetClusterPtr(wFreeCluster);
		memset(pDirItem,0,FLOPPY_BYTES_PER_SEC);
		return pDirItem;
	}
}
FAT_DIRITEM* __FindLongName(WCHAR *wLongName)
{
	return FindLongNameInDir(__wDirClus,wLongName);
}
FAT_DIRITEM* __FindShortName(char *szShort,char *szExt)
{
	return FindShortNameInDir(__wDirClus,szShort,szExt);
}


//-----------------------------------------------------------------------------
//ParseItem�����ļ����������ļ�������ļ�����
//-----------------------------------------------------------------------------
FAT_DIRITEM* ParseItem(char *szFile,BYTE bAttr,
					   FAT_DIRITEM*(__cdecl*NewItem)(void),
					   FAT_DIRITEM*(__cdecl*FindLongName)(WCHAR *wLongName),
					   FAT_DIRITEM*(__cdecl*FindShortName)(char *szShort,char *szExt))
{
	FAT_DIRITEM		*pIdle;
	FAT_LONGNAME	*pIdleLong;
	div_t			div_result;
	WCHAR			wLongName[DIRITEM_LONGNAMELEN];
	char			cShortName[8+3];
	UINT			uLongNameLen,i,uCharPos;
	struct	_timeb	pTime;
	struct	tm*		pTm;

	//�ȴӸ�Ŀ¼�ҵ�����Ŀ¼��
	pIdle=NewItem();
	if(!pIdle)
		return NULL;

	//���ɶ��ļ���
	if(!GenShortName(szFile,wLongName,cShortName,&cShortName[8]))
		return NULL;

	//����ļ�������
	uLongNameLen=wcslen(wLongName);
	if(uLongNameLen>DIRITEM_LONGNAMELEN)
		return NULL;

	//������ļ����ظ���
	if(FindLongName(wLongName))
		return NULL;

	//������ļ�����ͻ��
	for(i=0;
		i<DIRITEM_MAXSHORTALIAS &&
		FindShortName(cShortName,&cShortName[8]);
		i++)
		GenShortNameAlias(cShortName);//�����ɱ���

	//����Ҳ������ʵı����򷵻�NULL
	if(FindShortName(cShortName,&cShortName[8]))
		return NULL;

	//���㳤�ļ���ռ�õ�Ŀ¼����
	div_result=div(uLongNameLen,DIRITEM_CHARSPERITEM);
	if(div_result.rem)
		div_result.quot++;

	//ȡ��ʱ��
	_ftime(&pTime);
	pTm=localtime(&(pTime.time));

	//��д���ļ�����
	memcpy(pIdle->szFileName,cShortName,11);
	pIdle->bAttribute=bAttr;
	pIdle->bReserved=0;
	pIdle->bCreateTimeMS=(pTime.millitm/10)+(pTm->tm_sec&1)*100;
	pIdle->wCreateTime=MAKETIME(pTm->tm_hour,pTm->tm_min,pTm->tm_sec);
	pIdle->wCreateDate=
	pIdle->wLastAccDate=MAKEDATE(pTm->tm_year,pTm->tm_mon,pTm->tm_mday);
	pIdle->wFirstClusHI=0;
	pIdle->wWriteTime=pIdle->wCreateTime;
	pIdle->wWriteDate=pIdle->wCreateDate;
	pIdle->wFirstClusLO=0;
	pIdle->dwFileSize=0;

	//Ȼ��׼���������ļ�����
	if(!(pIdleLong=(FAT_LONGNAME*)NewItem()))
		return pIdle;

	//��д���еĳ��ļ�����
	for(uCharPos=0,i=1;i<(UINT)(div_result.quot);i++)
	{
		pIdleLong->bOrder=i;
		memcpy(pIdleLong->wNamePart1,&wLongName[uCharPos],10);uCharPos+=5;
		pIdleLong->bAttribute=ATTR_LONGNAME;
		pIdleLong->bType=0;
		pIdleLong->bChksum=ShortNameCheckSum(cShortName);
		memcpy(pIdleLong->wNamePart2,&wLongName[uCharPos],12);uCharPos+=6;
		pIdleLong->wFirstClusLO=0;
		memcpy(pIdleLong->wNamePart3,&wLongName[uCharPos],4);uCharPos+=2;

		if(!(pIdleLong=(FAT_LONGNAME*)NewItem()))//�������˳��ļ�����
		{
			pIdleLong->bOrder|=DIRITEM_LASTLONGNAME;//�ͱ��Ϊ�����ĳ��ļ����
			return pIdle;
		}
	}

	memset(&wLongName[uLongNameLen],0xFF,(DIRITEM_LONGNAMELEN-uLongNameLen)<<1);//���ļ���β��0xFFFF���

	pIdleLong->bOrder=i|DIRITEM_LASTLONGNAME;//���һ�����ļ�����
	memcpy(pIdleLong->wNamePart1,&wLongName[uCharPos],10);uCharPos+=5;
	pIdleLong->bAttribute=ATTR_LONGNAME;
	pIdleLong->bType=0;
	pIdleLong->bChksum=ShortNameCheckSum(cShortName);
	memcpy(pIdleLong->wNamePart2,&wLongName[uCharPos],12);uCharPos+=6;
	pIdleLong->wFirstClusLO=0;
	memcpy(pIdleLong->wNamePart3,&wLongName[uCharPos],4);uCharPos+=2;

	return pIdle;
}

//-----------------------------------------------------------------------------
//MakeDir������Ŀ¼������Ŀ¼ռ�õĴغ�
//-----------------------------------------------------------------------------
WORD MakeDir(WORD wParentClus,char *szName)
{
	WORD wNewClus;
	FAT_DIRITEM *pItem,*pItemList;
	if(wParentClus)
		pItem=DirCreateItem(wParentClus,szName,ATTR_SUBDIR);
	else
		pItem=RootCreateItem(szName,ATTR_SUBDIR);
	if(pItem)
	{
		wNewClus=FindFreeClus();
		if(wNewClus)
		{
			struct	_timeb	pTime;
			struct	tm*		pTm;
			//ȡ��ʱ��
			_ftime(&pTime);
			pTm=localtime(&(pTime.time));
			pItemList=(FAT_DIRITEM*)GetClusterPtr(wNewClus);
			memset(pItemList,0,FLOPPY_BYTES_PER_SEC);

			pItem->wFirstClusLO=wNewClus;

			memcpy(pItemList,DIRITEM_SELF,11);
			pItemList->bAttribute=ATTR_SUBDIR;
			pItemList->bReserved=0;
			pItemList->bCreateTimeMS=(pTime.millitm/10)+(pTm->tm_sec&1)*100;
			pItemList->wCreateTime=MAKETIME(pTm->tm_hour,pTm->tm_min,pTm->tm_sec);
			pItemList->wCreateDate=
			pItemList->wLastAccDate=MAKEDATE(pTm->tm_year,pTm->tm_mon,pTm->tm_mday);
			pItemList->wFirstClusHI=0;
			pItemList->wWriteTime=pItemList->wCreateTime;
			pItemList->wWriteDate=pItemList->wCreateDate;
			pItemList->wFirstClusLO=wNewClus;
			pItemList->dwFileSize=0;
			memcpy(++pItemList,DIRITEM_PARENT,11);
			pItemList->bAttribute=ATTR_SUBDIR;
			pItemList->bReserved=0;
			pItemList->bCreateTimeMS=(pTime.millitm/10)+(pTm->tm_sec&1)*100;
			pItemList->wCreateTime=MAKETIME(pTm->tm_hour,pTm->tm_min,pTm->tm_sec);
			pItemList->wCreateDate=
			pItemList->wLastAccDate=MAKEDATE(pTm->tm_year,pTm->tm_mon,pTm->tm_mday);
			pItemList->wFirstClusHI=0;
			pItemList->wWriteTime=pItemList->wCreateTime;
			pItemList->wWriteDate=pItemList->wCreateDate;
			pItemList->wFirstClusLO=wParentClus;
			pItemList->dwFileSize=0;
			return wNewClus;
		}
		else
			return 0;
	}
	else
		return 0;
}
