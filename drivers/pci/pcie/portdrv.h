multiline_comment|/*&n; * File:&t;portdrv.h&n; * Purpose:&t;PCI Express Port Bus Driver&squot;s Internal Data Structures&n; *&n; * Copyright (C) 2004 Intel&n; * Copyright (C) Tom Long Nguyen (tom.l.nguyen@intel.com)&n; */
macro_line|#ifndef _PORTDRV_H_
DECL|macro|_PORTDRV_H_
mdefine_line|#define _PORTDRV_H_
macro_line|#if !defined(PCI_CAP_ID_PME)
DECL|macro|PCI_CAP_ID_PME
mdefine_line|#define PCI_CAP_ID_PME&t;&t;&t;1
macro_line|#endif
macro_line|#if !defined(PCI_CAP_ID_EXP)
DECL|macro|PCI_CAP_ID_EXP
mdefine_line|#define PCI_CAP_ID_EXP&t;&t;&t;0x10
macro_line|#endif
DECL|macro|PORT_TYPE_MASK
mdefine_line|#define PORT_TYPE_MASK&t;&t;&t;0xf
DECL|macro|PORT_TO_SLOT_MASK
mdefine_line|#define PORT_TO_SLOT_MASK&t;&t;0x100
DECL|macro|SLOT_HP_CAPABLE_MASK
mdefine_line|#define SLOT_HP_CAPABLE_MASK&t;&t;0x40
DECL|macro|PCIE_CAPABILITIES_REG
mdefine_line|#define PCIE_CAPABILITIES_REG&t;&t;0x2
DECL|macro|PCIE_SLOT_CAPABILITIES_REG
mdefine_line|#define PCIE_SLOT_CAPABILITIES_REG&t;0x14
DECL|macro|PCIE_PORT_DEVICE_MAXSERVICES
mdefine_line|#define PCIE_PORT_DEVICE_MAXSERVICES&t;4
DECL|macro|PCI_CFG_SPACE_SIZE
mdefine_line|#define PCI_CFG_SPACE_SIZE&t;&t;256
DECL|macro|get_descriptor_id
mdefine_line|#define get_descriptor_id(type, service) (((type - 4) &lt;&lt; 4) | service)
r_extern
r_struct
id|bus_type
id|pcie_port_bus_type
suffix:semicolon
r_extern
r_int
id|pcie_port_device_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_int
id|pcie_port_device_register
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PM
r_extern
r_int
id|pcie_port_device_suspend
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u32
id|state
)paren
suffix:semicolon
r_extern
r_int
id|pcie_port_device_resume
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
macro_line|#endif
r_extern
r_void
id|pcie_port_device_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_extern
r_void
id|pcie_port_bus_register
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|pcie_port_bus_unregister
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* _PORTDRV_H_ */
eof
