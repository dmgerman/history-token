multiline_comment|/*&n; * COM1 NS16550 support&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/serialP.h&gt;
macro_line|#include &lt;linux/serial_reg.h&gt;
macro_line|#include &lt;asm/serial.h&gt;
DECL|macro|SERIAL_BAUD
mdefine_line|#define SERIAL_BAUD&t;9600
r_extern
r_void
id|outb
c_func
(paren
r_int
id|port
comma
r_int
r_char
id|val
)paren
suffix:semicolon
r_extern
r_int
r_char
id|inb
c_func
(paren
r_int
id|port
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ISA_io
suffix:semicolon
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
multiline_comment|/* Defined in &lt;asm/serial.h&gt; */
)brace
suffix:semicolon
DECL|variable|shift
r_static
r_int
id|shift
suffix:semicolon
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
id|inb
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
id|outb
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
l_int|0x80
)paren
suffix:semicolon
id|dlm
op_assign
id|inb
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
multiline_comment|/*&n;&t; * Test if serial port is unconfigured.&n;&t; * We assume that no-one uses less than 110 baud or&n;&t; * less than 7 bits per character these days.&n;&t; *  -- paulus.&n;&t; */
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
multiline_comment|/* port is configured, put the old LCR back */
id|outb
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
r_else
(brace
multiline_comment|/* Input clock. */
id|outb
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
id|BASE_BAUD
op_div
id|SERIAL_BAUD
)paren
)paren
suffix:semicolon
id|outb
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
id|BASE_BAUD
op_div
id|SERIAL_BAUD
)paren
op_rshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* 8 data, 1 stop, no parity */
id|outb
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
id|outb
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
)brace
multiline_comment|/* Clear &amp; enable FIFOs */
id|outb
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
id|inb
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
id|outb
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
id|inb
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
id|inb
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
id|inb
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
eof
