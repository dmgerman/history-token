multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 2001, 2002 Ralf Baechle&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/kdev_t.h&gt;
macro_line|#include &lt;linux/major.h&gt;
macro_line|#include &lt;linux/termios.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/tty.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/semaphore.h&gt;
macro_line|#include &lt;asm/sn/addrs.h&gt;
macro_line|#include &lt;asm/sn/sn0/hub.h&gt;
macro_line|#include &lt;asm/sn/klconfig.h&gt;
macro_line|#include &lt;asm/sn/ioc3.h&gt;
macro_line|#include &lt;asm/sn/sn_private.h&gt;
macro_line|#include &lt;linux/serial.h&gt;
macro_line|#include &lt;linux/serial_core.h&gt;
DECL|macro|IOC3_CLK
mdefine_line|#define IOC3_CLK&t;(22000000 / 3)
DECL|macro|IOC3_FLAGS
mdefine_line|#define IOC3_FLAGS&t;(0)
DECL|function|console_uart
r_static
r_inline
r_struct
id|ioc3_uartregs
op_star
id|console_uart
c_func
(paren
r_void
)paren
(brace
r_struct
id|ioc3
op_star
id|ioc3
suffix:semicolon
id|ioc3
op_assign
(paren
r_struct
id|ioc3
op_star
)paren
id|KL_CONFIG_CH_CONS_INFO
c_func
(paren
id|get_nasid
c_func
(paren
)paren
)paren
op_member_access_from_pointer
id|memory_base
suffix:semicolon
r_return
op_amp
id|ioc3-&gt;sregs.uarta
suffix:semicolon
)brace
DECL|function|prom_putchar
r_void
id|prom_putchar
c_func
(paren
r_char
id|c
)paren
(brace
r_struct
id|ioc3_uartregs
op_star
id|uart
op_assign
id|console_uart
c_func
(paren
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|uart-&gt;iu_lsr
op_amp
l_int|0x20
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|uart-&gt;iu_thr
op_assign
id|c
suffix:semicolon
)brace
DECL|function|prom_getchar
r_char
id|__init
id|prom_getchar
c_func
(paren
r_void
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ioc3_console_probe
r_static
r_void
r_inline
id|ioc3_console_probe
c_func
(paren
r_void
)paren
(brace
r_struct
id|uart_port
id|up
suffix:semicolon
multiline_comment|/*&n;&t; * Register to interrupt zero because we share the interrupt with&n;&t; * the serial driver which we don&squot;t properly support yet.&n;&t; */
id|memset
c_func
(paren
op_amp
id|up
comma
l_int|0
comma
r_sizeof
(paren
id|up
)paren
)paren
suffix:semicolon
id|up.membase
op_assign
(paren
r_int
r_char
op_star
)paren
id|console_uart
c_func
(paren
)paren
suffix:semicolon
id|up.irq
op_assign
l_int|0
suffix:semicolon
id|up.uartclk
op_assign
id|IOC3_CLK
suffix:semicolon
id|up.regshift
op_assign
l_int|0
suffix:semicolon
id|up.iotype
op_assign
id|UPIO_MEM
suffix:semicolon
id|up.flags
op_assign
id|IOC3_FLAGS
suffix:semicolon
id|up.line
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|early_serial_setup
c_func
(paren
op_amp
id|up
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;Early serial init of port 0 failed&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|ip27_setup_console
id|__init
r_void
id|ip27_setup_console
c_func
(paren
r_void
)paren
(brace
id|ioc3_console_probe
c_func
(paren
)paren
suffix:semicolon
)brace
eof
