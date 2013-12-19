#ifndef	_FAT12_IMAGE_GENERATOR_
#define	_FAT12_IMAGE_GENERATOR_

#ifndef	FAT12IMG_EXTRN
#ifdef	__cplusplus
#define	FAT12IMG_EXTRN	extern "C"
#else
#define	FAT12IMG_EXTRN	extern
#endif
#endif

#include<stdio.h>

typedef	unsigned char	BYTE;
typedef	unsigned short	WORD;
typedef	unsigned long	DWORD;

typedef	signed int		INT;
typedef	unsigned int	UINT;

typedef unsigned short	wchar_t;
typedef			wchar_t	WCHAR;

typedef	int		BOOL;
#define	TRUE	1
#define	FALSE	0

#pragma pack(push,1)

#define	FLOPPY_SECS_PER_FAT		9
#define	FLOPPY_BYTES_PER_SEC	0x200
#define	FLOPPY_BYTES_PER_CLUS	FLOPPY_BYTES_PER_SEC
#define	FLOPPY_MAX_ROOT			0xE0
#define	FLOPPY_DBR_SECS			1
#define	FLOPPY_FAT_SECS			9
#define	FLOPPY_FAT_COUNT		2
#define	FLOPPY_ROOT_SECS		(FLOPPY_MAX_ROOT>>4)
#define	FLOPPY_HEADS			2
#define	FLOPPY_SECS_PER_TRACK	18
#define	FLOPPY_TRACKS			80
#define	FLOPPY_SIZE				(FLOPPY_TRACKS*FLOPPY_HEADS*FLOPPY_SECS_PER_TRACK*FLOPPY_BYTES_PER_SEC)
#define	FLOPPY_CLUS_MAX			0xFEF
#define	FLOPPY_CLUS_MIN			2
#define	FLOPPY_CLUS_END			0xFFF
#define	FLOPPY_VALID_CLUS(c)	((c)>=FLOPPY_CLUS_MIN&&(c)<=FLOPPY_CLUS_MAX)
#define	MEDIA_FDD				0xF0

//�ļ�Ŀ¼���ֵ
#define	ATTR_NORMAL			0x00
#define	ATTR_READONLY		0x01
#define	ATTR_HIDE			0x02
#define	ATTR_SYSTEM			0x04
#define	ATTR_VOLUMELABEL	0x08
#define	ATTR_SUBDIR			0x10
#define	ATTR_ARCHIVE		0x20
#define	ATTR_LONGNAME		0x0F

#define	DIRITEM_DELETED		0xE5
#define	DIRITEM_FREE		0x00
#define	DIRITEM_DELETED_JPN	0x05//���ձ������ֵ��ͬ��DIRITEM_DELETED

#define	DIRITEM_SELF		".          "
#define	DIRITEM_PARENT		"..         "

typedef	struct				//FATĿ¼��ṹ��
{
	char	szFileName[8];	//8�ֽڶ��ļ�������һ���ֽڿ�����DIRITEM_DELETED���фh������DIRITEM_FREE�����п��ã�
	char	szExt[3];		//3�ֽ���չ��
	BYTE	bAttribute;		//1�ֽ�����
	BYTE	bReserved;		//����
	BYTE	bCreateTimeMS;	//�ļ�����ʱ��ĺ�������10����ֵΪ0-199��ʵΪ0-1990���룬��Ϊ�ļ�ʱ�����������������Ϊ��λ��
	WORD	wCreateTime;	//�ļ�����ʱ��
	WORD	wCreateDate;	//�ļ���������
	WORD	wLastAccDate;	//����������
	WORD	wFirstClusHI;	//�״غŵĸ�16λ
	WORD	wWriteTime;		//���д������ʱ��
	WORD	wWriteDate;		//���д����������
	WORD	wFirstClusLO;	//�״غŵĵ�16λ
	DWORD	dwFileSize;		//�ļ���С
}FAT_DIRITEM;

//���Ϸ����ļ����ַ���\ / * ? " < > |
#define	VALIDCHR(c)			((c)!= '\\'&&(c)!= '/'&&(c)!= '*'&&(c)!= '?'&&(c)!= '\"'&&(c)!= '<'&&(c)!= '>'&&(c)!= '|'&&(c)>0x20&&(c)<0x80)
#define	VALIDWCHR(c)		((c)!=L'\\'&&(c)!=L'/'&&(c)!=L'*'&&(c)!=L'?'&&(c)!=L'\"'&&(c)!=L'<'&&(c)!=L'>'&&(c)!=L'|'&&(c)>0x20&&(c)<0x80)

