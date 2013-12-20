org 0x100
bits 16

Start:
mov ax,cs
mov ds,ax
;先检测CPU是否支持CPUID这个指令
pushfd						;取得EFLAGS的值
mov eax,[esp]				;读入EAX
xor dword[esp],0x00200000	;改写ID位
popfd						;然后存回EFLAGS
pushfd						;再取得EFLAGS的值
pop edx
cmp eax,edx					;判断EFLAGS的ID位是否被改变
jne Support					;如果没改变说明不支持CPUID指令

NotSupport:
mov dx,.Prompt
mov ah,9
int 0x21
int 0x20
jmp $
.Prompt db "Your CPU does not support CPUID instruction.",0xD,0xA,'$'

Support:					;这里知道CPUID可用
xor eax,eax
CPUID						;取得CPU的厂商字符串
mov [CPUString.c0_3],ebx
mov [CPUString.c4_7],edx
mov [CPUString.c8_11],ecx
mov [MaxBasicFunc],eax		;最大基本功能号
mov eax,0x80000000
CPUID						;取得最大扩展功能号
mov [MaxExtendedFunc],eax
mov eax,1
CPUID						;取得CPU功能信息
mov [CPUFamilyType],eax
mov [CPUFunc1],ecx
mov [CPUFunc2],edx

mov dx,CPUString
mov ah,9
int 0x21					;打印CPUID文本
mov eax,[MaxBasicFunc]
call ShowHex				;打印最大基本功能号16进制
mov dx,CPUString.MaxExt
mov ah,9
int 0x21
mov eax,[MaxExtendedFunc]
call ShowHex				;打印最大扩展功能号16进制
mov dx,CPUString.FuncList
mov ah,9
int 0x21

mov ecx,32
mov ebx,[CPUFunc1]
mov si,FunctionPointers
mov ah,0x9
ShowFunctions:
	shr ebx,1
	jnc .Showed
	mov dx,[si]
	int 0x21
.Showed:
	add si,2
loop ShowFunctions
int 0x20


CPUString:
.Prompt			db	"CPU:"
.c0_3			db	"????"
.c4_7			db	"????"
.c8_11			db	"????"
.NewLine1		db	0xD,0xA,"Maximum basic functions number:   0x$"
.MaxExt			db	0xD,0xA,"Maximum extended functions number:0x$"
.FuncList		db	0xD,0xA,"Supported instructions:"
.NewLine2		db	0xD,0xA,"$"

MaxBasicFunc	dd	0	;CPU的最大基本功能号(EAX)
MaxExtendedFunc	dd	0	;CPU的最大基本功能号(EAX)
CPUFamilyType	dd	0	;CPU家族类型(EAX)
CPUFunc1		dd	0	;CPU功能信息(ECX)
CPUFunc2		dd	0	;CPU功能信息(EDX)

FunctionNames:
	.B0		db	"  SSE3 Extension(0)",0xD,0xA,"$"
	.B1		db	"  Carryless Multiplication(1)",0xD,0xA,"$"
	.B2		db	"  64-bit DS Area(2)",0xD,0xA,"$"
	.B3		db	"  MONITOR/MWAIT(3)",0xD,0xA,"$"
	.B4		db	"  CPL Qualified Debug Store(4)",0xD,0xA,"$"
	.B5		db	"  Virtual Machine Extensions(5)",0xD,0xA,"$"
	.B6		db	"  SaferMode Extensions(6)",0xD,0xA,"$"
	.B7		db	"  Enhanced Intel SpeedStep Technology(7)",0xD,0xA,"$"
	.B8		db	"  Thermal Monitor 2(8)",0xD,0xA,"$"
	.B9		db	"  SSSE3 Extensions(9)",0xD,0xA,"$"
	.B10	db	"  L1 Context ID(10)",0xD,0xA,"$"
	.B11	db	"  ???(11)",0xD,0xA,"$"
	.B12	db	"  Fused Multiply Add(12)",0xD,0xA,"$"
	.B13	db	"  CMPXCHG16B(13)",0xD,0xA,"$"
	.B14	db	"  Update Control(14)",0xD,0xA,"$"
	.B15	db	"  Perf/Debug Capability MSR(15)",0xD,0xA,"$"
	.B16	db	"  ???(16)",0xD,0xA,"$"
	.B17	db	"  Process-context Identifiers(17)",0xD,0xA,"$"
	.B18	db	"  Direct Cache Access(18)",0xD,0xA,"$"
	.B19	db	"  SSE4.1(19)",0xD,0xA,"$"
	.B20	db	"  SSE4.2(20)",0xD,0xA,"$"
	.B21	db	"  x2APIC(21)",0xD,0xA,"$"
	.B22	db	"  MOVEBE(22)",0xD,0xA,"$"
	.B23	db	"  POPCNT(23)",0xD,0xA,"$"
	.B24	db	"  TSC-Deadline(24)",0xD,0xA,"$"
	.B25	db	"  AES(25)",0xD,0xA,"$"
	.B26	db	"  XSAVE(26)",0xD,0xA,"$"
	.B27	db	"  OSXSAVE(27)",0xD,0xA,"$"
	.B28	db	"  AVX(28)",0xD,0xA,"$"
	.B29	db	"  ???(29)",0xD,0xA,"$"
	.B30	db	"  ???(30)",0xD,0xA,"$"
	.B31	db	"  ???(31)",0xD,0xA,"$"

FunctionPointers:
	.B0		dw	FunctionNames.B0
	.B1		dw	FunctionNames.B1
	.B2		dw	FunctionNames.B2
	.B3		dw	FunctionNames.B3
	.B4		dw	FunctionNames.B4
	.B5		dw	FunctionNames.B5
	.B6		dw	FunctionNames.B6
	.B7		dw	FunctionNames.B7
	.B8		dw	FunctionNames.B8
	.B9		dw	FunctionNames.B9
	.B10	dw	FunctionNames.B10
	.B11	dw	FunctionNames.B11
	.B12	dw	FunctionNames.B12
	.B13	dw	FunctionNames.B13
	.B14	dw	FunctionNames.B14
	.B15	dw	FunctionNames.B15
	.B16	dw	FunctionNames.B16
	.B17	dw	FunctionNames.B17
	.B18	dw	FunctionNames.B18
	.B19	dw	FunctionNames.B19
	.B20	dw	FunctionNames.B20
	.B21	dw	FunctionNames.B21
	.B22	dw	FunctionNames.B22
	.B23	dw	FunctionNames.B23
	.B24	dw	FunctionNames.B24
	.B25	dw	FunctionNames.B25
	.B26	dw	FunctionNames.B26
	.B27	dw	FunctionNames.B27
	.B28	dw	FunctionNames.B28
	.B29	dw	FunctionNames.B29
	.B30	dw	FunctionNames.B30
	.B31	dw	FunctionNames.B31

ShowHex:
	mov cx,8
.ShowHex:
	mov edx,eax
	shr edx,28
	cmp dl,10
	jb .GotChar
	add dl,'A'-'0'-10
.GotChar:
	add dl,'0'
	push ax
	mov ah,2
	int 0x21
	pop ax
	shl eax,4
	loop .ShowHex
	ret
