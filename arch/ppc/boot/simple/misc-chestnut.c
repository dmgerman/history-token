multiline_comment|/*&n; * arch/ppc/boot/simple/misc-chestnut.c&n; *&n; * Setup for the IBM Chestnut (ibm-750fxgx_eval)&n; *&n; * Author: Mark A. Greer &lt;mgreer@mvista.com&gt;&n; *&n; * 2005 (c) MontaVista Software, Inc. This file is licensed under&n; * the terms of the GNU General Public License version 2. This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/mv64x60_defs.h&gt;
macro_line|#include &lt;platforms/chestnut.h&gt;
multiline_comment|/* Not in the kernel so won&squot;t include kernel.h to get its &squot;max&squot; definition */
DECL|macro|max
mdefine_line|#define max(a,b)&t;(((a) &gt; (b)) ? (a) : (b))
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
macro_line|#ifdef CONFIG_SERIAL_8250_CONSOLE
multiline_comment|/*&n;&t; * Change device bus 2 window so that bootoader can do I/O thru&n;&t; * 8250/16550 UART that&squot;s mapped in that window.&n;&t; */
id|out_le32
c_func
(paren
id|new_base
op_plus
id|MV64x60_CPU2DEV_2_BASE
comma
id|CHESTNUT_UART_BASE
op_rshift
l_int|16
)paren
suffix:semicolon
id|out_le32
c_func
(paren
id|new_base
op_plus
id|MV64x60_CPU2DEV_2_SIZE
comma
id|CHESTNUT_UART_SIZE
op_rshift
l_int|16
)paren
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;sync&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
