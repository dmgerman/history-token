multiline_comment|/*&n; *  linux/arch/arm/mach-xscale/mm.c&n; */
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
id|adifcc_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* on-board devices */
(brace
l_int|0xff400000
comma
l_int|0x00400000
comma
l_int|0x00300000
comma
id|DOMAIN_IO
comma
l_int|1
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
DECL|function|adifcc_map_io
r_void
id|__init
id|adifcc_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|adifcc_io_desc
)paren
suffix:semicolon
)brace
eof
