#ifndef	_GLOBAL_HEADER_INCLUDED_
#define	_GLOBAL_HEADER_INCLUDED_

#define	OSNAME		"PandoraOS"

#define	STACKSIZE	0xFFFF

typedef	unsigned	char	BYTE;
typedef	unsigned	short	WORD;
typedef	unsigned	long	DWORD;
typedef	signed		int		INT;
typedef	signed		char	INT8;
typedef	signed		short	INT16;
typedef	signed		long	INT32;
typedef	unsigned	int		UINT;
typedef	unsigned	char	UINT8;
typedef	unsigned	short	UINT16;
typedef	unsigned	long	UINT32;

#ifndef __cplusplus
typedef	char	bool;
#define	true	1
#define	false	0
#endif

typedef	INT8	BOOL;
#define	TRUE	1
#define	FALSE	0

#endif
