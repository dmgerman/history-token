multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1995, 96, 98, 99, 2000 by Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_RESOURCE_H
DECL|macro|_ASM_RESOURCE_H
mdefine_line|#define _ASM_RESOURCE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * These five resource limit IDs have a MIPS/Linux-specific ordering,&n; * the rest comes from the generic header:&n; */
DECL|macro|RLIMIT_NOFILE
mdefine_line|#define RLIMIT_NOFILE&t;&t;5&t;/* max number of open files */
DECL|macro|RLIMIT_AS
mdefine_line|#define RLIMIT_AS&t;&t;6&t;/* address space limit */
DECL|macro|RLIMIT_RSS
mdefine_line|#define RLIMIT_RSS&t;&t;7&t;/* max resident set size */
DECL|macro|RLIMIT_NPROC
mdefine_line|#define RLIMIT_NPROC&t;&t;8&t;/* max number of processes */
DECL|macro|RLIMIT_MEMLOCK
mdefine_line|#define RLIMIT_MEMLOCK&t;&t;9&t;/* max locked-in-memory address space */
multiline_comment|/*&n; * SuS says limits have to be unsigned.&n; * Which makes a ton more sense anyway,&n; * but we keep the old value on MIPS32,&n; * for compatibility:&n; */
macro_line|#ifdef CONFIG_MIPS32
DECL|macro|RLIM_INFINITY
macro_line|# define RLIM_INFINITY&t;&t;0x7fffffffUL
macro_line|#endif
macro_line|#include &lt;asm-generic/resource.h&gt;
macro_line|#endif /* _ASM_RESOURCE_H */
eof
