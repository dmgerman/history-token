macro_line|#include &lt;linux/console.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/* Simple VGA output */
DECL|macro|VGABASE
mdefine_line|#define VGABASE&t;&t;0xffffffff800b8000UL
DECL|macro|MAX_YPOS
mdefine_line|#define MAX_YPOS&t;25
DECL|macro|MAX_XPOS
mdefine_line|#define MAX_XPOS&t;80
DECL|variable|current_ypos
DECL|variable|current_xpos
r_static
r_int
id|current_ypos
op_assign
l_int|1
comma
id|current_xpos
op_assign
l_int|0
suffix:semicolon
DECL|function|early_vga_write
r_static
r_void
id|early_vga_write
c_func
(paren
r_struct
id|console
op_star
id|con
comma
r_const
r_char
op_star
id|str
comma
r_int
id|n
)paren
(brace
r_char
id|c
suffix:semicolon
r_int
id|i
comma
id|k
comma
id|j
suffix:semicolon
r_while
c_loop
(paren
(paren
id|c
op_assign
op_star
id|str
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
op_logical_and
id|n
op_decrement
OG
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|current_ypos
op_ge
id|MAX_YPOS
)paren
(brace
multiline_comment|/* scroll 1 line up */
r_for
c_loop
(paren
id|k
op_assign
l_int|1
comma
id|j
op_assign
l_int|0
suffix:semicolon
id|k
OL
id|MAX_YPOS
suffix:semicolon
id|k
op_increment
comma
id|j
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_XPOS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|writew
c_func
(paren
id|readw
c_func
(paren
id|VGABASE
op_plus
l_int|2
op_star
(paren
id|MAX_XPOS
op_star
id|k
op_plus
id|i
)paren
)paren
comma
id|VGABASE
op_plus
l_int|2
op_star
(paren
id|MAX_XPOS
op_star
id|j
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|MAX_XPOS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|writew
c_func
(paren
l_int|0x720
comma
id|VGABASE
op_plus
l_int|2
op_star
(paren
id|MAX_XPOS
op_star
id|j
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
id|current_ypos
op_assign
id|MAX_YPOS
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
id|current_xpos
op_assign
l_int|0
suffix:semicolon
id|current_ypos
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|c
op_ne
l_char|&squot;&bslash;r&squot;
)paren
(brace
id|writew
c_func
(paren
(paren
(paren
l_int|0x7
op_lshift
l_int|8
)paren
op_or
(paren
r_int
r_int
)paren
id|c
)paren
comma
id|VGABASE
op_plus
l_int|2
op_star
(paren
id|MAX_XPOS
op_star
id|current_ypos
op_plus
id|current_xpos
op_increment
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|current_xpos
op_ge
id|MAX_XPOS
)paren
(brace
id|current_xpos
op_assign
l_int|0
suffix:semicolon
id|current_ypos
op_increment
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|variable|early_vga_console
r_static
r_struct
id|console
id|early_vga_console
op_assign
(brace
id|name
suffix:colon
l_string|&quot;earlyvga&quot;
comma
id|write
suffix:colon
id|early_vga_write
comma
id|flags
suffix:colon
id|CON_PRINTBUFFER
comma
id|index
suffix:colon
op_minus
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/* Serial functions losely based on a similar package from Klaus P. Gerlicher */
DECL|variable|early_serial_base
r_int
id|early_serial_base
op_assign
l_int|0x3f8
suffix:semicolon
multiline_comment|/* ttyS0 */
DECL|macro|XMTRDY
mdefine_line|#define XMTRDY          0x20
DECL|macro|DLAB
mdefine_line|#define DLAB&t;&t;0x80
DECL|macro|TXR
mdefine_line|#define TXR             0       /*  Transmit register (WRITE) */
DECL|macro|RXR
mdefine_line|#define RXR             0       /*  Receive register  (READ)  */
DECL|macro|IER
mdefine_line|#define IER             1       /*  Interrupt Enable          */
DECL|macro|IIR
mdefine_line|#define IIR             2       /*  Interrupt ID              */
DECL|macro|FCR
mdefine_line|#define FCR             2       /*  FIFO control              */
DECL|macro|LCR
mdefine_line|#define LCR             3       /*  Line control              */
DECL|macro|MCR
mdefine_line|#define MCR             4       /*  Modem control             */
DECL|macro|LSR
mdefine_line|#define LSR             5       /*  Line Status               */
DECL|macro|MSR
mdefine_line|#define MSR             6       /*  Modem Status              */
DECL|macro|DLL
mdefine_line|#define DLL             0       /*  Divisor Latch Low         */
DECL|macro|DLH
mdefine_line|#define DLH             1       /*  Divisor latch High        */
DECL|function|early_serial_putc
r_static
r_int
id|early_serial_putc
c_func
(paren
r_int
r_char
id|ch
)paren
(brace
r_int
id|timeout
op_assign
l_int|0xffff
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|early_serial_base
op_plus
id|LSR
)paren
op_amp
id|XMTRDY
)paren
op_eq
l_int|0
op_logical_and
op_decrement
id|timeout
)paren
id|rep_nop
c_func
(paren
)paren
suffix:semicolon
id|outb
c_func
(paren
id|ch
comma
id|early_serial_base
op_plus
id|TXR
)paren
suffix:semicolon
r_return
id|timeout
ques
c_cond
l_int|0
suffix:colon
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|early_serial_write
r_static
r_void
id|early_serial_write
c_func
(paren
r_struct
id|console
op_star
id|con
comma
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
(brace
r_while
c_loop
(paren
op_star
id|s
op_logical_and
id|n
op_decrement
OG
l_int|0
)paren
(brace
id|early_serial_putc
c_func
(paren
op_star
id|s
)paren
suffix:semicolon
r_if
c_cond
(paren
op_star
id|s
op_eq
l_char|&squot;&bslash;n&squot;
)paren
id|early_serial_putc
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|s
op_increment
suffix:semicolon
)brace
)brace
DECL|function|early_serial_init
r_static
id|__init
r_void
id|early_serial_init
c_func
(paren
r_char
op_star
id|opt
)paren
(brace
r_int
r_char
id|c
suffix:semicolon
r_int
id|divisor
comma
id|baud
op_assign
l_int|38400
suffix:semicolon
r_char
op_star
id|s
comma
op_star
id|e
suffix:semicolon
r_if
c_cond
(paren
op_star
id|opt
op_eq
l_char|&squot;,&squot;
)paren
op_increment
id|opt
suffix:semicolon
id|s
op_assign
id|strsep
c_func
(paren
op_amp
id|opt
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_ne
l_int|NULL
)paren
(brace
r_int
id|port
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|s
comma
l_string|&quot;0x&quot;
comma
l_int|2
)paren
)paren
id|early_serial_base
op_assign
id|simple_strtoul
c_func
(paren
id|s
comma
op_amp
id|e
comma
l_int|16
)paren
suffix:semicolon
r_else
(brace
r_static
r_int
id|bases
(braket
)braket
op_assign
(brace
l_int|0x3f8
comma
l_int|0x2f8
)brace
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|s
comma
l_string|&quot;ttyS&quot;
comma
l_int|4
)paren
)paren
id|s
op_add_assign
l_int|4
suffix:semicolon
id|port
op_assign
id|simple_strtoul
c_func
(paren
id|s
comma
op_amp
id|e
comma
l_int|10
)paren
suffix:semicolon
r_if
c_cond
(paren
id|port
OG
l_int|1
op_logical_or
id|s
op_eq
id|e
)paren
id|port
op_assign
l_int|0
suffix:semicolon
id|early_serial_base
op_assign
id|bases
(braket
id|port
)braket
suffix:semicolon
)brace
)brace
id|outb
c_func
(paren
l_int|0x3
comma
id|early_serial_base
op_plus
id|LCR
)paren
suffix:semicolon
multiline_comment|/* 8n1 */
id|outb
c_func
(paren
l_int|0
comma
id|early_serial_base
op_plus
id|IER
)paren
suffix:semicolon
multiline_comment|/* no interrupt */
id|outb
c_func
(paren
l_int|0
comma
id|early_serial_base
op_plus
id|FCR
)paren
suffix:semicolon
multiline_comment|/* no fifo */
id|outb
c_func
(paren
l_int|0x3
comma
id|early_serial_base
op_plus
id|MCR
)paren
suffix:semicolon
multiline_comment|/* DTR + RTS */
id|s
op_assign
id|strsep
c_func
(paren
op_amp
id|opt
comma
l_string|&quot;,&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
op_ne
l_int|NULL
)paren
(brace
id|baud
op_assign
id|simple_strtoul
c_func
(paren
id|s
comma
op_amp
id|e
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|baud
op_eq
l_int|0
op_logical_or
id|s
op_eq
id|e
)paren
id|baud
op_assign
l_int|38400
suffix:semicolon
)brace
id|divisor
op_assign
l_int|115200
op_div
id|baud
suffix:semicolon
id|c
op_assign
id|inb
c_func
(paren
id|early_serial_base
op_plus
id|LCR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|c
op_or
id|DLAB
comma
id|early_serial_base
op_plus
id|LCR
)paren
suffix:semicolon
id|outb
c_func
(paren
id|divisor
op_amp
l_int|0xff
comma
id|early_serial_base
op_plus
id|DLL
)paren
suffix:semicolon
id|outb
c_func
(paren
(paren
id|divisor
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
comma
id|early_serial_base
op_plus
id|DLH
)paren
suffix:semicolon
id|outb
c_func
(paren
id|c
op_amp
op_complement
id|DLAB
comma
id|early_serial_base
op_plus
id|LCR
)paren
suffix:semicolon
)brace
DECL|variable|early_serial_console
r_static
r_struct
id|console
id|early_serial_console
op_assign
(brace
id|name
suffix:colon
l_string|&quot;earlyser&quot;
comma
id|write
suffix:colon
id|early_serial_write
comma
id|flags
suffix:colon
id|CON_PRINTBUFFER
comma
id|index
suffix:colon
op_minus
l_int|1
comma
)brace
suffix:semicolon
multiline_comment|/* Direct interface for emergencies */
DECL|variable|early_console
r_struct
id|console
op_star
id|early_console
op_assign
op_amp
id|early_vga_console
suffix:semicolon
DECL|variable|early_console_initialized
r_static
r_int
id|early_console_initialized
op_assign
l_int|0
suffix:semicolon
DECL|function|early_printk
r_void
id|early_printk
c_func
(paren
r_const
r_char
op_star
id|fmt
comma
dot
dot
dot
)paren
(brace
r_char
id|buf
(braket
l_int|512
)braket
suffix:semicolon
r_int
id|n
suffix:semicolon
id|va_list
id|ap
suffix:semicolon
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|n
op_assign
id|vsnprintf
c_func
(paren
id|buf
comma
l_int|512
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|early_console
op_member_access_from_pointer
id|write
c_func
(paren
id|early_console
comma
id|buf
comma
id|n
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
DECL|variable|keep_early
r_static
r_int
id|keep_early
suffix:semicolon
DECL|function|setup_early_printk
r_int
id|__init
id|setup_early_printk
c_func
(paren
r_char
op_star
id|opt
)paren
(brace
r_char
op_star
id|space
suffix:semicolon
r_char
id|buf
(braket
l_int|256
)braket
suffix:semicolon
r_if
c_cond
(paren
id|early_console_initialized
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|strncpy
c_func
(paren
id|buf
comma
id|opt
comma
l_int|256
)paren
suffix:semicolon
id|buf
(braket
l_int|255
)braket
op_assign
l_int|0
suffix:semicolon
id|space
op_assign
id|strchr
c_func
(paren
id|buf
comma
l_char|&squot; &squot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|space
)paren
op_star
id|space
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|buf
comma
l_string|&quot;keep&quot;
)paren
)paren
id|keep_early
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buf
comma
l_string|&quot;serial&quot;
comma
l_int|6
)paren
)paren
(brace
id|early_serial_init
c_func
(paren
id|buf
op_plus
l_int|6
)paren
suffix:semicolon
id|early_console
op_assign
op_amp
id|early_serial_console
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|buf
comma
l_string|&quot;vga&quot;
comma
l_int|3
)paren
)paren
(brace
id|early_console
op_assign
op_amp
id|early_vga_console
suffix:semicolon
)brace
r_else
(brace
id|early_console
op_assign
l_int|NULL
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|early_console_initialized
op_assign
l_int|1
suffix:semicolon
id|register_console
c_func
(paren
id|early_console
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|disable_early_printk
r_void
id|__init
id|disable_early_printk
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|early_console_initialized
op_logical_or
op_logical_neg
id|early_console
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|keep_early
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;disabling early console...&bslash;n&quot;
)paren
suffix:semicolon
id|unregister_console
c_func
(paren
id|early_console
)paren
suffix:semicolon
id|early_console_initialized
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;keeping early console.&bslash;n&quot;
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* syntax: earlyprintk=vga&n;           earlyprintk=serial[,ttySn[,baudrate]] &n;   Append ,keep to not disable it when the real console takes over.&n;   Only vga or serial at a time, not both.&n;   Currently only ttyS0 and ttyS1 are supported. &n;   Interaction with the standard serial driver is not very good. &n;   The VGA output is eventually overwritten by the real console. */
id|__setup
c_func
(paren
l_string|&quot;earlyprintk=&quot;
comma
id|setup_early_printk
)paren
suffix:semicolon
eof
