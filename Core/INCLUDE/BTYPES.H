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

#ifdef	__cplusplus
#define	NASMEXTRN	extern "C"
#else
#define	NASMEXTRN	extern
#endif

#endif
