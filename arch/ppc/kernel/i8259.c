multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/signal.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/i8259.h&gt;
DECL|variable|pci_intack
r_static
r_volatile
r_int
r_char
op_star
id|pci_intack
suffix:semicolon
multiline_comment|/* RO, gives us the irq vector */
DECL|variable|cached_8259
r_int
r_char
id|cached_8259
(braket
l_int|2
)braket
op_assign
(brace
l_int|0xff
comma
l_int|0xff
)brace
suffix:semicolon
DECL|macro|cached_A1
mdefine_line|#define cached_A1 (cached_8259[0])
DECL|macro|cached_21
mdefine_line|#define cached_21 (cached_8259[1])
DECL|variable|i8259_lock
r_static
id|spinlock_t
id|i8259_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|i8259_pic_irq_offset
r_int
id|i8259_pic_irq_offset
suffix:semicolon
multiline_comment|/*&n; * Acknowledge the IRQ using either the PCI host bridge&squot;s interrupt&n; * acknowledge feature or poll.  How i8259_init() is called determines&n; * which is called.  It should be noted that polling is broken on some&n; * IBM and Motorola PReP boxes so we must use the int-ack feature on them.&n; */
r_int
DECL|function|i8259_irq
id|i8259_irq
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
id|spin_lock
c_func
(paren
op_amp
id|i8259_lock
)paren
suffix:semicolon
multiline_comment|/* Either int-ack or poll for the IRQ */
r_if
c_cond
(paren
id|pci_intack
)paren
id|irq
op_assign
op_star
id|pci_intack
suffix:semicolon
r_else
(brace
multiline_comment|/* Perform an interrupt acknowledge cycle on controller 1. */
id|outb
c_func
(paren
l_int|0x0C
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* prepare for poll */
id|irq
op_assign
id|inb
c_func
(paren
l_int|0x20
)paren
op_amp
l_int|7
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
l_int|2
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Interrupt is cascaded so perform interrupt&n;&t;&t;&t; * acknowledge on controller 2.&n;&t;&t;&t; */
id|outb
c_func
(paren
l_int|0x0C
comma
l_int|0xA0
)paren
suffix:semicolon
multiline_comment|/* prepare for poll */
id|irq
op_assign
(paren
id|inb
c_func
(paren
l_int|0xA0
)paren
op_amp
l_int|7
)paren
op_plus
l_int|8
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|irq
op_eq
l_int|7
)paren
(brace
multiline_comment|/*&n;&t;&t; * This may be a spurious interrupt.&n;&t;&t; *&n;&t;&t; * Read the interrupt status register (ISR). If the most&n;&t;&t; * significant bit is not set then there is no valid&n;&t;&t; * interrupt.&n;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|pci_intack
)paren
id|outb
c_func
(paren
l_int|0x0B
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* ISR register */
r_if
c_cond
(paren
op_complement
id|inb
c_func
(paren
l_int|0x20
)paren
op_amp
l_int|0x80
)paren
(brace
id|irq
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
)brace
id|spin_unlock
c_func
(paren
op_amp
id|i8259_lock
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
DECL|function|i8259_mask_and_ack_irq
r_static
r_void
id|i8259_mask_and_ack_irq
c_func
(paren
r_int
r_int
id|irq_nr
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
id|i8259_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_nr
op_ge
id|i8259_pic_irq_offset
)paren
id|irq_nr
op_sub_assign
id|i8259_pic_irq_offset
suffix:semicolon
r_if
c_cond
(paren
id|irq_nr
OG
l_int|7
)paren
(brace
id|cached_A1
op_or_assign
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
l_int|8
)paren
suffix:semicolon
id|inb
c_func
(paren
l_int|0xA1
)paren
suffix:semicolon
multiline_comment|/* DUMMY */
id|outb
c_func
(paren
id|cached_A1
comma
l_int|0xA1
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x20
comma
l_int|0xA0
)paren
suffix:semicolon
multiline_comment|/* Non-specific EOI */
id|outb
c_func
(paren
l_int|0x20
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* Non-specific EOI to cascade */
)brace
r_else
(brace
id|cached_21
op_or_assign
l_int|1
op_lshift
id|irq_nr
suffix:semicolon
id|inb
c_func
(paren
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* DUMMY */
id|outb
c_func
(paren
id|cached_21
comma
l_int|0x21
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x20
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* Non-specific EOI */
)brace
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8259_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|i8259_set_irq_mask
r_static
r_void
id|i8259_set_irq_mask
c_func
(paren
r_int
id|irq_nr
)paren
(brace
id|outb
c_func
(paren
id|cached_A1
comma
l_int|0xA1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|cached_21
comma
l_int|0x21
)paren
suffix:semicolon
)brace
DECL|function|i8259_mask_irq
r_static
r_void
id|i8259_mask_irq
c_func
(paren
r_int
r_int
id|irq_nr
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
id|i8259_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_nr
op_ge
id|i8259_pic_irq_offset
)paren
id|irq_nr
op_sub_assign
id|i8259_pic_irq_offset
suffix:semicolon
r_if
c_cond
(paren
id|irq_nr
OL
l_int|8
)paren
id|cached_21
op_or_assign
l_int|1
op_lshift
id|irq_nr
suffix:semicolon
r_else
id|cached_A1
op_or_assign
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
l_int|8
)paren
suffix:semicolon
id|i8259_set_irq_mask
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8259_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|i8259_unmask_irq
r_static
r_void
id|i8259_unmask_irq
c_func
(paren
r_int
r_int
id|irq_nr
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
id|i8259_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_nr
op_ge
id|i8259_pic_irq_offset
)paren
id|irq_nr
op_sub_assign
id|i8259_pic_irq_offset
suffix:semicolon
r_if
c_cond
(paren
id|irq_nr
OL
l_int|8
)paren
id|cached_21
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|irq_nr
)paren
suffix:semicolon
r_else
id|cached_A1
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|irq_nr
op_minus
l_int|8
)paren
)paren
suffix:semicolon
id|i8259_set_irq_mask
c_func
(paren
id|irq_nr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8259_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|i8259_end_irq
r_static
r_void
id|i8259_end_irq
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
id|i8259_unmask_irq
c_func
(paren
id|irq
)paren
suffix:semicolon
)brace
DECL|variable|i8259_pic
r_struct
id|hw_interrupt_type
id|i8259_pic
op_assign
(brace
l_string|&quot; i8259    &quot;
comma
l_int|NULL
comma
l_int|NULL
comma
id|i8259_unmask_irq
comma
id|i8259_mask_irq
comma
id|i8259_mask_and_ack_irq
comma
id|i8259_end_irq
comma
l_int|NULL
)brace
suffix:semicolon
DECL|variable|pic1_iores
r_static
r_struct
id|resource
id|pic1_iores
op_assign
(brace
l_string|&quot;8259 (master)&quot;
comma
l_int|0x20
comma
l_int|0x21
comma
id|IORESOURCE_BUSY
)brace
suffix:semicolon
DECL|variable|pic2_iores
r_static
r_struct
id|resource
id|pic2_iores
op_assign
(brace
l_string|&quot;8259 (slave)&quot;
comma
l_int|0xa0
comma
l_int|0xa1
comma
id|IORESOURCE_BUSY
)brace
suffix:semicolon
DECL|variable|pic_edgectrl_iores
r_static
r_struct
id|resource
id|pic_edgectrl_iores
op_assign
(brace
l_string|&quot;8259 edge control&quot;
comma
l_int|0x4d0
comma
l_int|0x4d1
comma
id|IORESOURCE_BUSY
)brace
suffix:semicolon
multiline_comment|/*&n; * i8259_init()&n; * intack_addr - PCI interrupt acknowledge (real) address which will return&n; *               the active irq from the 8259&n; */
r_void
id|__init
DECL|function|i8259_init
id|i8259_init
c_func
(paren
r_int
id|intack_addr
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
id|i8259_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* init master interrupt controller */
id|outb
c_func
(paren
l_int|0x11
comma
l_int|0x20
)paren
suffix:semicolon
multiline_comment|/* Start init sequence */
id|outb
c_func
(paren
l_int|0x00
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* Vector base */
id|outb
c_func
(paren
l_int|0x04
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* edge tiggered, Cascade (slave) on IRQ2 */
id|outb
c_func
(paren
l_int|0x01
comma
l_int|0x21
)paren
suffix:semicolon
multiline_comment|/* Select 8086 mode */
multiline_comment|/* init slave interrupt controller */
id|outb
c_func
(paren
l_int|0x11
comma
l_int|0xA0
)paren
suffix:semicolon
multiline_comment|/* Start init sequence */
id|outb
c_func
(paren
l_int|0x08
comma
l_int|0xA1
)paren
suffix:semicolon
multiline_comment|/* Vector base */
id|outb
c_func
(paren
l_int|0x02
comma
l_int|0xA1
)paren
suffix:semicolon
multiline_comment|/* edge triggered, Cascade (slave) on IRQ2 */
id|outb
c_func
(paren
l_int|0x01
comma
l_int|0xA1
)paren
suffix:semicolon
multiline_comment|/* Select 8086 mode */
multiline_comment|/* always read ISR */
id|outb
c_func
(paren
l_int|0x0B
comma
l_int|0x20
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x0B
comma
l_int|0xA0
)paren
suffix:semicolon
multiline_comment|/* Mask all interrupts */
id|outb
c_func
(paren
id|cached_A1
comma
l_int|0xA1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|cached_21
comma
l_int|0x21
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|i8259_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/* reserve our resources */
id|request_irq
c_func
(paren
id|i8259_pic_irq_offset
op_plus
l_int|2
comma
id|no_action
comma
id|SA_INTERRUPT
comma
l_string|&quot;82c59 secondary cascade&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|pic1_iores
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|pic2_iores
)paren
suffix:semicolon
id|request_resource
c_func
(paren
op_amp
id|ioport_resource
comma
op_amp
id|pic_edgectrl_iores
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intack_addr
op_ne
l_int|0
)paren
id|pci_intack
op_assign
id|ioremap
c_func
(paren
id|intack_addr
comma
l_int|1
)paren
suffix:semicolon
)brace
eof
