multiline_comment|/*&n; *  linux/arch/ppc64/kernel/signal.c&n; *&n; *  PowerPC version &n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Derived from &quot;arch/i386/kernel/signal.c&quot;&n; *    Copyright (C) 1991, 1992 Linus Torvalds&n; *    1997-11-28  Modified for POSIX.1b signals by Richard Henderson&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/wait.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;asm/ppc32.h&gt;
macro_line|#include &lt;asm/sigcontext.h&gt;
macro_line|#include &lt;asm/ucontext.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
DECL|macro|DEBUG_SIG
mdefine_line|#define DEBUG_SIG 0
DECL|macro|_BLOCKABLE
mdefine_line|#define _BLOCKABLE (~(sigmask(SIGKILL) | sigmask(SIGSTOP)))
macro_line|#ifndef MIN
DECL|macro|MIN
mdefine_line|#define MIN(a,b) (((a) &lt; (b)) ? (a) : (b))
macro_line|#endif
DECL|macro|GP_REGS_SIZE
mdefine_line|#define GP_REGS_SIZE&t;MIN(sizeof(elf_gregset_t), sizeof(struct pt_regs))
DECL|macro|FP_REGS_SIZE
mdefine_line|#define FP_REGS_SIZE&t;sizeof(elf_fpregset_t)
DECL|macro|TRAMP_TRACEBACK
mdefine_line|#define TRAMP_TRACEBACK&t;3
DECL|macro|TRAMP_SIZE
mdefine_line|#define TRAMP_SIZE&t;6
multiline_comment|/*&n; * When we have signals to deliver, we set up on the user stack,&n; * going down from the original stack pointer:&n; *&t;1) a rt_sigframe struct which contains the ucontext&t;&n; *&t;2) a gap of __SIGNAL_FRAMESIZE bytes which acts as a dummy caller&n; *&t;   frame for the signal handler.&n; */
DECL|struct|rt_sigframe
r_struct
id|rt_sigframe
(brace
multiline_comment|/* sys_rt_sigreturn requires the ucontext be the first field */
DECL|member|uc
r_struct
id|ucontext
id|uc
suffix:semicolon
DECL|member|_unused
r_int
r_int
id|_unused
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|tramp
r_int
r_int
id|tramp
(braket
id|TRAMP_SIZE
)braket
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
multiline_comment|/* 64 bit ABI allows for 288 bytes below sp before decrementing it. */
DECL|member|abigap
r_char
id|abigap
(braket
l_int|288
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Atomically swap in the new signal mask, and wait for a signal.&n; */
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
r_return
id|regs-&gt;gpr
(braket
l_int|3
)braket
suffix:semicolon
)brace
)brace
DECL|function|sys_sigaltstack
r_int
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
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_int
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
multiline_comment|/*&n; * Set up the sigcontext for the signal frame.&n; */
DECL|function|setup_sigcontext
r_static
r_int
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
id|signr
comma
id|sigset_t
op_star
id|set
comma
r_int
r_int
id|handler
)paren
(brace
multiline_comment|/* When CONFIG_ALTIVEC is set, we _always_ setup v_regs even if the&n;&t; * process never used altivec yet (MSR_VEC is zero in pt_regs of&n;&t; * the context). This is very important because we must ensure we&n;&t; * don&squot;t lose the VRSAVE content that may have been set prior to&n;&t; * the process doing its first vector operation&n;&t; * Userland shall check AT_HWCAP to know wether it can rely on the&n;&t; * v_regs pointer or not&n;&t; */
macro_line|#ifdef CONFIG_ALTIVEC
id|elf_vrreg_t
op_star
id|v_regs
op_assign
(paren
id|elf_vrreg_t
op_star
)paren
(paren
(paren
(paren
r_int
r_int
)paren
id|sc-&gt;vmx_reserve
)paren
op_amp
op_complement
l_int|0xful
)paren
suffix:semicolon
macro_line|#endif
r_int
id|err
op_assign
l_int|0
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
multiline_comment|/* Make sure signal doesn&squot;t get spurrious FP exceptions */
id|current-&gt;thread.fpscr
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_ALTIVEC
id|err
op_or_assign
id|__put_user
c_func
(paren
id|v_regs
comma
op_amp
id|sc-&gt;v_regs
)paren
suffix:semicolon
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
id|regs-&gt;msr
op_amp
id|MSR_VEC
)paren
id|giveup_altivec
c_func
(paren
id|current
)paren
suffix:semicolon
multiline_comment|/* Copy 33 vec registers (vr0..31 and vscr) to the stack */
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
id|v_regs
comma
id|current-&gt;thread.vr
comma
l_int|33
op_star
r_sizeof
(paren
id|vector128
)paren
)paren
suffix:semicolon
multiline_comment|/* set MSR_VEC in the MSR value in the frame to indicate that sc-&gt;v_reg)&n;&t;&t; * contains valid data.&n;&t;&t; */
id|regs-&gt;msr
op_or_assign
id|MSR_VEC
suffix:semicolon
)brace
multiline_comment|/* We always copy to/from vrsave, it&squot;s 0 if we don&squot;t have or don&squot;t&n;&t; * use altivec.&n;&t; */
id|err
op_or_assign
id|__put_user
c_func
(paren
id|current-&gt;thread.vrsave
comma
(paren
id|u32
op_star
)paren
op_amp
id|v_regs
(braket
l_int|33
)braket
)paren
suffix:semicolon
macro_line|#else /* CONFIG_ALTIVEC */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|sc-&gt;v_regs
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
id|err
op_or_assign
id|__put_user
c_func
(paren
op_amp
id|sc-&gt;gp_regs
comma
op_amp
id|sc-&gt;regs
)paren
suffix:semicolon
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;gp_regs
comma
id|regs
comma
id|GP_REGS_SIZE
)paren
suffix:semicolon
id|err
op_or_assign
id|__copy_to_user
c_func
(paren
op_amp
id|sc-&gt;fp_regs
comma
op_amp
id|current-&gt;thread.fpr
comma
id|FP_REGS_SIZE
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|signr
comma
op_amp
id|sc-&gt;signal
)paren
suffix:semicolon
id|err
op_or_assign
id|__put_user
c_func
(paren
id|handler
comma
op_amp
id|sc-&gt;handler
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
op_ne
l_int|NULL
)paren
id|err
op_or_assign
id|__put_user
c_func
(paren
id|set-&gt;sig
(braket
l_int|0
)braket
comma
op_amp
id|sc-&gt;oldmask
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Restore the sigcontext from the signal frame.&n; */
DECL|function|restore_sigcontext
r_static
r_int
id|restore_sigcontext
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|sigset_t
op_star
id|set
comma
r_int
id|sig
comma
r_struct
id|sigcontext
op_star
id|sc
)paren
(brace
macro_line|#ifdef CONFIG_ALTIVEC
id|elf_vrreg_t
op_star
id|v_regs
suffix:semicolon
macro_line|#endif
r_int
r_int
id|err
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|save_r13
suffix:semicolon
id|elf_greg_t
op_star
id|gregs
op_assign
(paren
id|elf_greg_t
op_star
)paren
id|regs
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* If this is not a signal return, we preserve the TLS in r13 */
r_if
c_cond
(paren
op_logical_neg
id|sig
)paren
id|save_r13
op_assign
id|regs-&gt;gpr
(braket
l_int|13
)braket
suffix:semicolon
multiline_comment|/* copy everything before MSR */
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
id|regs
comma
op_amp
id|sc-&gt;gp_regs
comma
id|PT_MSR
op_star
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
multiline_comment|/* skip MSR and SOFTE */
r_for
c_loop
(paren
id|i
op_assign
id|PT_MSR
op_plus
l_int|1
suffix:semicolon
id|i
op_le
id|PT_RESULT
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
id|PT_SOFTE
)paren
r_continue
suffix:semicolon
id|err
op_or_assign
id|__get_user
c_func
(paren
id|gregs
(braket
id|i
)braket
comma
op_amp
id|sc-&gt;gp_regs
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|sig
)paren
id|regs-&gt;gpr
(braket
l_int|13
)braket
op_assign
id|save_r13
suffix:semicolon
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
op_amp
id|current-&gt;thread.fpr
comma
op_amp
id|sc-&gt;fp_regs
comma
id|FP_REGS_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|set
op_ne
l_int|NULL
)paren
id|err
op_or_assign
id|__get_user
c_func
(paren
id|set-&gt;sig
(braket
l_int|0
)braket
comma
op_amp
id|sc-&gt;oldmask
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ALTIVEC
id|err
op_or_assign
id|__get_user
c_func
(paren
id|v_regs
comma
op_amp
id|sc-&gt;v_regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
id|err
suffix:semicolon
multiline_comment|/* Copy 33 vec registers (vr0..31 and vscr) from the stack */
r_if
c_cond
(paren
id|v_regs
op_ne
l_int|0
op_logical_and
(paren
id|regs-&gt;msr
op_amp
id|MSR_VEC
)paren
op_ne
l_int|0
)paren
id|err
op_or_assign
id|__copy_from_user
c_func
(paren
id|current-&gt;thread.vr
comma
id|v_regs
comma
l_int|33
op_star
r_sizeof
(paren
id|vector128
)paren
)paren
suffix:semicolon
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
l_int|33
)paren
suffix:semicolon
multiline_comment|/* Always get VRSAVE back */
r_if
c_cond
(paren
id|v_regs
op_ne
l_int|0
)paren
id|err
op_or_assign
id|__get_user
c_func
(paren
id|current-&gt;thread.vrsave
comma
(paren
id|u32
op_star
)paren
op_amp
id|v_regs
(braket
l_int|33
)braket
)paren
suffix:semicolon
r_else
id|current-&gt;thread.vrsave
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
multiline_comment|/* Force reload of FP/VEC */
id|regs-&gt;msr
op_and_assign
op_complement
(paren
id|MSR_FP
op_or
id|MSR_FE0
op_or
id|MSR_FE1
op_or
id|MSR_VEC
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Allocate space for the signal frame&n; */
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
id|newsp
suffix:semicolon
multiline_comment|/* Default to using normal stack */
id|newsp
op_assign
id|regs-&gt;gpr
(braket
l_int|1
)braket
suffix:semicolon
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
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
)paren
id|newsp
op_assign
(paren
id|current-&gt;sas_ss_sp
op_plus
id|current-&gt;sas_ss_size
)paren
suffix:semicolon
)brace
r_return
(paren
r_void
op_star
)paren
(paren
(paren
id|newsp
op_minus
id|frame_size
)paren
op_amp
op_minus
l_int|8ul
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Setup the trampoline code on the stack&n; */
DECL|function|setup_trampoline
r_static
r_int
id|setup_trampoline
c_func
(paren
r_int
r_int
id|syscall
comma
r_int
r_int
op_star
id|tramp
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|err
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* addi r1, r1, __SIGNAL_FRAMESIZE  # Pop the dummy stackframe */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x38210000UL
op_or
(paren
id|__SIGNAL_FRAMESIZE
op_amp
l_int|0xffff
)paren
comma
op_amp
id|tramp
(braket
l_int|0
)braket
)paren
suffix:semicolon
multiline_comment|/* li r0, __NR_[rt_]sigreturn| */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x38000000UL
op_or
(paren
id|syscall
op_amp
l_int|0xffff
)paren
comma
op_amp
id|tramp
(braket
l_int|1
)braket
)paren
suffix:semicolon
multiline_comment|/* sc */
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0x44000002UL
comma
op_amp
id|tramp
(braket
l_int|2
)braket
)paren
suffix:semicolon
multiline_comment|/* Minimal traceback info */
r_for
c_loop
(paren
id|i
op_assign
id|TRAMP_TRACEBACK
suffix:semicolon
id|i
OL
id|TRAMP_SIZE
suffix:semicolon
id|i
op_increment
)paren
id|err
op_or_assign
id|__put_user
c_func
(paren
l_int|0
comma
op_amp
id|tramp
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|err
)paren
id|flush_icache_range
c_func
(paren
(paren
r_int
r_int
)paren
op_amp
id|tramp
(braket
l_int|0
)braket
comma
(paren
r_int
r_int
)paren
op_amp
id|tramp
(braket
id|TRAMP_SIZE
)braket
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
multiline_comment|/*&n; * Restore the user process&squot;s signal mask (also used by signal32.c)&n; */
DECL|function|restore_sigmask
r_void
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
multiline_comment|/*&n; * Handle {get,set,swap}_context operations&n; */
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
id|sigset_t
id|set
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
id|setup_sigcontext
c_func
(paren
op_amp
id|old_ctx-&gt;uc_mcontext
comma
id|regs
comma
l_int|0
comma
l_int|NULL
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
id|__copy_from_user
c_func
(paren
op_amp
id|set
comma
op_amp
id|new_ctx-&gt;uc_sigmask
comma
r_sizeof
(paren
id|set
)paren
)paren
)paren
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
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
id|restore_sigcontext
c_func
(paren
id|regs
comma
l_int|NULL
comma
l_int|0
comma
op_amp
id|new_ctx-&gt;uc_mcontext
)paren
)paren
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
multiline_comment|/* This returns like rt_sigreturn */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Do a signal return; undo the signal stack.&n; */
DECL|function|sys_rt_sigreturn
r_int
id|sys_rt_sigreturn
c_func
(paren
r_int
r_int
id|r3
comma
r_int
r_int
id|r4
comma
r_int
r_int
id|r5
comma
r_int
r_int
id|r6
comma
r_int
r_int
id|r7
comma
r_int
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
id|ucontext
op_star
id|uc
op_assign
(paren
r_struct
id|ucontext
op_star
)paren
id|regs-&gt;gpr
(braket
l_int|1
)braket
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
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_READ
comma
id|uc
comma
r_sizeof
(paren
op_star
id|uc
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
id|uc-&gt;uc_sigmask
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
id|restore_sigcontext
c_func
(paren
id|regs
comma
l_int|NULL
comma
l_int|1
comma
op_amp
id|uc-&gt;uc_mcontext
)paren
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/* do_sigaltstack expects a __user pointer and won&squot;t modify&n;&t; * what&squot;s in there anyway&n;&t; */
id|do_sigaltstack
c_func
(paren
op_amp
id|uc-&gt;uc_stack
comma
l_int|NULL
comma
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_return
id|regs-&gt;result
suffix:semicolon
id|badframe
suffix:colon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;badframe in sys_rt_sigreturn, regs=%p uc=%p &amp;uc-&gt;uc_mcontext=%p&bslash;n&quot;
comma
id|regs
comma
id|uc
comma
op_amp
id|uc-&gt;uc_mcontext
)paren
suffix:semicolon
macro_line|#endif
id|do_exit
c_func
(paren
id|SIGSEGV
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
id|set
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* Handler is *really* a pointer to the function descriptor for&n;&t; * the signal routine.  The first entry in the function&n;&t; * descriptor is the entry address of signal and the second&n;&t; * entry is the TOC value we need to use.&n;&t; */
id|func_descr_t
op_star
id|funct_desc_ptr
suffix:semicolon
r_struct
id|rt_sigframe
op_star
id|frame
suffix:semicolon
r_int
r_int
id|newsp
op_assign
l_int|0
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
id|verify_area
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
id|badframe
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
id|badframe
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
l_int|1
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
id|signr
comma
l_int|NULL
comma
(paren
r_int
r_int
)paren
id|ka-&gt;sa.sa_handler
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
id|badframe
suffix:semicolon
multiline_comment|/* Set up to return from userspace. */
id|err
op_or_assign
id|setup_trampoline
c_func
(paren
id|__NR_rt_sigreturn
comma
op_amp
id|frame-&gt;tramp
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
id|badframe
suffix:semicolon
id|funct_desc_ptr
op_assign
(paren
id|func_descr_t
op_star
)paren
id|ka-&gt;sa.sa_handler
suffix:semicolon
multiline_comment|/* Allocate a dummy caller frame for the signal handler. */
id|newsp
op_assign
(paren
r_int
r_int
)paren
id|frame
op_minus
id|__SIGNAL_FRAMESIZE
suffix:semicolon
id|err
op_or_assign
id|put_user
c_func
(paren
l_int|0
comma
(paren
r_int
r_int
op_star
)paren
id|newsp
)paren
suffix:semicolon
multiline_comment|/* Set up &quot;regs&quot; so we &quot;return&quot; to the signal handler. */
id|err
op_or_assign
id|get_user
c_func
(paren
id|regs-&gt;nip
comma
op_amp
id|funct_desc_ptr-&gt;entry
)paren
suffix:semicolon
id|regs-&gt;link
op_assign
(paren
r_int
r_int
)paren
op_amp
id|frame-&gt;tramp
(braket
l_int|0
)braket
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_assign
id|newsp
suffix:semicolon
id|err
op_or_assign
id|get_user
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|2
)braket
comma
op_amp
id|funct_desc_ptr-&gt;toc
)paren
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|signr
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
op_or_assign
id|get_user
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|4
)braket
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|frame-&gt;pinfo
)paren
suffix:semicolon
id|err
op_or_assign
id|get_user
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|5
)braket
comma
(paren
r_int
r_int
op_star
)paren
op_amp
id|frame-&gt;puc
)paren
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
id|frame
suffix:semicolon
)brace
r_else
(brace
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
id|frame-&gt;uc.uc_mcontext
suffix:semicolon
)brace
r_if
c_cond
(paren
id|err
)paren
r_goto
id|badframe
suffix:semicolon
r_return
suffix:semicolon
id|badframe
suffix:colon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;badframe in setup_rt_frame, regs=%p frame=%p newsp=%lx&bslash;n&quot;
comma
id|regs
comma
id|frame
comma
id|newsp
)paren
suffix:semicolon
macro_line|#endif
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
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
multiline_comment|/* Set up Signal Frame */
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
r_return
suffix:semicolon
)brace
DECL|function|syscall_restart
r_static
r_inline
r_void
id|syscall_restart
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|k_sigaction
op_star
id|ka
)paren
(brace
r_switch
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;result
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
multiline_comment|/* ERESTARTNOHAND means that the syscall should only be&n;&t;&t; * restarted if there was no handler for the signal, and since&n;&t;&t; * we only get here if there is a handler, we dont restart.&n;&t;&t; */
id|regs-&gt;result
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
multiline_comment|/* ERESTARTSYS means to restart the syscall if there is no&n;&t;&t; * handler or the handler was registered with SA_RESTART&n;&t;&t; */
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
id|regs-&gt;result
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
multiline_comment|/* ERESTARTNOINTR means that the syscall should be&n;&t;&t; * called again after the signal handler returns.&n;&t;&t; */
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|regs-&gt;orig_gpr3
suffix:semicolon
id|regs-&gt;nip
op_sub_assign
l_int|4
suffix:semicolon
id|regs-&gt;result
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
)brace
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
r_int
id|signr
suffix:semicolon
multiline_comment|/*&n;&t; * If the current thread is 32 bit - invoke the&n;&t; * 32 bit signal handling code&n;&t; */
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
r_return
id|do_signal32
c_func
(paren
id|oldset
comma
id|regs
)paren
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
r_struct
id|k_sigaction
op_star
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
multiline_comment|/* Whee!  Actually deliver the signal.  */
r_if
c_cond
(paren
id|regs-&gt;trap
op_eq
l_int|0x0C00
)paren
id|syscall_restart
c_func
(paren
id|regs
comma
id|ka
)paren
suffix:semicolon
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
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|regs-&gt;trap
op_eq
l_int|0x0C00
)paren
(brace
multiline_comment|/* System Call! */
r_if
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;result
op_eq
op_minus
id|ERESTARTNOHAND
op_logical_or
(paren
r_int
)paren
id|regs-&gt;result
op_eq
op_minus
id|ERESTARTSYS
op_logical_or
(paren
r_int
)paren
id|regs-&gt;result
op_eq
op_minus
id|ERESTARTNOINTR
)paren
(brace
id|regs-&gt;gpr
(braket
l_int|3
)braket
op_assign
id|regs-&gt;orig_gpr3
suffix:semicolon
id|regs-&gt;nip
op_sub_assign
l_int|4
suffix:semicolon
multiline_comment|/* Back up &amp; retry system call */
id|regs-&gt;result
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
r_int
)paren
id|regs-&gt;result
op_eq
op_minus
id|ERESTART_RESTARTBLOCK
)paren
(brace
id|regs-&gt;gpr
(braket
l_int|0
)braket
op_assign
id|__NR_restart_syscall
suffix:semicolon
id|regs-&gt;nip
op_sub_assign
l_int|4
suffix:semicolon
id|regs-&gt;result
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
