multiline_comment|/*&n; * arch/ppc/boot/simple/misc-katana.c&n; *&n; * Set up MPSC values to bootwrapper can prompt user.&n; *&n; * Author: Mark A. Greer &lt;source@mvista.com&gt;&n; *&n; * 2004 (c) MontaVista Software, Inc. This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mv64x60_defs.h&gt;
macro_line|#include &lt;platforms/katana.h&gt;
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
multiline_comment|/* Not in the kernel so won&squot;t include kernel.h to get its &squot;min&squot; definition */
macro_line|#ifndef min
DECL|macro|min
mdefine_line|#define&t;min(a,b)&t;(((a) &lt; (b)) ? (a) : (b))
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
id|mv64x60_console_baud
op_assign
id|KATANA_DEFAULT_BAUD
suffix:semicolon
id|mv64x60_mpsc_clk_src
op_assign
id|KATANA_MPSC_CLK_SRC
suffix:semicolon
id|mv64x60_mpsc_clk_freq
op_assign
id|min
c_func
(paren
id|katana_bus_freq
c_func
(paren
(paren
r_void
id|__iomem
op_star
)paren
id|KATANA_CPLD_BASE
)paren
comma
id|MV64x60_TCLK_FREQ_MAX
)paren
suffix:semicolon
)brace
eof
