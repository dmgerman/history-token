multiline_comment|/*&n; *  linux/arch/arm/mach-anakin/mm.c&n; *&n; *  Copyright (C) 2001 Aleph One Ltd. for Acunia N.V.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Changelog:&n; *   09-Apr-2001 W/TTC&t;Created&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|anakin_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|IO_BASE
comma
id|IO_START
comma
id|IO_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|FLASH_BASE
comma
id|FLASH_START
comma
id|FLASH_SIZE
comma
id|MT_DEVICE
)brace
comma
(brace
id|VGA_BASE
comma
id|VGA_START
comma
id|VGA_SIZE
comma
id|MT_DEVICE
)brace
)brace
suffix:semicolon
r_void
id|__init
DECL|function|anakin_map_io
id|anakin_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|anakin_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|anakin_io_desc
)paren
)paren
suffix:semicolon
)brace
eof
