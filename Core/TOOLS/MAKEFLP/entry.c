//*****************************************************************************
//MAKEFLP
//  ENTRY.CPP: 程序的入口点和主要实现部分
//功能:
//  制造一个软盘镜像文件
//
//*****************************************************************************
#include<stdio.h>
#include<string.h>
#include<locale.h>
#include"fat12img.h"

void PrintUsage(void)
{
	printf(
		"Usage:\n"
		"MAKEFLP OUT.img <-bxxxx> files\n"
		"  -b:[Optional] Write xxxx to the DBR sector\n");
}

int main(int argc,char** argv)
{
	setlocale(LC_ALL,"");
	if(argc<3)
	{
		PrintUsage();
		return -1;
	}
	pErrStream=stderr;
	NewFloppy();
	return 0;
}






