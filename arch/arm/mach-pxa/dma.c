multiline_comment|/*&n; *  linux/arch/arm/mach-pxa/dma.c&n; *&n; *  PXA DMA registration and IRQ dispatching&n; *&n; *  Author:&t;Nicolas Pitre&n; *  Created:&t;Nov 15, 2001&n; *  Copyright:&t;MontaVista Software Inc.&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License version 2 as&n; *  published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
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
DECL|member|data
r_void
op_star
id|data
suffix:semicolon
DECL|variable|dma_channels
)brace
id|dma_channels
(braket
l_int|16
)braket
suffix:semicolon
DECL|function|pxa_request_dma
r_int
id|pxa_request_dma
(paren
r_char
op_star
id|name
comma
id|pxa_dma_prio
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
id|DCSR
c_func
(paren
id|i
)paren
op_assign
id|DCSR_STARTINTR
op_or
id|DCSR_ENDINTR
op_or
id|DCSR_BUSERR
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
id|data
op_assign
id|data
suffix:semicolon
)brace
r_else
(brace
id|printk
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
DECL|function|pxa_free_dma
r_void
id|pxa_free_dma
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
(paren
id|KERN_CRIT
id|__FUNCTION__
l_string|&quot;: trying to free channel %d which is already freed&bslash;n&quot;
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
id|DCSR
c_func
(paren
id|dma_ch
)paren
op_assign
id|DCSR_STARTINTR
op_or
id|DCSR_ENDINTR
op_or
id|DCSR_BUSERR
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
DECL|function|dma_irq_handler
r_static
r_void
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
id|dint
op_assign
id|DINT
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
l_int|16
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|dint
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
(paren
id|KERN_WARNING
l_string|&quot;spurious IRQ for DMA channel %d&bslash;n&quot;
comma
id|i
)paren
suffix:semicolon
id|DCSR
c_func
(paren
id|i
)paren
op_assign
id|DCSR_STARTINTR
op_or
id|DCSR_ENDINTR
op_or
id|DCSR_BUSERR
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|pxa_dma_init
r_static
r_int
id|__init
id|pxa_dma_init
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|request_irq
(paren
id|IRQ_DMA
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
id|printk
(paren
id|KERN_CRIT
l_string|&quot;Wow!  Can&squot;t register IRQ for DMA&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|pxa_dma_init
id|__initcall
c_func
(paren
id|pxa_dma_init
)paren
suffix:semicolon
DECL|variable|pxa_request_dma
id|EXPORT_SYMBOL
c_func
(paren
id|pxa_request_dma
)paren
suffix:semicolon
DECL|variable|pxa_free_dma
id|EXPORT_SYMBOL
c_func
(paren
id|pxa_free_dma
)paren
suffix:semicolon
eof
