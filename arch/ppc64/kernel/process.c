multiline_comment|/*&n; *  linux/arch/ppc64/kernel/process.c&n; *&n; *  Derived from &quot;arch/i386/kernel/process.c&quot;&n; *    Copyright (C) 1995  Linus Torvalds&n; *&n; *  Updated and modified by Cort Dougan (cort@cs.nmt.edu) and&n; *  Paul Mackerras (paulus@cs.anu.edu.au)&n; *&n; *  PowerPC version &n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
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
macro_line|#include &lt;linux/init_task.h&gt;
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
macro_line|#include &lt;asm/Naca.h&gt;
macro_line|#include &quot;ppc_defs.h&quot;
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
DECL|variable|last_task_used_math
r_struct
id|task_struct
op_star
id|last_task_used_math
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|ioremap_mm
r_struct
id|mm_struct
id|ioremap_mm
op_assign
(brace
id|pgd
suffix:colon
id|ioremap_dir
comma
id|page_table_lock
suffix:colon
id|SPIN_LOCK_UNLOCKED
)brace
suffix:semicolon
DECL|variable|sysmap
r_char
op_star
id|sysmap
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|sysmap_size
r_int
r_int
id|sysmap_size
op_assign
l_int|0
suffix:semicolon
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
r_void
DECL|function|_switch_to
id|_switch_to
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
macro_line|#endif /* CONFIG_SMP */
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
id|__save_and_cli
c_func
(paren
id|flags
)paren
suffix:semicolon
id|_switch
c_func
(paren
id|old_thread
comma
id|new_thread
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
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
id|printk
c_func
(paren
l_string|&quot;NIP: %016lX XER: %016lX LR: %016lX REGS: %p TRAP: %04lx    %s&bslash;n&quot;
comma
id|regs-&gt;nip
comma
id|regs-&gt;xer
comma
id|regs-&gt;link
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
id|printk
c_func
(paren
l_string|&quot;&bslash;nlast math %p &quot;
comma
id|last_task_used_math
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* printk(&quot; CPU: %d last CPU: %d&quot;, current-&gt;processor,current-&gt;last_processor); */
macro_line|#endif /* CONFIG_SMP */
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
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
l_int|4
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;GPR%02d: &quot;
comma
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|r
comma
op_amp
(paren
id|regs-&gt;gpr
(braket
id|i
)braket
)paren
)paren
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%016lX &quot;
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|i
op_mod
l_int|4
)paren
op_eq
l_int|3
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
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
l_int|13
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
id|p-&gt;thread.regs
op_assign
id|childregs
suffix:semicolon
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
multiline_comment|/*&n;&t; * copy fpu info - assume lazy fpu switch now always&n;&t; *  -- Cort&n;&t; */
r_if
c_cond
(paren
id|regs-&gt;msr
op_amp
id|MSR_FP
)paren
(brace
id|giveup_fpu
c_func
(paren
id|current
)paren
suffix:semicolon
id|childregs-&gt;msr
op_and_assign
op_complement
(paren
id|MSR_FP
op_or
id|MSR_FE0
op_or
id|MSR_FE1
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
op_amp
id|p-&gt;thread.fpr
comma
op_amp
id|current-&gt;thread.fpr
comma
r_sizeof
(paren
id|p-&gt;thread.fpr
)paren
)paren
suffix:semicolon
id|p-&gt;thread.fpscr
op_assign
id|current-&gt;thread.fpscr
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
multiline_comment|/* NIP is *really* a pointer to the function descriptor for&n;         * the elf _start routine.  The first entry in the function&n;         * descriptor is the entry address of _start and the second&n;         * entry is the TOC value we need to use.&n;         */
r_int
r_int
op_star
id|entry
op_assign
(paren
r_int
r_int
op_star
)paren
id|nip
suffix:semicolon
r_int
r_int
op_star
id|toc
op_assign
id|entry
op_plus
l_int|1
suffix:semicolon
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
id|memset
c_func
(paren
op_amp
id|regs-&gt;ctr
comma
l_int|0
comma
l_int|4
op_star
r_sizeof
(paren
id|regs-&gt;ctr
)paren
)paren
suffix:semicolon
id|__get_user
c_func
(paren
id|regs-&gt;nip
comma
id|entry
)paren
suffix:semicolon
id|regs-&gt;gpr
(braket
l_int|1
)braket
op_assign
id|sp
suffix:semicolon
id|__get_user
c_func
(paren
id|regs-&gt;gpr
(braket
l_int|2
)braket
comma
id|toc
)paren
suffix:semicolon
id|regs-&gt;msr
op_assign
id|MSR_USER64
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
id|current-&gt;thread.fpscr
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|sys_clone
r_int
id|sys_clone
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
r_return
id|do_fork
c_func
(paren
id|p1
comma
id|regs-&gt;gpr
(braket
l_int|1
)braket
comma
id|regs
comma
l_int|0
)paren
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
)paren
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
DECL|function|initialize_paca_hardware_interrupt_stack
r_void
id|initialize_paca_hardware_interrupt_stack
c_func
(paren
r_void
)paren
(brace
r_extern
r_struct
id|Naca
op_star
id|naca
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|stack
suffix:semicolon
r_int
r_int
id|end_of_stack
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|naca-&gt;processorCount
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Carve out storage for the hardware interrupt stack */
id|stack
op_assign
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|get_order
c_func
(paren
l_int|8
op_star
id|PAGE_SIZE
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stack
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ERROR, cannot find space for hardware stack.&bslash;n&quot;
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot; no hardware stack &quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Store the stack value in the PACA for the processor */
id|xPaca
(braket
id|i
)braket
dot
id|xHrdIntStack
op_assign
id|stack
op_plus
(paren
l_int|8
op_star
id|PAGE_SIZE
)paren
op_minus
id|STACK_FRAME_OVERHEAD
suffix:semicolon
id|xPaca
(braket
id|i
)braket
dot
id|xHrdIntCount
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * __get_free_pages() might give us a page &gt; KERNBASE+256M which&n;&t; * is mapped with large ptes so we can&squot;t set up the guard page.&n;&t; */
r_if
c_cond
(paren
id|__is_processor
c_func
(paren
id|PV_POWER4
)paren
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|naca-&gt;processorCount
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* set page at the top of stack to be protected - prevent overflow */
id|end_of_stack
op_assign
id|xPaca
(braket
id|i
)braket
dot
id|xHrdIntStack
op_minus
(paren
l_int|8
op_star
id|PAGE_SIZE
op_minus
id|STACK_FRAME_OVERHEAD
)paren
suffix:semicolon
id|ppc_md
dot
id|hpte_updateboltedpp
c_func
(paren
id|PP_RXRX
comma
id|end_of_stack
)paren
suffix:semicolon
)brace
)brace
r_extern
r_char
id|_stext
(braket
)braket
comma
id|_etext
(braket
)braket
suffix:semicolon
DECL|function|ppc_find_proc_name
r_char
op_star
id|ppc_find_proc_name
c_func
(paren
r_int
op_star
id|p
comma
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
(brace
r_int
r_int
id|tb_flags
suffix:semicolon
r_int
r_int
id|name_len
suffix:semicolon
r_int
r_int
id|tb_start
comma
id|code_start
comma
id|code_ptr
comma
id|code_offset
suffix:semicolon
r_int
id|code_len
suffix:semicolon
id|strcpy
c_func
(paren
id|buf
comma
l_string|&quot;Unknown&quot;
)paren
suffix:semicolon
id|code_ptr
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
id|code_offset
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
r_int
r_int
)paren
id|p
op_ge
(paren
r_int
r_int
)paren
id|_stext
)paren
op_logical_and
(paren
(paren
r_int
r_int
)paren
id|p
op_le
(paren
r_int
r_int
)paren
id|_etext
)paren
)paren
(brace
r_while
c_loop
(paren
(paren
r_int
r_int
)paren
id|p
op_le
(paren
r_int
r_int
)paren
id|_etext
)paren
(brace
r_if
c_cond
(paren
op_star
id|p
op_eq
l_int|0
)paren
(brace
id|tb_start
op_assign
(paren
r_int
r_int
)paren
id|p
suffix:semicolon
op_increment
id|p
suffix:semicolon
multiline_comment|/* Point to traceback flags */
id|tb_flags
op_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|p
)paren
suffix:semicolon
id|p
op_add_assign
l_int|2
suffix:semicolon
multiline_comment|/* Skip over traceback flags */
r_if
c_cond
(paren
id|tb_flags
op_amp
id|TB_NAME_PRESENT
)paren
(brace
r_if
c_cond
(paren
id|tb_flags
op_amp
id|TB_PARMINFO
)paren
op_increment
id|p
suffix:semicolon
multiline_comment|/* skip over parminfo data */
r_if
c_cond
(paren
id|tb_flags
op_amp
id|TB_HAS_TBOFF
)paren
(brace
id|code_len
op_assign
op_star
id|p
suffix:semicolon
multiline_comment|/* get code length */
id|code_start
op_assign
id|tb_start
op_minus
id|code_len
suffix:semicolon
id|code_offset
op_assign
id|code_ptr
op_minus
id|code_start
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|code_offset
OG
l_int|0x100000
)paren
r_break
suffix:semicolon
op_increment
id|p
suffix:semicolon
multiline_comment|/* skip over code size */
)brace
id|name_len
op_assign
op_star
(paren
(paren
r_int
r_int
op_star
)paren
id|p
)paren
suffix:semicolon
r_if
c_cond
(paren
id|name_len
OG
(paren
id|buflen
op_minus
l_int|20
)paren
)paren
id|name_len
op_assign
id|buflen
op_minus
l_int|20
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
comma
(paren
(paren
r_char
op_star
)paren
id|p
)paren
op_plus
l_int|2
comma
id|name_len
)paren
suffix:semicolon
id|buf
(braket
id|name_len
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|code_offset
)paren
id|sprintf
c_func
(paren
id|buf
op_plus
id|name_len
comma
l_string|&quot;+0x%lx&quot;
comma
id|code_offset
op_minus
l_int|1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
op_increment
id|p
suffix:semicolon
)brace
)brace
r_return
id|buf
suffix:semicolon
)brace
r_void
DECL|function|print_backtrace
id|print_backtrace
c_func
(paren
r_int
r_int
op_star
id|sp
)paren
(brace
r_int
id|cnt
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|i
suffix:semicolon
r_char
id|name_buf
(braket
l_int|256
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Call backtrace: &bslash;n&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sp
)paren
(brace
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|i
comma
op_amp
id|sp
(braket
l_int|2
)braket
)paren
)paren
r_break
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%016lX &quot;
comma
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s&bslash;n&quot;
comma
id|ppc_find_proc_name
c_func
(paren
(paren
r_int
op_star
)paren
id|i
comma
id|name_buf
comma
l_int|256
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cnt
OG
l_int|32
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|__get_user
c_func
(paren
id|sp
comma
(paren
r_int
r_int
op_star
op_star
)paren
id|sp
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
)brace
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
mdefine_line|#define first_sched    (*(unsigned long *)scheduling_functions_start_here)
DECL|macro|last_sched
mdefine_line|#define last_sched     (*(unsigned long *)scheduling_functions_end_here)
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
(paren
id|stack_page
op_plus
r_sizeof
(paren
r_struct
id|thread_struct
)paren
)paren
op_logical_or
id|sp
op_ge
(paren
id|stack_page
op_plus
id|THREAD_SIZE
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
id|ip
OL
id|first_sched
op_logical_or
id|ip
op_ge
id|last_sched
)paren
r_return
(paren
id|ip
op_amp
l_int|0xFFFFFFFF
)paren
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
DECL|function|show_trace_task
r_void
id|show_trace_task
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
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Call Trace: &quot;
)paren
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
(paren
id|stack_page
op_plus
r_sizeof
(paren
r_struct
id|thread_struct
)paren
)paren
op_logical_or
id|sp
op_ge
(paren
id|stack_page
op_plus
id|THREAD_SIZE
)paren
)paren
r_break
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
id|printk
c_func
(paren
l_string|&quot;[%016lx] &quot;
comma
id|ip
)paren
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
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
eof