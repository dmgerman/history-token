multiline_comment|/******************************************************************************&n; *&n; * Name: acinterp.h - Interpreter subcomponent prototypes and defines&n; *       $Revision: 141 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACINTERP_H__
DECL|macro|__ACINTERP_H__
mdefine_line|#define __ACINTERP_H__
DECL|macro|ACPI_WALK_OPERANDS
mdefine_line|#define ACPI_WALK_OPERANDS       (&amp;(walk_state-&gt;operands [walk_state-&gt;num_operands -1]))
id|acpi_status
id|acpi_ex_resolve_operands
(paren
id|u16
id|opcode
comma
id|acpi_operand_object
op_star
op_star
id|stack_ptr
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_check_object_type
(paren
id|acpi_object_type
id|type_needed
comma
id|acpi_object_type
id|this_type
comma
r_void
op_star
id|object
)paren
suffix:semicolon
multiline_comment|/*&n; * exxface - External interpreter interfaces&n; */
id|acpi_status
id|acpi_ex_load_table
(paren
id|acpi_table_type
id|table_id
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_execute_method
(paren
id|acpi_namespace_node
op_star
id|method_node
comma
id|acpi_operand_object
op_star
op_star
id|params
comma
id|acpi_operand_object
op_star
op_star
id|return_obj_desc
)paren
suffix:semicolon
multiline_comment|/*&n; * exconvrt - object conversion&n; */
id|acpi_status
id|acpi_ex_convert_to_integer
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_operand_object
op_star
op_star
id|result_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_convert_to_buffer
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_operand_object
op_star
op_star
id|result_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_convert_to_string
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_operand_object
op_star
op_star
id|result_desc
comma
id|u32
id|base
comma
id|u32
id|max_length
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_convert_to_target_type
(paren
id|acpi_object_type
id|destination_type
comma
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_operand_object
op_star
op_star
id|result_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|u32
id|acpi_ex_convert_to_ascii
(paren
id|acpi_integer
id|integer
comma
id|u32
id|base
comma
id|u8
op_star
id|string
)paren
suffix:semicolon
multiline_comment|/*&n; * exfield - ACPI AML (p-code) execution - field manipulation&n; */
id|acpi_status
id|acpi_ex_extract_from_field
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
r_void
op_star
id|buffer
comma
id|u32
id|buffer_length
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_insert_into_field
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
r_void
op_star
id|buffer
comma
id|u32
id|buffer_length
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_setup_region
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|u32
id|field_datum_byte_offset
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_access_region
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|u32
id|field_datum_byte_offset
comma
id|acpi_integer
op_star
id|value
comma
id|u32
id|read_write
)paren
suffix:semicolon
id|u8
id|acpi_ex_register_overflow
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_integer
id|value
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_field_datum_io
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|u32
id|field_datum_byte_offset
comma
id|acpi_integer
op_star
id|value
comma
id|u32
id|read_write
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_write_with_update_rule
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_integer
id|mask
comma
id|acpi_integer
id|field_value
comma
id|u32
id|field_datum_byte_offset
)paren
suffix:semicolon
r_void
id|acpi_ex_get_buffer_datum
c_func
(paren
id|acpi_integer
op_star
id|datum
comma
r_void
op_star
id|buffer
comma
id|u32
id|byte_granularity
comma
id|u32
id|offset
)paren
suffix:semicolon
r_void
id|acpi_ex_set_buffer_datum
(paren
id|acpi_integer
id|merged_datum
comma
r_void
op_star
id|buffer
comma
id|u32
id|byte_granularity
comma
id|u32
id|offset
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_read_data_from_field
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_operand_object
op_star
op_star
id|ret_buffer_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_write_data_to_field
(paren
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
multiline_comment|/*&n; * exmisc - ACPI AML (p-code) execution - specific opcodes&n; */
id|acpi_status
id|acpi_ex_opcode_3A_0T_0R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_opcode_3A_1T_1R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_opcode_6A_0T_1R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|u8
id|acpi_ex_do_match
(paren
id|u32
id|match_op
comma
id|acpi_integer
id|package_value
comma
id|acpi_integer
id|match_value
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_get_object_reference
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_operand_object
op_star
op_star
id|return_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_resolve_multiple
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_operand_object
op_star
id|operand
comma
id|acpi_object_type
op_star
id|return_type
comma
id|acpi_operand_object
op_star
op_star
id|return_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_concat_template
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_operand_object
op_star
id|obj_desc2
comma
id|acpi_operand_object
op_star
op_star
id|actual_return_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_do_concatenate
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_operand_object
op_star
id|obj_desc2
comma
id|acpi_operand_object
op_star
op_star
id|actual_return_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|u8
id|acpi_ex_do_logical_op
(paren
id|u16
id|opcode
comma
id|acpi_integer
id|operand0
comma
id|acpi_integer
id|operand1
)paren
suffix:semicolon
id|acpi_integer
id|acpi_ex_do_math_op
(paren
id|u16
id|opcode
comma
id|acpi_integer
id|operand0
comma
id|acpi_integer
id|operand1
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_create_mutex
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_create_processor
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_create_power_resource
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_create_region
(paren
id|u8
op_star
id|aml_start
comma
id|u32
id|aml_length
comma
id|u8
id|region_space
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_create_table_region
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_create_event
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_create_alias
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_create_method
(paren
id|u8
op_star
id|aml_start
comma
id|u32
id|aml_length
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n; * exconfig - dynamic table load/unload&n; */
id|acpi_status
id|acpi_ex_add_table
(paren
id|acpi_table_header
op_star
id|table
comma
id|acpi_namespace_node
op_star
id|parent_node
comma
id|acpi_operand_object
op_star
op_star
id|ddb_handle
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_load_op
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_operand_object
op_star
id|target
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_load_table_op
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_operand_object
op_star
op_star
id|return_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_unload_table
(paren
id|acpi_operand_object
op_star
id|ddb_handle
)paren
suffix:semicolon
multiline_comment|/*&n; * exmutex - mutex support&n; */
id|acpi_status
id|acpi_ex_acquire_mutex
(paren
id|acpi_operand_object
op_star
id|time_desc
comma
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_release_mutex
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
r_void
id|acpi_ex_release_all_mutexes
(paren
id|ACPI_THREAD_STATE
op_star
id|thread
)paren
suffix:semicolon
r_void
id|acpi_ex_unlink_mutex
(paren
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
r_void
id|acpi_ex_link_mutex
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|ACPI_THREAD_STATE
op_star
id|thread
)paren
suffix:semicolon
multiline_comment|/*&n; * exprep - ACPI AML (p-code) execution - prep utilities&n; */
id|acpi_status
id|acpi_ex_prep_common_field_object
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|u8
id|field_flags
comma
id|u8
id|field_attribute
comma
id|u32
id|field_bit_position
comma
id|u32
id|field_bit_length
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_prep_field_value
(paren
id|ACPI_CREATE_FIELD_INFO
op_star
id|info
)paren
suffix:semicolon
multiline_comment|/*&n; * exsystem - Interface to OS services&n; */
id|acpi_status
id|acpi_ex_system_do_notify_op
(paren
id|acpi_operand_object
op_star
id|value
comma
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_system_do_suspend
c_func
(paren
id|u32
id|time
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_system_do_stall
(paren
id|u32
id|time
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_system_acquire_mutex
c_func
(paren
id|acpi_operand_object
op_star
id|time
comma
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_system_release_mutex
c_func
(paren
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_system_signal_event
c_func
(paren
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_system_wait_event
c_func
(paren
id|acpi_operand_object
op_star
id|time
comma
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_system_reset_event
c_func
(paren
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_system_wait_semaphore
(paren
id|acpi_handle
id|semaphore
comma
id|u16
id|timeout
)paren
suffix:semicolon
multiline_comment|/*&n; * exmonadic - ACPI AML (p-code) execution, monadic operators&n; */
id|acpi_status
id|acpi_ex_opcode_1A_0T_0R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_opcode_1A_0T_1R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_opcode_1A_1T_1R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_opcode_1A_1T_0R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n; * exdyadic - ACPI AML (p-code) execution, dyadic operators&n; */
id|acpi_status
id|acpi_ex_opcode_2A_0T_0R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_opcode_2A_0T_1R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_opcode_2A_1T_1R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_opcode_2A_2T_1R
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n; * exresolv  - Object resolution and get value functions&n; */
id|acpi_status
id|acpi_ex_resolve_to_value
(paren
id|acpi_operand_object
op_star
op_star
id|stack_ptr
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_resolve_node_to_value
(paren
id|acpi_namespace_node
op_star
op_star
id|stack_ptr
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_resolve_object_to_value
(paren
id|acpi_operand_object
op_star
op_star
id|stack_ptr
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n; * exdump - Scanner debug output routines&n; */
r_void
id|acpi_ex_dump_operand
(paren
id|acpi_operand_object
op_star
id|entry_desc
)paren
suffix:semicolon
r_void
id|acpi_ex_dump_operands
(paren
id|acpi_operand_object
op_star
op_star
id|operands
comma
id|acpi_interpreter_mode
id|interpreter_mode
comma
id|NATIVE_CHAR
op_star
id|ident
comma
id|u32
id|num_levels
comma
id|NATIVE_CHAR
op_star
id|note
comma
id|NATIVE_CHAR
op_star
id|module_name
comma
id|u32
id|line_number
)paren
suffix:semicolon
r_void
id|acpi_ex_dump_object_descriptor
(paren
id|acpi_operand_object
op_star
id|object
comma
id|u32
id|flags
)paren
suffix:semicolon
r_void
id|acpi_ex_dump_node
(paren
id|acpi_namespace_node
op_star
id|node
comma
id|u32
id|flags
)paren
suffix:semicolon
r_void
id|acpi_ex_out_string
(paren
r_char
op_star
id|title
comma
r_char
op_star
id|value
)paren
suffix:semicolon
r_void
id|acpi_ex_out_pointer
(paren
r_char
op_star
id|title
comma
r_void
op_star
id|value
)paren
suffix:semicolon
r_void
id|acpi_ex_out_integer
(paren
r_char
op_star
id|title
comma
id|u32
id|value
)paren
suffix:semicolon
r_void
id|acpi_ex_out_address
(paren
r_char
op_star
id|title
comma
id|ACPI_PHYSICAL_ADDRESS
id|value
)paren
suffix:semicolon
multiline_comment|/*&n; * exnames - interpreter/scanner name load/execute&n; */
id|NATIVE_CHAR
op_star
id|acpi_ex_allocate_name_string
(paren
id|u32
id|prefix_count
comma
id|u32
id|num_name_segs
)paren
suffix:semicolon
id|u32
id|acpi_ex_good_char
(paren
id|u32
id|character
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_name_segment
(paren
id|u8
op_star
op_star
id|in_aml_address
comma
id|NATIVE_CHAR
op_star
id|name_string
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_get_name_string
(paren
id|acpi_object_type
id|data_type
comma
id|u8
op_star
id|in_aml_address
comma
id|NATIVE_CHAR
op_star
op_star
id|out_name_string
comma
id|u32
op_star
id|out_name_length
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_do_name
(paren
id|acpi_object_type
id|data_type
comma
id|acpi_interpreter_mode
id|load_exec_mode
)paren
suffix:semicolon
multiline_comment|/*&n; * exstore - Object store support&n; */
id|acpi_status
id|acpi_ex_store
(paren
id|acpi_operand_object
op_star
id|val_desc
comma
id|acpi_operand_object
op_star
id|dest_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_store_object_to_index
(paren
id|acpi_operand_object
op_star
id|val_desc
comma
id|acpi_operand_object
op_star
id|dest_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_store_object_to_node
(paren
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n; * exstoren&n; */
id|acpi_status
id|acpi_ex_resolve_object
(paren
id|acpi_operand_object
op_star
op_star
id|source_desc_ptr
comma
id|acpi_object_type
id|target_type
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_store_object_to_object
(paren
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_operand_object
op_star
id|dest_desc
comma
id|acpi_operand_object
op_star
op_star
id|new_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n; * excopy - object copy&n; */
id|acpi_status
id|acpi_ex_store_buffer_to_buffer
(paren
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_operand_object
op_star
id|target_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_store_string_to_string
(paren
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_operand_object
op_star
id|target_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_copy_integer_to_index_field
(paren
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_operand_object
op_star
id|target_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_copy_integer_to_bank_field
(paren
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_operand_object
op_star
id|target_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_copy_data_to_named_field
(paren
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_copy_integer_to_buffer_field
(paren
id|acpi_operand_object
op_star
id|source_desc
comma
id|acpi_operand_object
op_star
id|target_desc
)paren
suffix:semicolon
multiline_comment|/*&n; * exutils - interpreter/scanner utilities&n; */
id|acpi_status
id|acpi_ex_enter_interpreter
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_ex_exit_interpreter
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_ex_truncate_for32bit_table
(paren
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
id|u8
id|acpi_ex_acquire_global_lock
(paren
id|u32
id|rule
)paren
suffix:semicolon
r_void
id|acpi_ex_release_global_lock
(paren
id|u8
id|locked
)paren
suffix:semicolon
id|u32
id|acpi_ex_digits_needed
(paren
id|acpi_integer
id|value
comma
id|u32
id|base
)paren
suffix:semicolon
r_void
id|acpi_ex_eisa_id_to_string
(paren
id|u32
id|numeric_id
comma
id|NATIVE_CHAR
op_star
id|out_string
)paren
suffix:semicolon
r_void
id|acpi_ex_unsigned_integer_to_string
(paren
id|acpi_integer
id|value
comma
id|NATIVE_CHAR
op_star
id|out_string
)paren
suffix:semicolon
multiline_comment|/*&n; * exregion - default Op_region handlers&n; */
id|acpi_status
id|acpi_ex_system_memory_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|acpi_integer
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_system_io_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|acpi_integer
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_pci_config_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|acpi_integer
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_cmos_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|acpi_integer
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_pci_bar_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|acpi_integer
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_embedded_controller_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|acpi_integer
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_sm_bus_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|acpi_integer
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
suffix:semicolon
id|acpi_status
id|acpi_ex_data_table_space_handler
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|acpi_integer
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
suffix:semicolon
macro_line|#endif /* __INTERP_H__ */
eof
