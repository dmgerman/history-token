multiline_comment|/*&n; * File&t;&t;pci-acpi.h&n; *&n; * Copyright (C) 2004 Intel&n; * Copyright (C) Tom Long Nguyen (tom.l.nguyen@intel.com)&n; */
macro_line|#ifndef _PCI_ACPI_H_
DECL|macro|_PCI_ACPI_H_
mdefine_line|#define _PCI_ACPI_H_
DECL|macro|OSC_QUERY_TYPE
mdefine_line|#define OSC_QUERY_TYPE&t;&t;&t;0
DECL|macro|OSC_SUPPORT_TYPE
mdefine_line|#define OSC_SUPPORT_TYPE &t;&t;1
DECL|macro|OSC_CONTROL_TYPE
mdefine_line|#define OSC_CONTROL_TYPE&t;&t;2
DECL|macro|OSC_SUPPORT_MASKS
mdefine_line|#define OSC_SUPPORT_MASKS&t;&t;0x1f
multiline_comment|/*&n; * _OSC DW0 Definition &n; */
DECL|macro|OSC_QUERY_ENABLE
mdefine_line|#define OSC_QUERY_ENABLE&t;&t;1
DECL|macro|OSC_REQUEST_ERROR
mdefine_line|#define OSC_REQUEST_ERROR&t;&t;2
DECL|macro|OSC_INVALID_UUID_ERROR
mdefine_line|#define OSC_INVALID_UUID_ERROR&t;&t;4
DECL|macro|OSC_INVALID_REVISION_ERROR
mdefine_line|#define OSC_INVALID_REVISION_ERROR&t;8
DECL|macro|OSC_CAPABILITIES_MASK_ERROR
mdefine_line|#define OSC_CAPABILITIES_MASK_ERROR&t;16
multiline_comment|/*&n; * _OSC DW1 Definition (OS Support Fields)&n; */
DECL|macro|OSC_EXT_PCI_CONFIG_SUPPORT
mdefine_line|#define OSC_EXT_PCI_CONFIG_SUPPORT&t;&t;1
DECL|macro|OSC_ACTIVE_STATE_PWR_SUPPORT
mdefine_line|#define OSC_ACTIVE_STATE_PWR_SUPPORT &t;&t;2
DECL|macro|OSC_CLOCK_PWR_CAPABILITY_SUPPORT
mdefine_line|#define OSC_CLOCK_PWR_CAPABILITY_SUPPORT&t;4
DECL|macro|OSC_PCI_SEGMENT_GROUPS_SUPPORT
mdefine_line|#define OSC_PCI_SEGMENT_GROUPS_SUPPORT&t;&t;8
DECL|macro|OSC_MSI_SUPPORT
mdefine_line|#define OSC_MSI_SUPPORT&t;&t;&t;&t;16
multiline_comment|/*&n; * _OSC DW1 Definition (OS Control Fields)&n; */
DECL|macro|OSC_PCI_EXPRESS_NATIVE_HP_CONTROL
mdefine_line|#define OSC_PCI_EXPRESS_NATIVE_HP_CONTROL&t;1
DECL|macro|OSC_SHPC_NATIVE_HP_CONTROL
mdefine_line|#define OSC_SHPC_NATIVE_HP_CONTROL &t;&t;2
DECL|macro|OSC_PCI_EXPRESS_PME_CONTROL
mdefine_line|#define OSC_PCI_EXPRESS_PME_CONTROL&t;&t;4
DECL|macro|OSC_PCI_EXPRESS_AER_CONTROL
mdefine_line|#define OSC_PCI_EXPRESS_AER_CONTROL&t;&t;8
DECL|macro|OSC_PCI_EXPRESS_CAP_STRUCTURE_CONTROL
mdefine_line|#define OSC_PCI_EXPRESS_CAP_STRUCTURE_CONTROL&t;16
DECL|macro|OSC_CONTROL_MASKS
mdefine_line|#define OSC_CONTROL_MASKS &t;(OSC_PCI_EXPRESS_NATIVE_HP_CONTROL | &t;&bslash;&n;&t;&t;&t;&t;OSC_SHPC_NATIVE_HP_CONTROL | &t;&t;&bslash;&n;&t;&t;&t;&t;OSC_PCI_EXPRESS_PME_CONTROL |&t;&t;&bslash;&n;&t;&t;&t;&t;OSC_PCI_EXPRESS_AER_CONTROL |&t;&t;&bslash;&n;&t;&t;&t;&t;OSC_PCI_EXPRESS_CAP_STRUCTURE_CONTROL)
macro_line|#ifdef CONFIG_ACPI
r_extern
id|acpi_status
id|pci_osc_control_set
c_func
(paren
id|u32
id|flags
)paren
suffix:semicolon
r_extern
id|acpi_status
id|pci_osc_support_set
c_func
(paren
id|u32
id|flags
)paren
suffix:semicolon
macro_line|#else
macro_line|#if !defined(acpi_status)
DECL|typedef|acpi_status
r_typedef
id|u32
id|acpi_status
suffix:semicolon
DECL|macro|AE_ERROR
mdefine_line|#define AE_ERROR      &t;(acpi_status) (0x0001)
macro_line|#endif    
DECL|function|pci_osc_control_set
r_static
r_inline
id|acpi_status
id|pci_osc_control_set
c_func
(paren
id|u32
id|flags
)paren
(brace
r_return
id|AE_ERROR
suffix:semicolon
)brace
DECL|function|pci_osc_support_set
r_static
r_inline
id|acpi_status
id|pci_osc_support_set
c_func
(paren
id|u32
id|flags
)paren
(brace
r_return
id|AE_ERROR
suffix:semicolon
)brace
macro_line|#endif
macro_line|#endif&t;/* _PCI_ACPI_H_ */
eof
