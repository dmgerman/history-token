multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;sched.h&gt;
macro_line|#include &lt;string.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;sigcontext.h&quot;
macro_line|#include &quot;sysdep/sigcontext.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;mem_user.h&quot;
macro_line|#include &quot;process.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;chan_user.h&quot;
macro_line|#include &quot;ptrace_user.h&quot;
macro_line|#include &quot;mode.h&quot;
macro_line|#include &quot;tt.h&quot;
DECL|variable|tracer_winch
r_static
r_int
id|tracer_winch
(braket
l_int|2
)braket
suffix:semicolon
DECL|function|is_tracer_winch
r_int
id|is_tracer_winch
c_func
(paren
r_int
id|pid
comma
r_int
id|fd
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|pid
op_ne
id|tracing_pid
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|register_winch_irq
c_func
(paren
id|tracer_winch
(braket
l_int|0
)braket
comma
id|fd
comma
op_minus
l_int|1
comma
id|data
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|tracer_winch_handler
r_static
r_void
id|tracer_winch_handler
c_func
(paren
r_int
id|sig
)paren
(brace
r_int
id|n
suffix:semicolon
r_char
id|c
op_assign
l_int|1
suffix:semicolon
id|n
op_assign
id|os_write_file
c_func
(paren
id|tracer_winch
(braket
l_int|1
)braket
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
r_sizeof
(paren
id|c
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;tracer_winch_handler - write failed, err = %d&bslash;n&quot;
comma
op_minus
id|n
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Called only by the tracing thread during initialization */
DECL|function|setup_tracer_winch
r_static
r_void
id|setup_tracer_winch
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|os_pipe
c_func
(paren
id|tracer_winch
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;setup_tracer_winch : os_pipe failed, err = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|signal
c_func
(paren
id|SIGWINCH
comma
id|tracer_winch_handler
)paren
suffix:semicolon
)brace
DECL|function|attach_process
r_void
id|attach_process
c_func
(paren
r_int
id|pid
)paren
(brace
r_if
c_cond
(paren
(paren
id|ptrace
c_func
(paren
id|PTRACE_ATTACH
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
id|ptrace
c_func
(paren
id|PTRACE_CONT
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
id|tracer_panic
c_func
(paren
l_string|&quot;OP_FORK failed to attach pid&quot;
)paren
suffix:semicolon
)brace
id|wait_for_stop
c_func
(paren
id|pid
comma
id|SIGSTOP
comma
id|PTRACE_CONT
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_SETOPTIONS
comma
id|pid
comma
l_int|0
comma
(paren
r_void
op_star
)paren
id|PTRACE_O_TRACESYSGOOD
)paren
OL
l_int|0
)paren
id|tracer_panic
c_func
(paren
l_string|&quot;OP_FORK: PTRACE_SETOPTIONS failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_CONT
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
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;OP_FORK failed to continue process&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|tracer_panic
r_void
id|tracer_panic
c_func
(paren
r_char
op_star
id|format
comma
dot
dot
dot
)paren
(brace
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|format
)paren
suffix:semicolon
id|vprintf
c_func
(paren
id|format
comma
id|ap
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|pause
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|tracer_segv
r_static
r_void
id|tracer_segv
c_func
(paren
r_int
id|sig
comma
r_struct
id|sigcontext
id|sc
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Tracing thread segfault at address 0x%lx, ip 0x%lx&bslash;n&quot;
comma
id|SC_FAULT_ADDR
c_func
(paren
op_amp
id|sc
)paren
comma
id|SC_IP
c_func
(paren
op_amp
id|sc
)paren
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|pause
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Changed early in boot, and then only read */
DECL|variable|debug
r_int
id|debug
op_assign
l_int|0
suffix:semicolon
DECL|variable|debug_stop
r_int
id|debug_stop
op_assign
l_int|1
suffix:semicolon
DECL|variable|debug_parent
r_int
id|debug_parent
op_assign
l_int|0
suffix:semicolon
DECL|variable|honeypot
r_int
id|honeypot
op_assign
l_int|0
suffix:semicolon
DECL|function|signal_tramp
r_static
r_int
id|signal_tramp
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_int
(paren
op_star
id|proc
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
r_if
c_cond
(paren
id|honeypot
op_logical_and
id|munmap
c_func
(paren
(paren
r_void
op_star
)paren
(paren
id|host_task_size
op_minus
l_int|0x10000000
)paren
comma
l_int|0x10000000
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Unmapping stack failed&quot;
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
id|panic
c_func
(paren
l_string|&quot;ptrace PTRACE_TRACEME failed&quot;
)paren
suffix:semicolon
)brace
id|os_stop_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
id|change_sig
c_func
(paren
id|SIGWINCH
comma
l_int|0
)paren
suffix:semicolon
id|signal
c_func
(paren
id|SIGUSR1
comma
id|SIG_IGN
)paren
suffix:semicolon
id|change_sig
c_func
(paren
id|SIGCHLD
comma
l_int|0
)paren
suffix:semicolon
id|signal
c_func
(paren
id|SIGSEGV
comma
(paren
id|__sighandler_t
)paren
id|sig_handler
)paren
suffix:semicolon
id|set_cmdline
c_func
(paren
l_string|&quot;(idle thread)&quot;
)paren
suffix:semicolon
id|set_init_pid
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
id|proc
op_assign
id|arg
suffix:semicolon
r_return
(paren
op_star
id|proc
)paren
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|sleeping_process_signal
r_static
r_void
id|sleeping_process_signal
c_func
(paren
r_int
id|pid
comma
r_int
id|sig
)paren
(brace
r_switch
c_cond
(paren
id|sig
)paren
(brace
multiline_comment|/* These two result from UML being ^Z-ed and bg-ed.  PTRACE_CONT is&n;&t; * right because the process must be in the kernel already.&n;&t; */
r_case
id|SIGCONT
suffix:colon
r_case
id|SIGTSTP
suffix:colon
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_CONT
comma
id|pid
comma
l_int|0
comma
id|sig
)paren
OL
l_int|0
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;sleeping_process_signal : Failed to &quot;
l_string|&quot;continue pid %d, signal = %d, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|pid
comma
id|sig
comma
id|errno
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
multiline_comment|/* This happens when the debugger (e.g. strace) is doing system call &n;&t; * tracing on the kernel.  During a context switch, the current task&n;&t; * will be set to the incoming process and the outgoing process will&n;&t; * hop into write and then read.  Since it&squot;s not the current process&n;&t; * any more, the trace of those will land here.  So, we need to just &n;&t; * PTRACE_SYSCALL it.&n;&t; */
r_case
(paren
id|SIGTRAP
op_plus
l_int|0x80
)paren
suffix:colon
r_if
c_cond
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
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;sleeping_process_signal : Failed to &quot;
l_string|&quot;PTRACE_SYSCALL pid %d, errno = %d&bslash;n&quot;
comma
id|pid
comma
id|errno
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SIGSTOP
suffix:colon
r_break
suffix:semicolon
r_default
suffix:colon
id|tracer_panic
c_func
(paren
l_string|&quot;sleeping process %d got unexpected &quot;
l_string|&quot;signal : %d&bslash;n&quot;
comma
id|pid
comma
id|sig
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Accessed only by the tracing thread */
DECL|variable|debugger_pid
r_int
id|debugger_pid
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|debugger_parent
r_int
id|debugger_parent
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|debugger_fd
r_int
id|debugger_fd
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|gdb_pid
r_int
id|gdb_pid
op_assign
op_minus
l_int|1
suffix:semicolon
r_struct
(brace
DECL|member|pid
r_int
id|pid
suffix:semicolon
DECL|member|signal
r_int
id|signal
suffix:semicolon
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|time
r_struct
id|timeval
id|time
suffix:semicolon
DECL|variable|signal_record
)brace
id|signal_record
(braket
l_int|1024
)braket
(braket
l_int|32
)braket
suffix:semicolon
DECL|variable|signal_index
r_int
id|signal_index
(braket
l_int|32
)braket
suffix:semicolon
DECL|variable|nsignals
r_int
id|nsignals
op_assign
l_int|0
suffix:semicolon
DECL|variable|debug_trace
r_int
id|debug_trace
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
id|io_nsignals
comma
id|io_count
comma
id|intr_count
suffix:semicolon
r_extern
r_void
id|signal_usr1
c_func
(paren
r_int
id|sig
)paren
suffix:semicolon
DECL|variable|tracing_pid
r_int
id|tracing_pid
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|function|tracer
r_int
id|tracer
c_func
(paren
r_int
(paren
op_star
id|init_proc
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|sp
)paren
(brace
r_void
op_star
id|task
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|eip
op_assign
l_int|0
suffix:semicolon
r_int
id|status
comma
id|pid
op_assign
l_int|0
comma
id|sig
op_assign
l_int|0
comma
id|cont_type
comma
id|tracing
op_assign
l_int|0
comma
id|op
op_assign
l_int|0
suffix:semicolon
r_int
id|last_index
comma
id|proc_id
op_assign
l_int|0
comma
id|n
comma
id|err
comma
id|old_tracing
op_assign
l_int|0
comma
id|strace
op_assign
l_int|0
suffix:semicolon
r_int
id|local_using_sysemu
op_assign
l_int|0
suffix:semicolon
id|signal
c_func
(paren
id|SIGPIPE
comma
id|SIG_IGN
)paren
suffix:semicolon
id|setup_tracer_winch
c_func
(paren
)paren
suffix:semicolon
id|tracing_pid
op_assign
id|os_getpid
c_func
(paren
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;tracing thread pid = %d&bslash;n&quot;
comma
id|tracing_pid
)paren
suffix:semicolon
id|pid
op_assign
id|clone
c_func
(paren
id|signal_tramp
comma
id|sp
comma
id|CLONE_FILES
op_or
id|SIGCHLD
comma
id|init_proc
)paren
suffix:semicolon
id|CATCH_EINTR
c_func
(paren
id|n
op_assign
id|waitpid
c_func
(paren
id|pid
comma
op_amp
id|status
comma
id|WUNTRACED
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;waitpid on idle thread failed, errno = %d&bslash;n&quot;
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
id|ptrace
c_func
(paren
id|PTRACE_SETOPTIONS
comma
id|pid
comma
l_int|0
comma
(paren
r_void
op_star
)paren
id|PTRACE_O_TRACESYSGOOD
)paren
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Failed to PTRACE_SETOPTIONS for idle thread, errno = %d&bslash;n&quot;
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
(paren
id|ptrace
c_func
(paren
id|PTRACE_CONT
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
id|printf
c_func
(paren
l_string|&quot;Failed to continue idle thread, errno = %d&bslash;n&quot;
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
id|signal
c_func
(paren
id|SIGSEGV
comma
(paren
id|sighandler_t
)paren
id|tracer_segv
)paren
suffix:semicolon
id|signal
c_func
(paren
id|SIGUSR1
comma
id|signal_usr1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug_trace
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Tracing thread pausing to be attached&bslash;n&quot;
)paren
suffix:semicolon
id|stop
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|debug
)paren
(brace
r_if
c_cond
(paren
id|gdb_pid
op_ne
op_minus
l_int|1
)paren
(brace
id|debugger_pid
op_assign
id|attach_debugger
c_func
(paren
id|pid
comma
id|gdb_pid
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|debugger_pid
op_assign
id|init_ptrace_proxy
c_func
(paren
id|pid
comma
l_int|1
comma
id|debug_stop
)paren
suffix:semicolon
r_if
c_cond
(paren
id|debug_parent
)paren
(brace
id|debugger_parent
op_assign
id|os_process_parent
c_func
(paren
id|debugger_pid
)paren
suffix:semicolon
id|init_parent_proxy
c_func
(paren
id|debugger_parent
)paren
suffix:semicolon
id|err
op_assign
id|attach
c_func
(paren
id|debugger_parent
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Failed to attach debugger parent %d, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|debugger_parent
comma
op_minus
id|err
)paren
suffix:semicolon
id|debugger_parent
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_SYSCALL
comma
id|debugger_parent
comma
l_int|0
comma
l_int|0
)paren
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Failed to continue debugger &quot;
l_string|&quot;parent, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|debugger_parent
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
)brace
id|set_cmdline
c_func
(paren
l_string|&quot;(tracing thread)&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|CATCH_EINTR
c_func
(paren
id|pid
op_assign
id|waitpid
c_func
(paren
op_minus
l_int|1
comma
op_amp
id|status
comma
id|WUNTRACED
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
op_le
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ne
id|ECHILD
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;wait failed - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pid
op_eq
id|debugger_pid
)paren
(brace
r_int
id|cont
op_assign
l_int|0
suffix:semicolon
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
id|debugger_pid
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* XXX Figure out how to deal with gdb and SMP */
r_else
id|cont
op_assign
id|debugger_signal
c_func
(paren
id|status
comma
id|cpu_tasks
(braket
l_int|0
)braket
dot
id|pid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cont
op_eq
id|PTRACE_SYSCALL
)paren
(brace
id|strace
op_assign
l_int|1
suffix:semicolon
)brace
r_continue
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pid
op_eq
id|debugger_parent
)paren
(brace
id|debugger_parent_signal
c_func
(paren
id|status
comma
id|pid
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|nsignals
op_increment
suffix:semicolon
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
suffix:semicolon
)brace
macro_line|#ifdef notdef
(brace
id|printf
c_func
(paren
l_string|&quot;Child %d exited with status %d&bslash;n&quot;
comma
id|pid
comma
id|WEXITSTATUS
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
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
id|sig
op_assign
id|WTERMSIG
c_func
(paren
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_ne
l_int|9
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;Child %d exited with signal %d&bslash;n&quot;
comma
id|pid
comma
id|sig
)paren
suffix:semicolon
)brace
)brace
r_else
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
id|proc_id
op_assign
id|pid_to_processor_id
c_func
(paren
id|pid
)paren
suffix:semicolon
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
id|signal_index
(braket
id|proc_id
)braket
op_eq
l_int|1024
)paren
(brace
id|signal_index
(braket
id|proc_id
)braket
op_assign
l_int|0
suffix:semicolon
id|last_index
op_assign
l_int|1023
suffix:semicolon
)brace
r_else
id|last_index
op_assign
id|signal_index
(braket
id|proc_id
)braket
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|sig
op_eq
id|SIGPROF
)paren
op_logical_or
(paren
id|sig
op_eq
id|SIGVTALRM
)paren
op_logical_or
(paren
id|sig
op_eq
id|SIGALRM
)paren
)paren
op_logical_and
(paren
id|signal_record
(braket
id|proc_id
)braket
(braket
id|last_index
)braket
dot
id|signal
op_eq
id|sig
)paren
op_logical_and
(paren
id|signal_record
(braket
id|proc_id
)braket
(braket
id|last_index
)braket
dot
id|pid
op_eq
id|pid
)paren
)paren
(brace
id|signal_index
(braket
id|proc_id
)braket
op_assign
id|last_index
suffix:semicolon
)brace
id|signal_record
(braket
id|proc_id
)braket
(braket
id|signal_index
(braket
id|proc_id
)braket
)braket
dot
id|pid
op_assign
id|pid
suffix:semicolon
id|gettimeofday
c_func
(paren
op_amp
id|signal_record
(braket
id|proc_id
)braket
(braket
id|signal_index
(braket
id|proc_id
)braket
)braket
dot
id|time
comma
l_int|NULL
)paren
suffix:semicolon
id|eip
op_assign
id|ptrace
c_func
(paren
id|PTRACE_PEEKUSER
comma
id|pid
comma
id|PT_IP_OFFSET
comma
l_int|0
)paren
suffix:semicolon
id|signal_record
(braket
id|proc_id
)braket
(braket
id|signal_index
(braket
id|proc_id
)braket
)braket
dot
id|addr
op_assign
id|eip
suffix:semicolon
id|signal_record
(braket
id|proc_id
)braket
(braket
id|signal_index
(braket
id|proc_id
)braket
op_increment
)braket
dot
id|signal
op_assign
id|sig
suffix:semicolon
r_if
c_cond
(paren
id|proc_id
op_eq
op_minus
l_int|1
)paren
(brace
id|sleeping_process_signal
c_func
(paren
id|pid
comma
id|sig
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|task
op_assign
id|cpu_tasks
(braket
id|proc_id
)braket
dot
id|task
suffix:semicolon
id|tracing
op_assign
id|is_tracing
c_func
(paren
id|task
)paren
suffix:semicolon
id|old_tracing
op_assign
id|tracing
suffix:semicolon
multiline_comment|/* Assume: no syscall, when coming from user */
r_if
c_cond
(paren
id|tracing
)paren
id|do_sigtrap
c_func
(paren
id|task
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|sig
)paren
(brace
r_case
id|SIGUSR1
suffix:colon
id|sig
op_assign
l_int|0
suffix:semicolon
id|op
op_assign
id|do_proc_op
c_func
(paren
id|task
comma
id|proc_id
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|op
)paren
(brace
r_case
id|OP_TRACE_ON
suffix:colon
id|arch_leave_kernel
c_func
(paren
id|task
comma
id|pid
)paren
suffix:semicolon
id|tracing
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|OP_REBOOT
suffix:colon
r_case
id|OP_HALT
suffix:colon
id|unmap_physmem
c_func
(paren
)paren
suffix:semicolon
id|kmalloc_ok
op_assign
l_int|0
suffix:semicolon
id|os_kill_ptraced_process
c_func
(paren
id|pid
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Now let&squot;s reap remaining zombies */
id|errno
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|waitpid
c_func
(paren
op_minus
l_int|1
comma
op_amp
id|status
comma
id|WUNTRACED
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|errno
op_ne
id|ECHILD
)paren
suffix:semicolon
r_return
id|op
op_eq
id|OP_REBOOT
suffix:semicolon
r_case
id|OP_NONE
suffix:colon
id|printf
c_func
(paren
l_string|&quot;Detaching pid %d&bslash;n&quot;
comma
id|pid
)paren
suffix:semicolon
id|detach
c_func
(paren
id|pid
comma
id|SIGSTOP
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* OP_EXEC switches host processes on us,&n;&t;&t;&t;&t; * we want to continue the new one.&n;&t;&t;&t;&t; */
id|pid
op_assign
id|cpu_tasks
(braket
id|proc_id
)braket
dot
id|pid
suffix:semicolon
r_break
suffix:semicolon
r_case
(paren
id|SIGTRAP
op_plus
l_int|0x80
)paren
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|tracing
op_logical_and
(paren
id|debugger_pid
op_ne
op_minus
l_int|1
)paren
)paren
(brace
id|child_signal
c_func
(paren
id|pid
comma
id|status
op_amp
l_int|0x7fff
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|tracing
op_assign
l_int|0
suffix:semicolon
id|do_syscall
c_func
(paren
id|task
comma
id|pid
comma
id|local_using_sysemu
)paren
suffix:semicolon
id|sig
op_assign
id|SIGUSR2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIGTRAP
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|tracing
op_logical_and
(paren
id|debugger_pid
op_ne
op_minus
l_int|1
)paren
)paren
(brace
id|child_signal
c_func
(paren
id|pid
comma
id|status
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|tracing
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIGPROF
suffix:colon
r_if
c_cond
(paren
id|tracing
)paren
(brace
id|sig
op_assign
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|SIGCHLD
suffix:colon
r_case
id|SIGHUP
suffix:colon
id|sig
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIGSEGV
suffix:colon
r_case
id|SIGIO
suffix:colon
r_case
id|SIGALRM
suffix:colon
r_case
id|SIGVTALRM
suffix:colon
r_case
id|SIGFPE
suffix:colon
r_case
id|SIGBUS
suffix:colon
r_case
id|SIGILL
suffix:colon
r_case
id|SIGWINCH
suffix:colon
r_default
suffix:colon
id|tracing
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
id|set_tracing
c_func
(paren
id|task
comma
id|tracing
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tracing
op_logical_and
id|old_tracing
)paren
(brace
id|arch_enter_kernel
c_func
(paren
id|task
comma
id|pid
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tracing
op_logical_and
(paren
id|debugger_pid
op_ne
op_minus
l_int|1
)paren
op_logical_and
(paren
id|sig
op_ne
l_int|0
)paren
op_logical_and
(paren
id|sig
op_ne
id|SIGALRM
)paren
op_logical_and
(paren
id|sig
op_ne
id|SIGVTALRM
)paren
op_logical_and
(paren
id|sig
op_ne
id|SIGSEGV
)paren
op_logical_and
(paren
id|sig
op_ne
id|SIGTRAP
)paren
op_logical_and
(paren
id|sig
op_ne
id|SIGUSR2
)paren
op_logical_and
(paren
id|sig
op_ne
id|SIGIO
)paren
op_logical_and
(paren
id|sig
op_ne
id|SIGFPE
)paren
)paren
(brace
id|child_signal
c_func
(paren
id|pid
comma
id|status
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|local_using_sysemu
op_assign
id|get_using_sysemu
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tracing
)paren
(brace
id|cont_type
op_assign
id|SELECT_PTRACE_OPERATION
c_func
(paren
id|local_using_sysemu
comma
id|singlestepping
c_func
(paren
id|task
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
id|debugger_pid
op_ne
op_minus
l_int|1
)paren
op_logical_and
id|strace
)paren
(brace
id|cont_type
op_assign
id|PTRACE_SYSCALL
suffix:semicolon
)brace
r_else
id|cont_type
op_assign
id|PTRACE_CONT
suffix:semicolon
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|cont_type
comma
id|pid
comma
l_int|0
comma
id|sig
)paren
op_ne
l_int|0
)paren
(brace
id|tracer_panic
c_func
(paren
l_string|&quot;ptrace failed to continue &quot;
l_string|&quot;process - errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|uml_debug_setup
r_static
r_int
id|__init
id|uml_debug_setup
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
r_char
op_star
id|next
suffix:semicolon
id|debug
op_assign
l_int|1
suffix:semicolon
op_star
id|add
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_star
id|line
op_ne
l_char|&squot;=&squot;
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|line
op_increment
suffix:semicolon
r_while
c_loop
(paren
id|line
op_ne
l_int|NULL
)paren
(brace
id|next
op_assign
id|strchr
c_func
(paren
id|line
comma
l_char|&squot;,&squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
(brace
op_star
id|next
op_increment
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|line
comma
l_string|&quot;go&quot;
)paren
)paren
(brace
id|debug_stop
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|line
comma
l_string|&quot;parent&quot;
)paren
)paren
(brace
id|debug_parent
op_assign
l_int|1
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;Unknown debug option : &squot;%s&squot;&bslash;n&quot;
comma
id|line
)paren
suffix:semicolon
id|line
op_assign
id|next
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;debug&quot;
comma
id|uml_debug_setup
comma
l_string|&quot;debug&bslash;n&quot;
l_string|&quot;    Starts up the kernel under the control of gdb. See the &bslash;n&quot;
l_string|&quot;    kernel debugging tutorial and the debugging session pages&bslash;n&quot;
l_string|&quot;    at http://user-mode-linux.sourceforge.net/ for more information.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
DECL|function|uml_debugtrace_setup
r_static
r_int
id|__init
id|uml_debugtrace_setup
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
id|debug_trace
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;debugtrace&quot;
comma
id|uml_debugtrace_setup
comma
l_string|&quot;debugtrace&bslash;n&quot;
l_string|&quot;    Causes the tracing thread to pause until it is attached by a&bslash;n&quot;
l_string|&quot;    debugger and continued.  This is mostly for debugging crashes&bslash;n&quot;
l_string|&quot;    early during boot, and should be pretty much obsoleted by&bslash;n&quot;
l_string|&quot;    the debug switch.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
DECL|function|uml_honeypot_setup
r_static
r_int
id|__init
id|uml_honeypot_setup
c_func
(paren
r_char
op_star
id|line
comma
r_int
op_star
id|add
)paren
(brace
id|jail_setup
c_func
(paren
l_string|&quot;&quot;
comma
id|add
)paren
suffix:semicolon
id|honeypot
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|__uml_setup
c_func
(paren
l_string|&quot;honeypot&quot;
comma
id|uml_honeypot_setup
comma
l_string|&quot;honeypot&bslash;n&quot;
l_string|&quot;    This makes UML put process stacks in the same location as they are&bslash;n&quot;
l_string|&quot;    on the host, allowing expoits such as stack smashes to work against&bslash;n&quot;
l_string|&quot;    UML.  This implies &squot;jail&squot;.&bslash;n&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
