multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/victor.c&n; *&n; * Author: Nicolas Pitre&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|function|victor_power_off
r_static
r_void
id|victor_power_off
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* switch off power supply */
id|mdelay
c_func
(paren
l_int|2000
)paren
suffix:semicolon
id|GPCR
op_assign
id|GPIO_GPIO23
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|victor_init
r_static
r_int
id|__init
id|victor_init
c_func
(paren
r_void
)paren
(brace
id|pm_power_off
op_assign
id|victor_power_off
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|victor_init
id|__initcall
c_func
(paren
id|victor_init
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|fixup_victor
id|fixup_victor
c_func
(paren
r_struct
id|machine_desc
op_star
id|desc
comma
r_struct
id|param_struct
op_star
id|params
comma
r_char
op_star
op_star
id|cmdline
comma
r_struct
id|meminfo
op_star
id|mi
)paren
(brace
id|SET_BANK
c_func
(paren
l_int|0
comma
l_int|0xc0000000
comma
l_int|4
op_star
l_int|1024
op_star
l_int|1024
)paren
suffix:semicolon
id|mi-&gt;nr_banks
op_assign
l_int|1
suffix:semicolon
id|ROOT_DEV
op_assign
id|mk_kdev
c_func
(paren
l_int|60
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Get command line parameters passed from the loader (if any) */
r_if
c_cond
(paren
op_star
(paren
(paren
r_char
op_star
)paren
l_int|0xc0000000
)paren
)paren
(brace
id|strcpy
c_func
(paren
op_star
id|cmdline
comma
(paren
(paren
r_char
op_star
)paren
l_int|0xc0000000
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* power off if any problem */
id|strcat
c_func
(paren
op_star
id|cmdline
comma
l_string|&quot; panic=1&quot;
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|victor_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      domain     r  w  c  b */
(brace
l_int|0xe8000000
comma
l_int|0x00000000
comma
l_int|0x00200000
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
multiline_comment|/* Flash */
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|victor_map_io
r_static
r_void
id|__init
id|victor_map_io
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
id|victor_io_desc
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
)brace
id|MACHINE_START
c_func
(paren
id|VICTOR
comma
l_string|&quot;VisuAide Victor&quot;
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
id|FIXUP
c_func
(paren
id|fixup_victor
)paren
id|MAPIO
c_func
(paren
id|victor_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
