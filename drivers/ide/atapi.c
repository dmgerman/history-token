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
macro_line|#include &lt;linux/cdrom.h&gt;
macro_line|#include &lt;linux/hdreg.h&gt;
macro_line|#include &lt;linux/ide.h&gt;
macro_line|#include &lt;linux/atapi.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
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
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
