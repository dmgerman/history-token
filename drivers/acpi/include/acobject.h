multiline_comment|/******************************************************************************&n; *&n; * Name: acobject.h - Definition of acpi_operand_object  (Internal object only)&n; *       $Revision: 106 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _ACOBJECT_H
DECL|macro|_ACOBJECT_H
mdefine_line|#define _ACOBJECT_H
multiline_comment|/*&n; * The acpi_operand_object  is used to pass AML operands from the dispatcher&n; * to the interpreter, and to keep track of the various handlers such as&n; * address space handlers and notify handlers.  The object is a constant&n; * size in order to allow them to be cached and reused.&n; *&n; * All variants of the acpi_operand_object  are defined with the same&n; * sequence of field types, with fields that are not used in a particular&n; * variant being named &quot;Reserved&quot;.  This is not strictly necessary, but&n; * may in some circumstances simplify understanding if these structures&n; * need to be displayed in a debugger having limited (or no) support for&n; * union types.  It also simplifies some debug code in Dump_table() which&n; * dumps multi-level values: fetching Buffer.Pointer suffices to pick up&n; * the value or next level for any of several types.&n; */
multiline_comment|/******************************************************************************&n; *&n; * Common Descriptors&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Common area for all objects.&n; *&n; * Data_type is used to differentiate between internal descriptors, and MUST&n; * be the first byte in this structure.&n; */
DECL|macro|ACPI_OBJECT_COMMON_HEADER
mdefine_line|#define ACPI_OBJECT_COMMON_HEADER           /* SIZE/ALIGNMENT: 32 bits, one ptr plus trailing 8-bit flag */&bslash;&n;&t;u8                          descriptor;         /* To differentiate various internal objs */&bslash;&n;&t;u8                          type;               /* acpi_object_type */&bslash;&n;&t;u16                         reference_count;    /* For object deletion management */&bslash;&n;&t;union acpi_operand_obj      *next_object;       /* Objects linked to parent NS node */&bslash;&n;&t;u8                          flags; &bslash;&n;
multiline_comment|/* Defines for flag byte above */
DECL|macro|AOPOBJ_RESERVED
mdefine_line|#define AOPOBJ_RESERVED             0x01
DECL|macro|AOPOBJ_STATIC_POINTER
mdefine_line|#define AOPOBJ_STATIC_POINTER       0x02
DECL|macro|AOPOBJ_DATA_VALID
mdefine_line|#define AOPOBJ_DATA_VALID           0x04
DECL|macro|AOPOBJ_OBJECT_INITIALIZED
mdefine_line|#define AOPOBJ_OBJECT_INITIALIZED   0x08
DECL|macro|AOPOBJ_SETUP_COMPLETE
mdefine_line|#define AOPOBJ_SETUP_COMPLETE       0x10
DECL|macro|AOPOBJ_SINGLE_DATUM
mdefine_line|#define AOPOBJ_SINGLE_DATUM         0x20
multiline_comment|/*&n; * Common bitfield for the field objects&n; * &quot;Field Datum&quot;  -- a datum from the actual field object&n; * &quot;Buffer Datum&quot; -- a datum from a user buffer, read from or to be written to the field&n; */
DECL|macro|ACPI_COMMON_FIELD_INFO
mdefine_line|#define ACPI_COMMON_FIELD_INFO              /* SIZE/ALIGNMENT: 24 bits + three 32-bit values */&bslash;&n;&t;u8                          field_flags;        /* Access, update, and lock bits */&bslash;&n;&t;u8                          attribute;          /* From Access_as keyword */&bslash;&n;&t;u8                          access_byte_width;  /* Read/Write size in bytes */&bslash;&n;&t;u32                         bit_length;         /* Length of field in bits */&bslash;&n;&t;u32                         base_byte_offset;   /* Byte offset within containing object */&bslash;&n;&t;u8                          start_field_bit_offset;/* Bit offset within first field datum (0-63) */&bslash;&n;&t;u8                          datum_valid_bits;   /* Valid bit in first &quot;Field datum&quot; */&bslash;&n;&t;u8                          end_field_valid_bits; /* Valid bits in the last &quot;field datum&quot; */&bslash;&n;&t;u8                          end_buffer_valid_bits; /* Valid bits in the last &quot;buffer datum&quot; */&bslash;&n;&t;u32                         value;              /* Value to store into the Bank or Index register */&bslash;&n;&t;acpi_namespace_node         *node;              /* Link back to parent node */
multiline_comment|/*&n; * Fields common to both Strings and Buffers&n; */
DECL|macro|ACPI_COMMON_BUFFER_INFO
mdefine_line|#define ACPI_COMMON_BUFFER_INFO &bslash;&n;&t;u32                         length;
multiline_comment|/******************************************************************************&n; *&n; * Individual Object Descriptors&n; *&n; *****************************************************************************/
r_typedef
r_struct
multiline_comment|/* COMMON */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|typedef|ACPI_OBJECT_COMMON
)brace
id|ACPI_OBJECT_COMMON
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* CACHE_LIST */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|next
r_union
id|acpi_operand_obj
op_star
id|next
suffix:semicolon
multiline_comment|/* Link for object cache and internal lists*/
DECL|typedef|ACPI_OBJECT_CACHE_LIST
)brace
id|ACPI_OBJECT_CACHE_LIST
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* NUMBER - has value */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|value
id|acpi_integer
id|value
suffix:semicolon
DECL|typedef|ACPI_OBJECT_INTEGER
)brace
id|ACPI_OBJECT_INTEGER
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* STRING - has length and pointer - Null terminated, ASCII characters only */
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_BUFFER_INFO
DECL|member|pointer
id|NATIVE_CHAR
op_star
id|pointer
suffix:semicolon
multiline_comment|/* String value in AML stream or in allocated space */
DECL|typedef|ACPI_OBJECT_STRING
)brace
id|ACPI_OBJECT_STRING
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* BUFFER - has length and pointer - not null terminated */
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_BUFFER_INFO
DECL|member|pointer
id|u8
op_star
id|pointer
suffix:semicolon
multiline_comment|/* Buffer value in AML stream or in allocated space */
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
multiline_comment|/* Link back to parent node */
DECL|typedef|ACPI_OBJECT_BUFFER
)brace
id|ACPI_OBJECT_BUFFER
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* PACKAGE - has count, elements, next element */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|count
id|u32
id|count
suffix:semicolon
multiline_comment|/* # of elements in package */
DECL|member|elements
r_union
id|acpi_operand_obj
op_star
op_star
id|elements
suffix:semicolon
multiline_comment|/* Array of pointers to Acpi_objects */
DECL|member|next_element
r_union
id|acpi_operand_obj
op_star
op_star
id|next_element
suffix:semicolon
multiline_comment|/* used only while initializing */
DECL|typedef|ACPI_OBJECT_PACKAGE
)brace
id|ACPI_OBJECT_PACKAGE
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* DEVICE - has handle and notification handler/context */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|sys_handler
r_union
id|acpi_operand_obj
op_star
id|sys_handler
suffix:semicolon
multiline_comment|/* Handler for system notifies */
DECL|member|drv_handler
r_union
id|acpi_operand_obj
op_star
id|drv_handler
suffix:semicolon
multiline_comment|/* Handler for driver notifies */
DECL|member|addr_handler
r_union
id|acpi_operand_obj
op_star
id|addr_handler
suffix:semicolon
multiline_comment|/* Handler for Address space */
DECL|typedef|ACPI_OBJECT_DEVICE
)brace
id|ACPI_OBJECT_DEVICE
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* EVENT */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|semaphore
r_void
op_star
id|semaphore
suffix:semicolon
DECL|typedef|ACPI_OBJECT_EVENT
)brace
id|ACPI_OBJECT_EVENT
suffix:semicolon
DECL|macro|INFINITE_CONCURRENCY
mdefine_line|#define INFINITE_CONCURRENCY        0xFF
r_typedef
r_struct
multiline_comment|/* METHOD */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|method_flags
id|u8
id|method_flags
suffix:semicolon
DECL|member|param_count
id|u8
id|param_count
suffix:semicolon
DECL|member|aml_length
id|u32
id|aml_length
suffix:semicolon
DECL|member|semaphore
r_void
op_star
id|semaphore
suffix:semicolon
DECL|member|aml_start
id|u8
op_star
id|aml_start
suffix:semicolon
DECL|member|concurrency
id|u8
id|concurrency
suffix:semicolon
DECL|member|thread_count
id|u8
id|thread_count
suffix:semicolon
DECL|member|owning_id
id|acpi_owner_id
id|owning_id
suffix:semicolon
DECL|typedef|ACPI_OBJECT_METHOD
)brace
id|ACPI_OBJECT_METHOD
suffix:semicolon
DECL|struct|acpi_obj_mutex
r_typedef
r_struct
id|acpi_obj_mutex
multiline_comment|/* MUTEX */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|sync_level
id|u16
id|sync_level
suffix:semicolon
DECL|member|acquisition_depth
id|u16
id|acquisition_depth
suffix:semicolon
DECL|member|owner_thread
r_struct
id|acpi_thread_state
op_star
id|owner_thread
suffix:semicolon
DECL|member|semaphore
r_void
op_star
id|semaphore
suffix:semicolon
DECL|member|prev
r_union
id|acpi_operand_obj
op_star
id|prev
suffix:semicolon
multiline_comment|/* Link for list of acquired mutexes */
DECL|member|next
r_union
id|acpi_operand_obj
op_star
id|next
suffix:semicolon
multiline_comment|/* Link for list of acquired mutexes */
DECL|typedef|ACPI_OBJECT_MUTEX
)brace
id|ACPI_OBJECT_MUTEX
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* REGION */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|space_id
id|u8
id|space_id
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|address
id|ACPI_PHYSICAL_ADDRESS
id|address
suffix:semicolon
DECL|member|addr_handler
r_union
id|acpi_operand_obj
op_star
id|addr_handler
suffix:semicolon
multiline_comment|/* Handler for system notifies */
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
multiline_comment|/* containing object */
DECL|member|next
r_union
id|acpi_operand_obj
op_star
id|next
suffix:semicolon
DECL|typedef|ACPI_OBJECT_REGION
)brace
id|ACPI_OBJECT_REGION
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* POWER RESOURCE - has Handle and notification handler/context*/
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|system_level
id|u32
id|system_level
suffix:semicolon
DECL|member|resource_order
id|u32
id|resource_order
suffix:semicolon
DECL|member|sys_handler
r_union
id|acpi_operand_obj
op_star
id|sys_handler
suffix:semicolon
multiline_comment|/* Handler for system notifies */
DECL|member|drv_handler
r_union
id|acpi_operand_obj
op_star
id|drv_handler
suffix:semicolon
multiline_comment|/* Handler for driver notifies */
DECL|typedef|ACPI_OBJECT_POWER_RESOURCE
)brace
id|ACPI_OBJECT_POWER_RESOURCE
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* PROCESSOR - has Handle and notification handler/context*/
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|proc_id
id|u32
id|proc_id
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|address
id|ACPI_IO_ADDRESS
id|address
suffix:semicolon
DECL|member|sys_handler
r_union
id|acpi_operand_obj
op_star
id|sys_handler
suffix:semicolon
multiline_comment|/* Handler for system notifies */
DECL|member|drv_handler
r_union
id|acpi_operand_obj
op_star
id|drv_handler
suffix:semicolon
multiline_comment|/* Handler for driver notifies */
DECL|member|addr_handler
r_union
id|acpi_operand_obj
op_star
id|addr_handler
suffix:semicolon
multiline_comment|/* Handler for Address space */
DECL|typedef|ACPI_OBJECT_PROCESSOR
)brace
id|ACPI_OBJECT_PROCESSOR
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* THERMAL ZONE - has Handle and Handler/Context */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|sys_handler
r_union
id|acpi_operand_obj
op_star
id|sys_handler
suffix:semicolon
multiline_comment|/* Handler for system notifies */
DECL|member|drv_handler
r_union
id|acpi_operand_obj
op_star
id|drv_handler
suffix:semicolon
multiline_comment|/* Handler for driver notifies */
DECL|member|addr_handler
r_union
id|acpi_operand_obj
op_star
id|addr_handler
suffix:semicolon
multiline_comment|/* Handler for Address space */
DECL|typedef|ACPI_OBJECT_THERMAL_ZONE
)brace
id|ACPI_OBJECT_THERMAL_ZONE
suffix:semicolon
multiline_comment|/*&n; * Fields.  All share a common header/info field.&n; */
r_typedef
r_struct
multiline_comment|/* COMMON FIELD (for BUFFER, REGION, BANK, and INDEX fields) */
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_FIELD_INFO
DECL|member|region_obj
r_union
id|acpi_operand_obj
op_star
id|region_obj
suffix:semicolon
multiline_comment|/* Containing Operation Region object */
multiline_comment|/* (REGION/BANK fields only) */
DECL|typedef|ACPI_OBJECT_FIELD_COMMON
)brace
id|ACPI_OBJECT_FIELD_COMMON
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* REGION FIELD */
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_FIELD_INFO
DECL|member|region_obj
r_union
id|acpi_operand_obj
op_star
id|region_obj
suffix:semicolon
multiline_comment|/* Containing Op_region object */
DECL|typedef|ACPI_OBJECT_REGION_FIELD
)brace
id|ACPI_OBJECT_REGION_FIELD
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* BANK FIELD */
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_FIELD_INFO
DECL|member|region_obj
r_union
id|acpi_operand_obj
op_star
id|region_obj
suffix:semicolon
multiline_comment|/* Containing Op_region object */
DECL|member|bank_obj
r_union
id|acpi_operand_obj
op_star
id|bank_obj
suffix:semicolon
multiline_comment|/* Bank_select Register object */
DECL|typedef|ACPI_OBJECT_BANK_FIELD
)brace
id|ACPI_OBJECT_BANK_FIELD
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* INDEX FIELD */
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_FIELD_INFO
multiline_comment|/*&n;&t; * No &quot;Region_obj&quot; pointer needed since the Index and Data registers&n;&t; * are each field definitions unto themselves.&n;&t; */
DECL|member|index_obj
r_union
id|acpi_operand_obj
op_star
id|index_obj
suffix:semicolon
multiline_comment|/* Index register */
DECL|member|data_obj
r_union
id|acpi_operand_obj
op_star
id|data_obj
suffix:semicolon
multiline_comment|/* Data register */
DECL|typedef|ACPI_OBJECT_INDEX_FIELD
)brace
id|ACPI_OBJECT_INDEX_FIELD
suffix:semicolon
multiline_comment|/* The Buffer_field is different in that it is part of a Buffer, not an Op_region */
r_typedef
r_struct
multiline_comment|/* BUFFER FIELD */
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_FIELD_INFO
DECL|member|buffer_obj
r_union
id|acpi_operand_obj
op_star
id|buffer_obj
suffix:semicolon
multiline_comment|/* Containing Buffer object */
DECL|typedef|ACPI_OBJECT_BUFFER_FIELD
)brace
id|ACPI_OBJECT_BUFFER_FIELD
suffix:semicolon
multiline_comment|/*&n; * Handlers&n; */
r_typedef
r_struct
multiline_comment|/* NOTIFY HANDLER */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
multiline_comment|/* Parent device */
DECL|member|handler
id|acpi_notify_handler
id|handler
suffix:semicolon
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|typedef|ACPI_OBJECT_NOTIFY_HANDLER
)brace
id|ACPI_OBJECT_NOTIFY_HANDLER
suffix:semicolon
multiline_comment|/* Flags for address handler */
DECL|macro|ACPI_ADDR_HANDLER_DEFAULT_INSTALLED
mdefine_line|#define ACPI_ADDR_HANDLER_DEFAULT_INSTALLED  0x1
r_typedef
r_struct
multiline_comment|/* ADDRESS HANDLER */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|space_id
id|u8
id|space_id
suffix:semicolon
DECL|member|hflags
id|u16
id|hflags
suffix:semicolon
DECL|member|handler
id|acpi_adr_space_handler
id|handler
suffix:semicolon
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
multiline_comment|/* Parent device */
DECL|member|context
r_void
op_star
id|context
suffix:semicolon
DECL|member|setup
id|acpi_adr_space_setup
id|setup
suffix:semicolon
DECL|member|region_list
r_union
id|acpi_operand_obj
op_star
id|region_list
suffix:semicolon
multiline_comment|/* regions using this handler */
DECL|member|next
r_union
id|acpi_operand_obj
op_star
id|next
suffix:semicolon
DECL|typedef|ACPI_OBJECT_ADDR_HANDLER
)brace
id|ACPI_OBJECT_ADDR_HANDLER
suffix:semicolon
multiline_comment|/*&n; * The Reference object type is used for these opcodes:&n; * Arg[0-6], Local[0-7], Index_op, Name_op, Zero_op, One_op, Ones_op, Debug_op&n; */
r_typedef
r_struct
multiline_comment|/* Reference - Local object type */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|target_type
id|u8
id|target_type
suffix:semicolon
multiline_comment|/* Used for Index_op */
DECL|member|opcode
id|u16
id|opcode
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
multiline_comment|/* Used for Arg_op, Local_op, and Index_op */
DECL|member|object
r_void
op_star
id|object
suffix:semicolon
multiline_comment|/* Name_op=&gt;HANDLE to obj, Index_op=&gt;acpi_operand_object */
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
DECL|member|where
r_union
id|acpi_operand_obj
op_star
op_star
id|where
suffix:semicolon
DECL|typedef|ACPI_OBJECT_REFERENCE
)brace
id|ACPI_OBJECT_REFERENCE
suffix:semicolon
multiline_comment|/*&n; * Extra object is used as additional storage for types that&n; * have AML code in their declarations (Term_args) that must be&n; * evaluated at run time.&n; *&n; * Currently: Region and Field_unit types&n; */
r_typedef
r_struct
multiline_comment|/* EXTRA */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|byte_fill1
id|u8
id|byte_fill1
suffix:semicolon
DECL|member|word_fill1
id|u16
id|word_fill1
suffix:semicolon
DECL|member|aml_length
id|u32
id|aml_length
suffix:semicolon
DECL|member|aml_start
id|u8
op_star
id|aml_start
suffix:semicolon
DECL|member|method_REG
id|acpi_namespace_node
op_star
id|method_REG
suffix:semicolon
multiline_comment|/* _REG method for this region (if any) */
DECL|member|region_context
r_void
op_star
id|region_context
suffix:semicolon
multiline_comment|/* Region-specific data */
DECL|typedef|ACPI_OBJECT_EXTRA
)brace
id|ACPI_OBJECT_EXTRA
suffix:semicolon
r_typedef
r_struct
multiline_comment|/* DATA */
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|handler
id|ACPI_OBJECT_HANDLER
id|handler
suffix:semicolon
DECL|member|pointer
r_void
op_star
id|pointer
suffix:semicolon
DECL|typedef|ACPI_OBJECT_DATA
)brace
id|ACPI_OBJECT_DATA
suffix:semicolon
multiline_comment|/******************************************************************************&n; *&n; * acpi_operand_object  Descriptor - a giant union of all of the above&n; *&n; *****************************************************************************/
DECL|union|acpi_operand_obj
r_typedef
r_union
id|acpi_operand_obj
(brace
DECL|member|common
id|ACPI_OBJECT_COMMON
id|common
suffix:semicolon
DECL|member|cache
id|ACPI_OBJECT_CACHE_LIST
id|cache
suffix:semicolon
DECL|member|integer
id|ACPI_OBJECT_INTEGER
id|integer
suffix:semicolon
DECL|member|string
id|ACPI_OBJECT_STRING
id|string
suffix:semicolon
DECL|member|buffer
id|ACPI_OBJECT_BUFFER
id|buffer
suffix:semicolon
DECL|member|package
id|ACPI_OBJECT_PACKAGE
id|package
suffix:semicolon
DECL|member|buffer_field
id|ACPI_OBJECT_BUFFER_FIELD
id|buffer_field
suffix:semicolon
DECL|member|device
id|ACPI_OBJECT_DEVICE
id|device
suffix:semicolon
DECL|member|event
id|ACPI_OBJECT_EVENT
id|event
suffix:semicolon
DECL|member|method
id|ACPI_OBJECT_METHOD
id|method
suffix:semicolon
DECL|member|mutex
id|ACPI_OBJECT_MUTEX
id|mutex
suffix:semicolon
DECL|member|region
id|ACPI_OBJECT_REGION
id|region
suffix:semicolon
DECL|member|power_resource
id|ACPI_OBJECT_POWER_RESOURCE
id|power_resource
suffix:semicolon
DECL|member|processor
id|ACPI_OBJECT_PROCESSOR
id|processor
suffix:semicolon
DECL|member|thermal_zone
id|ACPI_OBJECT_THERMAL_ZONE
id|thermal_zone
suffix:semicolon
DECL|member|common_field
id|ACPI_OBJECT_FIELD_COMMON
id|common_field
suffix:semicolon
DECL|member|field
id|ACPI_OBJECT_REGION_FIELD
id|field
suffix:semicolon
DECL|member|bank_field
id|ACPI_OBJECT_BANK_FIELD
id|bank_field
suffix:semicolon
DECL|member|index_field
id|ACPI_OBJECT_INDEX_FIELD
id|index_field
suffix:semicolon
DECL|member|reference
id|ACPI_OBJECT_REFERENCE
id|reference
suffix:semicolon
DECL|member|notify_handler
id|ACPI_OBJECT_NOTIFY_HANDLER
id|notify_handler
suffix:semicolon
DECL|member|addr_handler
id|ACPI_OBJECT_ADDR_HANDLER
id|addr_handler
suffix:semicolon
DECL|member|extra
id|ACPI_OBJECT_EXTRA
id|extra
suffix:semicolon
DECL|member|data
id|ACPI_OBJECT_DATA
id|data
suffix:semicolon
DECL|typedef|acpi_operand_object
)brace
id|acpi_operand_object
suffix:semicolon
macro_line|#endif /* _ACOBJECT_H */
eof
