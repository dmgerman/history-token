multiline_comment|/*&n; * NS16550 Serial Port (uart) debugging stuff.&n; *&n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; * NOTE: I am trying to make this code avoid any static data references to&n; *  simplify debugging early boot.  We&squot;ll see how that goes...&n; *&n; * To use this call udbg_init() first.  It will init the uart to 9600 8N1.&n; * You may need to update the COM1 define if your uart is at a different addr.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;stdarg.h&gt;
DECL|macro|WANT_PPCDBG_TAB
mdefine_line|#define WANT_PPCDBG_TAB /* Only defined here */
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
DECL|struct|NS16550
r_struct
id|NS16550
(brace
multiline_comment|/* this struct must be packed */
DECL|member|rbr
r_int
r_char
id|rbr
suffix:semicolon
multiline_comment|/* 0 */
DECL|member|ier
r_int
r_char
id|ier
suffix:semicolon
multiline_comment|/* 1 */
DECL|member|fcr
r_int
r_char
id|fcr
suffix:semicolon
multiline_comment|/* 2 */
DECL|member|lcr
r_int
r_char
id|lcr
suffix:semicolon
multiline_comment|/* 3 */
DECL|member|mcr
r_int
r_char
id|mcr
suffix:semicolon
multiline_comment|/* 4 */
DECL|member|lsr
r_int
r_char
id|lsr
suffix:semicolon
multiline_comment|/* 5 */
DECL|member|msr
r_int
r_char
id|msr
suffix:semicolon
multiline_comment|/* 6 */
DECL|member|scr
r_int
r_char
id|scr
suffix:semicolon
multiline_comment|/* 7 */
)brace
suffix:semicolon
DECL|macro|thr
mdefine_line|#define thr rbr
DECL|macro|iir
mdefine_line|#define iir fcr
DECL|macro|dll
mdefine_line|#define dll rbr
DECL|macro|dlm
mdefine_line|#define dlm ier
DECL|macro|dlab
mdefine_line|#define dlab lcr
DECL|macro|LSR_DR
mdefine_line|#define LSR_DR   0x01  /* Data ready */
DECL|macro|LSR_OE
mdefine_line|#define LSR_OE   0x02  /* Overrun */
DECL|macro|LSR_PE
mdefine_line|#define LSR_PE   0x04  /* Parity error */
DECL|macro|LSR_FE
mdefine_line|#define LSR_FE   0x08  /* Framing error */
DECL|macro|LSR_BI
mdefine_line|#define LSR_BI   0x10  /* Break */
DECL|macro|LSR_THRE
mdefine_line|#define LSR_THRE 0x20  /* Xmit holding register empty */
DECL|macro|LSR_TEMT
mdefine_line|#define LSR_TEMT 0x40  /* Xmitter empty */
DECL|macro|LSR_ERR
mdefine_line|#define LSR_ERR  0x80  /* Error */
DECL|variable|udbg_comport
r_volatile
r_struct
id|NS16550
op_star
id|udbg_comport
suffix:semicolon
r_void
DECL|function|udbg_init_uart
id|udbg_init_uart
c_func
(paren
r_void
op_star
id|comport
)paren
(brace
r_if
c_cond
(paren
id|comport
)paren
(brace
id|udbg_comport
op_assign
(paren
r_struct
id|NS16550
op_star
)paren
id|comport
suffix:semicolon
id|udbg_comport-&gt;lcr
op_assign
l_int|0x00
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|udbg_comport-&gt;ier
op_assign
l_int|0xFF
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|udbg_comport-&gt;ier
op_assign
l_int|0x00
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
id|udbg_comport-&gt;lcr
op_assign
l_int|0x80
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Access baud rate */
id|udbg_comport-&gt;dll
op_assign
l_int|12
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* 1 = 115200,  2 = 57600, 3 = 38400, 12 = 9600 baud */
id|udbg_comport-&gt;dlm
op_assign
l_int|0
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* dll &gt;&gt; 8 which should be zero for fast rates; */
id|udbg_comport-&gt;lcr
op_assign
l_int|0x03
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* 8 data, 1 stop, no parity */
id|udbg_comport-&gt;mcr
op_assign
l_int|0x03
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* RTS/DTR */
id|udbg_comport-&gt;fcr
op_assign
l_int|0x07
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Clear &amp; enable FIFOs */
)brace
)brace
r_void
DECL|function|udbg_putc
id|udbg_putc
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
id|udbg_comport
)paren
(brace
r_while
c_loop
(paren
(paren
id|udbg_comport-&gt;lsr
op_amp
id|LSR_THRE
)paren
op_eq
l_int|0
)paren
multiline_comment|/* wait for idle */
suffix:semicolon
id|udbg_comport-&gt;thr
op_assign
id|c
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_eq
l_char|&squot;&bslash;n&squot;
)paren
(brace
multiline_comment|/* Also put a CR.  This is for convenience. */
r_while
c_loop
(paren
(paren
id|udbg_comport-&gt;lsr
op_amp
id|LSR_THRE
)paren
op_eq
l_int|0
)paren
multiline_comment|/* wait for idle */
suffix:semicolon
id|udbg_comport-&gt;thr
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
id|eieio
c_func
(paren
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|udbg_getc_poll
r_int
id|udbg_getc_poll
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|udbg_comport
)paren
(brace
r_if
c_cond
(paren
(paren
id|udbg_comport-&gt;lsr
op_amp
id|LSR_DR
)paren
op_ne
l_int|0
)paren
r_return
id|udbg_comport-&gt;rbr
suffix:semicolon
r_else
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_int
r_char
DECL|function|udbg_getc
id|udbg_getc
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|udbg_comport
)paren
(brace
r_while
c_loop
(paren
(paren
id|udbg_comport-&gt;lsr
op_amp
id|LSR_DR
)paren
op_eq
l_int|0
)paren
multiline_comment|/* wait for char */
suffix:semicolon
r_return
id|udbg_comport-&gt;rbr
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|udbg_puts
id|udbg_puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|ppc_md.udbg_putc
)paren
(brace
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
id|s
op_logical_and
op_star
id|s
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
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
l_char|&squot;&bslash;0&squot;
)paren
id|ppc_md
dot
id|udbg_putc
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|s
)paren
suffix:semicolon
)brace
)brace
r_int
DECL|function|udbg_write
id|udbg_write
c_func
(paren
r_const
r_char
op_star
id|s
comma
r_int
id|n
)paren
(brace
r_int
id|remain
op_assign
id|n
suffix:semicolon
r_char
id|c
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ppc_md.udbg_putc
)paren
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* stop here for cpuctl */
r_if
c_cond
(paren
id|s
op_logical_and
op_star
id|s
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
r_while
c_loop
(paren
(paren
(paren
id|c
op_assign
op_star
id|s
op_increment
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
op_logical_and
(paren
id|remain
op_decrement
OG
l_int|0
)paren
)paren
(brace
id|ppc_md
dot
id|udbg_putc
c_func
(paren
id|c
)paren
suffix:semicolon
)brace
)brace
r_return
id|n
op_minus
id|remain
suffix:semicolon
)brace
r_int
DECL|function|udbg_read
id|udbg_read
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|buflen
)paren
(brace
r_char
id|c
comma
op_star
id|p
op_assign
id|buf
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ppc_md.udbg_putc
)paren
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
suffix:semicolon
multiline_comment|/* stop here for cpuctl */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|buflen
suffix:semicolon
op_increment
id|i
)paren
(brace
r_do
(brace
id|c
op_assign
id|ppc_md
dot
id|udbg_getc
c_func
(paren
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|c
op_eq
l_int|0x11
op_logical_or
id|c
op_eq
l_int|0x13
)paren
suffix:semicolon
op_star
id|p
op_increment
op_assign
id|c
suffix:semicolon
)brace
r_return
id|i
suffix:semicolon
)brace
r_void
DECL|function|udbg_console_write
id|udbg_console_write
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
r_int
id|n
)paren
(brace
id|udbg_write
c_func
(paren
id|s
comma
id|n
)paren
suffix:semicolon
)brace
r_void
DECL|function|udbg_puthex
id|udbg_puthex
c_func
(paren
r_int
r_int
id|val
)paren
(brace
r_int
id|i
comma
id|nibbles
op_assign
r_sizeof
(paren
id|val
)paren
op_star
l_int|2
suffix:semicolon
r_int
r_char
id|buf
(braket
r_sizeof
(paren
id|val
)paren
op_star
l_int|2
op_plus
l_int|1
)braket
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|nibbles
op_minus
l_int|1
suffix:semicolon
id|i
op_ge
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
(brace
id|buf
(braket
id|i
)braket
op_assign
(paren
id|val
op_amp
l_int|0xf
)paren
op_plus
l_char|&squot;0&squot;
suffix:semicolon
r_if
c_cond
(paren
id|buf
(braket
id|i
)braket
OG
l_char|&squot;9&squot;
)paren
id|buf
(braket
id|i
)braket
op_add_assign
(paren
l_char|&squot;a&squot;
op_minus
l_char|&squot;0&squot;
op_minus
l_int|10
)paren
suffix:semicolon
id|val
op_rshift_assign
l_int|4
suffix:semicolon
)brace
id|buf
(braket
id|nibbles
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|udbg_puts
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
r_void
DECL|function|udbg_printSP
id|udbg_printSP
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_if
c_cond
(paren
id|naca-&gt;platform
op_eq
id|PLATFORM_PSERIES
)paren
(brace
r_int
r_int
id|sp
suffix:semicolon
id|asm
c_func
(paren
l_string|&quot;mr %0,1&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|sp
)paren
suffix:colon
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s
)paren
id|udbg_puts
c_func
(paren
id|s
)paren
suffix:semicolon
id|udbg_puthex
c_func
(paren
id|sp
)paren
suffix:semicolon
)brace
)brace
r_void
DECL|function|udbg_printf
id|udbg_printf
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
r_int
r_char
id|buf
(braket
l_int|256
)braket
suffix:semicolon
id|va_list
id|args
suffix:semicolon
id|va_start
c_func
(paren
id|args
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|args
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
id|buf
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|args
)paren
suffix:semicolon
)brace
multiline_comment|/* Special print used by PPCDBG() macro */
r_void
DECL|function|udbg_ppcdbg
id|udbg_ppcdbg
c_func
(paren
r_int
r_int
id|debug_flags
comma
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
r_int
r_int
id|active_debugs
op_assign
id|debug_flags
op_amp
id|naca-&gt;debug_switch
suffix:semicolon
r_if
c_cond
(paren
id|active_debugs
)paren
(brace
id|va_list
id|ap
suffix:semicolon
r_int
r_char
id|buf
(braket
l_int|256
)braket
suffix:semicolon
r_int
r_int
id|i
comma
id|len
op_assign
l_int|0
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
id|PPCDBG_NUM_FLAGS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
l_int|1U
op_lshift
id|i
)paren
op_amp
id|active_debugs
)paren
op_logical_and
id|trace_names
(braket
id|i
)braket
)paren
(brace
id|len
op_add_assign
id|strlen
c_func
(paren
id|trace_names
(braket
id|i
)braket
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
id|trace_names
(braket
id|i
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot; [%s]: &quot;
comma
id|current-&gt;comm
)paren
suffix:semicolon
id|len
op_add_assign
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
id|buf
)paren
suffix:semicolon
r_while
c_loop
(paren
id|len
OL
l_int|18
)paren
(brace
id|udbg_puts
c_func
(paren
l_string|&quot; &quot;
)paren
suffix:semicolon
id|len
op_increment
suffix:semicolon
)brace
id|va_start
c_func
(paren
id|ap
comma
id|fmt
)paren
suffix:semicolon
id|vsprintf
c_func
(paren
id|buf
comma
id|fmt
comma
id|ap
)paren
suffix:semicolon
id|udbg_puts
c_func
(paren
id|buf
)paren
suffix:semicolon
id|va_end
c_func
(paren
id|ap
)paren
suffix:semicolon
)brace
)brace
r_int
r_int
DECL|function|udbg_ifdebug
id|udbg_ifdebug
c_func
(paren
r_int
r_int
id|flags
)paren
(brace
r_return
(paren
id|flags
op_amp
id|naca-&gt;debug_switch
)paren
suffix:semicolon
)brace
eof
