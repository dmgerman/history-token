multiline_comment|/*&n; * linux/include/asm-arm/arch-brutus/uncompress.h&n; *&n; * (C) 1999 Nicolas Pitre &lt;nico@cam.org&gt;&n; *&n; * Reorganised to be machine independent.&n; */
macro_line|#include &quot;hardware.h&quot;
multiline_comment|/*&n; * The following code assumes the serial port has already been&n; * initialized by the bootloader.  We search for the first enabled&n; * port in the most probable order.  If you didn&squot;t setup a port in&n; * your bootloader then nothing will appear (which might be desired).&n; */
DECL|macro|UART
mdefine_line|#define UART(x)&t;&t;(*(volatile unsigned long *)(serial_port + (x)))
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
r_int
r_int
id|serial_port
suffix:semicolon
r_do
(brace
id|serial_port
op_assign
id|_Ser3UTCR0
suffix:semicolon
r_if
c_cond
(paren
id|UART
c_func
(paren
id|UTCR3
)paren
op_amp
id|UTCR3_TXE
)paren
r_break
suffix:semicolon
id|serial_port
op_assign
id|_Ser1UTCR0
suffix:semicolon
r_if
c_cond
(paren
id|UART
c_func
(paren
id|UTCR3
)paren
op_amp
id|UTCR3_TXE
)paren
r_break
suffix:semicolon
id|serial_port
op_assign
id|_Ser2UTCR0
suffix:semicolon
r_if
c_cond
(paren
id|UART
c_func
(paren
id|UTCR3
)paren
op_amp
id|UTCR3_TXE
)paren
r_break
suffix:semicolon
r_return
suffix:semicolon
)brace
r_while
c_loop
(paren
l_int|0
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
op_star
id|s
suffix:semicolon
id|s
op_increment
)paren
(brace
multiline_comment|/* wait for space in the UART&squot;s transmiter */
r_while
c_loop
(paren
op_logical_neg
(paren
id|UART
c_func
(paren
id|UTSR1
)paren
op_amp
id|UTSR1_TNF
)paren
)paren
suffix:semicolon
multiline_comment|/* send the character out. */
id|UART
c_func
(paren
id|UTDR
)paren
op_assign
op_star
id|s
suffix:semicolon
multiline_comment|/* if a LF, also do CR... */
r_if
c_cond
(paren
op_star
id|s
op_eq
l_int|10
)paren
(brace
r_while
c_loop
(paren
op_logical_neg
(paren
id|UART
c_func
(paren
id|UTSR1
)paren
op_amp
id|UTSR1_TNF
)paren
)paren
suffix:semicolon
id|UART
c_func
(paren
id|UTDR
)paren
op_assign
l_int|13
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * Nothing to do for these&n; */
DECL|macro|arch_decomp_setup
mdefine_line|#define arch_decomp_setup()
DECL|macro|arch_decomp_wdog
mdefine_line|#define arch_decomp_wdog()
eof
