multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/xp860.c&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/pm.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
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
id|cli
c_func
(paren
)paren
suffix:semicolon
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
multiline_comment|/*&n; * Note: I replaced the sa1111_init() without the full SA1111 initialisation&n; * because this machine doesn&squot;t appear to use the DMA features.  If this is&n; * wrong, please look at neponset.c to fix it properly.&n; */
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
multiline_comment|/*&n;&t; * Probe for SA1111.&n;&t; */
id|ret
op_assign
id|sa1111_probe
c_func
(paren
l_int|0x40000000
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
multiline_comment|/*&n;&t; * We found it.  Wake the chip up.&n;&t; */
id|sa1111_wake
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
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xf0000000
comma
l_int|0x10000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
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
id|MT_DEVICE
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
id|MT_DEVICE
)brace
multiline_comment|/* SA-1111 */
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
comma
id|ARRAY_SIZE
c_func
(paren
id|xp860_io_desc
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
