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
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/smp.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/irq.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallPci.h&gt;
macro_line|#include &lt;asm/iSeries/HvCallXm.h&gt;
macro_line|#include &lt;asm/iSeries/iSeries_irq.h&gt;
macro_line|#include &lt;asm/iSeries/XmPciLpEvent.h&gt;
DECL|variable|iSeries_IRQ_handler
id|hw_irq_controller
id|iSeries_IRQ_handler
op_assign
(brace
l_string|&quot;iSeries irq controller&quot;
comma
id|iSeries_startup_IRQ
comma
multiline_comment|/* startup */
id|iSeries_shutdown_IRQ
comma
multiline_comment|/* shutdown */
id|iSeries_enable_IRQ
comma
multiline_comment|/* enable */
id|iSeries_disable_IRQ
comma
multiline_comment|/* disable */
l_int|NULL
comma
multiline_comment|/* ack  */
id|iSeries_end_IRQ
comma
multiline_comment|/* end  */
l_int|NULL
multiline_comment|/* set_affinity */
)brace
suffix:semicolon
DECL|struct|iSeries_irqEntry
r_struct
id|iSeries_irqEntry
(brace
DECL|member|dsa
id|u32
id|dsa
suffix:semicolon
DECL|member|next
r_struct
id|iSeries_irqEntry
op_star
id|next
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|iSeries_irqAnchor
r_struct
id|iSeries_irqAnchor
(brace
DECL|member|valid
id|u8
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:colon
l_int|7
suffix:semicolon
DECL|member|entryCount
id|u16
id|entryCount
suffix:semicolon
DECL|member|head
r_struct
id|iSeries_irqEntry
op_star
id|head
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|iSeries_irqMap
r_struct
id|iSeries_irqAnchor
id|iSeries_irqMap
(braket
id|NR_IRQS
)braket
suffix:semicolon
r_void
id|iSeries_init_irqMap
c_func
(paren
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/*  This is called by init_IRQ.  set in ppc_md.init_IRQ by iSeries_setup.c */
DECL|function|iSeries_init_IRQ
r_void
id|__init
id|iSeries_init_IRQ
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
l_int|0
suffix:semicolon
id|i
OL
id|NR_IRQS
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
id|iSeries_IRQ_handler
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_assign
l_int|0
suffix:semicolon
id|irq_desc
(braket
id|i
)braket
dot
id|status
op_or_assign
id|IRQ_DISABLED
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
id|iSeries_init_irqMap
c_func
(paren
id|i
)paren
suffix:semicolon
)brace
multiline_comment|/* Register PCI event handler and open an event path */
id|XmPciLpEvent_init
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*  Called by iSeries_init_IRQ */
DECL|function|iSeries_init_irqMap
r_void
id|__init
id|iSeries_init_irqMap
c_func
(paren
r_int
id|irq
)paren
(brace
multiline_comment|/* Prevent IRQs 0 and 255 from being used.  IRQ 0 appears in&n;      uninitialized devices.  IRQ 255 appears in the PCI interrupt&n;      line register if a PCI error occurs */
id|iSeries_irqMap
(braket
id|irq
)braket
dot
id|valid
op_assign
(paren
id|irq
op_eq
l_int|0
op_logical_or
id|irq
op_eq
l_int|255
)paren
ques
c_cond
l_int|0
suffix:colon
l_int|1
suffix:semicolon
id|iSeries_irqMap
(braket
id|irq
)braket
dot
id|entryCount
op_assign
l_int|0
suffix:semicolon
id|iSeries_irqMap
(braket
id|irq
)braket
dot
id|head
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* This is called out of iSeries_scan_slot to allocate an IRQ for an EADS slot */
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
l_int|0x0F
suffix:semicolon
r_int
id|irq
op_assign
(paren
(paren
(paren
(paren
id|busNumber
op_minus
l_int|1
)paren
op_star
l_int|16
op_plus
(paren
id|idsel
op_minus
l_int|1
)paren
op_star
l_int|8
op_plus
id|function
)paren
op_star
l_int|9
op_div
l_int|8
)paren
op_mod
l_int|254
)paren
op_plus
l_int|1
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
multiline_comment|/* This is called out of iSeries_scan_slot to assign the EADS slot to its IRQ number */
DECL|function|iSeries_assign_IRQ
r_int
id|__init
id|iSeries_assign_IRQ
c_func
(paren
r_int
id|irq
comma
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
id|rc
suffix:semicolon
id|u32
id|dsa
op_assign
(paren
id|busNumber
op_lshift
l_int|16
)paren
op_or
(paren
id|subBusNumber
op_lshift
l_int|8
)paren
op_or
id|deviceId
suffix:semicolon
r_struct
id|iSeries_irqEntry
op_star
id|newEntry
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|irq
OL
l_int|0
op_logical_or
id|irq
op_ge
id|NR_IRQS
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|newEntry
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|newEntry
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|newEntry
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|newEntry-&gt;dsa
op_assign
id|dsa
suffix:semicolon
id|newEntry-&gt;next
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Probably not necessary to lock the irq since allocation is only&n;       done during buswalk, but it should not hurt anything except a little&n;       performance */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_desc
(braket
id|irq
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iSeries_irqMap
(braket
id|irq
)braket
dot
id|valid
)paren
(brace
multiline_comment|/* Push the new element onto the irq stack */
id|newEntry-&gt;next
op_assign
id|iSeries_irqMap
(braket
id|irq
)braket
dot
id|head
suffix:semicolon
id|iSeries_irqMap
(braket
id|irq
)braket
dot
id|head
op_assign
id|newEntry
suffix:semicolon
op_increment
id|iSeries_irqMap
(braket
id|irq
)braket
dot
id|entryCount
suffix:semicolon
id|rc
op_assign
l_int|0
suffix:semicolon
)brace
r_else
id|rc
op_assign
op_minus
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|irq_desc
(braket
id|irq
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
op_ne
l_int|0
op_logical_and
id|newEntry
)paren
id|kfree
c_func
(paren
id|newEntry
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
multiline_comment|/* This is called by iSeries_activate_IRQs */
DECL|function|iSeries_startup_IRQ
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
r_struct
id|iSeries_irqEntry
op_star
id|entry
suffix:semicolon
id|u32
id|bus
comma
id|subBus
comma
id|deviceId
comma
id|function
comma
id|mask
suffix:semicolon
multiline_comment|/* irq should be locked by the caller */
r_for
c_loop
(paren
id|entry
op_assign
id|iSeries_irqMap
(braket
id|irq
)braket
dot
id|head
suffix:semicolon
id|entry
op_ne
l_int|NULL
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
id|bus
op_assign
(paren
id|entry-&gt;dsa
op_rshift
l_int|16
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
id|subBus
op_assign
(paren
id|entry-&gt;dsa
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|deviceId
op_assign
id|entry-&gt;dsa
op_amp
l_int|0xFF
suffix:semicolon
id|function
op_assign
id|deviceId
op_amp
l_int|0x0F
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
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* This is called out of iSeries_fixup to&n;   activate interrupt generation for usable slots */
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
id|spin_lock_irqsave
c_func
(paren
op_amp
id|irq_desc
(braket
id|irq
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
id|irq_desc
(braket
id|irq
)braket
dot
id|handler
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
id|irq_desc
(braket
id|irq
)braket
dot
id|lock
comma
id|flags
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*  this is not called anywhere currently */
DECL|function|iSeries_shutdown_IRQ
r_void
id|iSeries_shutdown_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|iSeries_irqEntry
op_star
id|entry
suffix:semicolon
id|u32
id|bus
comma
id|subBus
comma
id|deviceId
comma
id|function
comma
id|mask
suffix:semicolon
multiline_comment|/* irq should be locked by the caller */
r_for
c_loop
(paren
id|entry
op_assign
id|iSeries_irqMap
(braket
id|irq
)braket
dot
id|head
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
id|bus
op_assign
(paren
id|entry-&gt;dsa
op_rshift
l_int|16
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
id|subBus
op_assign
(paren
id|entry-&gt;dsa
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|deviceId
op_assign
id|entry-&gt;dsa
op_amp
l_int|0xFF
suffix:semicolon
id|function
op_assign
id|deviceId
op_amp
l_int|0x0F
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
)brace
multiline_comment|/* This will be called by device drivers (via disable_IRQ to disable&n;   INTA in the bridge interrupt status register */
DECL|function|iSeries_disable_IRQ
r_void
id|iSeries_disable_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|iSeries_irqEntry
op_star
id|entry
suffix:semicolon
id|u32
id|bus
comma
id|subBus
comma
id|deviceId
comma
id|mask
suffix:semicolon
multiline_comment|/* The IRQ has already been locked by the caller */
r_for
c_loop
(paren
id|entry
op_assign
id|iSeries_irqMap
(braket
id|irq
)braket
dot
id|head
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
id|bus
op_assign
(paren
id|entry-&gt;dsa
op_rshift
l_int|16
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
id|subBus
op_assign
(paren
id|entry-&gt;dsa
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|deviceId
op_assign
id|entry-&gt;dsa
op_amp
l_int|0xFF
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
)brace
)brace
multiline_comment|/* This will be called by device drivers (via enable_IRQ to enable&n;   INTA in the bridge interrupt status register */
DECL|function|iSeries_enable_IRQ
r_void
id|iSeries_enable_IRQ
c_func
(paren
r_int
r_int
id|irq
)paren
(brace
r_struct
id|iSeries_irqEntry
op_star
id|entry
suffix:semicolon
id|u32
id|bus
comma
id|subBus
comma
id|deviceId
comma
id|mask
suffix:semicolon
multiline_comment|/* The IRQ has already been locked by the caller */
r_for
c_loop
(paren
id|entry
op_assign
id|iSeries_irqMap
(braket
id|irq
)braket
dot
id|head
suffix:semicolon
id|entry
suffix:semicolon
id|entry
op_assign
id|entry-&gt;next
)paren
(brace
id|bus
op_assign
(paren
id|entry-&gt;dsa
op_rshift
l_int|16
)paren
op_amp
l_int|0xFFFF
suffix:semicolon
id|subBus
op_assign
(paren
id|entry-&gt;dsa
op_rshift
l_int|8
)paren
op_amp
l_int|0xFF
suffix:semicolon
id|deviceId
op_assign
id|entry-&gt;dsa
op_amp
l_int|0xFF
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
)brace
)brace
multiline_comment|/* Need to define this so ppc_irq_dispatch_handler will NOT call&n;   enable_IRQ at the end of interrupt handling.  However, this&n;   does nothing because there is not enough information provided&n;   to do the EOI HvCall.  This is done by XmPciLpEvent.c */
DECL|function|iSeries_end_IRQ
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
