multiline_comment|/*&n; * arch/ppc/boot/simple/misc-radstone_ppc7d.c&n; *&n; * Misc data for Radstone PPC7D board.&n; *&n; * Author: James Chapman &lt;jchapman@katalix.com&gt;&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;platforms/radstone_ppc7d.h&gt;
macro_line|#if defined(CONFIG_SERIAL_MPSC_CONSOLE)
r_extern
id|u32
id|mv64x60_console_baud
suffix:semicolon
r_extern
id|u32
id|mv64x60_mpsc_clk_src
suffix:semicolon
r_extern
id|u32
id|mv64x60_mpsc_clk_freq
suffix:semicolon
macro_line|#endif
r_void
DECL|function|mv64x60_board_init
id|mv64x60_board_init
c_func
(paren
r_void
id|__iomem
op_star
id|old_base
comma
r_void
id|__iomem
op_star
id|new_base
)paren
(brace
macro_line|#if defined(CONFIG_SERIAL_MPSC_CONSOLE)
id|mv64x60_console_baud
op_assign
id|PPC7D_DEFAULT_BAUD
suffix:semicolon
id|mv64x60_mpsc_clk_src
op_assign
id|PPC7D_MPSC_CLK_SRC
suffix:semicolon
id|mv64x60_mpsc_clk_freq
op_assign
id|PPC7D_MPSC_CLK_FREQ
suffix:semicolon
macro_line|#endif
)brace
eof
