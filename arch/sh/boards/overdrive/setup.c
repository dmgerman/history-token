multiline_comment|/*&n; * arch/sh/overdrive/setup.c&n; *&n; * Copyright (C) 2000 Stuart Menefy (stuart.menefy@st.com)&n; *&n; * May be copied or modified under the terms of the GNU General Public&n; * License.  See linux/COPYING for more information.&n; *&n; * STMicroelectronics Overdrive Support.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/overdrive/overdrive.h&gt;
macro_line|#include &lt;asm/overdrive/fpga.h&gt;
r_extern
r_void
id|od_time_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|function|get_system_type
r_const
r_char
op_star
id|get_system_type
c_func
(paren
r_void
)paren
(brace
r_return
l_string|&quot;SH7750 Overdrive&quot;
suffix:semicolon
)brace
multiline_comment|/*&n; * Initialize the board&n; */
DECL|function|platform_setup
r_int
id|__init
id|platform_setup
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_PCI
id|init_overdrive_fpga
c_func
(paren
)paren
suffix:semicolon
id|galileo_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|board_time_init
op_assign
id|od_time_init
suffix:semicolon
multiline_comment|/* Enable RS232 receive buffers */
id|writel
c_func
(paren
l_int|0x1e
comma
id|OVERDRIVE_CTRL
)paren
suffix:semicolon
)brace
eof
