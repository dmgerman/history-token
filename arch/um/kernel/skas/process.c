multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;setjmp.h&gt;
macro_line|#include &lt;sched.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/mman.h&gt;
macro_line|#include &lt;sys/user.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &quot;user.h&quot;
macro_line|#include &quot;ptrace_user.h&quot;
macro_line|#include &quot;time_user.h&quot;
macro_line|#include &quot;sysdep/ptrace.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;skas.h&quot;
macro_line|#include &quot;sysdep/sigcontext.h&quot;
macro_line|#include &quot;os.h&quot;
macro_line|#include &quot;proc_mm.h&quot;
macro_line|#include &quot;skas_ptrace.h&quot;
macro_line|#include &quot;chan_user.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;registers.h&quot;
DECL|function|is_skas_winch
r_int
id|is_skas_winch
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
id|os_getpid
c_func
(paren
)paren
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
id|register_winch_irq
c_func
(paren
op_minus
l_int|1
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
DECL|function|handle_segv
r_static
r_void
id|handle_segv
c_func
(paren
r_int
id|pid
)paren
(brace
r_struct
id|ptrace_faultinfo
id|fault
suffix:semicolon
r_int
id|err
suffix:semicolon
id|err
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
id|fault
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;handle_segv - PTRACE_FAULTINFO failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
id|segv
c_func
(paren
id|fault.addr
comma
l_int|0
comma
id|FAULT_WRITE
c_func
(paren
id|fault.is_write
)paren
comma
l_int|1
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*To use the same value of using_sysemu as the caller, ask it that value (in local_using_sysemu)*/
DECL|function|handle_trap
r_static
r_void
id|handle_trap
c_func
(paren
r_int
id|pid
comma
r_union
id|uml_pt_regs
op_star
id|regs
comma
r_int
id|local_using_sysemu
)paren
(brace
r_int
id|err
comma
id|status
suffix:semicolon
multiline_comment|/* Mark this as a syscall */
id|UPT_SYSCALL_NR
c_func
(paren
id|regs
)paren
op_assign
id|PT_SYSCALL_NR
c_func
(paren
id|regs-&gt;skas.regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|local_using_sysemu
)paren
(brace
id|err
op_assign
id|ptrace
c_func
(paren
id|PTRACE_POKEUSR
comma
id|pid
comma
id|PT_SYSCALL_NR_OFFSET
comma
id|__NR_getpid
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
l_string|&quot;handle_trap - nullifying syscall failed errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
id|err
op_assign
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
l_string|&quot;handle_trap - continuing to end of syscall failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|errno
)paren
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
(paren
id|err
OL
l_int|0
)paren
op_logical_or
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
op_plus
l_int|0x80
)paren
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;handle_trap - failed to wait at end of syscall, &quot;
l_string|&quot;errno = %d, status = %d&bslash;n&quot;
comma
id|errno
comma
id|status
)paren
suffix:semicolon
)brace
)brace
id|handle_syscall
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
DECL|function|userspace_tramp
r_static
r_int
id|userspace_tramp
c_func
(paren
r_void
op_star
id|arg
)paren
(brace
id|init_new_thread_signals
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|enable_timer
c_func
(paren
)paren
suffix:semicolon
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
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Each element set once, and only accessed by a single processor anyway */
DECL|macro|NR_CPUS
macro_line|#undef NR_CPUS
DECL|macro|NR_CPUS
mdefine_line|#define NR_CPUS 1
DECL|variable|userspace_pid
r_int
id|userspace_pid
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|start_userspace
r_void
id|start_userspace
c_func
(paren
r_int
id|cpu
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
id|status
comma
id|n
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
l_string|&quot;start_userspace : mmap failed, errno = %d&quot;
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
id|userspace_tramp
comma
(paren
r_void
op_star
)paren
id|sp
comma
id|CLONE_FILES
op_or
id|CLONE_VM
op_or
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
l_string|&quot;start_userspace : clone failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_do
(brace
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
l_string|&quot;start_userspace : wait failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|WIFSTOPPED
c_func
(paren
id|status
)paren
op_logical_and
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
op_eq
id|SIGVTALRM
)paren
)paren
(brace
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
l_string|&quot;start_userspace : expected SIGSTOP, got status = %d&quot;
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
id|PTRACE_OLDSETOPTIONS
comma
id|pid
comma
l_int|NULL
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
id|panic
c_func
(paren
l_string|&quot;start_userspace : PTRACE_SETOPTIONS failed, errno=%d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
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
l_string|&quot;start_userspace : munmap failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
id|userspace_pid
(braket
id|cpu
)braket
op_assign
id|pid
suffix:semicolon
)brace
DECL|function|userspace
r_void
id|userspace
c_func
(paren
r_union
id|uml_pt_regs
op_star
id|regs
)paren
(brace
r_int
id|err
comma
id|status
comma
id|op
comma
id|pid
op_assign
id|userspace_pid
(braket
l_int|0
)braket
suffix:semicolon
r_int
id|local_using_sysemu
suffix:semicolon
multiline_comment|/*To prevent races if using_sysemu changes under us.*/
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|restore_registers
c_func
(paren
id|pid
comma
id|regs
)paren
suffix:semicolon
multiline_comment|/* Now we set local_using_sysemu to be used for one loop */
id|local_using_sysemu
op_assign
id|get_using_sysemu
c_func
(paren
)paren
suffix:semicolon
id|op
op_assign
id|SELECT_PTRACE_OPERATION
c_func
(paren
id|local_using_sysemu
comma
id|singlestepping
c_func
(paren
l_int|NULL
)paren
)paren
suffix:semicolon
id|err
op_assign
id|ptrace
c_func
(paren
id|op
comma
id|pid
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;userspace - could not resume userspace process, &quot;
l_string|&quot;pid=%d, ptrace operation = %d, errno = %d&bslash;n&quot;
comma
id|op
comma
id|errno
)paren
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
id|err
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;userspace - waitpid failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
id|regs-&gt;skas.is_user
op_assign
l_int|1
suffix:semicolon
id|save_registers
c_func
(paren
id|pid
comma
id|regs
)paren
suffix:semicolon
id|UPT_SYSCALL_NR
c_func
(paren
id|regs
)paren
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* Assume: It&squot;s not a syscall */
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
r_switch
c_cond
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
)paren
(brace
r_case
id|SIGSEGV
suffix:colon
id|handle_segv
c_func
(paren
id|pid
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIGTRAP
op_plus
l_int|0x80
suffix:colon
id|handle_trap
c_func
(paren
id|pid
comma
id|regs
comma
id|local_using_sysemu
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIGTRAP
suffix:colon
id|relay_signal
c_func
(paren
id|SIGTRAP
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SIGIO
suffix:colon
r_case
id|SIGVTALRM
suffix:colon
r_case
id|SIGILL
suffix:colon
r_case
id|SIGBUS
suffix:colon
r_case
id|SIGFPE
suffix:colon
r_case
id|SIGWINCH
suffix:colon
id|user_signal
c_func
(paren
id|WSTOPSIG
c_func
(paren
id|status
)paren
comma
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
l_string|&quot;userspace - child stopped with signal &quot;
l_string|&quot;%d&bslash;n&quot;
comma
id|WSTOPSIG
c_func
(paren
id|status
)paren
)paren
suffix:semicolon
)brace
id|interrupt_end
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Avoid -ERESTARTSYS handling in host */
id|PT_SYSCALL_NR
c_func
(paren
id|regs-&gt;skas.regs
)paren
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
)brace
DECL|function|new_thread
r_void
id|new_thread
c_func
(paren
r_void
op_star
id|stack
comma
r_void
op_star
op_star
id|switch_buf_ptr
comma
r_void
op_star
op_star
id|fork_buf_ptr
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
)paren
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|sigjmp_buf
id|switch_buf
comma
id|fork_buf
suffix:semicolon
op_star
id|switch_buf_ptr
op_assign
op_amp
id|switch_buf
suffix:semicolon
op_star
id|fork_buf_ptr
op_assign
op_amp
id|fork_buf
suffix:semicolon
multiline_comment|/* Somewhat subtle - siglongjmp restores the signal mask before doing&n;&t; * the longjmp.  This means that when jumping from one stack to another&n;&t; * when the target stack has interrupts enabled, an interrupt may occur&n;&t; * on the source stack.  This is bad when starting up a process because&n;&t; * it&squot;s not supposed to get timer ticks until it has been scheduled.&n;&t; * So, we disable interrupts around the sigsetjmp to ensure that&n;&t; * they can&squot;t happen until we get back here where they are safe.&n;&t; */
id|flags
op_assign
id|get_signals
c_func
(paren
)paren
suffix:semicolon
id|block_signals
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sigsetjmp
c_func
(paren
id|fork_buf
comma
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|new_thread_proc
c_func
(paren
id|stack
comma
id|handler
)paren
suffix:semicolon
)brace
id|remove_sigstack
c_func
(paren
)paren
suffix:semicolon
id|set_signals
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|thread_wait
r_void
id|thread_wait
c_func
(paren
r_void
op_star
id|sw
comma
r_void
op_star
id|fb
)paren
(brace
id|sigjmp_buf
id|buf
comma
op_star
op_star
id|switch_buf
op_assign
id|sw
comma
op_star
id|fork_buf
suffix:semicolon
op_star
id|switch_buf
op_assign
op_amp
id|buf
suffix:semicolon
id|fork_buf
op_assign
id|fb
suffix:semicolon
r_if
c_cond
(paren
id|sigsetjmp
c_func
(paren
id|buf
comma
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|siglongjmp
c_func
(paren
op_star
id|fork_buf
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|function|switch_threads
r_void
id|switch_threads
c_func
(paren
r_void
op_star
id|me
comma
r_void
op_star
id|next
)paren
(brace
id|sigjmp_buf
id|my_buf
comma
op_star
op_star
id|me_ptr
op_assign
id|me
comma
op_star
id|next_buf
op_assign
id|next
suffix:semicolon
op_star
id|me_ptr
op_assign
op_amp
id|my_buf
suffix:semicolon
r_if
c_cond
(paren
id|sigsetjmp
c_func
(paren
id|my_buf
comma
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|siglongjmp
c_func
(paren
op_star
id|next_buf
comma
l_int|1
)paren
suffix:semicolon
)brace
)brace
DECL|variable|initial_jmpbuf
r_static
id|sigjmp_buf
id|initial_jmpbuf
suffix:semicolon
multiline_comment|/* XXX Make these percpu */
DECL|variable|cb_proc
r_static
r_void
(paren
op_star
id|cb_proc
)paren
(paren
r_void
op_star
id|arg
)paren
suffix:semicolon
DECL|variable|cb_arg
r_static
r_void
op_star
id|cb_arg
suffix:semicolon
DECL|variable|cb_back
r_static
id|sigjmp_buf
op_star
id|cb_back
suffix:semicolon
DECL|function|start_idle_thread
r_int
id|start_idle_thread
c_func
(paren
r_void
op_star
id|stack
comma
r_void
op_star
id|switch_buf_ptr
comma
r_void
op_star
op_star
id|fork_buf_ptr
)paren
(brace
id|sigjmp_buf
op_star
op_star
id|switch_buf
op_assign
id|switch_buf_ptr
suffix:semicolon
r_int
id|n
suffix:semicolon
op_star
id|fork_buf_ptr
op_assign
op_amp
id|initial_jmpbuf
suffix:semicolon
id|n
op_assign
id|sigsetjmp
c_func
(paren
id|initial_jmpbuf
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_eq
l_int|0
)paren
(brace
id|new_thread_proc
c_func
(paren
(paren
r_void
op_star
)paren
id|stack
comma
id|new_thread_handler
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_eq
l_int|1
)paren
(brace
id|remove_sigstack
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_eq
l_int|2
)paren
(brace
(paren
op_star
id|cb_proc
)paren
(paren
id|cb_arg
)paren
suffix:semicolon
id|siglongjmp
c_func
(paren
op_star
id|cb_back
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_eq
l_int|3
)paren
(brace
id|kmalloc_ok
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|n
op_eq
l_int|4
)paren
(brace
id|kmalloc_ok
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|siglongjmp
c_func
(paren
op_star
op_star
id|switch_buf
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|remove_sigstack
r_void
id|remove_sigstack
c_func
(paren
r_void
)paren
(brace
id|stack_t
id|stack
op_assign
(paren
(paren
id|stack_t
)paren
(brace
dot
id|ss_flags
op_assign
id|SS_DISABLE
comma
dot
id|ss_sp
op_assign
l_int|NULL
comma
dot
id|ss_size
op_assign
l_int|0
)brace
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sigaltstack
c_func
(paren
op_amp
id|stack
comma
l_int|NULL
)paren
op_ne
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;disabling signal stack failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|initial_thread_cb_skas
r_void
id|initial_thread_cb_skas
c_func
(paren
r_void
(paren
op_star
id|proc
)paren
(paren
r_void
op_star
)paren
comma
r_void
op_star
id|arg
)paren
(brace
id|sigjmp_buf
id|here
suffix:semicolon
id|cb_proc
op_assign
id|proc
suffix:semicolon
id|cb_arg
op_assign
id|arg
suffix:semicolon
id|cb_back
op_assign
op_amp
id|here
suffix:semicolon
id|block_signals
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sigsetjmp
c_func
(paren
id|here
comma
l_int|1
)paren
op_eq
l_int|0
)paren
(brace
id|siglongjmp
c_func
(paren
id|initial_jmpbuf
comma
l_int|2
)paren
suffix:semicolon
)brace
id|unblock_signals
c_func
(paren
)paren
suffix:semicolon
id|cb_proc
op_assign
l_int|NULL
suffix:semicolon
id|cb_arg
op_assign
l_int|NULL
suffix:semicolon
id|cb_back
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|halt_skas
r_void
id|halt_skas
c_func
(paren
r_void
)paren
(brace
id|block_signals
c_func
(paren
)paren
suffix:semicolon
id|siglongjmp
c_func
(paren
id|initial_jmpbuf
comma
l_int|3
)paren
suffix:semicolon
)brace
DECL|function|reboot_skas
r_void
id|reboot_skas
c_func
(paren
r_void
)paren
(brace
id|block_signals
c_func
(paren
)paren
suffix:semicolon
id|siglongjmp
c_func
(paren
id|initial_jmpbuf
comma
l_int|4
)paren
suffix:semicolon
)brace
DECL|function|switch_mm_skas
r_void
id|switch_mm_skas
c_func
(paren
r_int
id|mm_fd
)paren
(brace
r_int
id|err
suffix:semicolon
macro_line|#warning need cpu pid in switch_mm_skas
id|err
op_assign
id|ptrace
c_func
(paren
id|PTRACE_SWITCH_MM
comma
id|userspace_pid
(braket
l_int|0
)braket
comma
l_int|0
comma
id|mm_fd
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;switch_mm_skas - PTRACE_SWITCH_MM failed, errno = %d&bslash;n&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
DECL|function|kill_off_processes_skas
r_void
id|kill_off_processes_skas
c_func
(paren
r_void
)paren
(brace
macro_line|#warning need to loop over userspace_pids in kill_off_processes_skas
id|os_kill_ptraced_process
c_func
(paren
id|userspace_pid
(braket
l_int|0
)braket
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
