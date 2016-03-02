multiline_comment|/*&n; * arch/m32r/boot/compressed/m32r_sio.c&n; *&n; * 2003-02-12:&t;Takeo Takahashi&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/m32r.h&gt;
macro_line|#include &lt;asm/io.h&gt;
r_void
id|putc
c_func
(paren
r_char
id|c
)paren
suffix:semicolon
DECL|function|puts
r_int
id|puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_char
id|c
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
)paren
id|putc
c_func
(paren
id|c
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#if defined(CONFIG_PLAT_M32700UT_Alpha) || defined(CONFIG_PLAT_M32700UT)
DECL|macro|USE_FPGA_MAP
mdefine_line|#define USE_FPGA_MAP&t;0
macro_line|#if USE_FPGA_MAP
multiline_comment|/*&n; * fpga configuration program uses MMU, and define map as same as&n; * M32104 uT-Engine board.&n; */
DECL|macro|BOOT_SIO0STS
mdefine_line|#define BOOT_SIO0STS&t;(volatile unsigned short *)(0x02c00000 + 0x20006)
DECL|macro|BOOT_SIO0TXB
mdefine_line|#define BOOT_SIO0TXB&t;(volatile unsigned short *)(0x02c00000 + 0x2000c)
macro_line|#else
DECL|macro|PLD_BASE
macro_line|#undef PLD_BASE
DECL|macro|PLD_BASE
mdefine_line|#define PLD_BASE&t;0xa4c00000
DECL|macro|BOOT_SIO0STS
mdefine_line|#define BOOT_SIO0STS&t;PLD_ESIO0STS
DECL|macro|BOOT_SIO0TXB
mdefine_line|#define BOOT_SIO0TXB&t;PLD_ESIO0TXB
macro_line|#endif
DECL|function|putc
r_void
id|putc
c_func
(paren
r_char
id|c
)paren
(brace
r_while
c_loop
(paren
(paren
op_star
id|BOOT_SIO0STS
op_amp
l_int|0x3
)paren
op_ne
l_int|0x3
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
op_star
id|BOOT_SIO0TXB
op_assign
l_char|&squot;&bslash;r&squot;
suffix:semicolon
r_while
c_loop
(paren
(paren
op_star
id|BOOT_SIO0STS
op_amp
l_int|0x3
)paren
op_ne
l_int|0x3
)paren
suffix:semicolon
)brace
op_star
id|BOOT_SIO0TXB
op_assign
id|c
suffix:semicolon
)brace
macro_line|#else
DECL|function|putc
r_void
id|putc
c_func
(paren
r_char
id|c
)paren
(brace
multiline_comment|/* do nothing */
)brace
macro_line|#endif
eof
