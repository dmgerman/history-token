multiline_comment|/* irq.c: FRV IRQ handling&n; *&n; * Copyright (C) 2003, 2004 Red Hat, Inc. All Rights Reserved.&n; * Written by David Howells (dhowells@redhat.com)&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
multiline_comment|/*&n; * (mostly architecture independent, will move to kernel/irq.c in 2.5.)&n; *&n; * IRQs are in fact implemented a bit like signal handlers for the kernel.&n; * Naturally it&squot;s not a 1:1 relation, but there are similarities.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/irc-regs.h&gt;
macro_line|#include &lt;asm/irq-routing.h&gt;
macro_line|#include &lt;asm/gdb-stub.h&gt;
r_extern
r_void
id|__init
id|fpga_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|__init
id|route_mb93493_irqs
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|register_irq_proc
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n; * Special irq handlers.&n; */
DECL|function|no_action
id|irqreturn_t
id|no_action
c_func
(paren
r_int
id|cpl
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|variable|irq_err_count
id|atomic_t
id|irq_err_count
suffix:semicolon
multiline_comment|/*&n; * Generic, controller-independent functions:&n; */
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
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_struct
id|irq_group
op_star
id|group
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|level
comma
id|grp
comma
id|ix
comma
id|i
comma
id|j
suffix:semicolon
id|i
op_assign
op_star
(paren
id|loff_t
op_star
)paren
id|v
suffix:semicolon
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|0
suffix:colon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;           &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_CPUS
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|j
)paren
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;CPU%d       &quot;
comma
id|j
)paren
suffix:semicolon
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
dot
dot
dot
id|NR_IRQ_GROUPS
op_star
id|NR_IRQ_ACTIONS_PER_GROUP
suffix:colon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|grp
op_assign
(paren
id|i
op_minus
l_int|1
)paren
op_div
id|NR_IRQ_ACTIONS_PER_GROUP
suffix:semicolon
id|group
op_assign
id|irq_groups
(braket
id|grp
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|group
)paren
r_goto
id|skip
suffix:semicolon
id|ix
op_assign
(paren
id|i
op_minus
l_int|1
)paren
op_mod
id|NR_IRQ_ACTIONS_PER_GROUP
suffix:semicolon
id|action
op_assign
id|group-&gt;actions
(braket
id|ix
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
)paren
r_goto
id|skip
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%3d: &quot;
comma
id|i
op_minus
l_int|1
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%10u &quot;
comma
id|kstat_irqs
c_func
(paren
id|i
)paren
)paren
suffix:semicolon
macro_line|#else
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|NR_CPUS
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|cpu_online
c_func
(paren
id|j
)paren
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%10u &quot;
comma
id|kstat_cpu
c_func
(paren
id|j
)paren
dot
id|irqs
(braket
id|i
op_minus
l_int|1
)braket
)paren
suffix:semicolon
macro_line|#endif
id|level
op_assign
id|group-&gt;sources
(braket
id|ix
)braket
op_member_access_from_pointer
id|level
op_minus
id|frv_irq_levels
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; %12s@%x&quot;
comma
id|group-&gt;sources
(braket
id|ix
)braket
op_member_access_from_pointer
id|muxname
comma
id|level
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
id|seq_putc
c_func
(paren
id|p
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|skip
suffix:colon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|NR_IRQ_GROUPS
op_star
id|NR_IRQ_ACTIONS_PER_GROUP
op_plus
l_int|1
suffix:colon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;ERR: %10u&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|irq_err_count
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Generic enable/disable code: this just calls&n; * down into the PIC-specific version for the actual&n; * hardware disable after having gotten the irq&n; * controller lock.&n; */
multiline_comment|/**&n; *&t;disable_irq_nosync - disable an irq without waiting&n; *&t;@irq: Interrupt to disable&n; *&n; *&t;Disable the selected interrupt line.  Disables and Enables are&n; *&t;nested.&n; *&t;Unlike disable_irq(), this function does not ensure existing&n; *&t;instances of the IRQ handler have completed before returning.&n; *&n; *&t;This function may be called from IRQ context.&n; */
DECL|function|disable_irq_nosync
r_void
id|disable_irq_nosync
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|irq_source
op_star
id|source
suffix:semicolon
r_struct
id|irq_group
op_star
id|group
suffix:semicolon
r_struct
id|irq_level
op_star
id|level
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|idx
op_assign
id|irq
op_amp
(paren
id|NR_IRQ_ACTIONS_PER_GROUP
op_minus
l_int|1
)paren
suffix:semicolon
id|group
op_assign
id|irq_groups
(braket
id|irq
op_rshift
id|NR_IRQ_LOG2_ACTIONS_PER_GROUP
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|group
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|source
op_assign
id|group-&gt;sources
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|source
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|level
op_assign
id|source-&gt;level
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|level-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|group-&gt;control
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|group-&gt;disable_cnt
(braket
id|idx
)braket
op_increment
)paren
id|group
op_member_access_from_pointer
id|control
c_func
(paren
id|group
comma
id|idx
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|level-&gt;disable_count
op_increment
)paren
(brace
id|__set_MASK
c_func
(paren
id|level
op_minus
id|frv_irq_levels
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|level-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;disable_irq - disable an irq and wait for completion&n; *&t;@irq: Interrupt to disable&n; *&n; *&t;Disable the selected interrupt line.  Enables and Disables are&n; *&t;nested.&n; *&t;This function waits for any pending IRQ handlers for this interrupt&n; *&t;to complete before returning. If you use this function while&n; *&t;holding a resource the IRQ handler may need you will deadlock.&n; *&n; *&t;This function may be called - with care - from IRQ context.&n; */
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
id|disable_irq_nosync
c_func
(paren
id|irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|local_irq_count
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
)paren
)paren
(brace
r_do
(brace
id|barrier
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
id|IRQ_INPROGRESS
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/**&n; *&t;enable_irq - enable handling of an irq&n; *&t;@irq: Interrupt to enable&n; *&n; *&t;Undoes the effect of one call to disable_irq().  If this&n; *&t;matches the last disable, processing of interrupts on this&n; *&t;IRQ line is re-enabled.&n; *&n; *&t;This function may be called from IRQ context.&n; */
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
id|irq_source
op_star
id|source
suffix:semicolon
r_struct
id|irq_group
op_star
id|group
suffix:semicolon
r_struct
id|irq_level
op_star
id|level
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|idx
op_assign
id|irq
op_amp
(paren
id|NR_IRQ_ACTIONS_PER_GROUP
op_minus
l_int|1
)paren
suffix:semicolon
r_int
id|count
suffix:semicolon
id|group
op_assign
id|irq_groups
(braket
id|irq
op_rshift
id|NR_IRQ_LOG2_ACTIONS_PER_GROUP
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|group
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|source
op_assign
id|group-&gt;sources
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|source
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|level
op_assign
id|source-&gt;level
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|level-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|group-&gt;control
)paren
id|count
op_assign
id|group-&gt;disable_cnt
(braket
id|idx
)braket
suffix:semicolon
r_else
id|count
op_assign
id|level-&gt;disable_count
suffix:semicolon
r_switch
c_cond
(paren
id|count
)paren
(brace
r_case
l_int|1
suffix:colon
r_if
c_cond
(paren
id|group-&gt;control
)paren
(brace
r_if
c_cond
(paren
id|group-&gt;actions
(braket
id|idx
)braket
)paren
id|group
op_member_access_from_pointer
id|control
c_func
(paren
id|group
comma
id|idx
comma
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|level-&gt;usage
)paren
id|__clr_MASK
c_func
(paren
id|level
op_minus
id|frv_irq_levels
)paren
suffix:semicolon
)brace
multiline_comment|/* fall-through */
r_default
suffix:colon
id|count
op_decrement
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0
suffix:colon
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
r_if
c_cond
(paren
id|group-&gt;control
)paren
id|group-&gt;disable_cnt
(braket
id|idx
)braket
op_assign
id|count
suffix:semicolon
r_else
id|level-&gt;disable_count
op_assign
id|count
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|level-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * handles all normal device IRQ&squot;s&n; * - registers are referred to by the __frame variable (GR28)&n; * - IRQ distribution is complicated in this arch because of the many PICs, the&n; *   way they work and the way they cascade&n; */
DECL|function|do_IRQ
id|asmlinkage
r_void
id|do_IRQ
c_func
(paren
r_void
)paren
(brace
r_struct
id|irq_source
op_star
id|source
suffix:semicolon
r_int
id|level
comma
id|cpu
suffix:semicolon
id|level
op_assign
(paren
id|__frame-&gt;tbr
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
suffix:semicolon
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
macro_line|#if 0
(brace
r_static
id|u32
id|irqcount
suffix:semicolon
op_star
(paren
r_volatile
id|u32
op_star
)paren
l_int|0xe1200004
op_assign
op_complement
(paren
(paren
id|irqcount
op_increment
op_lshift
l_int|8
)paren
op_or
id|level
)paren
suffix:semicolon
op_star
(paren
r_volatile
id|u16
op_star
)paren
l_int|0xffc00100
op_assign
(paren
id|u16
)paren
op_complement
l_int|0x9999
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|__frame
op_minus
(paren
r_int
r_int
)paren
(paren
id|current
op_plus
l_int|1
)paren
OL
l_int|512
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|__set_MASK
c_func
(paren
id|level
)paren
suffix:semicolon
id|__clr_RC
c_func
(paren
id|level
)paren
suffix:semicolon
id|__clr_IRL
c_func
(paren
)paren
suffix:semicolon
id|kstat_this_cpu.irqs
(braket
id|level
)braket
op_increment
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|source
op_assign
id|frv_irq_levels
(braket
id|level
)braket
dot
id|sources
suffix:semicolon
id|source
suffix:semicolon
id|source
op_assign
id|source-&gt;next
)paren
id|source
op_member_access_from_pointer
id|doirq
c_func
(paren
id|source
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
id|__clr_MASK
c_func
(paren
id|level
)paren
suffix:semicolon
multiline_comment|/* only process softirqs if we didn&squot;t interrupt another interrupt handler */
r_if
c_cond
(paren
(paren
id|__frame-&gt;psr
op_amp
id|PSR_PIL
)paren
op_eq
id|PSR_PIL_0
)paren
r_if
c_cond
(paren
id|local_softirq_pending
c_func
(paren
)paren
)paren
id|do_softirq
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PREEMPT
id|cli
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|current-&gt;preempt_count
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|__frame-&gt;psr
op_amp
id|PSR_S
)paren
op_logical_or
(paren
id|current-&gt;need_resched
op_eq
l_int|0
)paren
op_logical_or
id|in_interrupt
c_func
(paren
)paren
)paren
r_break
suffix:semicolon
id|current-&gt;preempt_count
op_increment
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
id|preempt_schedule
c_func
(paren
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if 0
(brace
op_star
(paren
r_volatile
id|u16
op_star
)paren
l_int|0xffc00100
op_assign
(paren
id|u16
)paren
op_complement
l_int|0x6666
suffix:semicolon
id|mb
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
multiline_comment|/* end do_IRQ() */
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * handles all NMIs when not co-opted by the debugger&n; * - registers are referred to by the __frame variable (GR28)&n; */
DECL|function|do_NMI
id|asmlinkage
r_void
id|do_NMI
c_func
(paren
r_void
)paren
(brace
)brace
multiline_comment|/* end do_NMI() */
multiline_comment|/*****************************************************************************/
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
id|irqreturn_t
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
id|irqflags
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
id|retval
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
macro_line|#if 1
multiline_comment|/*&n;&t; * Sanity-check: shared interrupts should REALLY pass in&n;&t; * a real dev-ID, otherwise we&squot;ll have trouble later trying&n;&t; * to figure out which interrupt is which (messes up the&n;&t; * interrupt freeing logic etc).&n;&t; */
r_if
c_cond
(paren
id|irqflags
op_amp
id|SA_SHIRQ
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dev_id
)paren
id|printk
c_func
(paren
l_string|&quot;Bad boy: %s (at 0x%x) called us without a dev_id!&bslash;n&quot;
comma
id|devname
comma
(paren
op_amp
id|irq
)paren
(braket
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
id|irq
op_rshift
id|NR_IRQ_LOG2_ACTIONS_PER_GROUP
)paren
op_ge
id|NR_IRQ_GROUPS
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handler
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
id|irqflags
suffix:semicolon
id|action-&gt;mask
op_assign
id|CPU_MASK_NONE
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
multiline_comment|/**&n; *&t;free_irq - free an interrupt&n; *&t;@irq: Interrupt line to free&n; *&t;@dev_id: Device identity to free&n; *&n; *&t;Remove an interrupt handler. The handler is removed and if the&n; *&t;interrupt line is no longer in use by any driver it is disabled.&n; *&t;On a shared IRQ the caller must ensure the interrupt is disabled&n; *&t;on the card it drives before calling this function. The function&n; *&t;does not return until any executing interrupts for this IRQ&n; *&t;have completed.&n; *&n; *&t;This function may be called from interrupt context.&n; *&n; *&t;Bugs: Attempting to free an irq in a handler for the same irq hangs&n; *&t;      the machine.&n; */
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
id|irq_source
op_star
id|source
suffix:semicolon
r_struct
id|irq_group
op_star
id|group
suffix:semicolon
r_struct
id|irq_level
op_star
id|level
suffix:semicolon
r_struct
id|irqaction
op_star
op_star
id|p
comma
op_star
op_star
id|pp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irq
op_rshift
id|NR_IRQ_LOG2_ACTIONS_PER_GROUP
)paren
op_ge
id|NR_IRQ_GROUPS
)paren
r_return
suffix:semicolon
id|group
op_assign
id|irq_groups
(braket
id|irq
op_rshift
id|NR_IRQ_LOG2_ACTIONS_PER_GROUP
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|group
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|source
op_assign
id|group-&gt;sources
(braket
id|irq
op_amp
(paren
id|NR_IRQ_ACTIONS_PER_GROUP
op_minus
l_int|1
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|source
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|level
op_assign
id|source-&gt;level
suffix:semicolon
id|p
op_assign
op_amp
id|group-&gt;actions
(braket
id|irq
op_amp
(paren
id|NR_IRQ_ACTIONS_PER_GROUP
op_minus
l_int|1
)paren
)braket
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|level-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_for
c_loop
(paren
id|pp
op_assign
id|p
suffix:semicolon
op_star
id|pp
suffix:semicolon
id|pp
op_assign
op_amp
(paren
op_star
id|pp
)paren
op_member_access_from_pointer
id|next
)paren
(brace
r_struct
id|irqaction
op_star
id|action
op_assign
op_star
id|pp
suffix:semicolon
r_if
c_cond
(paren
id|action-&gt;dev_id
op_ne
id|dev_id
)paren
r_continue
suffix:semicolon
multiline_comment|/* found it - remove from the list of entries */
op_star
id|pp
op_assign
id|action-&gt;next
suffix:semicolon
id|level-&gt;usage
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
id|pp
op_logical_and
id|group-&gt;control
)paren
id|group
op_member_access_from_pointer
id|control
c_func
(paren
id|group
comma
id|irq
op_amp
(paren
id|NR_IRQ_ACTIONS_PER_GROUP
op_minus
l_int|1
)paren
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|level-&gt;usage
op_eq
l_int|0
)paren
id|__set_MASK
c_func
(paren
id|level
op_minus
id|frv_irq_levels
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|level-&gt;lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* Wait to make sure it&squot;s not being used on another CPU */
r_while
c_loop
(paren
id|desc-&gt;status
op_amp
id|IRQ_INPROGRESS
)paren
id|barrier
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|kfree
c_func
(paren
id|action
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * IRQ autodetection code..&n; *&n; * This depends on the fact that any interrupt that comes in on to an&n; * unassigned IRQ will cause GxICR_DETECT to be set&n; */
r_static
id|DECLARE_MUTEX
c_func
(paren
id|probe_sem
)paren
suffix:semicolon
multiline_comment|/**&n; *&t;probe_irq_on&t;- begin an interrupt autodetect&n; *&n; *&t;Commence probing for an interrupt. The interrupts are scanned&n; *&t;and a mask of potential interrupt lines is returned.&n; *&n; */
DECL|function|probe_irq_on
r_int
r_int
id|probe_irq_on
c_func
(paren
r_void
)paren
(brace
id|down
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return a mask of triggered interrupts (this&n; * can handle only legacy ISA interrupts).&n; */
multiline_comment|/**&n; *&t;probe_irq_mask - scan a bitmap of interrupt lines&n; *&t;@val:&t;mask of interrupts to consider&n; *&n; *&t;Scan the ISA bus interrupt lines and return a bitmap of&n; *&t;active interrupts. The interrupt probe logic state is then&n; *&t;returned to its previous value.&n; *&n; *&t;Note: we need to scan all the irq&squot;s even though we will&n; *&t;only return ISA irq numbers - just so that we reset them&n; *&t;all to a known state.&n; */
DECL|function|probe_irq_mask
r_int
r_int
id|probe_irq_mask
c_func
(paren
r_int
r_int
id|xmask
)paren
(brace
id|up
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the one interrupt that triggered (this can&n; * handle any interrupt source).&n; */
multiline_comment|/**&n; *&t;probe_irq_off&t;- end an interrupt autodetect&n; *&t;@xmask: mask of potential interrupts (unused)&n; *&n; *&t;Scans the unused interrupt lines and returns the line which&n; *&t;appears to have triggered the interrupt. If no interrupt was&n; *&t;found then zero is returned. If more than one interrupt is&n; *&t;found then minus the first candidate is returned to indicate&n; *&t;their is doubt.&n; *&n; *&t;The interrupt probe logic state is returned to its previous&n; *&t;value.&n; *&n; *&t;BUGS: When used in a module (which arguably shouldnt happen)&n; *&t;nothing prevents two IRQ probe callers from overlapping. The&n; *&t;results of this are non-optimal.&n; */
DECL|function|probe_irq_off
r_int
id|probe_irq_off
c_func
(paren
r_int
r_int
id|xmask
)paren
(brace
id|up
c_func
(paren
op_amp
id|probe_sem
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* this was setup_x86_irq but it seems pretty generic */
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
r_struct
id|irq_source
op_star
id|source
suffix:semicolon
r_struct
id|irq_group
op_star
id|group
suffix:semicolon
r_struct
id|irq_level
op_star
id|level
suffix:semicolon
r_struct
id|irqaction
op_star
op_star
id|p
comma
op_star
op_star
id|pp
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|group
op_assign
id|irq_groups
(braket
id|irq
op_rshift
id|NR_IRQ_LOG2_ACTIONS_PER_GROUP
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|group
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|source
op_assign
id|group-&gt;sources
(braket
id|irq
op_amp
(paren
id|NR_IRQ_ACTIONS_PER_GROUP
op_minus
l_int|1
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|source
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|level
op_assign
id|source-&gt;level
suffix:semicolon
id|p
op_assign
op_amp
id|group-&gt;actions
(braket
id|irq
op_amp
(paren
id|NR_IRQ_ACTIONS_PER_GROUP
op_minus
l_int|1
)paren
)braket
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
multiline_comment|/* must juggle the interrupt processing stuff with interrupts disabled */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|level-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* can&squot;t share interrupts unless all parties agree to */
r_if
c_cond
(paren
id|level-&gt;usage
op_ne
l_int|0
op_logical_and
op_logical_neg
(paren
id|level-&gt;flags
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
id|level-&gt;lock
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
id|pp
op_assign
id|p
suffix:semicolon
r_while
c_loop
(paren
op_star
id|pp
)paren
id|pp
op_assign
op_amp
(paren
op_star
id|pp
)paren
op_member_access_from_pointer
id|next
suffix:semicolon
op_star
id|pp
op_assign
r_new
suffix:semicolon
id|level-&gt;usage
op_increment
suffix:semicolon
id|level-&gt;flags
op_assign
r_new
op_member_access_from_pointer
id|flags
suffix:semicolon
multiline_comment|/* turn the interrupts on */
r_if
c_cond
(paren
id|level-&gt;usage
op_eq
l_int|1
)paren
id|__clr_MASK
c_func
(paren
id|level
op_minus
id|frv_irq_levels
)paren
suffix:semicolon
r_if
c_cond
(paren
id|p
op_eq
id|pp
op_logical_and
id|group-&gt;control
)paren
id|group
op_member_access_from_pointer
id|control
c_func
(paren
id|group
comma
id|irq
op_amp
(paren
id|NR_IRQ_ACTIONS_PER_GROUP
op_minus
l_int|1
)paren
comma
l_int|1
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|level-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|register_irq_proc
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|root_irq_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|root_irq_dir
suffix:semicolon
DECL|variable|irq_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|irq_dir
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|macro|HEX_DIGITS
mdefine_line|#define HEX_DIGITS 8
DECL|function|parse_hex_value
r_static
r_int
r_int
id|parse_hex_value
(paren
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_int
r_int
op_star
id|ret
)paren
(brace
r_int
r_char
id|hexnum
(braket
id|HEX_DIGITS
)braket
suffix:semicolon
r_int
r_int
id|value
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|count
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|count
OG
id|HEX_DIGITS
)paren
id|count
op_assign
id|HEX_DIGITS
suffix:semicolon
r_if
c_cond
(paren
id|copy_from_user
c_func
(paren
id|hexnum
comma
id|buffer
comma
id|count
)paren
)paren
r_return
op_minus
id|EFAULT
suffix:semicolon
multiline_comment|/*&n;&t; * Parse the first 8 characters as a hex string, any non-hex char&n;&t; * is end-of-string. &squot;00e1&squot;, &squot;e1&squot;, &squot;00E1&squot;, &squot;E1&squot; are all the same.&n;&t; */
id|value
op_assign
l_int|0
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
id|count
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|c
op_assign
id|hexnum
(braket
id|i
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|c
)paren
(brace
r_case
l_char|&squot;0&squot;
dot
dot
dot
l_char|&squot;9&squot;
suffix:colon
id|c
op_sub_assign
l_char|&squot;0&squot;
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;a&squot;
dot
dot
dot
l_char|&squot;f&squot;
suffix:colon
id|c
op_sub_assign
l_char|&squot;a&squot;
op_minus
l_int|10
suffix:semicolon
r_break
suffix:semicolon
r_case
l_char|&squot;A&squot;
dot
dot
dot
l_char|&squot;F&squot;
suffix:colon
id|c
op_sub_assign
l_char|&squot;A&squot;
op_minus
l_int|10
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|out
suffix:semicolon
)brace
id|value
op_assign
(paren
id|value
op_lshift
l_int|4
)paren
op_or
id|c
suffix:semicolon
)brace
id|out
suffix:colon
op_star
id|ret
op_assign
id|value
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|prof_cpu_mask_read_proc
r_static
r_int
id|prof_cpu_mask_read_proc
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_int
op_star
id|mask
op_assign
(paren
r_int
r_int
op_star
)paren
id|data
suffix:semicolon
r_if
c_cond
(paren
id|count
OL
id|HEX_DIGITS
op_plus
l_int|1
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
r_return
id|sprintf
(paren
id|page
comma
l_string|&quot;%08lx&bslash;n&quot;
comma
op_star
id|mask
)paren
suffix:semicolon
)brace
DECL|function|prof_cpu_mask_write_proc
r_static
r_int
id|prof_cpu_mask_write_proc
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_int
r_int
op_star
id|mask
op_assign
(paren
r_int
r_int
op_star
)paren
id|data
comma
id|full_count
op_assign
id|count
comma
id|err
suffix:semicolon
r_int
r_int
id|new_value
suffix:semicolon
id|show_state
c_func
(paren
)paren
suffix:semicolon
id|err
op_assign
id|parse_hex_value
c_func
(paren
id|buffer
comma
id|count
comma
op_amp
id|new_value
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
op_star
id|mask
op_assign
id|new_value
suffix:semicolon
r_return
id|full_count
suffix:semicolon
)brace
DECL|macro|MAX_NAMELEN
mdefine_line|#define MAX_NAMELEN 10
DECL|function|register_irq_proc
r_static
r_void
id|register_irq_proc
(paren
r_int
r_int
id|irq
)paren
(brace
r_char
id|name
(braket
id|MAX_NAMELEN
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|root_irq_dir
op_logical_or
id|irq_dir
(braket
id|irq
)braket
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
id|name
comma
l_int|0
comma
id|MAX_NAMELEN
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%d&quot;
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* create /proc/irq/1234 */
id|irq_dir
(braket
id|irq
)braket
op_assign
id|proc_mkdir
c_func
(paren
id|name
comma
id|root_irq_dir
)paren
suffix:semicolon
)brace
DECL|variable|prof_cpu_mask
r_int
r_int
id|prof_cpu_mask
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|function|init_irq_proc
r_void
id|init_irq_proc
(paren
r_void
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* create /proc/irq */
id|root_irq_dir
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;irq&quot;
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* create /proc/irq/prof_cpu_mask */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
l_string|&quot;prof_cpu_mask&quot;
comma
l_int|0600
comma
id|root_irq_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
r_return
suffix:semicolon
id|entry-&gt;nlink
op_assign
l_int|1
suffix:semicolon
id|entry-&gt;data
op_assign
(paren
r_void
op_star
)paren
op_amp
id|prof_cpu_mask
suffix:semicolon
id|entry-&gt;read_proc
op_assign
id|prof_cpu_mask_read_proc
suffix:semicolon
id|entry-&gt;write_proc
op_assign
id|prof_cpu_mask_write_proc
suffix:semicolon
multiline_comment|/*&n;&t; * Create entries for all existing IRQs.&n;&t; */
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
id|register_irq_proc
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************/
multiline_comment|/*&n; * initialise the interrupt system&n; */
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
id|route_cpu_irqs
c_func
(paren
)paren
suffix:semicolon
id|fpga_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_FUJITSU_MB93493
id|route_mb93493_irqs
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* end init_IRQ() */
eof
