multiline_comment|/*&n; * I/O SAPIC support.&n; *&n; * Copyright (C) 1999 Intel Corp.&n; * Copyright (C) 1999 Asit Mallick &lt;asit.k.mallick@intel.com&gt;&n; * Copyright (C) 2000-2002 J.I. Lee &lt;jung-ik.lee@intel.com&gt;&n; * Copyright (C) 1999-2000, 2002-2003 Hewlett-Packard Co.&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; * Copyright (C) 1999 VA Linux Systems&n; * Copyright (C) 1999,2000 Walt Drummond &lt;drummond@valinux.com&gt;&n; *&n; * 00/04/19&t;D. Mosberger&t;Rewritten to mirror more closely the x86 I/O APIC code.&n; *&t;&t;&t;&t;In particular, we now have separate handlers for edge&n; *&t;&t;&t;&t;and level triggered interrupts.&n; * 00/10/27&t;Asit Mallick, Goutham Rao &lt;goutham.rao@intel.com&gt; IRQ vector allocation&n; *&t;&t;&t;&t;PCI to vector mapping, shared PCI interrupts.&n; * 00/10/27&t;D. Mosberger&t;Document things a bit more to make them more understandable.&n; *&t;&t;&t;&t;Clean up much of the old IOSAPIC cruft.&n; * 01/07/27&t;J.I. Lee&t;PCI irq routing, Platform/Legacy interrupts and fixes for&n; *&t;&t;&t;&t;ACPI S5(SoftOff) support.&n; * 02/01/23&t;J.I. Lee&t;iosapic pgm fixes for PCI irq routing from _PRT&n; * 02/01/07     E. Focht        &lt;efocht@ess.nec.de&gt; Redirectable interrupt vectors in&n; *                              iosapic_set_affinity(), initializations for&n; *                              /proc/irq/#/smp_affinity&n; * 02/04/02&t;P. Diefenbaugh&t;Cleaned up ACPI PCI IRQ routing.&n; * 02/04/18&t;J.I. Lee&t;bug fix in iosapic_init_pci_irq&n; * 02/04/30&t;J.I. Lee&t;bug fix in find_iosapic to fix ACPI PCI IRQ to IOSAPIC mapping&n; *&t;&t;&t;&t;error&n; * 02/07/29&t;T. Kochi&t;Allocate interrupt vectors dynamically&n; * 02/08/04&t;T. Kochi&t;Cleaned up terminology (irq, global system interrupt, vector, etc.)&n; * 02/09/20&t;D. Mosberger&t;Simplified by taking advantage of ACPI&squot;s pci_irq code.&n; * 03/02/19&t;B. Helgaas&t;Make pcat_compat system-wide, not per-IOSAPIC.&n; *&t;&t;&t;&t;Remove iosapic_address &amp; gsi_base from external interfaces.&n; *&t;&t;&t;&t;Rationalize __init/__devinit attributes.&n; */
multiline_comment|/*&n; * Here is what the interrupt logic between a PCI device and the kernel looks like:&n; *&n; * (1) A PCI device raises one of the four interrupt pins (INTA, INTB, INTC, INTD).  The&n; *     device is uniquely identified by its bus--, and slot-number (the function&n; *     number does not matter here because all functions share the same interrupt&n; *     lines).&n; *&n; * (2) The motherboard routes the interrupt line to a pin on a IOSAPIC controller.&n; *     Multiple interrupt lines may have to share the same IOSAPIC pin (if they&squot;re level&n; *     triggered and use the same polarity).  Each interrupt line has a unique Global&n; *     System Interrupt (GSI) number which can be calculated as the sum of the controller&squot;s&n; *     base GSI number and the IOSAPIC pin number to which the line connects.&n; *&n; * (3) The IOSAPIC uses an internal routing table entries (RTEs) to map the IOSAPIC pin&n; *     into the IA-64 interrupt vector.  This interrupt vector is then sent to the CPU.&n; *&n; * (4) The kernel recognizes an interrupt as an IRQ.  The IRQ interface is used as&n; *     architecture-independent interrupt handling mechanism in Linux.  As an&n; *     IRQ is a number, we have to have IA-64 interrupt vector number &lt;-&gt; IRQ number&n; *     mapping.  On smaller systems, we use one-to-one mapping between IA-64 vector and&n; *     IRQ.  A platform can implement platform_irq_to_vector(irq) and&n; *     platform_local_vector_to_irq(vector) APIs to differentiate the mapping.&n; *     Please see also include/asm-ia64/hw_irq.h for those APIs.&n; *&n; * To sum up, there are three levels of mappings involved:&n; *&n; *&t;PCI pin -&gt; global system interrupt (GSI) -&gt; IA-64 vector &lt;-&gt; IRQ&n; *&n; * Note: The term &quot;IRQ&quot; is loosely used everywhere in Linux kernel to describe interrupts.&n; * Now we use &quot;IRQ&quot; only for Linux IRQ&squot;s.  ISA IRQ (isa_irq) is the only exception in this&n; * source code.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
macro_line|#include &lt;asm/hw_irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/iosapic.h&gt;
macro_line|#include &lt;asm/machvec.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
DECL|macro|DEBUG_INTERRUPT_ROUTING
macro_line|#undef DEBUG_INTERRUPT_ROUTING
DECL|macro|OVERRIDE_DEBUG
macro_line|#undef OVERRIDE_DEBUG
macro_line|#ifdef DEBUG_INTERRUPT_ROUTING
DECL|macro|DBG
mdefine_line|#define DBG(fmt...)&t;printk(fmt)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(fmt...)
macro_line|#endif
DECL|variable|iosapic_lock
r_static
id|spinlock_t
id|iosapic_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/* These tables map IA-64 vectors to the IOSAPIC pin that generates this vector. */
DECL|struct|iosapic_intr_info
r_static
r_struct
id|iosapic_intr_info
(brace
DECL|member|addr
r_char
op_star
id|addr
suffix:semicolon
multiline_comment|/* base address of IOSAPIC */
DECL|member|gsi_base
r_int
r_int
id|gsi_base
suffix:semicolon
multiline_comment|/* first GSI assigned to this IOSAPIC */
DECL|member|rte_index
r_char
id|rte_index
suffix:semicolon
multiline_comment|/* IOSAPIC RTE index (-1 =&gt; not an IOSAPIC interrupt) */
DECL|member|dmode
r_int
r_char
id|dmode
suffix:colon
l_int|3
suffix:semicolon
multiline_comment|/* delivery mode (see iosapic.h) */
DECL|member|polarity
r_int
r_char
id|polarity
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* interrupt polarity (see iosapic.h) */
DECL|member|trigger
r_int
r_char
id|trigger
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* trigger mode (see iosapic.h) */
DECL|variable|iosapic_intr_info
)brace
id|iosapic_intr_info
(braket
id|IA64_NUM_VECTORS
)braket
suffix:semicolon
DECL|struct|iosapic
r_static
r_struct
id|iosapic
(brace
DECL|member|addr
r_char
op_star
id|addr
suffix:semicolon
multiline_comment|/* base address of IOSAPIC */
DECL|member|gsi_base
r_int
r_int
id|gsi_base
suffix:semicolon
multiline_comment|/* first GSI assigned to this IOSAPIC */
DECL|member|num_rte
r_int
r_int
id|num_rte
suffix:semicolon
multiline_comment|/* number of RTE in this IOSAPIC */
DECL|variable|iosapic_lists
)brace
id|iosapic_lists
(braket
l_int|256
)braket
suffix:semicolon
DECL|variable|num_iosapic
r_static
r_int
id|num_iosapic
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
r_char
id|pcat_compat
id|__initdata
suffix:semicolon
multiline_comment|/* 8259 compatibility flag */
multiline_comment|/*&n; * Find an IOSAPIC associated with a GSI&n; */
r_static
r_inline
r_int
DECL|function|find_iosapic
id|find_iosapic
(paren
r_int
r_int
id|gsi
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
id|num_iosapic
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
r_int
)paren
(paren
id|gsi
op_minus
id|iosapic_lists
(braket
id|i
)braket
dot
id|gsi_base
)paren
OL
id|iosapic_lists
(braket
id|i
)braket
dot
id|num_rte
)paren
r_return
id|i
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_static
r_inline
r_int
DECL|function|_gsi_to_vector
id|_gsi_to_vector
(paren
r_int
r_int
id|gsi
)paren
(brace
r_struct
id|iosapic_intr_info
op_star
id|info
suffix:semicolon
r_for
c_loop
(paren
id|info
op_assign
id|iosapic_intr_info
suffix:semicolon
id|info
OL
id|iosapic_intr_info
op_plus
id|IA64_NUM_VECTORS
suffix:semicolon
op_increment
id|info
)paren
r_if
c_cond
(paren
id|info-&gt;gsi_base
op_plus
id|info-&gt;rte_index
op_eq
id|gsi
)paren
r_return
id|info
op_minus
id|iosapic_intr_info
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * Translate GSI number to the corresponding IA-64 interrupt vector.  If no&n; * entry exists, return -1.&n; */
r_inline
r_int
DECL|function|gsi_to_vector
id|gsi_to_vector
(paren
r_int
r_int
id|gsi
)paren
(brace
r_return
id|_gsi_to_vector
c_func
(paren
id|gsi
)paren
suffix:semicolon
)brace
r_int
DECL|function|gsi_to_irq
id|gsi_to_irq
(paren
r_int
r_int
id|gsi
)paren
(brace
multiline_comment|/*&n;&t; * XXX fix me: this assumes an identity mapping vetween IA-64 vector and Linux irq&n;&t; * numbers...&n;&t; */
r_return
id|_gsi_to_vector
c_func
(paren
id|gsi
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|set_rte
id|set_rte
(paren
r_int
r_int
id|vector
comma
r_int
r_int
id|dest
)paren
(brace
r_int
r_int
id|pol
comma
id|trigger
comma
id|dmode
suffix:semicolon
id|u32
id|low32
comma
id|high32
suffix:semicolon
r_char
op_star
id|addr
suffix:semicolon
r_int
id|rte_index
suffix:semicolon
r_char
id|redir
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_DEBUG
l_string|&quot;IOSAPIC: routing vector %d to 0x%x&bslash;n&quot;
comma
id|vector
comma
id|dest
)paren
suffix:semicolon
id|rte_index
op_assign
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|rte_index
suffix:semicolon
r_if
c_cond
(paren
id|rte_index
OL
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* not an IOSAPIC interrupt */
id|addr
op_assign
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|addr
suffix:semicolon
id|pol
op_assign
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|polarity
suffix:semicolon
id|trigger
op_assign
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|trigger
suffix:semicolon
id|dmode
op_assign
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|dmode
suffix:semicolon
id|redir
op_assign
(paren
id|dmode
op_eq
id|IOSAPIC_LOWEST_PRIORITY
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
(brace
r_int
r_int
id|irq
suffix:semicolon
r_for
c_loop
(paren
id|irq
op_assign
l_int|0
suffix:semicolon
id|irq
OL
id|NR_IRQS
suffix:semicolon
op_increment
id|irq
)paren
r_if
c_cond
(paren
id|irq_to_vector
c_func
(paren
id|irq
)paren
op_eq
id|vector
)paren
(brace
id|set_irq_affinity_info
c_func
(paren
id|irq
comma
(paren
r_int
)paren
(paren
id|dest
op_amp
l_int|0xffff
)paren
comma
id|redir
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif
id|low32
op_assign
(paren
(paren
id|pol
op_lshift
id|IOSAPIC_POLARITY_SHIFT
)paren
op_or
(paren
id|trigger
op_lshift
id|IOSAPIC_TRIGGER_SHIFT
)paren
op_or
(paren
id|dmode
op_lshift
id|IOSAPIC_DELIVERY_SHIFT
)paren
op_or
id|vector
)paren
suffix:semicolon
multiline_comment|/* dest contains both id and eid */
id|high32
op_assign
(paren
id|dest
op_lshift
id|IOSAPIC_DEST_SHIFT
)paren
suffix:semicolon
id|writel
c_func
(paren
id|IOSAPIC_RTE_HIGH
c_func
(paren
id|rte_index
)paren
comma
id|addr
op_plus
id|IOSAPIC_REG_SELECT
)paren
suffix:semicolon
id|writel
c_func
(paren
id|high32
comma
id|addr
op_plus
id|IOSAPIC_WINDOW
)paren
suffix:semicolon
id|writel
c_func
(paren
id|IOSAPIC_RTE_LOW
c_func
(paren
id|rte_index
)paren
comma
id|addr
op_plus
id|IOSAPIC_REG_SELECT
)paren
suffix:semicolon
id|writel
c_func
(paren
id|low32
comma
id|addr
op_plus
id|IOSAPIC_WINDOW
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|nop
id|nop
(paren
r_int
r_int
id|vector
)paren
(brace
multiline_comment|/* do nothing... */
)brace
r_static
r_void
DECL|function|mask_irq
id|mask_irq
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_char
op_star
id|addr
suffix:semicolon
id|u32
id|low32
suffix:semicolon
r_int
id|rte_index
suffix:semicolon
id|ia64_vector
id|vec
op_assign
id|irq_to_vector
c_func
(paren
id|irq
)paren
suffix:semicolon
id|addr
op_assign
id|iosapic_intr_info
(braket
id|vec
)braket
dot
id|addr
suffix:semicolon
id|rte_index
op_assign
id|iosapic_intr_info
(braket
id|vec
)braket
dot
id|rte_index
suffix:semicolon
r_if
c_cond
(paren
id|rte_index
OL
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* not an IOSAPIC interrupt! */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iosapic_lock
comma
id|flags
)paren
suffix:semicolon
(brace
id|writel
c_func
(paren
id|IOSAPIC_RTE_LOW
c_func
(paren
id|rte_index
)paren
comma
id|addr
op_plus
id|IOSAPIC_REG_SELECT
)paren
suffix:semicolon
id|low32
op_assign
id|readl
c_func
(paren
id|addr
op_plus
id|IOSAPIC_WINDOW
)paren
suffix:semicolon
id|low32
op_or_assign
(paren
l_int|1
op_lshift
id|IOSAPIC_MASK_SHIFT
)paren
suffix:semicolon
multiline_comment|/* set only the mask bit */
id|writel
c_func
(paren
id|low32
comma
id|addr
op_plus
id|IOSAPIC_WINDOW
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iosapic_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|unmask_irq
id|unmask_irq
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_char
op_star
id|addr
suffix:semicolon
id|u32
id|low32
suffix:semicolon
r_int
id|rte_index
suffix:semicolon
id|ia64_vector
id|vec
op_assign
id|irq_to_vector
c_func
(paren
id|irq
)paren
suffix:semicolon
id|addr
op_assign
id|iosapic_intr_info
(braket
id|vec
)braket
dot
id|addr
suffix:semicolon
id|rte_index
op_assign
id|iosapic_intr_info
(braket
id|vec
)braket
dot
id|rte_index
suffix:semicolon
r_if
c_cond
(paren
id|rte_index
OL
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* not an IOSAPIC interrupt! */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iosapic_lock
comma
id|flags
)paren
suffix:semicolon
(brace
id|writel
c_func
(paren
id|IOSAPIC_RTE_LOW
c_func
(paren
id|rte_index
)paren
comma
id|addr
op_plus
id|IOSAPIC_REG_SELECT
)paren
suffix:semicolon
id|low32
op_assign
id|readl
c_func
(paren
id|addr
op_plus
id|IOSAPIC_WINDOW
)paren
suffix:semicolon
id|low32
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|IOSAPIC_MASK_SHIFT
)paren
suffix:semicolon
multiline_comment|/* clear only the mask bit */
id|writel
c_func
(paren
id|low32
comma
id|addr
op_plus
id|IOSAPIC_WINDOW
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iosapic_lock
comma
id|flags
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|iosapic_set_affinity
id|iosapic_set_affinity
(paren
r_int
r_int
id|irq
comma
id|cpumask_t
id|mask
)paren
(brace
macro_line|#ifdef CONFIG_SMP
r_int
r_int
id|flags
suffix:semicolon
id|u32
id|high32
comma
id|low32
suffix:semicolon
r_int
id|dest
comma
id|rte_index
suffix:semicolon
r_char
op_star
id|addr
suffix:semicolon
r_int
id|redir
op_assign
(paren
id|irq
op_amp
id|IA64_IRQ_REDIRECTED
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
id|ia64_vector
id|vec
suffix:semicolon
id|irq
op_and_assign
(paren
op_complement
id|IA64_IRQ_REDIRECTED
)paren
suffix:semicolon
id|vec
op_assign
id|irq_to_vector
c_func
(paren
id|irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|cpus_empty
c_func
(paren
id|mask
)paren
op_logical_or
id|vec
op_ge
id|IA64_NUM_VECTORS
)paren
r_return
suffix:semicolon
id|dest
op_assign
id|cpu_physical_id
c_func
(paren
id|first_cpu
c_func
(paren
id|mask
)paren
)paren
suffix:semicolon
id|rte_index
op_assign
id|iosapic_intr_info
(braket
id|vec
)braket
dot
id|rte_index
suffix:semicolon
id|addr
op_assign
id|iosapic_intr_info
(braket
id|vec
)braket
dot
id|addr
suffix:semicolon
r_if
c_cond
(paren
id|rte_index
OL
l_int|0
)paren
r_return
suffix:semicolon
multiline_comment|/* not an IOSAPIC interrupt */
id|set_irq_affinity_info
c_func
(paren
id|irq
comma
id|dest
comma
id|redir
)paren
suffix:semicolon
multiline_comment|/* dest contains both id and eid */
id|high32
op_assign
id|dest
op_lshift
id|IOSAPIC_DEST_SHIFT
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iosapic_lock
comma
id|flags
)paren
suffix:semicolon
(brace
multiline_comment|/* get current delivery mode by reading the low32 */
id|writel
c_func
(paren
id|IOSAPIC_RTE_LOW
c_func
(paren
id|rte_index
)paren
comma
id|addr
op_plus
id|IOSAPIC_REG_SELECT
)paren
suffix:semicolon
id|low32
op_assign
id|readl
c_func
(paren
id|addr
op_plus
id|IOSAPIC_WINDOW
)paren
suffix:semicolon
id|low32
op_and_assign
op_complement
(paren
l_int|7
op_lshift
id|IOSAPIC_DELIVERY_SHIFT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|redir
)paren
multiline_comment|/* change delivery mode to lowest priority */
id|low32
op_or_assign
(paren
id|IOSAPIC_LOWEST_PRIORITY
op_lshift
id|IOSAPIC_DELIVERY_SHIFT
)paren
suffix:semicolon
r_else
multiline_comment|/* change delivery mode to fixed */
id|low32
op_or_assign
(paren
id|IOSAPIC_FIXED
op_lshift
id|IOSAPIC_DELIVERY_SHIFT
)paren
suffix:semicolon
id|writel
c_func
(paren
id|IOSAPIC_RTE_HIGH
c_func
(paren
id|rte_index
)paren
comma
id|addr
op_plus
id|IOSAPIC_REG_SELECT
)paren
suffix:semicolon
id|writel
c_func
(paren
id|high32
comma
id|addr
op_plus
id|IOSAPIC_WINDOW
)paren
suffix:semicolon
id|writel
c_func
(paren
id|IOSAPIC_RTE_LOW
c_func
(paren
id|rte_index
)paren
comma
id|addr
op_plus
id|IOSAPIC_REG_SELECT
)paren
suffix:semicolon
id|writel
c_func
(paren
id|low32
comma
id|addr
op_plus
id|IOSAPIC_WINDOW
)paren
suffix:semicolon
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iosapic_lock
comma
id|flags
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/*&n; * Handlers for level-triggered interrupts.&n; */
r_static
r_int
r_int
DECL|function|iosapic_startup_level_irq
id|iosapic_startup_level_irq
(paren
r_int
r_int
id|irq
)paren
(brace
id|unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|iosapic_end_level_irq
id|iosapic_end_level_irq
(paren
r_int
r_int
id|irq
)paren
(brace
id|ia64_vector
id|vec
op_assign
id|irq_to_vector
c_func
(paren
id|irq
)paren
suffix:semicolon
id|writel
c_func
(paren
id|vec
comma
id|iosapic_intr_info
(braket
id|vec
)braket
dot
id|addr
op_plus
id|IOSAPIC_EOI
)paren
suffix:semicolon
)brace
DECL|macro|iosapic_shutdown_level_irq
mdefine_line|#define iosapic_shutdown_level_irq&t;mask_irq
DECL|macro|iosapic_enable_level_irq
mdefine_line|#define iosapic_enable_level_irq&t;unmask_irq
DECL|macro|iosapic_disable_level_irq
mdefine_line|#define iosapic_disable_level_irq&t;mask_irq
DECL|macro|iosapic_ack_level_irq
mdefine_line|#define iosapic_ack_level_irq&t;&t;nop
DECL|variable|irq_type_iosapic_level
r_struct
id|hw_interrupt_type
id|irq_type_iosapic_level
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;IO-SAPIC-level&quot;
comma
dot
id|startup
op_assign
id|iosapic_startup_level_irq
comma
dot
id|shutdown
op_assign
id|iosapic_shutdown_level_irq
comma
dot
id|enable
op_assign
id|iosapic_enable_level_irq
comma
dot
id|disable
op_assign
id|iosapic_disable_level_irq
comma
dot
id|ack
op_assign
id|iosapic_ack_level_irq
comma
dot
id|end
op_assign
id|iosapic_end_level_irq
comma
dot
id|set_affinity
op_assign
id|iosapic_set_affinity
)brace
suffix:semicolon
multiline_comment|/*&n; * Handlers for edge-triggered interrupts.&n; */
r_static
r_int
r_int
DECL|function|iosapic_startup_edge_irq
id|iosapic_startup_edge_irq
(paren
r_int
r_int
id|irq
)paren
(brace
id|unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * IOSAPIC simply drops interrupts pended while the&n;&t; * corresponding pin was masked, so we can&squot;t know if an&n;&t; * interrupt is pending already.  Let&squot;s hope not...&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|iosapic_ack_edge_irq
id|iosapic_ack_edge_irq
(paren
r_int
r_int
id|irq
)paren
(brace
id|irq_desc_t
op_star
id|idesc
op_assign
id|irq_descp
c_func
(paren
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Once we have recorded IRQ_PENDING already, we can mask the&n;&t; * interrupt for real. This prevents IRQ storms from unhandled&n;&t; * devices.&n;&t; */
r_if
c_cond
(paren
(paren
id|idesc-&gt;status
op_amp
(paren
id|IRQ_PENDING
op_or
id|IRQ_DISABLED
)paren
)paren
op_eq
(paren
id|IRQ_PENDING
op_or
id|IRQ_DISABLED
)paren
)paren
id|mask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|macro|iosapic_enable_edge_irq
mdefine_line|#define iosapic_enable_edge_irq&t;&t;unmask_irq
DECL|macro|iosapic_disable_edge_irq
mdefine_line|#define iosapic_disable_edge_irq&t;nop
DECL|macro|iosapic_end_edge_irq
mdefine_line|#define iosapic_end_edge_irq&t;&t;nop
DECL|variable|irq_type_iosapic_edge
r_struct
id|hw_interrupt_type
id|irq_type_iosapic_edge
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;IO-SAPIC-edge&quot;
comma
dot
id|startup
op_assign
id|iosapic_startup_edge_irq
comma
dot
id|shutdown
op_assign
id|iosapic_disable_edge_irq
comma
dot
id|enable
op_assign
id|iosapic_enable_edge_irq
comma
dot
id|disable
op_assign
id|iosapic_disable_edge_irq
comma
dot
id|ack
op_assign
id|iosapic_ack_edge_irq
comma
dot
id|end
op_assign
id|iosapic_end_edge_irq
comma
dot
id|set_affinity
op_assign
id|iosapic_set_affinity
)brace
suffix:semicolon
r_int
r_int
DECL|function|iosapic_version
id|iosapic_version
(paren
r_char
op_star
id|addr
)paren
(brace
multiline_comment|/*&n;&t; * IOSAPIC Version Register return 32 bit structure like:&n;&t; * {&n;&t; *&t;unsigned int version   : 8;&n;&t; *&t;unsigned int reserved1 : 8;&n;&t; *&t;unsigned int max_redir : 8;&n;&t; *&t;unsigned int reserved2 : 8;&n;&t; * }&n;&t; */
id|writel
c_func
(paren
id|IOSAPIC_VERSION
comma
id|addr
op_plus
id|IOSAPIC_REG_SELECT
)paren
suffix:semicolon
r_return
id|readl
c_func
(paren
id|IOSAPIC_WINDOW
op_plus
id|addr
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * if the given vector is already owned by other,&n; *  assign a new vector for the other and make the vector available&n; */
r_static
r_void
id|__init
DECL|function|iosapic_reassign_vector
id|iosapic_reassign_vector
(paren
r_int
id|vector
)paren
(brace
r_int
id|new_vector
suffix:semicolon
r_if
c_cond
(paren
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|rte_index
op_ge
l_int|0
op_logical_or
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|addr
op_logical_or
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|gsi_base
op_logical_or
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|dmode
op_logical_or
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|polarity
op_logical_or
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|trigger
)paren
(brace
id|new_vector
op_assign
id|ia64_alloc_vector
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Reassigning vector %d to %d&bslash;n&quot;
comma
id|vector
comma
id|new_vector
)paren
suffix:semicolon
id|memcpy
c_func
(paren
op_amp
id|iosapic_intr_info
(braket
id|new_vector
)braket
comma
op_amp
id|iosapic_intr_info
(braket
id|vector
)braket
comma
r_sizeof
(paren
r_struct
id|iosapic_intr_info
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|iosapic_intr_info
(braket
id|vector
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|iosapic_intr_info
)paren
)paren
suffix:semicolon
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|rte_index
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
r_static
r_void
DECL|function|register_intr
id|register_intr
(paren
r_int
r_int
id|gsi
comma
r_int
id|vector
comma
r_int
r_char
id|delivery
comma
r_int
r_int
id|polarity
comma
r_int
r_int
id|trigger
)paren
(brace
id|irq_desc_t
op_star
id|idesc
suffix:semicolon
r_struct
id|hw_interrupt_type
op_star
id|irq_type
suffix:semicolon
r_int
id|rte_index
suffix:semicolon
r_int
id|index
suffix:semicolon
r_int
r_int
id|gsi_base
suffix:semicolon
r_char
op_star
id|iosapic_address
suffix:semicolon
id|index
op_assign
id|find_iosapic
c_func
(paren
id|gsi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|index
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: No IOSAPIC for GSI 0x%x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|gsi
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|iosapic_address
op_assign
id|iosapic_lists
(braket
id|index
)braket
dot
id|addr
suffix:semicolon
id|gsi_base
op_assign
id|iosapic_lists
(braket
id|index
)braket
dot
id|gsi_base
suffix:semicolon
id|rte_index
op_assign
id|gsi
op_minus
id|gsi_base
suffix:semicolon
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|rte_index
op_assign
id|rte_index
suffix:semicolon
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|polarity
op_assign
id|polarity
suffix:semicolon
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|dmode
op_assign
id|delivery
suffix:semicolon
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|addr
op_assign
id|iosapic_address
suffix:semicolon
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|gsi_base
op_assign
id|gsi_base
suffix:semicolon
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|trigger
op_assign
id|trigger
suffix:semicolon
r_if
c_cond
(paren
id|trigger
op_eq
id|IOSAPIC_EDGE
)paren
id|irq_type
op_assign
op_amp
id|irq_type_iosapic_edge
suffix:semicolon
r_else
id|irq_type
op_assign
op_amp
id|irq_type_iosapic_level
suffix:semicolon
id|idesc
op_assign
id|irq_descp
c_func
(paren
id|vector
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idesc-&gt;handler
op_ne
id|irq_type
)paren
(brace
r_if
c_cond
(paren
id|idesc-&gt;handler
op_ne
op_amp
id|no_irq_type
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: changing vector %d from %s to %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|vector
comma
id|idesc-&gt;handler
op_member_access_from_pointer
r_typename
comma
id|irq_type
op_member_access_from_pointer
r_typename
)paren
suffix:semicolon
id|idesc-&gt;handler
op_assign
id|irq_type
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * ACPI can describe IOSAPIC interrupts via static tables and namespace&n; * methods.  This provides an interface to register those interrupts and&n; * program the IOSAPIC RTE.&n; */
r_int
DECL|function|iosapic_register_intr
id|iosapic_register_intr
(paren
r_int
r_int
id|gsi
comma
r_int
r_int
id|polarity
comma
r_int
r_int
id|trigger
)paren
(brace
r_int
id|vector
suffix:semicolon
r_int
r_int
id|dest
op_assign
(paren
id|ia64_get_lid
c_func
(paren
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|vector
op_assign
id|gsi_to_vector
c_func
(paren
id|gsi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vector
OL
l_int|0
)paren
id|vector
op_assign
id|ia64_alloc_vector
c_func
(paren
)paren
suffix:semicolon
id|register_intr
c_func
(paren
id|gsi
comma
id|vector
comma
id|IOSAPIC_LOWEST_PRIORITY
comma
id|polarity
comma
id|trigger
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;GSI 0x%x(%s,%s) -&gt; CPU 0x%04x vector %d&bslash;n&quot;
comma
id|gsi
comma
(paren
id|polarity
op_eq
id|IOSAPIC_POL_HIGH
ques
c_cond
l_string|&quot;high&quot;
suffix:colon
l_string|&quot;low&quot;
)paren
comma
(paren
id|trigger
op_eq
id|IOSAPIC_EDGE
ques
c_cond
l_string|&quot;edge&quot;
suffix:colon
l_string|&quot;level&quot;
)paren
comma
id|dest
comma
id|vector
)paren
suffix:semicolon
multiline_comment|/* program the IOSAPIC routing table */
id|set_rte
c_func
(paren
id|vector
comma
id|dest
)paren
suffix:semicolon
r_return
id|vector
suffix:semicolon
)brace
multiline_comment|/*&n; * ACPI calls this when it finds an entry for a platform interrupt.&n; * Note that the irq_base and IOSAPIC address must be set in iosapic_init().&n; */
r_int
id|__init
DECL|function|iosapic_register_platform_intr
id|iosapic_register_platform_intr
(paren
id|u32
id|int_type
comma
r_int
r_int
id|gsi
comma
r_int
id|iosapic_vector
comma
id|u16
id|eid
comma
id|u16
id|id
comma
r_int
r_int
id|polarity
comma
r_int
r_int
id|trigger
)paren
(brace
r_int
r_char
id|delivery
suffix:semicolon
r_int
id|vector
suffix:semicolon
r_int
r_int
id|dest
op_assign
(paren
(paren
id|id
op_lshift
l_int|8
)paren
op_or
id|eid
)paren
op_amp
l_int|0xffff
suffix:semicolon
r_switch
c_cond
(paren
id|int_type
)paren
(brace
r_case
id|ACPI_INTERRUPT_PMI
suffix:colon
id|vector
op_assign
id|iosapic_vector
suffix:semicolon
multiline_comment|/*&n;&t;&t; * since PMI vector is alloc&squot;d by FW(ACPI) not by kernel,&n;&t;&t; * we need to make sure the vector is available&n;&t;&t; */
id|iosapic_reassign_vector
c_func
(paren
id|vector
)paren
suffix:semicolon
id|delivery
op_assign
id|IOSAPIC_PMI
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_INTERRUPT_INIT
suffix:colon
id|vector
op_assign
id|ia64_alloc_vector
c_func
(paren
)paren
suffix:semicolon
id|delivery
op_assign
id|IOSAPIC_INIT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_INTERRUPT_CPEI
suffix:colon
id|vector
op_assign
id|IA64_CPE_VECTOR
suffix:semicolon
id|delivery
op_assign
id|IOSAPIC_LOWEST_PRIORITY
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;iosapic_register_platform_irq(): invalid int type&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|register_intr
c_func
(paren
id|gsi
comma
id|vector
comma
id|delivery
comma
id|polarity
comma
id|trigger
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PLATFORM int 0x%x: GSI 0x%x(%s,%s) -&gt; CPU 0x%04x vector %d&bslash;n&quot;
comma
id|int_type
comma
id|gsi
comma
(paren
id|polarity
op_eq
id|IOSAPIC_POL_HIGH
ques
c_cond
l_string|&quot;high&quot;
suffix:colon
l_string|&quot;low&quot;
)paren
comma
(paren
id|trigger
op_eq
id|IOSAPIC_EDGE
ques
c_cond
l_string|&quot;edge&quot;
suffix:colon
l_string|&quot;level&quot;
)paren
comma
id|dest
comma
id|vector
)paren
suffix:semicolon
multiline_comment|/* program the IOSAPIC routing table */
id|set_rte
c_func
(paren
id|vector
comma
id|dest
)paren
suffix:semicolon
r_return
id|vector
suffix:semicolon
)brace
multiline_comment|/*&n; * ACPI calls this when it finds an entry for a legacy ISA IRQ override.&n; * Note that the gsi_base and IOSAPIC address must be set in iosapic_init().&n; */
r_void
id|__init
DECL|function|iosapic_override_isa_irq
id|iosapic_override_isa_irq
(paren
r_int
r_int
id|isa_irq
comma
r_int
r_int
id|gsi
comma
r_int
r_int
id|polarity
comma
r_int
r_int
id|trigger
)paren
(brace
r_int
id|vector
suffix:semicolon
r_int
r_int
id|dest
op_assign
(paren
id|ia64_get_lid
c_func
(paren
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
id|vector
op_assign
id|isa_irq_to_vector
c_func
(paren
id|isa_irq
)paren
suffix:semicolon
id|register_intr
c_func
(paren
id|gsi
comma
id|vector
comma
id|IOSAPIC_LOWEST_PRIORITY
comma
id|polarity
comma
id|trigger
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;ISA: IRQ %u -&gt; GSI 0x%x (%s,%s) -&gt; CPU 0x%04x vector %d&bslash;n&quot;
comma
id|isa_irq
comma
id|gsi
comma
id|polarity
op_eq
id|IOSAPIC_POL_HIGH
ques
c_cond
l_string|&quot;high&quot;
suffix:colon
l_string|&quot;low&quot;
comma
id|trigger
op_eq
id|IOSAPIC_EDGE
ques
c_cond
l_string|&quot;edge&quot;
suffix:colon
l_string|&quot;level&quot;
comma
id|dest
comma
id|vector
)paren
suffix:semicolon
multiline_comment|/* program the IOSAPIC routing table */
id|set_rte
c_func
(paren
id|vector
comma
id|dest
)paren
suffix:semicolon
)brace
r_void
id|__init
DECL|function|iosapic_system_init
id|iosapic_system_init
(paren
r_int
id|system_pcat_compat
)paren
(brace
r_int
id|vector
suffix:semicolon
r_for
c_loop
(paren
id|vector
op_assign
l_int|0
suffix:semicolon
id|vector
OL
id|IA64_NUM_VECTORS
suffix:semicolon
op_increment
id|vector
)paren
id|iosapic_intr_info
(braket
id|vector
)braket
dot
id|rte_index
op_assign
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* mark as unused */
id|pcat_compat
op_assign
id|system_pcat_compat
suffix:semicolon
r_if
c_cond
(paren
id|pcat_compat
)paren
(brace
multiline_comment|/*&n;&t;&t; * Disable the compatibility mode interrupts (8259 style), needs IN/OUT support&n;&t;&t; * enabled.&n;&t;&t; */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;%s: Disabling PC-AT compatible 8259 interrupts&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
l_int|0xA1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
l_int|0x21
)paren
suffix:semicolon
)brace
)brace
r_void
id|__init
DECL|function|iosapic_init
id|iosapic_init
(paren
r_int
r_int
id|phys_addr
comma
r_int
r_int
id|gsi_base
)paren
(brace
r_int
id|num_rte
suffix:semicolon
r_int
r_int
id|isa_irq
comma
id|ver
suffix:semicolon
r_char
op_star
id|addr
suffix:semicolon
id|addr
op_assign
id|ioremap
c_func
(paren
id|phys_addr
comma
l_int|0
)paren
suffix:semicolon
id|ver
op_assign
id|iosapic_version
c_func
(paren
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The MAX_REDIR register holds the highest input pin&n;&t; * number (starting from 0).&n;&t; * We add 1 so that we can use it for number of pins (= RTEs)&n;&t; */
id|num_rte
op_assign
(paren
(paren
id|ver
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
)paren
op_plus
l_int|1
suffix:semicolon
id|iosapic_lists
(braket
id|num_iosapic
)braket
dot
id|addr
op_assign
id|addr
suffix:semicolon
id|iosapic_lists
(braket
id|num_iosapic
)braket
dot
id|gsi_base
op_assign
id|gsi_base
suffix:semicolon
id|iosapic_lists
(braket
id|num_iosapic
)braket
dot
id|num_rte
op_assign
id|num_rte
suffix:semicolon
id|num_iosapic
op_increment
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;  IOSAPIC v%x.%x, address 0x%lx, GSIs 0x%x-0x%x&bslash;n&quot;
comma
(paren
id|ver
op_amp
l_int|0xf0
)paren
op_rshift
l_int|4
comma
(paren
id|ver
op_amp
l_int|0x0f
)paren
comma
id|phys_addr
comma
id|gsi_base
comma
id|gsi_base
op_plus
id|num_rte
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|gsi_base
op_eq
l_int|0
)paren
op_logical_and
id|pcat_compat
)paren
(brace
multiline_comment|/*&n;&t;&t; * Map the legacy ISA devices into the IOSAPIC data.  Some of these may&n;&t;&t; * get reprogrammed later on with data from the ACPI Interrupt Source&n;&t;&t; * Override table.&n;&t;&t; */
r_for
c_loop
(paren
id|isa_irq
op_assign
l_int|0
suffix:semicolon
id|isa_irq
OL
l_int|16
suffix:semicolon
op_increment
id|isa_irq
)paren
id|iosapic_override_isa_irq
c_func
(paren
id|isa_irq
comma
id|isa_irq
comma
id|IOSAPIC_POL_HIGH
comma
id|IOSAPIC_EDGE
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|iosapic_enable_intr
id|iosapic_enable_intr
(paren
r_int
r_int
id|vector
)paren
(brace
r_int
r_int
id|dest
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
multiline_comment|/*&n;&t; * For platforms that do not support interrupt redirect via the XTP interface, we&n;&t; * can round-robin the PCI device interrupts to the processors&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|smp_int_redirect
op_amp
id|SMP_IRQ_REDIRECTION
)paren
)paren
(brace
r_static
r_int
id|cpu_index
op_assign
op_minus
l_int|1
suffix:semicolon
r_do
r_if
c_cond
(paren
op_increment
id|cpu_index
op_ge
id|NR_CPUS
)paren
id|cpu_index
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|cpu_online
c_func
(paren
id|cpu_index
)paren
)paren
suffix:semicolon
id|dest
op_assign
id|cpu_physical_id
c_func
(paren
id|cpu_index
)paren
op_amp
l_int|0xffff
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Direct the interrupt vector to the current cpu, platform redirection&n;&t;&t; * will distribute them.&n;&t;&t; */
id|dest
op_assign
(paren
id|ia64_get_lid
c_func
(paren
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* direct the interrupt vector to the running cpu id */
id|dest
op_assign
(paren
id|ia64_get_lid
c_func
(paren
)paren
op_rshift
l_int|16
)paren
op_amp
l_int|0xffff
suffix:semicolon
macro_line|#endif
id|set_rte
c_func
(paren
id|vector
comma
id|dest
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;IOSAPIC: vector %d -&gt; CPU 0x%04x, enabled&bslash;n&quot;
comma
id|vector
comma
id|dest
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_ACPI_PCI
r_void
id|__init
DECL|function|iosapic_parse_prt
id|iosapic_parse_prt
(paren
r_void
)paren
(brace
r_struct
id|acpi_prt_entry
op_star
id|entry
suffix:semicolon
r_struct
id|list_head
op_star
id|node
suffix:semicolon
r_int
r_int
id|gsi
suffix:semicolon
r_int
id|vector
suffix:semicolon
r_char
id|pci_id
(braket
l_int|16
)braket
suffix:semicolon
r_struct
id|hw_interrupt_type
op_star
id|irq_type
op_assign
op_amp
id|irq_type_iosapic_level
suffix:semicolon
id|irq_desc_t
op_star
id|idesc
suffix:semicolon
id|list_for_each
c_func
(paren
id|node
comma
op_amp
id|acpi_prt.entries
)paren
(brace
id|entry
op_assign
id|list_entry
c_func
(paren
id|node
comma
r_struct
id|acpi_prt_entry
comma
id|node
)paren
suffix:semicolon
multiline_comment|/* We&squot;re only interested in static (non-link) entries.  */
r_if
c_cond
(paren
id|entry-&gt;link.handle
)paren
r_continue
suffix:semicolon
id|gsi
op_assign
id|entry-&gt;link.index
suffix:semicolon
id|vector
op_assign
id|gsi_to_vector
c_func
(paren
id|gsi
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vector
OL
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|find_iosapic
c_func
(paren
id|gsi
)paren
OL
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* allocate a vector for this interrupt line */
r_if
c_cond
(paren
id|pcat_compat
op_logical_and
(paren
id|gsi
OL
l_int|16
)paren
)paren
id|vector
op_assign
id|isa_irq_to_vector
c_func
(paren
id|gsi
)paren
suffix:semicolon
r_else
multiline_comment|/* new GSI; allocate a vector for it */
id|vector
op_assign
id|ia64_alloc_vector
c_func
(paren
)paren
suffix:semicolon
id|register_intr
c_func
(paren
id|gsi
comma
id|vector
comma
id|IOSAPIC_LOWEST_PRIORITY
comma
id|IOSAPIC_POL_LOW
comma
id|IOSAPIC_LEVEL
)paren
suffix:semicolon
)brace
id|entry-&gt;irq
op_assign
id|vector
suffix:semicolon
id|snprintf
c_func
(paren
id|pci_id
comma
r_sizeof
(paren
id|pci_id
)paren
comma
l_string|&quot;%02x:%02x:%02x[%c]&quot;
comma
id|entry-&gt;id.segment
comma
id|entry-&gt;id.bus
comma
id|entry-&gt;id.device
comma
l_char|&squot;A&squot;
op_plus
id|entry-&gt;pin
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If vector was previously initialized to a different&n;&t;&t; * handler, re-initialize.&n;&t;&t; */
id|idesc
op_assign
id|irq_descp
c_func
(paren
id|vector
)paren
suffix:semicolon
r_if
c_cond
(paren
id|idesc-&gt;handler
op_ne
id|irq_type
)paren
id|register_intr
c_func
(paren
id|gsi
comma
id|vector
comma
id|IOSAPIC_LOWEST_PRIORITY
comma
id|IOSAPIC_POL_LOW
comma
id|IOSAPIC_LEVEL
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif /* CONFIG_ACPI */
eof
