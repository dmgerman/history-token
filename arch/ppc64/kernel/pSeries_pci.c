multiline_comment|/*&n; * pSeries_pci.c&n; *&n; * Copyright (C) 2001 Dave Engebretsen, IBM Corporation&n; * Copyright (C) 2003 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *&n; * pSeries specific routines for PCI.&n; * &n; * Based on code from pci.c and chrp_pci.c&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *    &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &lt;asm/rtas.h&gt;
macro_line|#include &quot;mpic.h&quot;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/* RTAS tokens */
DECL|variable|read_pci_config
r_static
r_int
id|read_pci_config
suffix:semicolon
DECL|variable|write_pci_config
r_static
r_int
id|write_pci_config
suffix:semicolon
DECL|variable|ibm_read_pci_config
r_static
r_int
id|ibm_read_pci_config
suffix:semicolon
DECL|variable|ibm_write_pci_config
r_static
r_int
id|ibm_write_pci_config
suffix:semicolon
DECL|variable|s7a_workaround
r_static
r_int
id|s7a_workaround
suffix:semicolon
r_extern
r_struct
id|mpic
op_star
id|pSeries_mpic
suffix:semicolon
DECL|function|rtas_read_config
r_static
r_int
id|rtas_read_config
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|val
)paren
(brace
r_int
id|returnval
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
r_int
id|buid
comma
id|addr
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dn
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
(paren
id|size
op_minus
l_int|1
)paren
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
id|addr
op_assign
(paren
id|dn-&gt;busno
op_lshift
l_int|16
)paren
op_or
(paren
id|dn-&gt;devfn
op_lshift
l_int|8
)paren
op_or
id|where
suffix:semicolon
id|buid
op_assign
id|dn-&gt;phb-&gt;buid
suffix:semicolon
r_if
c_cond
(paren
id|buid
)paren
(brace
id|ret
op_assign
id|rtas_call
c_func
(paren
id|ibm_read_pci_config
comma
l_int|4
comma
l_int|2
comma
op_amp
id|returnval
comma
id|addr
comma
id|buid
op_rshift
l_int|32
comma
id|buid
op_amp
l_int|0xffffffff
comma
id|size
)paren
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|rtas_call
c_func
(paren
id|read_pci_config
comma
l_int|2
comma
l_int|2
comma
op_amp
id|returnval
comma
id|addr
comma
id|size
)paren
suffix:semicolon
)brace
op_star
id|val
op_assign
id|returnval
suffix:semicolon
r_if
c_cond
(paren
id|ret
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_if
c_cond
(paren
id|returnval
op_eq
id|EEH_IO_ERROR_VALUE
c_func
(paren
id|size
)paren
op_logical_and
id|eeh_dn_check_failure
(paren
id|dn
comma
l_int|NULL
)paren
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|rtas_pci_read_config
r_static
r_int
id|rtas_pci_read_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
op_star
id|val
)paren
(brace
r_struct
id|device_node
op_star
id|busdn
comma
op_star
id|dn
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;self
)paren
id|busdn
op_assign
id|pci_device_to_OF_node
c_func
(paren
id|bus-&gt;self
)paren
suffix:semicolon
r_else
id|busdn
op_assign
id|bus-&gt;sysdata
suffix:semicolon
multiline_comment|/* must be a phb */
multiline_comment|/* Search only direct children of the bus */
r_for
c_loop
(paren
id|dn
op_assign
id|busdn-&gt;child
suffix:semicolon
id|dn
suffix:semicolon
id|dn
op_assign
id|dn-&gt;sibling
)paren
r_if
c_cond
(paren
id|dn-&gt;devfn
op_eq
id|devfn
)paren
r_return
id|rtas_read_config
c_func
(paren
id|dn
comma
id|where
comma
id|size
comma
id|val
)paren
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
DECL|function|rtas_write_config
r_static
r_int
id|rtas_write_config
c_func
(paren
r_struct
id|device_node
op_star
id|dn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|val
)paren
(brace
r_int
r_int
id|buid
comma
id|addr
suffix:semicolon
r_int
id|ret
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dn
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_if
c_cond
(paren
id|where
op_amp
(paren
id|size
op_minus
l_int|1
)paren
)paren
r_return
id|PCIBIOS_BAD_REGISTER_NUMBER
suffix:semicolon
id|addr
op_assign
(paren
id|dn-&gt;busno
op_lshift
l_int|16
)paren
op_or
(paren
id|dn-&gt;devfn
op_lshift
l_int|8
)paren
op_or
id|where
suffix:semicolon
id|buid
op_assign
id|dn-&gt;phb-&gt;buid
suffix:semicolon
r_if
c_cond
(paren
id|buid
)paren
(brace
id|ret
op_assign
id|rtas_call
c_func
(paren
id|ibm_write_pci_config
comma
l_int|5
comma
l_int|1
comma
l_int|NULL
comma
id|addr
comma
id|buid
op_rshift
l_int|32
comma
id|buid
op_amp
l_int|0xffffffff
comma
id|size
comma
(paren
id|ulong
)paren
id|val
)paren
suffix:semicolon
)brace
r_else
(brace
id|ret
op_assign
id|rtas_call
c_func
(paren
id|write_pci_config
comma
l_int|3
comma
l_int|1
comma
l_int|NULL
comma
id|addr
comma
id|size
comma
(paren
id|ulong
)paren
id|val
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|rtas_pci_write_config
r_static
r_int
id|rtas_pci_write_config
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|devfn
comma
r_int
id|where
comma
r_int
id|size
comma
id|u32
id|val
)paren
(brace
r_struct
id|device_node
op_star
id|busdn
comma
op_star
id|dn
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;self
)paren
id|busdn
op_assign
id|pci_device_to_OF_node
c_func
(paren
id|bus-&gt;self
)paren
suffix:semicolon
r_else
id|busdn
op_assign
id|bus-&gt;sysdata
suffix:semicolon
multiline_comment|/* must be a phb */
multiline_comment|/* Search only direct children of the bus */
r_for
c_loop
(paren
id|dn
op_assign
id|busdn-&gt;child
suffix:semicolon
id|dn
suffix:semicolon
id|dn
op_assign
id|dn-&gt;sibling
)paren
r_if
c_cond
(paren
id|dn-&gt;devfn
op_eq
id|devfn
)paren
r_return
id|rtas_write_config
c_func
(paren
id|dn
comma
id|where
comma
id|size
comma
id|val
)paren
suffix:semicolon
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
)brace
DECL|variable|rtas_pci_ops
r_struct
id|pci_ops
id|rtas_pci_ops
op_assign
(brace
id|rtas_pci_read_config
comma
id|rtas_pci_write_config
)brace
suffix:semicolon
DECL|function|is_python
r_static
r_int
id|is_python
c_func
(paren
r_struct
id|device_node
op_star
id|dev
)paren
(brace
r_char
op_star
id|model
op_assign
(paren
r_char
op_star
)paren
id|get_property
c_func
(paren
id|dev
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model
op_logical_and
id|strstr
c_func
(paren
id|model
comma
l_string|&quot;Python&quot;
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|python_countermeasures
r_static
r_void
id|python_countermeasures
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_void
id|__iomem
op_star
id|chip_regs
suffix:semicolon
r_volatile
id|u32
id|val
suffix:semicolon
multiline_comment|/* Python&squot;s register file is 1 MB in size. */
id|chip_regs
op_assign
id|ioremap
c_func
(paren
id|addr
op_amp
op_complement
(paren
l_int|0xfffffUL
)paren
comma
l_int|0x100000
)paren
suffix:semicolon
multiline_comment|/* &n;&t; * Firmware doesn&squot;t always clear this bit which is critical&n;&t; * for good performance - Anton&n;&t; */
DECL|macro|PRG_CL_RESET_VALID
mdefine_line|#define PRG_CL_RESET_VALID 0x00010000
id|val
op_assign
id|in_be32
c_func
(paren
id|chip_regs
op_plus
l_int|0xf6030
)paren
suffix:semicolon
r_if
c_cond
(paren
id|val
op_amp
id|PRG_CL_RESET_VALID
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Python workaround: &quot;
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|PRG_CL_RESET_VALID
suffix:semicolon
id|out_be32
c_func
(paren
id|chip_regs
op_plus
l_int|0xf6030
comma
id|val
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * We must read it back for changes to&n;&t;&t; * take effect&n;&t;&t; */
id|val
op_assign
id|in_be32
c_func
(paren
id|chip_regs
op_plus
l_int|0xf6030
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;reg0: %x&bslash;n&quot;
comma
id|val
)paren
suffix:semicolon
)brace
id|iounmap
c_func
(paren
id|chip_regs
)paren
suffix:semicolon
)brace
DECL|function|init_pci_config_tokens
r_void
id|__init
id|init_pci_config_tokens
(paren
r_void
)paren
(brace
id|read_pci_config
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;read-pci-config&quot;
)paren
suffix:semicolon
id|write_pci_config
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;write-pci-config&quot;
)paren
suffix:semicolon
id|ibm_read_pci_config
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,read-pci-config&quot;
)paren
suffix:semicolon
id|ibm_write_pci_config
op_assign
id|rtas_token
c_func
(paren
l_string|&quot;ibm,write-pci-config&quot;
)paren
suffix:semicolon
)brace
DECL|function|get_phb_buid
r_int
r_int
id|__devinit
id|get_phb_buid
(paren
r_struct
id|device_node
op_star
id|phb
)paren
(brace
r_int
id|addr_cells
suffix:semicolon
r_int
r_int
op_star
id|buid_vals
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
r_int
r_int
id|buid
suffix:semicolon
r_if
c_cond
(paren
id|ibm_read_pci_config
op_eq
op_minus
l_int|1
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* PHB&squot;s will always be children of the root node,&n;&t; * or so it is promised by the current firmware. */
r_if
c_cond
(paren
id|phb-&gt;parent
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|phb-&gt;parent-&gt;parent
)paren
r_return
l_int|0
suffix:semicolon
id|buid_vals
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|phb
comma
l_string|&quot;reg&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|buid_vals
op_eq
l_int|NULL
)paren
r_return
l_int|0
suffix:semicolon
id|addr_cells
op_assign
id|prom_n_addr_cells
c_func
(paren
id|phb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr_cells
op_eq
l_int|1
)paren
(brace
id|buid
op_assign
(paren
r_int
r_int
)paren
id|buid_vals
(braket
l_int|0
)braket
suffix:semicolon
)brace
r_else
(brace
id|buid
op_assign
(paren
(paren
(paren
r_int
r_int
)paren
id|buid_vals
(braket
l_int|0
)braket
)paren
op_lshift
l_int|32UL
)paren
op_or
(paren
(paren
(paren
r_int
r_int
)paren
id|buid_vals
(braket
l_int|1
)braket
)paren
op_amp
l_int|0xffffffff
)paren
suffix:semicolon
)brace
r_return
id|buid
suffix:semicolon
)brace
DECL|function|get_phb_reg_prop
r_static
r_int
id|get_phb_reg_prop
c_func
(paren
r_struct
id|device_node
op_star
id|dev
comma
r_int
r_int
id|addr_size_words
comma
r_struct
id|reg_property64
op_star
id|reg
)paren
(brace
r_int
r_int
op_star
id|ui_ptr
op_assign
l_int|NULL
comma
id|len
suffix:semicolon
multiline_comment|/* Found a PHB, now figure out where his registers are mapped. */
id|ui_ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dev
comma
l_string|&quot;reg&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ui_ptr
op_eq
l_int|NULL
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|addr_size_words
op_eq
l_int|1
)paren
(brace
id|reg-&gt;address
op_assign
(paren
(paren
r_struct
id|reg_property32
op_star
)paren
id|ui_ptr
)paren
op_member_access_from_pointer
id|address
suffix:semicolon
id|reg-&gt;size
op_assign
(paren
(paren
r_struct
id|reg_property32
op_star
)paren
id|ui_ptr
)paren
op_member_access_from_pointer
id|size
suffix:semicolon
)brace
r_else
(brace
op_star
id|reg
op_assign
op_star
(paren
(paren
r_struct
id|reg_property64
op_star
)paren
id|ui_ptr
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|phb_set_bus_ranges
r_static
r_int
id|phb_set_bus_ranges
c_func
(paren
r_struct
id|device_node
op_star
id|dev
comma
r_struct
id|pci_controller
op_star
id|phb
)paren
(brace
r_int
op_star
id|bus_range
suffix:semicolon
r_int
r_int
id|len
suffix:semicolon
id|bus_range
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|dev
comma
l_string|&quot;bus-range&quot;
comma
op_amp
id|len
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus_range
op_eq
l_int|NULL
op_logical_or
id|len
OL
l_int|2
op_star
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
id|phb-&gt;first_busno
op_assign
id|bus_range
(braket
l_int|0
)braket
suffix:semicolon
id|phb-&gt;last_busno
op_assign
id|bus_range
(braket
l_int|1
)braket
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alloc_phb
r_static
r_struct
id|pci_controller
op_star
id|alloc_phb
c_func
(paren
r_struct
id|device_node
op_star
id|dev
comma
r_int
r_int
id|addr_size_words
)paren
(brace
r_struct
id|pci_controller
op_star
id|phb
suffix:semicolon
r_struct
id|reg_property64
id|reg_struct
suffix:semicolon
r_struct
id|property
op_star
id|of_prop
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|get_phb_reg_prop
c_func
(paren
id|dev
comma
id|addr_size_words
comma
op_amp
id|reg_struct
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
l_int|NULL
suffix:semicolon
id|phb
op_assign
id|pci_alloc_pci_controller
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phb
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|is_python
c_func
(paren
id|dev
)paren
)paren
id|python_countermeasures
c_func
(paren
id|reg_struct.address
)paren
suffix:semicolon
id|rc
op_assign
id|phb_set_bus_ranges
c_func
(paren
id|dev
comma
id|phb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
l_int|NULL
suffix:semicolon
id|of_prop
op_assign
(paren
r_struct
id|property
op_star
)paren
id|alloc_bootmem
c_func
(paren
r_sizeof
(paren
r_struct
id|property
)paren
op_plus
r_sizeof
(paren
id|phb-&gt;global_number
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|of_prop
)paren
(brace
id|kfree
c_func
(paren
id|phb
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|of_prop
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|property
)paren
)paren
suffix:semicolon
id|of_prop-&gt;name
op_assign
l_string|&quot;linux,pci-domain&quot;
suffix:semicolon
id|of_prop-&gt;length
op_assign
r_sizeof
(paren
id|phb-&gt;global_number
)paren
suffix:semicolon
id|of_prop-&gt;value
op_assign
(paren
r_int
r_char
op_star
)paren
op_amp
id|of_prop
(braket
l_int|1
)braket
suffix:semicolon
id|memcpy
c_func
(paren
id|of_prop-&gt;value
comma
op_amp
id|phb-&gt;global_number
comma
r_sizeof
(paren
id|phb-&gt;global_number
)paren
)paren
suffix:semicolon
id|prom_add_property
c_func
(paren
id|dev
comma
id|of_prop
)paren
suffix:semicolon
id|phb-&gt;arch_data
op_assign
id|dev
suffix:semicolon
id|phb-&gt;ops
op_assign
op_amp
id|rtas_pci_ops
suffix:semicolon
id|phb-&gt;buid
op_assign
id|get_phb_buid
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|phb
suffix:semicolon
)brace
DECL|function|alloc_phb_dynamic
r_static
r_struct
id|pci_controller
op_star
id|__devinit
id|alloc_phb_dynamic
c_func
(paren
r_struct
id|device_node
op_star
id|dev
comma
r_int
r_int
id|addr_size_words
)paren
(brace
r_struct
id|pci_controller
op_star
id|phb
suffix:semicolon
r_struct
id|reg_property64
id|reg_struct
suffix:semicolon
r_int
id|rc
suffix:semicolon
id|rc
op_assign
id|get_phb_reg_prop
c_func
(paren
id|dev
comma
id|addr_size_words
comma
op_amp
id|reg_struct
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
l_int|NULL
suffix:semicolon
id|phb
op_assign
id|pci_alloc_phb_dynamic
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phb
op_eq
l_int|NULL
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|is_python
c_func
(paren
id|dev
)paren
)paren
id|python_countermeasures
c_func
(paren
id|reg_struct.address
)paren
suffix:semicolon
id|rc
op_assign
id|phb_set_bus_ranges
c_func
(paren
id|dev
comma
id|phb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
r_return
l_int|NULL
suffix:semicolon
multiline_comment|/* TODO: linux,pci-domain? */
id|phb-&gt;arch_data
op_assign
id|dev
suffix:semicolon
id|phb-&gt;ops
op_assign
op_amp
id|rtas_pci_ops
suffix:semicolon
id|phb-&gt;buid
op_assign
id|get_phb_buid
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|phb
suffix:semicolon
)brace
DECL|function|find_and_init_phbs
r_int
r_int
id|__init
id|find_and_init_phbs
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|node
suffix:semicolon
r_struct
id|pci_controller
op_star
id|phb
suffix:semicolon
r_int
r_int
id|root_size_cells
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|index
suffix:semicolon
r_int
r_int
op_star
id|opprop
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|device_node
op_star
id|root
op_assign
id|of_find_node_by_path
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|naca-&gt;interrupt_controller
op_eq
id|IC_OPEN_PIC
)paren
(brace
id|opprop
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;platform-open-pic&quot;
comma
l_int|NULL
)paren
suffix:semicolon
)brace
id|root_size_cells
op_assign
id|prom_n_size_cells
c_func
(paren
id|root
)paren
suffix:semicolon
id|index
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|node
op_assign
id|of_get_next_child
c_func
(paren
id|root
comma
l_int|NULL
)paren
suffix:semicolon
id|node
op_ne
l_int|NULL
suffix:semicolon
id|node
op_assign
id|of_get_next_child
c_func
(paren
id|root
comma
id|node
)paren
)paren
(brace
r_if
c_cond
(paren
id|node-&gt;type
op_eq
l_int|NULL
op_logical_or
id|strcmp
c_func
(paren
id|node-&gt;type
comma
l_string|&quot;pci&quot;
)paren
op_ne
l_int|0
)paren
r_continue
suffix:semicolon
id|phb
op_assign
id|alloc_phb
c_func
(paren
id|node
comma
id|root_size_cells
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|phb
)paren
r_continue
suffix:semicolon
id|pci_process_bridge_OF_ranges
c_func
(paren
id|phb
comma
id|node
)paren
suffix:semicolon
id|pci_setup_phb_io
c_func
(paren
id|phb
comma
id|index
op_eq
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|naca-&gt;interrupt_controller
op_eq
id|IC_OPEN_PIC
op_logical_and
id|pSeries_mpic
)paren
(brace
r_int
id|addr
op_assign
id|root_size_cells
op_star
(paren
id|index
op_plus
l_int|2
)paren
op_minus
l_int|1
suffix:semicolon
id|mpic_assign_isu
c_func
(paren
id|pSeries_mpic
comma
id|index
comma
id|opprop
(braket
id|addr
)braket
)paren
suffix:semicolon
)brace
id|index
op_increment
suffix:semicolon
)brace
id|of_node_put
c_func
(paren
id|root
)paren
suffix:semicolon
id|pci_devs_phb_init
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|init_phb_dynamic
r_struct
id|pci_controller
op_star
id|__devinit
id|init_phb_dynamic
c_func
(paren
r_struct
id|device_node
op_star
id|dn
)paren
(brace
r_struct
id|device_node
op_star
id|root
op_assign
id|of_find_node_by_path
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_int
r_int
id|root_size_cells
op_assign
l_int|0
suffix:semicolon
r_struct
id|pci_controller
op_star
id|phb
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
id|root_size_cells
op_assign
id|prom_n_size_cells
c_func
(paren
id|root
)paren
suffix:semicolon
id|phb
op_assign
id|alloc_phb_dynamic
c_func
(paren
id|dn
comma
id|root_size_cells
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|phb
)paren
r_return
l_int|NULL
suffix:semicolon
id|pci_process_bridge_OF_ranges
c_func
(paren
id|phb
comma
id|dn
)paren
suffix:semicolon
id|pci_setup_phb_io_dynamic
c_func
(paren
id|phb
)paren
suffix:semicolon
id|of_node_put
c_func
(paren
id|root
)paren
suffix:semicolon
id|pci_devs_phb_init_dynamic
c_func
(paren
id|phb
)paren
suffix:semicolon
id|phb-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|bus
op_assign
id|pci_scan_bus
c_func
(paren
id|phb-&gt;first_busno
comma
id|phb-&gt;ops
comma
id|phb-&gt;arch_data
)paren
suffix:semicolon
id|phb-&gt;bus
op_assign
id|bus
suffix:semicolon
id|phb-&gt;last_busno
op_assign
id|bus-&gt;subordinate
suffix:semicolon
r_return
id|phb
suffix:semicolon
)brace
DECL|variable|init_phb_dynamic
id|EXPORT_SYMBOL
c_func
(paren
id|init_phb_dynamic
)paren
suffix:semicolon
macro_line|#if 0
r_void
id|pcibios_name_device
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
id|dn
suffix:semicolon
multiline_comment|/*&n;&t; * Add IBM loc code (slot) as a prefix to the device names for service&n;&t; */
id|dn
op_assign
id|pci_device_to_OF_node
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dn
)paren
(brace
r_char
op_star
id|loc_code
op_assign
id|get_property
c_func
(paren
id|dn
comma
l_string|&quot;ibm,loc-code&quot;
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|loc_code
)paren
(brace
r_int
id|loc_len
op_assign
id|strlen
c_func
(paren
id|loc_code
)paren
suffix:semicolon
r_if
c_cond
(paren
id|loc_len
OL
r_sizeof
(paren
id|dev-&gt;dev.name
)paren
)paren
(brace
id|memmove
c_func
(paren
id|dev-&gt;dev.name
op_plus
id|loc_len
op_plus
l_int|1
comma
id|dev-&gt;dev.name
comma
r_sizeof
(paren
id|dev-&gt;dev.name
)paren
op_minus
id|loc_len
op_minus
l_int|1
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;dev.name
comma
id|loc_code
comma
id|loc_len
)paren
suffix:semicolon
id|dev-&gt;dev.name
(braket
id|loc_len
)braket
op_assign
l_char|&squot; &squot;
suffix:semicolon
id|dev-&gt;dev.name
(braket
r_sizeof
(paren
id|dev-&gt;dev.name
)paren
op_minus
l_int|1
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
)brace
)brace
)brace
)brace
id|DECLARE_PCI_FIXUP_HEADER
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|pcibios_name_device
)paren
suffix:semicolon
macro_line|#endif
DECL|function|check_s7a
r_static
r_void
id|check_s7a
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|root
suffix:semicolon
r_char
op_star
id|model
suffix:semicolon
id|root
op_assign
id|of_find_node_by_path
c_func
(paren
l_string|&quot;/&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|root
)paren
(brace
id|model
op_assign
id|get_property
c_func
(paren
id|root
comma
l_string|&quot;model&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|model
op_logical_and
op_logical_neg
id|strcmp
c_func
(paren
id|model
comma
l_string|&quot;IBM,7013-S7A&quot;
)paren
)paren
id|s7a_workaround
op_assign
l_int|1
suffix:semicolon
id|of_node_put
c_func
(paren
id|root
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* RPA-specific bits for removing PHBs */
DECL|function|pcibios_remove_root_bus
r_int
id|pcibios_remove_root_bus
c_func
(paren
r_struct
id|pci_controller
op_star
id|phb
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
op_assign
id|phb-&gt;bus
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_int
id|rc
comma
id|i
suffix:semicolon
id|res
op_assign
id|b-&gt;resource
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res-&gt;flags
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: no IO resource for PHB %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|b-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|rc
op_assign
id|unmap_bus_range
c_func
(paren
id|b
)paren
suffix:semicolon
r_if
c_cond
(paren
id|rc
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to unmap IO on bus %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|b-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|release_resource
c_func
(paren
id|res
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to release IO on bus %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|b-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|3
suffix:semicolon
op_increment
id|i
)paren
(brace
id|res
op_assign
id|b-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|res-&gt;flags
op_logical_and
id|i
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: no MEM resource for PHB %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|b-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|res-&gt;flags
op_logical_and
id|release_resource
c_func
(paren
id|res
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;%s: failed to release IO %d on bus %s&bslash;n&quot;
comma
id|__FUNCTION__
comma
id|i
comma
id|b-&gt;name
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
)brace
id|list_del
c_func
(paren
op_amp
id|phb-&gt;list_node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|phb-&gt;is_dynamic
)paren
id|kfree
c_func
(paren
id|phb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pcibios_remove_root_bus
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_remove_root_bus
)paren
suffix:semicolon
DECL|function|pSeries_request_regions
r_static
r_void
id|__init
id|pSeries_request_regions
c_func
(paren
r_void
)paren
(brace
id|request_region
c_func
(paren
l_int|0x20
comma
l_int|0x20
comma
l_string|&quot;pic1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xa0
comma
l_int|0x20
comma
l_string|&quot;pic2&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x00
comma
l_int|0x20
comma
l_string|&quot;dma1&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x40
comma
l_int|0x20
comma
l_string|&quot;timer&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0x80
comma
l_int|0x10
comma
l_string|&quot;dma page reg&quot;
)paren
suffix:semicolon
id|request_region
c_func
(paren
l_int|0xc0
comma
l_int|0x20
comma
l_string|&quot;dma2&quot;
)paren
suffix:semicolon
)brace
DECL|function|pSeries_final_fixup
r_void
id|__init
id|pSeries_final_fixup
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|check_s7a
c_func
(paren
)paren
suffix:semicolon
id|for_each_pci_dev
c_func
(paren
id|dev
)paren
(brace
id|pci_read_irq_line
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|s7a_workaround
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;irq
OG
l_int|16
)paren
(brace
id|dev-&gt;irq
op_sub_assign
l_int|3
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
)brace
)brace
id|phbs_remap_io
c_func
(paren
)paren
suffix:semicolon
id|pSeries_request_regions
c_func
(paren
)paren
suffix:semicolon
id|pci_fix_bus_sysdata
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|of_chosen
op_logical_or
op_logical_neg
id|get_property
c_func
(paren
id|of_chosen
comma
l_string|&quot;linux,iommu-off&quot;
comma
l_int|NULL
)paren
)paren
id|iommu_setup_pSeries
c_func
(paren
)paren
suffix:semicolon
id|pci_addr_cache_build
c_func
(paren
)paren
suffix:semicolon
)brace
eof
