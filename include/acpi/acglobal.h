multiline_comment|/******************************************************************************&n; *&n; * Name: acglobal.h - Declarations for global variables&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACGLOBAL_H__
DECL|macro|__ACGLOBAL_H__
mdefine_line|#define __ACGLOBAL_H__
multiline_comment|/*&n; * Ensure that the globals are actually defined only once.&n; *&n; * The use of these defines allows a single list of globals (here) in order&n; * to simplify maintenance of the code.&n; */
macro_line|#ifdef DEFINE_ACPI_GLOBALS
DECL|macro|ACPI_EXTERN
mdefine_line|#define ACPI_EXTERN
macro_line|#else
DECL|macro|ACPI_EXTERN
mdefine_line|#define ACPI_EXTERN extern
macro_line|#endif
multiline_comment|/*****************************************************************************&n; *&n; * Debug support&n; *&n; ****************************************************************************/
multiline_comment|/* Runtime configuration of debug print levels */
r_extern
id|u32
id|acpi_dbg_level
suffix:semicolon
r_extern
id|u32
id|acpi_dbg_layer
suffix:semicolon
multiline_comment|/* Procedure nesting level for debug output */
r_extern
id|u32
id|acpi_gbl_nesting_level
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * ACPI Table globals&n; *&n; ****************************************************************************/
multiline_comment|/*&n; * Table pointers.&n; * Although these pointers are somewhat redundant with the global acpi_table,&n; * they are convenient because they are typed pointers.&n; *&n; * These tables are single-table only; meaning that there can be at most one&n; * of each in the system.  Each global points to the actual table.&n; *&n; */
DECL|variable|acpi_gbl_table_flags
id|ACPI_EXTERN
id|u32
id|acpi_gbl_table_flags
suffix:semicolon
DECL|variable|acpi_gbl_rsdt_table_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_rsdt_table_count
suffix:semicolon
DECL|variable|acpi_gbl_RSDP
id|ACPI_EXTERN
r_struct
id|rsdp_descriptor
op_star
id|acpi_gbl_RSDP
suffix:semicolon
DECL|variable|acpi_gbl_XSDT
id|ACPI_EXTERN
id|XSDT_DESCRIPTOR
op_star
id|acpi_gbl_XSDT
suffix:semicolon
DECL|variable|acpi_gbl_FADT
id|ACPI_EXTERN
id|FADT_DESCRIPTOR
op_star
id|acpi_gbl_FADT
suffix:semicolon
DECL|variable|acpi_gbl_DSDT
id|ACPI_EXTERN
r_struct
id|acpi_table_header
op_star
id|acpi_gbl_DSDT
suffix:semicolon
DECL|variable|acpi_gbl_FACS
id|ACPI_EXTERN
id|FACS_DESCRIPTOR
op_star
id|acpi_gbl_FACS
suffix:semicolon
DECL|variable|acpi_gbl_common_fACS
id|ACPI_EXTERN
r_struct
id|acpi_common_facs
id|acpi_gbl_common_fACS
suffix:semicolon
multiline_comment|/*&n; * Handle both ACPI 1.0 and ACPI 2.0 Integer widths&n; * If we are running a method that exists in a 32-bit ACPI table.&n; * Use only 32 bits of the Integer for conversion.&n; */
DECL|variable|acpi_gbl_integer_bit_width
id|ACPI_EXTERN
id|u8
id|acpi_gbl_integer_bit_width
suffix:semicolon
DECL|variable|acpi_gbl_integer_byte_width
id|ACPI_EXTERN
id|u8
id|acpi_gbl_integer_byte_width
suffix:semicolon
DECL|variable|acpi_gbl_integer_nybble_width
id|ACPI_EXTERN
id|u8
id|acpi_gbl_integer_nybble_width
suffix:semicolon
multiline_comment|/* Keep local copies of these FADT-based registers */
DECL|variable|acpi_gbl_xpm1a_enable
id|ACPI_EXTERN
r_struct
id|acpi_generic_address
id|acpi_gbl_xpm1a_enable
suffix:semicolon
DECL|variable|acpi_gbl_xpm1b_enable
id|ACPI_EXTERN
r_struct
id|acpi_generic_address
id|acpi_gbl_xpm1b_enable
suffix:semicolon
multiline_comment|/*&n; * Since there may be multiple SSDTs and PSDTS, a single pointer is not&n; * sufficient; Therefore, there isn&squot;t one!&n; */
multiline_comment|/*&n; * ACPI Table info arrays&n; */
r_extern
r_struct
id|acpi_table_list
id|acpi_gbl_table_lists
(braket
id|NUM_ACPI_TABLE_TYPES
)braket
suffix:semicolon
r_extern
r_struct
id|acpi_table_support
id|acpi_gbl_table_data
(braket
id|NUM_ACPI_TABLE_TYPES
)braket
suffix:semicolon
multiline_comment|/*&n; * Predefined mutex objects.  This array contains the&n; * actual OS mutex handles, indexed by the local ACPI_MUTEX_HANDLEs.&n; * (The table maps local handles to the real OS handles)&n; */
DECL|variable|acpi_gbl_mutex_info
id|ACPI_EXTERN
r_struct
id|acpi_mutex_info
id|acpi_gbl_mutex_info
(braket
id|NUM_MUTEX
)braket
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Miscellaneous globals&n; *&n; ****************************************************************************/
DECL|variable|acpi_gbl_memory_lists
id|ACPI_EXTERN
r_struct
id|acpi_memory_list
id|acpi_gbl_memory_lists
(braket
id|ACPI_NUM_MEM_LISTS
)braket
suffix:semicolon
DECL|variable|acpi_gbl_device_notify
id|ACPI_EXTERN
r_struct
id|acpi_object_notify_handler
id|acpi_gbl_device_notify
suffix:semicolon
DECL|variable|acpi_gbl_system_notify
id|ACPI_EXTERN
r_struct
id|acpi_object_notify_handler
id|acpi_gbl_system_notify
suffix:semicolon
DECL|variable|acpi_gbl_init_handler
id|ACPI_EXTERN
id|acpi_init_handler
id|acpi_gbl_init_handler
suffix:semicolon
DECL|variable|acpi_gbl_breakpoint_walk
id|ACPI_EXTERN
r_struct
id|acpi_walk_state
op_star
id|acpi_gbl_breakpoint_walk
suffix:semicolon
DECL|variable|acpi_gbl_global_lock_semaphore
id|ACPI_EXTERN
id|acpi_handle
id|acpi_gbl_global_lock_semaphore
suffix:semicolon
DECL|variable|acpi_gbl_global_lock_thread_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_global_lock_thread_count
suffix:semicolon
DECL|variable|acpi_gbl_original_mode
id|ACPI_EXTERN
id|u32
id|acpi_gbl_original_mode
suffix:semicolon
DECL|variable|acpi_gbl_rsdp_original_location
id|ACPI_EXTERN
id|u32
id|acpi_gbl_rsdp_original_location
suffix:semicolon
DECL|variable|acpi_gbl_ns_lookup_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_ns_lookup_count
suffix:semicolon
DECL|variable|acpi_gbl_ps_find_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_ps_find_count
suffix:semicolon
DECL|variable|acpi_gbl_pm1_enable_register_save
id|ACPI_EXTERN
id|u16
id|acpi_gbl_pm1_enable_register_save
suffix:semicolon
DECL|variable|acpi_gbl_next_table_owner_id
id|ACPI_EXTERN
id|u16
id|acpi_gbl_next_table_owner_id
suffix:semicolon
DECL|variable|acpi_gbl_next_method_owner_id
id|ACPI_EXTERN
id|u16
id|acpi_gbl_next_method_owner_id
suffix:semicolon
DECL|variable|acpi_gbl_global_lock_handle
id|ACPI_EXTERN
id|u16
id|acpi_gbl_global_lock_handle
suffix:semicolon
DECL|variable|acpi_gbl_debugger_configuration
id|ACPI_EXTERN
id|u8
id|acpi_gbl_debugger_configuration
suffix:semicolon
DECL|variable|acpi_gbl_global_lock_acquired
id|ACPI_EXTERN
id|u8
id|acpi_gbl_global_lock_acquired
suffix:semicolon
DECL|variable|acpi_gbl_step_to_next_call
id|ACPI_EXTERN
id|u8
id|acpi_gbl_step_to_next_call
suffix:semicolon
DECL|variable|acpi_gbl_acpi_hardware_present
id|ACPI_EXTERN
id|u8
id|acpi_gbl_acpi_hardware_present
suffix:semicolon
DECL|variable|acpi_gbl_global_lock_present
id|ACPI_EXTERN
id|u8
id|acpi_gbl_global_lock_present
suffix:semicolon
DECL|variable|acpi_gbl_events_initialized
id|ACPI_EXTERN
id|u8
id|acpi_gbl_events_initialized
suffix:semicolon
r_extern
id|u8
id|acpi_gbl_shutdown
suffix:semicolon
r_extern
id|u32
id|acpi_gbl_startup_flags
suffix:semicolon
r_extern
r_const
id|u8
id|acpi_gbl_decode_to8bit
(braket
l_int|8
)braket
suffix:semicolon
r_extern
r_const
r_char
op_star
id|acpi_gbl_db_sleep_states
(braket
id|ACPI_S_STATE_COUNT
)braket
suffix:semicolon
r_extern
r_const
r_struct
id|acpi_opcode_info
id|acpi_gbl_aml_op_info
(braket
id|AML_NUM_OPCODES
)braket
suffix:semicolon
r_extern
r_const
r_char
op_star
id|acpi_gbl_region_types
(braket
id|ACPI_NUM_PREDEFINED_REGIONS
)braket
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Namespace globals&n; *&n; ****************************************************************************/
DECL|macro|NUM_NS_TYPES
mdefine_line|#define NUM_NS_TYPES                    ACPI_TYPE_INVALID+1
macro_line|#if defined (ACPI_NO_METHOD_EXECUTION) || defined (ACPI_CONSTANT_EVAL_ONLY)
DECL|macro|NUM_PREDEFINED_NAMES
mdefine_line|#define NUM_PREDEFINED_NAMES            10
macro_line|#else
DECL|macro|NUM_PREDEFINED_NAMES
mdefine_line|#define NUM_PREDEFINED_NAMES            9
macro_line|#endif
DECL|variable|acpi_gbl_root_node_struct
id|ACPI_EXTERN
r_struct
id|acpi_namespace_node
id|acpi_gbl_root_node_struct
suffix:semicolon
DECL|variable|acpi_gbl_root_node
id|ACPI_EXTERN
r_struct
id|acpi_namespace_node
op_star
id|acpi_gbl_root_node
suffix:semicolon
r_extern
r_const
id|u8
id|acpi_gbl_ns_properties
(braket
id|NUM_NS_TYPES
)braket
suffix:semicolon
r_extern
r_const
r_struct
id|acpi_predefined_names
id|acpi_gbl_pre_defined_names
(braket
id|NUM_PREDEFINED_NAMES
)braket
suffix:semicolon
macro_line|#ifdef ACPI_DEBUG_OUTPUT
DECL|variable|acpi_gbl_current_node_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_current_node_count
suffix:semicolon
DECL|variable|acpi_gbl_current_node_size
id|ACPI_EXTERN
id|u32
id|acpi_gbl_current_node_size
suffix:semicolon
DECL|variable|acpi_gbl_max_concurrent_node_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_max_concurrent_node_count
suffix:semicolon
DECL|variable|acpi_gbl_entry_stack_pointer
id|ACPI_EXTERN
id|acpi_size
id|acpi_gbl_entry_stack_pointer
suffix:semicolon
DECL|variable|acpi_gbl_lowest_stack_pointer
id|ACPI_EXTERN
id|acpi_size
id|acpi_gbl_lowest_stack_pointer
suffix:semicolon
DECL|variable|acpi_gbl_deepest_nesting
id|ACPI_EXTERN
id|u32
id|acpi_gbl_deepest_nesting
suffix:semicolon
macro_line|#endif
multiline_comment|/*****************************************************************************&n; *&n; * Interpreter globals&n; *&n; ****************************************************************************/
DECL|variable|acpi_gbl_current_walk_list
id|ACPI_EXTERN
r_struct
id|acpi_thread_state
op_star
id|acpi_gbl_current_walk_list
suffix:semicolon
multiline_comment|/* Control method single step flag */
DECL|variable|acpi_gbl_cm_single_step
id|ACPI_EXTERN
id|u8
id|acpi_gbl_cm_single_step
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Parser globals&n; *&n; ****************************************************************************/
DECL|variable|acpi_gbl_parsed_namespace_root
id|ACPI_EXTERN
r_union
id|acpi_parse_object
op_star
id|acpi_gbl_parsed_namespace_root
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Hardware globals&n; *&n; ****************************************************************************/
r_extern
r_struct
id|acpi_bit_register_info
id|acpi_gbl_bit_register_info
(braket
id|ACPI_NUM_BITREG
)braket
suffix:semicolon
DECL|variable|acpi_gbl_sleep_type_a
id|ACPI_EXTERN
id|u8
id|acpi_gbl_sleep_type_a
suffix:semicolon
DECL|variable|acpi_gbl_sleep_type_b
id|ACPI_EXTERN
id|u8
id|acpi_gbl_sleep_type_b
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Event and GPE globals&n; *&n; ****************************************************************************/
r_extern
r_struct
id|acpi_fixed_event_info
id|acpi_gbl_fixed_event_info
(braket
id|ACPI_NUM_FIXED_EVENTS
)braket
suffix:semicolon
DECL|variable|acpi_gbl_fixed_event_handlers
id|ACPI_EXTERN
r_struct
id|acpi_fixed_event_handler
id|acpi_gbl_fixed_event_handlers
(braket
id|ACPI_NUM_FIXED_EVENTS
)braket
suffix:semicolon
DECL|variable|acpi_gbl_gpe_xrupt_list_head
id|ACPI_EXTERN
r_struct
id|acpi_gpe_xrupt_info
op_star
id|acpi_gbl_gpe_xrupt_list_head
suffix:semicolon
DECL|variable|acpi_gbl_gpe_fadt_blocks
id|ACPI_EXTERN
r_struct
id|acpi_gpe_block_info
op_star
id|acpi_gbl_gpe_fadt_blocks
(braket
id|ACPI_MAX_GPE_BLOCKS
)braket
suffix:semicolon
DECL|variable|acpi_gbl_gpe_lock
id|ACPI_EXTERN
id|acpi_handle
id|acpi_gbl_gpe_lock
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Debugger globals&n; *&n; ****************************************************************************/
DECL|variable|acpi_gbl_db_output_flags
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_output_flags
suffix:semicolon
macro_line|#ifdef ACPI_DISASSEMBLER
DECL|variable|acpi_gbl_db_opt_disasm
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_opt_disasm
suffix:semicolon
DECL|variable|acpi_gbl_db_opt_verbose
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_opt_verbose
suffix:semicolon
macro_line|#endif
macro_line|#ifdef ACPI_DEBUGGER
r_extern
id|u8
id|acpi_gbl_method_executing
suffix:semicolon
r_extern
id|u8
id|acpi_gbl_abort_method
suffix:semicolon
r_extern
id|u8
id|acpi_gbl_db_terminate_threads
suffix:semicolon
DECL|variable|optind
id|ACPI_EXTERN
r_int
id|optind
suffix:semicolon
DECL|variable|optarg
id|ACPI_EXTERN
r_char
op_star
id|optarg
suffix:semicolon
DECL|variable|acpi_gbl_db_opt_tables
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_opt_tables
suffix:semicolon
DECL|variable|acpi_gbl_db_opt_stats
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_opt_stats
suffix:semicolon
DECL|variable|acpi_gbl_db_opt_ini_methods
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_opt_ini_methods
suffix:semicolon
DECL|variable|acpi_gbl_db_args
id|ACPI_EXTERN
r_char
op_star
id|acpi_gbl_db_args
(braket
id|ACPI_DEBUGGER_MAX_ARGS
)braket
suffix:semicolon
DECL|variable|acpi_gbl_db_line_buf
id|ACPI_EXTERN
r_char
id|acpi_gbl_db_line_buf
(braket
l_int|80
)braket
suffix:semicolon
DECL|variable|acpi_gbl_db_parsed_buf
id|ACPI_EXTERN
r_char
id|acpi_gbl_db_parsed_buf
(braket
l_int|80
)braket
suffix:semicolon
DECL|variable|acpi_gbl_db_scope_buf
id|ACPI_EXTERN
r_char
id|acpi_gbl_db_scope_buf
(braket
l_int|40
)braket
suffix:semicolon
DECL|variable|acpi_gbl_db_debug_filename
id|ACPI_EXTERN
r_char
id|acpi_gbl_db_debug_filename
(braket
l_int|40
)braket
suffix:semicolon
DECL|variable|acpi_gbl_db_output_to_file
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_output_to_file
suffix:semicolon
DECL|variable|acpi_gbl_db_buffer
id|ACPI_EXTERN
r_char
op_star
id|acpi_gbl_db_buffer
suffix:semicolon
DECL|variable|acpi_gbl_db_filename
id|ACPI_EXTERN
r_char
op_star
id|acpi_gbl_db_filename
suffix:semicolon
DECL|variable|acpi_gbl_db_debug_level
id|ACPI_EXTERN
id|u32
id|acpi_gbl_db_debug_level
suffix:semicolon
DECL|variable|acpi_gbl_db_console_debug_level
id|ACPI_EXTERN
id|u32
id|acpi_gbl_db_console_debug_level
suffix:semicolon
DECL|variable|acpi_gbl_db_table_ptr
id|ACPI_EXTERN
r_struct
id|acpi_table_header
op_star
id|acpi_gbl_db_table_ptr
suffix:semicolon
DECL|variable|acpi_gbl_db_scope_node
id|ACPI_EXTERN
r_struct
id|acpi_namespace_node
op_star
id|acpi_gbl_db_scope_node
suffix:semicolon
multiline_comment|/*&n; * Statistic globals&n; */
DECL|variable|acpi_gbl_obj_type_count
id|ACPI_EXTERN
id|u16
id|acpi_gbl_obj_type_count
(braket
id|ACPI_TYPE_NS_NODE_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|acpi_gbl_node_type_count
id|ACPI_EXTERN
id|u16
id|acpi_gbl_node_type_count
(braket
id|ACPI_TYPE_NS_NODE_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|acpi_gbl_obj_type_count_misc
id|ACPI_EXTERN
id|u16
id|acpi_gbl_obj_type_count_misc
suffix:semicolon
DECL|variable|acpi_gbl_node_type_count_misc
id|ACPI_EXTERN
id|u16
id|acpi_gbl_node_type_count_misc
suffix:semicolon
DECL|variable|acpi_gbl_num_nodes
id|ACPI_EXTERN
id|u32
id|acpi_gbl_num_nodes
suffix:semicolon
DECL|variable|acpi_gbl_num_objects
id|ACPI_EXTERN
id|u32
id|acpi_gbl_num_objects
suffix:semicolon
DECL|variable|acpi_gbl_size_of_parse_tree
id|ACPI_EXTERN
id|u32
id|acpi_gbl_size_of_parse_tree
suffix:semicolon
DECL|variable|acpi_gbl_size_of_method_trees
id|ACPI_EXTERN
id|u32
id|acpi_gbl_size_of_method_trees
suffix:semicolon
DECL|variable|acpi_gbl_size_of_node_entries
id|ACPI_EXTERN
id|u32
id|acpi_gbl_size_of_node_entries
suffix:semicolon
DECL|variable|acpi_gbl_size_of_acpi_objects
id|ACPI_EXTERN
id|u32
id|acpi_gbl_size_of_acpi_objects
suffix:semicolon
macro_line|#endif /* ACPI_DEBUGGER */
macro_line|#endif /* __ACGLOBAL_H__ */
eof
