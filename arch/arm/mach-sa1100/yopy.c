multiline_comment|/*&n; * linux/arch/arm/mach-sa1100/yopy.c&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/hardware.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/mach/arch.h&gt;
macro_line|#include &lt;asm/mach/map.h&gt;
macro_line|#include &lt;asm/mach/serial_sa1100.h&gt;
macro_line|#include &quot;generic.h&quot;
DECL|variable|egpio_lock
r_static
id|spinlock_t
id|egpio_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
DECL|variable|yopy_egpio
r_static
r_int
r_int
id|yopy_egpio
op_assign
id|GPIO_MASK
c_func
(paren
id|GPIO_CF_RESET
)paren
op_or
id|GPIO_MASK
c_func
(paren
id|GPIO_CLKDIV_CLR1
)paren
op_or
id|GPIO_MASK
c_func
(paren
id|GPIO_CLKDIV_CLR2
)paren
op_or
id|GPIO_MASK
c_func
(paren
id|GPIO_SPEAKER_MUTE
)paren
op_or
id|GPIO_MASK
c_func
(paren
id|GPIO_AUDIO_OPAMP_POWER
)paren
suffix:semicolon
DECL|function|yopy_gpio_test
r_int
id|yopy_gpio_test
c_func
(paren
r_int
r_int
id|gpio
)paren
(brace
r_return
(paren
(paren
id|yopy_egpio
op_amp
(paren
l_int|1
op_lshift
id|gpio
)paren
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|yopy_gpio_set
r_void
id|yopy_gpio_set
c_func
(paren
r_int
r_int
id|gpio
comma
r_int
id|level
)paren
(brace
r_int
r_int
id|flags
comma
id|mask
suffix:semicolon
id|mask
op_assign
l_int|1
op_lshift
id|gpio
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|egpio_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|level
)paren
id|yopy_egpio
op_or_assign
id|mask
suffix:semicolon
r_else
id|yopy_egpio
op_and_assign
op_complement
id|mask
suffix:semicolon
id|YOPY_EGPIO
op_assign
id|yopy_egpio
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|egpio_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|variable|yopy_gpio_test
id|EXPORT_SYMBOL
c_func
(paren
id|yopy_gpio_test
)paren
suffix:semicolon
DECL|variable|yopy_gpio_set
id|EXPORT_SYMBOL
c_func
(paren
id|yopy_gpio_set
)paren
suffix:semicolon
DECL|function|yopy_hw_init
r_static
r_int
id|__init
id|yopy_hw_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|machine_is_yopy
c_func
(paren
)paren
)paren
(brace
id|YOPY_EGPIO
op_assign
id|yopy_egpio
suffix:semicolon
multiline_comment|/* Enable Output */
id|PPDR
op_or_assign
id|PPC_L_BIAS
suffix:semicolon
id|PSDR
op_and_assign
op_complement
id|PPC_L_BIAS
suffix:semicolon
id|PPSR
op_or_assign
id|PPC_L_BIAS
suffix:semicolon
id|YOPY_EGPIO
op_assign
id|yopy_egpio
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|yopy_hw_init
id|__initcall
c_func
(paren
id|yopy_hw_init
)paren
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|map_desc
id|yopy_io_desc
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
l_int|0x04000000
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
multiline_comment|/* Flash 0 */
(brace
l_int|0xec000000
comma
l_int|0x08000000
comma
l_int|0x04000000
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
multiline_comment|/* Flash 1 */
(brace
l_int|0xf0000000
comma
l_int|0x48000000
comma
l_int|0x00300000
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
multiline_comment|/* LCD */
(brace
l_int|0xf1000000
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
multiline_comment|/* EGPIO */
id|LAST_DESC
)brace
suffix:semicolon
DECL|function|yopy_map_io
r_static
r_void
id|__init
id|yopy_map_io
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
id|yopy_io_desc
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
id|set_GPIO_IRQ_edge
c_func
(paren
id|GPIO_UCB1200_IRQ
comma
id|GPIO_RISING_EDGE
)paren
suffix:semicolon
)brace
id|MACHINE_START
c_func
(paren
id|YOPY
comma
l_string|&quot;Yopy&quot;
)paren
id|MAINTAINER
c_func
(paren
l_string|&quot;G.Mate, Inc.&quot;
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
id|yopy_map_io
)paren
id|INITIRQ
c_func
(paren
id|sa1100_init_irq
)paren
id|MACHINE_END
eof
