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
//                                 变量定义
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

FILE *pErrStream=NULL;//输出错误的流

//#############################################################################
//                                 函数定义
//#############################################################################

//-----------------------------------------------------------------------------
//ErrorOut：输出程序运行中的错误，如果pErrStream不为NULL
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
	while(IsValidCluster(wDirClus))
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
	if(IsValidCluster(wCluster))
		return (void*)&g_bDataArea[(wCluster-FLOPPY_CLUS_MIN)*FLOPPY_BYTES_PER_CLUS];
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
	while(IsValidCluster(wCluster))
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
BOOL CollectLongNameFromRoot(FAT_DIRITEM *pShortName,WCHAR *wLongName)
{
	BOOL			bCheckSum;
	BYTE			bSN=1;//序号
	FAT_LONGNAME	*pLongName;
	WCHAR			wLongItem[DIRITEM_CHARSPERITEM];
	WCHAR			wChr;
	UINT			uChars;
	bCheckSum=ShortNameCheckSum(pShortName->szFileName);				//计算校验和
	pLongName=(FAT_LONGNAME*)pShortName;								//从当前目录项往前找长文件名
	while(--pLongName>=(FAT_LONGNAME*)g_RootDirs)
	{
		if(pLongName->bAttribute!=ATTR_LONGNAME)						//如果目录项没有长文件名返回假
			return FALSE;
		if(pLongName->bChksum!=bCheckSum)								//如果前面有长文件名但是校验和不对返回假
			return FALSE;
		if((pLongName->bOrder & DIRITEM_LNORDERMASK)!=bSN)				//如果前面有长文件名而且校验和是对的但是序号不对返回假
		{
			ErrorOut("Root entry is bad.\n");
			return FALSE;
		}
		memcpy(&wLongItem[0],pLongName->wNamePart1,5*sizeof(WCHAR));	//拷贝第一个长文件名部分
		memcpy(&wLongItem[5],pLongName->wNamePart2,6*sizeof(WCHAR));	//拷贝第二个长文件名部分
		memcpy(&wLongItem[11],pLongName->wNamePart3,2*sizeof(WCHAR));	//拷贝第三个长文件名部分
		if(pLongName->bOrder&DIRITEM_LASTLONGNAME)						//如果是最后的长文件名项
		{
			for(uChars=0;uChars<DIRITEM_CHARSPERITEM;uChars++)			//则手动拷贝长文件名
			{
				wChr=wLongItem[uChars];	//取字符
				if(wChr&&wChr!=0xFFFF)	//如果不是结尾
					*wLongName++=wChr;	//就加到长文件名处
				else
					break;				//否则结束循环
			}
			*wLongName=0;				//输出的长文件名加个结尾标识
			return TRUE;
		}
		else							//这里不是最后的长文件名项
		{
			memcpy(wLongName,wLongItem,DIRITEM_CHARSPERITEM*sizeof(WCHAR));	//拷贝所有的长文件名字符
			wLongName+=DIRITEM_CHARSPERITEM;								//移动指针
		}
		bSN++;
	}
	return FALSE;						//没有集齐长文件名则返回假
}

