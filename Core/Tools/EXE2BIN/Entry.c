#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<malloc.h>
#include<stdarg.h>

#define	VER_MAJOR	1
#define	VER_MINOR	3
#define	VER_STR		"1.3"

typedef	unsigned	char	BYTE;
typedef	unsigned	short	WORD;
typedef	unsigned	long	DWORD;
typedef	char	bool;
#define	true	1
#define	false	0


WORD	wMagicNum;			//魔法数字
WORD	wFileRests;			//文件大小%256的值
WORD	wFileSegs;			//文件大小/256的值
WORD	wNbRelocItems;		//重定位项数
WORD	wHeadSegs;			//文件头所需段数
WORD	wRunMinSegs;		//运行所需最小段数
WORD	wRunMaxSegs;		//运行所需最大段数
WORD	wInitialSS;			//初始SS的值
WORD	wInitialSP;			//初始SP的值
WORD	wCheckSum;			//校验和
WORD	wInitialIP;			//初始IP的值
WORD	wInitialCS;			//初始CS的值
WORD	wRelocTableOffset;	//重定位表偏移
WORD	wOverlay;			//覆盖号

int eprintf(const char *format,...)
{
	int iRetVal;
	va_list pArgs;
	va_start(pArgs,format);
	iRetVal=vfprintf(stderr,format,pArgs);
	va_end(pArgs);
	return iRetVal;
}

//将一个文件的若干字节以最快速度复制到另一个文件的函数
bool copyfile(FILE *fpSrc,FILE *fpDest,DWORD dwBytesToCopy)
{
	void*	pMemBlock=NULL;
	DWORD	dwBytesOfTheBlock;
	DWORD	dwRestBytes;
	dwRestBytes=dwBytesOfTheBlock=dwBytesToCopy;
	while(!pMemBlock)//首先申请一个足够大的内存块用于临时转储文件内容。
	{
		if(!dwBytesOfTheBlock)//如果申请不到任何内存，则对文件进行逐字节拷贝。
		{
			for(;dwBytesToCopy--;)//逐字节拷贝
			{
				fputc(fgetc(fpSrc),fpDest);
				if(ferror(fpSrc)||ferror(fpDest))//如果中途出错则返回假
					return false;
			}
			return true;//否则拷贝完，返回真。
		}
		pMemBlock=malloc(dwBytesOfTheBlock--);//申请内存
	}
	dwBytesOfTheBlock++;//得到实际的内存块大小的值
	while(dwRestBytes>dwBytesOfTheBlock)//进行文件块读取操作
	{
		if(fread(pMemBlock,1,dwBytesOfTheBlock,fpSrc)!=dwBytesOfTheBlock)//读取一个块
		{
			free(pMemBlock);
			return false;
		}
		if(fwrite(pMemBlock,1,dwBytesOfTheBlock,fpDest)!=dwBytesOfTheBlock)//写入一个块
		{
			free(pMemBlock);
			return false;
		}
		dwRestBytes-=dwBytesOfTheBlock;
	}
	if(fread(pMemBlock,1,dwRestBytes,fpSrc)!=dwRestBytes)//剩下字节也如法炮制
	{
		free(pMemBlock);
		return false;
	}
	if(fwrite(pMemBlock,1,dwRestBytes,fpDest)!=dwRestBytes)//写入剩下字节
	{
		free(pMemBlock);
		return false;
	}
	free(pMemBlock);
	return true;//顺利完成，返回真
}

