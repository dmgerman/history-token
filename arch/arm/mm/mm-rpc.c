multiline_comment|/*&n; *  linux/arch/arm/mm/mm-rpc.c&n; *&n; *  Copyright (C) 1998-1999 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Extra MM routines for RiscPC architecture&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/proc/domain.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|rpc_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|SCREEN_BASE
comma
id|SCREEN_START
comma
l_int|2
op_star
l_int|1048576
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
multiline_comment|/* VRAM&t;&t;*/
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
multiline_comment|/* IO space&t;&t;*/
(brace
id|EASI_BASE
comma
id|EASI_START
comma
id|EASI_SIZE
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
multiline_comment|/* EASI space&t;*/
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|rpc_map_io
r_void
id|__init
id|rpc_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|rpc_io_desc
)paren
suffix:semicolon
)brace
eof
