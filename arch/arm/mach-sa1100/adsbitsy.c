multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/adsbitsy.c&n; *&n; * Author: Woojung Huh&n; *&n; * Pieces specific to the ADS Bitsy&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
macro_line|#include &quot;sa1111.h&quot;
DECL|function|adsbitsy_init
r_static
r_int
id|__init
id|adsbitsy_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|machine_is_adsbitsy
c_func
(paren
)paren
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/*&n;&t; * Ensure that the memory bus request/grant signals are setup,&n;&t; * and the grant is held in its inactive state&n;&t; */
id|sa1110_mb_disable
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Reset SA1111&n;&t; */
id|GPCR
op_or_assign
id|GPIO_GPIO26
suffix:semicolon
id|udelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|GPSR
op_or_assign
id|GPIO_GPIO26
suffix:semicolon
multiline_comment|/*&n;&t; * Probe for SA1111.&n;&t; */
id|ret
op_assign
id|sa1111_init
c_func
(paren
l_int|NULL
comma
l_int|0x18000000
comma
id|IRQ_GPIO0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
multiline_comment|/*&n;&t; * Enable PWM control for LCD&n;&t; */
id|sa1111_enable_device
c_func
(paren
id|SKPCR_PWMCLKEN
)paren
suffix:semicolon
id|SKPWM0
op_assign
l_int|0x7F
suffix:semicolon
singleline_comment|// VEE
id|SKPEN0
op_assign
l_int|1
suffix:semicolon
id|SKPWM1
op_assign
l_int|0x01
suffix:semicolon
singleline_comment|// Backlight
id|SKPEN1
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|adsbitsy_init
id|arch_initcall
c_func
(paren
id|adsbitsy_init
)paren
suffix:semicolon
DECL|function|adsbitsy_init_irq
r_static
r_void
id|__init
id|adsbitsy_init_irq
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* First the standard SA1100 IRQs */
id|sa1100_init_irq
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|adsbitsy_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xf4000000
comma
l_int|0x18000000
comma
l_int|0x00800000
comma
id|MT_DEVICE
)brace
multiline_comment|/* SA1111 */
)brace
suffix:semicolon
DECL|function|adsbitsy_uart_open
r_static
r_int
id|adsbitsy_uart_open
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
r_struct
id|uart_info
op_star
id|info
)paren
(brace
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser1UTCR0
)paren
(brace
id|Ser1SDCR0
op_or_assign
id|SDCR0_UART
suffix:semicolon
macro_line|#error Fixme&t;
singleline_comment|// Set RTS High (should be done in the set_mctrl fn)
id|GPCR
op_assign
id|GPIO_GPIO15
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser2UTCR0
)paren
(brace
id|Ser2UTCR4
op_assign
id|Ser2HSCR0
op_assign
l_int|0
suffix:semicolon
macro_line|#error Fixme&t;
singleline_comment|// Set RTS High (should be done in the set_mctrl fn)
id|GPCR
op_assign
id|GPIO_GPIO17
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser2UTCR0
)paren
(brace
macro_line|#error Fixme&t;
singleline_comment|// Set RTS High (should be done in the set_mctrl fn)
id|GPCR
op_assign
id|GPIO_GPIO19
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|sa1100_port_fns
id|adsbitsy_port_fns
id|__initdata
op_assign
(brace
dot
id|open
op_assign
id|adsbitsy_uart_open
comma
)brace
suffix:semicolon
DECL|function|adsbitsy_map_io
r_static
r_void
id|__init
id|adsbitsy_map_io
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
id|adsbitsy_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|adsbitsy_io_desc
)paren
)paren
suffix:semicolon
id|sa1100_register_uart_fns
c_func
(paren
op_amp
id|adsbitsy_port_fns
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
id|GPDR
op_or_assign
id|GPIO_GPIO15
op_or
id|GPIO_GPIO17
op_or
id|GPIO_GPIO19
suffix:semicolon
id|GPDR
op_and_assign
op_complement
(paren
id|GPIO_GPIO14
op_or
id|GPIO_GPIO16
op_or
id|GPIO_GPIO18
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|ADSBITSY
comma
l_string|&quot;ADS Bitsy&quot;
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
id|adsbitsy_map_io
)paren
id|INITIRQ
c_func
(paren
id|adsbitsy_init_irq
)paren
id|MACHINE_END
eof
