multiline_comment|/******************************************************************************&n; *&n; * Name: acstruct.h - Internal structs&n; *       $Revision: 3 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACSTRUCT_H__
DECL|macro|__ACSTRUCT_H__
mdefine_line|#define __ACSTRUCT_H__
multiline_comment|/*****************************************************************************&n; *&n; * Tree walking typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/*&n; * Walk state - current state of a parse tree walk.  Used for both a leisurely stroll through&n; * the tree (for whatever reason), and for control method execution.&n; */
DECL|macro|NEXT_OP_DOWNWARD
mdefine_line|#define NEXT_OP_DOWNWARD    1
DECL|macro|NEXT_OP_UPWARD
mdefine_line|#define NEXT_OP_UPWARD      2
DECL|macro|WALK_NON_METHOD
mdefine_line|#define WALK_NON_METHOD     0
DECL|macro|WALK_METHOD
mdefine_line|#define WALK_METHOD         1
DECL|macro|WALK_METHOD_RESTART
mdefine_line|#define WALK_METHOD_RESTART 2
DECL|struct|acpi_walk_state
r_typedef
r_struct
id|acpi_walk_state
(brace
DECL|member|data_type
id|u8
id|data_type
suffix:semicolon
multiline_comment|/* To differentiate various internal objs */
"&bslash;"
DECL|member|owner_id
id|ACPI_OWNER_ID
id|owner_id
suffix:semicolon
multiline_comment|/* Owner of objects created during the walk */
DECL|member|last_predicate
id|u8
id|last_predicate
suffix:semicolon
multiline_comment|/* Result of last predicate */
DECL|member|next_op_info
id|u8
id|next_op_info
suffix:semicolon
multiline_comment|/* Info about Next_op */
DECL|member|num_operands
id|u8
id|num_operands
suffix:semicolon
multiline_comment|/* Stack pointer for Operands[] array */
DECL|member|current_result
id|u8
id|current_result
suffix:semicolon
multiline_comment|/* */
DECL|member|next
r_struct
id|acpi_walk_state
op_star
id|next
suffix:semicolon
multiline_comment|/* Next Walk_state in list */
DECL|member|origin
id|ACPI_PARSE_OBJECT
op_star
id|origin
suffix:semicolon
multiline_comment|/* Start of walk [Obsolete] */
multiline_comment|/* TBD: Obsolete with removal of WALK procedure ? */
DECL|member|prev_op
id|ACPI_PARSE_OBJECT
op_star
id|prev_op
suffix:semicolon
multiline_comment|/* Last op that was processed */
DECL|member|next_op
id|ACPI_PARSE_OBJECT
op_star
id|next_op
suffix:semicolon
multiline_comment|/* next op to be processed */
DECL|member|results
id|ACPI_GENERIC_STATE
op_star
id|results
suffix:semicolon
multiline_comment|/* Stack of accumulated results */
DECL|member|control_state
id|ACPI_GENERIC_STATE
op_star
id|control_state
suffix:semicolon
multiline_comment|/* List of control states (nested IFs) */
DECL|member|scope_info
id|ACPI_GENERIC_STATE
op_star
id|scope_info
suffix:semicolon
multiline_comment|/* Stack of nested scopes */
DECL|member|parser_state
id|ACPI_PARSE_STATE
op_star
id|parser_state
suffix:semicolon
multiline_comment|/* Current state of parser */
DECL|member|aml_last_while
id|u8
op_star
id|aml_last_while
suffix:semicolon
DECL|member|op_info
id|ACPI_OPCODE_INFO
op_star
id|op_info
suffix:semicolon
multiline_comment|/* Info on current opcode */
DECL|member|descending_callback
id|ACPI_PARSE_DOWNWARDS
id|descending_callback
suffix:semicolon
DECL|member|ascending_callback
id|ACPI_PARSE_UPWARDS
id|ascending_callback
suffix:semicolon
DECL|member|return_desc
r_union
id|acpi_operand_obj
op_star
id|return_desc
suffix:semicolon
multiline_comment|/* Return object, if any */
DECL|member|method_desc
r_union
id|acpi_operand_obj
op_star
id|method_desc
suffix:semicolon
multiline_comment|/* Method descriptor if running a method */
DECL|member|method_node
r_struct
id|acpi_node
op_star
id|method_node
suffix:semicolon
multiline_comment|/* Method Node if running a method */
DECL|member|method_call_op
id|ACPI_PARSE_OBJECT
op_star
id|method_call_op
suffix:semicolon
multiline_comment|/* Method_call Op if running a method */
DECL|member|method_call_node
r_struct
id|acpi_node
op_star
id|method_call_node
suffix:semicolon
multiline_comment|/* Called method Node*/
DECL|member|operands
r_union
id|acpi_operand_obj
op_star
id|operands
(braket
id|OBJ_NUM_OPERANDS
)braket
suffix:semicolon
multiline_comment|/* Operands passed to the interpreter */
DECL|member|arguments
r_struct
id|acpi_node
id|arguments
(braket
id|MTH_NUM_ARGS
)braket
suffix:semicolon
multiline_comment|/* Control method arguments */
DECL|member|local_variables
r_struct
id|acpi_node
id|local_variables
(braket
id|MTH_NUM_LOCALS
)braket
suffix:semicolon
multiline_comment|/* Control method locals */
DECL|member|walk_list
r_struct
id|acpi_walk_list
op_star
id|walk_list
suffix:semicolon
DECL|member|parse_flags
id|u32
id|parse_flags
suffix:semicolon
DECL|member|walk_type
id|u8
id|walk_type
suffix:semicolon
DECL|member|return_used
id|u8
id|return_used
suffix:semicolon
DECL|member|opcode
id|u16
id|opcode
suffix:semicolon
multiline_comment|/* Current AML opcode */
DECL|member|prev_arg_types
id|u32
id|prev_arg_types
suffix:semicolon
DECL|member|current_sync_level
id|u16
id|current_sync_level
suffix:semicolon
multiline_comment|/* Mutex Sync (nested acquire) level */
multiline_comment|/* Debug support */
DECL|member|method_breakpoint
id|u32
id|method_breakpoint
suffix:semicolon
DECL|typedef|ACPI_WALK_STATE
)brace
id|ACPI_WALK_STATE
suffix:semicolon
multiline_comment|/*&n; * Walk list - head of a tree of walk states.  Multiple walk states are created when there&n; * are nested control methods executing.&n; */
DECL|struct|acpi_walk_list
r_typedef
r_struct
id|acpi_walk_list
(brace
DECL|member|walk_state
id|ACPI_WALK_STATE
op_star
id|walk_state
suffix:semicolon
DECL|member|acquired_mutex_list
id|ACPI_OBJECT_MUTEX
id|acquired_mutex_list
suffix:semicolon
multiline_comment|/* List of all currently acquired mutexes */
DECL|typedef|ACPI_WALK_LIST
)brace
id|ACPI_WALK_LIST
suffix:semicolon
multiline_comment|/* Info used by Acpi_ps_init_objects */
DECL|struct|acpi_init_walk_info
r_typedef
r_struct
id|acpi_init_walk_info
(brace
DECL|member|method_count
id|u16
id|method_count
suffix:semicolon
DECL|member|op_region_count
id|u16
id|op_region_count
suffix:semicolon
DECL|member|field_count
id|u16
id|field_count
suffix:semicolon
DECL|member|op_region_init
id|u16
id|op_region_init
suffix:semicolon
DECL|member|field_init
id|u16
id|field_init
suffix:semicolon
DECL|member|object_count
id|u16
id|object_count
suffix:semicolon
DECL|member|table_desc
id|ACPI_TABLE_DESC
op_star
id|table_desc
suffix:semicolon
DECL|typedef|ACPI_INIT_WALK_INFO
)brace
id|ACPI_INIT_WALK_INFO
suffix:semicolon
multiline_comment|/* Info used by TBD */
DECL|struct|acpi_device_walk_info
r_typedef
r_struct
id|acpi_device_walk_info
(brace
DECL|member|device_count
id|u16
id|device_count
suffix:semicolon
DECL|member|num_STA
id|u16
id|num_STA
suffix:semicolon
DECL|member|num_INI
id|u16
id|num_INI
suffix:semicolon
DECL|member|table_desc
id|ACPI_TABLE_DESC
op_star
id|table_desc
suffix:semicolon
DECL|typedef|ACPI_DEVICE_WALK_INFO
)brace
id|ACPI_DEVICE_WALK_INFO
suffix:semicolon
multiline_comment|/* TBD: [Restructure] Merge with struct above */
DECL|struct|acpi_walk_info
r_typedef
r_struct
id|acpi_walk_info
(brace
DECL|member|debug_level
id|u32
id|debug_level
suffix:semicolon
DECL|member|owner_id
id|u32
id|owner_id
suffix:semicolon
DECL|typedef|ACPI_WALK_INFO
)brace
id|ACPI_WALK_INFO
suffix:semicolon
DECL|struct|acpi_get_devices_info
r_typedef
r_struct
id|acpi_get_devices_info
(brace
DECL|member|user_function
id|ACPI_WALK_CALLBACK
id|user_function
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|member|hid
id|NATIVE_CHAR
op_star
id|hid
suffix:semicolon
DECL|typedef|ACPI_GET_DEVICES_INFO
)brace
id|ACPI_GET_DEVICES_INFO
suffix:semicolon
macro_line|#endif
eof
