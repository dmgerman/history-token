macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/hardware/iomd.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|function|iomd_ack_irq_a
r_static
r_void
id|iomd_ack_irq_a
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKA
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_IRQMASKA
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|mask
comma
id|IOMD_IRQCLRA
)paren
suffix:semicolon
)brace
DECL|function|iomd_mask_irq_a
r_static
r_void
id|iomd_mask_irq_a
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKA
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_IRQMASKA
)paren
suffix:semicolon
)brace
DECL|function|iomd_unmask_irq_a
r_static
r_void
id|iomd_unmask_irq_a
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
id|irq
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKA
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOMD_IRQMASKA
)paren
suffix:semicolon
)brace
DECL|variable|iomd_a_chip
r_static
r_struct
id|irqchip
id|iomd_a_chip
op_assign
(brace
dot
id|ack
op_assign
id|iomd_ack_irq_a
comma
dot
id|mask
op_assign
id|iomd_mask_irq_a
comma
dot
id|unmask
op_assign
id|iomd_unmask_irq_a
comma
)brace
suffix:semicolon
DECL|function|iomd_mask_irq_b
r_static
r_void
id|iomd_mask_irq_b
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKB
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_IRQMASKB
)paren
suffix:semicolon
)brace
DECL|function|iomd_unmask_irq_b
r_static
r_void
id|iomd_unmask_irq_b
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_IRQMASKB
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOMD_IRQMASKB
)paren
suffix:semicolon
)brace
DECL|variable|iomd_b_chip
r_static
r_struct
id|irqchip
id|iomd_b_chip
op_assign
(brace
dot
id|ack
op_assign
id|iomd_mask_irq_b
comma
dot
id|mask
op_assign
id|iomd_mask_irq_b
comma
dot
id|unmask
op_assign
id|iomd_unmask_irq_b
comma
)brace
suffix:semicolon
DECL|function|iomd_mask_irq_dma
r_static
r_void
id|iomd_mask_irq_dma
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_DMAMASK
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_DMAMASK
)paren
suffix:semicolon
)brace
DECL|function|iomd_unmask_irq_dma
r_static
r_void
id|iomd_unmask_irq_dma
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_DMAMASK
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOMD_DMAMASK
)paren
suffix:semicolon
)brace
DECL|variable|iomd_dma_chip
r_static
r_struct
id|irqchip
id|iomd_dma_chip
op_assign
(brace
dot
id|ack
op_assign
id|iomd_mask_irq_dma
comma
dot
id|mask
op_assign
id|iomd_mask_irq_dma
comma
dot
id|unmask
op_assign
id|iomd_unmask_irq_dma
comma
)brace
suffix:semicolon
DECL|function|iomd_mask_irq_fiq
r_static
r_void
id|iomd_mask_irq_fiq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_FIQMASK
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_amp
op_complement
id|mask
comma
id|IOMD_FIQMASK
)paren
suffix:semicolon
)brace
DECL|function|iomd_unmask_irq_fiq
r_static
r_void
id|iomd_unmask_irq_fiq
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_int
r_int
id|val
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
(paren
id|irq
op_amp
l_int|7
)paren
suffix:semicolon
id|val
op_assign
id|iomd_readb
c_func
(paren
id|IOMD_FIQMASK
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
id|val
op_or
id|mask
comma
id|IOMD_FIQMASK
)paren
suffix:semicolon
)brace
DECL|variable|iomd_fiq_chip
r_static
r_struct
id|irqchip
id|iomd_fiq_chip
op_assign
(brace
dot
id|ack
op_assign
id|iomd_mask_irq_fiq
comma
dot
id|mask
op_assign
id|iomd_mask_irq_fiq
comma
dot
id|unmask
op_assign
id|iomd_unmask_irq_fiq
comma
)brace
suffix:semicolon
DECL|function|rpc_init_irq
r_void
id|__init
id|rpc_init_irq
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|irq
comma
id|flags
suffix:semicolon
id|iomd_writeb
c_func
(paren
l_int|0
comma
id|IOMD_IRQMASKA
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
l_int|0
comma
id|IOMD_IRQMASKB
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
l_int|0
comma
id|IOMD_FIQMASK
)paren
suffix:semicolon
id|iomd_writeb
c_func
(paren
l_int|0
comma
id|IOMD_DMAMASK
)paren
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
id|irq
op_increment
)paren
(brace
id|flags
op_assign
id|IRQF_VALID
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_le
l_int|6
op_logical_or
(paren
id|irq
op_ge
l_int|9
op_logical_and
id|irq
op_le
l_int|15
)paren
)paren
id|flags
op_or_assign
id|IRQF_PROBE
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
l_int|21
op_logical_or
(paren
id|irq
op_ge
l_int|16
op_logical_and
id|irq
op_le
l_int|19
)paren
op_logical_or
id|irq
op_eq
id|IRQ_KEYBOARDTX
)paren
id|flags
op_or_assign
id|IRQF_NOAUTOEN
suffix:semicolon
r_switch
c_cond
(paren
id|irq
)paren
(brace
r_case
l_int|0
dot
dot
dot
l_int|7
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|iomd_a_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|8
dot
dot
dot
l_int|15
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|iomd_b_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|16
dot
dot
dot
l_int|21
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|iomd_dma_chip
)paren
suffix:semicolon
id|set_irq_handler
c_func
(paren
id|irq
comma
id|do_level_IRQ
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|flags
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|64
dot
dot
dot
l_int|71
suffix:colon
id|set_irq_chip
c_func
(paren
id|irq
comma
op_amp
id|iomd_fiq_chip
)paren
suffix:semicolon
id|set_irq_flags
c_func
(paren
id|irq
comma
id|IRQF_VALID
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|init_FIQ
c_func
(paren
)paren
suffix:semicolon
)brace
eof
