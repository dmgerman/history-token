multiline_comment|/******************************************************************************&n; *&n; * Name: acevents.h - Event subcomponent prototypes and defines&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACEVENTS_H__
DECL|macro|__ACEVENTS_H__
mdefine_line|#define __ACEVENTS_H__
id|acpi_status
id|acpi_ev_initialize
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_handler_initialize
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * Evfixed - Fixed event handling&n; */
id|acpi_status
id|acpi_ev_fixed_event_initialize
(paren
r_void
)paren
suffix:semicolon
id|u32
id|acpi_ev_fixed_event_detect
(paren
r_void
)paren
suffix:semicolon
id|u32
id|acpi_ev_fixed_event_dispatch
(paren
id|u32
id|event
)paren
suffix:semicolon
multiline_comment|/*&n; * Evmisc&n; */
id|u8
id|acpi_ev_is_notify_object
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_acquire_global_lock
c_func
(paren
id|u16
id|timeout
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_release_global_lock
c_func
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_init_global_lock_handler
(paren
r_void
)paren
suffix:semicolon
id|u32
id|acpi_ev_get_gpe_number_index
(paren
id|u32
id|gpe_number
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_queue_notify_request
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
comma
id|u32
id|notify_value
)paren
suffix:semicolon
r_void
id|ACPI_SYSTEM_XFACE
id|acpi_ev_notify_dispatch
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
multiline_comment|/*&n; * Evgpe - GPE handling and dispatch&n; */
id|acpi_status
id|acpi_ev_walk_gpe_list
(paren
id|ACPI_GPE_CALLBACK
id|gpe_walk_callback
)paren
suffix:semicolon
id|u8
id|acpi_ev_valid_gpe_event
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
)paren
suffix:semicolon
r_struct
id|acpi_gpe_event_info
op_star
id|acpi_ev_get_gpe_event_info
(paren
id|acpi_handle
id|gpe_device
comma
id|u32
id|gpe_number
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_gpe_initialize
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_create_gpe_block
(paren
r_struct
id|acpi_namespace_node
op_star
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
id|u8
id|gpe_block_base_number
comma
id|u32
id|interrupt_level
comma
r_struct
id|acpi_gpe_block_info
op_star
op_star
id|return_gpe_block
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_delete_gpe_block
(paren
r_struct
id|acpi_gpe_block_info
op_star
id|gpe_block
)paren
suffix:semicolon
id|u32
id|acpi_ev_gpe_dispatch
(paren
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
comma
id|u32
id|gpe_number
)paren
suffix:semicolon
id|u32
id|acpi_ev_gpe_detect
(paren
r_struct
id|acpi_gpe_xrupt_info
op_star
id|gpe_xrupt_list
)paren
suffix:semicolon
multiline_comment|/*&n; * Evregion - Address Space handling&n; */
id|acpi_status
id|acpi_ev_init_address_spaces
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_address_space_dispatch
(paren
r_union
id|acpi_operand_object
op_star
id|region_obj
comma
id|u32
id|function
comma
id|acpi_physical_address
id|address
comma
id|u32
id|bit_width
comma
r_void
op_star
id|value
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_addr_handler_helper
(paren
id|acpi_handle
id|obj_handle
comma
id|u32
id|level
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
id|acpi_ev_attach_region
(paren
r_union
id|acpi_operand_object
op_star
id|handler_obj
comma
r_union
id|acpi_operand_object
op_star
id|region_obj
comma
id|u8
id|acpi_ns_is_locked
)paren
suffix:semicolon
r_void
id|acpi_ev_detach_region
(paren
r_union
id|acpi_operand_object
op_star
id|region_obj
comma
id|u8
id|acpi_ns_is_locked
)paren
suffix:semicolon
multiline_comment|/*&n; * Evregini - Region initialization and setup&n; */
id|acpi_status
id|acpi_ev_system_memory_region_setup
(paren
id|acpi_handle
id|handle
comma
id|u32
id|function
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_io_space_region_setup
(paren
id|acpi_handle
id|handle
comma
id|u32
id|function
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_pci_config_region_setup
(paren
id|acpi_handle
id|handle
comma
id|u32
id|function
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_cmos_region_setup
(paren
id|acpi_handle
id|handle
comma
id|u32
id|function
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_pci_bar_region_setup
(paren
id|acpi_handle
id|handle
comma
id|u32
id|function
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_default_region_setup
(paren
id|acpi_handle
id|handle
comma
id|u32
id|function
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_initialize_region
(paren
r_union
id|acpi_operand_object
op_star
id|region_obj
comma
id|u8
id|acpi_ns_locked
)paren
suffix:semicolon
multiline_comment|/*&n; * Evsci - SCI (System Control Interrupt) handling/dispatch&n; */
id|u32
id|ACPI_SYSTEM_XFACE
id|acpi_ev_gpe_xrupt_handler
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
id|u32
id|acpi_ev_install_sci_handler
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_ev_remove_sci_handler
(paren
r_void
)paren
suffix:semicolon
id|u32
id|acpi_ev_initialize_sCI
(paren
id|u32
id|program_sCI
)paren
suffix:semicolon
r_void
id|acpi_ev_terminate
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif  /* __ACEVENTS_H__  */
eof
