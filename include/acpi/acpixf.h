multiline_comment|/******************************************************************************&n; *&n; * Name: acpixf.h - External interfaces to the ACPI subsystem&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACXFACE_H__
DECL|macro|__ACXFACE_H__
mdefine_line|#define __ACXFACE_H__
macro_line|#include &quot;actypes.h&quot;
macro_line|#include &quot;actbl.h&quot;
multiline_comment|/*&n; * Global interfaces&n; */
id|acpi_status
id|acpi_initialize_subsystem
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_enable_subsystem
(paren
id|u32
id|flags
)paren
suffix:semicolon
id|acpi_status
id|acpi_initialize_objects
(paren
id|u32
id|flags
)paren
suffix:semicolon
id|acpi_status
id|acpi_terminate
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_subsystem_status
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_enable
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_disable
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_system_info
(paren
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
suffix:semicolon
r_const
r_char
op_star
id|acpi_format_exception
(paren
id|acpi_status
id|exception
)paren
suffix:semicolon
id|acpi_status
id|acpi_purge_cached_objects
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_install_initialization_handler
(paren
id|acpi_init_handler
id|handler
comma
id|u32
id|function
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
id|acpi_status
id|acpi_find_root_pointer
(paren
id|u32
id|flags
comma
r_struct
id|acpi_pointer
op_star
id|rsdp_address
)paren
suffix:semicolon
id|acpi_status
id|acpi_load_tables
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_load_table
(paren
r_struct
id|acpi_table_header
op_star
id|table_ptr
)paren
suffix:semicolon
id|acpi_status
id|acpi_unload_table
(paren
id|acpi_table_type
id|table_type
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_table_header
(paren
id|acpi_table_type
id|table_type
comma
id|u32
id|instance
comma
r_struct
id|acpi_table_header
op_star
id|out_table_header
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_table
(paren
id|acpi_table_type
id|table_type
comma
id|u32
id|instance
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_firmware_table
(paren
id|acpi_string
id|signature
comma
id|u32
id|instance
comma
id|u32
id|flags
comma
r_struct
id|acpi_table_header
op_star
op_star
id|table_pointer
)paren
suffix:semicolon
multiline_comment|/*&n; * Namespace and name interfaces&n; */
id|acpi_status
id|acpi_walk_namespace
(paren
id|acpi_object_type
id|type
comma
id|acpi_handle
id|start_object
comma
id|u32
id|max_depth
comma
id|acpi_walk_callback
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
id|acpi_status
id|acpi_get_devices
(paren
r_char
op_star
id|HID
comma
id|acpi_walk_callback
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
id|acpi_status
id|acpi_get_name
(paren
id|acpi_handle
id|handle
comma
id|u32
id|name_type
comma
r_struct
id|acpi_buffer
op_star
id|ret_path_ptr
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_handle
(paren
id|acpi_handle
id|parent
comma
id|acpi_string
id|pathname
comma
id|acpi_handle
op_star
id|ret_handle
)paren
suffix:semicolon
id|acpi_status
id|acpi_attach_data
(paren
id|acpi_handle
id|obj_handle
comma
id|acpi_object_handler
id|handler
comma
r_void
op_star
id|data
)paren
suffix:semicolon
id|acpi_status
id|acpi_detach_data
(paren
id|acpi_handle
id|obj_handle
comma
id|acpi_object_handler
id|handler
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_data
(paren
id|acpi_handle
id|obj_handle
comma
id|acpi_object_handler
id|handler
comma
r_void
op_star
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * Object manipulation and enumeration&n; */
id|acpi_status
id|acpi_evaluate_object
(paren
id|acpi_handle
id|object
comma
id|acpi_string
id|pathname
comma
r_struct
id|acpi_object_list
op_star
id|parameter_objects
comma
r_struct
id|acpi_buffer
op_star
id|return_object_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_evaluate_object_typed
(paren
id|acpi_handle
id|object
comma
id|acpi_string
id|pathname
comma
r_struct
id|acpi_object_list
op_star
id|external_params
comma
r_struct
id|acpi_buffer
op_star
id|return_buffer
comma
id|acpi_object_type
id|return_type
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_object_info
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_buffer
op_star
id|return_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_next_object
(paren
id|acpi_object_type
id|type
comma
id|acpi_handle
id|parent
comma
id|acpi_handle
id|child
comma
id|acpi_handle
op_star
id|out_handle
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_type
(paren
id|acpi_handle
id|object
comma
id|acpi_object_type
op_star
id|out_type
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_parent
(paren
id|acpi_handle
id|object
comma
id|acpi_handle
op_star
id|out_handle
)paren
suffix:semicolon
multiline_comment|/*&n; * Event handler interfaces&n; */
id|acpi_status
id|acpi_install_fixed_event_handler
(paren
id|u32
id|acpi_event
comma
id|acpi_event_handler
id|handler
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|acpi_remove_fixed_event_handler
(paren
id|u32
id|acpi_event
comma
id|acpi_event_handler
id|handler
)paren
suffix:semicolon
id|acpi_status
id|acpi_install_notify_handler
(paren
id|acpi_handle
id|device
comma
id|u32
id|handler_type
comma
id|acpi_notify_handler
id|handler
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|acpi_remove_notify_handler
(paren
id|acpi_handle
id|device
comma
id|u32
id|handler_type
comma
id|acpi_notify_handler
id|handler
)paren
suffix:semicolon
id|acpi_status
id|acpi_install_address_space_handler
(paren
id|acpi_handle
id|device
comma
id|acpi_adr_space_type
id|space_id
comma
id|acpi_adr_space_handler
id|handler
comma
id|acpi_adr_space_setup
id|setup
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|acpi_remove_address_space_handler
(paren
id|acpi_handle
id|device
comma
id|acpi_adr_space_type
id|space_id
comma
id|acpi_adr_space_handler
id|handler
)paren
suffix:semicolon
id|acpi_status
id|acpi_install_gpe_handler
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
comma
id|u32
id|type
comma
id|acpi_event_handler
id|address
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|acpi_acquire_global_lock
(paren
id|u16
id|timeout
comma
id|u32
op_star
id|handle
)paren
suffix:semicolon
id|acpi_status
id|acpi_release_global_lock
(paren
id|u32
id|handle
)paren
suffix:semicolon
id|acpi_status
id|acpi_remove_gpe_handler
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
comma
id|acpi_event_handler
id|address
)paren
suffix:semicolon
id|acpi_status
id|acpi_enable_event
(paren
id|u32
id|event
comma
id|u32
id|flags
)paren
suffix:semicolon
id|acpi_status
id|acpi_disable_event
(paren
id|u32
id|event
comma
id|u32
id|flags
)paren
suffix:semicolon
id|acpi_status
id|acpi_clear_event
(paren
id|u32
id|event
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_event_status
(paren
id|u32
id|event
comma
id|acpi_event_status
op_star
id|event_status
)paren
suffix:semicolon
id|acpi_status
id|acpi_set_gpe_type
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
comma
id|u8
id|type
)paren
suffix:semicolon
id|acpi_status
id|acpi_enable_gpe
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
comma
id|u32
id|flags
)paren
suffix:semicolon
id|acpi_status
id|acpi_disable_gpe
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
comma
id|u32
id|flags
)paren
suffix:semicolon
id|acpi_status
id|acpi_clear_gpe
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
comma
id|u32
id|flags
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_gpe_status
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
comma
id|u32
id|flags
comma
id|acpi_event_status
op_star
id|event_status
)paren
suffix:semicolon
id|acpi_status
id|acpi_install_gpe_block
(paren
id|acpi_handle
id|gpe_device
comma
r_struct
id|acpi_generic_address
op_star
id|gpe_block_address
comma
id|u32
id|register_count
comma
id|u32
id|interrupt_level
)paren
suffix:semicolon
id|acpi_status
id|acpi_remove_gpe_block
(paren
id|acpi_handle
id|gpe_device
)paren
suffix:semicolon
multiline_comment|/*&n; * Resource interfaces&n; */
r_typedef
DECL|typedef|ACPI_WALK_RESOURCE_CALLBACK
id|acpi_status
(paren
op_star
id|ACPI_WALK_RESOURCE_CALLBACK
)paren
(paren
r_struct
id|acpi_resource
op_star
id|resource
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_current_resources
c_func
(paren
id|acpi_handle
id|device_handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_possible_resources
c_func
(paren
id|acpi_handle
id|device_handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_walk_resources
(paren
id|acpi_handle
id|device_handle
comma
r_char
op_star
id|path
comma
id|ACPI_WALK_RESOURCE_CALLBACK
id|user_function
comma
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|acpi_set_current_resources
(paren
id|acpi_handle
id|device_handle
comma
r_struct
id|acpi_buffer
op_star
id|in_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_irq_routing_table
(paren
id|acpi_handle
id|bus_device_handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
suffix:semicolon
id|acpi_status
id|acpi_resource_to_address64
(paren
r_struct
id|acpi_resource
op_star
id|resource
comma
r_struct
id|acpi_resource_address64
op_star
id|out
)paren
suffix:semicolon
multiline_comment|/*&n; * Hardware (ACPI device) interfaces&n; */
id|acpi_status
id|acpi_get_register
(paren
id|u32
id|register_id
comma
id|u32
op_star
id|return_value
comma
id|u32
id|flags
)paren
suffix:semicolon
id|acpi_status
id|acpi_set_register
(paren
id|u32
id|register_id
comma
id|u32
id|value
comma
id|u32
id|flags
)paren
suffix:semicolon
id|acpi_status
id|acpi_set_firmware_waking_vector
(paren
id|acpi_physical_address
id|physical_address
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_firmware_waking_vector
(paren
id|acpi_physical_address
op_star
id|physical_address
)paren
suffix:semicolon
id|acpi_status
id|acpi_get_sleep_type_data
(paren
id|u8
id|sleep_state
comma
id|u8
op_star
id|slp_typ_a
comma
id|u8
op_star
id|slp_typ_b
)paren
suffix:semicolon
id|acpi_status
id|acpi_enter_sleep_state_prep
(paren
id|u8
id|sleep_state
)paren
suffix:semicolon
id|acpi_status
id|asmlinkage
id|acpi_enter_sleep_state
(paren
id|u8
id|sleep_state
)paren
suffix:semicolon
id|acpi_status
id|asmlinkage
id|acpi_enter_sleep_state_s4bios
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_leave_sleep_state
(paren
id|u8
id|sleep_state
)paren
suffix:semicolon
macro_line|#endif /* __ACXFACE_H__ */
eof
