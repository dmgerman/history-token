multiline_comment|/*&n; * arch/ppc/platforms/4xx/ibmstbx25.c&n; *&n; * Author: Armin Kuster &lt;akuster@mvista.com&gt;&n; *&n; * 2000-2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ocp.h&gt;
macro_line|#include &lt;platforms/4xx/ibmstbx25.h&gt;
macro_line|#include &lt;asm/ppc4xx_pic.h&gt;
DECL|variable|ibmstbx25_iic0_def
r_static
r_struct
id|ocp_func_iic_data
id|ibmstbx25_iic0_def
op_assign
(brace
dot
id|fast_mode
op_assign
l_int|0
comma
multiline_comment|/* Use standad mode (100Khz) */
)brace
suffix:semicolon
id|OCP_SYSFS_IIC_DATA
c_func
(paren
)paren
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
dot
id|vendor
op_assign
id|OCP_VENDOR_IBM
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
id|UART0_IO_BASE
comma
dot
id|irq
op_assign
id|UART0_INT
comma
dot
id|pm
op_assign
id|IBM_CPM_UART0
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_IBM
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
id|UART1_IO_BASE
comma
dot
id|irq
op_assign
id|UART1_INT
comma
dot
id|pm
op_assign
id|IBM_CPM_UART1
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_IBM
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
id|UART2_IO_BASE
comma
dot
id|irq
op_assign
id|UART2_INT
comma
dot
id|pm
op_assign
id|IBM_CPM_UART2
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_IBM
comma
dot
id|function
op_assign
id|OCP_FUNC_IIC
comma
dot
id|paddr
op_assign
id|IIC0_BASE
comma
dot
id|irq
op_assign
id|IIC0_IRQ
comma
dot
id|pm
op_assign
id|IBM_CPM_IIC0
comma
dot
id|additions
op_assign
op_amp
id|ibmstbx25_iic0_def
comma
dot
id|show
op_assign
op_amp
id|ocp_show_iic_data
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_IBM
comma
dot
id|function
op_assign
id|OCP_FUNC_GPIO
comma
dot
id|paddr
op_assign
id|GPIO0_BASE
comma
dot
id|irq
op_assign
id|OCP_IRQ_NA
comma
dot
id|pm
op_assign
id|IBM_CPM_GPIO0
comma
)brace
comma
(brace
dot
id|vendor
op_assign
id|OCP_VENDOR_INVALID
)brace
)brace
suffix:semicolon
multiline_comment|/* Polarity and triggering settings for internal interrupt sources */
DECL|variable|__initdata
r_struct
id|ppc4xx_uic_settings
id|ppc4xx_core_uic_cfg
(braket
)braket
id|__initdata
op_assign
(brace
(brace
dot
id|polarity
op_assign
l_int|0xffff8f80
comma
dot
id|triggering
op_assign
l_int|0x00000000
comma
dot
id|ext_irq_mask
op_assign
l_int|0x0000707f
comma
multiline_comment|/* IRQ7 - IRQ9, IRQ0 - IRQ6 */
)brace
)brace
suffix:semicolon
eof
