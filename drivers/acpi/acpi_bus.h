multiline_comment|/*&n; *  acpi_bus.h - ACPI Bus Driver ($Revision: 17 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#ifndef __ACPI_BUS_H__
DECL|macro|__ACPI_BUS_H__
mdefine_line|#define __ACPI_BUS_H__
macro_line|#include &lt;linux/version.h&gt;
macro_line|#if (LINUX_VERSION_CODE &gt;= KERNEL_VERSION(2,5,4))
macro_line|#include &lt;linux/device.h&gt;
DECL|macro|CONFIG_LDM
mdefine_line|#define CONFIG_LDM
macro_line|#endif
macro_line|#include &quot;include/acpi.h&quot;
multiline_comment|/* TBD: Make dynamic */
DECL|macro|ACPI_MAX_HANDLES
mdefine_line|#define ACPI_MAX_HANDLES&t;10
DECL|struct|acpi_handle_list
r_struct
id|acpi_handle_list
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|handles
id|acpi_handle
id|handles
(braket
id|ACPI_MAX_HANDLES
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* acpi_utils.h */
id|acpi_status
id|acpi_extract_package
(paren
id|acpi_object
op_star
comma
id|acpi_buffer
op_star
comma
id|acpi_buffer
op_star
)paren
suffix:semicolon
id|acpi_status
id|acpi_evaluate
(paren
id|acpi_handle
comma
id|acpi_string
comma
id|acpi_object_list
op_star
comma
id|acpi_buffer
op_star
)paren
suffix:semicolon
id|acpi_status
id|acpi_evaluate_integer
(paren
id|acpi_handle
comma
id|acpi_string
comma
id|acpi_object_list
op_star
comma
r_int
r_int
op_star
)paren
suffix:semicolon
id|acpi_status
id|acpi_evaluate_reference
(paren
id|acpi_handle
comma
id|acpi_string
comma
id|acpi_object_list
op_star
comma
r_struct
id|acpi_handle_list
op_star
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_ACPI_BUS
macro_line|#include &lt;linux/proc_fs.h&gt;
DECL|macro|ACPI_BUS_FILE_ROOT
mdefine_line|#define ACPI_BUS_FILE_ROOT&t;&quot;acpi&quot;
r_extern
r_struct
id|proc_dir_entry
op_star
id|acpi_root_dir
suffix:semicolon
r_extern
id|FADT_DESCRIPTOR
id|acpi_fadt
suffix:semicolon
DECL|enum|acpi_bus_removal_type
r_enum
id|acpi_bus_removal_type
(brace
DECL|enumerator|ACPI_BUS_REMOVAL_NORMAL
id|ACPI_BUS_REMOVAL_NORMAL
op_assign
l_int|0
comma
DECL|enumerator|ACPI_BUS_REMOVAL_EJECT
id|ACPI_BUS_REMOVAL_EJECT
comma
DECL|enumerator|ACPI_BUS_REMOVAL_SUPRISE
id|ACPI_BUS_REMOVAL_SUPRISE
comma
DECL|enumerator|ACPI_BUS_REMOVAL_TYPE_COUNT
id|ACPI_BUS_REMOVAL_TYPE_COUNT
)brace
suffix:semicolon
DECL|enum|acpi_bus_device_type
r_enum
id|acpi_bus_device_type
(brace
DECL|enumerator|ACPI_BUS_TYPE_DEVICE
id|ACPI_BUS_TYPE_DEVICE
op_assign
l_int|0
comma
DECL|enumerator|ACPI_BUS_TYPE_POWER
id|ACPI_BUS_TYPE_POWER
comma
DECL|enumerator|ACPI_BUS_TYPE_PROCESSOR
id|ACPI_BUS_TYPE_PROCESSOR
comma
DECL|enumerator|ACPI_BUS_TYPE_THERMAL
id|ACPI_BUS_TYPE_THERMAL
comma
DECL|enumerator|ACPI_BUS_TYPE_SYSTEM
id|ACPI_BUS_TYPE_SYSTEM
comma
DECL|enumerator|ACPI_BUS_TYPE_POWER_BUTTON
id|ACPI_BUS_TYPE_POWER_BUTTON
comma
DECL|enumerator|ACPI_BUS_TYPE_SLEEP_BUTTON
id|ACPI_BUS_TYPE_SLEEP_BUTTON
comma
DECL|enumerator|ACPI_BUS_DEVICE_TYPE_COUNT
id|ACPI_BUS_DEVICE_TYPE_COUNT
)brace
suffix:semicolon
r_struct
id|acpi_driver
suffix:semicolon
r_struct
id|acpi_device
suffix:semicolon
multiline_comment|/*&n; * ACPI Driver&n; * -----------&n; */
DECL|typedef|acpi_op_add
r_typedef
r_int
(paren
op_star
id|acpi_op_add
)paren
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
DECL|typedef|acpi_op_remove
r_typedef
r_int
(paren
op_star
id|acpi_op_remove
)paren
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|type
)paren
suffix:semicolon
DECL|typedef|acpi_op_lock
r_typedef
r_int
(paren
op_star
id|acpi_op_lock
)paren
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|type
)paren
suffix:semicolon
DECL|typedef|acpi_op_start
r_typedef
r_int
(paren
op_star
id|acpi_op_start
)paren
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
DECL|typedef|acpi_op_stop
r_typedef
r_int
(paren
op_star
id|acpi_op_stop
)paren
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|type
)paren
suffix:semicolon
DECL|typedef|acpi_op_suspend
r_typedef
r_int
(paren
op_star
id|acpi_op_suspend
)paren
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
DECL|typedef|acpi_op_resume
r_typedef
r_int
(paren
op_star
id|acpi_op_resume
)paren
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
DECL|typedef|acpi_op_scan
r_typedef
r_int
(paren
op_star
id|acpi_op_scan
)paren
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
DECL|struct|acpi_driver_ops
r_struct
id|acpi_driver_ops
(brace
DECL|member|add
id|acpi_op_add
id|add
suffix:semicolon
DECL|member|remove
id|acpi_op_remove
id|remove
suffix:semicolon
DECL|member|lock
id|acpi_op_lock
id|lock
suffix:semicolon
DECL|member|start
id|acpi_op_start
id|start
suffix:semicolon
DECL|member|stop
id|acpi_op_stop
id|stop
suffix:semicolon
DECL|member|suspend
id|acpi_op_suspend
id|suspend
suffix:semicolon
DECL|member|resume
id|acpi_op_resume
id|resume
suffix:semicolon
DECL|member|scan
id|acpi_op_scan
id|scan
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_driver
r_struct
id|acpi_driver
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|class
r_char
r_class
(braket
l_int|80
)braket
suffix:semicolon
DECL|member|references
r_int
id|references
suffix:semicolon
DECL|member|ids
r_char
op_star
id|ids
suffix:semicolon
multiline_comment|/* Supported Hardware IDs */
DECL|member|ops
r_struct
id|acpi_driver_ops
id|ops
suffix:semicolon
)brace
suffix:semicolon
DECL|enum|acpi_blacklist_predicates
r_enum
id|acpi_blacklist_predicates
(brace
DECL|enumerator|all_versions
id|all_versions
comma
DECL|enumerator|less_than_or_equal
id|less_than_or_equal
comma
DECL|enumerator|equal
id|equal
comma
DECL|enumerator|greater_than_or_equal
id|greater_than_or_equal
comma
)brace
suffix:semicolon
DECL|struct|acpi_blacklist_item
r_struct
id|acpi_blacklist_item
(brace
DECL|member|oem_id
r_char
id|oem_id
(braket
l_int|7
)braket
suffix:semicolon
DECL|member|oem_table_id
r_char
id|oem_table_id
(braket
l_int|9
)braket
suffix:semicolon
DECL|member|oem_revision
id|u32
id|oem_revision
suffix:semicolon
DECL|member|table
id|acpi_table_type
id|table
suffix:semicolon
DECL|member|oem_revision_predicate
r_enum
id|acpi_blacklist_predicates
id|oem_revision_predicate
suffix:semicolon
DECL|member|reason
r_char
op_star
id|reason
suffix:semicolon
DECL|member|is_critical_error
id|u32
id|is_critical_error
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ACPI Device&n; * -----------&n; */
multiline_comment|/* Status (_STA) */
DECL|struct|acpi_device_status
r_struct
id|acpi_device_status
(brace
DECL|member|present
id|u32
id|present
suffix:colon
l_int|1
suffix:semicolon
DECL|member|enabled
id|u32
id|enabled
suffix:colon
l_int|1
suffix:semicolon
DECL|member|show_in_ui
id|u32
id|show_in_ui
suffix:colon
l_int|1
suffix:semicolon
DECL|member|functional
id|u32
id|functional
suffix:colon
l_int|1
suffix:semicolon
DECL|member|battery_present
id|u32
id|battery_present
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u32
id|reserved
suffix:colon
l_int|27
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Flags */
DECL|struct|acpi_device_flags
r_struct
id|acpi_device_flags
(brace
DECL|member|dynamic_status
id|u8
id|dynamic_status
suffix:colon
l_int|1
suffix:semicolon
DECL|member|compatible_ids
id|u8
id|compatible_ids
suffix:colon
l_int|1
suffix:semicolon
DECL|member|removable
id|u8
id|removable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|ejectable
id|u8
id|ejectable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|lockable
id|u8
id|lockable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|suprise_removal_ok
id|u8
id|suprise_removal_ok
suffix:colon
l_int|1
suffix:semicolon
DECL|member|power_manageable
id|u8
id|power_manageable
suffix:colon
l_int|1
suffix:semicolon
DECL|member|performance_manageable
id|u8
id|performance_manageable
suffix:colon
l_int|1
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* File System */
DECL|struct|acpi_device_dir
r_struct
id|acpi_device_dir
(brace
DECL|member|entry
r_struct
id|proc_dir_entry
op_star
id|entry
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|acpi_device_dir
mdefine_line|#define acpi_device_dir(d)&t;((d)-&gt;dir.entry)
multiline_comment|/* Plug and Play */
DECL|typedef|acpi_bus_id
r_typedef
r_char
id|acpi_bus_id
(braket
l_int|5
)braket
suffix:semicolon
DECL|typedef|acpi_bus_address
r_typedef
r_int
r_int
id|acpi_bus_address
suffix:semicolon
DECL|typedef|acpi_hardware_id
r_typedef
r_char
id|acpi_hardware_id
(braket
l_int|9
)braket
suffix:semicolon
DECL|typedef|acpi_unique_id
r_typedef
r_char
id|acpi_unique_id
(braket
l_int|9
)braket
suffix:semicolon
DECL|typedef|acpi_device_name
r_typedef
r_char
id|acpi_device_name
(braket
l_int|40
)braket
suffix:semicolon
DECL|typedef|acpi_device_class
r_typedef
r_char
id|acpi_device_class
(braket
l_int|20
)braket
suffix:semicolon
DECL|struct|acpi_device_pnp
r_struct
id|acpi_device_pnp
(brace
DECL|member|bus_id
id|acpi_bus_id
id|bus_id
suffix:semicolon
multiline_comment|/* Object name */
DECL|member|bus_address
id|acpi_bus_address
id|bus_address
suffix:semicolon
multiline_comment|/* _ADR */
DECL|member|hardware_id
id|acpi_hardware_id
id|hardware_id
suffix:semicolon
multiline_comment|/* _HID */
DECL|member|unique_id
id|acpi_unique_id
id|unique_id
suffix:semicolon
multiline_comment|/* _UID */
DECL|member|device_name
id|acpi_device_name
id|device_name
suffix:semicolon
multiline_comment|/* Driver-determined */
DECL|member|device_class
id|acpi_device_class
id|device_class
suffix:semicolon
multiline_comment|/*        &quot;          */
)brace
suffix:semicolon
DECL|macro|acpi_device_bid
mdefine_line|#define acpi_device_bid(d)&t;((d)-&gt;pnp.bus_id)
DECL|macro|acpi_device_adr
mdefine_line|#define acpi_device_adr(d)&t;((d)-&gt;pnp.bus_address)
DECL|macro|acpi_device_hid
mdefine_line|#define acpi_device_hid(d)&t;((d)-&gt;pnp.hardware_id)
DECL|macro|acpi_device_uid
mdefine_line|#define acpi_device_uid(d)&t;((d)-&gt;pnp.unique_id)
DECL|macro|acpi_device_name
mdefine_line|#define acpi_device_name(d)&t;((d)-&gt;pnp.device_name)
DECL|macro|acpi_device_class
mdefine_line|#define acpi_device_class(d)&t;((d)-&gt;pnp.device_class)
multiline_comment|/* Power Management */
DECL|struct|acpi_device_power_flags
r_struct
id|acpi_device_power_flags
(brace
DECL|member|explicit_get
id|u8
id|explicit_get
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* _PSC present? */
DECL|member|power_resources
id|u8
id|power_resources
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Power resources */
DECL|member|inrush_current
id|u8
id|inrush_current
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Serialize Dx-&gt;D0 */
DECL|member|wake_capable
id|u8
id|wake_capable
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Wakeup supported? */
DECL|member|wake_enabled
id|u8
id|wake_enabled
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Enabled for wakeup */
DECL|member|power_removed
id|u8
id|power_removed
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Optimize Dx-&gt;D0 */
DECL|member|reserved
id|u8
id|reserved
suffix:colon
l_int|2
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_device_power_state
r_struct
id|acpi_device_power_state
(brace
r_struct
(brace
DECL|member|valid
id|u8
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|explicit_set
id|u8
id|explicit_set
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* _PSx present? */
DECL|member|reserved
id|u8
id|reserved
suffix:colon
l_int|6
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
DECL|member|power
r_int
id|power
suffix:semicolon
multiline_comment|/* % Power (compared to D0) */
DECL|member|latency
r_int
id|latency
suffix:semicolon
multiline_comment|/* Dx-&gt;D0 time (microseconds) */
DECL|member|resources
r_struct
id|acpi_handle_list
id|resources
suffix:semicolon
multiline_comment|/* Power resources referenced */
)brace
suffix:semicolon
DECL|struct|acpi_device_power
r_struct
id|acpi_device_power
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
multiline_comment|/* Current state */
DECL|member|flags
r_struct
id|acpi_device_power_flags
id|flags
suffix:semicolon
DECL|member|states
r_struct
id|acpi_device_power_state
id|states
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Power states (D0-D3) */
)brace
suffix:semicolon
multiline_comment|/* Performance Management */
DECL|struct|acpi_device_perf_flags
r_struct
id|acpi_device_perf_flags
(brace
DECL|member|reserved
id|u8
id|reserved
suffix:colon
l_int|8
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_device_perf_state
r_struct
id|acpi_device_perf_state
(brace
r_struct
(brace
DECL|member|valid
id|u8
id|valid
suffix:colon
l_int|1
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
suffix:colon
l_int|7
suffix:semicolon
DECL|member|flags
)brace
id|flags
suffix:semicolon
DECL|member|power
id|u8
id|power
suffix:semicolon
multiline_comment|/* % Power (compared to P0) */
DECL|member|performance
id|u8
id|performance
suffix:semicolon
multiline_comment|/* % Performance (    &quot;   ) */
DECL|member|latency
r_int
id|latency
suffix:semicolon
multiline_comment|/* Px-&gt;P0 time (microseconds) */
)brace
suffix:semicolon
DECL|struct|acpi_device_perf
r_struct
id|acpi_device_perf
(brace
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|flags
r_struct
id|acpi_device_perf_flags
id|flags
suffix:semicolon
DECL|member|state_count
r_int
id|state_count
suffix:semicolon
DECL|member|states
r_struct
id|acpi_device_perf_state
op_star
id|states
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Device */
DECL|struct|acpi_device
r_struct
id|acpi_device
(brace
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
DECL|member|parent
r_struct
id|acpi_device
op_star
id|parent
suffix:semicolon
DECL|member|children
r_struct
id|list_head
id|children
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|status
r_struct
id|acpi_device_status
id|status
suffix:semicolon
DECL|member|flags
r_struct
id|acpi_device_flags
id|flags
suffix:semicolon
DECL|member|pnp
r_struct
id|acpi_device_pnp
id|pnp
suffix:semicolon
DECL|member|power
r_struct
id|acpi_device_power
id|power
suffix:semicolon
DECL|member|performance
r_struct
id|acpi_device_perf
id|performance
suffix:semicolon
DECL|member|dir
r_struct
id|acpi_device_dir
id|dir
suffix:semicolon
DECL|member|driver
r_struct
id|acpi_driver
op_star
id|driver
suffix:semicolon
DECL|member|driver_data
r_void
op_star
id|driver_data
suffix:semicolon
macro_line|#ifdef CONFIG_LDM
DECL|member|dev
r_struct
id|device
id|dev
suffix:semicolon
macro_line|#endif
)brace
suffix:semicolon
DECL|macro|acpi_driver_data
mdefine_line|#define acpi_driver_data(d)&t;((d)-&gt;driver_data)
multiline_comment|/*&n; * Events&n; * ------&n; */
DECL|struct|acpi_bus_event
r_struct
id|acpi_bus_event
(brace
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
DECL|member|device_class
id|acpi_device_class
id|device_class
suffix:semicolon
DECL|member|bus_id
id|acpi_bus_id
id|bus_id
suffix:semicolon
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|data
id|u32
id|data
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * External Functions&n; */
r_int
id|acpi_bus_get_device
c_func
(paren
id|acpi_handle
comma
r_struct
id|acpi_device
op_star
op_star
id|device
)paren
suffix:semicolon
r_int
id|acpi_bus_get_status
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_int
id|acpi_bus_get_power
(paren
id|acpi_handle
id|handle
comma
r_int
op_star
id|state
)paren
suffix:semicolon
r_int
id|acpi_bus_set_power
(paren
id|acpi_handle
id|handle
comma
r_int
id|state
)paren
suffix:semicolon
r_int
id|acpi_bus_generate_event
(paren
r_struct
id|acpi_device
op_star
id|device
comma
id|u8
id|type
comma
r_int
id|data
)paren
suffix:semicolon
r_int
id|acpi_bus_receive_event
(paren
r_struct
id|acpi_bus_event
op_star
id|event
)paren
suffix:semicolon
r_int
id|acpi_bus_register_driver
(paren
r_struct
id|acpi_driver
op_star
id|driver
)paren
suffix:semicolon
r_int
id|acpi_bus_unregister_driver
(paren
r_struct
id|acpi_driver
op_star
id|driver
)paren
suffix:semicolon
r_int
id|acpi_bus_scan
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_int
id|acpi_init
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_exit
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /*CONFIG_ACPI_BUS*/
macro_line|#endif /*__ACPI_BUS_H__*/
eof
