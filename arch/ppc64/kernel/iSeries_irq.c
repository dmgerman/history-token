multiline_comment|/************************************************************************/
multiline_comment|/* This module supports the iSeries PCI bus interrupt handling          */
multiline_comment|/* Copyright (C) 20yy  &lt;Robert L Holtorf&gt; &lt;IBM Corp&gt;                    */
multiline_comment|/*                                                                      */
multiline_comment|/* This program is free software; you can redistribute it and/or modify */
multiline_comment|/* it under the terms of the GNU General Public License as published by */
multiline_comment|/* the Free Software Foundation; either version 2 of the License, or    */
multiline_comment|/* (at your option) any later version.                                  */
multiline_comment|/*                                                                      */
multiline_comment|/* This program is distributed in the hope that it will be useful,      */
multiline_comment|/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
multiline_comment|/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
multiline_comment|/* GNU General Public License for more details.                         */
multiline_comment|/*                                                                      */
multiline_comment|/* You should have received a copy of the GNU General Public License    */
multiline_comment|/* along with this program; if not, write to the:                       */
multiline_comment|/* Free Software Foundation, Inc.,                                      */
multiline_comment|/* 59 Temple Place, Suite 330,                                          */
multiline_comment|/* Boston, MA  02111-1307  USA                                          */
multiline_comment|/************************************************************************/
multiline_comment|/* Change Activity:                                                     */
multiline_comment|/*   Created, December 13, 2000 by Wayne Holm                           */
multiline_comment|/* End Change Activity                                                  */
multiline_comment|/************************************************************************/
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallXm.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_irq.h&gt;
macro_line|#include &lt;asm/iSeries/XmPciLpEvent.h&gt;
r_static
r_int
r_int
id|iSeries_startup_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|iSeries_shutdown_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|iSeries_enable_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|iSeries_disable_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
r_static
r_void
id|iSeries_end_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
suffix:semicolon
DECL|variable|iSeries_IRQ_handler
r_static
id|hw_irq_controller
id|iSeries_IRQ_handler
op_assign
(brace
dot
r_typename
op_assign
l_string|&quot;iSeries irq controller&quot;
comma
dot
id|startup
op_assign
id|iSeries_startup_IRQ
comma
dot
id|shutdown
op_assign
id|iSeries_shutdown_IRQ
comma
dot
id|enable
op_assign
id|iSeries_enable_IRQ
comma
dot
id|disable
op_assign
id|iSeries_disable_IRQ
comma
dot
id|end
op_assign
id|iSeries_end_IRQ
)brace
suffix:semicolon
multiline_comment|/* This maps virtual irq numbers to real irqs */
DECL|variable|virt_irq_to_real_map
r_int
r_int
id|virt_irq_to_real_map
(braket
id|NR_IRQS
)braket
suffix:semicolon
multiline_comment|/* The next available virtual irq number */
multiline_comment|/* Note: the pcnet32 driver assumes irq numbers &lt; 2 aren&squot;t valid. :( */
DECL|variable|next_virtual_irq
r_static
r_int
id|next_virtual_irq
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* This is called by init_IRQ.  set in ppc_md.init_IRQ by iSeries_setup.c */
DECL|function|iSeries_init_IRQ
r_void
id|__init
id|iSeries_init_IRQ
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* Register PCI event handler and open an event path */
id|XmPciLpEvent_init
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called out of iSeries_scan_slot to allocate an IRQ for an EADS slot&n; * It calculates the irq value for the slot.&n; * Note that subBusNumber is always 0 (at the moment at least).&n; */
DECL|function|iSeries_allocate_IRQ
r_int
id|__init
id|iSeries_allocate_IRQ
c_func
(paren
id|HvBusNumber
id|busNumber
comma
id|HvSubBusNumber
id|subBusNumber
comma
id|HvAgentId
id|deviceId
)paren
(brace
r_int
r_int
id|realirq
comma
id|virtirq
suffix:semicolon
id|u8
id|idsel
op_assign
(paren
id|deviceId
op_rshift
l_int|4
)paren
suffix:semicolon
id|u8
id|function
op_assign
id|deviceId
op_amp
l_int|7
suffix:semicolon
id|virtirq
op_assign
id|next_virtual_irq
op_increment
suffix:semicolon
id|realirq
op_assign
(paren
(paren
id|busNumber
op_minus
l_int|1
)paren
op_lshift
l_int|6
)paren
op_plus
(paren
(paren
id|idsel
op_minus
l_int|1
)paren
op_lshift
l_int|3
)paren
op_plus
id|function
suffix:semicolon
id|virt_irq_to_real_map
(braket
id|virtirq
)braket
op_assign
id|realirq
suffix:semicolon
id|irq_desc
(braket
id|virtirq
)braket
dot
id|handler
op_assign
op_amp
id|iSeries_IRQ_handler
suffix:semicolon
r_return
id|virtirq
suffix:semicolon
)brace
DECL|macro|REAL_IRQ_TO_BUS
mdefine_line|#define REAL_IRQ_TO_BUS(irq)&t;((((irq) &gt;&gt; 6) &amp; 0xff) + 1)
DECL|macro|REAL_IRQ_TO_IDSEL
mdefine_line|#define REAL_IRQ_TO_IDSEL(irq)&t;((((irq) &gt;&gt; 3) &amp; 7) + 1)
DECL|macro|REAL_IRQ_TO_FUNC
mdefine_line|#define REAL_IRQ_TO_FUNC(irq)&t;((irq) &amp; 7)
multiline_comment|/* This is called by iSeries_activate_IRQs */
DECL|function|iSeries_startup_IRQ
r_static
r_int
r_int
id|iSeries_startup_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|bus
comma
id|deviceId
comma
id|function
comma
id|mask
suffix:semicolon
r_const
id|u32
id|subBus
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|rirq
op_assign
id|virt_irq_to_real_map
(braket
id|irq
)braket
suffix:semicolon
id|bus
op_assign
id|REAL_IRQ_TO_BUS
c_func
(paren
id|rirq
)paren
suffix:semicolon
id|function
op_assign
id|REAL_IRQ_TO_FUNC
c_func
(paren
id|rirq
)paren
suffix:semicolon
id|deviceId
op_assign
(paren
id|REAL_IRQ_TO_IDSEL
c_func
(paren
id|rirq
)paren
op_lshift
l_int|4
)paren
op_plus
id|function
suffix:semicolon
multiline_comment|/* Link the IRQ number to the bridge */
id|HvCallXm_connectBusUnit
c_func
(paren
id|bus
comma
id|subBus
comma
id|deviceId
comma
id|irq
)paren
suffix:semicolon
multiline_comment|/* Unmask bridge interrupts in the FISR */
id|mask
op_assign
l_int|0x01010000
op_lshift
id|function
suffix:semicolon
id|HvCallPci_unmaskFisr
c_func
(paren
id|bus
comma
id|subBus
comma
id|deviceId
comma
id|mask
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * This is called out of iSeries_fixup to activate interrupt&n; * generation for usable slots&n; */
DECL|function|iSeries_activate_IRQs
r_void
id|__init
id|iSeries_activate_IRQs
c_func
(paren
)paren
(brace
r_int
id|irq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|for_each_irq
(paren
id|irq
)paren
(brace
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
r_if
c_cond
(paren
id|desc
op_logical_and
id|desc-&gt;handler
op_logical_and
id|desc-&gt;handler-&gt;startup
)paren
(brace
id|spin_lock_irqsave
c_func
(paren
op_amp
id|desc-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|desc-&gt;handler
op_member_access_from_pointer
id|startup
c_func
(paren
id|irq
)paren
suffix:semicolon
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
)brace
)brace
multiline_comment|/*  this is not called anywhere currently */
DECL|function|iSeries_shutdown_IRQ
r_static
r_void
id|iSeries_shutdown_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|bus
comma
id|deviceId
comma
id|function
comma
id|mask
suffix:semicolon
r_const
id|u32
id|subBus
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|rirq
op_assign
id|virt_irq_to_real_map
(braket
id|irq
)braket
suffix:semicolon
multiline_comment|/* irq should be locked by the caller */
id|bus
op_assign
id|REAL_IRQ_TO_BUS
c_func
(paren
id|rirq
)paren
suffix:semicolon
id|function
op_assign
id|REAL_IRQ_TO_FUNC
c_func
(paren
id|rirq
)paren
suffix:semicolon
id|deviceId
op_assign
(paren
id|REAL_IRQ_TO_IDSEL
c_func
(paren
id|rirq
)paren
op_lshift
l_int|4
)paren
op_plus
id|function
suffix:semicolon
multiline_comment|/* Invalidate the IRQ number in the bridge */
id|HvCallXm_connectBusUnit
c_func
(paren
id|bus
comma
id|subBus
comma
id|deviceId
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Mask bridge interrupts in the FISR */
id|mask
op_assign
l_int|0x01010000
op_lshift
id|function
suffix:semicolon
id|HvCallPci_maskFisr
c_func
(paren
id|bus
comma
id|subBus
comma
id|deviceId
comma
id|mask
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This will be called by device drivers (via disable_IRQ)&n; * to disable INTA in the bridge interrupt status register.&n; */
DECL|function|iSeries_disable_IRQ
r_static
r_void
id|iSeries_disable_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|bus
comma
id|deviceId
comma
id|function
comma
id|mask
suffix:semicolon
r_const
id|u32
id|subBus
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|rirq
op_assign
id|virt_irq_to_real_map
(braket
id|irq
)braket
suffix:semicolon
multiline_comment|/* The IRQ has already been locked by the caller */
id|bus
op_assign
id|REAL_IRQ_TO_BUS
c_func
(paren
id|rirq
)paren
suffix:semicolon
id|function
op_assign
id|REAL_IRQ_TO_FUNC
c_func
(paren
id|rirq
)paren
suffix:semicolon
id|deviceId
op_assign
(paren
id|REAL_IRQ_TO_IDSEL
c_func
(paren
id|rirq
)paren
op_lshift
l_int|4
)paren
op_plus
id|function
suffix:semicolon
multiline_comment|/* Mask secondary INTA   */
id|mask
op_assign
l_int|0x80000000
suffix:semicolon
id|HvCallPci_maskInterrupts
c_func
(paren
id|bus
comma
id|subBus
comma
id|deviceId
comma
id|mask
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_BUSWALK
comma
l_string|&quot;iSeries_disable_IRQ 0x%02X.%02X.%02X 0x%04X&bslash;n&quot;
comma
id|bus
comma
id|subBus
comma
id|deviceId
comma
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This will be called by device drivers (via enable_IRQ)&n; * to enable INTA in the bridge interrupt status register.&n; */
DECL|function|iSeries_enable_IRQ
r_static
r_void
id|iSeries_enable_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
id|u32
id|bus
comma
id|deviceId
comma
id|function
comma
id|mask
suffix:semicolon
r_const
id|u32
id|subBus
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|rirq
op_assign
id|virt_irq_to_real_map
(braket
id|irq
)braket
suffix:semicolon
multiline_comment|/* The IRQ has already been locked by the caller */
id|bus
op_assign
id|REAL_IRQ_TO_BUS
c_func
(paren
id|rirq
)paren
suffix:semicolon
id|function
op_assign
id|REAL_IRQ_TO_FUNC
c_func
(paren
id|rirq
)paren
suffix:semicolon
id|deviceId
op_assign
(paren
id|REAL_IRQ_TO_IDSEL
c_func
(paren
id|rirq
)paren
op_lshift
l_int|4
)paren
op_plus
id|function
suffix:semicolon
multiline_comment|/* Unmask secondary INTA */
id|mask
op_assign
l_int|0x80000000
suffix:semicolon
id|HvCallPci_unmaskInterrupts
c_func
(paren
id|bus
comma
id|subBus
comma
id|deviceId
comma
id|mask
)paren
suffix:semicolon
id|PPCDBG
c_func
(paren
id|PPCDBG_BUSWALK
comma
l_string|&quot;iSeries_enable_IRQ 0x%02X.%02X.%02X 0x%04X&bslash;n&quot;
comma
id|bus
comma
id|subBus
comma
id|deviceId
comma
id|irq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Need to define this so ppc_irq_dispatch_handler will NOT call&n; * enable_IRQ at the end of interrupt handling.  However, this does&n; * nothing because there is not enough information provided to do&n; * the EOI HvCall.  This is done by XmPciLpEvent.c&n; */
DECL|function|iSeries_end_IRQ
r_static
r_void
id|iSeries_end_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
)brace
eof
