multiline_comment|/*&n; * arch/ppc/platforms/4xx/ibmnp4gs.c&n; *&n; * Author: Armin Kuster &lt;akuster@mvista.com&gt;&n; *&n; * 2000-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;ibmnp4gs.h&quot;
macro_line|#include &lt;asm/ocp.h&gt;
DECL|variable|core_ocp
r_struct
id|ocp_def
id|core_ocp
(braket
)braket
op_assign
(brace
(brace
id|UART
comma
id|UART0_IO_BASE
comma
id|UART0_INT
comma
id|IBM_CPM_UART0
)brace
comma
(brace
id|PCI
comma
id|PCIL0_BASE
comma
id|OCP_IRQ_NA
comma
id|IBM_CPM_PCI
)brace
comma
(brace
id|OCP_NULL_TYPE
comma
l_int|0x0
comma
id|OCP_IRQ_NA
comma
id|OCP_CPM_NA
)brace
comma
)brace
suffix:semicolon
eof
