multiline_comment|/*&n; * include/asm-sh/cpu-sh3/timer.h&n; *&n; * Copyright (C) 2004 Lineo Solutions, Inc.&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH3_TIMER_H
DECL|macro|__ASM_CPU_SH3_TIMER_H
mdefine_line|#define __ASM_CPU_SH3_TIMER_H
multiline_comment|/*&n; * ---------------------------------------------------------------------------&n; * TMU Common definitions for SH3 processors&n; *&t;SH7706&n; *&t;SH7709S&n; *&t;SH7727&n; *&t;SH7729R&n; *&t;SH7710&n; *&t;SH7720&n; *&t;SH7300&n; * ---------------------------------------------------------------------------&n; */
macro_line|#if defined(CONFIG_CPU_SUBTYPE_SH7300) || defined(CONFIG_CPU_SUBTYPE_SH7710)
DECL|macro|TMU_TSTR
mdefine_line|#define TMU_TSTR&t;0xa412fe92&t;/* Byte access */
DECL|macro|TMU0_TCOR
mdefine_line|#define TMU0_TCOR&t;0xa412fe94&t;/* Long access */
DECL|macro|TMU0_TCNT
mdefine_line|#define TMU0_TCNT&t;0xa412fe98&t;/* Long access */
DECL|macro|TMU0_TCR
mdefine_line|#define TMU0_TCR&t;0xa412fe9c&t;/* Word access */
DECL|macro|TMU1_TCOR
mdefine_line|#define TMU1_TCOR&t;0xa412fea0&t;/* Long access */
DECL|macro|TMU1_TCNT
mdefine_line|#define TMU1_TCNT&t;0xa412fea4&t;/* Long access */
DECL|macro|TMU1_TCR
mdefine_line|#define TMU1_TCR&t;0xa412fea8&t;/* Word access */
DECL|macro|TMU2_TCOR
mdefine_line|#define TMU2_TCOR&t;0xa412feac&t;/* Long access */
DECL|macro|TMU2_TCNT
mdefine_line|#define TMU2_TCNT&t;0xa412feb0&t;/* Long access */
DECL|macro|TMU2_TCR
mdefine_line|#define TMU2_TCR&t;0xa412feb4&t;/* Word access */
macro_line|#else
macro_line|#if !defined(CONFIG_CPU_SUBTYPE_SH7727)
DECL|macro|TMU_TOCR
mdefine_line|#define TMU_TOCR&t;0xfffffe90&t;/* Byte access */
macro_line|#endif
DECL|macro|TMU_TSTR
mdefine_line|#define TMU_TSTR&t;0xfffffe92&t;/* Byte access */
DECL|macro|TMU0_TCOR
mdefine_line|#define TMU0_TCOR&t;0xfffffe94&t;/* Long access */
DECL|macro|TMU0_TCNT
mdefine_line|#define TMU0_TCNT&t;0xfffffe98&t;/* Long access */
DECL|macro|TMU0_TCR
mdefine_line|#define TMU0_TCR&t;0xfffffe9c&t;/* Word access */
DECL|macro|TMU1_TCOR
mdefine_line|#define TMU1_TCOR&t;0xfffffea0&t;/* Long access */
DECL|macro|TMU1_TCNT
mdefine_line|#define TMU1_TCNT&t;0xfffffea4&t;/* Long access */
DECL|macro|TMU1_TCR
mdefine_line|#define TMU1_TCR&t;0xfffffea8&t;/* Word access */
DECL|macro|TMU2_TCOR
mdefine_line|#define TMU2_TCOR&t;0xfffffeac&t;/* Long access */
DECL|macro|TMU2_TCNT
mdefine_line|#define TMU2_TCNT&t;0xfffffeb0&t;/* Long access */
DECL|macro|TMU2_TCR
mdefine_line|#define TMU2_TCR&t;0xfffffeb4&t;/* Word access */
macro_line|#if !defined(CONFIG_CPU_SUBTYPE_SH7727)
DECL|macro|TMU2_TCPR2
mdefine_line|#define TMU2_TCPR2&t;0xfffffeb8&t;/* Long access */
macro_line|#endif
macro_line|#endif
macro_line|#endif /* __ASM_CPU_SH3_TIMER_H */
eof
