multiline_comment|/*&n; *  linux/arch/arm/mm/mm-ebsa110.c&n; *&n; *  Copyright (C) 1998-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Extra MM routines for the EBSA-110 architecture&n; */
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|ebsa110_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|IO_BASE
op_minus
id|PGDIR_SIZE
comma
l_int|0xc0000000
comma
id|PGDIR_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
id|IO_BASE
comma
id|IO_START
comma
id|IO_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
comma
l_int|0
comma
l_int|0
)brace
comma
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|ebsa110_map_io
r_void
id|__init
id|ebsa110_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|ebsa110_io_desc
)paren
suffix:semicolon
)brace
eof
