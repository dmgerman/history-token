multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/pangolin.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|pangolin_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xf2800000
comma
l_int|0x4b800000
comma
l_int|0x00800000
comma
id|MT_DEVICE
)brace
multiline_comment|/* MQ200 */
)brace
suffix:semicolon
DECL|function|pangolin_map_io
r_static
r_void
id|__init
id|pangolin_map_io
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
id|pangolin_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|pangolin_io_desc
)paren
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
id|Ser1SDCR0
op_or_assign
id|SDCR0_UART
suffix:semicolon
multiline_comment|/* set some GPDR bits while it&squot;s safe */
id|GPDR
op_or_assign
id|GPIO_PCMCIA_RESET
suffix:semicolon
macro_line|#ifndef CONFIG_SA1100_PANGOLIN_PCMCIA_IDE
id|GPDR
op_or_assign
id|GPIO_PCMCIA_BUS_ON
suffix:semicolon
macro_line|#endif
)brace
id|MACHINE_START
c_func
(paren
id|PANGOLIN
comma
l_string|&quot;Dialogue-Pangolin&quot;
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
id|pangolin_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
