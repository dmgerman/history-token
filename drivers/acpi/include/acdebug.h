multiline_comment|/******************************************************************************&n; *&n; * Name: acdebug.h - ACPI/AML debugger&n; *       $Revision: 63 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACDEBUG_H__
DECL|macro|__ACDEBUG_H__
mdefine_line|#define __ACDEBUG_H__
DECL|macro|ACPI_DEBUG_BUFFER_SIZE
mdefine_line|#define ACPI_DEBUG_BUFFER_SIZE  4196
DECL|struct|command_info
r_typedef
r_struct
id|command_info
(brace
DECL|member|name
id|NATIVE_CHAR
op_star
id|name
suffix:semicolon
multiline_comment|/* Command Name */
DECL|member|min_args
id|u8
id|min_args
suffix:semicolon
multiline_comment|/* Minimum arguments required */
DECL|typedef|COMMAND_INFO
)brace
id|COMMAND_INFO
suffix:semicolon
DECL|struct|argument_info
r_typedef
r_struct
id|argument_info
(brace
DECL|member|name
id|NATIVE_CHAR
op_star
id|name
suffix:semicolon
multiline_comment|/* Argument Name */
DECL|typedef|ARGUMENT_INFO
)brace
id|ARGUMENT_INFO
suffix:semicolon
DECL|macro|PARAM_LIST
mdefine_line|#define PARAM_LIST(pl)                  pl
DECL|macro|DBTEST_OUTPUT_LEVEL
mdefine_line|#define DBTEST_OUTPUT_LEVEL(lvl)        if (acpi_gbl_db_opt_verbose)
DECL|macro|VERBOSE_PRINT
mdefine_line|#define VERBOSE_PRINT(fp)               DBTEST_OUTPUT_LEVEL(lvl) {&bslash;&n;&t;&t;&t;  acpi_os_printf PARAM_LIST(fp);}
DECL|macro|EX_NO_SINGLE_STEP
mdefine_line|#define EX_NO_SINGLE_STEP       1
DECL|macro|EX_SINGLE_STEP
mdefine_line|#define EX_SINGLE_STEP          2
multiline_comment|/* Prototypes */
multiline_comment|/*&n; * dbapi - external debugger interfaces&n; */
id|acpi_status
id|acpi_db_initialize
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_db_terminate
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_single_step
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|op_type
)paren
suffix:semicolon
multiline_comment|/*&n; * dbcmds - debug commands and output routines&n; */
r_void
id|acpi_db_display_table_info
(paren
id|NATIVE_CHAR
op_star
id|table_arg
)paren
suffix:semicolon
r_void
id|acpi_db_unload_acpi_table
(paren
id|NATIVE_CHAR
op_star
id|table_arg
comma
id|NATIVE_CHAR
op_star
id|instance_arg
)paren
suffix:semicolon
r_void
id|acpi_db_set_method_breakpoint
(paren
id|NATIVE_CHAR
op_star
id|location
comma
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_db_set_method_call_breakpoint
(paren
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_db_disassemble_aml
(paren
id|NATIVE_CHAR
op_star
id|statements
comma
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_db_dump_namespace
(paren
id|NATIVE_CHAR
op_star
id|start_arg
comma
id|NATIVE_CHAR
op_star
id|depth_arg
)paren
suffix:semicolon
r_void
id|acpi_db_dump_namespace_by_owner
(paren
id|NATIVE_CHAR
op_star
id|owner_arg
comma
id|NATIVE_CHAR
op_star
id|depth_arg
)paren
suffix:semicolon
r_void
id|acpi_db_send_notify
(paren
id|NATIVE_CHAR
op_star
id|name
comma
id|u32
id|value
)paren
suffix:semicolon
r_void
id|acpi_db_set_method_data
(paren
id|NATIVE_CHAR
op_star
id|type_arg
comma
id|NATIVE_CHAR
op_star
id|index_arg
comma
id|NATIVE_CHAR
op_star
id|value_arg
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_display_objects
(paren
id|NATIVE_CHAR
op_star
id|obj_type_arg
comma
id|NATIVE_CHAR
op_star
id|display_count_arg
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_find_name_in_namespace
(paren
id|NATIVE_CHAR
op_star
id|name_arg
)paren
suffix:semicolon
r_void
id|acpi_db_set_scope
(paren
id|NATIVE_CHAR
op_star
id|name
)paren
suffix:semicolon
r_void
id|acpi_db_find_references
(paren
id|NATIVE_CHAR
op_star
id|object_arg
)paren
suffix:semicolon
r_void
id|acpi_db_display_locks
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_db_display_resources
(paren
id|NATIVE_CHAR
op_star
id|object_arg
)paren
suffix:semicolon
r_void
id|acpi_db_check_integrity
(paren
r_void
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_integrity_walk
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
id|acpi_db_walk_and_match_name
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
id|acpi_db_walk_for_references
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
id|acpi_db_walk_for_specific_objects
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
multiline_comment|/*&n; * dbdisply - debug display commands&n; */
r_void
id|acpi_db_display_method_info
(paren
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_db_decode_and_display_object
(paren
id|NATIVE_CHAR
op_star
id|target
comma
id|NATIVE_CHAR
op_star
id|output_type
)paren
suffix:semicolon
r_void
id|acpi_db_display_result_object
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
id|acpi_status
id|acpi_db_display_all_methods
(paren
id|NATIVE_CHAR
op_star
id|display_count_arg
)paren
suffix:semicolon
r_void
id|acpi_db_display_internal_object
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
id|acpi_db_display_arguments
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_db_display_locals
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_db_display_results
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_db_display_calling_tree
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_db_display_argument_object
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
id|acpi_db_dump_parser_descriptor
(paren
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
op_star
id|acpi_db_get_pointer
(paren
r_void
op_star
id|target
)paren
suffix:semicolon
r_void
id|acpi_db_decode_internal_object
(paren
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
multiline_comment|/*&n; * dbexec - debugger control method execution&n; */
r_void
id|acpi_db_execute
(paren
id|NATIVE_CHAR
op_star
id|name
comma
id|NATIVE_CHAR
op_star
op_star
id|args
comma
id|u32
id|flags
)paren
suffix:semicolon
r_void
id|acpi_db_create_execution_threads
(paren
id|NATIVE_CHAR
op_star
id|num_threads_arg
comma
id|NATIVE_CHAR
op_star
id|num_loops_arg
comma
id|NATIVE_CHAR
op_star
id|method_name_arg
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_execute_method
(paren
id|acpi_db_method_info
op_star
id|info
comma
id|acpi_buffer
op_star
id|return_obj
)paren
suffix:semicolon
r_void
id|acpi_db_execute_setup
(paren
id|acpi_db_method_info
op_star
id|info
)paren
suffix:semicolon
id|u32
id|acpi_db_get_outstanding_allocations
(paren
r_void
)paren
suffix:semicolon
r_void
id|ACPI_SYSTEM_XFACE
id|acpi_db_method_thread
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
multiline_comment|/*&n; * dbfileio - Debugger file I/O commands&n; */
id|acpi_object_type
id|acpi_db_match_argument
(paren
id|NATIVE_CHAR
op_star
id|user_argument
comma
id|ARGUMENT_INFO
op_star
id|arguments
)paren
suffix:semicolon
id|acpi_status
id|ae_local_load_table
(paren
id|acpi_table_header
op_star
id|table_ptr
)paren
suffix:semicolon
r_void
id|acpi_db_close_debug_file
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_db_open_debug_file
(paren
id|NATIVE_CHAR
op_star
id|name
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_load_acpi_table
(paren
id|NATIVE_CHAR
op_star
id|filename
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_get_acpi_table
(paren
id|NATIVE_CHAR
op_star
id|filename
)paren
suffix:semicolon
multiline_comment|/*&n; * dbhistry - debugger HISTORY command&n; */
r_void
id|acpi_db_add_to_history
(paren
id|NATIVE_CHAR
op_star
id|command_line
)paren
suffix:semicolon
r_void
id|acpi_db_display_history
(paren
r_void
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_db_get_from_history
(paren
id|NATIVE_CHAR
op_star
id|command_num_arg
)paren
suffix:semicolon
multiline_comment|/*&n; * dbinput - user front-end to the AML debugger&n; */
id|acpi_status
id|acpi_db_command_dispatch
(paren
id|NATIVE_CHAR
op_star
id|input_buffer
comma
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|ACPI_SYSTEM_XFACE
id|acpi_db_execute_thread
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_user_commands
(paren
id|NATIVE_CHAR
id|prompt
comma
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_db_display_help
(paren
id|NATIVE_CHAR
op_star
id|help_type
)paren
suffix:semicolon
id|NATIVE_CHAR
op_star
id|acpi_db_get_next_token
(paren
id|NATIVE_CHAR
op_star
id|string
comma
id|NATIVE_CHAR
op_star
op_star
id|next
)paren
suffix:semicolon
id|u32
id|acpi_db_get_line
(paren
id|NATIVE_CHAR
op_star
id|input_buffer
)paren
suffix:semicolon
id|u32
id|acpi_db_match_command
(paren
id|NATIVE_CHAR
op_star
id|user_command
)paren
suffix:semicolon
r_void
id|acpi_db_single_thread
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * dbstats - Generation and display of ACPI table statistics&n; */
r_void
id|acpi_db_generate_statistics
(paren
id|acpi_parse_object
op_star
id|root
comma
id|u8
id|is_method
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_display_statistics
(paren
id|NATIVE_CHAR
op_star
id|type_arg
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_classify_one_object
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
r_void
id|acpi_db_count_namespace_objects
(paren
r_void
)paren
suffix:semicolon
r_void
id|acpi_db_enumerate_object
(paren
id|acpi_operand_object
op_star
id|obj_desc
)paren
suffix:semicolon
multiline_comment|/*&n; * dbutils - AML debugger utilities&n; */
r_void
id|acpi_db_set_output_destination
(paren
id|u32
id|where
)paren
suffix:semicolon
r_void
id|acpi_db_dump_buffer
(paren
id|u32
id|address
)paren
suffix:semicolon
r_void
id|acpi_db_dump_object
(paren
id|acpi_object
op_star
id|obj_desc
comma
id|u32
id|level
)paren
suffix:semicolon
r_void
id|acpi_db_prep_namestring
(paren
id|NATIVE_CHAR
op_star
id|name
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_second_pass_parse
(paren
id|acpi_parse_object
op_star
id|root
)paren
suffix:semicolon
id|acpi_namespace_node
op_star
id|acpi_db_local_ns_lookup
(paren
id|NATIVE_CHAR
op_star
id|name
)paren
suffix:semicolon
macro_line|#endif  /* __ACDEBUG_H__ */
eof
