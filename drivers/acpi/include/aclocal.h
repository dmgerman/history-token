multiline_comment|/******************************************************************************&n; *&n; * Name: aclocal.h - Internal data types used across the ACPI subsystem&n; *       $Revision: 138 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
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
multiline_comment|/* Object descriptor types */
DECL|macro|ACPI_CACHED_OBJECT
mdefine_line|#define ACPI_CACHED_OBJECT              0x11    /* ORed in when object is cached */
DECL|macro|ACPI_DESC_TYPE_STATE
mdefine_line|#define ACPI_DESC_TYPE_STATE            0x20
DECL|macro|ACPI_DESC_TYPE_STATE_UPDATE
mdefine_line|#define ACPI_DESC_TYPE_STATE_UPDATE     0x21
DECL|macro|ACPI_DESC_TYPE_STATE_PACKAGE
mdefine_line|#define ACPI_DESC_TYPE_STATE_PACKAGE    0x22
DECL|macro|ACPI_DESC_TYPE_STATE_CONTROL
mdefine_line|#define ACPI_DESC_TYPE_STATE_CONTROL    0x23
DECL|macro|ACPI_DESC_TYPE_STATE_RPSCOPE
mdefine_line|#define ACPI_DESC_TYPE_STATE_RPSCOPE    0x24
DECL|macro|ACPI_DESC_TYPE_STATE_PSCOPE
mdefine_line|#define ACPI_DESC_TYPE_STATE_PSCOPE     0x25
DECL|macro|ACPI_DESC_TYPE_STATE_WSCOPE
mdefine_line|#define ACPI_DESC_TYPE_STATE_WSCOPE     0x26
DECL|macro|ACPI_DESC_TYPE_STATE_RESULT
mdefine_line|#define ACPI_DESC_TYPE_STATE_RESULT     0x27
DECL|macro|ACPI_DESC_TYPE_STATE_NOTIFY
mdefine_line|#define ACPI_DESC_TYPE_STATE_NOTIFY     0x28
DECL|macro|ACPI_DESC_TYPE_WALK
mdefine_line|#define ACPI_DESC_TYPE_WALK             0x44
DECL|macro|ACPI_DESC_TYPE_PARSER
mdefine_line|#define ACPI_DESC_TYPE_PARSER           0x66
DECL|macro|ACPI_DESC_TYPE_INTERNAL
mdefine_line|#define ACPI_DESC_TYPE_INTERNAL         0x88
DECL|macro|ACPI_DESC_TYPE_NAMED
mdefine_line|#define ACPI_DESC_TYPE_NAMED            0xAA
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
DECL|macro|OWNER_TYPE_TABLE
mdefine_line|#define OWNER_TYPE_TABLE                0x0
DECL|macro|OWNER_TYPE_METHOD
mdefine_line|#define OWNER_TYPE_METHOD               0x1
DECL|macro|FIRST_METHOD_ID
mdefine_line|#define FIRST_METHOD_ID                 0x0000
DECL|macro|FIRST_TABLE_ID
mdefine_line|#define FIRST_TABLE_ID                  0x8000
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
DECL|typedef|operating_mode
)brace
id|operating_mode
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
DECL|macro|ENTRY_NOT_FOUND
mdefine_line|#define ENTRY_NOT_FOUND             NULL
multiline_comment|/* Node flags */
DECL|macro|ANOBJ_AML_ATTACHMENT
mdefine_line|#define ANOBJ_AML_ATTACHMENT            0x01
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
id|u32
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
DECL|typedef|find_context
)brace
id|find_context
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
DECL|typedef|ns_search_data
)brace
id|ns_search_data
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
id|acpi_object_type8
id|type
suffix:semicolon
DECL|member|val
id|NATIVE_CHAR
op_star
id|val
suffix:semicolon
DECL|typedef|predefined_names
)brace
id|predefined_names
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
DECL|member|field_type
id|u8
id|field_type
suffix:semicolon
DECL|typedef|ACPI_CREATE_FIELD_INFO
)brace
id|ACPI_CREATE_FIELD_INFO
suffix:semicolon
multiline_comment|/*&n; * Field flags: Bits 00 - 03 : Access_type (Any_acc, Byte_acc, etc.)&n; *                   04      : Lock_rule (1 == Lock)&n; *                   05 - 06 : Update_rule&n; */
DECL|macro|FIELD_ACCESS_TYPE_MASK
mdefine_line|#define FIELD_ACCESS_TYPE_MASK      0x0F
DECL|macro|FIELD_LOCK_RULE_MASK
mdefine_line|#define FIELD_LOCK_RULE_MASK        0x10
DECL|macro|FIELD_UPDATE_RULE_MASK
mdefine_line|#define FIELD_UPDATE_RULE_MASK      0x60
multiline_comment|/*****************************************************************************&n; *&n; * Event typedefs and structs&n; *&n; ****************************************************************************/
multiline_comment|/* Status bits. */
DECL|macro|ACPI_STATUS_PMTIMER
mdefine_line|#define ACPI_STATUS_PMTIMER             0x0001
DECL|macro|ACPI_STATUS_BUSMASTER
mdefine_line|#define ACPI_STATUS_BUSMASTER           0x0010
DECL|macro|ACPI_STATUS_GLOBAL
mdefine_line|#define ACPI_STATUS_GLOBAL              0x0020
DECL|macro|ACPI_STATUS_POWER_BUTTON
mdefine_line|#define ACPI_STATUS_POWER_BUTTON        0x0100
DECL|macro|ACPI_STATUS_SLEEP_BUTTON
mdefine_line|#define ACPI_STATUS_SLEEP_BUTTON        0x0200
DECL|macro|ACPI_STATUS_RTC_ALARM
mdefine_line|#define ACPI_STATUS_RTC_ALARM           0x0400
multiline_comment|/* Enable bits. */
DECL|macro|ACPI_ENABLE_PMTIMER
mdefine_line|#define ACPI_ENABLE_PMTIMER             0x0001
DECL|macro|ACPI_ENABLE_GLOBAL
mdefine_line|#define ACPI_ENABLE_GLOBAL              0x0020
DECL|macro|ACPI_ENABLE_POWER_BUTTON
mdefine_line|#define ACPI_ENABLE_POWER_BUTTON        0x0100
DECL|macro|ACPI_ENABLE_SLEEP_BUTTON
mdefine_line|#define ACPI_ENABLE_SLEEP_BUTTON        0x0200
DECL|macro|ACPI_ENABLE_RTC_ALARM
mdefine_line|#define ACPI_ENABLE_RTC_ALARM           0x0400
multiline_comment|/*&n; * Entry in the Address_space (AKA Operation Region) table&n; */
r_typedef
r_struct
(brace
DECL|member|handler
id|acpi_adr_space_handler
id|handler
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|typedef|acpi_adr_space_info
)brace
id|acpi_adr_space_info
suffix:semicolon
multiline_comment|/* Values and addresses of the GPE registers (both banks) */
r_typedef
r_struct
(brace
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
DECL|member|gpe_base
id|u8
id|gpe_base
suffix:semicolon
multiline_comment|/* Base GPE number */
DECL|typedef|acpi_gpe_registers
)brace
id|acpi_gpe_registers
suffix:semicolon
DECL|macro|ACPI_GPE_LEVEL_TRIGGERED
mdefine_line|#define ACPI_GPE_LEVEL_TRIGGERED        1
DECL|macro|ACPI_GPE_EDGE_TRIGGERED
mdefine_line|#define ACPI_GPE_EDGE_TRIGGERED         2
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
DECL|typedef|acpi_gpe_level_info
)brace
id|acpi_gpe_level_info
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
DECL|macro|CONTROL_NORMAL
mdefine_line|#define CONTROL_NORMAL                  0xC0
DECL|macro|CONTROL_CONDITIONAL_EXECUTING
mdefine_line|#define CONTROL_CONDITIONAL_EXECUTING   0xC1
DECL|macro|CONTROL_PREDICATE_EXECUTING
mdefine_line|#define CONTROL_PREDICATE_EXECUTING     0xC2
DECL|macro|CONTROL_PREDICATE_FALSE
mdefine_line|#define CONTROL_PREDICATE_FALSE         0xC3
DECL|macro|CONTROL_PREDICATE_TRUE
mdefine_line|#define CONTROL_PREDICATE_TRUE          0xC4
multiline_comment|/* Forward declarations */
r_struct
id|acpi_walk_state
suffix:semicolon
r_struct
id|acpi_walk_list
suffix:semicolon
r_struct
id|acpi_parse_obj
suffix:semicolon
r_struct
id|acpi_obj_mutex
suffix:semicolon
DECL|macro|ACPI_STATE_COMMON
mdefine_line|#define ACPI_STATE_COMMON                  /* Two 32-bit fields and a pointer */&bslash;&n;&t;u8                      data_type;          /* To differentiate various internal objs */&bslash;&n;&t;u8                      flags; &bslash;&n;&t;u16                     value; &bslash;&n;&t;u16                     state; &bslash;&n;&t;u16                     acpi_eval; &bslash;&n;&t;void                    *next; &bslash;&n;
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
DECL|typedef|acpi_pscope_state
)brace
id|acpi_pscope_state
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
r_struct
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
id|u16
id|flags
suffix:semicolon
multiline_comment|/* Misc flags */
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
macro_line|#ifdef _OPCODE_NAMES
DECL|member|name
id|NATIVE_CHAR
op_star
id|name
suffix:semicolon
multiline_comment|/* op name (debug only) */
macro_line|#endif
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
r_struct
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
mdefine_line|#define ACPI_PARSE_COMMON &bslash;&n;&t;u8                      data_type;      /* To differentiate various internal objs */&bslash;&n;&t;u8                      flags;          /* Type of Op */&bslash;&n;&t;u16                     opcode;         /* AML opcode */&bslash;&n;&t;u32                     aml_offset;     /* offset of declaration in AML */&bslash;&n;&t;struct acpi_parse_obj   *parent;        /* parent op */&bslash;&n;&t;struct acpi_parse_obj   *next;          /* next op */&bslash;&n;&t;DEBUG_ONLY_MEMBERS (&bslash;&n;&t;NATIVE_CHAR             op_name[16])    /* op name (debug only) */&bslash;&n;&t;&t;&t;  /* NON-DEBUG members below: */&bslash;&n;&t;acpi_namespace_node     *node;          /* for use by interpreter */&bslash;&n;&t;acpi_parse_value        value;          /* Value or args associated with the opcode */&bslash;&n;
multiline_comment|/*&n; * generic operation (eg. If, While, Store)&n; */
DECL|struct|acpi_parse_obj
r_typedef
r_struct
id|acpi_parse_obj
(brace
id|ACPI_PARSE_COMMON
DECL|typedef|acpi_parse_object
)brace
id|acpi_parse_object
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
DECL|typedef|acpi_parse2_object
)brace
id|acpi_parse2_object
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
r_struct
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
r_struct
id|acpi_parse_obj
op_star
id|start_scope
suffix:semicolon
DECL|typedef|acpi_parse_state
)brace
id|acpi_parse_state
suffix:semicolon
multiline_comment|/*****************************************************************************&n; *&n; * Hardware and PNP&n; *&n; ****************************************************************************/
multiline_comment|/* PCI */
DECL|macro|PCI_ROOT_HID_STRING
mdefine_line|#define PCI_ROOT_HID_STRING             &quot;PNP0A03&quot;
multiline_comment|/*&n; * The #define&squot;s and enum below establish an abstract way of identifying what&n; * register block and register is to be accessed.  Do not change any of the&n; * values as they are used in switch statements and offset calculations.&n; */
DECL|macro|REGISTER_BLOCK_MASK
mdefine_line|#define REGISTER_BLOCK_MASK             0xFF00  /* Register Block Id    */
DECL|macro|BIT_IN_REGISTER_MASK
mdefine_line|#define BIT_IN_REGISTER_MASK            0x00FF  /* Bit Id in the Register Block Id    */
DECL|macro|BYTE_IN_REGISTER_MASK
mdefine_line|#define BYTE_IN_REGISTER_MASK           0x00FF  /* Register Offset in the Register Block    */
DECL|macro|REGISTER_BLOCK_ID
mdefine_line|#define REGISTER_BLOCK_ID(reg_id)       (reg_id &amp; REGISTER_BLOCK_MASK)
DECL|macro|REGISTER_BIT_ID
mdefine_line|#define REGISTER_BIT_ID(reg_id)         (reg_id &amp; BIT_IN_REGISTER_MASK)
DECL|macro|REGISTER_OFFSET
mdefine_line|#define REGISTER_OFFSET(reg_id)         (reg_id &amp; BYTE_IN_REGISTER_MASK)
multiline_comment|/*&n; * Access Rule&n; *  To access a Register Bit:&n; *  -&gt; Use Bit Name (= Register Block Id | Bit Id) defined in the enum.&n; *&n; *  To access a Register:&n; *  -&gt; Use Register Id (= Register Block Id | Register Offset)&n; */
multiline_comment|/*&n; * Register Block Id&n; */
DECL|macro|PM1_STS
mdefine_line|#define PM1_STS                         0x0100
DECL|macro|PM1_EN
mdefine_line|#define PM1_EN                          0x0200
DECL|macro|PM1_CONTROL
mdefine_line|#define PM1_CONTROL                     0x0300
DECL|macro|PM1A_CONTROL
mdefine_line|#define PM1A_CONTROL                    0x0400
DECL|macro|PM1B_CONTROL
mdefine_line|#define PM1B_CONTROL                    0x0500
DECL|macro|PM2_CONTROL
mdefine_line|#define PM2_CONTROL                     0x0600
DECL|macro|PM_TIMER
mdefine_line|#define PM_TIMER                        0x0700
DECL|macro|PROCESSOR_BLOCK
mdefine_line|#define PROCESSOR_BLOCK                 0x0800
DECL|macro|GPE0_STS_BLOCK
mdefine_line|#define GPE0_STS_BLOCK                  0x0900
DECL|macro|GPE0_EN_BLOCK
mdefine_line|#define GPE0_EN_BLOCK                   0x0A00
DECL|macro|GPE1_STS_BLOCK
mdefine_line|#define GPE1_STS_BLOCK                  0x0B00
DECL|macro|GPE1_EN_BLOCK
mdefine_line|#define GPE1_EN_BLOCK                   0x0C00
DECL|macro|SMI_CMD_BLOCK
mdefine_line|#define SMI_CMD_BLOCK                   0x0D00
multiline_comment|/*&n; * Address space bitmasks for mmio or io spaces&n; */
DECL|macro|SMI_CMD_ADDRESS_SPACE
mdefine_line|#define SMI_CMD_ADDRESS_SPACE           0x01
DECL|macro|PM1_BLK_ADDRESS_SPACE
mdefine_line|#define PM1_BLK_ADDRESS_SPACE           0x02
DECL|macro|PM2_CNT_BLK_ADDRESS_SPACE
mdefine_line|#define PM2_CNT_BLK_ADDRESS_SPACE       0x04
DECL|macro|PM_TMR_BLK_ADDRESS_SPACE
mdefine_line|#define PM_TMR_BLK_ADDRESS_SPACE        0x08
DECL|macro|GPE0_BLK_ADDRESS_SPACE
mdefine_line|#define GPE0_BLK_ADDRESS_SPACE          0x10
DECL|macro|GPE1_BLK_ADDRESS_SPACE
mdefine_line|#define GPE1_BLK_ADDRESS_SPACE          0x20
multiline_comment|/*&n; * Control bit definitions&n; */
DECL|macro|TMR_STS
mdefine_line|#define TMR_STS                         (PM1_STS | 0x01)
DECL|macro|BM_STS
mdefine_line|#define BM_STS                          (PM1_STS | 0x02)
DECL|macro|GBL_STS
mdefine_line|#define GBL_STS                         (PM1_STS | 0x03)
DECL|macro|PWRBTN_STS
mdefine_line|#define PWRBTN_STS                      (PM1_STS | 0x04)
DECL|macro|SLPBTN_STS
mdefine_line|#define SLPBTN_STS                      (PM1_STS | 0x05)
DECL|macro|RTC_STS
mdefine_line|#define RTC_STS                         (PM1_STS | 0x06)
DECL|macro|WAK_STS
mdefine_line|#define WAK_STS                         (PM1_STS | 0x07)
DECL|macro|TMR_EN
mdefine_line|#define TMR_EN                          (PM1_EN | 0x01)
multiline_comment|/* no BM_EN */
DECL|macro|GBL_EN
mdefine_line|#define GBL_EN                          (PM1_EN | 0x03)
DECL|macro|PWRBTN_EN
mdefine_line|#define PWRBTN_EN                       (PM1_EN | 0x04)
DECL|macro|SLPBTN_EN
mdefine_line|#define SLPBTN_EN                       (PM1_EN | 0x05)
DECL|macro|RTC_EN
mdefine_line|#define RTC_EN                          (PM1_EN | 0x06)
DECL|macro|WAK_EN
mdefine_line|#define WAK_EN                          (PM1_EN | 0x07)
DECL|macro|SCI_EN
mdefine_line|#define SCI_EN                          (PM1_CONTROL | 0x01)
DECL|macro|BM_RLD
mdefine_line|#define BM_RLD                          (PM1_CONTROL | 0x02)
DECL|macro|GBL_RLS
mdefine_line|#define GBL_RLS                         (PM1_CONTROL | 0x03)
DECL|macro|SLP_TYPE_A
mdefine_line|#define SLP_TYPE_A                      (PM1_CONTROL | 0x04)
DECL|macro|SLP_TYPE_B
mdefine_line|#define SLP_TYPE_B                      (PM1_CONTROL | 0x05)
DECL|macro|SLP_EN
mdefine_line|#define SLP_EN                          (PM1_CONTROL | 0x06)
DECL|macro|ARB_DIS
mdefine_line|#define ARB_DIS                         (PM2_CONTROL | 0x01)
DECL|macro|TMR_VAL
mdefine_line|#define TMR_VAL                         (PM_TIMER | 0x01)
DECL|macro|GPE0_STS
mdefine_line|#define GPE0_STS                        (GPE0_STS_BLOCK | 0x01)
DECL|macro|GPE0_EN
mdefine_line|#define GPE0_EN                         (GPE0_EN_BLOCK  | 0x01)
DECL|macro|GPE1_STS
mdefine_line|#define GPE1_STS                        (GPE1_STS_BLOCK | 0x01)
DECL|macro|GPE1_EN
mdefine_line|#define GPE1_EN                         (GPE1_EN_BLOCK  | 0x01)
DECL|macro|TMR_STS_MASK
mdefine_line|#define TMR_STS_MASK                    0x0001
DECL|macro|BM_STS_MASK
mdefine_line|#define BM_STS_MASK                     0x0010
DECL|macro|GBL_STS_MASK
mdefine_line|#define GBL_STS_MASK                    0x0020
DECL|macro|PWRBTN_STS_MASK
mdefine_line|#define PWRBTN_STS_MASK                 0x0100
DECL|macro|SLPBTN_STS_MASK
mdefine_line|#define SLPBTN_STS_MASK                 0x0200
DECL|macro|RTC_STS_MASK
mdefine_line|#define RTC_STS_MASK                    0x0400
DECL|macro|WAK_STS_MASK
mdefine_line|#define WAK_STS_MASK                    0x8000
DECL|macro|ALL_FIXED_STS_BITS
mdefine_line|#define ALL_FIXED_STS_BITS              (TMR_STS_MASK   | BM_STS_MASK  | GBL_STS_MASK &bslash;&n;&t;&t;&t;&t;&t;  | PWRBTN_STS_MASK | SLPBTN_STS_MASK &bslash;&n;&t;&t;&t;&t;&t;  | RTC_STS_MASK | WAK_STS_MASK)
DECL|macro|TMR_EN_MASK
mdefine_line|#define TMR_EN_MASK                     0x0001
DECL|macro|GBL_EN_MASK
mdefine_line|#define GBL_EN_MASK                     0x0020
DECL|macro|PWRBTN_EN_MASK
mdefine_line|#define PWRBTN_EN_MASK                  0x0100
DECL|macro|SLPBTN_EN_MASK
mdefine_line|#define SLPBTN_EN_MASK                  0x0200
DECL|macro|RTC_EN_MASK
mdefine_line|#define RTC_EN_MASK                     0x0400
DECL|macro|SCI_EN_MASK
mdefine_line|#define SCI_EN_MASK                     0x0001
DECL|macro|BM_RLD_MASK
mdefine_line|#define BM_RLD_MASK                     0x0002
DECL|macro|GBL_RLS_MASK
mdefine_line|#define GBL_RLS_MASK                    0x0004
DECL|macro|SLP_TYPE_X_MASK
mdefine_line|#define SLP_TYPE_X_MASK                 0x1C00
DECL|macro|SLP_EN_MASK
mdefine_line|#define SLP_EN_MASK                     0x2000
DECL|macro|ARB_DIS_MASK
mdefine_line|#define ARB_DIS_MASK                    0x0001
DECL|macro|TMR_VAL_MASK
mdefine_line|#define TMR_VAL_MASK                    0xFFFFFFFF
DECL|macro|GPE0_STS_MASK
mdefine_line|#define GPE0_STS_MASK
DECL|macro|GPE0_EN_MASK
mdefine_line|#define GPE0_EN_MASK
DECL|macro|GPE1_STS_MASK
mdefine_line|#define GPE1_STS_MASK
DECL|macro|GPE1_EN_MASK
mdefine_line|#define GPE1_EN_MASK
DECL|macro|ACPI_READ
mdefine_line|#define ACPI_READ                       1
DECL|macro|ACPI_WRITE
mdefine_line|#define ACPI_WRITE                      2
multiline_comment|/*****************************************************************************&n; *&n; * Resource descriptors&n; *&n; ****************************************************************************/
multiline_comment|/* Resource_type values */
DECL|macro|RESOURCE_TYPE_MEMORY_RANGE
mdefine_line|#define RESOURCE_TYPE_MEMORY_RANGE              0
DECL|macro|RESOURCE_TYPE_IO_RANGE
mdefine_line|#define RESOURCE_TYPE_IO_RANGE                  1
DECL|macro|RESOURCE_TYPE_BUS_NUMBER_RANGE
mdefine_line|#define RESOURCE_TYPE_BUS_NUMBER_RANGE          2
multiline_comment|/* Resource descriptor types and masks */
DECL|macro|RESOURCE_DESC_TYPE_LARGE
mdefine_line|#define RESOURCE_DESC_TYPE_LARGE                0x80
DECL|macro|RESOURCE_DESC_TYPE_SMALL
mdefine_line|#define RESOURCE_DESC_TYPE_SMALL                0x00
DECL|macro|RESOURCE_DESC_TYPE_MASK
mdefine_line|#define RESOURCE_DESC_TYPE_MASK                 0x80
DECL|macro|RESOURCE_DESC_SMALL_MASK
mdefine_line|#define RESOURCE_DESC_SMALL_MASK                0x78        /* Only bits 6:3 contain the type */
multiline_comment|/*&n; * Small resource descriptor types&n; * Note: The 3 length bits (2:0) must be zero&n; */
DECL|macro|RESOURCE_DESC_IRQ_FORMAT
mdefine_line|#define RESOURCE_DESC_IRQ_FORMAT                0x20
DECL|macro|RESOURCE_DESC_DMA_FORMAT
mdefine_line|#define RESOURCE_DESC_DMA_FORMAT                0x28
DECL|macro|RESOURCE_DESC_START_DEPENDENT
mdefine_line|#define RESOURCE_DESC_START_DEPENDENT           0x30
DECL|macro|RESOURCE_DESC_END_DEPENDENT
mdefine_line|#define RESOURCE_DESC_END_DEPENDENT             0x38
DECL|macro|RESOURCE_DESC_IO_PORT
mdefine_line|#define RESOURCE_DESC_IO_PORT                   0x40
DECL|macro|RESOURCE_DESC_FIXED_IO_PORT
mdefine_line|#define RESOURCE_DESC_FIXED_IO_PORT             0x48
DECL|macro|RESOURCE_DESC_SMALL_VENDOR
mdefine_line|#define RESOURCE_DESC_SMALL_VENDOR              0x70
DECL|macro|RESOURCE_DESC_END_TAG
mdefine_line|#define RESOURCE_DESC_END_TAG                   0x78
multiline_comment|/*&n; * Large resource descriptor types&n; */
DECL|macro|RESOURCE_DESC_MEMORY_24
mdefine_line|#define RESOURCE_DESC_MEMORY_24                 0x81
DECL|macro|RESOURCE_DESC_GENERAL_REGISTER
mdefine_line|#define RESOURCE_DESC_GENERAL_REGISTER          0x82
DECL|macro|RESOURCE_DESC_LARGE_VENDOR
mdefine_line|#define RESOURCE_DESC_LARGE_VENDOR              0x84
DECL|macro|RESOURCE_DESC_MEMORY_32
mdefine_line|#define RESOURCE_DESC_MEMORY_32                 0x85
DECL|macro|RESOURCE_DESC_FIXED_MEMORY_32
mdefine_line|#define RESOURCE_DESC_FIXED_MEMORY_32           0x86
DECL|macro|RESOURCE_DESC_DWORD_ADDRESS_SPACE
mdefine_line|#define RESOURCE_DESC_DWORD_ADDRESS_SPACE       0x87
DECL|macro|RESOURCE_DESC_WORD_ADDRESS_SPACE
mdefine_line|#define RESOURCE_DESC_WORD_ADDRESS_SPACE        0x88
DECL|macro|RESOURCE_DESC_EXTENDED_XRUPT
mdefine_line|#define RESOURCE_DESC_EXTENDED_XRUPT            0x89
DECL|macro|RESOURCE_DESC_QWORD_ADDRESS_SPACE
mdefine_line|#define RESOURCE_DESC_QWORD_ADDRESS_SPACE       0x8A
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
DECL|macro|ASCII_ZERO
mdefine_line|#define ASCII_ZERO                      0x30
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
DECL|typedef|db_method_info
)brace
id|db_method_info
suffix:semicolon
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
DECL|macro|MEM_MALLOC
mdefine_line|#define MEM_MALLOC                      0
DECL|macro|MEM_CALLOC
mdefine_line|#define MEM_CALLOC                      1
DECL|macro|MAX_MODULE_NAME
mdefine_line|#define MAX_MODULE_NAME                 16
DECL|macro|ACPI_COMMON_DEBUG_MEM_HEADER
mdefine_line|#define ACPI_COMMON_DEBUG_MEM_HEADER &bslash;&n;&t;struct acpi_debug_mem_block *previous; &bslash;&n;&t;struct acpi_debug_mem_block *next; &bslash;&n;&t;u32                         size; &bslash;&n;&t;u32                         component; &bslash;&n;&t;u32                         line; &bslash;&n;&t;NATIVE_CHAR                 module[MAX_MODULE_NAME]; &bslash;&n;&t;u8                          alloc_type;
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
