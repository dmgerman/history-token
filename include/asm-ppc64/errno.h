macro_line|#ifndef _PPC64_ERRNO_H
DECL|macro|_PPC64_ERRNO_H
mdefine_line|#define _PPC64_ERRNO_H
multiline_comment|/* &n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;asm-generic/errno.h&gt;
DECL|macro|EDEADLOCK
macro_line|#undef&t;EDEADLOCK
DECL|macro|EDEADLOCK
mdefine_line|#define&t;EDEADLOCK&t;58&t;/* File locking deadlock error */
DECL|macro|_LAST_ERRNO
mdefine_line|#define _LAST_ERRNO&t;516
macro_line|#endif
eof
