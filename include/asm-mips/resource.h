multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 96, 98, 99, 2000 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_RESOURCE_H
DECL|macro|_ASM_RESOURCE_H
mdefine_line|#define _ASM_RESOURCE_H
multiline_comment|/*&n; * Resource limits&n; */
DECL|macro|RLIMIT_CPU
mdefine_line|#define RLIMIT_CPU 0&t;&t;&t;/* CPU time in ms */
DECL|macro|RLIMIT_FSIZE
mdefine_line|#define RLIMIT_FSIZE 1&t;&t;&t;/* Maximum filesize */
DECL|macro|RLIMIT_DATA
mdefine_line|#define RLIMIT_DATA 2&t;&t;&t;/* max data size */
DECL|macro|RLIMIT_STACK
mdefine_line|#define RLIMIT_STACK 3&t;&t;&t;/* max stack size */
DECL|macro|RLIMIT_CORE
mdefine_line|#define RLIMIT_CORE 4&t;&t;&t;/* max core file size */
DECL|macro|RLIMIT_NOFILE
mdefine_line|#define RLIMIT_NOFILE 5&t;&t;&t;/* max number of open files */
DECL|macro|RLIMIT_AS
mdefine_line|#define RLIMIT_AS 6&t;&t;&t;/* mapped memory */
DECL|macro|RLIMIT_RSS
mdefine_line|#define RLIMIT_RSS 7&t;&t;&t;/* max resident set size */
DECL|macro|RLIMIT_NPROC
mdefine_line|#define RLIMIT_NPROC 8&t;&t;&t;/* max number of processes */
DECL|macro|RLIMIT_MEMLOCK
mdefine_line|#define RLIMIT_MEMLOCK 9&t;&t;/* max locked-in-memory address space */
DECL|macro|RLIMIT_LOCKS
mdefine_line|#define RLIMIT_LOCKS 10&t;&t;&t;/* maximum file locks held */
DECL|macro|RLIMIT_SIGPENDING
mdefine_line|#define RLIMIT_SIGPENDING 11&t;&t;/* max number of pending signals */
DECL|macro|RLIMIT_MSGQUEUE
mdefine_line|#define RLIMIT_MSGQUEUE 12&t;&t;/* maximum bytes in POSIX mqueues */
DECL|macro|RLIM_NLIMITS
mdefine_line|#define RLIM_NLIMITS 13&t;&t;&t;/* Number of limit flavors.  */
DECL|macro|__ARCH_RLIMIT_ORDER
mdefine_line|#define __ARCH_RLIMIT_ORDER
multiline_comment|/*&n; * SuS says limits have to be unsigned.&n; * Which makes a ton more sense anyway.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_MIPS32
DECL|macro|RLIM_INFINITY
mdefine_line|#define RLIM_INFINITY&t;0x7fffffffUL
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS64
DECL|macro|RLIM_INFINITY
mdefine_line|#define RLIM_INFINITY&t;(~0UL)
macro_line|#endif
macro_line|#include &lt;asm-generic/resource.h&gt;
macro_line|#endif /* _ASM_RESOURCE_H */
eof
