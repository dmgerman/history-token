multiline_comment|/*&n; * Copyright (C) 2001, 2002 Jens Axboe &lt;axboe@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * Support for the DMA queued protocol, which enables ATA disk drives to&n; * use tagged command queueing.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/io.h&gt;
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
multiline_comment|/*&n; * we are leaving the SERVICE interrupt alone, IBM drives have it&n; * on per default and it can&squot;t be turned off. Doesn&squot;t matter, this&n; * is the sane config.&n; */
DECL|macro|IDE_TCQ_FIDDLE_SI
macro_line|#undef IDE_TCQ_FIDDLE_SI
id|ide_startstop_t
id|ide_dmaq_intr
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
id|ide_startstop_t
id|ide_service
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
DECL|function|drive_ctl_nien
r_static
r_inline
r_void
id|drive_ctl_nien
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_int
id|set
)paren
(brace
macro_line|#ifdef IDE_TCQ_NIEN
r_if
c_cond
(paren
id|IDE_CONTROL_REG
)paren
(brace
r_int
id|mask
op_assign
id|set
ques
c_cond
l_int|0x02
suffix:colon
l_int|0x00
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
id|drive-&gt;ctl
op_or
id|mask
comma
id|IDE_CONTROL_REG
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|ide_tcq_nop_handler
r_static
id|ide_startstop_t
id|ide_tcq_nop_handler
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_task_t
op_star
id|args
op_assign
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|rq-&gt;special
suffix:semicolon
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_int
id|auto_poll_check
op_assign
l_int|0
suffix:semicolon
id|u8
id|stat
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
id|args-&gt;tfRegister
(braket
id|IDE_FEATURE_OFFSET
)braket
op_amp
l_int|0x01
)paren
id|auto_poll_check
op_assign
l_int|1
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
id|stat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|IDE_STATUS_REG
)paren
suffix:semicolon
id|err
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|IDE_ERROR_REG
)paren
suffix:semicolon
id|ide_end_drive_cmd
c_func
(paren
id|drive
comma
id|stat
comma
id|err
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * do taskfile and check ABRT bit -- intelligent adapters will not&n;&t; * pass NOP with sub-code 0x01 to device, so the command will not&n;&t; * fail there&n;&t; */
r_if
c_cond
(paren
id|auto_poll_check
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|args-&gt;tfRegister
(braket
id|IDE_FEATURE_OFFSET
)braket
op_amp
id|ABRT_ERR
)paren
)paren
(brace
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|auto_poll
op_assign
l_int|1
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: NOP Auto-poll enabled&bslash;n&quot;
comma
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|name
)paren
suffix:semicolon
)brace
)brace
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
multiline_comment|/*&n; * if we encounter _any_ error doing I/O to one of the tags, we must&n; * invalidate the pending queue. clear the software busy queue and requeue&n; * on the request queue for restart. issue a WIN_NOP to clear hardware queue&n; */
DECL|function|ide_tcq_invalidate_queue
r_static
r_void
id|ide_tcq_invalidate_queue
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_hwgroup_t
op_star
id|hwgroup
op_assign
id|HWGROUP
c_func
(paren
id|drive
)paren
suffix:semicolon
id|request_queue_t
op_star
id|q
op_assign
op_amp
id|drive-&gt;queue
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
l_string|&quot;%s: invalidating tag queue (%d commands)&bslash;n&quot;
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
multiline_comment|/*&n;&t; * first kill timer and block queue&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
id|del_timer
c_func
(paren
op_amp
id|hwgroup-&gt;timer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|dma
)paren
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|ide_dma_end
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
id|hwgroup-&gt;busy
op_assign
l_int|0
suffix:semicolon
id|hwgroup-&gt;handler
op_assign
l_int|NULL
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * now kill hardware queue with a NOP&n;&t; */
id|rq
op_assign
op_amp
id|hwgroup-&gt;wrq
suffix:semicolon
id|ide_init_drive_cmd
c_func
(paren
id|rq
)paren
suffix:semicolon
id|rq-&gt;buffer
op_assign
id|hwgroup-&gt;cmd_buf
suffix:semicolon
id|memset
c_func
(paren
id|rq-&gt;buffer
comma
l_int|0
comma
r_sizeof
(paren
id|hwgroup-&gt;cmd_buf
)paren
)paren
suffix:semicolon
id|rq-&gt;buffer
(braket
l_int|0
)braket
op_assign
id|WIN_NOP
suffix:semicolon
id|ide_do_drive_cmd
c_func
(paren
id|drive
comma
id|rq
comma
id|ide_preempt
)paren
suffix:semicolon
)brace
DECL|function|ide_tcq_intr_timeout
r_void
id|ide_tcq_intr_timeout
c_func
(paren
r_int
r_int
id|data
)paren
(brace
id|ide_drive_t
op_star
id|drive
op_assign
(paren
id|ide_drive_t
op_star
)paren
id|data
suffix:semicolon
id|ide_hwgroup_t
op_star
id|hwgroup
op_assign
id|HWGROUP
c_func
(paren
id|drive
)paren
suffix:semicolon
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ide_tcq_intr_timeout: timeout waiting for %s interrupt&bslash;n&quot;
comma
id|hwgroup-&gt;rq
ques
c_cond
l_string|&quot;completion&quot;
suffix:colon
l_string|&quot;service&quot;
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwgroup-&gt;busy
)paren
id|printk
c_func
(paren
l_string|&quot;ide_tcq_intr_timeout: hwgroup not busy&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hwgroup-&gt;handler
op_eq
l_int|NULL
)paren
id|printk
c_func
(paren
l_string|&quot;ide_tcq_intr_timeout: missing isr!&bslash;n&quot;
)paren
suffix:semicolon
id|hwgroup-&gt;busy
op_assign
l_int|1
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
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
)paren
(brace
id|u8
id|stat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|IDE_STATUS_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|stat
op_amp
id|SRV_STAT
)paren
op_logical_and
(paren
id|ide_service
c_func
(paren
id|drive
)paren
op_eq
id|ide_started
)paren
)paren
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|drive
)paren
id|ide_tcq_invalidate_queue
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
DECL|function|__ide_tcq_set_intr
r_void
id|__ide_tcq_set_intr
c_func
(paren
id|ide_hwgroup_t
op_star
id|hwgroup
comma
id|ide_handler_t
op_star
id|handler
)paren
(brace
multiline_comment|/*&n;&t; * always just bump the timer for now, the timeout handling will&n;&t; * have to be changed to be per-command&n;&t; */
id|hwgroup-&gt;timer.function
op_assign
id|ide_tcq_intr_timeout
suffix:semicolon
id|hwgroup-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|hwgroup-&gt;drive
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|hwgroup-&gt;timer
comma
id|jiffies
op_plus
l_int|5
op_star
id|HZ
)paren
suffix:semicolon
id|hwgroup-&gt;handler
op_assign
id|handler
suffix:semicolon
)brace
DECL|function|ide_tcq_set_intr
r_void
id|ide_tcq_set_intr
c_func
(paren
id|ide_hwgroup_t
op_star
id|hwgroup
comma
id|ide_handler_t
op_star
id|handler
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
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
id|__ide_tcq_set_intr
c_func
(paren
id|hwgroup
comma
id|handler
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * wait 400ns, then poll for busy_mask to clear from alt status&n; */
DECL|macro|IDE_TCQ_WAIT
mdefine_line|#define IDE_TCQ_WAIT&t;(10000)
DECL|function|ide_tcq_wait_altstat
r_int
id|ide_tcq_wait_altstat
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|byte
op_star
id|stat
comma
id|byte
id|busy_mask
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
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
r_do
(brace
op_star
id|stat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|IDE_ALTSTATUS_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
op_star
id|stat
op_amp
id|busy_mask
)paren
)paren
r_break
suffix:semicolon
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
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * issue SERVICE command to drive -- drive must have been selected first,&n; * and it must have reported a need for service (status has SRV_STAT set)&n; *&n; * Also, nIEN must be set as not to need protection against ide_dmaq_intr&n; */
DECL|function|ide_service
id|ide_startstop_t
id|ide_service
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|request
op_star
id|rq
suffix:semicolon
id|byte
id|feat
comma
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
multiline_comment|/*&n;&t; * could be called with IDE_DMA in-progress from invalidate&n;&t; * handler, refuse to do anything&n;&t; */
r_if
c_cond
(paren
id|hwif-&gt;dma
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
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|drive
)paren
(brace
id|SELECT_DRIVE
c_func
(paren
id|drive
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
id|drive_ctl_nien
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * send SERVICE, wait 400ns, wait for BUSY_STAT to clear&n;&t; */
id|hwif
op_member_access_from_pointer
id|OUTB
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
id|ide_tcq_wait_altstat
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
id|printk
c_func
(paren
l_string|&quot;ide_service: BUSY clear took too long&bslash;n&quot;
)paren
suffix:semicolon
id|ide_dump_status
c_func
(paren
id|drive
comma
l_string|&quot;ide_service&quot;
comma
id|stat
)paren
suffix:semicolon
id|ide_tcq_invalidate_queue
c_func
(paren
id|drive
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
id|drive_ctl_nien
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * FIXME, invalidate queue&n;&t; */
r_if
c_cond
(paren
id|stat
op_amp
id|ERR_STAT
)paren
(brace
id|ide_dump_status
c_func
(paren
id|drive
comma
l_string|&quot;ide_service&quot;
comma
id|stat
)paren
suffix:semicolon
id|ide_tcq_invalidate_queue
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
id|feat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|IDE_NSECTOR_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|feat
op_amp
id|REL
)paren
(brace
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|rq
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
l_string|&quot;ide_service: stat %x, feat %x&bslash;n&quot;
comma
id|stat
comma
id|feat
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rq
op_assign
id|blk_queue_find_tag
c_func
(paren
op_amp
id|drive-&gt;queue
comma
id|tag
)paren
)paren
)paren
(brace
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|rq
op_assign
id|rq
suffix:semicolon
multiline_comment|/*&n;&t;&t; * we&squot;ll start a dma read or write, device will trigger&n;&t;&t; * interrupt to indicate end of transfer, release is not&n;&t;&t; * allowed&n;&t;&t; */
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;ide_service: starting command, stat=%x&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|ide_dma_queued_start
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;ide_service: missing request for tag %d&bslash;n&quot;
comma
id|tag
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
DECL|function|ide_check_service
id|ide_startstop_t
id|ide_check_service
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
id|byte
id|stat
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: ide_check_service&bslash;n&quot;
comma
id|drive-&gt;name
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
id|stat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|IDE_STATUS_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|SRV_STAT
)paren
r_return
id|ide_service
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * we have pending commands, wait for interrupt&n;&t; */
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: wait for service interrupt&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
id|ide_tcq_set_intr
c_func
(paren
id|HWGROUP
c_func
(paren
id|drive
)paren
comma
id|ide_dmaq_intr
)paren
suffix:semicolon
r_return
id|ide_started
suffix:semicolon
)brace
DECL|function|ide_dmaq_complete
id|ide_startstop_t
id|ide_dmaq_complete
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
r_struct
id|request
op_star
id|rq
comma
id|byte
id|stat
)paren
(brace
id|byte
id|dma_stat
suffix:semicolon
multiline_comment|/*&n;&t; * transfer was in progress, stop DMA engine&n;&t; */
id|dma_stat
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|ide_dma_end
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * must be end of I/O, check status and complete as necessary&n;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
op_logical_neg
id|OK_STAT
c_func
(paren
id|stat
comma
id|READY_STAT
comma
id|drive-&gt;bad_wstat
op_or
id|DRQ_STAT
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide_dmaq_intr: %s: error status %x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|stat
)paren
suffix:semicolon
id|ide_dump_status
c_func
(paren
id|drive
comma
l_string|&quot;ide_dmaq_complete&quot;
comma
id|stat
)paren
suffix:semicolon
id|ide_tcq_invalidate_queue
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
l_string|&quot;ide_dmaq_complete: ending %p, tag %d&bslash;n&quot;
comma
id|rq
comma
id|rq-&gt;tag
)paren
suffix:semicolon
id|ide_end_request
c_func
(paren
id|drive
comma
l_int|1
comma
id|rq-&gt;nr_sectors
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * we completed this command, check if we can service a new command&n;&t; */
r_return
id|ide_check_service
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * intr handler for queued dma operations. this can be entered for two&n; * reasons:&n; *&n; * 1) device has completed dma transfer&n; * 2) service request to start a command&n; *&n; * if the drive has an active tag, we first complete that request before&n; * processing any pending SERVICE.&n; */
DECL|function|ide_dmaq_intr
id|ide_startstop_t
id|ide_dmaq_intr
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_struct
id|request
op_star
id|rq
op_assign
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|rq
suffix:semicolon
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
id|byte
id|stat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|IDE_STATUS_REG
)paren
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;ide_dmaq_intr: stat=%x&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * if a command completion interrupt is pending, do that first and&n;&t; * check service afterwards&n;&t; */
r_if
c_cond
(paren
id|rq
)paren
(brace
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;ide_dmaq_intr: completion&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ide_dmaq_complete
c_func
(paren
id|drive
comma
id|rq
comma
id|stat
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * service interrupt&n;&t; */
r_if
c_cond
(paren
id|stat
op_amp
id|SRV_STAT
)paren
(brace
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;ide_dmaq_intr: SERV (stat=%x)&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
r_return
id|ide_service
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;ide_dmaq_intr: stat=%x, not expected&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
r_return
id|ide_check_service
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * check if the ata adapter this drive is attached to supports the&n; * NOP auto-poll for multiple tcq enabled drives on one channel&n; */
DECL|function|ide_tcq_check_autopoll
r_static
r_int
id|ide_tcq_check_autopoll
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_task_t
op_star
id|args
suffix:semicolon
r_int
id|i
comma
id|drives
suffix:semicolon
multiline_comment|/*&n;&t; * only need to probe if both drives on a channel support tcq&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|drives
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
id|HWIF
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|drives
(braket
id|i
)braket
dot
id|present
op_logical_and
id|drive-&gt;media
op_eq
id|ide_disk
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
multiline_comment|/*&n;&t; * what a mess...&n;&t; */
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
r_return
l_int|1
suffix:semicolon
id|memset
c_func
(paren
id|args
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|args
)paren
)paren
suffix:semicolon
id|args-&gt;tfRegister
(braket
id|IDE_FEATURE_OFFSET
)braket
op_assign
l_int|0x01
suffix:semicolon
id|args-&gt;tfRegister
(braket
id|IDE_COMMAND_OFFSET
)braket
op_assign
id|WIN_NOP
suffix:semicolon
id|args-&gt;command_type
op_assign
id|ide_cmd_type_parser
c_func
(paren
id|args
)paren
suffix:semicolon
id|args-&gt;handler
op_assign
id|ide_tcq_nop_handler
suffix:semicolon
r_return
id|ide_raw_taskfile
c_func
(paren
id|drive
comma
id|args
comma
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * configure the drive for tcq&n; */
DECL|function|ide_tcq_configure
r_static
r_int
id|ide_tcq_configure
c_func
(paren
id|ide_drive_t
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
id|ide_task_t
op_star
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|args
comma
l_int|0
comma
r_sizeof
(paren
id|ide_task_t
)paren
)paren
suffix:semicolon
id|args-&gt;tfRegister
(braket
id|IDE_COMMAND_OFFSET
)braket
op_assign
id|WIN_SETFEATURES
suffix:semicolon
id|args-&gt;tfRegister
(braket
id|IDE_FEATURE_OFFSET
)braket
op_assign
id|SETFEATURES_EN_WCACHE
suffix:semicolon
id|args-&gt;command_type
op_assign
id|ide_cmd_type_parser
c_func
(paren
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
id|args
comma
l_int|NULL
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
r_goto
id|err
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * disable RELease interrupt, it&squot;s quicker to poll this after&n;&t; * having sent the command opcode&n;&t; */
id|memset
c_func
(paren
id|args
comma
l_int|0
comma
r_sizeof
(paren
id|ide_task_t
)paren
)paren
suffix:semicolon
id|args-&gt;tfRegister
(braket
id|IDE_COMMAND_OFFSET
)braket
op_assign
id|WIN_SETFEATURES
suffix:semicolon
id|args-&gt;tfRegister
(braket
id|IDE_FEATURE_OFFSET
)braket
op_assign
id|SETFEATURES_DIS_RI
suffix:semicolon
id|args-&gt;command_type
op_assign
id|ide_cmd_type_parser
c_func
(paren
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
id|args
comma
l_int|NULL
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
r_goto
id|err
suffix:semicolon
)brace
macro_line|#ifdef IDE_TCQ_FIDDLE_SI
multiline_comment|/*&n;&t; * enable SERVICE interrupt&n;&t; */
id|memset
c_func
(paren
id|args
comma
l_int|0
comma
r_sizeof
(paren
id|ide_task_t
)paren
)paren
suffix:semicolon
id|args-&gt;tfRegister
(braket
id|IDE_COMMAND_OFFSET
)braket
op_assign
id|WIN_SETFEATURES
suffix:semicolon
id|args-&gt;tfRegister
(braket
id|IDE_FEATURE_OFFSET
)braket
op_assign
id|SETFEATURES_EN_SI
suffix:semicolon
id|args-&gt;command_type
op_assign
id|ide_cmd_type_parser
c_func
(paren
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
id|args
comma
l_int|NULL
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
r_goto
id|err
suffix:semicolon
)brace
macro_line|#endif
id|kfree
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
id|kfree
c_func
(paren
id|args
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * for now assume that command list is always as big as we need and don&squot;t&n; * attempt to shrink it on tcq disable&n; */
DECL|function|ide_enable_queued
r_static
r_int
id|ide_enable_queued
c_func
(paren
id|ide_drive_t
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
id|ide_tcq_configure
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
id|ide_tcq_check_autopoll
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
DECL|function|ide_tcq_wait_dataphase
r_int
id|ide_tcq_wait_dataphase
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
id|byte
id|stat
suffix:semicolon
r_int
id|i
suffix:semicolon
r_do
(brace
id|stat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|IDE_STATUS_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|stat
op_amp
id|BUSY_STAT
)paren
)paren
r_break
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|OK_STAT
c_func
(paren
id|stat
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
r_do
(brace
id|stat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|IDE_STATUS_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|OK_STAT
c_func
(paren
id|stat
comma
id|READY_STAT
op_or
id|DRQ_STAT
comma
id|drive-&gt;bad_wstat
)paren
)paren
r_break
suffix:semicolon
op_increment
id|i
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|i
op_ge
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
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|__ide_dma_queued_on
r_int
id|__ide_dma_queued_on
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|drive-&gt;using_dma
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|ata_pending_commands
c_func
(paren
id|drive
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide-tcq; can&squot;t toggle tcq feature on busy drive&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|ide_enable_queued
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|__ide_dma_queued_off
r_int
id|__ide_dma_queued_off
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_if
c_cond
(paren
id|ata_pending_commands
c_func
(paren
id|drive
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide-tcq; can&squot;t toggle tcq feature on busy drive&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
id|ide_enable_queued
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|ide_dma_queued_rw
r_static
id|ide_startstop_t
id|ide_dma_queued_rw
c_func
(paren
id|ide_drive_t
op_star
id|drive
comma
id|u8
id|command
)paren
(brace
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|byte
id|stat
comma
id|feat
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: starting tag&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * set nIEN, tag start operation will enable again when&n;&t; * it is safe&n;&t; */
id|drive_ctl_nien
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;%s: sending cmd=%x&bslash;n&quot;
comma
id|drive-&gt;name
comma
id|command
)paren
suffix:semicolon
id|hwif
op_member_access_from_pointer
id|OUTB
c_func
(paren
id|command
comma
id|IDE_COMMAND_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ide_tcq_wait_altstat
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
id|printk
c_func
(paren
l_string|&quot;%s: alt stat timeout&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|drive_ctl_nien
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|ERR_STAT
)paren
r_goto
id|err
suffix:semicolon
multiline_comment|/*&n;&t; * bus not released, start dma&n;&t; */
id|feat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|IDE_NSECTOR_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|feat
op_amp
id|REL
)paren
)paren
(brace
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;IMMED in queued_start, feat=%x&bslash;n&quot;
comma
id|feat
)paren
suffix:semicolon
r_return
id|hwif
op_member_access_from_pointer
id|ide_dma_queued_start
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * drive released the bus, clear active request and check for service&n;&t; */
id|spin_lock_irqsave
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|rq
op_assign
l_int|NULL
suffix:semicolon
id|__ide_tcq_set_intr
c_func
(paren
id|HWGROUP
c_func
(paren
id|drive
)paren
comma
id|ide_dmaq_intr
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;REL in queued_start&bslash;n&quot;
)paren
suffix:semicolon
id|stat
op_assign
id|hwif
op_member_access_from_pointer
id|INB
c_func
(paren
id|IDE_STATUS_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
id|stat
op_amp
id|SRV_STAT
)paren
r_return
id|ide_service
c_func
(paren
id|drive
)paren
suffix:semicolon
r_return
id|ide_released
suffix:semicolon
id|err
suffix:colon
id|ide_dump_status
c_func
(paren
id|drive
comma
l_string|&quot;rw_queued&quot;
comma
id|stat
)paren
suffix:semicolon
id|ide_tcq_invalidate_queue
c_func
(paren
id|drive
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
DECL|function|__ide_dma_queued_read
id|ide_startstop_t
id|__ide_dma_queued_read
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|u8
id|command
op_assign
id|WIN_READDMA_QUEUED
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;addressing
op_eq
l_int|1
)paren
id|command
op_assign
id|WIN_READDMA_QUEUED_EXT
suffix:semicolon
r_return
id|ide_dma_queued_rw
c_func
(paren
id|drive
comma
id|command
)paren
suffix:semicolon
)brace
DECL|function|__ide_dma_queued_write
id|ide_startstop_t
id|__ide_dma_queued_write
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|u8
id|command
op_assign
id|WIN_WRITEDMA_QUEUED
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;addressing
op_eq
l_int|1
)paren
id|command
op_assign
id|WIN_WRITEDMA_QUEUED_EXT
suffix:semicolon
r_return
id|ide_dma_queued_rw
c_func
(paren
id|drive
comma
id|command
)paren
suffix:semicolon
)brace
DECL|function|__ide_dma_queued_start
id|ide_startstop_t
id|__ide_dma_queued_start
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|ide_hwgroup_t
op_star
id|hwgroup
op_assign
id|HWGROUP
c_func
(paren
id|drive
)paren
suffix:semicolon
r_struct
id|request
op_star
id|rq
op_assign
id|hwgroup-&gt;rq
suffix:semicolon
id|ide_hwif_t
op_star
id|hwif
op_assign
id|HWIF
c_func
(paren
id|drive
)paren
suffix:semicolon
r_int
r_int
id|reading
op_assign
l_int|0
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;ide_dma: setting up queued tag=%d&bslash;n&quot;
comma
id|rq-&gt;tag
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwgroup-&gt;busy
)paren
id|printk
c_func
(paren
l_string|&quot;queued_rw: hwgroup not busy&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ide_tcq_wait_dataphase
c_func
(paren
id|drive
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;timeout waiting for data phase&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
r_if
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|rq
)paren
op_eq
id|READ
)paren
id|reading
op_assign
l_int|1
op_lshift
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|ide_start_dma
c_func
(paren
id|hwif
comma
id|drive
comma
id|reading
)paren
)paren
r_return
id|ide_stopped
suffix:semicolon
id|ide_tcq_set_intr
c_func
(paren
id|hwgroup
comma
id|ide_dmaq_intr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hwif
op_member_access_from_pointer
id|ide_dma_begin
c_func
(paren
id|drive
)paren
)paren
r_return
id|ide_started
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
eof