int main(int argc,char** argv)
{
	int		i;
	char	*arg;
	bool	bAddJMP=false;
	bool	bConfirmedOffset=false;
	WORD	wSegment,wOffset;
	char	*szInput=NULL,*szOutput=NULL;
	FILE	*fp,*fpout;
	DWORD	dwFileSize,dwFileReadSize;
	WORD	wHeadSize;

	printf("EXE2BIN Version "VER_STR" by 0xAA55\n");							//打印版本信息
	if(argc<4)																	//如果参数少于3个参数则提示用户本程序的用法
	{
		eprintf(
"Usage:\n"
"EXE2BIN [options] exefile outfile\n"
"Options:\n"
" -j:       Add a far JMP instruction at the start of the file.\n"
" -o[xxxx]: Set the offset of the file. [xxxx] must be a far address in hex.\n"
"           You must specify the offset.\n"
		);
		return -1;
	}
	for(i=1;i<argc;i++)															//开始处理参数
	{
		arg=argv[i];
		if(arg[0]=='-')															//'-'开头的为参数开关
		{
			switch(arg[1])														//判断参数开关
			{
			case 'j':															//-j:文件开头加一个jmp
				bAddJMP=true;
				break;
			case 'o':
				bConfirmedOffset=true;
				if(sscanf(arg,"-o%x:%x",&wSegment,&wOffset)!=2)
				{
					eprintf("Invalid parameter %s\n",arg);
					return -1;
				}
				break;
			default:
				eprintf("Invalid parameter %s\n",arg);
				return -1;
			}
		}
		else
		{
			if(!szInput)
				szInput=arg;
			else if(!szOutput)
				szOutput=arg;
			else
			{
				eprintf("Invalid parameter %s\n",arg);
				return -1;
			}
		}
	}
	if(!bConfirmedOffset)
	{
		eprintf("You must specify the offset of the file.\n");
		return -1;
	}
	fp=fopen(szInput,"rb");
	if(!fp)
	{
		eprintf("Failed to open %s.\n",szInput);
		return -1;
	}
	fpout=fopen(szOutput,"wb");
	if(!fpout)
	{
		eprintf("Failed to write file to %s.\n",szOutput);
		fclose(fp);
		return -1;
	}

#	define	READERR		{eprintf("Unable to read data from %s\n",szInput);fclose(fpout);fclose(fp);return -1;}
#	define	READ(x)		if(fread(&(x),1,sizeof(x),fp)!=sizeof(x))READERR
#	define	WRITEERR	{eprintf("Unable to write data to %s\n",szOutput);fclose(fpout);fclose(fp);return -1;}
#	define	WRITE(x)	if(fwrite(&(x),1,sizeof(x),fpout)!=sizeof(x))WRITEERR

	printf("Now reading the file header...\n");

	fseek(fp,0,SEEK_END);
	dwFileReadSize=ftell(fp);
	fseek(fp,0,SEEK_SET);
	
	READ(wMagicNum);			//魔法数字
	READ(wFileRests);			//文件大小%256的值
	READ(wFileSegs);			//文件大小/256的值
	READ(wNbRelocItems);		//重定位项数
	READ(wHeadSegs);			//文件头所需段数
	READ(wRunMinSegs);			//运行所需最小段数
	READ(wRunMaxSegs);			//运行所需最大段数
	READ(wInitialSS);			//初始SS的值
	READ(wInitialSP);			//初始SP的值
	READ(wCheckSum);			//校验和
	READ(wInitialIP);			//初始IP的值
	READ(wInitialCS);			//初始CS的值
	READ(wRelocTableOffset);	//重定位表偏移
	READ(wOverlay);				//覆盖号

	if(wMagicNum!=0x5A4D)		//如果文件标记不是MZ则报错退出
	{
		eprintf("%s is not a valid EXE file.\n",szInput);
		fclose(fpout);
		fclose(fp);
		return 0;
	}
	dwFileSize=(wFileSegs<<8)|wFileRests;//计算文件大小
	printf(
		"Information:\n"
		"File label:\t\t\t\tMZ\n"
		"File size of the file:\t\t\t%lu bytes.\n"
		"The actual size of the file:\t\t%lu bytes.\n"
		"Count of the relocation table entries:\t%hu items.\n"
		"The size of the header:\t\t\t%hu bytes.\n"
		"The minimum number of bytes required:\t%u bytes.\n"
		"The maximum number of bytes required:\t%u bytes.\n"
		"Initial stack offset:\t\t\t0x%04X:0x%04X\n"
		"Checksum:\t\t\t\t0x%04X\n"
		"Entry point offset:\t\t\t0x%04X:0x%04X\n"
		"Relocation table offset:\t\t0x%04X\n"
		,
		dwFileSize,
		dwFileReadSize,
		wNbRelocItems,
		wHeadSize=wHeadSegs<<4,
		wRunMinSegs<<4,
		wRunMaxSegs<<4,
		wInitialSS,wInitialSP,
		wCheckSum,
		wInitialCS,wInitialIP,
		wRelocTableOffset
		);
	fseek(fp,wHeadSize,SEEK_SET);
	fseek(fpout,0,SEEK_SET);
	if(bAddJMP)
	{
		BYTE	bFarJMP=0xEA;
		WORD	wJmpSeg,wJmpOffs;
		printf("Inserting a JMP instruction.");
		wSegment++;
		if(!wSegment)
			eprintf("Warning:\tSegment overflow.\n");
		wJmpSeg=wSegment+wInitialCS;
		wJmpOffs=wOffset+wInitialIP;
		if(wJmpSeg<wSegment||wJmpSeg<wInitialCS)
			eprintf("Warning:\tSegment overflow.\n");
		if(wJmpOffs<wOffset||wJmpOffs<wInitialIP)
		{
			wJmpSeg+=0x1000;
			eprintf("Warning:\tOffset overflow.\n");
		}
		WRITE(bFarJMP);
		WRITE(wJmpOffs);
		WRITE(wJmpSeg);
		fseek(fpout,11,SEEK_CUR);
		printf("Inserted JMP 0x%04X:0x%04X\n",wJmpSeg,wJmpOffs);
	}
	copyfile(fp,fpout,dwFileReadSize-wHeadSize);//拷贝余下的文件内容
	if(wNbRelocItems)
	{
		WORD	wRelocItem;
		WORD	wRelocSeg,wRelocOffset;
		DWORD	dwOffset;
		WORD	wOrgOffset;
		printf("Relocation table information:\n");
		for(wRelocItem=0;wRelocItem<wNbRelocItems;wRelocItem++)//处理重定位项
		{
			fseek(fp,wRelocTableOffset+((DWORD)wRelocItem<<2),SEEK_SET);//定位到重定位表
			READ(wRelocOffset);
			READ(wRelocSeg);
			dwOffset=(DWORD)(wRelocSeg<<4)+(DWORD)wRelocOffset;
			printf("Offset:\t0x%04X:0x%04X",wRelocSeg,wRelocOffset);
			fseek(fp,dwOffset+wHeadSize,SEEK_SET);//定位到要修改的内容
			if(bAddJMP)
				fseek(fpout,dwOffset+16,SEEK_SET);
			else
				fseek(fpout,dwOffset,SEEK_SET);
			READ(wOrgOffset);
			printf("\tValue 0x%04X",wOrgOffset);
			wOrgOffset+=wSegment;
			WRITE(wOrgOffset);
			printf(" was changed to 0x%04X\n",wOrgOffset);
		}
	}


	fclose(fpout);
	fclose(fp);
	return 0;
}
