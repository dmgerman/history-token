multiline_comment|/*&n; *  linux/arch/ppc64/kernel/signal.c&n; *&n; *  PowerPC version &n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  Derived from &quot;arch/i386/kernel/signal.c&quot;&n; *    Copyright (C) 1991, 1992 Linus Torvalds&n; *    1997-11-28  Modified for POSIX.1b signals by Richard Henderson&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
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
multiline_comment|/* &n; * These are the flags in the MSR that the user is allowed to change&n; * by modifying the saved value of the MSR on the stack.  SE and BE&n; * should not be in this list since gdb may want to change these.  I.e,&n; * you should be able to step out of a signal handler to see what&n; * instruction executes next after the signal handler completes.&n; * Alternately, if you stepped into a signal handler, you should be&n; * able to continue &squot;til the next breakpoint from within the signal&n; * handler, even if the handler returns.&n; */
macro_line|#if 0
mdefine_line|#define MSR_USERCHANGE&t;(MSR_FE0 | MSR_FE1)
macro_line|#else
multiline_comment|/*&n; * glibc tries to set FE0/FE1 via a signal handler. Since it only ever&n; * sets both bits and this is the default setting we now disable this&n; * behaviour. This is done to insure the new prctl which alters FE0/FE1 does&n; * not get overriden by glibc. Setting and clearing FE0/FE1 via signal&n; * handler has always been bogus since load_up_fpu used to set FE0/FE1&n; * unconditionally.&n; */
DECL|macro|MSR_USERCHANGE
mdefine_line|#define MSR_USERCHANGE&t;0
macro_line|#endif
multiline_comment|/*&n; * When we have signals to deliver, we set up on the&n; * user stack, going down from the original stack pointer:&n; *&t;a sigregs struct&n; *&t;one or more sigcontext structs with&n; *&t;a gap of __SIGNAL_FRAMESIZE bytes&n; *&n; * Each of these things must be a multiple of 16 bytes in size.&n; *&n; */
DECL|struct|sigregs
r_struct
id|sigregs
(brace
DECL|member|gp_regs
id|elf_gregset_t
id|gp_regs
suffix:semicolon
DECL|member|fp_regs
r_float
id|fp_regs
(braket
id|ELF_NFPREG
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
multiline_comment|/* 64 bit API allows for 288 bytes below sp before &n;&t;   decrementing it. */
DECL|member|abigap
r_int
id|abigap
(braket
l_int|72
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|rt_sigframe
r_struct
id|rt_sigframe
(brace
DECL|member|_unused
r_int
r_int
id|_unused
(braket
l_int|2
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
DECL|member|uc
r_struct
id|ucontext
id|uc
suffix:semicolon
)brace
suffix:semicolon
r_extern
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
DECL|function|sys_sigsuspend
r_int
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
multiline_comment|/*&n;&t;&t;&t; * If a signal handler needs to be called,&n;&t;&t;&t; * do_signal() has set R3 to the signal number (the&n;&t;&t;&t; * first argument of the signal handler), so don&squot;t&n;&t;&t;&t; * overwrite that with EINTR !&n;&t;&t;&t; * In the other cases, do_signal() doesn&squot;t touch &n;&t;&t;&t; * R3, so it&squot;s still set to -EINTR (see above).&n;&t;&t;&t; */
r_return
id|regs-&gt;gpr
(braket
l_int|3
)braket
suffix:semicolon
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
DECL|function|sys_sigaction
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
multiline_comment|/*&n; *  When we have rt signals to deliver, we set up on the&n; *  user stack, going down from the original stack pointer:&n; *&t;   a sigregs struct&n; *&t;   one rt_sigframe struct (siginfo + ucontext)&n; *&t;   a gap of __SIGNAL_FRAMESIZE bytes&n; *&n; *  Each of these things must be a multiple of 16 bytes in size.&n; *&n; */
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
id|rt_sigframe
op_star
id|rt_sf
suffix:semicolon
r_struct
id|sigcontext
id|sigctx
suffix:semicolon
r_struct
id|sigregs
op_star
id|sr
suffix:semicolon
id|elf_gregset_t
id|saved_regs
suffix:semicolon
multiline_comment|/* an array of ELF_NGREG unsigned longs */
id|sigset_t
id|set
suffix:semicolon
id|stack_t
id|st
suffix:semicolon
id|rt_sf
op_assign
(paren
r_struct
id|rt_sigframe
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
op_amp
id|rt_sf-&gt;uc.uc_mcontext
comma
r_sizeof
(paren
id|sigctx
)paren
)paren
op_logical_or
id|copy_from_user
c_func
(paren
op_amp
id|set
comma
op_amp
id|rt_sf-&gt;uc.uc_sigmask
comma
r_sizeof
(paren
id|set
)paren
)paren
op_logical_or
id|copy_from_user
c_func
(paren
op_amp
id|st
comma
op_amp
id|rt_sf-&gt;uc.uc_stack
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
multiline_comment|/* restore registers -&n;&t; * sigctx is initialized to point to the &n;&t; * preamble frame (where registers are stored) &n;&t; * see handle_signal()&n;&t; */
id|sr
op_assign
(paren
r_struct
id|sigregs
op_star
)paren
id|sigctx.regs
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|saved_regs
comma
op_amp
id|sr-&gt;gp_regs
comma
r_sizeof
(paren
id|sr-&gt;gp_regs
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|saved_regs
(braket
id|PT_MSR
)braket
op_assign
(paren
id|regs-&gt;msr
op_amp
op_complement
id|MSR_USERCHANGE
)paren
op_or
(paren
id|saved_regs
(braket
id|PT_MSR
)braket
op_amp
id|MSR_USERCHANGE
)paren
suffix:semicolon
id|saved_regs
(braket
id|PT_SOFTE
)braket
op_assign
id|regs-&gt;softe
suffix:semicolon
id|memcpy
c_func
(paren
id|regs
comma
id|saved_regs
comma
id|GP_REGS_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|current-&gt;thread.fpr
comma
op_amp
id|sr-&gt;fp_regs
comma
r_sizeof
(paren
id|sr-&gt;fp_regs
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
multiline_comment|/* This function sets back the stack flags into&n;&t;   the current task structure.  */
id|sys_sigaltstack
c_func
(paren
op_amp
id|st
comma
l_int|NULL
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
r_return
id|regs-&gt;result
suffix:semicolon
id|badframe
suffix:colon
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
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|sigregs
op_star
id|frame
comma
r_int
r_int
id|newsp
)paren
(brace
r_struct
id|rt_sigframe
op_star
id|rt_sf
op_assign
(paren
r_struct
id|rt_sigframe
op_star
)paren
id|newsp
suffix:semicolon
multiline_comment|/* Handler is *really* a pointer to the function descriptor for&n;&t; * the signal routine.  The first entry in the function&n;&t; * descriptor is the entry address of signal and the second&n;&t; * entry is the TOC value we need to use.&n;&t; */
r_struct
id|funct_descr_entry
(brace
r_int
r_int
id|entry
suffix:semicolon
r_int
r_int
id|toc
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|funct_descr_entry
op_star
id|funct_desc_ptr
suffix:semicolon
r_int
r_int
id|temp_ptr
suffix:semicolon
multiline_comment|/* Set up preamble frame */
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
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;gp_regs
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
id|frame-&gt;fp_regs
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
multiline_comment|/* li r0, __NR_rt_sigreturn */
op_logical_or
id|__put_user
c_func
(paren
l_int|0x38000000UL
op_plus
id|__NR_rt_sigreturn
comma
op_amp
id|frame-&gt;tramp
(braket
l_int|0
)braket
)paren
multiline_comment|/* sc */
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
r_goto
id|badframe
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
id|current-&gt;thread.fpscr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* turn off all fp exceptions */
multiline_comment|/* Retrieve rt_sigframe from stack and&n;&t;   set up registers for signal handler&n;&t;*/
id|newsp
op_sub_assign
id|__SIGNAL_FRAMESIZE
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|temp_ptr
comma
op_amp
id|rt_sf-&gt;uc.uc_mcontext.handler
)paren
)paren
(brace
r_goto
id|badframe
suffix:semicolon
)brace
id|funct_desc_ptr
op_assign
(paren
r_struct
id|funct_descr_entry
op_star
)paren
id|temp_ptr
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
op_star
)paren
id|newsp
)paren
op_logical_or
id|get_user
c_func
(paren
id|regs-&gt;nip
comma
op_amp
id|funct_desc_ptr-&gt;entry
)paren
op_logical_or
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
op_logical_or
id|get_user
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|3
)braket
comma
op_amp
id|rt_sf-&gt;uc.uc_mcontext.signal
)paren
op_logical_or
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
id|rt_sf-&gt;pinfo
)paren
op_logical_or
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
id|rt_sf-&gt;puc
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
l_int|6
)braket
op_assign
(paren
r_int
r_int
)paren
id|rt_sf
suffix:semicolon
id|regs-&gt;link
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;tramp
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
multiline_comment|/*&n; * Do a signal return; undo the signal stack.&n; */
DECL|function|sys_sigreturn
r_int
id|sys_sigreturn
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
id|sigcontext
op_star
id|sc
comma
id|sigctx
suffix:semicolon
r_struct
id|sigregs
op_star
id|sr
suffix:semicolon
id|elf_gregset_t
id|saved_regs
suffix:semicolon
multiline_comment|/* an array of ELF_NGREG unsigned longs */
id|sigset_t
id|set
suffix:semicolon
id|sc
op_assign
(paren
r_struct
id|sigcontext
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
macro_line|#if _NSIG_WORDS &gt; 1
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
macro_line|#endif
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
multiline_comment|/* restore registers */
id|sr
op_assign
(paren
r_struct
id|sigregs
op_star
)paren
id|sigctx.regs
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|saved_regs
comma
op_amp
id|sr-&gt;gp_regs
comma
r_sizeof
(paren
id|sr-&gt;gp_regs
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|saved_regs
(braket
id|PT_MSR
)braket
op_assign
(paren
id|regs-&gt;msr
op_amp
op_complement
id|MSR_USERCHANGE
)paren
op_or
(paren
id|saved_regs
(braket
id|PT_MSR
)braket
op_amp
id|MSR_USERCHANGE
)paren
suffix:semicolon
id|saved_regs
(braket
id|PT_SOFTE
)braket
op_assign
id|regs-&gt;softe
suffix:semicolon
id|memcpy
c_func
(paren
id|regs
comma
id|saved_regs
comma
id|GP_REGS_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|current-&gt;thread.fpr
comma
op_amp
id|sr-&gt;fp_regs
comma
r_sizeof
(paren
id|sr-&gt;fp_regs
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
r_return
id|regs-&gt;result
suffix:semicolon
id|badframe
suffix:colon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up a signal frame.&n; */
DECL|function|setup_frame
r_static
r_void
id|setup_frame
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|sigregs
op_star
id|frame
comma
r_int
r_int
id|newsp
)paren
(brace
multiline_comment|/* Handler is *really* a pointer to the function descriptor for&n;&t; * the signal routine.  The first entry in the function&n;&t; * descriptor is the entry address of signal and the second&n;&t; * entry is the TOC value we need to use.&n;&t; */
r_struct
id|funct_descr_entry
(brace
r_int
r_int
id|entry
suffix:semicolon
r_int
r_int
id|toc
suffix:semicolon
)brace
suffix:semicolon
r_struct
id|funct_descr_entry
op_star
id|funct_desc_ptr
suffix:semicolon
r_int
r_int
id|temp_ptr
suffix:semicolon
r_struct
id|sigcontext
op_star
id|sc
op_assign
(paren
r_struct
id|sigcontext
op_star
)paren
id|newsp
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
r_if
c_cond
(paren
id|__copy_to_user
c_func
(paren
op_amp
id|frame-&gt;gp_regs
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
id|frame-&gt;fp_regs
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
multiline_comment|/* li r0, __NR_sigreturn */
op_logical_or
id|__put_user
c_func
(paren
l_int|0x38000000UL
op_plus
id|__NR_sigreturn
comma
op_amp
id|frame-&gt;tramp
(braket
l_int|0
)braket
)paren
multiline_comment|/* sc */
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
r_goto
id|badframe
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
id|current-&gt;thread.fpscr
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* turn off all fp exceptions */
id|newsp
op_sub_assign
id|__SIGNAL_FRAMESIZE
suffix:semicolon
r_if
c_cond
(paren
id|get_user
c_func
(paren
id|temp_ptr
comma
op_amp
id|sc-&gt;handler
)paren
)paren
r_goto
id|badframe
suffix:semicolon
id|funct_desc_ptr
op_assign
(paren
r_struct
id|funct_descr_entry
op_star
)paren
id|temp_ptr
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
op_star
)paren
id|newsp
)paren
op_logical_or
id|get_user
c_func
(paren
id|regs-&gt;nip
comma
op_amp
id|funct_desc_ptr
op_member_access_from_pointer
id|entry
)paren
op_logical_or
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
op_logical_or
id|get_user
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|3
)braket
comma
op_amp
id|sc-&gt;signal
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
l_int|4
)braket
op_assign
(paren
r_int
r_int
)paren
id|sc
suffix:semicolon
id|regs-&gt;link
op_assign
(paren
r_int
r_int
)paren
id|frame-&gt;tramp
suffix:semicolon
r_return
suffix:semicolon
id|badframe
suffix:colon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;badframe in setup_frame, regs=%p frame=%p newsp=%lx&bslash;n&quot;
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
op_star
id|newspp
comma
r_int
r_int
id|frame
)paren
(brace
r_struct
id|sigcontext
op_star
id|sc
suffix:semicolon
r_struct
id|rt_sigframe
op_star
id|rt_sf
suffix:semicolon
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
r_if
c_cond
(paren
id|regs-&gt;trap
op_eq
l_int|0x0C00
multiline_comment|/* System Call! */
op_logical_and
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
id|ERESTART_RESTARTBLOCK
op_logical_or
(paren
(paren
r_int
)paren
id|regs-&gt;result
op_eq
op_minus
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
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|restart_block.fn
op_assign
id|do_no_restart_syscall
suffix:semicolon
id|regs-&gt;result
op_assign
op_minus
id|EINTR
suffix:semicolon
)brace
multiline_comment|/* Set up Signal Frame */
r_if
c_cond
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_SIGINFO
)paren
(brace
multiline_comment|/* Put a Real Time Context onto stack */
op_star
id|newspp
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
op_star
)paren
op_star
id|newspp
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
comma
id|rt_sf
comma
r_sizeof
(paren
op_star
id|rt_sf
)paren
)paren
)paren
r_goto
id|badframe
suffix:semicolon
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
id|rt_sf-&gt;uc.uc_mcontext.handler
)paren
op_logical_or
id|__put_user
c_func
(paren
op_amp
id|rt_sf-&gt;info
comma
op_amp
id|rt_sf-&gt;pinfo
)paren
op_logical_or
id|__put_user
c_func
(paren
op_amp
id|rt_sf-&gt;uc
comma
op_amp
id|rt_sf-&gt;puc
)paren
multiline_comment|/* Put the siginfo */
op_logical_or
id|copy_siginfo_to_user
c_func
(paren
op_amp
id|rt_sf-&gt;info
comma
id|info
)paren
multiline_comment|/* Create the ucontext */
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
multiline_comment|/* mcontext.regs points to preamble register frame */
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
id|rt_sf-&gt;uc.uc_mcontext.regs
)paren
op_logical_or
id|__put_user
c_func
(paren
id|sig
comma
op_amp
id|rt_sf-&gt;uc.uc_mcontext.signal
)paren
)paren
r_goto
id|badframe
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Put a sigcontext on the stack */
op_star
id|newspp
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
op_star
)paren
op_star
id|newspp
suffix:semicolon
r_if
c_cond
(paren
id|verify_area
c_func
(paren
id|VERIFY_WRITE
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
id|badframe
suffix:semicolon
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
macro_line|#if _NSIG_WORDS &gt; 1
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
macro_line|#endif
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
)brace
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
id|badframe
suffix:colon
macro_line|#if DEBUG_SIG
id|printk
c_func
(paren
l_string|&quot;badframe in handle_signal, regs=%p frame=%lx newsp=%lx&bslash;n&quot;
comma
id|regs
comma
id|frame
comma
op_star
id|newspp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;sc=%p sig=%d ka=%p info=%p oldset=%p&bslash;n&quot;
comma
id|sc
comma
id|sig
comma
id|ka
comma
id|info
comma
id|oldset
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
multiline_comment|/*&n; * Note that &squot;init&squot; is a special process: it doesn&squot;t get signals it doesn&squot;t&n; * want to handle. Thus you cannot kill init even with a SIGKILL even by&n; * mistake.&n; */
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
(paren
id|ka-&gt;sa.sa_flags
op_amp
id|SA_ONSTACK
)paren
op_logical_and
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
)paren
id|newsp
op_assign
(paren
id|current-&gt;sas_ss_sp
op_plus
id|current-&gt;sas_ss_size
)paren
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
op_assign
id|frame
op_assign
id|newsp
op_minus
r_sizeof
(paren
r_struct
id|sigregs
)paren
suffix:semicolon
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
comma
op_amp
id|newsp
comma
id|frame
)paren
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
r_if
c_cond
(paren
id|newsp
op_eq
id|frame
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* no signals delivered */
multiline_comment|/* Invoke correct stack setup routine */
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
id|regs
comma
(paren
r_struct
id|sigregs
op_star
)paren
id|frame
comma
id|newsp
)paren
suffix:semicolon
r_else
id|setup_frame
c_func
(paren
id|regs
comma
(paren
r_struct
id|sigregs
op_star
)paren
id|frame
comma
id|newsp
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
eof
