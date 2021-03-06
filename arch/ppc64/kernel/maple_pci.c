multiline_comment|/*&n; * Copyright (C) 2004 Benjamin Herrenschmuidt (benh@kernel.crashing.org),&n; *&t;&t;      IBM Corp.&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License&n; * as published by the Free Software Foundation; either version&n; * 2 of the License, or (at your option) any later version.&n; */
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;asm/sections.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/machdep.h&gt;
macro_line|#include &lt;asm/iommu.h&gt;
macro_line|#include &quot;pci.h&quot;
macro_line|#ifdef DEBUG
DECL|macro|DBG
mdefine_line|#define DBG(x...) printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
DECL|variable|u3_agp
DECL|variable|u3_ht
r_static
r_struct
id|pci_controller
op_star
id|u3_agp
comma
op_star
id|u3_ht
suffix:semicolon
DECL|function|fixup_one_level_bus_range
r_static
r_int
id|__init
id|fixup_one_level_bus_range
c_func
(paren
r_struct
id|device_node
op_star
id|node
comma
r_int
id|higher
)paren
(brace
r_for
c_loop
(paren
suffix:semicolon
id|node
op_ne
l_int|0
suffix:semicolon
id|node
op_assign
id|node-&gt;sibling
)paren
(brace
r_int
op_star
id|bus_range
suffix:semicolon
r_int
r_int
op_star
id|class_code
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* For PCI&lt;-&gt;PCI bridges or CardBus bridges, we go down */
id|class_code
op_assign
(paren
r_int
r_int
op_star
)paren
id|get_property
c_func
(paren
id|node
comma
l_string|&quot;class-code&quot;
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|class_code
op_logical_or
(paren
(paren
op_star
id|class_code
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_BRIDGE_PCI
op_logical_and
(paren
op_star
id|class_code
op_rshift
l_int|8
)paren
op_ne
id|PCI_CLASS_BRIDGE_CARDBUS
)paren
)paren
r_continue
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
id|node
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
op_ne
l_int|NULL
op_logical_and
id|len
OG
l_int|2
op_star
r_sizeof
(paren
r_int
)paren
)paren
(brace
r_if
c_cond
(paren
id|bus_range
(braket
l_int|1
)braket
OG
id|higher
)paren
id|higher
op_assign
id|bus_range
(braket
l_int|1
)braket
suffix:semicolon
)brace
id|higher
op_assign
id|fixup_one_level_bus_range
c_func
(paren
id|node-&gt;child
comma
id|higher
)paren
suffix:semicolon
)brace
r_return
id|higher
suffix:semicolon
)brace
multiline_comment|/* This routine fixes the &quot;bus-range&quot; property of all bridges in the&n; * system since they tend to have their &quot;last&quot; member wrong on macs&n; *&n; * Note that the bus numbers manipulated here are OF bus numbers, they&n; * are not Linux bus numbers.&n; */
DECL|function|fixup_bus_range
r_static
r_void
id|__init
id|fixup_bus_range
c_func
(paren
r_struct
id|device_node
op_star
id|bridge
)paren
(brace
r_int
op_star
id|bus_range
suffix:semicolon
r_int
id|len
suffix:semicolon
multiline_comment|/* Lookup the &quot;bus-range&quot; property for the hose */
id|bus_range
op_assign
(paren
r_int
op_star
)paren
id|get_property
c_func
(paren
id|bridge
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t get bus-range for %s&bslash;n&quot;
comma
id|bridge-&gt;full_name
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|bus_range
(braket
l_int|1
)braket
op_assign
id|fixup_one_level_bus_range
c_func
(paren
id|bridge-&gt;child
comma
id|bus_range
(braket
l_int|1
)braket
)paren
suffix:semicolon
)brace
DECL|macro|U3_AGP_CFA0
mdefine_line|#define U3_AGP_CFA0(devfn, off)&t;&bslash;&n;&t;((1 &lt;&lt; (unsigned long)PCI_SLOT(dev_fn)) &bslash;&n;&t;| (((unsigned long)PCI_FUNC(dev_fn)) &lt;&lt; 8) &bslash;&n;&t;| (((unsigned long)(off)) &amp; 0xFCUL))
DECL|macro|U3_AGP_CFA1
mdefine_line|#define U3_AGP_CFA1(bus, devfn, off)&t;&bslash;&n;&t;((((unsigned long)(bus)) &lt;&lt; 16) &bslash;&n;&t;|(((unsigned long)(devfn)) &lt;&lt; 8) &bslash;&n;&t;|(((unsigned long)(off)) &amp; 0xFCUL) &bslash;&n;&t;|1UL)
DECL|function|u3_agp_cfg_access
r_static
r_int
r_int
id|u3_agp_cfg_access
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|u8
id|bus
comma
id|u8
id|dev_fn
comma
id|u8
id|offset
)paren
(brace
r_int
r_int
id|caddr
suffix:semicolon
r_if
c_cond
(paren
id|bus
op_eq
id|hose-&gt;first_busno
)paren
(brace
r_if
c_cond
(paren
id|dev_fn
OL
(paren
l_int|11
op_lshift
l_int|3
)paren
)paren
r_return
l_int|0
suffix:semicolon
id|caddr
op_assign
id|U3_AGP_CFA0
c_func
(paren
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
)brace
r_else
id|caddr
op_assign
id|U3_AGP_CFA1
c_func
(paren
id|bus
comma
id|dev_fn
comma
id|offset
)paren
suffix:semicolon
multiline_comment|/* Uninorth will return garbage if we don&squot;t read back the value ! */
r_do
(brace
id|out_le32
c_func
(paren
id|hose-&gt;cfg_addr
comma
id|caddr
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|in_le32
c_func
(paren
id|hose-&gt;cfg_addr
)paren
op_ne
id|caddr
)paren
suffix:semicolon
id|offset
op_and_assign
l_int|0x07
suffix:semicolon
r_return
(paren
(paren
r_int
r_int
)paren
id|hose-&gt;cfg_data
)paren
op_plus
id|offset
suffix:semicolon
)brace
DECL|function|u3_agp_read_config
r_static
r_int
id|u3_agp_read_config
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
id|offset
comma
r_int
id|len
comma
id|u32
op_star
id|val
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|hose
op_assign
id|pci_bus_to_host
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hose
op_eq
l_int|NULL
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|addr
op_assign
id|u3_agp_cfg_access
c_func
(paren
id|hose
comma
id|bus-&gt;number
comma
id|devfn
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
multiline_comment|/*&n;&t; * Note: the caller has already checked that offset is&n;&t; * suitably aligned and that len is 1, 2 or 4.&n;&t; */
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|val
op_assign
id|in_8
c_func
(paren
(paren
id|u8
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|val
op_assign
id|in_le16
c_func
(paren
(paren
id|u16
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|val
op_assign
id|in_le32
c_func
(paren
(paren
id|u32
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|u3_agp_write_config
r_static
r_int
id|u3_agp_write_config
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
id|offset
comma
r_int
id|len
comma
id|u32
id|val
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|hose
op_assign
id|pci_bus_to_host
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hose
op_eq
l_int|NULL
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|addr
op_assign
id|u3_agp_cfg_access
c_func
(paren
id|hose
comma
id|bus-&gt;number
comma
id|devfn
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
multiline_comment|/*&n;&t; * Note: the caller has already checked that offset is&n;&t; * suitably aligned and that len is 1, 2 or 4.&n;&t; */
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
id|out_8
c_func
(paren
(paren
id|u8
op_star
)paren
id|addr
comma
id|val
)paren
suffix:semicolon
(paren
r_void
)paren
id|in_8
c_func
(paren
(paren
id|u8
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|out_le16
c_func
(paren
(paren
id|u16
op_star
)paren
id|addr
comma
id|val
)paren
suffix:semicolon
(paren
r_void
)paren
id|in_le16
c_func
(paren
(paren
id|u16
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|out_le32
c_func
(paren
(paren
id|u32
op_star
)paren
id|addr
comma
id|val
)paren
suffix:semicolon
(paren
r_void
)paren
id|in_le32
c_func
(paren
(paren
id|u32
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|u3_agp_pci_ops
r_static
r_struct
id|pci_ops
id|u3_agp_pci_ops
op_assign
(brace
id|u3_agp_read_config
comma
id|u3_agp_write_config
)brace
suffix:semicolon
DECL|macro|U3_HT_CFA0
mdefine_line|#define U3_HT_CFA0(devfn, off)&t;&t;&bslash;&n;&t;&t;((((unsigned long)devfn) &lt;&lt; 8) | offset)
DECL|macro|U3_HT_CFA1
mdefine_line|#define U3_HT_CFA1(bus, devfn, off)&t;&bslash;&n;&t;&t;(U3_HT_CFA0(devfn, off) &bslash;&n;&t;&t;+ (((unsigned long)bus) &lt;&lt; 16) &bslash;&n;&t;&t;+ 0x01000000UL)
DECL|function|u3_ht_cfg_access
r_static
r_int
r_int
id|u3_ht_cfg_access
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
id|u8
id|bus
comma
id|u8
id|devfn
comma
id|u8
id|offset
)paren
(brace
r_if
c_cond
(paren
id|bus
op_eq
id|hose-&gt;first_busno
)paren
(brace
r_if
c_cond
(paren
id|PCI_SLOT
c_func
(paren
id|devfn
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
(paren
(paren
r_int
r_int
)paren
id|hose-&gt;cfg_data
)paren
op_plus
id|U3_HT_CFA0
c_func
(paren
id|devfn
comma
id|offset
)paren
suffix:semicolon
)brace
r_else
r_return
(paren
(paren
r_int
r_int
)paren
id|hose-&gt;cfg_data
)paren
op_plus
id|U3_HT_CFA1
c_func
(paren
id|bus
comma
id|devfn
comma
id|offset
)paren
suffix:semicolon
)brace
DECL|function|u3_ht_read_config
r_static
r_int
id|u3_ht_read_config
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
id|offset
comma
r_int
id|len
comma
id|u32
op_star
id|val
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|hose
op_assign
id|pci_bus_to_host
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hose
op_eq
l_int|NULL
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|addr
op_assign
id|u3_ht_cfg_access
c_func
(paren
id|hose
comma
id|bus-&gt;number
comma
id|devfn
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
multiline_comment|/*&n;&t; * Note: the caller has already checked that offset is&n;&t; * suitably aligned and that len is 1, 2 or 4.&n;&t; */
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
op_star
id|val
op_assign
id|in_8
c_func
(paren
(paren
id|u8
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
op_star
id|val
op_assign
id|in_le16
c_func
(paren
(paren
id|u16
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
op_star
id|val
op_assign
id|in_le32
c_func
(paren
(paren
id|u32
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|function|u3_ht_write_config
r_static
r_int
id|u3_ht_write_config
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
id|offset
comma
r_int
id|len
comma
id|u32
id|val
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_int
r_int
id|addr
suffix:semicolon
id|hose
op_assign
id|pci_bus_to_host
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hose
op_eq
l_int|NULL
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
id|addr
op_assign
id|u3_ht_cfg_access
c_func
(paren
id|hose
comma
id|bus-&gt;number
comma
id|devfn
comma
id|offset
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|addr
)paren
r_return
id|PCIBIOS_DEVICE_NOT_FOUND
suffix:semicolon
multiline_comment|/*&n;&t; * Note: the caller has already checked that offset is&n;&t; * suitably aligned and that len is 1, 2 or 4.&n;&t; */
r_switch
c_cond
(paren
id|len
)paren
(brace
r_case
l_int|1
suffix:colon
id|out_8
c_func
(paren
(paren
id|u8
op_star
)paren
id|addr
comma
id|val
)paren
suffix:semicolon
(paren
r_void
)paren
id|in_8
c_func
(paren
(paren
id|u8
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|out_le16
c_func
(paren
(paren
id|u16
op_star
)paren
id|addr
comma
id|val
)paren
suffix:semicolon
(paren
r_void
)paren
id|in_le16
c_func
(paren
(paren
id|u16
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|out_le32
c_func
(paren
(paren
id|u32
op_star
)paren
id|addr
comma
id|val
)paren
suffix:semicolon
(paren
r_void
)paren
id|in_le32
c_func
(paren
(paren
id|u32
op_star
)paren
id|addr
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
id|PCIBIOS_SUCCESSFUL
suffix:semicolon
)brace
DECL|variable|u3_ht_pci_ops
r_static
r_struct
id|pci_ops
id|u3_ht_pci_ops
op_assign
(brace
id|u3_ht_read_config
comma
id|u3_ht_write_config
)brace
suffix:semicolon
DECL|function|setup_u3_agp
r_static
r_void
id|__init
id|setup_u3_agp
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
)paren
(brace
multiline_comment|/* On G5, we move AGP up to high bus number so we don&squot;t need&n;&t; * to reassign bus numbers for HT. If we ever have P2P bridges&n;&t; * on AGP, we&squot;ll have to move pci_assign_all_busses to the&n;&t; * pci_controller structure so we enable it for AGP and not for&n;&t; * HT childs.&n;&t; * We hard code the address because of the different size of&n;&t; * the reg address cell, we shall fix that by killing struct&n;&t; * reg_property and using some accessor functions instead&n;&t; */
id|hose-&gt;first_busno
op_assign
l_int|0xf0
suffix:semicolon
id|hose-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|hose-&gt;ops
op_assign
op_amp
id|u3_agp_pci_ops
suffix:semicolon
id|hose-&gt;cfg_addr
op_assign
id|ioremap
c_func
(paren
l_int|0xf0000000
op_plus
l_int|0x800000
comma
l_int|0x1000
)paren
suffix:semicolon
id|hose-&gt;cfg_data
op_assign
id|ioremap
c_func
(paren
l_int|0xf0000000
op_plus
l_int|0xc00000
comma
l_int|0x1000
)paren
suffix:semicolon
id|u3_agp
op_assign
id|hose
suffix:semicolon
)brace
DECL|function|setup_u3_ht
r_static
r_void
id|__init
id|setup_u3_ht
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
)paren
(brace
id|hose-&gt;ops
op_assign
op_amp
id|u3_ht_pci_ops
suffix:semicolon
multiline_comment|/* We hard code the address because of the different size of&n;&t; * the reg address cell, we shall fix that by killing struct&n;&t; * reg_property and using some accessor functions instead&n;&t; */
id|hose-&gt;cfg_data
op_assign
(paren
r_volatile
r_int
r_char
op_star
)paren
id|ioremap
c_func
(paren
l_int|0xf2000000
comma
l_int|0x02000000
)paren
suffix:semicolon
id|hose-&gt;first_busno
op_assign
l_int|0
suffix:semicolon
id|hose-&gt;last_busno
op_assign
l_int|0xef
suffix:semicolon
id|u3_ht
op_assign
id|hose
suffix:semicolon
)brace
DECL|function|add_bridge
r_static
r_int
id|__init
id|add_bridge
c_func
(paren
r_struct
id|device_node
op_star
id|dev
)paren
(brace
r_int
id|len
suffix:semicolon
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_char
op_star
id|disp_name
suffix:semicolon
r_int
op_star
id|bus_range
suffix:semicolon
r_int
id|primary
op_assign
l_int|1
suffix:semicolon
r_struct
id|property
op_star
id|of_prop
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;Adding PCI host bridge %s&bslash;n&quot;
comma
id|dev-&gt;full_name
)paren
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;Can&squot;t get bus-range for %s, assume bus 0&bslash;n&quot;
comma
id|dev-&gt;full_name
)paren
suffix:semicolon
)brace
id|hose
op_assign
id|alloc_bootmem
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_controller
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hose
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|pci_setup_pci_controller
c_func
(paren
id|hose
)paren
suffix:semicolon
id|hose-&gt;arch_data
op_assign
id|dev
suffix:semicolon
id|hose-&gt;first_busno
op_assign
id|bus_range
ques
c_cond
id|bus_range
(braket
l_int|0
)braket
suffix:colon
l_int|0
suffix:semicolon
id|hose-&gt;last_busno
op_assign
id|bus_range
ques
c_cond
id|bus_range
(braket
l_int|1
)braket
suffix:colon
l_int|0xff
suffix:semicolon
id|of_prop
op_assign
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
id|hose-&gt;global_number
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|of_prop
)paren
(brace
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
id|hose-&gt;global_number
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
id|hose-&gt;global_number
comma
r_sizeof
(paren
id|hose-&gt;global_number
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
)brace
id|disp_name
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|device_is_compatible
c_func
(paren
id|dev
comma
l_string|&quot;u3-agp&quot;
)paren
)paren
(brace
id|setup_u3_agp
c_func
(paren
id|hose
)paren
suffix:semicolon
id|disp_name
op_assign
l_string|&quot;U3-AGP&quot;
suffix:semicolon
id|primary
op_assign
l_int|0
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|device_is_compatible
c_func
(paren
id|dev
comma
l_string|&quot;u3-ht&quot;
)paren
)paren
(brace
id|setup_u3_ht
c_func
(paren
id|hose
)paren
suffix:semicolon
id|disp_name
op_assign
l_string|&quot;U3-HT&quot;
suffix:semicolon
id|primary
op_assign
l_int|1
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;Found %s PCI host bridge. Firmware bus number: %d-&gt;%d&bslash;n&quot;
comma
id|disp_name
comma
id|hose-&gt;first_busno
comma
id|hose-&gt;last_busno
)paren
suffix:semicolon
multiline_comment|/* Interpret the &quot;ranges&quot; property */
multiline_comment|/* This also maps the I/O region and sets isa_io/mem_base */
id|pci_process_bridge_OF_ranges
c_func
(paren
id|hose
comma
id|dev
)paren
suffix:semicolon
id|pci_setup_phb_io
c_func
(paren
id|hose
comma
id|primary
)paren
suffix:semicolon
multiline_comment|/* Fixup &quot;bus-range&quot; OF property */
id|fixup_bus_range
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|maple_pcibios_fixup
r_void
id|__init
id|maple_pcibios_fixup
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
id|DBG
c_func
(paren
l_string|&quot; -&gt; maple_pcibios_fixup&bslash;n&quot;
)paren
suffix:semicolon
id|for_each_pci_dev
c_func
(paren
id|dev
)paren
id|pci_read_irq_line
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Do the mapping of the IO space */
id|phbs_remap_io
c_func
(paren
)paren
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot; &lt;- maple_pcibios_fixup&bslash;n&quot;
)paren
suffix:semicolon
)brace
DECL|function|maple_fixup_phb_resources
r_static
r_void
id|__init
id|maple_fixup_phb_resources
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
comma
op_star
id|tmp
suffix:semicolon
id|list_for_each_entry_safe
c_func
(paren
id|hose
comma
id|tmp
comma
op_amp
id|hose_list
comma
id|list_node
)paren
(brace
r_int
r_int
id|offset
op_assign
(paren
r_int
r_int
)paren
id|hose-&gt;io_base_virt
op_minus
id|pci_io_base
suffix:semicolon
id|hose-&gt;io_resource.start
op_add_assign
id|offset
suffix:semicolon
id|hose-&gt;io_resource.end
op_add_assign
id|offset
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI Host %d, io start: %lx; io end: %lx&bslash;n&quot;
comma
id|hose-&gt;global_number
comma
id|hose-&gt;io_resource.start
comma
id|hose-&gt;io_resource.end
)paren
suffix:semicolon
)brace
)brace
DECL|function|maple_pci_init
r_void
id|__init
id|maple_pci_init
c_func
(paren
r_void
)paren
(brace
r_struct
id|device_node
op_star
id|np
comma
op_star
id|root
suffix:semicolon
r_struct
id|device_node
op_star
id|ht
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Probe root PCI hosts, that is on U3 the AGP host and the&n;&t; * HyperTransport host. That one is actually &quot;kept&quot; around&n;&t; * and actually added last as it&squot;s resource management relies&n;&t; * on the AGP resources to have been setup first&n;&t; */
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
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;maple_find_bridges: can&squot;t find root of device tree&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_for
c_loop
(paren
id|np
op_assign
l_int|NULL
suffix:semicolon
(paren
id|np
op_assign
id|of_get_next_child
c_func
(paren
id|root
comma
id|np
)paren
)paren
op_ne
l_int|NULL
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
id|np-&gt;name
op_eq
l_int|NULL
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|np-&gt;name
comma
l_string|&quot;pci&quot;
)paren
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|add_bridge
c_func
(paren
id|np
)paren
op_eq
l_int|0
)paren
id|of_node_get
c_func
(paren
id|np
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strcmp
c_func
(paren
id|np-&gt;name
comma
l_string|&quot;ht&quot;
)paren
op_eq
l_int|0
)paren
(brace
id|of_node_get
c_func
(paren
id|np
)paren
suffix:semicolon
id|ht
op_assign
id|np
suffix:semicolon
)brace
)brace
id|of_node_put
c_func
(paren
id|root
)paren
suffix:semicolon
multiline_comment|/* Now setup the HyperTransport host if we found any&n;&t; */
r_if
c_cond
(paren
id|ht
op_logical_and
id|add_bridge
c_func
(paren
id|ht
)paren
op_ne
l_int|0
)paren
id|of_node_put
c_func
(paren
id|ht
)paren
suffix:semicolon
multiline_comment|/* Fixup the IO resources on our host bridges as the common code&n;&t; * does it only for childs of the host bridges&n;&t; */
id|maple_fixup_phb_resources
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Setup the linkage between OF nodes and PHBs */
id|pci_devs_phb_init
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Fixup the PCI&lt;-&gt;OF mapping for U3 AGP due to bus renumbering. We&n;&t; * assume there is no P2P bridge on the AGP bus, which should be a&n;&t; * safe assumptions hopefully.&n;&t; */
r_if
c_cond
(paren
id|u3_agp
)paren
(brace
r_struct
id|device_node
op_star
id|np
op_assign
id|u3_agp-&gt;arch_data
suffix:semicolon
id|np-&gt;busno
op_assign
l_int|0xf0
suffix:semicolon
r_for
c_loop
(paren
id|np
op_assign
id|np-&gt;child
suffix:semicolon
id|np
suffix:semicolon
id|np
op_assign
id|np-&gt;sibling
)paren
id|np-&gt;busno
op_assign
l_int|0xf0
suffix:semicolon
)brace
multiline_comment|/* Tell pci.c to use the common resource allocation mecanism */
id|pci_probe_only
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Allow all IO */
id|io_page_mask
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|maple_pci_get_legacy_ide_irq
r_int
id|maple_pci_get_legacy_ide_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_int
id|channel
)paren
(brace
r_struct
id|device_node
op_star
id|np
suffix:semicolon
r_int
id|irq
op_assign
id|channel
ques
c_cond
l_int|15
suffix:colon
l_int|14
suffix:semicolon
r_if
c_cond
(paren
id|pdev-&gt;vendor
op_ne
id|PCI_VENDOR_ID_AMD
op_logical_or
id|pdev-&gt;device
op_ne
id|PCI_DEVICE_ID_AMD_8111_IDE
)paren
r_return
id|irq
suffix:semicolon
id|np
op_assign
id|pci_device_to_OF_node
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|np
op_eq
l_int|NULL
)paren
r_return
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|np-&gt;n_intrs
OL
l_int|2
)paren
r_return
id|irq
suffix:semicolon
r_return
id|np-&gt;intrs
(braket
id|channel
op_amp
l_int|0x1
)braket
dot
id|line
suffix:semicolon
)brace
multiline_comment|/* XXX: To remove once all firmwares are ok */
DECL|function|fixup_maple_ide
r_static
r_void
id|fixup_maple_ide
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
macro_line|#if 0 /* Enable this to enable IDE port 0 */
(brace
id|u8
id|v
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
l_int|0x40
comma
op_amp
id|v
)paren
suffix:semicolon
id|v
op_or_assign
l_int|2
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
l_int|0x40
comma
id|v
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#if 0 /* fix bus master base */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x20
comma
l_int|0xcc01
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;old ide resource: %lx -&gt; %lx &bslash;n&quot;
comma
id|dev-&gt;resource
(braket
l_int|4
)braket
dot
id|start
comma
id|dev-&gt;resource
(braket
l_int|4
)braket
dot
id|end
)paren
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|4
)braket
dot
id|start
op_assign
l_int|0xcc00
suffix:semicolon
id|dev-&gt;resource
(braket
l_int|4
)braket
dot
id|end
op_assign
l_int|0xcc10
suffix:semicolon
macro_line|#endif
macro_line|#if 1 /* Enable this to fixup IDE sense/polarity of irqs in IO-APICs */
(brace
r_struct
id|pci_dev
op_star
id|apicdev
suffix:semicolon
id|u32
id|v
suffix:semicolon
id|apicdev
op_assign
id|pci_get_slot
(paren
id|dev-&gt;bus
comma
id|PCI_DEVFN
c_func
(paren
l_int|5
comma
l_int|0
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|apicdev
op_eq
l_int|NULL
)paren
id|printk
c_func
(paren
l_string|&quot;IDE Fixup IRQ: Can&squot;t find IO-APIC !&bslash;n&quot;
)paren
suffix:semicolon
r_else
(brace
id|pci_write_config_byte
c_func
(paren
id|apicdev
comma
l_int|0xf2
comma
l_int|0x10
op_plus
l_int|2
op_star
l_int|14
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|apicdev
comma
l_int|0xf4
comma
op_amp
id|v
)paren
suffix:semicolon
id|v
op_and_assign
op_complement
l_int|0x00000022
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|apicdev
comma
l_int|0xf4
comma
id|v
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|apicdev
comma
l_int|0xf2
comma
l_int|0x10
op_plus
l_int|2
op_star
l_int|15
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|apicdev
comma
l_int|0xf4
comma
op_amp
id|v
)paren
suffix:semicolon
id|v
op_and_assign
op_complement
l_int|0x00000022
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|apicdev
comma
l_int|0xf4
comma
id|v
)paren
suffix:semicolon
id|pci_dev_put
c_func
(paren
id|apicdev
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
id|DECLARE_PCI_FIXUP_HEADER
c_func
(paren
id|PCI_VENDOR_ID_AMD
comma
id|PCI_DEVICE_ID_AMD_8111_IDE
comma
id|fixup_maple_ide
)paren
suffix:semicolon
eof
