multiline_comment|/*&n; * pci_dn.c&n; *&n; * Copyright (C) 2001 Todd Inglett, IBM Corporation&n; *&n; * PCI manipulation via device_nodes.&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *    &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/*&n; * Traverse_func that inits the PCI fields of the device node.&n; * NOTE: this *must* be done before read/write config to the device.&n; */
DECL|function|update_dn_pci_info
r_static
r_void
op_star
id|__init
id|update_dn_pci_info
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|pci_controller
op_star
id|phb
op_assign
id|data
suffix:semicolon
id|u32
op_star
id|regs
suffix:semicolon
r_char
op_star
id|device_type
op_assign
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;device_type&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_char
op_star
id|model
suffix:semicolon
id|dn-&gt;phb
op_assign
id|phb
suffix:semicolon
r_if
c_cond
(paren
id|device_type
op_logical_and
(paren
id|strcmp
c_func
(paren
id|device_type
comma
l_string|&quot;pci&quot;
)paren
op_eq
l_int|0
)paren
op_logical_and
(paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;class-code&quot;
comma
l_int|NULL
)paren
op_eq
l_int|0
)paren
)paren
(brace
multiline_comment|/* special case for PHB&squot;s.  Sigh. */
id|regs
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;bus-range&quot;
comma
l_int|NULL
)paren
suffix:semicolon
id|dn-&gt;busno
op_assign
id|regs
(braket
l_int|0
)braket
suffix:semicolon
id|model
op_assign
(paren
r_char
op_star
)paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|strstr
c_func
(paren
id|model
comma
l_string|&quot;U3&quot;
)paren
)paren
id|dn-&gt;devfn
op_assign
op_minus
l_int|1
suffix:semicolon
r_else
id|dn-&gt;devfn
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* assumption */
)brace
r_else
(brace
id|regs
op_assign
(paren
id|u32
op_star
)paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;reg&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|regs
)paren
(brace
multiline_comment|/* First register entry is addr (00BBSS00)  */
id|dn-&gt;busno
op_assign
(paren
id|regs
(braket
l_int|0
)braket
op_rshift
l_int|16
)paren
op_amp
l_int|0xff
suffix:semicolon
id|dn-&gt;devfn
op_assign
(paren
id|regs
(braket
l_int|0
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Traverse a device tree stopping each PCI device in the tree.&n; * This is done depth first.  As each node is processed, a &quot;pre&quot;&n; * function is called and the children are processed recursively.&n; *&n; * The &quot;pre&quot; func returns a value.  If non-zero is returned from&n; * the &quot;pre&quot; func, the traversal stops and this value is returned.&n; * This return value is useful when using traverse as a method of&n; * finding a device.&n; *&n; * NOTE: we do not run the func for devices that do not appear to&n; * be PCI except for the start node which we assume (this is good&n; * because the start node is often a phb which may be missing PCI&n; * properties).&n; * We use the class-code as an indicator. If we run into&n; * one of these nodes we also assume its siblings are non-pci for&n; * performance.&n; */
DECL|function|traverse_pci_devices
r_void
op_star
id|traverse_pci_devices
c_func
(paren
r_struct
id|device_node
op_star
id|start
comma
id|traverse_func
id|pre
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|device_node
op_star
id|dn
comma
op_star
id|nextdn
suffix:semicolon
r_void
op_star
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|pre
op_logical_and
(paren
(paren
id|ret
op_assign
id|pre
c_func
(paren
id|start
comma
id|data
)paren
)paren
op_ne
l_int|NULL
)paren
)paren
r_return
id|ret
suffix:semicolon
r_for
c_loop
(paren
id|dn
op_assign
id|start-&gt;child
suffix:semicolon
id|dn
suffix:semicolon
id|dn
op_assign
id|nextdn
)paren
(brace
id|nextdn
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;class-code&quot;
comma
l_int|NULL
)paren
)paren
(brace
r_if
c_cond
(paren
id|pre
op_logical_and
(paren
(paren
id|ret
op_assign
id|pre
c_func
(paren
id|dn
comma
id|data
)paren
)paren
op_ne
l_int|NULL
)paren
)paren
r_return
id|ret
suffix:semicolon
r_if
c_cond
(paren
id|dn-&gt;child
)paren
multiline_comment|/* Depth first...do children */
id|nextdn
op_assign
id|dn-&gt;child
suffix:semicolon
r_else
r_if
c_cond
(paren
id|dn-&gt;sibling
)paren
multiline_comment|/* ok, try next sibling instead. */
id|nextdn
op_assign
id|dn-&gt;sibling
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|nextdn
)paren
(brace
multiline_comment|/* Walk up to next valid sibling. */
r_do
(brace
id|dn
op_assign
id|dn-&gt;parent
suffix:semicolon
r_if
c_cond
(paren
id|dn
op_eq
id|start
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
r_while
c_loop
(paren
id|dn-&gt;sibling
op_eq
l_int|NULL
)paren
suffix:semicolon
id|nextdn
op_assign
id|dn-&gt;sibling
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Same as traverse_pci_devices except this does it for all phbs.&n; */
DECL|function|traverse_all_pci_devices
r_static
r_void
op_star
id|traverse_all_pci_devices
c_func
(paren
id|traverse_func
id|pre
)paren
(brace
r_struct
id|pci_controller
op_star
id|phb
comma
op_star
id|tmp
suffix:semicolon
r_void
op_star
id|ret
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|phb
comma
id|tmp
comma
op_amp
id|hose_list
comma
id|list_node
)paren
r_if
c_cond
(paren
(paren
id|ret
op_assign
id|traverse_pci_devices
c_func
(paren
id|phb-&gt;arch_data
comma
id|pre
comma
id|phb
)paren
)paren
op_ne
l_int|NULL
)paren
r_return
id|ret
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * Traversal func that looks for a &lt;busno,devfcn&gt; value.&n; * If found, the device_node is returned (thus terminating the traversal).&n; */
DECL|function|is_devfn_node
r_static
r_void
op_star
id|is_devfn_node
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|busno
op_assign
(paren
(paren
r_int
r_int
)paren
id|data
op_rshift
l_int|8
)paren
op_amp
l_int|0xff
suffix:semicolon
r_int
id|devfn
op_assign
(paren
(paren
r_int
r_int
)paren
id|data
)paren
op_amp
l_int|0xff
suffix:semicolon
r_return
(paren
(paren
id|devfn
op_eq
id|dn-&gt;devfn
)paren
op_logical_and
(paren
id|busno
op_eq
id|dn-&gt;busno
)paren
)paren
ques
c_cond
id|dn
suffix:colon
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/*&n; * This is the &quot;slow&quot; path for looking up a device_node from a&n; * pci_dev.  It will hunt for the device under its parent&squot;s&n; * phb and then update sysdata for a future fastpath.&n; *&n; * It may also do fixups on the actual device since this happens&n; * on the first read/write.&n; *&n; * Note that it also must deal with devices that don&squot;t exist.&n; * In this case it may probe for real hardware (&quot;just in case&quot;)&n; * and add a device_node to the device tree if necessary.&n; *&n; */
DECL|function|fetch_dev_dn
r_struct
id|device_node
op_star
id|fetch_dev_dn
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|device_node
op_star
id|orig_dn
op_assign
id|dev-&gt;sysdata
suffix:semicolon
r_struct
id|pci_controller
op_star
id|phb
op_assign
id|orig_dn-&gt;phb
suffix:semicolon
multiline_comment|/* assume same phb as orig_dn */
r_struct
id|device_node
op_star
id|phb_dn
suffix:semicolon
r_struct
id|device_node
op_star
id|dn
suffix:semicolon
r_int
r_int
id|searchval
op_assign
(paren
id|dev-&gt;bus-&gt;number
op_lshift
l_int|8
)paren
op_or
id|dev-&gt;devfn
suffix:semicolon
id|phb_dn
op_assign
id|phb-&gt;arch_data
suffix:semicolon
id|dn
op_assign
id|traverse_pci_devices
c_func
(paren
id|phb_dn
comma
id|is_devfn_node
comma
(paren
r_void
op_star
)paren
id|searchval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn
)paren
(brace
id|dev-&gt;sysdata
op_assign
id|dn
suffix:semicolon
multiline_comment|/* ToDo: call some device init hook here */
)brace
r_return
id|dn
suffix:semicolon
)brace
DECL|variable|fetch_dev_dn
id|EXPORT_SYMBOL
c_func
(paren
id|fetch_dev_dn
)paren
suffix:semicolon
multiline_comment|/*&n; * Actually initialize the phbs.&n; * The buswalk on this phb has not happened yet.&n; */
DECL|function|pci_devs_phb_init
r_void
id|__init
id|pci_devs_phb_init
c_func
(paren
r_void
)paren
(brace
multiline_comment|/* This must be done first so the device nodes have valid pci info! */
id|traverse_all_pci_devices
c_func
(paren
id|update_dn_pci_info
)paren
suffix:semicolon
)brace
DECL|function|pci_fixup_bus_sysdata_list
r_static
r_void
id|__init
id|pci_fixup_bus_sysdata_list
c_func
(paren
r_struct
id|list_head
op_star
id|bus_list
)paren
(brace
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_for
c_loop
(paren
id|ln
op_assign
id|bus_list-&gt;next
suffix:semicolon
id|ln
op_ne
id|bus_list
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
id|bus
op_assign
id|pci_bus_b
c_func
(paren
id|ln
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;self
)paren
id|bus-&gt;sysdata
op_assign
id|bus-&gt;self-&gt;sysdata
suffix:semicolon
id|pci_fixup_bus_sysdata_list
c_func
(paren
op_amp
id|bus-&gt;children
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Fixup the bus-&gt;sysdata ptrs to point to the bus&squot; device_node.&n; * This is done late in pcibios_init().  We do this mostly for&n; * sanity, but pci_dma.c uses these at DMA time so they must be&n; * correct.&n; * To do this we recurse down the bus hierarchy.  Note that PHB&squot;s&n; * have bus-&gt;self == NULL, but fortunately bus-&gt;sysdata is already&n; * correct in this case.&n; */
DECL|function|pci_fix_bus_sysdata
r_void
id|__init
id|pci_fix_bus_sysdata
c_func
(paren
r_void
)paren
(brace
id|pci_fixup_bus_sysdata_list
c_func
(paren
op_amp
id|pci_root_buses
)paren
suffix:semicolon
)brace
eof
