multiline_comment|/*&n; *  acpi_drivers.h  ($Revision: 31 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#ifndef __ACPI_DRIVERS_H__
DECL|macro|__ACPI_DRIVERS_H__
mdefine_line|#define __ACPI_DRIVERS_H__
macro_line|#include &lt;linux/acpi.h&gt;
macro_line|#include &lt;acpi/acpi_bus.h&gt;
DECL|macro|ACPI_MAX_STRING
mdefine_line|#define ACPI_MAX_STRING&t;&t;&t;80
DECL|macro|ACPI_BUS_COMPONENT
mdefine_line|#define ACPI_BUS_COMPONENT&t;&t;0x00010000
DECL|macro|ACPI_SYSTEM_COMPONENT
mdefine_line|#define ACPI_SYSTEM_COMPONENT&t;&t;0x02000000
multiline_comment|/* _HID definitions */
DECL|macro|ACPI_POWER_HID
mdefine_line|#define ACPI_POWER_HID&t;&t;&t;&quot;ACPI_PWR&quot;
DECL|macro|ACPI_PROCESSOR_HID
mdefine_line|#define ACPI_PROCESSOR_HID&t;&t;&quot;ACPI_CPU&quot;
DECL|macro|ACPI_SYSTEM_HID
mdefine_line|#define ACPI_SYSTEM_HID&t;&t;&t;&quot;ACPI_SYS&quot;
DECL|macro|ACPI_THERMAL_HID
mdefine_line|#define ACPI_THERMAL_HID&t;&t;&quot;ACPI_THM&quot;
DECL|macro|ACPI_BUTTON_HID_POWERF
mdefine_line|#define ACPI_BUTTON_HID_POWERF&t;&t;&quot;ACPI_FPB&quot;
DECL|macro|ACPI_BUTTON_HID_SLEEPF
mdefine_line|#define ACPI_BUTTON_HID_SLEEPF&t;&t;&quot;ACPI_FSB&quot;
multiline_comment|/* --------------------------------------------------------------------------&n;                                       PCI&n;   -------------------------------------------------------------------------- */
macro_line|#ifdef CONFIG_ACPI_PCI
DECL|macro|ACPI_PCI_COMPONENT
mdefine_line|#define ACPI_PCI_COMPONENT&t;&t;0x00400000
multiline_comment|/* ACPI PCI Root Bridge (pci_root.c) */
r_void
id|acpi_pci_get_translations
(paren
r_struct
id|acpi_pci_id
op_star
id|id
comma
id|u64
op_star
id|mem_tra
comma
id|u64
op_star
id|io_tra
)paren
suffix:semicolon
multiline_comment|/* ACPI PCI Interrupt Link (pci_link.c) */
r_int
id|acpi_pci_link_check
(paren
r_void
)paren
suffix:semicolon
r_int
id|acpi_pci_link_get_irq
(paren
id|acpi_handle
id|handle
comma
r_int
id|index
comma
r_int
op_star
id|edge_level
comma
r_int
op_star
id|active_high_low
)paren
suffix:semicolon
multiline_comment|/* ACPI PCI Interrupt Routing (pci_irq.c) */
r_int
id|acpi_pci_irq_add_prt
(paren
id|acpi_handle
id|handle
comma
r_int
id|segment
comma
r_int
id|bus
)paren
suffix:semicolon
multiline_comment|/* ACPI PCI Device Binding (pci_bind.c) */
r_struct
id|pci_bus
suffix:semicolon
r_int
id|acpi_pci_bind
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_int
id|acpi_pci_bind_root
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_struct
id|acpi_pci_id
op_star
id|id
comma
r_struct
id|pci_bus
op_star
id|bus
)paren
suffix:semicolon
multiline_comment|/* Arch-defined function to add a bus to the system */
r_struct
id|pci_bus
op_star
id|pci_acpi_scan_root
c_func
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|domain
comma
r_int
id|bus
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_PCI*/
multiline_comment|/* --------------------------------------------------------------------------&n;                                  Power Resource&n;   -------------------------------------------------------------------------- */
macro_line|#ifdef CONFIG_ACPI_POWER
r_int
id|acpi_power_get_inferred_state
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_int
id|acpi_power_transition
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|state
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* --------------------------------------------------------------------------&n;                                  Embedded Controller&n;   -------------------------------------------------------------------------- */
macro_line|#ifdef CONFIG_ACPI_EC
r_int
id|acpi_ec_ecdt_probe
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* --------------------------------------------------------------------------&n;                                    Processor&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_PROCESSOR_LIMIT_NONE
mdefine_line|#define ACPI_PROCESSOR_LIMIT_NONE&t;0x00
DECL|macro|ACPI_PROCESSOR_LIMIT_INCREMENT
mdefine_line|#define ACPI_PROCESSOR_LIMIT_INCREMENT&t;0x01
DECL|macro|ACPI_PROCESSOR_LIMIT_DECREMENT
mdefine_line|#define ACPI_PROCESSOR_LIMIT_DECREMENT&t;0x02
r_int
id|acpi_processor_set_thermal_limit
c_func
(paren
id|acpi_handle
id|handle
comma
r_int
id|type
)paren
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                                Debug Support&n;   -------------------------------------------------------------------------- */
DECL|macro|ACPI_DEBUG_RESTORE
mdefine_line|#define ACPI_DEBUG_RESTORE&t;0
DECL|macro|ACPI_DEBUG_LOW
mdefine_line|#define ACPI_DEBUG_LOW&t;&t;1
DECL|macro|ACPI_DEBUG_MEDIUM
mdefine_line|#define ACPI_DEBUG_MEDIUM&t;2
DECL|macro|ACPI_DEBUG_HIGH
mdefine_line|#define ACPI_DEBUG_HIGH&t;&t;3
DECL|macro|ACPI_DEBUG_DRIVERS
mdefine_line|#define ACPI_DEBUG_DRIVERS&t;4
r_extern
id|u32
id|acpi_dbg_level
suffix:semicolon
r_extern
id|u32
id|acpi_dbg_layer
suffix:semicolon
r_static
r_inline
r_void
DECL|function|acpi_set_debug
id|acpi_set_debug
(paren
id|u32
id|flag
)paren
(brace
r_static
id|u32
id|layer_save
suffix:semicolon
r_static
id|u32
id|level_save
suffix:semicolon
r_switch
c_cond
(paren
id|flag
)paren
(brace
r_case
id|ACPI_DEBUG_RESTORE
suffix:colon
id|acpi_dbg_layer
op_assign
id|layer_save
suffix:semicolon
id|acpi_dbg_level
op_assign
id|level_save
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DEBUG_LOW
suffix:colon
r_case
id|ACPI_DEBUG_MEDIUM
suffix:colon
r_case
id|ACPI_DEBUG_HIGH
suffix:colon
r_case
id|ACPI_DEBUG_DRIVERS
suffix:colon
id|layer_save
op_assign
id|acpi_dbg_layer
suffix:semicolon
id|level_save
op_assign
id|acpi_dbg_level
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|flag
)paren
(brace
r_case
id|ACPI_DEBUG_LOW
suffix:colon
id|acpi_dbg_layer
op_assign
id|ACPI_COMPONENT_DEFAULT
op_or
id|ACPI_ALL_DRIVERS
suffix:semicolon
id|acpi_dbg_level
op_assign
id|ACPI_DEBUG_DEFAULT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DEBUG_MEDIUM
suffix:colon
id|acpi_dbg_layer
op_assign
id|ACPI_COMPONENT_DEFAULT
op_or
id|ACPI_ALL_DRIVERS
suffix:semicolon
id|acpi_dbg_level
op_assign
id|ACPI_LV_FUNCTIONS
op_or
id|ACPI_LV_ALL_EXCEPTIONS
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DEBUG_HIGH
suffix:colon
id|acpi_dbg_layer
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
id|acpi_dbg_level
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DEBUG_DRIVERS
suffix:colon
id|acpi_dbg_layer
op_assign
id|ACPI_ALL_DRIVERS
suffix:semicolon
id|acpi_dbg_level
op_assign
l_int|0xFFFFFFFF
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
macro_line|#endif /*__ACPI_DRIVERS_H__*/
eof
