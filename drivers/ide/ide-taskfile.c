multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; *  Copyright (C) 2002&t;&t;Marcin Dalecki &lt;martin@dalecki.de&gt;&n; *  Copyright (C) 2000&t;&t;Michael Cornwell &lt;cornwell@acm.org&gt;&n; *  Copyright (C) 2000&t;&t;Andre Hedrick &lt;andre@linux-ide.org&gt;&n; *&n; *  May be copied or modified under the terms of the GNU General Public License&n; */
macro_line|#include &lt;linux/config.h&gt;
DECL|macro|__NO_VERSION__
mdefine_line|#define __NO_VERSION__
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/genhd.h&gt;
macro_line|#include &lt;linux/blkpg.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
multiline_comment|/*&n; * Data transfer functions for polled IO.&n; */
DECL|function|ata_read_32
r_static
r_void
id|ata_read_32
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
id|insl
c_func
(paren
id|IDE_DATA_REG
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
DECL|function|ata_write_32
r_static
r_void
id|ata_write_32
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
id|outsl
c_func
(paren
id|IDE_DATA_REG
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
macro_line|#if SUPPORT_SLOW_DATA_PORTS
DECL|function|ata_read_slow
r_static
r_void
id|ata_read_slow
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
r_int
r_int
op_star
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|wcount
op_decrement
)paren
(brace
op_star
id|ptr
op_increment
op_assign
id|inw_p
c_func
(paren
id|IDE_DATA_REG
)paren
suffix:semicolon
op_star
id|ptr
op_increment
op_assign
id|inw_p
c_func
(paren
id|IDE_DATA_REG
)paren
suffix:semicolon
)brace
)brace
DECL|function|ata_write_slow
r_static
r_void
id|ata_write_slow
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
r_int
r_int
op_star
id|ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|buffer
suffix:semicolon
r_while
c_loop
(paren
id|wcount
op_decrement
)paren
(brace
id|outw_p
c_func
(paren
op_star
id|ptr
op_increment
comma
id|IDE_DATA_REG
)paren
suffix:semicolon
id|outw_p
c_func
(paren
op_star
id|ptr
op_increment
comma
id|IDE_DATA_REG
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
DECL|function|ata_read_16
r_static
r_void
id|ata_read_16
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
id|insw
c_func
(paren
id|IDE_DATA_REG
comma
id|buffer
comma
id|wcount
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|ata_write_16
r_static
r_void
id|ata_write_16
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
id|outsw
c_func
(paren
id|IDE_DATA_REG
comma
id|buffer
comma
id|wcount
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This is used for most PIO data transfers *from* the device.&n; */
DECL|function|ata_read
r_void
id|ata_read
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
r_int
id|io_32bit
suffix:semicolon
multiline_comment|/*&n;&t; * First check if this controller has defined a special function&n;&t; * for handling polled ide transfers.&n;&t; */
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;ata_read
)paren
(brace
id|drive-&gt;channel
op_member_access_from_pointer
id|ata_read
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|io_32bit
op_assign
id|drive-&gt;channel-&gt;io_32bit
suffix:semicolon
r_if
c_cond
(paren
id|io_32bit
)paren
(brace
id|ata_read_32
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if SUPPORT_SLOW_DATA_PORTS
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;slow
)paren
id|ata_read_slow
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
r_else
macro_line|#endif
id|ata_read_16
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * This is used for most PIO data transfers *to* the device interface.&n; */
DECL|function|ata_write
r_void
id|ata_write
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_void
op_star
id|buffer
comma
r_int
r_int
id|wcount
)paren
(brace
r_int
id|io_32bit
suffix:semicolon
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;ata_write
)paren
(brace
id|drive-&gt;channel
op_member_access_from_pointer
id|ata_write
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|io_32bit
op_assign
id|drive-&gt;channel-&gt;io_32bit
suffix:semicolon
r_if
c_cond
(paren
id|io_32bit
)paren
(brace
id|ata_write_32
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
r_else
(brace
macro_line|#if SUPPORT_SLOW_DATA_PORTS
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;slow
)paren
id|ata_write_slow
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
r_else
macro_line|#endif
id|ata_write_16
c_func
(paren
id|drive
comma
id|buffer
comma
id|wcount
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Invoked on completion of a special REQ_SPECIAL command.&n; */
DECL|function|special_intr
r_static
id|ide_startstop_t
id|special_intr
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
r_int
id|flags
suffix:semicolon
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_struct
id|ata_taskfile
op_star
id|ar
op_assign
id|rq-&gt;special
suffix:semicolon
id|ide_startstop_t
id|ret
op_assign
id|ATA_OP_FINISHED
suffix:semicolon
id|local_irq_enable
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rq-&gt;buffer
op_logical_and
id|ar-&gt;taskfile.sector_number
)paren
(brace
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
id|DRQ_STAT
)paren
op_logical_and
id|ar-&gt;taskfile.sector_number
)paren
(brace
r_int
id|retries
op_assign
l_int|10
suffix:semicolon
id|ata_read
c_func
(paren
id|drive
comma
id|rq-&gt;buffer
comma
id|ar-&gt;taskfile.sector_number
op_star
id|SECTOR_WORDS
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
l_int|0
comma
id|BUSY_STAT
)paren
op_logical_and
id|retries
op_decrement
)paren
id|udelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
)brace
)brace
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
id|BAD_STAT
)paren
)paren
(brace
multiline_comment|/* Keep quiet for NOP because it is expected to fail. */
r_if
c_cond
(paren
id|ar-&gt;cmd
op_ne
id|WIN_NOP
)paren
id|ret
op_assign
id|ata_error
c_func
(paren
id|drive
comma
id|rq
comma
id|__FUNCTION__
)paren
suffix:semicolon
id|rq-&gt;errors
op_assign
l_int|1
suffix:semicolon
)brace
id|ar-&gt;taskfile.feature
op_assign
id|IN_BYTE
c_func
(paren
id|IDE_ERROR_REG
)paren
suffix:semicolon
id|ata_in_regfile
c_func
(paren
id|drive
comma
op_amp
id|ar-&gt;taskfile
)paren
suffix:semicolon
id|ar-&gt;taskfile.device_head
op_assign
id|IN_BYTE
c_func
(paren
id|IDE_SELECT_REG
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|drive-&gt;id-&gt;command_set_2
op_amp
l_int|0x0400
)paren
op_logical_and
(paren
id|drive-&gt;id-&gt;cfs_enable_2
op_amp
l_int|0x0400
)paren
op_logical_and
(paren
id|drive-&gt;addressing
op_eq
l_int|1
)paren
)paren
(brace
multiline_comment|/* The following command goes to the hob file! */
id|OUT_BYTE
c_func
(paren
l_int|0x80
comma
id|drive-&gt;channel-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
suffix:semicolon
id|ar-&gt;hobfile.feature
op_assign
id|IN_BYTE
c_func
(paren
id|IDE_FEATURE_REG
)paren
suffix:semicolon
id|ata_in_regfile
c_func
(paren
id|drive
comma
op_amp
id|ar-&gt;hobfile
)paren
suffix:semicolon
)brace
id|spin_lock_irqsave
c_func
(paren
id|ch-&gt;lock
comma
id|flags
)paren
suffix:semicolon
id|blkdev_dequeue_request
c_func
(paren
id|rq
)paren
suffix:semicolon
id|drive-&gt;rq
op_assign
l_int|NULL
suffix:semicolon
id|end_that_request_last
c_func
(paren
id|rq
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
r_return
id|ret
suffix:semicolon
)brace
DECL|function|ide_raw_taskfile
r_int
id|ide_raw_taskfile
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|ata_taskfile
op_star
id|ar
comma
r_char
op_star
id|buf
)paren
(brace
r_struct
id|request
op_star
id|rq
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
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
id|list_head
op_star
id|queue_head
op_assign
op_amp
id|q-&gt;queue_head
suffix:semicolon
id|DECLARE_COMPLETION
c_func
(paren
id|wait
)paren
suffix:semicolon
r_struct
id|request
id|req
suffix:semicolon
macro_line|#ifdef CONFIG_BLK_DEV_PDC4030
r_if
c_cond
(paren
id|ch-&gt;chipset
op_eq
id|ide_pdc4030
op_logical_and
id|buf
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
multiline_comment|/* special drive cmds not supported */
macro_line|#endif
id|memset
c_func
(paren
op_amp
id|req
comma
l_int|0
comma
r_sizeof
(paren
id|req
)paren
)paren
suffix:semicolon
id|rq
op_assign
op_amp
id|req
suffix:semicolon
id|rq-&gt;flags
op_assign
id|REQ_SPECIAL
suffix:semicolon
id|rq-&gt;buffer
op_assign
id|buf
suffix:semicolon
id|rq-&gt;special
op_assign
id|ar
suffix:semicolon
id|rq-&gt;errors
op_assign
l_int|0
suffix:semicolon
id|rq-&gt;rq_status
op_assign
id|RQ_ACTIVE
suffix:semicolon
id|rq-&gt;waiting
op_assign
op_amp
id|wait
suffix:semicolon
id|ar-&gt;XXX_handler
op_assign
id|special_intr
suffix:semicolon
id|ar-&gt;command_type
op_assign
id|IDE_DRIVE_TASK_NO_DATA
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
op_logical_neg
id|blk_queue_empty
c_func
(paren
op_amp
id|drive-&gt;queue
)paren
)paren
id|queue_head
op_assign
id|queue_head-&gt;prev
suffix:semicolon
id|__elv_add_request
c_func
(paren
id|q
comma
id|rq
comma
id|queue_head
)paren
suffix:semicolon
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
id|wait_for_completion
c_func
(paren
op_amp
id|wait
)paren
suffix:semicolon
multiline_comment|/* wait for it to be serviced */
r_return
id|rq-&gt;errors
ques
c_cond
op_minus
id|EIO
suffix:colon
l_int|0
suffix:semicolon
multiline_comment|/* return -EIO if errors */
)brace
DECL|variable|ata_read
id|EXPORT_SYMBOL
c_func
(paren
id|ata_read
)paren
suffix:semicolon
DECL|variable|ata_write
id|EXPORT_SYMBOL
c_func
(paren
id|ata_write
)paren
suffix:semicolon
DECL|variable|ide_raw_taskfile
id|EXPORT_SYMBOL
c_func
(paren
id|ide_raw_taskfile
)paren
suffix:semicolon
eof
