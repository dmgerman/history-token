multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Licensed under the GPL&n; */
macro_line|#include &quot;linux/config.h&quot;
macro_line|#include &quot;linux/stddef.h&quot;
macro_line|#include &quot;linux/sys.h&quot;
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;linux/wait.h&quot;
macro_line|#include &quot;linux/kernel.h&quot;
macro_line|#include &quot;linux/smp_lock.h&quot;
macro_line|#include &quot;linux/module.h&quot;
macro_line|#include &quot;linux/slab.h&quot;
macro_line|#include &quot;linux/tty.h&quot;
macro_line|#include &quot;linux/binfmts.h&quot;
macro_line|#include &quot;asm/signal.h&quot;
macro_line|#include &quot;asm/uaccess.h&quot;
macro_line|#include &quot;asm/unistd.h&quot;
macro_line|#include &quot;user_util.h&quot;
macro_line|#include &quot;asm/ucontext.h&quot;
macro_line|#include &quot;kern_util.h&quot;
macro_line|#include &quot;signal_kern.h&quot;
macro_line|#include &quot;signal_user.h&quot;
macro_line|#include &quot;kern.h&quot;
macro_line|#include &quot;frame_kern.h&quot;
macro_line|#include &quot;sigcontext.h&quot;
macro_line|#include &quot;mode.h&quot;
DECL|variable|block_signals
id|EXPORT_SYMBOL
c_func
(paren
id|block_signals
)paren
suffix:semicolon
DECL|variable|unblock_signals
id|EXPORT_SYMBOL
c_func
(paren
id|unblock_signals
)paren
suffix:semicolon
DECL|function|force_segv
r_static
r_void
id|force_segv
c_func
(paren
r_int
id|sig
)paren
(brace
r_if
c_cond
(paren
id|sig
op_eq
id|SIGSEGV
)paren
(brace
r_struct
id|k_sigaction
op_star
id|ka
suffix:semicolon
id|ka
op_assign
op_amp
id|current-&gt;sig-&gt;action
(braket
id|SIGSEGV
op_minus
l_int|1
)braket
suffix:semicolon
id|ka-&gt;sa.sa_handler
op_assign
id|SIG_DFL
suffix:semicolon
)brace
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
)brace
DECL|macro|_S
mdefine_line|#define _S(nr) (1&lt;&lt;((nr)-1))
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(_S(SIGKILL) | _S(SIGSTOP)))
multiline_comment|/*&n; * OK, we&squot;re invoking a handler&n; */
DECL|function|handle_signal
r_static
r_int
id|handle_signal
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|signr
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
id|siginfo_t
op_star
id|info
comma
id|sigset_t
op_star
id|oldset
comma
r_int
id|error
)paren
(brace
id|__sighandler_t
id|handler
suffix:semicolon
r_void
(paren
op_star
id|restorer
)paren
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|sp
suffix:semicolon
id|sigset_t
id|save
suffix:semicolon
r_int
id|err
comma
id|ret
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|error
)paren
(brace
r_case
op_minus
id|ERESTART_RESTARTBLOCK
suffix:colon
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|restart_block.fn
op_assign
id|do_no_restart_syscall
suffix:semicolon
r_case
op_minus
id|ERESTARTNOHAND
suffix:colon
id|ret
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
r_case
op_minus
id|ERESTARTSYS
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTART
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* fallthrough */
r_case
op_minus
id|ERESTARTNOINTR
suffix:colon
id|PT_REGS_RESTART_SYSCALL
c_func
(paren
id|regs
)paren
suffix:semicolon
id|PT_REGS_ORIG_SYSCALL
c_func
(paren
id|regs
)paren
op_assign
id|PT_REGS_SYSCALL_NR
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* This is because of the UM_SET_SYSCALL_RETURN and the fact&n;&t;&t; * that on i386 the system call number and return value are&n;&t;&t; * in the same register.  When the system call restarts, %eax&n;&t;&t; * had better have the system call number in it.  Since the&n;&t;&t; * return value doesn&squot;t matter (except that it shouldn&squot;t be&n;&t;&t; * -ERESTART*), we&squot;ll stick the system call number there.&n;&t;&t; */
id|ret
op_assign
id|PT_REGS_SYSCALL_NR
c_func
(paren
id|regs
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|handler
op_assign
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|save
op_assign
op_star
id|oldset
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_ONESHOT
)paren
id|ka-&gt;sa.sa_handler
op_assign
id|SIG_DFL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_NODEFER
)paren
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|sigorsets
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_amp
id|current-&gt;blocked
comma
op_amp
id|ka-&gt;sa.sa_mask
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|signr
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
)brace
id|sp
op_assign
id|PT_REGS_SP
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_ONSTACK
)paren
op_logical_and
(paren
id|sas_ss_flags
c_func
(paren
id|sp
)paren
op_eq
l_int|0
)paren
)paren
(brace
id|sp
op_assign
id|current-&gt;sas_ss_sp
op_plus
id|current-&gt;sas_ss_size
suffix:semicolon
)brace
r_if
c_cond
(paren
id|error
op_ne
l_int|0
)paren
(brace
id|PT_REGS_SET_SYSCALL_RETURN
c_func
(paren
id|regs
comma
id|ret
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
id|restorer
op_assign
id|ka-&gt;sa.sa_restorer
suffix:semicolon
r_else
id|restorer
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_SIGINFO
)paren
(brace
id|err
op_assign
id|setup_signal_stack_si
c_func
(paren
id|sp
comma
id|signr
comma
(paren
r_int
r_int
)paren
id|handler
comma
id|restorer
comma
id|regs
comma
id|info
comma
op_amp
id|save
)paren
suffix:semicolon
)brace
r_else
id|err
op_assign
id|setup_signal_stack_sc
c_func
(paren
id|sp
comma
id|signr
comma
(paren
r_int
r_int
)paren
id|handler
comma
id|restorer
comma
id|regs
comma
op_amp
id|save
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
r_goto
id|segv
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
id|segv
suffix:colon
id|force_segv
c_func
(paren
id|signr
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|kern_do_signal
r_static
r_int
id|kern_do_signal
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|sigset_t
op_star
id|oldset
comma
r_int
id|error
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_struct
id|k_sigaction
op_star
id|ka
suffix:semicolon
r_int
id|err
comma
id|sig
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|oldset
)paren
id|oldset
op_assign
op_amp
id|current-&gt;blocked
suffix:semicolon
id|sig
op_assign
id|get_signal_to_deliver
c_func
(paren
op_amp
id|info
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sig
op_eq
l_int|0
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Whee!  Actually deliver the signal.  */
id|ka
op_assign
op_amp
id|current-&gt;sig-&gt;action
(braket
id|sig
op_minus
l_int|1
)braket
suffix:semicolon
id|err
op_assign
id|handle_signal
c_func
(paren
id|regs
comma
id|sig
comma
id|ka
comma
op_amp
id|info
comma
id|oldset
comma
id|error
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
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Did we come from a system call? */
r_if
c_cond
(paren
id|PT_REGS_SYSCALL_NR
c_func
(paren
id|regs
)paren
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Restart the system call - no handlers present */
r_if
c_cond
(paren
id|PT_REGS_SYSCALL_RET
c_func
(paren
id|regs
)paren
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|PT_REGS_SYSCALL_RET
c_func
(paren
id|regs
)paren
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|PT_REGS_SYSCALL_RET
c_func
(paren
id|regs
)paren
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|PT_REGS_ORIG_SYSCALL
c_func
(paren
id|regs
)paren
op_assign
id|PT_REGS_SYSCALL_NR
c_func
(paren
id|regs
)paren
suffix:semicolon
id|PT_REGS_RESTART_SYSCALL
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|PT_REGS_SYSCALL_RET
c_func
(paren
id|regs
)paren
op_eq
op_minus
id|ERESTART_RESTARTBLOCK
)paren
(brace
id|PT_REGS_SYSCALL_RET
c_func
(paren
id|regs
)paren
op_assign
id|__NR_restart_syscall
suffix:semicolon
id|PT_REGS_RESTART_SYSCALL
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* This closes a way to execute a system call on the host.  If&n;&t; * you set a breakpoint on a system call instruction and singlestep&n;&t; * from it, the tracing thread used to PTRACE_SINGLESTEP the process&n;&t; * rather than PTRACE_SYSCALL it, allowing the system call to execute&n;&t; * on the host.  The tracing thread will check this flag and &n;&t; * PTRACE_SYSCALL if necessary.&n;&t; */
r_if
c_cond
(paren
(paren
id|current-&gt;ptrace
op_amp
id|PT_DTRACE
)paren
op_logical_and
id|is_syscall
c_func
(paren
id|PT_REGS_IP
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
)paren
)paren
(brace
(paren
r_void
)paren
id|CHOOSE_MODE
c_func
(paren
id|current-&gt;thread.mode.tt.singlestep_syscall
op_assign
l_int|1
comma
l_int|0
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|do_signal
r_int
id|do_signal
c_func
(paren
r_int
id|error
)paren
(brace
r_return
id|kern_do_signal
c_func
(paren
op_amp
id|current-&gt;thread.regs
comma
l_int|NULL
comma
id|error
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Atomically swap in the new signal mask, and wait for a signal.&n; */
DECL|function|sys_sigsuspend
r_int
id|sys_sigsuspend
c_func
(paren
r_int
id|history0
comma
r_int
id|history1
comma
id|old_sigset_t
id|mask
)paren
(brace
id|sigset_t
id|saveset
suffix:semicolon
id|mask
op_and_assign
id|_BLOCKABLE
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|saveset
op_assign
id|current-&gt;blocked
suffix:semicolon
id|siginitset
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|mask
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kern_do_signal
c_func
(paren
op_amp
id|current-&gt;thread.regs
comma
op_amp
id|saveset
comma
op_minus
id|EINTR
)paren
)paren
(brace
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
)brace
DECL|function|sys_rt_sigsuspend
r_int
id|sys_rt_sigsuspend
c_func
(paren
id|sigset_t
op_star
id|unewset
comma
r_int
id|sigsetsize
)paren
(brace
id|sigset_t
id|saveset
comma
id|newset
suffix:semicolon
multiline_comment|/* XXX: Don&squot;t preclude handling different sized sigset_t&squot;s.  */
r_if
c_cond
(paren
id|sigsetsize
op_ne
r_sizeof
(paren
id|sigset_t
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|newset
comma
id|unewset
comma
r_sizeof
(paren
id|newset
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|newset
comma
op_complement
id|_BLOCKABLE
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|saveset
op_assign
id|current-&gt;blocked
suffix:semicolon
id|current-&gt;blocked
op_assign
id|newset
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|current-&gt;state
op_assign
id|TASK_INTERRUPTIBLE
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kern_do_signal
c_func
(paren
op_amp
id|current-&gt;thread.regs
comma
op_amp
id|saveset
comma
op_minus
id|EINTR
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
DECL|function|copy_sc_from_user
r_static
r_int
id|copy_sc_from_user
c_func
(paren
r_struct
id|pt_regs
op_star
id|to
comma
r_void
op_star
id|from
comma
r_struct
id|arch_frame_data
op_star
id|arch
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|CHOOSE_MODE
c_func
(paren
id|copy_sc_from_user_tt
c_func
(paren
id|UPT_SC
c_func
(paren
op_amp
id|to-&gt;regs
)paren
comma
id|from
comma
id|arch
)paren
comma
id|copy_sc_from_user_skas
c_func
(paren
op_amp
id|to-&gt;regs
comma
id|from
)paren
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|sys_sigreturn
r_int
id|sys_sigreturn
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_void
op_star
id|sc
op_assign
id|sp_to_sc
c_func
(paren
id|PT_REGS_SP
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
)paren
suffix:semicolon
r_void
op_star
id|mask
op_assign
id|sp_to_mask
c_func
(paren
id|PT_REGS_SP
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
)paren
suffix:semicolon
r_int
id|sig_size
op_assign
(paren
id|_NSIG_WORDS
op_minus
l_int|1
)paren
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|copy_from_user
c_func
(paren
op_amp
id|current-&gt;blocked.sig
(braket
l_int|0
)braket
comma
id|sc_sigmask
c_func
(paren
id|sc
)paren
comma
r_sizeof
(paren
id|current-&gt;blocked.sig
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
id|copy_from_user
c_func
(paren
op_amp
id|current-&gt;blocked.sig
(braket
l_int|1
)braket
comma
id|mask
comma
id|sig_size
)paren
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_complement
id|_BLOCKABLE
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|copy_sc_from_user
c_func
(paren
op_amp
id|current-&gt;thread.regs
comma
id|sc
comma
op_amp
id|signal_frame_sc.common.arch
)paren
suffix:semicolon
r_return
id|PT_REGS_SYSCALL_RET
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
suffix:semicolon
)brace
DECL|function|sys_rt_sigreturn
r_int
id|sys_rt_sigreturn
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_struct
id|ucontext
op_star
id|uc
op_assign
id|sp_to_uc
c_func
(paren
id|PT_REGS_SP
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
)paren
suffix:semicolon
r_void
op_star
id|fp
suffix:semicolon
r_int
id|sig_size
op_assign
id|_NSIG_WORDS
op_star
r_sizeof
(paren
r_int
r_int
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|copy_from_user
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_amp
id|uc-&gt;uc_sigmask
comma
id|sig_size
)paren
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_complement
id|_BLOCKABLE
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
id|fp
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|uc
)paren
op_plus
r_sizeof
(paren
r_struct
id|ucontext
)paren
)paren
suffix:semicolon
id|copy_sc_from_user
c_func
(paren
op_amp
id|current-&gt;thread.regs
comma
op_amp
id|uc-&gt;uc_mcontext
comma
op_amp
id|signal_frame_si.common.arch
)paren
suffix:semicolon
r_return
id|PT_REGS_SYSCALL_RET
c_func
(paren
op_amp
id|current-&gt;thread.regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
