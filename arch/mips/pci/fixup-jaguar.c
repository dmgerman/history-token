multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Marvell MV64340 interrupt fixup code.&n; *&n; * Marvell wants an NDA for their docs so this was written without&n; * documentation.  You&squot;ve been warned.&n; *&n; * Copyright (C) 2004 Ralf Baechle (ralf@linux-mips.org)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/mipsregs.h&gt;
multiline_comment|/*&n; * WARNING: Example of how _NOT_ to do it.&n; */
DECL|function|pcibios_map_irq
r_int
id|__init
id|pcibios_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_int
id|bus
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
op_logical_and
id|slot
op_eq
l_int|1
)paren
r_return
l_int|3
suffix:semicolon
multiline_comment|/* PCI-X A */
r_if
c_cond
(paren
id|bus
op_eq
l_int|0
op_logical_and
id|slot
op_eq
l_int|2
)paren
r_return
l_int|4
suffix:semicolon
multiline_comment|/* PCI-X B */
r_if
c_cond
(paren
id|bus
op_eq
l_int|1
op_logical_and
id|slot
op_eq
l_int|1
)paren
r_return
l_int|5
suffix:semicolon
multiline_comment|/* PCI A */
r_if
c_cond
(paren
id|bus
op_eq
l_int|1
op_logical_and
id|slot
op_eq
l_int|2
)paren
r_return
l_int|6
suffix:semicolon
multiline_comment|/* PCI B */
r_return
l_int|0
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;Whooops in pcibios_map_irq&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Do platform specific device initialization at pci_enable_device() time */
DECL|function|pcibios_plat_dev_init
r_int
id|pcibios_plat_dev_init
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
eof
