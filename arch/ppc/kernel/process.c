multiline_comment|/*&n; *  arch/ppc/kernel/process.c&n; *&n; *  Derived from &quot;arch/i386/kernel/process.c&quot;&n; *    Copyright (C) 1995  Linus Torvalds&n; *&n; *  Updated and modified by Cort Dougan (cort@cs.nmt.edu) and&n; *  Paul Mackerras (paulus@cs.anu.edu.au)&n; *&n; *  PowerPC version &n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/prctl.h&gt;
macro_line|#include &lt;linux/init_task.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
r_int
id|dump_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_fpregset_t
op_star
id|fpregs
)paren
suffix:semicolon
r_extern
r_int
r_int
id|_get_SP
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|last_task_used_math
r_struct
id|task_struct
op_star
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|last_task_used_altivec
r_struct
id|task_struct
op_star
id|last_task_used_altivec
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|init_fs
r_static
r_struct
id|fs_struct
id|init_fs
op_assign
id|INIT_FS
suffix:semicolon
DECL|variable|init_files
r_static
r_struct
id|files_struct
id|init_files
op_assign
id|INIT_FILES
suffix:semicolon
DECL|variable|init_signals
r_static
r_struct
id|signal_struct
id|init_signals
op_assign
id|INIT_SIGNALS
c_func
(paren
id|init_signals
)paren
suffix:semicolon
DECL|variable|init_sighand
r_static
r_struct
id|sighand_struct
id|init_sighand
op_assign
id|INIT_SIGHAND
c_func
(paren
id|init_sighand
)paren
suffix:semicolon
DECL|variable|init_mm
r_struct
id|mm_struct
id|init_mm
op_assign
id|INIT_MM
c_func
(paren
id|init_mm
)paren
suffix:semicolon
multiline_comment|/* this is 8kB-aligned so we can get to the thread_info struct&n;   at the base of it from the stack pointer with 1 integer instruction. */
DECL|variable|init_thread_union
r_union
id|thread_union
id|init_thread_union
id|__attribute__
c_func
(paren
(paren
id|__section__
c_func
(paren
l_string|&quot;.data.init_task&quot;
)paren
)paren
)paren
op_assign
(brace
id|INIT_THREAD_INFO
c_func
(paren
id|init_task
)paren
)brace
suffix:semicolon
multiline_comment|/* initial task structure */
DECL|variable|init_task
r_struct
id|task_struct
id|init_task
op_assign
id|INIT_TASK
c_func
(paren
id|init_task
)paren
suffix:semicolon
multiline_comment|/* only used to get secondary processor up */
DECL|variable|current_set
r_struct
id|task_struct
op_star
id|current_set
(braket
id|NR_CPUS
)braket
op_assign
(brace
op_amp
id|init_task
comma
)brace
suffix:semicolon
r_static
r_void
id|show_tsk_stack
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|sp
)paren
suffix:semicolon
DECL|macro|SHOW_TASK_SWITCHES
macro_line|#undef SHOW_TASK_SWITCHES
DECL|macro|CHECK_STACK
macro_line|#undef CHECK_STACK
macro_line|#if defined(CHECK_STACK)
r_int
r_int
DECL|function|kernel_stack_top
id|kernel_stack_top
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_return
(paren
(paren
r_int
r_int
)paren
id|tsk
)paren
op_plus
r_sizeof
(paren
r_union
id|task_union
)paren
suffix:semicolon
)brace
r_int
r_int
DECL|function|task_top
id|task_top
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_return
(paren
(paren
r_int
r_int
)paren
id|tsk
)paren
op_plus
r_sizeof
(paren
r_struct
id|task_struct
)paren
suffix:semicolon
)brace
multiline_comment|/* check to make sure the kernel stack is healthy */
DECL|function|check_stack
r_int
id|check_stack
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_int
r_int
id|stack_top
op_assign
id|kernel_stack_top
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_int
r_int
id|tsk_top
op_assign
id|task_top
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#if 0&t;
multiline_comment|/* check thread magic */
r_if
c_cond
(paren
id|tsk-&gt;thread.magic
op_ne
id|THREAD_MAGIC
)paren
(brace
id|ret
op_or_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;thread.magic bad: %08x&bslash;n&quot;
comma
id|tsk-&gt;thread.magic
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|tsk
)paren
id|printk
c_func
(paren
l_string|&quot;check_stack(): tsk bad tsk %p&bslash;n&quot;
comma
id|tsk
)paren
suffix:semicolon
multiline_comment|/* check if stored ksp is bad */
r_if
c_cond
(paren
(paren
id|tsk-&gt;thread.ksp
OG
id|stack_top
)paren
op_logical_or
(paren
id|tsk-&gt;thread.ksp
OL
id|tsk_top
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;stack out of bounds: %s/%d&bslash;n&quot;
l_string|&quot; tsk_top %08lx ksp %08lx stack_top %08lx&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|tsk-&gt;pid
comma
id|tsk_top
comma
id|tsk-&gt;thread.ksp
comma
id|stack_top
)paren
suffix:semicolon
id|ret
op_or_assign
l_int|2
suffix:semicolon
)brace
multiline_comment|/* check if stack ptr RIGHT NOW is bad */
r_if
c_cond
(paren
(paren
id|tsk
op_eq
id|current
)paren
op_logical_and
(paren
(paren
id|_get_SP
c_func
(paren
)paren
OG
id|stack_top
)paren
op_logical_or
(paren
id|_get_SP
c_func
(paren
)paren
OL
id|tsk_top
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;current stack ptr out of bounds: %s/%d&bslash;n&quot;
l_string|&quot; tsk_top %08lx sp %08lx stack_top %08lx&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|tsk_top
comma
id|_get_SP
c_func
(paren
)paren
comma
id|stack_top
)paren
suffix:semicolon
id|ret
op_or_assign
l_int|4
suffix:semicolon
)brace
macro_line|#if 0&t;
multiline_comment|/* check amount of free stack */
r_for
c_loop
(paren
id|i
op_assign
(paren
r_int
r_int
op_star
)paren
id|task_top
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|i
OL
id|kernel_stack_top
c_func
(paren
id|tsk
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|i
)paren
id|printk
c_func
(paren
l_string|&quot;check_stack(): i = %p&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|i
op_ne
l_int|0
)paren
(brace
multiline_comment|/* only notify if it&squot;s less than 900 bytes */
r_if
c_cond
(paren
(paren
id|i
op_minus
(paren
r_int
r_int
op_star
)paren
id|task_top
c_func
(paren
id|tsk
)paren
)paren
OL
l_int|900
)paren
id|printk
c_func
(paren
l_string|&quot;%d bytes free on stack&bslash;n&quot;
comma
id|i
op_minus
id|task_top
c_func
(paren
id|tsk
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif
r_if
c_cond
(paren
id|ret
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;bad kernel stack&quot;
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
macro_line|#endif /* defined(CHECK_STACK) */
macro_line|#ifdef CONFIG_ALTIVEC
r_int
DECL|function|dump_altivec
id|dump_altivec
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_vrregset_t
op_star
id|vrregs
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
id|memcpy
c_func
(paren
id|vrregs
comma
op_amp
id|current-&gt;thread.vr
(braket
l_int|0
)braket
comma
r_sizeof
(paren
op_star
id|vrregs
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_void
DECL|function|enable_kernel_altivec
id|enable_kernel_altivec
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|current-&gt;thread.regs
op_logical_and
(paren
id|current-&gt;thread.regs-&gt;msr
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
r_else
id|giveup_altivec
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* just enable AltiVec for kernel - force */
macro_line|#else
id|giveup_altivec
c_func
(paren
id|last_task_used_altivec
)paren
suffix:semicolon
macro_line|#endif /* __SMP __ */
)brace
macro_line|#endif /* CONFIG_ALTIVEC */
r_void
DECL|function|enable_kernel_fp
id|enable_kernel_fp
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|current-&gt;thread.regs
op_logical_and
(paren
id|current-&gt;thread.regs-&gt;msr
op_amp
id|MSR_FP
)paren
)paren
id|giveup_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
r_else
id|giveup_fpu
c_func
(paren
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/* just enables FP for kernel */
macro_line|#else
id|giveup_fpu
c_func
(paren
id|last_task_used_math
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
)brace
r_int
DECL|function|dump_fpu
id|dump_fpu
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
id|elf_fpregset_t
op_star
id|fpregs
)paren
(brace
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
id|memcpy
c_func
(paren
id|fpregs
comma
op_amp
id|current-&gt;thread.fpr
(braket
l_int|0
)braket
comma
r_sizeof
(paren
op_star
id|fpregs
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|__switch_to
r_struct
id|task_struct
op_star
id|__switch_to
c_func
(paren
r_struct
id|task_struct
op_star
id|prev
comma
r_struct
id|task_struct
op_star
r_new
)paren
(brace
r_struct
id|thread_struct
op_star
id|new_thread
comma
op_star
id|old_thread
suffix:semicolon
r_int
r_int
id|s
suffix:semicolon
r_struct
id|task_struct
op_star
id|last
suffix:semicolon
id|local_irq_save
c_func
(paren
id|s
)paren
suffix:semicolon
macro_line|#if CHECK_STACK
id|check_stack
c_func
(paren
id|prev
)paren
suffix:semicolon
id|check_stack
c_func
(paren
r_new
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* avoid complexity of lazy save/restore of fpu&n;&t; * by just saving it every time we switch out if&n;&t; * this task used the fpu during the last quantum.&n;&t; * &n;&t; * If it tries to use the fpu again, it&squot;ll trap and&n;&t; * reload its fp regs.  So we don&squot;t have to do a restore&n;&t; * every switch, just a save.&n;&t; *  -- Cort&n;&t; */
r_if
c_cond
(paren
id|prev-&gt;thread.regs
op_logical_and
(paren
id|prev-&gt;thread.regs-&gt;msr
op_amp
id|MSR_FP
)paren
)paren
id|giveup_fpu
c_func
(paren
id|prev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ALTIVEC&t;
multiline_comment|/*&n;&t; * If the previous thread used altivec in the last quantum&n;&t; * (thus changing altivec regs) then save them.&n;&t; * We used to check the VRSAVE register but not all apps&n;&t; * set it, so we don&squot;t rely on it now (and in fact we need&n;&t; * to save &amp; restore VSCR even if VRSAVE == 0).  -- paulus&n;&t; *&n;&t; * On SMP we always save/restore altivec regs just to avoid the&n;&t; * complexity of changing processors.&n;&t; *  -- Cort&n;&t; */
r_if
c_cond
(paren
(paren
id|prev-&gt;thread.regs
op_logical_and
(paren
id|prev-&gt;thread.regs-&gt;msr
op_amp
id|MSR_VEC
)paren
)paren
)paren
id|giveup_altivec
c_func
(paren
id|prev
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */&t;
macro_line|#endif /* CONFIG_SMP */
multiline_comment|/* Avoid the trap.  On smp this this never happens since&n;&t; * we don&squot;t set last_task_used_altivec -- Cort&n;&t; */
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|thread.regs
op_logical_and
id|last_task_used_altivec
op_eq
r_new
)paren
r_new
op_member_access_from_pointer
id|thread.regs-&gt;msr
op_or_assign
id|MSR_VEC
suffix:semicolon
id|new_thread
op_assign
op_amp
r_new
op_member_access_from_pointer
id|thread
suffix:semicolon
id|old_thread
op_assign
op_amp
id|current-&gt;thread
suffix:semicolon
id|last
op_assign
id|_switch
c_func
(paren
id|old_thread
comma
id|new_thread
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
id|last
suffix:semicolon
)brace
DECL|function|show_regs
r_void
id|show_regs
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|i
comma
id|trap
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;NIP: %08lX LR: %08lX SP: %08lX REGS: %p TRAP: %04lx    %s&bslash;n&quot;
comma
id|regs-&gt;nip
comma
id|regs-&gt;link
comma
id|regs-&gt;gpr
(braket
l_int|1
)braket
comma
id|regs
comma
id|regs-&gt;trap
comma
id|print_tainted
c_func
(paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;MSR: %08lx EE: %01x PR: %01x FP: %01x ME: %01x IR/DR: %01x%01x&bslash;n&quot;
comma
id|regs-&gt;msr
comma
id|regs-&gt;msr
op_amp
id|MSR_EE
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|regs-&gt;msr
op_amp
id|MSR_PR
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|regs-&gt;msr
op_amp
id|MSR_FP
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|regs-&gt;msr
op_amp
id|MSR_ME
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|regs-&gt;msr
op_amp
id|MSR_IR
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|regs-&gt;msr
op_amp
id|MSR_DR
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
suffix:semicolon
id|trap
op_assign
id|TRAP
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|trap
op_eq
l_int|0x300
op_logical_or
id|trap
op_eq
l_int|0x600
)paren
id|printk
c_func
(paren
l_string|&quot;DAR: %08lX, DSISR: %08lX&bslash;n&quot;
comma
id|regs-&gt;dar
comma
id|regs-&gt;dsisr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;TASK = %p[%d] &squot;%s&squot; &quot;
comma
id|current
comma
id|current-&gt;pid
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Last syscall: %ld &quot;
comma
id|current-&gt;thread.last_syscall
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_4xx) &amp;&amp; defined(DCRN_PLB0_BEAR)
id|printk
c_func
(paren
l_string|&quot;&bslash;nPLB0: bear= 0x%8.8x acr=   0x%8.8x besr=  0x%8.8x&bslash;n&quot;
comma
id|mfdcr
c_func
(paren
id|DCRN_PLB0_BEAR
)paren
comma
id|mfdcr
c_func
(paren
id|DCRN_PLB0_ACR
)paren
comma
id|mfdcr
c_func
(paren
id|DCRN_PLB0_BESR
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CONFIG_4xx) &amp;&amp; defined(DCRN_POB0_BEAR)
id|printk
c_func
(paren
l_string|&quot;PLB0 to OPB: bear= 0x%8.8x besr0= 0x%8.8x besr1= 0x%8.8x&bslash;n&quot;
comma
id|mfdcr
c_func
(paren
id|DCRN_POB0_BEAR
)paren
comma
id|mfdcr
c_func
(paren
id|DCRN_POB0_BESR0
)paren
comma
id|mfdcr
c_func
(paren
id|DCRN_POB0_BESR1
)paren
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
id|printk
c_func
(paren
l_string|&quot; CPU: %d&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|r
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|8
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
id|KERN_INFO
l_string|&quot;GPR%02d: &quot;
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|r
comma
op_amp
id|regs-&gt;gpr
(braket
id|i
)braket
)paren
)paren
r_break
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08lX &quot;
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|12
op_logical_and
op_logical_neg
id|FULL_REGS
c_func
(paren
id|regs
)paren
)paren
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|show_tsk_stack
c_func
(paren
id|current
comma
id|regs-&gt;gpr
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
DECL|function|exit_thread
r_void
id|exit_thread
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|last_task_used_altivec
op_eq
id|current
)paren
id|last_task_used_altivec
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|last_task_used_altivec
op_eq
id|current
)paren
id|last_task_used_altivec
op_assign
l_int|NULL
suffix:semicolon
)brace
r_void
DECL|function|release_thread
id|release_thread
c_func
(paren
r_struct
id|task_struct
op_star
id|t
)paren
(brace
)brace
multiline_comment|/*&n; * This gets called before we allocate a new thread and copy&n; * the current task into it.&n; */
DECL|function|prepare_to_copy
r_void
id|prepare_to_copy
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
id|tsk-&gt;thread.regs
suffix:semicolon
r_if
c_cond
(paren
id|regs
op_eq
l_int|NULL
)paren
r_return
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
macro_line|#endif /* CONFIG_ALTIVEC */
)brace
multiline_comment|/*&n; * Copy a thread..&n; */
r_int
DECL|function|copy_thread
id|copy_thread
c_func
(paren
r_int
id|nr
comma
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|usp
comma
r_int
r_int
id|unused
comma
r_struct
id|task_struct
op_star
id|p
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|pt_regs
op_star
id|childregs
comma
op_star
id|kregs
suffix:semicolon
r_extern
r_void
id|ret_from_fork
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|sp
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
op_plus
id|THREAD_SIZE
suffix:semicolon
r_int
r_int
id|childframe
suffix:semicolon
id|p-&gt;set_child_tid
op_assign
id|p-&gt;clear_child_tid
op_assign
l_int|NULL
suffix:semicolon
id|CHECK_FULL_REGS
c_func
(paren
id|regs
)paren
suffix:semicolon
multiline_comment|/* Copy registers */
id|sp
op_sub_assign
r_sizeof
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
id|childregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|sp
suffix:semicolon
op_star
id|childregs
op_assign
op_star
id|regs
suffix:semicolon
r_if
c_cond
(paren
(paren
id|childregs-&gt;msr
op_amp
id|MSR_PR
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* for kernel thread, set `current&squot; and stackptr in new task */
id|childregs-&gt;gpr
(braket
l_int|1
)braket
op_assign
id|sp
op_plus
r_sizeof
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
id|childregs-&gt;gpr
(braket
l_int|2
)braket
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|p-&gt;thread.regs
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* no user register state */
)brace
r_else
(brace
id|childregs-&gt;gpr
(braket
l_int|1
)braket
op_assign
id|usp
suffix:semicolon
id|p-&gt;thread.regs
op_assign
id|childregs
suffix:semicolon
r_if
c_cond
(paren
id|clone_flags
op_amp
id|CLONE_SETTLS
)paren
id|childregs-&gt;gpr
(braket
l_int|2
)braket
op_assign
id|childregs-&gt;gpr
(braket
l_int|6
)braket
suffix:semicolon
)brace
id|childregs-&gt;gpr
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Result from fork() */
id|sp
op_sub_assign
id|STACK_FRAME_OVERHEAD
suffix:semicolon
id|childframe
op_assign
id|sp
suffix:semicolon
multiline_comment|/*&n;&t; * The way this works is that at some point in the future&n;&t; * some task will call _switch to switch to the new task.&n;&t; * That will pop off the stack frame created below and start&n;&t; * the new task running at ret_from_fork.  The new task will&n;&t; * do some house keeping and then return from the fork or clone&n;&t; * system call, using the stack frame created above.&n;&t; */
id|sp
op_sub_assign
r_sizeof
(paren
r_struct
id|pt_regs
)paren
suffix:semicolon
id|kregs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
id|sp
suffix:semicolon
id|sp
op_sub_assign
id|STACK_FRAME_OVERHEAD
suffix:semicolon
id|p-&gt;thread.ksp
op_assign
id|sp
suffix:semicolon
id|kregs-&gt;nip
op_assign
(paren
r_int
r_int
)paren
id|ret_from_fork
suffix:semicolon
id|p-&gt;thread.last_syscall
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Set up a thread for executing a new program&n; */
DECL|function|start_thread
r_void
id|start_thread
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
r_int
id|nip
comma
r_int
r_int
id|sp
)paren
(brace
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
id|memset
c_func
(paren
id|regs-&gt;gpr
comma
l_int|0
comma
r_sizeof
(paren
id|regs-&gt;gpr
)paren
)paren
suffix:semicolon
id|regs-&gt;ctr
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;link
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;xer
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;ccr
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;mq
op_assign
l_int|0
suffix:semicolon
id|regs-&gt;nip
op_assign
id|nip
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_assign
id|sp
suffix:semicolon
id|regs-&gt;msr
op_assign
id|MSR_USER
suffix:semicolon
r_if
c_cond
(paren
id|last_task_used_math
op_eq
id|current
)paren
id|last_task_used_math
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|last_task_used_altivec
op_eq
id|current
)paren
id|last_task_used_altivec
op_assign
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|current-&gt;thread.fpr
comma
l_int|0
comma
r_sizeof
(paren
id|current-&gt;thread.fpr
)paren
)paren
suffix:semicolon
id|current-&gt;thread.fpscr
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_ALTIVEC
id|memset
c_func
(paren
id|current-&gt;thread.vr
comma
l_int|0
comma
r_sizeof
(paren
id|current-&gt;thread.vr
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|current-&gt;thread.vscr
comma
l_int|0
comma
r_sizeof
(paren
id|current-&gt;thread.vscr
)paren
)paren
suffix:semicolon
id|current-&gt;thread.vrsave
op_assign
l_int|0
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
)brace
DECL|function|set_fpexc_mode
r_int
id|set_fpexc_mode
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|val
)paren
(brace
r_struct
id|pt_regs
op_star
id|regs
op_assign
id|tsk-&gt;thread.regs
suffix:semicolon
r_if
c_cond
(paren
id|val
OG
id|PR_FP_EXC_PRECISE
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|tsk-&gt;thread.fpexc_mode
op_assign
id|__pack_fe01
c_func
(paren
id|val
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs
op_ne
l_int|NULL
op_logical_and
(paren
id|regs-&gt;msr
op_amp
id|MSR_FP
)paren
op_ne
l_int|0
)paren
id|regs-&gt;msr
op_assign
(paren
id|regs-&gt;msr
op_amp
op_complement
(paren
id|MSR_FE0
op_or
id|MSR_FE1
)paren
)paren
op_or
id|tsk-&gt;thread.fpexc_mode
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|get_fpexc_mode
r_int
id|get_fpexc_mode
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|adr
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|val
op_assign
id|__unpack_fe01
c_func
(paren
id|tsk-&gt;thread.fpexc_mode
)paren
suffix:semicolon
r_return
id|put_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|adr
)paren
suffix:semicolon
)brace
DECL|function|sys_clone
r_int
id|sys_clone
c_func
(paren
r_int
r_int
id|clone_flags
comma
r_int
r_int
id|usp
comma
r_int
op_star
id|parent_tidp
comma
r_void
op_star
id|child_threadptr
comma
r_int
op_star
id|child_tidp
comma
r_int
id|p6
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|CHECK_FULL_REGS
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|usp
op_eq
l_int|0
)paren
id|usp
op_assign
id|regs-&gt;gpr
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* stack pointer for child */
id|p
op_assign
id|do_fork
c_func
(paren
id|clone_flags
op_amp
op_complement
id|CLONE_IDLETASK
comma
id|usp
comma
id|regs
comma
l_int|0
comma
id|parent_tidp
comma
id|child_tidp
)paren
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|p
)paren
ques
c_cond
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:colon
id|p-&gt;pid
suffix:semicolon
)brace
DECL|function|sys_fork
r_int
id|sys_fork
c_func
(paren
r_int
id|p1
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
id|p5
comma
r_int
id|p6
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|CHECK_FULL_REGS
c_func
(paren
id|regs
)paren
suffix:semicolon
id|p
op_assign
id|do_fork
c_func
(paren
id|SIGCHLD
comma
id|regs-&gt;gpr
(braket
l_int|1
)braket
comma
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|p
)paren
ques
c_cond
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:colon
id|p-&gt;pid
suffix:semicolon
)brace
DECL|function|sys_vfork
r_int
id|sys_vfork
c_func
(paren
r_int
id|p1
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
id|p5
comma
r_int
id|p6
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|task_struct
op_star
id|p
suffix:semicolon
id|CHECK_FULL_REGS
c_func
(paren
id|regs
)paren
suffix:semicolon
id|p
op_assign
id|do_fork
c_func
(paren
id|CLONE_VFORK
op_or
id|CLONE_VM
op_or
id|SIGCHLD
comma
id|regs-&gt;gpr
(braket
l_int|1
)braket
comma
id|regs
comma
l_int|0
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_return
id|IS_ERR
c_func
(paren
id|p
)paren
ques
c_cond
id|PTR_ERR
c_func
(paren
id|p
)paren
suffix:colon
id|p-&gt;pid
suffix:semicolon
)brace
DECL|function|sys_execve
r_int
id|sys_execve
c_func
(paren
r_int
r_int
id|a0
comma
r_int
r_int
id|a1
comma
r_int
r_int
id|a2
comma
r_int
r_int
id|a3
comma
r_int
r_int
id|a4
comma
r_int
r_int
id|a5
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|error
suffix:semicolon
r_char
op_star
id|filename
suffix:semicolon
id|filename
op_assign
id|getname
c_func
(paren
(paren
r_char
op_star
)paren
id|a0
)paren
suffix:semicolon
id|error
op_assign
id|PTR_ERR
c_func
(paren
id|filename
)paren
suffix:semicolon
r_if
c_cond
(paren
id|IS_ERR
c_func
(paren
id|filename
)paren
)paren
r_goto
id|out
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
macro_line|#endif /* CONFIG_ALTIVEC */ 
id|error
op_assign
id|do_execve
c_func
(paren
id|filename
comma
(paren
r_char
op_star
op_star
)paren
id|a1
comma
(paren
r_char
op_star
op_star
)paren
id|a2
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|error
op_eq
l_int|0
)paren
id|current-&gt;ptrace
op_and_assign
op_complement
id|PT_DTRACE
suffix:semicolon
id|putname
c_func
(paren
id|filename
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|error
suffix:semicolon
)brace
DECL|function|show_trace_task
r_void
id|show_trace_task
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
id|show_tsk_stack
c_func
(paren
id|tsk
comma
id|tsk-&gt;thread.ksp
)paren
suffix:semicolon
)brace
DECL|function|dump_stack
r_void
id|dump_stack
c_func
(paren
r_void
)paren
(brace
id|show_tsk_stack
c_func
(paren
id|current
comma
id|_get_SP
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|function|show_tsk_stack
r_static
r_void
id|show_tsk_stack
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
id|sp
)paren
(brace
r_int
r_int
id|stack_top
comma
id|prev_sp
comma
id|ret
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|next_exc
op_assign
l_int|0
suffix:semicolon
r_struct
id|pt_regs
op_star
id|regs
suffix:semicolon
r_extern
r_char
id|ret_from_except
comma
id|ret_from_except_full
comma
id|ret_from_syscall
suffix:semicolon
r_if
c_cond
(paren
id|tsk
op_eq
l_int|NULL
)paren
r_return
suffix:semicolon
id|prev_sp
op_assign
(paren
r_int
r_int
)paren
(paren
id|tsk-&gt;thread_info
op_plus
l_int|1
)paren
suffix:semicolon
id|stack_top
op_assign
(paren
r_int
r_int
)paren
id|tsk-&gt;thread_info
op_plus
id|THREAD_SIZE
suffix:semicolon
r_while
c_loop
(paren
id|count
template_param
id|prev_sp
op_logical_and
id|sp
OL
id|stack_top
op_logical_and
(paren
id|sp
op_amp
l_int|3
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|count
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Call trace:&quot;
)paren
suffix:semicolon
macro_line|#if CONFIG_KALLSYMS
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
r_if
c_cond
(paren
id|next_exc
)paren
(brace
id|ret
op_assign
id|next_exc
suffix:semicolon
id|next_exc
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|ret
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|sp
op_plus
l_int|4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; [%08lx] &quot;
comma
id|ret
)paren
suffix:semicolon
macro_line|#if CONFIG_KALLSYMS
id|print_symbol
c_func
(paren
l_string|&quot;%s&quot;
comma
id|ret
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|ret
op_eq
(paren
r_int
r_int
)paren
op_amp
id|ret_from_except
op_logical_or
id|ret
op_eq
(paren
r_int
r_int
)paren
op_amp
id|ret_from_except_full
op_logical_or
id|ret
op_eq
(paren
r_int
r_int
)paren
op_amp
id|ret_from_syscall
)paren
(brace
multiline_comment|/* sp + 16 points to an exception frame */
id|regs
op_assign
(paren
r_struct
id|pt_regs
op_star
)paren
(paren
id|sp
op_plus
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sp
op_plus
l_int|16
op_plus
r_sizeof
(paren
op_star
id|regs
)paren
op_le
id|stack_top
)paren
id|next_exc
op_assign
id|regs-&gt;nip
suffix:semicolon
)brace
)brace
op_increment
id|count
suffix:semicolon
id|sp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|sp
suffix:semicolon
)brace
macro_line|#if !CONFIG_KALLSYMS
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
macro_line|#if 0
multiline_comment|/*&n; * Low level print for debugging - Cort&n; */
r_int
id|__init
id|ll_printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
id|va_list
id|args
suffix:semicolon
r_char
id|buf
(braket
l_int|256
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|i
op_assign
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|ll_puts
c_func
(paren
id|buf
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
r_int
id|lines
op_assign
l_int|24
comma
id|cols
op_assign
l_int|80
suffix:semicolon
r_int
id|orig_x
op_assign
l_int|0
comma
id|orig_y
op_assign
l_int|0
suffix:semicolon
r_void
id|puthex
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_int
r_char
id|buf
(braket
l_int|10
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|buf
(braket
id|i
)braket
op_assign
l_string|&quot;0123456789ABCDEF&quot;
(braket
id|val
op_amp
l_int|0x0F
)braket
suffix:semicolon
id|val
op_rshift_assign
l_int|4
suffix:semicolon
)brace
id|buf
(braket
l_int|8
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|prom_print
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_void
id|__init
id|ll_puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_int
id|x
comma
id|y
suffix:semicolon
r_char
op_star
id|vidmem
op_assign
(paren
r_char
op_star
)paren
multiline_comment|/*(_ISA_MEM_BASE + 0xB8000) */
l_int|0xD00B8000
suffix:semicolon
r_char
id|c
suffix:semicolon
r_extern
r_int
id|mem_init_done
suffix:semicolon
r_if
c_cond
(paren
id|mem_init_done
)paren
multiline_comment|/* assume this means we can printk */
(brace
id|printk
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#if 0&t;
r_if
c_cond
(paren
id|have_of
)paren
(brace
id|prom_print
c_func
(paren
id|s
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n;&t; * can&squot;t ll_puts on chrp without openfirmware yet.&n;&t; * vidmem just needs to be setup for it.&n;&t; * -- Cort&n;&t; */
r_if
c_cond
(paren
id|_machine
op_ne
id|_MACH_prep
)paren
r_return
suffix:semicolon
id|x
op_assign
id|orig_x
suffix:semicolon
id|y
op_assign
id|orig_y
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|y
op_ge
id|lines
)paren
(brace
multiline_comment|/*scroll();*/
multiline_comment|/*y--;*/
id|y
op_assign
l_int|0
suffix:semicolon
)brace
)brace
r_else
(brace
id|vidmem
(braket
(paren
id|x
op_plus
id|cols
op_star
id|y
)paren
op_star
l_int|2
)braket
op_assign
id|c
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|x
op_ge
id|cols
)paren
(brace
id|x
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|y
op_ge
id|lines
)paren
(brace
multiline_comment|/*scroll();*/
multiline_comment|/*y--;*/
id|y
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
)brace
id|orig_x
op_assign
id|x
suffix:semicolon
id|orig_y
op_assign
id|y
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*&n; * These bracket the sleeping functions..&n; */
r_extern
r_void
id|scheduling_functions_start_here
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|scheduling_functions_end_here
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|first_sched
mdefine_line|#define first_sched    ((unsigned long) scheduling_functions_start_here)
DECL|macro|last_sched
mdefine_line|#define last_sched     ((unsigned long) scheduling_functions_end_here)
DECL|function|get_wchan
r_int
r_int
id|get_wchan
c_func
(paren
r_struct
id|task_struct
op_star
id|p
)paren
(brace
r_int
r_int
id|ip
comma
id|sp
suffix:semicolon
r_int
r_int
id|stack_page
op_assign
(paren
r_int
r_int
)paren
id|p-&gt;thread_info
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|p
op_logical_or
id|p
op_eq
id|current
op_logical_or
id|p-&gt;state
op_eq
id|TASK_RUNNING
)paren
r_return
l_int|0
suffix:semicolon
id|sp
op_assign
id|p-&gt;thread.ksp
suffix:semicolon
r_do
(brace
id|sp
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
id|sp
suffix:semicolon
r_if
c_cond
(paren
id|sp
OL
id|stack_page
op_logical_or
id|sp
op_ge
id|stack_page
op_plus
l_int|8188
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
l_int|0
)paren
(brace
id|ip
op_assign
op_star
(paren
r_int
r_int
op_star
)paren
(paren
id|sp
op_plus
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ip
OL
id|first_sched
op_logical_or
id|ip
op_ge
id|last_sched
)paren
r_return
id|ip
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|count
op_increment
OL
l_int|16
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
