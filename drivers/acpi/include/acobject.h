multiline_comment|/******************************************************************************&n; *&n; * Name: acobject.h - Definition of acpi_operand_object  (Internal object only)&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef _ACOBJECT_H
DECL|macro|_ACOBJECT_H
mdefine_line|#define _ACOBJECT_H
multiline_comment|/*&n; * The acpi_operand_object  is used to pass AML operands from the dispatcher&n; * to the interpreter, and to keep track of the various handlers such as&n; * address space handlers and notify handlers.  The object is a constant&n; * size in order to allow it to be cached and reused.&n; */
multiline_comment|/*******************************************************************************&n; *&n; * Common Descriptors&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Common area for all objects.&n; *&n; * data_type is used to differentiate between internal descriptors, and MUST&n; * be the first byte in this structure.&n; */
DECL|macro|ACPI_OBJECT_COMMON_HEADER
mdefine_line|#define ACPI_OBJECT_COMMON_HEADER           /* SIZE/ALIGNMENT: 32 bits, one ptr plus trailing 8-bit flag */&bslash;&n;&t;u8                          descriptor;         /* To differentiate various internal objs */&bslash;&n;&t;u8                          type;               /* acpi_object_type */&bslash;&n;&t;u16                         reference_count;    /* For object deletion management */&bslash;&n;&t;union acpi_operand_obj      *next_object;       /* Objects linked to parent NS node */&bslash;&n;&t;u8                          flags; &bslash;&n;
multiline_comment|/* Values for flag byte above */
DECL|macro|AOPOBJ_AML_CONSTANT
mdefine_line|#define AOPOBJ_AML_CONSTANT         0x01
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
mdefine_line|#define ACPI_COMMON_FIELD_INFO              /* SIZE/ALIGNMENT: 24 bits + three 32-bit values */&bslash;&n;&t;u8                          field_flags;        /* Access, update, and lock bits */&bslash;&n;&t;u8                          attribute;          /* From access_as keyword */&bslash;&n;&t;u8                          access_byte_width;  /* Read/Write size in bytes */&bslash;&n;&t;u32                         bit_length;         /* Length of field in bits */&bslash;&n;&t;u32                         base_byte_offset;   /* Byte offset within containing object */&bslash;&n;&t;u8                          start_field_bit_offset;/* Bit offset within first field datum (0-63) */&bslash;&n;&t;u8                          datum_valid_bits;   /* Valid bit in first &quot;Field datum&quot; */&bslash;&n;&t;u8                          end_field_valid_bits; /* Valid bits in the last &quot;field datum&quot; */&bslash;&n;&t;u8                          end_buffer_valid_bits; /* Valid bits in the last &quot;buffer datum&quot; */&bslash;&n;&t;u32                         value;              /* Value to store into the Bank or Index register */&bslash;&n;&t;acpi_namespace_node         *node;              /* Link back to parent node */
multiline_comment|/*&n; * Fields common to both Strings and Buffers&n; */
DECL|macro|ACPI_COMMON_BUFFER_INFO
mdefine_line|#define ACPI_COMMON_BUFFER_INFO &bslash;&n;&t;u32                         length;
multiline_comment|/*&n; * Common fields for objects that support ASL notifications&n; */
DECL|macro|ACPI_COMMON_NOTIFY_INFO
mdefine_line|#define ACPI_COMMON_NOTIFY_INFO &bslash;&n;&t;union acpi_operand_obj      *sys_handler;        /* Handler for system notifies */&bslash;&n;&t;union acpi_operand_obj      *drv_handler;        /* Handler for driver notifies */&bslash;&n;&t;union acpi_operand_obj      *addr_handler;       /* Handler for Address space */
multiline_comment|/******************************************************************************&n; *&n; * Basic data types&n; *&n; *****************************************************************************/
DECL|struct|acpi_object_common
r_typedef
r_struct
id|acpi_object_common
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|typedef|acpi_object_common
)brace
id|acpi_object_common
suffix:semicolon
DECL|struct|acpi_object_integer
r_typedef
r_struct
id|acpi_object_integer
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|value
id|acpi_integer
id|value
suffix:semicolon
DECL|typedef|acpi_object_integer
)brace
id|acpi_object_integer
suffix:semicolon
DECL|struct|acpi_object_string
r_typedef
r_struct
id|acpi_object_string
multiline_comment|/* Null terminated, ASCII characters only */
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_BUFFER_INFO
DECL|member|pointer
r_char
op_star
id|pointer
suffix:semicolon
multiline_comment|/* String in AML stream or allocated string */
DECL|typedef|acpi_object_string
)brace
id|acpi_object_string
suffix:semicolon
DECL|struct|acpi_object_buffer
r_typedef
r_struct
id|acpi_object_buffer
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_BUFFER_INFO
DECL|member|pointer
id|u8
op_star
id|pointer
suffix:semicolon
multiline_comment|/* Buffer in AML stream or allocated buffer */
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
multiline_comment|/* Link back to parent node */
DECL|member|aml_start
id|u8
op_star
id|aml_start
suffix:semicolon
DECL|member|aml_length
id|u32
id|aml_length
suffix:semicolon
DECL|typedef|acpi_object_buffer
)brace
id|acpi_object_buffer
suffix:semicolon
DECL|struct|acpi_object_package
r_typedef
r_struct
id|acpi_object_package
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|count
id|u32
id|count
suffix:semicolon
multiline_comment|/* # of elements in package */
DECL|member|aml_length
id|u32
id|aml_length
suffix:semicolon
DECL|member|aml_start
id|u8
op_star
id|aml_start
suffix:semicolon
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
multiline_comment|/* Link back to parent node */
DECL|member|elements
r_union
id|acpi_operand_obj
op_star
op_star
id|elements
suffix:semicolon
multiline_comment|/* Array of pointers to acpi_objects */
DECL|typedef|acpi_object_package
)brace
id|acpi_object_package
suffix:semicolon
multiline_comment|/******************************************************************************&n; *&n; * Complex data types&n; *&n; *****************************************************************************/
DECL|struct|acpi_object_event
r_typedef
r_struct
id|acpi_object_event
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|semaphore
r_void
op_star
id|semaphore
suffix:semicolon
DECL|typedef|acpi_object_event
)brace
id|acpi_object_event
suffix:semicolon
DECL|macro|INFINITE_CONCURRENCY
mdefine_line|#define INFINITE_CONCURRENCY        0xFF
DECL|struct|acpi_object_method
r_typedef
r_struct
id|acpi_object_method
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
DECL|typedef|acpi_object_method
)brace
id|acpi_object_method
suffix:semicolon
DECL|struct|acpi_object_mutex
r_typedef
r_struct
id|acpi_object_mutex
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
DECL|member|node
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
multiline_comment|/* containing object */
DECL|typedef|acpi_object_mutex
)brace
id|acpi_object_mutex
suffix:semicolon
DECL|struct|acpi_object_region
r_typedef
r_struct
id|acpi_object_region
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|space_id
id|u8
id|space_id
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
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|address
id|acpi_physical_address
id|address
suffix:semicolon
DECL|typedef|acpi_object_region
)brace
id|acpi_object_region
suffix:semicolon
multiline_comment|/******************************************************************************&n; *&n; * Objects that can be notified.  All share a common notify_info area.&n; *&n; *****************************************************************************/
DECL|struct|acpi_object_notify_common
r_typedef
r_struct
id|acpi_object_notify_common
multiline_comment|/* COMMON NOTIFY for POWER, PROCESSOR, DEVICE, and THERMAL */
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_NOTIFY_INFO
DECL|typedef|acpi_object_notify_common
)brace
id|acpi_object_notify_common
suffix:semicolon
DECL|struct|acpi_object_device
r_typedef
r_struct
id|acpi_object_device
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_NOTIFY_INFO
DECL|typedef|acpi_object_device
)brace
id|acpi_object_device
suffix:semicolon
DECL|struct|acpi_object_power_resource
r_typedef
r_struct
id|acpi_object_power_resource
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_NOTIFY_INFO
DECL|member|system_level
id|u32
id|system_level
suffix:semicolon
DECL|member|resource_order
id|u32
id|resource_order
suffix:semicolon
DECL|typedef|acpi_object_power_resource
)brace
id|acpi_object_power_resource
suffix:semicolon
DECL|struct|acpi_object_processor
r_typedef
r_struct
id|acpi_object_processor
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_NOTIFY_INFO
DECL|member|proc_id
id|u32
id|proc_id
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|address
id|acpi_io_address
id|address
suffix:semicolon
DECL|typedef|acpi_object_processor
)brace
id|acpi_object_processor
suffix:semicolon
DECL|struct|acpi_object_thermal_zone
r_typedef
r_struct
id|acpi_object_thermal_zone
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_NOTIFY_INFO
DECL|typedef|acpi_object_thermal_zone
)brace
id|acpi_object_thermal_zone
suffix:semicolon
multiline_comment|/******************************************************************************&n; *&n; * Fields.  All share a common header/info field.&n; *&n; *****************************************************************************/
DECL|struct|acpi_object_field_common
r_typedef
r_struct
id|acpi_object_field_common
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
DECL|typedef|acpi_object_field_common
)brace
id|acpi_object_field_common
suffix:semicolon
DECL|struct|acpi_object_region_field
r_typedef
r_struct
id|acpi_object_region_field
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_FIELD_INFO
DECL|member|region_obj
r_union
id|acpi_operand_obj
op_star
id|region_obj
suffix:semicolon
multiline_comment|/* Containing op_region object */
DECL|typedef|acpi_object_region_field
)brace
id|acpi_object_region_field
suffix:semicolon
DECL|struct|acpi_object_bank_field
r_typedef
r_struct
id|acpi_object_bank_field
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_FIELD_INFO
DECL|member|region_obj
r_union
id|acpi_operand_obj
op_star
id|region_obj
suffix:semicolon
multiline_comment|/* Containing op_region object */
DECL|member|bank_obj
r_union
id|acpi_operand_obj
op_star
id|bank_obj
suffix:semicolon
multiline_comment|/* bank_select Register object */
DECL|typedef|acpi_object_bank_field
)brace
id|acpi_object_bank_field
suffix:semicolon
DECL|struct|acpi_object_index_field
r_typedef
r_struct
id|acpi_object_index_field
(brace
id|ACPI_OBJECT_COMMON_HEADER
id|ACPI_COMMON_FIELD_INFO
multiline_comment|/*&n;&t; * No &quot;region_obj&quot; pointer needed since the Index and Data registers&n;&t; * are each field definitions unto themselves.&n;&t; */
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
DECL|typedef|acpi_object_index_field
)brace
id|acpi_object_index_field
suffix:semicolon
multiline_comment|/* The buffer_field is different in that it is part of a Buffer, not an op_region */
DECL|struct|acpi_object_buffer_field
r_typedef
r_struct
id|acpi_object_buffer_field
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
DECL|typedef|acpi_object_buffer_field
)brace
id|acpi_object_buffer_field
suffix:semicolon
multiline_comment|/******************************************************************************&n; *&n; * Objects for handlers&n; *&n; *****************************************************************************/
DECL|struct|acpi_object_notify_handler
r_typedef
r_struct
id|acpi_object_notify_handler
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
DECL|typedef|acpi_object_notify_handler
)brace
id|acpi_object_notify_handler
suffix:semicolon
multiline_comment|/* Flags for address handler */
DECL|macro|ACPI_ADDR_HANDLER_DEFAULT_INSTALLED
mdefine_line|#define ACPI_ADDR_HANDLER_DEFAULT_INSTALLED  0x1
DECL|struct|acpi_object_addr_handler
r_typedef
r_struct
id|acpi_object_addr_handler
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
DECL|typedef|acpi_object_addr_handler
)brace
id|acpi_object_addr_handler
suffix:semicolon
multiline_comment|/******************************************************************************&n; *&n; * Special internal objects&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * The Reference object type is used for these opcodes:&n; * Arg[0-6], Local[0-7], index_op, name_op, zero_op, one_op, ones_op, debug_op&n; */
DECL|struct|acpi_object_reference
r_typedef
r_struct
id|acpi_object_reference
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|target_type
id|u8
id|target_type
suffix:semicolon
multiline_comment|/* Used for index_op */
DECL|member|opcode
id|u16
id|opcode
suffix:semicolon
DECL|member|offset
id|u32
id|offset
suffix:semicolon
multiline_comment|/* Used for arg_op, local_op, and index_op */
DECL|member|object
r_void
op_star
id|object
suffix:semicolon
multiline_comment|/* name_op=&gt;HANDLE to obj, index_op=&gt;acpi_operand_object */
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
DECL|typedef|acpi_object_reference
)brace
id|acpi_object_reference
suffix:semicolon
multiline_comment|/*&n; * Extra object is used as additional storage for types that&n; * have AML code in their declarations (term_args) that must be&n; * evaluated at run time.&n; *&n; * Currently: Region and field_unit types&n; */
DECL|struct|acpi_object_extra
r_typedef
r_struct
id|acpi_object_extra
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
DECL|typedef|acpi_object_extra
)brace
id|acpi_object_extra
suffix:semicolon
multiline_comment|/* Additional data that can be attached to namespace nodes */
DECL|struct|acpi_object_data
r_typedef
r_struct
id|acpi_object_data
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|handler
id|acpi_object_handler
id|handler
suffix:semicolon
DECL|member|pointer
r_void
op_star
id|pointer
suffix:semicolon
DECL|typedef|acpi_object_data
)brace
id|acpi_object_data
suffix:semicolon
multiline_comment|/* Structure used when objects are cached for reuse */
DECL|struct|acpi_object_cache_list
r_typedef
r_struct
id|acpi_object_cache_list
(brace
id|ACPI_OBJECT_COMMON_HEADER
DECL|member|next
r_union
id|acpi_operand_obj
op_star
id|next
suffix:semicolon
multiline_comment|/* Link for object cache and internal lists*/
DECL|typedef|acpi_object_cache_list
)brace
id|acpi_object_cache_list
suffix:semicolon
multiline_comment|/******************************************************************************&n; *&n; * acpi_operand_object Descriptor - a giant union of all of the above&n; *&n; *****************************************************************************/
DECL|union|acpi_operand_obj
r_typedef
r_union
id|acpi_operand_obj
(brace
DECL|member|common
id|acpi_object_common
id|common
suffix:semicolon
DECL|member|integer
id|acpi_object_integer
id|integer
suffix:semicolon
DECL|member|string
id|acpi_object_string
id|string
suffix:semicolon
DECL|member|buffer
id|acpi_object_buffer
id|buffer
suffix:semicolon
DECL|member|package
id|acpi_object_package
id|package
suffix:semicolon
DECL|member|event
id|acpi_object_event
id|event
suffix:semicolon
DECL|member|method
id|acpi_object_method
id|method
suffix:semicolon
DECL|member|mutex
id|acpi_object_mutex
id|mutex
suffix:semicolon
DECL|member|region
id|acpi_object_region
id|region
suffix:semicolon
DECL|member|common_notify
id|acpi_object_notify_common
id|common_notify
suffix:semicolon
DECL|member|device
id|acpi_object_device
id|device
suffix:semicolon
DECL|member|power_resource
id|acpi_object_power_resource
id|power_resource
suffix:semicolon
DECL|member|processor
id|acpi_object_processor
id|processor
suffix:semicolon
DECL|member|thermal_zone
id|acpi_object_thermal_zone
id|thermal_zone
suffix:semicolon
DECL|member|common_field
id|acpi_object_field_common
id|common_field
suffix:semicolon
DECL|member|field
id|acpi_object_region_field
id|field
suffix:semicolon
DECL|member|buffer_field
id|acpi_object_buffer_field
id|buffer_field
suffix:semicolon
DECL|member|bank_field
id|acpi_object_bank_field
id|bank_field
suffix:semicolon
DECL|member|index_field
id|acpi_object_index_field
id|index_field
suffix:semicolon
DECL|member|notify_handler
id|acpi_object_notify_handler
id|notify_handler
suffix:semicolon
DECL|member|addr_handler
id|acpi_object_addr_handler
id|addr_handler
suffix:semicolon
DECL|member|reference
id|acpi_object_reference
id|reference
suffix:semicolon
DECL|member|extra
id|acpi_object_extra
id|extra
suffix:semicolon
DECL|member|data
id|acpi_object_data
id|data
suffix:semicolon
DECL|member|cache
id|acpi_object_cache_list
id|cache
suffix:semicolon
DECL|typedef|acpi_operand_object
)brace
id|acpi_operand_object
suffix:semicolon
multiline_comment|/******************************************************************************&n; *&n; * acpi_descriptor - objects that share a common descriptor identifier&n; *&n; *****************************************************************************/
multiline_comment|/* Object descriptor types */
DECL|macro|ACPI_DESC_TYPE_CACHED
mdefine_line|#define ACPI_DESC_TYPE_CACHED           0x11    /* Used only when object is cached */
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
DECL|macro|ACPI_DESC_TYPE_STATE_THREAD
mdefine_line|#define ACPI_DESC_TYPE_STATE_THREAD     0x29
DECL|macro|ACPI_DESC_TYPE_WALK
mdefine_line|#define ACPI_DESC_TYPE_WALK             0x44
DECL|macro|ACPI_DESC_TYPE_PARSER
mdefine_line|#define ACPI_DESC_TYPE_PARSER           0x66
DECL|macro|ACPI_DESC_TYPE_OPERAND
mdefine_line|#define ACPI_DESC_TYPE_OPERAND          0x88
DECL|macro|ACPI_DESC_TYPE_NAMED
mdefine_line|#define ACPI_DESC_TYPE_NAMED            0xAA
DECL|union|acpi_desc
r_typedef
r_union
id|acpi_desc
(brace
DECL|member|descriptor_id
id|u8
id|descriptor_id
suffix:semicolon
multiline_comment|/* To differentiate various internal objs */
"&bslash;"
DECL|member|object
id|acpi_operand_object
id|object
suffix:semicolon
DECL|member|node
id|acpi_namespace_node
id|node
suffix:semicolon
DECL|member|op
id|acpi_parse_object
id|op
suffix:semicolon
DECL|typedef|acpi_descriptor
)brace
id|acpi_descriptor
suffix:semicolon
macro_line|#endif /* _ACOBJECT_H */
eof
