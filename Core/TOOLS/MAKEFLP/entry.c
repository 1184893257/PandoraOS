//*****************************************************************************
//MAKEFLP
//  ENTRY.CPP: �������ڵ����Ҫʵ�ֲ���
//����:
//  ����һ�����̾����ļ�
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






