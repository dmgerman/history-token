multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/nanoengine.c&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
r_static
r_void
id|__init
DECL|function|fixup_nanoengine
id|fixup_nanoengine
c_func
(paren
r_struct
id|machine_desc
op_star
id|desc
comma
r_struct
id|tag
op_star
id|tags
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
l_int|0xc0800000
)paren
comma
l_int|4
op_star
l_int|1024
op_star
l_int|1024
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
l_int|0xc0000100
)paren
)paren
(brace
op_star
id|cmdline
op_assign
(paren
(paren
r_char
op_star
)paren
l_int|0xc0000100
)paren
suffix:semicolon
)brace
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|nanoengine_io_desc
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
multiline_comment|/* Flash bank 0 */
(brace
l_int|0xf0000000
comma
l_int|0x10000000
comma
l_int|0x00100000
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
multiline_comment|/* System Registers */
(brace
l_int|0xf1000000
comma
l_int|0x18A00000
comma
l_int|0x00100000
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
multiline_comment|/* Internal PCI Config Space */
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|nanoengine_map_io
r_static
r_void
id|__init
id|nanoengine_map_io
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
id|nanoengine_io_desc
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
id|Ser1SDCR0
op_or_assign
id|SDCR0_UART
suffix:semicolon
multiline_comment|/* disable IRDA -- UART2 is used as a normal serial port */
id|Ser2UTCR4
op_assign
l_int|0
suffix:semicolon
id|Ser2HSCR0
op_assign
l_int|0
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|NANOENGINE
comma
l_string|&quot;BSE nanoEngine&quot;
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
id|fixup_nanoengine
)paren
id|MAPIO
c_func
(paren
id|nanoengine_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
