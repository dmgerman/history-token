multiline_comment|/*&n; * linux/arch/arm/mach-omap/board-generic.c&n; *&n; * Modified from board-innovator1510.c&n; *&n; * Code for generic OMAP board. Should work on many OMAP systems where&n; * the device drivers take care of all the necessary hardware initialization.&n; * Do not put any board specific code to this file; create a new machine&n; * type if you need custom low-level initializations.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/arch/clocks.h&gt;
macro_line|#include &lt;asm/arch/gpio.h&gt;
macro_line|#include &lt;asm/arch/mux.h&gt;
macro_line|#include &quot;common.h&quot;
DECL|function|omap_generic_init_irq
r_static
r_void
id|__init
id|omap_generic_init_irq
c_func
(paren
r_void
)paren
(brace
id|omap_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Muxes the serial ports on&n; */
DECL|function|omap_early_serial_init
r_static
r_void
id|__init
id|omap_early_serial_init
c_func
(paren
r_void
)paren
(brace
id|omap_cfg_reg
c_func
(paren
id|UART1_TX
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|UART1_RTS
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|UART2_TX
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|UART2_RTS
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|UART3_TX
)paren
suffix:semicolon
id|omap_cfg_reg
c_func
(paren
id|UART3_RX
)paren
suffix:semicolon
)brace
DECL|function|omap_generic_init
r_static
r_void
id|__init
id|omap_generic_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/*&n;&t; * Make sure the serial ports are muxed on at this point.&n;&t; * You have to mux them off in device drivers later on&n;&t; * if not needed.&n;&t; */
r_if
c_cond
(paren
id|cpu_is_omap1510
c_func
(paren
)paren
)paren
(brace
id|omap_early_serial_init
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
DECL|function|omap_generic_map_io
r_static
r_void
id|__init
id|omap_generic_map_io
c_func
(paren
r_void
)paren
(brace
id|omap_map_io
c_func
(paren
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|OMAP_GENERIC
comma
l_string|&quot;Generic OMAP-1510/1610/1710&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;Tony Lindgren &lt;tony@atomide.com&gt;&quot;
)paren
id|BOOT_MEM
c_func
(paren
l_int|0x10000000
comma
l_int|0xfff00000
comma
l_int|0xfef00000
)paren
id|BOOT_PARAMS
c_func
(paren
l_int|0x10000100
)paren
id|MAPIO
c_func
(paren
id|omap_generic_map_io
)paren
id|INITIRQ
c_func
(paren
id|omap_generic_init_irq
)paren
id|INIT_MACHINE
c_func
(paren
id|omap_generic_init
)paren
id|MACHINE_END
eof
