multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/cerf.c&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|function|cerf_init_irq
r_static
r_void
id|__init
id|cerf_init_irq
c_func
(paren
r_void
)paren
(brace
id|sa1100_init_irq
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Need to register these as rising edge interrupts&n;&t; * For standard 16550 serial driver support&n;&t; * Basically - I copied it from pfs168.c :)&n;&t; */
macro_line|#ifdef CONFIG_SA1100_CERF_CPLD
multiline_comment|/* PDA Full serial port */
id|set_irq_type
c_func
(paren
id|IRQ_GPIO3
comma
id|IRQT_RISING
)paren
suffix:semicolon
multiline_comment|/* PDA Bluetooth */
id|set_irq_type
c_func
(paren
id|IRQ_GPIO2
comma
id|IRQT_RISING
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_SA1100_CERF_CPLD */
id|set_irq_type
c_func
(paren
id|IRQ_GPIO_UCB1200_IRQ
comma
id|IRQT_RISING
)paren
suffix:semicolon
)brace
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|cerf_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual&t; physical    length&t; domain     r  w  c  b */
(brace
l_int|0xf0000000
comma
l_int|0x08000000
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
multiline_comment|/* Crystal Ethernet Chip */
macro_line|#ifdef CONFIG_SA1100_CERF_CPLD
(brace
l_int|0xf1000000
comma
l_int|0x40000000
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
multiline_comment|/* CPLD Chip */
(brace
l_int|0xf2000000
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
multiline_comment|/* CerfPDA Bluetooth */
(brace
l_int|0xf3000000
comma
l_int|0x18000000
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
multiline_comment|/* CerfPDA Serial */
macro_line|#endif
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|cerf_map_io
r_static
r_void
id|__init
id|cerf_map_io
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
id|cerf_io_desc
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
macro_line|#ifdef CONFIG_SA1100_CERF_IRDA_ENABLED
id|sa1100_register_uart
c_func
(paren
l_int|1
comma
l_int|1
)paren
suffix:semicolon
macro_line|#else
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
l_int|1
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* set some GPDR bits here while it&squot;s safe */
id|GPDR
op_or_assign
id|GPIO_CF_RESET
suffix:semicolon
macro_line|#ifdef CONFIG_SA1100_CERF_CPLD
id|GPDR
op_or_assign
id|GPIO_PWR_SHUTDOWN
suffix:semicolon
macro_line|#endif
)brace
id|MACHINE_START
c_func
(paren
id|CERF
comma
l_string|&quot;Intrinsyc&squot;s Cerf Family of Products&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;support@intrinsyc.com&quot;
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
id|cerf_map_io
)paren
id|INITIRQ
c_func
(paren
id|cerf_init_irq
)paren
id|MACHINE_END
eof
