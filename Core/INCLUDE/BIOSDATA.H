#ifndef _BIOS_DATAAREA_STRUCTURE_INCLUDED_
#define	_BIOS_DATAAREA_STRUCTURE_INCLUDED_

#include"BTYPES.H"
#define	BIOSDATA_OFFSET		0x400			//BIOS��������λ��

typedef	struct
{
	WORD	COM1Port;						//COM�˿�
	WORD	COM2Port;
	WORD	COM3Port;
	WORD	COM4Port;
	WORD	LPT1Port;						//LPT��ӡ���˿�
	WORD	LPT2Port;
	WORD	LPT3Port;
	WORD	LPT4Port;
	WORD	Equipments;						//Ӳ����
	//λ��
	//0:		�Ƿ�װ������
	//1:		�Ƿ�װ��FPU
	//2-3:	ϵͳ��RAM��С��00=16K��01=32K��10=48K��11=64K
	//4-5:	��ʼ��ʾ��ʽ��00=AG��01=CGA-40��10=CGA-80��11=MDA-80
	//6-7:	��������
	//8:		DMA��־��0=��DMA
	//9-11:	COM������
	//12:	װ����Ϸ�ֱ�
	//13:	����MODEM�Ƿ�װ
	//14-15:	��ӡ����
	#define	BDE_FDDEXIST	0x0001
	#define	BDE_FPUEXIST	0x0002
	#define	BDE_NODMA		0x0100
	#define	BDE_GCEXIST		0x1000
	#define	BDE_MODEMEXIST	0x2000
	BYTE	ProductTest;					//��������
	//λ��
	//0:		���Ϊ0����ʹ��ģʽ������Ϊ��������ģʽ
	//����λδ�ã��������κ�ֵ��
	#define	BDP_TESTMODE	1
	WORD	MainRAMSize;					//���ڴ��С����KBΪ��λ
	WORD	IOChannelSize;					//IOͨ����С
	WORD	ShiftMode;						//����ģʽ
	//λ��
	//0:	��Shift����
	//1:	��Shift����
	//2:	Ctrl����
	//3:	Alt����
	//4:	Scroll Lock��
	//5:	Num Lock��
	//6:	Caps Lock��
	//7:	Insert��
	//8:	Ctrl�����ڱ�����
	//9:	��Alt�����ڱ�����
	//10:Sysrq�����ڱ�����
	//11:Pause�����ڱ�����
	//12:Scroll Lock�����ڱ�����
	//13:Num Lock�����ڱ�����
	//14:Caps Lock�����ڱ�����
	//15:Insert�����ڱ�����
	#define	BDS_RSHIFTDOWN		0x0001
	#define	BDS_LSHIFTDOWN		0x0002
	#define	BDS_CTRLDOWN		0x0004
	#define	BDS_ALTDOWN			0x0008
	#define	BDS_SCROLLLOCKON	0x0010
	#define	BDS_NUMLOCKON		0x0020
	#define	BDS_CAPSLOCKON		0x0040
	#define	BDS_INSERTON		0x0080
	#define	BDSE_CTRLDOWN		0x0100
	#define	BDSE_LALTDOWN		0x0200
	#define	BDSE_SYSRQDOWN		0x0400
	#define	BDSE_PAUSEDOWN		0x0800
	#define	BDSE_SCROLLLOCKDOWN	0x1000
	#define	BDSE_NUMLOCKDOWN	0x2000
	#define	BDSE_CAPSLOCKDOWN	0x4000
	#define	BDSE_INSERTDOWN		0x8000
	BYTE	VirtualKey;						//���û���סAlt����С�����������ֵ�ʱ�����ﱣ����ֵ���ɿ�Alt�������ֱ��0��ͬʱԭ��ֵ�����͵����̻�����
	WORD	KbdBufferStart;					//���̻�������ַ
	WORD	KbdBufferEnd;					//���̻�����βַ�����̻�����16�ַ������ֵ��ǰһ��ֵ�Ĳ���0-15��
	WORD	KbdBufferFIFO[16];				//���̻�����
	BYTE	DriverSeekStatus;				//��������������״̬
	//λ��
	//0:		������1����ҪУ׼��У׼=��ͷ�Ƶ��ŵ�0��
	//1:		������2����ҪУ׼
	//2:		������3����ҪУ׼
	//3:		������4����ҪУ׼
	//4-6:	����
	//7:		�жϱ�־
	#define	BDDS_DRV1OK		0x01
	#define	BDDS_DRV2OK		0x02
	#define	BDDS_DRV3OK		0x04
	#define	BDDS_DRV4OK		0x08
	#define	BDDS_INTERRUPT	0x80
	BYTE	DriverMotorStatus;				//�����������־
	//λ��
	//0:		������1��������ת
	//1:		������2��������ת
	//2:		������3��������ת
	//3:		������4��������ת
	//4-5:	ѡ�е�������
	//6:		����
	//7:		д����
	#define	BDDM_DRV1SPIN	0x01
	#define	BDDM_DRV2SPIN	0x02
	#define	BDDM_DRV3SPIN	0x04
	#define	BDDM_DRV4SPIN	0x08
	#define	BDDM_INTERRUPT	0x80
	BYTE	MotorTicksRemaining;			//����ʣ�µ�ת��ʱ������������ֹͣת��
	BYTE	LastDriverStatus;				//��һ�β�����״̬
	#define	BDL_OK					0x00	//û�д���
	#define	BDL_BADCOMMAND			0x01	//��Ч����
	#define	BDL_ADDRESSNOTFOUND		0x02	//��ַ�����
	#define	BDL_WRITEPROTECT		0x03	//��ͼд��д�����Ĵ���
	#define	BDL_SECTORNOTFOUND		0x04	//����û�ҵ�
	#define	BDL_DMAERROR			0x08	//DMA����
	#define	BDL_DMAERROR_64KBUF		0x09	//DMA���
	#define	BDL_BADMEDIATYPE		0x0C	//�������Ͳ���
	#define	BDL_CRCERROR			0x10	//CRC����
	#define	BDL_CONTROLLERERROR		0x20	//����������
	#define	BDL_SEEKFAILED			0x40	//����ʧ��
	#define	BDL_DISKTIMEOUT			0x80	//����û��Ӧ
	BYTE	ControllerStatusReg0;			//���̺����̿�����״̬�Ĵ���0
	//λ��
	//0-1:	�жϷ���ʱ��������
	//2:		�жϷ���ʱ��ͷ״̬
	//3:		������δ׼����
	//4:		����������
	//5:		������ҽ���
	//6-7:
	//	00:������������
	//	01:ִ�����������������
	//	10:��Ч����
	//	11:���������������ڶ�ʱ��������
	#define	BDR0_HEAD				0x04	//ͷ״̬����Ҳ��֪��ʲô��ͷ״̬��
	#define	BDR0_DRIVERNOTREADY		0x08	//������û׼����
	#define	BDR0_DRIVERERROR		0x10	//����������
	#define	BDR0_COMMANDSEEKEND		0x20	//������ҽ���
	#define	BDR0_NONNORMALEND		0x40	//����������
	#define	BDR0_INVALIDCOMMAND		0x80	//��Ч����
	BYTE	ControllerStatusReg1;			//���̺����̿�����״̬�Ĵ���1
	//λ��
	//0:		��ʧ��ַ��ǩ
	//1:		��ͼ��д�����Ĵ��̽��и�ʽ��
	//2:		�Ҳ����������ܶ�ȡ����ID��
	//3:		δ��
	//4:		DMA�������У�DMA̫�����¿�������ʱ��
	//5:		CRC����
	//6:		δʹ��
	//7:		��������ͼ�����������һ����֮�������
	#define	BDR1_LOSTADDRESSID		0x01	//��ʧ��ַ��ǩ
	#define	BDR1_FORMATWRITEPROTECT	0x02	//��ͼ��ʽ��д��������
	#define	BDR1_SECTORNOTFOUND		0x04	//�Ҳ�������
	#define	BDR1_RESERVED1			0x08	//δ��
	#define	BDR1_DMAOVERLOAD		0x10	//DMA���ص��³�ʱ
	#define	BDR1_CRCERROR			0x20	//CRC����
	#define	BDR1_RESERVED2			0x40	//δ��
	#define	BDR1_BADCYLINDERNUMBER	0x80	//����������
	BYTE	ControllerStatusReg2;			//���̺����̿�����״̬�Ĵ���2
	//λ��
	//0:		�Ҳ�����ַ��ǩ
	//1:		������
	//2:		����û�к��ʵ�����
	//3:		�����������
	//4:		����Ĵ���
	//5:		CRC����
	//6:		��ַ��ǩ��ɾ��
	//7:		δ��
	#define	BDR2_ADDRESSIDNOTFOUND	0x01	//�Ҳ�����ַ��ǩ
	#define	BDR2_BADCYLINDER		0x02	//������
	#define	BDR2_SECTORNOTFOUND		0x04	//������û�з�������������
	#define	BDR2_MEETEQUAL			0x08	//�����������
	#define	BDR2_READWRONGCYLINDER	0x10	//��ȡ�Ĵ�����ͬ�ڿ�����ָ���Ĵ���
	#define	BDR2_CRCERROR			0x20	//CRC����
	#define	BDR2_ADDRESSIDREMOVED	0x40	//�˶�����ʱ��⵽���ݵ�ַ��ǩ��ɾ��
	#define	BDR2_RESERVED			0x80	//δ��
	BYTE	ControllerStatusReg3;			//δ��
	BYTE	FDDHeadNumber;					//���̿����������һ�β����õ��Ĵ�ͷ��
	BYTE	FDDectorNumber;					//���̿����������һ�β����õ���������
	BYTE	FDDBytesWriteToSec;				//д��һ���������ֽ���
	BYTE	VideoMode;						//��Ƶģʽ
	BYTE	VideoRows;						//��Ƶ����������ǰ�ֱ���������ʾ��һ���ַ���
	BYTE	VideoBytesPerPage;				//��Ƶÿҳ�ֽ���
	BYTE	VideoPageOffset;				//��Ƶ��ǰҳƫ��
	BYTE	VideoPage0CursorY;				//��0ҳ���λ��
	BYTE	VideoPage0CursorX;
	BYTE	VideoPage1CursorY;				//��1ҳ���λ��
	BYTE	VideoPage1CursorX;
	BYTE	VideoPage2CursorY;				//��2ҳ���λ��
	BYTE	VideoPage2CursorX;
	BYTE	VideoPage3CursorY;				//��3ҳ���λ��
	BYTE	VideoPage3CursorX;
	BYTE	VideoPage4CursorY;				//��4ҳ���λ��
	BYTE	VideoPage4CursorX;
	BYTE	VideoPage5CursorY;				//��5ҳ���λ��
	BYTE	VideoPage5CursorX;
	BYTE	VideoPage6CursorY;				//��6ҳ���λ��
	BYTE	VideoPage6CursorX;
	BYTE	VideoPage7CursorY;				//��7ҳ���λ��
	BYTE	VideoPage7CursorX;
	BYTE	VideoCurScanLineEnd;			//�����״
	BYTE	VideoCurScanLineStart;
	#define	BDVCS_MAXSCANLINE	15
	#define	BDVCS_MINSCANLINE	0
	BYTE	VideoActivePage;				//�����ʾҳ
	BYTE	VideoIOBase;					//�˿ڻ���
	#define	BDVIOB_MGA_MONO		0x3B4
	#define	BDVIOB_HGA_MONO		0x3B4
	#define	BDVIOB_CGA_MONO		0x3D4
	#define	BDVIOB_EGA_MONO		0x3B4
	#define	BDVIOB_VGA_MONO		0x3B4
	#define	BDVIOB_SVG_MONO		0x3B4
	#define	BDVIOB_AXGA_MONO	0x3B4
	#define	BDVIOB_MGA_COLOR
	#define	BDVIOB_HGA_COLOR	0x3D4
	#define	BDVIOB_CGA_COLOR	0x3D4
	#define	BDVIOB_EGA_COLOR	0x3D4
	#define	BDVIOB_VGA_COLOR	0x3D4
	#define	BDVIOB_SVG_COLOR	0x3D4
	#define	BDVIOB_AXGA_COLOR	0x3D4
	BYTE	VideoInternalModeReg;				//�ڲ�ģʽ�Ĵ�����6845оƬ�ķ�ʽ�Ĵ�����ǰֵ���˿�0x3X8
	BYTE	VideoPalette;						//��ɫ�壬CGA�������˿�0x3X9
	//λ��
	//0:	��
	//1:	��
	//2:	��
	//3:	40x25�ı�ģʽ�¼�ǿ�߽�ɫ��ͼ��ģʽ5����ɫ
	//4:
	//	0:��ͨ����ɫ
	//	1:�ı�ģʽ��ǿ����ɫ
	//5:
	//	0:ģʽ5��ǰ��ɫ=�̺��
	//	1:ģʽ5��ǰ��ɫ=��۰�
	//6:	δ��
	//7:	δ��
	#define	BDVP_BLUE			0x01
	#define	BDVP_GREEN			0x02
	#define	BDVP_RED			0x04
	#define	BDVP_BCOL			0x08
	#define	BDVP_EXBGCOLOR		0x10
	#define	BDVP_MODE5USEBLUE	0x20
	DWORD	ReturnToRealModePtr;				//ATƽ̨�������ص�ʵģʽ����תָ�룬PCƽ̨�Ŵ�������״̬
	BYTE	LastIRQNumber;						//���һ��IRQ��
	//λ��
	//0:	������IRQ0�ж�
	//1:	������IRQ1�ж�
	//2:	������IRQ2�ж�
	//3:	������IRQ3�ж�
	//4:	������IRQ4�ж�
	//5:	������IRQ5�ж�
	//6:	������IRQ6�ж�
	//7:	������IRQ7�ж�
	#define	BDLI_IRQ0			0x01
	#define	BDLI_IRQ1			0x02			//IRQ8-15
	#define	BDLI_IRQ2			0x04
	#define	BDLI_IRQ3			0x08
	#define	BDLI_IRQ4			0x10
	#define	BDLI_IRQ5			0x20
	#define	BDLI_IRQ6			0x40
	#define	BDLI_IRQ7			0x80
	DWORD	TimeTick;							//ʱ�ӵδ������IRQ0�жϵ������ֵ
	DWORD	TimeTickFlip;						//ʱ�ӵδ��������һ��֮���ֵ��1����ֵֻ������ֵ��0,1
	#define	BDTT_FLIP			0x01
	BYTE	KbdCtrlBreak;						//���̰���Ctrl+Break֮���ֵ��7λ������
	#define	BDCB_SET			0x80
	WORD	HotStart;							//��������ʶ�����ֵΪ0x1234��Ϊ��������ֵΪ0x5678Ϊϵͳ��ֹ��ֵΪ0x9ABC��0x0064Ϊ��������
	#define	BDHS_HOTSTART		0x1234
	#define	BDHS_SYSHALT		0x5678
	#define	BDHS_PRODTEST1		0x9ABC
	#define	BDHS_PRODTEST2		0x0064
	BYTE	HDDLastOperation;					//Ӳ�����һ�β�����״̬
	#define	BDHDD_SUCCESS				0x00	//�ɹ�
	#define	BDHDD_BADCOMMAND			0x01	//����������
	#define	BDHDD_LOSTADDRESSID			0x02	//��ʧ��ַ��ǩ
	#define	BDHDD_RMWRITEPROTECT		0x03	//������ý���д����
	#define	BDHDD_SECTORNOTFOUND		0x04	//����û�ҵ�
	#define	BDHDD_RESTARTFAILED			0x05	//����ʧ��
	#define	BDHDD_RMCHANGED				0x06	//������ý����̸ı�
	#define	BDHDD_DRIVERPARAMFAILED		0x07	//�������������ʧ��
	#define	BDHDD_DMAOVERLOAD			0x08	//DMA����
	#define	BDHDD_DATABOUNDERROR		0x09	//���ݱ߽����
	#define	BDHDD_BADSECTOR				0x0A	//��⵽������
	#define	BDHDD_BADTRACK				0x0B	//��⵽���ŵ�
	#define	BDHDD_FORMATILLEGALSEC		0x0D	//��ʽ��ʱ���������Ϸ�
	#define	BDHDD_DATAIDDETECTED		0x0E	//��⵽�����ݿ��Ʊ�ǩ
	#define	BDHDD_DMAARBTRANSBOUND		0x0F	//DMA�ٲ�ˮƽԽ��
	#define	BDHDD_READECCERROR			0x10	//��ȡʱ������ECC����
	#define	BDHDD_ECCCORRECTERROR		0x11	//ECC�������ݴ���
	#define	BDHDD_DRIVERPROBLEM			0x20	//��������������������
	#define	BDHDD_RMNOMEDIA				0x31	//��������������ý��
	#define	BDHDD_SEEKERROR				0x40	//���Ҳ���ʧ��
	#define	BDHDD_TIMEOUT				0x80	//��ʱ
	#define	BDHDD_DRIVERNOTREADY		0xAA	//������û��׼����
	#define	BDHDD_DISKGROUPNOTLOCKED	0xB0	//�������ڵĴ�����û��ס
	#define	BDHDD_LOCKEDDISKGROUP		0xB1	//��ס���������ڵĴ�����
	#define	BDHDD_UNMOVABLEDISKGROUP	0xB2	//�����ƶ�������
	#define	BDHDD_USINGDISKGROUP		0xB3	//����ʹ�ô�����
	#define	BDHDD_LOCKCNTTRANSBOUNDARY	0xB4	//������Խ��
	#define	BDHDD_VALIDEJECTFAILED		0xB5	//��Ч�ĵ�������ʧ��
	#define	BDHDD_UNDEFINEDERROR		0xBB	//δ�������
	#define	BDHDD_WRITEERROR			0xCC	//д����
	#define	BDHDD_NOERROR				0xE0	//������̬�����ʶ�����ƴ���������Ϊ0
	#define	BDHDD_SENSINGFAILED			0xFF	//���в���ʧ��
	DWORD	HDDCount;							//Ӳ����Ŀ
	DWORD	HDDControlByte;						//Ӳ�̿����ֽ�
	//λ��
	//0:	δʹ��
	//1:	δʹ��
	//2:	δʹ��
	//3:	��������8�����ϴ�ͷ
	//4:	δʹ��
	//5:	δʹ��
	//6:	���̳���ʱ��ֹ����
	//7:	���̳���ʱ��ֹ����
	#define	BDHDDC_MORE8HEADS	0x08
	#define	BDHDDC_DONOTRETRY	0xC0
	BYTE	HDDOffset;					//Ӳ��ƫ����
	BYTE	LPT1TimeOut;				//��ӡ����ʱ��ʱ����
	BYTE	LPT2TimeOut;
	BYTE	LPT3TimeOut;
	BYTE	LPT4TimeOut;
	BYTE	COM1TimeOut;				//���пڳ�ʱ��ʱ����
	BYTE	COM2TimeOut;
	BYTE	COM3TimeOut;
	BYTE	COM4TimeOut;
	BYTE	KbdBufferStart2;			//���̻��������
	BYTE	KbdBufferEnd2;				//���̻������յ�
	BYTE	VideoLines;					//��Ļ��ʾ�ַ�������
	BYTE	VideoScanLinesPerChar;		//ÿ�ַ���ɨ������
	BYTE	VideoOptions;				//��Ƶѡ��
	//λ��
	//0:		���CGAģ��
	//	�ο�INT 0x10 AH=0x12
	//1:
	//	0:������ɫ��ʾ����ʹ�ö˿�0x3DX��
	//	1:������ɫ��ʾ����ʹ�ö˿�0x3BX��
	//2:		�ȴ���ʾ����
	//3:		��Ƶ����������
	//4:		δ��
	//5-6:	�Դ��С
	//	00:64K
	//	01:128K
	//	10:192K
	//	11:256K�����
	//7:		������Ƶģʽʱ������Դ�
	#define	BDVO_CURCGAEMU			0x01
	#define	BDVO_HASMONOMONITOR		0x02
	#define	BDVO_WAITFORDISPLAYOPEN	0x04
	#define	BDVO_VIDEOADAPTERACTIVE	0x08
	#define	BDVO_DONOTCLEARVRAM		0x80
	BYTE	VideoSwitches;				//��Ƶ����
	//λ��
	//0-3:	���������Ϳ�������
	//	λ3210 ��				��
	//	  0000:MDA				��ɫ40x25
	//	  0001:MDA				��ɫ80x25
	//	  0010:MDA				�߷ֱ���80x25
	//	  0011:MDA				�߷ֱ�����ǿ
	//	  0100:CGA40x25			��ɫ
	//	  0101:CGA80x25			��ɫ
	//	  0110:��ɫ40x25		MDA
	//	  0111:��ɫ80x25		MDA
	//	  1000:�߷ֱ���80x25	MDA
	//	  1001:�߷ֱ�����ǿ		MDA
	//	  1010:��ɫ				CGA40x25
	//	  1011:��ɫ				CGA80x25
	//	  1100:δʹ��
	//	  1101:δʹ��
	//	  1110:δʹ��
	//	  1111:δʹ��
	//4:		���״̬Ϊ1ʱ����������������1�ߵ�ֵ
	//5:		���״̬Ϊ1ʱ����������������0�ߵ�ֵ
	//6:		���״̬Ϊ0ʱ����������������1�ߵ�ֵ
	//7:		���״̬Ϊ0ʱ����������������0�ߵ�ֵ
	BYTE	VideoSaveArea1;				//��Ƶ������1
	//λ��
	//0:	������ʾ��֧������ģʽ
	//1:
	//	0:����ɫ��
	//	1:��ɫ��ת��Ϊ�Ҷ�ֵ
	//2:
	//	0:������ɫ��ʾ��
	//	1:������ɫ��ʾ��
	//3:
	//	0:����ģʽʱ�ָ���ɫ��ΪĬ��ֵ
	//	1:����ģʽʱ���ı��ɫ��
	//4:
	//	0:ɨ����200��350
	//	1:ɨ����400
	//5:	δ��
	//6:	ĳЩBIOS����
	//7:
	//	0:ɨ����350��400
	//	1:ɨ����200
	BYTE	VideoSaveArea2;				//��Ƶ������2
	BYTE	FDDSettings;				//�����趨
	//λ��
	//0:		δ��
	//1:		δ��
	//2-3:	��������
	//	00:500Kbps
	//	01:300Kbps
	//	10:250Kbps
	//	11:1Mbps
	//4-5:	�͵����̿������������������������
	//	00:8ms
	//	01:7ms
	//	10:6ms
	//	11:5ms
	//6-7:	�͵����̿����������������
	//	00:500Kbps
	//	01:300Kbps
	//	10:250Kbps
	//	11:δ�������ʻ�1Mbps
	BYTE	HDDStatus;					//Ӳ��״̬���˿�0x1F7��ֵ
	BYTE	HDDError;					//Ӳ�̴��󣬶˿�0x1F1��ֵ
	BYTE	HDDComplete;				//Ӳ�̲�����ɺ��ֵΪ0xFF��Ӳ�̿�ʼ����ʱֵΪ0
	BYTE	FDDControllerInfo;			//���̿�������Ϣ
	//λ��
	//0:	������0���ı�����
	//1:	������0�Ƕ����ʵ�
	//2:	ȷ����������0������
	//3:	δ��
	//4:	������1���ı�����
	//5:	������1�Ƕ����ʵ�
	//6:	ȷ����������1������
	//7:	δ��
	#define	BDFDDCI_DRV0CHANGELINE		0x01
	#define	BDFDDCI_DRV0MULTIRATE		0x02
	#define	BDFDDCI_DRV0TYPECONFIRMED	0x04
	#define	BDFDDCI_DRV1CHANGELINE		0x10
	#define	BDFDDCI_DRV1MULTIRATE		0x20
	#define	BDFDDCI_DRV1TYPECONFIRMED	0x40
	BYTE	FDD0MediaStatus;			//����0����״̬
	BYTE	FDD1MediaStatus;			//����1����״̬
	//λ��
	//0-2:	ȷ���ϴη���
	//	000:��360K������������360K�Ľ���
	//	001:��1.2M������������360K�Ľ���
	//	010:��1.2M������������360K�Ľ���
	//	011:��360K������������֪360K�Ľ���
	//	100:��1.2M������������֪360K�Ľ���
	//	101:��1.2M������������֪1.2M�Ľ���
	//	110:δʹ��״̬
	//	111:��720K������������720K�Ľ��ʻ�1.44M������������1.44M�Ľ���
	//3:		δʹ��
	//4:		��֪�����еĽ���
	//5:		Ҫ��˫��������1.2M��������360K���̣�
	//6-7:	���ݴ�����
	//	00:500Kbps
	//	01:300Kbps
	//	10:250Kbps
	//	11:1Mbps
	#define	BDFDDMS_MEDIACONFIRMED		0x10
	#define	BDFDDMS_DOUBLESPEED			0x20
	BYTE	FDD0OperationStartStatus;	//����0������ʼ״̬
	BYTE	FDD1OperationStartStatus;	//����1������ʼ״̬
	//λ��
	//0:		���������ı�����
	//1:		�������Ƕ����ʵ�
	//2:		ȷ����������������
	//3:		δ��
	//4:		δ֪����
	//5:		δ֪����
	//6-7:
	//	00:500Kbps
	//	01:300Kbps
	//	10:250Kbps
	//	11:1Mbps
	#define	BDFDDOSS_DRV0CHANGELINE		0x01
	#define	BDFDDOSS_DRV0MULTIRATE		0x02
	#define	BDFDDOSS_DRV0TYPECONFIRMED	0x04
	BYTE	FDD0CurCylinder;					//����0��ǰ����
	BYTE	FDD1CurCylinder;					//����1��ǰ����
	BYTE	KbdStatus3;							//����״̬��־3
	//λ��
	//0:	��װ�˼���
	//1:
	//	0:ɨ������0xE1ʱ���øñ�־���Ӽ��̶�ȡ��һ���ֽ�
	//	1:ɨ������0xE0ʱ���øñ�־���Ӽ��̶�ȡ��һ���ֽ�
	//2:	��������Ctrl
	//3:	��������Alt
	//4:	101����104������
	//5:	ȡ�ü���ID����������ǿ��Num-Lock
	//6:	�ϴ������һ�������ֽ���ID�ĵ�һ���ַ������ڶ�ȡ�ڶ���
	//7:	���ڶ�ȡID�����ֽ�
	#define	BDKS3_KBDINSTALLED			0x01
	#define	BDKS3_SCE0SETFLAGANDREAD	0x02
	#define	BDKS3_RCTRLDOWN				0x04
	#define	BDKS3_RALTDOWN				0x08
	#define	BDKS3_101OR104KBD			0x10
	#define	BDKS3_SETNUMLOCKWHENGETID	0x20
	#define	BDKS3_LASTISFCOFIDNOWREAD	0x40
	#define	BDKS3_READING2BYTEID		0x80
	BYTE	KbdStatus4;					//����״̬��־4
	//λ��
	//0:	Scroll Lock��
	//1:	Num Lock��
	//2: Caps Lock��
	//3:	δ��
	//4:	���̷�����һ��ACK��0xFA
	//5:	���̷�����һ�����ط�����0xFE
	//6:	�����и�����LED
	//7:	���̴��ʹ�
	#define	BDKS4_SCROLLLOCKON			0x01
	#define	BDKS4_NUMLOCKON				0x02
	#define	BDKS4_CAPSLOCKON			0x04
	#define	BDKS4_RESERVED				0x08
	#define	BDKS4_KBDACK				0x10
	#define	BDKS4_KBDWANTAGAIN			0x20
	#define	BDKS4_UPDATELED				0x40
	#define	BDKS4_KBDERROR				0x80
	DWORD	UserTimerPointer;					//�û��ȴ���־ָ��
	DWORD	UserWaitCount;						//�û��ȴ�������������ʱ
	BYTE	WaitFlag;							//�ȴ���־
	//λ��
	//0:		���ڵȴ�
	//1-6:	δʹ��
	//7:		�ȴ�ʱ�䵽��
	#define	BDWF_WAITING	0x01
	#define	BDWF_EXPIRE		0x80
	BYTE	LocalNetworkBytes[7];	//�������ֽ�
	DWORD	VideoParamsControlPtr;	//��Ƶ�������ƿ�ָ�룬������档
	BYTE	DaysFrom1980;			//��1980�굽���ڵ�����
	BYTE	PrintScreenStatus;		//��ӡ��Ļ״̬
	#define	BDPSS_READY		0x00	//׼����
	#define	BDPSS_PRINTING	0x01	//���ڴ�ӡ
	#define	BDPSS_ERROR		0xFF	//ȱֽ����ӡ�����󡢳�ʱ��
}BIOSDATA;

typedef	struct//��Ƶ�������ƿ�
{
	DWORD	VideoParam;			//��Ƶ����
	DWORD	ParamSaveArea;		//����������
	DWORD	AlNumCharset;		//��ĸ�����ַ���
	DWORD	GraphicsCharset;	//ͼ���ַ���
	DWORD	SecondSaveAreaPtr;	//�ڶ��������ָ��
	DWORD	Unused[2];			//δ��
}VideoParamsControl;

typedef	struct
{
	WORD	StructSize;			//�ṹ���С
	DWORD	CombinePresentCode;	//��ϴ�����
	DWORD	SecondAlNumCharset;	//�ڶ�����ĸ�����ַ���
	DWORD	UserPaletteTable;	//�û���ɫ���
	DWORD	Unused[3];			//δ��
}SecondSaveArea;

#endif