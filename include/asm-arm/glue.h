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
multiline_comment|/*&n; *&t;MMU TLB Model&n; *&t;=============&n; *&n; *&t;We have the following to choose from:&n; *&t;  v3    - ARMv3&n; *&t;  v4    - ARMv4 without write buffer&n; *&t;  v4wb  - ARMv4 with write buffer without I TLB flush entry instruction&n; *&t;  v4wbi - ARMv4 with write buffer with I TLB flush entry instruction&n; */
DECL|macro|_TLB
macro_line|#undef _TLB
DECL|macro|MULTI_TLB
macro_line|#undef MULTI_TLB
macro_line|#if defined(CONFIG_CPU_ARM610) || defined(CONFIG_CPU_ARM710)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v3
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_ARM720T)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_ARM920T) || defined(CONFIG_CPU_ARM922T) || &bslash;&n;    defined(CONFIG_CPU_ARM926T) || defined(CONFIG_CPU_ARM1020) || &bslash;&n;    defined(CONFIG_CPU_XSCALE)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4wbi
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_SA110) || defined(CONFIG_CPU_SA1100)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4wb
macro_line|# endif
macro_line|#endif
macro_line|#ifndef _TLB
macro_line|#error Unknown TLB model
macro_line|#endif
multiline_comment|/*&n; *&t;Data Abort Model&n; *&t;================&n; *&n; *&t;We have the following to choose from:&n; *&t;  arm6          - ARM6 style&n; *&t;  arm7&t;&t;- ARM7 style&n; *&t;  v4_early&t;- ARMv4 without Thumb early abort handler&n; *&t;  v4t_late&t;- ARMv4 with Thumb late abort handler&n; *&t;  v4t_early&t;- ARMv4 with Thumb early abort handler&n; *&t;  v5ej_early&t;- ARMv5 with Thumb and Java early abort handler&n; */
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
macro_line|#if defined(CONFIG_CPU_ARM720T)
macro_line|# ifdef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#  define MULTI_ABORT 1
macro_line|# else
DECL|macro|CPU_ABORT_HANDLER
macro_line|#  define CPU_ABORT_HANDLER v4t_late_abort
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_SA110) || defined(CONFIG_CPU_SA1100)
macro_line|# ifdef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#  define MULTI_ABORT 1
macro_line|# else
DECL|macro|CPU_ABORT_HANDLER
macro_line|#  define CPU_ABORT_HANDLER v4_early_abort
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_ARM920T) || defined(CONFIG_CPU_ARM922T) || &bslash;&n;    defined(CONFIG_CPU_ARM1020) || defined(CONFIG_CPU_XSCALE)
macro_line|# ifdef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#  define MULTI_ABORT 1
macro_line|# else
DECL|macro|CPU_ABORT_HANDLER
macro_line|#  define CPU_ABORT_HANDLER v4t_early_abort
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_ARM926T)
macro_line|# ifdef CPU_ABORT_HANDLER
DECL|macro|MULTI_ABORT
macro_line|#  define MULTI_ABORT 1
macro_line|# else
DECL|macro|CPU_ABORT_HANDLER
macro_line|#  define CPU_ABORT_HANDLER v5ej_early_abort
macro_line|# endif
macro_line|#endif
macro_line|#ifndef CPU_ABORT_HANDLER
macro_line|#error Unknown data abort handler type
macro_line|#endif
multiline_comment|/*&n; *&t;User Space Model&n; *&t;================&n; *&n; *&t;This section selects the correct set of functions for dealing with&n; *&t;page-based copying and clearing for user space for the particular&n; *&t;processor(s) we&squot;re building for.&n; *&n; *&t;We have the following to choose from:&n; *&t;  v3&t;&t;- ARMv3&n; *&t;  v4&t;&t;- ARMv4 without minicache&n; *&t;  v4_mc&t;&t;- ARMv4 with minicache&n; *&t;  v5te_mc&t;- ARMv5TE with minicache&n; */
DECL|macro|_USER
macro_line|#undef _USER
DECL|macro|MULTI_USER
macro_line|#undef MULTI_USER
macro_line|#if defined(CONFIG_CPU_ARM610) || defined(CONFIG_CPU_ARM710)
macro_line|# ifdef _USER
DECL|macro|MULTI_USER
macro_line|#  define MULTI_USER 1
macro_line|# else
DECL|macro|_USER
macro_line|#  define _USER v3
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_ARM720T) || defined(CONFIG_CPU_ARM920T) || &bslash;&n;    defined(CONFIG_CPU_ARM922T) || defined(CONFIG_CPU_ARM926T) || &bslash;&n;    defined(CONFIG_CPU_SA110)   || defined(CONFIG_CPU_ARM1020)
macro_line|# ifdef _USER
DECL|macro|MULTI_USER
macro_line|#  define MULTI_USER 1
macro_line|# else
DECL|macro|_USER
macro_line|#  define _USER v4
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_SA1100)
macro_line|# ifdef _USER
DECL|macro|MULTI_USER
macro_line|#  define MULTI_USER 1
macro_line|# else
DECL|macro|_USER
macro_line|#  define _USER v4_mc
macro_line|# endif
macro_line|#endif
macro_line|#if defined(CONFIG_CPU_XSCALE)
macro_line|# ifdef _USER
DECL|macro|MULTI_USER
macro_line|#  define MULTI_USER 1
macro_line|# else
DECL|macro|_USER
macro_line|#  define _USER v5te_mc
macro_line|# endif
macro_line|#endif
macro_line|#ifndef _USER
macro_line|#error Unknown user operations model
macro_line|#endif
macro_line|#endif
eof
