multiline_comment|/*&n; * Architecture-specific signal handling support.&n; *&n; * Copyright (C) 1999-2003 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; *&n; * Derived from i386 and Alpha versions.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;asm/ia32.h&gt;
macro_line|#include &lt;asm/intrinsics.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/rse.h&gt;
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#include &quot;sigframe.h&quot;
DECL|macro|DEBUG_SIG
mdefine_line|#define DEBUG_SIG&t;0
DECL|macro|STACK_ALIGN
mdefine_line|#define STACK_ALIGN&t;16&t;&t;/* minimal alignment for stack pointer */
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE&t;(~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
macro_line|#if _NSIG_WORDS &gt; 1
DECL|macro|PUT_SIGSET
macro_line|# define PUT_SIGSET(k,u)&t;__copy_to_user((u)-&gt;sig, (k)-&gt;sig, sizeof(sigset_t))
DECL|macro|GET_SIGSET
macro_line|# define GET_SIGSET(k,u)&t;__copy_from_user((k)-&gt;sig, (u)-&gt;sig, sizeof(sigset_t))
macro_line|#else
DECL|macro|PUT_SIGSET
macro_line|# define PUT_SIGSET(k,u)&t;__put_user((k)-&gt;sig[0], &amp;(u)-&gt;sig[0])
DECL|macro|GET_SIGSET
macro_line|# define GET_SIGSET(k,u)&t;__get_user((k)-&gt;sig[0], &amp;(u)-&gt;sig[0])
macro_line|#endif
r_int
DECL|function|ia64_rt_sigsuspend
id|ia64_rt_sigsuspend
(paren
id|sigset_t
op_star
id|uset
comma
r_int
id|sigsetsize
comma
r_struct
id|sigscratch
op_star
id|scr
)paren
(brace
id|sigset_t
id|oldset
comma
id|set
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
op_logical_neg
id|access_ok
c_func
(paren
id|VERIFY_READ
comma
id|uset
comma
id|sigsetsize
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_if
c_cond
(paren
id|GET_SIGSET
c_func
(paren
op_amp
id|set
comma
id|uset
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
(brace
id|oldset
op_assign
id|current-&gt;blocked
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
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The return below usually returns to the signal handler.  We need to&n;&t; * pre-set the correct error code here to ensure that the right values&n;&t; * get saved in sigcontext by ia64_do_signal.&n;&t; */
id|scr-&gt;pt.r8
op_assign
id|EINTR
suffix:semicolon
id|scr-&gt;pt.r10
op_assign
op_minus
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
id|ia64_do_signal
c_func
(paren
op_amp
id|oldset
comma
id|scr
comma
l_int|1
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
DECL|function|sys_sigaltstack
id|sys_sigaltstack
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
r_int
id|arg2
comma
r_int
id|arg3
comma
r_int
id|arg4
comma
r_int
id|arg5
comma
r_int
id|arg6
comma
r_int
id|arg7
comma
r_int
id|stack
)paren
(brace
r_struct
id|pt_regs
op_star
id|pt
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
op_amp
id|stack
suffix:semicolon
r_return
id|do_sigaltstack
c_func
(paren
id|uss
comma
id|uoss
comma
id|pt-&gt;r12
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|restore_sigcontext
id|restore_sigcontext
(paren
r_struct
id|sigcontext
op_star
id|sc
comma
r_struct
id|sigscratch
op_star
id|scr
)paren
(brace
r_int
r_int
id|ip
comma
id|flags
comma
id|nat
comma
id|um
comma
id|cfm
suffix:semicolon
r_int
id|err
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
multiline_comment|/* restore scratch that always needs gets updated during signal delivery: */
id|err
op_assign
id|__get_user
c_func
(paren
id|flags
comma
op_amp
id|sc-&gt;sc_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|nat
comma
op_amp
id|sc-&gt;sc_nat
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|ip
comma
op_amp
id|sc-&gt;sc_ip
)paren
suffix:semicolon
multiline_comment|/* instruction pointer */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|cfm
comma
op_amp
id|sc-&gt;sc_cfm
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|um
comma
op_amp
id|sc-&gt;sc_um
)paren
suffix:semicolon
multiline_comment|/* user mask */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.ar_rsc
comma
op_amp
id|sc-&gt;sc_ar_rsc
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.ar_unat
comma
op_amp
id|sc-&gt;sc_ar_unat
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.ar_fpsr
comma
op_amp
id|sc-&gt;sc_ar_fpsr
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.ar_pfs
comma
op_amp
id|sc-&gt;sc_ar_pfs
)paren
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.pr
comma
op_amp
id|sc-&gt;sc_pr
)paren
suffix:semicolon
multiline_comment|/* predicates */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.b0
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* b0 (rp) */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.b6
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|6
)braket
)paren
suffix:semicolon
multiline_comment|/* b6 */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|scr-&gt;pt.r1
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|1
)braket
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r1 */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|scr-&gt;pt.r8
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|8
)braket
comma
l_int|4
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r8-r11 */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|scr-&gt;pt.r12
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|12
)braket
comma
l_int|2
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r12-r13 */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|scr-&gt;pt.r15
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|15
)braket
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r15 */
id|scr-&gt;pt.cr_ifs
op_assign
id|cfm
op_or
(paren
l_int|1UL
op_lshift
l_int|63
)paren
suffix:semicolon
multiline_comment|/* establish new instruction pointer: */
id|scr-&gt;pt.cr_iip
op_assign
id|ip
op_amp
op_complement
l_int|0x3UL
suffix:semicolon
id|ia64_psr
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
op_member_access_from_pointer
id|ri
op_assign
id|ip
op_amp
l_int|0x3
suffix:semicolon
id|scr-&gt;pt.cr_ipsr
op_assign
(paren
id|scr-&gt;pt.cr_ipsr
op_amp
op_complement
id|IA64_PSR_UM
)paren
op_or
(paren
id|um
op_amp
id|IA64_PSR_UM
)paren
suffix:semicolon
id|scr-&gt;scratch_unat
op_assign
id|ia64_put_scratch_nat_bits
c_func
(paren
op_amp
id|scr-&gt;pt
comma
id|nat
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|flags
op_amp
id|IA64_SC_FLAG_IN_SYSCALL
)paren
)paren
(brace
multiline_comment|/* Restore most scratch-state only when not in syscall. */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.ar_ccv
comma
op_amp
id|sc-&gt;sc_ar_ccv
)paren
suffix:semicolon
multiline_comment|/* ar.ccv */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.b7
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|7
)braket
)paren
suffix:semicolon
multiline_comment|/* b7 */
id|err
op_or_assign
id|__get_user
c_func
(paren
id|scr-&gt;pt.r14
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|14
)braket
)paren
suffix:semicolon
multiline_comment|/* r14 */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|scr-&gt;pt.ar_csd
comma
op_amp
id|sc-&gt;sc_ar25
comma
l_int|2
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* ar.csd &amp; ar.ssd */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|scr-&gt;pt.r2
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|2
)braket
comma
l_int|2
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r2-r3 */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|scr-&gt;pt.r16
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|16
)braket
comma
l_int|16
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r16-r31 */
)brace
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|IA64_SC_FLAG_FPH_VALID
)paren
op_ne
l_int|0
)paren
(brace
r_struct
id|ia64_psr
op_star
id|psr
op_assign
id|ia64_psr
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
suffix:semicolon
id|__copy_from_user
c_func
(paren
id|current-&gt;thread.fph
comma
op_amp
id|sc-&gt;sc_fr
(braket
l_int|32
)braket
comma
l_int|96
op_star
l_int|16
)paren
suffix:semicolon
id|psr-&gt;mfh
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* drop signal handler&squot;s fph contents... */
r_if
c_cond
(paren
id|psr-&gt;dfh
)paren
id|ia64_drop_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
r_else
(brace
multiline_comment|/* We already own the local fph, otherwise psr-&gt;dfh wouldn&squot;t be 0.  */
id|__ia64_load_fpu
c_func
(paren
id|current-&gt;thread.fph
)paren
suffix:semicolon
id|ia64_set_local_fpu_owner
c_func
(paren
id|current
)paren
suffix:semicolon
)brace
)brace
r_return
id|err
suffix:semicolon
)brace
r_int
DECL|function|copy_siginfo_to_user
id|copy_siginfo_to_user
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
c_func
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
(brace
r_if
c_cond
(paren
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
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_else
(brace
r_int
id|err
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If you change siginfo_t structure, please be sure this code is fixed&n;&t;&t; * accordingly.  It should never copy any pad contained in the structure&n;&t;&t; * to avoid security leaks, but must copy the generic 3 ints plus the&n;&t;&t; * relevant union member.&n;&t;&t; */
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
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_flags
comma
op_amp
id|to-&gt;si_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_isr
comma
op_amp
id|to-&gt;si_isr
)paren
suffix:semicolon
r_case
id|__SI_POLL
op_rshift
l_int|16
suffix:colon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_addr
comma
op_amp
id|to-&gt;si_addr
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_imm
comma
op_amp
id|to-&gt;si_imm
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|__SI_TIMER
op_rshift
l_int|16
suffix:colon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_tid
comma
op_amp
id|to-&gt;si_tid
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_overrun
comma
op_amp
id|to-&gt;si_overrun
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_ptr
comma
op_amp
id|to-&gt;si_ptr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|__SI_RT
op_rshift
l_int|16
suffix:colon
multiline_comment|/* Not generated by the kernel as of now.  */
r_case
id|__SI_MESGQ
op_rshift
l_int|16
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
id|err
op_or_assign
id|__put_user
c_func
(paren
id|from-&gt;si_ptr
comma
op_amp
id|to-&gt;si_ptr
)paren
suffix:semicolon
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
r_break
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
)brace
r_int
DECL|function|ia64_rt_sigreturn
id|ia64_rt_sigreturn
(paren
r_struct
id|sigscratch
op_star
id|scr
)paren
(brace
r_extern
r_char
id|ia64_strace_leave_kernel
comma
id|ia64_leave_kernel
suffix:semicolon
r_struct
id|sigcontext
op_star
id|sc
suffix:semicolon
r_struct
id|siginfo
id|si
suffix:semicolon
id|sigset_t
id|set
suffix:semicolon
r_int
id|retval
suffix:semicolon
id|sc
op_assign
op_amp
(paren
(paren
r_struct
id|sigframe
op_star
)paren
(paren
id|scr-&gt;pt.r12
op_plus
l_int|16
)paren
)paren
op_member_access_from_pointer
id|sc
suffix:semicolon
multiline_comment|/*&n;&t; * When we return to the previously executing context, r8 and r10 have already&n;&t; * been setup the way we want them.  Indeed, if the signal wasn&squot;t delivered while&n;&t; * in a system call, we must not touch r8 or r10 as otherwise user-level state&n;&t; * could be corrupted.&n;&t; */
id|retval
op_assign
(paren
r_int
)paren
op_amp
id|ia64_leave_kernel
suffix:semicolon
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_SYSCALL_TRACE
)paren
)paren
multiline_comment|/*&n;&t;&t; * strace expects to be notified after sigreturn returns even though the&n;&t;&t; * context to which we return may not be in the middle of a syscall.&n;&t;&t; * Thus, the return-value that strace displays for sigreturn is&n;&t;&t; * meaningless.&n;&t;&t; */
id|retval
op_assign
(paren
r_int
)paren
op_amp
id|ia64_strace_leave_kernel
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
id|sc
comma
r_sizeof
(paren
op_star
id|sc
)paren
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
r_if
c_cond
(paren
id|GET_SIGSET
c_func
(paren
op_amp
id|set
comma
op_amp
id|sc-&gt;sc_mask
)paren
)paren
r_goto
id|give_sigsegv
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
(brace
id|current-&gt;blocked
op_assign
id|set
suffix:semicolon
id|recalc_sigpending
c_func
(paren
)paren
suffix:semicolon
)brace
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
id|sc
comma
id|scr
)paren
)paren
r_goto
id|give_sigsegv
suffix:semicolon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;SIG return (%s:%d): sp=%lx ip=%lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|scr-&gt;pt.r12
comma
id|scr-&gt;pt.cr_iip
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * It is more difficult to avoid calling this function than to&n;&t; * call it and ignore errors.&n;&t; */
id|do_sigaltstack
c_func
(paren
op_amp
id|sc-&gt;sc_stack
comma
l_int|0
comma
id|scr-&gt;pt.r12
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
id|give_sigsegv
suffix:colon
id|si.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|si.si_errno
op_assign
l_int|0
suffix:semicolon
id|si.si_code
op_assign
id|SI_KERNEL
suffix:semicolon
id|si.si_pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|si.si_uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|si.si_addr
op_assign
id|sc
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGSEGV
comma
op_amp
id|si
comma
id|current
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/*&n; * This does just the minimum required setup of sigcontext.&n; * Specifically, it only installs data that is either not knowable at&n; * the user-level or that gets modified before execution in the&n; * trampoline starts.  Everything else is done at the user-level.&n; */
r_static
r_int
DECL|function|setup_sigcontext
id|setup_sigcontext
(paren
r_struct
id|sigcontext
op_star
id|sc
comma
id|sigset_t
op_star
id|mask
comma
r_struct
id|sigscratch
op_star
id|scr
)paren
(brace
r_int
r_int
id|flags
op_assign
l_int|0
comma
id|ifs
comma
id|cfm
comma
id|nat
suffix:semicolon
r_int
id|err
suffix:semicolon
id|ifs
op_assign
id|scr-&gt;pt.cr_ifs
suffix:semicolon
r_if
c_cond
(paren
id|on_sig_stack
c_func
(paren
(paren
r_int
r_int
)paren
id|sc
)paren
)paren
id|flags
op_or_assign
id|IA64_SC_FLAG_ONSTACK
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ifs
op_amp
(paren
l_int|1UL
op_lshift
l_int|63
)paren
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* if cr_ifs isn&squot;t valid, we got here through a syscall */
id|flags
op_or_assign
id|IA64_SC_FLAG_IN_SYSCALL
suffix:semicolon
id|cfm
op_assign
id|scr-&gt;ar_pfs
op_amp
(paren
(paren
l_int|1UL
op_lshift
l_int|38
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_else
id|cfm
op_assign
id|ifs
op_amp
(paren
(paren
l_int|1UL
op_lshift
l_int|38
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|ia64_flush_fph
c_func
(paren
id|current
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current-&gt;thread.flags
op_amp
id|IA64_THREAD_FPH_VALID
)paren
)paren
(brace
id|flags
op_or_assign
id|IA64_SC_FLAG_FPH_VALID
suffix:semicolon
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_fr
(braket
l_int|32
)braket
comma
id|current-&gt;thread.fph
comma
l_int|96
op_star
l_int|16
)paren
suffix:semicolon
)brace
id|nat
op_assign
id|ia64_get_scratch_nat_bits
c_func
(paren
op_amp
id|scr-&gt;pt
comma
id|scr-&gt;scratch_unat
)paren
suffix:semicolon
id|err
op_assign
id|__put_user
c_func
(paren
id|flags
comma
op_amp
id|sc-&gt;sc_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|nat
comma
op_amp
id|sc-&gt;sc_nat
)paren
suffix:semicolon
id|err
op_or_assign
id|PUT_SIGSET
c_func
(paren
id|mask
comma
op_amp
id|sc-&gt;sc_mask
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|cfm
comma
op_amp
id|sc-&gt;sc_cfm
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.cr_ipsr
op_amp
id|IA64_PSR_UM
comma
op_amp
id|sc-&gt;sc_um
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.ar_rsc
comma
op_amp
id|sc-&gt;sc_ar_rsc
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.ar_unat
comma
op_amp
id|sc-&gt;sc_ar_unat
)paren
suffix:semicolon
multiline_comment|/* ar.unat */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.ar_fpsr
comma
op_amp
id|sc-&gt;sc_ar_fpsr
)paren
suffix:semicolon
multiline_comment|/* ar.fpsr */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.ar_pfs
comma
op_amp
id|sc-&gt;sc_ar_pfs
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.pr
comma
op_amp
id|sc-&gt;sc_pr
)paren
suffix:semicolon
multiline_comment|/* predicates */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.b0
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* b0 (rp) */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.b6
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|6
)braket
)paren
suffix:semicolon
multiline_comment|/* b6 */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|1
)braket
comma
op_amp
id|scr-&gt;pt.r1
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r1 */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|8
)braket
comma
op_amp
id|scr-&gt;pt.r8
comma
l_int|4
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r8-r11 */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|12
)braket
comma
op_amp
id|scr-&gt;pt.r12
comma
l_int|2
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r12-r13 */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|15
)braket
comma
op_amp
id|scr-&gt;pt.r15
comma
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r15 */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.cr_iip
op_plus
id|ia64_psr
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
op_member_access_from_pointer
id|ri
comma
op_amp
id|sc-&gt;sc_ip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|IA64_SC_FLAG_IN_SYSCALL
)paren
(brace
multiline_comment|/* Clear scratch registers if the signal interrupted a system call. */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|sc-&gt;sc_ar_ccv
)paren
suffix:semicolon
multiline_comment|/* ar.ccv */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|7
)braket
)paren
suffix:semicolon
multiline_comment|/* b7 */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|14
)braket
)paren
suffix:semicolon
multiline_comment|/* r14 */
id|err
op_or_assign
id|__clear_user
c_func
(paren
op_amp
id|sc-&gt;sc_ar25
comma
l_int|2
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* ar.csd &amp; ar.ssd */
id|err
op_or_assign
id|__clear_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|2
)braket
comma
l_int|2
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r2-r3 */
id|err
op_or_assign
id|__clear_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|16
)braket
comma
l_int|16
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r16-r31 */
)brace
r_else
(brace
multiline_comment|/* Copy scratch regs to sigcontext if the signal didn&squot;t interrupt a syscall. */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.ar_ccv
comma
op_amp
id|sc-&gt;sc_ar_ccv
)paren
suffix:semicolon
multiline_comment|/* ar.ccv */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.b7
comma
op_amp
id|sc-&gt;sc_br
(braket
l_int|7
)braket
)paren
suffix:semicolon
multiline_comment|/* b7 */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|scr-&gt;pt.r14
comma
op_amp
id|sc-&gt;sc_gr
(braket
l_int|14
)braket
)paren
suffix:semicolon
multiline_comment|/* r14 */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|scr-&gt;pt.ar_csd
comma
op_amp
id|sc-&gt;sc_ar25
comma
l_int|2
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* ar.csd &amp; ar.ssd */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|2
)braket
comma
op_amp
id|scr-&gt;pt.r2
comma
l_int|2
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r2-r3 */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;sc_gr
(braket
l_int|16
)braket
comma
op_amp
id|scr-&gt;pt.r16
comma
l_int|16
op_star
l_int|8
)paren
suffix:semicolon
multiline_comment|/* r16-r31 */
)brace
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Check whether the register-backing store is already on the signal stack.&n; */
r_static
r_inline
r_int
DECL|function|rbs_on_sig_stack
id|rbs_on_sig_stack
(paren
r_int
r_int
id|bsp
)paren
(brace
r_return
(paren
id|bsp
op_minus
id|current-&gt;sas_ss_sp
OL
id|current-&gt;sas_ss_size
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|setup_frame
id|setup_frame
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
id|sigscratch
op_star
id|scr
)paren
(brace
r_extern
r_char
id|__kernel_sigtramp
(braket
)braket
suffix:semicolon
r_int
r_int
id|tramp_addr
comma
id|new_rbs
op_assign
l_int|0
suffix:semicolon
r_struct
id|sigframe
op_star
id|frame
suffix:semicolon
r_struct
id|siginfo
id|si
suffix:semicolon
r_int
id|err
suffix:semicolon
id|frame
op_assign
(paren
r_void
op_star
)paren
id|scr-&gt;pt.r12
suffix:semicolon
id|tramp_addr
op_assign
(paren
r_int
r_int
)paren
id|__kernel_sigtramp
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
id|sas_ss_flags
c_func
(paren
(paren
r_int
r_int
)paren
id|frame
)paren
op_eq
l_int|0
)paren
(brace
id|frame
op_assign
(paren
r_void
op_star
)paren
(paren
(paren
id|current-&gt;sas_ss_sp
op_plus
id|current-&gt;sas_ss_size
)paren
op_amp
op_complement
(paren
id|STACK_ALIGN
op_minus
l_int|1
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We need to check for the register stack being on the signal stack&n;&t;&t; * separately, because it&squot;s switched separately (memory stack is switched&n;&t;&t; * in the kernel, register stack is switched in the signal trampoline).&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|rbs_on_sig_stack
c_func
(paren
id|scr-&gt;pt.ar_bspstore
)paren
)paren
id|new_rbs
op_assign
(paren
id|current-&gt;sas_ss_sp
op_plus
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
r_sizeof
(paren
r_int
)paren
op_minus
l_int|1
)paren
suffix:semicolon
)brace
id|frame
op_assign
(paren
r_void
op_star
)paren
id|frame
op_minus
(paren
(paren
r_sizeof
(paren
op_star
id|frame
)paren
op_plus
id|STACK_ALIGN
op_minus
l_int|1
)paren
op_amp
op_complement
(paren
id|STACK_ALIGN
op_minus
l_int|1
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
op_assign
id|__put_user
c_func
(paren
id|sig
comma
op_amp
id|frame-&gt;arg0
)paren
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
id|frame-&gt;arg1
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
op_amp
id|frame-&gt;sc
comma
op_amp
id|frame-&gt;arg2
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|new_rbs
comma
op_amp
id|frame-&gt;sc.sc_rbs_base
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
id|frame-&gt;sc.sc_loadrs
)paren
suffix:semicolon
multiline_comment|/* initialize to zero */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|ka-&gt;sa.sa_handler
comma
op_amp
id|frame-&gt;handler
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
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;sas_ss_sp
comma
op_amp
id|frame-&gt;sc.sc_stack.ss_sp
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
id|frame-&gt;sc.sc_stack.ss_size
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
id|scr-&gt;pt.r12
)paren
comma
op_amp
id|frame-&gt;sc.sc_stack.ss_flags
)paren
suffix:semicolon
id|err
op_or_assign
id|setup_sigcontext
c_func
(paren
op_amp
id|frame-&gt;sc
comma
id|set
comma
id|scr
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
id|scr-&gt;pt.r12
op_assign
(paren
r_int
r_int
)paren
id|frame
op_minus
l_int|16
suffix:semicolon
multiline_comment|/* new stack pointer */
id|scr-&gt;pt.ar_fpsr
op_assign
id|FPSR_DEFAULT
suffix:semicolon
multiline_comment|/* reset fpsr for signal handler */
id|scr-&gt;pt.cr_iip
op_assign
id|tramp_addr
suffix:semicolon
id|ia64_psr
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
op_member_access_from_pointer
id|ri
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* start executing in first slot */
id|ia64_psr
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
op_member_access_from_pointer
id|be
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* force little-endian byte-order */
multiline_comment|/*&n;&t; * Force the interruption function mask to zero.  This has no effect when a&n;&t; * system-call got interrupted by a signal (since, in that case, scr-&gt;pt_cr_ifs is&n;&t; * ignored), but it has the desirable effect of making it possible to deliver a&n;&t; * signal with an incomplete register frame (which happens when a mandatory RSE&n;&t; * load faults).  Furthermore, it has no negative effect on the getting the user&squot;s&n;&t; * dirty partition preserved, because that&squot;s governed by scr-&gt;pt.loadrs.&n;&t; */
id|scr-&gt;pt.cr_ifs
op_assign
(paren
l_int|1UL
op_lshift
l_int|63
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Note: this affects only the NaT bits of the scratch regs (the ones saved in&n;&t; * pt_regs), which is exactly what we want.&n;&t; */
id|scr-&gt;scratch_unat
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* ensure NaT bits of r12 is clear */
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;SIG deliver (%s:%d): sig=%d sp=%lx ip=%lx handler=%p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|sig
comma
id|scr-&gt;pt.r12
comma
id|frame-&gt;sc.sc_ip
comma
id|frame-&gt;handler
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|1
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
id|si.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|si.si_errno
op_assign
l_int|0
suffix:semicolon
id|si.si_code
op_assign
id|SI_KERNEL
suffix:semicolon
id|si.si_pid
op_assign
id|current-&gt;pid
suffix:semicolon
id|si.si_uid
op_assign
id|current-&gt;uid
suffix:semicolon
id|si.si_addr
op_assign
id|frame
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGSEGV
comma
op_amp
id|si
comma
id|current
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|handle_signal
id|handle_signal
(paren
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
id|sigscratch
op_star
id|scr
)paren
(brace
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
(brace
multiline_comment|/* send signal to IA-32 process */
r_if
c_cond
(paren
op_logical_neg
id|ia32_setup_frame1
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
op_amp
id|scr-&gt;pt
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_else
multiline_comment|/* send signal to IA-64 process */
r_if
c_cond
(paren
op_logical_neg
id|setup_frame
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
id|scr
)paren
)paren
r_return
l_int|0
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
(brace
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
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|current-&gt;sighand-&gt;siglock
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Note that `init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t want to&n; * handle.  Thus you cannot kill init even with a SIGKILL even by mistake.&n; */
r_int
DECL|function|ia64_do_signal
id|ia64_do_signal
(paren
id|sigset_t
op_star
id|oldset
comma
r_struct
id|sigscratch
op_star
id|scr
comma
r_int
id|in_syscall
)paren
(brace
r_struct
id|k_sigaction
op_star
id|ka
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
r_int
id|restart
op_assign
id|in_syscall
suffix:semicolon
r_int
id|errno
op_assign
id|scr-&gt;pt.r8
suffix:semicolon
DECL|macro|ERR_CODE
macro_line|#&t;define ERR_CODE(c)&t;(IS_IA32_PROCESS(&amp;scr-&gt;pt) ? -(c) : (c))
multiline_comment|/*&n;&t; * In the ia64_leave_kernel code path, we want the common case to go fast, which&n;&t; * is why we may in certain cases get here from kernel mode. Just return without&n;&t; * doing anything if so.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
r_return
l_int|0
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
multiline_comment|/*&n;&t; * This only loops in the rare cases of handle_signal() failing, in which case we&n;&t; * need to push through a forced SIGSEGV.&n;&t; */
r_while
c_loop
(paren
l_int|1
)paren
(brace
r_int
id|signr
op_assign
id|get_signal_to_deliver
c_func
(paren
op_amp
id|info
comma
op_amp
id|scr-&gt;pt
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * get_signal_to_deliver() may have run a debugger (via notify_parent())&n;&t;&t; * and the debugger may have modified the state (e.g., to arrange for an&n;&t;&t; * inferior call), thus it&squot;s important to check for restarting _after_&n;&t;&t; * get_signal_to_deliver().&n;&t;&t; */
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
(brace
r_if
c_cond
(paren
id|in_syscall
)paren
(brace
r_if
c_cond
(paren
id|errno
op_ge
l_int|0
)paren
id|restart
op_assign
l_int|0
suffix:semicolon
r_else
id|errno
op_assign
op_minus
id|errno
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
r_int
)paren
id|scr-&gt;pt.r10
op_ne
op_minus
l_int|1
)paren
multiline_comment|/*&n;&t;&t;&t; * A system calls has to be restarted only if one of the error codes&n;&t;&t;&t; * ERESTARTNOHAND, ERESTARTSYS, or ERESTARTNOINTR is returned.  If r10&n;&t;&t;&t; * isn&squot;t -1 then r8 doesn&squot;t hold an error code and we don&squot;t need to&n;&t;&t;&t; * restart the syscall, so we can clear the &quot;restart&quot; flag here.&n;&t;&t;&t; */
id|restart
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|signr
op_le
l_int|0
)paren
r_break
suffix:semicolon
id|ka
op_assign
op_amp
id|current-&gt;sighand-&gt;action
(braket
id|signr
op_minus
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|restart
)paren
)paren
(brace
r_switch
c_cond
(paren
id|errno
)paren
(brace
r_case
id|ERESTART_RESTARTBLOCK
suffix:colon
r_case
id|ERESTARTNOHAND
suffix:colon
id|scr-&gt;pt.r8
op_assign
id|ERR_CODE
c_func
(paren
id|EINTR
)paren
suffix:semicolon
multiline_comment|/* note: scr-&gt;pt.r10 is already -1 */
r_break
suffix:semicolon
r_case
id|ERESTARTSYS
suffix:colon
r_if
c_cond
(paren
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTART
)paren
op_eq
l_int|0
)paren
(brace
id|scr-&gt;pt.r8
op_assign
id|ERR_CODE
c_func
(paren
id|EINTR
)paren
suffix:semicolon
multiline_comment|/* note: scr-&gt;pt.r10 is already -1 */
r_break
suffix:semicolon
)brace
r_case
id|ERESTARTNOINTR
suffix:colon
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
(brace
id|scr-&gt;pt.r8
op_assign
id|scr-&gt;pt.r1
suffix:semicolon
id|scr-&gt;pt.cr_iip
op_sub_assign
l_int|2
suffix:semicolon
)brace
r_else
id|ia64_decrement_ip
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
suffix:semicolon
id|restart
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* don&squot;t restart twice if handle_signal() fails... */
)brace
)brace
multiline_comment|/*&n;&t;&t; * Whee!  Actually deliver the signal.  If the delivery failed, we need to&n;&t;&t; * continue to iterate in this loop so we can deliver the SIGSEGV...&n;&t;&t; */
r_if
c_cond
(paren
id|handle_signal
c_func
(paren
id|signr
comma
id|ka
comma
op_amp
id|info
comma
id|oldset
comma
id|scr
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Did we come from a system call? */
r_if
c_cond
(paren
id|restart
)paren
(brace
multiline_comment|/* Restart the system call - no handlers present */
r_if
c_cond
(paren
id|errno
op_eq
id|ERESTARTNOHAND
op_logical_or
id|errno
op_eq
id|ERESTARTSYS
op_logical_or
id|errno
op_eq
id|ERESTARTNOINTR
op_logical_or
id|errno
op_eq
id|ERESTART_RESTARTBLOCK
)paren
(brace
r_if
c_cond
(paren
id|IS_IA32_PROCESS
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
)paren
(brace
id|scr-&gt;pt.r8
op_assign
id|scr-&gt;pt.r1
suffix:semicolon
id|scr-&gt;pt.cr_iip
op_sub_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|errno
op_eq
id|ERESTART_RESTARTBLOCK
)paren
id|scr-&gt;pt.r8
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* x86 version of __NR_restart_syscall */
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Note: the syscall number is in r15 which is saved in&n;&t;&t;&t;&t; * pt_regs so all we need to do here is adjust ip so that&n;&t;&t;&t;&t; * the &quot;break&quot; instruction gets re-executed.&n;&t;&t;&t;&t; */
id|ia64_decrement_ip
c_func
(paren
op_amp
id|scr-&gt;pt
)paren
suffix:semicolon
r_if
c_cond
(paren
id|errno
op_eq
id|ERESTART_RESTARTBLOCK
)paren
id|scr-&gt;pt.r15
op_assign
id|__NR_restart_syscall
suffix:semicolon
)brace
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
