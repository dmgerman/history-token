multiline_comment|/*&n; *  linux/include/asm-arm/glue.h&n; *&n; *  Copyright (C) 1997-1999 Russell King&n; *  Copyright (C) 2000-2002 Deep Blue Solutions Ltd.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This file provides the glue to stick the processor-specific bits&n; *  into the kernel in an efficient manner.  The idea is to use branches&n; *  when we&squot;re only targetting one class of TLB, or indirect calls&n; *  when we&squot;re targetting multiple classes of TLBs.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef __STDC__
DECL|macro|____glue
mdefine_line|#define ____glue(name,fn)&t;name##fn
macro_line|#else
DECL|macro|____glue
mdefine_line|#define ____glue(name,fn)&t;name/**/fn
macro_line|#endif
DECL|macro|__glue
mdefine_line|#define __glue(name,fn)&t;&t;____glue(name,fn)
multiline_comment|/*&n; *&t;Data Abort Model&n; *&t;================&n; *&n; *&t;We have the following to choose from:&n; *&t;  arm6          - ARM6 style&n; *&t;  arm7&t;&t;- ARM7 style&n; *&t;  v4_early&t;- ARMv4 without Thumb early abort handler&n; *&t;  v4t_late&t;- ARMv4 with Thumb late abort handler&n; *&t;  v4t_early&t;- ARMv4 with Thumb early abort handler&n; *&t;  v5tej_early&t;- ARMv5 with Thumb and Java early abort handler&n; *&t;  xscale&t;- ARMv5 with Thumb with Xscale extensions&n; */
DECL|macro|CPU_ABORT_HANDLER
macro_line|#undef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#undef MULTI_ABORT
macro_line|#if defined(CONFIG_CPU_ARM610)
macro_line|# ifdef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#  define MULTI_ABORT 1
macro_line|# else
DECL|macro|CPU_ABORT_HANDLER
macro_line|#  define CPU_ABORT_HANDLER cpu_arm6_data_abort
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_ARM710)
macro_line|# ifdef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#  define MULTI_ABORT 1
macro_line|# else
DECL|macro|CPU_ABORT_HANDLER
macro_line|#  define CPU_ABORT_HANDLER cpu_arm7_data_abort
macro_line|# endif
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_ABRT_LV4T
macro_line|# ifdef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#  define MULTI_ABORT 1
macro_line|# else
DECL|macro|CPU_ABORT_HANDLER
macro_line|#  define CPU_ABORT_HANDLER v4t_late_abort
macro_line|# endif
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_ABRT_EV4
macro_line|# ifdef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#  define MULTI_ABORT 1
macro_line|# else
DECL|macro|CPU_ABORT_HANDLER
macro_line|#  define CPU_ABORT_HANDLER v4_early_abort
macro_line|# endif
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_ABRT_EV4T
macro_line|# ifdef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#  define MULTI_ABORT 1
macro_line|# else
DECL|macro|CPU_ABORT_HANDLER
macro_line|#  define CPU_ABORT_HANDLER v4t_early_abort
macro_line|# endif
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_ABRT_EV5TJ
macro_line|# ifdef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#  define MULTI_ABORT 1
macro_line|# else
DECL|macro|CPU_ABORT_HANDLER
macro_line|#  define CPU_ABORT_HANDLER v5tj_early_abort
macro_line|# endif
macro_line|#endif
macro_line|#ifdef CONFIG_CPU_ABORT_EV5T
macro_line|# ifdef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#  define MULTI_ABORT 1
macro_line|# else
DECL|macro|CPU_ABORT_HANDLER
macro_line|#  define CPU_ABORT_HANDLER v5t_early_abort
macro_line|# endif
macro_line|#endif
macro_line|#ifndef CPU_ABORT_HANDLER
macro_line|#error Unknown data abort handler type
macro_line|#endif
macro_line|#endif
eof
