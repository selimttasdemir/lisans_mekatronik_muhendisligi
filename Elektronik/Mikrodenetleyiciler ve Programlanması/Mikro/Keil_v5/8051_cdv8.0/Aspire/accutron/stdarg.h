#ifndef _VA_LIST_DEFINED
typedef struct {char buf[4];} va_list;
extern void *_va_arg(va_list *p, unsigned char n);
#define _VA_LIST_DEFINED

#define va_start(ap,v)
#define va_arg(ap,t) (*((t *)_va_arg(&ap, (unsigned char)sizeof(t))))
#define va_end(ap)
#endif

void dprint( char *szTypes, ... );
