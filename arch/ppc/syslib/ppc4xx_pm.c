multiline_comment|/*&n; * Author: Armin Kuster &lt;akuster@mvista.com&gt;&n; *&n; * 2002 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; *&n; * This an attempt to get Power Management going for the IBM 4xx processor.&n; * This was derived from the ppc4xx._setup.c file&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/ibm4xx.h&gt;
r_void
id|__init
DECL|function|ppc4xx_pm_init
id|ppc4xx_pm_init
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|value
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* turn off unused hardware to save power */
macro_line|#ifdef CONFIG_405GP
id|value
op_or_assign
id|CPM_DCP
suffix:semicolon
multiline_comment|/* CodePack */
macro_line|#endif
macro_line|#if !defined(CONFIG_IBM_OCP_GPIO)
id|value
op_or_assign
id|CPM_GPIO0
suffix:semicolon
macro_line|#endif
macro_line|#if !defined(CONFIG_PPC405_I2C_ADAP)
id|value
op_or_assign
id|CPM_IIC0
suffix:semicolon
macro_line|#ifdef CONFIG_STB03xxx
id|value
op_or_assign
id|CPM_IIC1
suffix:semicolon
macro_line|#endif
macro_line|#endif
macro_line|#if !defined(CONFIG_405_DMA)
id|value
op_or_assign
id|CPM_DMA
suffix:semicolon
macro_line|#endif
id|mtdcr
c_func
(paren
id|DCRN_CPMFR
comma
id|value
)paren
suffix:semicolon
)brace
eof
