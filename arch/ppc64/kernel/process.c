multiline_comment|/*&n; *  linux/arch/ppc64/kernel/process.c&n; *&n; *  Derived from &quot;arch/i386/kernel/process.c&quot;&n; *    Copyright (C) 1995  Linus Torvalds&n; *&n; *  Updated and modified by Cort Dougan (cort@cs.nmt.edu) and&n; *  Paul Mackerras (paulus@cs.anu.edu.au)&n; *&n; *  PowerPC version &n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/unistd.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/user.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/init_task.h&gt;
macro_line|#include &lt;linux/prctl.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallHpt.h&gt;
macro_line|#include &lt;asm/hardirq.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#ifndef CONFIG_SMP
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
macro_line|#endif
DECL|variable|ioremap_mm
r_struct
id|mm_struct
id|ioremap_mm
op_assign
(brace
dot
id|pgd
op_assign
id|ioremap_dir
comma
dot
id|mm_users
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|2
)paren
comma
dot
id|mm_count
op_assign
id|ATOMIC_INIT
c_func
(paren
l_int|1
)paren
comma
dot
id|cpu_vm_mask
op_assign
id|CPU_MASK_ALL
comma
dot
id|page_table_lock
op_assign
id|SPIN_LOCK_UNLOCKED
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * Make sure the floating-point register state in the&n; * the thread_struct is up to date for task tsk.&n; */
DECL|function|flush_fp_to_thread
r_void
id|flush_fp_to_thread
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_if
c_cond
(paren
id|tsk-&gt;thread.regs
)paren
(brace
multiline_comment|/*&n;&t;&t; * We need to disable preemption here because if we didn&squot;t,&n;&t;&t; * another process could get scheduled after the regs-&gt;msr&n;&t;&t; * test but before we have finished saving the FP registers&n;&t;&t; * to the thread_struct.  That process could take over the&n;&t;&t; * FPU, and then when we get scheduled again we would store&n;&t;&t; * bogus values for the remaining FP registers.&n;&t;&t; */
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tsk-&gt;thread.regs-&gt;msr
op_amp
id|MSR_FP
)paren
(brace
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n;&t;&t;&t; * This should only ever be called for current or&n;&t;&t;&t; * for a stopped child process.  Since we save away&n;&t;&t;&t; * the FP register state on context switch on SMP,&n;&t;&t;&t; * there is something wrong if a stopped child appears&n;&t;&t;&t; * to still have its FP state in the CPU registers.&n;&t;&t;&t; */
id|BUG_ON
c_func
(paren
id|tsk
op_ne
id|current
)paren
suffix:semicolon
macro_line|#endif
id|giveup_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
)brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|enable_kernel_fp
r_void
id|enable_kernel_fp
c_func
(paren
r_void
)paren
(brace
id|WARN_ON
c_func
(paren
id|preemptible
c_func
(paren
)paren
)paren
suffix:semicolon
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
DECL|variable|enable_kernel_fp
id|EXPORT_SYMBOL
c_func
(paren
id|enable_kernel_fp
)paren
suffix:semicolon
DECL|function|dump_task_fpu
r_int
id|dump_task_fpu
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
id|elf_fpregset_t
op_star
id|fpregs
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|tsk-&gt;thread.regs
)paren
r_return
l_int|0
suffix:semicolon
id|flush_fp_to_thread
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
id|tsk-&gt;thread.fpr
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
macro_line|#ifdef CONFIG_ALTIVEC
DECL|function|enable_kernel_altivec
r_void
id|enable_kernel_altivec
c_func
(paren
r_void
)paren
(brace
id|WARN_ON
c_func
(paren
id|preemptible
c_func
(paren
)paren
)paren
suffix:semicolon
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
multiline_comment|/* just enables FP for kernel */
macro_line|#else
id|giveup_altivec
c_func
(paren
id|last_task_used_altivec
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SMP */
)brace
DECL|variable|enable_kernel_altivec
id|EXPORT_SYMBOL
c_func
(paren
id|enable_kernel_altivec
)paren
suffix:semicolon
multiline_comment|/*&n; * Make sure the VMX/Altivec register state in the&n; * the thread_struct is up to date for task tsk.&n; */
DECL|function|flush_altivec_to_thread
r_void
id|flush_altivec_to_thread
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
macro_line|#ifdef CONFIG_ALTIVEC
r_if
c_cond
(paren
id|tsk-&gt;thread.regs
)paren
(brace
id|preempt_disable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tsk-&gt;thread.regs-&gt;msr
op_amp
id|MSR_VEC
)paren
(brace
macro_line|#ifdef CONFIG_SMP
id|BUG_ON
c_func
(paren
id|tsk
op_ne
id|current
)paren
suffix:semicolon
macro_line|#endif
id|giveup_altivec
c_func
(paren
id|current
)paren
suffix:semicolon
)brace
id|preempt_enable
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|dump_task_altivec
r_int
id|dump_task_altivec
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
id|flush_altivec_to_thread
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
macro_line|#endif /* CONFIG_ALTIVEC */
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
id|flags
suffix:semicolon
r_struct
id|task_struct
op_star
id|last
suffix:semicolon
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
macro_line|#ifdef CONFIG_ALTIVEC
r_if
c_cond
(paren
id|prev-&gt;thread.regs
op_logical_and
(paren
id|prev-&gt;thread.regs-&gt;msr
op_amp
id|MSR_VEC
)paren
)paren
id|giveup_altivec
c_func
(paren
id|prev
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_ALTIVEC */
macro_line|#endif /* CONFIG_SMP */
macro_line|#if defined(CONFIG_ALTIVEC) &amp;&amp; !defined(CONFIG_SMP)
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
macro_line|#endif /* CONFIG_ALTIVEC */
id|flush_tlb_pending
c_func
(paren
)paren
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
id|local_irq_save
c_func
(paren
id|flags
)paren
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
id|flags
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
suffix:semicolon
r_int
r_int
id|trap
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;NIP: %016lX XER: %016lX LR: %016lX&bslash;n&quot;
comma
id|regs-&gt;nip
comma
id|regs-&gt;xer
comma
id|regs-&gt;link
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;REGS: %p TRAP: %04lx   %s  (%s)&bslash;n&quot;
comma
id|regs
comma
id|regs-&gt;trap
comma
id|print_tainted
c_func
(paren
)paren
comma
id|UTS_RELEASE
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;MSR: %016lx EE: %01x PR: %01x FP: %01x ME: %01x IR/DR: %01x%01x&bslash;n&quot;
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
l_int|0x380
op_logical_or
id|trap
op_eq
l_int|0x600
)paren
id|printk
c_func
(paren
l_string|&quot;DAR: %016lx, DSISR: %016lx&bslash;n&quot;
comma
id|regs-&gt;dar
comma
id|regs-&gt;dsisr
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;TASK: %p[%d] &squot;%s&squot; THREAD: %p&quot;
comma
id|current
comma
id|current-&gt;pid
comma
id|current-&gt;comm
comma
id|current-&gt;thread_info
)paren
suffix:semicolon
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
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
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
)brace
id|printk
c_func
(paren
l_string|&quot;%016lX &quot;
comma
id|regs-&gt;gpr
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
l_int|13
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
multiline_comment|/*&n;&t; * Lookup NIP late so we have the best change of getting the&n;&t; * above info out without failing&n;&t; */
id|printk
c_func
(paren
l_string|&quot;NIP [%016lx] &quot;
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;LR [%016lx] &quot;
comma
id|regs-&gt;link
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|regs-&gt;link
)paren
suffix:semicolon
id|show_stack
c_func
(paren
id|current
comma
(paren
r_int
r_int
op_star
)paren
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
macro_line|#ifndef CONFIG_SMP
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
macro_line|#ifdef CONFIG_ALTIVEC
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
macro_line|#endif /* CONFIG_ALTIVEC */
macro_line|#endif /* CONFIG_SMP */
)brace
DECL|function|flush_thread
r_void
id|flush_thread
c_func
(paren
r_void
)paren
(brace
r_struct
id|thread_info
op_star
id|t
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|t-&gt;flags
op_amp
id|_TIF_ABI_PENDING
)paren
id|t-&gt;flags
op_xor_assign
(paren
id|_TIF_ABI_PENDING
op_or
id|_TIF_32BIT
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
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
macro_line|#ifdef CONFIG_ALTIVEC
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
macro_line|#endif /* CONFIG_ALTIVEC */
macro_line|#endif /* CONFIG_SMP */
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
id|flush_fp_to_thread
c_func
(paren
id|current
)paren
suffix:semicolon
id|flush_altivec_to_thread
c_func
(paren
id|current
)paren
suffix:semicolon
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
id|p-&gt;set_child_tid
op_assign
id|p-&gt;clear_child_tid
op_assign
l_int|NULL
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
multiline_comment|/* for kernel thread, set stackptr in new task */
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
id|p-&gt;thread.regs
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* no user register state */
id|clear_ti_thread_flag
c_func
(paren
id|p-&gt;thread_info
comma
id|TIF_32BIT
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
id|set_ti_thread_flag
c_func
(paren
id|p-&gt;thread_info
comma
id|TIF_RUN_LIGHT
)paren
suffix:semicolon
macro_line|#endif
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
(brace
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
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
r_else
id|childregs-&gt;gpr
(braket
l_int|13
)braket
op_assign
id|childregs-&gt;gpr
(braket
l_int|6
)braket
suffix:semicolon
)brace
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
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_SLB
)paren
(brace
r_int
r_int
id|sp_vsid
op_assign
id|get_kernel_vsid
c_func
(paren
id|sp
)paren
suffix:semicolon
id|sp_vsid
op_lshift_assign
id|SLB_VSID_SHIFT
suffix:semicolon
id|sp_vsid
op_or_assign
id|SLB_VSID_KERNEL
suffix:semicolon
r_if
c_cond
(paren
id|cur_cpu_spec-&gt;cpu_features
op_amp
id|CPU_FTR_16M_PAGE
)paren
id|sp_vsid
op_or_assign
id|SLB_VSID_L
suffix:semicolon
id|p-&gt;thread.ksp_vsid
op_assign
id|sp_vsid
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The PPC64 ABI makes use of a TOC to contain function &n;&t; * pointers.  The function (ret_from_except) is actually a pointer&n;&t; * to the TOC entry.  The first entry is a pointer to the actual&n;&t; * function.&n; &t; */
id|kregs-&gt;nip
op_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|ret_from_fork
)paren
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
id|fdptr
comma
r_int
r_int
id|sp
)paren
(brace
r_int
r_int
id|entry
comma
id|toc
comma
id|load_addr
op_assign
id|regs-&gt;gpr
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/* fdptr is a relocated pointer to the function descriptor for&n;         * the elf _start routine.  The first entry in the function&n;         * descriptor is the entry address of _start and the second&n;         * entry is the TOC value we need to use.&n;         */
id|set_fs
c_func
(paren
id|USER_DS
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|entry
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|fdptr
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|toc
comma
(paren
r_int
r_int
id|__user
op_star
)paren
id|fdptr
op_plus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Check whether the e_entry function descriptor entries&n;&t; * need to be relocated before we can use them.&n;&t; */
r_if
c_cond
(paren
id|load_addr
op_ne
l_int|0
)paren
(brace
id|entry
op_add_assign
id|load_addr
suffix:semicolon
id|toc
op_add_assign
id|load_addr
suffix:semicolon
)brace
id|regs-&gt;nip
op_assign
id|entry
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_assign
id|sp
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|2
)braket
op_assign
id|toc
suffix:semicolon
id|regs-&gt;msr
op_assign
id|MSR_USER64
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
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
macro_line|#endif /* CONFIG_SMP */
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
macro_line|#ifndef CONFIG_SMP
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
macro_line|#endif /* CONFIG_SMP */
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
id|current-&gt;thread.vscr.u
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.vscr.u
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.vscr.u
(braket
l_int|2
)braket
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.vscr.u
(braket
l_int|3
)braket
op_assign
l_int|0x00010000
suffix:semicolon
multiline_comment|/* Java mode disabled */
id|current-&gt;thread.vrsave
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.used_vr
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
id|__user
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
id|p2
comma
r_int
r_int
id|p3
comma
r_int
r_int
id|p4
comma
r_int
r_int
id|p5
comma
r_int
r_int
id|p6
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|parent_tidptr
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|child_tidptr
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|p2
op_eq
l_int|0
)paren
id|p2
op_assign
id|regs-&gt;gpr
(braket
l_int|1
)braket
suffix:semicolon
multiline_comment|/* stack pointer for child */
r_if
c_cond
(paren
id|clone_flags
op_amp
(paren
id|CLONE_PARENT_SETTID
op_or
id|CLONE_CHILD_SETTID
op_or
id|CLONE_CHILD_CLEARTID
)paren
)paren
(brace
id|parent_tidptr
op_assign
id|p3
suffix:semicolon
id|child_tidptr
op_assign
id|p5
suffix:semicolon
r_if
c_cond
(paren
id|test_thread_flag
c_func
(paren
id|TIF_32BIT
)paren
)paren
(brace
id|parent_tidptr
op_and_assign
l_int|0xffffffff
suffix:semicolon
id|child_tidptr
op_and_assign
l_int|0xffffffff
suffix:semicolon
)brace
)brace
r_return
id|do_fork
c_func
(paren
id|clone_flags
comma
id|p2
comma
id|regs
comma
l_int|0
comma
(paren
r_int
id|__user
op_star
)paren
id|parent_tidptr
comma
(paren
r_int
id|__user
op_star
)paren
id|child_tidptr
)paren
suffix:semicolon
)brace
DECL|function|sys_fork
r_int
id|sys_fork
c_func
(paren
r_int
r_int
id|p1
comma
r_int
r_int
id|p2
comma
r_int
r_int
id|p3
comma
r_int
r_int
id|p4
comma
r_int
r_int
id|p5
comma
r_int
r_int
id|p6
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
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
)brace
DECL|function|sys_vfork
r_int
id|sys_vfork
c_func
(paren
r_int
r_int
id|p1
comma
r_int
r_int
id|p2
comma
r_int
r_int
id|p3
comma
r_int
r_int
id|p4
comma
r_int
r_int
id|p5
comma
r_int
r_int
id|p6
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
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
id|__user
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
id|flush_fp_to_thread
c_func
(paren
id|current
)paren
suffix:semicolon
id|flush_altivec_to_thread
c_func
(paren
id|current
)paren
suffix:semicolon
id|error
op_assign
id|do_execve
c_func
(paren
id|filename
comma
(paren
r_char
id|__user
op_star
id|__user
op_star
)paren
id|a1
comma
(paren
r_char
id|__user
op_star
id|__user
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
DECL|variable|kstack_depth_to_print
r_static
r_int
id|kstack_depth_to_print
op_assign
l_int|64
suffix:semicolon
DECL|function|validate_sp
r_static
r_int
id|validate_sp
c_func
(paren
r_int
r_int
id|sp
comma
r_struct
id|task_struct
op_star
id|p
comma
r_int
r_int
id|nbytes
)paren
(brace
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
r_if
c_cond
(paren
id|sp
op_ge
id|stack_page
op_plus
r_sizeof
(paren
r_struct
id|thread_struct
)paren
op_logical_and
id|sp
op_le
id|stack_page
op_plus
id|THREAD_SIZE
op_minus
id|nbytes
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#ifdef CONFIG_IRQSTACKS
id|stack_page
op_assign
(paren
r_int
r_int
)paren
id|hardirq_ctx
(braket
id|task_cpu
c_func
(paren
id|p
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sp
op_ge
id|stack_page
op_plus
r_sizeof
(paren
r_struct
id|thread_struct
)paren
op_logical_and
id|sp
op_le
id|stack_page
op_plus
id|THREAD_SIZE
op_minus
id|nbytes
)paren
r_return
l_int|1
suffix:semicolon
id|stack_page
op_assign
(paren
r_int
r_int
)paren
id|softirq_ctx
(braket
id|task_cpu
c_func
(paren
id|p
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|sp
op_ge
id|stack_page
op_plus
r_sizeof
(paren
r_struct
id|thread_struct
)paren
op_logical_and
id|sp
op_le
id|stack_page
op_plus
id|THREAD_SIZE
op_minus
id|nbytes
)paren
r_return
l_int|1
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
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
r_if
c_cond
(paren
op_logical_neg
id|validate_sp
c_func
(paren
id|sp
comma
id|p
comma
l_int|112
)paren
)paren
r_return
l_int|0
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
op_logical_neg
id|validate_sp
c_func
(paren
id|sp
comma
id|p
comma
l_int|112
)paren
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
l_int|16
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|in_sched_functions
c_func
(paren
id|ip
)paren
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
DECL|function|show_stack
r_void
id|show_stack
c_func
(paren
r_struct
id|task_struct
op_star
id|p
comma
r_int
r_int
op_star
id|_sp
)paren
(brace
r_int
r_int
id|ip
comma
id|newsp
comma
id|lr
suffix:semicolon
r_int
id|count
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|sp
op_assign
(paren
r_int
r_int
)paren
id|_sp
suffix:semicolon
r_int
id|firstframe
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sp
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|p
)paren
(brace
id|sp
op_assign
id|p-&gt;thread.ksp
suffix:semicolon
)brace
r_else
(brace
id|sp
op_assign
id|__get_SP
c_func
(paren
)paren
suffix:semicolon
id|p
op_assign
id|current
suffix:semicolon
)brace
)brace
id|lr
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Call Trace:&bslash;n&quot;
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|validate_sp
c_func
(paren
id|sp
comma
id|p
comma
l_int|112
)paren
)paren
r_return
suffix:semicolon
id|_sp
op_assign
(paren
r_int
r_int
op_star
)paren
id|sp
suffix:semicolon
id|newsp
op_assign
id|_sp
(braket
l_int|0
)braket
suffix:semicolon
id|ip
op_assign
id|_sp
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|firstframe
op_logical_or
id|ip
op_ne
id|lr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;[%016lx] [%016lx] &quot;
comma
id|sp
comma
id|ip
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot;%s&quot;
comma
id|ip
)paren
suffix:semicolon
r_if
c_cond
(paren
id|firstframe
)paren
id|printk
c_func
(paren
l_string|&quot; (unreliable)&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|firstframe
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * See if this is an exception frame.&n;&t;&t; * We look for the &quot;regshere&quot; marker in the current frame.&n;&t;&t; */
r_if
c_cond
(paren
id|validate_sp
c_func
(paren
id|sp
comma
id|p
comma
r_sizeof
(paren
r_struct
id|pt_regs
)paren
op_plus
l_int|400
)paren
op_logical_and
id|_sp
(braket
l_int|12
)braket
op_eq
l_int|0x7265677368657265ul
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
(paren
id|sp
op_plus
id|STACK_FRAME_OVERHEAD
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;--- Exception: %lx&quot;
comma
id|regs-&gt;trap
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot; at %s&bslash;n&quot;
comma
id|regs-&gt;nip
)paren
suffix:semicolon
id|lr
op_assign
id|regs-&gt;link
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot;    LR = %s&bslash;n&quot;
comma
id|lr
)paren
suffix:semicolon
id|firstframe
op_assign
l_int|1
suffix:semicolon
)brace
id|sp
op_assign
id|newsp
suffix:semicolon
)brace
r_while
c_loop
(paren
id|count
op_increment
OL
id|kstack_depth_to_print
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
id|show_stack
c_func
(paren
id|current
comma
(paren
r_int
r_int
op_star
)paren
id|__get_SP
c_func
(paren
)paren
)paren
suffix:semicolon
)brace
DECL|variable|dump_stack
id|EXPORT_SYMBOL
c_func
(paren
id|dump_stack
)paren
suffix:semicolon
eof
