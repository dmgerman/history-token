multiline_comment|/* &n; * Copyright (C) 2000 - 2004  Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#ifndef _UM_UNISTD_H_
DECL|macro|_UM_UNISTD_H_
mdefine_line|#define _UM_UNISTD_H_
macro_line|#include &lt;linux/syscalls.h&gt;
macro_line|#include &quot;linux/resource.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
r_extern
r_int
id|um_execve
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_char
op_star
r_const
id|argv
(braket
)braket
comma
r_char
op_star
r_const
id|env
(braket
)braket
)paren
suffix:semicolon
macro_line|#ifdef __KERNEL__
multiline_comment|/* We get __ARCH_WANT_OLD_STAT and __ARCH_WANT_STAT64 from the base arch */
DECL|macro|__ARCH_WANT_IPC_PARSE_VERSION
mdefine_line|#define __ARCH_WANT_IPC_PARSE_VERSION
DECL|macro|__ARCH_WANT_OLD_READDIR
mdefine_line|#define __ARCH_WANT_OLD_READDIR
DECL|macro|__ARCH_WANT_SYS_ALARM
mdefine_line|#define __ARCH_WANT_SYS_ALARM
DECL|macro|__ARCH_WANT_SYS_GETHOSTNAME
mdefine_line|#define __ARCH_WANT_SYS_GETHOSTNAME
DECL|macro|__ARCH_WANT_SYS_PAUSE
mdefine_line|#define __ARCH_WANT_SYS_PAUSE
DECL|macro|__ARCH_WANT_SYS_SGETMASK
mdefine_line|#define __ARCH_WANT_SYS_SGETMASK
DECL|macro|__ARCH_WANT_SYS_SIGNAL
mdefine_line|#define __ARCH_WANT_SYS_SIGNAL
DECL|macro|__ARCH_WANT_SYS_TIME
mdefine_line|#define __ARCH_WANT_SYS_TIME
DECL|macro|__ARCH_WANT_SYS_UTIME
mdefine_line|#define __ARCH_WANT_SYS_UTIME
DECL|macro|__ARCH_WANT_SYS_WAITPID
mdefine_line|#define __ARCH_WANT_SYS_WAITPID
DECL|macro|__ARCH_WANT_SYS_SOCKETCALL
mdefine_line|#define __ARCH_WANT_SYS_SOCKETCALL
DECL|macro|__ARCH_WANT_SYS_FADVISE64
mdefine_line|#define __ARCH_WANT_SYS_FADVISE64
DECL|macro|__ARCH_WANT_SYS_GETPGRP
mdefine_line|#define __ARCH_WANT_SYS_GETPGRP
DECL|macro|__ARCH_WANT_SYS_LLSEEK
mdefine_line|#define __ARCH_WANT_SYS_LLSEEK
DECL|macro|__ARCH_WANT_SYS_NICE
mdefine_line|#define __ARCH_WANT_SYS_NICE
DECL|macro|__ARCH_WANT_SYS_OLD_GETRLIMIT
mdefine_line|#define __ARCH_WANT_SYS_OLD_GETRLIMIT
DECL|macro|__ARCH_WANT_SYS_OLDUMOUNT
mdefine_line|#define __ARCH_WANT_SYS_OLDUMOUNT
DECL|macro|__ARCH_WANT_SYS_SIGPENDING
mdefine_line|#define __ARCH_WANT_SYS_SIGPENDING
DECL|macro|__ARCH_WANT_SYS_SIGPROCMASK
mdefine_line|#define __ARCH_WANT_SYS_SIGPROCMASK
DECL|macro|__ARCH_WANT_SYS_RT_SIGACTION
mdefine_line|#define __ARCH_WANT_SYS_RT_SIGACTION
macro_line|#endif
macro_line|#ifdef __KERNEL_SYSCALLS__
macro_line|#include &lt;linux/compiler.h&gt;
macro_line|#include &lt;linux/types.h&gt;
DECL|function|execve
r_static
r_inline
r_int
id|execve
c_func
(paren
r_const
r_char
op_star
id|filename
comma
r_char
op_star
r_const
id|argv
(braket
)braket
comma
r_char
op_star
r_const
id|envp
(braket
)braket
)paren
(brace
id|mm_segment_t
id|fs
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|ret
op_assign
id|um_execve
c_func
(paren
id|filename
comma
id|argv
comma
id|envp
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ge
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|errno
op_assign
op_minus
(paren
r_int
)paren
id|ret
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_int
id|sys_execve
c_func
(paren
r_char
op_star
id|file
comma
r_char
op_star
op_star
id|argv
comma
r_char
op_star
op_star
id|env
)paren
suffix:semicolon
macro_line|#endif /* __KERNEL_SYSCALLS__ */
DECL|macro|__KERNEL_SYSCALLS__
macro_line|#undef __KERNEL_SYSCALLS__
macro_line|#include &quot;asm/arch/unistd.h&quot;
macro_line|#endif /* _UM_UNISTD_H_*/
eof
