multiline_comment|/**********************************************************************&n;sysdep.c&n;&n;Copyright (C) 1999 Lars Brinkhoff.  See the file COPYING for licensing&n;terms and conditions.&n;**********************************************************************/
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &quot;ptrace_user.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;user.h&quot;
DECL|function|get_syscall
r_int
id|get_syscall
c_func
(paren
id|pid_t
id|pid
comma
r_int
op_star
id|arg1
comma
r_int
op_star
id|arg2
comma
r_int
op_star
id|arg3
comma
r_int
op_star
id|arg4
comma
r_int
op_star
id|arg5
)paren
(brace
op_star
id|arg1
op_assign
id|ptrace
c_func
(paren
id|PTRACE_PEEKUSER
comma
id|pid
comma
id|PT_SYSCALL_ARG1_OFFSET
comma
l_int|0
)paren
suffix:semicolon
op_star
id|arg2
op_assign
id|ptrace
c_func
(paren
id|PTRACE_PEEKUSER
comma
id|pid
comma
id|PT_SYSCALL_ARG2_OFFSET
comma
l_int|0
)paren
suffix:semicolon
op_star
id|arg3
op_assign
id|ptrace
c_func
(paren
id|PTRACE_PEEKUSER
comma
id|pid
comma
id|PT_SYSCALL_ARG3_OFFSET
comma
l_int|0
)paren
suffix:semicolon
op_star
id|arg4
op_assign
id|ptrace
c_func
(paren
id|PTRACE_PEEKUSER
comma
id|pid
comma
id|PT_SYSCALL_ARG4_OFFSET
comma
l_int|0
)paren
suffix:semicolon
op_star
id|arg5
op_assign
id|ptrace
c_func
(paren
id|PTRACE_PEEKUSER
comma
id|pid
comma
id|PT_SYSCALL_ARG5_OFFSET
comma
l_int|0
)paren
suffix:semicolon
r_return
id|ptrace
c_func
(paren
id|PTRACE_PEEKUSER
comma
id|pid
comma
id|PT_SYSCALL_NR_OFFSET
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|syscall_cancel
r_void
id|syscall_cancel
c_func
(paren
id|pid_t
id|pid
comma
r_int
id|result
)paren
(brace
r_if
c_cond
(paren
(paren
id|ptrace
c_func
(paren
id|PTRACE_POKEUSER
comma
id|pid
comma
id|PT_SYSCALL_NR_OFFSET
comma
id|__NR_getpid
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|ptrace
c_func
(paren
id|PTRACE_SYSCALL
comma
id|pid
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|wait_for_stop
c_func
(paren
id|pid
comma
id|SIGTRAP
comma
id|PTRACE_SYSCALL
comma
l_int|NULL
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|ptrace
c_func
(paren
id|PTRACE_POKEUSER
comma
id|pid
comma
id|PT_SYSCALL_RET_OFFSET
comma
id|result
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|ptrace
c_func
(paren
id|PTRACE_SYSCALL
comma
id|pid
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ptproxy: couldn&squot;t cancel syscall: errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|syscall_set_result
r_void
id|syscall_set_result
c_func
(paren
id|pid_t
id|pid
comma
r_int
id|result
)paren
(brace
id|ptrace
c_func
(paren
id|PTRACE_POKEUSER
comma
id|pid
comma
id|PT_SYSCALL_RET_OFFSET
comma
id|result
)paren
suffix:semicolon
)brace
DECL|function|syscall_continue
r_void
id|syscall_continue
c_func
(paren
id|pid_t
id|pid
)paren
(brace
id|ptrace
c_func
(paren
id|PTRACE_SYSCALL
comma
id|pid
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|syscall_pause
r_int
id|syscall_pause
c_func
(paren
id|pid_t
id|pid
)paren
(brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_POKEUSER
comma
id|pid
comma
id|PT_SYSCALL_NR_OFFSET
comma
id|__NR_pause
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;syscall_change - ptrace failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
