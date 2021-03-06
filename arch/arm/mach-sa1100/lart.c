multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/lart.c&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
macro_line|#warning &quot;include/asm/arch-sa1100/ide.h needs fixing for lart&quot;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|lart_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xe8000000
comma
l_int|0x00000000
comma
l_int|0x00400000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* main flash memory */
(brace
l_int|0xec000000
comma
l_int|0x08000000
comma
l_int|0x00400000
comma
id|MT_DEVICE
)brace
multiline_comment|/* main flash, alternative location */
)brace
suffix:semicolon
DECL|function|lart_map_io
r_static
r_void
id|__init
id|lart_map_io
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
id|lart_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|lart_io_desc
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
id|GAFR
op_or_assign
(paren
id|GPIO_UART_TXD
op_or
id|GPIO_UART_RXD
)paren
suffix:semicolon
id|GPDR
op_or_assign
id|GPIO_UART_TXD
suffix:semicolon
id|GPDR
op_and_assign
op_complement
id|GPIO_UART_RXD
suffix:semicolon
id|PPAR
op_or_assign
id|PPAR_UPR
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|LART
comma
l_string|&quot;LART&quot;
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
id|lart_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
dot
id|timer
op_assign
op_amp
id|sa1100_timer
comma
id|MACHINE_END
eof
