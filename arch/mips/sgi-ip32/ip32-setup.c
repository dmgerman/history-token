multiline_comment|/*&n; * IP32 basic setup&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2000 Harald Koerfgen&n; * Copyright (C) 2002, 03 Ilya A. Volynets&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/mc146818rtc.h&gt;
macro_line|#include &lt;linux/param.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/mc146818-time.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
macro_line|#include &lt;asm/mmu_context.h&gt;
macro_line|#include &lt;asm/sgialib.h&gt;
macro_line|#include &lt;asm/time.h&gt;
macro_line|#include &lt;asm/traps.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/ip32/crime.h&gt;
macro_line|#include &lt;asm/ip32/mace.h&gt;
macro_line|#include &lt;asm/ip32/ip32_ints.h&gt;
r_extern
r_void
id|ip32_be_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|crime_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SGI_O2MACE_ETH
multiline_comment|/*&n; * This is taken care of in here &squot;cause they say using Arc later on is&n; * problematic&n; */
r_extern
r_char
id|o2meth_eaddr
(braket
l_int|8
)braket
suffix:semicolon
DECL|function|str2hexnum
r_static
r_inline
r_int
r_char
id|str2hexnum
c_func
(paren
r_int
r_char
id|c
)paren
(brace
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;0&squot;
op_logical_and
id|c
op_le
l_char|&squot;9&squot;
)paren
r_return
id|c
op_minus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|c
op_ge
l_char|&squot;a&squot;
op_logical_and
id|c
op_le
l_char|&squot;f&squot;
)paren
r_return
id|c
op_minus
l_char|&squot;a&squot;
op_plus
l_int|10
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* foo */
)brace
DECL|function|str2eaddr
r_static
r_inline
r_void
id|str2eaddr
c_func
(paren
r_int
r_char
op_star
id|ea
comma
r_int
r_char
op_star
id|str
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|num
suffix:semicolon
r_if
c_cond
(paren
op_star
id|str
op_eq
l_char|&squot;:&squot;
)paren
(brace
id|str
op_increment
suffix:semicolon
)brace
id|num
op_assign
id|str2hexnum
c_func
(paren
op_star
id|str
op_increment
)paren
op_lshift
l_int|4
suffix:semicolon
id|num
op_or_assign
(paren
id|str2hexnum
c_func
(paren
op_star
id|str
op_increment
)paren
)paren
suffix:semicolon
id|ea
(braket
id|i
)braket
op_assign
id|num
suffix:semicolon
)brace
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SERIAL_8250
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
r_extern
r_int
id|early_serial_setup
c_func
(paren
r_struct
id|uart_port
op_star
id|port
)paren
suffix:semicolon
DECL|macro|STD_COM_FLAGS
mdefine_line|#define STD_COM_FLAGS (ASYNC_SKIP_TEST)
DECL|macro|BASE_BAUD
mdefine_line|#define BASE_BAUD (1843200 / 16)
macro_line|#endif /* CONFIG_SERIAL_8250 */
multiline_comment|/* An arbitrary time; this can be decreased if reliability looks good */
DECL|macro|WAIT_MS
mdefine_line|#define WAIT_MS 10
DECL|function|ip32_time_init
r_void
id|__init
id|ip32_time_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Calibrating system timer... &quot;
)paren
suffix:semicolon
id|write_c0_count
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|crime_write
c_func
(paren
l_int|0
comma
id|CRIME_TIMER
)paren
suffix:semicolon
r_while
c_loop
(paren
id|crime_read
c_func
(paren
id|CRIME_TIMER
)paren
OL
id|CRIME_MASTER_FREQ
op_star
id|WAIT_MS
op_div
l_int|1000
)paren
suffix:semicolon
id|mips_hpt_frequency
op_assign
id|read_c0_count
c_func
(paren
)paren
op_star
l_int|1000
op_div
id|WAIT_MS
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%d MHz CPU detected&bslash;n&quot;
comma
id|mips_hpt_frequency
op_star
l_int|2
op_div
l_int|1000000
)paren
suffix:semicolon
)brace
DECL|function|ip32_timer_setup
r_void
id|__init
id|ip32_timer_setup
c_func
(paren
r_struct
id|irqaction
op_star
id|irq
)paren
(brace
id|irq-&gt;handler
op_assign
id|no_action
suffix:semicolon
id|setup_irq
c_func
(paren
id|IP32_R4K_TIMER_IRQ
comma
id|irq
)paren
suffix:semicolon
)brace
DECL|function|ip32_setup
r_static
r_int
id|__init
id|ip32_setup
c_func
(paren
r_void
)paren
(brace
id|set_io_port_base
c_func
(paren
(paren
r_int
r_int
)paren
id|ioremap
c_func
(paren
id|MACEPCI_LOW_IO
comma
l_int|0x2000000
)paren
)paren
suffix:semicolon
id|crime_init
c_func
(paren
)paren
suffix:semicolon
id|board_be_init
op_assign
id|ip32_be_init
suffix:semicolon
id|rtc_get_time
op_assign
id|mc146818_get_cmos_time
suffix:semicolon
id|rtc_set_mmss
op_assign
id|mc146818_set_rtc_mmss
suffix:semicolon
id|board_time_init
op_assign
id|ip32_time_init
suffix:semicolon
id|board_timer_setup
op_assign
id|ip32_timer_setup
suffix:semicolon
macro_line|#ifdef CONFIG_SERIAL_8250
(brace
r_static
r_struct
id|uart_port
id|o2_serial
(braket
l_int|2
)braket
suffix:semicolon
id|memset
c_func
(paren
id|o2_serial
comma
l_int|0
comma
r_sizeof
(paren
id|o2_serial
)paren
)paren
suffix:semicolon
id|o2_serial
(braket
l_int|0
)braket
dot
id|type
op_assign
id|PORT_16550A
suffix:semicolon
id|o2_serial
(braket
l_int|0
)braket
dot
id|line
op_assign
l_int|0
suffix:semicolon
id|o2_serial
(braket
l_int|0
)braket
dot
id|irq
op_assign
id|MACEISA_SERIAL1_IRQ
suffix:semicolon
id|o2_serial
(braket
l_int|0
)braket
dot
id|flags
op_assign
id|STD_COM_FLAGS
op_or
id|UPF_RESOURCES
suffix:semicolon
id|o2_serial
(braket
l_int|0
)braket
dot
id|uartclk
op_assign
id|BASE_BAUD
op_star
l_int|16
suffix:semicolon
id|o2_serial
(braket
l_int|0
)braket
dot
id|iotype
op_assign
id|UPIO_MEM
suffix:semicolon
id|o2_serial
(braket
l_int|0
)braket
dot
id|membase
op_assign
(paren
r_char
op_star
)paren
op_amp
id|mace-&gt;isa.serial1
suffix:semicolon
id|o2_serial
(braket
l_int|0
)braket
dot
id|fifosize
op_assign
l_int|14
suffix:semicolon
multiline_comment|/* How much to shift register offset by. Each UART register&n;&t;&t; * is replicated over 256 byte space */
id|o2_serial
(braket
l_int|0
)braket
dot
id|regshift
op_assign
l_int|8
suffix:semicolon
id|o2_serial
(braket
l_int|1
)braket
dot
id|type
op_assign
id|PORT_16550A
suffix:semicolon
id|o2_serial
(braket
l_int|1
)braket
dot
id|line
op_assign
l_int|1
suffix:semicolon
id|o2_serial
(braket
l_int|1
)braket
dot
id|irq
op_assign
id|MACEISA_SERIAL2_IRQ
suffix:semicolon
id|o2_serial
(braket
l_int|1
)braket
dot
id|flags
op_assign
id|STD_COM_FLAGS
op_or
id|UPF_RESOURCES
suffix:semicolon
id|o2_serial
(braket
l_int|1
)braket
dot
id|uartclk
op_assign
id|BASE_BAUD
op_star
l_int|16
suffix:semicolon
id|o2_serial
(braket
l_int|1
)braket
dot
id|iotype
op_assign
id|UPIO_MEM
suffix:semicolon
id|o2_serial
(braket
l_int|1
)braket
dot
id|membase
op_assign
(paren
r_char
op_star
)paren
op_amp
id|mace-&gt;isa.serial2
suffix:semicolon
id|o2_serial
(braket
l_int|1
)braket
dot
id|fifosize
op_assign
l_int|14
suffix:semicolon
id|o2_serial
(braket
l_int|1
)braket
dot
id|regshift
op_assign
l_int|8
suffix:semicolon
id|early_serial_setup
c_func
(paren
op_amp
id|o2_serial
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|early_serial_setup
c_func
(paren
op_amp
id|o2_serial
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_SGI_O2MACE_ETH
(brace
r_char
op_star
id|mac
op_assign
id|ArcGetEnvironmentVariable
c_func
(paren
l_string|&quot;eaddr&quot;
)paren
suffix:semicolon
id|str2eaddr
c_func
(paren
id|o2meth_eaddr
comma
id|mac
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if defined(CONFIG_SERIAL_CORE_CONSOLE)
(brace
r_char
op_star
id|con
op_assign
id|ArcGetEnvironmentVariable
c_func
(paren
l_string|&quot;console&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|con
op_logical_and
op_star
id|con
op_eq
l_char|&squot;d&squot;
)paren
(brace
r_static
r_char
id|options
(braket
l_int|8
)braket
suffix:semicolon
r_char
op_star
id|baud
op_assign
id|ArcGetEnvironmentVariable
c_func
(paren
l_string|&quot;dbaud&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|baud
)paren
id|strcpy
c_func
(paren
id|options
comma
id|baud
)paren
suffix:semicolon
id|add_preferred_console
c_func
(paren
l_string|&quot;ttyS&quot;
comma
op_star
(paren
id|con
op_plus
l_int|1
)paren
op_eq
l_char|&squot;2&squot;
ques
c_cond
l_int|1
suffix:colon
l_int|0
comma
id|baud
ques
c_cond
id|options
suffix:colon
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ip32_setup
id|early_initcall
c_func
(paren
id|ip32_setup
)paren
suffix:semicolon
eof
