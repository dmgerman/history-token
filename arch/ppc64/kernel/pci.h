multiline_comment|/*&n; * c 2001 PPC 64 Team, IBM Corp&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#ifndef __PPC_KERNEL_PCI_H__
DECL|macro|__PPC_KERNEL_PCI_H__
mdefine_line|#define __PPC_KERNEL_PCI_H__
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
r_extern
r_int
r_int
id|isa_io_base
suffix:semicolon
r_extern
r_struct
id|pci_controller
op_star
id|pci_alloc_pci_controller
c_func
(paren
r_enum
id|phb_types
id|controller_type
)paren
suffix:semicolon
r_extern
r_struct
id|pci_controller
op_star
id|pci_find_hose_for_OF_device
c_func
(paren
r_struct
id|device_node
op_star
id|node
)paren
suffix:semicolon
r_extern
r_struct
id|pci_controller
op_star
id|hose_head
suffix:semicolon
r_extern
r_struct
id|pci_controller
op_star
op_star
id|hose_tail
suffix:semicolon
multiline_comment|/* PHB&squot;s are also in a table. */
DECL|macro|PCI_MAX_PHB
mdefine_line|#define PCI_MAX_PHB 64
r_extern
r_int
id|global_phb_number
suffix:semicolon
r_extern
r_struct
id|pci_controller
op_star
id|phbtab
(braket
)braket
suffix:semicolon
multiline_comment|/*******************************************************************&n; * Platform functions that are brand specific implementation. &n; *******************************************************************/
r_extern
r_int
r_int
id|find_and_init_phbs
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|ppc64_pcibios_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|pci_dev
op_star
id|ppc64_isabridge_dev
suffix:semicolon
multiline_comment|/* may be NULL if no ISA bus */
multiline_comment|/*******************************************************************&n; * PCI device_node operations&n; *******************************************************************/
r_struct
id|device_node
suffix:semicolon
DECL|typedef|traverse_func
r_typedef
r_void
op_star
(paren
op_star
id|traverse_func
)paren
(paren
r_struct
id|device_node
op_star
id|me
comma
r_void
op_star
id|data
)paren
suffix:semicolon
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
id|traverse_func
id|post
comma
r_void
op_star
id|data
)paren
suffix:semicolon
r_void
op_star
id|traverse_all_pci_devices
c_func
(paren
id|traverse_func
id|pre
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|pci_find_dev_by_addr
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_void
id|pci_devs_phb_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pci_fix_bus_sysdata
c_func
(paren
r_void
)paren
suffix:semicolon
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
suffix:semicolon
r_void
id|iSeries_pcibios_init_early
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pSeries_pcibios_init_early
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|pSeries_pcibios_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*******************************************************************&n; * Helper macros for extracting data from pci structures.  &n; *   PCI_GET_PHB_PTR(struct pci_dev*)    returns the Phb pointer.&n; *   PCI_GET_PHB_NUMBER(struct pci_dev*) returns the Phb number.&n; *   PCI_GET_BUS_NUMBER(struct pci_dev*) returns the bus number.&n; *******************************************************************/
DECL|macro|PCI_GET_PHB_PTR
mdefine_line|#define PCI_GET_PHB_PTR(dev)    (((struct device_node *)(dev)-&gt;sysdata)-&gt;phb)
DECL|macro|PCI_GET_PHB_NUMBER
mdefine_line|#define PCI_GET_PHB_NUMBER(dev) (((dev)-&gt;bus-&gt;number&amp;0x00FFFF00)&gt;&gt;8)
DECL|macro|PCI_GET_BUS_NUMBER
mdefine_line|#define PCI_GET_BUS_NUMBER(dev) ((dev)-&gt;bus-&gt;number&amp;0x0000FF)
multiline_comment|/*******************************************************************&n; * Debugging  Routines.&n; *******************************************************************/
r_extern
r_void
id|dumpResources
c_func
(paren
r_struct
id|resource
op_star
id|Resource
)paren
suffix:semicolon
r_extern
r_void
id|dumpPci_Controller
c_func
(paren
r_struct
id|pci_controller
op_star
id|phb
)paren
suffix:semicolon
r_extern
r_void
id|dumpPci_Bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|Pci_Bus
)paren
suffix:semicolon
r_extern
r_void
id|dumpPci_Dev
c_func
(paren
r_struct
id|pci_dev
op_star
id|Pci_Dev
)paren
suffix:semicolon
macro_line|#endif /* __PPC_KERNEL_PCI_H__ */
eof
