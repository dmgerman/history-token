multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; * Copyright (C) 2002 Marcin Dalecki &lt;martin@dalecki.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful, but WITHOUT&n; * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for&n; * more details.&n; */
multiline_comment|/*&n; * Code common among all the ATAPI device drivers.&n; *&n; * Ideally this should evolve in to a unified driver.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/completion.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/atapi.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * Initializes a packet command. Used by tape and floppy driver.&n; */
DECL|function|atapi_init_pc
r_void
id|atapi_init_pc
c_func
(paren
r_struct
id|atapi_packet_command
op_star
id|pc
)paren
(brace
id|memset
c_func
(paren
id|pc-&gt;c
comma
l_int|0
comma
l_int|12
)paren
suffix:semicolon
id|pc-&gt;retries
op_assign
l_int|0
suffix:semicolon
id|pc-&gt;flags
op_assign
l_int|0
suffix:semicolon
id|pc-&gt;request_transfer
op_assign
l_int|0
suffix:semicolon
id|pc-&gt;buffer
op_assign
id|pc-&gt;pc_buffer
suffix:semicolon
id|pc-&gt;buffer_size
op_assign
id|IDEFLOPPY_PC_BUFFER_SIZE
suffix:semicolon
id|pc-&gt;b_data
op_assign
l_int|NULL
suffix:semicolon
id|pc-&gt;bio
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Too bad. The drive wants to send us data which we are not ready to accept.&n; * Just throw it away.&n; */
DECL|function|atapi_discard_data
r_void
id|atapi_discard_data
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
r_int
id|bcount
)paren
(brace
r_while
c_loop
(paren
id|bcount
op_decrement
)paren
id|IN_BYTE
c_func
(paren
id|IDE_DATA_REG
)paren
suffix:semicolon
)brace
DECL|function|atapi_write_zeros
r_void
id|atapi_write_zeros
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
r_int
id|bcount
)paren
(brace
r_while
c_loop
(paren
id|bcount
op_decrement
)paren
id|OUT_BYTE
c_func
(paren
l_int|0
comma
id|IDE_DATA_REG
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following routines are mainly used by the ATAPI drivers.&n; *&n; * These routines will round up any request for an odd number of bytes, so if&n; * an odd n is specified, be sure that there&squot;s at least one extra byte&n; * allocated for the buffer.&n; */
DECL|function|atapi_read
r_void
id|atapi_read
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|u8
op_star
id|buf
comma
r_int
r_int
id|n
)paren
(brace
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;atapi_read
)paren
(brace
id|drive-&gt;channel
op_member_access_from_pointer
id|atapi_read
c_func
(paren
id|drive
comma
id|buf
comma
id|n
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
op_increment
id|n
suffix:semicolon
macro_line|#if defined(CONFIG_ATARI) || defined(CONFIG_Q40)
r_if
c_cond
(paren
id|MACH_IS_ATARI
op_logical_or
id|MACH_IS_Q40
)paren
(brace
multiline_comment|/* Atari has a byte-swapped IDE interface */
id|insw_swapw
c_func
(paren
id|IDE_DATA_REG
comma
id|buf
comma
id|n
op_div
l_int|2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|ata_read
c_func
(paren
id|drive
comma
id|buf
comma
id|n
op_div
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
op_amp
l_int|0x03
)paren
op_ge
l_int|2
)paren
id|insw
c_func
(paren
id|IDE_DATA_REG
comma
id|buf
op_plus
(paren
id|n
op_amp
op_complement
l_int|0x03
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|atapi_write
r_void
id|atapi_write
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|u8
op_star
id|buf
comma
r_int
r_int
id|n
)paren
(brace
r_if
c_cond
(paren
id|drive-&gt;channel-&gt;atapi_write
)paren
(brace
id|drive-&gt;channel
op_member_access_from_pointer
id|atapi_write
c_func
(paren
id|drive
comma
id|buf
comma
id|n
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
op_increment
id|n
suffix:semicolon
macro_line|#if defined(CONFIG_ATARI) || defined(CONFIG_Q40)
r_if
c_cond
(paren
id|MACH_IS_ATARI
op_logical_or
id|MACH_IS_Q40
)paren
(brace
multiline_comment|/* Atari has a byte-swapped IDE interface */
id|outsw_swapw
c_func
(paren
id|IDE_DATA_REG
comma
id|buf
comma
id|n
op_div
l_int|2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#endif
id|ata_write
c_func
(paren
id|drive
comma
id|buf
comma
id|n
op_div
l_int|4
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
op_amp
l_int|0x03
)paren
op_ge
l_int|2
)paren
id|outsw
c_func
(paren
id|IDE_DATA_REG
comma
id|buf
op_plus
(paren
id|n
op_amp
op_complement
l_int|0x03
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * This function issues a special IDE device request onto the request queue.&n; *&n; * If action is ide_wait, then the rq is queued at the end of the request&n; * queue, and the function sleeps until it has been processed.  This is for use&n; * when invoked from an ioctl handler.&n; *&n; * If action is ide_preempt, then the rq is queued at the head of the request&n; * queue, displacing the currently-being-processed request and this function&n; * returns immediately without waiting for the new rq to be completed.  This is&n; * VERY DANGEROUS, and is intended for careful use by the ATAPI tape/cdrom&n; * driver code.&n; *&n; * If action is ide_end, then the rq is queued at the end of the request queue,&n; * and the function returns immediately without waiting for the new rq to be&n; * completed. This is again intended for careful use by the ATAPI tape/cdrom&n; * driver code.&n; */
DECL|function|ide_do_drive_cmd
r_int
id|ide_do_drive_cmd
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
comma
id|ide_action_t
id|action
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
r_int
r_int
id|major
op_assign
id|ch-&gt;major
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
macro_line|#ifdef CONFIG_BLK_DEV_PDC4030
r_if
c_cond
(paren
id|ch-&gt;chipset
op_eq
id|ide_pdc4030
op_logical_and
id|rq-&gt;buffer
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
multiline_comment|/* special drive cmds not supported */
macro_line|#endif
id|rq-&gt;errors
op_assign
l_int|0
suffix:semicolon
id|rq-&gt;rq_status
op_assign
id|RQ_ACTIVE
suffix:semicolon
id|rq-&gt;rq_dev
op_assign
id|mk_kdev
c_func
(paren
id|major
comma
(paren
id|drive-&gt;select.b.unit
)paren
op_lshift
id|PARTN_BITS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|action
op_eq
id|ide_wait
)paren
id|rq-&gt;waiting
op_assign
op_amp
id|wait
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
id|action
op_eq
id|ide_preempt
)paren
id|drive-&gt;rq
op_assign
l_int|NULL
suffix:semicolon
r_else
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
multiline_comment|/* ide_end and ide_wait */
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
id|do_ide_request
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
r_if
c_cond
(paren
id|action
op_eq
id|ide_wait
)paren
(brace
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ide_do_drive_cmd
id|EXPORT_SYMBOL
c_func
(paren
id|ide_do_drive_cmd
)paren
suffix:semicolon
DECL|variable|atapi_discard_data
id|EXPORT_SYMBOL
c_func
(paren
id|atapi_discard_data
)paren
suffix:semicolon
DECL|variable|atapi_write_zeros
id|EXPORT_SYMBOL
c_func
(paren
id|atapi_write_zeros
)paren
suffix:semicolon
DECL|variable|atapi_init_pc
id|EXPORT_SYMBOL
c_func
(paren
id|atapi_init_pc
)paren
suffix:semicolon
DECL|variable|atapi_read
id|EXPORT_SYMBOL
c_func
(paren
id|atapi_read
)paren
suffix:semicolon
DECL|variable|atapi_write
id|EXPORT_SYMBOL
c_func
(paren
id|atapi_write
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
