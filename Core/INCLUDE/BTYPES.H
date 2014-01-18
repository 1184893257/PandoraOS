#ifndef _BASIC_TYPES_INCLUDED_
#define	_BASIC_TYPES_INCLUDED_

typedef	unsigned char		BYTE;
typedef	unsigned short		WORD;
typedef	unsigned long		DWORD;
typedef	unsigned long long	QWORD;

typedef	signed int			INT;
typedef	signed char			INT8;
typedef	signed short		INT16;
typedef	signed long			INT32;
typedef	signed long long	INT64;

typedef	unsigned int		UINT;
typedef	unsigned char		UINT8;
typedef	unsigned short		UINT16;
typedef	unsigned long		UINT32;
typedef	unsigned long long	UINT64;

#ifndef __cplusplus
typedef	char	bool;
#define	true	1
#define	false	0
#endif

typedef	INT		BOOL;
#define	TRUE	1
#define	FALSE	0

typedef	WORD WCHAR;

#ifdef __cplusplus
#define	NASMFUNC extern"C"
#define	NASMSYM extern"C"
#else
#define	NASMFUNC extern
#define	NASMSYM extern
#endif

#define	MAKEWORD(l,h)	((WORD)l|((WORD)h<<8))
#define	MAKEDWORD(l,h)	((DWORD)l|((DWORD)h<<16))

#define	LOBYTE(w)		((w & 0x00FF)>>0)
#define	HIBYTE(w)		((w & 0xFF00)>>8)

#define	LOWORD(dw)		((dw & 0x0000FFFF)>>0)
#define	HIWORD(dw)		((dw & 0xFFFF0000)>>16)

#endif
