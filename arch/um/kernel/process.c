multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdio.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;sched.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;stdarg.h&gt;
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;setjmp.h&gt;
macro_line|#include &lt;sys/time.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/user.h&gt;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;process.h&quot;
macro_line|#include &quot;signal_kern.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;sysdep/sigcontext.h&quot;
macro_line|#include &quot;irq_user.h&quot;
macro_line|#include &quot;ptrace_user.h&quot;
macro_line|#include &quot;time_user.h&quot;
macro_line|#include &quot;init.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;uml-config.h&quot;
macro_line|#include &quot;choose-mode.h&quot;
macro_line|#include &quot;mode.h&quot;
macro_line|#ifdef UML_CONFIG_MODE_SKAS
macro_line|#include &quot;skas.h&quot;
macro_line|#include &quot;skas_ptrace.h&quot;
macro_line|#endif
DECL|function|init_new_thread_stack
r_void
id|init_new_thread_stack
c_func
(paren
r_void
op_star
id|sig_stack
comma
r_void
(paren
op_star
id|usr1_handler
)paren
(paren
r_int
)paren
)paren
(brace
r_int
id|flags
op_assign
l_int|0
comma
id|pages
suffix:semicolon
r_if
c_cond
(paren
id|sig_stack
op_ne
l_int|NULL
)paren
(brace
id|pages
op_assign
(paren
l_int|1
op_lshift
id|UML_CONFIG_KERNEL_STACK_ORDER
)paren
suffix:semicolon
id|set_sigstack
c_func
(paren
id|sig_stack
comma
id|pages
op_star
id|page_size
c_func
(paren
)paren
)paren
suffix:semicolon
id|flags
op_assign
id|SA_ONSTACK
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usr1_handler
)paren
(brace
id|set_handler
c_func
(paren
id|SIGUSR1
comma
id|usr1_handler
comma
id|flags
comma
op_minus
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|init_new_thread_signals
r_void
id|init_new_thread_signals
c_func
(paren
r_int
id|altstack
)paren
(brace
r_int
id|flags
op_assign
id|altstack
ques
c_cond
id|SA_ONSTACK
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* NODEFER is set here because SEGV isn&squot;t turned back on when the&n;&t; * handler is ready to receive signals.  This causes any segfault&n;&t; * during a copy_user to kill the process because the fault is blocked.&n;&t; */
id|set_handler
c_func
(paren
id|SIGSEGV
comma
(paren
id|__sighandler_t
)paren
id|sig_handler
comma
id|flags
op_or
id|SA_NODEFER
comma
id|SIGUSR1
comma
id|SIGIO
comma
id|SIGWINCH
comma
id|SIGALRM
comma
id|SIGVTALRM
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|set_handler
c_func
(paren
id|SIGTRAP
comma
(paren
id|__sighandler_t
)paren
id|sig_handler
comma
id|flags
comma
id|SIGUSR1
comma
id|SIGIO
comma
id|SIGWINCH
comma
id|SIGALRM
comma
id|SIGVTALRM
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|set_handler
c_func
(paren
id|SIGFPE
comma
(paren
id|__sighandler_t
)paren
id|sig_handler
comma
id|flags
comma
id|SIGUSR1
comma
id|SIGIO
comma
id|SIGWINCH
comma
id|SIGALRM
comma
id|SIGVTALRM
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|set_handler
c_func
(paren
id|SIGILL
comma
(paren
id|__sighandler_t
)paren
id|sig_handler
comma
id|flags
comma
id|SIGUSR1
comma
id|SIGIO
comma
id|SIGWINCH
comma
id|SIGALRM
comma
id|SIGVTALRM
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|set_handler
c_func
(paren
id|SIGBUS
comma
(paren
id|__sighandler_t
)paren
id|sig_handler
comma
id|flags
comma
id|SIGUSR1
comma
id|SIGIO
comma
id|SIGWINCH
comma
id|SIGALRM
comma
id|SIGVTALRM
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|set_handler
c_func
(paren
id|SIGWINCH
comma
(paren
id|__sighandler_t
)paren
id|sig_handler
comma
id|flags
comma
id|SIGUSR1
comma
id|SIGIO
comma
id|SIGWINCH
comma
id|SIGALRM
comma
id|SIGVTALRM
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|set_handler
c_func
(paren
id|SIGUSR2
comma
(paren
id|__sighandler_t
)paren
id|sig_handler
comma
id|SA_NOMASK
op_or
id|flags
comma
op_minus
l_int|1
)paren
suffix:semicolon
id|signal
c_func
(paren
id|SIGHUP
comma
id|SIG_IGN
)paren
suffix:semicolon
id|init_irq_signals
c_func
(paren
id|altstack
)paren
suffix:semicolon
)brace
DECL|struct|tramp
r_struct
id|tramp
(brace
DECL|member|tramp
r_int
(paren
op_star
id|tramp
)paren
(paren
r_void
op_star
)paren
suffix:semicolon
DECL|member|tramp_data
r_void
op_star
id|tramp_data
suffix:semicolon
DECL|member|temp_stack
r_int
r_int
id|temp_stack
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|pid
r_int
id|pid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* See above for why sigkill is here */
DECL|variable|sigkill
r_int
id|sigkill
op_assign
id|SIGKILL
suffix:semicolon
DECL|function|outer_tramp
r_int
id|outer_tramp
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
r_struct
id|tramp
op_star
id|t
suffix:semicolon
r_int
id|sig
op_assign
id|sigkill
suffix:semicolon
id|t
op_assign
id|arg
suffix:semicolon
id|t-&gt;pid
op_assign
id|clone
c_func
(paren
id|t-&gt;tramp
comma
(paren
r_void
op_star
)paren
id|t-&gt;temp_stack
op_plus
id|page_size
c_func
(paren
)paren
op_div
l_int|2
comma
id|t-&gt;flags
comma
id|t-&gt;tramp_data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;pid
OG
l_int|0
)paren
(brace
id|wait_for_stop
c_func
(paren
id|t-&gt;pid
comma
id|SIGSTOP
comma
id|PTRACE_CONT
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|kill
c_func
(paren
id|os_getpid
c_func
(paren
)paren
comma
id|sig
)paren
suffix:semicolon
id|_exit
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|start_fork_tramp
r_int
id|start_fork_tramp
c_func
(paren
r_void
op_star
id|thread_arg
comma
r_int
r_int
id|temp_stack
comma
r_int
id|clone_flags
comma
r_int
(paren
op_star
id|tramp
)paren
(paren
r_void
op_star
)paren
)paren
(brace
r_struct
id|tramp
id|arg
suffix:semicolon
r_int
r_int
id|sp
suffix:semicolon
r_int
id|new_pid
comma
id|status
comma
id|err
suffix:semicolon
multiline_comment|/* The trampoline will run on the temporary stack */
id|sp
op_assign
id|stack_sp
c_func
(paren
id|temp_stack
)paren
suffix:semicolon
id|clone_flags
op_or_assign
id|CLONE_FILES
op_or
id|SIGCHLD
suffix:semicolon
id|arg.tramp
op_assign
id|tramp
suffix:semicolon
id|arg.tramp_data
op_assign
id|thread_arg
suffix:semicolon
id|arg.temp_stack
op_assign
id|temp_stack
suffix:semicolon
id|arg.flags
op_assign
id|clone_flags
suffix:semicolon
multiline_comment|/* Start the process and wait for it to kill itself */
id|new_pid
op_assign
id|clone
c_func
(paren
id|outer_tramp
comma
(paren
r_void
op_star
)paren
id|sp
comma
id|clone_flags
comma
op_amp
id|arg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|new_pid
OL
l_int|0
)paren
(brace
r_return
id|new_pid
suffix:semicolon
)brace
id|CATCH_EINTR
c_func
(paren
id|err
op_assign
id|waitpid
c_func
(paren
id|new_pid
comma
op_amp
id|status
comma
l_int|0
)paren
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
id|panic
c_func
(paren
l_string|&quot;Waiting for outer trampoline failed - errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|WIFSIGNALED
c_func
(paren
id|status
)paren
op_logical_or
(paren
id|WTERMSIG
c_func
(paren
id|status
)paren
op_ne
id|SIGKILL
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;outer trampoline didn&squot;t exit with SIGKILL, &quot;
l_string|&quot;status = %d&quot;
comma
id|status
)paren
suffix:semicolon
)brace
r_return
id|arg.pid
suffix:semicolon
)brace
DECL|function|suspend_new_thread
r_void
id|suspend_new_thread
c_func
(paren
r_int
id|fd
)paren
(brace
r_char
id|c
suffix:semicolon
id|os_stop_process
c_func
(paren
id|os_getpid
c_func
(paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|os_read_file
c_func
(paren
id|fd
comma
op_amp
id|c
comma
r_sizeof
(paren
id|c
)paren
)paren
op_ne
r_sizeof
(paren
id|c
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;read failed in suspend_new_thread&quot;
)paren
suffix:semicolon
)brace
)brace
DECL|function|ptrace_child
r_static
r_int
id|ptrace_child
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
id|os_getpid
c_func
(paren
)paren
suffix:semicolon
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
id|perror
c_func
(paren
l_string|&quot;ptrace&quot;
)paren
suffix:semicolon
id|os_kill_process
c_func
(paren
id|pid
comma
l_int|0
)paren
suffix:semicolon
)brace
id|os_stop_process
c_func
(paren
id|pid
)paren
suffix:semicolon
id|_exit
c_func
(paren
id|os_getpid
c_func
(paren
)paren
op_eq
id|pid
)paren
suffix:semicolon
)brace
DECL|function|start_ptraced_child
r_static
r_int
id|start_ptraced_child
c_func
(paren
r_void
op_star
op_star
id|stack_out
)paren
(brace
r_void
op_star
id|stack
suffix:semicolon
r_int
r_int
id|sp
suffix:semicolon
r_int
id|pid
comma
id|n
comma
id|status
suffix:semicolon
id|stack
op_assign
id|mmap
c_func
(paren
l_int|NULL
comma
id|PAGE_SIZE
comma
id|PROT_READ
op_or
id|PROT_WRITE
op_or
id|PROT_EXEC
comma
id|MAP_PRIVATE
op_or
id|MAP_ANONYMOUS
comma
op_minus
l_int|1
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stack
op_eq
id|MAP_FAILED
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_ptrace : mmap failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
id|sp
op_assign
(paren
r_int
r_int
)paren
id|stack
op_plus
id|PAGE_SIZE
op_minus
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
id|pid
op_assign
id|clone
c_func
(paren
id|ptrace_child
comma
(paren
r_void
op_star
)paren
id|sp
comma
id|SIGCHLD
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pid
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_ptrace : clone failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
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
id|panic
c_func
(paren
l_string|&quot;check_ptrace : wait failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|WIFSTOPPED
c_func
(paren
id|status
)paren
op_logical_or
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_ne
id|SIGSTOP
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_ptrace : expected SIGSTOP, got status = %d&quot;
comma
id|status
)paren
suffix:semicolon
)brace
op_star
id|stack_out
op_assign
id|stack
suffix:semicolon
r_return
id|pid
suffix:semicolon
)brace
DECL|function|stop_ptraced_child
r_static
r_void
id|stop_ptraced_child
c_func
(paren
r_int
id|pid
comma
r_void
op_star
id|stack
comma
r_int
id|exitcode
)paren
(brace
r_int
id|status
comma
id|n
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
id|panic
c_func
(paren
l_string|&quot;check_ptrace : ptrace failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
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
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|WIFEXITED
c_func
(paren
id|status
)paren
op_logical_or
(paren
id|WEXITSTATUS
c_func
(paren
id|status
)paren
op_ne
id|exitcode
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_ptrace : child exited with status 0x%x&quot;
comma
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|munmap
c_func
(paren
id|stack
comma
id|PAGE_SIZE
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_ptrace : munmap failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|variable|force_sysemu_disabled
r_static
r_int
id|force_sysemu_disabled
op_assign
l_int|0
suffix:semicolon
DECL|function|nosysemu_cmd_param
r_static
r_int
id|__init
id|nosysemu_cmd_param
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|add
)paren
(brace
id|force_sysemu_disabled
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
l_string|&quot;nosysemu&quot;
comma
id|nosysemu_cmd_param
comma
l_string|&quot;nosysemu&bslash;n&quot;
l_string|&quot;    Turns off syscall emulation patch for ptrace (SYSEMU) on.&bslash;n&quot;
l_string|&quot;    SYSEMU is a performance-patch introduced by Laurent Vivier. It changes&bslash;n&quot;
l_string|&quot;    behaviour of ptrace() and helps reducing host context switch rate.&bslash;n&quot;
l_string|&quot;    To make it working, you need a kernel patch for your host, too.&bslash;n&quot;
l_string|&quot;    See http://perso.wanadoo.fr/laurent.vivier/UML/ for further information.&bslash;n&quot;
)paren
suffix:semicolon
DECL|function|check_sysemu
r_static
r_void
id|__init
id|check_sysemu
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|stack
suffix:semicolon
r_int
id|pid
comma
id|n
comma
id|status
suffix:semicolon
r_if
c_cond
(paren
id|mode_tt
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Checking syscall emulation patch for ptrace...&quot;
)paren
suffix:semicolon
id|sysemu_supported
op_assign
l_int|0
suffix:semicolon
id|pid
op_assign
id|start_ptraced_child
c_func
(paren
op_amp
id|stack
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|PTRACE_SYSEMU
comma
id|pid
comma
l_int|0
comma
l_int|0
)paren
op_ge
l_int|0
)paren
(brace
r_struct
id|user_regs_struct
id|regs
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
id|panic
c_func
(paren
l_string|&quot;check_ptrace : wait failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|WIFSTOPPED
c_func
(paren
id|status
)paren
op_logical_or
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_ne
id|SIGTRAP
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_ptrace : expected SIGTRAP, &quot;
l_string|&quot;got status = %d&quot;
comma
id|status
)paren
suffix:semicolon
)brace
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
op_amp
id|regs
)paren
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;check_ptrace : failed to read child &quot;
l_string|&quot;registers, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
id|regs.orig_eax
op_assign
id|pid
suffix:semicolon
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
op_amp
id|regs
)paren
OL
l_int|0
)paren
id|panic
c_func
(paren
l_string|&quot;check_ptrace : failed to modify child &quot;
l_string|&quot;registers, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
id|stop_ptraced_child
c_func
(paren
id|pid
comma
id|stack
comma
l_int|0
)paren
suffix:semicolon
id|sysemu_supported
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;found&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|stop_ptraced_child
c_func
(paren
id|pid
comma
id|stack
comma
l_int|1
)paren
suffix:semicolon
id|sysemu_supported
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;missing&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|set_using_sysemu
c_func
(paren
op_logical_neg
id|force_sysemu_disabled
)paren
suffix:semicolon
)brace
DECL|function|check_ptrace
r_void
id|__init
id|check_ptrace
c_func
(paren
r_void
)paren
(brace
r_void
op_star
id|stack
suffix:semicolon
r_int
id|pid
comma
id|syscall
comma
id|n
comma
id|status
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Checking that ptrace can change system call numbers...&quot;
)paren
suffix:semicolon
id|pid
op_assign
id|start_ptraced_child
c_func
(paren
op_amp
id|stack
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
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
id|panic
c_func
(paren
l_string|&quot;check_ptrace : ptrace failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
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
id|panic
c_func
(paren
l_string|&quot;check_ptrace : wait failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|WIFSTOPPED
c_func
(paren
id|status
)paren
op_logical_or
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_ne
id|SIGTRAP
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_ptrace : expected SIGTRAP, &quot;
l_string|&quot;got status = %d&quot;
comma
id|status
)paren
suffix:semicolon
)brace
id|syscall
op_assign
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
r_if
c_cond
(paren
id|syscall
op_eq
id|__NR_getpid
)paren
(brace
id|n
op_assign
id|ptrace
c_func
(paren
id|PTRACE_POKEUSER
comma
id|pid
comma
id|PT_SYSCALL_NR_OFFSET
comma
id|__NR_getppid
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
id|panic
c_func
(paren
l_string|&quot;check_ptrace : failed to modify system &quot;
l_string|&quot;call, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
)brace
id|stop_ptraced_child
c_func
(paren
id|pid
comma
id|stack
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;OK&bslash;n&quot;
)paren
suffix:semicolon
id|check_sysemu
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|run_kernel_thread
r_int
id|run_kernel_thread
c_func
(paren
r_int
(paren
op_star
id|fn
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
comma
r_void
op_star
op_star
id|jmp_ptr
)paren
(brace
id|jmp_buf
id|buf
suffix:semicolon
r_int
id|n
suffix:semicolon
op_star
id|jmp_ptr
op_assign
op_amp
id|buf
suffix:semicolon
id|n
op_assign
id|sigsetjmp
c_func
(paren
id|buf
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
l_int|0
)paren
(brace
r_return
id|n
suffix:semicolon
)brace
(paren
op_star
id|fn
)paren
(paren
id|arg
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|forward_pending_sigio
r_void
id|forward_pending_sigio
c_func
(paren
r_int
id|target
)paren
(brace
id|sigset_t
id|sigs
suffix:semicolon
r_if
c_cond
(paren
id|sigpending
c_func
(paren
op_amp
id|sigs
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;forward_pending_sigio : sigpending failed&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sigismember
c_func
(paren
op_amp
id|sigs
comma
id|SIGIO
)paren
)paren
(brace
id|kill
c_func
(paren
id|target
comma
id|SIGIO
)paren
suffix:semicolon
)brace
)brace
DECL|function|can_do_skas
r_int
id|can_do_skas
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef UML_CONFIG_MODE_SKAS
r_struct
id|ptrace_faultinfo
id|fi
suffix:semicolon
r_void
op_star
id|stack
suffix:semicolon
r_int
id|pid
comma
id|n
comma
id|ret
op_assign
l_int|1
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Checking for the skas3 patch in the host...&quot;
)paren
suffix:semicolon
id|pid
op_assign
id|start_ptraced_child
c_func
(paren
op_amp
id|stack
)paren
suffix:semicolon
id|n
op_assign
id|ptrace
c_func
(paren
id|PTRACE_FAULTINFO
comma
id|pid
comma
l_int|0
comma
op_amp
id|fi
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
r_if
c_cond
(paren
id|errno
op_eq
id|EIO
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;not found&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;No (unexpected errno - %d)&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;found&bslash;n&quot;
)paren
suffix:semicolon
id|init_registers
c_func
(paren
id|pid
)paren
suffix:semicolon
id|stop_ptraced_child
c_func
(paren
id|pid
comma
id|stack
comma
l_int|1
)paren
suffix:semicolon
id|printf
c_func
(paren
l_string|&quot;Checking for /proc/mm...&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|os_access
c_func
(paren
l_string|&quot;/proc/mm&quot;
comma
id|OS_ACC_W_OK
)paren
OL
l_int|0
)paren
(brace
id|printf
c_func
(paren
l_string|&quot;not found&bslash;n&quot;
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|printf
c_func
(paren
l_string|&quot;found&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
macro_line|#else
r_return
l_int|0
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
