multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/brutus.c&n; *&n; * Author: Nicolas Pitre&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|function|brutus_map_io
r_static
r_void
id|__init
id|brutus_map_io
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
id|sa1100_register_uart
c_func
(paren
l_int|0
comma
l_int|1
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|3
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
id|BRUTUS
comma
l_string|&quot;Intel Brutus (SA1100 eval board)&quot;
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
id|MAPIO
c_func
(paren
id|brutus_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
