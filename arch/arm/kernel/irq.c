multiline_comment|/*&n; *  linux/arch/arm/kernel/irq.c&n; *&n; *  Copyright (C) 1992 Linus Torvalds&n; *  Modifications for ARM processor Copyright (C) 1995-2000 Russell King.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  This file contains the code used by various IRQ handling routines:&n; *  asking for different IRQ&squot;s should be done through these routines&n; *  instead of just grabbing them. Thus setups with different IRQ numbers&n; *  shouldn&squot;t result in any weird surprises, and installing new handlers&n; *  should be easier.&n; *&n; *  IRQ&squot;s are in fact implemented a bit like signal handlers for the kernel.&n; *  Naturally it&squot;s not a 1:1 relation, but there are similarities.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
multiline_comment|/*&n; * Maximum IRQ count.  Currently, this is arbitary.  However, it should&n; * not be set too low to prevent false triggering.  Conversely, if it&n; * is set too high, then you could miss a stuck IRQ.&n; *&n; * Maybe we ought to set a timer and re-enable the IRQ at a later time?&n; */
DECL|macro|MAX_IRQ_CNT
mdefine_line|#define MAX_IRQ_CNT&t;100000
DECL|variable|irq_err_count
r_static
r_volatile
r_int
r_int
id|irq_err_count
suffix:semicolon
DECL|variable|irq_controller_lock
r_static
id|spinlock_t
id|irq_controller_lock
suffix:semicolon
DECL|variable|irq_desc
r_struct
id|irqdesc
id|irq_desc
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_void
(paren
op_star
id|init_arch_irq
)paren
(paren
r_void
)paren
id|__initdata
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * Dummy mask/unmask handler&n; */
DECL|function|dummy_mask_unmask_irq
r_void
id|dummy_mask_unmask_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|do_bad_IRQ
r_void
id|do_bad_IRQ
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|irq_err_count
op_add_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;IRQ: spurious interrupt %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|bad_chip
r_static
r_struct
id|irqchip
id|bad_chip
op_assign
(brace
dot
id|ack
op_assign
id|dummy_mask_unmask_irq
comma
dot
id|mask
op_assign
id|dummy_mask_unmask_irq
comma
dot
id|unmask
op_assign
id|dummy_mask_unmask_irq
comma
)brace
suffix:semicolon
DECL|variable|bad_irq_desc
r_static
r_struct
id|irqdesc
id|bad_irq_desc
op_assign
(brace
dot
id|chip
op_assign
op_amp
id|bad_chip
comma
dot
id|handle
op_assign
id|do_bad_IRQ
comma
dot
id|depth
op_assign
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/**&n; *&t;disable_irq - disable an irq and wait for completion&n; *&t;@irq: Interrupt to disable&n; *&n; *&t;Disable the selected interrupt line.  We do this lazily.&n; *&n; *&t;This function may be called from IRQ context.&n; */
DECL|function|disable_irq
r_void
id|disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|irqdesc
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc-&gt;depth
op_increment
)paren
id|desc-&gt;enabled
op_assign
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;enable_irq - enable interrupt handling on an irq&n; *&t;@irq: Interrupt to enable&n; *&n; *&t;Re-enables the processing of interrupts on this IRQ line.&n; *&t;Note that this may call the interrupt handler, so you may&n; *&t;get unexpected results if you hold IRQs disabled.&n; *&n; *&t;This function may be called from IRQ context.&n; */
DECL|function|enable_irq
r_void
id|enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|irqdesc
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|pending
op_assign
l_int|0
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|desc-&gt;depth
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;enable_irq(%u) unbalanced from %p&bslash;n&quot;
comma
id|irq
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|desc-&gt;depth
)paren
(brace
id|desc-&gt;probing
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;enabled
op_assign
l_int|1
suffix:semicolon
id|desc-&gt;chip
op_member_access_from_pointer
id|unmask
c_func
(paren
id|irq
)paren
suffix:semicolon
id|pending
op_assign
id|desc-&gt;pending
suffix:semicolon
id|desc-&gt;pending
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If the interrupt was waiting to be processed,&n;&t;&t; * retrigger it.&n;&t;&t; */
r_if
c_cond
(paren
id|pending
)paren
id|desc-&gt;chip
op_member_access_from_pointer
id|rerun
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|show_interrupts
r_int
id|show_interrupts
c_func
(paren
r_struct
id|seq_file
op_star
id|p
comma
r_void
op_star
id|v
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
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
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|action
op_assign
id|irq_desc
(braket
id|i
)braket
dot
id|action
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_continue
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%3d: %10u &quot;
comma
id|i
comma
id|kstat_irqs
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;  %s&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
r_for
c_loop
(paren
id|action
op_assign
id|action-&gt;next
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
(brace
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;, %s&quot;
comma
id|action-&gt;name
)paren
suffix:semicolon
)brace
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ARCH_ACORN
id|show_fiq_list
c_func
(paren
id|p
comma
id|v
)paren
suffix:semicolon
macro_line|#endif
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;Err: %10lu&bslash;n&quot;
comma
id|irq_err_count
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * IRQ lock detection.&n; *&n; * Hopefully, this should get us out of a few locked situations.&n; * However, it may take a while for this to happen, since we need&n; * a large number if IRQs to appear in the same jiffie with the&n; * same instruction pointer (or within 2 instructions).&n; */
DECL|function|check_irq_lock
r_static
r_int
id|check_irq_lock
c_func
(paren
r_struct
id|irqdesc
op_star
id|desc
comma
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|instr_ptr
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|desc-&gt;lck_jif
op_eq
id|jiffies
op_logical_and
id|desc-&gt;lck_pc
op_ge
id|instr_ptr
op_logical_and
id|desc-&gt;lck_pc
OL
id|instr_ptr
op_plus
l_int|8
)paren
(brace
id|desc-&gt;lck_cnt
op_add_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|desc-&gt;lck_cnt
OG
id|MAX_IRQ_CNT
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;IRQ LOCK: IRQ%d is locking the system, disabled&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
id|desc-&gt;lck_cnt
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;lck_pc
op_assign
id|instruction_pointer
c_func
(paren
id|regs
)paren
suffix:semicolon
id|desc-&gt;lck_jif
op_assign
id|jiffies
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|__do_irq
id|__do_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqaction
op_star
id|action
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|status
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|action-&gt;flags
op_amp
id|SA_INTERRUPT
)paren
)paren
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|status
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|status
op_or_assign
id|action-&gt;flags
suffix:semicolon
id|action
op_member_access_from_pointer
id|handler
c_func
(paren
id|irq
comma
id|action-&gt;dev_id
comma
id|regs
)paren
suffix:semicolon
id|action
op_assign
id|action-&gt;next
suffix:semicolon
)brace
r_while
c_loop
(paren
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
id|SA_SAMPLE_RANDOM
)paren
id|add_interrupt_randomness
c_func
(paren
id|irq
)paren
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is for software-decoded IRQs.  The caller is expected to&n; * handle the ack, clear, mask and unmask issues.&n; */
r_void
DECL|function|do_simple_IRQ
id|do_simple_IRQ
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_const
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|desc-&gt;triggered
op_assign
l_int|1
suffix:semicolon
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
id|action
op_assign
id|desc-&gt;action
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
id|__do_irq
c_func
(paren
id|irq
comma
id|desc-&gt;action
comma
id|regs
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Most edge-triggered IRQ implementations seem to take a broken&n; * approach to this.  Hence the complexity.&n; */
r_void
DECL|function|do_edge_IRQ
id|do_edge_IRQ
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_const
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|desc-&gt;triggered
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * If we&squot;re currently running this IRQ, or its disabled,&n;&t; * we shouldn&squot;t process the IRQ.  Instead, turn on the&n;&t; * hardware masks.&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|desc-&gt;running
op_logical_or
op_logical_neg
id|desc-&gt;enabled
)paren
)paren
r_goto
id|running
suffix:semicolon
multiline_comment|/*&n;&t; * Acknowledge and clear the IRQ, but don&squot;t mask it.&n;&t; */
id|desc-&gt;chip
op_member_access_from_pointer
id|ack
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Mark the IRQ currently in progress.&n;&t; */
id|desc-&gt;running
op_assign
l_int|1
suffix:semicolon
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
r_do
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
id|action
op_assign
id|desc-&gt;action
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|desc-&gt;pending
op_logical_and
id|desc-&gt;enabled
)paren
(brace
id|desc-&gt;pending
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;chip
op_member_access_from_pointer
id|unmask
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|__do_irq
c_func
(paren
id|irq
comma
id|action
comma
id|regs
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|desc-&gt;pending
op_logical_and
id|desc-&gt;enabled
)paren
suffix:semicolon
id|desc-&gt;running
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * If we were disabled or freed, shut down the handler.&n;&t; */
r_if
c_cond
(paren
id|likely
c_func
(paren
id|desc-&gt;action
op_logical_and
op_logical_neg
id|check_irq_lock
c_func
(paren
id|desc
comma
id|irq
comma
id|regs
)paren
)paren
)paren
r_return
suffix:semicolon
id|running
suffix:colon
multiline_comment|/*&n;&t; * We got another IRQ while this one was masked or&n;&t; * currently running.  Delay it.&n;&t; */
id|desc-&gt;pending
op_assign
l_int|1
suffix:semicolon
id|desc-&gt;chip
op_member_access_from_pointer
id|mask
c_func
(paren
id|irq
)paren
suffix:semicolon
id|desc-&gt;chip
op_member_access_from_pointer
id|ack
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Level-based IRQ handler.  Nice and simple.&n; */
r_void
DECL|function|do_level_IRQ
id|do_level_IRQ
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqdesc
op_star
id|desc
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_const
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|desc-&gt;triggered
op_assign
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Acknowledge, clear _AND_ disable the interrupt.&n;&t; */
id|desc-&gt;chip
op_member_access_from_pointer
id|ack
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|desc-&gt;enabled
)paren
)paren
(brace
id|kstat_cpu
c_func
(paren
id|cpu
)paren
dot
id|irqs
(braket
id|irq
)braket
op_increment
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Return with this interrupt masked if no action&n;&t;&t; */
id|action
op_assign
id|desc-&gt;action
suffix:semicolon
r_if
c_cond
(paren
id|action
)paren
(brace
id|__do_irq
c_func
(paren
id|irq
comma
id|desc-&gt;action
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
id|desc-&gt;enabled
op_logical_and
op_logical_neg
id|check_irq_lock
c_func
(paren
id|desc
comma
id|irq
comma
id|regs
)paren
)paren
)paren
id|desc-&gt;chip
op_member_access_from_pointer
id|unmask
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * do_IRQ handles all hardware IRQ&squot;s.  Decoded IRQs should not&n; * come via this function.  Instead, they should provide their&n; * own &squot;handler&squot;&n; */
DECL|function|asm_do_IRQ
id|asmlinkage
r_void
id|asm_do_IRQ
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|irqdesc
op_star
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
multiline_comment|/*&n;&t; * Some hardware gives randomly wrong interrupts.  Rather&n;&t; * than crashing, do something sensible.&n;&t; */
r_if
c_cond
(paren
id|irq
op_ge
id|NR_IRQS
)paren
id|desc
op_assign
op_amp
id|bad_irq_desc
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
id|desc
op_member_access_from_pointer
id|handle
c_func
(paren
id|irq
comma
id|desc
comma
id|regs
)paren
suffix:semicolon
id|spin_unlock
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|__set_irq_handler
r_void
id|__set_irq_handler
c_func
(paren
r_int
r_int
id|irq
comma
id|irq_handler_t
id|handle
comma
r_int
id|is_chained
)paren
(brace
r_struct
id|irqdesc
op_star
id|desc
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|NR_IRQS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Trying to install handler for IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|handle
op_eq
l_int|NULL
)paren
id|handle
op_assign
id|do_bad_IRQ
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|is_chained
op_logical_and
id|desc-&gt;chip
op_eq
op_amp
id|bad_chip
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Trying to install chained handler for IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|handle
op_eq
id|do_bad_IRQ
)paren
(brace
id|desc-&gt;chip
op_member_access_from_pointer
id|mask
c_func
(paren
id|irq
)paren
suffix:semicolon
id|desc-&gt;chip
op_member_access_from_pointer
id|ack
c_func
(paren
id|irq
)paren
suffix:semicolon
id|desc-&gt;depth
op_assign
l_int|1
suffix:semicolon
id|desc-&gt;enabled
op_assign
l_int|0
suffix:semicolon
)brace
id|desc-&gt;handle
op_assign
id|handle
suffix:semicolon
r_if
c_cond
(paren
id|handle
op_ne
id|do_bad_IRQ
op_logical_and
id|is_chained
)paren
(brace
id|desc-&gt;valid
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;probe_ok
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;depth
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;chip
op_member_access_from_pointer
id|unmask
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|set_irq_chip
r_void
id|set_irq_chip
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqchip
op_star
id|chip
)paren
(brace
r_struct
id|irqdesc
op_star
id|desc
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|NR_IRQS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Trying to install chip for IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|chip
op_eq
l_int|NULL
)paren
id|chip
op_assign
op_amp
id|bad_chip
suffix:semicolon
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
id|desc-&gt;chip
op_assign
id|chip
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|set_irq_type
r_int
id|set_irq_type
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|type
)paren
(brace
r_struct
id|irqdesc
op_star
id|desc
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|ret
op_assign
op_minus
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|NR_IRQS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Trying to set irq type for IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|desc-&gt;chip-&gt;type
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
id|ret
op_assign
id|desc-&gt;chip
op_member_access_from_pointer
id|type
c_func
(paren
id|irq
comma
id|type
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|set_irq_flags
r_void
id|set_irq_flags
c_func
(paren
r_int
r_int
id|irq
comma
r_int
r_int
id|iflags
)paren
(brace
r_struct
id|irqdesc
op_star
id|desc
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|NR_IRQS
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Trying to set irq flags for IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
id|desc-&gt;valid
op_assign
(paren
id|iflags
op_amp
id|IRQF_VALID
)paren
op_ne
l_int|0
suffix:semicolon
id|desc-&gt;probe_ok
op_assign
(paren
id|iflags
op_amp
id|IRQF_PROBE
)paren
op_ne
l_int|0
suffix:semicolon
id|desc-&gt;noautoenable
op_assign
(paren
id|iflags
op_amp
id|IRQF_NOAUTOEN
)paren
op_ne
l_int|0
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|setup_irq
r_int
id|setup_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|irqaction
op_star
r_new
)paren
(brace
r_int
id|shared
op_assign
l_int|0
suffix:semicolon
r_struct
id|irqaction
op_star
id|old
comma
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|irqdesc
op_star
id|desc
suffix:semicolon
multiline_comment|/*&n;&t; * Some drivers like serial.c use request_irq() heavily,&n;&t; * so we have to be careful not to interfere with a&n;&t; * running system.&n;&t; */
r_if
c_cond
(paren
r_new
op_member_access_from_pointer
id|flags
op_amp
id|SA_SAMPLE_RANDOM
)paren
(brace
multiline_comment|/*&n;&t;&t; * This function might sleep, we want to call it first,&n;&t;&t; * outside of the atomic block.&n;&t;&t; * Yes, this might clear the entropy pool if the wrong&n;&t;&t; * driver is attempted to be loaded, without actually&n;&t;&t; * installing a new handler, but is this really a problem,&n;&t;&t; * only the sysadmin is able to do this.&n;&t;&t; */
id|rand_initialize_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The following block of code has to be executed atomically&n;&t; */
id|desc
op_assign
id|irq_desc
op_plus
id|irq
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
id|p
op_assign
op_amp
id|desc-&gt;action
suffix:semicolon
r_if
c_cond
(paren
(paren
id|old
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/* Can&squot;t share interrupts unless both agree to */
r_if
c_cond
(paren
op_logical_neg
(paren
id|old-&gt;flags
op_amp
r_new
op_member_access_from_pointer
id|flags
op_amp
id|SA_SHIRQ
)paren
)paren
(brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
multiline_comment|/* add new interrupt at end of irq queue */
r_do
(brace
id|p
op_assign
op_amp
id|old-&gt;next
suffix:semicolon
id|old
op_assign
op_star
id|p
suffix:semicolon
)brace
r_while
c_loop
(paren
id|old
)paren
suffix:semicolon
id|shared
op_assign
l_int|1
suffix:semicolon
)brace
op_star
id|p
op_assign
r_new
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|shared
)paren
(brace
id|desc-&gt;probing
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;running
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;pending
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;depth
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|desc-&gt;noautoenable
)paren
(brace
id|desc-&gt;depth
op_assign
l_int|0
suffix:semicolon
id|desc-&gt;enabled
op_assign
l_int|1
suffix:semicolon
id|desc-&gt;chip
op_member_access_from_pointer
id|unmask
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;request_irq - allocate an interrupt line&n; *&t;@irq: Interrupt line to allocate&n; *&t;@handler: Function to be called when the IRQ occurs&n; *&t;@irqflags: Interrupt type flags&n; *&t;@devname: An ascii name for the claiming device&n; *&t;@dev_id: A cookie passed back to the handler function&n; *&n; *&t;This call allocates interrupt resources and enables the&n; *&t;interrupt line and IRQ handling. From the point this&n; *&t;call is made your handler function may be invoked. Since&n; *&t;your handler function must clear any interrupt the board&n; *&t;raises, you must take care both to initialise your hardware&n; *&t;and to set up the interrupt handler in the right order.&n; *&n; *&t;Dev_id must be globally unique. Normally the address of the&n; *&t;device data structure is used as the cookie. Since the handler&n; *&t;receives this value it makes sense to use it.&n; *&n; *&t;If your interrupt is shared you must pass a non NULL dev_id&n; *&t;as this is required when freeing the interrupt.&n; *&n; *&t;Flags:&n; *&n; *&t;SA_SHIRQ&t;&t;Interrupt is shared&n; *&n; *&t;SA_INTERRUPT&t;&t;Disable local interrupts while processing&n; *&n; *&t;SA_SAMPLE_RANDOM&t;The interrupt can be used for entropy&n; *&n; */
DECL|function|request_irq
r_int
id|request_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
(paren
op_star
id|handler
)paren
(paren
r_int
comma
r_void
op_star
comma
r_struct
id|pt_regs
op_star
)paren
comma
r_int
r_int
id|irq_flags
comma
r_const
r_char
op_star
id|devname
comma
r_void
op_star
id|dev_id
)paren
(brace
r_int
r_int
id|retval
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|NR_IRQS
op_logical_or
op_logical_neg
id|irq_desc
(braket
id|irq
)braket
dot
id|valid
op_logical_or
op_logical_neg
id|handler
op_logical_or
(paren
id|irq_flags
op_amp
id|SA_SHIRQ
op_logical_and
op_logical_neg
id|dev_id
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|action
op_assign
(paren
r_struct
id|irqaction
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|irqaction
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|action-&gt;handler
op_assign
id|handler
suffix:semicolon
id|action-&gt;flags
op_assign
id|irq_flags
suffix:semicolon
id|action-&gt;mask
op_assign
l_int|0
suffix:semicolon
id|action-&gt;name
op_assign
id|devname
suffix:semicolon
id|action-&gt;next
op_assign
l_int|NULL
suffix:semicolon
id|action-&gt;dev_id
op_assign
id|dev_id
suffix:semicolon
id|retval
op_assign
id|setup_irq
c_func
(paren
id|irq
comma
id|action
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;free_irq - free an interrupt&n; *&t;@irq: Interrupt line to free&n; *&t;@dev_id: Device identity to free&n; *&n; *&t;Remove an interrupt handler. The handler is removed and if the&n; *&t;interrupt line is no longer in use by any driver it is disabled.&n; *&t;On a shared IRQ the caller must ensure the interrupt is disabled&n; *&t;on the card it drives before calling this function.&n; *&n; *&t;This function must not be called from interrupt context.&n; */
DECL|function|free_irq
r_void
id|free_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_void
op_star
id|dev_id
)paren
(brace
r_struct
id|irqaction
op_star
id|action
comma
op_star
op_star
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
id|NR_IRQS
op_logical_or
op_logical_neg
id|irq_desc
(braket
id|irq
)braket
dot
id|valid
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Trying to free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|p
op_assign
op_amp
id|irq_desc
(braket
id|irq
)braket
dot
id|action
suffix:semicolon
(paren
id|action
op_assign
op_star
id|p
)paren
op_ne
l_int|NULL
suffix:semicolon
id|p
op_assign
op_amp
id|action-&gt;next
)paren
(brace
r_if
c_cond
(paren
id|action-&gt;dev_id
op_ne
id|dev_id
)paren
r_continue
suffix:semicolon
multiline_comment|/* Found it - now free it */
op_star
id|p
op_assign
id|action-&gt;next
suffix:semicolon
r_break
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_controller_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Trying to free free IRQ%d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|synchronize_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
)brace
)brace
r_static
id|DECLARE_MUTEX
c_func
(paren
id|probe_sem
)paren
suffix:semicolon
multiline_comment|/* Start the interrupt probing.  Unlike other architectures,&n; * we don&squot;t return a mask of interrupts from probe_irq_on,&n; * but return the number of interrupts enabled for the probe.&n; * The interrupts which have been enabled for probing is&n; * instead recorded in the irq_desc structure.&n; */
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|i
comma
id|irqs
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|delay
suffix:semicolon
id|down
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * first snaffle up any unassigned but&n;&t; * probe-able interrupts&n;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|irq_controller_lock
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
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|irq_desc
(braket
id|i
)braket
dot
id|probe_ok
op_logical_or
id|irq_desc
(braket
id|i
)braket
dot
id|action
)paren
r_continue
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|probing
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|triggered
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|irq_desc
(braket
id|i
)braket
dot
id|chip-&gt;type
)paren
id|irq_desc
(braket
id|i
)braket
dot
id|chip
op_member_access_from_pointer
id|type
c_func
(paren
id|i
comma
id|IRQT_PROBE
)paren
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|chip
op_member_access_from_pointer
id|unmask
c_func
(paren
id|i
)paren
suffix:semicolon
id|irqs
op_add_assign
l_int|1
suffix:semicolon
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * wait for spurious interrupts to mask themselves out again&n;&t; */
r_for
c_loop
(paren
id|delay
op_assign
id|jiffies
op_plus
id|HZ
op_div
l_int|10
suffix:semicolon
id|time_before
c_func
(paren
id|jiffies
comma
id|delay
)paren
suffix:semicolon
)paren
multiline_comment|/* min 100ms delay */
suffix:semicolon
multiline_comment|/*&n;&t; * now filter out any obviously spurious interrupts&n;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|irq_controller_lock
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
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irq_desc
(braket
id|i
)braket
dot
id|probing
op_logical_and
id|irq_desc
(braket
id|i
)braket
dot
id|triggered
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|probing
op_assign
l_int|0
suffix:semicolon
id|irqs
op_sub_assign
l_int|1
suffix:semicolon
)brace
)brace
id|spin_unlock_irq
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
r_return
id|irqs
suffix:semicolon
)brace
DECL|function|probe_irq_mask
r_int
r_int
id|probe_irq_mask
c_func
(paren
r_int
r_int
id|irqs
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|0
comma
id|i
suffix:semicolon
id|spin_lock_irq
c_func
(paren
op_amp
id|irq_controller_lock
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
l_int|16
op_logical_and
id|i
OL
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|irq_desc
(braket
id|i
)braket
dot
id|probing
op_logical_and
id|irq_desc
(braket
id|i
)braket
dot
id|triggered
)paren
id|mask
op_or_assign
l_int|1
op_lshift
id|i
suffix:semicolon
id|spin_unlock_irq
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
r_return
id|mask
suffix:semicolon
)brace
multiline_comment|/*&n; * Possible return values:&n; *  &gt;= 0 - interrupt number&n; *    -1 - no interrupt/many interrupts&n; */
DECL|function|probe_irq_off
r_int
id|probe_irq_off
c_func
(paren
r_int
r_int
id|irqs
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
r_int
id|irq_found
op_assign
id|NO_IRQ
suffix:semicolon
multiline_comment|/*&n;&t; * look at the interrupts, and find exactly one&n;&t; * that we were probing has been triggered&n;&t; */
id|spin_lock_irq
c_func
(paren
op_amp
id|irq_controller_lock
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
id|NR_IRQS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irq_desc
(braket
id|i
)braket
dot
id|probing
op_logical_and
id|irq_desc
(braket
id|i
)braket
dot
id|triggered
)paren
(brace
r_if
c_cond
(paren
id|irq_found
op_ne
id|NO_IRQ
)paren
(brace
id|irq_found
op_assign
id|NO_IRQ
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|irq_found
op_assign
id|i
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|irq_found
op_eq
op_minus
l_int|1
)paren
id|irq_found
op_assign
id|NO_IRQ
suffix:semicolon
id|out
suffix:colon
id|spin_unlock_irq
c_func
(paren
op_amp
id|irq_controller_lock
)paren
suffix:semicolon
id|up
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
r_return
id|irq_found
suffix:semicolon
)brace
DECL|function|init_irq_proc
r_void
id|__init
id|init_irq_proc
c_func
(paren
r_void
)paren
(brace
)brace
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_struct
id|irqdesc
op_star
id|desc
suffix:semicolon
r_extern
r_void
id|init_dma
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|irq
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
comma
id|desc
op_assign
id|irq_desc
suffix:semicolon
id|irq
OL
id|NR_IRQS
suffix:semicolon
id|irq
op_increment
comma
id|desc
op_increment
)paren
op_star
id|desc
op_assign
id|bad_irq_desc
suffix:semicolon
id|init_arch_irq
c_func
(paren
)paren
suffix:semicolon
id|init_dma
c_func
(paren
)paren
suffix:semicolon
)brace
eof
