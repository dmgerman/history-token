multiline_comment|/*&n; *  linux/arch/arm/mach-shark/arch.c&n; *&n; *  Architecture specific stuff.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
r_extern
r_void
id|shark_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|shark_io_desc
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
)brace
suffix:semicolon
DECL|function|shark_map_io
r_static
r_void
id|__init
id|shark_map_io
c_func
(paren
r_void
)paren
(brace
id|iotable_init
c_func
(paren
id|shark_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|shark_io_desc
)paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|SHARK
comma
l_string|&quot;Shark&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Alexander Schulz&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x08000000
comma
l_int|0x40000000
comma
l_int|0xe0000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x08003000
)paren
id|MAPIO
c_func
(paren
id|shark_map_io
)paren
id|INITIRQ
c_func
(paren
id|shark_init_irq
)paren
id|MACHINE_END
eof
