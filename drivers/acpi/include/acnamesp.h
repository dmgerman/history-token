multiline_comment|/******************************************************************************&n; *&n; * Name: acnamesp.h - Namespace subcomponent prototypes and defines&n; *       $Revision: 125 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACNAMESP_H__
DECL|macro|__ACNAMESP_H__
mdefine_line|#define __ACNAMESP_H__
multiline_comment|/* To search the entire name space, pass this as Search_base */
DECL|macro|ACPI_NS_ALL
mdefine_line|#define ACPI_NS_ALL                 ((acpi_handle)0)
multiline_comment|/*&n; * Elements of Acpi_ns_properties are bit significant&n; * and should be one-to-one with values of acpi_object_type&n; */
DECL|macro|ACPI_NS_NORMAL
mdefine_line|#define ACPI_NS_NORMAL              0
DECL|macro|ACPI_NS_NEWSCOPE
mdefine_line|#define ACPI_NS_NEWSCOPE            1   /* a definition of this type opens a name scope */
DECL|macro|ACPI_NS_LOCAL
mdefine_line|#define ACPI_NS_LOCAL               2   /* suppress search of enclosing scopes */
multiline_comment|/* Definitions of the predefined namespace names  */
DECL|macro|ACPI_UNKNOWN_NAME
mdefine_line|#define ACPI_UNKNOWN_NAME           (u32) 0x3F3F3F3F     /* Unknown name is  &quot;????&quot; */
DECL|macro|ACPI_ROOT_NAME
mdefine_line|#define ACPI_ROOT_NAME              (u32) 0x2F202020     /* Root name is     &quot;/   &quot; */
DECL|macro|ACPI_SYS_BUS_NAME
mdefine_line|#define ACPI_SYS_BUS_NAME           (u32) 0x5F53425F     /* Sys bus name is  &quot;_SB_&quot; */
DECL|macro|ACPI_NS_ROOT_PATH
mdefine_line|#define ACPI_NS_ROOT_PATH           &quot;&bslash;&bslash;&quot;
DECL|macro|ACPI_NS_SYSTEM_BUS
mdefine_line|#define ACPI_NS_SYSTEM_BUS          &quot;_SB_&quot;
multiline_comment|/* Flags for Acpi_ns_lookup, Acpi_ns_search_and_enter */
DECL|macro|ACPI_NS_NO_UPSEARCH
mdefine_line|#define ACPI_NS_NO_UPSEARCH         0
DECL|macro|ACPI_NS_SEARCH_PARENT
mdefine_line|#define ACPI_NS_SEARCH_PARENT       0x01
DECL|macro|ACPI_NS_DONT_OPEN_SCOPE
mdefine_line|#define ACPI_NS_DONT_OPEN_SCOPE     0x02
DECL|macro|ACPI_NS_NO_PEER_SEARCH
mdefine_line|#define ACPI_NS_NO_PEER_SEARCH      0x04
DECL|macro|ACPI_NS_ERROR_IF_FOUND
mdefine_line|#define ACPI_NS_ERROR_IF_FOUND      0x08
DECL|macro|ACPI_NS_WALK_UNLOCK
mdefine_line|#define ACPI_NS_WALK_UNLOCK         TRUE
DECL|macro|ACPI_NS_WALK_NO_UNLOCK
mdefine_line|#define ACPI_NS_WALK_NO_UNLOCK      FALSE
id|acpi_status
id|acpi_ns_load_namespace
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_initialize_objects
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_initialize_devices
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* Namespace init - nsxfinit */
id|acpi_status
id|acpi_ns_init_one_device
(paren
id|acpi_handle
id|obj_handle
comma
id|u32
id|nesting_level
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
id|acpi_ns_init_one_object
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
id|acpi_ns_walk_namespace
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
id|u8
id|unlock_before_callback
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
id|acpi_namespace_node
op_star
id|acpi_ns_get_next_node
(paren
id|acpi_object_type
id|type
comma
id|acpi_namespace_node
op_star
id|parent
comma
id|acpi_namespace_node
op_star
id|child
)paren
suffix:semicolon
r_void
id|acpi_ns_delete_namespace_by_owner
(paren
id|u16
id|table_id
)paren
suffix:semicolon
multiline_comment|/* Namespace loading - nsload */
id|acpi_status
id|acpi_ns_one_complete_parse
(paren
id|u32
id|pass_number
comma
id|acpi_table_desc
op_star
id|table_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_parse_table
(paren
id|acpi_table_desc
op_star
id|table_desc
comma
id|acpi_namespace_node
op_star
id|scope
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_load_table
(paren
id|acpi_table_desc
op_star
id|table_desc
comma
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_load_table_by_type
(paren
id|acpi_table_type
id|table_type
)paren
suffix:semicolon
multiline_comment|/*&n; * Top-level namespace access - nsaccess&n; */
id|acpi_status
id|acpi_ns_root_initialize
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_lookup
(paren
id|acpi_generic_state
op_star
id|scope_info
comma
id|NATIVE_CHAR
op_star
id|name
comma
id|acpi_object_type
id|type
comma
id|acpi_interpreter_mode
id|interpreter_mode
comma
id|u32
id|flags
comma
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_namespace_node
op_star
op_star
id|ret_node
)paren
suffix:semicolon
multiline_comment|/*&n; * Named object allocation/deallocation - nsalloc&n; */
id|acpi_namespace_node
op_star
id|acpi_ns_create_node
(paren
id|u32
id|name
)paren
suffix:semicolon
r_void
id|acpi_ns_delete_node
(paren
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
r_void
id|acpi_ns_delete_namespace_subtree
(paren
id|acpi_namespace_node
op_star
id|parent_handle
)paren
suffix:semicolon
r_void
id|acpi_ns_detach_object
(paren
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
r_void
id|acpi_ns_delete_children
(paren
id|acpi_namespace_node
op_star
id|parent
)paren
suffix:semicolon
multiline_comment|/*&n; * Namespace modification - nsmodify&n; */
id|acpi_status
id|acpi_ns_unload_namespace
(paren
id|acpi_handle
id|handle
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_delete_subtree
(paren
id|acpi_handle
id|start_handle
)paren
suffix:semicolon
multiline_comment|/*&n; * Namespace dump/print utilities - nsdump&n; */
r_void
id|acpi_ns_dump_tables
(paren
id|acpi_handle
id|search_base
comma
id|u32
id|max_depth
)paren
suffix:semicolon
r_void
id|acpi_ns_dump_entry
(paren
id|acpi_handle
id|handle
comma
id|u32
id|debug_level
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_dump_pathname
(paren
id|acpi_handle
id|handle
comma
id|NATIVE_CHAR
op_star
id|msg
comma
id|u32
id|level
comma
id|u32
id|component
)paren
suffix:semicolon
r_void
id|acpi_ns_print_pathname
(paren
id|u32
id|num_segments
comma
r_char
op_star
id|pathname
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_dump_one_device
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
r_void
id|acpi_ns_dump_root_devices
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_dump_one_object
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
r_void
id|acpi_ns_dump_objects
(paren
id|acpi_object_type
id|type
comma
id|u8
id|display_type
comma
id|u32
id|max_depth
comma
id|u32
id|ownder_id
comma
id|acpi_handle
id|start_handle
)paren
suffix:semicolon
multiline_comment|/*&n; * Namespace evaluation functions - nseval&n; */
id|acpi_status
id|acpi_ns_evaluate_by_handle
(paren
id|acpi_namespace_node
op_star
id|prefix_node
comma
id|acpi_operand_object
op_star
op_star
id|params
comma
id|acpi_operand_object
op_star
op_star
id|return_object
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_evaluate_by_name
(paren
id|NATIVE_CHAR
op_star
id|pathname
comma
id|acpi_operand_object
op_star
op_star
id|params
comma
id|acpi_operand_object
op_star
op_star
id|return_object
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_evaluate_relative
(paren
id|acpi_namespace_node
op_star
id|prefix_node
comma
id|NATIVE_CHAR
op_star
id|pathname
comma
id|acpi_operand_object
op_star
op_star
id|params
comma
id|acpi_operand_object
op_star
op_star
id|return_object
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_execute_control_method
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
id|acpi_status
id|acpi_ns_get_object_value
(paren
id|acpi_namespace_node
op_star
id|object_node
comma
id|acpi_operand_object
op_star
op_star
id|return_obj_desc
)paren
suffix:semicolon
multiline_comment|/*&n; * Parent/Child/Peer utility functions - nsfamily&n; */
id|acpi_name
id|acpi_ns_find_parent_name
(paren
id|acpi_namespace_node
op_star
id|node_to_search
)paren
suffix:semicolon
id|u8
id|acpi_ns_exist_downstream_sibling
(paren
id|acpi_namespace_node
op_star
id|this_node
)paren
suffix:semicolon
multiline_comment|/*&n; * Name and Scope manipulation - nsnames&n; */
id|u32
id|acpi_ns_opens_scope
(paren
id|acpi_object_type
id|type
)paren
suffix:semicolon
r_void
id|acpi_ns_build_external_path
(paren
id|acpi_namespace_node
op_star
id|node
comma
id|ACPI_SIZE
id|size
comma
id|NATIVE_CHAR
op_star
id|name_buffer
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_ns_get_external_pathname
(paren
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_ns_name_of_current_scope
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_handle_to_pathname
(paren
id|acpi_handle
id|target_handle
comma
id|acpi_buffer
op_star
id|buffer
)paren
suffix:semicolon
id|u8
id|acpi_ns_pattern_match
(paren
id|acpi_namespace_node
op_star
id|obj_node
comma
id|NATIVE_CHAR
op_star
id|search_for
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_get_node_by_path
(paren
id|NATIVE_CHAR
op_star
id|external_pathname
comma
id|acpi_namespace_node
op_star
id|in_prefix_node
comma
id|u32
id|flags
comma
id|acpi_namespace_node
op_star
op_star
id|out_node
)paren
suffix:semicolon
id|ACPI_SIZE
id|acpi_ns_get_pathname_length
(paren
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
multiline_comment|/*&n; * Object management for namespace nodes - nsobject&n; */
id|acpi_status
id|acpi_ns_attach_object
(paren
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_operand_object
op_star
id|object
comma
id|acpi_object_type
id|type
)paren
suffix:semicolon
id|acpi_operand_object
op_star
id|acpi_ns_get_attached_object
(paren
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
id|acpi_operand_object
op_star
id|acpi_ns_get_secondary_object
(paren
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_attach_data
(paren
id|acpi_namespace_node
op_star
id|node
comma
id|ACPI_OBJECT_HANDLER
id|handler
comma
r_void
op_star
id|data
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_detach_data
(paren
id|acpi_namespace_node
op_star
id|node
comma
id|ACPI_OBJECT_HANDLER
id|handler
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_get_attached_data
(paren
id|acpi_namespace_node
op_star
id|node
comma
id|ACPI_OBJECT_HANDLER
id|handler
comma
r_void
op_star
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/*&n; * Namespace searching and entry - nssearch&n; */
id|acpi_status
id|acpi_ns_search_and_enter
(paren
id|u32
id|entry_name
comma
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_interpreter_mode
id|interpreter_mode
comma
id|acpi_object_type
id|type
comma
id|u32
id|flags
comma
id|acpi_namespace_node
op_star
op_star
id|ret_node
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_search_node
(paren
id|u32
id|entry_name
comma
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_object_type
id|type
comma
id|acpi_namespace_node
op_star
op_star
id|ret_node
)paren
suffix:semicolon
r_void
id|acpi_ns_install_node
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_namespace_node
op_star
id|parent_node
comma
multiline_comment|/* Parent */
id|acpi_namespace_node
op_star
id|node
comma
multiline_comment|/* New Child*/
id|acpi_object_type
id|type
)paren
suffix:semicolon
multiline_comment|/*&n; * Utility functions - nsutils&n; */
id|u8
id|acpi_ns_valid_root_prefix
(paren
id|NATIVE_CHAR
id|prefix
)paren
suffix:semicolon
id|u8
id|acpi_ns_valid_path_separator
(paren
id|NATIVE_CHAR
id|sep
)paren
suffix:semicolon
id|acpi_object_type
id|acpi_ns_get_type
(paren
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
id|u32
id|acpi_ns_local
(paren
id|acpi_object_type
id|type
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_build_internal_name
(paren
id|acpi_namestring_info
op_star
id|info
)paren
suffix:semicolon
r_void
id|acpi_ns_get_internal_name_length
(paren
id|acpi_namestring_info
op_star
id|info
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_internalize_name
(paren
id|NATIVE_CHAR
op_star
id|dotted_name
comma
id|NATIVE_CHAR
op_star
op_star
id|converted_name
)paren
suffix:semicolon
id|acpi_status
id|acpi_ns_externalize_name
(paren
id|u32
id|internal_name_length
comma
id|NATIVE_CHAR
op_star
id|internal_name
comma
id|u32
op_star
id|converted_name_length
comma
id|NATIVE_CHAR
op_star
op_star
id|converted_name
)paren
suffix:semicolon
id|acpi_namespace_node
op_star
id|acpi_ns_map_handle_to_node
(paren
id|acpi_handle
id|handle
)paren
suffix:semicolon
id|acpi_handle
id|acpi_ns_convert_entry_to_handle
c_func
(paren
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
r_void
id|acpi_ns_terminate
(paren
r_void
)paren
suffix:semicolon
id|acpi_namespace_node
op_star
id|acpi_ns_get_parent_node
(paren
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
id|acpi_namespace_node
op_star
id|acpi_ns_get_next_valid_node
(paren
id|acpi_namespace_node
op_star
id|node
)paren
suffix:semicolon
macro_line|#endif /* __ACNAMESP_H__ */
eof
