multiline_comment|/******************************************************************************&n; *&n; * Name: acglobal.h - Declarations for global variables&n; *       $Revision: 121 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
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
multiline_comment|/*&n; * Table pointers.&n; * Although these pointers are somewhat redundant with the global Acpi_table,&n; * they are convenient because they are typed pointers.&n; *&n; * These tables are single-table only; meaning that there can be at most one&n; * of each in the system.  Each global points to the actual table.&n; *&n; */
DECL|variable|acpi_gbl_table_flags
id|ACPI_EXTERN
id|u32
id|acpi_gbl_table_flags
suffix:semicolon
DECL|variable|acpi_gbl_RSDP
id|ACPI_EXTERN
id|RSDP_DESCRIPTOR
op_star
id|acpi_gbl_RSDP
suffix:semicolon
DECL|variable|acpi_gbl_XSDT
id|ACPI_EXTERN
id|xsdt_descriptor
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
id|acpi_common_facs
id|acpi_gbl_common_fACS
suffix:semicolon
multiline_comment|/*&n; * Since there may be multiple SSDTs and PSDTS, a single pointer is not&n; * sufficient; Therefore, there isn&squot;t one!&n; */
multiline_comment|/*&n; * ACPI Table info arrays&n; */
r_extern
id|acpi_table_desc
id|acpi_gbl_acpi_tables
(braket
id|NUM_ACPI_TABLES
)braket
suffix:semicolon
r_extern
id|ACPI_TABLE_SUPPORT
id|acpi_gbl_acpi_table_data
(braket
id|NUM_ACPI_TABLES
)braket
suffix:semicolon
multiline_comment|/*&n; * Predefined mutex objects.  This array contains the&n; * actual OS mutex handles, indexed by the local ACPI_MUTEX_HANDLEs.&n; * (The table maps local handles to the real OS handles)&n; */
DECL|variable|acpi_gbl_acpi_mutex_info
id|ACPI_EXTERN
id|acpi_mutex_info
id|acpi_gbl_acpi_mutex_info
(braket
id|NUM_MTX
)braket
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Miscellaneous globals&n; *&n; ****************************************************************************/
DECL|variable|acpi_gbl_memory_lists
id|ACPI_EXTERN
id|ACPI_MEMORY_LIST
id|acpi_gbl_memory_lists
(braket
id|ACPI_NUM_MEM_LISTS
)braket
suffix:semicolon
DECL|variable|acpi_gbl_drv_notify
id|ACPI_EXTERN
id|ACPI_OBJECT_NOTIFY_HANDLER
id|acpi_gbl_drv_notify
suffix:semicolon
DECL|variable|acpi_gbl_sys_notify
id|ACPI_EXTERN
id|ACPI_OBJECT_NOTIFY_HANDLER
id|acpi_gbl_sys_notify
suffix:semicolon
DECL|variable|acpi_gbl_breakpoint_walk
id|ACPI_EXTERN
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
id|NATIVE_CHAR
op_star
id|acpi_gbl_db_sleep_states
(braket
id|ACPI_NUM_SLEEP_STATES
)braket
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Namespace globals&n; *&n; ****************************************************************************/
DECL|macro|NUM_NS_TYPES
mdefine_line|#define NUM_NS_TYPES                    INTERNAL_TYPE_INVALID+1
DECL|macro|NUM_PREDEFINED_NAMES
mdefine_line|#define NUM_PREDEFINED_NAMES            9
DECL|variable|acpi_gbl_root_node_struct
id|ACPI_EXTERN
id|acpi_namespace_node
id|acpi_gbl_root_node_struct
suffix:semicolon
DECL|variable|acpi_gbl_root_node
id|ACPI_EXTERN
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
id|acpi_predefined_names
id|acpi_gbl_pre_defined_names
(braket
id|NUM_PREDEFINED_NAMES
)braket
suffix:semicolon
macro_line|#ifdef ACPI_DEBUG
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
id|ACPI_SIZE
id|acpi_gbl_entry_stack_pointer
suffix:semicolon
DECL|variable|acpi_gbl_lowest_stack_pointer
id|ACPI_EXTERN
id|ACPI_SIZE
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
id|ACPI_THREAD_STATE
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
id|acpi_parse_object
op_star
id|acpi_gbl_parsed_namespace_root
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Hardware globals&n; *&n; ****************************************************************************/
DECL|variable|acpi_gbl_bit_register_info
id|ACPI_EXTERN
id|ACPI_BIT_REGISTER_INFO
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
id|acpi_fixed_event_info
id|acpi_gbl_fixed_event_info
(braket
id|ACPI_NUM_FIXED_EVENTS
)braket
suffix:semicolon
DECL|variable|acpi_gbl_fixed_event_handlers
id|ACPI_EXTERN
id|ACPI_FIXED_EVENT_HANDLER
id|acpi_gbl_fixed_event_handlers
(braket
id|ACPI_NUM_FIXED_EVENTS
)braket
suffix:semicolon
DECL|variable|acpi_gbl_gpe_obj_handle
id|ACPI_EXTERN
id|acpi_handle
id|acpi_gbl_gpe_obj_handle
suffix:semicolon
DECL|variable|acpi_gbl_gpe_register_count
id|ACPI_EXTERN
id|u32
id|acpi_gbl_gpe_register_count
suffix:semicolon
DECL|variable|acpi_gbl_gpe_number_max
id|ACPI_EXTERN
id|u32
id|acpi_gbl_gpe_number_max
suffix:semicolon
DECL|variable|acpi_gbl_gpe_register_info
id|ACPI_EXTERN
id|ACPI_GPE_REGISTER_INFO
op_star
id|acpi_gbl_gpe_register_info
suffix:semicolon
DECL|variable|acpi_gbl_gpe_number_info
id|ACPI_EXTERN
id|ACPI_GPE_NUMBER_INFO
op_star
id|acpi_gbl_gpe_number_info
suffix:semicolon
DECL|variable|acpi_gbl_gpe_block_info
id|ACPI_EXTERN
id|ACPI_GPE_BLOCK_INFO
id|acpi_gbl_gpe_block_info
(braket
id|ACPI_MAX_GPE_BLOCKS
)braket
suffix:semicolon
multiline_comment|/*&n; * GPE translation table&n; * Indexed by the GPE number, returns a valid index into the global GPE tables.&n; *&n; * This table is needed because the GPE numbers supported by block 1 do not&n; * have to be contiguous with the GPE numbers supported by block 0.&n; */
DECL|variable|acpi_gbl_gpe_number_to_index
id|ACPI_EXTERN
id|ACPI_GPE_INDEX_INFO
op_star
id|acpi_gbl_gpe_number_to_index
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Debugger globals&n; *&n; ****************************************************************************/
DECL|variable|acpi_gbl_db_output_flags
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_output_flags
suffix:semicolon
macro_line|#ifdef ENABLE_DEBUGGER
DECL|variable|acpi_gbl_method_executing
id|ACPI_EXTERN
id|u8
id|acpi_gbl_method_executing
suffix:semicolon
DECL|variable|acpi_gbl_db_terminate_threads
id|ACPI_EXTERN
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
id|NATIVE_CHAR
op_star
id|optarg
suffix:semicolon
DECL|variable|aml_start
id|ACPI_EXTERN
id|u8
op_star
id|aml_start
suffix:semicolon
DECL|variable|aml_length
id|ACPI_EXTERN
id|u32
id|aml_length
suffix:semicolon
DECL|variable|acpi_gbl_db_opt_tables
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_opt_tables
suffix:semicolon
DECL|variable|acpi_gbl_db_opt_disasm
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_opt_disasm
suffix:semicolon
DECL|variable|acpi_gbl_db_opt_stats
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_opt_stats
suffix:semicolon
DECL|variable|acpi_gbl_db_opt_verbose
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_opt_verbose
suffix:semicolon
DECL|variable|acpi_gbl_db_opt_ini_methods
id|ACPI_EXTERN
id|u8
id|acpi_gbl_db_opt_ini_methods
suffix:semicolon
DECL|variable|acpi_gbl_db_args
id|ACPI_EXTERN
id|NATIVE_CHAR
op_star
id|acpi_gbl_db_args
(braket
id|ACPI_DEBUGGER_MAX_ARGS
)braket
suffix:semicolon
DECL|variable|acpi_gbl_db_line_buf
id|ACPI_EXTERN
id|NATIVE_CHAR
id|acpi_gbl_db_line_buf
(braket
l_int|80
)braket
suffix:semicolon
DECL|variable|acpi_gbl_db_parsed_buf
id|ACPI_EXTERN
id|NATIVE_CHAR
id|acpi_gbl_db_parsed_buf
(braket
l_int|80
)braket
suffix:semicolon
DECL|variable|acpi_gbl_db_scope_buf
id|ACPI_EXTERN
id|NATIVE_CHAR
id|acpi_gbl_db_scope_buf
(braket
l_int|40
)braket
suffix:semicolon
DECL|variable|acpi_gbl_db_debug_filename
id|ACPI_EXTERN
id|NATIVE_CHAR
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
id|NATIVE_CHAR
op_star
id|acpi_gbl_db_buffer
suffix:semicolon
DECL|variable|acpi_gbl_db_filename
id|ACPI_EXTERN
id|NATIVE_CHAR
op_star
id|acpi_gbl_db_filename
suffix:semicolon
DECL|variable|acpi_gbl_db_disasm_indent
id|ACPI_EXTERN
id|NATIVE_CHAR
op_star
id|acpi_gbl_db_disasm_indent
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
id|acpi_table_header
op_star
id|acpi_gbl_db_table_ptr
suffix:semicolon
DECL|variable|acpi_gbl_db_scope_node
id|ACPI_EXTERN
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
id|INTERNAL_TYPE_NODE_MAX
op_plus
l_int|1
)braket
suffix:semicolon
DECL|variable|acpi_gbl_node_type_count
id|ACPI_EXTERN
id|u16
id|acpi_gbl_node_type_count
(braket
id|INTERNAL_TYPE_NODE_MAX
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
macro_line|#endif /* ENABLE_DEBUGGER */
macro_line|#endif /* __ACGLOBAL_H__ */
eof
