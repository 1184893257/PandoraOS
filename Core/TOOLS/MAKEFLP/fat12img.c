#include"fat12img.h"
#include<ctype.h>
#include<stdio.h>
#include<memory.h>
#include<string.h>
#include<time.h>
#include<sys/timeb.h>
#include<windows.h>
#include<stdarg.h>

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

FILE *pErrStream=NULL;//输出错误的流

static
void ErrorOut(char* szFormat, ...)
{
	va_list	ap;
	va_start(ap,szFormat);
	if(pErrStream)
		vfprintf(pErrStream,szFormat,ap);
}

//-----------------------------------------------------------------------------
//NewFAT12：初始化FAT12的FAT表
//-----------------------------------------------------------------------------
void NewFAT12(void)
{
	memset(g_bFAT12,0,sizeof(g_bFAT12));
	WriteFAT12Item(0,MEDIA_FDD|0xF00);
	WriteFAT12Item(1,0xFFF);
}

//-----------------------------------------------------------------------------
//NewRoot：初始化FAT12的根目录表
//-----------------------------------------------------------------------------
void NewRoot(void)
{
	memset(g_RootDirs,0,sizeof(g_RootDirs));
}

//-----------------------------------------------------------------------------
//NewData：初始化FAT12的数据区（也就是全部清空）
//-----------------------------------------------------------------------------
void NewData(void)
{
	memset(g_bDataArea,0,sizeof(g_bDataArea));
}

