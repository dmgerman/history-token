multiline_comment|/******************************************************************************&n; *&n; * Name: aclocal.h - Internal data types used across the ACPI subsystem&n; *       $Revision: 167 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACLOCAL_H__
DECL|macro|__ACLOCAL_H__
mdefine_line|#define __ACLOCAL_H__
DECL|macro|WAIT_FOREVER
mdefine_line|#define WAIT_FOREVER                    ((u32) -1)
DECL|typedef|acpi_mutex
r_typedef
r_void
op_star
id|acpi_mutex
suffix:semicolon
DECL|typedef|ACPI_MUTEX_HANDLE
r_typedef
id|u32
id|ACPI_MUTEX_HANDLE
suffix:semicolon
DECL|macro|ACPI_MEMORY_MODE
mdefine_line|#define ACPI_MEMORY_MODE                0x01
DECL|macro|ACPI_LOGICAL_ADDRESSING
mdefine_line|#define ACPI_LOGICAL_ADDRESSING         0x00
DECL|macro|ACPI_PHYSICAL_ADDRESSING
mdefine_line|#define ACPI_PHYSICAL_ADDRESSING        0x01
multiline_comment|/* Total number of aml opcodes defined */
DECL|macro|AML_NUM_OPCODES
mdefine_line|#define AML_NUM_OPCODES                 0x7E
multiline_comment|/*****************************************************************************&n; *&n; * Mutex typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/*&n; * Predefined handles for the mutex objects used within the subsystem&n; * All mutex objects are automatically created by Acpi_ut_mutex_initialize.&n; *&n; * The acquire/release ordering protocol is implied via this list.  Mutexes&n; * with a lower value must be acquired before mutexes with a higher value.&n; *&n; * NOTE: any changes here must be reflected in the Acpi_gbl_Mutex_names table also!&n; */
DECL|macro|ACPI_MTX_EXECUTE
mdefine_line|#define ACPI_MTX_EXECUTE                0
DECL|macro|ACPI_MTX_INTERPRETER
mdefine_line|#define ACPI_MTX_INTERPRETER            1
DECL|macro|ACPI_MTX_PARSER
mdefine_line|#define ACPI_MTX_PARSER                 2
DECL|macro|ACPI_MTX_DISPATCHER
mdefine_line|#define ACPI_MTX_DISPATCHER             3
DECL|macro|ACPI_MTX_TABLES
mdefine_line|#define ACPI_MTX_TABLES                 4
DECL|macro|ACPI_MTX_OP_REGIONS
mdefine_line|#define ACPI_MTX_OP_REGIONS             5
DECL|macro|ACPI_MTX_NAMESPACE
mdefine_line|#define ACPI_MTX_NAMESPACE              6
DECL|macro|ACPI_MTX_EVENTS
mdefine_line|#define ACPI_MTX_EVENTS                 7
DECL|macro|ACPI_MTX_HARDWARE
mdefine_line|#define ACPI_MTX_HARDWARE               8
DECL|macro|ACPI_MTX_CACHES
mdefine_line|#define ACPI_MTX_CACHES                 9
DECL|macro|ACPI_MTX_MEMORY
mdefine_line|#define ACPI_MTX_MEMORY                 10
DECL|macro|ACPI_MTX_DEBUG_CMD_COMPLETE
mdefine_line|#define ACPI_MTX_DEBUG_CMD_COMPLETE     11
DECL|macro|ACPI_MTX_DEBUG_CMD_READY
mdefine_line|#define ACPI_MTX_DEBUG_CMD_READY        12
DECL|macro|MAX_MTX
mdefine_line|#define MAX_MTX                         12
DECL|macro|NUM_MTX
mdefine_line|#define NUM_MTX                         MAX_MTX+1
macro_line|#if defined(ACPI_DEBUG) || defined(ENABLE_DEBUGGER)
macro_line|#ifdef DEFINE_ACPI_GLOBALS
multiline_comment|/* Names for the mutexes used in the subsystem */
DECL|variable|acpi_gbl_mutex_names
r_static
id|NATIVE_CHAR
op_star
id|acpi_gbl_mutex_names
(braket
)braket
op_assign
(brace
l_string|&quot;ACPI_MTX_Execute&quot;
comma
l_string|&quot;ACPI_MTX_Interpreter&quot;
comma
l_string|&quot;ACPI_MTX_Parser&quot;
comma
l_string|&quot;ACPI_MTX_Dispatcher&quot;
comma
l_string|&quot;ACPI_MTX_Tables&quot;
comma
l_string|&quot;ACPI_MTX_Op_regions&quot;
comma
l_string|&quot;ACPI_MTX_Namespace&quot;
comma
l_string|&quot;ACPI_MTX_Events&quot;
comma
l_string|&quot;ACPI_MTX_Hardware&quot;
comma
l_string|&quot;ACPI_MTX_Caches&quot;
comma
l_string|&quot;ACPI_MTX_Memory&quot;
comma
l_string|&quot;ACPI_MTX_Debug_cmd_complete&quot;
comma
l_string|&quot;ACPI_MTX_Debug_cmd_ready&quot;
comma
)brace
suffix:semicolon
macro_line|#endif
macro_line|#endif
multiline_comment|/* Table for the global mutexes */
DECL|struct|acpi_mutex_info
r_typedef
r_struct
id|acpi_mutex_info
(brace
DECL|member|mutex
id|acpi_mutex
id|mutex
suffix:semicolon
DECL|member|use_count
id|u32
id|use_count
suffix:semicolon
DECL|member|owner_id
id|u32
id|owner_id
suffix:semicolon
DECL|typedef|acpi_mutex_info
)brace
id|acpi_mutex_info
suffix:semicolon
multiline_comment|/* This owner ID means that the mutex is not in use (unlocked) */
DECL|macro|ACPI_MUTEX_NOT_ACQUIRED
mdefine_line|#define ACPI_MUTEX_NOT_ACQUIRED         (u32) (-1)
multiline_comment|/* Lock flag parameter for various interfaces */
DECL|macro|ACPI_MTX_DO_NOT_LOCK
mdefine_line|#define ACPI_MTX_DO_NOT_LOCK            0
DECL|macro|ACPI_MTX_LOCK
mdefine_line|#define ACPI_MTX_LOCK                   1
DECL|typedef|acpi_owner_id
r_typedef
id|u16
id|acpi_owner_id
suffix:semicolon
DECL|macro|ACPI_OWNER_TYPE_TABLE
mdefine_line|#define ACPI_OWNER_TYPE_TABLE           0x0
DECL|macro|ACPI_OWNER_TYPE_METHOD
mdefine_line|#define ACPI_OWNER_TYPE_METHOD          0x1
DECL|macro|ACPI_FIRST_METHOD_ID
mdefine_line|#define ACPI_FIRST_METHOD_ID            0x0000
DECL|macro|ACPI_FIRST_TABLE_ID
mdefine_line|#define ACPI_FIRST_TABLE_ID             0x8000
multiline_comment|/* TBD: [Restructure] get rid of the need for this! */
DECL|macro|TABLE_ID_DSDT
mdefine_line|#define TABLE_ID_DSDT                   (acpi_owner_id) 0x8000
multiline_comment|/* Field access granularities */
DECL|macro|ACPI_FIELD_BYTE_GRANULARITY
mdefine_line|#define ACPI_FIELD_BYTE_GRANULARITY     1
DECL|macro|ACPI_FIELD_WORD_GRANULARITY
mdefine_line|#define ACPI_FIELD_WORD_GRANULARITY     2
DECL|macro|ACPI_FIELD_DWORD_GRANULARITY
mdefine_line|#define ACPI_FIELD_DWORD_GRANULARITY    4
DECL|macro|ACPI_FIELD_QWORD_GRANULARITY
mdefine_line|#define ACPI_FIELD_QWORD_GRANULARITY    8
multiline_comment|/*****************************************************************************&n; *&n; * Namespace typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/* Operational modes of the AML interpreter/scanner */
r_typedef
r_enum
(brace
DECL|enumerator|ACPI_IMODE_LOAD_PASS1
id|ACPI_IMODE_LOAD_PASS1
op_assign
l_int|0x01
comma
DECL|enumerator|ACPI_IMODE_LOAD_PASS2
id|ACPI_IMODE_LOAD_PASS2
op_assign
l_int|0x02
comma
DECL|enumerator|ACPI_IMODE_EXECUTE
id|ACPI_IMODE_EXECUTE
op_assign
l_int|0x0E
DECL|typedef|acpi_interpreter_mode
)brace
id|acpi_interpreter_mode
suffix:semicolon
multiline_comment|/*&n; * The Node describes a named object that appears in the AML&n; * An Acpi_node is used to store Nodes.&n; *&n; * Data_type is used to differentiate between internal descriptors, and MUST&n; * be the first byte in this structure.&n; */
DECL|union|acpi_name_union
r_typedef
r_union
id|acpi_name_union
(brace
DECL|member|integer
id|u32
id|integer
suffix:semicolon
DECL|member|ascii
r_char
id|ascii
(braket
l_int|4
)braket
suffix:semicolon
DECL|typedef|ACPI_NAME_UNION
)brace
id|ACPI_NAME_UNION
suffix:semicolon
DECL|struct|acpi_node
r_typedef
r_struct
id|acpi_node
(brace
DECL|member|descriptor
id|u8
id|descriptor
suffix:semicolon
multiline_comment|/* Used to differentiate object descriptor types */
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* Type associated with this name */
DECL|member|owner_id
id|u16
id|owner_id
suffix:semicolon
DECL|member|name
id|ACPI_NAME_UNION
id|name
suffix:semicolon
multiline_comment|/* ACPI Name, always 4 chars per ACPI spec */
DECL|member|object
r_union
id|acpi_operand_obj
op_star
id|object
suffix:semicolon
multiline_comment|/* Pointer to attached ACPI object (optional) */
DECL|member|child
r_struct
id|acpi_node
op_star
id|child
suffix:semicolon
multiline_comment|/* first child */
DECL|member|peer
r_struct
id|acpi_node
op_star
id|peer
suffix:semicolon
multiline_comment|/* Next peer*/
DECL|member|reference_count
id|u16
id|reference_count
suffix:semicolon
multiline_comment|/* Current count of references and children */
DECL|member|flags
id|u8
id|flags
suffix:semicolon
DECL|typedef|acpi_namespace_node
)brace
id|acpi_namespace_node
suffix:semicolon
DECL|macro|ACPI_ENTRY_NOT_FOUND
mdefine_line|#define ACPI_ENTRY_NOT_FOUND            NULL
multiline_comment|/* Node flags */
DECL|macro|ANOBJ_RESERVED
mdefine_line|#define ANOBJ_RESERVED                  0x01
DECL|macro|ANOBJ_END_OF_PEER_LIST
mdefine_line|#define ANOBJ_END_OF_PEER_LIST          0x02
DECL|macro|ANOBJ_DATA_WIDTH_32
mdefine_line|#define ANOBJ_DATA_WIDTH_32             0x04     /* Parent table is 64-bits */
DECL|macro|ANOBJ_METHOD_ARG
mdefine_line|#define ANOBJ_METHOD_ARG                0x08
DECL|macro|ANOBJ_METHOD_LOCAL
mdefine_line|#define ANOBJ_METHOD_LOCAL              0x10
DECL|macro|ANOBJ_METHOD_NO_RETVAL
mdefine_line|#define ANOBJ_METHOD_NO_RETVAL          0x20
DECL|macro|ANOBJ_METHOD_SOME_NO_RETVAL
mdefine_line|#define ANOBJ_METHOD_SOME_NO_RETVAL     0x40
DECL|macro|ANOBJ_IS_BIT_OFFSET
mdefine_line|#define ANOBJ_IS_BIT_OFFSET             0x80
multiline_comment|/*&n; * ACPI Table Descriptor.  One per ACPI table&n; */
DECL|struct|acpi_table_desc
r_typedef
r_struct
id|acpi_table_desc
(brace
DECL|member|prev
r_struct
id|acpi_table_desc
op_star
id|prev
suffix:semicolon
DECL|member|next
r_struct
id|acpi_table_desc
op_star
id|next
suffix:semicolon
DECL|member|installed_desc
r_struct
id|acpi_table_desc
op_star
id|installed_desc
suffix:semicolon
DECL|member|pointer
id|acpi_table_header
op_star
id|pointer
suffix:semicolon
DECL|member|base_pointer
r_void
op_star
id|base_pointer
suffix:semicolon
DECL|member|aml_start
id|u8
op_star
id|aml_start
suffix:semicolon
DECL|member|physical_address
id|u64
id|physical_address
suffix:semicolon
DECL|member|aml_length
id|u32
id|aml_length
suffix:semicolon
DECL|member|length
id|ACPI_SIZE
id|length
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|table_id
id|acpi_owner_id
id|table_id
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|allocation
id|u8
id|allocation
suffix:semicolon
DECL|member|loaded_into_namespace
id|u8
id|loaded_into_namespace
suffix:semicolon
DECL|typedef|acpi_table_desc
)brace
id|acpi_table_desc
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|search_for
id|NATIVE_CHAR
op_star
id|search_for
suffix:semicolon
DECL|member|list
id|acpi_handle
op_star
id|list
suffix:semicolon
DECL|member|count
id|u32
op_star
id|count
suffix:semicolon
DECL|typedef|acpi_find_context
)brace
id|acpi_find_context
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
DECL|typedef|acpi_ns_search_data
)brace
id|acpi_ns_search_data
suffix:semicolon
multiline_comment|/*&n; * Predefined Namespace items&n; */
r_typedef
r_struct
(brace
DECL|member|name
id|NATIVE_CHAR
op_star
id|name
suffix:semicolon
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|val
id|NATIVE_CHAR
op_star
id|val
suffix:semicolon
DECL|typedef|acpi_predefined_names
)brace
id|acpi_predefined_names
suffix:semicolon
multiline_comment|/* Object types used during package copies */
DECL|macro|ACPI_COPY_TYPE_SIMPLE
mdefine_line|#define ACPI_COPY_TYPE_SIMPLE           0
DECL|macro|ACPI_COPY_TYPE_PACKAGE
mdefine_line|#define ACPI_COPY_TYPE_PACKAGE          1
multiline_comment|/* Info structure used to convert external&lt;-&gt;internal namestrings */
DECL|struct|acpi_namestring_info
r_typedef
r_struct
id|acpi_namestring_info
(brace
DECL|member|external_name
id|NATIVE_CHAR
op_star
id|external_name
suffix:semicolon
DECL|member|next_external_char
id|NATIVE_CHAR
op_star
id|next_external_char
suffix:semicolon
DECL|member|internal_name
id|NATIVE_CHAR
op_star
id|internal_name
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|num_segments
id|u32
id|num_segments
suffix:semicolon
DECL|member|num_carats
id|u32
id|num_carats
suffix:semicolon
DECL|member|fully_qualified
id|u8
id|fully_qualified
suffix:semicolon
DECL|typedef|acpi_namestring_info
)brace
id|acpi_namestring_info
suffix:semicolon
multiline_comment|/* Field creation info */
r_typedef
r_struct
(brace
DECL|member|region_node
id|acpi_namespace_node
op_star
id|region_node
suffix:semicolon
DECL|member|field_node
id|acpi_namespace_node
op_star
id|field_node
suffix:semicolon
DECL|member|register_node
id|acpi_namespace_node
op_star
id|register_node
suffix:semicolon
DECL|member|data_register_node
id|acpi_namespace_node
op_star
id|data_register_node
suffix:semicolon
DECL|member|bank_value
id|u32
id|bank_value
suffix:semicolon
DECL|member|field_bit_position
id|u32
id|field_bit_position
suffix:semicolon
DECL|member|field_bit_length
id|u32
id|field_bit_length
suffix:semicolon
DECL|member|field_flags
id|u8
id|field_flags
suffix:semicolon
DECL|member|attribute
id|u8
id|attribute
suffix:semicolon
DECL|member|field_type
id|u8
id|field_type
suffix:semicolon
DECL|typedef|ACPI_CREATE_FIELD_INFO
)brace
id|ACPI_CREATE_FIELD_INFO
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Event typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/* Information about each GPE register block */
r_typedef
r_struct
(brace
DECL|member|address_space_id
id|u8
id|address_space_id
suffix:semicolon
DECL|member|block_address
id|acpi_generic_address
op_star
id|block_address
suffix:semicolon
DECL|member|register_count
id|u16
id|register_count
suffix:semicolon
DECL|member|block_base_number
id|u8
id|block_base_number
suffix:semicolon
DECL|typedef|ACPI_GPE_BLOCK_INFO
)brace
id|ACPI_GPE_BLOCK_INFO
suffix:semicolon
multiline_comment|/* Information about a particular GPE register pair */
r_typedef
r_struct
(brace
DECL|member|status_address
id|acpi_generic_address
id|status_address
suffix:semicolon
multiline_comment|/* Address of status reg */
DECL|member|enable_address
id|acpi_generic_address
id|enable_address
suffix:semicolon
multiline_comment|/* Address of enable reg */
DECL|member|status
id|u8
id|status
suffix:semicolon
multiline_comment|/* Current value of status reg */
DECL|member|enable
id|u8
id|enable
suffix:semicolon
multiline_comment|/* Current value of enable reg */
DECL|member|wake_enable
id|u8
id|wake_enable
suffix:semicolon
multiline_comment|/* Mask of bits to keep enabled when sleeping */
DECL|member|base_gpe_number
id|u8
id|base_gpe_number
suffix:semicolon
multiline_comment|/* Base GPE number for this register */
DECL|typedef|ACPI_GPE_REGISTER_INFO
)brace
id|ACPI_GPE_REGISTER_INFO
suffix:semicolon
DECL|macro|ACPI_GPE_LEVEL_TRIGGERED
mdefine_line|#define ACPI_GPE_LEVEL_TRIGGERED        1
DECL|macro|ACPI_GPE_EDGE_TRIGGERED
mdefine_line|#define ACPI_GPE_EDGE_TRIGGERED         2
multiline_comment|/* Information about each particular GPE level */
r_typedef
r_struct
(brace
DECL|member|method_handle
id|acpi_handle
id|method_handle
suffix:semicolon
multiline_comment|/* Method handle for direct (fast) execution */
DECL|member|handler
id|acpi_gpe_handler
id|handler
suffix:semicolon
multiline_comment|/* Address of handler, if any */
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
multiline_comment|/* Context to be passed to handler */
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* Level or Edge */
DECL|member|bit_mask
id|u8
id|bit_mask
suffix:semicolon
DECL|typedef|ACPI_GPE_NUMBER_INFO
)brace
id|ACPI_GPE_NUMBER_INFO
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|number_index
id|u8
id|number_index
suffix:semicolon
DECL|typedef|ACPI_GPE_INDEX_INFO
)brace
id|ACPI_GPE_INDEX_INFO
suffix:semicolon
multiline_comment|/* Information about each particular fixed event */
r_typedef
r_struct
(brace
DECL|member|handler
id|acpi_event_handler
id|handler
suffix:semicolon
multiline_comment|/* Address of handler. */
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
multiline_comment|/* Context to be passed to handler */
DECL|typedef|ACPI_FIXED_EVENT_HANDLER
)brace
id|ACPI_FIXED_EVENT_HANDLER
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|status_register_id
id|u8
id|status_register_id
suffix:semicolon
DECL|member|enable_register_id
id|u8
id|enable_register_id
suffix:semicolon
DECL|member|status_bit_mask
id|u16
id|status_bit_mask
suffix:semicolon
DECL|member|enable_bit_mask
id|u16
id|enable_bit_mask
suffix:semicolon
DECL|typedef|acpi_fixed_event_info
)brace
id|acpi_fixed_event_info
suffix:semicolon
multiline_comment|/* Information used during field processing */
r_typedef
r_struct
(brace
DECL|member|skip_field
id|u8
id|skip_field
suffix:semicolon
DECL|member|field_flag
id|u8
id|field_flag
suffix:semicolon
DECL|member|pkg_length
id|u32
id|pkg_length
suffix:semicolon
DECL|typedef|acpi_field_info
)brace
id|acpi_field_info
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Generic &quot;state&quot; object for stacks&n; *&n; ****************************************************************************/
DECL|macro|ACPI_CONTROL_NORMAL
mdefine_line|#define ACPI_CONTROL_NORMAL                  0xC0
DECL|macro|ACPI_CONTROL_CONDITIONAL_EXECUTING
mdefine_line|#define ACPI_CONTROL_CONDITIONAL_EXECUTING   0xC1
DECL|macro|ACPI_CONTROL_PREDICATE_EXECUTING
mdefine_line|#define ACPI_CONTROL_PREDICATE_EXECUTING     0xC2
DECL|macro|ACPI_CONTROL_PREDICATE_FALSE
mdefine_line|#define ACPI_CONTROL_PREDICATE_FALSE         0xC3
DECL|macro|ACPI_CONTROL_PREDICATE_TRUE
mdefine_line|#define ACPI_CONTROL_PREDICATE_TRUE          0xC4
multiline_comment|/* Forward declarations */
r_struct
id|acpi_walk_state
suffix:semicolon
r_struct
id|acpi_obj_mutex
suffix:semicolon
r_union
id|acpi_parse_obj
suffix:semicolon
DECL|macro|ACPI_STATE_COMMON
mdefine_line|#define ACPI_STATE_COMMON                  /* Two 32-bit fields and a pointer */&bslash;&n;&t;u8                      data_type;          /* To differentiate various internal objs */&bslash;&n;&t;u8                      flags;      &bslash;&n;&t;u16                     value;      &bslash;&n;&t;u16                     state;      &bslash;&n;&t;u16                     reserved;   &bslash;&n;&t;void                    *next;      &bslash;&n;
DECL|struct|acpi_common_state
r_typedef
r_struct
id|acpi_common_state
(brace
id|ACPI_STATE_COMMON
DECL|typedef|acpi_common_state
)brace
id|acpi_common_state
suffix:semicolon
multiline_comment|/*&n; * Update state - used to traverse complex objects such as packages&n; */
DECL|struct|acpi_update_state
r_typedef
r_struct
id|acpi_update_state
(brace
id|ACPI_STATE_COMMON
DECL|member|object
r_union
id|acpi_operand_obj
op_star
id|object
suffix:semicolon
DECL|typedef|acpi_update_state
)brace
id|acpi_update_state
suffix:semicolon
multiline_comment|/*&n; * Pkg state - used to traverse nested package structures&n; */
DECL|struct|acpi_pkg_state
r_typedef
r_struct
id|acpi_pkg_state
(brace
id|ACPI_STATE_COMMON
DECL|member|source_object
r_union
id|acpi_operand_obj
op_star
id|source_object
suffix:semicolon
DECL|member|dest_object
r_union
id|acpi_operand_obj
op_star
id|dest_object
suffix:semicolon
DECL|member|walk_state
r_struct
id|acpi_walk_state
op_star
id|walk_state
suffix:semicolon
DECL|member|this_target_obj
r_void
op_star
id|this_target_obj
suffix:semicolon
DECL|member|num_packages
id|u32
id|num_packages
suffix:semicolon
DECL|member|index
id|u16
id|index
suffix:semicolon
DECL|typedef|acpi_pkg_state
)brace
id|acpi_pkg_state
suffix:semicolon
multiline_comment|/*&n; * Control state - one per if/else and while constructs.&n; * Allows nesting of these constructs&n; */
DECL|struct|acpi_control_state
r_typedef
r_struct
id|acpi_control_state
(brace
id|ACPI_STATE_COMMON
DECL|member|predicate_op
r_union
id|acpi_parse_obj
op_star
id|predicate_op
suffix:semicolon
DECL|member|aml_predicate_start
id|u8
op_star
id|aml_predicate_start
suffix:semicolon
multiline_comment|/* Start of if/while predicate */
DECL|member|package_end
id|u8
op_star
id|package_end
suffix:semicolon
multiline_comment|/* End of if/while block */
DECL|member|opcode
id|u16
id|opcode
suffix:semicolon
DECL|typedef|acpi_control_state
)brace
id|acpi_control_state
suffix:semicolon
multiline_comment|/*&n; * Scope state - current scope during namespace lookups&n; */
DECL|struct|acpi_scope_state
r_typedef
r_struct
id|acpi_scope_state
(brace
id|ACPI_STATE_COMMON
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
DECL|typedef|acpi_scope_state
)brace
id|acpi_scope_state
suffix:semicolon
DECL|struct|acpi_pscope_state
r_typedef
r_struct
id|acpi_pscope_state
(brace
id|ACPI_STATE_COMMON
DECL|member|op
r_union
id|acpi_parse_obj
op_star
id|op
suffix:semicolon
multiline_comment|/* current op being parsed */
DECL|member|arg_end
id|u8
op_star
id|arg_end
suffix:semicolon
multiline_comment|/* current argument end */
DECL|member|pkg_end
id|u8
op_star
id|pkg_end
suffix:semicolon
multiline_comment|/* current package end */
DECL|member|arg_list
id|u32
id|arg_list
suffix:semicolon
multiline_comment|/* next argument to parse */
DECL|member|arg_count
id|u32
id|arg_count
suffix:semicolon
multiline_comment|/* Number of fixed arguments */
DECL|typedef|acpi_pscope_state
)brace
id|acpi_pscope_state
suffix:semicolon
multiline_comment|/*&n; * Thread state - one per thread across multiple walk states.  Multiple walk&n; * states are created when there are nested control methods executing.&n; */
DECL|struct|acpi_thread_state
r_typedef
r_struct
id|acpi_thread_state
(brace
id|ACPI_STATE_COMMON
DECL|member|walk_state_list
r_struct
id|acpi_walk_state
op_star
id|walk_state_list
suffix:semicolon
multiline_comment|/* Head of list of Walk_states for this thread */
DECL|member|acquired_mutex_list
r_union
id|acpi_operand_obj
op_star
id|acquired_mutex_list
suffix:semicolon
multiline_comment|/* List of all currently acquired mutexes */
DECL|member|thread_id
id|u32
id|thread_id
suffix:semicolon
multiline_comment|/* Running thread ID */
DECL|member|current_sync_level
id|u16
id|current_sync_level
suffix:semicolon
multiline_comment|/* Mutex Sync (nested acquire) level */
DECL|typedef|ACPI_THREAD_STATE
)brace
id|ACPI_THREAD_STATE
suffix:semicolon
multiline_comment|/*&n; * Result values - used to accumulate the results of nested&n; * AML arguments&n; */
DECL|struct|acpi_result_values
r_typedef
r_struct
id|acpi_result_values
(brace
id|ACPI_STATE_COMMON
DECL|member|obj_desc
r_union
id|acpi_operand_obj
op_star
id|obj_desc
(braket
id|OBJ_NUM_OPERANDS
)braket
suffix:semicolon
DECL|member|num_results
id|u8
id|num_results
suffix:semicolon
DECL|member|last_insert
id|u8
id|last_insert
suffix:semicolon
DECL|typedef|acpi_result_values
)brace
id|acpi_result_values
suffix:semicolon
r_typedef
DECL|typedef|acpi_parse_downwards
id|acpi_status
(paren
op_star
id|acpi_parse_downwards
)paren
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_parse_obj
op_star
op_star
id|out_op
)paren
suffix:semicolon
r_typedef
DECL|typedef|acpi_parse_upwards
id|acpi_status
(paren
op_star
id|acpi_parse_upwards
)paren
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n; * Notify info - used to pass info to the deferred notify&n; * handler/dispatcher.&n; */
DECL|struct|acpi_notify_info
r_typedef
r_struct
id|acpi_notify_info
(brace
id|ACPI_STATE_COMMON
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
DECL|member|handler_obj
r_union
id|acpi_operand_obj
op_star
id|handler_obj
suffix:semicolon
DECL|typedef|acpi_notify_info
)brace
id|acpi_notify_info
suffix:semicolon
multiline_comment|/* Generic state is union of structs above */
DECL|union|acpi_gen_state
r_typedef
r_union
id|acpi_gen_state
(brace
DECL|member|common
id|acpi_common_state
id|common
suffix:semicolon
DECL|member|control
id|acpi_control_state
id|control
suffix:semicolon
DECL|member|update
id|acpi_update_state
id|update
suffix:semicolon
DECL|member|scope
id|acpi_scope_state
id|scope
suffix:semicolon
DECL|member|parse_scope
id|acpi_pscope_state
id|parse_scope
suffix:semicolon
DECL|member|pkg
id|acpi_pkg_state
id|pkg
suffix:semicolon
DECL|member|thread
id|ACPI_THREAD_STATE
id|thread
suffix:semicolon
DECL|member|results
id|acpi_result_values
id|results
suffix:semicolon
DECL|member|notify
id|acpi_notify_info
id|notify
suffix:semicolon
DECL|typedef|acpi_generic_state
)brace
id|acpi_generic_state
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Interpreter typedefs and structs&n; *&n; ****************************************************************************/
r_typedef
DECL|typedef|ACPI_EXECUTE_OP
id|acpi_status
(paren
op_star
id|ACPI_EXECUTE_OP
)paren
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Parser typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/*&n; * AML opcode, name, and argument layout&n; */
DECL|struct|acpi_opcode_info
r_typedef
r_struct
id|acpi_opcode_info
(brace
macro_line|#ifdef _OPCODE_NAMES
DECL|member|name
id|NATIVE_CHAR
op_star
id|name
suffix:semicolon
multiline_comment|/* Opcode name (debug only) */
macro_line|#endif
DECL|member|parse_args
id|u32
id|parse_args
suffix:semicolon
multiline_comment|/* Grammar/Parse time arguments */
DECL|member|runtime_args
id|u32
id|runtime_args
suffix:semicolon
multiline_comment|/* Interpret time arguments */
DECL|member|flags
id|u32
id|flags
suffix:semicolon
multiline_comment|/* Misc flags */
DECL|member|object_type
id|u8
id|object_type
suffix:semicolon
multiline_comment|/* Corresponding internal object type */
DECL|member|class
id|u8
r_class
suffix:semicolon
multiline_comment|/* Opcode class */
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* Opcode type */
DECL|typedef|acpi_opcode_info
)brace
id|acpi_opcode_info
suffix:semicolon
DECL|union|acpi_parse_val
r_typedef
r_union
id|acpi_parse_val
(brace
DECL|member|integer
id|acpi_integer
id|integer
suffix:semicolon
multiline_comment|/* integer constant (Up to 64 bits) */
DECL|member|integer64
id|uint64_struct
id|integer64
suffix:semicolon
multiline_comment|/* Structure overlay for 2 32-bit Dwords */
DECL|member|integer32
id|u32
id|integer32
suffix:semicolon
multiline_comment|/* integer constant, 32 bits only */
DECL|member|integer16
id|u16
id|integer16
suffix:semicolon
multiline_comment|/* integer constant, 16 bits only */
DECL|member|integer8
id|u8
id|integer8
suffix:semicolon
multiline_comment|/* integer constant, 8 bits only */
DECL|member|size
id|u32
id|size
suffix:semicolon
multiline_comment|/* bytelist or field size */
DECL|member|string
id|NATIVE_CHAR
op_star
id|string
suffix:semicolon
multiline_comment|/* NULL terminated string */
DECL|member|buffer
id|u8
op_star
id|buffer
suffix:semicolon
multiline_comment|/* buffer or string */
DECL|member|name
id|NATIVE_CHAR
op_star
id|name
suffix:semicolon
multiline_comment|/* NULL terminated string */
DECL|member|arg
r_union
id|acpi_parse_obj
op_star
id|arg
suffix:semicolon
multiline_comment|/* arguments and contained ops */
DECL|typedef|acpi_parse_value
)brace
id|acpi_parse_value
suffix:semicolon
DECL|macro|ACPI_PARSE_COMMON
mdefine_line|#define ACPI_PARSE_COMMON &bslash;&n;&t;u8                      data_type;      /* To differentiate various internal objs */&bslash;&n;&t;u8                      flags;          /* Type of Op */&bslash;&n;&t;u16                     aml_opcode;     /* AML opcode */&bslash;&n;&t;u32                     aml_offset;     /* offset of declaration in AML */&bslash;&n;&t;union acpi_parse_obj    *parent;        /* parent op */&bslash;&n;&t;union acpi_parse_obj    *next;          /* next op */&bslash;&n;&t;ACPI_DEBUG_ONLY_MEMBERS (&bslash;&n;&t;NATIVE_CHAR             aml_op_name[16]) /* op name (debug only) */&bslash;&n;&t;&t;&t;  /* NON-DEBUG members below: */&bslash;&n;&t;acpi_namespace_node     *node;          /* for use by interpreter */&bslash;&n;&t;acpi_parse_value        value;          /* Value or args associated with the opcode */&bslash;&n;
multiline_comment|/*&n; * generic operation (eg. If, While, Store)&n; */
DECL|struct|acpi_parseobj_common
r_typedef
r_struct
id|acpi_parseobj_common
(brace
id|ACPI_PARSE_COMMON
DECL|typedef|ACPI_PARSE_OBJ_COMMON
)brace
id|ACPI_PARSE_OBJ_COMMON
suffix:semicolon
multiline_comment|/*&n; * Extended Op for named ops (Scope, Method, etc.), deferred ops (Methods and Op_regions),&n; * and bytelists.&n; */
DECL|struct|acpi_parseobj_named
r_typedef
r_struct
id|acpi_parseobj_named
(brace
id|ACPI_PARSE_COMMON
DECL|member|data
id|u8
op_star
id|data
suffix:semicolon
multiline_comment|/* AML body or bytelist data */
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* AML length */
DECL|member|name
id|u32
id|name
suffix:semicolon
multiline_comment|/* 4-byte name or zero if no name */
DECL|typedef|ACPI_PARSE_OBJ_NAMED
)brace
id|ACPI_PARSE_OBJ_NAMED
suffix:semicolon
multiline_comment|/* The parse node is the fundamental element of the parse tree */
DECL|struct|acpi_parseobj_asl
r_typedef
r_struct
id|acpi_parseobj_asl
(brace
id|ACPI_PARSE_COMMON
DECL|member|child
r_union
id|acpi_parse_obj
op_star
id|child
suffix:semicolon
DECL|member|parent_method
r_union
id|acpi_parse_obj
op_star
id|parent_method
suffix:semicolon
DECL|member|filename
r_char
op_star
id|filename
suffix:semicolon
DECL|member|external_name
r_char
op_star
id|external_name
suffix:semicolon
DECL|member|namepath
r_char
op_star
id|namepath
suffix:semicolon
DECL|member|extra_value
id|u32
id|extra_value
suffix:semicolon
DECL|member|column
id|u32
id|column
suffix:semicolon
DECL|member|line_number
id|u32
id|line_number
suffix:semicolon
DECL|member|logical_line_number
id|u32
id|logical_line_number
suffix:semicolon
DECL|member|logical_byte_offset
id|u32
id|logical_byte_offset
suffix:semicolon
DECL|member|end_line
id|u32
id|end_line
suffix:semicolon
DECL|member|end_logical_line
id|u32
id|end_logical_line
suffix:semicolon
DECL|member|parse_opcode
id|u16
id|parse_opcode
suffix:semicolon
DECL|member|acpi_btype
id|u32
id|acpi_btype
suffix:semicolon
DECL|member|aml_length
id|u32
id|aml_length
suffix:semicolon
DECL|member|aml_subtree_length
id|u32
id|aml_subtree_length
suffix:semicolon
DECL|member|final_aml_length
id|u32
id|final_aml_length
suffix:semicolon
DECL|member|final_aml_offset
id|u32
id|final_aml_offset
suffix:semicolon
DECL|member|aml_opcode_length
id|u8
id|aml_opcode_length
suffix:semicolon
DECL|member|aml_pkg_len_bytes
id|u8
id|aml_pkg_len_bytes
suffix:semicolon
DECL|member|compile_flags
id|u16
id|compile_flags
suffix:semicolon
DECL|member|extra
id|u8
id|extra
suffix:semicolon
DECL|member|parse_op_name
r_char
id|parse_op_name
(braket
l_int|12
)braket
suffix:semicolon
DECL|typedef|ACPI_PARSE_OBJ_ASL
)brace
id|ACPI_PARSE_OBJ_ASL
suffix:semicolon
DECL|union|acpi_parse_obj
r_typedef
r_union
id|acpi_parse_obj
(brace
DECL|member|common
id|ACPI_PARSE_OBJ_COMMON
id|common
suffix:semicolon
DECL|member|named
id|ACPI_PARSE_OBJ_NAMED
id|named
suffix:semicolon
DECL|member|asl
id|ACPI_PARSE_OBJ_ASL
id|asl
suffix:semicolon
DECL|typedef|acpi_parse_object
)brace
id|acpi_parse_object
suffix:semicolon
multiline_comment|/*&n; * Parse state - one state per parser invocation and each control&n; * method.&n; */
DECL|struct|acpi_parse_state
r_typedef
r_struct
id|acpi_parse_state
(brace
DECL|member|aml_size
id|u32
id|aml_size
suffix:semicolon
DECL|member|aml_start
id|u8
op_star
id|aml_start
suffix:semicolon
multiline_comment|/* first AML byte */
DECL|member|aml
id|u8
op_star
id|aml
suffix:semicolon
multiline_comment|/* next AML byte */
DECL|member|aml_end
id|u8
op_star
id|aml_end
suffix:semicolon
multiline_comment|/* (last + 1) AML byte */
DECL|member|pkg_start
id|u8
op_star
id|pkg_start
suffix:semicolon
multiline_comment|/* current package begin */
DECL|member|pkg_end
id|u8
op_star
id|pkg_end
suffix:semicolon
multiline_comment|/* current package end */
DECL|member|start_op
r_union
id|acpi_parse_obj
op_star
id|start_op
suffix:semicolon
multiline_comment|/* root of parse tree */
DECL|member|start_node
r_struct
id|acpi_node
op_star
id|start_node
suffix:semicolon
DECL|member|scope
r_union
id|acpi_gen_state
op_star
id|scope
suffix:semicolon
multiline_comment|/* current scope */
DECL|member|start_scope
r_union
id|acpi_parse_obj
op_star
id|start_scope
suffix:semicolon
DECL|typedef|acpi_parse_state
)brace
id|acpi_parse_state
suffix:semicolon
multiline_comment|/* Parse object flags */
DECL|macro|ACPI_PARSEOP_GENERIC
mdefine_line|#define ACPI_PARSEOP_GENERIC                    0x01
DECL|macro|ACPI_PARSEOP_NAMED
mdefine_line|#define ACPI_PARSEOP_NAMED                      0x02
DECL|macro|ACPI_PARSEOP_DEFERRED
mdefine_line|#define ACPI_PARSEOP_DEFERRED                   0x04
DECL|macro|ACPI_PARSEOP_BYTELIST
mdefine_line|#define ACPI_PARSEOP_BYTELIST                   0x08
DECL|macro|ACPI_PARSEOP_IN_CACHE
mdefine_line|#define ACPI_PARSEOP_IN_CACHE                   0x80
multiline_comment|/*****************************************************************************&n; *&n; * Hardware (ACPI registers) and PNP&n; *&n; ****************************************************************************/
DECL|macro|PCI_ROOT_HID_STRING
mdefine_line|#define PCI_ROOT_HID_STRING         &quot;PNP0A03&quot;
r_typedef
r_struct
(brace
DECL|member|parent_register
id|u8
id|parent_register
suffix:semicolon
DECL|member|bit_position
id|u8
id|bit_position
suffix:semicolon
DECL|member|access_bit_mask
id|u16
id|access_bit_mask
suffix:semicolon
DECL|typedef|ACPI_BIT_REGISTER_INFO
)brace
id|ACPI_BIT_REGISTER_INFO
suffix:semicolon
multiline_comment|/*&n; * Register IDs&n; * These are the full ACPI registers&n; */
DECL|macro|ACPI_REGISTER_PM1_STATUS
mdefine_line|#define ACPI_REGISTER_PM1_STATUS                0x01
DECL|macro|ACPI_REGISTER_PM1_ENABLE
mdefine_line|#define ACPI_REGISTER_PM1_ENABLE                0x02
DECL|macro|ACPI_REGISTER_PM1_CONTROL
mdefine_line|#define ACPI_REGISTER_PM1_CONTROL               0x03
DECL|macro|ACPI_REGISTER_PM1A_CONTROL
mdefine_line|#define ACPI_REGISTER_PM1A_CONTROL              0x04
DECL|macro|ACPI_REGISTER_PM1B_CONTROL
mdefine_line|#define ACPI_REGISTER_PM1B_CONTROL              0x05
DECL|macro|ACPI_REGISTER_PM2_CONTROL
mdefine_line|#define ACPI_REGISTER_PM2_CONTROL               0x06
DECL|macro|ACPI_REGISTER_PM_TIMER
mdefine_line|#define ACPI_REGISTER_PM_TIMER                  0x07
DECL|macro|ACPI_REGISTER_PROCESSOR_BLOCK
mdefine_line|#define ACPI_REGISTER_PROCESSOR_BLOCK           0x08
DECL|macro|ACPI_REGISTER_SMI_COMMAND_BLOCK
mdefine_line|#define ACPI_REGISTER_SMI_COMMAND_BLOCK         0x09
multiline_comment|/* Masks used to access the Bit_registers */
DECL|macro|ACPI_BITMASK_TIMER_STATUS
mdefine_line|#define ACPI_BITMASK_TIMER_STATUS               0x0001
DECL|macro|ACPI_BITMASK_BUS_MASTER_STATUS
mdefine_line|#define ACPI_BITMASK_BUS_MASTER_STATUS          0x0010
DECL|macro|ACPI_BITMASK_GLOBAL_LOCK_STATUS
mdefine_line|#define ACPI_BITMASK_GLOBAL_LOCK_STATUS         0x0020
DECL|macro|ACPI_BITMASK_POWER_BUTTON_STATUS
mdefine_line|#define ACPI_BITMASK_POWER_BUTTON_STATUS        0x0100
DECL|macro|ACPI_BITMASK_SLEEP_BUTTON_STATUS
mdefine_line|#define ACPI_BITMASK_SLEEP_BUTTON_STATUS        0x0200
DECL|macro|ACPI_BITMASK_RT_CLOCK_STATUS
mdefine_line|#define ACPI_BITMASK_RT_CLOCK_STATUS            0x0400
DECL|macro|ACPI_BITMASK_WAKE_STATUS
mdefine_line|#define ACPI_BITMASK_WAKE_STATUS                0x8000
DECL|macro|ACPI_BITMASK_ALL_FIXED_STATUS
mdefine_line|#define ACPI_BITMASK_ALL_FIXED_STATUS           (ACPI_BITMASK_TIMER_STATUS          | &bslash;&n;&t;&t;&t; ACPI_BITMASK_BUS_MASTER_STATUS     | &bslash;&n;&t;&t;&t; ACPI_BITMASK_GLOBAL_LOCK_STATUS    | &bslash;&n;&t;&t;&t; ACPI_BITMASK_POWER_BUTTON_STATUS   | &bslash;&n;&t;&t;&t; ACPI_BITMASK_SLEEP_BUTTON_STATUS   | &bslash;&n;&t;&t;&t; ACPI_BITMASK_RT_CLOCK_STATUS       | &bslash;&n;&t;&t;&t; ACPI_BITMASK_WAKE_STATUS)
DECL|macro|ACPI_BITMASK_TIMER_ENABLE
mdefine_line|#define ACPI_BITMASK_TIMER_ENABLE               0x0001
DECL|macro|ACPI_BITMASK_GLOBAL_LOCK_ENABLE
mdefine_line|#define ACPI_BITMASK_GLOBAL_LOCK_ENABLE         0x0020
DECL|macro|ACPI_BITMASK_POWER_BUTTON_ENABLE
mdefine_line|#define ACPI_BITMASK_POWER_BUTTON_ENABLE        0x0100
DECL|macro|ACPI_BITMASK_SLEEP_BUTTON_ENABLE
mdefine_line|#define ACPI_BITMASK_SLEEP_BUTTON_ENABLE        0x0200
DECL|macro|ACPI_BITMASK_RT_CLOCK_ENABLE
mdefine_line|#define ACPI_BITMASK_RT_CLOCK_ENABLE            0x0400
DECL|macro|ACPI_BITMASK_SCI_ENABLE
mdefine_line|#define ACPI_BITMASK_SCI_ENABLE                 0x0001
DECL|macro|ACPI_BITMASK_BUS_MASTER_RLD
mdefine_line|#define ACPI_BITMASK_BUS_MASTER_RLD             0x0002
DECL|macro|ACPI_BITMASK_GLOBAL_LOCK_RELEASE
mdefine_line|#define ACPI_BITMASK_GLOBAL_LOCK_RELEASE        0x0004
DECL|macro|ACPI_BITMASK_SLEEP_TYPE_X
mdefine_line|#define ACPI_BITMASK_SLEEP_TYPE_X               0x1C00
DECL|macro|ACPI_BITMASK_SLEEP_ENABLE
mdefine_line|#define ACPI_BITMASK_SLEEP_ENABLE               0x2000
DECL|macro|ACPI_BITMASK_ARB_DISABLE
mdefine_line|#define ACPI_BITMASK_ARB_DISABLE                0x0001
multiline_comment|/* Raw bit position of each Bit_register */
DECL|macro|ACPI_BITPOSITION_TIMER_STATUS
mdefine_line|#define ACPI_BITPOSITION_TIMER_STATUS           0x00
DECL|macro|ACPI_BITPOSITION_BUS_MASTER_STATUS
mdefine_line|#define ACPI_BITPOSITION_BUS_MASTER_STATUS      0x04
DECL|macro|ACPI_BITPOSITION_GLOBAL_LOCK_STATUS
mdefine_line|#define ACPI_BITPOSITION_GLOBAL_LOCK_STATUS     0x05
DECL|macro|ACPI_BITPOSITION_POWER_BUTTON_STATUS
mdefine_line|#define ACPI_BITPOSITION_POWER_BUTTON_STATUS    0x08
DECL|macro|ACPI_BITPOSITION_SLEEP_BUTTON_STATUS
mdefine_line|#define ACPI_BITPOSITION_SLEEP_BUTTON_STATUS    0x09
DECL|macro|ACPI_BITPOSITION_RT_CLOCK_STATUS
mdefine_line|#define ACPI_BITPOSITION_RT_CLOCK_STATUS        0x0A
DECL|macro|ACPI_BITPOSITION_WAKE_STATUS
mdefine_line|#define ACPI_BITPOSITION_WAKE_STATUS            0x0F
DECL|macro|ACPI_BITPOSITION_TIMER_ENABLE
mdefine_line|#define ACPI_BITPOSITION_TIMER_ENABLE           0x00
DECL|macro|ACPI_BITPOSITION_GLOBAL_LOCK_ENABLE
mdefine_line|#define ACPI_BITPOSITION_GLOBAL_LOCK_ENABLE     0x05
DECL|macro|ACPI_BITPOSITION_POWER_BUTTON_ENABLE
mdefine_line|#define ACPI_BITPOSITION_POWER_BUTTON_ENABLE    0x08
DECL|macro|ACPI_BITPOSITION_SLEEP_BUTTON_ENABLE
mdefine_line|#define ACPI_BITPOSITION_SLEEP_BUTTON_ENABLE    0x09
DECL|macro|ACPI_BITPOSITION_RT_CLOCK_ENABLE
mdefine_line|#define ACPI_BITPOSITION_RT_CLOCK_ENABLE        0x0A
DECL|macro|ACPI_BITPOSITION_SCI_ENABLE
mdefine_line|#define ACPI_BITPOSITION_SCI_ENABLE             0x00
DECL|macro|ACPI_BITPOSITION_BUS_MASTER_RLD
mdefine_line|#define ACPI_BITPOSITION_BUS_MASTER_RLD         0x01
DECL|macro|ACPI_BITPOSITION_GLOBAL_LOCK_RELEASE
mdefine_line|#define ACPI_BITPOSITION_GLOBAL_LOCK_RELEASE    0x02
DECL|macro|ACPI_BITPOSITION_SLEEP_TYPE_X
mdefine_line|#define ACPI_BITPOSITION_SLEEP_TYPE_X           0x0A
DECL|macro|ACPI_BITPOSITION_SLEEP_ENABLE
mdefine_line|#define ACPI_BITPOSITION_SLEEP_ENABLE           0x0D
DECL|macro|ACPI_BITPOSITION_ARB_DISABLE
mdefine_line|#define ACPI_BITPOSITION_ARB_DISABLE            0x00
multiline_comment|/*****************************************************************************&n; *&n; * Resource descriptors&n; *&n; ****************************************************************************/
multiline_comment|/* Resource_type values */
DECL|macro|ACPI_RESOURCE_TYPE_MEMORY_RANGE
mdefine_line|#define ACPI_RESOURCE_TYPE_MEMORY_RANGE         0
DECL|macro|ACPI_RESOURCE_TYPE_IO_RANGE
mdefine_line|#define ACPI_RESOURCE_TYPE_IO_RANGE             1
DECL|macro|ACPI_RESOURCE_TYPE_BUS_NUMBER_RANGE
mdefine_line|#define ACPI_RESOURCE_TYPE_BUS_NUMBER_RANGE     2
multiline_comment|/* Resource descriptor types and masks */
DECL|macro|ACPI_RDESC_TYPE_LARGE
mdefine_line|#define ACPI_RDESC_TYPE_LARGE                   0x80
DECL|macro|ACPI_RDESC_TYPE_SMALL
mdefine_line|#define ACPI_RDESC_TYPE_SMALL                   0x00
DECL|macro|ACPI_RDESC_TYPE_MASK
mdefine_line|#define ACPI_RDESC_TYPE_MASK                    0x80
DECL|macro|ACPI_RDESC_SMALL_MASK
mdefine_line|#define ACPI_RDESC_SMALL_MASK                   0x78 /* Only bits 6:3 contain the type */
multiline_comment|/*&n; * Small resource descriptor types&n; * Note: The 3 length bits (2:0) must be zero&n; */
DECL|macro|ACPI_RDESC_TYPE_IRQ_FORMAT
mdefine_line|#define ACPI_RDESC_TYPE_IRQ_FORMAT              0x20
DECL|macro|ACPI_RDESC_TYPE_DMA_FORMAT
mdefine_line|#define ACPI_RDESC_TYPE_DMA_FORMAT              0x28
DECL|macro|ACPI_RDESC_TYPE_START_DEPENDENT
mdefine_line|#define ACPI_RDESC_TYPE_START_DEPENDENT         0x30
DECL|macro|ACPI_RDESC_TYPE_END_DEPENDENT
mdefine_line|#define ACPI_RDESC_TYPE_END_DEPENDENT           0x38
DECL|macro|ACPI_RDESC_TYPE_IO_PORT
mdefine_line|#define ACPI_RDESC_TYPE_IO_PORT                 0x40
DECL|macro|ACPI_RDESC_TYPE_FIXED_IO_PORT
mdefine_line|#define ACPI_RDESC_TYPE_FIXED_IO_PORT           0x48
DECL|macro|ACPI_RDESC_TYPE_SMALL_VENDOR
mdefine_line|#define ACPI_RDESC_TYPE_SMALL_VENDOR            0x70
DECL|macro|ACPI_RDESC_TYPE_END_TAG
mdefine_line|#define ACPI_RDESC_TYPE_END_TAG                 0x78
multiline_comment|/*&n; * Large resource descriptor types&n; */
DECL|macro|ACPI_RDESC_TYPE_MEMORY_24
mdefine_line|#define ACPI_RDESC_TYPE_MEMORY_24               0x81
DECL|macro|ACPI_RDESC_TYPE_GENERAL_REGISTER
mdefine_line|#define ACPI_RDESC_TYPE_GENERAL_REGISTER        0x82
DECL|macro|ACPI_RDESC_TYPE_LARGE_VENDOR
mdefine_line|#define ACPI_RDESC_TYPE_LARGE_VENDOR            0x84
DECL|macro|ACPI_RDESC_TYPE_MEMORY_32
mdefine_line|#define ACPI_RDESC_TYPE_MEMORY_32               0x85
DECL|macro|ACPI_RDESC_TYPE_FIXED_MEMORY_32
mdefine_line|#define ACPI_RDESC_TYPE_FIXED_MEMORY_32         0x86
DECL|macro|ACPI_RDESC_TYPE_DWORD_ADDRESS_SPACE
mdefine_line|#define ACPI_RDESC_TYPE_DWORD_ADDRESS_SPACE     0x87
DECL|macro|ACPI_RDESC_TYPE_WORD_ADDRESS_SPACE
mdefine_line|#define ACPI_RDESC_TYPE_WORD_ADDRESS_SPACE      0x88
DECL|macro|ACPI_RDESC_TYPE_EXTENDED_XRUPT
mdefine_line|#define ACPI_RDESC_TYPE_EXTENDED_XRUPT          0x89
DECL|macro|ACPI_RDESC_TYPE_QWORD_ADDRESS_SPACE
mdefine_line|#define ACPI_RDESC_TYPE_QWORD_ADDRESS_SPACE     0x8A
multiline_comment|/* String version of device HIDs and UIDs */
DECL|macro|ACPI_DEVICE_ID_LENGTH
mdefine_line|#define ACPI_DEVICE_ID_LENGTH                   0x09
r_typedef
r_struct
(brace
DECL|member|buffer
r_char
id|buffer
(braket
id|ACPI_DEVICE_ID_LENGTH
)braket
suffix:semicolon
DECL|typedef|acpi_device_id
)brace
id|acpi_device_id
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Miscellaneous&n; *&n; ****************************************************************************/
DECL|macro|ACPI_ASCII_ZERO
mdefine_line|#define ACPI_ASCII_ZERO                      0x30
multiline_comment|/*****************************************************************************&n; *&n; * Debugger&n; *&n; ****************************************************************************/
DECL|struct|dbmethodinfo
r_typedef
r_struct
id|dbmethodinfo
(brace
DECL|member|thread_gate
id|acpi_handle
id|thread_gate
suffix:semicolon
DECL|member|name
id|NATIVE_CHAR
op_star
id|name
suffix:semicolon
DECL|member|args
id|NATIVE_CHAR
op_star
op_star
id|args
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|num_loops
id|u32
id|num_loops
suffix:semicolon
DECL|member|pathname
id|NATIVE_CHAR
id|pathname
(braket
l_int|128
)braket
suffix:semicolon
DECL|typedef|acpi_db_method_info
)brace
id|acpi_db_method_info
suffix:semicolon
DECL|macro|ACPI_DB_REDIRECTABLE_OUTPUT
mdefine_line|#define ACPI_DB_REDIRECTABLE_OUTPUT  0x01
DECL|macro|ACPI_DB_CONSOLE_OUTPUT
mdefine_line|#define ACPI_DB_CONSOLE_OUTPUT       0x02
DECL|macro|ACPI_DB_DUPLICATE_OUTPUT
mdefine_line|#define ACPI_DB_DUPLICATE_OUTPUT     0x03
multiline_comment|/*****************************************************************************&n; *&n; * Debug&n; *&n; ****************************************************************************/
r_typedef
r_struct
(brace
DECL|member|component_id
id|u32
id|component_id
suffix:semicolon
DECL|member|proc_name
id|NATIVE_CHAR
op_star
id|proc_name
suffix:semicolon
DECL|member|module_name
id|NATIVE_CHAR
op_star
id|module_name
suffix:semicolon
DECL|typedef|acpi_debug_print_info
)brace
id|acpi_debug_print_info
suffix:semicolon
multiline_comment|/* Entry for a memory allocation (debug only) */
DECL|macro|ACPI_MEM_MALLOC
mdefine_line|#define ACPI_MEM_MALLOC                      0
DECL|macro|ACPI_MEM_CALLOC
mdefine_line|#define ACPI_MEM_CALLOC                      1
DECL|macro|ACPI_MAX_MODULE_NAME
mdefine_line|#define ACPI_MAX_MODULE_NAME                 16
DECL|macro|ACPI_COMMON_DEBUG_MEM_HEADER
mdefine_line|#define ACPI_COMMON_DEBUG_MEM_HEADER &bslash;&n;&t;struct acpi_debug_mem_block *previous; &bslash;&n;&t;struct acpi_debug_mem_block *next; &bslash;&n;&t;u32                         size; &bslash;&n;&t;u32                         component; &bslash;&n;&t;u32                         line; &bslash;&n;&t;NATIVE_CHAR                 module[ACPI_MAX_MODULE_NAME]; &bslash;&n;&t;u8                          alloc_type;
r_typedef
r_struct
(brace
id|ACPI_COMMON_DEBUG_MEM_HEADER
DECL|typedef|acpi_debug_mem_header
)brace
id|acpi_debug_mem_header
suffix:semicolon
DECL|struct|acpi_debug_mem_block
r_typedef
r_struct
id|acpi_debug_mem_block
(brace
id|ACPI_COMMON_DEBUG_MEM_HEADER
DECL|member|user_space
id|u64
id|user_space
suffix:semicolon
DECL|typedef|acpi_debug_mem_block
)brace
id|acpi_debug_mem_block
suffix:semicolon
DECL|macro|ACPI_MEM_LIST_GLOBAL
mdefine_line|#define ACPI_MEM_LIST_GLOBAL            0
DECL|macro|ACPI_MEM_LIST_NSNODE
mdefine_line|#define ACPI_MEM_LIST_NSNODE            1
DECL|macro|ACPI_MEM_LIST_FIRST_CACHE_LIST
mdefine_line|#define ACPI_MEM_LIST_FIRST_CACHE_LIST  2
DECL|macro|ACPI_MEM_LIST_STATE
mdefine_line|#define ACPI_MEM_LIST_STATE             2
DECL|macro|ACPI_MEM_LIST_PSNODE
mdefine_line|#define ACPI_MEM_LIST_PSNODE            3
DECL|macro|ACPI_MEM_LIST_PSNODE_EXT
mdefine_line|#define ACPI_MEM_LIST_PSNODE_EXT        4
DECL|macro|ACPI_MEM_LIST_OPERAND
mdefine_line|#define ACPI_MEM_LIST_OPERAND           5
DECL|macro|ACPI_MEM_LIST_WALK
mdefine_line|#define ACPI_MEM_LIST_WALK              6
DECL|macro|ACPI_MEM_LIST_MAX
mdefine_line|#define ACPI_MEM_LIST_MAX               6
DECL|macro|ACPI_NUM_MEM_LISTS
mdefine_line|#define ACPI_NUM_MEM_LISTS              7
r_typedef
r_struct
(brace
DECL|member|list_head
r_void
op_star
id|list_head
suffix:semicolon
DECL|member|link_offset
id|u16
id|link_offset
suffix:semicolon
DECL|member|max_cache_depth
id|u16
id|max_cache_depth
suffix:semicolon
DECL|member|cache_depth
id|u16
id|cache_depth
suffix:semicolon
DECL|member|object_size
id|u16
id|object_size
suffix:semicolon
macro_line|#ifdef ACPI_DBG_TRACK_ALLOCATIONS
multiline_comment|/* Statistics for debug memory tracking only */
DECL|member|total_allocated
id|u32
id|total_allocated
suffix:semicolon
DECL|member|total_freed
id|u32
id|total_freed
suffix:semicolon
DECL|member|current_total_size
id|u32
id|current_total_size
suffix:semicolon
DECL|member|cache_requests
id|u32
id|cache_requests
suffix:semicolon
DECL|member|cache_hits
id|u32
id|cache_hits
suffix:semicolon
DECL|member|list_name
r_char
op_star
id|list_name
suffix:semicolon
macro_line|#endif
DECL|typedef|ACPI_MEMORY_LIST
)brace
id|ACPI_MEMORY_LIST
suffix:semicolon
macro_line|#endif /* __ACLOCAL_H__ */
eof
