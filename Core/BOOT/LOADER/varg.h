#ifndef _VARG_
#define _VARG_

typedef char* va_list;
#define va_start(ap,v)  ( ap = (va_list)(&v) + sizeof(v) )
#define va_arg(ap,t)    ( *(t *)((ap += sizeof(t)) - sizeof(t)) )
#define va_end(ap)      ( ap = (va_list)0 )

#endif
