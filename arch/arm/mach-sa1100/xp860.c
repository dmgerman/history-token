multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/xp860.c&n; */
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
macro_line|#include &quot;sa1111.h&quot;
DECL|function|xp860_power_off
r_static
r_void
id|xp860_power_off
c_func
(paren
r_void
)paren
(brace
id|GPDR
op_or_assign
id|GPIO_GPIO20
suffix:semicolon
id|GPSR
op_assign
id|GPIO_GPIO20
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1000
)paren
suffix:semicolon
id|GPCR
op_assign
id|GPIO_GPIO20
suffix:semicolon
r_while
c_loop
(paren
l_int|1
)paren
(brace
suffix:semicolon
)brace
)brace
DECL|function|xp860_init
r_static
r_int
id|__init
id|xp860_init
c_func
(paren
r_void
)paren
(brace
id|pm_power_off
op_assign
id|xp860_power_off
suffix:semicolon
id|sa1111_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|xp860_init
id|__initcall
c_func
(paren
id|xp860_init
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|fixup_xp860
id|fixup_xp860
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
l_int|32
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
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|xp860_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      domain     r  w  c  b */
(brace
l_int|0xf0000000
comma
l_int|0x10000000
comma
l_int|0x00100000
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
multiline_comment|/* SCSI */
(brace
l_int|0xf1000000
comma
l_int|0x18000000
comma
l_int|0x00100000
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
multiline_comment|/* LAN */
(brace
l_int|0xf4000000
comma
l_int|0x40000000
comma
l_int|0x00800000
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
multiline_comment|/* SA-1111 */
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|xp860_map_io
r_static
r_void
id|__init
id|xp860_map_io
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
id|xp860_io_desc
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
)brace
id|MACHINE_START
c_func
(paren
id|XP860
comma
l_string|&quot;XP860&quot;
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
id|fixup_xp860
)paren
id|MAPIO
c_func
(paren
id|xp860_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
