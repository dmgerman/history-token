macro_line|#ifndef _ASM_IA64_PARAM_H
DECL|macro|_ASM_IA64_PARAM_H
mdefine_line|#define _ASM_IA64_PARAM_H
multiline_comment|/*&n; * Fundamental kernel parameters.&n; *&n; * Copyright (C) 1998, 1999 Hewlett-Packard Co&n; * Copyright (C) 1998, 1999 David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_IA64_HP_SIM
multiline_comment|/*&n; * Yeah, simulating stuff is slow, so let us catch some breath between&n; * timer interrupts...&n; */
DECL|macro|HZ
macro_line|# define HZ&t;  32
macro_line|#else
DECL|macro|HZ
macro_line|# define HZ&t;1024
macro_line|#endif
DECL|macro|EXEC_PAGESIZE
mdefine_line|#define EXEC_PAGESIZE&t;65536
macro_line|#ifndef NGROUPS
DECL|macro|NGROUPS
macro_line|# define NGROUPS&t;32
macro_line|#endif
macro_line|#ifndef NOGROUP
DECL|macro|NOGROUP
macro_line|# define NOGROUP&t;(-1)
macro_line|#endif
DECL|macro|MAXHOSTNAMELEN
mdefine_line|#define MAXHOSTNAMELEN&t;64&t;/* max length of hostname */
macro_line|#ifdef __KERNEL__
DECL|macro|CLOCKS_PER_SEC
macro_line|# define CLOCKS_PER_SEC&t;HZ&t;/* frequency at which times() counts */
macro_line|#endif
macro_line|#endif /* _ASM_IA64_PARAM_H */
eof
