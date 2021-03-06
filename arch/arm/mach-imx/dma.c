multiline_comment|/*&n; *  linux/arch/arm/mach-imx/dma.c&n; *&n; *  imx DMA registration and IRQ dispatching&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation.&n; *&n; *  03/03/2004 Sascha Hauer &lt;sascha@saschahauer.de&gt;&n; *             initial version heavily inspired by&n; *             linux/arch/arm/mach-pxa/dma.c&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
DECL|struct|dma_channel
r_static
r_struct
id|dma_channel
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|irq_handler
r_void
(paren
op_star
id|irq_handler
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
suffix:semicolon
DECL|member|err_handler
r_void
(paren
op_star
id|err_handler
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
suffix:semicolon
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|variable|dma_channels
)brace
id|dma_channels
(braket
l_int|11
)braket
suffix:semicolon
multiline_comment|/* set err_handler to NULL to have the standard info-only error handler */
r_int
DECL|function|imx_request_dma
id|imx_request_dma
c_func
(paren
r_char
op_star
id|name
comma
id|imx_dma_prio
id|prio
comma
r_void
(paren
op_star
id|irq_handler
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
r_void
(paren
op_star
id|err_handler
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
r_void
op_star
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
comma
id|found
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* basic sanity checks */
r_if
c_cond
(paren
op_logical_neg
id|name
op_logical_or
op_logical_neg
id|irq_handler
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* try grabbing a DMA channel with the requested priority */
r_for
c_loop
(paren
id|i
op_assign
id|prio
suffix:semicolon
id|i
OL
id|prio
op_plus
(paren
id|prio
op_eq
id|DMA_PRIO_LOW
)paren
ques
c_cond
l_int|8
suffix:colon
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dma_channels
(braket
id|i
)braket
dot
id|name
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|found
)paren
(brace
multiline_comment|/* requested prio group is full, try hier priorities */
r_for
c_loop
(paren
id|i
op_assign
id|prio
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|dma_channels
(braket
id|i
)braket
dot
id|name
)paren
(brace
id|found
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
id|found
)paren
(brace
id|DIMR
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
id|dma_channels
(braket
id|i
)braket
dot
id|name
op_assign
id|name
suffix:semicolon
id|dma_channels
(braket
id|i
)braket
dot
id|irq_handler
op_assign
id|irq_handler
suffix:semicolon
id|dma_channels
(braket
id|i
)braket
dot
id|err_handler
op_assign
id|err_handler
suffix:semicolon
id|dma_channels
(braket
id|i
)braket
dot
id|data
op_assign
id|data
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;No more available DMA channels for %s&bslash;n&quot;
comma
id|name
)paren
suffix:semicolon
id|i
op_assign
op_minus
id|ENODEV
suffix:semicolon
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
r_void
DECL|function|imx_free_dma
id|imx_free_dma
c_func
(paren
r_int
id|dma_ch
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma_channels
(braket
id|dma_ch
)braket
dot
id|name
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;%s: trying to free channel %d which is already freed&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|dma_ch
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|DIMR
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|dma_ch
)paren
suffix:semicolon
id|dma_channels
(braket
id|dma_ch
)braket
dot
id|name
op_assign
l_int|NULL
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|dma_err_handler
id|dma_err_handler
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
r_int
id|i
comma
id|disr
op_assign
id|DISR
suffix:semicolon
r_struct
id|dma_channel
op_star
id|channel
suffix:semicolon
r_int
r_int
id|err_mask
op_assign
id|DBTOSR
op_or
id|DRTOSR
op_or
id|DSESR
op_or
id|DBOSR
suffix:semicolon
id|DISR
op_assign
id|disr
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
l_int|11
suffix:semicolon
id|i
op_increment
)paren
(brace
id|channel
op_assign
op_amp
id|dma_channels
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err_mask
op_amp
l_int|1
op_lshift
id|i
)paren
op_logical_and
id|channel-&gt;name
op_logical_and
id|channel-&gt;err_handler
)paren
(brace
id|channel
op_member_access_from_pointer
id|err_handler
c_func
(paren
id|i
comma
id|channel-&gt;data
comma
id|regs
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DBTOSR
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Burst timeout on channel %d (%s)&bslash;n&quot;
comma
id|i
comma
id|channel-&gt;name
)paren
suffix:semicolon
id|DBTOSR
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DRTOSR
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Request timeout on channel %d (%s)&bslash;n&quot;
comma
id|i
comma
id|channel-&gt;name
)paren
suffix:semicolon
id|DRTOSR
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DSESR
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Transfer timeout on channel %d (%s)&bslash;n&quot;
comma
id|i
comma
id|channel-&gt;name
)paren
suffix:semicolon
id|DSESR
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|DBOSR
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Buffer overflow timeout on channel %d (%s)&bslash;n&quot;
comma
id|i
comma
id|channel-&gt;name
)paren
suffix:semicolon
id|DBOSR
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
)brace
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
id|irqreturn_t
DECL|function|dma_irq_handler
id|dma_irq_handler
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
r_int
id|i
comma
id|disr
op_assign
id|DISR
suffix:semicolon
id|DISR
op_assign
id|disr
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
l_int|11
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|disr
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
r_struct
id|dma_channel
op_star
id|channel
op_assign
op_amp
id|dma_channels
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|channel-&gt;name
op_logical_and
id|channel-&gt;irq_handler
)paren
(brace
id|channel
op_member_access_from_pointer
id|irq_handler
c_func
(paren
id|i
comma
id|channel-&gt;data
comma
id|regs
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * IRQ for an unregistered DMA channel:&n;&t;&t;&t;&t; * let&squot;s clear the interrupts and disable it.&n;&t;&t;&t;&t; */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;spurious IRQ for DMA channel %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
)brace
)brace
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|imx_dma_init
id|imx_dma_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
multiline_comment|/* reset DMA module */
id|DCR
op_assign
id|DCR_DRST
suffix:semicolon
id|ret
op_assign
id|request_irq
c_func
(paren
id|DMA_INT
comma
id|dma_irq_handler
comma
l_int|0
comma
l_string|&quot;DMA&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Wow!  Can&squot;t register IRQ for DMA&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
id|ret
op_assign
id|request_irq
c_func
(paren
id|DMA_ERR
comma
id|dma_err_handler
comma
l_int|0
comma
l_string|&quot;DMA&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Wow!  Can&squot;t register ERRIRQ for DMA&bslash;n&quot;
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|DMA_INT
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* enable DMA module */
id|DCR
op_assign
id|DCR_DEN
suffix:semicolon
multiline_comment|/* clear all interrupts */
id|DISR
op_assign
l_int|0x3ff
suffix:semicolon
multiline_comment|/* enable interrupts */
id|DIMR
op_assign
l_int|0
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|imx_dma_init
id|arch_initcall
c_func
(paren
id|imx_dma_init
)paren
suffix:semicolon
DECL|variable|imx_request_dma
id|EXPORT_SYMBOL
c_func
(paren
id|imx_request_dma
)paren
suffix:semicolon
DECL|variable|imx_free_dma
id|EXPORT_SYMBOL
c_func
(paren
id|imx_free_dma
)paren
suffix:semicolon
eof
