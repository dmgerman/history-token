multiline_comment|/*&n; * arch/ppc/platforms/pcore_pci.c&n; * &n; * PCI support for Force PCORE boards&n; *&n; * Author: Matt Porter &lt;mporter@mvista.com&gt;&n; *&n; * 2001 (c) MontaVista, Software, Inc.  This file is licensed under&n; * the terms of the GNU General Public License version 2.1.  This program&n; * is licensed &quot;as is&quot; without any warranty of any kind, whether express&n; * or implied.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/mpc10x.h&gt;
macro_line|#include &quot;pcore.h&quot;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif /* DEBUG */ 
r_static
r_inline
r_int
id|__init
DECL|function|pcore_6750_map_irq
id|pcore_6750_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t; *      PCI IDSEL/INTPIN-&gt;INTLINE&n;&t; *      A       B       C       D&n;&t; */
(brace
(brace
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
)brace
comma
multiline_comment|/* IDSEL 24 - DEC 21554 */
(brace
l_int|10
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 25 - DEC 21143 */
(brace
l_int|11
comma
l_int|12
comma
l_int|9
comma
l_int|10
)brace
comma
multiline_comment|/* IDSEL 26 - PMC I */
(brace
l_int|12
comma
l_int|9
comma
l_int|10
comma
l_int|11
)brace
comma
multiline_comment|/* IDSEL 27 - PMC II */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 28 - unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|9
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 29 - unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 30 - Winbond */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|24
comma
id|max_idsel
op_assign
l_int|30
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
suffix:semicolon
r_static
r_inline
r_int
id|__init
DECL|function|pcore_680_map_irq
id|pcore_680_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
r_char
id|idsel
comma
r_int
r_char
id|pin
)paren
(brace
r_static
r_char
id|pci_irq_table
(braket
)braket
(braket
l_int|4
)braket
op_assign
multiline_comment|/*&n;&t; *      PCI IDSEL/INTPIN-&gt;INTLINE&n;&t; *      A       B       C       D&n;&t; */
(brace
(brace
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
)brace
comma
multiline_comment|/* IDSEL 24 - Sentinel */
(brace
l_int|10
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 25 - i82559 #1 */
(brace
l_int|11
comma
l_int|12
comma
l_int|9
comma
l_int|10
)brace
comma
multiline_comment|/* IDSEL 26 - PMC I */
(brace
l_int|12
comma
l_int|9
comma
l_int|10
comma
l_int|11
)brace
comma
multiline_comment|/* IDSEL 27 - PMC II */
(brace
l_int|9
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 28 - i82559 #2 */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 29 - unused */
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
multiline_comment|/* IDSEL 30 - Winbond */
)brace
suffix:semicolon
r_const
r_int
id|min_idsel
op_assign
l_int|24
comma
id|max_idsel
op_assign
l_int|30
comma
id|irqs_per_slot
op_assign
l_int|4
suffix:semicolon
r_return
id|PCI_IRQ_TABLE_LOOKUP
suffix:semicolon
)brace
suffix:semicolon
r_void
id|__init
DECL|function|pcore_pcibios_fixup
id|pcore_pcibios_fixup
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_83C553
comma
l_int|0
)paren
)paren
)paren
(brace
multiline_comment|/* Reroute interrupts both IDE channels to 15 */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCORE_WINBOND_IDE_INT
comma
l_int|0xff
)paren
suffix:semicolon
multiline_comment|/* Route INTA-D to IRQ9-12, respectively */
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCORE_WINBOND_PCI_INT
comma
l_int|0x9abc
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Set up 8259 edge/level triggering&n;&t;&t; */
id|outb
c_func
(paren
l_int|0x00
comma
id|PCORE_WINBOND_PRI_EDG_LVL
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x1e
comma
id|PCORE_WINBOND_SEC_EDG_LVL
)paren
suffix:semicolon
)brace
)brace
r_int
id|__init
DECL|function|pcore_find_bridges
id|pcore_find_bridges
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_int
id|host_bridge
comma
id|board_type
suffix:semicolon
id|hose
op_assign
id|pcibios_alloc_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose
)paren
r_return
l_int|0
suffix:semicolon
id|mpc10x_bridge_init
c_func
(paren
id|hose
comma
id|MPC10X_MEM_MAP_B
comma
id|MPC10X_MEM_MAP_B
comma
id|MPC10X_MAPB_EUMB_BASE
)paren
suffix:semicolon
multiline_comment|/* Determine board type */
id|early_read_config_dword
c_func
(paren
id|hose
comma
l_int|0
comma
id|PCI_DEVFN
c_func
(paren
l_int|0
comma
l_int|0
)paren
comma
id|PCI_VENDOR_ID
comma
op_amp
id|host_bridge
)paren
suffix:semicolon
r_if
c_cond
(paren
id|host_bridge
op_eq
id|MPC10X_BRIDGE_106
)paren
id|board_type
op_assign
id|PCORE_TYPE_6750
suffix:semicolon
r_else
multiline_comment|/* MPC10X_BRIDGE_107 */
id|board_type
op_assign
id|PCORE_TYPE_680
suffix:semicolon
id|hose-&gt;last_busno
op_assign
id|pciauto_bus_scan
c_func
(paren
id|hose
comma
id|hose-&gt;first_busno
)paren
suffix:semicolon
id|ppc_md.pcibios_fixup
op_assign
id|pcore_pcibios_fixup
suffix:semicolon
id|ppc_md.pci_swizzle
op_assign
id|common_swizzle
suffix:semicolon
r_if
c_cond
(paren
id|board_type
op_eq
id|PCORE_TYPE_6750
)paren
id|ppc_md.pci_map_irq
op_assign
id|pcore_6750_map_irq
suffix:semicolon
r_else
multiline_comment|/* PCORE_TYPE_680 */
id|ppc_md.pci_map_irq
op_assign
id|pcore_680_map_irq
suffix:semicolon
r_return
id|board_type
suffix:semicolon
)brace
eof
