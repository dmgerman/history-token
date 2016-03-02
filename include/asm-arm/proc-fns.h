multiline_comment|/*&n; *  linux/include/asm-arm/proc-fns.h&n; *&n; *  Copyright (C) 1997-1999 Russell King&n; *  Copyright (C) 2000 Deep Blue Solutions Ltd&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_PROCFNS_H
DECL|macro|__ASM_PROCFNS_H
mdefine_line|#define __ASM_PROCFNS_H
macro_line|#ifdef __KERNEL__
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Work out if we need multiple CPU support&n; */
DECL|macro|MULTI_CPU
macro_line|#undef MULTI_CPU
DECL|macro|CPU_NAME
macro_line|#undef CPU_NAME
multiline_comment|/*&n; * CPU_NAME - the prefix for CPU related functions&n; */
macro_line|#ifdef CONFIG_CPU_32
macro_line|# ifdef CONFIG_CPU_ARM610
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm6
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_ARM710
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm7
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_ARM720T
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm720
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_ARM920T
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm920
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_ARM922T
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm922
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_ARM925T
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm925
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_ARM926T
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm926
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_SA110
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_sa110
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_SA1100
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_sa1100
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_ARM1020
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm1020
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_ARM1020E
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm1020e
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_ARM1022
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm1022
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_ARM1026
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm1026
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_XSCALE
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_xscale
macro_line|#  endif
macro_line|# endif
macro_line|# ifdef CONFIG_CPU_V6
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_v6
macro_line|#  endif
macro_line|# endif
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
macro_line|#ifndef MULTI_CPU
macro_line|#include &quot;asm/cpu-single.h&quot;
macro_line|#else
macro_line|#include &quot;asm/cpu-multi32.h&quot;
macro_line|#endif
macro_line|#include &lt;asm/memory.h&gt;
DECL|macro|cpu_switch_mm
mdefine_line|#define cpu_switch_mm(pgd,mm) cpu_do_switch_mm(virt_to_phys(pgd),mm)
DECL|macro|cpu_get_pgd
mdefine_line|#define cpu_get_pgd()&t;&bslash;&n;&t;({&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;unsigned long pg;&t;&t;&t;&bslash;&n;&t;&t;__asm__(&quot;mrc&t;p15, 0, %0, c2, c0, 0&quot;&t;&bslash;&n;&t;&t;&t; : &quot;=r&quot; (pg) : : &quot;cc&quot;);&t;&t;&bslash;&n;&t;&t;pg &amp;= ~0x3fff;&t;&t;&t;&t;&bslash;&n;&t;&t;(pgd_t *)phys_to_virt(pg);&t;&t;&bslash;&n;&t;})
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* __ASM_PROCFNS_H */
eof
