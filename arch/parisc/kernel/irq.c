multiline_comment|/* &n; * Code to handle x86 style IRQs plus some generic interrupt stuff.&n; *&n; * Copyright (C) 1992 Linus Torvalds&n; * Copyright (C) 1994, 1995, 1996, 1997, 1998 Ralf Baechle&n; * Copyright (C) 1999 SuSE GmbH (Philipp Rumpf, prumpf@tux.org)&n; * Copyright (C) 1999-2000 Grant Grundler&n; * Copyright (c) 2005 Matthew Wilcox&n; *&n; *    This program is free software; you can redistribute it and/or modify&n; *    it under the terms of the GNU General Public License as published by&n; *    the Free Software Foundation; either version 2, or (at your option)&n; *    any later version.&n; *&n; *    This program is distributed in the hope that it will be useful,&n; *    but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *    GNU General Public License for more details.&n; *&n; *    You should have received a copy of the GNU General Public License&n; *    along with this program; if not, write to the Free Software&n; *    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; */
macro_line|#include &lt;linux/bitops.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/types.h&gt;
DECL|macro|PARISC_IRQ_CR16_COUNTS
macro_line|#undef PARISC_IRQ_CR16_COUNTS
r_extern
id|irqreturn_t
id|timer_interrupt
c_func
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
suffix:semicolon
r_extern
id|irqreturn_t
id|ipi_interrupt
c_func
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
suffix:semicolon
DECL|macro|EIEM_MASK
mdefine_line|#define EIEM_MASK(irq)       (1UL&lt;&lt;(CPU_IRQ_MAX - irq))
multiline_comment|/* Bits in EIEM correlate with cpu_irq_action[].&n;** Numbered *Big Endian*! (ie bit 0 is MSB)&n;*/
DECL|variable|cpu_eiem
r_static
r_volatile
r_int
r_int
id|cpu_eiem
op_assign
l_int|0
suffix:semicolon
DECL|function|cpu_set_eiem
r_static
r_void
id|cpu_set_eiem
c_func
(paren
r_void
op_star
id|info
)paren
(brace
id|set_eiem
c_func
(paren
(paren
r_int
r_int
)paren
id|info
)paren
suffix:semicolon
)brace
DECL|function|cpu_disable_irq
r_static
r_inline
r_void
id|cpu_disable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|eirr_bit
op_assign
id|EIEM_MASK
c_func
(paren
id|irq
)paren
suffix:semicolon
id|cpu_eiem
op_and_assign
op_complement
id|eirr_bit
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|cpu_set_eiem
comma
(paren
r_void
op_star
)paren
id|cpu_eiem
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|cpu_enable_irq
r_static
r_void
id|cpu_enable_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|eirr_bit
op_assign
id|EIEM_MASK
c_func
(paren
id|irq
)paren
suffix:semicolon
id|mtctl
c_func
(paren
id|eirr_bit
comma
l_int|23
)paren
suffix:semicolon
multiline_comment|/* clear EIRR bit before unmasking */
id|cpu_eiem
op_or_assign
id|eirr_bit
suffix:semicolon
id|on_each_cpu
c_func
(paren
id|cpu_set_eiem
comma
(paren
r_void
op_star
)paren
id|cpu_eiem
comma
l_int|1
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|cpu_startup_irq
r_static
r_int
r_int
id|cpu_startup_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|cpu_enable_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|no_ack_irq
r_void
id|no_ack_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|function|no_end_irq
r_void
id|no_end_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
DECL|variable|cpu_interrupt_type
r_static
r_struct
id|hw_interrupt_type
id|cpu_interrupt_type
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;CPU&quot;
comma
dot
id|startup
op_assign
id|cpu_startup_irq
comma
dot
id|shutdown
op_assign
id|cpu_disable_irq
comma
dot
id|enable
op_assign
id|cpu_enable_irq
comma
dot
id|disable
op_assign
id|cpu_disable_irq
comma
dot
id|ack
op_assign
id|no_ack_irq
comma
dot
id|end
op_assign
id|no_end_irq
comma
singleline_comment|//&t;.set_affinity&t;= cpu_set_affinity_irq,
)brace
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
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;    &quot;
)paren
suffix:semicolon
id|for_each_online_cpu
c_func
(paren
id|j
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;       CPU%d&quot;
comma
id|j
)paren
suffix:semicolon
macro_line|#ifdef PARISC_IRQ_CR16_COUNTS
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; [min/avg/max] (CPU cycle counts)&quot;
)paren
suffix:semicolon
macro_line|#endif
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_desc
(braket
id|i
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
r_struct
id|irqaction
op_star
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
id|for_each_online_cpu
c_func
(paren
id|j
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
macro_line|#endif
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; %14s&quot;
comma
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_member_access_from_pointer
r_typename
)paren
suffix:semicolon
macro_line|#ifndef PARISC_IRQ_CR16_COUNTS
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
r_while
c_loop
(paren
(paren
id|action
op_assign
id|action-&gt;next
)paren
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
macro_line|#else
r_for
c_loop
(paren
suffix:semicolon
id|action
suffix:semicolon
id|action
op_assign
id|action-&gt;next
)paren
(brace
r_int
r_int
id|k
comma
id|avg
comma
id|min
comma
id|max
suffix:semicolon
id|min
op_assign
id|max
op_assign
id|action-&gt;cr16_hist
(braket
l_int|0
)braket
suffix:semicolon
r_for
c_loop
(paren
id|avg
op_assign
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|PARISC_CR16_HIST_SIZE
suffix:semicolon
id|k
op_increment
)paren
(brace
r_int
id|hist
op_assign
id|action-&gt;cr16_hist
(braket
id|k
)braket
suffix:semicolon
r_if
c_cond
(paren
id|hist
)paren
(brace
id|avg
op_add_assign
id|hist
suffix:semicolon
)brace
r_else
r_break
suffix:semicolon
r_if
c_cond
(paren
id|hist
OG
id|max
)paren
id|max
op_assign
id|hist
suffix:semicolon
r_if
c_cond
(paren
id|hist
OL
id|min
)paren
id|min
op_assign
id|hist
suffix:semicolon
)brace
id|avg
op_div_assign
id|k
suffix:semicolon
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; %s[%d/%d/%d]&quot;
comma
id|action-&gt;name
comma
id|min
comma
id|avg
comma
id|max
)paren
suffix:semicolon
)brace
macro_line|#endif
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
id|irq_desc
(braket
id|i
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n;** The following form a &quot;set&quot;: Virtual IRQ, Transaction Address, Trans Data.&n;** Respectively, these map to IRQ region+EIRR, Processor HPA, EIRR bit.&n;**&n;** To use txn_XXX() interfaces, get a Virtual IRQ first.&n;** Then use that to get the Transaction address and data.&n;*/
DECL|function|cpu_claim_irq
r_int
id|cpu_claim_irq
c_func
(paren
r_int
r_int
id|irq
comma
r_struct
id|hw_interrupt_type
op_star
id|type
comma
r_void
op_star
id|data
)paren
(brace
r_if
c_cond
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|action
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_ne
op_amp
id|cpu_interrupt_type
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|type
)paren
(brace
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
op_assign
id|type
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|handler_data
op_assign
id|data
suffix:semicolon
id|cpu_interrupt_type
dot
id|enable
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|txn_claim_irq
r_int
id|txn_claim_irq
c_func
(paren
r_int
id|irq
)paren
(brace
r_return
id|cpu_claim_irq
c_func
(paren
id|irq
comma
l_int|NULL
comma
l_int|NULL
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
id|irq
suffix:semicolon
)brace
multiline_comment|/*&n; * The bits_wide parameter accommodates the limitations of the HW/SW which&n; * use these bits:&n; * Legacy PA I/O (GSC/NIO): 5 bits (architected EIM register)&n; * V-class (EPIC):          6 bits&n; * N/L/A-class (iosapic):   8 bits&n; * PCI 2.2 MSI:            16 bits&n; * Some PCI devices:       32 bits (Symbios SCSI/ATM/HyperFabric)&n; *&n; * On the service provider side:&n; * o PA 1.1 (and PA2.0 narrow mode)     5-bits (width of EIR register)&n; * o PA 2.0 wide mode                   6-bits (per processor)&n; * o IA64                               8-bits (0-256 total)&n; *&n; * So a Legacy PA I/O device on a PA 2.0 box can&squot;t use all the bits supported&n; * by the processor...and the N/L-class I/O subsystem supports more bits than&n; * PA2.0 has. The first case is the problem.&n; */
DECL|function|txn_alloc_irq
r_int
id|txn_alloc_irq
c_func
(paren
r_int
r_int
id|bits_wide
)paren
(brace
r_int
id|irq
suffix:semicolon
multiline_comment|/* never return irq 0 cause that&squot;s the interval timer */
r_for
c_loop
(paren
id|irq
op_assign
id|CPU_IRQ_BASE
op_plus
l_int|1
suffix:semicolon
id|irq
op_le
id|CPU_IRQ_MAX
suffix:semicolon
id|irq
op_increment
)paren
(brace
r_if
c_cond
(paren
id|cpu_claim_irq
c_func
(paren
id|irq
comma
l_int|NULL
comma
l_int|NULL
)paren
OL
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|irq
op_minus
id|CPU_IRQ_BASE
)paren
op_ge
(paren
l_int|1
op_lshift
id|bits_wide
)paren
)paren
r_continue
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
multiline_comment|/* unlikely, but be prepared */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|txn_alloc_addr
r_int
r_int
id|txn_alloc_addr
c_func
(paren
r_int
r_int
id|virt_irq
)paren
(brace
r_static
r_int
id|next_cpu
op_assign
op_minus
l_int|1
suffix:semicolon
id|next_cpu
op_increment
suffix:semicolon
multiline_comment|/* assign to &quot;next&quot; CPU we want this bugger on */
multiline_comment|/* validate entry */
r_while
c_loop
(paren
(paren
id|next_cpu
OL
id|NR_CPUS
)paren
op_logical_and
(paren
op_logical_neg
id|cpu_data
(braket
id|next_cpu
)braket
dot
id|txn_addr
op_logical_or
op_logical_neg
id|cpu_online
c_func
(paren
id|next_cpu
)paren
)paren
)paren
id|next_cpu
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|next_cpu
op_ge
id|NR_CPUS
)paren
id|next_cpu
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* nothing else, assign monarch */
r_return
id|cpu_data
(braket
id|next_cpu
)braket
dot
id|txn_addr
suffix:semicolon
)brace
DECL|function|txn_alloc_data
r_int
r_int
id|txn_alloc_data
c_func
(paren
r_int
r_int
id|virt_irq
)paren
(brace
r_return
id|virt_irq
op_minus
id|CPU_IRQ_BASE
suffix:semicolon
)brace
multiline_comment|/* ONLY called from entry.S:intr_extint() */
DECL|function|do_cpu_irq_mask
r_void
id|do_cpu_irq_mask
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
id|eirr_val
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Only allow interrupt processing to be interrupted by the&n;&t; * timer tick&n;&t; */
id|set_eiem
c_func
(paren
id|EIEM_MASK
c_func
(paren
id|TIMER_IRQ
)paren
)paren
suffix:semicolon
multiline_comment|/* 1) only process IRQs that are enabled/unmasked (cpu_eiem)&n;&t; * 2) We loop here on EIRR contents in order to avoid&n;&t; *    nested interrupts or having to take another interrupt&n;&t; *    when we could have just handled it right away.&n;&t; */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_int
r_int
id|bit
op_assign
(paren
l_int|1UL
op_lshift
(paren
id|BITS_PER_LONG
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_int
r_int
id|irq
suffix:semicolon
id|eirr_val
op_assign
id|mfctl
c_func
(paren
l_int|23
)paren
op_amp
id|cpu_eiem
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|eirr_val
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|eirr_val
op_amp
id|EIEM_MASK
c_func
(paren
id|TIMER_IRQ
)paren
)paren
id|set_eiem
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|mtctl
c_func
(paren
id|eirr_val
comma
l_int|23
)paren
suffix:semicolon
multiline_comment|/* reset bits we are going to process */
multiline_comment|/* Work our way from MSb to LSb...same order we alloc EIRs */
r_for
c_loop
(paren
id|irq
op_assign
id|TIMER_IRQ
suffix:semicolon
id|eirr_val
op_logical_and
id|bit
suffix:semicolon
id|bit
op_rshift_assign
l_int|1
comma
id|irq
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|bit
op_amp
id|eirr_val
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/* clear bit in mask - can exit loop sooner */
id|eirr_val
op_and_assign
op_complement
id|bit
suffix:semicolon
id|__do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
)brace
id|set_eiem
c_func
(paren
id|cpu_eiem
)paren
suffix:semicolon
id|irq_exit
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|timer_action
r_static
r_struct
id|irqaction
id|timer_action
op_assign
(brace
dot
id|handler
op_assign
id|timer_interrupt
comma
dot
id|name
op_assign
l_string|&quot;timer&quot;
comma
)brace
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
DECL|variable|ipi_action
r_static
r_struct
id|irqaction
id|ipi_action
op_assign
(brace
dot
id|handler
op_assign
id|ipi_interrupt
comma
dot
id|name
op_assign
l_string|&quot;IPI&quot;
comma
)brace
suffix:semicolon
macro_line|#endif
DECL|function|claim_cpu_irqs
r_static
r_void
id|claim_cpu_irqs
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
id|CPU_IRQ_BASE
suffix:semicolon
id|i
op_le
id|CPU_IRQ_MAX
suffix:semicolon
id|i
op_increment
)paren
(brace
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|cpu_interrupt_type
suffix:semicolon
)brace
id|irq_desc
(braket
id|TIMER_IRQ
)braket
dot
id|action
op_assign
op_amp
id|timer_action
suffix:semicolon
id|irq_desc
(braket
id|TIMER_IRQ
)braket
dot
id|status
op_or_assign
id|IRQ_PER_CPU
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|irq_desc
(braket
id|IPI_IRQ
)braket
dot
id|action
op_assign
op_amp
id|ipi_action
suffix:semicolon
id|irq_desc
(braket
id|IPI_IRQ
)braket
dot
id|status
op_assign
id|IRQ_PER_CPU
suffix:semicolon
macro_line|#endif
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
id|local_irq_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* PARANOID - should already be disabled */
id|mtctl
c_func
(paren
op_complement
l_int|0UL
comma
l_int|23
)paren
suffix:semicolon
multiline_comment|/* EIRR : clear all pending external intr */
id|claim_cpu_irqs
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|cpu_eiem
)paren
id|cpu_eiem
op_assign
id|EIEM_MASK
c_func
(paren
id|IPI_IRQ
)paren
op_or
id|EIEM_MASK
c_func
(paren
id|TIMER_IRQ
)paren
suffix:semicolon
macro_line|#else
id|cpu_eiem
op_assign
id|EIEM_MASK
c_func
(paren
id|TIMER_IRQ
)paren
suffix:semicolon
macro_line|#endif
id|set_eiem
c_func
(paren
id|cpu_eiem
)paren
suffix:semicolon
multiline_comment|/* EIEM : enable all external intr */
)brace
DECL|function|hw_resend_irq
r_void
id|hw_resend_irq
c_func
(paren
r_struct
id|hw_interrupt_type
op_star
id|type
comma
r_int
r_int
id|irq
)paren
(brace
multiline_comment|/* XXX: Needs to be written.  We managed without it so far, but&n;&t; * we really ought to write it.&n;&t; */
)brace
DECL|function|ack_bad_irq
r_void
id|ack_bad_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;unexpected IRQ %d&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
)brace
eof
