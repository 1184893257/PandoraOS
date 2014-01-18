%ifndef	_PROGRAMMABLE_INTERRUPT_CHIP_
%define	_PROGRAMMABLE_INTERRUPT_CHIP_

%define	PIC_MASK		0x21
%define	PIC_MODE		0x20
%define	PIC2_MASK		0xA1
%define	PIC2_MODE		0xA0

%define	PIC_EOI			0x20
%define	PIC_SPECEOI		0x60

%define	PIC_IRQ0_7BEGIN	0x08
%define	PIC_IRQ8_FBEGIN	0x70

%ifndef _INTR_ASM_
extern	_GetVector	;DWORD	GetVector(BYTE);
extern	_SetVector	;void	SetVector(BYTE,DWORD);
extern	_SendEOI	;void	SendEOI(BYTE);
extern	_SetMask	;void	SetMask(BYTE);
extern	_GetMask	;BYTE	GetMask(BYTE);
extern	_ClearMask	;void	ClearMask(BYTE);
%endif

%endif
