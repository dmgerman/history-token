multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; * Copyright (C) 2002 Marcin Dalecki &lt;martin@dalecki.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful, but WITHOUT&n; * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for&n; * more details.&n; */
multiline_comment|/*&n; * Common low leved device access code. This is the lowest layer of hardware&n; * access.&n; *&n; * This is the place where register set access portability will be handled in&n; * the future.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
multiline_comment|/*&n; * Select a device for operation with possible busy waiting for the operation&n; * to complete.&n; */
DECL|function|ata_select
r_void
id|ata_select
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
r_int
id|delay
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;selectproc
)paren
id|ch
op_member_access_from_pointer
id|selectproc
c_func
(paren
id|drive
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|drive-&gt;select.all
comma
id|ch-&gt;io_ports
(braket
id|IDE_SELECT_OFFSET
)braket
)paren
suffix:semicolon
multiline_comment|/* The delays during probing for drives can be georgeous.  Deal with&n;&t; * it.&n;&t; */
r_if
c_cond
(paren
id|delay
)paren
(brace
r_if
c_cond
(paren
id|delay
op_ge
l_int|1000
)paren
id|mdelay
c_func
(paren
id|delay
op_div
l_int|1000
)paren
suffix:semicolon
r_else
id|udelay
c_func
(paren
id|delay
)paren
suffix:semicolon
)brace
)brace
DECL|variable|ata_select
id|EXPORT_SYMBOL
c_func
(paren
id|ata_select
)paren
suffix:semicolon
multiline_comment|/*&n; * Handle quirky routing of interrupts.&n; */
DECL|function|ata_mask
r_void
id|ata_mask
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
r_if
c_cond
(paren
op_logical_neg
id|ch
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|ch-&gt;maskproc
)paren
id|ch
op_member_access_from_pointer
id|maskproc
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Spin until the drive is no longer busy.&n; *&n; * Not exported, since it&squot;s not used within any modules.&n; */
DECL|function|ata_busy_poll
r_int
id|ata_busy_poll
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_int
r_int
id|timeout
)paren
(brace
multiline_comment|/* spec allows drive 400ns to assert &quot;BUSY&quot; */
id|udelay
c_func
(paren
l_int|1
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
id|BUSY_STAT
)paren
)paren
(brace
id|timeout
op_add_assign
id|jiffies
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
(brace
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
r_return
l_int|1
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Check the state of the status register.&n; *&n; * FIXME: Channel lock should be held.&n; */
DECL|function|ata_status
r_int
id|ata_status
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|u8
id|good
comma
id|u8
id|bad
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
id|drive-&gt;status
op_assign
id|IN_BYTE
c_func
(paren
id|ch-&gt;io_ports
(braket
id|IDE_STATUS_OFFSET
)braket
)paren
suffix:semicolon
r_return
(paren
id|drive-&gt;status
op_amp
(paren
id|good
op_or
id|bad
)paren
)paren
op_eq
id|good
suffix:semicolon
)brace
DECL|variable|ata_status
id|EXPORT_SYMBOL
c_func
(paren
id|ata_status
)paren
suffix:semicolon
multiline_comment|/*&n; * Busy-wait for the drive status to be not &quot;busy&quot;.  Check then the status for&n; * all of the &quot;good&quot; bits and none of the &quot;bad&quot; bits, and if all is okay it&n; * returns 0.  All other cases return 1 after invoking error handler -- caller&n; * should just return.&n; *&n; * This routine should get fixed to not hog the cpu during extra long waits..&n; * That could be done by busy-waiting for the first jiffy or two, and then&n; * setting a timer to wake up at half second intervals thereafter, until&n; * timeout is achieved, before timing out.&n; *&n; * Channel lock should be held.&n; */
DECL|function|ata_status_poll
r_int
id|ata_status_poll
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
id|u8
id|good
comma
id|u8
id|bad
comma
r_int
r_int
id|timeout
comma
r_struct
id|request
op_star
id|rq
comma
id|ide_startstop_t
op_star
id|startstop
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* bail early if we&squot;ve exceeded max_failures */
r_if
c_cond
(paren
id|drive-&gt;max_failures
op_logical_and
(paren
id|drive-&gt;failures
OG
id|drive-&gt;max_failures
)paren
)paren
(brace
op_star
id|startstop
op_assign
id|ide_stopped
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ata_busy_poll
c_func
(paren
id|drive
comma
id|timeout
)paren
)paren
(brace
op_star
id|startstop
op_assign
id|ata_error
c_func
(paren
id|drive
comma
id|rq
comma
l_string|&quot;status timeout&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allow status to settle, then read it again.  A few rare drives&n;&t; * vastly violate the 400ns spec here, so we&squot;ll wait up to 10usec for a&n;&t; * &quot;good&quot; status rather than expensively fail things immediately.  This&n;&t; * fix courtesy of Matthew Faupel &amp; Niccolo Rigacci.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|10
suffix:semicolon
id|i
op_increment
)paren
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
id|ata_status
c_func
(paren
id|drive
comma
id|good
comma
id|bad
)paren
)paren
r_return
l_int|0
suffix:semicolon
)brace
op_star
id|startstop
op_assign
id|ata_error
c_func
(paren
id|drive
comma
id|rq
comma
l_string|&quot;status error&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ata_status_poll
id|EXPORT_SYMBOL
c_func
(paren
id|ata_status_poll
)paren
suffix:semicolon
multiline_comment|/*&n; * Handle the nIEN - negated Interrupt ENable of the drive.&n; * This is controlling whatever the drive will acnowlenge commands&n; * with interrupts or not.&n; */
DECL|function|ata_irq_enable
r_int
id|ata_irq_enable
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
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* 0x08 is for legacy ATA-1 devices */
r_if
c_cond
(paren
id|on
)paren
id|OUT_BYTE
c_func
(paren
l_int|0x08
op_or
l_int|0x00
comma
id|ch-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
suffix:semicolon
r_else
(brace
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;intrproc
)paren
id|OUT_BYTE
c_func
(paren
l_int|0x08
op_or
l_int|0x02
comma
id|ch-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
suffix:semicolon
r_else
id|ch
op_member_access_from_pointer
id|intrproc
c_func
(paren
id|drive
)paren
suffix:semicolon
)brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ata_irq_enable
id|EXPORT_SYMBOL
c_func
(paren
id|ata_irq_enable
)paren
suffix:semicolon
multiline_comment|/*&n; * Perform a reset operation on the currently selected drive.&n; */
DECL|function|ata_reset
r_void
id|ata_reset
c_func
(paren
r_struct
id|ata_channel
op_star
id|ch
)paren
(brace
r_int
r_int
id|timeout
op_assign
id|jiffies
op_plus
id|WAIT_WORSTCASE
suffix:semicolon
id|u8
id|stat
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ch-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: reset&bslash;n&quot;
comma
id|ch-&gt;name
)paren
suffix:semicolon
multiline_comment|/* 0x08 is for legacy ATA-1 devices */
id|OUT_BYTE
c_func
(paren
l_int|0x08
op_or
l_int|0x04
comma
id|ch-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
suffix:semicolon
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
multiline_comment|/* 0x08 is for legacy ATA-1 devices */
id|OUT_BYTE
c_func
(paren
l_int|0x08
op_or
l_int|0x00
comma
id|ch-&gt;io_ports
(braket
id|IDE_CONTROL_OFFSET
)braket
)paren
suffix:semicolon
r_do
(brace
id|mdelay
c_func
(paren
l_int|50
)paren
suffix:semicolon
id|stat
op_assign
id|IN_BYTE
c_func
(paren
id|ch-&gt;io_ports
(braket
id|IDE_STATUS_OFFSET
)braket
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|stat
op_amp
id|BUSY_STAT
)paren
op_logical_and
id|time_before
c_func
(paren
id|jiffies
comma
id|timeout
)paren
)paren
suffix:semicolon
)brace
DECL|variable|ata_reset
id|EXPORT_SYMBOL
c_func
(paren
id|ata_reset
)paren
suffix:semicolon
multiline_comment|/*&n; * Output a complete register file.&n; */
DECL|function|ata_out_regfile
r_void
id|ata_out_regfile
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|hd_drive_task_hdr
op_star
id|rf
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|rf-&gt;feature
comma
id|ch-&gt;io_ports
(braket
id|IDE_FEATURE_OFFSET
)braket
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|rf-&gt;sector_count
comma
id|ch-&gt;io_ports
(braket
id|IDE_NSECTOR_OFFSET
)braket
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|rf-&gt;sector_number
comma
id|ch-&gt;io_ports
(braket
id|IDE_SECTOR_OFFSET
)braket
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|rf-&gt;low_cylinder
comma
id|ch-&gt;io_ports
(braket
id|IDE_LCYL_OFFSET
)braket
)paren
suffix:semicolon
id|OUT_BYTE
c_func
(paren
id|rf-&gt;high_cylinder
comma
id|ch-&gt;io_ports
(braket
id|IDE_HCYL_OFFSET
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Input a complete register file.&n; */
DECL|function|ata_in_regfile
r_void
id|ata_in_regfile
c_func
(paren
r_struct
id|ata_device
op_star
id|drive
comma
r_struct
id|hd_drive_task_hdr
op_star
id|rf
)paren
(brace
r_struct
id|ata_channel
op_star
id|ch
op_assign
id|drive-&gt;channel
suffix:semicolon
id|rf-&gt;sector_count
op_assign
id|IN_BYTE
c_func
(paren
id|ch-&gt;io_ports
(braket
id|IDE_NSECTOR_OFFSET
)braket
)paren
suffix:semicolon
id|rf-&gt;sector_number
op_assign
id|IN_BYTE
c_func
(paren
id|ch-&gt;io_ports
(braket
id|IDE_SECTOR_OFFSET
)braket
)paren
suffix:semicolon
id|rf-&gt;low_cylinder
op_assign
id|IN_BYTE
c_func
(paren
id|ch-&gt;io_ports
(braket
id|IDE_LCYL_OFFSET
)braket
)paren
suffix:semicolon
id|rf-&gt;high_cylinder
op_assign
id|IN_BYTE
c_func
(paren
id|ch-&gt;io_ports
(braket
id|IDE_HCYL_OFFSET
)braket
)paren
suffix:semicolon
)brace
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
