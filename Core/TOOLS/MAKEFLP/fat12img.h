#ifndef	_FAT12_IMAGE_GENERATOR_
#define	_FAT12_IMAGE_GENERATOR_

#ifndef	FAT12IMG_EXTRN
#ifdef	__cplusplus
#define	FAT12IMG_EXTRN	extern "C"
#else
#define	FAT12IMG_EXTRN	extern
#endif
#endif

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

#define	FLOPPY_SECS_PER_FAT		9
#define	FLOPPY_BYTES_PER_SEC	0x200
#define	FLOPPY_MAX_ROOT			0xE0
#define	FLOPPY_DBR_SECS			1
#define	FLOPPY_FAT_SECS			9
#define	FLOPPY_FAT_COUNT		2
#define	FLOPPY_ROOT_SECS		(FLOPPY_MAX_ROOT>>4)
#define	FLOPPY_HEADS			2
#define	FLOPPY_SECS_PER_TRACK	18
#define	FLOPPY_TRACKS			80
#define	FLOPPY_SIZE				(FLOPPY_TRACKS*FLOPPY_HEADS*FLOPPY_TRACKS*FLOPPY_BYTES_PER_SEC)
#define	FLOPPY_CLUS_MAX			0xFEF
#define	FLOPPY_CLUS_MIN			2
#define	FLOPPY_CLUS_END			0xFFF
#define	MEDIA_FDD				0xF0

//�ļ�Ŀ¼���ֵ
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

#define	VALIDCHR(c)			((c)!= '\\'&&(c)!= '/'&&(c)!= '*'&&(c)!= '?'&&(c)!= '\"'&&(c)!= '<'&&(c)!= '>'&&(c)!= '|'&&(c)>0x20&&(c)<0x80)
#define	VALIDWCHR(c)		((c)!=L'\\'&&(c)!=L'/'&&(c)!=L'*'&&(c)!=L'?'&&(c)!=L'\"'&&(c)!=L'<'&&(c)!=L'>'&&(c)!=L'|'&&(c)>0x20&&(c)<0x80)

#define	MAKETIME(h,m,s)		((((s)/2)&0x1F)|(((m)&0x3F)<<5)|(((h)&0x1F)<<11))
#define	MAKEDATE(y,m,d)		((((d)&0x1F))|(((m)&0x0F)<<5)|(((y)&0x7F)<<9))

#define	DIRITEM_LASTLONGNAME	0x40//���һ�����ļ������λ�����������ļ�����ġ�bOrder���߼������ֵ���㣬���ʾ�������һ�����ļ����
#define	DIRITEM_LONGNAMELEN		0x100//���ļ�����󳤶�
typedef	struct						//FAT�ĳ��ļ���Ŀ¼��ṹ��
{
	BYTE	bOrder;					//���ļ���˳��
	WCHAR	wNamePart1[5];			//5���ַ��ĳ��ļ�����һ����
	BYTE	bAttribute;				//���ԣ�����ΪATTR_LONGNAME
	BYTE	bType;					//���ͣ�Ϊ0���ʾ���ǳ��ļ�����һ���ݣ�����ֵ����Ϊ������չʱ�á�
	BYTE	bChksum;				//У���
	WCHAR	wNamePart2[6];			//6���ַ��ĳ��ļ�����һ����
	WORD	wFirstClusLO;			//����Ϊ0
	WCHAR	wNamePart3[2];			//2���ַ��ĳ��ļ�����һ����
}FAT_LONGNAME;

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

void NewFAT12();	//��ʼ��FAT��
void NewRoot();		//��ʼ����Ŀ¼��
void NewData();		//��ʼ��������

WORD ReadFAT12Item(WORD wIndex);					//��FAT��
void WriteFAT12Item(WORD wIndex,WORD wValue);		//дFAT��

WORD FindFreeClus();								//Ѱ�ҿ��д�
FAT_DIRITEM* FindFreeRootItem();					//Ѱ�ҿ��и�Ŀ¼��
FAT_DIRITEM* FindFreeDirItem(WORD wDirClus);		//����Ŀ¼Ѱ�ҿ���Ŀ¼��

void* GetClusterPtr(WORD wCluster);					//ͨ���غ�ȡ����������ָ��

BYTE ShortNameCheckSum(BYTE *pFileName8_3);			//ȡ�ö��ļ�����У���

BOOL GenShortName(char *szLongName,WCHAR *wLongNameOut,char *szShortOut,char *szExtOut);//����һ�����ļ���
BOOL IsShortNameDupInRoot(char *szShort,char *szExt);//����ڸ�Ŀ¼����ļ����Ƿ��ظ�
BOOL IsShortNameDupInDir(WORD wDirClus,char *szShort,char *szExt);//�����Ŀ¼����ļ����Ƿ��ظ�

FAT_DIRITEM* RootCreateItem(char *szFile,BYTE bAttr);//�Ӹ�Ŀ¼������Ŀ¼��
FAT_DIRITEM* DirCreateItem(WORD wDirClus,char *szFile,BYTE bAttr);//����Ŀ¼����Ŀ¼��

#endif
