multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1992 Linus Torvalds&n; * Copyright (C) 1994 - 2000 Ralf Baechle&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/sni.h&gt;
DECL|variable|pciasic_lock
id|DEFINE_SPINLOCK
c_func
(paren
id|pciasic_lock
)paren
suffix:semicolon
r_extern
id|asmlinkage
r_void
id|sni_rm200_pci_handle_int
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|enable_pciasic_irq
r_static
r_void
id|enable_pciasic_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_minus
id|PCIMT_IRQ_INT2
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pciasic_lock
comma
id|flags
)paren
suffix:semicolon
op_star
(paren
r_volatile
id|u8
op_star
)paren
id|PCIMT_IRQSEL
op_or_assign
id|mask
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pciasic_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|startup_pciasic_irq
r_static
r_int
r_int
id|startup_pciasic_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|enable_pciasic_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* never anything pending */
)brace
DECL|macro|shutdown_pciasic_irq
mdefine_line|#define shutdown_pciasic_irq&t;disable_pciasic_irq
DECL|function|disable_pciasic_irq
r_void
id|disable_pciasic_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|mask
op_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq
op_minus
id|PCIMT_IRQ_INT2
)paren
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pciasic_lock
comma
id|flags
)paren
suffix:semicolon
op_star
(paren
r_volatile
id|u8
op_star
)paren
id|PCIMT_IRQSEL
op_and_assign
id|mask
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pciasic_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|macro|mask_and_ack_pciasic_irq
mdefine_line|#define mask_and_ack_pciasic_irq disable_pciasic_irq
DECL|function|end_pciasic_irq
r_static
r_void
id|end_pciasic_irq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_desc
(braket
id|irq
)braket
dot
id|status
op_amp
(paren
id|IRQ_DISABLED
op_or
id|IRQ_INPROGRESS
)paren
)paren
)paren
id|enable_pciasic_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|pciasic_irq_type
r_static
r_struct
id|hw_interrupt_type
id|pciasic_irq_type
op_assign
(brace
l_string|&quot;ASIC-PCI&quot;
comma
id|startup_pciasic_irq
comma
id|shutdown_pciasic_irq
comma
id|enable_pciasic_irq
comma
id|disable_pciasic_irq
comma
id|mask_and_ack_pciasic_irq
comma
id|end_pciasic_irq
comma
l_int|NULL
)brace
suffix:semicolon
multiline_comment|/*&n; * hwint0 should deal with MP agent, ASIC PCI, EISA NMI and debug&n; * button interrupts.  Later ...&n; */
DECL|function|pciasic_hwint0
r_void
id|pciasic_hwint0
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;Received int0 but no handler yet ...&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* This interrupt was used for the com1 console on the first prototypes.  */
DECL|function|pciasic_hwint2
r_void
id|pciasic_hwint2
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
multiline_comment|/* I think this shouldn&squot;t happen on production machines.  */
id|panic
c_func
(paren
l_string|&quot;hwint2 and no handler yet&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* hwint5 is the r4k count / compare interrupt  */
DECL|function|pciasic_hwint5
r_void
id|pciasic_hwint5
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|panic
c_func
(paren
l_string|&quot;hwint5 and no handler yet&quot;
)paren
suffix:semicolon
)brace
DECL|function|ls1bit8
r_static
r_int
r_int
id|ls1bit8
c_func
(paren
r_int
r_int
id|x
)paren
(brace
r_int
id|b
op_assign
l_int|7
comma
id|s
suffix:semicolon
id|s
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x
op_amp
l_int|0x0f
)paren
op_eq
l_int|0
)paren
id|s
op_assign
l_int|0
suffix:semicolon
id|b
op_sub_assign
id|s
suffix:semicolon
id|x
op_lshift_assign
id|s
suffix:semicolon
id|s
op_assign
l_int|2
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x
op_amp
l_int|0x30
)paren
op_eq
l_int|0
)paren
id|s
op_assign
l_int|0
suffix:semicolon
id|b
op_sub_assign
id|s
suffix:semicolon
id|x
op_lshift_assign
id|s
suffix:semicolon
id|s
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
(paren
id|x
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
id|s
op_assign
l_int|0
suffix:semicolon
id|b
op_sub_assign
id|s
suffix:semicolon
r_return
id|b
suffix:semicolon
)brace
multiline_comment|/*&n; * hwint 1 deals with EISA and SCSI interrupts,&n; * &n; * The EISA_INT bit in CSITPEND is high active, all others are low active.&n; */
DECL|function|pciasic_hwint1
r_void
id|pciasic_hwint1
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u8
id|pend
op_assign
op_star
(paren
r_volatile
r_char
op_star
)paren
id|PCIMT_CSITPEND
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|pend
op_amp
id|IT_EISA
)paren
(brace
r_int
id|irq
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Note: ASIC PCI&squot;s builtin interrupt achknowledge feature is&n;&t;&t; * broken.  Using it may result in loss of some or all i8259&n;&t;&t; * interupts, so don&squot;t use PCIMT_INT_ACKNOWLEDGE ...&n;&t;&t; */
id|irq
op_assign
id|i8259_irq
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|irq
OL
l_int|0
)paren
)paren
r_return
suffix:semicolon
id|do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|pend
op_amp
id|IT_SCSI
)paren
)paren
(brace
id|flags
op_assign
id|read_c0_status
c_func
(paren
)paren
suffix:semicolon
id|clear_c0_status
c_func
(paren
id|ST0_IM
)paren
suffix:semicolon
id|do_IRQ
c_func
(paren
id|PCIMT_IRQ_SCSI
comma
id|regs
)paren
suffix:semicolon
id|write_c0_status
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * hwint 3 should deal with the PCI A - D interrupts,&n; */
DECL|function|pciasic_hwint3
r_void
id|pciasic_hwint3
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|u8
id|pend
op_assign
op_star
(paren
r_volatile
r_char
op_star
)paren
id|PCIMT_CSITPEND
suffix:semicolon
r_int
id|irq
suffix:semicolon
id|pend
op_and_assign
(paren
id|IT_INTA
op_or
id|IT_INTB
op_or
id|IT_INTC
op_or
id|IT_INTD
)paren
suffix:semicolon
id|clear_c0_status
c_func
(paren
id|IE_IRQ3
)paren
suffix:semicolon
id|irq
op_assign
id|PCIMT_IRQ_INT2
op_plus
id|ls1bit8
c_func
(paren
id|pend
)paren
suffix:semicolon
id|do_IRQ
c_func
(paren
id|irq
comma
id|regs
)paren
suffix:semicolon
id|set_c0_status
c_func
(paren
id|IE_IRQ3
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * hwint 4 is used for only the onboard PCnet 32.&n; */
DECL|function|pciasic_hwint4
r_void
id|pciasic_hwint4
c_func
(paren
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
id|clear_c0_status
c_func
(paren
id|IE_IRQ4
)paren
suffix:semicolon
id|do_IRQ
c_func
(paren
id|PCIMT_IRQ_ETHERNET
comma
id|regs
)paren
suffix:semicolon
id|set_c0_status
c_func
(paren
id|IE_IRQ4
)paren
suffix:semicolon
)brace
DECL|function|init_pciasic
r_void
id|__init
id|init_pciasic
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pciasic_lock
comma
id|flags
)paren
suffix:semicolon
op_star
(paren
r_volatile
id|u8
op_star
)paren
id|PCIMT_IRQSEL
op_assign
id|IT_EISA
op_or
id|IT_INTA
op_or
id|IT_INTB
op_or
id|IT_INTC
op_or
id|IT_INTD
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pciasic_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * On systems with i8259-style interrupt controllers we assume for&n; * driver compatibility reasons interrupts 0 - 15 to be the i8295&n; * interrupts even if the hardware uses a different interrupt numbering.&n; */
DECL|function|arch_init_irq
r_void
id|__init
id|arch_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
id|set_except_vector
c_func
(paren
l_int|0
comma
id|sni_rm200_pci_handle_int
)paren
suffix:semicolon
id|init_i8259_irqs
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Integrated i8259  */
id|init_pciasic
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Actually we&squot;ve got more interrupts to handle ...  */
r_for
c_loop
(paren
id|i
op_assign
id|PCIMT_IRQ_INT2
suffix:semicolon
id|i
op_le
id|PCIMT_IRQ_ETHERNET
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
id|status
op_assign
id|IRQ_DISABLED
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|action
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|depth
op_assign
l_int|1
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|handler
op_assign
op_amp
id|pciasic_irq_type
suffix:semicolon
)brace
id|change_c0_status
c_func
(paren
id|ST0_IM
comma
id|IE_IRQ1
op_or
id|IE_IRQ2
op_or
id|IE_IRQ3
op_or
id|IE_IRQ4
)paren
suffix:semicolon
)brace
eof
