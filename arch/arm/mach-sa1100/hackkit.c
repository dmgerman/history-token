multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/hackkit.c&n; *&n; * Copyright (C) 2002 Stefan Eletzhofer &lt;stefan.eletzhofer@eletztrick.de&gt;&n; *&n; * This file contains all HackKit tweaks. Based on original work from&n; * Nicolas Pitre&squot;s assabet fixes&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/cpufreq.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/mach-types.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/irq.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
multiline_comment|/**********************************************************************&n; *  prototypes&n; */
multiline_comment|/* init funcs */
r_static
r_int
id|__init
id|hackkit_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__init
id|hackkit_init_irq
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|__init
id|hackkit_map_io
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
id|u_int
id|hackkit_get_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
suffix:semicolon
r_static
r_void
id|hackkit_set_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|mctrl
)paren
suffix:semicolon
r_static
r_void
id|hackkit_uart_pm
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|state
comma
id|u_int
id|oldstate
)paren
suffix:semicolon
multiline_comment|/**********************************************************************&n; *  global data&n; */
multiline_comment|/**********************************************************************&n; *  static data&n; */
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|hackkit_io_desc
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
l_int|0x01000000
comma
id|MT_DEVICE
)brace
multiline_comment|/* Flash bank 0 */
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|sa1100_port_fns
id|hackkit_port_fns
id|__initdata
op_assign
(brace
dot
id|set_mctrl
op_assign
id|hackkit_set_mctrl
comma
dot
id|get_mctrl
op_assign
id|hackkit_get_mctrl
comma
dot
id|pm
op_assign
id|hackkit_uart_pm
comma
)brace
suffix:semicolon
multiline_comment|/**********************************************************************&n; *  Static functions&n; */
DECL|function|hackkit_map_io
r_static
r_void
id|__init
id|hackkit_map_io
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
id|hackkit_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|hackkit_io_desc
)paren
)paren
suffix:semicolon
id|sa1100_register_uart_fns
c_func
(paren
op_amp
id|hackkit_port_fns
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
multiline_comment|/* com port */
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|2
)paren
suffix:semicolon
id|sa1100_register_uart
c_func
(paren
l_int|2
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* radio module */
id|Ser1SDCR0
op_or_assign
id|SDCR0_SUS
suffix:semicolon
)brace
DECL|function|hackkit_init_irq
r_static
r_void
id|__init
id|hackkit_init_irq
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* none used yet */
)brace
multiline_comment|/**&n; *&t;hackkit_uart_pm - powermgmt callback function for system 3 UART&n; *&t;@port: uart port structure&n; *&t;@state: pm state&n; *&t;@oldstate: old pm state&n; *&n; */
DECL|function|hackkit_uart_pm
r_static
r_void
id|hackkit_uart_pm
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|state
comma
id|u_int
id|oldstate
)paren
(brace
multiline_comment|/* TODO: switch on/off uart in powersave mode */
)brace
multiline_comment|/*&n; * Note! this can be called from IRQ context.&n; * FIXME: No modem ctrl lines yet.&n; */
DECL|function|hackkit_set_mctrl
r_static
r_void
id|hackkit_set_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
comma
id|u_int
id|mctrl
)paren
(brace
macro_line|#if 0
r_if
c_cond
(paren
id|port-&gt;mapbase
op_eq
id|_Ser1UTCR0
)paren
(brace
id|u_int
id|set
op_assign
l_int|0
comma
id|clear
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_RTS
)paren
id|set
op_or_assign
id|PT_CTRL2_RS1_RTS
suffix:semicolon
r_else
id|clear
op_or_assign
id|PT_CTRL2_RS1_RTS
suffix:semicolon
r_if
c_cond
(paren
id|mctrl
op_amp
id|TIOCM_DTR
)paren
id|set
op_or_assign
id|PT_CTRL2_RS1_DTR
suffix:semicolon
r_else
id|clear
op_or_assign
id|PT_CTRL2_RS1_DTR
suffix:semicolon
id|PTCTRL2_clear
c_func
(paren
id|clear
)paren
suffix:semicolon
id|PTCTRL2_set
c_func
(paren
id|set
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
DECL|function|hackkit_get_mctrl
r_static
id|u_int
id|hackkit_get_mctrl
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
(brace
id|u_int
id|ret
op_assign
l_int|0
suffix:semicolon
macro_line|#if 0
id|u_int
id|irqsr
op_assign
id|PT_IRQSR
suffix:semicolon
multiline_comment|/* need 2 reads to read current value */
id|irqsr
op_assign
id|PT_IRQSR
suffix:semicolon
multiline_comment|/* TODO: check IRQ source register for modem/com&n;&t; status lines and set them correctly. */
macro_line|#endif
id|ret
op_assign
id|TIOCM_CD
op_or
id|TIOCM_CTS
op_or
id|TIOCM_DSR
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
DECL|function|hackkit_init
r_static
r_int
id|__init
id|hackkit_init
c_func
(paren
r_void
)paren
(brace
r_int
id|ret
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|machine_is_hackkit
c_func
(paren
)paren
)paren
(brace
id|ret
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_goto
id|DONE
suffix:semicolon
)brace
id|hackkit_init_irq
c_func
(paren
)paren
suffix:semicolon
id|ret
op_assign
l_int|0
suffix:semicolon
id|DONE
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/**********************************************************************&n; *  Exported Functions&n; */
multiline_comment|/**********************************************************************&n; *  kernel magic macros&n; */
DECL|variable|hackkit_init
id|arch_initcall
c_func
(paren
id|hackkit_init
)paren
suffix:semicolon
id|MACHINE_START
c_func
(paren
id|HACKKIT
comma
l_string|&quot;HackKit Cpu Board&quot;
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
id|hackkit_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
