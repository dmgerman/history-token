multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1997, 98, 99, 2000, 2003 Ralf Baechle&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_CACHE_H
DECL|macro|_ASM_CACHE_H
mdefine_line|#define _ASM_CACHE_H
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|L1_CACHE_SHIFT
mdefine_line|#define L1_CACHE_SHIFT&t;&t;CONFIG_MIPS_L1_CACHE_SHIFT
DECL|macro|L1_CACHE_BYTES
mdefine_line|#define L1_CACHE_BYTES&t;&t;(1 &lt;&lt; L1_CACHE_SHIFT)
DECL|macro|L1_CACHE_SHIFT_MAX
mdefine_line|#define L1_CACHE_SHIFT_MAX&t;6
DECL|macro|SMP_CACHE_SHIFT
mdefine_line|#define SMP_CACHE_SHIFT&t;&t;L1_CACHE_SHIFT
DECL|macro|SMP_CACHE_BYTES
mdefine_line|#define SMP_CACHE_BYTES&t;&t;L1_CACHE_BYTES
DECL|macro|ARCH_KMALLOC_MINALIGN
mdefine_line|#define ARCH_KMALLOC_MINALIGN&t;8
macro_line|#endif /* _ASM_CACHE_H */
eof