//-----------------------------------------------------------------------------
//GetPrevCluster：取得前一个簇号
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
//CollectLongNameFromDir：在目录中从一个校验和找到所有长文件名组分，组成一个长文件名
//-----------------------------------------------------------------------------
BOOL CollectLongNameFromDir(WORD wCurrentCluster,FAT_DIRITEM *pShortName,WCHAR *wLongName)
{
	BOOL			bCheckSum;
	BYTE			bSN=1;//序号
	WORD			wPrevCluster;
	FAT_LONGNAME	*pLongName;
	FAT_LONGNAME	*pFirstItem;//当前簇的第一个目录项
	WCHAR			wLongItem[DIRITEM_CHARSPERITEM];
	WCHAR			wChr;
	UINT			uChars;
	bCheckSum=ShortNameCheckSum(pShortName->szFileName);				//计算校验和
	pLongName=(FAT_LONGNAME*)pShortName;								//从当前目录项往前找长文件名
	pFirstItem=(FAT_LONGNAME*)GetClusterPtr(wCurrentCluster);			//找到当前簇的指针
	for(;;)
	{
		while(--pLongName>=pFirstItem)
		{
			if(pLongName->bAttribute!=ATTR_LONGNAME)						//如果目录项没有长文件名返回假
				return FALSE;
			if(pLongName->bChksum!=bCheckSum)								//如果前面有长文件名但是校验和不对返回假
				return FALSE;
			if((pLongName->bOrder & DIRITEM_LNORDERMASK)!=bSN)				//如果前面有长文件名而且校验和是对的但是序号不对返回假
			{
				ErrorOut("Root entry is bad.\n");
				return FALSE;
			}
			memcpy(&wLongItem[0],pLongName->wNamePart1,5*sizeof(WCHAR));	//拷贝第一个长文件名部分
			memcpy(&wLongItem[5],pLongName->wNamePart2,6*sizeof(WCHAR));	//拷贝第二个长文件名部分
			memcpy(&wLongItem[11],pLongName->wNamePart3,2*sizeof(WCHAR));	//拷贝第三个长文件名部分
			if(pLongName->bOrder&DIRITEM_LASTLONGNAME)						//如果是最后的长文件名项
			{
				for(uChars=0;uChars<DIRITEM_CHARSPERITEM;uChars++)			//则手动拷贝长文件名
				{
					wChr=wLongItem[uChars];	//取字符
					if(wChr&&wChr!=0xFFFF)	//如果不是结尾
						*wLongName++=wChr;	//就加到长文件名处
					else
						break;				//否则结束循环
				}
				*wLongName=0;				//输出的长文件名加个结尾标识
				return TRUE;
			}
			else							//这里不是最后的长文件名项
			{
				memcpy(wLongName,wLongItem,DIRITEM_CHARSPERITEM*sizeof(WCHAR));	//拷贝所有的长文件名字符
				wLongName+=DIRITEM_CHARSPERITEM;								//移动指针
			}
			bSN++;
		}
		wPrevCluster=GetPrevCluster(wCurrentCluster);
		if(!IsValidCluster(wPrevCluster))
			return FALSE;					//如果没有集齐长文件名而且已经是第一个簇则返回假
		wCurrentCluster=wPrevCluster;
		pFirstItem=(FAT_LONGNAME*)GetClusterPtr(wCurrentCluster);					//找到前面簇的指针
		pLongName=pFirstItem+FLOPPY_BYTES_PER_CLUS/sizeof(FAT_LONGNAME);
	}
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
//FindLongNameInRoot：从根目录表找对应的长文件名
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindLongNameInRoot(WCHAR *wLongName)
{
	WCHAR	wLongNameBuf[DIRITEM_LONGNAMELEN];
	UINT	i;
	for(i=0;i<FLOPPY_MAX_ROOT;i++)			//遍历整个根目录表
	{
		if(!IsFreeDirItem(&g_RootDirs[i]))	//判断是否为空闲目录项
		{									//如果不是
			if(g_RootDirs[i].bAttribute!=ATTR_LONGNAME)//如果不是长文件名项
			{
				if(CollectLongNameFromRoot(&g_RootDirs[i],wLongNameBuf))//则找它的长文件名
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
//FindShortNameInDir：在目录中通过短文件名查找目录项
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
//FindLongNameInDir：在根目录中通过长文件名查找目录项
//-----------------------------------------------------------------------------
FAT_DIRITEM* FindLongNameInDir(WORD wDirClus,WCHAR *wLongName)
{
	WORD i;
	FAT_DIRITEM* pDir;
	WCHAR wLongNameBuf[DIRITEM_LONGNAMELEN];
	while(IsValidCluster(wDirClus))
	{
		pDir=(FAT_DIRITEM*)GetClusterPtr(wDirClus);	//取得目录的指针
		if(!pDir)
			return NULL;
		for(i=0;i<16;i++)							//从目录中找空闲目录项
		{
			if(!IsFreeDirItem((FAT_DIRITEM*)(&pDir[i])))//判断是否为空闲目录项
			{										//如果不是
				if(pDir[i].bAttribute!=ATTR_LONGNAME)//如果不是长文件名目录项
				{
					if(CollectLongNameFromDir(wDirClus,&pDir[i],wLongNameBuf))//集齐长文件名
					{
						if(!wcscmp(wLongNameBuf,wLongName))//如果文件名是匹配的
							return &pDir[i];		//则返回找到的目录项
					}
				}
			}
		}
		wDirClus=ReadFAT12Item(wDirClus);			//否则从簇链找到下一个目录块的位置继续找
	}
	return NULL;
}

//-----------------------------------------------------------------------------
//IsFreeDirItem：检查是否为空闲目录项
//-----------------------------------------------------------------------------
BOOL IsFreeDirItem(FAT_DIRITEM* pDir)
{
	if(	(BYTE)(pDir->szFileName[0])==DIRITEM_FREE||			//空白
		(BYTE)(pDir->szFileName[0])==DIRITEM_DELETED)		//已删除
		//(BYTE)(pDir->szFileName[0])==DIRITEM_DELETED_JPN)	//日本的已删除
		return TRUE;
	else
		return FALSE;
}

//-----------------------------------------------------------------------------
//IsShortName：检查这个文件名是否为短文件名
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
//CopyLongNameToItem：拷贝长文件名的一部分到一个长文件名目录项
//-----------------------------------------------------------------------------
void CopyLongNameToItem(FAT_LONGNAME *pItem,WCHAR *wLongName)
{
	UINT i,j=0;
	memset(pItem->wNamePart1,0xFF,5*sizeof(WCHAR));	//先把长文件名项的三个文件名部分用0xFF填充
	memset(pItem->wNamePart2,0xFF,6*sizeof(WCHAR));
	memset(pItem->wNamePart3,0xFF,2*sizeof(WCHAR));
	//拷贝第一个部分
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
	//拷贝第二个部分
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
	//拷贝第三个部分
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
//RootCreateItem：从根目录区创建目录项
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

	if(!GenShortName(szFile,wLongName,szShortName,&szShortName[8]))	//先生成短文件名
		return NULL;

	bCheckSum=ShortNameCheckSum(szShortName);						//根据短文件名计算校验和

	uLongNameLen=wcslen(wLongName);									//取得长文件名长度
	dItemsNeeded=div(uLongNameLen,DIRITEM_CHARSPERITEM);			//计算长文件名占用项数
	if(dItemsNeeded.rem)
		dItemsNeeded.quot++;
	uItemsNeeded=dItemsNeeded.quot+1;								//取得长文件名和短文件名总共占用的项数，加一这里加上的是短文件名占用的项

	for(i=0;i<FLOPPY_MAX_ROOT-uItemsNeeded;i++)						//从根目录中寻找连续的空闲项
	{
		if(IsFreeDirItem(&g_RootDirs[i]))							//找到一个空闲项
		{
			bFindEnoughFreeItems=TRUE;
			for(j=1;j<uItemsNeeded;j++)								//再看看有没有足够数量的连续的空闲项
			{
				if(!IsFreeDirItem(&g_RootDirs[i+j]))				//如果没有则继续寻找新的空闲项
				{
					bFindEnoughFreeItems=FALSE;
					i+=j;											//顺便跳过这些数量不够的空闲项
					break;
				}
			}
			if(bFindEnoughFreeItems)								//如果找到足够数量的目录项则准备创建目录项
			{
				_ftime(&Time);

				j=uItemsNeeded-1;
				pShort=&g_RootDirs[i+j];							//先填写短文件名项
				memcpy(pShort->szFileName,szShortName,8+3);
				pShort->bAttribute=bAttr;
				pShort->bReserved=0;
				SetCreateTime(pShort,&Time);
				pShort->wFirstClusHI=0;
				pShort->wFirstClusLO=0;
				pShort->dwFileSize=0;

				pLong=(FAT_LONGNAME*)pShort;						//然后准备填写长文件名项
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
				pLong->bOrder|=DIRITEM_LASTLONGNAME;				//最后一个长文件名项的标识
				return pShort;
			}
		}
	}
	return NULL;													//如果到最终找不到足够数量的目录项则返回NULL
}

//-----------------------------------------------------------------------------
//DirGetItem：在目录中根据索引取得目录项
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
//GetClusterChainLastCluster：取得簇链的最后一个簇
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
//AppendNewClusterToChain：给簇链尾追加一个新的簇
//-----------------------------------------------------------------------------
WORD AppendNewClusterToChain(WORD wCluster)
{
	return AllocateNewCluster(GetClusterChainLastCluster(wCluster));
}

//-----------------------------------------------------------------------------
//DirCreateItem：从目录创建目录项
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

	if(!GenShortName(szFile,wLongName,szShortName,&szShortName[8]))	//先生成短文件名
		return NULL;

	bCheckSum=ShortNameCheckSum(szShortName);

	uLongNameLen=wcslen(wLongName);									//取得长文件名长度
	dItemsNeeded=div(uLongNameLen,DIRITEM_CHARSPERITEM);			//计算长文件名占用项数
	if(dItemsNeeded.rem)
		dItemsNeeded.quot++;
	uItemsNeeded=dItemsNeeded.quot+1;								//取得长文件名和短文件名总共占用的项数

	for(i=0;;i++)													//从根目录中寻找连续的空闲项
	{
		pShort=DirGetItem(wDirClus,i);								//按照索引取得目录项
		if(!pShort)													//取不到目录项，说明是到了这个目录的尾部了
		{
			WORD wNewClus;
			wNewClus=AppendNewClusterToChain(wDirClus);				//给这个目录分配一个新簇
			if(!IsValidCluster(wNewClus))
				return NULL;										//分配不到则返回NULL
			pShort=(FAT_DIRITEM*)GetClusterPtr(wNewClus);			//分配到了则新簇就是空闲项
			bFindEnoughFreeItems=TRUE;
			break;
		}
		if(IsFreeDirItem(pShort))									//取得了目录项，判断是否为空闲项
		{															//是空闲项
			bFindEnoughFreeItems=TRUE;
			for(j=1;j<uItemsNeeded;j++)								//再看看有没有足够数量的连续的空闲项
			{
				pPtr=DirGetItem(wDirClus,i+j);
				if(!pPtr)											//检查的过程中发现取不到后面的目录项，说明到了尾簇
				{
					WORD wNewClus;
					wNewClus=AppendNewClusterToChain(wDirClus);		//给这个目录分配一个新簇
					if(!IsValidCluster(wNewClus))
						return NULL;								//分配不到则返回NULL
					bFindEnoughFreeItems=TRUE;
					break;
				}
				if(!IsFreeDirItem(pPtr))							//如果没有则继续寻找新的空闲项
				{
					bFindEnoughFreeItems=FALSE;
					i+=j;											//顺便跳过这些数量不够的空闲项
					break;
				}
			}
			if(bFindEnoughFreeItems)								//如果找到足够数量的目录项则准备创建目录项
				break;
		}
		else
			bFindEnoughFreeItems=FALSE;								//如果不是空闲项则设置这个值为假
	}
	if(bFindEnoughFreeItems)
	{
		UINT uOrder;
		_ftime(&Time);

		j=uItemsNeeded-1;
		pShort=DirGetItem(wDirClus,i+j);							//先填写短文件名项
		memcpy(pShort->szFileName,szShortName,8+3);
		pShort->bAttribute=bAttr;
		pShort->bReserved=0;
		SetCreateTime(pShort,&Time);
		pShort->wFirstClusHI=0;
		pShort->wFirstClusLO=0;
		pShort->dwFileSize=0;

		uCharPos=0;													//然后准备填写长文件名项
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
		pLong->bOrder|=DIRITEM_LASTLONGNAME;						//最后一个长文件名项的标识
		return pShort;
	}
	return NULL;													//如果到最终找不到足够数量的目录项则返回NULL
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
	if(!IsValidCluster(wNewClus=AllocateNewCluster(0)))
		return NULL;
	pItem=CreateEmptyFile(wParentClus,szName,(BYTE)(bAttribute|ATTR_SUBDIR));
	if(pItem)
	{
		struct	_timeb	Time;
		//取得时间
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
//WriteDataToEOF：写数据到文件尾，返回实际写入的字节数。
//-----------------------------------------------------------------------------
DWORD WriteDataToEOF(FAT_DIRITEM* pFileItem,void *pData,DWORD dwDataSize)
{
	DWORD	dwBytesToCopy,dwBytesCopyed;
	DWORD	dwOffset;
	WORD	wClusRest,wCurClus;
	void	*pClusterPointer;			//簇的内存指针
	struct _timeb Time;					//时间

	if(!IsValidCluster(pFileItem->wFirstClusLO))		//如果文件首簇为0则分配新簇
		pFileItem->wFirstClusLO=AllocateNewCluster(0);
	if(!IsValidCluster(pFileItem->wFirstClusLO))		//分配不到新簇则返回
		return 0;

	//从簇链找到文件尾
	wCurClus=GetClusterChainLastCluster(pFileItem->wFirstClusLO);

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
				if(!IsValidCluster(wCurClus=AllocateNewCluster(wCurClus)))//要写入的数据超过这个簇的剩余字节则必须分配新簇
					return wClusRest;	//如果分配不了新簇则返回
			}
		}
		else							//此时文件大小已经是簇号的整数倍
		{								//则要分配新簇
			if(!IsValidCluster(wCurClus=AllocateNewCluster(wCurClus)))
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
		if(!IsValidCluster(wCurClus=AllocateNewCluster(wCurClus)))//分配新簇
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
