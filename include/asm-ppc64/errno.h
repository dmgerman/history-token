macro_line|#ifndef _PPC64_ERRNO_H
DECL|macro|_PPC64_ERRNO_H
mdefine_line|#define _PPC64_ERRNO_H
multiline_comment|/* &n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
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
