multiline_comment|/*&n; * linux/kernel/seccomp.c&n; *&n; * Copyright 2004-2005  Andrea Arcangeli &lt;andrea@cpushare.com&gt;&n; *&n; * This defines a simple but solid secure-computing mode.&n; */
macro_line|#include &lt;linux/seccomp.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#ifdef TIF_IA32
macro_line|#include &lt;asm/ia32_unistd.h&gt;
macro_line|#endif
multiline_comment|/* #define SECCOMP_DEBUG 1 */
multiline_comment|/*&n; * Secure computing mode 1 allows only read/write/exit/sigreturn.&n; * To be fully secure this must be combined with rlimit&n; * to limit the stack allocations too.&n; */
DECL|variable|mode1_syscalls
r_static
r_int
id|mode1_syscalls
(braket
)braket
op_assign
(brace
id|__NR_read
comma
id|__NR_write
comma
id|__NR_exit
comma
multiline_comment|/*&n;&t; * Allow either sigreturn or rt_sigreturn, newer archs&n;&t; * like x86-64 only defines __NR_rt_sigreturn.&n;&t; */
macro_line|#ifdef __NR_sigreturn
id|__NR_sigreturn
comma
macro_line|#else
id|__NR_rt_sigreturn
comma
macro_line|#endif
l_int|0
comma
multiline_comment|/* null terminated */
)brace
suffix:semicolon
macro_line|#ifdef TIF_IA32
DECL|variable|mode1_syscalls_32bit
r_static
r_int
id|mode1_syscalls_32bit
(braket
)braket
op_assign
(brace
id|__NR_ia32_read
comma
id|__NR_ia32_write
comma
id|__NR_ia32_exit
comma
multiline_comment|/*&n;&t; * Allow either sigreturn or rt_sigreturn, newer archs&n;&t; * like x86-64 only defines __NR_rt_sigreturn.&n;&t; */
id|__NR_ia32_sigreturn
comma
l_int|0
comma
multiline_comment|/* null terminated */
)brace
suffix:semicolon
macro_line|#endif
DECL|function|__secure_computing
r_void
id|__secure_computing
c_func
(paren
r_int
id|this_syscall
)paren
(brace
r_int
id|mode
op_assign
id|current-&gt;seccomp.mode
suffix:semicolon
r_int
op_star
id|syscall
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
l_int|1
suffix:colon
id|syscall
op_assign
id|mode1_syscalls
suffix:semicolon
macro_line|#ifdef TIF_IA32
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_IA32
)paren
)paren
id|syscall
op_assign
id|mode1_syscalls_32bit
suffix:semicolon
macro_line|#endif
r_do
(brace
r_if
c_cond
(paren
op_star
id|syscall
op_eq
id|this_syscall
)paren
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
op_star
op_increment
id|syscall
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifdef SECCOMP_DEBUG
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|do_exit
c_func
(paren
id|SIGKILL
)paren
suffix:semicolon
)brace
eof
