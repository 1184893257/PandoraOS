//*****************************************************************************
//MAKEFLP
//  ENTRY.CPP: �������ڵ����Ҫʵ�ֲ���
//����:
//  ����һ�����̾����ļ�
//
//*****************************************************************************
#include<stdio.h>
#include<string.h>
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
	pErrStream=stderr;
	NewFAT12();
	NewRoot();
	NewData();
	CreateEmptyDir(CreateEmptyDir(0,"Fuck off!",ATTR_NORMAL)->wFirstClusLO,"Fuck again!",ATTR_NORMAL);
	WriteFloppy("A.IMG",NULL);
	if(argc<3)
	{
		PrintUsage();
		return -1;
	}
	return 0;
}






