multiline_comment|/*&n; *  linux/arch/arm/mm/mm-cl7500.c&n; *&n; *  Copyright (C) 1998 Russell King&n; *  Copyright (C) 1999 Nexus Electronics Ltd&n; *&n; * Extra MM routines for CL7500 architecture&n; */
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
id|cl7500_io_desc
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
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* IO space&t;*/
(brace
id|ISA_BASE
comma
id|ISA_START
comma
id|ISA_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* ISA space&t;*/
(brace
id|FLASH_BASE
comma
id|FLASH_START
comma
id|FLASH_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* Flash&t;*/
(brace
id|LED_BASE
comma
id|LED_START
comma
id|LED_SIZE
comma
id|DOMAIN_IO
comma
l_int|0
comma
l_int|1
)brace
comma
multiline_comment|/* LED&t;&t;*/
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|clps7500_map_io
r_void
id|__init
id|clps7500_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|cl7500_io_desc
)paren
suffix:semicolon
)brace
eof
