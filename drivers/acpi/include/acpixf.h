multiline_comment|/******************************************************************************&n; *&n; * Name: acpixf.h - External interfaces to the ACPI subsystem&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACXFACE_H__
DECL|macro|__ACXFACE_H__
mdefine_line|#define __ACXFACE_H__
macro_line|#include &quot;actypes.h&quot;
macro_line|#include &quot;actbl.h&quot;
multiline_comment|/*&n; * Global interfaces&n; */
id|ACPI_STATUS
id|acpi_initialize_subsystem
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_enable_subsystem
(paren
id|u32
id|flags
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_terminate
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_enable
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_disable
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_system_info
c_func
(paren
id|ACPI_BUFFER
op_star
id|ret_buffer
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_format_exception
(paren
id|ACPI_STATUS
id|exception
comma
id|ACPI_BUFFER
op_star
id|out_buffer
)paren
suffix:semicolon
multiline_comment|/*&n; * ACPI Memory manager&n; */
r_void
op_star
id|acpi_allocate
(paren
id|u32
id|size
)paren
suffix:semicolon
r_void
op_star
id|acpi_callocate
(paren
id|u32
id|size
)paren
suffix:semicolon
r_void
id|acpi_free
(paren
r_void
op_star
id|address
)paren
suffix:semicolon
multiline_comment|/*&n; * ACPI table manipulation interfaces&n; */
id|ACPI_STATUS
id|acpi_find_root_pointer
(paren
id|ACPI_PHYSICAL_ADDRESS
op_star
id|rsdp_physical_address
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_load_tables
(paren
id|ACPI_PHYSICAL_ADDRESS
id|rsdp_physical_address
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_load_table
(paren
id|ACPI_TABLE_HEADER
op_star
id|table_ptr
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_unload_table
(paren
id|ACPI_TABLE_TYPE
id|table_type
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_table_header
(paren
id|ACPI_TABLE_TYPE
id|table_type
comma
id|u32
id|instance
comma
id|ACPI_TABLE_HEADER
op_star
id|out_table_header
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_table
(paren
id|ACPI_TABLE_TYPE
id|table_type
comma
id|u32
id|instance
comma
id|ACPI_BUFFER
op_star
id|ret_buffer
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_firmware_table
(paren
id|ACPI_STRING
id|signature
comma
id|u32
id|instance
comma
id|u32
id|flags
comma
id|ACPI_TABLE_HEADER
op_star
op_star
id|table_pointer
)paren
suffix:semicolon
multiline_comment|/*&n; * Namespace and name interfaces&n; */
id|ACPI_STATUS
id|acpi_walk_namespace
(paren
id|ACPI_OBJECT_TYPE
id|type
comma
id|ACPI_HANDLE
id|start_object
comma
id|u32
id|max_depth
comma
id|ACPI_WALK_CALLBACK
id|user_function
comma
r_void
op_star
id|context
comma
r_void
op_star
op_star
id|return_value
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_devices
(paren
id|NATIVE_CHAR
op_star
id|HID
comma
id|ACPI_WALK_CALLBACK
id|user_function
comma
r_void
op_star
id|context
comma
r_void
op_star
op_star
id|return_value
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_name
(paren
id|ACPI_HANDLE
id|handle
comma
id|u32
id|name_type
comma
id|ACPI_BUFFER
op_star
id|ret_path_ptr
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_handle
(paren
id|ACPI_HANDLE
id|parent
comma
id|ACPI_STRING
id|pathname
comma
id|ACPI_HANDLE
op_star
id|ret_handle
)paren
suffix:semicolon
multiline_comment|/*&n; * Object manipulation and enumeration&n; */
id|ACPI_STATUS
id|acpi_evaluate_object
(paren
id|ACPI_HANDLE
id|object
comma
id|ACPI_STRING
id|pathname
comma
id|ACPI_OBJECT_LIST
op_star
id|parameter_objects
comma
id|ACPI_BUFFER
op_star
id|return_object_buffer
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_object_info
(paren
id|ACPI_HANDLE
id|device
comma
id|ACPI_DEVICE_INFO
op_star
id|info
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_next_object
(paren
id|ACPI_OBJECT_TYPE
id|type
comma
id|ACPI_HANDLE
id|parent
comma
id|ACPI_HANDLE
id|child
comma
id|ACPI_HANDLE
op_star
id|out_handle
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_type
(paren
id|ACPI_HANDLE
id|object
comma
id|ACPI_OBJECT_TYPE
op_star
id|out_type
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_parent
(paren
id|ACPI_HANDLE
id|object
comma
id|ACPI_HANDLE
op_star
id|out_handle
)paren
suffix:semicolon
multiline_comment|/*&n; * Event handler interfaces&n; */
id|ACPI_STATUS
id|acpi_install_fixed_event_handler
(paren
id|u32
id|acpi_event
comma
id|ACPI_EVENT_HANDLER
id|handler
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_remove_fixed_event_handler
(paren
id|u32
id|acpi_event
comma
id|ACPI_EVENT_HANDLER
id|handler
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_install_notify_handler
(paren
id|ACPI_HANDLE
id|device
comma
id|u32
id|handler_type
comma
id|ACPI_NOTIFY_HANDLER
id|handler
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_remove_notify_handler
(paren
id|ACPI_HANDLE
id|device
comma
id|u32
id|handler_type
comma
id|ACPI_NOTIFY_HANDLER
id|handler
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_install_address_space_handler
(paren
id|ACPI_HANDLE
id|device
comma
id|ACPI_ADR_SPACE_TYPE
id|space_id
comma
id|ACPI_ADR_SPACE_HANDLER
id|handler
comma
id|ACPI_ADR_SPACE_SETUP
id|setup
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_remove_address_space_handler
(paren
id|ACPI_HANDLE
id|device
comma
id|ACPI_ADR_SPACE_TYPE
id|space_id
comma
id|ACPI_ADR_SPACE_HANDLER
id|handler
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_install_gpe_handler
(paren
id|u32
id|gpe_number
comma
id|u32
id|type
comma
id|ACPI_GPE_HANDLER
id|handler
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_acquire_global_lock
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_release_global_lock
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_remove_gpe_handler
(paren
id|u32
id|gpe_number
comma
id|ACPI_GPE_HANDLER
id|handler
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_enable_event
(paren
id|u32
id|acpi_event
comma
id|u32
id|type
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_disable_event
(paren
id|u32
id|acpi_event
comma
id|u32
id|type
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_clear_event
(paren
id|u32
id|acpi_event
comma
id|u32
id|type
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_event_status
(paren
id|u32
id|acpi_event
comma
id|u32
id|type
comma
id|ACPI_EVENT_STATUS
op_star
id|event_status
)paren
suffix:semicolon
multiline_comment|/*&n; * Resource interfaces&n; */
id|ACPI_STATUS
id|acpi_get_current_resources
c_func
(paren
id|ACPI_HANDLE
id|device_handle
comma
id|ACPI_BUFFER
op_star
id|ret_buffer
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_possible_resources
c_func
(paren
id|ACPI_HANDLE
id|device_handle
comma
id|ACPI_BUFFER
op_star
id|ret_buffer
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_set_current_resources
(paren
id|ACPI_HANDLE
id|device_handle
comma
id|ACPI_BUFFER
op_star
id|in_buffer
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_irq_routing_table
(paren
id|ACPI_HANDLE
id|bus_device_handle
comma
id|ACPI_BUFFER
op_star
id|ret_buffer
)paren
suffix:semicolon
multiline_comment|/*&n; * Hardware (ACPI device) interfaces&n; */
id|ACPI_STATUS
id|acpi_set_firmware_waking_vector
(paren
id|ACPI_PHYSICAL_ADDRESS
id|physical_address
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_firmware_waking_vector
(paren
id|ACPI_PHYSICAL_ADDRESS
op_star
id|physical_address
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_enter_sleep_state
(paren
id|u8
id|sleep_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_processor_throttling_info
(paren
id|ACPI_HANDLE
id|processor_handle
comma
id|ACPI_BUFFER
op_star
id|user_buffer
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_set_processor_throttling_state
(paren
id|ACPI_HANDLE
id|processor_handle
comma
id|u32
id|throttle_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_processor_throttling_state
(paren
id|ACPI_HANDLE
id|processor_handle
comma
id|u32
op_star
id|throttle_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_get_processor_cx_info
(paren
id|ACPI_HANDLE
id|processor_handle
comma
id|ACPI_BUFFER
op_star
id|user_buffer
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_set_processor_sleep_state
(paren
id|ACPI_HANDLE
id|processor_handle
comma
id|u32
id|cx_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_processor_sleep
(paren
id|ACPI_HANDLE
id|processor_handle
comma
id|u32
op_star
id|pm_timer_ticks
)paren
suffix:semicolon
macro_line|#endif /* __ACXFACE_H__ */
eof
