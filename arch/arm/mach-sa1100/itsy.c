multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/itsy.c&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
multiline_comment|/* BRADFIXME The egpio addresses aren&squot;t verifiably correct. (i.e. they&squot;re most&n;   likely wrong. */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|itsy_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xf0000000
comma
l_int|0x49000000
comma
l_int|0x01000000
comma
id|MT_DEVICE
)brace
multiline_comment|/* EGPIO 0 */
)brace
suffix:semicolon
DECL|function|itsy_map_io
r_static
r_void
id|__init
id|itsy_map_io
c_func
(paren
r_void
)paren
(brace
id|sa1100_map_io
c_func
(paren
)paren
suffix:semicolon
id|iotable_init
c_func
(paren
id|itsy_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|itsy_io_desc
)paren
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|0
comma
l_int|3
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|2
comma
l_int|2
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|ITSY
comma
l_string|&quot;Compaq Itsy&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0xc0000000
comma
l_int|0x80000000
comma
l_int|0xf8000000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0xc0000100
)paren
id|MAPIO
c_func
(paren
id|itsy_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
