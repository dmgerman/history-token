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
r_void
)paren
suffix:semicolon
r_extern
r_struct
id|pci_controller
op_star
id|pci_alloc_phb_dynamic
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pci_setup_phb_io
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
comma
r_int
id|primary
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
r_void
id|pci_setup_phb_io_dynamic
c_func
(paren
r_struct
id|pci_controller
op_star
id|hose
)paren
suffix:semicolon
r_extern
r_struct
id|list_head
id|hose_list
suffix:semicolon
r_extern
r_int
id|global_phb_number
suffix:semicolon
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
r_struct
id|pci_dev
op_star
id|ppc64_isabridge_dev
suffix:semicolon
multiline_comment|/* may be NULL if no ISA bus */
multiline_comment|/* PCI device_node operations */
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
r_void
op_star
id|data
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
id|pci_devs_phb_init_dynamic
c_func
(paren
r_struct
id|pci_controller
op_star
id|phb
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
DECL|macro|PCI_GET_PHB_PTR
mdefine_line|#define PCI_GET_PHB_PTR(dev)    (((struct device_node *)(dev)-&gt;sysdata)-&gt;phb)
multiline_comment|/* PCI address cache management routines */
r_void
id|pci_addr_cache_insert_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|pci_addr_cache_remove_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* From pSeries_pci.h */
r_void
id|init_pci_config_tokens
(paren
r_void
)paren
suffix:semicolon
r_int
r_int
id|get_phb_buid
(paren
r_struct
id|device_node
op_star
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pci_probe_only
suffix:semicolon
r_extern
r_int
r_int
id|pci_assign_all_buses
suffix:semicolon
r_extern
r_int
id|pci_read_irq_line
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci_dev
)paren
suffix:semicolon
macro_line|#endif /* __PPC_KERNEL_PCI_H__ */
eof
