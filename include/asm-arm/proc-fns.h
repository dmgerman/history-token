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
macro_line|#ifdef CONFIG_CPU_26
DECL|macro|CPU_INCLUDE_NAME
macro_line|# define CPU_INCLUDE_NAME &quot;asm/cpu-multi26.h&quot;
DECL|macro|MULTI_CPU
macro_line|# define MULTI_CPU
macro_line|#endif
multiline_comment|/*&n; * CPU_NAME - the prefix for CPU related functions&n; * MMU_ARCH - the prefix for copy_user_page/clear_user_page&n; */
macro_line|#ifdef CONFIG_CPU_32
DECL|macro|CPU_INCLUDE_NAME
macro_line|# define CPU_INCLUDE_NAME &quot;asm/cpu-multi32.h&quot;
macro_line|# ifdef CONFIG_CPU_ARM610
macro_line|#  ifdef CPU_NAME
DECL|macro|MULTI_CPU
macro_line|#   undef  MULTI_CPU
DECL|macro|MULTI_CPU
macro_line|#   define MULTI_CPU
macro_line|#  else
DECL|macro|CPU_NAME
macro_line|#   define CPU_NAME cpu_arm6
DECL|macro|MMU_ARCH
macro_line|#   define MMU_ARCH armv3
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
DECL|macro|MMU_ARCH
macro_line|#   define MMU_ARCH armv3
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
DECL|macro|MMU_ARCH
macro_line|#   define MMU_ARCH armv4
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
DECL|macro|MMU_ARCH
macro_line|#   define MMU_ARCH armv4
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
DECL|macro|MMU_ARCH
macro_line|#   define MMU_ARCH armv4
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
DECL|macro|MMU_ARCH
macro_line|#   define MMU_ARCH armv4
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
DECL|macro|MMU_ARCH
macro_line|#   define MMU_ARCH armv4
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
DECL|macro|MMU_ARCH
macro_line|#   define MMU_ARCH armv4_mc
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
DECL|macro|MMU_ARCH
macro_line|#   define MMU_ARCH armv4
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
DECL|macro|MMU_ARCH
macro_line|#   define MMU_ARCH armv5te
macro_line|#  endif
macro_line|# endif
macro_line|#endif
macro_line|#ifndef MULTI_CPU
DECL|macro|CPU_INCLUDE_NAME
macro_line|#undef CPU_INCLUDE_NAME
DECL|macro|CPU_INCLUDE_NAME
mdefine_line|#define CPU_INCLUDE_NAME &quot;asm/cpu-single.h&quot;
macro_line|#endif
macro_line|#include CPU_INCLUDE_NAME
macro_line|#endif /* __KERNEL__ */
macro_line|#if 0
op_star
id|The
id|following
id|is
id|to
id|fool
id|mkdep
id|into
id|generating
id|the
id|correct
op_star
id|dependencies
dot
id|Without
id|this
comma
id|it
id|cant
id|figure
id|out
id|that
id|this
op_star
id|file
id|does
id|indeed
id|depend
id|on
id|the
id|cpu
op_minus
op_star
dot
id|h
id|files
dot
macro_line|#include &lt;asm/cpu-single.h&gt;
macro_line|#include &lt;asm/cpu-multi26.h&gt;
macro_line|#include &lt;asm/cpu-multi32.h&gt;
op_star
macro_line|#endif
macro_line|#endif /* __ASM_PROCFNS_H */
eof
