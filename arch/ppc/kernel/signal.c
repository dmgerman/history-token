multiline_comment|/*&n; *  arch/ppc/kernel/signal.c&n; *&n; *  PowerPC version&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Derived from &quot;arch/i386/kernel/signal.c&quot;&n; *    Copyright (C) 1991, 1992 Linus Torvalds&n; *    1997-11-28  Modified for POSIX.1b signals by Richard Henderson&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
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
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/binfmts.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
DECL|macro|DEBUG_SIG
macro_line|#undef DEBUG_SIG
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
r_extern
r_void
id|sigreturn_exit
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
DECL|macro|GP_REGS_SIZE
mdefine_line|#define GP_REGS_SIZE&t;min(sizeof(elf_gregset_t), sizeof(struct pt_regs))
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
r_int
DECL|function|sys_sigsuspend
id|sys_sigsuspend
c_func
(paren
id|old_sigset_t
id|mask
comma
r_int
id|p2
comma
r_int
id|p3
comma
r_int
id|p4
comma
r_int
id|p6
comma
r_int
id|p7
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
id|regs-&gt;result
op_assign
op_minus
id|EINTR
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|EINTR
suffix:semicolon
id|regs-&gt;ccr
op_or_assign
l_int|0x10000000
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
id|regs
)paren
)paren
id|sigreturn_exit
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
)brace
r_int
DECL|function|sys_rt_sigsuspend
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
comma
r_int
id|p3
comma
r_int
id|p4
comma
r_int
id|p6
comma
r_int
id|p7
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
id|regs-&gt;result
op_assign
op_minus
id|EINTR
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|EINTR
suffix:semicolon
id|regs-&gt;ccr
op_or_assign
l_int|0x10000000
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
id|regs
)paren
)paren
id|sigreturn_exit
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
)brace
r_int
DECL|function|sys_sigaltstack
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
comma
r_int
id|r5
comma
r_int
id|r6
comma
r_int
id|r7
comma
r_int
id|r8
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
l_int|1
)braket
)paren
suffix:semicolon
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
(paren
id|act
ques
c_cond
op_amp
id|new_ka
suffix:colon
l_int|NULL
)paren
comma
(paren
id|oact
ques
c_cond
op_amp
id|old_ka
suffix:colon
l_int|NULL
)paren
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
multiline_comment|/*&n; * When we have signals to deliver, we set up on the&n; * user stack, going down from the original stack pointer:&n; *&t;a sigregs struct&n; *&t;a sigcontext struct&n; *&t;a gap of __SIGNAL_FRAMESIZE bytes&n; *&n; * Each of these things must be a multiple of 16 bytes in size.&n; *&n; */
DECL|struct|sigregs
r_struct
id|sigregs
(brace
DECL|member|mctx
r_struct
id|mcontext
id|mctx
suffix:semicolon
multiline_comment|/* all the register values */
multiline_comment|/* Programs using the rs6000/xcoff abi can save up to 19 gp regs&n;&t;   and 18 fp regs below sp before decrementing it. */
DECL|member|abigap
r_int
id|abigap
(braket
l_int|56
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* We use the mc_pad field for the signal return trampoline. */
DECL|macro|tramp
mdefine_line|#define tramp&t;mc_pad
multiline_comment|/*&n; *  When we have rt signals to deliver, we set up on the&n; *  user stack, going down from the original stack pointer:&n; *&t;one rt_sigframe struct (siginfo + ucontext + ABI gap)&n; *&t;a gap of __SIGNAL_FRAMESIZE+16 bytes&n; *  (the +16 is to get the siginfo and ucontext in the same&n; *  positions as in older kernels).&n; *&n; *  Each of these things must be a multiple of 16 bytes in size.&n; *&n; */
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
multiline_comment|/* Programs using the rs6000/xcoff abi can save up to 19 gp regs&n;&t;   and 18 fp regs below sp before decrementing it. */
DECL|member|abigap
r_int
id|abigap
(braket
l_int|56
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Save the current user registers on the user stack.&n; * We only save the altivec/spe registers if the process has used&n; * altivec/spe instructions at some point.&n; */
r_static
r_int
DECL|function|save_user_regs
id|save_user_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|mcontext
id|__user
op_star
id|frame
comma
r_int
id|sigret
)paren
(brace
multiline_comment|/* save general and floating-point registers */
id|CHECK_FULL_REGS
c_func
(paren
id|regs
)paren
suffix:semicolon
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
id|MSR_FP
)paren
id|giveup_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ALTIVEC
r_if
c_cond
(paren
id|current-&gt;thread.used_vr
op_logical_and
(paren
id|regs-&gt;msr
op_amp
id|MSR_VEC
)paren
)paren
id|giveup_altivec
c_func
(paren
id|current
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
macro_line|#ifdef CONFIG_SPE
r_if
c_cond
(paren
id|current-&gt;thread.used_spe
op_logical_and
(paren
id|regs-&gt;msr
op_amp
id|MSR_SPE
)paren
)paren
id|giveup_spe
c_func
(paren
id|current
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;mc_gregs
comma
id|regs
comma
id|GP_REGS_SIZE
)paren
op_logical_or
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;mc_fregs
comma
id|current-&gt;thread.fpr
comma
id|ELF_NFPREG
op_star
r_sizeof
(paren
r_float
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|current-&gt;thread.fpscr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* turn off all fp exceptions */
macro_line|#ifdef CONFIG_ALTIVEC
multiline_comment|/* save altivec registers */
r_if
c_cond
(paren
id|current-&gt;thread.used_vr
)paren
(brace
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;mc_vregs
comma
id|current-&gt;thread.vr
comma
id|ELF_NVRREG
op_star
r_sizeof
(paren
id|vector128
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* set MSR_VEC in the saved MSR value to indicate that&n;&t;&t;   frame-&gt;mc_vregs contains valid data */
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|regs-&gt;msr
op_or
id|MSR_VEC
comma
op_amp
id|frame-&gt;mc_gregs
(braket
id|PT_MSR
)braket
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* else assert((regs-&gt;msr &amp; MSR_VEC) == 0) */
multiline_comment|/* We always copy to/from vrsave, it&squot;s 0 if we don&squot;t have or don&squot;t&n;&t; * use altivec. Since VSCR only contains 32 bits saved in the least&n;&t; * significant bits of a vector, we &quot;cheat&quot; and stuff VRSAVE in the&n;&t; * most significant bits of that same vector. --BenH&n;&t; */
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|current-&gt;thread.vrsave
comma
(paren
id|u32
id|__user
op_star
)paren
op_amp
id|frame-&gt;mc_vregs
(braket
l_int|32
)braket
)paren
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
macro_line|#ifdef CONFIG_SPE
multiline_comment|/* save spe registers */
r_if
c_cond
(paren
id|current-&gt;thread.used_spe
)paren
(brace
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;mc_vregs
comma
id|current-&gt;thread.evr
comma
id|ELF_NEVRREG
op_star
r_sizeof
(paren
id|u32
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* set MSR_SPE in the saved MSR value to indicate that&n;&t;&t;   frame-&gt;mc_vregs contains valid data */
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|regs-&gt;msr
op_or
id|MSR_SPE
comma
op_amp
id|frame-&gt;mc_gregs
(braket
id|PT_MSR
)braket
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* else assert((regs-&gt;msr &amp; MSR_SPE) == 0) */
multiline_comment|/* We always copy to/from spefscr */
r_if
c_cond
(paren
id|__put_user
c_func
(paren
id|current-&gt;thread.spefscr
comma
(paren
id|u32
op_star
)paren
op_amp
id|frame-&gt;mc_vregs
op_plus
id|ELF_NEVRREG
)paren
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif /* CONFIG_SPE */
r_if
c_cond
(paren
id|sigret
)paren
(brace
multiline_comment|/* Set up the sigreturn trampoline: li r0,sigret; sc */
r_if
c_cond
(paren
id|__put_user
c_func
(paren
l_int|0x38000000UL
op_plus
id|sigret
comma
op_amp
id|frame-&gt;tramp
(braket
l_int|0
)braket
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0x44000002UL
comma
op_amp
id|frame-&gt;tramp
(braket
l_int|1
)braket
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;tramp
(braket
l_int|0
)braket
comma
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;tramp
(braket
l_int|2
)braket
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Restore the current user register values from the user stack,&n; * (except for MSR).&n; */
r_static
r_int
DECL|function|restore_user_regs
id|restore_user_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|mcontext
id|__user
op_star
id|sr
comma
r_int
id|sig
)paren
(brace
r_int
r_int
id|save_r2
suffix:semicolon
macro_line|#if defined(CONFIG_ALTIVEC) || defined(CONFIG_SPE)
r_int
r_int
id|msr
suffix:semicolon
macro_line|#endif
multiline_comment|/* backup/restore the TLS as we don&squot;t want it to be modified */
r_if
c_cond
(paren
op_logical_neg
id|sig
)paren
id|save_r2
op_assign
id|regs-&gt;gpr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* copy up to but not including MSR */
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|regs
comma
op_amp
id|sr-&gt;mc_gregs
comma
id|PT_MSR
op_star
r_sizeof
(paren
id|elf_greg_t
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* copy from orig_r3 (the word after the MSR) up to the end */
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
op_amp
id|regs-&gt;orig_gpr3
comma
op_amp
id|sr-&gt;mc_gregs
(braket
id|PT_ORIG_R3
)braket
comma
id|GP_REGS_SIZE
op_minus
id|PT_ORIG_R3
op_star
r_sizeof
(paren
id|elf_greg_t
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|sig
)paren
id|regs-&gt;gpr
(braket
l_int|2
)braket
op_assign
id|save_r2
suffix:semicolon
multiline_comment|/* force the process to reload the FP registers from&n;&t;   current-&gt;thread when it next does FP instructions */
id|regs-&gt;msr
op_and_assign
op_complement
id|MSR_FP
suffix:semicolon
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|current-&gt;thread.fpr
comma
op_amp
id|sr-&gt;mc_fregs
comma
r_sizeof
(paren
id|sr-&gt;mc_fregs
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_ALTIVEC
multiline_comment|/* force the process to reload the altivec registers from&n;&t;   current-&gt;thread when it next does altivec instructions */
id|regs-&gt;msr
op_and_assign
op_complement
id|MSR_VEC
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|__get_user
c_func
(paren
id|msr
comma
op_amp
id|sr-&gt;mc_gregs
(braket
id|PT_MSR
)braket
)paren
op_logical_and
(paren
id|msr
op_amp
id|MSR_VEC
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* restore altivec registers from the stack */
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|current-&gt;thread.vr
comma
op_amp
id|sr-&gt;mc_vregs
comma
r_sizeof
(paren
id|sr-&gt;mc_vregs
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|current-&gt;thread.used_vr
)paren
id|memset
c_func
(paren
op_amp
id|current-&gt;thread.vr
comma
l_int|0
comma
id|ELF_NVRREG
op_star
r_sizeof
(paren
id|vector128
)paren
)paren
suffix:semicolon
multiline_comment|/* Always get VRSAVE back */
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|current-&gt;thread.vrsave
comma
(paren
id|u32
id|__user
op_star
)paren
op_amp
id|sr-&gt;mc_vregs
(braket
l_int|32
)braket
)paren
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
macro_line|#ifdef CONFIG_SPE
multiline_comment|/* force the process to reload the spe registers from&n;&t;   current-&gt;thread when it next does spe instructions */
id|regs-&gt;msr
op_and_assign
op_complement
id|MSR_SPE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|__get_user
c_func
(paren
id|msr
comma
op_amp
id|sr-&gt;mc_gregs
(braket
id|PT_MSR
)braket
)paren
op_logical_and
(paren
id|msr
op_amp
id|MSR_SPE
)paren
op_ne
l_int|0
)paren
(brace
multiline_comment|/* restore spe registers from the stack */
r_if
c_cond
(paren
id|__copy_from_user
c_func
(paren
id|current-&gt;thread.evr
comma
op_amp
id|sr-&gt;mc_vregs
comma
r_sizeof
(paren
id|sr-&gt;mc_vregs
)paren
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|current-&gt;thread.used_spe
)paren
id|memset
c_func
(paren
op_amp
id|current-&gt;thread.evr
comma
l_int|0
comma
id|ELF_NEVRREG
op_star
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
multiline_comment|/* Always get SPEFSCR back */
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|current-&gt;thread.spefscr
comma
(paren
id|u32
op_star
)paren
op_amp
id|sr-&gt;mc_vregs
op_plus
id|ELF_NEVRREG
)paren
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif /* CONFIG_SPE */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Restore the user process&squot;s signal mask&n; */
r_static
r_void
DECL|function|restore_sigmask
id|restore_sigmask
c_func
(paren
id|sigset_t
op_star
id|set
)paren
(brace
id|sigdelsetmask
c_func
(paren
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
op_star
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
)brace
multiline_comment|/*&n; * Set up a signal frame for a &quot;real-time&quot; signal handler&n; * (one which gets siginfo).&n; */
r_static
r_void
DECL|function|handle_rt_signal
id|handle_rt_signal
c_func
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
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|newsp
)paren
(brace
r_struct
id|rt_sigframe
id|__user
op_star
id|rt_sf
suffix:semicolon
r_struct
id|mcontext
id|__user
op_star
id|frame
suffix:semicolon
r_int
r_int
id|origsp
op_assign
id|newsp
suffix:semicolon
multiline_comment|/* Set up Signal Frame */
multiline_comment|/* Put a Real Time Context onto stack */
id|newsp
op_sub_assign
r_sizeof
(paren
op_star
id|rt_sf
)paren
suffix:semicolon
id|rt_sf
op_assign
(paren
r_struct
id|rt_sigframe
id|__user
op_star
)paren
id|newsp
suffix:semicolon
multiline_comment|/* create a stack frame for the caller of the handler */
id|newsp
op_sub_assign
id|__SIGNAL_FRAMESIZE
op_plus
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
id|__user
op_star
)paren
id|newsp
comma
id|origsp
op_minus
id|newsp
)paren
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/* Put the siginfo &amp; fill in most of the ucontext */
r_if
c_cond
(paren
id|copy_siginfo_to_user
c_func
(paren
op_amp
id|rt_sf-&gt;info
comma
id|info
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|rt_sf-&gt;uc.uc_flags
)paren
op_logical_or
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|rt_sf-&gt;uc.uc_link
)paren
op_logical_or
id|__put_user
c_func
(paren
id|current-&gt;sas_ss_sp
comma
op_amp
id|rt_sf-&gt;uc.uc_stack.ss_sp
)paren
op_logical_or
id|__put_user
c_func
(paren
id|sas_ss_flags
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
comma
op_amp
id|rt_sf-&gt;uc.uc_stack.ss_flags
)paren
op_logical_or
id|__put_user
c_func
(paren
id|current-&gt;sas_ss_size
comma
op_amp
id|rt_sf-&gt;uc.uc_stack.ss_size
)paren
op_logical_or
id|__put_user
c_func
(paren
op_amp
id|rt_sf-&gt;uc.uc_mcontext
comma
op_amp
id|rt_sf-&gt;uc.uc_regs
)paren
op_logical_or
id|__copy_to_user
c_func
(paren
op_amp
id|rt_sf-&gt;uc.uc_sigmask
comma
id|oldset
comma
r_sizeof
(paren
op_star
id|oldset
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/* Save user registers on the stack */
id|frame
op_assign
op_amp
id|rt_sf-&gt;uc.uc_mcontext
suffix:semicolon
r_if
c_cond
(paren
id|save_user_regs
c_func
(paren
id|regs
comma
id|frame
comma
id|__NR_rt_sigreturn
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|newsp
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_assign
id|newsp
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|sig
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
op_amp
id|rt_sf-&gt;info
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|5
)braket
op_assign
(paren
r_int
r_int
)paren
op_amp
id|rt_sf-&gt;uc
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|6
)braket
op_assign
(paren
r_int
r_int
)paren
id|rt_sf
suffix:semicolon
id|regs-&gt;nip
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|regs-&gt;link
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;tramp
suffix:semicolon
id|regs-&gt;trap
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
id|badframe
suffix:colon
macro_line|#ifdef DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;badframe in handle_rt_signal, regs=%p frame=%p newsp=%lx&bslash;n&quot;
comma
id|regs
comma
id|frame
comma
id|newsp
)paren
suffix:semicolon
macro_line|#endif
id|force_sigsegv
c_func
(paren
id|sig
comma
id|current
)paren
suffix:semicolon
)brace
DECL|function|do_setcontext
r_static
r_int
id|do_setcontext
c_func
(paren
r_struct
id|ucontext
id|__user
op_star
id|ucp
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|sig
)paren
(brace
id|sigset_t
id|set
suffix:semicolon
r_struct
id|mcontext
id|__user
op_star
id|mcp
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
id|ucp-&gt;uc_sigmask
comma
r_sizeof
(paren
id|set
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|mcp
comma
op_amp
id|ucp-&gt;uc_regs
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
id|restore_sigmask
c_func
(paren
op_amp
id|set
)paren
suffix:semicolon
r_if
c_cond
(paren
id|restore_user_regs
c_func
(paren
id|regs
comma
id|mcp
comma
id|sig
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
DECL|function|sys_swapcontext
r_int
id|sys_swapcontext
c_func
(paren
r_struct
id|ucontext
id|__user
op_star
id|old_ctx
comma
r_struct
id|ucontext
id|__user
op_star
id|new_ctx
comma
r_int
id|ctx_size
comma
r_int
id|r6
comma
r_int
id|r7
comma
r_int
id|r8
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_char
id|tmp
suffix:semicolon
multiline_comment|/* Context size is for future use. Right now, we only make sure&n;&t; * we are passed something we understand&n;&t; */
r_if
c_cond
(paren
id|ctx_size
OL
r_sizeof
(paren
r_struct
id|ucontext
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|old_ctx
op_ne
l_int|NULL
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
id|old_ctx
comma
r_sizeof
(paren
op_star
id|old_ctx
)paren
)paren
op_logical_or
id|save_user_regs
c_func
(paren
id|regs
comma
op_amp
id|old_ctx-&gt;uc_mcontext
comma
l_int|0
)paren
op_logical_or
id|__copy_to_user
c_func
(paren
op_amp
id|old_ctx-&gt;uc_sigmask
comma
op_amp
id|current-&gt;blocked
comma
r_sizeof
(paren
id|sigset_t
)paren
)paren
op_logical_or
id|__put_user
c_func
(paren
op_amp
id|old_ctx-&gt;uc_mcontext
comma
op_amp
id|old_ctx-&gt;uc_regs
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_ctx
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|new_ctx
comma
r_sizeof
(paren
op_star
id|new_ctx
)paren
)paren
op_logical_or
id|__get_user
c_func
(paren
id|tmp
comma
(paren
id|u8
id|__user
op_star
)paren
id|new_ctx
)paren
op_logical_or
id|__get_user
c_func
(paren
id|tmp
comma
(paren
id|u8
id|__user
op_star
)paren
(paren
id|new_ctx
op_plus
l_int|1
)paren
op_minus
l_int|1
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/*&n;&t; * If we get a fault copying the context into the kernel&squot;s&n;&t; * image of the user&squot;s registers, we can&squot;t just return -EFAULT&n;&t; * because the user&squot;s registers will be corrupted.  For instance&n;&t; * the NIP value may have been updated but not some of the&n;&t; * other registers.  Given that we have done the verify_area&n;&t; * and successfully read the first and last bytes of the region&n;&t; * above, this should only happen in an out-of-memory situation&n;&t; * or if another thread unmaps the region containing the context.&n;&t; * We kill the task with a SIGSEGV in this situation.&n;&t; */
r_if
c_cond
(paren
id|do_setcontext
c_func
(paren
id|new_ctx
comma
id|regs
comma
l_int|0
)paren
)paren
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
id|sigreturn_exit
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* doesn&squot;t actually return back to here */
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sys_rt_sigreturn
r_int
id|sys_rt_sigreturn
c_func
(paren
r_int
id|r3
comma
r_int
id|r4
comma
r_int
id|r5
comma
r_int
id|r6
comma
r_int
id|r7
comma
r_int
id|r8
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
id|rt_sf
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
id|rt_sf
op_assign
(paren
r_struct
id|rt_sigframe
id|__user
op_star
)paren
(paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_plus
id|__SIGNAL_FRAMESIZE
op_plus
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|rt_sf
comma
r_sizeof
(paren
r_struct
id|rt_sigframe
)paren
)paren
)paren
r_goto
id|bad
suffix:semicolon
r_if
c_cond
(paren
id|do_setcontext
c_func
(paren
op_amp
id|rt_sf-&gt;uc
comma
id|regs
comma
l_int|1
)paren
)paren
r_goto
id|bad
suffix:semicolon
multiline_comment|/*&n;&t; * It&squot;s not clear whether or why it is desirable to save the&n;&t; * sigaltstack setting on signal delivery and restore it on&n;&t; * signal return.  But other architectures do this and we have&n;&t; * always done it up until now so it is probably better not to&n;&t; * change it.  -- paulus&n;&t; */
id|do_sigaltstack
c_func
(paren
op_amp
id|rt_sf-&gt;uc.uc_stack
comma
l_int|NULL
comma
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|sigreturn_exit
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* doesn&squot;t return here */
r_return
l_int|0
suffix:semicolon
id|bad
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
comma
r_int
r_int
id|newsp
)paren
(brace
r_struct
id|sigcontext
id|__user
op_star
id|sc
suffix:semicolon
r_struct
id|sigregs
id|__user
op_star
id|frame
suffix:semicolon
r_int
r_int
id|origsp
op_assign
id|newsp
suffix:semicolon
multiline_comment|/* Set up Signal Frame */
id|newsp
op_sub_assign
r_sizeof
(paren
r_struct
id|sigregs
)paren
suffix:semicolon
id|frame
op_assign
(paren
r_struct
id|sigregs
id|__user
op_star
)paren
id|newsp
suffix:semicolon
multiline_comment|/* Put a sigcontext on the stack */
id|newsp
op_sub_assign
r_sizeof
(paren
op_star
id|sc
)paren
suffix:semicolon
id|sc
op_assign
(paren
r_struct
id|sigcontext
id|__user
op_star
)paren
id|newsp
suffix:semicolon
multiline_comment|/* create a stack frame for the caller of the handler */
id|newsp
op_sub_assign
id|__SIGNAL_FRAMESIZE
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
(paren
r_void
id|__user
op_star
)paren
id|newsp
comma
id|origsp
op_minus
id|newsp
)paren
)paren
r_goto
id|badframe
suffix:semicolon
macro_line|#if _NSIG != 64
macro_line|#error &quot;Please adjust handle_signal()&quot;
macro_line|#endif
r_if
c_cond
(paren
id|__put_user
c_func
(paren
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
comma
op_amp
id|sc-&gt;handler
)paren
op_logical_or
id|__put_user
c_func
(paren
id|oldset-&gt;sig
(braket
l_int|0
)braket
comma
op_amp
id|sc-&gt;oldmask
)paren
op_logical_or
id|__put_user
c_func
(paren
id|oldset-&gt;sig
(braket
l_int|1
)braket
comma
op_amp
id|sc-&gt;_unused
(braket
l_int|3
)braket
)paren
op_logical_or
id|__put_user
c_func
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
id|frame
comma
op_amp
id|sc-&gt;regs
)paren
op_logical_or
id|__put_user
c_func
(paren
id|sig
comma
op_amp
id|sc-&gt;signal
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_if
c_cond
(paren
id|save_user_regs
c_func
(paren
id|regs
comma
op_amp
id|frame-&gt;mctx
comma
id|__NR_sigreturn
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_if
c_cond
(paren
id|put_user
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|newsp
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_assign
id|newsp
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|sig
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
id|sc
suffix:semicolon
id|regs-&gt;nip
op_assign
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
id|regs-&gt;link
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;mctx.tramp
suffix:semicolon
id|regs-&gt;trap
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
id|badframe
suffix:colon
macro_line|#ifdef DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;badframe in handle_signal, regs=%p frame=%p newsp=%lx&bslash;n&quot;
comma
id|regs
comma
id|frame
comma
id|newsp
)paren
suffix:semicolon
macro_line|#endif
id|force_sigsegv
c_func
(paren
id|sig
comma
id|current
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Do a signal return; undo the signal stack.&n; */
DECL|function|sys_sigreturn
r_int
id|sys_sigreturn
c_func
(paren
r_int
id|r3
comma
r_int
id|r4
comma
r_int
id|r5
comma
r_int
id|r6
comma
r_int
id|r7
comma
r_int
id|r8
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|sigcontext
id|__user
op_star
id|sc
suffix:semicolon
r_struct
id|sigcontext
id|sigctx
suffix:semicolon
r_struct
id|mcontext
id|__user
op_star
id|sr
suffix:semicolon
id|sigset_t
id|set
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
id|sc
op_assign
(paren
r_struct
id|sigcontext
id|__user
op_star
)paren
(paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_plus
id|__SIGNAL_FRAMESIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
op_amp
id|sigctx
comma
id|sc
comma
r_sizeof
(paren
id|sigctx
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|set.sig
(braket
l_int|0
)braket
op_assign
id|sigctx.oldmask
suffix:semicolon
id|set.sig
(braket
l_int|1
)braket
op_assign
id|sigctx._unused
(braket
l_int|3
)braket
suffix:semicolon
id|restore_sigmask
c_func
(paren
op_amp
id|set
)paren
suffix:semicolon
id|sr
op_assign
(paren
r_struct
id|mcontext
id|__user
op_star
)paren
id|sigctx.regs
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|sr
comma
r_sizeof
(paren
op_star
id|sr
)paren
)paren
op_logical_or
id|restore_user_regs
c_func
(paren
id|regs
comma
id|sr
comma
l_int|1
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|sigreturn_exit
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* doesn&squot;t return */
r_return
l_int|0
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
multiline_comment|/*&n; * Note that &squot;init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t&n; * want to handle. Thus you cannot kill init even with a SIGKILL even by&n; * mistake.&n; */
DECL|function|do_signal
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
id|siginfo_t
id|info
suffix:semicolon
r_struct
id|k_sigaction
op_star
id|ka
suffix:semicolon
r_int
r_int
id|frame
comma
id|newsp
suffix:semicolon
r_int
id|signr
comma
id|ret
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
id|newsp
op_assign
id|frame
op_assign
l_int|0
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
comma
l_int|NULL
)paren
suffix:semicolon
id|ka
op_assign
(paren
id|signr
op_eq
l_int|0
)paren
ques
c_cond
l_int|NULL
suffix:colon
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
id|TRAP
c_func
(paren
id|regs
)paren
op_eq
l_int|0x0C00
multiline_comment|/* System Call! */
op_logical_and
id|regs-&gt;ccr
op_amp
l_int|0x10000000
multiline_comment|/* error signalled */
op_logical_and
(paren
(paren
id|ret
op_assign
id|regs-&gt;gpr
(braket
l_int|3
)braket
)paren
op_eq
id|ERESTARTSYS
op_logical_or
id|ret
op_eq
id|ERESTARTNOHAND
op_logical_or
id|ret
op_eq
id|ERESTARTNOINTR
op_logical_or
id|ret
op_eq
id|ERESTART_RESTARTBLOCK
)paren
)paren
(brace
r_if
c_cond
(paren
id|signr
OG
l_int|0
op_logical_and
(paren
id|ret
op_eq
id|ERESTARTNOHAND
op_logical_or
id|ret
op_eq
id|ERESTART_RESTARTBLOCK
op_logical_or
(paren
id|ret
op_eq
id|ERESTARTSYS
op_logical_and
op_logical_neg
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_RESTART
)paren
)paren
)paren
)paren
(brace
multiline_comment|/* make the system call return an EINTR error */
id|regs-&gt;result
op_assign
op_minus
id|EINTR
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|EINTR
suffix:semicolon
multiline_comment|/* note that the cr0.SO bit is already set */
)brace
r_else
(brace
id|regs-&gt;nip
op_sub_assign
l_int|4
suffix:semicolon
multiline_comment|/* Back up &amp; retry system call */
id|regs-&gt;result
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;trap
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_eq
id|ERESTART_RESTARTBLOCK
)paren
id|regs-&gt;gpr
(braket
l_int|0
)braket
op_assign
id|__NR_restart_syscall
suffix:semicolon
r_else
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|regs-&gt;orig_gpr3
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|signr
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* no signals delivered */
r_if
c_cond
(paren
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_ONSTACK
)paren
op_logical_and
id|current-&gt;sas_ss_size
op_logical_and
op_logical_neg
id|on_sig_stack
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
)paren
id|newsp
op_assign
id|current-&gt;sas_ss_sp
op_plus
id|current-&gt;sas_ss_size
suffix:semicolon
r_else
id|newsp
op_assign
id|regs-&gt;gpr
(braket
l_int|1
)braket
suffix:semicolon
id|newsp
op_and_assign
op_complement
l_int|0xfUL
suffix:semicolon
multiline_comment|/* Whee!  Actually deliver the signal.  */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_SIGINFO
)paren
id|handle_rt_signal
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
id|regs
comma
id|newsp
)paren
suffix:semicolon
r_else
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
id|regs
comma
id|newsp
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
r_return
l_int|1
suffix:semicolon
)brace
eof
