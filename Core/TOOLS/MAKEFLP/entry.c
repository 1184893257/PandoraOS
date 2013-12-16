//*****************************************************************************
//MAKEFLP
//  ENTRY.CPP: 程序的入口点和主要实现部分
//功能:
//  制造一个软盘镜像文件
//
//*****************************************************************************
#include<stdio.h>
#include"fat12img.h"

void PrintUsage()
{
	printf(
		"Usage:\n"
		"MAKEFLP OUT.img <-bxxxx> files\n"
		"  -b:[Optional] Write xxxx to the DBR sector\n");
}

int main(int argc,char** argv)
{
	FILE *fpout;
	if(argc<3)
	{
		PrintUsage();
		return -1;
	}
	fpout=fopen(argv[1],"wb");
	if(!fpout)
	{
		printf("Could not write data to %s.\n",argv[1]);
		return -1;
	}
	NewFAT12();
	NewRoot();
	NewData();
	fclose(fpout);
	return 0;
}






