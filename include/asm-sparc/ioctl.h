multiline_comment|/* $Id: ioctl.h,v 1.6 1999/12/01 23:58:36 davem Exp $ */
macro_line|#ifndef _SPARC_IOCTL_H
DECL|macro|_SPARC_IOCTL_H
mdefine_line|#define _SPARC_IOCTL_H
multiline_comment|/*&n; * Our DIR and SIZE overlap in order to simulteneously provide&n; * a non-zero _IOC_NONE (for binary compatibility) and&n; * 14 bits of size as on i386. Here&squot;s the layout:&n; *&n; *   0xE0000000   DIR&n; *   0x80000000     DIR = WRITE&n; *   0x40000000     DIR = READ&n; *   0x20000000     DIR = NONE&n; *   0x3FFF0000   SIZE (overlaps NONE bit)&n; *   0x0000FF00   TYPE&n; *   0x000000FF   NR (CMD)&n; */
DECL|macro|_IOC_NRBITS
mdefine_line|#define _IOC_NRBITS      8
DECL|macro|_IOC_TYPEBITS
mdefine_line|#define _IOC_TYPEBITS    8
DECL|macro|_IOC_SIZEBITS
mdefine_line|#define _IOC_SIZEBITS   13&t;/* Actually 14, see below. */
DECL|macro|_IOC_DIRBITS
mdefine_line|#define _IOC_DIRBITS     3
DECL|macro|_IOC_NRMASK
mdefine_line|#define _IOC_NRMASK      ((1 &lt;&lt; _IOC_NRBITS)-1)
DECL|macro|_IOC_TYPEMASK
mdefine_line|#define _IOC_TYPEMASK    ((1 &lt;&lt; _IOC_TYPEBITS)-1)
DECL|macro|_IOC_SIZEMASK
mdefine_line|#define _IOC_SIZEMASK    ((1 &lt;&lt; _IOC_SIZEBITS)-1)
DECL|macro|_IOC_XSIZEMASK
mdefine_line|#define _IOC_XSIZEMASK   ((1 &lt;&lt; (_IOC_SIZEBITS+1))-1)
DECL|macro|_IOC_DIRMASK
mdefine_line|#define _IOC_DIRMASK     ((1 &lt;&lt; _IOC_DIRBITS)-1)
DECL|macro|_IOC_NRSHIFT
mdefine_line|#define _IOC_NRSHIFT     0
DECL|macro|_IOC_TYPESHIFT
mdefine_line|#define _IOC_TYPESHIFT   (_IOC_NRSHIFT + _IOC_NRBITS)
DECL|macro|_IOC_SIZESHIFT
mdefine_line|#define _IOC_SIZESHIFT   (_IOC_TYPESHIFT + _IOC_TYPEBITS)
DECL|macro|_IOC_DIRSHIFT
mdefine_line|#define _IOC_DIRSHIFT    (_IOC_SIZESHIFT + _IOC_SIZEBITS)
DECL|macro|_IOC_NONE
mdefine_line|#define _IOC_NONE        1U
DECL|macro|_IOC_READ
mdefine_line|#define _IOC_READ        2U
DECL|macro|_IOC_WRITE
mdefine_line|#define _IOC_WRITE       4U
DECL|macro|_IOC
mdefine_line|#define _IOC(dir,type,nr,size) &bslash;&n;        (((dir)  &lt;&lt; _IOC_DIRSHIFT) | &bslash;&n;         ((type) &lt;&lt; _IOC_TYPESHIFT) | &bslash;&n;         ((nr)   &lt;&lt; _IOC_NRSHIFT) | &bslash;&n;         ((size) &lt;&lt; _IOC_SIZESHIFT))
DECL|macro|_IO
mdefine_line|#define _IO(type,nr)        _IOC(_IOC_NONE,(type),(nr),0)
DECL|macro|_IOR
mdefine_line|#define _IOR(type,nr,size)  _IOC(_IOC_READ,(type),(nr),sizeof(size))
DECL|macro|_IOW
mdefine_line|#define _IOW(type,nr,size)  _IOC(_IOC_WRITE,(type),(nr),sizeof(size))
DECL|macro|_IOWR
mdefine_line|#define _IOWR(type,nr,size) _IOC(_IOC_READ|_IOC_WRITE,(type),(nr),sizeof(size))
multiline_comment|/* Used to decode ioctl numbers in drivers despite the leading underscore... */
DECL|macro|_IOC_DIR
mdefine_line|#define _IOC_DIR(nr)    &bslash;&n; ( (((((nr) &gt;&gt; _IOC_DIRSHIFT) &amp; _IOC_DIRMASK) &amp; (_IOC_WRITE|_IOC_READ)) != 0)?   &bslash;&n;                            (((nr) &gt;&gt; _IOC_DIRSHIFT) &amp; (_IOC_WRITE|_IOC_READ)):  &bslash;&n;                            (((nr) &gt;&gt; _IOC_DIRSHIFT) &amp; _IOC_DIRMASK) )
DECL|macro|_IOC_TYPE
mdefine_line|#define _IOC_TYPE(nr)       (((nr) &gt;&gt; _IOC_TYPESHIFT) &amp; _IOC_TYPEMASK)
DECL|macro|_IOC_NR
mdefine_line|#define _IOC_NR(nr)         (((nr) &gt;&gt; _IOC_NRSHIFT) &amp; _IOC_NRMASK)
DECL|macro|_IOC_SIZE
mdefine_line|#define _IOC_SIZE(nr)       (((nr) &gt;&gt; _IOC_SIZESHIFT) &amp; _IOC_XSIZEMASK)
multiline_comment|/* ...and for the PCMCIA and sound. */
DECL|macro|IOC_IN
mdefine_line|#define IOC_IN          (_IOC_WRITE &lt;&lt; _IOC_DIRSHIFT)
DECL|macro|IOC_OUT
mdefine_line|#define IOC_OUT         (_IOC_READ &lt;&lt; _IOC_DIRSHIFT)
DECL|macro|IOC_INOUT
mdefine_line|#define IOC_INOUT       ((_IOC_WRITE|_IOC_READ) &lt;&lt; _IOC_DIRSHIFT)
DECL|macro|IOCSIZE_MASK
mdefine_line|#define IOCSIZE_MASK    (_IOC_XSIZEMASK &lt;&lt; _IOC_SIZESHIFT)
DECL|macro|IOCSIZE_SHIFT
mdefine_line|#define IOCSIZE_SHIFT   (_IOC_SIZESHIFT)
macro_line|#endif /* !(_SPARC_IOCTL_H) */
eof
