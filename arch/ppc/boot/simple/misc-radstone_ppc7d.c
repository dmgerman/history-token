multiline_comment|/*&n; * arch/ppc/boot/simple/misc-radstone_ppc7d.c&n; *&n; * Misc data for Radstone PPC7D board.&n; *&n; * Author: James Chapman &lt;jchapman@katalix.com&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/reg.h&gt;
macro_line|#include &quot;../../platforms/radstone_ppc7d.h&quot;
macro_line|#if defined(CONFIG_SERIAL_MPSC_CONSOLE)
DECL|variable|mv64x60_mpsc_clk_freq
r_int
id|mv64x60_mpsc_clk_freq
op_assign
id|PPC7D_MPSC_CLK_FREQ
suffix:semicolon
suffix:semicolon
DECL|variable|mv64x60_mpsc_clk_src
r_int
id|mv64x60_mpsc_clk_src
op_assign
id|PPC7D_MPSC_CLK_SRC
suffix:semicolon
DECL|variable|mv64x60_mpsc_console_baud
r_int
id|mv64x60_mpsc_console_baud
op_assign
id|PPC7D_DEFAULT_BAUD
suffix:semicolon
macro_line|#endif
eof
