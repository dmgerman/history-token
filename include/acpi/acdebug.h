multiline_comment|/******************************************************************************&n; *&n; * Name: acdebug.h - ACPI/AML debugger&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACDEBUG_H__
DECL|macro|__ACDEBUG_H__
mdefine_line|#define __ACDEBUG_H__
DECL|macro|ACPI_DEBUG_BUFFER_SIZE
mdefine_line|#define ACPI_DEBUG_BUFFER_SIZE  4196
DECL|struct|command_info
r_struct
id|command_info
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Command Name */
DECL|member|min_args
id|u8
id|min_args
suffix:semicolon
multiline_comment|/* Minimum arguments required */
)brace
suffix:semicolon
DECL|struct|argument_info
r_struct
id|argument_info
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
multiline_comment|/* Argument Name */
)brace
suffix:semicolon
DECL|macro|PARAM_LIST
mdefine_line|#define PARAM_LIST(pl)                  pl
DECL|macro|DBTEST_OUTPUT_LEVEL
mdefine_line|#define DBTEST_OUTPUT_LEVEL(lvl)        if (acpi_gbl_db_opt_verbose)
DECL|macro|VERBOSE_PRINT
mdefine_line|#define VERBOSE_PRINT(fp)               DBTEST_OUTPUT_LEVEL(lvl) {&bslash;&n;&t;&t;&t;  acpi_os_printf PARAM_LIST(fp);}
DECL|macro|EX_NO_SINGLE_STEP
mdefine_line|#define EX_NO_SINGLE_STEP               1
DECL|macro|EX_SINGLE_STEP
mdefine_line|#define EX_SINGLE_STEP                  2
multiline_comment|/* Prototypes */
multiline_comment|/*&n; * dbxface - external debugger interfaces&n; */
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
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|op_type
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_start_command
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_db_method_end
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n; * dbcmds - debug commands and output routines&n; */
r_void
id|acpi_db_display_table_info
(paren
r_char
op_star
id|table_arg
)paren
suffix:semicolon
r_void
id|acpi_db_unload_acpi_table
(paren
r_char
op_star
id|table_arg
comma
r_char
op_star
id|instance_arg
)paren
suffix:semicolon
r_void
id|acpi_db_set_method_breakpoint
(paren
r_char
op_star
id|location
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_db_set_method_call_breakpoint
(paren
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_db_disassemble_aml
(paren
r_char
op_star
id|statements
comma
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_db_dump_namespace
(paren
r_char
op_star
id|start_arg
comma
r_char
op_star
id|depth_arg
)paren
suffix:semicolon
r_void
id|acpi_db_dump_namespace_by_owner
(paren
r_char
op_star
id|owner_arg
comma
r_char
op_star
id|depth_arg
)paren
suffix:semicolon
r_void
id|acpi_db_send_notify
(paren
r_char
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
r_char
op_star
id|type_arg
comma
r_char
op_star
id|index_arg
comma
r_char
op_star
id|value_arg
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_display_objects
(paren
r_char
op_star
id|obj_type_arg
comma
r_char
op_star
id|display_count_arg
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_find_name_in_namespace
(paren
r_char
op_star
id|name_arg
)paren
suffix:semicolon
r_void
id|acpi_db_set_scope
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
r_void
id|acpi_db_find_references
(paren
r_char
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
r_char
op_star
id|object_arg
)paren
suffix:semicolon
r_void
id|acpi_db_display_gpes
(paren
r_void
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
r_void
id|acpi_db_generate_gpe
(paren
r_char
op_star
id|gpe_arg
comma
r_char
op_star
id|block_arg
)paren
suffix:semicolon
multiline_comment|/*&n; * dbdisply - debug display commands&n; */
r_void
id|acpi_db_display_method_info
(paren
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_db_decode_and_display_object
(paren
r_char
op_star
id|target
comma
r_char
op_star
id|output_type
)paren
suffix:semicolon
r_void
id|acpi_db_display_result_object
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_display_all_methods
(paren
r_char
op_star
id|display_count_arg
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
id|acpi_db_display_object_type
(paren
r_char
op_star
id|object_arg
)paren
suffix:semicolon
r_void
id|acpi_db_display_argument_object
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
r_void
id|acpi_db_dump_parser_descriptor
(paren
r_union
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
multiline_comment|/*&n; * dbexec - debugger control method execution&n; */
r_void
id|acpi_db_execute
(paren
r_char
op_star
id|name
comma
r_char
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
r_char
op_star
id|num_threads_arg
comma
r_char
op_star
id|num_loops_arg
comma
r_char
op_star
id|method_name_arg
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_execute_method
(paren
r_struct
id|acpi_db_method_info
op_star
id|info
comma
r_struct
id|acpi_buffer
op_star
id|return_obj
)paren
suffix:semicolon
r_void
id|acpi_db_execute_setup
(paren
r_struct
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
id|acpi_status
id|acpi_db_execution_walk
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
multiline_comment|/*&n; * dbfileio - Debugger file I/O commands&n; */
id|acpi_object_type
id|acpi_db_match_argument
(paren
r_char
op_star
id|user_argument
comma
r_struct
id|argument_info
op_star
id|arguments
)paren
suffix:semicolon
id|acpi_status
id|ae_local_load_table
(paren
r_struct
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
r_char
op_star
id|name
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_load_acpi_table
(paren
r_char
op_star
id|filename
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_get_table_from_file
(paren
r_char
op_star
id|filename
comma
r_struct
id|acpi_table_header
op_star
op_star
id|table
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_read_table_from_file
(paren
r_char
op_star
id|filename
comma
r_struct
id|acpi_table_header
op_star
op_star
id|table
)paren
suffix:semicolon
multiline_comment|/*&n; * dbhistry - debugger HISTORY command&n; */
r_void
id|acpi_db_add_to_history
(paren
r_char
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
r_char
op_star
id|acpi_db_get_from_history
(paren
r_char
op_star
id|command_num_arg
)paren
suffix:semicolon
multiline_comment|/*&n; * dbinput - user front-end to the AML debugger&n; */
id|acpi_status
id|acpi_db_command_dispatch
(paren
r_char
op_star
id|input_buffer
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
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
r_char
id|prompt
comma
r_union
id|acpi_parse_object
op_star
id|op
)paren
suffix:semicolon
r_void
id|acpi_db_display_help
(paren
r_char
op_star
id|help_type
)paren
suffix:semicolon
r_char
op_star
id|acpi_db_get_next_token
(paren
r_char
op_star
id|string
comma
r_char
op_star
op_star
id|next
)paren
suffix:semicolon
id|u32
id|acpi_db_get_line
(paren
r_char
op_star
id|input_buffer
)paren
suffix:semicolon
id|u32
id|acpi_db_match_command
(paren
r_char
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
r_union
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
r_char
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
r_union
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
r_union
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
r_char
op_star
id|name
)paren
suffix:semicolon
id|acpi_status
id|acpi_db_second_pass_parse
(paren
r_union
id|acpi_parse_object
op_star
id|root
)paren
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|acpi_db_local_ns_lookup
(paren
r_char
op_star
id|name
)paren
suffix:semicolon
macro_line|#endif  /* __ACDEBUG_H__ */
eof
