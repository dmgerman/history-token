multiline_comment|/******************************************************************************&n; *&n; * Name: aclocal.h - Internal data types used across the ACPI subsystem&n; *       $Revision: 104 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACLOCAL_H__
DECL|macro|__ACLOCAL_H__
mdefine_line|#define __ACLOCAL_H__
DECL|macro|WAIT_FOREVER
mdefine_line|#define WAIT_FOREVER                ((u32) -1)
DECL|typedef|ACPI_MUTEX
r_typedef
r_void
op_star
id|ACPI_MUTEX
suffix:semicolon
DECL|typedef|ACPI_MUTEX_HANDLE
r_typedef
id|u32
id|ACPI_MUTEX_HANDLE
suffix:semicolon
multiline_comment|/* Object descriptor types */
DECL|macro|ACPI_CACHED_OBJECT
mdefine_line|#define ACPI_CACHED_OBJECT          0x11    /* ORed in when object is cached */
DECL|macro|ACPI_DESC_TYPE_STATE
mdefine_line|#define ACPI_DESC_TYPE_STATE        0x22
DECL|macro|ACPI_DESC_TYPE_WALK
mdefine_line|#define ACPI_DESC_TYPE_WALK         0x44
DECL|macro|ACPI_DESC_TYPE_PARSER
mdefine_line|#define ACPI_DESC_TYPE_PARSER       0x66
DECL|macro|ACPI_DESC_TYPE_INTERNAL
mdefine_line|#define ACPI_DESC_TYPE_INTERNAL     0x88
DECL|macro|ACPI_DESC_TYPE_NAMED
mdefine_line|#define ACPI_DESC_TYPE_NAMED        0xAA
multiline_comment|/*****************************************************************************&n; *&n; * Mutex typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/*&n; * Predefined handles for the mutex objects used within the subsystem&n; * All mutex objects are automatically created by Acpi_cm_mutex_initialize.&n; * NOTE: any changes here must be reflected in the Acpi_gbl_Mutex_names table also!&n; */
DECL|macro|ACPI_MTX_HARDWARE
mdefine_line|#define ACPI_MTX_HARDWARE           0
DECL|macro|ACPI_MTX_MEMORY
mdefine_line|#define ACPI_MTX_MEMORY             1
DECL|macro|ACPI_MTX_CACHES
mdefine_line|#define ACPI_MTX_CACHES             2
DECL|macro|ACPI_MTX_TABLES
mdefine_line|#define ACPI_MTX_TABLES             3
DECL|macro|ACPI_MTX_PARSER
mdefine_line|#define ACPI_MTX_PARSER             4
DECL|macro|ACPI_MTX_DISPATCHER
mdefine_line|#define ACPI_MTX_DISPATCHER         5
DECL|macro|ACPI_MTX_INTERPRETER
mdefine_line|#define ACPI_MTX_INTERPRETER        6
DECL|macro|ACPI_MTX_EXECUTE
mdefine_line|#define ACPI_MTX_EXECUTE            7
DECL|macro|ACPI_MTX_NAMESPACE
mdefine_line|#define ACPI_MTX_NAMESPACE          8
DECL|macro|ACPI_MTX_EVENTS
mdefine_line|#define ACPI_MTX_EVENTS             9
DECL|macro|ACPI_MTX_OP_REGIONS
mdefine_line|#define ACPI_MTX_OP_REGIONS         10
DECL|macro|ACPI_MTX_DEBUG_CMD_READY
mdefine_line|#define ACPI_MTX_DEBUG_CMD_READY    11
DECL|macro|ACPI_MTX_DEBUG_CMD_COMPLETE
mdefine_line|#define ACPI_MTX_DEBUG_CMD_COMPLETE 12
DECL|macro|MAX_MTX
mdefine_line|#define MAX_MTX                     12
DECL|macro|NUM_MTX
mdefine_line|#define NUM_MTX                     MAX_MTX+1
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
l_string|&quot;ACPI_MTX_Hardware&quot;
comma
l_string|&quot;ACPI_MTX_Memory&quot;
comma
l_string|&quot;ACPI_MTX_Caches&quot;
comma
l_string|&quot;ACPI_MTX_Tables&quot;
comma
l_string|&quot;ACPI_MTX_Parser&quot;
comma
l_string|&quot;ACPI_MTX_Dispatcher&quot;
comma
l_string|&quot;ACPI_MTX_Interpreter&quot;
comma
l_string|&quot;ACPI_MTX_Execute&quot;
comma
l_string|&quot;ACPI_MTX_Namespace&quot;
comma
l_string|&quot;ACPI_MTX_Events&quot;
comma
l_string|&quot;ACPI_MTX_Op_regions&quot;
comma
l_string|&quot;ACPI_MTX_Debug_cmd_ready&quot;
comma
l_string|&quot;ACPI_MTX_Debug_cmd_complete&quot;
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
id|ACPI_MUTEX
id|mutex
suffix:semicolon
DECL|member|use_count
id|u32
id|use_count
suffix:semicolon
DECL|member|locked
id|u8
id|locked
suffix:semicolon
DECL|typedef|ACPI_MUTEX_INFO
)brace
id|ACPI_MUTEX_INFO
suffix:semicolon
multiline_comment|/* Lock flag parameter for various interfaces */
DECL|macro|ACPI_MTX_DO_NOT_LOCK
mdefine_line|#define ACPI_MTX_DO_NOT_LOCK        0
DECL|macro|ACPI_MTX_LOCK
mdefine_line|#define ACPI_MTX_LOCK               1
DECL|typedef|ACPI_OWNER_ID
r_typedef
id|u16
id|ACPI_OWNER_ID
suffix:semicolon
DECL|macro|OWNER_TYPE_TABLE
mdefine_line|#define OWNER_TYPE_TABLE            0x0
DECL|macro|OWNER_TYPE_METHOD
mdefine_line|#define OWNER_TYPE_METHOD           0x1
DECL|macro|FIRST_METHOD_ID
mdefine_line|#define FIRST_METHOD_ID             0x0000
DECL|macro|FIRST_TABLE_ID
mdefine_line|#define FIRST_TABLE_ID              0x8000
multiline_comment|/* TBD: [Restructure] get rid of the need for this! */
DECL|macro|TABLE_ID_DSDT
mdefine_line|#define TABLE_ID_DSDT               (ACPI_OWNER_ID) 0x8000
multiline_comment|/*****************************************************************************&n; *&n; * Namespace typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/* Operational modes of the AML interpreter/scanner */
r_typedef
r_enum
(brace
DECL|enumerator|IMODE_LOAD_PASS1
id|IMODE_LOAD_PASS1
op_assign
l_int|0x01
comma
DECL|enumerator|IMODE_LOAD_PASS2
id|IMODE_LOAD_PASS2
op_assign
l_int|0x02
comma
DECL|enumerator|IMODE_EXECUTE
id|IMODE_EXECUTE
op_assign
l_int|0x0E
DECL|typedef|OPERATING_MODE
)brace
id|OPERATING_MODE
suffix:semicolon
multiline_comment|/*&n; * The Node describes a named object that appears in the AML&n; * An Acpi_node is used to store Nodes.&n; *&n; * Data_type is used to differentiate between internal descriptors, and MUST&n; * be the first byte in this structure.&n; */
DECL|struct|acpi_node
r_typedef
r_struct
id|acpi_node
(brace
DECL|member|data_type
id|u8
id|data_type
suffix:semicolon
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
id|u32
id|name
suffix:semicolon
multiline_comment|/* ACPI Name, always 4 chars per ACPI spec */
DECL|member|object
r_void
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
DECL|typedef|ACPI_NAMESPACE_NODE
)brace
id|ACPI_NAMESPACE_NODE
suffix:semicolon
DECL|macro|ENTRY_NOT_FOUND
mdefine_line|#define ENTRY_NOT_FOUND             NULL
multiline_comment|/* Node flags */
DECL|macro|ANOBJ_AML_ATTACHMENT
mdefine_line|#define ANOBJ_AML_ATTACHMENT        0x01
DECL|macro|ANOBJ_END_OF_PEER_LIST
mdefine_line|#define ANOBJ_END_OF_PEER_LIST      0x02
DECL|macro|ANOBJ_DATA_WIDTH_32
mdefine_line|#define ANOBJ_DATA_WIDTH_32         0x04     /* Parent table is 64-bits */
DECL|macro|ANOBJ_METHOD_ARG
mdefine_line|#define ANOBJ_METHOD_ARG            0x08
DECL|macro|ANOBJ_METHOD_LOCAL
mdefine_line|#define ANOBJ_METHOD_LOCAL          0x10
DECL|macro|ANOBJ_METHOD_NO_RETVAL
mdefine_line|#define ANOBJ_METHOD_NO_RETVAL      0x20
DECL|macro|ANOBJ_METHOD_SOME_NO_RETVAL
mdefine_line|#define ANOBJ_METHOD_SOME_NO_RETVAL 0x40
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
id|ACPI_TABLE_HEADER
op_star
id|pointer
suffix:semicolon
DECL|member|base_pointer
r_void
op_star
id|base_pointer
suffix:semicolon
DECL|member|aml_pointer
id|u8
op_star
id|aml_pointer
suffix:semicolon
DECL|member|physical_address
id|UINT64
id|physical_address
suffix:semicolon
DECL|member|aml_length
id|u32
id|aml_length
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|table_id
id|ACPI_OWNER_ID
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
DECL|typedef|ACPI_TABLE_DESC
)brace
id|ACPI_TABLE_DESC
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
id|ACPI_HANDLE
op_star
id|list
suffix:semicolon
DECL|member|count
id|u32
op_star
id|count
suffix:semicolon
DECL|typedef|FIND_CONTEXT
)brace
id|FIND_CONTEXT
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|node
id|ACPI_NAMESPACE_NODE
op_star
id|node
suffix:semicolon
DECL|typedef|NS_SEARCH_DATA
)brace
id|NS_SEARCH_DATA
suffix:semicolon
multiline_comment|/*&n; * Predefined Namespace items&n; */
DECL|macro|ACPI_MAX_ADDRESS_SPACE
mdefine_line|#define ACPI_MAX_ADDRESS_SPACE      255
DECL|macro|ACPI_NUM_ADDRESS_SPACES
mdefine_line|#define ACPI_NUM_ADDRESS_SPACES     256
r_typedef
r_struct
(brace
DECL|member|name
id|NATIVE_CHAR
op_star
id|name
suffix:semicolon
DECL|member|type
id|ACPI_OBJECT_TYPE
id|type
suffix:semicolon
DECL|member|val
id|NATIVE_CHAR
op_star
id|val
suffix:semicolon
DECL|typedef|PREDEFINED_NAMES
)brace
id|PREDEFINED_NAMES
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Event typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/* Status bits. */
DECL|macro|ACPI_STATUS_PMTIMER
mdefine_line|#define ACPI_STATUS_PMTIMER                  0x0001
DECL|macro|ACPI_STATUS_GLOBAL
mdefine_line|#define ACPI_STATUS_GLOBAL                   0x0020
DECL|macro|ACPI_STATUS_POWER_BUTTON
mdefine_line|#define ACPI_STATUS_POWER_BUTTON             0x0100
DECL|macro|ACPI_STATUS_SLEEP_BUTTON
mdefine_line|#define ACPI_STATUS_SLEEP_BUTTON             0x0200
DECL|macro|ACPI_STATUS_RTC_ALARM
mdefine_line|#define ACPI_STATUS_RTC_ALARM                0x0400
multiline_comment|/* Enable bits. */
DECL|macro|ACPI_ENABLE_PMTIMER
mdefine_line|#define ACPI_ENABLE_PMTIMER                  0x0001
DECL|macro|ACPI_ENABLE_GLOBAL
mdefine_line|#define ACPI_ENABLE_GLOBAL                   0x0020
DECL|macro|ACPI_ENABLE_POWER_BUTTON
mdefine_line|#define ACPI_ENABLE_POWER_BUTTON             0x0100
DECL|macro|ACPI_ENABLE_SLEEP_BUTTON
mdefine_line|#define ACPI_ENABLE_SLEEP_BUTTON             0x0200
DECL|macro|ACPI_ENABLE_RTC_ALARM
mdefine_line|#define ACPI_ENABLE_RTC_ALARM                0x0400
multiline_comment|/*&n; * Entry in the Address_space (AKA Operation Region) table&n; */
r_typedef
r_struct
(brace
DECL|member|handler
id|ADDRESS_SPACE_HANDLER
id|handler
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|typedef|ACPI_ADDRESS_SPACE_INFO
)brace
id|ACPI_ADDRESS_SPACE_INFO
suffix:semicolon
multiline_comment|/* Values and addresses of the GPE registers (both banks) */
r_typedef
r_struct
(brace
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
DECL|member|status_addr
id|u16
id|status_addr
suffix:semicolon
multiline_comment|/* Address of status reg */
DECL|member|enable_addr
id|u16
id|enable_addr
suffix:semicolon
multiline_comment|/* Address of enable reg */
DECL|member|gpe_base
id|u8
id|gpe_base
suffix:semicolon
multiline_comment|/* Base GPE number */
DECL|typedef|ACPI_GPE_REGISTERS
)brace
id|ACPI_GPE_REGISTERS
suffix:semicolon
DECL|macro|ACPI_GPE_LEVEL_TRIGGERED
mdefine_line|#define ACPI_GPE_LEVEL_TRIGGERED            1
DECL|macro|ACPI_GPE_EDGE_TRIGGERED
mdefine_line|#define ACPI_GPE_EDGE_TRIGGERED             2
multiline_comment|/* Information about each particular GPE level */
r_typedef
r_struct
(brace
DECL|member|type
id|u8
id|type
suffix:semicolon
multiline_comment|/* Level or Edge */
DECL|member|method_handle
id|ACPI_HANDLE
id|method_handle
suffix:semicolon
multiline_comment|/* Method handle for direct (fast) execution */
DECL|member|handler
id|GPE_HANDLER
id|handler
suffix:semicolon
multiline_comment|/* Address of handler, if any */
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
multiline_comment|/* Context to be passed to handler */
DECL|typedef|ACPI_GPE_LEVEL_INFO
)brace
id|ACPI_GPE_LEVEL_INFO
suffix:semicolon
multiline_comment|/* Information about each particular fixed event */
r_typedef
r_struct
(brace
DECL|member|handler
id|FIXED_EVENT_HANDLER
id|handler
suffix:semicolon
multiline_comment|/* Address of handler. */
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
multiline_comment|/* Context to be passed to handler */
DECL|typedef|ACPI_FIXED_EVENT_INFO
)brace
id|ACPI_FIXED_EVENT_INFO
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
DECL|typedef|ACPI_FIELD_INFO
)brace
id|ACPI_FIELD_INFO
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Generic &quot;state&quot; object for stacks&n; *&n; ****************************************************************************/
DECL|macro|CONTROL_NORMAL
mdefine_line|#define CONTROL_NORMAL                        0xC0
DECL|macro|CONTROL_CONDITIONAL_EXECUTING
mdefine_line|#define CONTROL_CONDITIONAL_EXECUTING         0xC1
DECL|macro|CONTROL_PREDICATE_EXECUTING
mdefine_line|#define CONTROL_PREDICATE_EXECUTING           0xC2
DECL|macro|CONTROL_PREDICATE_FALSE
mdefine_line|#define CONTROL_PREDICATE_FALSE               0xC3
DECL|macro|CONTROL_PREDICATE_TRUE
mdefine_line|#define CONTROL_PREDICATE_TRUE                0xC4
multiline_comment|/* Forward declaration */
r_struct
id|acpi_walk_state
suffix:semicolon
r_struct
id|acpi_parse_obj
suffix:semicolon
DECL|macro|ACPI_STATE_COMMON
mdefine_line|#define ACPI_STATE_COMMON                  /* Two 32-bit fields and a pointer */&bslash;&n;&t;u8                      data_type;          /* To differentiate various internal objs */&bslash;&n;&t;u8                      flags; &bslash;&n;&t;u16                     value; &bslash;&n;&t;u16                     state; &bslash;&n;&t;u16                     acpi_eval; &bslash;&n;&t;void                    *next; &bslash;&n;
DECL|struct|acpi_common_state
r_typedef
r_struct
id|acpi_common_state
(brace
id|ACPI_STATE_COMMON
DECL|typedef|ACPI_COMMON_STATE
)brace
id|ACPI_COMMON_STATE
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
DECL|typedef|ACPI_UPDATE_STATE
)brace
id|ACPI_UPDATE_STATE
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
DECL|typedef|ACPI_PKG_STATE
)brace
id|ACPI_PKG_STATE
suffix:semicolon
multiline_comment|/*&n; * Control state - one per if/else and while constructs.&n; * Allows nesting of these constructs&n; */
DECL|struct|acpi_control_state
r_typedef
r_struct
id|acpi_control_state
(brace
id|ACPI_STATE_COMMON
DECL|member|predicate_op
r_struct
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
DECL|typedef|ACPI_CONTROL_STATE
)brace
id|ACPI_CONTROL_STATE
suffix:semicolon
multiline_comment|/*&n; * Scope state - current scope during namespace lookups&n; */
DECL|struct|acpi_scope_state
r_typedef
r_struct
id|acpi_scope_state
(brace
id|ACPI_STATE_COMMON
DECL|member|node
id|ACPI_NAMESPACE_NODE
op_star
id|node
suffix:semicolon
DECL|typedef|ACPI_SCOPE_STATE
)brace
id|ACPI_SCOPE_STATE
suffix:semicolon
DECL|struct|acpi_pscope_state
r_typedef
r_struct
id|acpi_pscope_state
(brace
id|ACPI_STATE_COMMON
DECL|member|op
r_struct
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
DECL|typedef|ACPI_PSCOPE_STATE
)brace
id|ACPI_PSCOPE_STATE
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
DECL|typedef|ACPI_RESULT_VALUES
)brace
id|ACPI_RESULT_VALUES
suffix:semicolon
multiline_comment|/* Generic state is union of structs above */
DECL|union|acpi_gen_state
r_typedef
r_union
id|acpi_gen_state
(brace
DECL|member|common
id|ACPI_COMMON_STATE
id|common
suffix:semicolon
DECL|member|control
id|ACPI_CONTROL_STATE
id|control
suffix:semicolon
DECL|member|update
id|ACPI_UPDATE_STATE
id|update
suffix:semicolon
DECL|member|scope
id|ACPI_SCOPE_STATE
id|scope
suffix:semicolon
DECL|member|parse_scope
id|ACPI_PSCOPE_STATE
id|parse_scope
suffix:semicolon
DECL|member|pkg
id|ACPI_PKG_STATE
id|pkg
suffix:semicolon
DECL|member|results
id|ACPI_RESULT_VALUES
id|results
suffix:semicolon
DECL|typedef|ACPI_GENERIC_STATE
)brace
id|ACPI_GENERIC_STATE
suffix:semicolon
r_typedef
DECL|typedef|ACPI_PARSE_DOWNWARDS
id|ACPI_STATUS
(paren
op_star
id|ACPI_PARSE_DOWNWARDS
)paren
(paren
id|u16
id|opcode
comma
r_struct
id|acpi_parse_obj
op_star
id|op
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_struct
id|acpi_parse_obj
op_star
op_star
id|out_op
)paren
suffix:semicolon
r_typedef
DECL|typedef|ACPI_PARSE_UPWARDS
id|ACPI_STATUS
(paren
op_star
id|ACPI_PARSE_UPWARDS
)paren
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_struct
id|acpi_parse_obj
op_star
id|op
)paren
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Parser typedefs and structs&n; *&n; ****************************************************************************/
DECL|macro|ACPI_OP_CLASS_MASK
mdefine_line|#define ACPI_OP_CLASS_MASK          0x1F
DECL|macro|ACPI_OP_ARGS_MASK
mdefine_line|#define ACPI_OP_ARGS_MASK           0x20
DECL|macro|ACPI_OP_TYPE_MASK
mdefine_line|#define ACPI_OP_TYPE_MASK           0xC0
DECL|macro|ACPI_OP_TYPE_OPCODE
mdefine_line|#define ACPI_OP_TYPE_OPCODE         0x00
DECL|macro|ACPI_OP_TYPE_ASCII
mdefine_line|#define ACPI_OP_TYPE_ASCII          0x40
DECL|macro|ACPI_OP_TYPE_PREFIX
mdefine_line|#define ACPI_OP_TYPE_PREFIX         0x80
DECL|macro|ACPI_OP_TYPE_UNKNOWN
mdefine_line|#define ACPI_OP_TYPE_UNKNOWN        0xC0
DECL|macro|ACPI_GET_OP_CLASS
mdefine_line|#define ACPI_GET_OP_CLASS(a)        ((a)-&gt;flags &amp; ACPI_OP_CLASS_MASK)
DECL|macro|ACPI_GET_OP_ARGS
mdefine_line|#define ACPI_GET_OP_ARGS(a)         ((a)-&gt;flags &amp; ACPI_OP_ARGS_MASK)
DECL|macro|ACPI_GET_OP_TYPE
mdefine_line|#define ACPI_GET_OP_TYPE(a)         ((a)-&gt;flags &amp; ACPI_OP_TYPE_MASK)
multiline_comment|/*&n; * AML opcode, name, and argument layout&n; */
DECL|struct|acpi_opcode_info
r_typedef
r_struct
id|acpi_opcode_info
(brace
DECL|member|flags
id|u8
id|flags
suffix:semicolon
multiline_comment|/* Opcode type, Has_args flag */
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
macro_line|#ifdef _OPCODE_NAMES
DECL|member|name
id|NATIVE_CHAR
op_star
id|name
suffix:semicolon
multiline_comment|/* op name (debug only) */
macro_line|#endif
DECL|typedef|ACPI_OPCODE_INFO
)brace
id|ACPI_OPCODE_INFO
suffix:semicolon
DECL|union|acpi_parse_val
r_typedef
r_union
id|acpi_parse_val
(brace
DECL|member|integer
id|u32
id|integer
suffix:semicolon
multiline_comment|/* integer constant */
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
r_struct
id|acpi_parse_obj
op_star
id|arg
suffix:semicolon
multiline_comment|/* arguments and contained ops */
DECL|typedef|ACPI_PARSE_VALUE
)brace
id|ACPI_PARSE_VALUE
suffix:semicolon
DECL|macro|ACPI_PARSE_COMMON
mdefine_line|#define ACPI_PARSE_COMMON &bslash;&n;&t;u8                      data_type;      /* To differentiate various internal objs */&bslash;&n;&t;u8                      flags;          /* Type of Op */&bslash;&n;&t;u16                     opcode;         /* AML opcode */&bslash;&n;&t;u32                     aml_offset;     /* offset of declaration in AML */&bslash;&n;&t;struct acpi_parse_obj   *parent;        /* parent op */&bslash;&n;&t;struct acpi_parse_obj   *next;          /* next op */&bslash;&n;&t;DEBUG_ONLY_MEMBERS (&bslash;&n;&t;NATIVE_CHAR             op_name[16])    /* op name (debug only) */&bslash;&n;&t;&t;&t;  /* NON-DEBUG members below: */&bslash;&n;&t;ACPI_NAMESPACE_NODE     *node;          /* for use by interpreter */&bslash;&n;&t;ACPI_PARSE_VALUE        value;          /* Value or args associated with the opcode */&bslash;&n;
multiline_comment|/*&n; * generic operation (eg. If, While, Store)&n; */
DECL|struct|acpi_parse_obj
r_typedef
r_struct
id|acpi_parse_obj
(brace
id|ACPI_PARSE_COMMON
DECL|typedef|ACPI_PARSE_OBJECT
)brace
id|ACPI_PARSE_OBJECT
suffix:semicolon
multiline_comment|/*&n; * Extended Op for named ops (Scope, Method, etc.), deferred ops (Methods and Op_regions),&n; * and bytelists.&n; */
DECL|struct|acpi_parse2_obj
r_typedef
r_struct
id|acpi_parse2_obj
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
DECL|typedef|ACPI_PARSE2_OBJECT
)brace
id|ACPI_PARSE2_OBJECT
suffix:semicolon
multiline_comment|/*&n; * Parse state - one state per parser invocation and each control&n; * method.&n; */
DECL|struct|acpi_parse_state
r_typedef
r_struct
id|acpi_parse_state
(brace
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
id|ACPI_PARSE_OBJECT
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
id|ACPI_GENERIC_STATE
op_star
id|scope
suffix:semicolon
multiline_comment|/* current scope */
DECL|member|next
r_struct
id|acpi_parse_state
op_star
id|next
suffix:semicolon
DECL|typedef|ACPI_PARSE_STATE
)brace
id|ACPI_PARSE_STATE
suffix:semicolon
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
id|WALK_CALLBACK
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
multiline_comment|/*****************************************************************************&n; *&n; * Hardware and PNP&n; *&n; ****************************************************************************/
multiline_comment|/* PCI */
DECL|macro|PCI_ROOT_HID_STRING
mdefine_line|#define PCI_ROOT_HID_STRING         &quot;PNP0A03&quot;
DECL|macro|PCI_ROOT_HID_VALUE
mdefine_line|#define PCI_ROOT_HID_VALUE          0x030AD041       /* EISAID(&quot;PNP0A03&quot;) */
multiline_comment|/* Sleep states */
DECL|macro|SLWA_DEBUG_LEVEL
mdefine_line|#define SLWA_DEBUG_LEVEL            4
DECL|macro|GTS_CALL
mdefine_line|#define GTS_CALL                    0
DECL|macro|GTS_WAKE
mdefine_line|#define GTS_WAKE                    1
multiline_comment|/* Cx States */
DECL|macro|MAX_CX_STATE_LATENCY
mdefine_line|#define MAX_CX_STATE_LATENCY        0xFFFFFFFF
DECL|macro|MAX_CX_STATES
mdefine_line|#define MAX_CX_STATES               4
multiline_comment|/*&n; * The #define&squot;s and enum below establish an abstract way of identifying what&n; * register block and register is to be accessed.  Do not change any of the&n; * values as they are used in switch statements and offset calculations.&n; */
DECL|macro|REGISTER_BLOCK_MASK
mdefine_line|#define REGISTER_BLOCK_MASK         0xFF00  /* Register Block Id    */
DECL|macro|BIT_IN_REGISTER_MASK
mdefine_line|#define BIT_IN_REGISTER_MASK        0x00FF  /* Bit Id in the Register Block Id    */
DECL|macro|BYTE_IN_REGISTER_MASK
mdefine_line|#define BYTE_IN_REGISTER_MASK       0x00FF  /* Register Offset in the Register Block    */
DECL|macro|REGISTER_BLOCK_ID
mdefine_line|#define REGISTER_BLOCK_ID(reg_id)   (reg_id &amp; REGISTER_BLOCK_MASK)
DECL|macro|REGISTER_BIT_ID
mdefine_line|#define REGISTER_BIT_ID(reg_id)     (reg_id &amp; BIT_IN_REGISTER_MASK)
DECL|macro|REGISTER_OFFSET
mdefine_line|#define REGISTER_OFFSET(reg_id)     (reg_id &amp; BYTE_IN_REGISTER_MASK)
multiline_comment|/*&n; * Access Rule&n; *  To access a Register Bit:&n; *  -&gt; Use Bit Name (= Register Block Id | Bit Id) defined in the enum.&n; *&n; *  To access a Register:&n; *  -&gt; Use Register Id (= Register Block Id | Register Offset)&n; */
multiline_comment|/*&n; * Register Block Id&n; */
DECL|macro|PM1_STS
mdefine_line|#define PM1_STS                     0x0100
DECL|macro|PM1_EN
mdefine_line|#define PM1_EN                      0x0200
DECL|macro|PM1_CONTROL
mdefine_line|#define PM1_CONTROL                 0x0300
DECL|macro|PM1_a_CONTROL
mdefine_line|#define PM1_a_CONTROL               0x0400
DECL|macro|PM1_b_CONTROL
mdefine_line|#define PM1_b_CONTROL               0x0500
DECL|macro|PM2_CONTROL
mdefine_line|#define PM2_CONTROL                 0x0600
DECL|macro|PM_TIMER
mdefine_line|#define PM_TIMER                    0x0700
DECL|macro|PROCESSOR_BLOCK
mdefine_line|#define PROCESSOR_BLOCK             0x0800
DECL|macro|GPE0_STS_BLOCK
mdefine_line|#define GPE0_STS_BLOCK              0x0900
DECL|macro|GPE0_EN_BLOCK
mdefine_line|#define GPE0_EN_BLOCK               0x0A00
DECL|macro|GPE1_STS_BLOCK
mdefine_line|#define GPE1_STS_BLOCK              0x0B00
DECL|macro|GPE1_EN_BLOCK
mdefine_line|#define GPE1_EN_BLOCK               0x0C00
DECL|macro|SMI_CMD_BLOCK
mdefine_line|#define SMI_CMD_BLOCK               0x0D00
multiline_comment|/*&n; * Address space bitmasks for mmio or io spaces&n; */
DECL|macro|SMI_CMD_ADDRESS_SPACE
mdefine_line|#define SMI_CMD_ADDRESS_SPACE       0x01
DECL|macro|PM1_BLK_ADDRESS_SPACE
mdefine_line|#define PM1_BLK_ADDRESS_SPACE       0x02
DECL|macro|PM2_CNT_BLK_ADDRESS_SPACE
mdefine_line|#define PM2_CNT_BLK_ADDRESS_SPACE   0x04
DECL|macro|PM_TMR_BLK_ADDRESS_SPACE
mdefine_line|#define PM_TMR_BLK_ADDRESS_SPACE    0x08
DECL|macro|GPE0_BLK_ADDRESS_SPACE
mdefine_line|#define GPE0_BLK_ADDRESS_SPACE      0x10
DECL|macro|GPE1_BLK_ADDRESS_SPACE
mdefine_line|#define GPE1_BLK_ADDRESS_SPACE      0x20
multiline_comment|/*&n; * Control bit definitions&n; */
DECL|macro|TMR_STS
mdefine_line|#define TMR_STS                     (PM1_STS | 0x01)
DECL|macro|BM_STS
mdefine_line|#define BM_STS                      (PM1_STS | 0x02)
DECL|macro|GBL_STS
mdefine_line|#define GBL_STS                     (PM1_STS | 0x03)
DECL|macro|PWRBTN_STS
mdefine_line|#define PWRBTN_STS                  (PM1_STS | 0x04)
DECL|macro|SLPBTN_STS
mdefine_line|#define SLPBTN_STS                  (PM1_STS | 0x05)
DECL|macro|RTC_STS
mdefine_line|#define RTC_STS                     (PM1_STS | 0x06)
DECL|macro|WAK_STS
mdefine_line|#define WAK_STS                     (PM1_STS | 0x07)
DECL|macro|TMR_EN
mdefine_line|#define TMR_EN                      (PM1_EN | 0x01)
multiline_comment|/* no BM_EN */
DECL|macro|GBL_EN
mdefine_line|#define GBL_EN                      (PM1_EN | 0x03)
DECL|macro|PWRBTN_EN
mdefine_line|#define PWRBTN_EN                   (PM1_EN | 0x04)
DECL|macro|SLPBTN_EN
mdefine_line|#define SLPBTN_EN                   (PM1_EN | 0x05)
DECL|macro|RTC_EN
mdefine_line|#define RTC_EN                      (PM1_EN | 0x06)
DECL|macro|WAK_EN
mdefine_line|#define WAK_EN                      (PM1_EN | 0x07)
DECL|macro|SCI_EN
mdefine_line|#define SCI_EN                      (PM1_CONTROL | 0x01)
DECL|macro|BM_RLD
mdefine_line|#define BM_RLD                      (PM1_CONTROL | 0x02)
DECL|macro|GBL_RLS
mdefine_line|#define GBL_RLS                     (PM1_CONTROL | 0x03)
DECL|macro|SLP_TYPE_A
mdefine_line|#define SLP_TYPE_A                  (PM1_CONTROL | 0x04)
DECL|macro|SLP_TYPE_B
mdefine_line|#define SLP_TYPE_B                  (PM1_CONTROL | 0x05)
DECL|macro|SLP_EN
mdefine_line|#define SLP_EN                      (PM1_CONTROL | 0x06)
DECL|macro|ARB_DIS
mdefine_line|#define ARB_DIS                     (PM2_CONTROL | 0x01)
DECL|macro|TMR_VAL
mdefine_line|#define TMR_VAL                     (PM_TIMER | 0x01)
DECL|macro|GPE0_STS
mdefine_line|#define GPE0_STS                    (GPE0_STS_BLOCK | 0x01)
DECL|macro|GPE0_EN
mdefine_line|#define GPE0_EN                     (GPE0_EN_BLOCK  | 0x01)
DECL|macro|GPE1_STS
mdefine_line|#define GPE1_STS                    (GPE1_STS_BLOCK | 0x01)
DECL|macro|GPE1_EN
mdefine_line|#define GPE1_EN                     (GPE1_EN_BLOCK  | 0x01)
DECL|macro|TMR_STS_MASK
mdefine_line|#define TMR_STS_MASK                0x0001
DECL|macro|BM_STS_MASK
mdefine_line|#define BM_STS_MASK                 0x0010
DECL|macro|GBL_STS_MASK
mdefine_line|#define GBL_STS_MASK                0x0020
DECL|macro|PWRBTN_STS_MASK
mdefine_line|#define PWRBTN_STS_MASK             0x0100
DECL|macro|SLPBTN_STS_MASK
mdefine_line|#define SLPBTN_STS_MASK             0x0200
DECL|macro|RTC_STS_MASK
mdefine_line|#define RTC_STS_MASK                0x0400
DECL|macro|WAK_STS_MASK
mdefine_line|#define WAK_STS_MASK                0x8000
DECL|macro|ALL_FIXED_STS_BITS
mdefine_line|#define ALL_FIXED_STS_BITS          (TMR_STS_MASK   | BM_STS_MASK  | GBL_STS_MASK &bslash;&n;&t;&t;&t;&t;&t; | PWRBTN_STS_MASK | SLPBTN_STS_MASK &bslash;&n;&t;&t;&t;&t;&t; | RTC_STS_MASK | WAK_STS_MASK)
DECL|macro|TMR_EN_MASK
mdefine_line|#define TMR_EN_MASK                 0x0001
DECL|macro|GBL_EN_MASK
mdefine_line|#define GBL_EN_MASK                 0x0020
DECL|macro|PWRBTN_EN_MASK
mdefine_line|#define PWRBTN_EN_MASK              0x0100
DECL|macro|SLPBTN_EN_MASK
mdefine_line|#define SLPBTN_EN_MASK              0x0200
DECL|macro|RTC_EN_MASK
mdefine_line|#define RTC_EN_MASK                 0x0400
DECL|macro|SCI_EN_MASK
mdefine_line|#define SCI_EN_MASK                 0x0001
DECL|macro|BM_RLD_MASK
mdefine_line|#define BM_RLD_MASK                 0x0002
DECL|macro|GBL_RLS_MASK
mdefine_line|#define GBL_RLS_MASK                0x0004
DECL|macro|SLP_TYPE_X_MASK
mdefine_line|#define SLP_TYPE_X_MASK             0x1C00
DECL|macro|SLP_EN_MASK
mdefine_line|#define SLP_EN_MASK                 0x2000
DECL|macro|ARB_DIS_MASK
mdefine_line|#define ARB_DIS_MASK                0x0001
DECL|macro|TMR_VAL_MASK
mdefine_line|#define TMR_VAL_MASK                0xFFFFFFFF
DECL|macro|GPE0_STS_MASK
mdefine_line|#define GPE0_STS_MASK
DECL|macro|GPE0_EN_MASK
mdefine_line|#define GPE0_EN_MASK
DECL|macro|GPE1_STS_MASK
mdefine_line|#define GPE1_STS_MASK
DECL|macro|GPE1_EN_MASK
mdefine_line|#define GPE1_EN_MASK
DECL|macro|ACPI_READ
mdefine_line|#define ACPI_READ                   1
DECL|macro|ACPI_WRITE
mdefine_line|#define ACPI_WRITE                  2
multiline_comment|/* Plug and play */
multiline_comment|/* Pnp and ACPI data */
DECL|macro|VERSION_NO
mdefine_line|#define VERSION_NO                      0x01
DECL|macro|LOGICAL_DEVICE_ID
mdefine_line|#define LOGICAL_DEVICE_ID               0x02
DECL|macro|COMPATIBLE_DEVICE_ID
mdefine_line|#define COMPATIBLE_DEVICE_ID            0x03
DECL|macro|IRQ_FORMAT
mdefine_line|#define IRQ_FORMAT                      0x04
DECL|macro|DMA_FORMAT
mdefine_line|#define DMA_FORMAT                      0x05
DECL|macro|START_DEPENDENT_TAG
mdefine_line|#define START_DEPENDENT_TAG             0x06
DECL|macro|END_DEPENDENT_TAG
mdefine_line|#define END_DEPENDENT_TAG               0x07
DECL|macro|IO_PORT_DESCRIPTOR
mdefine_line|#define IO_PORT_DESCRIPTOR              0x08
DECL|macro|FIXED_LOCATION_IO_DESCRIPTOR
mdefine_line|#define FIXED_LOCATION_IO_DESCRIPTOR    0x09
DECL|macro|RESERVED_TYPE0
mdefine_line|#define RESERVED_TYPE0                  0x0A
DECL|macro|RESERVED_TYPE1
mdefine_line|#define RESERVED_TYPE1                  0x0B
DECL|macro|RESERVED_TYPE2
mdefine_line|#define RESERVED_TYPE2                  0x0C
DECL|macro|RESERVED_TYPE3
mdefine_line|#define RESERVED_TYPE3                  0x0D
DECL|macro|SMALL_VENDOR_DEFINED
mdefine_line|#define SMALL_VENDOR_DEFINED            0x0E
DECL|macro|END_TAG
mdefine_line|#define END_TAG                         0x0F
multiline_comment|/* Pnp and ACPI data */
DECL|macro|MEMORY_RANGE_24
mdefine_line|#define MEMORY_RANGE_24                 0x81
DECL|macro|ISA_MEMORY_RANGE
mdefine_line|#define ISA_MEMORY_RANGE                0x81
DECL|macro|LARGE_VENDOR_DEFINED
mdefine_line|#define LARGE_VENDOR_DEFINED            0x84
DECL|macro|EISA_MEMORY_RANGE
mdefine_line|#define EISA_MEMORY_RANGE               0x85
DECL|macro|MEMORY_RANGE_32
mdefine_line|#define MEMORY_RANGE_32                 0x85
DECL|macro|FIXED_EISA_MEMORY_RANGE
mdefine_line|#define FIXED_EISA_MEMORY_RANGE         0x86
DECL|macro|FIXED_MEMORY_RANGE_32
mdefine_line|#define FIXED_MEMORY_RANGE_32           0x86
multiline_comment|/* ACPI only data */
DECL|macro|DWORD_ADDRESS_SPACE
mdefine_line|#define DWORD_ADDRESS_SPACE             0x87
DECL|macro|WORD_ADDRESS_SPACE
mdefine_line|#define WORD_ADDRESS_SPACE              0x88
DECL|macro|EXTENDED_IRQ
mdefine_line|#define EXTENDED_IRQ                    0x89
multiline_comment|/* MUST HAVES */
DECL|macro|DEVICE_ID_LENGTH
mdefine_line|#define DEVICE_ID_LENGTH                0x09
r_typedef
r_struct
(brace
DECL|member|buffer
id|NATIVE_CHAR
id|buffer
(braket
id|DEVICE_ID_LENGTH
)braket
suffix:semicolon
DECL|typedef|DEVICE_ID
)brace
id|DEVICE_ID
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Debug&n; *&n; ****************************************************************************/
multiline_comment|/* Entry for a memory allocation (debug only) */
macro_line|#ifdef ACPI_DEBUG
DECL|macro|MEM_MALLOC
mdefine_line|#define MEM_MALLOC          0
DECL|macro|MEM_CALLOC
mdefine_line|#define MEM_CALLOC          1
DECL|macro|MAX_MODULE_NAME
mdefine_line|#define MAX_MODULE_NAME     16
DECL|struct|allocation_info
r_typedef
r_struct
id|allocation_info
(brace
DECL|member|previous
r_struct
id|allocation_info
op_star
id|previous
suffix:semicolon
DECL|member|next
r_struct
id|allocation_info
op_star
id|next
suffix:semicolon
DECL|member|address
r_void
op_star
id|address
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|component
id|u32
id|component
suffix:semicolon
DECL|member|line
id|u32
id|line
suffix:semicolon
DECL|member|module
id|NATIVE_CHAR
id|module
(braket
id|MAX_MODULE_NAME
)braket
suffix:semicolon
DECL|member|alloc_type
id|u8
id|alloc_type
suffix:semicolon
DECL|typedef|ALLOCATION_INFO
)brace
id|ALLOCATION_INFO
suffix:semicolon
macro_line|#endif
macro_line|#endif /* __ACLOCAL_H__ */
eof