#define	MAKETIME(h,m,s)		((((s)/2)&0x1F)|(((m)&0x3F)<<5)|(((h)&0x1F)<<11))
#define	MAKEDATE(y,m,d)		((((d)&0x1F))|(((m)&0x0F)<<5)|(((y)&0x7F)<<9))

#define	DIRITEM_LASTLONGNAME	0x40				//���һ�����ļ������λ�����������ļ�����ġ�bOrder���߼������ֵ���㣬���ʾ�������һ�����ļ����
#define	DIRITEM_LONGNAMELEN		0x100				//���ļ�����󳤶�
#define	DIRITEM_CHARSPERITEM	(5+6+2)				//���ļ�����ÿ���ַ�����13��M$��ô��ģ�������ֲ�������
#define	DIRITEM_MAXSHORTALIAS	1000000				//���ļ�����������
typedef	struct										//FAT�ĳ��ļ���Ŀ¼��ṹ��
{
	BYTE	bOrder;									//���ļ���˳��
	WCHAR	wNamePart1[5];							//5���ַ��ĳ��ļ�����һ����
	BYTE	bAttribute;								//���ԣ�����ΪATTR_LONGNAME
	BYTE	bType;									//���ͣ�Ϊ0���ʾ���ǳ��ļ�����һ���ݣ�����ֵ����Ϊ������չʱ�á�
	BYTE	bChksum;								//У���
	WCHAR	wNamePart2[6];							//6���ַ��ĳ��ļ�����һ����
	WORD	wFirstClusLO;							//����Ϊ0
	WCHAR	wNamePart3[2];							//2���ַ��ĳ��ļ�����һ����
}FAT_LONGNAME;

FAT12IMG_EXTRN	FILE		*pErrStream;										//���������ļ���

FAT12IMG_EXTRN	BYTE		g_bDefaultDBR[FLOPPY_BYTES_PER_SEC];				//Ĭ��DBR
FAT12IMG_EXTRN	BYTE		g_bFAT12[FLOPPY_SECS_PER_FAT*FLOPPY_BYTES_PER_SEC];	//FAT��
FAT12IMG_EXTRN	FAT_DIRITEM	g_RootDirs[FLOPPY_MAX_ROOT];						//��Ŀ¼��
FAT12IMG_EXTRN	BYTE		g_bDataArea											//������
[
	FLOPPY_SIZE-
	(FLOPPY_DBR_SECS+
	FLOPPY_FAT_SECS*FLOPPY_FAT_COUNT+
	FLOPPY_ROOT_SECS)
	*FLOPPY_BYTES_PER_SEC
];

FAT12IMG_EXTRN	void NewFAT12(void);												//��ʼ��FAT��
FAT12IMG_EXTRN	void NewRoot(void);													//��ʼ����Ŀ¼��
FAT12IMG_EXTRN	void NewData(void);													//��ʼ��������

FAT12IMG_EXTRN	WORD ReadFAT12Item(WORD wIndex);									//��FAT��
FAT12IMG_EXTRN	void WriteFAT12Item(WORD wIndex,WORD wValue);						//дFAT��

FAT12IMG_EXTRN	WORD FindFreeClus(void);											//Ѱ�ҿ��д�
FAT12IMG_EXTRN	WORD AllocateNewCluster(WORD wParentCluster);						//�����������µĴ�

FAT12IMG_EXTRN	FAT_DIRITEM* FindFreeRootItem(void);								//Ѱ�ҿ��и�Ŀ¼��
FAT12IMG_EXTRN	FAT_DIRITEM* FindFreeDirItem(WORD wDirClus);						//����Ŀ¼Ѱ�ҿ���Ŀ¼��
FAT12IMG_EXTRN	FAT_DIRITEM* FindShortNameInRoot(char *szShort,char *szExt);		//�ڸ�Ŀ¼����Ҷ��ļ���
FAT12IMG_EXTRN	FAT_DIRITEM* FindLongNameInRoot(WCHAR *wLongName);					//�ڸ�Ŀ¼����ҳ��ļ���
FAT12IMG_EXTRN	FAT_DIRITEM* FindShortNameInDir(WORD wDirClus,char *szShort,char *szExt);//��Ŀ¼����Ҷ��ļ���
FAT12IMG_EXTRN	FAT_DIRITEM* FindLongNameInDir(WORD wDirClus,WCHAR *wLongName);		//��Ŀ¼����ҳ��ļ���
FAT12IMG_EXTRN	FAT_DIRITEM* FindShortNameInRootByCheckSum(BYTE);					//�Ӹ�Ŀ¼���ҵ����У��͵�ԭ�ļ���
FAT12IMG_EXTRN	FAT_DIRITEM* FindShortNameInDirByCheckSum(WORD wCluster,BYTE);		//��Ŀ¼�ҵ����У��͵�ԭ�ļ���

