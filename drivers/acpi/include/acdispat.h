multiline_comment|/******************************************************************************&n; *&n; * Name: acdispat.h - dispatcher (parser to interpreter interface)&n; *       $Revision: 40 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _ACDISPAT_H_
DECL|macro|_ACDISPAT_H_
mdefine_line|#define _ACDISPAT_H_
DECL|macro|NAMEOF_LOCAL_NTE
mdefine_line|#define NAMEOF_LOCAL_NTE    &quot;__L0&quot;
DECL|macro|NAMEOF_ARG_NTE
mdefine_line|#define NAMEOF_ARG_NTE      &quot;__A0&quot;
multiline_comment|/* Common interfaces */
id|ACPI_STATUS
id|acpi_ds_obj_stack_push
(paren
r_void
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_obj_stack_pop
(paren
id|u32
id|pop_count
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
r_void
op_star
id|acpi_ds_obj_stack_get_value
(paren
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_obj_stack_pop_object
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/* dsopcode - support for late evaluation */
id|ACPI_STATUS
id|acpi_ds_get_buffer_field_arguments
(paren
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_get_region_arguments
(paren
id|ACPI_OPERAND_OBJECT
op_star
id|rgn_desc
)paren
suffix:semicolon
multiline_comment|/* dsctrl - Parser/Interpreter interface, control stack routines */
id|ACPI_STATUS
id|acpi_ds_exec_begin_control_op
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_exec_end_control_op
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
suffix:semicolon
multiline_comment|/* dsexec - Parser/Interpreter interface, method execution callbacks */
id|ACPI_STATUS
id|acpi_ds_get_predicate_value
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|u32
id|has_result_obj
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_exec_begin_op
(paren
id|u16
id|opcode
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
op_star
id|out_op
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_exec_end_op
(paren
id|ACPI_WALK_STATE
op_star
id|state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
suffix:semicolon
multiline_comment|/* dsfield - Parser/Interpreter interface for AML fields */
id|ACPI_STATUS
id|acpi_ds_create_field
(paren
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_NAMESPACE_NODE
op_star
id|region_node
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_create_bank_field
(paren
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_NAMESPACE_NODE
op_star
id|region_node
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_create_index_field
(paren
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_NAMESPACE_NODE
op_star
id|region_node
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/* dsload - Parser/Interpreter interface, namespace load callbacks */
id|ACPI_STATUS
id|acpi_ds_load1_begin_op
(paren
id|u16
id|opcode
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
op_star
id|out_op
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_load1_end_op
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_load2_begin_op
(paren
id|u16
id|opcode
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
op_star
id|out_op
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_load2_end_op
(paren
id|ACPI_WALK_STATE
op_star
id|state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_load3_begin_op
(paren
id|u16
id|opcode
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
op_star
id|out_op
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_load3_end_op
(paren
id|ACPI_WALK_STATE
op_star
id|state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
suffix:semicolon
multiline_comment|/* dsmthdat - method data (locals/args) */
id|ACPI_STATUS
id|acpi_ds_store_object_to_local
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_OPERAND_OBJECT
op_star
id|src_desc
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_method_data_get_entry
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
op_star
id|node
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_method_data_delete_all
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|u8
id|acpi_ds_is_method_value
(paren
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
)paren
suffix:semicolon
id|ACPI_OBJECT_TYPE8
id|acpi_ds_method_data_get_type
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_method_data_get_value
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|dest_desc
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_method_data_delete_value
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_method_data_init_args
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|params
comma
id|u32
id|max_param_count
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_NAMESPACE_NODE
op_star
id|acpi_ds_method_data_get_node
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_method_data_init
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_method_data_set_entry
(paren
id|u16
id|opcode
comma
id|u32
id|index
comma
id|ACPI_OPERAND_OBJECT
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/* dsmethod - Parser/Interpreter interface - control method parsing */
id|ACPI_STATUS
id|acpi_ds_parse_method
(paren
id|ACPI_HANDLE
id|obj_handle
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_call_control_method
(paren
id|ACPI_WALK_LIST
op_star
id|walk_list
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_restart_control_method
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_OPERAND_OBJECT
op_star
id|return_desc
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_terminate_control_method
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_begin_method_execution
(paren
id|ACPI_NAMESPACE_NODE
op_star
id|method_node
comma
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
comma
id|ACPI_NAMESPACE_NODE
op_star
id|calling_method_node
)paren
suffix:semicolon
multiline_comment|/* dsobj - Parser/Interpreter interface - object initialization and conversion */
id|ACPI_STATUS
id|acpi_ds_init_one_object
(paren
id|ACPI_HANDLE
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
id|ACPI_STATUS
id|acpi_ds_initialize_objects
(paren
id|ACPI_TABLE_DESC
op_star
id|table_desc
comma
id|ACPI_NAMESPACE_NODE
op_star
id|start_node
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_build_internal_package_obj
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|obj_desc
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_build_internal_object
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|obj_desc_ptr
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_init_object_from_op
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|u16
id|opcode
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|obj_desc
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_create_node
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_NAMESPACE_NODE
op_star
id|node
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
suffix:semicolon
multiline_comment|/* dsregn - Parser/Interpreter interface - Op Region parsing */
id|ACPI_STATUS
id|acpi_ds_eval_buffer_field_operands
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_eval_region_operands
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_initialize_region
(paren
id|ACPI_HANDLE
id|obj_handle
)paren
suffix:semicolon
multiline_comment|/* dsutils - Parser/Interpreter interface utility routines */
id|u8
id|acpi_ds_is_result_used
(paren
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
r_void
id|acpi_ds_delete_result_if_not_used
(paren
id|ACPI_PARSE_OBJECT
op_star
id|op
comma
id|ACPI_OPERAND_OBJECT
op_star
id|result_obj
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_create_operand
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|arg
comma
id|u32
id|args_remaining
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_create_operands
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_PARSE_OBJECT
op_star
id|first_arg
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_resolve_operands
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_OBJECT_TYPE8
id|acpi_ds_map_opcode_to_data_type
(paren
id|u16
id|opcode
comma
id|u32
op_star
id|out_flags
)paren
suffix:semicolon
id|ACPI_OBJECT_TYPE8
id|acpi_ds_map_named_opcode_to_data_type
(paren
id|u16
id|opcode
)paren
suffix:semicolon
multiline_comment|/*&n; * dswscope - Scope Stack manipulation&n; */
id|ACPI_STATUS
id|acpi_ds_scope_stack_push
(paren
id|ACPI_NAMESPACE_NODE
op_star
id|node
comma
id|ACPI_OBJECT_TYPE8
id|type
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_scope_stack_pop
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
r_void
id|acpi_ds_scope_stack_clear
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/* Acpi_dswstate - parser WALK_STATE management routines */
id|ACPI_WALK_STATE
op_star
id|acpi_ds_create_walk_state
(paren
id|ACPI_OWNER_ID
id|owner_id
comma
id|ACPI_PARSE_OBJECT
op_star
id|origin
comma
id|ACPI_OPERAND_OBJECT
op_star
id|mth_desc
comma
id|ACPI_WALK_LIST
op_star
id|walk_list
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_obj_stack_delete_all
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_obj_stack_pop_and_delete
(paren
id|u32
id|pop_count
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
r_void
id|acpi_ds_delete_walk_state
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_WALK_STATE
op_star
id|acpi_ds_pop_walk_state
(paren
id|ACPI_WALK_LIST
op_star
id|walk_list
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_result_stack_pop
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_result_stack_push
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_result_stack_clear
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_WALK_STATE
op_star
id|acpi_ds_get_current_walk_state
(paren
id|ACPI_WALK_LIST
op_star
id|walk_list
)paren
suffix:semicolon
r_void
id|acpi_ds_delete_walk_state_cache
(paren
r_void
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_result_insert
(paren
r_void
op_star
id|object
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_result_remove
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|object
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_result_pop
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_result_push
(paren
id|ACPI_OPERAND_OBJECT
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
id|ACPI_STATUS
id|acpi_ds_result_pop_from_bottom
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
suffix:semicolon
macro_line|#endif /* _ACDISPAT_H_ */
eof
