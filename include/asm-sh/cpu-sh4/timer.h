multiline_comment|/*&n; * include/asm-sh/cpu-sh4/timer.h&n; *&n; * Copyright (C) 2004 Lineo Solutions, Inc. &n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH4_TIMER_H
DECL|macro|__ASM_CPU_SH4_TIMER_H
mdefine_line|#define __ASM_CPU_SH4_TIMER_H
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * TMU Common definitions for SH4 processors&n; *&t;SH7750S/SH7750R&n; *&t;SH7751/SH7751R&n; *&t;SH7760&n; * ---------------------------------------------------------------------------&n; */
macro_line|#if !defined(CONFIG_CPU_SUBTYPE_SH7760)
DECL|macro|TMU_TOCR
mdefine_line|#define TMU_TOCR        0xffd80000      /* Byte access */
macro_line|#endif
DECL|macro|TMU_TSTR
mdefine_line|#define TMU_TSTR        0xffd80004      /* Byte access */
DECL|macro|TMU0_TCOR
mdefine_line|#define TMU0_TCOR       0xffd80008      /* Long access */
DECL|macro|TMU0_TCNT
mdefine_line|#define TMU0_TCNT       0xffd8000c      /* Long access */
DECL|macro|TMU0_TCR
mdefine_line|#define TMU0_TCR        0xffd80010      /* Word access */
DECL|macro|TMU1_TCOR
mdefine_line|#define TMU1_TCOR       0xffd80014      /* Long access */
DECL|macro|TMU1_TCNT
mdefine_line|#define TMU1_TCNT       0xffd80018      /* Long access */
DECL|macro|TMU1_TCR
mdefine_line|#define TMU1_TCR        0xffd8001c      /* Word access */
DECL|macro|TMU2_TCOR
mdefine_line|#define TMU2_TCOR       0xffd80020      /* Long access */
DECL|macro|TMU2_TCNT
mdefine_line|#define TMU2_TCNT       0xffd80024      /* Long access */
DECL|macro|TMU2_TCR
mdefine_line|#define TMU2_TCR        0xffd80028      /* Word access */
DECL|macro|TMU2_TCPR
mdefine_line|#define TMU2_TCPR&t;0xffd8002c&t;/* Long access */
macro_line|#if !defined(CONFIG_CPU_SUBTYPE_SH7760)
DECL|macro|TMU3_TCOR
mdefine_line|#define TMU3_TCOR       0xfe100008      /* Long access */
DECL|macro|TMU3_TCNT
mdefine_line|#define TMU3_TCNT       0xfe10000c      /* Long access */
DECL|macro|TMU3_TCR
mdefine_line|#define TMU3_TCR        0xfe100010      /* Word access */
DECL|macro|TMU4_TCOR
mdefine_line|#define TMU4_TCOR       0xfe100014      /* Long access */
DECL|macro|TMU4_TCNT
mdefine_line|#define TMU4_TCNT       0xfe100018      /* Long access */
DECL|macro|TMU4_TCR
mdefine_line|#define TMU4_TCR        0xfe10001c      /* Word access */
macro_line|#endif
macro_line|#endif /* __ASM_CPU_SH4_TIMER_H */
eof
