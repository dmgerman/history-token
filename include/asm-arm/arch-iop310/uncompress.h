multiline_comment|/*&n; *  linux/include/asm-arm/arch-iop80310/uncompress.h&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef CONFIG_ARCH_IQ80310
DECL|macro|UART1_BASE
mdefine_line|#define UART1_BASE    ((volatile unsigned char *)0xfe800000)
DECL|macro|UART2_BASE
mdefine_line|#define UART2_BASE    ((volatile unsigned char *)0xfe810000)
macro_line|#endif
DECL|function|putc
r_static
id|__inline__
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
id|UART2_BASE
(braket
l_int|5
)braket
op_amp
l_int|0x60
)paren
op_ne
l_int|0x60
)paren
suffix:semicolon
id|UART2_BASE
(braket
l_int|0
)braket
op_assign
id|c
suffix:semicolon
)brace
multiline_comment|/*&n; * This does not append a newline&n; */
DECL|function|puts
r_static
r_void
id|puts
c_func
(paren
r_const
r_char
op_star
id|s
)paren
(brace
r_while
c_loop
(paren
op_star
id|s
)paren
(brace
id|putc
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
id|putc
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
multiline_comment|/*&n; * nothing to do&n; */
DECL|macro|arch_decomp_setup
mdefine_line|#define arch_decomp_setup()
DECL|macro|arch_decomp_wdog
mdefine_line|#define arch_decomp_wdog()
eof
