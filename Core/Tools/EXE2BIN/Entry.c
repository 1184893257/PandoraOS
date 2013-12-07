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


WORD	wMagicNum;			//ħ������
WORD	wFileRests;			//�ļ���С%256��ֵ
WORD	wFileSegs;			//�ļ���С/256��ֵ
WORD	wNbRelocItems;		//�ض�λ����
WORD	wHeadSegs;			//�ļ�ͷ�������
WORD	wRunMinSegs;		//����������С����
WORD	wRunMaxSegs;		//��������������
WORD	wInitialSS;			//��ʼSS��ֵ
WORD	wInitialSP;			//��ʼSP��ֵ
WORD	wCheckSum;			//У���
WORD	wInitialIP;			//��ʼIP��ֵ
WORD	wInitialCS;			//��ʼCS��ֵ
WORD	wRelocTableOffset;	//�ض�λ��ƫ��
WORD	wOverlay;			//���Ǻ�

int eprintf(const char *format,...)
{
	int iRetVal;
	va_list pArgs;
	va_start(pArgs,format);
	iRetVal=vfprintf(stderr,format,pArgs);
	va_end(pArgs);
	return iRetVal;
}

//��һ���ļ��������ֽ�������ٶȸ��Ƶ���һ���ļ��ĺ���
bool copyfile(FILE *fpSrc,FILE *fpDest,DWORD dwBytesToCopy)
{
	void*	pMemBlock=NULL;
	DWORD	dwBytesOfTheBlock;
	DWORD	dwRestBytes;
	dwRestBytes=dwBytesOfTheBlock=dwBytesToCopy;
	while(!pMemBlock)//��������һ���㹻����ڴ��������ʱת���ļ����ݡ�
	{
		if(!dwBytesOfTheBlock)//������벻���κ��ڴ棬����ļ��������ֽڿ�����
		{
			for(;dwBytesToCopy--;)//���ֽڿ���
			{
				fputc(fgetc(fpSrc),fpDest);
				if(ferror(fpSrc)||ferror(fpDest))//�����;�����򷵻ؼ�
					return false;
			}
			return true;//���򿽱��꣬�����档
		}
		pMemBlock=malloc(dwBytesOfTheBlock--);//�����ڴ�
	}
	dwBytesOfTheBlock++;//�õ�ʵ�ʵ��ڴ���С��ֵ
	while(dwRestBytes>dwBytesOfTheBlock)//�����ļ����ȡ����
	{
		if(fread(pMemBlock,1,dwBytesOfTheBlock,fpSrc)!=dwBytesOfTheBlock)//��ȡһ����
		{
			free(pMemBlock);
			return false;
		}
		if(fwrite(pMemBlock,1,dwBytesOfTheBlock,fpDest)!=dwBytesOfTheBlock)//д��һ����
		{
			free(pMemBlock);
			return false;
		}
		dwRestBytes-=dwBytesOfTheBlock;
	}
	if(fread(pMemBlock,1,dwRestBytes,fpSrc)!=dwRestBytes)//ʣ���ֽ�Ҳ�編����
	{
		free(pMemBlock);
		return false;
	}
	if(fwrite(pMemBlock,1,dwRestBytes,fpDest)!=dwRestBytes)//д��ʣ���ֽ�
	{
		free(pMemBlock);
		return false;
	}
	free(pMemBlock);
	return true;//˳����ɣ�������
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

	printf("EXE2BIN Version "VER_STR" by 0xAA55\n");							//��ӡ�汾��Ϣ
	if(argc<4)																	//�����������3����������ʾ�û���������÷�
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
	for(i=1;i<argc;i++)															//��ʼ�������
	{
		arg=argv[i];
		if(arg[0]=='-')															//'-'��ͷ��Ϊ��������
		{
			switch(arg[1])														//�жϲ�������
			{
			case 'j':															//-j:�ļ���ͷ��һ��jmp
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
	
	READ(wMagicNum);			//ħ������
	READ(wFileRests);			//�ļ���С%256��ֵ
	READ(wFileSegs);			//�ļ���С/256��ֵ
	READ(wNbRelocItems);		//�ض�λ����
	READ(wHeadSegs);			//�ļ�ͷ�������
	READ(wRunMinSegs);			//����������С����
	READ(wRunMaxSegs);			//��������������
	READ(wInitialSS);			//��ʼSS��ֵ
	READ(wInitialSP);			//��ʼSP��ֵ
	READ(wCheckSum);			//У���
	READ(wInitialIP);			//��ʼIP��ֵ
	READ(wInitialCS);			//��ʼCS��ֵ
	READ(wRelocTableOffset);	//�ض�λ��ƫ��
	READ(wOverlay);				//���Ǻ�

	if(wMagicNum!=0x5A4D)		//����ļ���ǲ���MZ�򱨴��˳�
	{
		eprintf("%s is not a valid EXE file.\n",szInput);
		fclose(fpout);
		fclose(fp);
		return 0;
	}
	dwFileSize=(wFileSegs<<8)|wFileRests;//�����ļ���С
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
	copyfile(fp,fpout,dwFileReadSize-wHeadSize);//�������µ��ļ�����
	if(wNbRelocItems)
	{
		WORD	wRelocItem;
		WORD	wRelocSeg,wRelocOffset;
		DWORD	dwOffset;
		WORD	wOrgOffset;
		printf("Relocation table information:\n");
		for(wRelocItem=0;wRelocItem<wNbRelocItems;wRelocItem++)//�����ض�λ��
		{
			fseek(fp,wRelocTableOffset+((DWORD)wRelocItem<<2),SEEK_SET);//��λ���ض�λ��
			READ(wRelocOffset);
			READ(wRelocSeg);
			dwOffset=(DWORD)(wRelocSeg<<4)+(DWORD)wRelocOffset;
			printf("Offset:\t0x%04X:0x%04X",wRelocSeg,wRelocOffset);
			fseek(fp,dwOffset+wHeadSize,SEEK_SET);//��λ��Ҫ�޸ĵ�����
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
