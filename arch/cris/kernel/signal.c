multiline_comment|/*&n; *  linux/arch/cris/kernel/signal.c&n; *&n; *  Based on arch/i386/kernel/signal.c by&n; *     Copyright (C) 1991, 1992  Linus Torvalds&n; *     1997-11-28  Modified for POSIX.1b signals by Richard Henderson *&n; *&n; *  Ideas also taken from arch/arm.&n; *&n; *  Copyright (C) 2000 Axis Communications AB&n; *&n; *  Authors:  Bjorn Wesen (bjornw@axis.com)&n; *&n; */
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
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|macro|DEBUG_SIG
mdefine_line|#define DEBUG_SIG 0
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
multiline_comment|/* a syscall in Linux/CRIS is a break 13 instruction which is 2 bytes */
multiline_comment|/* manipulate regs so that upon return, it will be re-executed */
DECL|macro|RESTART_CRIS_SYS
mdefine_line|#define RESTART_CRIS_SYS(regs) regs-&gt;r10 = regs-&gt;orig_r10; regs-&gt;irp -= 2;
r_int
id|do_signal
c_func
(paren
r_int
id|canrestart
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
suffix:semicolon
DECL|function|copy_siginfo_to_user
r_int
id|copy_siginfo_to_user
c_func
(paren
id|siginfo_t
op_star
id|to
comma
id|siginfo_t
op_star
id|from
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|access_ok
(paren
id|VERIFY_WRITE
comma
id|to
comma
r_sizeof
(paren
id|siginfo_t
)paren
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|from-&gt;si_code
OL
l_int|0
)paren
r_return
id|__copy_to_user
c_func
(paren
id|to
comma
id|from
comma
r_sizeof
(paren
id|siginfo_t
)paren
)paren
suffix:semicolon
r_else
(brace
r_int
id|err
suffix:semicolon
multiline_comment|/* If you change siginfo_t structure, please be sure&n;&t;&t;   this code is fixed accordingly.&n;&t;&t;   It should never copy any pad contained in the structure&n;&t;&t;   to avoid security leaks, but must copy the generic&n;&t;&t;   3 ints plus the relevant union member.  */
id|err
op_assign
id|__put_user
c_func
(paren
id|from-&gt;si_signo
comma
op_amp
id|to-&gt;si_signo
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_errno
comma
op_amp
id|to-&gt;si_errno
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
(paren
r_int
)paren
id|from-&gt;si_code
comma
op_amp
id|to-&gt;si_code
)paren
suffix:semicolon
multiline_comment|/* First 32bits of unions are always present.  */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_pid
comma
op_amp
id|to-&gt;si_pid
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|from-&gt;si_code
op_rshift
l_int|16
)paren
(brace
r_case
id|__SI_FAULT
op_rshift
l_int|16
suffix:colon
r_break
suffix:semicolon
r_case
id|__SI_CHLD
op_rshift
l_int|16
suffix:colon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_utime
comma
op_amp
id|to-&gt;si_utime
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_stime
comma
op_amp
id|to-&gt;si_stime
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_status
comma
op_amp
id|to-&gt;si_status
)paren
suffix:semicolon
r_default
suffix:colon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_uid
comma
op_amp
id|to-&gt;si_uid
)paren
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/* case __SI_RT: This is not generated by the kernel as of now.  */
)brace
r_return
id|err
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Atomically swap in the new signal mask, and wait for a signal.&n; */
r_int
DECL|function|sys_sigsuspend
id|sys_sigsuspend
c_func
(paren
id|old_sigset_t
id|mask
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|current_regs
c_func
(paren
)paren
suffix:semicolon
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
id|current-&gt;sigmask_lock
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
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|regs-&gt;r10
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
id|do_signal
c_func
(paren
l_int|0
comma
op_amp
id|saveset
comma
id|regs
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
r_int
DECL|function|sys_rt_sigsuspend
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
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|current_regs
c_func
(paren
)paren
suffix:semicolon
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
id|current-&gt;sigmask_lock
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
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|regs-&gt;r10
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
id|do_signal
c_func
(paren
l_int|0
comma
op_amp
id|saveset
comma
id|regs
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
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
id|rdusp
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do a signal return; undo the signal stack.&n; */
DECL|struct|sigframe
r_struct
id|sigframe
(brace
DECL|member|sc
r_struct
id|sigcontext
id|sc
suffix:semicolon
DECL|member|extramask
r_int
r_int
id|extramask
(braket
id|_NSIG_WORDS
op_minus
l_int|1
)braket
suffix:semicolon
DECL|member|retcode
r_int
r_char
id|retcode
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* trampoline code */
)brace
suffix:semicolon
DECL|struct|rt_sigframe
r_struct
id|rt_sigframe
(brace
DECL|member|pinfo
r_struct
id|siginfo
op_star
id|pinfo
suffix:semicolon
DECL|member|puc
r_void
op_star
id|puc
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
DECL|member|retcode
r_int
r_char
id|retcode
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* trampoline code */
)brace
suffix:semicolon
r_static
r_int
DECL|function|restore_sigcontext
id|restore_sigcontext
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|sigcontext
op_star
id|sc
)paren
(brace
r_int
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|old_usp
suffix:semicolon
multiline_comment|/* restore the regs from &amp;sc-&gt;regs (same as sc, since regs is first)&n;&t; * (sc is already checked for VERIFY_READ since the sigframe was&n;&t; *  checked in sys_sigreturn previously)&n;&t; */
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|regs
comma
id|sc
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/* make sure the U-flag is set so user-mode cannot fool us */
id|regs-&gt;dccr
op_or_assign
l_int|1
op_lshift
l_int|8
suffix:semicolon
multiline_comment|/* restore the old USP as it was before we stacked the sc etc.&n;&t; * (we cannot just pop the sigcontext since we aligned the sp and&n;&t; *  stuff after pushing it)&n;&t; */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|old_usp
comma
op_amp
id|sc-&gt;usp
)paren
suffix:semicolon
id|wrusp
c_func
(paren
id|old_usp
)paren
suffix:semicolon
multiline_comment|/* TODO: the other ports use regs-&gt;orig_XX to disable syscall checks&n;&t; * after this completes, but we don&squot;t use that mechanism. maybe we can&n;&t; * use it now ? &n;&t; */
r_return
id|err
suffix:semicolon
id|badframe
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|sys_sigreturn
id|asmlinkage
r_int
id|sys_sigreturn
c_func
(paren
r_void
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|current_regs
c_func
(paren
)paren
suffix:semicolon
r_struct
id|sigframe
op_star
id|frame
op_assign
(paren
r_struct
id|sigframe
op_star
)paren
id|rdusp
c_func
(paren
)paren
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
multiline_comment|/*&n;         * Since we stacked the signal on a dword boundary,&n;         * then frame should be dword aligned here.  If it&squot;s&n;         * not, then the user is trying to mess with us.&n;         */
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|frame
)paren
op_amp
l_int|3
)paren
r_goto
id|badframe
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
id|__get_user
c_func
(paren
id|set.sig
(braket
l_int|0
)braket
comma
op_amp
id|frame-&gt;sc.oldmask
)paren
op_logical_or
(paren
id|_NSIG_WORDS
OG
l_int|1
op_logical_and
id|__copy_from_user
c_func
(paren
op_amp
id|set.sig
(braket
l_int|1
)braket
comma
op_amp
id|frame-&gt;extramask
comma
r_sizeof
(paren
id|frame-&gt;extramask
)paren
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
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|set
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|restore_sigcontext
c_func
(paren
id|regs
comma
op_amp
id|frame-&gt;sc
)paren
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/* TODO: SIGTRAP when single-stepping as in arm ? */
r_return
id|regs-&gt;r10
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
r_void
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|current_regs
c_func
(paren
)paren
suffix:semicolon
r_struct
id|rt_sigframe
op_star
id|frame
op_assign
(paren
r_struct
id|rt_sigframe
op_star
)paren
id|rdusp
c_func
(paren
)paren
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
id|stack_t
id|st
suffix:semicolon
multiline_comment|/*&n;         * Since we stacked the signal on a dword boundary,&n;         * then frame should be dword aligned here.  If it&squot;s&n;         * not, then the user is trying to mess with us.&n;         */
r_if
c_cond
(paren
(paren
(paren
r_int
)paren
id|frame
)paren
op_amp
l_int|3
)paren
r_goto
id|badframe
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
id|set
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
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|current-&gt;blocked
op_assign
id|set
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|restore_sigcontext
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
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
op_amp
id|st
comma
op_amp
id|frame-&gt;uc.uc_stack
comma
r_sizeof
(paren
id|st
)paren
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
id|st
comma
l_int|NULL
comma
id|rdusp
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
id|regs-&gt;r10
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
r_static
r_int
DECL|function|setup_sigcontext
id|setup_sigcontext
c_func
(paren
r_struct
id|sigcontext
op_star
id|sc
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|mask
)paren
(brace
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|usp
op_assign
id|rdusp
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* copy the regs. they are first in sc so we can use sc directly */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
id|sc
comma
id|regs
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
)paren
suffix:semicolon
multiline_comment|/* then some other stuff */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|mask
comma
op_amp
id|sc-&gt;oldmask
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|usp
comma
op_amp
id|sc-&gt;usp
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/* figure out where we want to put the new signal frame - usually on the stack */
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
op_assign
id|rdusp
c_func
(paren
)paren
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
multiline_comment|/* make sure the frame is dword-aligned */
id|sp
op_and_assign
op_complement
l_int|3
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
(paren
id|sp
op_minus
id|frame_size
)paren
suffix:semicolon
)brace
multiline_comment|/* grab and setup a signal frame.&n; * &n; * basically we stack a lot of state info, and arrange for the&n; * user-mode program to return to the kernel using either a&n; * trampoline which performs the syscall sigreturn, or a provided&n; * user-mode trampoline.&n; */
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
r_struct
id|sigframe
op_star
id|frame
suffix:semicolon
r_int
r_int
id|return_ip
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
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
op_star
id|frame
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
op_star
id|frame
)paren
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
id|err
op_or_assign
id|setup_sigcontext
c_func
(paren
op_amp
id|frame-&gt;sc
comma
id|regs
comma
id|set-&gt;sig
(braket
l_int|0
)braket
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
r_if
c_cond
(paren
id|_NSIG_WORDS
OG
l_int|1
)paren
(brace
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
id|frame-&gt;extramask
comma
op_amp
id|set-&gt;sig
(braket
l_int|1
)braket
comma
r_sizeof
(paren
id|frame-&gt;extramask
)paren
)paren
suffix:semicolon
)brace
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
id|return_ip
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_restorer
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* trampoline - the desired return ip is the retcode itself */
id|return_ip
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;retcode
suffix:semicolon
multiline_comment|/* This is movu.w __NR_sigreturn, r9; break 13; */
multiline_comment|/* TODO: check byteorder */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x9c5f
comma
(paren
r_int
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|0
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|__NR_sigreturn
comma
(paren
r_int
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|2
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0xe93d
comma
(paren
r_int
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|4
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
r_goto
id|give_sigsegv
suffix:semicolon
multiline_comment|/* Set up registers for signal handler */
id|regs-&gt;irp
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
multiline_comment|/* what we enter NOW   */
id|regs-&gt;srp
op_assign
id|return_ip
suffix:semicolon
multiline_comment|/* what we enter LATER */
multiline_comment|/* actually move the usp to reflect the stacked frame */
id|wrusp
c_func
(paren
(paren
r_int
r_int
)paren
id|frame
)paren
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
r_struct
id|rt_sigframe
op_star
id|frame
suffix:semicolon
r_int
r_int
id|return_ip
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
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
op_star
id|frame
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
op_star
id|frame
)paren
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
op_amp
id|frame-&gt;info
comma
op_amp
id|frame-&gt;pinfo
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
op_amp
id|frame-&gt;uc
comma
op_amp
id|frame-&gt;puc
)paren
suffix:semicolon
id|err
op_or_assign
id|copy_siginfo_to_user
c_func
(paren
op_amp
id|frame-&gt;info
comma
id|info
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
multiline_comment|/* Clear all the bits of the ucontext we don&squot;t use.  */
id|err
op_or_assign
id|__clear_user
c_func
(paren
op_amp
id|frame-&gt;uc
comma
m_offsetof
(paren
r_struct
id|ucontext
comma
id|uc_mcontext
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|setup_sigcontext
c_func
(paren
op_amp
id|frame-&gt;uc.uc_mcontext
comma
id|regs
comma
id|set-&gt;sig
(braket
l_int|0
)braket
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
id|return_ip
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_restorer
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* trampoline - the desired return ip is the retcode itself */
id|return_ip
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;retcode
suffix:semicolon
multiline_comment|/* This is movu.w __NR_sigreturn, r9; break 13; */
multiline_comment|/* TODO: check byteorder */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x9c5f
comma
(paren
r_int
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|0
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|__NR_sigreturn
comma
(paren
r_int
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|2
)paren
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0xe93d
comma
(paren
r_int
op_star
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|4
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
r_goto
id|give_sigsegv
suffix:semicolon
multiline_comment|/* TODO what is the current-&gt;exec_domain stuff and invmap ? */
multiline_comment|/* Set up registers for signal handler */
id|regs-&gt;irp
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
multiline_comment|/* what we enter NOW   */
id|regs-&gt;srp
op_assign
id|return_ip
suffix:semicolon
multiline_comment|/* what we enter LATER */
multiline_comment|/* actually move the usp to reflect the stacked frame */
id|wrusp
c_func
(paren
(paren
r_int
r_int
)paren
id|frame
)paren
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
r_inline
r_void
DECL|function|handle_signal
id|handle_signal
c_func
(paren
r_int
id|canrestart
comma
r_int
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
id|oldset
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* Are we from a system call? */
r_if
c_cond
(paren
id|canrestart
)paren
(brace
multiline_comment|/* If so, check system call restarting.. */
r_switch
c_cond
(paren
id|regs-&gt;r10
)paren
(brace
r_case
op_minus
id|ERESTARTNOHAND
suffix:colon
multiline_comment|/* ERESTARTNOHAND means that the syscall should only be&n;&t;&t;&t;&t;   restarted if there was no handler for the signal, and since&n;&t;&t;&t;&t;   we only get here if there is a handler, we dont restart */
id|regs-&gt;r10
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
multiline_comment|/* ERESTARTSYS means to restart the syscall if there is no&n;&t;&t;&t;&t;   handler or the handler was registered with SA_RESTART */
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
id|regs-&gt;r10
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
multiline_comment|/* ERESTARTNOINTR means that the syscall should be called again&n;&t;&t;&t;&t;   after the signal handler returns. */
id|RESTART_CRIS_SYS
c_func
(paren
id|regs
)paren
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
id|current-&gt;sigmask_lock
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
id|current
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Note that &squot;init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t&n; * want to handle. Thus you cannot kill init even with a SIGKILL even by&n; * mistake.&n; */
DECL|function|do_signal
r_int
id|do_signal
c_func
(paren
r_int
id|canrestart
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
id|siginfo_t
id|info
suffix:semicolon
r_struct
id|k_sigaction
op_star
id|ka
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
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|signr
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
id|signr
op_assign
id|dequeue_signal
c_func
(paren
op_amp
id|current-&gt;blocked
comma
op_amp
id|info
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sigmask_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|signr
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;ptrace
op_amp
id|PT_PTRACED
)paren
op_logical_and
id|signr
op_ne
id|SIGKILL
)paren
(brace
multiline_comment|/* Let the debugger run.  */
id|current-&gt;exit_code
op_assign
id|signr
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|notify_parent
c_func
(paren
id|current
comma
id|SIGCHLD
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* We&squot;re back.  Did the debugger cancel the sig?  */
r_if
c_cond
(paren
op_logical_neg
(paren
id|signr
op_assign
id|current-&gt;exit_code
)paren
)paren
r_continue
suffix:semicolon
id|current-&gt;exit_code
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* The debugger continued.  Ignore SIGSTOP.  */
r_if
c_cond
(paren
id|signr
op_eq
id|SIGSTOP
)paren
r_continue
suffix:semicolon
multiline_comment|/* Update the siginfo structure.  Is this good?  */
r_if
c_cond
(paren
id|signr
op_ne
id|info.si_signo
)paren
(brace
id|info.si_signo
op_assign
id|signr
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|SI_USER
suffix:semicolon
id|info.si_pid
op_assign
id|current-&gt;p_pptr-&gt;pid
suffix:semicolon
id|info.si_uid
op_assign
id|current-&gt;p_pptr-&gt;uid
suffix:semicolon
)brace
multiline_comment|/* If the (new) signal is now blocked, requeue it.  */
r_if
c_cond
(paren
id|sigismember
c_func
(paren
op_amp
id|current-&gt;blocked
comma
id|signr
)paren
)paren
(brace
id|send_sig_info
c_func
(paren
id|signr
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
id|ka
op_assign
op_amp
id|current-&gt;sig-&gt;action
(braket
id|signr
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ka-&gt;sa.sa_handler
op_eq
id|SIG_IGN
)paren
(brace
r_if
c_cond
(paren
id|signr
op_ne
id|SIGCHLD
)paren
r_continue
suffix:semicolon
multiline_comment|/* Check for SIGCHLD: it&squot;s special.  */
r_while
c_loop
(paren
id|sys_wait4
c_func
(paren
op_minus
l_int|1
comma
l_int|NULL
comma
id|WNOHANG
comma
l_int|NULL
)paren
OG
l_int|0
)paren
multiline_comment|/* nothing */
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ka-&gt;sa.sa_handler
op_eq
id|SIG_DFL
)paren
(brace
r_int
id|exit_code
op_assign
id|signr
suffix:semicolon
multiline_comment|/* Init gets no signals it doesn&squot;t want.  */
r_if
c_cond
(paren
id|current-&gt;pid
op_eq
l_int|1
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|signr
)paren
(brace
r_case
id|SIGCONT
suffix:colon
r_case
id|SIGCHLD
suffix:colon
r_case
id|SIGWINCH
suffix:colon
r_continue
suffix:semicolon
r_case
id|SIGTSTP
suffix:colon
r_case
id|SIGTTIN
suffix:colon
r_case
id|SIGTTOU
suffix:colon
r_if
c_cond
(paren
id|is_orphaned_pgrp
c_func
(paren
id|current-&gt;pgrp
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* FALLTHRU */
r_case
id|SIGSTOP
suffix:colon
id|current-&gt;state
op_assign
id|TASK_STOPPED
suffix:semicolon
id|current-&gt;exit_code
op_assign
id|signr
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|current-&gt;p_pptr-&gt;sig-&gt;action
(braket
id|SIGCHLD
op_minus
l_int|1
)braket
dot
id|sa.sa_flags
op_amp
id|SA_NOCLDSTOP
)paren
)paren
id|notify_parent
c_func
(paren
id|current
comma
id|SIGCHLD
)paren
suffix:semicolon
id|schedule
c_func
(paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
r_case
id|SIGQUIT
suffix:colon
r_case
id|SIGILL
suffix:colon
r_case
id|SIGTRAP
suffix:colon
r_case
id|SIGABRT
suffix:colon
r_case
id|SIGFPE
suffix:colon
r_case
id|SIGSEGV
suffix:colon
r_case
id|SIGBUS
suffix:colon
r_case
id|SIGSYS
suffix:colon
r_case
id|SIGXCPU
suffix:colon
r_case
id|SIGXFSZ
suffix:colon
r_if
c_cond
(paren
id|do_coredump
c_func
(paren
id|signr
comma
id|regs
)paren
)paren
id|exit_code
op_or_assign
l_int|0x80
suffix:semicolon
multiline_comment|/* FALLTHRU */
r_default
suffix:colon
id|lock_kernel
c_func
(paren
)paren
suffix:semicolon
id|sigaddset
c_func
(paren
op_amp
id|current-&gt;pending.signal
comma
id|signr
)paren
suffix:semicolon
id|recalc_sigpending
c_func
(paren
id|current
)paren
suffix:semicolon
id|current-&gt;flags
op_or_assign
id|PF_SIGNALED
suffix:semicolon
id|do_exit
c_func
(paren
id|exit_code
)paren
suffix:semicolon
multiline_comment|/* NOTREACHED */
)brace
)brace
multiline_comment|/* Whee!  Actually deliver the signal.  */
id|handle_signal
c_func
(paren
id|canrestart
comma
id|signr
comma
id|ka
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
id|canrestart
)paren
(brace
multiline_comment|/* Restart the system call - no handlers present */
r_if
c_cond
(paren
id|regs-&gt;r10
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;r10
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|regs-&gt;r10
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|RESTART_CRIS_SYS
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
