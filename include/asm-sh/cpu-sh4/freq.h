multiline_comment|/*&n; * include/asm-sh/cpu-sh4/freq.h&n; *&n; * Copyright (C) 2002, 2003 Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH4_FREQ_H
DECL|macro|__ASM_CPU_SH4_FREQ_H
mdefine_line|#define __ASM_CPU_SH4_FREQ_H
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH73180)
DECL|macro|FRQCR
mdefine_line|#define FRQCR&t;&t;        0xa4150000
macro_line|#else
DECL|macro|FRQCR
mdefine_line|#define FRQCR&t;&t;&t;0xffc00000
macro_line|#endif
DECL|macro|MIN_DIVISOR_NR
mdefine_line|#define MIN_DIVISOR_NR&t;&t;0
DECL|macro|MAX_DIVISOR_NR
mdefine_line|#define MAX_DIVISOR_NR&t;&t;3
macro_line|#endif /* __ASM_CPU_SH4_FREQ_H */
eof
