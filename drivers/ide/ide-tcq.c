multiline_comment|/*&n; * Copyright (C) 2001, 2002 Jens Axboe &lt;axboe@suse.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
multiline_comment|/*&n; * Support for the DMA queued protocol, which enables ATA disk drives to&n; * use tagged command queueing.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/delay.h&gt;
multiline_comment|/*&n; * warning: it will be _very_ verbose if set to 1&n; */
macro_line|#if 0
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
r_int
id|ide_tcq_end
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
suffix:semicolon
id|ide_startstop_t
id|ide_dmaq_intr
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
id|clear
)paren
(brace
macro_line|#ifdef IDE_TCQ_NIEN
r_int
id|mask
op_assign
id|clear
ques
c_cond
l_int|0
suffix:colon
l_int|2
suffix:semicolon
r_if
c_cond
(paren
id|IDE_CONTROL_REG
)paren
id|OUT_BYTE
c_func
(paren
id|drive-&gt;ctl
op_or
id|mask
comma
id|IDE_CONTROL_REG
)paren
suffix:semicolon
macro_line|#endif
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
id|request_queue_t
op_star
id|q
op_assign
op_amp
id|drive-&gt;queue
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_struct
id|ata_request
op_star
id|ar
suffix:semicolon
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: invalidating pending queue&bslash;n&quot;
comma
id|drive-&gt;name
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
id|del_timer
c_func
(paren
op_amp
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|timer
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * assume oldest commands have the higher tags... doesn&squot;t matter&n;&t; * much. shove requests back into request queue.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|drive-&gt;queue_depth
op_minus
l_int|1
suffix:semicolon
id|i
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|ar
op_assign
id|drive-&gt;tcq-&gt;ar
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ar
)paren
r_continue
suffix:semicolon
id|ar-&gt;ar_rq-&gt;special
op_assign
l_int|NULL
suffix:semicolon
id|ar-&gt;ar_rq-&gt;flags
op_and_assign
op_complement
id|REQ_STARTED
suffix:semicolon
id|_elv_add_request
c_func
(paren
id|q
comma
id|ar-&gt;ar_rq
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|ata_ar_put
c_func
(paren
id|drive
comma
id|ar
)paren
suffix:semicolon
)brace
id|drive-&gt;tcq-&gt;queued
op_assign
l_int|0
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
op_amp
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
id|IDE_DMA
comma
op_amp
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|flags
)paren
suffix:semicolon
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|handler
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * do some internal stuff -- we really need this command to be&n;&t; * executed before any new commands are started. issue a NOP&n;&t; * to clear internal queue on drive&n;&t; */
id|ar
op_assign
id|ata_ar_get
c_func
(paren
id|drive
)paren
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|ar-&gt;ar_task
comma
l_int|0
comma
r_sizeof
(paren
id|ar-&gt;ar_task
)paren
)paren
suffix:semicolon
id|AR_TASK_CMD
c_func
(paren
id|ar
)paren
op_assign
id|WIN_NOP
suffix:semicolon
id|ide_cmd_type_parser
c_func
(paren
op_amp
id|ar-&gt;ar_task
)paren
suffix:semicolon
id|ar-&gt;ar_rq
op_assign
op_amp
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|wrq
suffix:semicolon
id|init_taskfile_request
c_func
(paren
id|ar-&gt;ar_rq
)paren
suffix:semicolon
id|ar-&gt;ar_rq-&gt;rq_dev
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
id|ar-&gt;ar_rq-&gt;special
op_assign
id|ar
suffix:semicolon
id|ar-&gt;ar_flags
op_or_assign
id|ATA_AR_RETURN
suffix:semicolon
id|_elv_add_request
c_func
(paren
id|q
comma
id|ar-&gt;ar_rq
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * make sure that nIEN is cleared&n;&t; */
id|drive_ctl_nien
c_func
(paren
id|drive
comma
l_int|0
)paren
suffix:semicolon
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
op_amp
id|ide_lock
comma
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ide_tcq_invalidate_queue: done&bslash;n&quot;
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
id|ide_hwgroup_t
op_star
id|hwgroup
op_assign
(paren
id|ide_hwgroup_t
op_star
)paren
id|data
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|ide_drive_t
op_star
id|drive
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;ide_tcq_intr_timeout: timeout waiting for interrupt...&bslash;n&quot;
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
id|test_bit
c_func
(paren
id|IDE_BUSY
comma
op_amp
id|hwgroup-&gt;flags
)paren
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
r_if
c_cond
(paren
(paren
id|drive
op_assign
id|hwgroup-&gt;drive
)paren
op_eq
l_int|NULL
)paren
id|printk
c_func
(paren
l_string|&quot;ide_tcq_intr_timeout: missing drive!&bslash;n&quot;
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
id|hwgroup
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
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * one initial udelay(1) should be enough, reading alt stat should&n;&t; * provide the required delay...&n;&t; */
op_star
id|stat
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|udelay
c_func
(paren
l_int|1
)paren
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
)brace
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
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * issue SERVICE command to drive -- drive must have been selected first,&n; * and it must have reported a need for service (status has SERVICE_STAT set)&n; *&n; * Also, nIEN must be set as not to need protection against ide_dmaq_intr&n; */
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
r_struct
id|ata_request
op_star
id|ar
suffix:semicolon
id|byte
id|feat
comma
id|tag
comma
id|stat
suffix:semicolon
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|IDE_DMA
comma
op_amp
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|flags
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;ide_service: DMA in progress&bslash;n&quot;
)paren
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
id|drive-&gt;channel
comma
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
id|printk
c_func
(paren
l_string|&quot;%s: error SERVICING drive (%x)&bslash;n&quot;
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
l_string|&quot;ide_service&quot;
comma
id|stat
)paren
suffix:semicolon
r_return
id|ide_tcq_end
c_func
(paren
id|drive
)paren
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
id|printk
c_func
(paren
l_string|&quot;%s: release in service&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
id|IDE_SET_CUR_TAG
c_func
(paren
id|drive
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * start dma&n;&t; */
id|tag
op_assign
id|feat
op_rshift
l_int|3
suffix:semicolon
id|IDE_SET_CUR_TAG
c_func
(paren
id|drive
comma
id|tag
)paren
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
r_if
c_cond
(paren
(paren
id|ar
op_assign
id|IDE_CUR_TAG
c_func
(paren
id|drive
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide_service: missing request for tag %d&bslash;n&quot;
comma
id|tag
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * we&squot;ll start a dma read or write, device will trigger&n;&t; * interrupt to indicate end of transfer, release is not allowed&n;&t; */
r_if
c_cond
(paren
id|rq_data_dir
c_func
(paren
id|ar-&gt;ar_rq
)paren
op_eq
id|READ
)paren
(brace
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;ide_service: starting READ %x&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
id|drive-&gt;channel
op_member_access_from_pointer
id|dmaproc
c_func
(paren
id|ide_dma_read_queued
comma
id|drive
)paren
suffix:semicolon
)brace
r_else
(brace
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;ide_service: starting WRITE %x&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
id|drive-&gt;channel
op_member_access_from_pointer
id|dmaproc
c_func
(paren
id|ide_dma_write_queued
comma
id|drive
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * dmaproc set intr handler&n;&t; */
r_return
id|ide_started
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
id|byte
id|stat
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ide_pending_commands
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
(paren
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
)paren
op_amp
id|SERVICE_STAT
)paren
r_return
id|ide_service
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * we have pending commands, wait for interrupt&n;&t; */
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
DECL|function|ide_tcq_end
r_int
id|ide_tcq_end
c_func
(paren
id|ide_drive_t
op_star
id|drive
)paren
(brace
id|byte
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
suffix:semicolon
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
l_string|&quot;ide_tcq_end&quot;
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
r_else
r_if
c_cond
(paren
id|stat
op_amp
id|SERVICE_STAT
)paren
(brace
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;ide_tcq_end: serv stat=%x&bslash;n&quot;
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
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;ide_tcq_end: stat=%x, feat=%x&bslash;n&quot;
comma
id|stat
comma
id|GET_FEAT
c_func
(paren
)paren
)paren
suffix:semicolon
r_return
id|ide_stopped
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
id|byte
id|stat
)paren
(brace
r_struct
id|ata_request
op_star
id|ar
suffix:semicolon
id|byte
id|dma_stat
suffix:semicolon
macro_line|#if 0
id|byte
id|feat
op_assign
id|GET_FEAT
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|feat
op_amp
(paren
id|NSEC_CD
op_or
id|NSEC_IO
)paren
)paren
op_ne
(paren
id|NSEC_CD
op_or
id|NSEC_IO
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;%s: C/D | I/O not set&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n;&t; * transfer was in progress, stop DMA engine&n;&t; */
id|ar
op_assign
id|IDE_CUR_TAG
c_func
(paren
id|drive
)paren
suffix:semicolon
id|dma_stat
op_assign
id|drive-&gt;channel
op_member_access_from_pointer
id|dmaproc
c_func
(paren
id|ide_dma_end
comma
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
l_string|&quot;ide_dmaq_intr&quot;
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
l_string|&quot;ide_dmaq_intr: ending %p, tag %d&bslash;n&quot;
comma
id|ar
comma
id|ar-&gt;ar_tag
)paren
suffix:semicolon
id|ide_end_queued_request
c_func
(paren
id|drive
comma
op_logical_neg
id|dma_stat
comma
id|ar-&gt;ar_rq
)paren
suffix:semicolon
id|IDE_SET_CUR_TAG
c_func
(paren
id|drive
comma
op_minus
l_int|1
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
id|byte
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;ide_dmaq_intr: stat=%x, tag %d&bslash;n&quot;
comma
id|stat
comma
id|drive-&gt;tcq-&gt;active_tag
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * if a command completion interrupt is pending, do that first and&n;&t; * check service afterwards&n;&t; */
r_if
c_cond
(paren
id|drive-&gt;tcq-&gt;active_tag
op_ne
op_minus
l_int|1
)paren
r_return
id|ide_dmaq_complete
c_func
(paren
id|drive
comma
id|stat
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * service interrupt&n;&t; */
r_if
c_cond
(paren
id|stat
op_amp
id|SERVICE_STAT
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
r_struct
id|hd_drive_task_hdr
id|taskfile
suffix:semicolon
r_int
id|tcq_supp
op_assign
l_int|1
op_lshift
l_int|1
op_or
l_int|1
op_lshift
l_int|14
suffix:semicolon
id|memset
c_func
(paren
op_amp
id|taskfile
comma
l_int|0
comma
r_sizeof
(paren
id|taskfile
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * bit 14 and 1 must be set in word 83 of the device id to indicate&n;&t; * support for dma queued protocol&n;&t; */
r_if
c_cond
(paren
(paren
id|drive-&gt;id-&gt;command_set_2
op_amp
id|tcq_supp
)paren
op_ne
id|tcq_supp
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: queued feature set not supported&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|taskfile.feature
op_assign
id|SETFEATURES_EN_WCACHE
suffix:semicolon
id|taskfile.command
op_assign
id|WIN_SETFEATURES
suffix:semicolon
r_if
c_cond
(paren
id|ide_wait_taskfile
c_func
(paren
id|drive
comma
op_amp
id|taskfile
comma
l_int|NULL
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
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * disable RELease interrupt, it&squot;s quicker to poll this after&n;&t; * having sent the command opcode&n;&t; */
id|taskfile.feature
op_assign
id|SETFEATURES_DIS_RI
suffix:semicolon
id|taskfile.command
op_assign
id|WIN_SETFEATURES
suffix:semicolon
r_if
c_cond
(paren
id|ide_wait_taskfile
c_func
(paren
id|drive
comma
op_amp
id|taskfile
comma
l_int|NULL
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
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#ifdef IDE_TCQ_FIDDLE_SI
multiline_comment|/*&n;&t; * enable SERVICE interrupt&n;&t; */
id|taskfile.feature
op_assign
id|SETFEATURES_EN_SI
suffix:semicolon
id|taskfile.command
op_assign
id|WIN_SETFEATURES
suffix:semicolon
r_if
c_cond
(paren
id|ide_wait_taskfile
c_func
(paren
id|drive
comma
op_amp
id|taskfile
comma
l_int|NULL
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
r_return
l_int|1
suffix:semicolon
)brace
macro_line|#endif
r_return
l_int|0
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
multiline_comment|/*&n;&t; * disable or adjust queue depth&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|on
)paren
(brace
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
r_else
r_if
c_cond
(paren
id|drive-&gt;using_tcq
)paren
(brace
id|drive-&gt;queue_depth
op_assign
id|drive-&gt;using_tcq
suffix:semicolon
r_goto
id|out
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
id|out
suffix:colon
id|drive-&gt;tcq-&gt;max_depth
op_assign
l_int|0
suffix:semicolon
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
DECL|function|ide_tcq_dmaproc
r_int
id|ide_tcq_dmaproc
c_func
(paren
id|ide_dma_action_t
id|func
comma
id|ide_drive_t
op_star
id|drive
)paren
(brace
r_struct
id|ata_channel
op_star
id|hwif
op_assign
id|drive-&gt;channel
suffix:semicolon
r_int
r_int
id|reading
op_assign
l_int|0
comma
id|enable_tcq
op_assign
l_int|1
suffix:semicolon
id|ide_startstop_t
id|startstop
suffix:semicolon
r_struct
id|ata_request
op_star
id|ar
suffix:semicolon
id|byte
id|stat
comma
id|feat
suffix:semicolon
r_switch
c_cond
(paren
id|func
)paren
(brace
multiline_comment|/*&n;&t;&t; * invoked from a SERVICE interrupt, command etc already known.&n;&t;&t; * just need to start the dma engine for this tag&n;&t;&t; */
r_case
id|ide_dma_read_queued
suffix:colon
id|reading
op_assign
l_int|1
op_lshift
l_int|3
suffix:semicolon
r_case
id|ide_dma_write_queued
suffix:colon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;ide_dma: setting up queued %d&bslash;n&quot;
comma
id|drive-&gt;tcq-&gt;active_tag
)paren
suffix:semicolon
id|BUG_ON
c_func
(paren
id|drive-&gt;tcq-&gt;active_tag
op_eq
op_minus
l_int|1
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
op_amp
id|HWGROUP
c_func
(paren
id|drive
)paren
op_member_access_from_pointer
id|flags
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
id|ide_wait_stat
c_func
(paren
op_amp
id|startstop
comma
id|drive
comma
id|READY_STAT
op_or
id|DRQ_STAT
comma
id|BUSY_STAT
comma
id|WAIT_READY
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: timeout waiting for data phase&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_return
id|startstop
suffix:semicolon
)brace
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
id|func
)paren
)paren
r_return
l_int|1
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
id|hwif
op_member_access_from_pointer
id|dmaproc
c_func
(paren
id|ide_dma_begin
comma
id|drive
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * start a queued command from scratch&n;&t;&t;&t; */
r_case
id|ide_dma_queued_start
suffix:colon
id|BUG_ON
c_func
(paren
id|drive-&gt;tcq-&gt;active_tag
op_eq
op_minus
l_int|1
)paren
suffix:semicolon
id|ar
op_assign
id|IDE_CUR_TAG
c_func
(paren
id|drive
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * set nIEN, tag start operation will enable again when&n;&t;&t;&t; * it is safe&n;&t;&t;&t; */
id|drive_ctl_nien
c_func
(paren
id|drive
comma
l_int|1
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|AR_TASK_CMD
c_func
(paren
id|ar
)paren
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
l_string|&quot;ide_dma_queued_start: abort (stat=%x)&bslash;n&quot;
comma
id|stat
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
r_if
c_cond
(paren
id|stat
op_amp
id|ERR_STAT
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;ide_dma_queued_start: abort (stat=%x)&bslash;n&quot;
comma
id|stat
)paren
suffix:semicolon
r_return
id|ide_stopped
suffix:semicolon
)brace
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
id|drive-&gt;tcq-&gt;immed_rel
op_increment
suffix:semicolon
id|TCQ_PRINTK
c_func
(paren
l_string|&quot;REL in queued_start&bslash;n&quot;
)paren
suffix:semicolon
id|IDE_SET_CUR_TAG
c_func
(paren
id|drive
comma
op_minus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|stat
op_assign
id|GET_STAT
c_func
(paren
)paren
)paren
op_amp
id|SERVICE_STAT
)paren
r_return
id|ide_service
c_func
(paren
id|drive
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
id|ide_released
suffix:semicolon
)brace
id|drive-&gt;tcq-&gt;immed_comp
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ide_wait_stat
c_func
(paren
op_amp
id|startstop
comma
id|drive
comma
id|READY_STAT
op_or
id|DRQ_STAT
comma
id|BUSY_STAT
comma
id|WAIT_READY
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: timeout waiting for data phase&bslash;n&quot;
comma
id|drive-&gt;name
)paren
suffix:semicolon
r_return
id|startstop
suffix:semicolon
)brace
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
id|func
)paren
)paren
r_return
id|ide_stopped
suffix:semicolon
r_if
c_cond
(paren
id|hwif
op_member_access_from_pointer
id|dmaproc
c_func
(paren
id|ide_dma_begin
comma
id|drive
)paren
)paren
r_return
id|ide_stopped
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; * wait for SERVICE or completion interrupt&n;&t;&t;&t; */
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
r_case
id|ide_dma_queued_off
suffix:colon
id|enable_tcq
op_assign
l_int|0
suffix:semicolon
r_case
id|ide_dma_queued_on
suffix:colon
r_return
id|ide_enable_queued
c_func
(paren
id|drive
comma
id|enable_tcq
)paren
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
r_int
id|ide_build_sglist
(paren
r_struct
id|ata_channel
op_star
id|hwif
comma
r_struct
id|request
op_star
id|rq
)paren
suffix:semicolon
DECL|function|ide_start_tag
id|ide_startstop_t
id|ide_start_tag
c_func
(paren
id|ide_dma_action_t
id|func
comma
id|ide_drive_t
op_star
id|drive
comma
r_struct
id|ata_request
op_star
id|ar
)paren
(brace
multiline_comment|/*&n;&t; * do this now, no need to run that with interrupts disabled&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|ide_build_sglist
c_func
(paren
id|drive-&gt;channel
comma
id|ar-&gt;ar_rq
)paren
)paren
r_return
id|ide_stopped
suffix:semicolon
id|IDE_SET_CUR_TAG
c_func
(paren
id|drive
comma
id|ar-&gt;ar_tag
)paren
suffix:semicolon
r_return
id|ide_tcq_dmaproc
c_func
(paren
id|func
comma
id|drive
)paren
suffix:semicolon
)brace
eof
