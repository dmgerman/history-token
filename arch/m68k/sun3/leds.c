macro_line|#include &lt;asm/contregs.h&gt;
macro_line|#include &lt;asm/sun3mmu.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/movs.h&gt;
DECL|macro|FC_CONTROL
mdefine_line|#define FC_CONTROL 3    /* This should go somewhere else... */
DECL|function|sun3_leds
r_void
id|sun3_leds
c_func
(paren
r_int
r_char
id|byte
)paren
(brace
r_int
r_char
id|dfc
suffix:semicolon
id|GET_DFC
c_func
(paren
id|dfc
)paren
suffix:semicolon
id|SET_DFC
c_func
(paren
id|FC_CONTROL
)paren
suffix:semicolon
id|SET_CONTROL_BYTE
c_func
(paren
id|AC_LEDS
comma
id|byte
)paren
suffix:semicolon
id|SET_DFC
c_func
(paren
id|dfc
)paren
suffix:semicolon
)brace
eof
