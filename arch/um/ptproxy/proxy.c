multiline_comment|/**********************************************************************&n;proxy.c&n;&n;Copyright (C) 1999 Lars Brinkhoff.  See the file COPYING for licensing&n;terms and conditions.&n;&n;Jeff Dike (jdike@karaya.com) : Modified for integration into uml&n;**********************************************************************/
multiline_comment|/* XXX This file shouldn&squot;t refer to CONFIG_* */
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;fcntl.h&gt;
macro_line|#include &lt;termios.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/types.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;sys/ioctl.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &quot;ptproxy.h&quot;
macro_line|#include &quot;sysdep.h&quot;
macro_line|#include &quot;wait.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;os.h&quot;
DECL|function|debugger_wait
r_static
r_int
id|debugger_wait
c_func
(paren
id|debugger_state
op_star
id|debugger
comma
r_int
op_star
id|status
comma
r_int
id|options
comma
r_int
(paren
op_star
id|syscall
)paren
(paren
id|debugger_state
op_star
id|debugger
comma
id|pid_t
id|child
)paren
comma
r_int
(paren
op_star
id|normal_return
)paren
(paren
id|debugger_state
op_star
id|debugger
comma
id|pid_t
id|unused
)paren
comma
r_int
(paren
op_star
id|wait_return
)paren
(paren
id|debugger_state
op_star
id|debugger
comma
id|pid_t
id|unused
)paren
)paren
(brace
r_if
c_cond
(paren
id|debugger-&gt;real_wait
)paren
(brace
id|debugger-&gt;handle_trace
op_assign
id|normal_return
suffix:semicolon
id|syscall_continue
c_func
(paren
id|debugger-&gt;pid
)paren
suffix:semicolon
id|debugger-&gt;real_wait
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|debugger-&gt;wait_status_ptr
op_assign
id|status
suffix:semicolon
id|debugger-&gt;wait_options
op_assign
id|options
suffix:semicolon
r_if
c_cond
(paren
(paren
id|debugger-&gt;debugee
op_ne
l_int|NULL
)paren
op_logical_and
id|debugger-&gt;debugee-&gt;event
)paren
(brace
id|syscall_continue
c_func
(paren
id|debugger-&gt;pid
)paren
suffix:semicolon
id|wait_for_stop
c_func
(paren
id|debugger-&gt;pid
comma
id|SIGTRAP
comma
id|PTRACE_SYSCALL
comma
l_int|NULL
)paren
suffix:semicolon
(paren
op_star
id|wait_return
)paren
(paren
id|debugger
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|debugger-&gt;wait_options
op_amp
id|WNOHANG
)paren
(brace
id|syscall_cancel
c_func
(paren
id|debugger-&gt;pid
comma
l_int|0
)paren
suffix:semicolon
id|debugger-&gt;handle_trace
op_assign
id|syscall
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|syscall_pause
c_func
(paren
id|debugger-&gt;pid
)paren
suffix:semicolon
id|debugger-&gt;handle_trace
op_assign
id|wait_return
suffix:semicolon
id|debugger-&gt;waiting
op_assign
l_int|1
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Handle debugger trap, i.e. syscall.&n; */
DECL|function|debugger_syscall
r_int
id|debugger_syscall
c_func
(paren
id|debugger_state
op_star
id|debugger
comma
id|pid_t
id|child
)paren
(brace
r_int
id|arg1
comma
id|arg2
comma
id|arg3
comma
id|arg4
comma
id|arg5
comma
id|result
suffix:semicolon
r_int
id|syscall
comma
id|ret
op_assign
l_int|0
suffix:semicolon
id|syscall
op_assign
id|get_syscall
c_func
(paren
id|debugger-&gt;pid
comma
op_amp
id|arg1
comma
op_amp
id|arg2
comma
op_amp
id|arg3
comma
op_amp
id|arg4
comma
op_amp
id|arg5
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|syscall
)paren
(brace
r_case
id|__NR_execve
suffix:colon
multiline_comment|/* execve never returns */
id|debugger-&gt;handle_trace
op_assign
id|debugger_syscall
suffix:semicolon
r_break
suffix:semicolon
r_case
id|__NR_ptrace
suffix:colon
r_if
c_cond
(paren
id|debugger-&gt;debugee-&gt;pid
op_ne
l_int|0
)paren
(brace
id|arg2
op_assign
id|debugger-&gt;debugee-&gt;pid
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|debugger-&gt;debugee-&gt;in_context
)paren
(brace
id|child
op_assign
id|debugger-&gt;debugee-&gt;pid
suffix:semicolon
)brace
id|result
op_assign
id|proxy_ptrace
c_func
(paren
id|debugger
comma
id|arg1
comma
id|arg2
comma
id|arg3
comma
id|arg4
comma
id|child
comma
op_amp
id|ret
)paren
suffix:semicolon
id|syscall_cancel
c_func
(paren
id|debugger-&gt;pid
comma
id|result
)paren
suffix:semicolon
id|debugger-&gt;handle_trace
op_assign
id|debugger_syscall
suffix:semicolon
r_return
id|ret
suffix:semicolon
r_case
id|__NR_waitpid
suffix:colon
r_case
id|__NR_wait4
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|debugger_wait
c_func
(paren
id|debugger
comma
(paren
r_int
op_star
)paren
id|arg2
comma
id|arg3
comma
id|debugger_syscall
comma
id|debugger_normal_return
comma
id|proxy_wait_return
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|__NR_kill
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|debugger-&gt;debugee-&gt;in_context
)paren
(brace
id|child
op_assign
id|debugger-&gt;debugee-&gt;pid
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg1
op_eq
id|debugger-&gt;debugee-&gt;pid
)paren
(brace
id|result
op_assign
id|kill
c_func
(paren
id|child
comma
id|arg2
)paren
suffix:semicolon
id|syscall_cancel
c_func
(paren
id|debugger-&gt;pid
comma
id|result
)paren
suffix:semicolon
id|debugger-&gt;handle_trace
op_assign
id|debugger_syscall
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
id|debugger-&gt;handle_trace
op_assign
id|debugger_normal_return
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|debugger-&gt;handle_trace
op_assign
id|debugger_normal_return
suffix:semicolon
)brace
id|syscall_continue
c_func
(paren
id|debugger-&gt;pid
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Used by the tracing thread */
DECL|variable|parent
r_static
id|debugger_state
id|parent
suffix:semicolon
r_static
r_int
id|parent_syscall
c_func
(paren
id|debugger_state
op_star
id|debugger
comma
r_int
id|pid
)paren
suffix:semicolon
DECL|function|init_parent_proxy
r_int
id|init_parent_proxy
c_func
(paren
r_int
id|pid
)paren
(brace
id|parent
op_assign
(paren
(paren
id|debugger_state
)paren
(brace
id|pid
suffix:colon
id|pid
comma
id|wait_options
suffix:colon
l_int|0
comma
id|wait_status_ptr
suffix:colon
l_int|NULL
comma
id|waiting
suffix:colon
l_int|0
comma
id|real_wait
suffix:colon
l_int|0
comma
id|expecting_child
suffix:colon
l_int|0
comma
id|handle_trace
suffix:colon
id|parent_syscall
comma
id|debugee
suffix:colon
l_int|NULL
)brace
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parent_normal_return
r_int
id|parent_normal_return
c_func
(paren
id|debugger_state
op_star
id|debugger
comma
id|pid_t
id|unused
)paren
(brace
id|debugger-&gt;handle_trace
op_assign
id|parent_syscall
suffix:semicolon
id|syscall_continue
c_func
(paren
id|debugger-&gt;pid
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parent_syscall
r_static
r_int
id|parent_syscall
c_func
(paren
id|debugger_state
op_star
id|debugger
comma
r_int
id|pid
)paren
(brace
r_int
id|arg1
comma
id|arg2
comma
id|arg3
comma
id|arg4
comma
id|arg5
suffix:semicolon
r_int
id|syscall
suffix:semicolon
id|syscall
op_assign
id|get_syscall
c_func
(paren
id|pid
comma
op_amp
id|arg1
comma
op_amp
id|arg2
comma
op_amp
id|arg3
comma
op_amp
id|arg4
comma
op_amp
id|arg5
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|syscall
op_eq
id|__NR_waitpid
)paren
op_logical_or
(paren
id|syscall
op_eq
id|__NR_wait4
)paren
)paren
(brace
id|debugger_wait
c_func
(paren
op_amp
id|parent
comma
(paren
r_int
op_star
)paren
id|arg2
comma
id|arg3
comma
id|parent_syscall
comma
id|parent_normal_return
comma
id|parent_wait_return
)paren
suffix:semicolon
)brace
r_else
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|debugger_normal_return
r_int
id|debugger_normal_return
c_func
(paren
id|debugger_state
op_star
id|debugger
comma
id|pid_t
id|unused
)paren
(brace
id|debugger-&gt;handle_trace
op_assign
id|debugger_syscall
suffix:semicolon
id|syscall_continue
c_func
(paren
id|debugger-&gt;pid
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|debugger_cancelled_return
r_void
id|debugger_cancelled_return
c_func
(paren
id|debugger_state
op_star
id|debugger
comma
r_int
id|result
)paren
(brace
id|debugger-&gt;handle_trace
op_assign
id|debugger_syscall
suffix:semicolon
id|syscall_set_result
c_func
(paren
id|debugger-&gt;pid
comma
id|result
)paren
suffix:semicolon
id|syscall_continue
c_func
(paren
id|debugger-&gt;pid
)paren
suffix:semicolon
)brace
multiline_comment|/* Used by the tracing thread */
DECL|variable|debugger
r_static
id|debugger_state
id|debugger
suffix:semicolon
DECL|variable|debugee
r_static
id|debugee_state
id|debugee
suffix:semicolon
DECL|function|init_proxy
r_void
id|init_proxy
(paren
id|pid_t
id|debugger_pid
comma
r_int
id|stopped
comma
r_int
id|status
)paren
(brace
id|debugger.pid
op_assign
id|debugger_pid
suffix:semicolon
id|debugger.handle_trace
op_assign
id|debugger_syscall
suffix:semicolon
id|debugger.debugee
op_assign
op_amp
id|debugee
suffix:semicolon
id|debugger.waiting
op_assign
l_int|0
suffix:semicolon
id|debugger.real_wait
op_assign
l_int|0
suffix:semicolon
id|debugger.expecting_child
op_assign
l_int|0
suffix:semicolon
id|debugee.pid
op_assign
l_int|0
suffix:semicolon
id|debugee.traced
op_assign
l_int|0
suffix:semicolon
id|debugee.stopped
op_assign
id|stopped
suffix:semicolon
id|debugee.event
op_assign
l_int|0
suffix:semicolon
id|debugee.zombie
op_assign
l_int|0
suffix:semicolon
id|debugee.died
op_assign
l_int|0
suffix:semicolon
id|debugee.wait_status
op_assign
id|status
suffix:semicolon
id|debugee.in_context
op_assign
l_int|1
suffix:semicolon
)brace
DECL|function|debugger_proxy
r_int
id|debugger_proxy
c_func
(paren
r_int
id|status
comma
r_int
id|pid
)paren
(brace
r_int
id|ret
op_assign
l_int|0
comma
id|sig
suffix:semicolon
r_if
c_cond
(paren
id|WIFSTOPPED
c_func
(paren
id|status
)paren
)paren
(brace
id|sig
op_assign
id|WSTOPSIG
c_func
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_eq
id|SIGTRAP
)paren
id|ret
op_assign
(paren
op_star
id|debugger.handle_trace
)paren
(paren
op_amp
id|debugger
comma
id|pid
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|sig
op_eq
id|SIGCHLD
)paren
(brace
r_if
c_cond
(paren
id|debugger.expecting_child
)paren
(brace
id|ptrace
c_func
(paren
id|PTRACE_SYSCALL
comma
id|debugger.pid
comma
l_int|0
comma
id|sig
)paren
suffix:semicolon
id|debugger.expecting_child
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|debugger.waiting
)paren
(brace
id|real_wait_return
c_func
(paren
op_amp
id|debugger
)paren
suffix:semicolon
)brace
r_else
(brace
id|ptrace
c_func
(paren
id|PTRACE_SYSCALL
comma
id|debugger.pid
comma
l_int|0
comma
id|sig
)paren
suffix:semicolon
id|debugger.real_wait
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
id|ptrace
c_func
(paren
id|PTRACE_SYSCALL
comma
id|debugger.pid
comma
l_int|0
comma
id|sig
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|WIFEXITED
c_func
(paren
id|status
)paren
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;debugger (pid %d) exited with status %d&quot;
comma
id|debugger.pid
comma
id|WEXITSTATUS
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|WIFSIGNALED
c_func
(paren
id|status
)paren
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;debugger (pid %d) exited with signal %d&quot;
comma
id|debugger.pid
comma
id|WTERMSIG
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;proxy got unknown status (0x%x) on debugger &quot;
l_string|&quot;(pid %d)&quot;
comma
id|status
comma
id|debugger.pid
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|child_proxy
r_void
id|child_proxy
c_func
(paren
id|pid_t
id|pid
comma
r_int
id|status
)paren
(brace
id|debugee.event
op_assign
l_int|1
suffix:semicolon
id|debugee.wait_status
op_assign
id|status
suffix:semicolon
r_if
c_cond
(paren
id|WIFSTOPPED
c_func
(paren
id|status
)paren
)paren
(brace
id|debugee.stopped
op_assign
l_int|1
suffix:semicolon
id|debugger.expecting_child
op_assign
l_int|1
suffix:semicolon
id|kill
c_func
(paren
id|debugger.pid
comma
id|SIGCHLD
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|WIFEXITED
c_func
(paren
id|status
)paren
op_logical_or
id|WIFSIGNALED
c_func
(paren
id|status
)paren
)paren
(brace
id|debugee.zombie
op_assign
l_int|1
suffix:semicolon
id|debugger.expecting_child
op_assign
l_int|1
suffix:semicolon
id|kill
c_func
(paren
id|debugger.pid
comma
id|SIGCHLD
)paren
suffix:semicolon
)brace
r_else
id|panic
c_func
(paren
l_string|&quot;proxy got unknown status (0x%x) on child (pid %d)&quot;
comma
id|status
comma
id|pid
)paren
suffix:semicolon
)brace
DECL|function|debugger_parent_signal
r_void
id|debugger_parent_signal
c_func
(paren
r_int
id|status
comma
r_int
id|pid
)paren
(brace
r_int
id|sig
suffix:semicolon
r_if
c_cond
(paren
id|WIFSTOPPED
c_func
(paren
id|status
)paren
)paren
(brace
id|sig
op_assign
id|WSTOPSIG
c_func
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_eq
id|SIGTRAP
)paren
(brace
(paren
op_star
id|parent.handle_trace
)paren
(paren
op_amp
id|parent
comma
id|pid
)paren
suffix:semicolon
)brace
r_else
id|ptrace
c_func
(paren
id|PTRACE_SYSCALL
comma
id|pid
comma
l_int|0
comma
id|sig
)paren
suffix:semicolon
)brace
)brace
DECL|function|fake_child_exit
r_void
id|fake_child_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|status
comma
id|pid
suffix:semicolon
id|child_proxy
c_func
(paren
l_int|1
comma
id|W_EXITCODE
c_func
(paren
l_int|0
comma
l_int|0
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
id|debugger.waiting
op_eq
l_int|1
)paren
(brace
id|pid
op_assign
id|waitpid
c_func
(paren
id|debugger.pid
comma
op_amp
id|status
comma
id|WUNTRACED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_ne
id|debugger.pid
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fake_child_exit - waitpid failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|debugger_proxy
c_func
(paren
id|status
comma
id|debugger.pid
)paren
suffix:semicolon
)brace
id|pid
op_assign
id|waitpid
c_func
(paren
id|debugger.pid
comma
op_amp
id|status
comma
id|WUNTRACED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_ne
id|debugger.pid
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fake_child_exit - waitpid failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_DETACH
comma
id|debugger.pid
comma
l_int|0
comma
id|SIGCONT
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fake_child_exit - PTRACE_DETACH failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|variable|gdb_init_string
r_char
id|gdb_init_string
(braket
)braket
op_assign
"&quot;"
id|att
l_int|1
id|b
id|panic
id|b
id|stop
id|handle
id|SIGWINCH
id|nostop
id|noprint
id|pass
"&quot;"
suffix:semicolon
DECL|function|start_debugger
r_int
id|start_debugger
c_func
(paren
r_char
op_star
id|prog
comma
r_int
id|startup
comma
r_int
id|stop
comma
r_int
op_star
id|fd_out
)paren
(brace
r_int
id|slave
comma
id|child
suffix:semicolon
id|slave
op_assign
id|open_gdb_chan
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|child
op_assign
id|fork
c_func
(paren
)paren
)paren
op_eq
l_int|0
)paren
(brace
r_char
op_star
id|tempname
op_assign
l_int|NULL
suffix:semicolon
r_int
id|fd
suffix:semicolon
r_if
c_cond
(paren
id|setsid
c_func
(paren
)paren
OL
l_int|0
)paren
(brace
id|perror
c_func
(paren
l_string|&quot;setsid&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|dup2
c_func
(paren
id|slave
comma
l_int|0
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|dup2
c_func
(paren
id|slave
comma
l_int|1
)paren
OL
l_int|0
)paren
op_logical_or
(paren
id|dup2
c_func
(paren
id|slave
comma
l_int|2
)paren
OL
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;start_debugger : dup2 failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ioctl
c_func
(paren
l_int|0
comma
id|TIOCSCTTY
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;start_debugger : TIOCSCTTY failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|tcsetpgrp
(paren
l_int|1
comma
id|os_getpid
c_func
(paren
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;start_debugger : tcsetpgrp failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
macro_line|#ifdef notdef
m_exit
(paren
l_int|1
)paren
suffix:semicolon
macro_line|#endif
)brace
r_if
c_cond
(paren
(paren
id|fd
op_assign
id|make_tempfile
c_func
(paren
l_string|&quot;/tmp/gdb_init-XXXXXX&quot;
comma
op_amp
id|tempname
comma
l_int|0
)paren
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;start_debugger : make_tempfile failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|write
c_func
(paren
id|fd
comma
id|gdb_init_string
comma
r_sizeof
(paren
id|gdb_init_string
)paren
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|startup
)paren
(brace
r_if
c_cond
(paren
id|stop
)paren
(brace
id|write
c_func
(paren
id|fd
comma
l_string|&quot;b start_kernel&bslash;n&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;b start_kernel&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|write
c_func
(paren
id|fd
comma
l_string|&quot;c&bslash;n&quot;
comma
id|strlen
c_func
(paren
l_string|&quot;c&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_TRACEME
comma
l_int|0
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;start_debugger :  PTRACE_TRACEME failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
m_exit
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|execlp
c_func
(paren
l_string|&quot;gdb&quot;
comma
l_string|&quot;gdb&quot;
comma
l_string|&quot;--command&quot;
comma
id|tempname
comma
id|prog
comma
l_int|NULL
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;start_debugger : exec of gdb failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|child
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;start_debugger : fork for gdb failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
op_star
id|fd_out
op_assign
id|slave
suffix:semicolon
r_return
id|child
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
