multiline_comment|/*&n; *&t;Adaptec AAC series RAID controller driver&n; *&t;(c) Copyright 2001 Red Hat Inc.&t;&lt;alan@redhat.com&gt;&n; *&n; * based on the old aacraid driver that is..&n; * Adaptec aacraid device driver for Linux.&n; *&n; * Copyright (c) 2000 Adaptec, Inc. (aacraid@adaptec.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Module Name:&n; *  rkt.c&n; *&n; * Abstract: Hardware miniport for Drawbridge specific hardware functions.&n; *&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/time.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;scsi/scsi_host.h&gt;
macro_line|#include &quot;aacraid.h&quot;
DECL|function|aac_rkt_intr
r_static
id|irqreturn_t
id|aac_rkt_intr
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
r_struct
id|aac_dev
op_star
id|dev
op_assign
id|dev_id
suffix:semicolon
r_int
r_int
id|bellbits
suffix:semicolon
id|u8
id|intstat
comma
id|mask
suffix:semicolon
id|intstat
op_assign
id|rkt_readb
c_func
(paren
id|dev
comma
id|MUnit.OISR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Read mask and invert because drawbridge is reversed.&n;&t; *&t;This allows us to only service interrupts that have &n;&t; *&t;been enabled.&n;&t; */
id|mask
op_assign
op_complement
(paren
id|dev-&gt;OIMR
)paren
suffix:semicolon
multiline_comment|/* Check to see if this is our interrupt.  If it isn&squot;t just return */
r_if
c_cond
(paren
id|intstat
op_amp
id|mask
)paren
(brace
id|bellbits
op_assign
id|rkt_readl
c_func
(paren
id|dev
comma
id|OutboundDoorbellReg
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bellbits
op_amp
id|DoorBellPrintfReady
)paren
(brace
id|aac_printf
c_func
(paren
id|dev
comma
id|le32_to_cpu
c_func
(paren
id|rkt_readl
(paren
id|dev
comma
id|IndexRegs.Mailbox
(braket
l_int|5
)braket
)paren
)paren
)paren
suffix:semicolon
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.ODR
comma
id|DoorBellPrintfReady
)paren
suffix:semicolon
id|rkt_writel
c_func
(paren
id|dev
comma
id|InboundDoorbellReg
comma
id|DoorBellPrintfDone
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bellbits
op_amp
id|DoorBellAdapterNormCmdReady
)paren
(brace
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.ODR
comma
id|DoorBellAdapterNormCmdReady
)paren
suffix:semicolon
id|aac_command_normal
c_func
(paren
op_amp
id|dev-&gt;queues-&gt;queue
(braket
id|HostNormCmdQueue
)braket
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bellbits
op_amp
id|DoorBellAdapterNormRespReady
)paren
(brace
id|aac_response_normal
c_func
(paren
op_amp
id|dev-&gt;queues-&gt;queue
(braket
id|HostNormRespQueue
)braket
)paren
suffix:semicolon
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.ODR
comma
id|DoorBellAdapterNormRespReady
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bellbits
op_amp
id|DoorBellAdapterNormCmdNotFull
)paren
(brace
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.ODR
comma
id|DoorBellAdapterNormCmdNotFull
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|bellbits
op_amp
id|DoorBellAdapterNormRespNotFull
)paren
(brace
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.ODR
comma
id|DoorBellAdapterNormCmdNotFull
)paren
suffix:semicolon
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.ODR
comma
id|DoorBellAdapterNormRespNotFull
)paren
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
r_return
id|IRQ_NONE
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_rkt_enable_interrupt&t;-&t;Enable event reporting&n; *&t;@dev: Adapter&n; *&t;@event: Event to enable&n; *&n; *&t;Enable event reporting from the i960 for a given event.&n; */
DECL|function|aac_rkt_enable_interrupt
r_static
r_void
id|aac_rkt_enable_interrupt
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
id|u32
id|event
)paren
(brace
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|HostNormCmdQue
suffix:colon
id|dev-&gt;irq_mask
op_and_assign
op_complement
(paren
id|OUTBOUNDDOORBELL_1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HostNormRespQue
suffix:colon
id|dev-&gt;irq_mask
op_and_assign
op_complement
(paren
id|OUTBOUNDDOORBELL_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapNormCmdNotFull
suffix:colon
id|dev-&gt;irq_mask
op_and_assign
op_complement
(paren
id|OUTBOUNDDOORBELL_3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapNormRespNotFull
suffix:colon
id|dev-&gt;irq_mask
op_and_assign
op_complement
(paren
id|OUTBOUNDDOORBELL_4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;aac_rkt_disable_interrupt&t;-&t;Disable event reporting&n; *&t;@dev: Adapter&n; *&t;@event: Event to enable&n; *&n; *&t;Disable event reporting from the i960 for a given event.&n; */
DECL|function|aac_rkt_disable_interrupt
r_static
r_void
id|aac_rkt_disable_interrupt
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
id|u32
id|event
)paren
(brace
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|HostNormCmdQue
suffix:colon
id|dev-&gt;irq_mask
op_or_assign
(paren
id|OUTBOUNDDOORBELL_1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HostNormRespQue
suffix:colon
id|dev-&gt;irq_mask
op_or_assign
(paren
id|OUTBOUNDDOORBELL_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapNormCmdNotFull
suffix:colon
id|dev-&gt;irq_mask
op_or_assign
(paren
id|OUTBOUNDDOORBELL_3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapNormRespNotFull
suffix:colon
id|dev-&gt;irq_mask
op_or_assign
(paren
id|OUTBOUNDDOORBELL_4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;rkt_sync_cmd&t;-&t;send a command and wait&n; *&t;@dev: Adapter&n; *&t;@command: Command to execute&n; *&t;@p1: first parameter&n; *&t;@ret: adapter status&n; *&n; *&t;This routine will send a synchronous comamnd to the adapter and wait &n; *&t;for its&t;completion.&n; */
DECL|function|rkt_sync_cmd
r_static
r_int
id|rkt_sync_cmd
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
id|u32
id|command
comma
id|u32
id|p1
comma
id|u32
op_star
id|status
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
r_int
id|ok
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Write the command into Mailbox 0&n;&t; */
id|rkt_writel
c_func
(paren
id|dev
comma
id|InboundMailbox0
comma
id|cpu_to_le32
c_func
(paren
id|command
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Write the parameters into Mailboxes 1 - 4&n;&t; */
id|rkt_writel
c_func
(paren
id|dev
comma
id|InboundMailbox1
comma
id|cpu_to_le32
c_func
(paren
id|p1
)paren
)paren
suffix:semicolon
id|rkt_writel
c_func
(paren
id|dev
comma
id|InboundMailbox2
comma
l_int|0
)paren
suffix:semicolon
id|rkt_writel
c_func
(paren
id|dev
comma
id|InboundMailbox3
comma
l_int|0
)paren
suffix:semicolon
id|rkt_writel
c_func
(paren
id|dev
comma
id|InboundMailbox4
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Clear the synch command doorbell to start on a clean slate.&n;&t; */
id|rkt_writel
c_func
(paren
id|dev
comma
id|OutboundDoorbellReg
comma
id|OUTBOUNDDOORBELL_0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Disable doorbell interrupts&n;&t; */
id|rkt_writeb
c_func
(paren
id|dev
comma
id|MUnit.OIMR
comma
id|dev-&gt;OIMR
op_or_assign
l_int|0x04
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Force the completion of the mask register write before issuing&n;&t; *&t;the interrupt.&n;&t; */
id|rkt_readb
(paren
id|dev
comma
id|MUnit.OIMR
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Signal that there is a new synch command&n;&t; */
id|rkt_writel
c_func
(paren
id|dev
comma
id|InboundDoorbellReg
comma
id|INBOUNDDOORBELL_0
)paren
suffix:semicolon
id|ok
op_assign
l_int|0
suffix:semicolon
id|start
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Wait up to 30 seconds&n;&t; */
r_while
c_loop
(paren
id|time_before
c_func
(paren
id|jiffies
comma
id|start
op_plus
l_int|30
op_star
id|HZ
)paren
)paren
(brace
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Delay 5 microseconds to let Mon960 get info. */
multiline_comment|/*&n;&t;&t; *&t;Mon960 will set doorbell0 bit when it has completed the command.&n;&t;&t; */
r_if
c_cond
(paren
id|rkt_readl
c_func
(paren
id|dev
comma
id|OutboundDoorbellReg
)paren
op_amp
id|OUTBOUNDDOORBELL_0
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; *&t;Clear the doorbell.&n;&t;&t;&t; */
id|rkt_writel
c_func
(paren
id|dev
comma
id|OutboundDoorbellReg
comma
id|OUTBOUNDDOORBELL_0
)paren
suffix:semicolon
id|ok
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; *&t;Yield the processor in case we are slow &n;&t;&t; */
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ok
op_ne
l_int|1
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;Restore interrupt mask even though we timed out&n;&t;&t; */
id|rkt_writeb
c_func
(paren
id|dev
comma
id|MUnit.OIMR
comma
id|dev-&gt;OIMR
op_and_assign
l_int|0xfb
)paren
suffix:semicolon
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Pull the synch status from Mailbox 0.&n;&t; */
op_star
id|status
op_assign
id|le32_to_cpu
c_func
(paren
id|rkt_readl
c_func
(paren
id|dev
comma
id|IndexRegs.Mailbox
(braket
l_int|0
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Clear the synch command doorbell.&n;&t; */
id|rkt_writel
c_func
(paren
id|dev
comma
id|OutboundDoorbellReg
comma
id|OUTBOUNDDOORBELL_0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Restore interrupt mask&n;&t; */
id|rkt_writeb
c_func
(paren
id|dev
comma
id|MUnit.OIMR
comma
id|dev-&gt;OIMR
op_and_assign
l_int|0xfb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_rkt_interrupt_adapter&t;-&t;interrupt adapter&n; *&t;@dev: Adapter&n; *&n; *&t;Send an interrupt to the i960 and breakpoint it.&n; */
DECL|function|aac_rkt_interrupt_adapter
r_static
r_void
id|aac_rkt_interrupt_adapter
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
(brace
id|u32
id|ret
suffix:semicolon
id|rkt_sync_cmd
c_func
(paren
id|dev
comma
id|BREAKPOINT_REQUEST
comma
l_int|0
comma
op_amp
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_rkt_notify_adapter&t;&t;-&t;send an event to the adapter&n; *&t;@dev: Adapter&n; *&t;@event: Event to send&n; *&n; *&t;Notify the i960 that something it probably cares about has&n; *&t;happened.&n; */
DECL|function|aac_rkt_notify_adapter
r_static
r_void
id|aac_rkt_notify_adapter
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
id|u32
id|event
)paren
(brace
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|AdapNormCmdQue
suffix:colon
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.IDR
comma
id|INBOUNDDOORBELL_1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HostNormRespNotFull
suffix:colon
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.IDR
comma
id|INBOUNDDOORBELL_4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapNormRespQue
suffix:colon
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.IDR
comma
id|INBOUNDDOORBELL_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HostNormCmdNotFull
suffix:colon
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.IDR
comma
id|INBOUNDDOORBELL_3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HostShutdown
suffix:colon
singleline_comment|//&t;&t;rkt_sync_cmd(dev, HOST_CRASHING, 0, 0, 0, 0, &amp;ret);
r_break
suffix:semicolon
r_case
id|FastIo
suffix:colon
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.IDR
comma
id|INBOUNDDOORBELL_6
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapPrintfDone
suffix:colon
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.IDR
comma
id|INBOUNDDOORBELL_5
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;aac_rkt_start_adapter&t;&t;-&t;activate adapter&n; *&t;@dev:&t;Adapter&n; *&n; *&t;Start up processing on an i960 based AAC adapter&n; */
DECL|function|aac_rkt_start_adapter
r_static
r_void
id|aac_rkt_start_adapter
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
(brace
id|u32
id|status
suffix:semicolon
r_struct
id|aac_init
op_star
id|init
suffix:semicolon
id|init
op_assign
id|dev-&gt;init
suffix:semicolon
id|init-&gt;HostElapsedSeconds
op_assign
id|cpu_to_le32
c_func
(paren
id|get_seconds
c_func
(paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Tell the adapter we are back and up and running so it will scan&n;&t; *&t;its command queues and enable our interrupts&n;&t; */
id|dev-&gt;irq_mask
op_assign
(paren
id|DoorBellPrintfReady
op_or
id|OUTBOUNDDOORBELL_1
op_or
id|OUTBOUNDDOORBELL_2
op_or
id|OUTBOUNDDOORBELL_3
op_or
id|OUTBOUNDDOORBELL_4
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;First clear out all interrupts.  Then enable the one&squot;s that we&n;&t; *&t;can handle.&n;&t; */
id|rkt_writeb
c_func
(paren
id|dev
comma
id|MUnit.OIMR
comma
l_int|0xff
)paren
suffix:semicolon
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.ODR
comma
l_int|0xffffffff
)paren
suffix:semicolon
singleline_comment|//&t;rkt_writeb(dev, MUnit.OIMR, ~(u8)OUTBOUND_DOORBELL_INTERRUPT_MASK);
id|rkt_writeb
c_func
(paren
id|dev
comma
id|MUnit.OIMR
comma
id|dev-&gt;OIMR
op_assign
l_int|0xfb
)paren
suffix:semicolon
singleline_comment|// We can only use a 32 bit address here
id|rkt_sync_cmd
c_func
(paren
id|dev
comma
id|INIT_STRUCT_BASE_ADDRESS
comma
(paren
id|u32
)paren
(paren
id|ulong
)paren
id|dev-&gt;init_pa
comma
op_amp
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_rkt_check_health&n; *&t;@dev: device to check if healthy&n; *&n; *&t;Will attempt to determine if the specified adapter is alive and&n; *&t;capable of handling requests, returning 0 if alive.&n; */
DECL|function|aac_rkt_check_health
r_static
r_int
id|aac_rkt_check_health
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
(brace
r_int
id|status
op_assign
id|rkt_readl
c_func
(paren
id|dev
comma
id|IndexRegs.Mailbox
(braket
l_int|7
)braket
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check to see if the board failed any self tests.&n;&t; */
r_if
c_cond
(paren
id|status
op_amp
id|SELF_TEST_FAILED
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Check to see if the board panic&squot;d.&n;&t; */
r_if
c_cond
(paren
id|status
op_amp
id|KERNEL_PANIC
)paren
(brace
r_char
op_star
id|buffer
op_assign
id|kmalloc
c_func
(paren
l_int|512
comma
id|GFP_KERNEL
op_or
id|__GFP_DMA
)paren
suffix:semicolon
r_struct
id|POSTSTATUS
(brace
id|u32
id|Post_Command
suffix:semicolon
id|u32
id|Post_Address
suffix:semicolon
)brace
op_star
id|post
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|POSTSTATUS
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|dma_addr_t
id|paddr
op_assign
id|pci_map_single
c_func
(paren
id|dev-&gt;pdev
comma
id|post
comma
r_sizeof
(paren
r_struct
id|POSTSTATUS
)paren
comma
l_int|2
)paren
suffix:semicolon
id|dma_addr_t
id|baddr
op_assign
id|pci_map_single
c_func
(paren
id|dev-&gt;pdev
comma
id|buffer
comma
l_int|512
comma
l_int|1
)paren
suffix:semicolon
id|u32
id|status
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|ret
op_assign
op_minus
l_int|2
suffix:semicolon
id|memset
c_func
(paren
id|buffer
comma
l_int|0
comma
l_int|512
)paren
suffix:semicolon
id|post-&gt;Post_Command
op_assign
id|cpu_to_le32
c_func
(paren
id|COMMAND_POST_RESULTS
)paren
suffix:semicolon
id|post-&gt;Post_Address
op_assign
id|cpu_to_le32
c_func
(paren
id|baddr
)paren
suffix:semicolon
id|rkt_writel
c_func
(paren
id|dev
comma
id|MUnit.IMRx
(braket
l_int|0
)braket
comma
id|cpu_to_le32
c_func
(paren
id|paddr
)paren
)paren
suffix:semicolon
id|rkt_sync_cmd
c_func
(paren
id|dev
comma
id|COMMAND_POST_RESULTS
comma
id|baddr
comma
op_amp
id|status
)paren
suffix:semicolon
id|pci_unmap_single
c_func
(paren
id|dev-&gt;pdev
comma
id|paddr
comma
r_sizeof
(paren
r_struct
id|POSTSTATUS
)paren
comma
l_int|2
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|post
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|buffer
(braket
l_int|0
)braket
op_eq
l_char|&squot;0&squot;
)paren
op_logical_and
(paren
id|buffer
(braket
l_int|1
)braket
op_eq
l_char|&squot;x&squot;
)paren
)paren
(brace
id|ret
op_assign
(paren
id|buffer
(braket
l_int|2
)braket
op_le
l_char|&squot;9&squot;
)paren
ques
c_cond
(paren
id|buffer
(braket
l_int|2
)braket
op_minus
l_char|&squot;0&squot;
)paren
suffix:colon
(paren
id|buffer
(braket
l_int|2
)braket
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
)paren
suffix:semicolon
id|ret
op_lshift_assign
l_int|4
suffix:semicolon
id|ret
op_add_assign
(paren
id|buffer
(braket
l_int|3
)braket
op_le
l_char|&squot;9&squot;
)paren
ques
c_cond
(paren
id|buffer
(braket
l_int|3
)braket
op_minus
l_char|&squot;0&squot;
)paren
suffix:colon
(paren
id|buffer
(braket
l_int|3
)braket
op_minus
l_char|&squot;A&squot;
op_plus
l_int|10
)paren
suffix:semicolon
)brace
id|pci_unmap_single
c_func
(paren
id|dev-&gt;pdev
comma
id|baddr
comma
l_int|512
comma
l_int|1
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buffer
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Wait for the adapter to be up and running.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
(paren
id|status
op_amp
id|KERNEL_UP_AND_RUNNING
)paren
)paren
r_return
op_minus
l_int|3
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Everything is OK&n;&t; */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_rkt_init&t;-&t;initialize an i960 based AAC card&n; *&t;@dev: device to configure&n; *&n; *&t;Allocate and set up resources for the i960 based AAC variants. The &n; *&t;device_interface in the commregion will be allocated and linked &n; *&t;to the comm region.&n; */
DECL|function|aac_rkt_init
r_int
id|aac_rkt_init
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
r_int
r_int
id|status
suffix:semicolon
r_int
id|instance
suffix:semicolon
r_const
r_char
op_star
id|name
suffix:semicolon
id|instance
op_assign
id|dev-&gt;id
suffix:semicolon
id|name
op_assign
id|dev-&gt;name
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Map in the registers from the adapter.&n;&t; */
r_if
c_cond
(paren
(paren
id|dev-&gt;regs.rkt
op_assign
(paren
r_struct
id|rkt_registers
op_star
)paren
id|ioremap
c_func
(paren
(paren
r_int
r_int
)paren
id|dev-&gt;scsi_host_ptr-&gt;base
comma
l_int|8192
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;aacraid: unable to map i960.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Check to see if the board failed any self tests.&n;&t; */
r_if
c_cond
(paren
id|rkt_readl
c_func
(paren
id|dev
comma
id|MUnit.OMRx
(braket
l_int|0
)braket
)paren
op_amp
id|SELF_TEST_FAILED
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s%d: adapter self-test failed.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|instance
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Check to see if the monitor panic&squot;d while booting.&n;&t; */
r_if
c_cond
(paren
id|rkt_readl
c_func
(paren
id|dev
comma
id|MUnit.OMRx
(braket
l_int|0
)braket
)paren
op_amp
id|MONITOR_PANIC
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s%d: adapter monitor panic.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|instance
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Check to see if the board panic&squot;d while booting.&n;&t; */
r_if
c_cond
(paren
id|rkt_readl
c_func
(paren
id|dev
comma
id|MUnit.OMRx
(braket
l_int|0
)braket
)paren
op_amp
id|KERNEL_PANIC
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s%d: adapter kernel panic&squot;d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|instance
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|start
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Wait for the adapter to be up and running. Wait up to 3 minutes&n;&t; */
r_while
c_loop
(paren
op_logical_neg
(paren
id|rkt_readl
c_func
(paren
id|dev
comma
id|MUnit.OMRx
(braket
l_int|0
)braket
)paren
op_amp
id|KERNEL_UP_AND_RUNNING
)paren
)paren
(brace
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|start
op_plus
l_int|180
op_star
id|HZ
)paren
)paren
(brace
id|status
op_assign
id|rkt_readl
c_func
(paren
id|dev
comma
id|IndexRegs.Mailbox
(braket
l_int|7
)braket
)paren
op_rshift
l_int|16
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s%d: adapter kernel failed to start, init status = %ld.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|instance
comma
id|status
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|set_current_state
c_func
(paren
id|TASK_UNINTERRUPTIBLE
)paren
suffix:semicolon
id|schedule_timeout
c_func
(paren
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;scsi_host_ptr-&gt;irq
comma
id|aac_rkt_intr
comma
id|SA_SHIRQ
op_or
id|SA_INTERRUPT
comma
l_string|&quot;aacraid&quot;
comma
(paren
r_void
op_star
)paren
id|dev
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s%d: Interrupt unavailable.&bslash;n&quot;
comma
id|name
comma
id|instance
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Fill in the function dispatch table.&n;&t; */
id|dev-&gt;a_ops.adapter_interrupt
op_assign
id|aac_rkt_interrupt_adapter
suffix:semicolon
id|dev-&gt;a_ops.adapter_enable_int
op_assign
id|aac_rkt_enable_interrupt
suffix:semicolon
id|dev-&gt;a_ops.adapter_disable_int
op_assign
id|aac_rkt_disable_interrupt
suffix:semicolon
id|dev-&gt;a_ops.adapter_notify
op_assign
id|aac_rkt_notify_adapter
suffix:semicolon
id|dev-&gt;a_ops.adapter_sync_cmd
op_assign
id|rkt_sync_cmd
suffix:semicolon
id|dev-&gt;a_ops.adapter_check_health
op_assign
id|aac_rkt_check_health
suffix:semicolon
r_if
c_cond
(paren
id|aac_init_adapter
c_func
(paren
id|dev
)paren
op_eq
l_int|NULL
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Start any kernel threads needed&n;&t; */
id|dev-&gt;thread_pid
op_assign
id|kernel_thread
c_func
(paren
(paren
r_int
(paren
op_star
)paren
(paren
r_void
op_star
)paren
)paren
id|aac_command_thread
comma
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;thread_pid
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;aacraid: Unable to create rkt thread.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;Tell the adapter that all is configured, and it can start&n;&t; *&t;accepting requests&n;&t; */
id|aac_rkt_start_adapter
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
