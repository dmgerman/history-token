multiline_comment|/* &n; * Copyright (C) 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &lt;stdlib.h&gt;
macro_line|#include &lt;unistd.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;signal.h&gt;
macro_line|#include &lt;setjmp.h&gt;
macro_line|#include &lt;sched.h&gt;
macro_line|#include &lt;sys/wait.h&gt;
macro_line|#include &lt;sys/ptrace.h&gt;
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
id|getpid
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
multiline_comment|/* These are set once at boot time and not changed thereafter */
DECL|variable|exec_regs
r_int
r_int
id|exec_regs
(braket
id|FRAME_SIZE
)braket
suffix:semicolon
DECL|variable|exec_fp_regs
r_int
r_int
id|exec_fp_regs
(braket
id|HOST_FP_SIZE
)braket
suffix:semicolon
DECL|variable|exec_fpx_regs
r_int
r_int
id|exec_fpx_regs
(braket
id|HOST_XFP_SIZE
)braket
suffix:semicolon
DECL|variable|have_fpx_regs
r_int
id|have_fpx_regs
op_assign
l_int|1
suffix:semicolon
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
id|syscall_nr
comma
id|status
suffix:semicolon
id|syscall_nr
op_assign
id|PT_SYSCALL_NR
c_func
(paren
id|regs-&gt;skas.regs
)paren
suffix:semicolon
id|UPT_SYSCALL_NR
c_func
(paren
id|regs
)paren
op_assign
id|syscall_nr
suffix:semicolon
r_if
c_cond
(paren
id|syscall_nr
OL
l_int|1
)paren
(brace
id|relay_signal
c_func
(paren
id|SIGTRAP
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|PTRACE_POKEUSER
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
id|restore_registers
c_func
(paren
id|regs
)paren
suffix:semicolon
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
id|local_using_sysemu
)paren
id|err
op_assign
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
suffix:semicolon
r_else
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
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;userspace - PTRACE_%s failed, errno = %d&bslash;n&quot;
comma
id|local_using_sysemu
ques
c_cond
l_string|&quot;SYSEMU&quot;
suffix:colon
l_string|&quot;SYSCALL&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
(brace
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
id|regs
)paren
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
)brace
id|restore_registers
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/*Now we ended the syscall, so re-read local_using_sysemu.*/
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
id|local_using_sysemu
)paren
id|op
op_assign
id|singlestepping_skas
c_func
(paren
)paren
ques
c_cond
id|PTRACE_SINGLESTEP
suffix:colon
id|PTRACE_SYSEMU
suffix:semicolon
r_else
id|op
op_assign
id|singlestepping_skas
c_func
(paren
)paren
ques
c_cond
id|PTRACE_SINGLESTEP
suffix:colon
id|PTRACE_SYSCALL
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
l_string|&quot;userspace - PTRACE_%s failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
id|local_using_sysemu
ques
c_cond
l_string|&quot;SYSEMU&quot;
suffix:colon
l_string|&quot;SYSCALL&quot;
comma
id|errno
)paren
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
id|set_signals
c_func
(paren
id|flags
)paren
suffix:semicolon
id|remove_sigstack
c_func
(paren
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
DECL|function|move_registers
r_static
r_int
id|move_registers
c_func
(paren
r_int
id|pid
comma
r_int
id|int_op
comma
r_int
id|fp_op
comma
r_union
id|uml_pt_regs
op_star
id|regs
comma
r_int
r_int
op_star
id|fp_regs
)paren
(brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|int_op
comma
id|pid
comma
l_int|0
comma
id|regs-&gt;skas.regs
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ptrace
c_func
(paren
id|fp_op
comma
id|pid
comma
l_int|0
comma
id|fp_regs
)paren
OL
l_int|0
)paren
(brace
r_return
op_minus
id|errno
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|save_registers
r_void
id|save_registers
c_func
(paren
r_union
id|uml_pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
op_star
id|fp_regs
suffix:semicolon
r_int
id|err
comma
id|fp_op
suffix:semicolon
r_if
c_cond
(paren
id|have_fpx_regs
)paren
(brace
id|fp_op
op_assign
id|PTRACE_GETFPXREGS
suffix:semicolon
id|fp_regs
op_assign
id|regs-&gt;skas.xfp
suffix:semicolon
)brace
r_else
(brace
id|fp_op
op_assign
id|PTRACE_GETFPREGS
suffix:semicolon
id|fp_regs
op_assign
id|regs-&gt;skas.fp
suffix:semicolon
)brace
id|err
op_assign
id|move_registers
c_func
(paren
id|userspace_pid
(braket
l_int|0
)braket
comma
id|PTRACE_GETREGS
comma
id|fp_op
comma
id|regs
comma
id|fp_regs
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
l_string|&quot;save_registers - saving registers failed, errno = %d&bslash;n&quot;
comma
op_minus
id|err
)paren
suffix:semicolon
)brace
)brace
DECL|function|restore_registers
r_void
id|restore_registers
c_func
(paren
r_union
id|uml_pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
op_star
id|fp_regs
suffix:semicolon
r_int
id|err
comma
id|fp_op
suffix:semicolon
r_if
c_cond
(paren
id|have_fpx_regs
)paren
(brace
id|fp_op
op_assign
id|PTRACE_SETFPXREGS
suffix:semicolon
id|fp_regs
op_assign
id|regs-&gt;skas.xfp
suffix:semicolon
)brace
r_else
(brace
id|fp_op
op_assign
id|PTRACE_SETFPREGS
suffix:semicolon
id|fp_regs
op_assign
id|regs-&gt;skas.fp
suffix:semicolon
)brace
id|err
op_assign
id|move_registers
c_func
(paren
id|userspace_pid
(braket
l_int|0
)braket
comma
id|PTRACE_SETREGS
comma
id|fp_op
comma
id|regs
comma
id|fp_regs
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
l_string|&quot;restore_registers - saving registers failed, &quot;
l_string|&quot;errno = %d&bslash;n&quot;
comma
op_minus
id|err
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
DECL|function|new_mm
r_int
id|new_mm
c_func
(paren
r_int
id|from
)paren
(brace
r_struct
id|proc_mm_op
id|copy
suffix:semicolon
r_int
id|n
comma
id|fd
op_assign
id|os_open_file
c_func
(paren
l_string|&quot;/proc/mm&quot;
comma
id|of_cloexec
c_func
(paren
id|of_write
c_func
(paren
id|OPENFLAGS
c_func
(paren
)paren
)paren
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|fd
OL
l_int|0
)paren
(brace
r_return
id|fd
suffix:semicolon
)brace
r_if
c_cond
(paren
id|from
op_ne
op_minus
l_int|1
)paren
(brace
id|copy
op_assign
(paren
(paren
r_struct
id|proc_mm_op
)paren
(brace
dot
id|op
op_assign
id|MM_COPY_SEGMENTS
comma
dot
id|u
op_assign
(brace
dot
id|copy_segments
op_assign
id|from
)brace
)brace
)paren
suffix:semicolon
id|n
op_assign
id|os_write_file
c_func
(paren
id|fd
comma
op_amp
id|copy
comma
r_sizeof
(paren
id|copy
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
id|copy
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;new_mm : /proc/mm copy_segments failed, &quot;
l_string|&quot;err = %d&bslash;n&quot;
comma
op_minus
id|n
)paren
suffix:semicolon
)brace
)brace
r_return
id|fd
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
id|os_kill_process
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
DECL|function|init_registers
r_void
id|init_registers
c_func
(paren
r_int
id|pid
)paren
(brace
r_int
id|err
suffix:semicolon
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
id|exec_regs
)paren
OL
l_int|0
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_ptrace : PTRACE_GETREGS failed, errno = %d&quot;
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
id|PTRACE_GETFPXREGS
comma
id|pid
comma
l_int|0
comma
id|exec_fpx_regs
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
(brace
r_return
suffix:semicolon
)brace
id|have_fpx_regs
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|errno
op_ne
id|EIO
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;check_ptrace : PTRACE_GETFPXREGS failed, errno = %d&quot;
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
id|PTRACE_GETFPREGS
comma
id|pid
comma
l_int|0
comma
id|exec_fp_regs
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
l_string|&quot;check_ptrace : PTRACE_GETFPREGS failed, errno = %d&quot;
comma
id|errno
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
