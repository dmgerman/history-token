multiline_comment|/*&n; * arch/ppc/platforms/4xx/virtex-ii_pro.c&n; *&n; * Author: MontaVista Software, Inc.&n; *         source@mvista.com&n; *&n; * 2002-2004 (c) MontaVista Software, Inc.  This file is licensed under the&n; * terms of the GNU General Public License version 2.  This program is licensed&n; * &quot;as is&quot; without any warranty of any kind, whether express or implied.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &quot;virtex-ii_pro.h&quot;
multiline_comment|/* Have OCP take care of the serial ports. */
DECL|variable|core_ocp
r_struct
id|ocp_def
id|core_ocp
(braket
)braket
op_assign
(brace
macro_line|#ifdef XPAR_UARTNS550_0_BASEADDR
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_XILINX
comma
dot
id|function
op_assign
id|OCP_FUNC_16550
comma
dot
id|index
op_assign
l_int|0
comma
dot
id|paddr
op_assign
id|XPAR_UARTNS550_0_BASEADDR
comma
dot
id|irq
op_assign
id|XPAR_INTC_0_UARTNS550_0_VEC_ID
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
)brace
comma
macro_line|#ifdef XPAR_UARTNS550_1_BASEADDR
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_XILINX
comma
dot
id|function
op_assign
id|OCP_FUNC_16550
comma
dot
id|index
op_assign
l_int|1
comma
dot
id|paddr
op_assign
id|XPAR_UARTNS550_1_BASEADDR
comma
dot
id|irq
op_assign
id|XPAR_INTC_0_UARTNS550_1_VEC_ID
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
)brace
comma
macro_line|#ifdef XPAR_UARTNS550_2_BASEADDR
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_XILINX
comma
dot
id|function
op_assign
id|OCP_FUNC_16550
comma
dot
id|index
op_assign
l_int|2
comma
dot
id|paddr
op_assign
id|XPAR_UARTNS550_2_BASEADDR
comma
dot
id|irq
op_assign
id|XPAR_INTC_0_UARTNS550_2_VEC_ID
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
)brace
comma
macro_line|#ifdef XPAR_UARTNS550_3_BASEADDR
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_XILINX
comma
dot
id|function
op_assign
id|OCP_FUNC_16550
comma
dot
id|index
op_assign
l_int|3
comma
dot
id|paddr
op_assign
id|XPAR_UARTNS550_3_BASEADDR
comma
dot
id|irq
op_assign
id|XPAR_INTC_0_UARTNS550_3_VEC_ID
comma
dot
id|pm
op_assign
id|OCP_CPM_NA
)brace
comma
macro_line|#ifdef XPAR_UARTNS550_4_BASEADDR
macro_line|#error Edit this file to add more devices.
macro_line|#endif&t;&t;&t;/* 4 */
macro_line|#endif&t;&t;&t;/* 3 */
macro_line|#endif&t;&t;&t;/* 2 */
macro_line|#endif&t;&t;&t;/* 1 */
macro_line|#endif&t;&t;&t;/* 0 */
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_INVALID
)brace
)brace
suffix:semicolon
eof
