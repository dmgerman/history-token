multiline_comment|/*&n; * Copyright (C) 2001, 2002 Jens Axboe &lt;axboe@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * Support for the DMA queued protocol, which enables ATA disk drives to&n; * use tagged command queueing.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
multiline_comment|/*&n; * warning: it will be _very_ verbose if defined&n; */
DECL|macro|IDE_TCQ_DEBUG
macro_line|#undef IDE_TCQ_DEBUG
macro_line|#ifdef IDE_TCQ_DEBUG
DECL|macro|TCQ_PRINTK
mdefine_line|#define TCQ_PRINTK printk
macro_line|#else
DECL|macro|TCQ_PRINTK
mdefine_line|#define TCQ_PRINTK(x...)
macro_line|#endif
multiline_comment|/*&n; * use nIEN or not&n; */
DECL|macro|IDE_TCQ_NIEN
macro_line|#undef IDE_TCQ_NIEN
multiline_comment|/*&n; * We are leaving the SERVICE interrupt alone, IBM drives have it&n; * on per default and it can&squot;t be turned off. Doesn&squot;t matter, this&n; * is the sane config.&n; */
DECL|macro|IDE_TCQ_FIDDLE_SI
macro_line|#undef IDE_TCQ_FIDDLE_SI
r_static
id|ide_startstop_t
id|ide_dmaq_intr
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
suffix:semicolon
r_static
id|ide_startstop_t
id|service
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
suffix:semicolon
DECL|function|tcq_nop_handler
r_static
id|ide_startstop_t
id|tcq_nop_handler
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
r_struct
id|ata_taskfile
op_star
id|args
op_assign
id|rq-&gt;special
suffix:semicolon
id|ide__sti
c_func
(paren
)paren
suffix:semicolon
id|ide_end_drive_cmd
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
multiline_comment|/*&n; * If we encounter _any_ error doing I/O to one of the tags, we must&n; * invalidate the pending queue. Clear the software busy queue and requeue&n; * on the request queue for restart. Issue a WIN_NOP to clear hardware queue.&n; */
DECL|function|tcq_invalidate_queue
r_static
r_void
id|tcq_invalidate_queue
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
id|request_queue_t
op_star
id|q
op_assign
op_amp
id|drive-&gt;queue
suffix:semicolon
r_struct
id|ata_taskfile
op_star
id|args
suffix:semicolon
r_struct
id|request
op_star
id|rq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ATA: %s: invalidating pending queue (%d)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|ata_pending_commands
c_func
(paren
id|drive
)paren
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|ch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|ch-&gt;timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|IDE_DMA
comma
id|ch-&gt;active
)paren
)paren
id|udma_stop
c_func
(paren
id|drive
)paren
suffix:semicolon
id|blk_queue_invalidate_tags
c_func
(paren
id|q
)paren
suffix:semicolon
id|drive-&gt;using_tcq
op_assign
l_int|0
suffix:semicolon
id|drive-&gt;queue_depth
op_assign
l_int|1
suffix:semicolon
id|clear_bit
c_func
(paren
id|IDE_BUSY
comma
id|ch-&gt;active
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|IDE_DMA
comma
id|ch-&gt;active
)paren
suffix:semicolon
id|ch-&gt;handler
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Do some internal stuff -- we really need this command to be&n;&t; * executed before any new commands are started. issue a NOP&n;&t; * to clear internal queue on drive.&n;&t; */
id|args
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|args
)paren
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|args
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ATA: %s: failed to issue NOP&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|rq
op_assign
id|blk_get_request
c_func
(paren
op_amp
id|drive-&gt;queue
comma
id|READ
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rq
)paren
id|rq
op_assign
id|blk_get_request
c_func
(paren
op_amp
id|drive-&gt;queue
comma
id|WRITE
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * blk_queue_invalidate_tags() just added back at least one command&n;&t; * to the free list, so there _must_ be at least one free.&n;&t; */
id|BUG_ON
c_func
(paren
op_logical_neg
id|rq
)paren
suffix:semicolon
id|rq-&gt;special
op_assign
id|args
suffix:semicolon
id|args-&gt;cmd
op_assign
id|WIN_NOP
suffix:semicolon
id|args-&gt;handler
op_assign
id|tcq_nop_handler
suffix:semicolon
id|args-&gt;command_type
op_assign
id|IDE_DRIVE_TASK_NO_DATA
suffix:semicolon
id|rq-&gt;rq_dev
op_assign
id|mk_kdev
c_func
(paren
id|drive-&gt;channel-&gt;major
comma
(paren
id|drive-&gt;select.b.unit
)paren
op_lshift
id|PARTN_BITS
)paren
suffix:semicolon
id|_elv_add_request
c_func
(paren
id|q
comma
id|rq
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|out
suffix:colon
macro_line|#ifdef IDE_TCQ_NIEN
id|ata_irq_enable
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * start doing stuff again&n;&t; */
id|q
op_member_access_from_pointer
id|request_fn
c_func
(paren
id|q
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|ch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;ATA: tcq_invalidate_queue: done&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|ata_tcq_irq_timeout
r_static
r_void
id|ata_tcq_irq_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
r_struct
id|ata_device
op_star
id|drive
op_assign
(paren
r_struct
id|ata_device
op_star
)paren
id|data
suffix:semicolon
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ATA: %s: timeout waiting for interrupt...&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|ch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|test_and_set_bit
c_func
(paren
id|IDE_BUSY
comma
id|ch-&gt;active
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ATA: %s: IRQ handler not busy&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;handler
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ATA: %s: missing ISR!&bslash;n&quot;
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|ch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * if pending commands, try service before giving up&n;&t; */
r_if
c_cond
(paren
id|ata_pending_commands
c_func
(paren
id|drive
)paren
op_logical_and
op_logical_neg
id|ata_status
c_func
(paren
id|drive
comma
l_int|0
comma
id|SERVICE_STAT
)paren
)paren
r_if
c_cond
(paren
id|service
c_func
(paren
id|drive
comma
id|drive-&gt;rq
)paren
op_eq
id|ide_started
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|drive
)paren
id|tcq_invalidate_queue
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|set_irq
r_static
r_void
id|set_irq
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|ata_handler_t
op_star
id|handler
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
id|ch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * always just bump the timer for now, the timeout handling will&n;&t; * have to be changed to be per-command&n;&t; *&n;&t; * FIXME: Jens - this is broken it will interfere with&n;&t; * the normal timer function on serialized drives!&n;&t; */
id|ch-&gt;timer.function
op_assign
id|ata_tcq_irq_timeout
suffix:semicolon
id|ch-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|ch-&gt;drive
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|ch-&gt;timer
comma
id|jiffies
op_plus
l_int|5
op_star
id|HZ
)paren
suffix:semicolon
id|ch-&gt;handler
op_assign
id|handler
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
id|ch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * wait 400ns, then poll for busy_mask to clear from alt status&n; */
DECL|macro|IDE_TCQ_WAIT
mdefine_line|#define IDE_TCQ_WAIT&t;(10000)
DECL|function|wait_altstat
r_static
r_int
id|wait_altstat
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|u8
op_star
id|stat
comma
id|u8
id|busy_mask
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|stat
op_assign
id|GET_ALTSTAT
c_func
(paren
)paren
)paren
op_amp
id|busy_mask
)paren
(brace
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|i
op_increment
OG
id|IDE_TCQ_WAIT
)paren
)paren
r_return
l_int|1
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_static
id|ide_startstop_t
id|udma_tcq_start
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
suffix:semicolon
multiline_comment|/*&n; * issue SERVICE command to drive -- drive must have been selected first,&n; * and it must have reported a need for service (status has SERVICE_STAT set)&n; *&n; * Also, nIEN must be set as not to need protection against ide_dmaq_intr&n; */
DECL|function|service
r_static
id|ide_startstop_t
id|service
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
id|u8
id|feat
suffix:semicolon
id|u8
id|stat
suffix:semicolon
r_int
id|tag
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: started service&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Could be called with IDE_DMA in-progress from invalidate&n;&t; * handler, refuse to do anything.&n;&t; */
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|IDE_DMA
comma
id|drive-&gt;channel-&gt;active
)paren
)paren
r_return
id|ide_stopped
suffix:semicolon
multiline_comment|/*&n;&t; * need to select the right drive first...&n;&t; */
r_if
c_cond
(paren
id|drive
op_ne
id|drive-&gt;channel-&gt;drive
)paren
id|ata_select
c_func
(paren
id|drive
comma
l_int|10
)paren
suffix:semicolon
macro_line|#ifdef IDE_TCQ_NIEN
id|ata_irq_enable
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * send SERVICE, wait 400ns, wait for BUSY_STAT to clear&n;&t; */
id|OUT_BYTE
c_func
(paren
id|WIN_QUEUED_SERVICE
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_altstat
c_func
(paren
id|drive
comma
op_amp
id|stat
comma
id|BUSY_STAT
)paren
)paren
(brace
id|ata_dump
c_func
(paren
id|drive
comma
id|rq
comma
l_string|&quot;BUSY clear took too long&quot;
)paren
suffix:semicolon
id|tcq_invalidate_queue
c_func
(paren
id|drive
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
macro_line|#ifdef IDE_TCQ_NIEN
id|ata_irq_enable
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * FIXME, invalidate queue&n;&t; */
r_if
c_cond
(paren
id|stat
op_amp
id|ERR_STAT
)paren
(brace
id|ata_dump
c_func
(paren
id|drive
comma
id|rq
comma
l_string|&quot;ERR condition&quot;
)paren
suffix:semicolon
id|tcq_invalidate_queue
c_func
(paren
id|drive
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * should not happen, a buggy device could introduce loop&n;&t; */
r_if
c_cond
(paren
(paren
id|feat
op_assign
id|GET_FEAT
c_func
(paren
)paren
)paren
op_amp
id|NSEC_REL
)paren
(brace
id|drive-&gt;rq
op_assign
l_int|NULL
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: release in service&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
id|tag
op_assign
id|feat
op_rshift
l_int|3
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: stat %x, feat %x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|stat
comma
id|feat
)paren
suffix:semicolon
id|rq
op_assign
id|blk_queue_tag_request
c_func
(paren
op_amp
id|drive-&gt;queue
comma
id|tag
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rq
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: missing request for tag %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|tag
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
id|drive-&gt;rq
op_assign
id|rq
suffix:semicolon
multiline_comment|/*&n;&t; * we&squot;ll start a dma read or write, device will trigger&n;&t; * interrupt to indicate end of transfer, release is not allowed&n;&t; */
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: starting command %x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|stat
)paren
suffix:semicolon
r_return
id|udma_tcq_start
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
)brace
DECL|function|check_service
r_static
id|ide_startstop_t
id|check_service
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: %s&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|__FUNCTION__
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ata_pending_commands
c_func
(paren
id|drive
)paren
)paren
r_return
id|ide_stopped
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ata_status
c_func
(paren
id|drive
comma
l_int|0
comma
id|SERVICE_STAT
)paren
)paren
r_return
id|service
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * we have pending commands, wait for interrupt&n;&t; */
id|set_irq
c_func
(paren
id|drive
comma
id|ide_dmaq_intr
)paren
suffix:semicolon
r_return
id|ide_started
suffix:semicolon
)brace
DECL|function|dmaq_complete
r_static
id|ide_startstop_t
id|dmaq_complete
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
id|u8
id|dma_stat
suffix:semicolon
multiline_comment|/*&n;&t; * transfer was in progress, stop DMA engine&n;&t; */
id|dma_stat
op_assign
id|udma_stop
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * must be end of I/O, check status and complete as necessary&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ata_status
c_func
(paren
id|drive
comma
id|READY_STAT
comma
id|drive-&gt;bad_wstat
op_or
id|DRQ_STAT
)paren
)paren
(brace
id|ata_dump
c_func
(paren
id|drive
comma
id|rq
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|tcq_invalidate_queue
c_func
(paren
id|drive
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dma_stat
)paren
id|printk
c_func
(paren
l_string|&quot;%s: bad DMA status (dma_stat=%x)&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|dma_stat
)paren
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: ending %p, tag %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|rq
comma
id|rq-&gt;tag
)paren
suffix:semicolon
id|__ide_end_request
c_func
(paren
id|drive
comma
id|rq
comma
op_logical_neg
id|dma_stat
comma
id|rq-&gt;nr_sectors
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * we completed this command, check if we can service a new command&n;&t; */
r_return
id|check_service
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Interrupt handler for queued dma operations. this can be entered for two&n; * reasons:&n; *&n; * 1) device has completed dma transfer&n; * 2) service request to start a command&n; *&n; * if the drive has an active tag, we first complete that request before&n; * processing any pending SERVICE.&n; */
DECL|function|ide_dmaq_intr
r_static
id|ide_startstop_t
id|ide_dmaq_intr
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
r_int
id|ok
suffix:semicolon
id|ok
op_assign
op_logical_neg
id|ata_status
c_func
(paren
id|drive
comma
l_int|0
comma
id|SERVICE_STAT
)paren
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: stat=%x&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|drive-&gt;status
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If a command completion interrupt is pending, do that first and&n;&t; * check service afterwards.&n;&t; */
r_if
c_cond
(paren
id|rq
)paren
r_return
id|dmaq_complete
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * service interrupt&n;&t; */
r_if
c_cond
(paren
id|ok
)paren
(brace
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: SERV (stat=%x)&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|drive-&gt;status
)paren
suffix:semicolon
r_return
id|service
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;%s: stat=%x, not expected&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|drive-&gt;status
)paren
suffix:semicolon
r_return
id|check_service
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Check if the ata adapter this drive is attached to supports the&n; * NOP auto-poll for multiple tcq enabled drives on one channel.&n; */
DECL|function|check_autopoll
r_static
r_int
id|check_autopoll
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_struct
id|ata_taskfile
id|args
suffix:semicolon
r_int
id|drives
op_assign
l_int|0
comma
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * only need to probe if both drives on a channel support tcq&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_DRIVES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;drives
(braket
id|i
)braket
dot
id|present
op_logical_and
id|drive-&gt;type
op_eq
id|ATA_DISK
)paren
id|drives
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|drives
op_le
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|args
comma
l_int|0
comma
r_sizeof
(paren
id|args
)paren
)paren
suffix:semicolon
id|args.taskfile.feature
op_assign
l_int|0x01
suffix:semicolon
id|args.cmd
op_assign
id|WIN_NOP
suffix:semicolon
id|ide_cmd_type_parser
c_func
(paren
op_amp
id|args
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * do taskfile and check ABRT bit -- intelligent adapters will not&n;&t; * pass NOP with sub-code 0x01 to device, so the command will not&n;&t; * fail there&n;&t; */
id|ide_raw_taskfile
c_func
(paren
id|drive
comma
op_amp
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|args.taskfile.feature
op_amp
id|ABRT_ERR
)paren
r_return
l_int|1
suffix:semicolon
id|ch-&gt;auto_poll
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: NOP Auto-poll enabled&bslash;n&quot;
comma
id|ch-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * configure the drive for tcq&n; */
DECL|function|configure_tcq
r_static
r_int
id|configure_tcq
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_int
id|tcq_mask
op_assign
l_int|1
op_lshift
l_int|1
op_or
l_int|1
op_lshift
l_int|14
suffix:semicolon
r_int
id|tcq_bits
op_assign
id|tcq_mask
op_or
l_int|1
op_lshift
l_int|15
suffix:semicolon
r_struct
id|ata_taskfile
id|args
suffix:semicolon
multiline_comment|/*&n;&t; * bit 14 and 1 must be set in word 83 of the device id to indicate&n;&t; * support for dma queued protocol, and bit 15 must be cleared&n;&t; */
r_if
c_cond
(paren
(paren
id|drive-&gt;id-&gt;command_set_2
op_amp
id|tcq_bits
)paren
op_xor
id|tcq_mask
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|args
comma
l_int|0
comma
r_sizeof
(paren
id|args
)paren
)paren
suffix:semicolon
id|args.taskfile.feature
op_assign
id|SETFEATURES_EN_WCACHE
suffix:semicolon
id|args.cmd
op_assign
id|WIN_SETFEATURES
suffix:semicolon
id|ide_cmd_type_parser
c_func
(paren
op_amp
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ide_raw_taskfile
c_func
(paren
id|drive
comma
op_amp
id|args
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: failed to enable write cache&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * disable RELease interrupt, it&squot;s quicker to poll this after&n;&t; * having sent the command opcode&n;&t; */
id|memset
c_func
(paren
op_amp
id|args
comma
l_int|0
comma
r_sizeof
(paren
id|args
)paren
)paren
suffix:semicolon
id|args.taskfile.feature
op_assign
id|SETFEATURES_DIS_RI
suffix:semicolon
id|args.cmd
op_assign
id|WIN_SETFEATURES
suffix:semicolon
id|ide_cmd_type_parser
c_func
(paren
op_amp
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ide_raw_taskfile
c_func
(paren
id|drive
comma
op_amp
id|args
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: disabling release interrupt fail&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef IDE_TCQ_FIDDLE_SI
multiline_comment|/*&n;&t; * enable SERVICE interrupt&n;&t; */
id|memset
c_func
(paren
op_amp
id|args
comma
l_int|0
comma
r_sizeof
(paren
id|args
)paren
)paren
suffix:semicolon
id|args.taskfile.feature
op_assign
id|SETFEATURES_EN_SI
suffix:semicolon
id|args.cmd
op_assign
id|WIN_SETFEATURES
suffix:semicolon
id|ide_cmd_type_parser
c_func
(paren
op_amp
id|args
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ide_raw_taskfile
c_func
(paren
id|drive
comma
op_amp
id|args
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: enabling service interrupt fail&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tcq_wait_dataphase
r_static
r_int
id|tcq_wait_dataphase
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
)paren
(brace
r_int
id|i
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|ata_status
c_func
(paren
id|drive
comma
l_int|0
comma
id|BUSY_STAT
)paren
)paren
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ata_status
c_func
(paren
id|drive
comma
id|READY_STAT
op_or
id|DRQ_STAT
comma
id|drive-&gt;bad_wstat
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|ata_status
c_func
(paren
id|drive
comma
id|READY_STAT
op_or
id|DRQ_STAT
comma
id|drive-&gt;bad_wstat
)paren
)paren
(brace
op_increment
id|i
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|IDE_TCQ_WAIT
)paren
r_return
l_int|1
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; * UDMA transfer handling functions.&n; */
multiline_comment|/*&n; * Invoked from a SERVICE interrupt, command etc already known.  Just need to&n; * start the dma engine for this tag.&n; */
DECL|function|udma_tcq_start
r_static
id|ide_startstop_t
id|udma_tcq_start
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: setting up queued %d&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|rq-&gt;tag
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|IDE_BUSY
comma
id|ch-&gt;active
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;queued_rw: IDE_BUSY not set&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tcq_wait_dataphase
c_func
(paren
id|drive
)paren
)paren
r_return
id|ide_stopped
suffix:semicolon
r_if
c_cond
(paren
id|ata_start_dma
c_func
(paren
id|drive
comma
id|rq
)paren
)paren
r_return
id|ide_stopped
suffix:semicolon
id|set_irq
c_func
(paren
id|drive
comma
id|ide_dmaq_intr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|udma_start
c_func
(paren
id|drive
comma
id|rq
)paren
)paren
r_return
id|ide_started
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
multiline_comment|/*&n; * Start a queued command from scratch.&n; */
DECL|function|udma_tcq_taskfile
id|ide_startstop_t
id|udma_tcq_taskfile
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
)paren
(brace
id|u8
id|stat
suffix:semicolon
id|u8
id|feat
suffix:semicolon
r_struct
id|ata_taskfile
op_star
id|args
op_assign
id|rq-&gt;special
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: start tag %d&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|rq-&gt;tag
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * set nIEN, tag start operation will enable again when&n;&t; * it is safe&n;&t; */
macro_line|#ifdef IDE_TCQ_NIEN
id|ata_irq_enable
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
macro_line|#endif
id|OUT_BYTE
c_func
(paren
id|args-&gt;cmd
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|wait_altstat
c_func
(paren
id|drive
comma
op_amp
id|stat
comma
id|BUSY_STAT
)paren
)paren
(brace
id|ata_dump
c_func
(paren
id|drive
comma
id|rq
comma
l_string|&quot;queued start&quot;
)paren
suffix:semicolon
id|tcq_invalidate_queue
c_func
(paren
id|drive
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
macro_line|#ifdef IDE_TCQ_NIEN
id|ata_irq_enable
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|stat
op_amp
id|ERR_STAT
)paren
(brace
id|ata_dump
c_func
(paren
id|drive
comma
id|rq
comma
l_string|&quot;tcq_start&quot;
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * drive released the bus, clear active tag and&n;&t; * check for service&n;&t; */
r_if
c_cond
(paren
(paren
id|feat
op_assign
id|GET_FEAT
c_func
(paren
)paren
)paren
op_amp
id|NSEC_REL
)paren
(brace
id|drive-&gt;immed_rel
op_increment
suffix:semicolon
id|drive-&gt;rq
op_assign
l_int|NULL
suffix:semicolon
id|set_irq
c_func
(paren
id|drive
comma
id|ide_dmaq_intr
)paren
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;REL in queued_start&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ata_status
c_func
(paren
id|drive
comma
l_int|0
comma
id|SERVICE_STAT
)paren
)paren
r_return
id|service
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
r_return
id|ide_released
suffix:semicolon
)brace
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;IMMED in queued_start&bslash;n&quot;
)paren
suffix:semicolon
id|drive-&gt;immed_comp
op_increment
suffix:semicolon
r_return
id|udma_tcq_start
c_func
(paren
id|drive
comma
id|rq
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * For now assume that command list is always as big as we need and don&squot;t&n; * attempt to shrink it on tcq disable.&n; */
DECL|function|udma_tcq_enable
r_int
id|udma_tcq_enable
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
id|on
)paren
(brace
r_int
id|depth
op_assign
id|drive-&gt;using_tcq
ques
c_cond
id|drive-&gt;queue_depth
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * disable or adjust queue depth&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|on
)paren
(brace
r_if
c_cond
(paren
id|drive-&gt;using_tcq
)paren
id|printk
c_func
(paren
l_string|&quot;%s: TCQ disabled&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
id|drive-&gt;using_tcq
op_assign
l_int|0
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|configure_tcq
c_func
(paren
id|drive
)paren
)paren
(brace
id|drive-&gt;using_tcq
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * enable block tagging&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|blk_queue_tagged
c_func
(paren
op_amp
id|drive-&gt;queue
)paren
)paren
id|blk_queue_init_tags
c_func
(paren
op_amp
id|drive-&gt;queue
comma
id|IDE_MAX_TAG
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * check auto-poll support&n;&t; */
id|check_autopoll
c_func
(paren
id|drive
)paren
suffix:semicolon
r_if
c_cond
(paren
id|depth
op_ne
id|drive-&gt;queue_depth
)paren
id|printk
c_func
(paren
l_string|&quot;%s: tagged command queueing enabled, command queue depth %d&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|drive-&gt;queue_depth
)paren
suffix:semicolon
id|drive-&gt;using_tcq
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* FIXME: This should go away! */
DECL|variable|udma_tcq_enable
id|EXPORT_SYMBOL
c_func
(paren
id|udma_tcq_enable
)paren
suffix:semicolon
eof
