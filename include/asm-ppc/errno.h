multiline_comment|/*&n; * BK Id: SCCS/s.errno.h 1.7 05/17/01 18:14:24 cort&n; */
macro_line|#ifndef _PPC_ERRNO_H
DECL|macro|_PPC_ERRNO_H
mdefine_line|#define _PPC_ERRNO_H
macro_line|#include &lt;asm-generic/errno.h&gt;
DECL|macro|EDEADLOCK
macro_line|#undef&t;EDEADLOCK
DECL|macro|EDEADLOCK
mdefine_line|#define&t;EDEADLOCK&t;58&t;/* File locking deadlock error */
multiline_comment|/* Should never be seen by user programs */
DECL|macro|ERESTARTSYS
mdefine_line|#define ERESTARTSYS&t;512
DECL|macro|ERESTARTNOINTR
mdefine_line|#define ERESTARTNOINTR&t;513
DECL|macro|ERESTARTNOHAND
mdefine_line|#define ERESTARTNOHAND&t;514&t;/* restart if no handler.. */
DECL|macro|ENOIOCTLCMD
mdefine_line|#define ENOIOCTLCMD&t;515&t;/* No ioctl command */
DECL|macro|_LAST_ERRNO
mdefine_line|#define _LAST_ERRNO&t;515
macro_line|#endif
eof
