multiline_comment|/*&n; *  arch/s390/kernel/signal.c&n; *&n; *  S390 version&n; *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation&n; *    Author(s): Denis Joseph Barrow (djbarrow@de.ibm.com,barrow_dj@yahoo.com)&n; *&n; *    Based on Intel version&n; * &n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  1997-11-28  Modified for POSIX.1b signals by Richard Henderson&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/lowcore.h&gt;
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
r_typedef
r_struct
(brace
DECL|member|callee_used_stack
id|__u8
id|callee_used_stack
(braket
id|__SIGNAL_FRAMESIZE
)braket
suffix:semicolon
DECL|member|sc
r_struct
id|sigcontext
id|sc
suffix:semicolon
DECL|member|sregs
id|_sigregs
id|sregs
suffix:semicolon
DECL|member|retcode
id|__u8
id|retcode
(braket
id|S390_SYSCALL_SIZE
)braket
suffix:semicolon
DECL|typedef|sigframe
)brace
id|sigframe
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|callee_used_stack
id|__u8
id|callee_used_stack
(braket
id|__SIGNAL_FRAMESIZE
)braket
suffix:semicolon
DECL|member|retcode
id|__u8
id|retcode
(braket
id|S390_SYSCALL_SIZE
)braket
suffix:semicolon
DECL|member|info
r_struct
id|siginfo
id|info
suffix:semicolon
DECL|member|uc
r_struct
id|ucontext
id|uc
suffix:semicolon
DECL|typedef|rt_sigframe
)brace
id|rt_sigframe
suffix:semicolon
r_int
id|do_signal
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
)paren
suffix:semicolon
multiline_comment|/*&n; * Atomically swap in the new signal mask, and wait for a signal.&n; */
id|asmlinkage
r_int
DECL|function|sys_sigsuspend
id|sys_sigsuspend
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
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
id|regs-&gt;gprs
(braket
l_int|2
)braket
op_assign
op_minus
id|EINTR
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_signal
c_func
(paren
id|regs
comma
op_amp
id|saveset
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
id|asmlinkage
r_int
DECL|function|sys_rt_sigsuspend
id|sys_rt_sigsuspend
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
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
id|regs-&gt;gprs
(braket
l_int|2
)braket
op_assign
op_minus
id|EINTR
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
id|set_current_state
c_func
(paren
id|TASK_INTERRUPTIBLE
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|do_signal
c_func
(paren
id|regs
comma
op_amp
id|saveset
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
id|asmlinkage
r_int
DECL|function|sys_sigaction
id|sys_sigaction
c_func
(paren
r_int
id|sig
comma
r_const
r_struct
id|old_sigaction
op_star
id|act
comma
r_struct
id|old_sigaction
op_star
id|oact
)paren
(brace
r_struct
id|k_sigaction
id|new_ka
comma
id|old_ka
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|act
)paren
(brace
id|old_sigset_t
id|mask
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|act
comma
r_sizeof
(paren
op_star
id|act
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|new_ka.sa.sa_handler
comma
op_amp
id|act-&gt;sa_handler
)paren
op_logical_or
id|__get_user
c_func
(paren
id|new_ka.sa.sa_restorer
comma
op_amp
id|act-&gt;sa_restorer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__get_user
c_func
(paren
id|new_ka.sa.sa_flags
comma
op_amp
id|act-&gt;sa_flags
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|mask
comma
op_amp
id|act-&gt;sa_mask
)paren
suffix:semicolon
id|siginitset
c_func
(paren
op_amp
id|new_ka.sa.sa_mask
comma
id|mask
)paren
suffix:semicolon
)brace
id|ret
op_assign
id|do_sigaction
c_func
(paren
id|sig
comma
id|act
ques
c_cond
op_amp
id|new_ka
suffix:colon
l_int|NULL
comma
id|oact
ques
c_cond
op_amp
id|old_ka
suffix:colon
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret
op_logical_and
id|oact
)paren
(brace
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|oact
comma
r_sizeof
(paren
op_star
id|oact
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
id|old_ka.sa.sa_handler
comma
op_amp
id|oact-&gt;sa_handler
)paren
op_logical_or
id|__put_user
c_func
(paren
id|old_ka.sa.sa_restorer
comma
op_amp
id|oact-&gt;sa_restorer
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|__put_user
c_func
(paren
id|old_ka.sa.sa_flags
comma
op_amp
id|oact-&gt;sa_flags
)paren
suffix:semicolon
id|__put_user
c_func
(paren
id|old_ka.sa.sa_mask.sig
(braket
l_int|0
)braket
comma
op_amp
id|oact-&gt;sa_mask
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
id|asmlinkage
r_int
DECL|function|sys_sigaltstack
id|sys_sigaltstack
c_func
(paren
r_const
id|stack_t
op_star
id|uss
comma
id|stack_t
op_star
id|uoss
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
id|do_sigaltstack
c_func
(paren
id|uss
comma
id|uoss
comma
id|regs-&gt;gprs
(braket
l_int|15
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns non-zero on fault. */
DECL|function|save_sigregs
r_static
r_int
id|save_sigregs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|_sigregs
op_star
id|sregs
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sregs-&gt;regs
comma
id|regs
comma
r_sizeof
(paren
id|_s390_regs_common
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* &n;&t; * We have to store the fp registers to current-&gt;thread.fp_regs&n;&t; * to merge them with the emulated registers.&n;&t; */
id|save_fp_regs
c_func
(paren
op_amp
id|current-&gt;thread.fp_regs
)paren
suffix:semicolon
r_return
id|__copy_to_user
c_func
(paren
op_amp
id|sregs-&gt;fpregs
comma
op_amp
id|current-&gt;thread.fp_regs
comma
r_sizeof
(paren
id|s390_fp_regs
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Returns positive number on error */
DECL|function|restore_sigregs
r_static
r_int
id|restore_sigregs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|_sigregs
op_star
id|sregs
)paren
(brace
r_int
id|err
suffix:semicolon
id|err
op_assign
id|__copy_from_user
c_func
(paren
id|regs
comma
op_amp
id|sregs-&gt;regs
comma
r_sizeof
(paren
id|_s390_regs_common
)paren
)paren
suffix:semicolon
id|regs-&gt;psw.mask
op_assign
id|PSW_USER_BITS
op_or
(paren
id|regs-&gt;psw.mask
op_amp
id|PSW_MASK_CC
)paren
suffix:semicolon
id|regs-&gt;psw.addr
op_or_assign
id|PSW_ADDR_AMODE
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|err
op_assign
id|__copy_from_user
c_func
(paren
op_amp
id|current-&gt;thread.fp_regs
comma
op_amp
id|sregs-&gt;fpregs
comma
r_sizeof
(paren
id|s390_fp_regs
)paren
)paren
suffix:semicolon
id|current-&gt;thread.fp_regs.fpc
op_and_assign
id|FPC_VALID_MASK
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
id|restore_fp_regs
c_func
(paren
op_amp
id|current-&gt;thread.fp_regs
)paren
suffix:semicolon
id|regs-&gt;trap
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* disable syscall checks */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_sigreturn
id|asmlinkage
r_int
id|sys_sigreturn
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|sigframe
op_star
id|frame
op_assign
(paren
id|sigframe
op_star
)paren
id|regs-&gt;gprs
(braket
l_int|15
)braket
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|frame
comma
r_sizeof
(paren
op_star
id|frame
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
op_amp
id|set.sig
comma
op_amp
id|frame-&gt;sc.oldmask
comma
id|_SIGMASK_COPY_SIZE
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|set
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
id|current-&gt;blocked
op_assign
id|set
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
r_if
c_cond
(paren
id|restore_sigregs
c_func
(paren
id|regs
comma
op_amp
id|frame-&gt;sregs
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_return
id|regs-&gt;gprs
(braket
l_int|2
)braket
suffix:semicolon
id|badframe
suffix:colon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_rt_sigreturn
id|asmlinkage
r_int
id|sys_rt_sigreturn
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|rt_sigframe
op_star
id|frame
op_assign
(paren
id|rt_sigframe
op_star
)paren
id|regs-&gt;gprs
(braket
l_int|15
)braket
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|frame
comma
r_sizeof
(paren
op_star
id|frame
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
op_amp
id|set.sig
comma
op_amp
id|frame-&gt;uc.uc_sigmask
comma
r_sizeof
(paren
id|set
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|sigdelsetmask
c_func
(paren
op_amp
id|set
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
id|current-&gt;blocked
op_assign
id|set
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
r_if
c_cond
(paren
id|restore_sigregs
c_func
(paren
id|regs
comma
op_amp
id|frame-&gt;uc.uc_mcontext
)paren
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/* It is more difficult to avoid calling this function than to&n;&t;   call it and ignore errors.  */
id|do_sigaltstack
c_func
(paren
op_amp
id|frame-&gt;uc.uc_stack
comma
l_int|NULL
comma
id|regs-&gt;gprs
(braket
l_int|15
)braket
)paren
suffix:semicolon
r_return
id|regs-&gt;gprs
(braket
l_int|2
)braket
suffix:semicolon
id|badframe
suffix:colon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up a signal frame.&n; */
multiline_comment|/*&n; * Determine which stack to use..&n; */
r_static
r_inline
r_void
op_star
DECL|function|get_sigframe
id|get_sigframe
c_func
(paren
r_struct
id|k_sigaction
op_star
id|ka
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|frame_size
)paren
(brace
r_int
r_int
id|sp
suffix:semicolon
multiline_comment|/* Default to using normal stack */
id|sp
op_assign
id|regs-&gt;gprs
(braket
l_int|15
)braket
suffix:semicolon
multiline_comment|/* This is the X/Open sanctioned signal stack switching.  */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_ONSTACK
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|on_sig_stack
c_func
(paren
id|sp
)paren
)paren
id|sp
op_assign
id|current-&gt;sas_ss_sp
op_plus
id|current-&gt;sas_ss_size
suffix:semicolon
)brace
multiline_comment|/* This is the legacy signal stack switching. */
r_else
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
op_logical_and
op_logical_neg
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
op_logical_and
id|ka-&gt;sa.sa_restorer
)paren
(brace
id|sp
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_restorer
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
(paren
(paren
id|sp
op_minus
id|frame_size
)paren
op_amp
op_minus
l_int|8ul
)paren
suffix:semicolon
)brace
DECL|function|map_signal
r_static
r_inline
r_int
id|map_signal
c_func
(paren
r_int
id|sig
)paren
(brace
r_if
c_cond
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain
op_logical_and
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain-&gt;signal_invmap
op_logical_and
id|sig
OL
l_int|32
)paren
r_return
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain-&gt;signal_invmap
(braket
id|sig
)braket
suffix:semicolon
r_else
r_return
id|sig
suffix:semicolon
)brace
DECL|function|setup_frame
r_static
r_void
id|setup_frame
c_func
(paren
r_int
id|sig
comma
r_struct
id|k_sigaction
op_star
id|ka
comma
id|sigset_t
op_star
id|set
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|sigframe
op_star
id|frame
op_assign
id|get_sigframe
c_func
(paren
id|ka
comma
id|regs
comma
r_sizeof
(paren
id|sigframe
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|frame
comma
r_sizeof
(paren
id|sigframe
)paren
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;sc.oldmask
comma
op_amp
id|set-&gt;sig
comma
id|_SIGMASK_COPY_SIZE
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
r_if
c_cond
(paren
id|save_sigregs
c_func
(paren
id|regs
comma
op_amp
id|frame-&gt;sregs
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
c_func
(paren
op_amp
id|frame-&gt;sregs
comma
op_amp
id|frame-&gt;sc.sregs
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
multiline_comment|/* Set up to return from userspace.  If provided, use a stub&n;&t;   already in userspace.  */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
(brace
id|regs-&gt;gprs
(braket
l_int|14
)braket
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_restorer
op_or
id|PSW_ADDR_AMODE
suffix:semicolon
)brace
r_else
(brace
id|regs-&gt;gprs
(braket
l_int|14
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;retcode
op_or
id|PSW_ADDR_AMODE
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|S390_SYSCALL_OPCODE
op_or
id|__NR_sigreturn
comma
(paren
id|u16
op_star
)paren
(paren
id|frame-&gt;retcode
)paren
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
)brace
multiline_comment|/* Set up backchain. */
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|regs-&gt;gprs
(braket
l_int|15
)braket
comma
(paren
id|addr_t
op_star
)paren
id|frame
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
multiline_comment|/* Set up registers for signal handler */
id|regs-&gt;gprs
(braket
l_int|15
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|regs-&gt;psw.addr
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
op_or
id|PSW_ADDR_AMODE
suffix:semicolon
id|regs-&gt;psw.mask
op_assign
id|PSW_USER_BITS
suffix:semicolon
id|regs-&gt;gprs
(braket
l_int|2
)braket
op_assign
id|map_signal
c_func
(paren
id|sig
)paren
suffix:semicolon
id|regs-&gt;gprs
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;sc
suffix:semicolon
multiline_comment|/* We forgot to include these in the sigcontext.&n;&t;   To avoid breaking binary compatibility, they are passed as args. */
id|regs-&gt;gprs
(braket
l_int|4
)braket
op_assign
id|current-&gt;thread.trap_no
suffix:semicolon
id|regs-&gt;gprs
(braket
l_int|5
)braket
op_assign
id|current-&gt;thread.prot_addr
suffix:semicolon
r_return
suffix:semicolon
id|give_sigsegv
suffix:colon
r_if
c_cond
(paren
id|sig
op_eq
id|SIGSEGV
)paren
id|ka-&gt;sa.sa_handler
op_assign
id|SIG_DFL
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|setup_rt_frame
r_static
r_void
id|setup_rt_frame
c_func
(paren
r_int
id|sig
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
id|set
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
id|rt_sigframe
op_star
id|frame
op_assign
id|get_sigframe
c_func
(paren
id|ka
comma
id|regs
comma
r_sizeof
(paren
id|rt_sigframe
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_WRITE
comma
id|frame
comma
r_sizeof
(paren
id|rt_sigframe
)paren
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
r_if
c_cond
(paren
id|copy_siginfo_to_user
c_func
(paren
op_amp
id|frame-&gt;info
comma
id|info
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
multiline_comment|/* Create the ucontext.  */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|frame-&gt;uc.uc_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|frame-&gt;uc.uc_link
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
r_void
op_star
)paren
id|current-&gt;sas_ss_sp
comma
op_amp
id|frame-&gt;uc.uc_stack.ss_sp
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|sas_ss_flags
c_func
(paren
id|regs-&gt;gprs
(braket
l_int|15
)braket
)paren
comma
op_amp
id|frame-&gt;uc.uc_stack.ss_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;sas_ss_size
comma
op_amp
id|frame-&gt;uc.uc_stack.ss_size
)paren
suffix:semicolon
id|err
op_or_assign
id|save_sigregs
c_func
(paren
id|regs
comma
op_amp
id|frame-&gt;uc.uc_mcontext
)paren
suffix:semicolon
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;uc.uc_sigmask
comma
id|set
comma
r_sizeof
(paren
op_star
id|set
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|give_sigsegv
suffix:semicolon
multiline_comment|/* Set up to return from userspace.  If provided, use a stub&n;&t;   already in userspace.  */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
(brace
id|regs-&gt;gprs
(braket
l_int|14
)braket
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_restorer
op_or
id|PSW_ADDR_AMODE
suffix:semicolon
)brace
r_else
(brace
id|regs-&gt;gprs
(braket
l_int|14
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;retcode
op_or
id|PSW_ADDR_AMODE
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|S390_SYSCALL_OPCODE
op_or
id|__NR_rt_sigreturn
comma
(paren
id|u16
op_star
)paren
(paren
id|frame-&gt;retcode
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Set up backchain. */
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|regs-&gt;gprs
(braket
l_int|15
)braket
comma
(paren
id|addr_t
op_star
)paren
id|frame
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
multiline_comment|/* Set up registers for signal handler */
id|regs-&gt;gprs
(braket
l_int|15
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|regs-&gt;psw.addr
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
op_or
id|PSW_ADDR_AMODE
suffix:semicolon
id|regs-&gt;psw.mask
op_assign
id|PSW_USER_BITS
suffix:semicolon
id|regs-&gt;gprs
(braket
l_int|2
)braket
op_assign
id|map_signal
c_func
(paren
id|sig
)paren
suffix:semicolon
id|regs-&gt;gprs
(braket
l_int|3
)braket
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;info
suffix:semicolon
id|regs-&gt;gprs
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;uc
suffix:semicolon
r_return
suffix:semicolon
id|give_sigsegv
suffix:colon
r_if
c_cond
(paren
id|sig
op_eq
id|SIGSEGV
)paren
id|ka-&gt;sa.sa_handler
op_assign
id|SIG_DFL
suffix:semicolon
id|force_sig
c_func
(paren
id|SIGSEGV
comma
id|current
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * OK, we&squot;re invoking a handler&n; */
r_static
r_void
DECL|function|handle_signal
id|handle_signal
c_func
(paren
r_int
r_int
id|sig
comma
id|siginfo_t
op_star
id|info
comma
id|sigset_t
op_star
id|oldset
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|k_sigaction
op_star
id|ka
op_assign
op_amp
id|current-&gt;sighand-&gt;action
(braket
id|sig
op_minus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Are we from a system call? */
r_if
c_cond
(paren
id|regs-&gt;trap
op_eq
id|__LC_SVC_OLD_PSW
)paren
(brace
multiline_comment|/* If so, check system call restarting.. */
r_switch
c_cond
(paren
id|regs-&gt;gprs
(braket
l_int|2
)braket
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
id|clear_thread_flag
c_func
(paren
id|TIF_RESTART_SVC
)paren
suffix:semicolon
r_case
op_minus
id|ERESTARTNOHAND
suffix:colon
id|regs-&gt;gprs
(braket
l_int|2
)braket
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
id|regs-&gt;gprs
(braket
l_int|2
)braket
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
id|regs-&gt;gprs
(braket
l_int|2
)braket
op_assign
id|regs-&gt;orig_gpr2
suffix:semicolon
id|regs-&gt;psw.addr
op_sub_assign
id|regs-&gt;ilc
suffix:semicolon
)brace
)brace
multiline_comment|/* Set up the stack frame */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_SIGINFO
)paren
id|setup_rt_frame
c_func
(paren
id|sig
comma
id|ka
comma
id|info
comma
id|oldset
comma
id|regs
)paren
suffix:semicolon
r_else
id|setup_frame
c_func
(paren
id|sig
comma
id|ka
comma
id|oldset
comma
id|regs
)paren
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
id|sig
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
)brace
multiline_comment|/*&n; * Note that &squot;init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t&n; * want to handle. Thus you cannot kill init even with a SIGKILL even by&n; * mistake.&n; *&n; * Note that we go through the signals twice: once to check the signals that&n; * the kernel can handle, and then we build all the user-level signal handling&n; * stack-frames in one go after that.&n; */
DECL|function|do_signal
r_int
id|do_signal
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
)paren
(brace
id|siginfo_t
id|info
suffix:semicolon
r_int
id|signr
suffix:semicolon
multiline_comment|/*&n;&t; * We want the common case to go fast, which&n;&t; * is why we may in certain cases get here from&n;&t; * kernel mode. Just return without doing anything&n;&t; * if so.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_return
l_int|1
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
macro_line|#ifdef CONFIG_S390_SUPPORT 
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_31BIT
)paren
)paren
(brace
r_extern
id|asmlinkage
r_int
id|do_signal32
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
)paren
suffix:semicolon
r_return
id|do_signal32
c_func
(paren
id|regs
comma
id|oldset
)paren
suffix:semicolon
)brace
macro_line|#endif 
id|signr
op_assign
id|get_signal_to_deliver
c_func
(paren
op_amp
id|info
comma
id|regs
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|signr
OG
l_int|0
)paren
(brace
multiline_comment|/* Whee!  Actually deliver the signal.  */
id|handle_signal
c_func
(paren
id|signr
comma
op_amp
id|info
comma
id|oldset
comma
id|regs
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Did we come from a system call? */
r_if
c_cond
(paren
id|regs-&gt;trap
op_eq
id|__LC_SVC_OLD_PSW
multiline_comment|/* System Call! */
)paren
(brace
multiline_comment|/* Restart the system call - no handlers present */
r_if
c_cond
(paren
id|regs-&gt;gprs
(braket
l_int|2
)braket
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;gprs
(braket
l_int|2
)braket
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|regs-&gt;gprs
(braket
l_int|2
)braket
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|regs-&gt;gprs
(braket
l_int|2
)braket
op_assign
id|regs-&gt;orig_gpr2
suffix:semicolon
id|regs-&gt;psw.addr
op_sub_assign
id|regs-&gt;ilc
suffix:semicolon
)brace
multiline_comment|/* Restart the system call with a new system call number */
r_if
c_cond
(paren
id|regs-&gt;gprs
(braket
l_int|2
)braket
op_eq
op_minus
id|ERESTART_RESTARTBLOCK
)paren
(brace
id|regs-&gt;gprs
(braket
l_int|2
)braket
op_assign
id|__NR_restart_syscall
suffix:semicolon
id|set_thread_flag
c_func
(paren
id|TIF_RESTART_SVC
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
