multiline_comment|/*&n; * BK Id: SCCS/s.ioctl.h 1.5 05/17/01 18:14:24 cort&n; */
macro_line|#ifndef _PPC_IOCTL_H
DECL|macro|_PPC_IOCTL_H
mdefine_line|#define _PPC_IOCTL_H
multiline_comment|/*&n; * this was copied from the alpha as it&squot;s a bit cleaner there.&n; *                         -- Cort&n; */
DECL|macro|_IOC_NRBITS
mdefine_line|#define _IOC_NRBITS&t;8
DECL|macro|_IOC_TYPEBITS
mdefine_line|#define _IOC_TYPEBITS&t;8
DECL|macro|_IOC_SIZEBITS
mdefine_line|#define _IOC_SIZEBITS&t;13
DECL|macro|_IOC_DIRBITS
mdefine_line|#define _IOC_DIRBITS&t;3
DECL|macro|_IOC_NRMASK
mdefine_line|#define _IOC_NRMASK&t;((1 &lt;&lt; _IOC_NRBITS)-1)
DECL|macro|_IOC_TYPEMASK
mdefine_line|#define _IOC_TYPEMASK&t;((1 &lt;&lt; _IOC_TYPEBITS)-1)
DECL|macro|_IOC_SIZEMASK
mdefine_line|#define _IOC_SIZEMASK&t;((1 &lt;&lt; _IOC_SIZEBITS)-1)
DECL|macro|_IOC_DIRMASK
mdefine_line|#define _IOC_DIRMASK&t;((1 &lt;&lt; _IOC_DIRBITS)-1)
DECL|macro|_IOC_NRSHIFT
mdefine_line|#define _IOC_NRSHIFT&t;0
DECL|macro|_IOC_TYPESHIFT
mdefine_line|#define _IOC_TYPESHIFT&t;(_IOC_NRSHIFT+_IOC_NRBITS)
DECL|macro|_IOC_SIZESHIFT
mdefine_line|#define _IOC_SIZESHIFT&t;(_IOC_TYPESHIFT+_IOC_TYPEBITS)
DECL|macro|_IOC_DIRSHIFT
mdefine_line|#define _IOC_DIRSHIFT&t;(_IOC_SIZESHIFT+_IOC_SIZEBITS)
multiline_comment|/*&n; * Direction bits _IOC_NONE could be 0, but OSF/1 gives it a bit.&n; * And this turns out useful to catch old ioctl numbers in header&n; * files for us.&n; */
DECL|macro|_IOC_NONE
mdefine_line|#define _IOC_NONE&t;1U
DECL|macro|_IOC_READ
mdefine_line|#define _IOC_READ&t;2U
DECL|macro|_IOC_WRITE
mdefine_line|#define _IOC_WRITE&t;4U
DECL|macro|_IOC
mdefine_line|#define _IOC(dir,type,nr,size) &bslash;&n;&t;(((dir)  &lt;&lt; _IOC_DIRSHIFT) | &bslash;&n;&t; ((type) &lt;&lt; _IOC_TYPESHIFT) | &bslash;&n;&t; ((nr)   &lt;&lt; _IOC_NRSHIFT) | &bslash;&n;&t; ((size) &lt;&lt; _IOC_SIZESHIFT))
multiline_comment|/* used to create numbers */
DECL|macro|_IO
mdefine_line|#define _IO(type,nr)&t;&t;_IOC(_IOC_NONE,(type),(nr),0)
DECL|macro|_IOR
mdefine_line|#define _IOR(type,nr,size)&t;_IOC(_IOC_READ,(type),(nr),sizeof(size))
DECL|macro|_IOW
mdefine_line|#define _IOW(type,nr,size)&t;_IOC(_IOC_WRITE,(type),(nr),sizeof(size))
DECL|macro|_IOWR
mdefine_line|#define _IOWR(type,nr,size)&t;_IOC(_IOC_READ|_IOC_WRITE,(type),(nr),sizeof(size))
multiline_comment|/* used to decode them.. */
DECL|macro|_IOC_DIR
mdefine_line|#define _IOC_DIR(nr)&t;&t;(((nr) &gt;&gt; _IOC_DIRSHIFT) &amp; _IOC_DIRMASK)
DECL|macro|_IOC_TYPE
mdefine_line|#define _IOC_TYPE(nr)&t;&t;(((nr) &gt;&gt; _IOC_TYPESHIFT) &amp; _IOC_TYPEMASK)
DECL|macro|_IOC_NR
mdefine_line|#define _IOC_NR(nr)&t;&t;(((nr) &gt;&gt; _IOC_NRSHIFT) &amp; _IOC_NRMASK)
DECL|macro|_IOC_SIZE
mdefine_line|#define _IOC_SIZE(nr)&t;&t;(((nr) &gt;&gt; _IOC_SIZESHIFT) &amp; _IOC_SIZEMASK)
multiline_comment|/* various drivers, such as the pcmcia stuff, need these... */
DECL|macro|IOC_IN
mdefine_line|#define IOC_IN&t;&t;(_IOC_WRITE &lt;&lt; _IOC_DIRSHIFT)
DECL|macro|IOC_OUT
mdefine_line|#define IOC_OUT&t;&t;(_IOC_READ &lt;&lt; _IOC_DIRSHIFT)
DECL|macro|IOC_INOUT
mdefine_line|#define IOC_INOUT&t;((_IOC_WRITE|_IOC_READ) &lt;&lt; _IOC_DIRSHIFT)
DECL|macro|IOCSIZE_MASK
mdefine_line|#define IOCSIZE_MASK&t;(_IOC_SIZEMASK &lt;&lt; _IOC_SIZESHIFT)
DECL|macro|IOCSIZE_SHIFT
mdefine_line|#define IOCSIZE_SHIFT&t;(_IOC_SIZESHIFT)
macro_line|#endif
eof
