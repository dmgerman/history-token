multiline_comment|/*&n; *  linux/include/asm-arm/param.h&n; *&n; *  Copyright (C) 1995-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef __ASM_PARAM_H
DECL|macro|__ASM_PARAM_H
mdefine_line|#define __ASM_PARAM_H
macro_line|#ifdef __KERNEL__
macro_line|# include &lt;asm/arch/param.h&gt;&t;&t;/* for kernel version of HZ */
macro_line|# ifndef HZ
DECL|macro|HZ
macro_line|#  define HZ&t;&t;100&t;&t;/* Internal kernel timer frequency */
macro_line|# endif
DECL|macro|USER_HZ
macro_line|# define USER_HZ&t;100&t;&t;/* User interfaces are in &quot;ticks&quot; */
DECL|macro|CLOCKS_PER_SEC
macro_line|# define CLOCKS_PER_SEC&t;(USER_HZ)&t;/* like times() */
macro_line|#else
DECL|macro|HZ
macro_line|# define HZ&t;&t;100
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE&t;4096
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
mdefine_line|#define NOGROUP         (-1)
macro_line|#endif
multiline_comment|/* max length of hostname */
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN  64
macro_line|#endif
eof
