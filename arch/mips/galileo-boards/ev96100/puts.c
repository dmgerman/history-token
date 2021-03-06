multiline_comment|/*&n; * Debug routines which directly access the uart.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/gt64120.h&gt;
singleline_comment|//#define SERIAL_BASE    EV96100_UART0_REGS_BASE
DECL|macro|SERIAL_BASE
mdefine_line|#define SERIAL_BASE    0xBD000020
DECL|macro|NS16550_BASE
mdefine_line|#define NS16550_BASE   SERIAL_BASE
DECL|macro|SERA_CMD
mdefine_line|#define SERA_CMD       0x0D
DECL|macro|SERA_DATA
mdefine_line|#define SERA_DATA      0x08
singleline_comment|//#define SERB_CMD       0x05
DECL|macro|SERB_CMD
mdefine_line|#define SERB_CMD       20
DECL|macro|SERB_DATA
mdefine_line|#define SERB_DATA      0x00
DECL|macro|TX_BUSY
mdefine_line|#define TX_BUSY        0x20
DECL|macro|TIMEOUT
mdefine_line|#define TIMEOUT    0xffff
DECL|macro|SLOW_DOWN
macro_line|#undef SLOW_DOWN
DECL|variable|digits
r_static
r_const
r_char
id|digits
(braket
l_int|16
)braket
op_assign
l_string|&quot;0123456789abcdef&quot;
suffix:semicolon
DECL|variable|com1
r_static
r_volatile
r_int
r_char
op_star
r_const
id|com1
op_assign
(paren
r_int
r_char
op_star
)paren
id|SERIAL_BASE
suffix:semicolon
macro_line|#ifdef SLOW_DOWN
DECL|function|slow_down
r_static
r_inline
r_void
id|slow_down
c_func
(paren
)paren
(brace
r_int
id|k
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|10000
suffix:semicolon
id|k
op_increment
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|macro|slow_down
mdefine_line|#define slow_down()
macro_line|#endif
DECL|function|putch
r_void
id|putch
c_func
(paren
r_const
r_int
r_char
id|c
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|ch
op_assign
id|com1
(braket
id|SERB_CMD
)braket
suffix:semicolon
id|slow_down
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|TIMEOUT
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|0
op_eq
(paren
id|ch
op_amp
id|TX_BUSY
)paren
)paren
suffix:semicolon
id|com1
(braket
id|SERB_DATA
)braket
op_assign
id|c
suffix:semicolon
)brace
DECL|function|putchar
r_void
id|putchar
c_func
(paren
r_const
r_int
r_char
id|c
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|ch
op_assign
id|com1
(braket
id|SERB_CMD
)braket
suffix:semicolon
id|slow_down
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|TIMEOUT
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|0
op_eq
(paren
id|ch
op_amp
id|TX_BUSY
)paren
)paren
suffix:semicolon
id|com1
(braket
id|SERB_DATA
)braket
op_assign
id|c
suffix:semicolon
)brace
DECL|function|puts
r_void
id|puts
c_func
(paren
r_int
r_char
op_star
id|cp
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
)paren
(brace
r_do
(brace
id|ch
op_assign
id|com1
(braket
id|SERB_CMD
)braket
suffix:semicolon
id|slow_down
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|TIMEOUT
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|0
op_eq
(paren
id|ch
op_amp
id|TX_BUSY
)paren
)paren
suffix:semicolon
id|com1
(braket
id|SERB_DATA
)braket
op_assign
op_star
id|cp
op_increment
suffix:semicolon
)brace
id|putch
c_func
(paren
l_char|&squot;&bslash;r&squot;
)paren
suffix:semicolon
id|putch
c_func
(paren
l_char|&squot;&bslash;n&squot;
)paren
suffix:semicolon
)brace
DECL|function|fputs
r_void
id|fputs
c_func
(paren
r_int
r_char
op_star
id|cp
)paren
(brace
r_int
r_char
id|ch
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
op_star
id|cp
)paren
(brace
r_do
(brace
id|ch
op_assign
id|com1
(braket
id|SERB_CMD
)braket
suffix:semicolon
id|slow_down
c_func
(paren
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|i
OG
id|TIMEOUT
)paren
(brace
r_break
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
l_int|0
op_eq
(paren
id|ch
op_amp
id|TX_BUSY
)paren
)paren
suffix:semicolon
id|com1
(braket
id|SERB_DATA
)braket
op_assign
op_star
id|cp
op_increment
suffix:semicolon
)brace
)brace
DECL|function|put64
r_void
id|put64
c_func
(paren
r_uint64
id|ul
)paren
(brace
r_int
id|cnt
suffix:semicolon
r_int
id|ch
suffix:semicolon
id|cnt
op_assign
l_int|16
suffix:semicolon
multiline_comment|/* 16 nibbles in a 64 bit long */
id|putch
c_func
(paren
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|putch
c_func
(paren
l_char|&squot;x&squot;
)paren
suffix:semicolon
r_do
(brace
id|cnt
op_decrement
suffix:semicolon
id|ch
op_assign
(paren
r_int
r_char
)paren
(paren
id|ul
op_rshift
id|cnt
op_star
l_int|4
)paren
op_amp
l_int|0x0F
suffix:semicolon
id|putch
c_func
(paren
id|digits
(braket
id|ch
)braket
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cnt
OG
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|put32
r_void
id|put32
c_func
(paren
r_int
id|u
)paren
(brace
r_int
id|cnt
suffix:semicolon
r_int
id|ch
suffix:semicolon
id|cnt
op_assign
l_int|8
suffix:semicolon
multiline_comment|/* 8 nibbles in a 32 bit long */
id|putch
c_func
(paren
l_char|&squot;0&squot;
)paren
suffix:semicolon
id|putch
c_func
(paren
l_char|&squot;x&squot;
)paren
suffix:semicolon
r_do
(brace
id|cnt
op_decrement
suffix:semicolon
id|ch
op_assign
(paren
r_int
r_char
)paren
(paren
id|u
op_rshift
id|cnt
op_star
l_int|4
)paren
op_amp
l_int|0x0F
suffix:semicolon
id|putch
c_func
(paren
id|digits
(braket
id|ch
)braket
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|cnt
OG
l_int|0
)paren
suffix:semicolon
)brace
eof
