multiline_comment|/*&n; *  linux/arch/arm/mm/mm-tbox.c&n; *&n; *  Copyright (C) 1998, 1999, 2000 Phil Blundell&n; *  Copyright (C) 1998-1999 Russell King&n; *&n; *  Extra MM routines for the Tbox architecture&n; */
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|tbox_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* See hardware.h for details */
(brace
id|IO_BASE
comma
id|IO_START
comma
l_int|0x00100000
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
DECL|function|tbox_map_io
r_void
id|__init
id|tbox_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|tbox_io_desc
)paren
suffix:semicolon
)brace
eof
