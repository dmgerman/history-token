multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1991, 1992  Linus Torvalds&n; * Copyright (C) 1994 - 2000  Ralf Baechle&n; * Copyright (C) 1999, 2000 Silicon Graphics, Inc.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/suspend.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/asm.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/fpu.h&gt;
macro_line|#include &lt;asm/sim.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
DECL|macro|DEBUG_SIG
mdefine_line|#define DEBUG_SIG 0
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
r_extern
id|asmlinkage
r_int
id|do_signal
c_func
(paren
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
multiline_comment|/*&n; * Atomically swap in the new signal mask, and wait for a signal.&n; */
macro_line|#ifdef CONFIG_TRAD_SIGNALS
DECL|variable|sys_sigsuspend
id|save_static_function
c_func
(paren
id|sys_sigsuspend
)paren
suffix:semicolon
DECL|function|_sys_sigsuspend
id|static_unused
r_int
id|_sys_sigsuspend
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
id|sigset_t
op_star
id|uset
comma
id|saveset
comma
id|newset
suffix:semicolon
id|uset
op_assign
(paren
id|sigset_t
op_star
)paren
id|regs.regs
(braket
l_int|4
)braket
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
id|uset
comma
r_sizeof
(paren
id|sigset_t
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
id|regs.regs
(braket
l_int|2
)braket
op_assign
id|EINTR
suffix:semicolon
id|regs.regs
(braket
l_int|7
)braket
op_assign
l_int|1
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
op_amp
id|saveset
comma
op_amp
id|regs
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|variable|sys_rt_sigsuspend
id|save_static_function
c_func
(paren
id|sys_rt_sigsuspend
)paren
suffix:semicolon
DECL|function|_sys_rt_sigsuspend
id|static_unused
r_int
id|_sys_rt_sigsuspend
c_func
(paren
id|nabi_no_regargs
r_struct
id|pt_regs
id|regs
)paren
(brace
id|sigset_t
op_star
id|unewset
comma
id|saveset
comma
id|newset
suffix:semicolon
r_int
id|sigsetsize
suffix:semicolon
multiline_comment|/* XXX Don&squot;t preclude handling different sized sigset_t&squot;s.  */
id|sigsetsize
op_assign
id|regs.regs
(braket
l_int|5
)braket
suffix:semicolon
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
id|unewset
op_assign
(paren
id|sigset_t
op_star
)paren
id|regs.regs
(braket
l_int|4
)braket
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
id|regs.regs
(braket
l_int|2
)braket
op_assign
id|EINTR
suffix:semicolon
id|regs.regs
(braket
l_int|7
)braket
op_assign
l_int|1
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
op_amp
id|saveset
comma
op_amp
id|regs
)paren
)paren
r_return
op_minus
id|EINTR
suffix:semicolon
)brace
)brace
macro_line|#ifdef CONFIG_TRAD_SIGNALS
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
id|sigaction
op_star
id|act
comma
r_struct
id|sigaction
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
r_int
id|err
op_assign
l_int|0
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
op_logical_neg
id|access_ok
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
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|new_ka.sa.sa_handler
comma
op_amp
id|act-&gt;sa_handler
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|new_ka.sa.sa_flags
comma
op_amp
id|act-&gt;sa_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|mask
comma
op_amp
id|act-&gt;sa_mask.sig
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
r_return
op_minus
id|EFAULT
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
op_logical_neg
id|access_ok
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
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|old_ka.sa.sa_flags
comma
op_amp
id|oact-&gt;sa_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|old_ka.sa.sa_handler
comma
op_amp
id|oact-&gt;sa_handler
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|old_ka.sa.sa_mask.sig
(braket
l_int|0
)braket
comma
id|oact-&gt;sa_mask.sig
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
id|oact-&gt;sa_mask.sig
(braket
l_int|1
)braket
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
id|oact-&gt;sa_mask.sig
(braket
l_int|2
)braket
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
id|oact-&gt;sa_mask.sig
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif
DECL|function|sys_sigaltstack
id|asmlinkage
r_int
id|sys_sigaltstack
c_func
(paren
id|nabi_no_regargs
r_struct
id|pt_regs
id|regs
)paren
(brace
r_const
id|stack_t
op_star
id|uss
op_assign
(paren
r_const
id|stack_t
op_star
)paren
id|regs.regs
(braket
l_int|4
)braket
suffix:semicolon
id|stack_t
op_star
id|uoss
op_assign
(paren
id|stack_t
op_star
)paren
id|regs.regs
(braket
l_int|5
)braket
suffix:semicolon
r_int
r_int
id|usp
op_assign
id|regs.regs
(braket
l_int|29
)braket
suffix:semicolon
r_return
id|do_sigaltstack
c_func
(paren
id|uss
comma
id|uoss
comma
id|usp
)paren
suffix:semicolon
)brace
DECL|function|restore_sigcontext
id|asmlinkage
r_int
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
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Always make any pending restarted system calls return -EINTR */
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|restart_block.fn
op_assign
id|do_no_restart_syscall
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|regs-&gt;cp0_epc
comma
op_amp
id|sc-&gt;sc_pc
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|regs-&gt;hi
comma
op_amp
id|sc-&gt;sc_mdhi
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|regs-&gt;lo
comma
op_amp
id|sc-&gt;sc_mdlo
)paren
suffix:semicolon
DECL|macro|restore_gp_reg
mdefine_line|#define restore_gp_reg(i) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;err |= __get_user(regs-&gt;regs[i], &amp;sc-&gt;sc_regs[i]);&t;&t;&bslash;&n;} while(0)
id|restore_gp_reg
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|11
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|12
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|13
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|14
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|15
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|16
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|17
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|18
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|19
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|21
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|22
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|23
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|24
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|25
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|26
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|27
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|28
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|29
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|30
)paren
suffix:semicolon
id|restore_gp_reg
c_func
(paren
l_int|31
)paren
suffix:semicolon
DECL|macro|restore_gp_reg
macro_line|#undef restore_gp_reg
id|err
op_or_assign
id|__get_user
c_func
(paren
id|current-&gt;used_math
comma
op_amp
id|sc-&gt;sc_used_math
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;used_math
)paren
(brace
multiline_comment|/* restore fpu context if we have used it before */
id|own_fpu
c_func
(paren
)paren
suffix:semicolon
id|err
op_or_assign
id|restore_fp_context
c_func
(paren
id|sc
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* signal handler may have used FPU.  Give it up. */
id|lose_fpu
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_TRAD_SIGNALS
DECL|struct|sigframe
r_struct
id|sigframe
(brace
DECL|member|sf_ass
id|u32
id|sf_ass
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* argument save space for o32 */
DECL|member|sf_code
id|u32
id|sf_code
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* signal trampoline */
DECL|member|sf_sc
r_struct
id|sigcontext
id|sf_sc
suffix:semicolon
DECL|member|sf_mask
id|sigset_t
id|sf_mask
suffix:semicolon
)brace
suffix:semicolon
macro_line|#endif
DECL|struct|rt_sigframe
r_struct
id|rt_sigframe
(brace
DECL|member|rs_ass
id|u32
id|rs_ass
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* argument save space for o32 */
DECL|member|rs_code
id|u32
id|rs_code
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* signal trampoline */
DECL|member|rs_info
r_struct
id|siginfo
id|rs_info
suffix:semicolon
DECL|member|rs_uc
r_struct
id|ucontext
id|rs_uc
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_TRAD_SIGNALS
DECL|function|sys_sigreturn
id|asmlinkage
r_void
id|sys_sigreturn
c_func
(paren
r_struct
id|pt_regs
id|regs
)paren
(brace
r_struct
id|sigframe
op_star
id|frame
suffix:semicolon
id|sigset_t
id|blocked
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|sigframe
op_star
)paren
id|regs.regs
(braket
l_int|29
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
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
id|blocked
comma
op_amp
id|frame-&gt;sf_mask
comma
r_sizeof
(paren
id|blocked
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
id|blocked
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
id|blocked
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
id|regs
comma
op_amp
id|frame-&gt;sf_sc
)paren
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t let your children do this ...&n;&t; */
r_if
c_cond
(paren
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|flags
op_amp
id|TIF_SYSCALL_TRACE
)paren
id|do_syscall_trace
c_func
(paren
op_amp
id|regs
comma
l_int|1
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move&bslash;t$29, %0&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;tsyscall_exit&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|regs
)paren
)paren
suffix:semicolon
multiline_comment|/* Unreached */
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
)brace
macro_line|#endif
DECL|function|sys_rt_sigreturn
id|asmlinkage
r_void
id|sys_rt_sigreturn
c_func
(paren
id|nabi_no_regargs
r_struct
id|pt_regs
id|regs
)paren
(brace
r_struct
id|rt_sigframe
op_star
id|frame
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
id|stack_t
id|st
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|rt_sigframe
op_star
)paren
id|regs.regs
(braket
l_int|29
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|access_ok
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
id|frame-&gt;rs_uc.uc_sigmask
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
id|regs
comma
op_amp
id|frame-&gt;rs_uc.uc_mcontext
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
id|frame-&gt;rs_uc.uc_stack
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
id|regs.regs
(braket
l_int|29
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Don&squot;t let your children do this ...&n;&t; */
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;move&bslash;t$29, %0&bslash;n&bslash;t&quot;
l_string|&quot;j&bslash;tsyscall_exit&quot;
suffix:colon
multiline_comment|/* no outputs */
suffix:colon
l_string|&quot;r&quot;
(paren
op_amp
id|regs
)paren
)paren
suffix:semicolon
multiline_comment|/* Unreached */
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
)brace
DECL|function|setup_sigcontext
r_inline
r_int
id|setup_sigcontext
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
id|err
op_assign
l_int|0
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;cp0_epc
comma
op_amp
id|sc-&gt;sc_pc
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;cp0_status
comma
op_amp
id|sc-&gt;sc_status
)paren
suffix:semicolon
DECL|macro|save_gp_reg
mdefine_line|#define save_gp_reg(i) do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;err |= __put_user(regs-&gt;regs[i], &amp;sc-&gt;sc_regs[i]);&t;&t;&bslash;&n;} while(0)
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|sc-&gt;sc_regs
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|4
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|5
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|6
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|7
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|8
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|9
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|10
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|11
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|12
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|13
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|14
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|15
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|16
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|17
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|18
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|19
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|21
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|22
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|23
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|24
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|25
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|26
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|27
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|28
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|29
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|30
)paren
suffix:semicolon
id|save_gp_reg
c_func
(paren
l_int|31
)paren
suffix:semicolon
DECL|macro|save_gp_reg
macro_line|#undef save_gp_reg
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;hi
comma
op_amp
id|sc-&gt;sc_mdhi
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;lo
comma
op_amp
id|sc-&gt;sc_mdlo
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;cp0_cause
comma
op_amp
id|sc-&gt;sc_cause
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|regs-&gt;cp0_badvaddr
comma
op_amp
id|sc-&gt;sc_badvaddr
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;used_math
comma
op_amp
id|sc-&gt;sc_used_math
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|current-&gt;used_math
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Save FPU state to signal context.  Signal handler will &quot;inherit&quot;&n;&t; * current FPU state.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|is_fpu_owner
c_func
(paren
)paren
)paren
(brace
id|own_fpu
c_func
(paren
)paren
suffix:semicolon
id|restore_fp
c_func
(paren
id|current
)paren
suffix:semicolon
)brace
id|err
op_or_assign
id|save_fp_context
c_func
(paren
id|sc
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Determine which stack to use..&n; */
DECL|function|get_sigframe
r_static
r_inline
r_void
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
id|regs-&gt;regs
(braket
l_int|29
)braket
suffix:semicolon
multiline_comment|/*&n; &t; * FPU emulator may have it&squot;s own trampoline active just&n; &t; * above the user stack, 16-bytes before the next lowest&n; &t; * 16 byte boundary.  Try to avoid trashing it.&n; &t; */
id|sp
op_sub_assign
l_int|32
suffix:semicolon
multiline_comment|/* This is the X/Open sanctioned signal stack switching.  */
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
(paren
id|sp
)paren
op_eq
l_int|0
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
id|ALMASK
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_TRAD_SIGNALS
DECL|function|setup_frame
r_static
r_void
r_inline
id|setup_frame
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
id|signr
comma
id|sigset_t
op_star
id|set
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
multiline_comment|/*&n;&t; * Set up the return code ...&n;&t; *&n;&t; *         li      v0, __NR_sigreturn&n;&t; *         syscall&n;&t; */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x24020000
op_plus
id|__NR_sigreturn
comma
id|frame-&gt;sf_code
op_plus
l_int|0
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x0000000c
comma
id|frame-&gt;sf_code
op_plus
l_int|1
)paren
suffix:semicolon
id|flush_cache_sigtramp
c_func
(paren
(paren
r_int
r_int
)paren
id|frame-&gt;sf_code
)paren
suffix:semicolon
id|err
op_or_assign
id|setup_sigcontext
c_func
(paren
id|regs
comma
op_amp
id|frame-&gt;sf_sc
)paren
suffix:semicolon
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;sf_mask
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
multiline_comment|/*&n;&t; * Arguments to signal handler:&n;&t; *&n;&t; *   a0 = signal number&n;&t; *   a1 = 0 (should be cause)&n;&t; *   a2 = pointer to struct sigcontext&n;&t; *&n;&t; * $25 and c0_epc point to the signal handler, $29 points to the&n;&t; * struct sigframe.&n;&t; */
id|regs-&gt;regs
(braket
l_int|4
)braket
op_assign
id|signr
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|5
)braket
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|6
)braket
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;sf_sc
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|29
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|31
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;sf_code
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|regs-&gt;regs
(braket
l_int|25
)braket
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;SIG deliver (%s:%d): sp=0x%p pc=0x%lx ra=0x%p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|frame
comma
id|regs-&gt;cp0_epc
comma
id|frame-&gt;regs
(braket
l_int|31
)braket
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
id|give_sigsegv
suffix:colon
id|force_sigsegv
c_func
(paren
id|signr
comma
id|current
)paren
suffix:semicolon
)brace
macro_line|#endif
DECL|function|setup_rt_frame
r_static
r_void
r_inline
id|setup_rt_frame
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
id|signr
comma
id|sigset_t
op_star
id|set
comma
id|siginfo_t
op_star
id|info
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
multiline_comment|/*&n;&t; * Set up the return code ...&n;&t; *&n;&t; *         li      v0, __NR_rt_sigreturn&n;&t; *         syscall&n;&t; */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x24020000
op_plus
id|__NR_rt_sigreturn
comma
id|frame-&gt;rs_code
op_plus
l_int|0
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x0000000c
comma
id|frame-&gt;rs_code
op_plus
l_int|1
)paren
suffix:semicolon
id|flush_cache_sigtramp
c_func
(paren
(paren
r_int
r_int
)paren
id|frame-&gt;rs_code
)paren
suffix:semicolon
multiline_comment|/* Create siginfo.  */
id|err
op_or_assign
id|copy_siginfo_to_user
c_func
(paren
op_amp
id|frame-&gt;rs_info
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
id|frame-&gt;rs_uc.uc_flags
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
id|frame-&gt;rs_uc.uc_link
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
id|frame-&gt;rs_uc.uc_stack.ss_sp
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
id|regs-&gt;regs
(braket
l_int|29
)braket
)paren
comma
op_amp
id|frame-&gt;rs_uc.uc_stack.ss_flags
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
id|frame-&gt;rs_uc.uc_stack.ss_size
)paren
suffix:semicolon
id|err
op_or_assign
id|setup_sigcontext
c_func
(paren
id|regs
comma
op_amp
id|frame-&gt;rs_uc.uc_mcontext
)paren
suffix:semicolon
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;rs_uc.uc_sigmask
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
multiline_comment|/*&n;&t; * Arguments to signal handler:&n;&t; *&n;&t; *   a0 = signal number&n;&t; *   a1 = 0 (should be cause)&n;&t; *   a2 = pointer to ucontext&n;&t; *&n;&t; * $25 and c0_epc point to the signal handler, $29 points to&n;&t; * the struct rt_sigframe.&n;&t; */
id|regs-&gt;regs
(braket
l_int|4
)braket
op_assign
id|signr
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|5
)braket
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;rs_info
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|6
)braket
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;rs_uc
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|29
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|31
)braket
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;rs_code
suffix:semicolon
id|regs-&gt;cp0_epc
op_assign
id|regs-&gt;regs
(braket
l_int|25
)braket
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;SIG deliver (%s:%d): sp=0x%p pc=0x%lx ra=0x%p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|frame
comma
id|regs-&gt;cp0_epc
comma
id|regs-&gt;regs
(braket
l_int|31
)braket
)paren
suffix:semicolon
macro_line|#endif
r_return
suffix:semicolon
id|give_sigsegv
suffix:colon
id|force_sigsegv
c_func
(paren
id|signr
comma
id|current
)paren
suffix:semicolon
)brace
r_extern
r_void
id|setup_rt_frame_n32
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
id|signr
comma
id|sigset_t
op_star
id|set
comma
id|siginfo_t
op_star
id|info
)paren
suffix:semicolon
DECL|function|handle_signal
r_static
r_inline
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
r_switch
c_cond
(paren
id|regs-&gt;regs
(braket
l_int|0
)braket
)paren
(brace
r_case
id|ERESTART_RESTARTBLOCK
suffix:colon
r_case
id|ERESTARTNOHAND
suffix:colon
id|regs-&gt;regs
(braket
l_int|2
)braket
op_assign
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
r_case
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
id|regs-&gt;regs
(braket
l_int|2
)braket
op_assign
id|EINTR
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* fallthrough */
r_case
id|ERESTARTNOINTR
suffix:colon
multiline_comment|/* Userland will reload $v0.  */
id|regs-&gt;regs
(braket
l_int|7
)braket
op_assign
id|regs-&gt;regs
(braket
l_int|26
)braket
suffix:semicolon
id|regs-&gt;cp0_epc
op_sub_assign
l_int|8
suffix:semicolon
)brace
id|regs-&gt;regs
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Don&squot;t deal with this again.  */
macro_line|#ifdef CONFIG_TRAD_SIGNALS
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_SIGINFO
)paren
(brace
macro_line|#else
r_if
c_cond
(paren
l_int|1
)paren
(brace
macro_line|#endif
macro_line|#ifdef CONFIG_MIPS32_N32
r_if
c_cond
(paren
(paren
id|current-&gt;thread.mflags
op_amp
id|MF_ABI_MASK
)paren
op_eq
id|MF_N32
)paren
id|setup_rt_frame_n32
(paren
id|ka
comma
id|regs
comma
id|sig
comma
id|oldset
comma
id|info
)paren
suffix:semicolon
r_else
macro_line|#endif
id|setup_rt_frame
c_func
(paren
id|ka
comma
id|regs
comma
id|sig
comma
id|oldset
comma
id|info
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_TRAD_SIGNALS
r_else
id|setup_frame
c_func
(paren
id|ka
comma
id|regs
comma
id|sig
comma
id|oldset
)paren
suffix:semicolon
macro_line|#endif
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
r_extern
r_int
id|do_signal32
c_func
(paren
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
r_extern
r_int
id|do_irix_signal
c_func
(paren
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
DECL|function|do_signal
id|asmlinkage
r_int
id|do_signal
c_func
(paren
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
id|ka
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
r_int
id|signr
suffix:semicolon
macro_line|#ifdef CONFIG_BINFMT_ELF32
r_if
c_cond
(paren
(paren
id|current-&gt;thread.mflags
op_amp
id|MF_ABI_MASK
)paren
op_eq
id|MF_O32
)paren
(brace
r_return
id|do_signal32
c_func
(paren
id|oldset
comma
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * We want the common case to go fast, which is why we may in certain&n;&t; * cases get here from kernel mode. Just return without doing anything&n;&t; * if so.&n;&t; */
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
multiline_comment|/*&n;&t; * Who&squot;s code doesn&squot;t conform to the restartable syscall convention&n;&t; * dies here!!!  The li instruction, a single machine instruction,&n;&t; * must directly be followed by the syscall instruction.&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;regs
(braket
l_int|0
)braket
)paren
(brace
r_if
c_cond
(paren
id|regs-&gt;regs
(braket
l_int|2
)braket
op_eq
id|ERESTARTNOHAND
op_logical_or
id|regs-&gt;regs
(braket
l_int|2
)braket
op_eq
id|ERESTARTSYS
op_logical_or
id|regs-&gt;regs
(braket
l_int|2
)braket
op_eq
id|ERESTARTNOINTR
)paren
(brace
id|regs-&gt;regs
(braket
l_int|7
)braket
op_assign
id|regs-&gt;regs
(braket
l_int|26
)braket
suffix:semicolon
id|regs-&gt;cp0_epc
op_sub_assign
l_int|8
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regs-&gt;regs
(braket
l_int|2
)braket
op_eq
id|ERESTART_RESTARTBLOCK
)paren
(brace
id|regs-&gt;regs
(braket
l_int|2
)braket
op_assign
id|__NR_restart_syscall
suffix:semicolon
id|regs-&gt;regs
(braket
l_int|7
)braket
op_assign
id|regs-&gt;regs
(braket
l_int|26
)braket
suffix:semicolon
id|regs-&gt;cp0_epc
op_sub_assign
l_int|4
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|do_irix_signal
c_func
(paren
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
multiline_comment|/*&n; * notification of userspace execution resumption&n; * - triggered by current-&gt;work.notify_resume&n; */
DECL|function|do_notify_resume
id|asmlinkage
r_void
id|do_notify_resume
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
id|__u32
id|thread_info_flags
)paren
(brace
multiline_comment|/* deal with pending signal delivery */
r_if
c_cond
(paren
id|thread_info_flags
op_amp
id|_TIF_SIGPENDING
)paren
(brace
macro_line|#ifdef CONFIG_BINFMT_ELF32
r_if
c_cond
(paren
id|likely
c_func
(paren
(paren
id|current-&gt;thread.mflags
op_amp
id|MF_ABI_MASK
)paren
op_eq
id|MF_O32
)paren
)paren
(brace
id|do_signal32
c_func
(paren
id|oldset
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_BINFMT_IRIX
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|current-&gt;personality
op_ne
id|PER_LINUX
)paren
)paren
(brace
id|do_irix_signal
c_func
(paren
id|oldset
comma
id|regs
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|do_signal
c_func
(paren
id|oldset
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
eof
