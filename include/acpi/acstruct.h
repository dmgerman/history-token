multiline_comment|/******************************************************************************&n; *&n; * Name: acstruct.h - Internal structs&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACSTRUCT_H__
DECL|macro|__ACSTRUCT_H__
mdefine_line|#define __ACSTRUCT_H__
multiline_comment|/*****************************************************************************&n; *&n; * Tree walking typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/*&n; * Walk state - current state of a parse tree walk.  Used for both a leisurely stroll through&n; * the tree (for whatever reason), and for control method execution.&n; */
DECL|macro|ACPI_NEXT_OP_DOWNWARD
mdefine_line|#define ACPI_NEXT_OP_DOWNWARD       1
DECL|macro|ACPI_NEXT_OP_UPWARD
mdefine_line|#define ACPI_NEXT_OP_UPWARD         2
DECL|macro|ACPI_WALK_NON_METHOD
mdefine_line|#define ACPI_WALK_NON_METHOD        0
DECL|macro|ACPI_WALK_METHOD
mdefine_line|#define ACPI_WALK_METHOD            1
DECL|macro|ACPI_WALK_METHOD_RESTART
mdefine_line|#define ACPI_WALK_METHOD_RESTART    2
DECL|macro|ACPI_WALK_CONST_REQUIRED
mdefine_line|#define ACPI_WALK_CONST_REQUIRED    3
DECL|macro|ACPI_WALK_CONST_OPTIONAL
mdefine_line|#define ACPI_WALK_CONST_OPTIONAL    4
DECL|struct|acpi_walk_state
r_struct
id|acpi_walk_state
(brace
DECL|member|data_type
id|u8
id|data_type
suffix:semicolon
multiline_comment|/* To differentiate various internal objs MUST BE FIRST!*/
"&bslash;"
DECL|member|walk_type
id|u8
id|walk_type
suffix:semicolon
DECL|member|owner_id
id|acpi_owner_id
id|owner_id
suffix:semicolon
multiline_comment|/* Owner of objects created during the walk */
DECL|member|last_predicate
id|u8
id|last_predicate
suffix:semicolon
multiline_comment|/* Result of last predicate */
DECL|member|reserved
id|u8
id|reserved
suffix:semicolon
multiline_comment|/* For alignment */
DECL|member|current_result
id|u8
id|current_result
suffix:semicolon
multiline_comment|/* */
DECL|member|next_op_info
id|u8
id|next_op_info
suffix:semicolon
multiline_comment|/* Info about next_op */
DECL|member|num_operands
id|u8
id|num_operands
suffix:semicolon
multiline_comment|/* Stack pointer for Operands[] array */
DECL|member|return_used
id|u8
id|return_used
suffix:semicolon
DECL|member|opcode
id|u16
id|opcode
suffix:semicolon
multiline_comment|/* Current AML opcode */
DECL|member|scope_depth
id|u8
id|scope_depth
suffix:semicolon
DECL|member|reserved1
id|u8
id|reserved1
suffix:semicolon
DECL|member|arg_count
id|u32
id|arg_count
suffix:semicolon
multiline_comment|/* push for fixed or var args */
DECL|member|aml_offset
id|u32
id|aml_offset
suffix:semicolon
DECL|member|arg_types
id|u32
id|arg_types
suffix:semicolon
DECL|member|method_breakpoint
id|u32
id|method_breakpoint
suffix:semicolon
multiline_comment|/* For single stepping */
DECL|member|user_breakpoint
id|u32
id|user_breakpoint
suffix:semicolon
multiline_comment|/* User AML breakpoint */
DECL|member|parse_flags
id|u32
id|parse_flags
suffix:semicolon
DECL|member|prev_arg_types
id|u32
id|prev_arg_types
suffix:semicolon
DECL|member|aml_last_while
id|u8
op_star
id|aml_last_while
suffix:semicolon
DECL|member|arguments
r_struct
id|acpi_namespace_node
id|arguments
(braket
id|ACPI_METHOD_NUM_ARGS
)braket
suffix:semicolon
multiline_comment|/* Control method arguments */
DECL|member|caller_return_desc
r_union
id|acpi_operand_object
op_star
op_star
id|caller_return_desc
suffix:semicolon
DECL|member|control_state
r_union
id|acpi_generic_state
op_star
id|control_state
suffix:semicolon
multiline_comment|/* List of control states (nested IFs) */
DECL|member|deferred_node
r_struct
id|acpi_namespace_node
op_star
id|deferred_node
suffix:semicolon
multiline_comment|/* Used when executing deferred opcodes */
DECL|member|gpe_event_info
r_struct
id|acpi_gpe_event_info
op_star
id|gpe_event_info
suffix:semicolon
multiline_comment|/* Info for GPE (_Lxx/_Exx methods only */
DECL|member|local_variables
r_struct
id|acpi_namespace_node
id|local_variables
(braket
id|ACPI_METHOD_NUM_LOCALS
)braket
suffix:semicolon
multiline_comment|/* Control method locals */
DECL|member|method_call_node
r_struct
id|acpi_namespace_node
op_star
id|method_call_node
suffix:semicolon
multiline_comment|/* Called method Node*/
DECL|member|method_call_op
r_union
id|acpi_parse_object
op_star
id|method_call_op
suffix:semicolon
multiline_comment|/* method_call Op if running a method */
DECL|member|method_desc
r_union
id|acpi_operand_object
op_star
id|method_desc
suffix:semicolon
multiline_comment|/* Method descriptor if running a method */
DECL|member|method_node
r_struct
id|acpi_namespace_node
op_star
id|method_node
suffix:semicolon
multiline_comment|/* Method node if running a method. */
DECL|member|op
r_union
id|acpi_parse_object
op_star
id|op
suffix:semicolon
multiline_comment|/* Current parser op */
DECL|member|operands
r_union
id|acpi_operand_object
op_star
id|operands
(braket
id|ACPI_OBJ_NUM_OPERANDS
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* Operands passed to the interpreter (+1 for NULL terminator) */
DECL|member|op_info
r_const
r_struct
id|acpi_opcode_info
op_star
id|op_info
suffix:semicolon
multiline_comment|/* Info on current opcode */
DECL|member|origin
r_union
id|acpi_parse_object
op_star
id|origin
suffix:semicolon
multiline_comment|/* Start of walk [Obsolete] */
DECL|member|params
r_union
id|acpi_operand_object
op_star
op_star
id|params
suffix:semicolon
DECL|member|parser_state
r_struct
id|acpi_parse_state
id|parser_state
suffix:semicolon
multiline_comment|/* Current state of parser */
DECL|member|result_obj
r_union
id|acpi_operand_object
op_star
id|result_obj
suffix:semicolon
DECL|member|results
r_union
id|acpi_generic_state
op_star
id|results
suffix:semicolon
multiline_comment|/* Stack of accumulated results */
DECL|member|return_desc
r_union
id|acpi_operand_object
op_star
id|return_desc
suffix:semicolon
multiline_comment|/* Return object, if any */
DECL|member|scope_info
r_union
id|acpi_generic_state
op_star
id|scope_info
suffix:semicolon
multiline_comment|/* Stack of nested scopes */
DECL|member|prev_op
r_union
id|acpi_parse_object
op_star
id|prev_op
suffix:semicolon
multiline_comment|/* Last op that was processed */
DECL|member|next_op
r_union
id|acpi_parse_object
op_star
id|next_op
suffix:semicolon
multiline_comment|/* next op to be processed */
DECL|member|descending_callback
id|acpi_parse_downwards
id|descending_callback
suffix:semicolon
DECL|member|ascending_callback
id|acpi_parse_upwards
id|ascending_callback
suffix:semicolon
DECL|member|thread
r_struct
id|acpi_thread_state
op_star
id|thread
suffix:semicolon
DECL|member|next
r_struct
id|acpi_walk_state
op_star
id|next
suffix:semicolon
multiline_comment|/* Next walk_state in list */
)brace
suffix:semicolon
multiline_comment|/* Info used by acpi_ps_init_objects */
DECL|struct|acpi_init_walk_info
r_struct
id|acpi_init_walk_info
(brace
DECL|member|method_count
id|u16
id|method_count
suffix:semicolon
DECL|member|device_count
id|u16
id|device_count
suffix:semicolon
DECL|member|op_region_count
id|u16
id|op_region_count
suffix:semicolon
DECL|member|field_count
id|u16
id|field_count
suffix:semicolon
DECL|member|buffer_count
id|u16
id|buffer_count
suffix:semicolon
DECL|member|package_count
id|u16
id|package_count
suffix:semicolon
DECL|member|op_region_init
id|u16
id|op_region_init
suffix:semicolon
DECL|member|field_init
id|u16
id|field_init
suffix:semicolon
DECL|member|buffer_init
id|u16
id|buffer_init
suffix:semicolon
DECL|member|package_init
id|u16
id|package_init
suffix:semicolon
DECL|member|object_count
id|u16
id|object_count
suffix:semicolon
DECL|member|table_desc
r_struct
id|acpi_table_desc
op_star
id|table_desc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Info used by acpi_ns_initialize_devices */
DECL|struct|acpi_device_walk_info
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
r_struct
id|acpi_table_desc
op_star
id|table_desc
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* TBD: [Restructure] Merge with struct above */
DECL|struct|acpi_walk_info
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
DECL|member|display_type
id|u8
id|display_type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Display Types */
DECL|macro|ACPI_DISPLAY_SUMMARY
mdefine_line|#define ACPI_DISPLAY_SUMMARY    0
DECL|macro|ACPI_DISPLAY_OBJECTS
mdefine_line|#define ACPI_DISPLAY_OBJECTS    1
DECL|struct|acpi_get_devices_info
r_struct
id|acpi_get_devices_info
(brace
DECL|member|user_function
id|acpi_walk_callback
id|user_function
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|member|hid
r_char
op_star
id|hid
suffix:semicolon
)brace
suffix:semicolon
DECL|union|acpi_aml_operands
r_union
id|acpi_aml_operands
(brace
DECL|member|operands
r_union
id|acpi_operand_object
op_star
id|operands
(braket
l_int|7
)braket
suffix:semicolon
r_struct
(brace
DECL|member|type
r_struct
id|acpi_object_integer
op_star
id|type
suffix:semicolon
DECL|member|code
r_struct
id|acpi_object_integer
op_star
id|code
suffix:semicolon
DECL|member|argument
r_struct
id|acpi_object_integer
op_star
id|argument
suffix:semicolon
DECL|member|fatal
)brace
id|fatal
suffix:semicolon
r_struct
(brace
DECL|member|source
r_union
id|acpi_operand_object
op_star
id|source
suffix:semicolon
DECL|member|index
r_struct
id|acpi_object_integer
op_star
id|index
suffix:semicolon
DECL|member|target
r_union
id|acpi_operand_object
op_star
id|target
suffix:semicolon
DECL|member|index
)brace
id|index
suffix:semicolon
r_struct
(brace
DECL|member|source
r_union
id|acpi_operand_object
op_star
id|source
suffix:semicolon
DECL|member|index
r_struct
id|acpi_object_integer
op_star
id|index
suffix:semicolon
DECL|member|length
r_struct
id|acpi_object_integer
op_star
id|length
suffix:semicolon
DECL|member|target
r_union
id|acpi_operand_object
op_star
id|target
suffix:semicolon
DECL|member|mid
)brace
id|mid
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Internal method parameter list */
DECL|struct|acpi_parameter_info
r_struct
id|acpi_parameter_info
(brace
DECL|member|node
r_struct
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
DECL|member|parameters
r_union
id|acpi_operand_object
op_star
op_star
id|parameters
suffix:semicolon
DECL|member|return_object
r_union
id|acpi_operand_object
op_star
id|return_object
suffix:semicolon
DECL|member|parameter_type
id|u8
id|parameter_type
suffix:semicolon
DECL|member|return_object_type
id|u8
id|return_object_type
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Types for parameter_type above */
DECL|macro|ACPI_PARAM_ARGS
mdefine_line|#define ACPI_PARAM_ARGS                 0
DECL|macro|ACPI_PARAM_GPE
mdefine_line|#define ACPI_PARAM_GPE                  1
macro_line|#endif
eof
