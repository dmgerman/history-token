multiline_comment|/*&n; *  linux/arch/arm/kernel/traps.c&n; *&n; *  Copyright (C) 1995-2002 Russell King&n; *  Fragments that appear the same as linux/arch/i386/kernel/traps.c (C) Linus Torvalds&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  &squot;traps.c&squot; handles hardware exceptions after we have saved some state in&n; *  &squot;linux/arch/arm/lib/traps.S&squot;.  Mostly a debugging aid, but will probably&n; *  kill the offending process.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/personality.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/elf.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/unistd.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &quot;ptrace.h&quot;
r_extern
r_void
id|c_backtrace
(paren
r_int
r_int
id|fp
comma
r_int
id|pmode
)paren
suffix:semicolon
r_extern
r_void
id|show_pte
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|variable|processor_modes
r_const
r_char
op_star
id|processor_modes
(braket
)braket
op_assign
(brace
l_string|&quot;USER_26&quot;
comma
l_string|&quot;FIQ_26&quot;
comma
l_string|&quot;IRQ_26&quot;
comma
l_string|&quot;SVC_26&quot;
comma
l_string|&quot;UK4_26&quot;
comma
l_string|&quot;UK5_26&quot;
comma
l_string|&quot;UK6_26&quot;
comma
l_string|&quot;UK7_26&quot;
comma
l_string|&quot;UK8_26&quot;
comma
l_string|&quot;UK9_26&quot;
comma
l_string|&quot;UK10_26&quot;
comma
l_string|&quot;UK11_26&quot;
comma
l_string|&quot;UK12_26&quot;
comma
l_string|&quot;UK13_26&quot;
comma
l_string|&quot;UK14_26&quot;
comma
l_string|&quot;UK15_26&quot;
comma
l_string|&quot;USER_32&quot;
comma
l_string|&quot;FIQ_32&quot;
comma
l_string|&quot;IRQ_32&quot;
comma
l_string|&quot;SVC_32&quot;
comma
l_string|&quot;UK4_32&quot;
comma
l_string|&quot;UK5_32&quot;
comma
l_string|&quot;UK6_32&quot;
comma
l_string|&quot;ABT_32&quot;
comma
l_string|&quot;UK8_32&quot;
comma
l_string|&quot;UK9_32&quot;
comma
l_string|&quot;UK10_32&quot;
comma
l_string|&quot;UND_32&quot;
comma
l_string|&quot;UK12_32&quot;
comma
l_string|&quot;UK13_32&quot;
comma
l_string|&quot;UK14_32&quot;
comma
l_string|&quot;SYS_32&quot;
)brace
suffix:semicolon
DECL|variable|handler
r_static
r_const
r_char
op_star
id|handler
(braket
)braket
op_assign
(brace
l_string|&quot;prefetch abort&quot;
comma
l_string|&quot;data abort&quot;
comma
l_string|&quot;address exception&quot;
comma
l_string|&quot;interrupt&quot;
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_USER
DECL|variable|user_debug
r_int
r_int
id|user_debug
suffix:semicolon
DECL|function|user_debug_setup
r_static
r_int
id|__init
id|user_debug_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
id|get_option
c_func
(paren
op_amp
id|str
comma
op_amp
id|user_debug
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;user_debug=&quot;
comma
id|user_debug_setup
)paren
suffix:semicolon
macro_line|#endif
DECL|function|dump_backtrace_entry
r_void
id|dump_backtrace_entry
c_func
(paren
r_int
r_int
id|where
comma
r_int
r_int
id|from
)paren
(brace
macro_line|#ifdef CONFIG_KALLSYMS
id|printk
c_func
(paren
l_string|&quot;[&lt;%08lx&gt;] &quot;
comma
id|where
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot;(%s) &quot;
comma
id|where
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;from [&lt;%08lx&gt;] &quot;
comma
id|from
)paren
suffix:semicolon
id|print_symbol
c_func
(paren
l_string|&quot;(%s)&bslash;n&quot;
comma
id|from
)paren
suffix:semicolon
macro_line|#else
id|printk
c_func
(paren
l_string|&quot;Function entered at [&lt;%08lx&gt;] from [&lt;%08lx&gt;]&bslash;n&quot;
comma
id|where
comma
id|from
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Stack pointers should always be within the kernels view of&n; * physical memory.  If it is not there, then we can&squot;t dump&n; * out any information relating to the stack.&n; */
DECL|function|verify_stack
r_static
r_int
id|verify_stack
c_func
(paren
r_int
r_int
id|sp
)paren
(brace
r_if
c_cond
(paren
id|sp
OL
id|PAGE_OFFSET
op_logical_or
(paren
id|sp
OG
(paren
r_int
r_int
)paren
id|high_memory
op_logical_and
id|high_memory
op_ne
l_int|0
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
multiline_comment|/*&n; * Dump out the contents of some memory nicely...&n; */
DECL|function|dump_mem
r_static
r_void
id|dump_mem
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_int
r_int
id|bottom
comma
r_int
r_int
id|top
)paren
(brace
r_int
r_int
id|p
op_assign
id|bottom
op_amp
op_complement
l_int|31
suffix:semicolon
id|mm_segment_t
id|fs
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * We need to switch to kernel mode so that we can use __get_user&n;&t; * to safely read from kernel space.  Note that we now dump the&n;&t; * code first, just in case the backtrace kills us.&n;&t; */
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s(0x%08lx to 0x%08lx)&bslash;n&quot;
comma
id|str
comma
id|bottom
comma
id|top
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
id|bottom
op_amp
op_complement
l_int|31
suffix:semicolon
id|p
OL
id|top
suffix:semicolon
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%04lx: &quot;
comma
id|p
op_amp
l_int|0xffff
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
l_int|8
suffix:semicolon
id|i
op_increment
comma
id|p
op_add_assign
l_int|4
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
r_if
c_cond
(paren
id|p
OL
id|bottom
op_logical_or
id|p
op_ge
id|top
)paren
id|printk
c_func
(paren
l_string|&quot;         &quot;
)paren
suffix:semicolon
r_else
(brace
id|__get_user
c_func
(paren
id|val
comma
(paren
r_int
r_int
op_star
)paren
id|p
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%08x &quot;
comma
id|val
)paren
suffix:semicolon
)brace
)brace
id|printk
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
)brace
DECL|function|dump_instr
r_static
r_void
id|dump_instr
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|addr
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_const
r_int
id|thumb
op_assign
id|thumb_mode
c_func
(paren
id|regs
)paren
suffix:semicolon
r_const
r_int
id|width
op_assign
id|thumb
ques
c_cond
l_int|4
suffix:colon
l_int|8
suffix:semicolon
id|mm_segment_t
id|fs
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * We need to switch to kernel mode so that we can use __get_user&n;&t; * to safely read from kernel space.  Note that we now dump the&n;&t; * code first, just in case the backtrace kills us.&n;&t; */
id|fs
op_assign
id|get_fs
c_func
(paren
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|KERNEL_DS
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Code: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
op_minus
l_int|4
suffix:semicolon
id|i
OL
l_int|1
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|val
comma
id|bad
suffix:semicolon
r_if
c_cond
(paren
id|thumb
)paren
id|bad
op_assign
id|__get_user
c_func
(paren
id|val
comma
op_amp
(paren
(paren
id|u16
op_star
)paren
id|addr
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
r_else
id|bad
op_assign
id|__get_user
c_func
(paren
id|val
comma
op_amp
(paren
(paren
id|u32
op_star
)paren
id|addr
)paren
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|bad
)paren
id|printk
c_func
(paren
id|i
op_eq
l_int|0
ques
c_cond
l_string|&quot;(%0*x) &quot;
suffix:colon
l_string|&quot;%0*x &quot;
comma
id|width
comma
id|val
)paren
suffix:semicolon
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;bad PC value.&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
id|set_fs
c_func
(paren
id|fs
)paren
suffix:semicolon
)brace
DECL|function|dump_backtrace
r_static
r_void
id|dump_backtrace
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_int
r_int
id|fp
suffix:semicolon
r_int
id|ok
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Backtrace: &quot;
)paren
suffix:semicolon
id|fp
op_assign
id|regs-&gt;ARM_fp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;no frame pointer&quot;
)paren
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|verify_stack
c_func
(paren
id|fp
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;invalid frame pointer 0x%08x&quot;
comma
id|fp
)paren
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|fp
OL
(paren
r_int
r_int
)paren
(paren
id|tsk-&gt;thread_info
op_plus
l_int|1
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;frame pointer underflow&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ok
)paren
id|c_backtrace
c_func
(paren
id|fp
comma
id|processor_mode
c_func
(paren
id|regs
)paren
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
macro_line|#ifdef CONFIG_DEBUG_ERRORS
id|__backtrace
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
DECL|variable|dump_stack
id|EXPORT_SYMBOL
c_func
(paren
id|dump_stack
)paren
suffix:semicolon
DECL|function|show_stack
r_void
id|show_stack
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_int
r_int
op_star
id|sp
)paren
(brace
r_int
r_int
id|fp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tsk
)paren
id|tsk
op_assign
id|current
suffix:semicolon
r_if
c_cond
(paren
id|tsk
op_ne
id|current
)paren
id|fp
op_assign
id|thread_saved_fp
c_func
(paren
id|tsk
)paren
suffix:semicolon
r_else
id|asm
c_func
(paren
l_string|&quot;mov%? %0, fp&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|fp
)paren
)paren
suffix:semicolon
id|c_backtrace
c_func
(paren
id|fp
comma
l_int|0x10
)paren
suffix:semicolon
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|die_lock
id|spinlock_t
id|die_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * This function is protected against re-entrancy.&n; */
DECL|function|die
id|NORET_TYPE
r_void
id|die
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
(brace
r_struct
id|task_struct
op_star
id|tsk
op_assign
id|current
suffix:semicolon
r_static
r_int
id|die_counter
suffix:semicolon
id|console_verbose
c_func
(paren
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|die_lock
)paren
suffix:semicolon
id|bust_spinlocks
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Internal error: %s: %x [#%d]&bslash;n&quot;
comma
id|str
comma
id|err
comma
op_increment
id|die_counter
)paren
suffix:semicolon
id|print_modules
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;CPU: %d&bslash;n&quot;
comma
id|smp_processor_id
c_func
(paren
)paren
)paren
suffix:semicolon
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Process %s (pid: %d, stack limit = 0x%p)&bslash;n&quot;
comma
id|tsk-&gt;comm
comma
id|tsk-&gt;pid
comma
id|tsk-&gt;thread_info
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
op_logical_or
id|in_interrupt
c_func
(paren
)paren
)paren
(brace
id|dump_mem
c_func
(paren
l_string|&quot;Stack: &quot;
comma
id|regs-&gt;ARM_sp
comma
l_int|8192
op_plus
(paren
r_int
r_int
)paren
id|tsk-&gt;thread_info
)paren
suffix:semicolon
id|dump_backtrace
c_func
(paren
id|regs
comma
id|tsk
)paren
suffix:semicolon
id|dump_instr
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
id|bust_spinlocks
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|die_lock
)paren
suffix:semicolon
id|do_exit
c_func
(paren
id|SIGSEGV
)paren
suffix:semicolon
)brace
DECL|function|die_if_kernel
r_void
id|die_if_kernel
c_func
(paren
r_const
r_char
op_star
id|str
comma
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|err
)paren
(brace
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
r_return
suffix:semicolon
id|die
c_func
(paren
id|str
comma
id|regs
comma
id|err
)paren
suffix:semicolon
)brace
r_static
id|LIST_HEAD
c_func
(paren
id|undef_hook
)paren
suffix:semicolon
DECL|variable|undef_lock
r_static
id|spinlock_t
id|undef_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|function|register_undef_hook
r_void
id|register_undef_hook
c_func
(paren
r_struct
id|undef_hook
op_star
id|hook
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|undef_lock
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|hook-&gt;node
comma
op_amp
id|undef_hook
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|undef_lock
)paren
suffix:semicolon
)brace
DECL|function|unregister_undef_hook
r_void
id|unregister_undef_hook
c_func
(paren
r_struct
id|undef_hook
op_star
id|hook
)paren
(brace
id|spin_lock_irq
c_func
(paren
op_amp
id|undef_lock
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|hook-&gt;node
)paren
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|undef_lock
)paren
suffix:semicolon
)brace
DECL|function|do_undefinstr
id|asmlinkage
r_void
id|do_undefinstr
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|correction
op_assign
id|thumb_mode
c_func
(paren
id|regs
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|4
suffix:semicolon
r_int
r_int
id|instr
suffix:semicolon
r_struct
id|undef_hook
op_star
id|hook
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
r_void
op_star
id|pc
suffix:semicolon
multiline_comment|/*&n;&t; * According to the ARM ARM, PC is 2 or 4 bytes ahead,&n;&t; * depending whether we&squot;re in Thumb mode or not.&n;&t; * Correct this offset.&n;&t; */
id|regs-&gt;ARM_pc
op_sub_assign
id|correction
suffix:semicolon
id|pc
op_assign
(paren
r_void
op_star
)paren
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|thumb_mode
c_func
(paren
id|regs
)paren
)paren
(brace
id|get_user
c_func
(paren
id|instr
comma
(paren
id|u16
op_star
)paren
id|pc
)paren
suffix:semicolon
)brace
r_else
(brace
id|get_user
c_func
(paren
id|instr
comma
(paren
id|u32
op_star
)paren
id|pc
)paren
suffix:semicolon
)brace
id|spin_lock_irq
c_func
(paren
op_amp
id|undef_lock
)paren
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|hook
comma
op_amp
id|undef_hook
comma
id|node
)paren
(brace
r_if
c_cond
(paren
(paren
id|instr
op_amp
id|hook-&gt;instr_mask
)paren
op_eq
id|hook-&gt;instr_val
op_logical_and
(paren
id|regs-&gt;ARM_cpsr
op_amp
id|hook-&gt;cpsr_mask
)paren
op_eq
id|hook-&gt;cpsr_val
)paren
(brace
r_if
c_cond
(paren
id|hook
op_member_access_from_pointer
id|fn
c_func
(paren
id|regs
comma
id|instr
)paren
op_eq
l_int|0
)paren
(brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|undef_lock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|undef_lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_USER
r_if
c_cond
(paren
id|user_debug
op_amp
id|UDBG_UNDEFINED
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s (%d): undefined instruction: pc=%p&bslash;n&quot;
comma
id|current-&gt;comm
comma
id|current-&gt;pid
comma
id|pc
)paren
suffix:semicolon
id|dump_instr
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
id|current-&gt;thread.error_code
op_assign
l_int|0
suffix:semicolon
id|current-&gt;thread.trap_no
op_assign
l_int|6
suffix:semicolon
id|info.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|ILL_ILLOPC
suffix:semicolon
id|info.si_addr
op_assign
id|pc
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops - undefined instruction&quot;
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|do_unexp_fiq
id|asmlinkage
r_void
id|do_unexp_fiq
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
macro_line|#ifndef CONFIG_IGNORE_FIQ
id|printk
c_func
(paren
l_string|&quot;Hmm.  Unexpected FIQ received, but trying to continue&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;You may have a hardware problem...&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * bad_mode handles the impossible case in the vectors.  If you see one of&n; * these, then it&squot;s extremely serious, and could mean you have buggy hardware.&n; * It never returns, and never tries to sync.  We hope that we can at least&n; * dump out some state information...&n; */
DECL|function|bad_mode
id|asmlinkage
r_void
id|bad_mode
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|reason
comma
r_int
id|proc_mode
)paren
(brace
r_int
r_int
id|vectors
op_assign
id|vectors_base
c_func
(paren
)paren
suffix:semicolon
id|console_verbose
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Bad mode in %s handler detected: mode %s&bslash;n&quot;
comma
id|handler
(braket
id|reason
)braket
comma
id|processor_modes
(braket
id|proc_mode
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Dump out the vectors and stub routines.  Maybe a better solution&n;&t; * would be to dump them out only if we detect that they are corrupted.&n;&t; */
id|dump_mem
c_func
(paren
id|KERN_CRIT
l_string|&quot;Vectors: &quot;
comma
id|vectors
comma
id|vectors
op_plus
l_int|0x40
)paren
suffix:semicolon
id|dump_mem
c_func
(paren
id|KERN_CRIT
l_string|&quot;Stubs: &quot;
comma
id|vectors
op_plus
l_int|0x200
comma
id|vectors
op_plus
l_int|0x4b8
)paren
suffix:semicolon
id|die
c_func
(paren
l_string|&quot;Oops - bad mode&quot;
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;bad mode&quot;
)paren
suffix:semicolon
)brace
DECL|function|bad_syscall
r_static
r_int
id|bad_syscall
c_func
(paren
r_int
id|n
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|thread_info
op_star
id|thread
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
r_if
c_cond
(paren
id|current-&gt;personality
op_ne
id|PER_LINUX
op_logical_and
id|thread-&gt;exec_domain-&gt;handler
)paren
(brace
id|thread-&gt;exec_domain
op_member_access_from_pointer
id|handler
c_func
(paren
id|n
comma
id|regs
)paren
suffix:semicolon
r_return
id|regs-&gt;ARM_r0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DEBUG_USER
r_if
c_cond
(paren
id|user_debug
op_amp
id|UDBG_SYSCALL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;[%d] %s: obsolete system call %08x.&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
comma
id|n
)paren
suffix:semicolon
id|dump_instr
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif
id|info.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|ILL_ILLTRP
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|instruction_pointer
c_func
(paren
id|regs
)paren
op_minus
(paren
id|thumb_mode
c_func
(paren
id|regs
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|4
)paren
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops - bad syscall&quot;
comma
id|regs
comma
id|n
)paren
suffix:semicolon
r_return
id|regs-&gt;ARM_r0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|do_cache_op
id|do_cache_op
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
comma
r_int
id|flags
)paren
(brace
r_struct
id|vm_area_struct
op_star
id|vma
suffix:semicolon
r_if
c_cond
(paren
id|end
OL
id|start
)paren
r_return
suffix:semicolon
id|vma
op_assign
id|find_vma
c_func
(paren
id|current-&gt;active_mm
comma
id|start
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vma
op_logical_and
id|vma-&gt;vm_start
OL
id|end
)paren
(brace
r_if
c_cond
(paren
id|start
OL
id|vma-&gt;vm_start
)paren
id|start
op_assign
id|vma-&gt;vm_start
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|vma-&gt;vm_end
)paren
id|end
op_assign
id|vma-&gt;vm_end
suffix:semicolon
id|flush_cache_range
c_func
(paren
id|vma
comma
id|start
comma
id|end
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Handle all unrecognised system calls.&n; *  0x9f0000 - 0x9fffff are some more esoteric system calls&n; */
DECL|macro|NR
mdefine_line|#define NR(x) ((__ARM_NR_##x) - __ARM_NR_BASE)
DECL|function|arm_syscall
id|asmlinkage
r_int
id|arm_syscall
c_func
(paren
r_int
id|no
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
r_if
c_cond
(paren
(paren
id|no
op_rshift
l_int|16
)paren
op_ne
l_int|0x9f
)paren
r_return
id|bad_syscall
c_func
(paren
id|no
comma
id|regs
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|no
op_amp
l_int|0xffff
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* branch through 0 */
id|info.si_signo
op_assign
id|SIGSEGV
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|SEGV_MAPERR
suffix:semicolon
id|info.si_addr
op_assign
l_int|NULL
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGSEGV
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;branch through zero&quot;
comma
id|regs
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|NR
c_func
(paren
id|breakpoint
)paren
suffix:colon
multiline_comment|/* SWI BREAK_POINT */
id|regs-&gt;ARM_pc
op_sub_assign
id|thumb_mode
c_func
(paren
id|regs
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|4
suffix:semicolon
id|ptrace_break
c_func
(paren
id|current
comma
id|regs
)paren
suffix:semicolon
r_return
id|regs-&gt;ARM_r0
suffix:semicolon
multiline_comment|/*&n;&t; * Flush a region from virtual address &squot;r0&squot; to virtual address &squot;r1&squot;&n;&t; * _inclusive_.  There is no alignment requirement on either address;&n;&t; * user space does not need to know the hardware cache layout.&n;&t; *&n;&t; * r2 contains flags.  It should ALWAYS be passed as ZERO until it&n;&t; * is defined to be something else.  For now we ignore it, but may&n;&t; * the fires of hell burn in your belly if you break this rule. ;)&n;&t; *&n;&t; * (at a later date, we may want to allow this call to not flush&n;&t; * various aspects of the cache.  Passing &squot;0&squot; will guarantee that&n;&t; * everything necessary gets flushed to maintain consistency in&n;&t; * the specified region).&n;&t; */
r_case
id|NR
c_func
(paren
id|cacheflush
)paren
suffix:colon
id|do_cache_op
c_func
(paren
id|regs-&gt;ARM_r0
comma
id|regs-&gt;ARM_r1
comma
id|regs-&gt;ARM_r2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|NR
c_func
(paren
id|usr26
)paren
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|elf_hwcap
op_amp
id|HWCAP_26BIT
)paren
)paren
r_break
suffix:semicolon
id|regs-&gt;ARM_cpsr
op_and_assign
op_complement
id|MODE32_BIT
suffix:semicolon
r_return
id|regs-&gt;ARM_r0
suffix:semicolon
r_case
id|NR
c_func
(paren
id|usr32
)paren
suffix:colon
r_if
c_cond
(paren
op_logical_neg
(paren
id|elf_hwcap
op_amp
id|HWCAP_26BIT
)paren
)paren
r_break
suffix:semicolon
id|regs-&gt;ARM_cpsr
op_or_assign
id|MODE32_BIT
suffix:semicolon
r_return
id|regs-&gt;ARM_r0
suffix:semicolon
r_default
suffix:colon
(brace
)brace
multiline_comment|/* Calls 9f00xx..9f07ff are defined to return -ENOSYS&n;&t;&t;   if not implemented, rather than raising SIGILL.  This&n;&t;&t;   way the calling program can gracefully determine whether&n;&t;&t;   a feature is supported.  */
r_if
c_cond
(paren
id|no
op_le
l_int|0x7ff
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_DEBUG_USER
multiline_comment|/*&n;&t; * experience shows that these seem to indicate that&n;&t; * something catastrophic has happened&n;&t; */
r_if
c_cond
(paren
id|user_debug
op_amp
id|UDBG_SYSCALL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;[%d] %s: arm syscall %d&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
comma
id|no
)paren
suffix:semicolon
id|dump_instr
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
id|show_regs
c_func
(paren
id|regs
)paren
suffix:semicolon
id|c_backtrace
c_func
(paren
id|regs-&gt;ARM_fp
comma
id|processor_mode
c_func
(paren
id|regs
)paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|info.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|ILL_ILLTRP
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|instruction_pointer
c_func
(paren
id|regs
)paren
op_minus
(paren
id|thumb_mode
c_func
(paren
id|regs
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|4
)paren
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;Oops - bad syscall(2)&quot;
comma
id|regs
comma
id|no
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__bad_xchg
r_void
id|__bad_xchg
c_func
(paren
r_volatile
r_void
op_star
id|ptr
comma
r_int
id|size
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;xchg: bad data size: pc 0x%p, ptr 0x%p, size %d&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
comma
id|ptr
comma
id|size
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * A data abort trap was taken, but we did not handle the instruction.&n; * Try to abort the user program, or panic if it was the kernel.&n; */
id|asmlinkage
r_void
DECL|function|baddataabort
id|baddataabort
c_func
(paren
r_int
id|code
comma
r_int
r_int
id|instr
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|addr
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|siginfo_t
id|info
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_USER
r_if
c_cond
(paren
id|user_debug
op_amp
id|UDBG_BADABORT
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;[%d] %s: bad data abort: code %d instr 0x%08lx&bslash;n&quot;
comma
id|current-&gt;pid
comma
id|current-&gt;comm
comma
id|code
comma
id|instr
)paren
suffix:semicolon
id|dump_instr
c_func
(paren
id|regs
)paren
suffix:semicolon
id|show_pte
c_func
(paren
id|current-&gt;mm
comma
id|addr
)paren
suffix:semicolon
)brace
macro_line|#endif
id|info.si_signo
op_assign
id|SIGILL
suffix:semicolon
id|info.si_errno
op_assign
l_int|0
suffix:semicolon
id|info.si_code
op_assign
id|ILL_ILLOPC
suffix:semicolon
id|info.si_addr
op_assign
(paren
r_void
op_star
)paren
id|addr
suffix:semicolon
id|force_sig_info
c_func
(paren
id|SIGILL
comma
op_amp
id|info
comma
id|current
)paren
suffix:semicolon
id|die_if_kernel
c_func
(paren
l_string|&quot;unknown data abort code&quot;
comma
id|regs
comma
id|instr
)paren
suffix:semicolon
)brace
DECL|function|__bug
r_volatile
r_void
id|__bug
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_void
op_star
id|data
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;kernel BUG at %s:%d!&quot;
comma
id|file
comma
id|line
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
)paren
id|printk
c_func
(paren
l_string|&quot; - extra data = %p&quot;
comma
id|data
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
op_star
(paren
r_int
op_star
)paren
l_int|0
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|__readwrite_bug
r_void
id|__readwrite_bug
c_func
(paren
r_const
r_char
op_star
id|fn
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s called, but not implemented&quot;
comma
id|fn
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__pte_error
r_void
id|__pte_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s:%d: bad pte %08lx.&bslash;n&quot;
comma
id|file
comma
id|line
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|__pmd_error
r_void
id|__pmd_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;
comma
id|file
comma
id|line
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|__pgd_error
r_void
id|__pgd_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;
comma
id|file
comma
id|line
comma
id|val
)paren
suffix:semicolon
)brace
DECL|function|__div0
id|asmlinkage
r_void
id|__div0
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;Division by zero in kernel.&bslash;n&quot;
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|abort
r_void
m_abort
(paren
r_void
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* if that doesn&squot;t kill us, halt */
id|panic
c_func
(paren
l_string|&quot;Oops failed to kill thread&quot;
)paren
suffix:semicolon
)brace
DECL|function|trap_init
r_void
id|__init
id|trap_init
c_func
(paren
r_void
)paren
(brace
r_extern
r_void
id|__trap_init
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_int
r_int
id|base
op_assign
id|vectors_base
c_func
(paren
)paren
suffix:semicolon
id|__trap_init
c_func
(paren
id|base
)paren
suffix:semicolon
id|flush_icache_range
c_func
(paren
id|base
comma
id|base
op_plus
id|PAGE_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|base
op_ne
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Relocating machine vectors to 0x%08lx&bslash;n&quot;
comma
id|base
)paren
suffix:semicolon
id|modify_domain
c_func
(paren
id|DOMAIN_USER
comma
id|DOMAIN_CLIENT
)paren
suffix:semicolon
)brace
eof
