multiline_comment|/*&n; * File:&t;pcieport_if.h&n; * Purpose:&t;PCI Express Port Bus Driver&squot;s IF Data Structure&n; *&n; * Copyright (C) 2004 Intel&n; * Copyright (C) Tom Long Nguyen (tom.l.nguyen@intel.com)&n; */
macro_line|#ifndef _PCIEPORT_IF_H_
DECL|macro|_PCIEPORT_IF_H_
mdefine_line|#define _PCIEPORT_IF_H_
multiline_comment|/* Port Type */
DECL|macro|PCIE_RC_PORT
mdefine_line|#define PCIE_RC_PORT&t;&t;&t;4&t;/* Root port of RC */
DECL|macro|PCIE_SW_UPSTREAM_PORT
mdefine_line|#define PCIE_SW_UPSTREAM_PORT&t;&t;5&t;/* Upstream port of Switch */
DECL|macro|PCIE_SW_DOWNSTREAM_PORT
mdefine_line|#define PCIE_SW_DOWNSTREAM_PORT&t;&t;6&t;/* Downstream port of Switch */
DECL|macro|PCIE_ANY_PORT
mdefine_line|#define PCIE_ANY_PORT&t;&t;&t;7
multiline_comment|/* Service Type */
DECL|macro|PCIE_PORT_SERVICE_PME
mdefine_line|#define PCIE_PORT_SERVICE_PME&t;&t;1&t;/* Power Management Event */
DECL|macro|PCIE_PORT_SERVICE_AER
mdefine_line|#define PCIE_PORT_SERVICE_AER&t;&t;2&t;/* Advanced Error Reporting */
DECL|macro|PCIE_PORT_SERVICE_HP
mdefine_line|#define PCIE_PORT_SERVICE_HP&t;&t;4&t;/* Native Hotplug */
DECL|macro|PCIE_PORT_SERVICE_VC
mdefine_line|#define PCIE_PORT_SERVICE_VC&t;&t;8&t;/* Virtual Channel */
multiline_comment|/* Root/Upstream/Downstream Port&squot;s Interrupt Mode */
DECL|macro|PCIE_PORT_INTx_MODE
mdefine_line|#define PCIE_PORT_INTx_MODE&t;&t;0
DECL|macro|PCIE_PORT_MSI_MODE
mdefine_line|#define PCIE_PORT_MSI_MODE&t;&t;1
DECL|macro|PCIE_PORT_MSIX_MODE
mdefine_line|#define PCIE_PORT_MSIX_MODE&t;&t;2
DECL|struct|pcie_port_service_id
r_struct
id|pcie_port_service_id
(brace
DECL|member|vendor
DECL|member|device
id|__u32
id|vendor
comma
id|device
suffix:semicolon
multiline_comment|/* Vendor and device ID or PCI_ANY_ID*/
DECL|member|subvendor
DECL|member|subdevice
id|__u32
id|subvendor
comma
id|subdevice
suffix:semicolon
multiline_comment|/* Subsystem ID&squot;s or PCI_ANY_ID */
DECL|member|class
DECL|member|class_mask
id|__u32
r_class
comma
id|class_mask
suffix:semicolon
multiline_comment|/* (class,subclass,prog-if) triplet */
DECL|member|port_type
DECL|member|service_type
id|__u32
id|port_type
comma
id|service_type
suffix:semicolon
multiline_comment|/* Port Entity */
DECL|member|driver_data
id|kernel_ulong_t
id|driver_data
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|pcie_device
r_struct
id|pcie_device
(brace
DECL|member|irq
r_int
id|irq
suffix:semicolon
multiline_comment|/* Service IRQ/MSI/MSI-X Vector */
DECL|member|interrupt_mode
r_int
id|interrupt_mode
suffix:semicolon
multiline_comment|/* [0:INTx | 1:MSI | 2:MSI-X] */
DECL|member|id
r_struct
id|pcie_port_service_id
id|id
suffix:semicolon
multiline_comment|/* Service ID */
DECL|member|port
r_struct
id|pci_dev
op_star
id|port
suffix:semicolon
multiline_comment|/* Root/Upstream/Downstream Port */
DECL|member|priv_data
r_void
op_star
id|priv_data
suffix:semicolon
multiline_comment|/* Service Private Data */
DECL|member|device
r_struct
id|device
id|device
suffix:semicolon
multiline_comment|/* Generic Device Interface */
)brace
suffix:semicolon
DECL|macro|to_pcie_device
mdefine_line|#define to_pcie_device(d) container_of(d, struct pcie_device, device)
DECL|function|set_service_data
r_static
r_inline
r_void
id|set_service_data
c_func
(paren
r_struct
id|pcie_device
op_star
id|dev
comma
r_void
op_star
id|data
)paren
(brace
id|dev-&gt;priv_data
op_assign
id|data
suffix:semicolon
)brace
DECL|function|get_service_data
r_static
r_inline
r_void
op_star
id|get_service_data
c_func
(paren
r_struct
id|pcie_device
op_star
id|dev
)paren
(brace
r_return
id|dev-&gt;priv_data
suffix:semicolon
)brace
DECL|struct|pcie_port_service_driver
r_struct
id|pcie_port_service_driver
(brace
DECL|member|name
r_const
r_char
op_star
id|name
suffix:semicolon
DECL|member|probe
r_int
(paren
op_star
id|probe
)paren
(paren
r_struct
id|pcie_device
op_star
id|dev
comma
r_const
r_struct
id|pcie_port_service_id
op_star
id|id
)paren
suffix:semicolon
DECL|member|remove
r_void
(paren
op_star
id|remove
)paren
(paren
r_struct
id|pcie_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|suspend
r_int
(paren
op_star
id|suspend
)paren
(paren
r_struct
id|pcie_device
op_star
id|dev
comma
id|u32
id|state
)paren
suffix:semicolon
DECL|member|resume
r_int
(paren
op_star
id|resume
)paren
(paren
r_struct
id|pcie_device
op_star
id|dev
)paren
suffix:semicolon
DECL|member|id_table
r_const
r_struct
id|pcie_port_service_id
op_star
id|id_table
suffix:semicolon
DECL|member|driver
r_struct
id|device_driver
id|driver
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|to_service_driver
mdefine_line|#define to_service_driver(d) &bslash;&n;&t;container_of(d, struct pcie_port_service_driver, driver)
r_extern
r_int
id|pcie_port_service_register
c_func
(paren
r_struct
id|pcie_port_service_driver
op_star
r_new
)paren
suffix:semicolon
r_extern
r_void
id|pcie_port_service_unregister
c_func
(paren
r_struct
id|pcie_port_service_driver
op_star
r_new
)paren
suffix:semicolon
macro_line|#endif /* _PCIEPORT_IF_H_ */
eof
