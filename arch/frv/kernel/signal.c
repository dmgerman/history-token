multiline_comment|/*&n; *  linux/arch/frvnommu/kernel/signal.c&n; *&n; *  Copyright (C) 1991, 1992  Linus Torvalds&n; *&n; *  1997-11-28  Modified for POSIX.1b signals by Richard Henderson&n; *  2000-06-20  Pentium III FXSR, SSE support by Gareth Hughes&n; */
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
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
DECL|macro|DEBUG_SIG
mdefine_line|#define DEBUG_SIG 0
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
DECL|struct|fdpic_func_descriptor
r_struct
id|fdpic_func_descriptor
(brace
DECL|member|text
r_int
r_int
id|text
suffix:semicolon
DECL|member|GOT
r_int
r_int
id|GOT
suffix:semicolon
)brace
suffix:semicolon
id|asmlinkage
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
DECL|function|sys_sigsuspend
id|asmlinkage
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
id|__frame-&gt;gr8
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
id|__frame
comma
op_amp
id|saveset
)paren
)paren
multiline_comment|/* return the signal number as the return value of this function&n;&t;&t;&t; * - this is an utterly evil hack. syscalls should not invoke do_signal()&n;&t;&t;&t; *   as entry.S sets regs-&gt;gr8 to the return value of the system call&n;&t;&t;&t; * - we can&squot;t just use sigpending() as we&squot;d have to discard SIG_IGN signals&n;&t;&t;&t; *   and call waitpid() if SIGCHLD needed discarding&n;&t;&t;&t; * - this only works on the i386 because it passes arguments to the signal&n;&t;&t;&t; *   handler on the stack, and the return value in EAX is effectively&n;&t;&t;&t; *   discarded&n;&t;&t;&t; */
r_return
id|__frame-&gt;gr8
suffix:semicolon
)brace
)brace
DECL|function|sys_rt_sigsuspend
id|asmlinkage
r_int
id|sys_rt_sigsuspend
c_func
(paren
id|sigset_t
id|__user
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
id|__frame-&gt;gr8
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
id|__frame
comma
op_amp
id|saveset
)paren
)paren
multiline_comment|/* return the signal number as the return value of this function&n;&t;&t;&t; * - this is an utterly evil hack. syscalls should not invoke do_signal()&n;&t;&t;&t; *   as entry.S sets regs-&gt;gr8 to the return value of the system call&n;&t;&t;&t; * - we can&squot;t just use sigpending() as we&squot;d have to discard SIG_IGN signals&n;&t;&t;&t; *   and call waitpid() if SIGCHLD needed discarding&n;&t;&t;&t; * - this only works on the i386 because it passes arguments to the signal&n;&t;&t;&t; *   handler on the stack, and the return value in EAX is effectively&n;&t;&t;&t; *   discarded&n;&t;&t;&t; */
r_return
id|__frame-&gt;gr8
suffix:semicolon
)brace
)brace
DECL|function|sys_sigaction
id|asmlinkage
r_int
id|sys_sigaction
c_func
(paren
r_int
id|sig
comma
r_const
r_struct
id|old_sigaction
id|__user
op_star
id|act
comma
r_struct
id|old_sigaction
id|__user
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
DECL|function|sys_sigaltstack
r_int
id|sys_sigaltstack
c_func
(paren
r_const
id|stack_t
id|__user
op_star
id|uss
comma
id|stack_t
id|__user
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
id|__frame-&gt;sp
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do a signal return; undo the signal stack.&n; */
DECL|struct|sigframe
r_struct
id|sigframe
(brace
DECL|member|pretcode
r_void
(paren
op_star
id|pretcode
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|sig
r_int
id|sig
suffix:semicolon
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
r_uint32
id|retcode
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rt_sigframe
r_struct
id|rt_sigframe
(brace
DECL|member|pretcode
r_void
(paren
op_star
id|pretcode
)paren
(paren
r_void
)paren
suffix:semicolon
DECL|member|sig
r_int
id|sig
suffix:semicolon
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
r_uint32
id|retcode
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|function|restore_sigcontext
r_static
r_int
id|restore_sigcontext
c_func
(paren
r_struct
id|sigcontext
id|__user
op_star
id|sc
comma
r_int
op_star
id|_gr8
)paren
(brace
r_struct
id|user_context
op_star
id|user
op_assign
id|current-&gt;thread.user
suffix:semicolon
r_int
r_int
id|tbr
comma
id|psr
suffix:semicolon
id|tbr
op_assign
id|user-&gt;i.tbr
suffix:semicolon
id|psr
op_assign
id|user-&gt;i.psr
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|user
comma
op_amp
id|sc-&gt;sc_context
comma
r_sizeof
(paren
id|sc-&gt;sc_context
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|user-&gt;i.tbr
op_assign
id|tbr
suffix:semicolon
id|user-&gt;i.psr
op_assign
id|psr
suffix:semicolon
id|restore_user_regs
c_func
(paren
id|user
)paren
suffix:semicolon
id|user-&gt;i.syscallno
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* disable syscall checks */
op_star
id|_gr8
op_assign
id|user-&gt;i.gr
(braket
l_int|8
)braket
suffix:semicolon
r_return
l_int|0
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
id|sigframe
id|__user
op_star
id|frame
op_assign
(paren
r_struct
id|sigframe
id|__user
op_star
)paren
id|__frame-&gt;sp
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
r_int
id|gr8
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
id|frame-&gt;sc.sc_oldmask
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_if
c_cond
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
id|restore_sigcontext
c_func
(paren
op_amp
id|frame-&gt;sc
comma
op_amp
id|gr8
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_return
id|gr8
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
id|rt_sigframe
id|__user
op_star
id|frame
op_assign
(paren
r_struct
id|rt_sigframe
id|__user
op_star
)paren
id|__frame-&gt;sp
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
id|stack_t
id|st
suffix:semicolon
r_int
id|gr8
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
id|restore_sigcontext
c_func
(paren
op_amp
id|frame-&gt;uc.uc_mcontext
comma
op_amp
id|gr8
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
multiline_comment|/* It is more difficult to avoid calling this function than to&n;&t; * call it and ignore errors.  */
multiline_comment|/*&n;&t; * THIS CANNOT WORK! &quot;&amp;st&quot; is a kernel address, and &quot;do_sigaltstack()&quot;&n;&t; * takes a user address (and verifies that it is a user address). End&n;&t; * result: it does exactly _nothing_.&n;&t; */
id|do_sigaltstack
c_func
(paren
op_amp
id|st
comma
l_int|NULL
comma
id|__frame-&gt;sp
)paren
suffix:semicolon
r_return
id|gr8
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
multiline_comment|/*&n; * Set up a signal frame&n; */
DECL|function|setup_sigcontext
r_static
r_int
id|setup_sigcontext
c_func
(paren
r_struct
id|sigcontext
id|__user
op_star
id|sc
comma
r_int
r_int
id|mask
)paren
(brace
id|save_user_regs
c_func
(paren
id|current-&gt;thread.user
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_context
comma
id|current-&gt;thread.user
comma
r_sizeof
(paren
id|sc-&gt;sc_context
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/* non-iBCS2 extensions.. */
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|mask
comma
op_amp
id|sc-&gt;sc_oldmask
)paren
OL
l_int|0
)paren
r_goto
id|badframe
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|badframe
suffix:colon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Determine which stack to use..&n; */
DECL|function|get_sigframe
r_static
r_inline
r_void
id|__user
op_star
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
id|regs-&gt;sp
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
r_return
(paren
r_void
id|__user
op_star
)paren
(paren
(paren
id|sp
op_minus
id|frame_size
)paren
op_amp
op_complement
l_int|7UL
)paren
suffix:semicolon
)brace
multiline_comment|/* end get_sigframe() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&n; */
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
id|__user
op_star
id|frame
suffix:semicolon
r_int
id|rsig
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
id|rsig
op_assign
id|sig
suffix:semicolon
r_if
c_cond
(paren
id|sig
OL
l_int|32
op_logical_and
id|__current_thread_info-&gt;exec_domain
op_logical_and
id|__current_thread_info-&gt;exec_domain-&gt;signal_invmap
)paren
id|rsig
op_assign
id|__current_thread_info-&gt;exec_domain-&gt;signal_invmap
(braket
id|sig
)braket
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|rsig
comma
op_amp
id|frame-&gt;sig
)paren
OL
l_int|0
)paren
r_goto
id|give_sigsegv
suffix:semicolon
r_if
c_cond
(paren
id|setup_sigcontext
c_func
(paren
op_amp
id|frame-&gt;sc
comma
id|set-&gt;sig
(braket
l_int|0
)braket
)paren
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
r_if
c_cond
(paren
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
)paren
r_goto
id|give_sigsegv
suffix:semicolon
)brace
multiline_comment|/* Set up to return from userspace.  If provided, use a stub&n;&t; * already in userspace.  */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
(brace
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|ka-&gt;sa.sa_restorer
comma
op_amp
id|frame-&gt;pretcode
)paren
OL
l_int|0
)paren
r_goto
id|give_sigsegv
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Set up the following code on the stack:&n;&t;&t; *&t;setlos&t;#__NR_sigreturn,gr7&n;&t;&t; *&t;tira&t;gr0,0&n;&t;&t; */
r_if
c_cond
(paren
id|__put_user
c_func
(paren
(paren
r_void
(paren
op_star
)paren
(paren
r_void
)paren
)paren
id|frame-&gt;retcode
comma
op_amp
id|frame-&gt;pretcode
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0x8efc0000
op_or
id|__NR_sigreturn
comma
op_amp
id|frame-&gt;retcode
(braket
l_int|0
)braket
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0xc0700000
comma
op_amp
id|frame-&gt;retcode
(braket
l_int|1
)braket
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|frame-&gt;retcode
comma
(paren
r_int
r_int
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|2
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* set up registers for signal handler */
id|regs-&gt;sp
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|regs-&gt;lr
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;retcode
suffix:semicolon
id|regs-&gt;gr8
op_assign
id|sig
suffix:semicolon
r_if
c_cond
(paren
id|get_personality
op_amp
id|FDPIC_FUNCPTRS
)paren
(brace
r_struct
id|fdpic_func_descriptor
id|__user
op_star
id|funcptr
op_assign
(paren
r_struct
id|fdpic_func_descriptor
op_star
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|__get_user
c_func
(paren
id|regs-&gt;pc
comma
op_amp
id|funcptr-&gt;text
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|regs-&gt;gr15
comma
op_amp
id|funcptr-&gt;GOT
)paren
suffix:semicolon
)brace
r_else
(brace
id|regs-&gt;pc
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|regs-&gt;gr15
op_assign
l_int|0
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;SIG deliver %d (%s:%d): sp=%p pc=%lx ra=%p&bslash;n&quot;
comma
id|sig
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|frame
comma
id|regs-&gt;pc
comma
id|frame-&gt;pretcode
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* end setup_frame() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; *&n; */
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
id|__user
op_star
id|frame
suffix:semicolon
r_int
id|rsig
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
id|rsig
op_assign
id|sig
suffix:semicolon
r_if
c_cond
(paren
id|sig
OL
l_int|32
op_logical_and
id|__current_thread_info-&gt;exec_domain
op_logical_and
id|__current_thread_info-&gt;exec_domain-&gt;signal_invmap
)paren
id|rsig
op_assign
id|__current_thread_info-&gt;exec_domain-&gt;signal_invmap
(braket
id|sig
)braket
suffix:semicolon
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|rsig
comma
op_amp
id|frame-&gt;sig
)paren
op_logical_or
id|__put_user
c_func
(paren
op_amp
id|frame-&gt;info
comma
op_amp
id|frame-&gt;pinfo
)paren
op_logical_or
id|__put_user
c_func
(paren
op_amp
id|frame-&gt;uc
comma
op_amp
id|frame-&gt;puc
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
r_if
c_cond
(paren
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|frame-&gt;uc.uc_flags
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|frame-&gt;uc.uc_link
)paren
op_logical_or
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
op_logical_or
id|__put_user
c_func
(paren
id|sas_ss_flags
c_func
(paren
id|regs-&gt;sp
)paren
comma
op_amp
id|frame-&gt;uc.uc_stack.ss_flags
)paren
op_logical_or
id|__put_user
c_func
(paren
id|current-&gt;sas_ss_size
comma
op_amp
id|frame-&gt;uc.uc_stack.ss_size
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
r_if
c_cond
(paren
id|setup_sigcontext
c_func
(paren
op_amp
id|frame-&gt;uc.uc_mcontext
comma
id|set-&gt;sig
(braket
l_int|0
)braket
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
)paren
r_goto
id|give_sigsegv
suffix:semicolon
multiline_comment|/* Set up to return from userspace.  If provided, use a stub&n;&t; * already in userspace.  */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
(brace
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|ka-&gt;sa.sa_restorer
comma
op_amp
id|frame-&gt;pretcode
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Set up the following code on the stack:&n;&t;&t; *&t;setlos&t;#__NR_sigreturn,gr7&n;&t;&t; *&t;tira&t;gr0,0&n;&t;&t; */
r_if
c_cond
(paren
id|__put_user
c_func
(paren
(paren
r_void
(paren
op_star
)paren
(paren
r_void
)paren
)paren
id|frame-&gt;retcode
comma
op_amp
id|frame-&gt;pretcode
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0x8efc0000
op_or
id|__NR_rt_sigreturn
comma
op_amp
id|frame-&gt;retcode
(braket
l_int|0
)braket
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0xc0700000
comma
op_amp
id|frame-&gt;retcode
(braket
l_int|1
)braket
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|frame-&gt;retcode
comma
(paren
r_int
r_int
)paren
(paren
id|frame-&gt;retcode
op_plus
l_int|2
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Set up registers for signal handler */
id|regs-&gt;sp
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|regs-&gt;lr
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;retcode
suffix:semicolon
id|regs-&gt;gr8
op_assign
id|sig
suffix:semicolon
id|regs-&gt;gr9
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;info
suffix:semicolon
r_if
c_cond
(paren
id|get_personality
op_amp
id|FDPIC_FUNCPTRS
)paren
(brace
r_struct
id|fdpic_func_descriptor
op_star
id|funcptr
op_assign
(paren
r_struct
id|fdpic_func_descriptor
id|__user
op_star
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|__get_user
c_func
(paren
id|regs-&gt;pc
comma
op_amp
id|funcptr-&gt;text
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|regs-&gt;gr15
comma
op_amp
id|funcptr-&gt;GOT
)paren
suffix:semicolon
)brace
r_else
(brace
id|regs-&gt;pc
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|regs-&gt;gr15
op_assign
l_int|0
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;SIG deliver %d (%s:%d): sp=%p pc=%lx ra=%p&bslash;n&quot;
comma
id|sig
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|frame
comma
id|regs-&gt;pc
comma
id|frame-&gt;pretcode
)paren
suffix:semicolon
macro_line|#endif
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
multiline_comment|/* end setup_rt_frame() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * OK, we&squot;re invoking a handler&n; */
DECL|function|handle_signal
r_static
r_void
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
r_struct
id|k_sigaction
op_star
id|ka
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
id|in_syscall
c_func
(paren
id|regs
)paren
)paren
(brace
multiline_comment|/* If so, check system call restarting.. */
r_switch
c_cond
(paren
id|regs-&gt;gr8
)paren
(brace
r_case
op_minus
id|ERESTART_RESTARTBLOCK
suffix:colon
r_case
op_minus
id|ERESTARTNOHAND
suffix:colon
id|regs-&gt;gr8
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
id|regs-&gt;gr8
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
id|regs-&gt;gr8
op_assign
id|regs-&gt;orig_gr8
suffix:semicolon
id|regs-&gt;pc
op_sub_assign
l_int|4
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
multiline_comment|/* end handle_signal() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * Note that &squot;init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t&n; * want to handle. Thus you cannot kill init even with a SIGKILL even by&n; * mistake.&n; */
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
r_struct
id|k_sigaction
id|ka
suffix:semicolon
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
id|current-&gt;flags
op_amp
id|PF_FREEZE
)paren
(brace
id|refrigerator
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_goto
id|no_signal
suffix:semicolon
)brace
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
id|signr
op_assign
id|get_signal_to_deliver
c_func
(paren
op_amp
id|info
comma
op_amp
id|ka
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
id|handle_signal
c_func
(paren
id|signr
comma
op_amp
id|info
comma
op_amp
id|ka
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
id|no_signal
suffix:colon
multiline_comment|/* Did we come from a system call? */
r_if
c_cond
(paren
id|regs-&gt;syscallno
op_ge
l_int|0
)paren
(brace
multiline_comment|/* Restart the system call - no handlers present */
r_if
c_cond
(paren
id|regs-&gt;gr8
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;gr8
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|regs-&gt;gr8
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|regs-&gt;gr8
op_assign
id|regs-&gt;orig_gr8
suffix:semicolon
id|regs-&gt;pc
op_sub_assign
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regs-&gt;gr8
op_eq
op_minus
id|ERESTART_RESTARTBLOCK
)paren
(brace
id|regs-&gt;gr8
op_assign
id|__NR_restart_syscall
suffix:semicolon
id|regs-&gt;pc
op_sub_assign
l_int|4
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* end do_signal() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * notification of userspace execution resumption&n; * - triggered by current-&gt;work.notify_resume&n; */
DECL|function|do_notify_resume
id|asmlinkage
r_void
id|do_notify_resume
c_func
(paren
id|__u32
id|thread_info_flags
)paren
(brace
multiline_comment|/* pending single-step? */
r_if
c_cond
(paren
id|thread_info_flags
op_amp
id|_TIF_SINGLESTEP
)paren
id|clear_thread_flag
c_func
(paren
id|TIF_SINGLESTEP
)paren
suffix:semicolon
multiline_comment|/* deal with pending signal delivery */
r_if
c_cond
(paren
id|thread_info_flags
op_amp
id|_TIF_SIGPENDING
)paren
id|do_signal
c_func
(paren
id|__frame
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* end do_notify_resume() */
eof
