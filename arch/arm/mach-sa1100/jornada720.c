multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/jornada720.c&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
macro_line|#include &quot;sa1111.h&quot;
DECL|macro|JORTUCR_VAL
mdefine_line|#define JORTUCR_VAL&t;0x20000400
DECL|macro|JORSKCR_INIT
mdefine_line|#define JORSKCR_INIT&t;0x00002081&t;/* Turn off VCO to enable PLL, set Ready En and enable nOE assertion from DC */
DECL|macro|JORSKCR_RCLK
mdefine_line|#define JORSKCR_RCLK&t;0x00002083&t;/* Add turning on RCLK to above */
DECL|macro|JORSKCR_VAL
mdefine_line|#define JORSKCR_VAL&t;0x0000001B&t;/* sets the 1101 control register to on */
DECL|function|jornada720_init
r_static
r_int
id|__init
id|jornada720_init
c_func
(paren
r_void
)paren
(brace
id|GPDR
op_or_assign
id|GPIO_GPIO20
suffix:semicolon
id|TUCR
op_assign
id|JORTUCR_VAL
suffix:semicolon
multiline_comment|/* set the oscillator out to the SA-1101 */
id|GPSR
op_assign
id|GPIO_GPIO20
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|GPCR
op_assign
id|GPIO_GPIO20
suffix:semicolon
id|udelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|GPSR
op_assign
id|GPIO_GPIO20
suffix:semicolon
id|udelay
c_func
(paren
l_int|20
)paren
suffix:semicolon
id|SKCR
op_assign
id|JORSKCR_INIT
suffix:semicolon
multiline_comment|/* Turn on the PLL, enable Ready and enable nOE assertion from DC */
id|mdelay
c_func
(paren
l_int|100
)paren
suffix:semicolon
id|SBI_SKCR
op_assign
id|JORSKCR_RCLK
suffix:semicolon
multiline_comment|/* turn on the RCLOCK */
id|SBI_SMCR
op_assign
l_int|0x35
suffix:semicolon
multiline_comment|/* initialize the SMC (debug SA-1111 reset */
id|PCCR
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* initialize the S2MC (debug SA-1111 reset) */
multiline_comment|/* LDD4 is speaker, LDD3 is microphone */
id|PPSR
op_and_assign
op_complement
(paren
id|PPC_LDD3
op_or
id|PPC_LDD4
)paren
suffix:semicolon
id|PPDR
op_or_assign
id|PPC_LDD3
op_or
id|PPC_LDD4
suffix:semicolon
multiline_comment|/* initialize extra IRQs */
id|set_GPIO_IRQ_edge
c_func
(paren
id|GPIO_GPIO1
comma
id|GPIO_RISING_EDGE
)paren
suffix:semicolon
id|sa1111_init_irq
c_func
(paren
id|IRQ_GPIO1
)paren
suffix:semicolon
multiline_comment|/* chained on GPIO 1 */
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|jornada720_init
id|__initcall
c_func
(paren
id|jornada720_init
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|jornada720_io_desc
(braket
)braket
id|__initdata
op_assign
(brace
multiline_comment|/* virtual     physical    length      type */
(brace
l_int|0xf0000000
comma
l_int|0x48000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Epson registers */
(brace
l_int|0xf1000000
comma
l_int|0x48200000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
comma
multiline_comment|/* Epson frame buffer */
(brace
l_int|0xf4000000
comma
l_int|0x40000000
comma
l_int|0x00100000
comma
id|MT_DEVICE
)brace
multiline_comment|/* SA-1111 */
)brace
suffix:semicolon
DECL|function|jornada720_map_io
r_static
r_void
id|__init
id|jornada720_map_io
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
id|jornada720_io_desc
comma
id|ARRAY_SIZE
c_func
(paren
id|jornada720_io_desc
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
id|JORNADA720
comma
l_string|&quot;HP Jornada 720&quot;
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
id|jornada720_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
