multiline_comment|/*&n; *  arch/ppc/kernel/irq.c&n; *&n; *  Derived from arch/i386/kernel/irq.c&n; *    Copyright (C) 1992 Linus Torvalds&n; *  Adapted from arch/i386 by Gary Thomas&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *  Updated and modified by Cort Dougan (cort@cs.nmt.edu)&n; *    Copyright (C) 1996 Cort Dougan&n; *  Adapted for Power Macintosh by Paul Mackerras&n; *    Copyright (C) 1996 Paul Mackerras (paulus@cs.anu.edu.au)&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; * &n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; *&n; * This file contains the code used by various IRQ handling routines:&n; * asking for different IRQ&squot;s should be done through these routines&n; * instead of just grabbing them. Thus setups with different IRQ numbers&n; * shouldn&squot;t result in any weird surprises, and installing new handlers&n; * should be easier.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/timex.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/random.h&gt;
macro_line|#include &lt;linux/kallsyms.h&gt;
macro_line|#include &lt;linux/profile.h&gt;
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/cache.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/iSeries/LparData.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/paca.h&gt;
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|iSeries_smp_message_recv
c_func
(paren
r_struct
id|pt_regs
op_star
)paren
suffix:semicolon
macro_line|#endif
r_extern
id|irq_desc_t
id|irq_desc
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|variable|__irq_offset_value
r_int
id|__irq_offset_value
suffix:semicolon
DECL|variable|ppc_spurious_interrupts
r_int
id|ppc_spurious_interrupts
suffix:semicolon
DECL|variable|lpevent_count
r_int
r_int
id|lpevent_count
suffix:semicolon
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
op_assign
op_star
(paren
id|loff_t
op_star
)paren
id|v
comma
id|j
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
id|irq_desc_t
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
id|i
op_eq
l_int|0
)paren
(brace
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
(brace
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
r_if
c_cond
(paren
id|i
OL
id|NR_IRQS
)paren
(brace
id|desc
op_assign
id|get_irq_desc
c_func
(paren
id|i
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
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
op_logical_or
op_logical_neg
id|action-&gt;handler
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
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
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
(brace
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
)braket
)paren
suffix:semicolon
)brace
macro_line|#else
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
macro_line|#endif /* CONFIG_SMP */
r_if
c_cond
(paren
id|desc-&gt;handler
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; %s &quot;
comma
id|desc-&gt;handler
op_member_access_from_pointer
r_typename
)paren
suffix:semicolon
r_else
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;  None      &quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;%s&quot;
comma
(paren
id|desc-&gt;status
op_amp
id|IRQ_LEVEL
)paren
ques
c_cond
l_string|&quot;Level &quot;
suffix:colon
l_string|&quot;Edge  &quot;
)paren
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;    %s&quot;
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
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|i
op_eq
id|NR_IRQS
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;BAD: %10u&bslash;n&quot;
comma
id|ppc_spurious_interrupts
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_extern
r_int
id|noirqdebug
suffix:semicolon
multiline_comment|/*&n; * Eventually, this should take an array of interrupts and an array size&n; * so it can dispatch multiple interrupts.&n; */
DECL|function|ppc_irq_dispatch_handler
r_void
id|ppc_irq_dispatch_handler
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
comma
r_int
id|irq
)paren
(brace
r_int
id|status
suffix:semicolon
r_struct
id|irqaction
op_star
id|action
suffix:semicolon
r_int
id|cpu
op_assign
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|irq_desc_t
op_star
id|desc
op_assign
id|get_irq_desc
c_func
(paren
id|irq
)paren
suffix:semicolon
id|irqreturn_t
id|action_ret
suffix:semicolon
macro_line|#ifdef CONFIG_IRQSTACKS
r_struct
id|thread_info
op_star
id|curtp
comma
op_star
id|irqtp
suffix:semicolon
macro_line|#endif
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
r_if
c_cond
(paren
id|desc-&gt;status
op_amp
id|IRQ_PER_CPU
)paren
(brace
multiline_comment|/* no locking required for CPU-local interrupts: */
id|ack_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
id|action_ret
op_assign
id|handle_IRQ_event
c_func
(paren
id|irq
comma
id|regs
comma
id|desc-&gt;action
)paren
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|end
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|spin_lock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
id|ack_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t;   REPLAY is when Linux resends an IRQ that was dropped earlier&n;&t;   WAITING is used by probe to mark irqs that are being tested&n;&t;   */
id|status
op_assign
id|desc-&gt;status
op_amp
op_complement
(paren
id|IRQ_REPLAY
op_or
id|IRQ_WAITING
)paren
suffix:semicolon
id|status
op_or_assign
id|IRQ_PENDING
suffix:semicolon
multiline_comment|/* we _want_ to handle it */
multiline_comment|/*&n;&t; * If the IRQ is disabled for whatever reason, we cannot&n;&t; * use the action we have.&n;&t; */
id|action
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
(paren
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
)paren
(brace
id|action
op_assign
id|desc-&gt;action
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|action
op_logical_or
op_logical_neg
id|action-&gt;handler
)paren
(brace
id|ppc_spurious_interrupts
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Unhandled interrupt %x, disabled&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* We can&squot;t call disable_irq here, it would deadlock */
r_if
c_cond
(paren
op_logical_neg
id|desc-&gt;depth
)paren
id|desc-&gt;depth
op_assign
l_int|1
suffix:semicolon
id|desc-&gt;status
op_or_assign
id|IRQ_DISABLED
suffix:semicolon
multiline_comment|/* This is not a real spurrious interrupt, we&n;&t;&t;&t; * have to eoi it, so we jump to out&n;&t;&t;&t; */
id|mask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|status
op_and_assign
op_complement
id|IRQ_PENDING
suffix:semicolon
multiline_comment|/* we commit to handling */
id|status
op_or_assign
id|IRQ_INPROGRESS
suffix:semicolon
multiline_comment|/* we are handling it */
)brace
id|desc-&gt;status
op_assign
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * If there is no IRQ handler or it was disabled, exit early.&n;&t;   Since we set PENDING, if another processor is handling&n;&t;   a different instance of this same irq, the other processor&n;&t;   will take care of it.&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|action
)paren
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/*&n;&t; * Edge triggered interrupts need to remember&n;&t; * pending events.&n;&t; * This applies to any hw interrupts that allow a second&n;&t; * instance of the same irq to arrive while we are in do_IRQ&n;&t; * or in the handler. But the code here only handles the _second_&n;&t; * instance of the irq, not the third or fourth. So it is mostly&n;&t; * useful for irq hardware that does not mask cleanly in an&n;&t; * SMP environment.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
id|spin_unlock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IRQSTACKS
multiline_comment|/* Switch to the irq stack to handle this */
id|curtp
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
id|irqtp
op_assign
id|hardirq_ctx
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
r_if
c_cond
(paren
id|curtp
op_ne
id|irqtp
)paren
(brace
id|irqtp-&gt;task
op_assign
id|curtp-&gt;task
suffix:semicolon
id|irqtp-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|action_ret
op_assign
id|call_handle_IRQ_event
c_func
(paren
id|irq
comma
id|regs
comma
id|action
comma
id|irqtp
)paren
suffix:semicolon
id|irqtp-&gt;task
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|irqtp-&gt;flags
)paren
id|set_bits
c_func
(paren
id|irqtp-&gt;flags
comma
op_amp
id|curtp-&gt;flags
)paren
suffix:semicolon
)brace
r_else
macro_line|#endif
id|action_ret
op_assign
id|handle_IRQ_event
c_func
(paren
id|irq
comma
id|regs
comma
id|action
)paren
suffix:semicolon
id|spin_lock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|noirqdebug
)paren
id|note_interrupt
c_func
(paren
id|irq
comma
id|desc
comma
id|action_ret
)paren
suffix:semicolon
r_if
c_cond
(paren
id|likely
c_func
(paren
op_logical_neg
(paren
id|desc-&gt;status
op_amp
id|IRQ_PENDING
)paren
)paren
)paren
r_break
suffix:semicolon
id|desc-&gt;status
op_and_assign
op_complement
id|IRQ_PENDING
suffix:semicolon
)brace
id|out
suffix:colon
id|desc-&gt;status
op_and_assign
op_complement
id|IRQ_INPROGRESS
suffix:semicolon
multiline_comment|/*&n;&t; * The -&gt;end() handler has to deal with interrupts which got&n;&t; * disabled while the handler was running.&n;&t; */
r_if
c_cond
(paren
id|desc-&gt;handler
)paren
(brace
r_if
c_cond
(paren
id|desc-&gt;handler-&gt;end
)paren
id|desc-&gt;handler
op_member_access_from_pointer
id|end
c_func
(paren
id|irq
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|desc-&gt;handler-&gt;enable
)paren
id|desc-&gt;handler
op_member_access_from_pointer
id|enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
id|spin_unlock
c_func
(paren
op_amp
id|desc-&gt;lock
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PPC_ISERIES
DECL|function|do_IRQ
r_void
id|do_IRQ
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|paca_struct
op_star
id|lpaca
suffix:semicolon
r_struct
id|ItLpQueue
op_star
id|lpq
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_STACKOVERFLOW
multiline_comment|/* Debugging check for stack overflow: is there less than 2KB free? */
(brace
r_int
id|sp
suffix:semicolon
id|sp
op_assign
id|__get_SP
c_func
(paren
)paren
op_amp
(paren
id|THREAD_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|sp
OL
(paren
r_sizeof
(paren
r_struct
id|thread_info
)paren
op_plus
l_int|2048
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;do_IRQ: stack overflow: %ld&bslash;n&quot;
comma
id|sp
op_minus
r_sizeof
(paren
r_struct
id|thread_info
)paren
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|lpaca
op_assign
id|get_paca
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
id|lpaca-&gt;lppaca.xIntDword.xFields.xIpiCnt
)paren
(brace
id|lpaca-&gt;lppaca.xIntDword.xFields.xIpiCnt
op_assign
l_int|0
suffix:semicolon
id|iSeries_smp_message_recv
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SMP */
id|lpq
op_assign
id|lpaca-&gt;lpqueue_ptr
suffix:semicolon
r_if
c_cond
(paren
id|lpq
op_logical_and
id|ItLpQueue_isLpIntPending
c_func
(paren
id|lpq
)paren
)paren
id|lpevent_count
op_add_assign
id|ItLpQueue_process
c_func
(paren
id|lpq
comma
id|regs
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lpaca-&gt;lppaca.xIntDword.xFields.xDecrInt
)paren
(brace
id|lpaca-&gt;lppaca.xIntDword.xFields.xDecrInt
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Signal a fake decrementer interrupt */
id|timer_interrupt
c_func
(paren
id|regs
)paren
suffix:semicolon
)brace
)brace
macro_line|#else&t;/* CONFIG_PPC_ISERIES */
DECL|function|do_IRQ
r_void
id|do_IRQ
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
id|irq
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_STACKOVERFLOW
multiline_comment|/* Debugging check for stack overflow: is there less than 2KB free? */
(brace
r_int
id|sp
suffix:semicolon
id|sp
op_assign
id|__get_SP
c_func
(paren
)paren
op_amp
(paren
id|THREAD_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|sp
OL
(paren
r_sizeof
(paren
r_struct
id|thread_info
)paren
op_plus
l_int|2048
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;do_IRQ: stack overflow: %ld&bslash;n&quot;
comma
id|sp
op_minus
r_sizeof
(paren
r_struct
id|thread_info
)paren
)paren
suffix:semicolon
id|dump_stack
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
id|irq
op_assign
id|ppc_md
dot
id|get_irq
c_func
(paren
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_ge
l_int|0
)paren
id|ppc_irq_dispatch_handler
c_func
(paren
id|regs
comma
id|irq
)paren
suffix:semicolon
r_else
multiline_comment|/* That&squot;s not SMP safe ... but who cares ? */
id|ppc_spurious_interrupts
op_increment
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif&t;/* CONFIG_PPC_ISERIES */
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
r_static
r_int
id|once
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|once
)paren
r_return
suffix:semicolon
id|once
op_increment
suffix:semicolon
id|ppc_md
dot
id|init_IRQ
c_func
(paren
)paren
suffix:semicolon
id|irq_ctx_init
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#ifndef CONFIG_PPC_ISERIES
multiline_comment|/*&n; * Virtual IRQ mapping code, used on systems with XICS interrupt controllers.&n; */
DECL|macro|UNDEFINED_IRQ
mdefine_line|#define UNDEFINED_IRQ 0xffffffff
DECL|variable|virt_irq_to_real_map
r_int
r_int
id|virt_irq_to_real_map
(braket
id|NR_IRQS
)braket
suffix:semicolon
multiline_comment|/*&n; * Don&squot;t use virtual irqs 0, 1, 2 for devices.&n; * The pcnet32 driver considers interrupt numbers &lt; 2 to be invalid,&n; * and 2 is the XICS IPI interrupt.&n; * We limit virtual irqs to 17 less than NR_IRQS so that when we&n; * offset them by 16 (to reserve the first 16 for ISA interrupts)&n; * we don&squot;t end up with an interrupt number &gt;= NR_IRQS.&n; */
DECL|macro|MIN_VIRT_IRQ
mdefine_line|#define MIN_VIRT_IRQ&t;3
DECL|macro|MAX_VIRT_IRQ
mdefine_line|#define MAX_VIRT_IRQ&t;(NR_IRQS - NUM_ISA_INTERRUPTS - 1)
DECL|macro|NR_VIRT_IRQS
mdefine_line|#define NR_VIRT_IRQS&t;(MAX_VIRT_IRQ - MIN_VIRT_IRQ + 1)
r_void
DECL|function|virt_irq_init
id|virt_irq_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
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
id|virt_irq_to_real_map
(braket
id|i
)braket
op_assign
id|UNDEFINED_IRQ
suffix:semicolon
)brace
multiline_comment|/* Create a mapping for a real_irq if it doesn&squot;t already exist.&n; * Return the virtual irq as a convenience.&n; */
DECL|function|virt_irq_create_mapping
r_int
id|virt_irq_create_mapping
c_func
(paren
r_int
r_int
id|real_irq
)paren
(brace
r_int
r_int
id|virq
comma
id|first_virq
suffix:semicolon
r_static
r_int
id|warned
suffix:semicolon
r_if
c_cond
(paren
id|naca-&gt;interrupt_controller
op_eq
id|IC_OPEN_PIC
)paren
r_return
id|real_irq
suffix:semicolon
multiline_comment|/* no mapping for openpic (for now) */
multiline_comment|/* don&squot;t map interrupts &lt; MIN_VIRT_IRQ */
r_if
c_cond
(paren
id|real_irq
OL
id|MIN_VIRT_IRQ
)paren
(brace
id|virt_irq_to_real_map
(braket
id|real_irq
)braket
op_assign
id|real_irq
suffix:semicolon
r_return
id|real_irq
suffix:semicolon
)brace
multiline_comment|/* map to a number between MIN_VIRT_IRQ and MAX_VIRT_IRQ */
id|virq
op_assign
id|real_irq
suffix:semicolon
r_if
c_cond
(paren
id|virq
OG
id|MAX_VIRT_IRQ
)paren
id|virq
op_assign
(paren
id|virq
op_mod
id|NR_VIRT_IRQS
)paren
op_plus
id|MIN_VIRT_IRQ
suffix:semicolon
multiline_comment|/* search for this number or a free slot */
id|first_virq
op_assign
id|virq
suffix:semicolon
r_while
c_loop
(paren
id|virt_irq_to_real_map
(braket
id|virq
)braket
op_ne
id|UNDEFINED_IRQ
)paren
(brace
r_if
c_cond
(paren
id|virt_irq_to_real_map
(braket
id|virq
)braket
op_eq
id|real_irq
)paren
r_return
id|virq
suffix:semicolon
r_if
c_cond
(paren
op_increment
id|virq
OG
id|MAX_VIRT_IRQ
)paren
id|virq
op_assign
id|MIN_VIRT_IRQ
suffix:semicolon
r_if
c_cond
(paren
id|virq
op_eq
id|first_virq
)paren
r_goto
id|nospace
suffix:semicolon
multiline_comment|/* oops, no free slots */
)brace
id|virt_irq_to_real_map
(braket
id|virq
)braket
op_assign
id|real_irq
suffix:semicolon
r_return
id|virq
suffix:semicolon
id|nospace
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|warned
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Interrupt table is full&bslash;n&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Increase NR_IRQS (currently %d) &quot;
l_string|&quot;in your kernel sources and rebuild.&bslash;n&quot;
comma
id|NR_IRQS
)paren
suffix:semicolon
id|warned
op_assign
l_int|1
suffix:semicolon
)brace
r_return
id|NO_IRQ
suffix:semicolon
)brace
multiline_comment|/*&n; * In most cases will get a hit on the very first slot checked in the&n; * virt_irq_to_real_map.  Only when there are a large number of&n; * IRQs will this be expensive.&n; */
DECL|function|real_irq_to_virt_slowpath
r_int
r_int
id|real_irq_to_virt_slowpath
c_func
(paren
r_int
r_int
id|real_irq
)paren
(brace
r_int
r_int
id|virq
suffix:semicolon
r_int
r_int
id|first_virq
suffix:semicolon
id|virq
op_assign
id|real_irq
suffix:semicolon
r_if
c_cond
(paren
id|virq
OG
id|MAX_VIRT_IRQ
)paren
id|virq
op_assign
(paren
id|virq
op_mod
id|NR_VIRT_IRQS
)paren
op_plus
id|MIN_VIRT_IRQ
suffix:semicolon
id|first_virq
op_assign
id|virq
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|virt_irq_to_real_map
(braket
id|virq
)braket
op_eq
id|real_irq
)paren
r_return
id|virq
suffix:semicolon
id|virq
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|virq
op_ge
id|MAX_VIRT_IRQ
)paren
id|virq
op_assign
l_int|0
suffix:semicolon
)brace
r_while
c_loop
(paren
id|first_virq
op_ne
id|virq
)paren
suffix:semicolon
r_return
id|NO_IRQ
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_PPC_ISERIES */
macro_line|#ifdef CONFIG_IRQSTACKS
DECL|variable|softirq_ctx
r_struct
id|thread_info
op_star
id|softirq_ctx
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|variable|hardirq_ctx
r_struct
id|thread_info
op_star
id|hardirq_ctx
(braket
id|NR_CPUS
)braket
suffix:semicolon
DECL|function|irq_ctx_init
r_void
id|irq_ctx_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|thread_info
op_star
id|tp
suffix:semicolon
r_int
id|i
suffix:semicolon
id|for_each_cpu
c_func
(paren
id|i
)paren
(brace
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|softirq_ctx
(braket
id|i
)braket
comma
l_int|0
comma
id|THREAD_SIZE
)paren
suffix:semicolon
id|tp
op_assign
id|softirq_ctx
(braket
id|i
)braket
suffix:semicolon
id|tp-&gt;cpu
op_assign
id|i
suffix:semicolon
id|tp-&gt;preempt_count
op_assign
id|SOFTIRQ_OFFSET
suffix:semicolon
id|memset
c_func
(paren
(paren
r_void
op_star
)paren
id|hardirq_ctx
(braket
id|i
)braket
comma
l_int|0
comma
id|THREAD_SIZE
)paren
suffix:semicolon
id|tp
op_assign
id|hardirq_ctx
(braket
id|i
)braket
suffix:semicolon
id|tp-&gt;cpu
op_assign
id|i
suffix:semicolon
id|tp-&gt;preempt_count
op_assign
id|HARDIRQ_OFFSET
suffix:semicolon
)brace
)brace
DECL|function|do_softirq
r_void
id|do_softirq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|thread_info
op_star
id|curtp
comma
op_star
id|irqtp
suffix:semicolon
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
r_return
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|local_softirq_pending
c_func
(paren
)paren
)paren
(brace
id|curtp
op_assign
id|current_thread_info
c_func
(paren
)paren
suffix:semicolon
id|irqtp
op_assign
id|softirq_ctx
(braket
id|smp_processor_id
c_func
(paren
)paren
)braket
suffix:semicolon
id|irqtp-&gt;task
op_assign
id|curtp-&gt;task
suffix:semicolon
id|call_do_softirq
c_func
(paren
id|irqtp
)paren
suffix:semicolon
id|irqtp-&gt;task
op_assign
l_int|NULL
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|do_softirq
id|EXPORT_SYMBOL
c_func
(paren
id|do_softirq
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_IRQSTACKS */
eof