FAT12IMG_EXTRN	void*GetClusterPtr(WORD wCluster);									//ͨ���غ�ȡ����������ָ��
FAT12IMG_EXTRN	WORD GetClusterChainLength(WORD wCluster);							//�������ĳ���

FAT12IMG_EXTRN	BYTE ShortNameCheckSum(BYTE *pFileName8_3);							//ȡ�ö��ļ�����У���

FAT12IMG_EXTRN	BOOL ValidateName(WCHAR *wLongName);								//��鳤�ļ����Ƿ�Ϸ�
FAT12IMG_EXTRN	BOOL GenShortName(char *szLongName,WCHAR *wLongNameOut,char *szShortOut,char *szExtOut);//����һ�����ļ���
FAT12IMG_EXTRN	void GenShortNameAlias(char *szShort);								//ȡ����һ�����ļ���������ԭ���Ķ��ļ���ΪXXXXXX~1���˺���������XXXXXX~2

FAT12IMG_EXTRN	BOOL CollectLongNameFromRoot(BYTE,WCHAR *wLongName);				//�ڸ�Ŀ¼����һ��У����ҵ����г��ļ�����֣����һ�����ļ���
FAT12IMG_EXTRN	BOOL CollectLongNameFromDir(WORD wCluster,BYTE,WCHAR *wLongName);	//��Ŀ¼�д�һ��У����ҵ����г��ļ�����֣����һ�����ļ���

FAT12IMG_EXTRN	BOOL IsFreeDirItem(FAT_DIRITEM*);									//�ж�Ŀ¼���Ƿ�Ϊ����Ŀ¼��

FAT12IMG_EXTRN	FAT_DIRITEM* ParseItem(	char *szFile,BYTE bAttr,					//���ļ����������ļ�������ļ�����
										FAT_DIRITEM*(__cdecl*NewItem)(void),							//����Ŀ¼����ӳ���
										FAT_DIRITEM*(__cdecl*FindLongName)(WCHAR *wLongName),			//���ҳ��ļ������ӳ���
										FAT_DIRITEM*(__cdecl*FindShortName)(char *szShort,char *szExt));//���Ҷ��ļ������ӳ���
FAT12IMG_EXTRN	FAT_DIRITEM* RootCreateItem(char *szFile,BYTE bAttr);				//�Ӹ�Ŀ¼������Ŀ¼��
FAT12IMG_EXTRN	FAT_DIRITEM* DirCreateItem(WORD wDirClus,char *szFile,BYTE bAttr);	//����Ŀ¼����Ŀ¼��

FAT12IMG_EXTRN	FAT_DIRITEM* CreateEmptyDir(WORD wParentClus,char *szName,BYTE bAttribute);	//������Ŀ¼������Ŀ¼�ڸ�Ŀ¼����
FAT12IMG_EXTRN	FAT_DIRITEM* CreateEmptyFile(WORD wParentClus,char *szName,BYTE bAttribute);//�������ļ��������ļ��ڸ�Ŀ¼����
FAT12IMG_EXTRN	DWORD WriteDataToEOF(FAT_DIRITEM* pFileItem,void *pData,DWORD dwDataSize);	//д���ݵ��ļ�β������ʵ��д����ֽ�����

FAT12IMG_EXTRN	void SetCreateTime		(FAT_DIRITEM *pItem,struct _timeb *pTime);	//����Ŀ¼��Ĵ���ʱ��
FAT12IMG_EXTRN	void SetLastAccessDate	(FAT_DIRITEM *pItem,struct _timeb *pTime);	//����Ŀ¼�������������
FAT12IMG_EXTRN	void SetLastWriteTime	(FAT_DIRITEM *pItem,struct _timeb *pTime);	//����Ŀ¼������д��ʱ��

FAT12IMG_EXTRN	WORD GetNbFreeClusters(void);										//ͳ�ƿ��д���

FAT12IMG_EXTRN	BOOL WriteFloppy(char *szFile,char *szDBRFile);						//���澵���ļ�


#pragma pack(pop)

#endif
