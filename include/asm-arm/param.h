multiline_comment|/*&n; *  linux/include/asm-arm/param.h&n; *&n; *  Copyright (C) 1995-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_PARAM_H
DECL|macro|__ASM_PARAM_H
mdefine_line|#define __ASM_PARAM_H
macro_line|#include &lt;asm/arch/param.h&gt;&t;/* for HZ */
macro_line|#include &lt;asm/proc/page.h&gt;&t;/* for EXEC_PAGE_SIZE */
macro_line|#ifndef HZ
DECL|macro|HZ
mdefine_line|#define HZ 100
macro_line|#endif
macro_line|#if defined(__KERNEL__) &amp;&amp; (HZ == 100)
DECL|macro|hz_to_std
mdefine_line|#define hz_to_std(a) (a)
macro_line|#endif
macro_line|#ifndef NGROUPS
DECL|macro|NGROUPS
mdefine_line|#define NGROUPS         32
macro_line|#endif
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
mdefine_line|#define NOGROUP         (-1)
macro_line|#endif
multiline_comment|/* max length of hostname */
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN  64
macro_line|#ifdef __KERNEL__
DECL|macro|CLOCKS_PER_SEC
macro_line|# define CLOCKS_PER_SEC&t;HZ
macro_line|#endif
macro_line|#endif
eof
