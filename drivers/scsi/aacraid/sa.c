multiline_comment|/*&n; *&t;Adaptec AAC series RAID controller driver&n; *&t;(c) Copyright 2001 Red Hat Inc.&t;&lt;alan@redhat.com&gt;&n; *&n; * based on the old aacraid driver that is..&n; * Adaptec aacraid device driver for Linux.&n; *&n; * Copyright (c) 2000 Adaptec, Inc. (aacraid@adaptec.com)&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2, or (at your option)&n; * any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; see the file COPYING.  If not, write to&n; * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; * Module Name:&n; *  sa.c&n; *&n; * Abstract: Drawbridge specific support functions&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/blk.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &quot;scsi.h&quot;
macro_line|#include &quot;hosts.h&quot;
macro_line|#include &quot;aacraid.h&quot;
DECL|function|aac_sa_intr
r_static
id|irqreturn_t
id|aac_sa_intr
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
id|intstat
comma
id|mask
suffix:semicolon
id|intstat
op_assign
id|sa_readw
c_func
(paren
id|dev
comma
id|DoorbellReg_p
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Read mask and invert because drawbridge is reversed.&n;&t; *&t;This allows us to only service interrupts that have been enabled.&n;&t; */
id|mask
op_assign
op_complement
(paren
id|sa_readw
c_func
(paren
id|dev
comma
id|SaDbCSR.PRISETIRQMASK
)paren
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
r_if
c_cond
(paren
id|intstat
op_amp
id|PrintfReady
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
id|sa_readl
c_func
(paren
id|dev
comma
id|Mailbox5
)paren
)paren
)paren
suffix:semicolon
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellClrReg_p
comma
id|PrintfReady
)paren
suffix:semicolon
multiline_comment|/* clear PrintfReady */
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellReg_s
comma
id|PrintfDone
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|intstat
op_amp
id|DOORBELL_1
)paren
(brace
singleline_comment|// dev -&gt; Host Normal Command Ready
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
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellClrReg_p
comma
id|DOORBELL_1
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|intstat
op_amp
id|DOORBELL_2
)paren
(brace
singleline_comment|// dev -&gt; Host Normal Response Ready
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
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellClrReg_p
comma
id|DOORBELL_2
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|intstat
op_amp
id|DOORBELL_3
)paren
(brace
singleline_comment|// dev -&gt; Host Normal Command Not Full
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellClrReg_p
comma
id|DOORBELL_3
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|intstat
op_amp
id|DOORBELL_4
)paren
(brace
singleline_comment|// dev -&gt; Host Normal Response Not Full
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellClrReg_p
comma
id|DOORBELL_4
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
multiline_comment|/**&n; *&t;aac_sa_enable_interrupt&t;-&t;enable an interrupt event&n; *&t;@dev: Which adapter to enable.&n; *&t;@event: Which adapter event.&n; *&n; *&t;This routine will enable the corresponding adapter event to cause an interrupt on &n; * &t;the host.&n; */
DECL|function|aac_sa_enable_interrupt
r_void
id|aac_sa_enable_interrupt
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
id|sa_writew
c_func
(paren
id|dev
comma
id|SaDbCSR.PRICLEARIRQMASK
comma
id|DOORBELL_1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HostNormRespQue
suffix:colon
id|sa_writew
c_func
(paren
id|dev
comma
id|SaDbCSR.PRICLEARIRQMASK
comma
id|DOORBELL_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapNormCmdNotFull
suffix:colon
id|sa_writew
c_func
(paren
id|dev
comma
id|SaDbCSR.PRICLEARIRQMASK
comma
id|DOORBELL_3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapNormRespNotFull
suffix:colon
id|sa_writew
c_func
(paren
id|dev
comma
id|SaDbCSR.PRICLEARIRQMASK
comma
id|DOORBELL_4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;aac_sa_disable_interrupt&t;-&t;disable an interrupt event&n; *&t;@dev: Which adapter to enable.&n; *&t;@event: Which adapter event.&n; *&n; *&t;This routine will enable the corresponding adapter event to cause an interrupt on &n; * &t;the host.&n; */
DECL|function|aac_sa_disable_interrupt
r_void
id|aac_sa_disable_interrupt
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
id|sa_writew
c_func
(paren
id|dev
comma
id|SaDbCSR.PRISETIRQMASK
comma
id|DOORBELL_1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HostNormRespQue
suffix:colon
id|sa_writew
c_func
(paren
id|dev
comma
id|SaDbCSR.PRISETIRQMASK
comma
id|DOORBELL_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapNormCmdNotFull
suffix:colon
id|sa_writew
c_func
(paren
id|dev
comma
id|SaDbCSR.PRISETIRQMASK
comma
id|DOORBELL_3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapNormRespNotFull
suffix:colon
id|sa_writew
c_func
(paren
id|dev
comma
id|SaDbCSR.PRISETIRQMASK
comma
id|DOORBELL_4
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/**&n; *&t;aac_sa_notify_adapter&t;&t;-&t;handle adapter notification&n; *&t;@dev:&t;Adapter that notification is for&n; *&t;@event:&t;Event to notidy&n; *&n; *&t;Notify the adapter of an event&n; */
DECL|function|aac_sa_notify_adapter
r_void
id|aac_sa_notify_adapter
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
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellReg_s
comma
id|DOORBELL_1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HostNormRespNotFull
suffix:colon
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellReg_s
comma
id|DOORBELL_4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapNormRespQue
suffix:colon
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellReg_s
comma
id|DOORBELL_2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HostNormCmdNotFull
suffix:colon
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellReg_s
comma
id|DOORBELL_3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HostShutdown
suffix:colon
singleline_comment|//sa_sync_cmd(dev, HOST_CRASHING, 0, &amp;ret);
r_break
suffix:semicolon
r_case
id|FastIo
suffix:colon
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellReg_s
comma
id|DOORBELL_6
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AdapPrintfDone
suffix:colon
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellReg_s
comma
id|DOORBELL_5
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
multiline_comment|/**&n; *&t;sa_sync_cmd&t;-&t;send a command and wait&n; *&t;@dev: Adapter&n; *&t;@command: Command to execute&n; *&t;@p1: first parameter&n; *&t;@ret: adapter status&n; *&n; *&t;This routine will send a synchronous comamnd to the adapter and wait &n; *&t;for its&t;completion.&n; */
DECL|function|sa_sync_cmd
r_static
r_int
id|sa_sync_cmd
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
id|ret
)paren
(brace
r_int
r_int
id|start
suffix:semicolon
r_int
id|ok
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Write the Command into Mailbox 0&n;&t; */
id|sa_writel
c_func
(paren
id|dev
comma
id|Mailbox0
comma
id|cpu_to_le32
c_func
(paren
id|command
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Write the parameters into Mailboxes 1 - 4&n;&t; */
id|sa_writel
c_func
(paren
id|dev
comma
id|Mailbox1
comma
id|cpu_to_le32
c_func
(paren
id|p1
)paren
)paren
suffix:semicolon
id|sa_writel
c_func
(paren
id|dev
comma
id|Mailbox2
comma
l_int|0
)paren
suffix:semicolon
id|sa_writel
c_func
(paren
id|dev
comma
id|Mailbox3
comma
l_int|0
)paren
suffix:semicolon
id|sa_writel
c_func
(paren
id|dev
comma
id|Mailbox4
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Clear the synch command doorbell to start on a clean slate.&n;&t; */
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellClrReg_p
comma
id|DOORBELL_0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Signal that there is a new synch command&n;&t; */
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellReg_s
comma
id|DOORBELL_0
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
multiline_comment|/*&n;&t;&t; *&t;Delay 5uS so that the monitor gets access&n;&t;&t; */
id|udelay
c_func
(paren
l_int|5
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; *&t;Mon110 will set doorbell0 bit when it has &n;&t;&t; *&t;completed the command.&n;&t;&t; */
r_if
c_cond
(paren
id|sa_readw
c_func
(paren
id|dev
comma
id|DoorbellReg_p
)paren
op_amp
id|DOORBELL_0
)paren
(brace
id|ok
op_assign
l_int|1
suffix:semicolon
r_break
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
id|ok
op_ne
l_int|1
)paren
r_return
op_minus
id|ETIMEDOUT
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Clear the synch command doorbell.&n;&t; */
id|sa_writew
c_func
(paren
id|dev
comma
id|DoorbellClrReg_p
comma
id|DOORBELL_0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Pull the synch status from Mailbox 0.&n;&t; */
op_star
id|ret
op_assign
id|le32_to_cpu
c_func
(paren
id|sa_readl
c_func
(paren
id|dev
comma
id|Mailbox0
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_sa_interrupt_adapter&t;-&t;interrupt an adapter&n; *&t;@dev: Which adapter to enable.&n; *&n; *&t;Breakpoint an adapter.&n; */
DECL|function|aac_sa_interrupt_adapter
r_static
r_void
id|aac_sa_interrupt_adapter
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
id|sa_sync_cmd
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
multiline_comment|/**&n; *&t;aac_sa_start_adapter&t;&t;-&t;activate adapter&n; *&t;@dev:&t;Adapter&n; *&n; *&t;Start up processing on an ARM based AAC adapter&n; */
DECL|function|aac_sa_start_adapter
r_static
r_void
id|aac_sa_start_adapter
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
r_struct
id|aac_init
op_star
id|init
suffix:semicolon
multiline_comment|/*&n;&t; * Fill in the remaining pieces of the init.&n;&t; */
id|init
op_assign
id|dev-&gt;init
suffix:semicolon
id|init-&gt;HostElapsedSeconds
op_assign
id|cpu_to_le32
c_func
(paren
id|jiffies
op_div
id|HZ
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;INIT&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Tell the adapter we are back and up and running so it will scan its command&n;&t; * queues and enable our interrupts&n;&t; */
id|dev-&gt;irq_mask
op_assign
(paren
id|PrintfReady
op_or
id|DOORBELL_1
op_or
id|DOORBELL_2
op_or
id|DOORBELL_3
op_or
id|DOORBELL_4
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;First clear out all interrupts.  Then enable the one&squot;s that &n;&t; *&t;we can handle.&n;&t; */
id|dprintk
c_func
(paren
(paren
l_string|&quot;MASK&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|sa_writew
c_func
(paren
id|dev
comma
id|SaDbCSR.PRISETIRQMASK
comma
id|cpu_to_le16
c_func
(paren
l_int|0xffff
)paren
)paren
suffix:semicolon
id|sa_writew
c_func
(paren
id|dev
comma
id|SaDbCSR.PRICLEARIRQMASK
comma
(paren
id|PrintfReady
op_or
id|DOORBELL_1
op_or
id|DOORBELL_2
op_or
id|DOORBELL_3
op_or
id|DOORBELL_4
)paren
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;SYNCCMD&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* We can only use a 32 bit address here */
id|sa_sync_cmd
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
id|ret
)paren
suffix:semicolon
)brace
multiline_comment|/**&n; *&t;aac_sa_init&t;-&t;initialize an ARM based AAC card&n; *&t;@dev: device to configure&n; *&t;@devnum: adapter number&n; *&n; *&t;Allocate and set up resources for the ARM based AAC variants. The &n; *&t;device_interface in the commregion will be allocated and linked &n; *&t;to the comm region.&n; */
DECL|function|aac_sa_init
r_int
id|aac_sa_init
c_func
(paren
r_struct
id|aac_dev
op_star
id|dev
comma
r_int
r_int
id|devnum
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
id|dev-&gt;devnum
op_assign
id|devnum
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;PREINST&bslash;n&quot;
)paren
)paren
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
id|dprintk
c_func
(paren
(paren
l_string|&quot;PREMAP&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev-&gt;regs.sa
op_assign
(paren
r_struct
id|sa_registers
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
l_string|&quot;aacraid: unable to map ARM.&bslash;n&quot;
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
id|sa_readl
c_func
(paren
id|dev
comma
id|Mailbox7
)paren
op_amp
id|SELF_TEST_FAILED
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s%d: adapter self-test failed.&bslash;n&quot;
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
multiline_comment|/*&n;&t; *&t;Check to see if the board panic&squot;d while booting.&n;&t; */
r_if
c_cond
(paren
id|sa_readl
c_func
(paren
id|dev
comma
id|Mailbox7
)paren
op_amp
id|KERNEL_PANIC
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s%d: adapter kernel panic&squot;d.&bslash;n&quot;
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
id|start
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Wait for the adapter to be up and running. Wait up to 3 minutes.&n;&t; */
r_while
c_loop
(paren
op_logical_neg
(paren
id|sa_readl
c_func
(paren
id|dev
comma
id|Mailbox7
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
id|start
op_plus
l_int|180
op_star
id|HZ
comma
id|jiffies
)paren
)paren
(brace
id|status
op_assign
id|sa_readl
c_func
(paren
id|dev
comma
id|Mailbox7
)paren
op_rshift
l_int|16
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s%d: adapter kernel failed to start, init status = %d.&bslash;n&quot;
comma
id|name
comma
id|instance
comma
id|le32_to_cpu
c_func
(paren
id|status
)paren
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
id|dprintk
c_func
(paren
(paren
l_string|&quot;ATIRQ&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;scsi_host_ptr-&gt;irq
comma
id|aac_sa_intr
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
id|KERN_WARNING
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
id|aac_sa_interrupt_adapter
suffix:semicolon
id|dev-&gt;a_ops.adapter_enable_int
op_assign
id|aac_sa_enable_interrupt
suffix:semicolon
id|dev-&gt;a_ops.adapter_disable_int
op_assign
id|aac_sa_disable_interrupt
suffix:semicolon
id|dev-&gt;a_ops.adapter_notify
op_assign
id|aac_sa_notify_adapter
suffix:semicolon
id|dev-&gt;a_ops.adapter_sync_cmd
op_assign
id|sa_sync_cmd
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;FUNCDONE&bslash;n&quot;
)paren
)paren
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
(brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|dprintk
c_func
(paren
(paren
l_string|&quot;NEWADAPTDONE&bslash;n&quot;
)paren
)paren
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
multiline_comment|/*&n;&t; *&t;Tell the adapter that all is configure, and it can start &n;&t; *&t;accepting requests&n;&t; */
id|dprintk
c_func
(paren
(paren
l_string|&quot;STARTING&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|aac_sa_start_adapter
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dprintk
c_func
(paren
(paren
l_string|&quot;STARTED&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
