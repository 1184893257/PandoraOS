#ifndef _BIOS_DATAAREA_STRUCTURE_INCLUDED_
#define	_BIOS_DATAAREA_STRUCTURE_INCLUDED_

#include"BTYPES.H"
#define	BIOSDATA_OFFSET		0x400			//BIOS数据区的位置

typedef	struct
{
	WORD	COM1Port;						//COM端口
	WORD	COM2Port;
	WORD	COM3Port;
	WORD	COM4Port;
	WORD	LPT1Port;						//LPT打印机端口
	WORD	LPT2Port;
	WORD	LPT3Port;
	WORD	LPT4Port;
	WORD	Equipments;						//硬件表
	//位：
	//0:		是否安装了软驱
	//1:		是否安装了FPU
	//2-3:	系统板RAM大小，00=16K，01=32K，10=48K，11=64K
	//4-5:	初始显示方式，00=AG，01=CGA-40，10=CGA-80，11=MDA-80
	//6-7:	软驱数量
	//8:		DMA标志，0=有DMA
	//9-11:	COM口数量
	//12:	装了游戏手柄
	//13:	内置MODEM是否安装
	//14-15:	打印机数
	#define	BDE_FDDEXIST	0x0001
	#define	BDE_FPUEXIST	0x0002
	#define	BDE_NODMA		0x0100
	#define	BDE_GCEXIST		0x1000
	#define	BDE_MODEMEXIST	0x2000
	BYTE	ProductTest;					//生产测试
	//位：
	//0:		如果为0则是使用模式，否则为生产测试模式
	//其它位未用，可能是任何值。
	#define	BDP_TESTMODE	1
	WORD	MainRAMSize;					//主内存大小，以KB为单位
	WORD	IOChannelSize;					//IO通道大小
	WORD	ShiftMode;						//换挡模式
	//位：
	//0:	右Shift按下
	//1:	左Shift按下
	//2:	Ctrl按下
	//3:	Alt按下
	//4:	Scroll Lock打开
	//5:	Num Lock打开
	//6:	Caps Lock打开
	//7:	Insert打开
	//8:	Ctrl键正在被按下
	//9:	左Alt键正在被按下
	//10:Sysrq键正在被按下
	//11:Pause键正在被按下
	//12:Scroll Lock键正在被按下
	//13:Num Lock键正在被按下
	//14:Caps Lock键正在被按下
	//15:Insert键正在被按下
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
	BYTE	VirtualKey;						//当用户按住Alt并从小键盘输入数字的时候这里保存数值。松开Alt则这里又变成0，同时原数值被发送到键盘缓冲区
	WORD	KbdBufferStart;					//键盘缓冲区首址
	WORD	KbdBufferEnd;					//键盘缓冲区尾址（键盘缓冲区16字符，这个值与前一个值的差在0-15）
	WORD	KbdBufferFIFO[16];				//键盘缓冲区
	BYTE	DriverSeekStatus;				//磁盘驱动器搜索状态
	//位：
	//0:		驱动器1不需要校准（校准=磁头移到磁道0）
	//1:		驱动器2不需要校准
	//2:		驱动器3不需要校准
	//3:		驱动器4不需要校准
	//4-6:	保留
	//7:		中断标志
	#define	BDDS_DRV1OK		0x01
	#define	BDDS_DRV2OK		0x02
	#define	BDDS_DRV3OK		0x04
	#define	BDDS_DRV4OK		0x08
	#define	BDDS_INTERRUPT	0x80
	BYTE	DriverMotorStatus;				//驱动器马达标志
	//位：
	//0:		驱动器1马达正在转
	//1:		驱动器2马达正在转
	//2:		驱动器3马达正在转
	//3:		驱动器4马达正在转
	//4-5:	选中的驱动器
	//6:		保留
	//7:		写操作
	#define	BDDM_DRV1SPIN	0x01
	#define	BDDM_DRV2SPIN	0x02
	#define	BDDM_DRV3SPIN	0x04
	#define	BDDM_DRV4SPIN	0x08
	#define	BDDM_INTERRUPT	0x80
	BYTE	MotorTicksRemaining;			//马达剩下的转动时钟数，归零则停止转动
	BYTE	LastDriverStatus;				//上一次操作的状态
	#define	BDL_OK					0x00	//没有错误
	#define	BDL_BADCOMMAND			0x01	//无效命令
	#define	BDL_ADDRESSNOTFOUND		0x02	//地址标记损坏
	#define	BDL_WRITEPROTECT		0x03	//试图写带写保护的磁盘
	#define	BDL_SECTORNOTFOUND		0x04	//扇区没找到
	#define	BDL_DMAERROR			0x08	//DMA错误
	#define	BDL_DMAERROR_64KBUF		0x09	//DMA溢出
	#define	BDL_BADMEDIATYPE		0x0C	//介质类型不对
	#define	BDL_CRCERROR			0x10	//CRC错误
	#define	BDL_CONTROLLERERROR		0x20	//控制器错误
	#define	BDL_SEEKFAILED			0x40	//查找失败
	#define	BDL_DISKTIMEOUT			0x80	//磁盘没反应
	BYTE	ControllerStatusReg0;			//磁盘和软盘控制器状态寄存器0
	//位：
	//0-1:	中断发生时的驱动器
	//2:		中断发生时的头状态
	//3:		驱动器未准备好
	//4:		驱动器错误
	//5:		命令查找结束
	//6-7:
	//	00:命令正常结束
	//	01:执行中命令非正常结束
	//	10:无效命令
	//	11:非正常结束，正在读时更换软盘
	#define	BDR0_HEAD				0x04	//头状态（我也不知道什么叫头状态）
	#define	BDR0_DRIVERNOTREADY		0x08	//驱动器没准备好
	#define	BDR0_DRIVERERROR		0x10	//驱动器错误
	#define	BDR0_COMMANDSEEKEND		0x20	//命令查找结束
	#define	BDR0_NONNORMALEND		0x40	//非正常结束
	#define	BDR0_INVALIDCOMMAND		0x80	//无效命令
	BYTE	ControllerStatusReg1;			//磁盘和软盘控制器状态寄存器1
	//位：
	//0:		丢失地址标签
	//1:		试图给写保护的磁盘进行格式化
	//2:		找不到扇区或不能读取磁盘ID区
	//3:		未用
	//4:		DMA过载运行（DMA太慢导致控制器超时）
	//5:		CRC错误
	//6:		未使用
	//7:		控制器试图访问软盘最后一磁柱之外的扇区
	#define	BDR1_LOSTADDRESSID		0x01	//丢失地址标签
	#define	BDR1_FORMATWRITEPROTECT	0x02	//试图格式化写保护磁盘
	#define	BDR1_SECTORNOTFOUND		0x04	//找不到扇区
	#define	BDR1_RESERVED1			0x08	//未用
	#define	BDR1_DMAOVERLOAD		0x10	//DMA过载导致超时
	#define	BDR1_CRCERROR			0x20	//CRC错误
	#define	BDR1_RESERVED2			0x40	//未用
	#define	BDR1_BADCYLINDERNUMBER	0x80	//错误的柱面号
	BYTE	ControllerStatusReg2;			//磁盘和软盘控制器状态寄存器2
	//位：
	//0:		找不到地址标签
	//1:		坏磁柱
	//2:		磁柱没有合适的扇区
	//3:		满足相等条件
	//4:		错误的磁柱
	//5:		CRC错误
	//6:		地址标签被删除
	//7:		未用
	#define	BDR2_ADDRESSIDNOTFOUND	0x01	//找不到地址标签
	#define	BDR2_BADCYLINDER		0x02	//坏磁柱
	#define	BDR2_SECTORNOTFOUND		0x04	//磁柱上没有符合条件的扇区
	#define	BDR2_MEETEQUAL			0x08	//满足相等条件
	#define	BDR2_READWRONGCYLINDER	0x10	//读取的磁柱不同于控制器指定的磁柱
	#define	BDR2_CRCERROR			0x20	//CRC错误
	#define	BDR2_ADDRESSIDREMOVED	0x40	//核对数据时检测到数据地址标签被删除
	#define	BDR2_RESERVED			0x80	//未用
	BYTE	ControllerStatusReg3;			//未用
	BYTE	FDDHeadNumber;					//软盘控制器的最后一次操作用到的磁头号
	BYTE	FDDectorNumber;					//软盘控制器的最后一次操作用到的扇区号
	BYTE	FDDBytesWriteToSec;				//写入一个扇区的字节数
	BYTE	VideoMode;						//视频模式
	BYTE	VideoRows;						//视频列数，即当前分辨率下能显示的一行字符数
	BYTE	VideoBytesPerPage;				//视频每页字节数
	BYTE	VideoPageOffset;				//视频当前页偏移
	BYTE	VideoPage0CursorY;				//第0页光标位置
	BYTE	VideoPage0CursorX;
	BYTE	VideoPage1CursorY;				//第1页光标位置
	BYTE	VideoPage1CursorX;
	BYTE	VideoPage2CursorY;				//第2页光标位置
	BYTE	VideoPage2CursorX;
	BYTE	VideoPage3CursorY;				//第3页光标位置
	BYTE	VideoPage3CursorX;
	BYTE	VideoPage4CursorY;				//第4页光标位置
	BYTE	VideoPage4CursorX;
	BYTE	VideoPage5CursorY;				//第5页光标位置
	BYTE	VideoPage5CursorX;
	BYTE	VideoPage6CursorY;				//第6页光标位置
	BYTE	VideoPage6CursorX;
	BYTE	VideoPage7CursorY;				//第7页光标位置
	BYTE	VideoPage7CursorX;
	BYTE	VideoCurScanLineEnd;			//光标形状
	BYTE	VideoCurScanLineStart;
	#define	BDVCS_MAXSCANLINE	15
	#define	BDVCS_MINSCANLINE	0
	BYTE	VideoActivePage;				//活动的显示页
	BYTE	VideoIOBase;					//端口基号
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
	BYTE	VideoInternalModeReg;				//内部模式寄存器，6845芯片的方式寄存器当前值，端口0x3X8
	BYTE	VideoPalette;						//调色板，CGA适配器端口0x3X9
	//位：
	//0:	蓝
	//1:	绿
	//2:	红
	//3:	40x25文本模式下加强边界色，图形模式5背景色
	//4:
	//	0:普通背景色
	//	1:文本模式加强背景色
	//5:
	//	0:模式5的前景色=绿红黄
	//	1:模式5的前景色=青粉白
	//6:	未用
	//7:	未用
	#define	BDVP_BLUE			0x01
	#define	BDVP_GREEN			0x02
	#define	BDVP_RED			0x04
	#define	BDVP_BCOL			0x08
	#define	BDVP_EXBGCOLOR		0x10
	#define	BDVP_MODE5USEBLUE	0x20
	DWORD	ReturnToRealModePtr;				//AT平台重启、回到实模式的跳转指针，PC平台磁带控制器状态
	BYTE	LastIRQNumber;						//最后一个IRQ号
	//位：
	//0:	发生了IRQ0中断
	//1:	发生了IRQ1中断
	//2:	发生了IRQ2中断
	//3:	发生了IRQ3中断
	//4:	发生了IRQ4中断
	//5:	发生了IRQ5中断
	//6:	发生了IRQ6中断
	//7:	发生了IRQ7中断
	#define	BDLI_IRQ0			0x01
	#define	BDLI_IRQ1			0x02			//IRQ8-15
	#define	BDLI_IRQ2			0x04
	#define	BDLI_IRQ3			0x08
	#define	BDLI_IRQ4			0x10
	#define	BDLI_IRQ5			0x20
	#define	BDLI_IRQ6			0x40
	#define	BDLI_IRQ7			0x80
	DWORD	TimeTick;							//时钟滴答计数，IRQ0中断递增这个值
	DWORD	TimeTickFlip;						//时钟滴答计数超过一天之后此值置1。此值只有两个值，0,1
	#define	BDTT_FLIP			0x01
	BYTE	KbdCtrlBreak;						//键盘按下Ctrl+Break之后此值第7位被设置
	#define	BDCB_SET			0x80
	WORD	HotStart;							//热启动标识，如果值为0x1234则为热启动，值为0x5678为系统终止，值为0x9ABC或0x0064为生产测试
	#define	BDHS_HOTSTART		0x1234
	#define	BDHS_SYSHALT		0x5678
	#define	BDHS_PRODTEST1		0x9ABC
	#define	BDHS_PRODTEST2		0x0064
	BYTE	HDDLastOperation;					//硬盘最后一次操作的状态
	#define	BDHDD_SUCCESS				0x00	//成功
	#define	BDHDD_BADCOMMAND			0x01	//坏命令或参数
	#define	BDHDD_LOSTADDRESSID			0x02	//丢失地址标签
	#define	BDHDD_RMWRITEPROTECT		0x03	//可移走媒介的写保护
	#define	BDHDD_SECTORNOTFOUND		0x04	//扇区没找到
	#define	BDHDD_RESTARTFAILED			0x05	//重启失败
	#define	BDHDD_RMCHANGED				0x06	//可移走媒介磁盘改变
	#define	BDHDD_DRIVERPARAMFAILED		0x07	//驱动器参数活动性失败
	#define	BDHDD_DMAOVERLOAD			0x08	//DMA过载
	#define	BDHDD_DATABOUNDERROR		0x09	//数据边界错误
	#define	BDHDD_BADSECTOR				0x0A	//检测到坏扇区
	#define	BDHDD_BADTRACK				0x0B	//检测到坏磁道
	#define	BDHDD_FORMATILLEGALSEC		0x0D	//格式化时扇区数不合法
	#define	BDHDD_DATAIDDETECTED		0x0E	//检测到了数据控制标签
	#define	BDHDD_DMAARBTRANSBOUND		0x0F	//DMA仲裁水平越界
	#define	BDHDD_READECCERROR			0x10	//读取时出现了ECC错误
	#define	BDHDD_ECCCORRECTERROR		0x11	//ECC纠正数据错误
	#define	BDHDD_DRIVERPROBLEM			0x20	//驱动器、控制器出问题
	#define	BDHDD_RMNOMEDIA				0x31	//可移走驱动器无媒介
	#define	BDHDD_SEEKERROR				0x40	//查找操作失败
	#define	BDHDD_TIMEOUT				0x80	//超时
	#define	BDHDD_DRIVERNOTREADY		0xAA	//驱动器没有准备好
	#define	BDHDD_DISKGROUPNOTLOCKED	0xB0	//驱动器内的磁盘组没锁住
	#define	BDHDD_LOCKEDDISKGROUP		0xB1	//锁住了驱动器内的磁盘组
	#define	BDHDD_UNMOVABLEDISKGROUP	0xB2	//不可移动磁盘组
	#define	BDHDD_USINGDISKGROUP		0xB3	//正在使用磁盘组
	#define	BDHDD_LOCKCNTTRANSBOUNDARY	0xB4	//锁计数越界
	#define	BDHDD_VALIDEJECTFAILED		0xB5	//有效的弹出请求失败
	#define	BDHDD_UNDEFINEDERROR		0xBB	//未定义错误
	#define	BDHDD_WRITEERROR			0xCC	//写错误
	#define	BDHDD_NOERROR				0xE0	//设置了态错误标识，控制错误码设置为0
	#define	BDHDD_SENSINGFAILED			0xFF	//传感操作失败
	DWORD	HDDCount;							//硬盘数目
	DWORD	HDDControlByte;						//硬盘控制字节
	//位：
	//0:	未使用
	//1:	未使用
	//2:	未使用
	//3:	驱动器有8个以上磁头
	//4:	未使用
	//5:	未使用
	//6:	磁盘出错时禁止重试
	//7:	磁盘出错时禁止重试
	#define	BDHDDC_MORE8HEADS	0x08
	#define	BDHDDC_DONOTRETRY	0xC0
	BYTE	HDDOffset;					//硬盘偏移量
	BYTE	LPT1TimeOut;				//打印机超时的时间量
	BYTE	LPT2TimeOut;
	BYTE	LPT3TimeOut;
	BYTE	LPT4TimeOut;
	BYTE	COM1TimeOut;				//串行口超时的时间量
	BYTE	COM2TimeOut;
	BYTE	COM3TimeOut;
	BYTE	COM4TimeOut;
	BYTE	KbdBufferStart2;			//键盘缓冲区起点
	BYTE	KbdBufferEnd2;				//键盘缓冲区终点
	BYTE	VideoLines;					//屏幕显示字符的行数
	BYTE	VideoScanLinesPerChar;		//每字符的扫描行数
	BYTE	VideoOptions;				//视频选项
	//位：
	//0:		光标CGA模拟
	//	参看INT 0x10 AH=0x12
	//1:
	//	0:附带彩色显示器（使用端口0x3DX）
	//	1:附带单色显示器（使用端口0x3BX）
	//2:		等待显示开放
	//3:		视频适配器激活
	//4:		未用
	//5-6:	显存大小
	//	00:64K
	//	01:128K
	//	10:192K
	//	11:256K或更多
	//7:		设置视频模式时不清除显存
	#define	BDVO_CURCGAEMU			0x01
	#define	BDVO_HASMONOMONITOR		0x02
	#define	BDVO_WAITFORDISPLAYOPEN	0x04
	#define	BDVO_VIDEOADAPTERACTIVE	0x08
	#define	BDVO_DONOTCLEARVRAM		0x80
	BYTE	VideoSwitches;				//视频开关
	//位：
	//0-3:	适配器类型开关设置
	//	位3210 主				次
	//	  0000:MDA				彩色40x25
	//	  0001:MDA				彩色80x25
	//	  0010:MDA				高分辨率80x25
	//	  0011:MDA				高分辨率增强
	//	  0100:CGA40x25			单色
	//	  0101:CGA80x25			单色
	//	  0110:彩色40x25		MDA
	//	  0111:彩色80x25		MDA
	//	  1000:高分辨率80x25	MDA
	//	  1001:高分辨率增强		MDA
	//	  1010:单色				CGA40x25
	//	  1011:单色				CGA80x25
	//	  1100:未使用
	//	  1101:未使用
	//	  1110:未使用
	//	  1111:未使用
	//4:		输出状态为1时特性连接器上特性1线的值
	//5:		输出状态为1时特性连接器上特性0线的值
	//6:		输出状态为0时特性连接器上特性1线的值
	//7:		输出状态为0时特性连接器上特性0线的值
	BYTE	VideoSaveArea1;				//视频保存区1
	//位：
	//0:	附带显示器支持所有模式
	//1:
	//	0:正常色彩
	//	1:调色板转化为灰度值
	//2:
	//	0:附带彩色显示器
	//	1:附带单色显示器
	//3:
	//	0:设置模式时恢复调色板为默认值
	//	1:设置模式时不改变调色板
	//4:
	//	0:扫描线200或350
	//	1:扫描线400
	//5:	未用
	//6:	某些BIOS不用
	//7:
	//	0:扫描线350或400
	//	1:扫描线200
	BYTE	VideoSaveArea2;				//视频保存区2
	BYTE	FDDSettings;				//软盘设定
	//位：
	//0:		未用
	//1:		未用
	//2-3:	数据速率
	//	00:500Kbps
	//	01:300Kbps
	//	10:250Kbps
	//	11:1Mbps
	//4-5:	送到软盘控制器的最后驱动器步进速率
	//	00:8ms
	//	01:7ms
	//	10:6ms
	//	11:5ms
	//6-7:	送到软盘控制器的最后数据率
	//	00:500Kbps
	//	01:300Kbps
	//	10:250Kbps
	//	11:未设置速率或1Mbps
	BYTE	HDDStatus;					//硬盘状态，端口0x1F7的值
	BYTE	HDDError;					//硬盘错误，端口0x1F1的值
	BYTE	HDDComplete;				//硬盘操作完成后此值为0xFF，硬盘开始操作时值为0
	BYTE	FDDControllerInfo;			//软盘控制器信息
	//位：
	//0:	驱动器0带改变检测线
	//1:	驱动器0是多速率的
	//2:	确定了驱动器0的类型
	//3:	未用
	//4:	驱动器1带改变检测线
	//5:	驱动器1是多速率的
	//6:	确定了驱动器1的类型
	//7:	未用
	#define	BDFDDCI_DRV0CHANGELINE		0x01
	#define	BDFDDCI_DRV0MULTIRATE		0x02
	#define	BDFDDCI_DRV0TYPECONFIRMED	0x04
	#define	BDFDDCI_DRV1CHANGELINE		0x10
	#define	BDFDDCI_DRV1MULTIRATE		0x20
	#define	BDFDDCI_DRV1TYPECONFIRMED	0x40
	BYTE	FDD0MediaStatus;			//软驱0介质状态
	BYTE	FDD1MediaStatus;			//软驱1介质状态
	//位：
	//0-2:	确定上次访问
	//	000:在360K的驱动器中是360K的介质
	//	001:在1.2M的驱动器中是360K的介质
	//	010:在1.2M的驱动器中是360K的介质
	//	011:在360K的驱动器中已知360K的介质
	//	100:在1.2M的驱动器中已知360K的介质
	//	101:在1.2M的驱动器中已知1.2M的介质
	//	110:未使用状态
	//	111:在720K的驱动器中是720K的介质或1.44M的驱动器中是1.44M的介质
	//3:		未使用
	//4:		已知软驱中的介质
	//5:		要求双倍步进（1.2M驱动器带360K软盘）
	//6-7:	数据传送率
	//	00:500Kbps
	//	01:300Kbps
	//	10:250Kbps
	//	11:1Mbps
	#define	BDFDDMS_MEDIACONFIRMED		0x10
	#define	BDFDDMS_DOUBLESPEED			0x20
	BYTE	FDD0OperationStartStatus;	//软驱0操作起始状态
	BYTE	FDD1OperationStartStatus;	//软驱1操作起始状态
	//位：
	//0:		驱动器带改变检测线
	//1:		驱动器是多速率的
	//2:		确定了驱动器的类型
	//3:		未用
	//4:		未知功能
	//5:		未知功能
	//6-7:
	//	00:500Kbps
	//	01:300Kbps
	//	10:250Kbps
	//	11:1Mbps
	#define	BDFDDOSS_DRV0CHANGELINE		0x01
	#define	BDFDDOSS_DRV0MULTIRATE		0x02
	#define	BDFDDOSS_DRV0TYPECONFIRMED	0x04
	BYTE	FDD0CurCylinder;					//软驱0当前柱面
	BYTE	FDD1CurCylinder;					//软驱1当前柱面
	BYTE	KbdStatus3;							//键盘状态标志3
	//位：
	//0:	安装了键盘
	//1:
	//	0:扫描码是0xE1时设置该标志并从键盘读取下一个字节
	//	1:扫描码是0xE0时设置该标志并从键盘读取下一个字节
	//2:	按下了右Ctrl
	//3:	按下了右Alt
	//4:	101键或104键键盘
	//5:	取得键盘ID（重启）后强制Num-Lock
	//6:	上次输入的一个键盘字节是ID的第一个字符，现在读取第二个
	//7:	正在读取ID的两字节
	#define	BDKS3_KBDINSTALLED			0x01
	#define	BDKS3_SCE0SETFLAGANDREAD	0x02
	#define	BDKS3_RCTRLDOWN				0x04
	#define	BDKS3_RALTDOWN				0x08
	#define	BDKS3_101OR104KBD			0x10
	#define	BDKS3_SETNUMLOCKWHENGETID	0x20
	#define	BDKS3_LASTISFCOFIDNOWREAD	0x40
	#define	BDKS3_READING2BYTEID		0x80
	BYTE	KbdStatus4;					//键盘状态标志4
	//位：
	//0:	Scroll Lock开
	//1:	Num Lock开
	//2: Caps Lock开
	//3:	未用
	//4:	键盘发送了一个ACK，0xFA
	//5:	键盘发送了一个“重发”，0xFE
	//6:	程序中更新了LED
	//7:	键盘传送错
	#define	BDKS4_SCROLLLOCKON			0x01
	#define	BDKS4_NUMLOCKON				0x02
	#define	BDKS4_CAPSLOCKON			0x04
	#define	BDKS4_RESERVED				0x08
	#define	BDKS4_KBDACK				0x10
	#define	BDKS4_KBDWANTAGAIN			0x20
	#define	BDKS4_UPDATELED				0x40
	#define	BDKS4_KBDERROR				0x80
	DWORD	UserTimerPointer;					//用户等待标志指针
	DWORD	UserWaitCount;						//用户等待计数，用作延时
	BYTE	WaitFlag;							//等待标志
	//位：
	//0:		正在等待
	//1-6:	未使用
	//7:		等待时间到期
	#define	BDWF_WAITING	0x01
	#define	BDWF_EXPIRE		0x80
	BYTE	LocalNetworkBytes[7];	//局域网字节
	DWORD	VideoParamsControlPtr;	//视频参数控制块指针，请见后面。
	BYTE	DaysFrom1980;			//从1980年到现在的天数
	BYTE	PrintScreenStatus;		//打印屏幕状态
	#define	BDPSS_READY		0x00	//准备好
	#define	BDPSS_PRINTING	0x01	//正在打印
	#define	BDPSS_ERROR		0xFF	//缺纸、打印机错误、超时等
}BIOSDATA;

typedef	struct//视频参数控制块
{
	DWORD	VideoParam;			//视频参数
	DWORD	ParamSaveArea;		//参数保存区
	DWORD	AlNumCharset;		//字母数字字符集
	DWORD	GraphicsCharset;	//图形字符集
	DWORD	SecondSaveAreaPtr;	//第二个保存表指针
	DWORD	Unused[2];			//未用
}VideoParamsControl;

typedef	struct
{
	WORD	StructSize;			//结构体大小
	DWORD	CombinePresentCode;	//组合代表码
	DWORD	SecondAlNumCharset;	//第二个字母数字字符集
	DWORD	UserPaletteTable;	//用户调色板表
	DWORD	Unused[3];			//未用
}SecondSaveArea;

#endif
