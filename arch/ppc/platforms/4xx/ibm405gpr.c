multiline_comment|/*&n; * arch/ppc/platforms/4xx/ibm405gpr.c&n; *&n; * Author: Armin Kuster &lt;akuster@mvista.com&gt;&n; *&n; * 2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &quot;ibm405gpr.h&quot;
DECL|variable|__initdata
r_struct
id|ocp_def
id|core_ocp
(braket
)braket
id|__initdata
op_assign
(brace
(brace
id|OCP_VENDOR_IBM
comma
id|OCP_FUNC_OPB
comma
id|OPB_BASE_START
comma
id|OCP_IRQ_NA
comma
id|OCP_CPM_NA
)brace
comma
(brace
id|OCP_VENDOR_IBM
comma
id|OCP_FUNC_16550
comma
id|UART0_IO_BASE
comma
id|UART0_INT
comma
id|IBM_CPM_UART0
)brace
comma
(brace
id|OCP_VENDOR_IBM
comma
id|OCP_FUNC_16550
comma
id|UART1_IO_BASE
comma
id|UART1_INT
comma
id|IBM_CPM_UART1
)brace
comma
(brace
id|OCP_VENDOR_IBM
comma
id|OCP_FUNC_IIC
comma
id|IIC0_BASE
comma
id|IIC0_IRQ
comma
id|IBM_CPM_IIC0
)brace
comma
(brace
id|OCP_VENDOR_IBM
comma
id|OCP_FUNC_GPIO
comma
id|GPIO0_BASE
comma
id|OCP_IRQ_NA
comma
id|IBM_CPM_GPIO0
)brace
comma
(brace
id|OCP_VENDOR_IBM
comma
id|OCP_FUNC_EMAC
comma
id|EMAC0_BASE
comma
id|BL_MAC_ETH0
comma
id|IBM_CPM_EMAC0
)brace
comma
(brace
id|OCP_VENDOR_INVALID
comma
id|OCP_FUNC_INVALID
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
