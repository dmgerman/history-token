multiline_comment|/*&n; * linux/arch/arm/mach-omap/ocpi.c&n; *&n; * Minimal OCP bus support for OMAP-1610 and OMAP-5912&n; *&n; * Copyright (C) 2003 - 2004 Nokia Corporation&n; * Written by Tony Lindgren &lt;tony@atomide.com&gt;&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/arch/hardware.h&gt;
DECL|macro|OCPI_BASE
mdefine_line|#define OCPI_BASE&t;&t;0xfffec320
DECL|macro|OCPI_FAULT
mdefine_line|#define OCPI_FAULT&t;&t;(OCPI_BASE + 0x00)
DECL|macro|OCPI_CMD_FAULT
mdefine_line|#define OCPI_CMD_FAULT&t;&t;(OCPI_BASE + 0x04)
DECL|macro|OCPI_SINT0
mdefine_line|#define OCPI_SINT0&t;&t;(OCPI_BASE + 0x08)
DECL|macro|OCPI_TABORT
mdefine_line|#define OCPI_TABORT&t;&t;(OCPI_BASE + 0x0c)
DECL|macro|OCPI_SINT1
mdefine_line|#define OCPI_SINT1&t;&t;(OCPI_BASE + 0x10)
DECL|macro|OCPI_PROT
mdefine_line|#define OCPI_PROT&t;&t;(OCPI_BASE + 0x14)
DECL|macro|OCPI_SEC
mdefine_line|#define OCPI_SEC&t;&t;(OCPI_BASE + 0x18)
DECL|macro|EN_OCPI_CK
mdefine_line|#define EN_OCPI_CK&t;&t;(1 &lt;&lt; 0)
DECL|macro|IDLOCPI_ARM
mdefine_line|#define IDLOCPI_ARM&t;&t;(1 &lt;&lt; 1)
multiline_comment|/* USB OHCI OCPI access error registers */
DECL|macro|HOSTUEADDR
mdefine_line|#define HOSTUEADDR&t;0xfffba0e0
DECL|macro|HOSTUESTATUS
mdefine_line|#define HOSTUESTATUS&t;0xfffba0e4
multiline_comment|/*&n; * Enables device access to OMAP buses via the OCPI bridge&n; * FIXME: Add locking&n; */
DECL|function|ocpi_enable
r_int
id|ocpi_enable
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
multiline_comment|/* Make sure there&squot;s clock for OCPI */
macro_line|#if defined(CONFIG_ARCH_OMAP16XX)
r_if
c_cond
(paren
id|cpu_is_omap1610
c_func
(paren
)paren
op_logical_or
id|cpu_is_omap1710
c_func
(paren
)paren
)paren
(brace
id|val
op_assign
id|omap_readl
c_func
(paren
id|OMAP16XX_ARM_IDLECT3
)paren
suffix:semicolon
id|val
op_or_assign
id|EN_OCPI_CK
suffix:semicolon
id|val
op_and_assign
op_complement
id|IDLOCPI_ARM
suffix:semicolon
id|omap_writel
c_func
(paren
id|val
comma
id|OMAP16XX_ARM_IDLECT3
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* Enable access for OHCI in OCPI */
id|val
op_assign
id|omap_readl
c_func
(paren
id|OCPI_PROT
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
l_int|0xff
suffix:semicolon
singleline_comment|//val &amp;= (1 &lt;&lt; 0);&t;/* Allow access only to EMIFS */
id|omap_writel
c_func
(paren
id|val
comma
id|OCPI_PROT
)paren
suffix:semicolon
id|val
op_assign
id|omap_readl
c_func
(paren
id|OCPI_SEC
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
l_int|0xff
suffix:semicolon
id|omap_writel
c_func
(paren
id|val
comma
id|OCPI_SEC
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ocpi_enable
id|EXPORT_SYMBOL
c_func
(paren
id|ocpi_enable
)paren
suffix:semicolon
DECL|function|ocpi_status
r_int
id|ocpi_status
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;OCPI: addr: 0x%08x cmd: 0x%08x&bslash;n&quot;
l_string|&quot;      ohci-addr: 0x%08x ohci-status: 0x%08x&bslash;n&quot;
comma
id|omap_readl
c_func
(paren
id|OCPI_FAULT
)paren
comma
id|omap_readl
c_func
(paren
id|OCPI_CMD_FAULT
)paren
comma
id|omap_readl
c_func
(paren
id|HOSTUEADDR
)paren
comma
id|omap_readl
c_func
(paren
id|HOSTUESTATUS
)paren
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
DECL|variable|ocpi_status
id|EXPORT_SYMBOL
c_func
(paren
id|ocpi_status
)paren
suffix:semicolon
DECL|function|omap_ocpi_init
r_static
r_int
id|__init
id|omap_ocpi_init
c_func
(paren
r_void
)paren
(brace
id|ocpi_enable
c_func
(paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;OMAP OCPI interconnect driver loaded&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|omap_ocpi_exit
r_static
r_void
id|__exit
id|omap_ocpi_exit
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* FIXME: Disable OCPI */
)brace
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Tony Lindgren &lt;tony@atomide.com&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;OMAP OCPI bus controller module&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|omap_ocpi_init
id|module_init
c_func
(paren
id|omap_ocpi_init
)paren
suffix:semicolon
DECL|variable|omap_ocpi_exit
id|module_exit
c_func
(paren
id|omap_ocpi_exit
)paren
suffix:semicolon
eof
