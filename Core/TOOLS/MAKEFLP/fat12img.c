#include"fat12img.h"
#include<ctype.h>
#include<stdio.h>
#include<memory.h>
#include<string.h>
#include<time.h>
#include<sys/timeb.h>
#include<windows.h>
#include<stdarg.h>

//#############################################################################
//                                 ��������
//#############################################################################

const
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

FILE *pErrStream=NULL;//����������

//#############################################################################
//                                 ��������
//#############################################################################

//-----------------------------------------------------------------------------
//ErrorOut��������������еĴ������pErrStream��ΪNULL
//-----------------------------------------------------------------------------
static
void ErrorOut(char* szFormat, ...)
{
	va_list	ap;
	va_start(ap,szFormat);
	if(pErrStream)
		vfprintf(pErrStream,szFormat,ap);
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
	while(IsValidCluster(wDirClus))
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
	if(IsValidCluster(wCluster))
		return (void*)&g_bDataArea[(wCluster-FLOPPY_CLUS_MIN)*FLOPPY_BYTES_PER_CLUS];
	else
	{
		ErrorOut("Invalid cluster number.\n");
		return NULL;
	}
}

//-----------------------------------------------------------------------------
//GetClusterChainLength��ȡ�ô�������
//-----------------------------------------------------------------------------
WORD GetClusterChainLength(WORD wCluster)
{
	WORD wLen=0;//�������ȴ�0��ʼͳ��
	while(IsValidCluster(wCluster))
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
	{
		ErrorOut("File name %S is illegal.\n",wLongNameOut);
		return FALSE;
	}
	//������չ��
	szExtOut[0]=szExtOut[1]=szExtOut[2]=' ';//�Ȱ������չ������Ϊ3�ո�
	pChr=wcsrchr(wLongNameOut,L'.');//��ԭ���ļ����еľ��
	if(pChr++)//����ҵ����
	{//��Ϊ��չ���������ַ�������ǷǷ��ַ������纺�֣�����ʾ���ַ�_����
		uChars=pChr-wLongNameOut-1;
		*szExtOut++=(VALIDWCHR(*pChr))?towupper(*pChr++):'_';
		*szExtOut++=(VALIDWCHR(*pChr))?towupper(*pChr++):'_';
		*szExtOut++=(VALIDWCHR(*pChr))?towupper(*pChr++):'_';
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
BOOL CollectLongNameFromRoot(FAT_DIRITEM *pShortName,WCHAR *wLongName)
{
	BOOL			bCheckSum;
	BYTE			bSN=1;//���
	FAT_LONGNAME	*pLongName;
	WCHAR			wLongItem[DIRITEM_CHARSPERITEM];
	WCHAR			wChr;
	UINT			uChars;
	bCheckSum=ShortNameCheckSum(pShortName->szFileName);				//����У���
	pLongName=(FAT_LONGNAME*)pShortName;								//�ӵ�ǰĿ¼����ǰ�ҳ��ļ���
	while(--pLongName>=(FAT_LONGNAME*)g_RootDirs)
	{
		if(pLongName->bAttribute!=ATTR_LONGNAME)						//���Ŀ¼��û�г��ļ������ؼ�
			return FALSE;
		if(pLongName->bChksum!=bCheckSum)								//���ǰ���г��ļ�������У��Ͳ��Է��ؼ�
			return FALSE;
		if((pLongName->bOrder & DIRITEM_LNORDERMASK)!=bSN)				//���ǰ���г��ļ�������У����ǶԵĵ�����Ų��Է��ؼ�
		{
			ErrorOut("Root entry is bad.\n");
			return FALSE;
		}
		memcpy(&wLongItem[0],pLongName->wNamePart1,5*sizeof(WCHAR));	//������һ�����ļ�������
		memcpy(&wLongItem[5],pLongName->wNamePart2,6*sizeof(WCHAR));	//�����ڶ������ļ�������
		memcpy(&wLongItem[11],pLongName->wNamePart3,2*sizeof(WCHAR));	//�������������ļ�������
		if(pLongName->bOrder&DIRITEM_LASTLONGNAME)						//��������ĳ��ļ�����
		{
			for(uChars=0;uChars<DIRITEM_CHARSPERITEM;uChars++)			//���ֶ��������ļ���
			{
				wChr=wLongItem[uChars];	//ȡ�ַ�
				if(wChr&&wChr!=0xFFFF)	//������ǽ�β
					*wLongName++=wChr;	//�ͼӵ����ļ�����
				else
					break;				//�������ѭ��
			}
			*wLongName=0;				//����ĳ��ļ����Ӹ���β��ʶ
			return TRUE;
		}
		else							//���ﲻ�����ĳ��ļ�����
		{
			memcpy(wLongName,wLongItem,DIRITEM_CHARSPERITEM*sizeof(WCHAR));	//�������еĳ��ļ����ַ�
			wLongName+=DIRITEM_CHARSPERITEM;								//�ƶ�ָ��
		}
		bSN++;
	}
	return FALSE;						//û�м��볤�ļ����򷵻ؼ�
}

//-----------------------------------------------------------------------------
//GetPrevCluster��ȡ��ǰһ���غ�
//-----------------------------------------------------------------------------
WORD GetPrevCluster(WORD wCurrentCluster)
{
	WORD i;
	for(i=FLOPPY_CLUS_MIN;i<=FLOPPY_CLUS_MAX;i++)
	{
		if(ReadFAT12Item(i)==wCurrentCluster)
			return i;
	}
	return 0;
}

//-----------------------------------------------------------------------------
//CollectLongNameFromDir����Ŀ¼�д�һ��У����ҵ����г��ļ�����֣����һ�����ļ���
//-----------------------------------------------------------------------------
BOOL CollectLongNameFromDir(WORD wCurrentCluster,FAT_DIRITEM *pShortName,WCHAR *wLongName)
{
	BOOL			bCheckSum;
	BYTE			bSN=1;//���
	WORD			wPrevCluster;
	FAT_LONGNAME	*pLongName;
	FAT_LONGNAME	*pFirstItem;//��ǰ�صĵ�һ��Ŀ¼��
	WCHAR			wLongItem[DIRITEM_CHARSPERITEM];
	WCHAR			wChr;
	UINT			uChars;
	bCheckSum=ShortNameCheckSum(pShortName->szFileName);				//����У���
	pLongName=(FAT_LONGNAME*)pShortName;								//�ӵ�ǰĿ¼����ǰ�ҳ��ļ���
	pFirstItem=(FAT_LONGNAME*)GetClusterPtr(wCurrentCluster);			//�ҵ���ǰ�ص�ָ��
	for(;;)
	{
		while(--pLongName>=pFirstItem)
		{
			if(pLongName->bAttribute!=ATTR_LONGNAME)						//���Ŀ¼��û�г��ļ������ؼ�
				return FALSE;
			if(pLongName->bChksum!=bCheckSum)								//���ǰ���г��ļ�������У��Ͳ��Է��ؼ�
				return FALSE;
			if((pLongName->bOrder & DIRITEM_LNORDERMASK)!=bSN)				//���ǰ���г��ļ�������У����ǶԵĵ�����Ų��Է��ؼ�
			{
				ErrorOut("Root entry is bad.\n");
				return FALSE;
			}
			memcpy(&wLongItem[0],pLongName->wNamePart1,5*sizeof(WCHAR));	//������һ�����ļ�������
			memcpy(&wLongItem[5],pLongName->wNamePart2,6*sizeof(WCHAR));	//�����ڶ������ļ�������
			memcpy(&wLongItem[11],pLongName->wNamePart3,2*sizeof(WCHAR));	//�������������ļ�������
			if(pLongName->bOrder&DIRITEM_LASTLONGNAME)						//��������ĳ��ļ�����
			{
				for(uChars=0;uChars<DIRITEM_CHARSPERITEM;uChars++)			//���ֶ��������ļ���
				{
					wChr=wLongItem[uChars];	//ȡ�ַ�
					if(wChr&&wChr!=0xFFFF)	//������ǽ�β
						*wLongName++=wChr;	//�ͼӵ����ļ�����
					else
						break;				//�������ѭ��
				}
				*wLongName=0;				//����ĳ��ļ����Ӹ���β��ʶ
				return TRUE;
			}
			else							//���ﲻ�����ĳ��ļ�����
			{
				memcpy(wLongName,wLongItem,DIRITEM_CHARSPERITEM*sizeof(WCHAR));	//�������еĳ��ļ����ַ�
				wLongName+=DIRITEM_CHARSPERITEM;								//�ƶ�ָ��
			}
			bSN++;
		}
		wPrevCluster=GetPrevCluster(wCurrentCluster);
		if(!IsValidCluster(wPrevCluster))
			return FALSE;					//���û�м��볤�ļ��������Ѿ��ǵ�һ�����򷵻ؼ�
		wCurrentCluster=wPrevCluster;
		pFirstItem=(FAT_LONGNAME*)GetClusterPtr(wCurrentCluster);					//�ҵ�ǰ��ص�ָ��
		pLongName=pFirstItem+FLOPPY_BYTES_PER_CLUS/sizeof(FAT_LONGNAME);
	}
}

//-----------------------------------------------------------------------------
//FindShortNameInRootByCheckSum���Ӹ�Ŀ¼���ҵ����У��͵�ԭ�ļ���
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindShortNameInRootByCheckSum(BYTE bCheckSum)
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
//FindShortNameInDirByCheckSum����Ŀ¼�ҵ����У��͵�ԭ�ļ���
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindShortNameInDirByCheckSum(WORD wCluster,BYTE bCheckSum)
{
	UINT i;
	FAT_DIRITEM* pDir;
	if(!IsValidCluster(wCluster))
	{
		ErrorOut("You should to specify a valid directory cluster.\n");
		return NULL;
	}
	do
	{
		pDir=(FAT_DIRITEM*)GetClusterPtr(wCluster);
		for(i=0;i<16;i++)
		{
			if(ShortNameCheckSum(pDir[i].szFileName)==bCheckSum)
				return &pDir[i];
		}
		wCluster=ReadFAT12Item(wCluster);
	}while(IsValidCluster(wCluster));
	return NULL;
}

//-----------------------------------------------------------------------------
//FindLongNameInRoot���Ӹ�Ŀ¼���Ҷ�Ӧ�ĳ��ļ���
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindLongNameInRoot(WCHAR *wLongName)
{
	WCHAR	wLongNameBuf[DIRITEM_LONGNAMELEN];
	UINT	i;
	for(i=0;i<FLOPPY_MAX_ROOT;i++)			//����������Ŀ¼��
	{
		if(!IsFreeDirItem(&g_RootDirs[i]))	//�ж��Ƿ�Ϊ����Ŀ¼��
		{									//�������
			if(g_RootDirs[i].bAttribute!=ATTR_LONGNAME)//������ǳ��ļ�����
			{
				if(CollectLongNameFromRoot(&g_RootDirs[i],wLongNameBuf))//�������ĳ��ļ���
				{
					if(!wcscmp(wLongNameBuf,wLongName))
						return FindShortNameInRootByCheckSum(ShortNameCheckSum(g_RootDirs[i].szFileName));
				}
			}
		}
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//FindShortNameInDir����Ŀ¼��ͨ�����ļ�������Ŀ¼��
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindShortNameInDir(WORD wDirClus,char *szShort,char *szExt)
{
	char szName[8+3];
	WORD i;
	FAT_DIRITEM* pDir;
	memcpy(szName,szShort,8);
	memcpy(szName+8,szExt,3);
	while(IsValidCluster(wDirClus))
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
//FindLongNameInDir���ڸ�Ŀ¼��ͨ�����ļ�������Ŀ¼��
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindLongNameInDir(WORD wDirClus,WCHAR *wLongName)
{
	WORD i;
	FAT_DIRITEM* pDir;
	WCHAR wLongNameBuf[DIRITEM_LONGNAMELEN];
	while(IsValidCluster(wDirClus))
	{
		pDir=(FAT_DIRITEM*)GetClusterPtr(wDirClus);	//ȡ��Ŀ¼��ָ��
		if(!pDir)
			return NULL;
		for(i=0;i<16;i++)							//��Ŀ¼���ҿ���Ŀ¼��
		{
			if(!IsFreeDirItem((FAT_DIRITEM*)(&pDir[i])))//�ж��Ƿ�Ϊ����Ŀ¼��
			{										//�������
				if(pDir[i].bAttribute!=ATTR_LONGNAME)//������ǳ��ļ���Ŀ¼��
				{
					if(CollectLongNameFromDir(wDirClus,&pDir[i],wLongNameBuf))//���볤�ļ���
					{
						if(!wcscmp(wLongNameBuf,wLongName))//����ļ�����ƥ���
							return &pDir[i];		//�򷵻��ҵ���Ŀ¼��
					}
				}
			}
		}
		wDirClus=ReadFAT12Item(wDirClus);			//����Ӵ����ҵ���һ��Ŀ¼���λ�ü�����
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//IsFreeDirItem������Ƿ�Ϊ����Ŀ¼��
//-----------------------------------------------------------------------------
BOOL IsFreeDirItem(FAT_DIRITEM* pDir)
{
	if(	(BYTE)(pDir->szFileName[0])==DIRITEM_FREE||			//�հ�
		(BYTE)(pDir->szFileName[0])==DIRITEM_DELETED)		//��ɾ��
		//(BYTE)(pDir->szFileName[0])==DIRITEM_DELETED_JPN)	//�ձ�����ɾ��
		return TRUE;
	else
		return FALSE;
}

//-----------------------------------------------------------------------------
//IsShortName���������ļ����Ƿ�Ϊ���ļ���
//-----------------------------------------------------------------------------
BOOL IsShortName(WCHAR *wName)
{
	UINT i;
	if(wcslen(wName)>8+3)
		return FALSE;
	for(i=0;i<11;i++)
	{
		if(iswlower(wName[i]))
			return FALSE;
		if(!VALIDWCHR(wName[i]))
			return FALSE;
	}
	return TRUE;
}

//-----------------------------------------------------------------------------
//CopyLongNameToItem���������ļ�����һ���ֵ�һ�����ļ���Ŀ¼��
//-----------------------------------------------------------------------------
void CopyLongNameToItem(FAT_LONGNAME *pItem,WCHAR *wLongName)
{
	UINT i,j=0;
	memset(pItem->wNamePart1,0xFF,5*sizeof(WCHAR));	//�Ȱѳ��ļ�����������ļ���������0xFF���
	memset(pItem->wNamePart2,0xFF,6*sizeof(WCHAR));
	memset(pItem->wNamePart3,0xFF,2*sizeof(WCHAR));
	//������һ������
	for(i=0;i<5;i++)
	{
		if(wLongName[j])
			pItem->wNamePart1[i]=wLongName[j++];
		else
		{
			pItem->wNamePart1[i]=0;
			return;
		}
	}
	//�����ڶ�������
	for(i=0;i<6;i++)
	{
		if(wLongName[j])
			pItem->wNamePart2[i]=wLongName[j++];
		else
		{
			pItem->wNamePart2[i]=0;
			return;
		}
	}
	//��������������
	for(i=0;i<2;i++)
	{
		if(wLongName[j])
			pItem->wNamePart3[i]=wLongName[j++];
		else
		{
			pItem->wNamePart3[i]=0;
			return;
		}
	}
}

//-----------------------------------------------------------------------------
//RootCreateItem���Ӹ�Ŀ¼������Ŀ¼��
//-----------------------------------------------------------------------------
FAT_DIRITEM* RootCreateItem(char *szFile,BYTE bAttr)
{
	WCHAR			wLongName[DIRITEM_LONGNAMELEN];
	char			szShortName[8+3];
	UINT			uLongNameLen,uItemsNeeded;
	div_t			dItemsNeeded;
	UINT			i,j,uCharPos;
	BOOL			bFindEnoughFreeItems;
	FAT_DIRITEM		*pShort;
	FAT_LONGNAME	*pLong;
	struct _timeb	Time;
	BOOL			bCheckSum;

	if(!GenShortName(szFile,wLongName,szShortName,&szShortName[8]))	//�����ɶ��ļ���
		return NULL;

	bCheckSum=ShortNameCheckSum(szShortName);						//���ݶ��ļ�������У���

	uLongNameLen=wcslen(wLongName);									//ȡ�ó��ļ�������
	dItemsNeeded=div(uLongNameLen,DIRITEM_CHARSPERITEM);			//���㳤�ļ���ռ������
	if(dItemsNeeded.rem)
		dItemsNeeded.quot++;
	uItemsNeeded=dItemsNeeded.quot+1;								//ȡ�ó��ļ����Ͷ��ļ����ܹ�ռ�õ���������һ������ϵ��Ƕ��ļ���ռ�õ���

	for(i=0;i<FLOPPY_MAX_ROOT-uItemsNeeded;i++)						//�Ӹ�Ŀ¼��Ѱ�������Ŀ�����
	{
		if(IsFreeDirItem(&g_RootDirs[i]))							//�ҵ�һ��������
		{
			bFindEnoughFreeItems=TRUE;
			for(j=1;j<uItemsNeeded;j++)								//�ٿ�����û���㹻�����������Ŀ�����
			{
				if(!IsFreeDirItem(&g_RootDirs[i+j]))				//���û�������Ѱ���µĿ�����
				{
					bFindEnoughFreeItems=FALSE;
					i+=j;											//˳��������Щ���������Ŀ�����
					break;
				}
			}
			if(bFindEnoughFreeItems)								//����ҵ��㹻������Ŀ¼����׼������Ŀ¼��
			{
				_ftime(&Time);

				j=uItemsNeeded-1;
				pShort=&g_RootDirs[i+j];							//����д���ļ�����
				memcpy(pShort->szFileName,szShortName,8+3);
				pShort->bAttribute=bAttr;
				pShort->bReserved=0;
				SetCreateTime(pShort,&Time);
				pShort->wFirstClusHI=0;
				pShort->wFirstClusLO=0;
				pShort->dwFileSize=0;

				pLong=(FAT_LONGNAME*)pShort;						//Ȼ��׼����д���ļ�����
				uCharPos=0;
				i=1;
				while(j--)
				{
					pLong--;
					pLong->bOrder=i++;
					pLong->bAttribute=ATTR_LONGNAME;
					pLong->bType=0;
					pLong->bChksum=bCheckSum;
					pLong->wFirstClusLO=0;
					CopyLongNameToItem(pLong,&wLongName[uCharPos]);
					uCharPos+=DIRITEM_CHARSPERITEM;
				}
				pLong->bOrder|=DIRITEM_LASTLONGNAME;				//���һ�����ļ�����ı�ʶ
				return pShort;
			}
		}
	}
	return NULL;													//����������Ҳ����㹻������Ŀ¼���򷵻�NULL
}

//-----------------------------------------------------------------------------
//DirGetItem����Ŀ¼�и�������ȡ��Ŀ¼��
//-----------------------------------------------------------------------------
FAT_DIRITEM* DirGetItem(WORD wDirClus,UINT uIndex)
{
	UINT i;
	div_t dClusters;
	if(!wDirClus)
		return &g_RootDirs[uIndex];
	else if(wDirClus>FLOPPY_CLUS_MAX)
		return NULL;
	dClusters=div(uIndex,DIRITEMS_PER_CLUS);
	for(i=0;i<(UINT)(dClusters.quot);i++)
	{
		wDirClus=ReadFAT12Item(wDirClus);
		if(!IsValidCluster(wDirClus))
			return NULL;
	}
	return &((FAT_DIRITEM*)GetClusterPtr(wDirClus))[dClusters.rem];
}

//-----------------------------------------------------------------------------
//GetClusterChainLastCluster��ȡ�ô��������һ����
//-----------------------------------------------------------------------------
WORD GetClusterChainLastCluster(WORD wCluster)
{
	WORD wNextCluster;
	if(!IsValidCluster(wCluster))
		return 0;
	while((wNextCluster=ReadFAT12Item(wCluster))<=FLOPPY_CLUS_MAX)
		wCluster=wNextCluster;
	return wCluster;
}

//-----------------------------------------------------------------------------
//AppendNewClusterToChain��������β׷��һ���µĴ�
//-----------------------------------------------------------------------------
WORD AppendNewClusterToChain(WORD wCluster)
{
	return AllocateNewCluster(GetClusterChainLastCluster(wCluster));
}

//-----------------------------------------------------------------------------
//DirCreateItem����Ŀ¼����Ŀ¼��
//-----------------------------------------------------------------------------
FAT_DIRITEM* DirCreateItem(WORD wDirClus,char *szFile,BYTE bAttr)
{
	WCHAR			wLongName[DIRITEM_LONGNAMELEN];
	char			szShortName[8+3];
	UINT			uLongNameLen,uItemsNeeded;
	div_t			dItemsNeeded;
	UINT			i,j,uCharPos;
	BOOL			bFindEnoughFreeItems;
	FAT_DIRITEM		*pShort,*pPtr;
	FAT_LONGNAME	*pLong;
	struct _timeb	Time;
	BOOL			bCheckSum;

	if(!GenShortName(szFile,wLongName,szShortName,&szShortName[8]))	//�����ɶ��ļ���
		return NULL;

	bCheckSum=ShortNameCheckSum(szShortName);

	uLongNameLen=wcslen(wLongName);									//ȡ�ó��ļ�������
	dItemsNeeded=div(uLongNameLen,DIRITEM_CHARSPERITEM);			//���㳤�ļ���ռ������
	if(dItemsNeeded.rem)
		dItemsNeeded.quot++;
	uItemsNeeded=dItemsNeeded.quot+1;								//ȡ�ó��ļ����Ͷ��ļ����ܹ�ռ�õ�����

	for(i=0;;i++)													//�Ӹ�Ŀ¼��Ѱ�������Ŀ�����
	{
		pShort=DirGetItem(wDirClus,i);								//��������ȡ��Ŀ¼��
		if(!pShort)													//ȡ����Ŀ¼�˵���ǵ������Ŀ¼��β����
		{
			WORD wNewClus;
			wNewClus=AppendNewClusterToChain(wDirClus);				//�����Ŀ¼����һ���´�
			if(!IsValidCluster(wNewClus))
				return NULL;										//���䲻���򷵻�NULL
			pShort=(FAT_DIRITEM*)GetClusterPtr(wNewClus);			//���䵽�����´ؾ��ǿ�����
			bFindEnoughFreeItems=TRUE;
			break;
		}
		if(IsFreeDirItem(pShort))									//ȡ����Ŀ¼��ж��Ƿ�Ϊ������
		{															//�ǿ�����
			bFindEnoughFreeItems=TRUE;
			for(j=1;j<uItemsNeeded;j++)								//�ٿ�����û���㹻�����������Ŀ�����
			{
				pPtr=DirGetItem(wDirClus,i+j);
				if(!pPtr)											//���Ĺ����з���ȡ���������Ŀ¼�˵������β��
				{
					WORD wNewClus;
					wNewClus=AppendNewClusterToChain(wDirClus);		//�����Ŀ¼����һ���´�
					if(!IsValidCluster(wNewClus))
						return NULL;								//���䲻���򷵻�NULL
					bFindEnoughFreeItems=TRUE;
					break;
				}
				if(!IsFreeDirItem(pPtr))							//���û�������Ѱ���µĿ�����
				{
					bFindEnoughFreeItems=FALSE;
					i+=j;											//˳��������Щ���������Ŀ�����
					break;
				}
			}
			if(bFindEnoughFreeItems)								//����ҵ��㹻������Ŀ¼����׼������Ŀ¼��
				break;
		}
		else
			bFindEnoughFreeItems=FALSE;								//������ǿ��������������ֵΪ��
	}
	if(bFindEnoughFreeItems)
	{
		UINT uOrder;
		_ftime(&Time);

		j=uItemsNeeded-1;
		pShort=DirGetItem(wDirClus,i+j);							//����д���ļ�����
		memcpy(pShort->szFileName,szShortName,8+3);
		pShort->bAttribute=bAttr;
		pShort->bReserved=0;
		SetCreateTime(pShort,&Time);
		pShort->wFirstClusHI=0;
		pShort->wFirstClusLO=0;
		pShort->dwFileSize=0;

		uCharPos=0;													//Ȼ��׼����д���ļ�����
		uOrder=1;
		while(j--)
		{
			pLong=(FAT_LONGNAME*)DirGetItem(wDirClus,i+j);
			pLong->bOrder=uOrder++;
			pLong->bAttribute=ATTR_LONGNAME;
			pLong->bType=0;
			pLong->bChksum=bCheckSum;
			pLong->wFirstClusLO=0;
			CopyLongNameToItem(pLong,&wLongName[uCharPos]);
			uCharPos+=DIRITEM_CHARSPERITEM;
		}
		pLong->bOrder|=DIRITEM_LASTLONGNAME;						//���һ�����ļ�����ı�ʶ
		return pShort;
	}
	return NULL;													//����������Ҳ����㹻������Ŀ¼���򷵻�NULL
}

//-----------------------------------------------------------------------------
//SetCreateTime������Ŀ¼��Ĵ���ʱ��
//-----------------------------------------------------------------------------
void SetCreateTime(FAT_DIRITEM *pItem,struct _timeb *pTime)
{
	struct tm	*pTm;
	pTm=localtime(&(pTime->time));
	if(pItem->bAttribute&ATTR_SUBDIR)//Ŀ¼ֻ�д���ʱ��
	{
		SetLastWriteTime(pItem,pTime);
		return;
	}
	pItem->bCreateTimeMS=(pTime->millitm/10)+(pTm->tm_sec&1)*100;
	pItem->wLastAccDate=
	pItem->wWriteDate=pItem->wCreateDate=MAKEDATE(pTm->tm_year,pTm->tm_mon,pTm->tm_mday);
	pItem->wWriteTime=pItem->wCreateTime=MAKETIME(pTm->tm_hour,pTm->tm_min,pTm->tm_sec);
}

//-----------------------------------------------------------------------------
//SetLastAccessDate������Ŀ¼�������������
//-----------------------------------------------------------------------------
void SetLastAccessDate(FAT_DIRITEM *pItem,struct _timeb *pTime)
{
	struct tm	*pTm;
	pTm=localtime(&(pTime->time));
	pItem->wLastAccDate=MAKEDATE(pTm->tm_year,pTm->tm_mon,pTm->tm_mday);
}

//-----------------------------------------------------------------------------
//SetLastWriteTime������Ŀ¼������д��ʱ��
//-----------------------------------------------------------------------------
void SetLastWriteTime(FAT_DIRITEM *pItem,struct _timeb *pTime)
{
	struct tm	*pTm;
	pTm=localtime(&(pTime->time));
	pItem->wWriteDate=MAKEDATE(pTm->tm_year,pTm->tm_mon,pTm->tm_mday);
	pItem->wWriteTime=MAKETIME(pTm->tm_hour,pTm->tm_min,pTm->tm_sec);
}


//-----------------------------------------------------------------------------
//CreateEmptyDir������Ŀ¼������Ŀ¼�ڸ�Ŀ¼����
//-----------------------------------------------------------------------------
FAT_DIRITEM* CreateEmptyDir(WORD wParentClus,char *szName,BYTE bAttribute)
{
	WORD wNewClus;
	FAT_DIRITEM *pItem,*pItemList;
	if(!IsValidCluster(wNewClus=AllocateNewCluster(0)))
		return NULL;
	pItem=CreateEmptyFile(wParentClus,szName,(BYTE)(bAttribute|ATTR_SUBDIR));
	if(pItem)
	{
		struct	_timeb	Time;
		//ȡ��ʱ��
		_ftime(&Time);
		pItemList=(FAT_DIRITEM*)GetClusterPtr(wNewClus);
		memset(pItemList,0,FLOPPY_BYTES_PER_CLUS);

		pItem->wFirstClusLO=wNewClus;
		SetLastWriteTime(pItem,&Time);

		memcpy(pItemList,DIRITEM_SELF,11);
		SetCreateTime(pItemList,&Time);
		pItemList->bAttribute=ATTR_SUBDIR;
		pItemList->bReserved=0;
		pItemList->wFirstClusHI=0;
		pItemList->wFirstClusLO=wNewClus;
		pItemList->dwFileSize=0;
		memcpy(++pItemList,DIRITEM_PARENT,11);
		SetCreateTime(pItemList,&Time);
		pItemList->bAttribute=ATTR_SUBDIR;
		pItemList->bReserved=0;
		pItemList->wFirstClusHI=0;
		pItemList->wFirstClusLO=wParentClus;
		pItemList->dwFileSize=0;
		return pItem;
	}
	else
		return NULL;
}

//-----------------------------------------------------------------------------
//CreateEmptyFile���������ļ��������ļ��ڸ�Ŀ¼����
//-----------------------------------------------------------------------------
FAT_DIRITEM* CreateEmptyFile(WORD wParentClus,char *szName,BYTE bAttribute)
{
	if(wParentClus)
		return DirCreateItem(wParentClus,szName,bAttribute);
	else
		return RootCreateItem(szName,bAttribute);
}

//-----------------------------------------------------------------------------
//AllocateNewCluster�������´�
//-----------------------------------------------------------------------------
WORD AllocateNewCluster(WORD wParentCluster)
{
	WORD wNewCluster;
	if(wParentCluster>FLOPPY_CLUS_MAX)
		return 0;
	wNewCluster=FindFreeClus();
	if(!IsValidCluster(wNewCluster))
	{
		ErrorOut("No enough floppy image space.\n");
		return 0;
	}
	memset(GetClusterPtr(wNewCluster),0,FLOPPY_BYTES_PER_CLUS);
	if(wParentCluster)
		WriteFAT12Item(wParentCluster,wNewCluster);
	WriteFAT12Item(wNewCluster,FLOPPY_CLUS_END);
	return wNewCluster;
}

//-----------------------------------------------------------------------------
//GetNbFreeClusters��ȡ��ʣ��������
//-----------------------------------------------------------------------------
WORD GetNbFreeClusters(void)
{
	WORD wClusters=0,i;
	for(i=FLOPPY_CLUS_MIN;i<=FLOPPY_CLUS_MAX;i++)//��������FAT��
	{
		if(!ReadFAT12Item(i))//�������д������+1
			wClusters++;
	}
	return wClusters;//���ؼ���
}

//-----------------------------------------------------------------------------
//WriteDataToEOF��д���ݵ��ļ�β������ʵ��д����ֽ�����
//-----------------------------------------------------------------------------
DWORD WriteDataToEOF(FAT_DIRITEM* pFileItem,void *pData,DWORD dwDataSize)
{
	DWORD	dwBytesToCopy,dwBytesCopyed;
	DWORD	dwOffset;
	WORD	wClusRest,wCurClus;
	void	*pClusterPointer;			//�ص��ڴ�ָ��
	struct _timeb Time;					//ʱ��

	if(!IsValidCluster(pFileItem->wFirstClusLO))		//����ļ��״�Ϊ0������´�
		pFileItem->wFirstClusLO=AllocateNewCluster(0);
	if(!IsValidCluster(pFileItem->wFirstClusLO))		//���䲻���´��򷵻�
		return 0;

	//�Ӵ����ҵ��ļ�β
	wCurClus=GetClusterChainLastCluster(pFileItem->wFirstClusLO);

	dwBytesCopyed=0;					//�ѿ������ֽ���
	dwBytesToCopy=dwDataSize;			//Ҫ�������ֽ���

	//����ļ���С���Ǵغŵ���������������һ����
	if(pFileItem->dwFileSize)			//����ļ��Ѿ�������
	{
		dwOffset=pFileItem->dwFileSize%FLOPPY_BYTES_PER_CLUS;//������ļ�ĩβ��ĩ���е�λ��
		if(dwOffset)					//����ļ���С���Ǵغŵ�������
		{
			wClusRest=(WORD)(FLOPPY_BYTES_PER_CLUS-dwOffset);//����ص�ʣ���ֽ���
			pClusterPointer=(BYTE*)GetClusterPtr(wCurClus)+dwOffset;//ȡ��Ҫд���λ��
			if(wClusRest>=dwDataSize)	//�������ص�ʣ���ֽ�������Ҫд�������
			{
				memcpy(pClusterPointer,pData,dwDataSize);//д������
				pFileItem->dwFileSize+=dwDataSize;//�����ļ���С
				_ftime(&Time);			//ȡ��ʱ��
				SetLastWriteTime(pFileItem,&Time);//�������д��ʱ��
				return dwDataSize;		//���ء�
			}
			else
			{
				memcpy(pClusterPointer,pData,wClusRest);//��������أ�׼����һ���Ĳ���
				pFileItem->dwFileSize+=wClusRest;
				dwBytesToCopy-=wClusRest;
				dwBytesCopyed+=wClusRest;
				(BYTE*)pData+=wClusRest;
				if(!IsValidCluster(wCurClus=AllocateNewCluster(wCurClus)))//Ҫд������ݳ�������ص�ʣ���ֽ����������´�
					return wClusRest;	//������䲻���´��򷵻�
			}
		}
		else							//��ʱ�ļ���С�Ѿ��Ǵغŵ�������
		{								//��Ҫ�����´�
			if(!IsValidCluster(wCurClus=AllocateNewCluster(wCurClus)))
				return 0;				//������䲻���´��򷵻�
		}
	}
	while(dwBytesToCopy>FLOPPY_BYTES_PER_CLUS)//�ظ�����������
	{
		pClusterPointer=GetClusterPtr(wCurClus);//ȡ�õ�ǰ�غŵĻ�����
		memcpy(pClusterPointer,pData,FLOPPY_BYTES_PER_CLUS);//��������
		pFileItem->dwFileSize+=FLOPPY_BYTES_PER_CLUS;
		dwBytesToCopy-=FLOPPY_BYTES_PER_CLUS;//ʣ���ֽ����ݼ�
		dwBytesCopyed+=FLOPPY_BYTES_PER_CLUS;//�ѿ����ֽ�������
		(BYTE*)pData+=FLOPPY_BYTES_PER_CLUS;//ָ�����
		_ftime(&Time);					//ȡ��ʱ��
		SetLastWriteTime(pFileItem,&Time);//�������д��ʱ��
		if(!IsValidCluster(wCurClus=AllocateNewCluster(wCurClus)))//�����´�
			return dwBytesCopyed;		//������䲻���´��򷵻�
	}
	pClusterPointer=GetClusterPtr(wCurClus);//ȡ�õ�ǰ�غŵĻ�����
	memcpy(pClusterPointer,pData,dwBytesToCopy);//������������
	pFileItem->dwFileSize+=dwBytesToCopy;
	_ftime(&Time);						//ȡ��ʱ��
	SetLastWriteTime(pFileItem,&Time);	//�������д��ʱ��
	return dwDataSize;					//����д����ֽ���
}

//-----------------------------------------------------------------------------
//WriteFloppy�������̾���д�뵽�ļ�/���̣����еڶ��������ɴ���NULL
//-----------------------------------------------------------------------------
#define	WRITE(x)	if(fwrite((x),1,sizeof(x),fp)!=sizeof(x)){ErrorOut(__szWriteDataFailed,sizeof(x),szFile);fclose(fp);return FALSE;}fp
BOOL WriteFloppy(char *szFile,char *szDBRFile)
{
	FILE *fp;
	static char __szWriteDataFailed[]="Could not write %u bytes of data to %s.\n";
	if(!(fp=fopen(szFile,"wb")))			//�ȴ�Ҫд����ļ�
	{
		ErrorOut("Could not write file to %s.\n",szFile);
		return FALSE;
	}
	if(szDBRFile)							//���ָ����DBR�ļ�
	{
		FILE *fpDBR;
		if(!(fpDBR=fopen(szDBRFile,"rb")))	//���Դ�Ҫ��ȡ��DBR�ļ�
		{
			ErrorOut("Open DBR file %s failed. Using the default DOS DBR file.\n",szDBRFile);
			WRITE(g_bDefaultDBR);
		}
		else
		{
			char Buf[FLOPPY_BYTES_PER_SEC];
			if(fread(Buf,1,FLOPPY_BYTES_PER_SEC,fpDBR)==FLOPPY_BYTES_PER_SEC)
			{
				fclose(fpDBR);
				WRITE(Buf);
			}
			else
			{
				fclose(fpDBR);
				ErrorOut("Could not read DBR sector from %s,  Using the default DOS DBR file.\n",szDBRFile);
				WRITE(g_bDefaultDBR);
			}
		}
	}
	else
	{
		WRITE(g_bDefaultDBR);
	}
	WRITE(g_bFAT12);
	WRITE(g_bFAT12);
	WRITE(g_RootDirs);
	WRITE(g_bDataArea);
	fclose(fp);
	return TRUE;
}
#undef WRITE
