multiline_comment|/*&n; * arch/sh/boards/dreamcast/dma-pvr2.c&n; *&n; * NEC PowerVR 2 (Dreamcast) DMA support&n; *&n; * Copyright (C) 2003, 2004  Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/mach/sysasic.h&gt;
macro_line|#include &lt;asm/mach/dma.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|variable|xfer_complete
r_static
r_int
r_int
id|xfer_complete
op_assign
l_int|0
suffix:semicolon
DECL|variable|count
r_static
r_int
id|count
op_assign
l_int|0
suffix:semicolon
DECL|function|pvr2_dma_interrupt
r_static
id|irqreturn_t
id|pvr2_dma_interrupt
c_func
(paren
r_int
id|irq
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
r_if
c_cond
(paren
id|get_dma_residue
c_func
(paren
id|PVR2_CASCADE_CHAN
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;DMA: SH DMAC did not complete transfer &quot;
l_string|&quot;on channel %d, waiting..&bslash;n&quot;
comma
id|PVR2_CASCADE_CHAN
)paren
suffix:semicolon
id|dma_wait_for_completion
c_func
(paren
id|PVR2_CASCADE_CHAN
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|count
op_increment
OL
l_int|10
)paren
id|pr_debug
c_func
(paren
l_string|&quot;Got a pvr2 dma interrupt for channel %d&bslash;n&quot;
comma
id|irq
op_minus
id|HW_EVENT_PVR2_DMA
)paren
suffix:semicolon
id|xfer_complete
op_assign
l_int|1
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|pvr2_request_dma
r_static
r_int
id|pvr2_request_dma
c_func
(paren
r_struct
id|dma_channel
op_star
id|chan
)paren
(brace
r_if
c_cond
(paren
id|ctrl_inl
c_func
(paren
id|PVR2_DMA_MODE
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|ctrl_outl
c_func
(paren
l_int|0
comma
id|PVR2_DMA_LMMODE0
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pvr2_get_dma_residue
r_static
r_int
id|pvr2_get_dma_residue
c_func
(paren
r_struct
id|dma_channel
op_star
id|chan
)paren
(brace
r_return
id|xfer_complete
op_eq
l_int|0
suffix:semicolon
)brace
DECL|function|pvr2_xfer_dma
r_static
r_int
id|pvr2_xfer_dma
c_func
(paren
r_struct
id|dma_channel
op_star
id|chan
)paren
(brace
r_if
c_cond
(paren
id|chan-&gt;sar
op_logical_or
op_logical_neg
id|chan-&gt;dar
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|xfer_complete
op_assign
l_int|0
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|chan-&gt;dar
comma
id|PVR2_DMA_ADDR
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|chan-&gt;count
comma
id|PVR2_DMA_COUNT
)paren
suffix:semicolon
id|ctrl_outl
c_func
(paren
id|chan-&gt;mode
op_amp
id|DMA_MODE_MASK
comma
id|PVR2_DMA_MODE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pvr2_dma_irq
r_static
r_struct
id|irqaction
id|pvr2_dma_irq
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pvr2 DMA handler&quot;
comma
dot
id|handler
op_assign
id|pvr2_dma_interrupt
comma
dot
id|flags
op_assign
id|SA_INTERRUPT
comma
)brace
suffix:semicolon
DECL|variable|pvr2_dma_ops
r_static
r_struct
id|dma_ops
id|pvr2_dma_ops
op_assign
(brace
dot
id|request
op_assign
id|pvr2_request_dma
comma
dot
id|get_residue
op_assign
id|pvr2_get_dma_residue
comma
dot
id|xfer
op_assign
id|pvr2_xfer_dma
comma
)brace
suffix:semicolon
DECL|variable|pvr2_dma_info
r_static
r_struct
id|dma_info
id|pvr2_dma_info
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;PowerVR 2 DMA&quot;
comma
dot
id|nr_channels
op_assign
l_int|1
comma
dot
id|ops
op_assign
op_amp
id|pvr2_dma_ops
comma
dot
id|flags
op_assign
id|DMAC_CHANNELS_TEI_CAPABLE
comma
)brace
suffix:semicolon
DECL|function|pvr2_dma_init
r_static
r_int
id|__init
id|pvr2_dma_init
c_func
(paren
r_void
)paren
(brace
id|setup_irq
c_func
(paren
id|HW_EVENT_PVR2_DMA
comma
op_amp
id|pvr2_dma_irq
)paren
suffix:semicolon
id|request_dma
c_func
(paren
id|PVR2_CASCADE_CHAN
comma
l_string|&quot;pvr2 cascade&quot;
)paren
suffix:semicolon
r_return
id|register_dmac
c_func
(paren
op_amp
id|pvr2_dma_info
)paren
suffix:semicolon
)brace
DECL|function|pvr2_dma_exit
r_static
r_void
id|__exit
id|pvr2_dma_exit
c_func
(paren
r_void
)paren
(brace
id|free_dma
c_func
(paren
id|PVR2_CASCADE_CHAN
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|HW_EVENT_PVR2_DMA
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|pvr2_dma_init
id|subsys_initcall
c_func
(paren
id|pvr2_dma_init
)paren
suffix:semicolon
DECL|variable|pvr2_dma_exit
id|module_exit
c_func
(paren
id|pvr2_dma_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Paul Mundt &lt;lethal@linux-sh.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;NEC PowerVR 2 DMA driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