//-----------------------------------------------------------------------------
//ReadFAT12Item：读取FAT12的FAT表的表项
//-----------------------------------------------------------------------------
WORD ReadFAT12Item(WORD wIndex)
{
/*
	FAT12表：
	字节：0 1 2 3 4 5 6 7 8
	索引： 0 1   2 3   4 5
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
//WriteFAT12Item：写入FAT12的FAT表的表项
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
//FindFreeClus：寻找空闲簇号
//-----------------------------------------------------------------------------
WORD FindFreeClus(void)
{
	WORD i;
	for(i=FLOPPY_CLUS_MIN;i<=FLOPPY_CLUS_MAX;i++)
	{
		if(!ReadFAT12Item(i))//找到空闲簇号则返回
			return i;
	}
	return 0;
}

//-----------------------------------------------------------------------------
//FindFreeRootItem：寻找空闲根目录项
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
//FindFreeDirItem：寻找空闲目录项
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindFreeDirItem(WORD wDirClus)
{
	WORD i;
	FAT_DIRITEM* pDir;
	while(FLOPPY_VALID_CLUS(wDirClus))
	{
		pDir=(FAT_DIRITEM*)GetClusterPtr(wDirClus);	//取得目录的指针
		if(!pDir)
			return NULL;
		for(i=0;i<16;i++)							//从目录中找空闲目录项
		{
			if(IsFreeDirItem(&pDir[i]))
				return &pDir[i];					//找到则返回
		}
		wDirClus=ReadFAT12Item(wDirClus);			//否则从簇链找到下一个目录块的位置继续找
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//GetClusterPtr：取得簇在数据区对应簇号的指针
//-----------------------------------------------------------------------------
void* GetClusterPtr(WORD wCluster)
{
	if(FLOPPY_VALID_CLUS(wCluster))
		return (void*)&g_bDataArea[(wCluster-FLOPPY_CLUS_MIN)*FLOPPY_BYTES_PER_SEC];
	else
	{
		ErrorOut("Invalid cluster number.\n");
		return NULL;
	}
}

//-----------------------------------------------------------------------------
//GetClusterChainLength：取得簇链长度
//-----------------------------------------------------------------------------
WORD GetClusterChainLength(WORD wCluster)
{
	WORD wLen=0;//簇链长度从0开始统计
	if(!wCluster)//如果是空闲簇则返回0
	{
		ErrorOut("Invalid cluster number.\n");
		return 0;
	}
	while(FLOPPY_VALID_CLUS(wCluster))
	{
		wLen++;
		wCluster=ReadFAT12Item(wCluster);
	}
	return wLen;
}

//-----------------------------------------------------------------------------
//ShortNameCheckSum：取得短文件名的校验和，用于长文件名目录项
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
//ValidateName：检查长文件名是否合法
//-----------------------------------------------------------------------------
BOOL ValidateName(WCHAR *wLongName)
{
	UINT uIndex,uLen;
	uLen=wcslen(wLongName);
	if(uLen>DIRITEM_LONGNAMELEN)
		return FALSE;
	for(uIndex=0;uIndex<uLen;uIndex++)
	{
		if(	wLongName[uIndex]<0x20	||	//不能有不可打印字符（可以有空格）
			wLongName[uIndex]==L'\\'||	//文件名中不能有路径分隔符'\'
			wLongName[uIndex]==L'/'	||	//以及'/'
			wLongName[uIndex]==L'*'	||	//不能有通配符'*'
			wLongName[uIndex]==L'?'	||	//和'?'
			wLongName[uIndex]==L'\"'||	//不能有半角双引号'"'
			wLongName[uIndex]==L'<'	||	//不能有重定向符号'<'
			wLongName[uIndex]==L'>'	||	//和'>'
			wLongName[uIndex]==L'|')	//也不能有管道'|'
			return FALSE;
	}
	return TRUE;
}

//-----------------------------------------------------------------------------
//GenShortName：生成一个基本的短文件名
//-----------------------------------------------------------------------------
BOOL GenShortName(char *szLongName,WCHAR *wLongNameOut,char *szShortOut,char *szExtOut)
{
	WCHAR	*pChr;
	UINT	uChar,uChars,uChrOut;
	//先把长文件名转换成UNICODE
	if(!OemToCharBuffW(szLongName,wLongNameOut,DIRITEM_LONGNAMELEN))
		return FALSE;
	//去掉前面的空格
	pChr=wLongNameOut;
	while(*pChr==L' ')pChr++;
	wcscpy(wLongNameOut,pChr);
	//去掉后面的空格
	pChr=&wLongNameOut[wcslen(wLongNameOut)-1];
	while(*pChr==L' '||!*pChr)pChr--;
	pChr[1]=L'\0';
	if(!ValidateName(wLongNameOut))
	{
		ErrorOut("File name %S is illegal.\n",wLongNameOut);
		return FALSE;
	}
	//处理扩展名
	szExtOut[0]=szExtOut[1]=szExtOut[2]=' ';//先把输出扩展名设置为3空格
	pChr=wcsrchr(wLongNameOut,L'.');//找原来文件名中的句点
	if(pChr++)//如果找到句点
	{//作为扩展名的三个字符，如果是非法字符（比如汉字）则显示用字符_代替
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
	else//如果没有句点则没有扩展名
		uChars=wcslen(wLongNameOut);
	memset(szShortOut,' ',8);//把输出短文件名先初始化为全空格
	for(uChar=uChrOut=0;		//准备开始处理字符串
		uChar<uChars&&uChrOut<8;//循环直到已经得到了足够长的字符串
		uChar++)				//继续从长文件名读取字符
	{
		if(VALIDWCHR(wLongNameOut[uChar]))
			szShortOut[uChrOut++]=toupper(wLongNameOut[uChar]);//如果是合法字符则转换成大写
		else
			szShortOut[uChrOut++]='_';//否则替换成_
	}
	if(wLongNameOut[uChar])		//如果长文件名超过8字节
	{
		szShortOut[6]='~';		//结尾改成~1
		szShortOut[7]='1';
	}
	return TRUE;
}

//-----------------------------------------------------------------------------
//GenShortNameAlias：生成一个短文件名的别名
//假设原来的短文件名为XXXXXX~1，此函数将生成XXXXXX~2
//-----------------------------------------------------------------------------
void GenShortNameAlias(char *szShort)
{
	UINT uIndex=8;
	DWORD dwAliasNum;
	while(uIndex--)//倒着来遍历原短文件名的8个字符
	{
		if(szShort[uIndex]=='~')//如果找到~符号
		{
			if(uIndex<7)//并且~不是倒数第一个字符
			{
				dwAliasNum=atol(&szShort[uIndex+1])+1;//到这里的时候~后面是纯数字
				if(dwAliasNum>999999)//这个数字+1就是新的文件名，不能大于999999
				{
					for(uIndex=0;uIndex<6;uIndex++)
					{
						if(szShort[uIndex]<=' ')
							szShort[uIndex]='_';
					}
					szShort[6]='~';//则结尾改成~1
					szShort[7]='1';
					return;
				}
				else
				{
					char szNum[8];//算出新的文件名的序号
					for(uIndex=0;uIndex<6;uIndex++)
					{
						if(szShort[uIndex]<=' ')
							szShort[uIndex]='_';
					}
					sprintf(szNum,"~%lu",dwAliasNum);
					if(dwAliasNum>=100000)			//如果是6位数
						memcpy(&szShort[1],szNum,7);//复制7个字符
					else if(dwAliasNum>=10000)		//如果是5位数
						memcpy(&szShort[2],szNum,6);//复制6个字符
					else if(dwAliasNum>=1000)		//如果是4位数
						memcpy(&szShort[3],szNum,5);//复制5个字符
					else if(dwAliasNum>=100)		//如果是3位数
						memcpy(&szShort[4],szNum,4);//复制4个字符
					else if(dwAliasNum>=10)			//如果是2位数
						memcpy(&szShort[5],szNum,3);//复制3个字符
					else							//否则就是1位数
						memcpy(&szShort[6],szNum,2);//复制2个字符
					return;//已经产生新的文件名，返回
				}
			}
			else//~是最后一个字符
			{
				for(uIndex=0;uIndex<6;uIndex++)
				{
					if(szShort[uIndex]<=' ')
						szShort[uIndex]='_';
				}
				szShort[6]='~';//则结尾改成~1
				szShort[7]='1';
				return;
			}
		}
		else//如果遍历到的字符不是~
		{
			if(!isdigit(szShort[uIndex]))//并且不是数字
			{
				for(uIndex=0;uIndex<6;uIndex++)
				{
					if(szShort[uIndex]<=' ')
						szShort[uIndex]='_';
				}
				szShort[6]='~';//则结尾改成~1
				szShort[7]='1';
				return;
			}
		}
	}
	//运行到这里，说明文件名为全数字
	for(uIndex=0;uIndex<6;uIndex++)
	{
		if(szShort[uIndex]<=' ')
			szShort[uIndex]='_';
	}
	szShort[6]='~';//结尾改成~1
	szShort[7]='1';
	return;
}

//-----------------------------------------------------------------------------
//FindShortNameInRoot：从根目录表找对应的短文件名
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindShortNameInRoot(char *szShort,char *szExt)
{
	char szName[8+3];
	UINT i;
	memcpy(szName,szShort,8);
	memcpy(szName+8,szExt,3);
	for(i=0;i<FLOPPY_MAX_ROOT;i++)			//遍历整个根目录表
	{
		if(!IsFreeDirItem(&g_RootDirs[i]))	//判断是否为空闲目录项
		{									//如果不是
			if(!memcmp(g_RootDirs[i].szFileName,szName,8))//而且文件名一致
				return &g_RootDirs[i];		//返回这个目录项
		}
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//CollectLongNameFromRoot：在根目录区从一个校验和找到所有长文件名组分，组成一个长文件名
//-----------------------------------------------------------------------------
BOOL CollectLongNameFromRoot(BYTE bCheckSum,WCHAR *wLongName)
{
	UINT	i,uIndex,uCharPos,uMaxItems=DIRITEM_LASTLONGNAME;
	WCHAR	wcOneItem[DIRITEM_CHARSPERITEM+1]={0};
	BOOL	bCollected[DIRITEM_LASTLONGNAME]={FALSE};//判断是否集齐的数组
	BOOL	bAllTrue;
	bCollected[0]=TRUE;
#	define	pLong	((FAT_LONGNAME*)g_RootDirs)
	for(i=0;i<FLOPPY_MAX_ROOT;i++)			//遍历整个根目录表
	{
		if(!IsFreeDirItem(&g_RootDirs[i]))	//判断是否为空闲目录项
		{									//如果不是
			if(g_RootDirs[i].bAttribute==ATTR_LONGNAME)//如果是长文件名项
			{
				if(bCheckSum==pLong[i].bChksum)//并且校验和匹配
				{
					uIndex=pLong[i].bOrder&0x3F;//取得序号
					if(pLong[i].bOrder&DIRITEM_LASTLONGNAME)//如果是最后一个项
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
					for(bAllTrue=TRUE,uCharPos=0;uCharPos<uMaxItems;uCharPos++)//检查是否集齐了
					{
						if(!bCollected[uCharPos])//没集齐则继续找
						{
							bAllTrue=FALSE;
							break;
						}
					}
					if(bAllTrue)
						return TRUE;//如果集齐了则返回真
					
				}
			}
		}
	}
#	undef pLong
	return FALSE;//如果没有集齐则返回假
TODO:重写这个函数，使其的收集算法变为只收集连续的倒序的长文件名。
}

//-----------------------------------------------------------------------------
//CollectLongNameFromDir：在目录中从一个校验和找到所有长文件名组分，组成一个长文件名
//-----------------------------------------------------------------------------
BOOL CollectLongNameFromDir(WORD wCluster,BYTE bCheckSum,WCHAR *wLongName)
{
	UINT	i,uIndex,uCharPos,uMaxItems=DIRITEM_LASTLONGNAME,uDirLen;
	WCHAR	wcOneItem[DIRITEM_CHARSPERITEM+1]={0};
	BOOL	bCollected[DIRITEM_LASTLONGNAME]={FALSE};//判断是否集齐的数组
	BOOL	bAllTrue;
	FAT_LONGNAME *pLong;
	if(!wCluster)
	{
		ErrorOut("Invalid parameter.\n");
		return FALSE;
	}
	pLong=(FAT_LONGNAME*)malloc(sizeof(FAT_LONGNAME)*(uDirLen=GetClusterChainLength(wCluster)*0x10));
	if(!pLong)
	{
		ErrorOut("Insufficient memory.\n");
		return FALSE;
	}
	uIndex=0;
	do										//先把所有目录簇集齐
	{
		memcpy(&pLong[uIndex],GetClusterPtr(wCluster),FLOPPY_BYTES_PER_SEC);
		uIndex+=FLOPPY_BYTES_PER_SEC;
		wCluster=ReadFAT12Item(wCluster);	//找下一个目录簇
	}
	while(FLOPPY_VALID_CLUS(wCluster));
	bCollected[0]=TRUE;
	for(i=0;i<uDirLen;i++)					//遍历整个根目录表
	{
		if(!IsFreeDirItem((FAT_DIRITEM*)&pLong[i]))//判断是否为空闲目录项
		{									//如果不是
			if(pLong[i].bAttribute==ATTR_LONGNAME)//如果是长文件名项
			{
				if(bCheckSum==pLong[i].bChksum)//并且校验和匹配
				{
					uIndex=pLong[i].bOrder&0x3F;//取得序号
					if(pLong[i].bOrder&DIRITEM_LASTLONGNAME)//如果是最后一个项
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
					for(bAllTrue=TRUE,uCharPos=0;uCharPos<uMaxItems;uCharPos++)//检查是否集齐了
					{
						if(!bCollected[uCharPos])//没集齐则继续找
						{
							bAllTrue=FALSE;
							break;
						}
					}
					if(bAllTrue)
					{
						free(pLong);
						return TRUE;//如果集齐了则返回真
					}
					
				}
			}
		}
	}
	free(pLong);
	return FALSE;//如果没有集齐则返回假
TODO:重写这个函数，使其的收集算法变为只收集连续的倒序的长文件名。
}

//-----------------------------------------------------------------------------
//FindShortNameInRootByCheckSum：从根目录区找到这个校验和的原文件名
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
//FindShortNameInDirByCheckSum：从目录找到这个校验和的原文件名
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindShortNameInDirByCheckSum(WORD wCluster,BYTE bCheckSum)
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
//FindLongNameInRoot：从根目录表找对应的长文件名
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindLongNameInRoot(WCHAR *wLongName)
{
	WCHAR	wLongNameBuf[DIRITEM_LONGNAMELEN];
	BYTE	bCheckSum;
	UINT	i;
	for(i=0;i<FLOPPY_MAX_ROOT;i++)			//遍历整个根目录表
	{
		if(!IsFreeDirItem(&g_RootDirs[i]))	//判断是否为空闲目录项
		{									//如果不是
			if(g_RootDirs[i].bAttribute==ATTR_LONGNAME)//如果是长文件名项
			{
				bCheckSum=((FAT_LONGNAME*)g_RootDirs)[i].bChksum;
				if(CollectLongNameFromRoot(bCheckSum,wLongNameBuf))
				{
					if(!wcscmp(wLongNameBuf,wLongName))
						return FindShortNameInRootByCheckSum(bCheckSum);
				}
			}
		}
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//FindShortNameInDir：检查在目录表短文件名是否重复
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
		pDir=(FAT_DIRITEM*)GetClusterPtr(wDirClus);	//取得目录的指针
		if(!pDir)
			return NULL;
		for(i=0;i<16;i++)							//从目录中找空闲目录项
		{
			if(!IsFreeDirItem(&pDir[i]))			//判断是否为空闲目录项
			{										//如果不是
				if(!memcmp(pDir[i].szFileName,szName,8))//而且文件名一致
					return &pDir[i];				//返回这个目录项
			}
		}
		wDirClus=ReadFAT12Item(wDirClus);			//否则从簇链找到下一个目录块的位置继续找
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//FindShortNameInDir：检查在目录表短文件名是否重复
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindLongNameInDir(WORD wDirClus,WCHAR *wLongName)
{
	WORD i;
	FAT_DIRITEM* pDir;
	FAT_LONGNAME* pLong;
	WCHAR wLongNameBuf[DIRITEM_LONGNAMELEN];
	while(FLOPPY_VALID_CLUS(wDirClus))
	{
		pDir=(FAT_DIRITEM*)GetClusterPtr(wDirClus);	//取得目录的指针
		if(!pDir)
			return NULL;
		for(i=0;i<16;i++)							//从目录中找空闲目录项
		{
			if(!IsFreeDirItem((FAT_DIRITEM*)(pLong=(FAT_LONGNAME*)&pDir[i])))//判断是否为空闲目录项
			{										//如果不是
				if(CollectLongNameFromDir(wDirClus,pLong->bChksum,wLongNameBuf))
				{
					if(!wcscmp(wLongNameBuf,wLongName))
						return FindShortNameInDirByCheckSum(wDirClus,pLong->bChksum);
				}
			}
		}
		wDirClus=ReadFAT12Item(wDirClus);			//否则从簇链找到下一个目录块的位置继续找
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//IsFreeDirItem：检查在根目录表短文件名是否重复
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
//RootCreateItem：从根目录区创建目录项
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
//DirCreateItem：从目录创建目录项
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
		if(!(wFreeCluster=AllocateNewCluster(0)))
			return NULL;
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
//ParseItem：从文件名产生短文件名项、长文件名项
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
	struct	_timeb	Time;

	//生成短文件名
	if(!GenShortName(szFile,wLongName,cShortName,&cShortName[8]))
		return NULL;

	//如果文件名超长
	uLongNameLen=wcslen(wLongName);
	if(uLongNameLen>DIRITEM_LONGNAMELEN)
	{
		ErrorOut("File name (%S) is too long(%u characters, max is %u).\n",wLongName,uLongNameLen,DIRITEM_LONGNAMELEN);
		return NULL;
	}

	//如果长文件名重复了
	if(FindLongName(wLongName))
	{
		ErrorOut("File %S already exists.\n",wLongName);
		return NULL;
	}

	//如果短文件名冲突了
	for(i=0;
		i<DIRITEM_MAXSHORTALIAS &&
		FindShortName(cShortName,&cShortName[8]);
		i++)
		GenShortNameAlias(cShortName);//则生成别名

	//如果找不到合适的别名则返回NULL
	if(FindShortName(cShortName,&cShortName[8]))
	{
		ErrorOut("Could not generate an identical short name.\n");
		return NULL;
	}

	//计算长文件名占用的目录项数
	div_result=div(uLongNameLen,DIRITEM_CHARSPERITEM);
	if(div_result.rem)
		div_result.quot++;


	//从根目录找到空闲目录项
	pIdle=NewItem();
	if(!pIdle)
		return NULL;

	//取得时间
	_ftime(&Time);

	//填写短文件名项
	memcpy(pIdle->szFileName,cShortName,11);
	pIdle->bAttribute=bAttr;
	pIdle->bReserved=0;
	pIdle->wFirstClusHI=0;
	pIdle->wFirstClusLO=0;
	pIdle->dwFileSize=0;
	SetCreateTime(pIdle,&Time);

	//然后准备创建长文件名项
	if(!(pIdleLong=(FAT_LONGNAME*)NewItem()))
		return pIdle;

	//填写所有的长文件名项
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

		if(!(pIdleLong=(FAT_LONGNAME*)NewItem()))//创建不了长文件名项
		{
			pIdleLong->bOrder|=DIRITEM_LASTLONGNAME;//就标记为“最后的长文件名项”
			return pIdle;
		}
	}

	if(uLongNameLen+1<DIRITEM_LONGNAMELEN)
		memset(&wLongName[uLongNameLen+1],0xFF,(DIRITEM_LONGNAMELEN-uLongNameLen)<<1);//长文件名尾用0xFFFF填充

	pIdleLong->bOrder=i|DIRITEM_LASTLONGNAME;//最后一个长文件名项
	memcpy(pIdleLong->wNamePart1,&wLongName[uCharPos],10);uCharPos+=5;
	pIdleLong->bAttribute=ATTR_LONGNAME;
	pIdleLong->bType=0;
	pIdleLong->bChksum=ShortNameCheckSum(cShortName);
	memcpy(pIdleLong->wNamePart2,&wLongName[uCharPos],12);uCharPos+=6;
	pIdleLong->wFirstClusLO=0;
	memcpy(pIdleLong->wNamePart3,&wLongName[uCharPos],4);uCharPos+=2;

	return pIdle;
TODO:修改这个函数，使其能按照正确的顺序产生长文件名。（倒序）
}

//-----------------------------------------------------------------------------
//SetCreateTime：设置目录项的创建时间
//-----------------------------------------------------------------------------
void SetCreateTime(FAT_DIRITEM *pItem,struct _timeb *pTime)
{
	struct tm	*pTm;
	pTm=localtime(&(pTime->time));
	if(pItem->bAttribute&ATTR_SUBDIR)//目录只有创建时间
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
//SetLastAccessDate：设置目录项的最后访问日期
//-----------------------------------------------------------------------------
void SetLastAccessDate(FAT_DIRITEM *pItem,struct _timeb *pTime)
{
	struct tm	*pTm;
	pTm=localtime(&(pTime->time));
	pItem->wLastAccDate=MAKEDATE(pTm->tm_year,pTm->tm_mon,pTm->tm_mday);
}

//-----------------------------------------------------------------------------
//SetLastWriteTime：设置目录项的最后写的时间
//-----------------------------------------------------------------------------
void SetLastWriteTime(FAT_DIRITEM *pItem,struct _timeb *pTime)
{
	struct tm	*pTm;
	pTm=localtime(&(pTime->time));
	pItem->wWriteDate=MAKEDATE(pTm->tm_year,pTm->tm_mon,pTm->tm_mday);
	pItem->wWriteTime=MAKETIME(pTm->tm_hour,pTm->tm_min,pTm->tm_sec);
}


//-----------------------------------------------------------------------------
//CreateEmptyDir：创建目录，返回目录在父目录的项
//-----------------------------------------------------------------------------
FAT_DIRITEM* CreateEmptyDir(WORD wParentClus,char *szName,BYTE bAttribute)
{
	WORD wNewClus;
	FAT_DIRITEM *pItem,*pItemList;
	if(!(wNewClus=AllocateNewCluster(0)))
		return NULL;
	pItem=CreateEmptyFile(wParentClus,szName,(BYTE)(bAttribute|ATTR_SUBDIR));
	if(pItem)
	{
		struct	_timeb	Time;
		//取得时间
		_ftime(&Time);
		pItemList=(FAT_DIRITEM*)GetClusterPtr(wNewClus);
		memset(pItemList,0,FLOPPY_BYTES_PER_SEC);

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
//CreateEmptyFile：创建空文件，返回文件在父目录的项
//-----------------------------------------------------------------------------
FAT_DIRITEM* CreateEmptyFile(WORD wParentClus,char *szName,BYTE bAttribute)
{
	if(wParentClus)
		return DirCreateItem(wParentClus,szName,bAttribute);
	else
		return RootCreateItem(szName,bAttribute);
}

//-----------------------------------------------------------------------------
//AllocateNewCluster：分配新簇
//-----------------------------------------------------------------------------
WORD AllocateNewCluster(WORD wParentCluster)
{
	WORD wNewCluster;
	wNewCluster=FindFreeClus();
	if(!wNewCluster)
	{
		ErrorOut("No enough floppy image space.\n");
		return 0;
	}
	if(wParentCluster)
		WriteFAT12Item(wParentCluster,wNewCluster);
	WriteFAT12Item(wNewCluster,FLOPPY_CLUS_END);
	return wNewCluster;
}

//-----------------------------------------------------------------------------
//WriteDataToEOF：写数据到文件尾，返回实际写入的字节数。
//-----------------------------------------------------------------------------
DWORD WriteDataToEOF(FAT_DIRITEM* pFileItem,void *pData,DWORD dwDataSize)
{
	DWORD	dwBytesToCopy,dwBytesCopyed;
	DWORD	dwOffset;
	WORD	wClusRest,wCurClus,wNextClus;
	void	*pClusterPointer;			//簇的内存指针
	struct _timeb Time;					//时间

	if(!pFileItem->wFirstClusLO)		//如果文件首簇为0则分配新簇
		pFileItem->wFirstClusLO=AllocateNewCluster(0);
	if(!pFileItem->wFirstClusLO)		//分配不到新簇则返回
		return 0;

	//从簇链找到文件尾
	wCurClus=pFileItem->wFirstClusLO;
	while((wNextClus=ReadFAT12Item(wCurClus))<=FLOPPY_CLUS_MAX)
		wCurClus=wNextClus;
	//wCurClus=文件末簇号

	dwBytesCopyed=0;					//已拷贝的字节数
	dwBytesToCopy=dwDataSize;			//要拷贝的字节数

	//如果文件大小不是簇号的整数倍，则填充第一个簇
	if(pFileItem->dwFileSize)			//如果文件已经有数据
	{
		dwOffset=pFileItem->dwFileSize%FLOPPY_BYTES_PER_CLUS;//计算出文件末尾在末簇中的位置
		if(dwOffset)					//如果文件大小不是簇号的整数倍
		{
			wClusRest=(WORD)(FLOPPY_BYTES_PER_CLUS-dwOffset);//这个簇的剩余字节数
			pClusterPointer=(BYTE*)GetClusterPtr(wCurClus)+dwOffset;//取得要写入的位置
			if(wClusRest>=dwDataSize)	//如果这个簇的剩余字节能容纳要写入的数据
			{
				memcpy(pClusterPointer,pData,dwDataSize);//写入内容
				pFileItem->dwFileSize+=dwDataSize;//递增文件大小
				_ftime(&Time);			//取得时间
				SetLastWriteTime(pFileItem,&Time);//设置最后写的时间
				return dwDataSize;		//返回。
			}
			else
			{
				memcpy(pClusterPointer,pData,wClusRest);//填满这个簇，准备下一步的操作
				pFileItem->dwFileSize+=wClusRest;
				dwBytesToCopy-=wClusRest;
				dwBytesCopyed+=wClusRest;
				(BYTE*)pData+=wClusRest;
				if(!(wCurClus=AllocateNewCluster(wCurClus)))//要写入的数据超过这个簇的剩余字节则必须分配新簇
					return wClusRest;	//如果分配不了新簇则返回
			}
		}
		else							//此时文件大小已经是簇号的整数倍
		{								//则要分配新簇
			if(!(wCurClus=AllocateNewCluster(wCurClus)))
				return 0;				//如果分配不了新簇则返回
		}
	}
	while(dwBytesToCopy>FLOPPY_BYTES_PER_CLUS)//重复复制整个簇
	{
		pClusterPointer=GetClusterPtr(wCurClus);//取得当前簇号的缓冲区
		memcpy(pClusterPointer,pData,FLOPPY_BYTES_PER_CLUS);//拷贝数据
		pFileItem->dwFileSize+=FLOPPY_BYTES_PER_CLUS;
		dwBytesToCopy-=FLOPPY_BYTES_PER_CLUS;//剩余字节数递减
		dwBytesCopyed+=FLOPPY_BYTES_PER_CLUS;//已拷贝字节数递增
		(BYTE*)pData+=FLOPPY_BYTES_PER_CLUS;//指针递增
		_ftime(&Time);					//取得时间
		SetLastWriteTime(pFileItem,&Time);//设置最后写的时间
		if(!(wCurClus=AllocateNewCluster(wCurClus)))//分配新簇
			return dwBytesCopyed;		//如果分配不了新簇则返回
	}
	pClusterPointer=GetClusterPtr(wCurClus);//取得当前簇号的缓冲区
	memcpy(pClusterPointer,pData,dwBytesToCopy);//拷贝最后的数据
	pFileItem->dwFileSize+=dwBytesToCopy;
	_ftime(&Time);						//取得时间
	SetLastWriteTime(pFileItem,&Time);	//设置最后写的时间
	return dwDataSize;					//返回写入的字节数
}

//-----------------------------------------------------------------------------
//GetNbFreeClusters：取得剩余扇区数
//-----------------------------------------------------------------------------
WORD GetNbFreeClusters(void)
{
	WORD wClusters=0,i;
	for(i=FLOPPY_CLUS_MIN;i<=FLOPPY_CLUS_MAX;i++)//遍历整个FAT表
	{
		if(!ReadFAT12Item(i))//遇到空闲簇则计数+1
			wClusters++;
	}
	return wClusters;//返回计数
}

//-----------------------------------------------------------------------------
//WriteFloppy：把软盘镜像写入到文件/磁盘，其中第二个参数可传入NULL
//-----------------------------------------------------------------------------
#define	WRITE(x)	if(fwrite((x),1,sizeof(x),fp)!=sizeof(x)){ErrorOut(__szWriteDataFailed,sizeof(x),szFile);fclose(fp);return FALSE;}fp
BOOL WriteFloppy(char *szFile,char *szDBRFile)
{
	FILE *fp;
	static char __szWriteDataFailed[]="Could not write %u bytes of data to %s.\n";
	if(!(fp=fopen(szFile,"wb")))			//先打开要写入的文件
	{
		ErrorOut("Could not write file to %s.\n",szFile);
		return FALSE;
	}
	if(szDBRFile)							//如果指定了DBR文件
	{
		FILE *fpDBR;
		if(!(fpDBR=fopen(szDBRFile,"rb")))	//则尝试打开要读取的DBR文件
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
