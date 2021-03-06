multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &quot;ptrace_user.h&quot;
multiline_comment|/* Grr, asm/user.h includes asm/ptrace.h, so has to follow ptrace_user.h */
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;sysdep/thread.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|function|ptrace_getregs
r_int
id|ptrace_getregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs_out
)paren
(brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_GETREGS
comma
id|pid
comma
l_int|0
comma
id|regs_out
)paren
OL
l_int|0
)paren
r_return
op_minus
id|errno
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ptrace_setregs
r_int
id|ptrace_setregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_SETREGS
comma
id|pid
comma
l_int|0
comma
id|regs
)paren
OL
l_int|0
)paren
r_return
op_minus
id|errno
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ptrace_getfpregs
r_int
id|ptrace_getfpregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_GETFPREGS
comma
id|pid
comma
l_int|0
comma
id|regs
)paren
OL
l_int|0
)paren
r_return
op_minus
id|errno
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ptrace_setfpregs
r_int
id|ptrace_setfpregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_SETFPREGS
comma
id|pid
comma
l_int|0
comma
id|regs
)paren
OL
l_int|0
)paren
r_return
op_minus
id|errno
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|write_debugregs
r_static
r_void
id|write_debugregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs
)paren
(brace
r_struct
id|user
op_star
id|dummy
suffix:semicolon
r_int
id|nregs
comma
id|i
suffix:semicolon
id|dummy
op_assign
l_int|NULL
suffix:semicolon
id|nregs
op_assign
r_sizeof
(paren
id|dummy-&gt;u_debugreg
)paren
op_div
r_sizeof
(paren
id|dummy-&gt;u_debugreg
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nregs
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_eq
l_int|4
)paren
op_logical_or
(paren
id|i
op_eq
l_int|5
)paren
)paren
(brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_POKEUSR
comma
id|pid
comma
op_amp
id|dummy-&gt;u_debugreg
(braket
id|i
)braket
comma
id|regs
(braket
id|i
)braket
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;write_debugregs - ptrace failed on &quot;
l_string|&quot;register %d, value = 0x%x, errno = %d&bslash;n&quot;
comma
id|i
comma
id|regs
(braket
id|i
)braket
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|read_debugregs
r_static
r_void
id|read_debugregs
c_func
(paren
r_int
id|pid
comma
r_int
r_int
op_star
id|regs
)paren
(brace
r_struct
id|user
op_star
id|dummy
suffix:semicolon
r_int
id|nregs
comma
id|i
suffix:semicolon
id|dummy
op_assign
l_int|NULL
suffix:semicolon
id|nregs
op_assign
r_sizeof
(paren
id|dummy-&gt;u_debugreg
)paren
op_div
r_sizeof
(paren
id|dummy-&gt;u_debugreg
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nregs
suffix:semicolon
id|i
op_increment
)paren
(brace
id|regs
(braket
id|i
)braket
op_assign
id|ptrace
c_func
(paren
id|PTRACE_PEEKUSR
comma
id|pid
comma
op_amp
id|dummy-&gt;u_debugreg
(braket
id|i
)braket
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Accessed only by the tracing thread */
DECL|variable|kernel_debugregs
r_static
r_int
r_int
id|kernel_debugregs
(braket
l_int|8
)braket
op_assign
(brace
(braket
l_int|0
dot
dot
dot
l_int|7
)braket
op_assign
l_int|0
)brace
suffix:semicolon
DECL|variable|debugregs_seq
r_static
r_int
id|debugregs_seq
op_assign
l_int|0
suffix:semicolon
DECL|function|arch_enter_kernel
r_void
id|arch_enter_kernel
c_func
(paren
r_void
op_star
id|task
comma
r_int
id|pid
)paren
(brace
id|read_debugregs
c_func
(paren
id|pid
comma
id|TASK_DEBUGREGS
c_func
(paren
id|task
)paren
)paren
suffix:semicolon
id|write_debugregs
c_func
(paren
id|pid
comma
id|kernel_debugregs
)paren
suffix:semicolon
)brace
DECL|function|arch_leave_kernel
r_void
id|arch_leave_kernel
c_func
(paren
r_void
op_star
id|task
comma
r_int
id|pid
)paren
(brace
id|read_debugregs
c_func
(paren
id|pid
comma
id|kernel_debugregs
)paren
suffix:semicolon
id|write_debugregs
c_func
(paren
id|pid
comma
id|TASK_DEBUGREGS
c_func
(paren
id|task
)paren
)paren
suffix:semicolon
)brace
DECL|function|ptrace_pokeuser
r_void
id|ptrace_pokeuser
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|data
)paren
(brace
r_if
c_cond
(paren
(paren
id|addr
OL
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|0
)braket
)paren
)paren
op_logical_or
(paren
id|addr
OG
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|7
)braket
)paren
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
id|addr
op_sub_assign
m_offsetof
(paren
r_struct
id|user
comma
id|u_debugreg
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|addr
op_assign
id|addr
op_rshift
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|kernel_debugregs
(braket
id|addr
)braket
op_eq
id|data
)paren
(brace
r_return
suffix:semicolon
)brace
id|kernel_debugregs
(braket
id|addr
)braket
op_assign
id|data
suffix:semicolon
id|debugregs_seq
op_increment
suffix:semicolon
)brace
DECL|function|update_debugregs_cb
r_static
r_void
id|update_debugregs_cb
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_int
id|pid
op_assign
op_star
(paren
(paren
r_int
op_star
)paren
id|arg
)paren
suffix:semicolon
id|write_debugregs
c_func
(paren
id|pid
comma
id|kernel_debugregs
)paren
suffix:semicolon
)brace
DECL|function|update_debugregs
r_void
id|update_debugregs
c_func
(paren
r_int
id|seq
)paren
(brace
r_int
id|me
suffix:semicolon
r_if
c_cond
(paren
id|seq
op_eq
id|debugregs_seq
)paren
(brace
r_return
suffix:semicolon
)brace
id|me
op_assign
id|os_getpid
c_func
(paren
)paren
suffix:semicolon
id|initial_thread_cb
c_func
(paren
id|update_debugregs_cb
comma
op_amp
id|me
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
