multiline_comment|/*&n; *  arch/ppc/kernel/irq.c&n; *&n; *  Derived from arch/i386/kernel/irq.c&n; *    Copyright (C) 1992 Linus Torvalds&n; *  Adapted from arch/i386 by Gary Thomas&n; *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)&n; *  Updated and modified by Cort Dougan &lt;cort@fsmlabs.com&gt;&n; *    Copyright (C) 1996-2001 Cort Dougan&n; *  Adapted for Power Macintosh by Paul Mackerras&n; *    Copyright (C) 1996 Paul Mackerras (paulus@cs.anu.edu.au)&n; *  Amiga/APUS changes by Jesper Skov (jskov@cygnus.co.uk).&n; *&n; * This file contains the code used by various IRQ handling routines:&n; * asking for different IRQ&squot;s should be done through these routines&n; * instead of just grabbing them. Thus setups with different IRQ numbers&n; * shouldn&squot;t result in any weird surprises, and installing new handlers&n; * should be easier.&n; *&n; * The MPC8xx has an interrupt mask in the SIU.  If a bit is set, the&n; * interrupt is _enabled_.  As expected, IRQ0 is bit 0 in the 32-bit&n; * mask register (of which only 16 are defined), hence the weird shifting&n; * and complement of the cached_irq_mask.  I want to be able to stuff&n; * this right into the SIU SMASK register.&n; * Many of the prep/chrp functions are conditional compiled on CONFIG_8xx&n; * to reduce code space and undefined function references.&n; */
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/kernel_stat.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
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
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &lt;linux/cpumask.h&gt;
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
DECL|macro|NR_MASK_WORDS
mdefine_line|#define NR_MASK_WORDS&t;((NR_IRQS + 31) / 32)
r_extern
id|atomic_t
id|ipi_recv
suffix:semicolon
r_extern
id|atomic_t
id|ipi_sent
suffix:semicolon
DECL|macro|MAXCOUNT
mdefine_line|#define MAXCOUNT 10000000
DECL|variable|ppc_spurious_interrupts
r_int
id|ppc_spurious_interrupts
op_assign
l_int|0
suffix:semicolon
DECL|variable|ppc_irq_action
r_struct
id|irqaction
op_star
id|ppc_irq_action
(braket
id|NR_IRQS
)braket
suffix:semicolon
DECL|variable|ppc_cached_irq_mask
r_int
r_int
id|ppc_cached_irq_mask
(braket
id|NR_MASK_WORDS
)braket
suffix:semicolon
DECL|variable|ppc_lost_interrupts
r_int
r_int
id|ppc_lost_interrupts
(braket
id|NR_MASK_WORDS
)braket
suffix:semicolon
DECL|variable|ppc_n_lost_interrupts
id|atomic_t
id|ppc_n_lost_interrupts
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
id|irq_desc
(braket
id|i
)braket
dot
id|handler
)paren
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot; %s &quot;
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
r_else
id|seq_puts
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
id|irq_desc
(braket
id|i
)braket
dot
id|status
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
r_else
r_if
c_cond
(paren
id|i
op_eq
id|NR_IRQS
)paren
(brace
macro_line|#ifdef CONFIG_TAU_INT
r_if
c_cond
(paren
id|tau_initialized
)paren
(brace
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;TAU: &quot;
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
l_string|&quot;%10u &quot;
comma
id|tau_interrupts
c_func
(paren
id|j
)paren
)paren
suffix:semicolon
id|seq_puts
c_func
(paren
id|p
comma
l_string|&quot;  PowerPC             Thermal Assist (cpu temp)&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SMP
multiline_comment|/* should this be per processor send/receive? */
id|seq_printf
c_func
(paren
id|p
comma
l_string|&quot;IPI (recv/sent): %10u/%u&bslash;n&quot;
comma
id|atomic_read
c_func
(paren
op_amp
id|ipi_recv
)paren
comma
id|atomic_read
c_func
(paren
op_amp
id|ipi_sent
)paren
)paren
suffix:semicolon
macro_line|#endif
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
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
comma
id|first
op_assign
l_int|1
suffix:semicolon
id|irq_enter
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Every platform is required to implement ppc_md.get_irq.&n;&t; * This function will either return an irq number or -1 to&n;&t; * indicate there are no more pending.  But the first time&n;&t; * through the loop this means there wasn&squot;t and IRQ pending.&n;&t; * The value -2 is for buggy hardware and means that this IRQ&n;&t; * has already been handled. -- Tom&n;&t; */
r_while
c_loop
(paren
(paren
id|irq
op_assign
id|ppc_md
dot
id|get_irq
c_func
(paren
id|regs
)paren
)paren
op_ge
l_int|0
)paren
(brace
id|__do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
id|first
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|irq
op_ne
op_minus
l_int|2
op_logical_and
id|first
)paren
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
DECL|function|init_IRQ
r_void
id|__init
id|init_IRQ
c_func
(paren
r_void
)paren
(brace
id|ppc_md
dot
id|init_IRQ
c_func
(paren
)paren
suffix:semicolon
)brace
eof
