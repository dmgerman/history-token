multiline_comment|/**** vi:set ts=8 sts=8 sw=8:************************************************&n; *&n; * Copyright (C) 2002 Marcin Dalecki &lt;martin@dalecki.de&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; *&n; * This program is distributed in the hope that it will be useful, but WITHOUT&n; * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or&n; * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for&n; * more details.&n; */
multiline_comment|/*&n; * Common low leved device access code. This is the lowest layer of hardware&n; * access.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/blkdev.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/cdrom.h&gt;
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
multiline_comment|/*&n; * Check the state of the status register.&n; */
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
