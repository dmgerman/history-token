multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/omnimeter.c&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|function|omnimeter_backlight_power
r_static
r_void
id|omnimeter_backlight_power
c_func
(paren
r_int
id|on
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
id|LEDBacklightOn
c_func
(paren
)paren
suffix:semicolon
r_else
id|LEDBacklightOff
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|omnimeter_lcd_power
r_static
r_void
id|omnimeter_lcd_power
c_func
(paren
r_int
id|on
)paren
(brace
r_if
c_cond
(paren
id|on
)paren
id|LCDPowerOn
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|omnimeter_init
r_static
r_int
id|__init
id|omnimeter_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_omnimeter
c_func
(paren
)paren
)paren
(brace
id|sa1100fb_backlight_power
op_assign
id|omnimeter_backlight_power
suffix:semicolon
id|sa1100fb_lcd_power
op_assign
id|omnimeter_lcd_power
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|omnimeter_init
id|__initcall
c_func
(paren
id|omnimeter_init
)paren
suffix:semicolon
r_static
r_void
id|__init
DECL|function|fixup_omnimeter
id|fixup_omnimeter
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
l_int|16
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
id|RAMDISK_MAJOR
comma
l_int|0
)paren
suffix:semicolon
id|setup_ramdisk
c_func
(paren
l_int|1
comma
l_int|0
comma
l_int|0
comma
l_int|8192
)paren
suffix:semicolon
id|setup_initrd
c_func
(paren
id|__phys_to_virt
c_func
(paren
l_int|0xd0000000
)paren
comma
l_int|0x00400000
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|omnimeter_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      domain     r  w  c  b */
(brace
l_int|0xd2000000
comma
l_int|0x10000000
comma
l_int|0x02000000
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
multiline_comment|/* TS */
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|omnimeter_map_io
r_static
r_void
id|__init
id|omnimeter_map_io
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
id|omnimeter_io_desc
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
id|OMNIMETER
comma
l_string|&quot;OmniMeter&quot;
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
id|fixup_omnimeter
)paren
id|MAPIO
c_func
(paren
id|omnimeter_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
