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
multiline_comment|/*&n; * Select MMU TLB handling.&n; */
multiline_comment|/*&n; * ARMv3 MMU&n; */
DECL|macro|_TLB
macro_line|#undef _TLB
macro_line|#if defined(CONFIG_CPU_ARM610) || defined(CONFIG_CPU_ARM710)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v3
macro_line|# endif
macro_line|#endif
multiline_comment|/*&n; * ARMv4 MMU without write buffer&n; */
macro_line|#if defined(CONFIG_CPU_ARM720T)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4
macro_line|# endif
macro_line|#endif
multiline_comment|/*&n; * ARMv4 MMU with write buffer, with invalidate I TLB entry instruction&n; */
macro_line|#if defined(CONFIG_CPU_ARM920T) || defined(CONFIG_CPU_ARM922T) || &bslash;&n;    defined(CONFIG_CPU_ARM926T) || defined(CONFIG_CPU_ARM1020) || &bslash;&n;    defined(CONFIG_CPU_XSCALE)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4wbi
macro_line|# endif
macro_line|#endif
multiline_comment|/*&n; * ARMv4 MMU with write buffer, without invalidate I TLB entry instruction&n; */
macro_line|#if defined(CONFIG_CPU_SA110) || defined(CONFIG_CPU_SA1100)
macro_line|# ifdef _TLB
DECL|macro|MULTI_TLB
macro_line|#  define MULTI_TLB 1
macro_line|# else
DECL|macro|_TLB
macro_line|#  define _TLB v4wb
macro_line|# endif
macro_line|#endif
macro_line|#endif
eof
