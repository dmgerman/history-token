multiline_comment|/*&n; * arch/v850/kernel/signal.c -- Signal handling&n; *&n; *  Copyright (C) 2001,02  NEC Corporation&n; *  Copyright (C) 2001,02  Miles Bader &lt;miles@gnu.org&gt;&n; *  Copyright (C) 1999,2000,2002  Niibe Yutaka &amp; Kaz Kojima&n; *  Copyright (C) 1991,1992  Linus Torvalds&n; *&n; * This file is subject to the terms and conditions of the GNU General&n; * Public License.  See the file COPYING in the main directory of this&n; * archive for more details.&n; *&n; * 1997-11-28  Modified for POSIX.1b signals by Richard Henderson&n; *&n; * This file was derived from the sh version, arch/sh/kernel/signal.c&n; */
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
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/thread_info.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
DECL|macro|DEBUG_SIG
mdefine_line|#define DEBUG_SIG 0
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
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
id|asmlinkage
r_int
DECL|function|sys_sigsuspend
id|sys_sigsuspend
c_func
(paren
id|old_sigset_t
id|mask
comma
r_struct
id|pt_regs
op_star
id|regs
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
id|current-&gt;sig-&gt;siglock
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
id|current-&gt;sig-&gt;siglock
)paren
suffix:semicolon
id|regs-&gt;gpr
(braket
id|GPR_RVAL
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
id|sigset_t
op_star
id|unewset
comma
r_int
id|sigsetsize
comma
r_struct
id|pt_regs
op_star
id|regs
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
id|current-&gt;sig-&gt;siglock
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
id|current-&gt;sig-&gt;siglock
)paren
suffix:semicolon
id|regs-&gt;gpr
(braket
id|GPR_RVAL
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
id|regs-&gt;gpr
(braket
id|GPR_SP
)braket
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
DECL|member|tramp
r_int
r_int
id|tramp
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* signal trampoline */
)brace
suffix:semicolon
DECL|struct|rt_sigframe
r_struct
id|rt_sigframe
(brace
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
DECL|member|tramp
r_int
r_int
id|tramp
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* signal trampoline */
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
comma
r_int
op_star
id|rval_p
)paren
(brace
r_int
r_int
id|err
op_assign
l_int|0
suffix:semicolon
DECL|macro|COPY
mdefine_line|#define COPY(x)&t;&t;err |= __get_user(regs-&gt;x, &amp;sc-&gt;regs.x)
id|COPY
c_func
(paren
id|gpr
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|8
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|9
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|10
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|12
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|13
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|14
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|15
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|16
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|17
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|18
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|19
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|20
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|21
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|22
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|23
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|24
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|25
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|26
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|27
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|28
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|29
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|30
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|31
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|pc
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|psw
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ctpc
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ctpsw
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ctbp
)paren
suffix:semicolon
DECL|macro|COPY
macro_line|#undef COPY
r_return
id|err
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
id|regs-&gt;gpr
(braket
id|GPR_SP
)braket
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
r_int
id|rval
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
id|current-&gt;sig-&gt;siglock
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
id|current-&gt;sig-&gt;siglock
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
comma
op_amp
id|rval
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_return
id|rval
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
id|regs-&gt;gpr
(braket
id|GPR_SP
)braket
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
id|stack_t
id|st
suffix:semicolon
r_int
id|rval
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
id|current-&gt;sig-&gt;siglock
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
id|current-&gt;sig-&gt;siglock
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
comma
op_amp
id|rval
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
id|regs-&gt;gpr
(braket
id|GPR_SP
)braket
)paren
suffix:semicolon
r_return
id|rval
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
DECL|macro|COPY
mdefine_line|#define COPY(x)&t;&t;err |= __put_user(regs-&gt;x, &amp;sc-&gt;regs.x)
id|COPY
c_func
(paren
id|gpr
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|7
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|8
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|9
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|10
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|11
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|12
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|13
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|14
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|15
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|16
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|17
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|18
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|19
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|20
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|21
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|22
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|23
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|24
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|25
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|26
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|27
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|28
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|29
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|30
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|gpr
(braket
l_int|31
)braket
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|pc
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|psw
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ctpc
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ctpsw
)paren
suffix:semicolon
id|COPY
c_func
(paren
id|ctbp
)paren
suffix:semicolon
DECL|macro|COPY
macro_line|#undef COPY
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
r_return
id|err
suffix:semicolon
)brace
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
multiline_comment|/* Default to using normal stack */
r_int
r_int
id|sp
op_assign
id|regs-&gt;gpr
(braket
id|GPR_SP
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_ONSTACK
)paren
op_ne
l_int|0
op_logical_and
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
l_int|8UL
)paren
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
r_struct
id|sigframe
op_star
id|frame
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|signal
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
id|signal
op_assign
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
ques
c_cond
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain-&gt;signal_invmap
(braket
id|sig
)braket
suffix:colon
id|sig
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
multiline_comment|/* Set up to return from userspace.  If provided, use a stub&n;&t;   already in userspace.  */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
(brace
id|regs-&gt;gpr
(braket
id|GPR_LP
)braket
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
multiline_comment|/* Note, these encodings are _little endian_!  */
multiline_comment|/* addi  __NR_sigreturn, r0, r12  */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x6600
op_or
(paren
id|__NR_sigreturn
op_lshift
l_int|16
)paren
comma
id|frame-&gt;tramp
op_plus
l_int|0
)paren
suffix:semicolon
multiline_comment|/* trap 0 */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x010007e0
comma
id|frame-&gt;tramp
op_plus
l_int|1
)paren
suffix:semicolon
id|regs-&gt;gpr
(braket
id|GPR_LP
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;tramp
suffix:semicolon
id|flush_cache_sigtramp
(paren
id|regs-&gt;gpr
(braket
id|GPR_LP
)braket
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
multiline_comment|/* Set up registers for signal handler.  */
id|regs-&gt;pc
op_assign
(paren
id|v850_reg_t
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|regs-&gt;gpr
(braket
id|GPR_SP
)braket
op_assign
(paren
id|v850_reg_t
)paren
id|frame
suffix:semicolon
multiline_comment|/* Signal handler args:  */
id|regs-&gt;gpr
(braket
id|GPR_ARG0
)braket
op_assign
id|signal
suffix:semicolon
multiline_comment|/* arg 0: signum */
id|regs-&gt;gpr
(braket
id|GPR_ARG1
)braket
op_assign
(paren
id|v850_reg_t
)paren
op_amp
id|frame-&gt;sc
suffix:semicolon
multiline_comment|/* arg 1: sigcontext */
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
l_string|&quot;SIG deliver (%s:%d): sp=%p pc=%08lx ra=%08lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|frame
comma
id|regs-&gt;pc
comma
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
id|err
op_assign
l_int|0
suffix:semicolon
r_int
id|signal
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
id|signal
op_assign
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
ques
c_cond
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|exec_domain-&gt;signal_invmap
(braket
id|sig
)braket
suffix:colon
id|sig
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
id|regs-&gt;gpr
(braket
id|GPR_SP
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
multiline_comment|/* Set up to return from userspace.  If provided, use a stub&n;&t;   already in userspace.  */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTORER
)paren
(brace
id|regs-&gt;gpr
(braket
id|GPR_LP
)braket
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
multiline_comment|/* Note, these encodings are _little endian_!  */
multiline_comment|/* addi  __NR_sigreturn, r0, r12  */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x6600
op_or
(paren
id|__NR_sigreturn
op_lshift
l_int|16
)paren
comma
id|frame-&gt;tramp
op_plus
l_int|0
)paren
suffix:semicolon
multiline_comment|/* trap 0 */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x010007e0
comma
id|frame-&gt;tramp
op_plus
l_int|1
)paren
suffix:semicolon
id|regs-&gt;gpr
(braket
id|GPR_LP
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;tramp
suffix:semicolon
id|flush_cache_sigtramp
(paren
id|regs-&gt;gpr
(braket
id|GPR_LP
)braket
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
multiline_comment|/* Set up registers for signal handler.  */
id|regs-&gt;pc
op_assign
(paren
id|v850_reg_t
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|regs-&gt;gpr
(braket
id|GPR_SP
)braket
op_assign
(paren
id|v850_reg_t
)paren
id|frame
suffix:semicolon
multiline_comment|/* Signal handler args:  */
id|regs-&gt;gpr
(braket
id|GPR_ARG0
)braket
op_assign
id|signal
suffix:semicolon
multiline_comment|/* arg 0: signum */
id|regs-&gt;gpr
(braket
id|GPR_ARG1
)braket
op_assign
(paren
id|v850_reg_t
)paren
op_amp
id|frame-&gt;info
suffix:semicolon
multiline_comment|/* arg 1: siginfo */
id|regs-&gt;gpr
(braket
id|GPR_ARG2
)braket
op_assign
(paren
id|v850_reg_t
)paren
op_amp
id|frame-&gt;uc
suffix:semicolon
multiline_comment|/* arg 2: ucontext */
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
l_string|&quot;SIG deliver (%s:%d): sp=%p pc=%08lx pr=%08lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|frame
comma
id|regs-&gt;pc
comma
id|regs-&gt;pr
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
id|current-&gt;sig-&gt;action
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
id|PT_REGS_SYSCALL
(paren
id|regs
)paren
)paren
(brace
multiline_comment|/* If so, check system call restarting.. */
r_switch
c_cond
(paren
id|regs-&gt;gpr
(braket
id|GPR_RVAL
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
multiline_comment|/* fall through */
r_case
op_minus
id|ERESTARTNOHAND
suffix:colon
id|regs-&gt;gpr
(braket
id|GPR_RVAL
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
id|regs-&gt;gpr
(braket
id|GPR_RVAL
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
id|regs-&gt;gpr
(braket
l_int|12
)braket
op_assign
id|PT_REGS_SYSCALL
(paren
id|regs
)paren
suffix:semicolon
id|regs-&gt;pc
op_sub_assign
l_int|4
suffix:semicolon
multiline_comment|/* Size of `trap 0&squot; insn.  */
)brace
id|PT_REGS_SET_SYSCALL
(paren
id|regs
comma
l_int|0
)paren
suffix:semicolon
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
id|current-&gt;sig-&gt;siglock
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
id|current-&gt;sig-&gt;siglock
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
id|signr
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
id|PT_REGS_SYSCALL
(paren
id|regs
)paren
)paren
(brace
r_int
id|rval
op_assign
(paren
r_int
)paren
id|regs-&gt;gpr
(braket
id|GPR_RVAL
)braket
suffix:semicolon
multiline_comment|/* Restart the system call - no handlers present */
r_if
c_cond
(paren
id|rval
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
id|rval
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
id|rval
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|regs-&gt;gpr
(braket
l_int|12
)braket
op_assign
id|PT_REGS_SYSCALL
(paren
id|regs
)paren
suffix:semicolon
id|regs-&gt;pc
op_sub_assign
l_int|4
suffix:semicolon
multiline_comment|/* Size of `trap 0&squot; insn.  */
)brace
r_else
r_if
c_cond
(paren
id|rval
op_eq
op_minus
id|ERESTART_RESTARTBLOCK
)paren
(brace
id|regs-&gt;gpr
(braket
l_int|12
)braket
op_assign
id|__NR_restart_syscall
suffix:semicolon
id|regs-&gt;pc
op_sub_assign
l_int|4
suffix:semicolon
multiline_comment|/* Size of `trap 0&squot; insn.  */
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
