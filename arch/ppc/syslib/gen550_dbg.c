multiline_comment|/*&n; * arch/ppc/syslib/gen550_dbg.c&n; *&n; * A library of polled 16550 serial routines.  These are intended to&n; * be used to support progress messages, xmon, kgdb, etc. on a&n; * variety of platforms.&n; *&n; * Adapted from lots of code ripped from the arch/ppc/boot/ polled&n; * 16550 support.&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2002-2003 (c) MontaVista Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/tty.h&gt;&t;&t;/* For linux/serial_core.h */
macro_line|#include &lt;linux/serial_core.h&gt;
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|SERIAL_BAUD
mdefine_line|#define SERIAL_BAUD&t;9600
DECL|variable|rs_table
r_static
r_struct
id|serial_state
id|rs_table
(braket
id|RS_TABLE_SIZE
)braket
op_assign
(brace
id|SERIAL_PORT_DFNS
multiline_comment|/* defined in &lt;asm/serial.h&gt; */
)brace
suffix:semicolon
DECL|variable|serial_outb
r_static
r_void
(paren
op_star
id|serial_outb
)paren
(paren
r_int
r_int
comma
r_int
r_char
)paren
suffix:semicolon
DECL|variable|serial_inb
r_static
r_int
r_int
(paren
op_star
id|serial_inb
)paren
(paren
r_int
r_int
)paren
suffix:semicolon
DECL|variable|shift
r_static
r_int
id|shift
suffix:semicolon
DECL|function|direct_inb
r_int
r_int
id|direct_inb
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_return
id|readb
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|direct_outb
r_void
id|direct_outb
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_char
id|val
)paren
(brace
id|writeb
c_func
(paren
id|val
comma
id|addr
)paren
suffix:semicolon
)brace
DECL|function|io_inb
r_int
r_int
id|io_inb
c_func
(paren
r_int
r_int
id|port
)paren
(brace
r_return
id|inb
c_func
(paren
id|port
)paren
suffix:semicolon
)brace
DECL|function|io_outb
r_void
id|io_outb
c_func
(paren
r_int
r_int
id|port
comma
r_int
r_char
id|val
)paren
(brace
id|outb
c_func
(paren
id|val
comma
id|port
)paren
suffix:semicolon
)brace
DECL|function|serial_init
r_int
r_int
id|serial_init
c_func
(paren
r_int
id|chan
comma
r_void
op_star
id|ignored
)paren
(brace
r_int
r_int
id|com_port
suffix:semicolon
r_int
r_char
id|lcr
comma
id|dlm
suffix:semicolon
multiline_comment|/* We need to find out which type io we&squot;re expecting.  If it&squot;s&n;&t; * &squot;SERIAL_IO_PORT&squot;, we get an offset from the isa_io_base.&n;&t; * If it&squot;s &squot;SERIAL_IO_MEM&squot;, we can the exact location.  -- Tom */
r_switch
c_cond
(paren
id|rs_table
(braket
id|chan
)braket
dot
id|io_type
)paren
(brace
r_case
id|SERIAL_IO_PORT
suffix:colon
id|com_port
op_assign
id|rs_table
(braket
id|chan
)braket
dot
id|port
suffix:semicolon
id|serial_outb
op_assign
id|io_outb
suffix:semicolon
id|serial_inb
op_assign
id|io_inb
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SERIAL_IO_MEM
suffix:colon
id|com_port
op_assign
(paren
r_int
r_int
)paren
id|rs_table
(braket
id|chan
)braket
dot
id|iomem_base
suffix:semicolon
id|serial_outb
op_assign
id|direct_outb
suffix:semicolon
id|serial_inb
op_assign
id|direct_inb
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* We can&squot;t deal with it. */
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* How far apart the registers are. */
id|shift
op_assign
id|rs_table
(braket
id|chan
)braket
dot
id|iomem_reg_shift
suffix:semicolon
multiline_comment|/* save the LCR */
id|lcr
op_assign
id|serial_inb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_LCR
op_lshift
id|shift
)paren
)paren
suffix:semicolon
multiline_comment|/* Access baud rate */
id|serial_outb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_LCR
op_lshift
id|shift
)paren
comma
id|UART_LCR_DLAB
)paren
suffix:semicolon
id|dlm
op_assign
id|serial_inb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_DLM
op_lshift
id|shift
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Test if serial port is unconfigured&n;&t; * We assume that no-one uses less than 110 baud or&n;&t; * less than 7 bits per character these days.&n;&t; *  -- paulus.&n;&t; */
r_if
c_cond
(paren
(paren
id|dlm
op_le
l_int|4
)paren
op_logical_and
(paren
id|lcr
op_amp
l_int|2
)paren
)paren
(brace
multiline_comment|/* port is configured, put the old LCR back */
id|serial_outb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_LCR
op_lshift
id|shift
)paren
comma
id|lcr
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Input clock. */
id|serial_outb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_DLL
op_lshift
id|shift
)paren
comma
(paren
id|rs_table
(braket
id|chan
)braket
dot
id|baud_base
op_div
id|SERIAL_BAUD
)paren
op_amp
l_int|0xFF
)paren
suffix:semicolon
id|serial_outb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_DLM
op_lshift
id|shift
)paren
comma
(paren
id|rs_table
(braket
id|chan
)braket
dot
id|baud_base
op_div
id|SERIAL_BAUD
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* 8 data, 1 stop, no parity */
id|serial_outb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_LCR
op_lshift
id|shift
)paren
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* RTS/DTR */
id|serial_outb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_MCR
op_lshift
id|shift
)paren
comma
l_int|0x03
)paren
suffix:semicolon
multiline_comment|/* Clear &amp; enable FIFOs */
id|serial_outb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_FCR
op_lshift
id|shift
)paren
comma
l_int|0x07
)paren
suffix:semicolon
)brace
r_return
(paren
id|com_port
)paren
suffix:semicolon
)brace
r_void
DECL|function|serial_putc
id|serial_putc
c_func
(paren
r_int
r_int
id|com_port
comma
r_int
r_char
id|c
)paren
(brace
r_while
c_loop
(paren
(paren
id|serial_inb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_LSR
op_lshift
id|shift
)paren
)paren
op_amp
id|UART_LSR_THRE
)paren
op_eq
l_int|0
)paren
suffix:semicolon
id|serial_outb
c_func
(paren
id|com_port
comma
id|c
)paren
suffix:semicolon
)brace
r_int
r_char
DECL|function|serial_getc
id|serial_getc
c_func
(paren
r_int
r_int
id|com_port
)paren
(brace
r_while
c_loop
(paren
(paren
id|serial_inb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_LSR
op_lshift
id|shift
)paren
)paren
op_amp
id|UART_LSR_DR
)paren
op_eq
l_int|0
)paren
suffix:semicolon
r_return
id|serial_inb
c_func
(paren
id|com_port
)paren
suffix:semicolon
)brace
r_int
DECL|function|serial_tstc
id|serial_tstc
c_func
(paren
r_int
r_int
id|com_port
)paren
(brace
r_return
(paren
(paren
id|serial_inb
c_func
(paren
id|com_port
op_plus
(paren
id|UART_LSR
op_lshift
id|shift
)paren
)paren
op_amp
id|UART_LSR_DR
)paren
op_ne
l_int|0
)paren
suffix:semicolon
)brace
r_void
DECL|function|serial_close
id|serial_close
c_func
(paren
r_int
r_int
id|com_port
)paren
(brace
)brace
r_void
DECL|function|gen550_init
id|gen550_init
c_func
(paren
r_int
id|i
comma
r_struct
id|uart_port
op_star
id|serial_req
)paren
(brace
id|rs_table
(braket
id|i
)braket
dot
id|io_type
op_assign
id|serial_req-&gt;iotype
suffix:semicolon
id|rs_table
(braket
id|i
)braket
dot
id|port
op_assign
id|serial_req-&gt;line
suffix:semicolon
id|rs_table
(braket
id|i
)braket
dot
id|iomem_base
op_assign
id|serial_req-&gt;membase
suffix:semicolon
id|rs_table
(braket
id|i
)braket
dot
id|iomem_reg_shift
op_assign
id|serial_req-&gt;regshift
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SERIAL_TEXT_DEBUG
r_void
DECL|function|gen550_progress
id|gen550_progress
c_func
(paren
r_char
op_star
id|s
comma
r_int
r_int
id|hex
)paren
(brace
r_volatile
r_int
r_int
id|progress_debugport
suffix:semicolon
r_volatile
r_char
id|c
suffix:semicolon
id|progress_debugport
op_assign
id|serial_init
c_func
(paren
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
id|serial_putc
c_func
(paren
id|progress_debugport
comma
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_int|0
)paren
id|serial_putc
c_func
(paren
id|progress_debugport
comma
id|c
)paren
suffix:semicolon
id|serial_putc
c_func
(paren
id|progress_debugport
comma
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
id|serial_putc
c_func
(paren
id|progress_debugport
comma
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_SERIAL_TEXT_DEBUG */
eof
