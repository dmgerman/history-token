multiline_comment|/******************************************************************************&n; *&n; * Name: actypes.h - Common data types for the entire ACPI subsystem&n; *       $Revision: 224 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __ACTYPES_H__
DECL|macro|__ACTYPES_H__
mdefine_line|#define __ACTYPES_H__
multiline_comment|/*! [Begin] no source code translation (keep the typedefs) */
multiline_comment|/*&n; * Data types - Fixed across all compilation models&n; *&n; * BOOLEAN      Logical Boolean.&n; *              1 byte value containing a 0 for FALSE or a 1 for TRUE.&n; *              Other values are undefined.&n; *&n; * INT8         8-bit  (1 byte) signed value&n; * UINT8        8-bit  (1 byte) unsigned value&n; * INT16        16-bit (2 byte) signed value&n; * UINT16       16-bit (2 byte) unsigned value&n; * INT32        32-bit (4 byte) signed value&n; * UINT32       32-bit (4 byte) unsigned value&n; * INT64        64-bit (8 byte) signed value&n; * UINT64       64-bit (8 byte) unsigned value&n; * NATIVE_INT   32-bit on IA-32, 64-bit on IA-64 signed value&n; * NATIVE_UINT  32-bit on IA-32, 64-bit on IA-64 unsigned value&n; */
macro_line|#ifdef _IA64
multiline_comment|/*&n; * 64-bit type definitions&n; */
DECL|typedef|UINT8
r_typedef
r_int
r_char
id|UINT8
suffix:semicolon
DECL|typedef|BOOLEAN
r_typedef
r_int
r_char
id|BOOLEAN
suffix:semicolon
DECL|typedef|UINT16
r_typedef
r_int
r_int
id|UINT16
suffix:semicolon
DECL|typedef|INT32
r_typedef
r_int
id|INT32
suffix:semicolon
DECL|typedef|UINT32
r_typedef
r_int
r_int
id|UINT32
suffix:semicolon
DECL|typedef|UINT64
r_typedef
id|COMPILER_DEPENDENT_UINT64
id|UINT64
suffix:semicolon
DECL|typedef|NATIVE_UINT
r_typedef
id|UINT64
id|NATIVE_UINT
suffix:semicolon
DECL|typedef|NATIVE_INT
r_typedef
id|UINT64
id|NATIVE_INT
suffix:semicolon
DECL|typedef|ACPI_TBLPTR
r_typedef
id|NATIVE_UINT
id|ACPI_TBLPTR
suffix:semicolon
DECL|typedef|ACPI_IO_ADDRESS
r_typedef
id|UINT64
id|ACPI_IO_ADDRESS
suffix:semicolon
DECL|typedef|ACPI_PHYSICAL_ADDRESS
r_typedef
id|UINT64
id|ACPI_PHYSICAL_ADDRESS
suffix:semicolon
DECL|typedef|ACPI_SIZE
r_typedef
id|UINT64
id|ACPI_SIZE
suffix:semicolon
DECL|macro|ALIGNED_ADDRESS_BOUNDARY
mdefine_line|#define ALIGNED_ADDRESS_BOUNDARY        0x00000008      /* No hardware alignment support in IA64 */
DECL|macro|ACPI_USE_NATIVE_DIVIDE
mdefine_line|#define ACPI_USE_NATIVE_DIVIDE                          /* Native 64-bit integer support */
DECL|macro|ACPI_MAX_PTR
mdefine_line|#define ACPI_MAX_PTR                    0xFFFFFFFFFFFFFFFF
macro_line|#elif _IA16
multiline_comment|/*&n; * 16-bit type definitions&n; */
DECL|typedef|UINT8
r_typedef
r_int
r_char
id|UINT8
suffix:semicolon
DECL|typedef|BOOLEAN
r_typedef
r_int
r_char
id|BOOLEAN
suffix:semicolon
DECL|typedef|UINT16
r_typedef
r_int
r_int
id|UINT16
suffix:semicolon
DECL|typedef|INT32
r_typedef
r_int
id|INT32
suffix:semicolon
DECL|typedef|INT16
r_typedef
r_int
id|INT16
suffix:semicolon
DECL|typedef|UINT32
r_typedef
r_int
r_int
id|UINT32
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|Lo
id|UINT32
id|Lo
suffix:semicolon
DECL|member|Hi
id|UINT32
id|Hi
suffix:semicolon
DECL|typedef|UINT64
)brace
id|UINT64
suffix:semicolon
DECL|typedef|NATIVE_UINT
r_typedef
id|UINT16
id|NATIVE_UINT
suffix:semicolon
DECL|typedef|NATIVE_INT
r_typedef
id|INT16
id|NATIVE_INT
suffix:semicolon
DECL|typedef|ACPI_TBLPTR
r_typedef
id|UINT32
id|ACPI_TBLPTR
suffix:semicolon
DECL|typedef|ACPI_IO_ADDRESS
r_typedef
id|UINT32
id|ACPI_IO_ADDRESS
suffix:semicolon
DECL|typedef|ACPI_PHYSICAL_ADDRESS
r_typedef
r_char
op_star
id|ACPI_PHYSICAL_ADDRESS
suffix:semicolon
DECL|typedef|ACPI_SIZE
r_typedef
id|UINT32
id|ACPI_SIZE
suffix:semicolon
DECL|macro|ALIGNED_ADDRESS_BOUNDARY
mdefine_line|#define ALIGNED_ADDRESS_BOUNDARY        0x00000002
DECL|macro|_HW_ALIGNMENT_SUPPORT
mdefine_line|#define _HW_ALIGNMENT_SUPPORT
DECL|macro|ACPI_USE_NATIVE_DIVIDE
mdefine_line|#define ACPI_USE_NATIVE_DIVIDE                          /* No 64-bit integers, ok to use native divide */
DECL|macro|ACPI_MAX_PTR
mdefine_line|#define ACPI_MAX_PTR                    0xFFFF
multiline_comment|/*&n; * (16-bit only) internal integers must be 32-bits, so&n; * 64-bit integers cannot be supported&n; */
DECL|macro|ACPI_NO_INTEGER64_SUPPORT
mdefine_line|#define ACPI_NO_INTEGER64_SUPPORT
macro_line|#else
multiline_comment|/*&n; * 32-bit type definitions (default)&n; */
DECL|typedef|UINT8
r_typedef
r_int
r_char
id|UINT8
suffix:semicolon
DECL|typedef|BOOLEAN
r_typedef
r_int
r_char
id|BOOLEAN
suffix:semicolon
DECL|typedef|UINT16
r_typedef
r_int
r_int
id|UINT16
suffix:semicolon
DECL|typedef|INT32
r_typedef
r_int
id|INT32
suffix:semicolon
DECL|typedef|UINT32
r_typedef
r_int
r_int
id|UINT32
suffix:semicolon
DECL|typedef|UINT64
r_typedef
id|COMPILER_DEPENDENT_UINT64
id|UINT64
suffix:semicolon
DECL|typedef|NATIVE_UINT
r_typedef
id|UINT32
id|NATIVE_UINT
suffix:semicolon
DECL|typedef|NATIVE_INT
r_typedef
id|INT32
id|NATIVE_INT
suffix:semicolon
DECL|typedef|ACPI_TBLPTR
r_typedef
id|NATIVE_UINT
id|ACPI_TBLPTR
suffix:semicolon
DECL|typedef|ACPI_IO_ADDRESS
r_typedef
id|UINT32
id|ACPI_IO_ADDRESS
suffix:semicolon
DECL|typedef|ACPI_PHYSICAL_ADDRESS
r_typedef
id|UINT64
id|ACPI_PHYSICAL_ADDRESS
suffix:semicolon
DECL|typedef|ACPI_SIZE
r_typedef
id|UINT32
id|ACPI_SIZE
suffix:semicolon
DECL|macro|ALIGNED_ADDRESS_BOUNDARY
mdefine_line|#define ALIGNED_ADDRESS_BOUNDARY        0x00000004
DECL|macro|_HW_ALIGNMENT_SUPPORT
mdefine_line|#define _HW_ALIGNMENT_SUPPORT
DECL|macro|ACPI_MAX_PTR
mdefine_line|#define ACPI_MAX_PTR                    0xFFFFFFFF
macro_line|#endif
multiline_comment|/*&n; * Miscellaneous common types&n; */
DECL|typedef|UINT32_BIT
r_typedef
id|UINT32
id|UINT32_BIT
suffix:semicolon
DECL|typedef|ACPI_PTRDIFF
r_typedef
id|NATIVE_UINT
id|ACPI_PTRDIFF
suffix:semicolon
DECL|typedef|NATIVE_CHAR
r_typedef
r_char
id|NATIVE_CHAR
suffix:semicolon
multiline_comment|/*&n; * Data type ranges&n; */
DECL|macro|ACPI_UINT8_MAX
mdefine_line|#define ACPI_UINT8_MAX                  (UINT8)  0xFF
DECL|macro|ACPI_UINT16_MAX
mdefine_line|#define ACPI_UINT16_MAX                 (UINT16) 0xFFFF
DECL|macro|ACPI_UINT32_MAX
mdefine_line|#define ACPI_UINT32_MAX                 (UINT32) 0xFFFFFFFF
DECL|macro|ACPI_UINT64_MAX
mdefine_line|#define ACPI_UINT64_MAX                 (UINT64) 0xFFFFFFFFFFFFFFFF
DECL|macro|ACPI_ASCII_MAX
mdefine_line|#define ACPI_ASCII_MAX                  0x7F
macro_line|#ifdef DEFINE_ALTERNATE_TYPES
multiline_comment|/*&n; * Types used only in translated source, defined here to enable&n; * cross-platform compilation only.&n; */
DECL|typedef|s32
r_typedef
id|INT32
id|s32
suffix:semicolon
DECL|typedef|u8
r_typedef
id|UINT8
id|u8
suffix:semicolon
DECL|typedef|u16
r_typedef
id|UINT16
id|u16
suffix:semicolon
DECL|typedef|u32
r_typedef
id|UINT32
id|u32
suffix:semicolon
DECL|typedef|u64
r_typedef
id|UINT64
id|u64
suffix:semicolon
macro_line|#endif
multiline_comment|/*! [End] no source code translation !*/
multiline_comment|/*&n; * Useful defines&n; */
macro_line|#ifdef FALSE
DECL|macro|FALSE
macro_line|#undef FALSE
macro_line|#endif
DECL|macro|FALSE
mdefine_line|#define FALSE                           (1 == 0)
macro_line|#ifdef TRUE
DECL|macro|TRUE
macro_line|#undef TRUE
macro_line|#endif
DECL|macro|TRUE
mdefine_line|#define TRUE                            (1 == 1)
macro_line|#ifndef NULL
DECL|macro|NULL
mdefine_line|#define NULL                            (void *) 0
macro_line|#endif
multiline_comment|/*&n; * Local datatypes&n; */
DECL|typedef|acpi_status
r_typedef
id|u32
id|acpi_status
suffix:semicolon
multiline_comment|/* All ACPI Exceptions */
DECL|typedef|acpi_name
r_typedef
id|u32
id|acpi_name
suffix:semicolon
multiline_comment|/* 4-byte ACPI name */
DECL|typedef|acpi_string
r_typedef
r_char
op_star
id|acpi_string
suffix:semicolon
multiline_comment|/* Null terminated ASCII string */
DECL|typedef|acpi_handle
r_typedef
r_void
op_star
id|acpi_handle
suffix:semicolon
multiline_comment|/* Actually a ptr to an Node */
r_typedef
r_struct
(brace
DECL|member|lo
id|u32
id|lo
suffix:semicolon
DECL|member|hi
id|u32
id|hi
suffix:semicolon
DECL|typedef|uint64_struct
)brace
id|uint64_struct
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|full
id|u64
id|full
suffix:semicolon
DECL|member|part
id|uint64_struct
id|part
suffix:semicolon
DECL|typedef|uint64_overlay
)brace
id|uint64_overlay
suffix:semicolon
multiline_comment|/*&n; * Acpi integer width. In ACPI version 1, integers are&n; * 32 bits.  In ACPI version 2, integers are 64 bits.&n; * Note that this pertains to the ACPI integer type only, not&n; * other integers used in the implementation of the ACPI CA&n; * subsystem.&n; */
macro_line|#ifdef ACPI_NO_INTEGER64_SUPPORT
multiline_comment|/* 32-bit integers only, no 64-bit support */
DECL|typedef|acpi_integer
r_typedef
id|u32
id|acpi_integer
suffix:semicolon
DECL|macro|ACPI_INTEGER_MAX
mdefine_line|#define ACPI_INTEGER_MAX                ACPI_UINT32_MAX
DECL|macro|ACPI_INTEGER_BIT_SIZE
mdefine_line|#define ACPI_INTEGER_BIT_SIZE           32
DECL|macro|ACPI_MAX_BCD_VALUE
mdefine_line|#define ACPI_MAX_BCD_VALUE              99999999
DECL|macro|ACPI_MAX_BCD_DIGITS
mdefine_line|#define ACPI_MAX_BCD_DIGITS             8
DECL|macro|ACPI_MAX_DECIMAL_DIGITS
mdefine_line|#define ACPI_MAX_DECIMAL_DIGITS         10
DECL|macro|ACPI_USE_NATIVE_DIVIDE
mdefine_line|#define ACPI_USE_NATIVE_DIVIDE          /* Use compiler native 32-bit divide */
macro_line|#else
multiline_comment|/* 64-bit integers */
DECL|typedef|acpi_integer
r_typedef
id|u64
id|acpi_integer
suffix:semicolon
DECL|macro|ACPI_INTEGER_MAX
mdefine_line|#define ACPI_INTEGER_MAX                ACPI_UINT64_MAX
DECL|macro|ACPI_INTEGER_BIT_SIZE
mdefine_line|#define ACPI_INTEGER_BIT_SIZE           64
DECL|macro|ACPI_MAX_BCD_VALUE
mdefine_line|#define ACPI_MAX_BCD_VALUE              9999999999999999
DECL|macro|ACPI_MAX_BCD_DIGITS
mdefine_line|#define ACPI_MAX_BCD_DIGITS             16
DECL|macro|ACPI_MAX_DECIMAL_DIGITS
mdefine_line|#define ACPI_MAX_DECIMAL_DIGITS         19
macro_line|#ifdef _IA64
DECL|macro|ACPI_USE_NATIVE_DIVIDE
mdefine_line|#define ACPI_USE_NATIVE_DIVIDE          /* Use compiler native 64-bit divide */
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Constants with special meanings&n; */
DECL|macro|ACPI_ROOT_OBJECT
mdefine_line|#define ACPI_ROOT_OBJECT                (acpi_handle) ACPI_PTR_ADD (char, NULL, ACPI_UINT32_MAX)
multiline_comment|/*&n; * Initialization sequence&n; */
DECL|macro|ACPI_FULL_INITIALIZATION
mdefine_line|#define ACPI_FULL_INITIALIZATION        0x00
DECL|macro|ACPI_NO_ADDRESS_SPACE_INIT
mdefine_line|#define ACPI_NO_ADDRESS_SPACE_INIT      0x01
DECL|macro|ACPI_NO_HARDWARE_INIT
mdefine_line|#define ACPI_NO_HARDWARE_INIT           0x02
DECL|macro|ACPI_NO_EVENT_INIT
mdefine_line|#define ACPI_NO_EVENT_INIT              0x04
DECL|macro|ACPI_NO_HANDLER_INIT
mdefine_line|#define ACPI_NO_HANDLER_INIT            0x08
DECL|macro|ACPI_NO_ACPI_ENABLE
mdefine_line|#define ACPI_NO_ACPI_ENABLE             0x10
DECL|macro|ACPI_NO_DEVICE_INIT
mdefine_line|#define ACPI_NO_DEVICE_INIT             0x20
DECL|macro|ACPI_NO_OBJECT_INIT
mdefine_line|#define ACPI_NO_OBJECT_INIT             0x40
multiline_comment|/*&n; * Initialization state&n; */
DECL|macro|ACPI_INITIALIZED_OK
mdefine_line|#define ACPI_INITIALIZED_OK             0x01
multiline_comment|/*&n; * Power state values&n; */
DECL|macro|ACPI_STATE_UNKNOWN
mdefine_line|#define ACPI_STATE_UNKNOWN              (u8) 0xFF
DECL|macro|ACPI_STATE_S0
mdefine_line|#define ACPI_STATE_S0                   (u8) 0
DECL|macro|ACPI_STATE_S1
mdefine_line|#define ACPI_STATE_S1                   (u8) 1
DECL|macro|ACPI_STATE_S2
mdefine_line|#define ACPI_STATE_S2                   (u8) 2
DECL|macro|ACPI_STATE_S3
mdefine_line|#define ACPI_STATE_S3                   (u8) 3
DECL|macro|ACPI_STATE_S4
mdefine_line|#define ACPI_STATE_S4                   (u8) 4
DECL|macro|ACPI_STATE_S5
mdefine_line|#define ACPI_STATE_S5                   (u8) 5
DECL|macro|ACPI_S_STATES_MAX
mdefine_line|#define ACPI_S_STATES_MAX               ACPI_STATE_S5
DECL|macro|ACPI_S_STATE_COUNT
mdefine_line|#define ACPI_S_STATE_COUNT              6
DECL|macro|ACPI_STATE_D0
mdefine_line|#define ACPI_STATE_D0                   (u8) 0
DECL|macro|ACPI_STATE_D1
mdefine_line|#define ACPI_STATE_D1                   (u8) 1
DECL|macro|ACPI_STATE_D2
mdefine_line|#define ACPI_STATE_D2                   (u8) 2
DECL|macro|ACPI_STATE_D3
mdefine_line|#define ACPI_STATE_D3                   (u8) 3
DECL|macro|ACPI_D_STATES_MAX
mdefine_line|#define ACPI_D_STATES_MAX               ACPI_STATE_D3
DECL|macro|ACPI_D_STATE_COUNT
mdefine_line|#define ACPI_D_STATE_COUNT              4
DECL|macro|ACPI_STATE_C0
mdefine_line|#define ACPI_STATE_C0                   (u8) 0
DECL|macro|ACPI_STATE_C1
mdefine_line|#define ACPI_STATE_C1                   (u8) 1
DECL|macro|ACPI_STATE_C2
mdefine_line|#define ACPI_STATE_C2                   (u8) 2
DECL|macro|ACPI_STATE_C3
mdefine_line|#define ACPI_STATE_C3                   (u8) 3
DECL|macro|ACPI_C_STATES_MAX
mdefine_line|#define ACPI_C_STATES_MAX               ACPI_STATE_C3
DECL|macro|ACPI_C_STATE_COUNT
mdefine_line|#define ACPI_C_STATE_COUNT              4
multiline_comment|/*&n; * Sleep type invalid value&n; */
DECL|macro|ACPI_SLEEP_TYPE_MAX
mdefine_line|#define ACPI_SLEEP_TYPE_MAX             0x7
DECL|macro|ACPI_SLEEP_TYPE_INVALID
mdefine_line|#define ACPI_SLEEP_TYPE_INVALID         0xFF
multiline_comment|/*&n; * Standard notify values&n; */
DECL|macro|ACPI_NOTIFY_BUS_CHECK
mdefine_line|#define ACPI_NOTIFY_BUS_CHECK           (u8) 0
DECL|macro|ACPI_NOTIFY_DEVICE_CHECK
mdefine_line|#define ACPI_NOTIFY_DEVICE_CHECK        (u8) 1
DECL|macro|ACPI_NOTIFY_DEVICE_WAKE
mdefine_line|#define ACPI_NOTIFY_DEVICE_WAKE         (u8) 2
DECL|macro|ACPI_NOTIFY_EJECT_REQUEST
mdefine_line|#define ACPI_NOTIFY_EJECT_REQUEST       (u8) 3
DECL|macro|ACPI_NOTIFY_DEVICE_CHECK_LIGHT
mdefine_line|#define ACPI_NOTIFY_DEVICE_CHECK_LIGHT  (u8) 4
DECL|macro|ACPI_NOTIFY_FREQUENCY_MISMATCH
mdefine_line|#define ACPI_NOTIFY_FREQUENCY_MISMATCH  (u8) 5
DECL|macro|ACPI_NOTIFY_BUS_MODE_MISMATCH
mdefine_line|#define ACPI_NOTIFY_BUS_MODE_MISMATCH   (u8) 6
DECL|macro|ACPI_NOTIFY_POWER_FAULT
mdefine_line|#define ACPI_NOTIFY_POWER_FAULT         (u8) 7
multiline_comment|/*&n; *  Table types.  These values are passed to the table related APIs&n; */
DECL|typedef|acpi_table_type
r_typedef
id|u32
id|acpi_table_type
suffix:semicolon
DECL|macro|ACPI_TABLE_RSDP
mdefine_line|#define ACPI_TABLE_RSDP                 (acpi_table_type) 0
DECL|macro|ACPI_TABLE_DSDT
mdefine_line|#define ACPI_TABLE_DSDT                 (acpi_table_type) 1
DECL|macro|ACPI_TABLE_FADT
mdefine_line|#define ACPI_TABLE_FADT                 (acpi_table_type) 2
DECL|macro|ACPI_TABLE_FACS
mdefine_line|#define ACPI_TABLE_FACS                 (acpi_table_type) 3
DECL|macro|ACPI_TABLE_PSDT
mdefine_line|#define ACPI_TABLE_PSDT                 (acpi_table_type) 4
DECL|macro|ACPI_TABLE_SSDT
mdefine_line|#define ACPI_TABLE_SSDT                 (acpi_table_type) 5
DECL|macro|ACPI_TABLE_XSDT
mdefine_line|#define ACPI_TABLE_XSDT                 (acpi_table_type) 6
DECL|macro|ACPI_TABLE_MAX
mdefine_line|#define ACPI_TABLE_MAX                  6
DECL|macro|NUM_ACPI_TABLES
mdefine_line|#define NUM_ACPI_TABLES                 (ACPI_TABLE_MAX+1)
multiline_comment|/*&n; * Types associated with names.  The first group of&n; * values correspond to the definition of the ACPI&n; * Object_type operator (See the ACPI Spec). Therefore,&n; * only add to the first group if the spec changes.&n; *&n; * Types must be kept in sync with the Acpi_ns_properties&n; * and Acpi_ns_type_names arrays&n; */
DECL|typedef|acpi_object_type
r_typedef
id|u32
id|acpi_object_type
suffix:semicolon
DECL|macro|ACPI_TYPE_ANY
mdefine_line|#define ACPI_TYPE_ANY                   0x00
DECL|macro|ACPI_TYPE_INTEGER
mdefine_line|#define ACPI_TYPE_INTEGER               0x01  /* Byte/Word/Dword/Zero/One/Ones */
DECL|macro|ACPI_TYPE_STRING
mdefine_line|#define ACPI_TYPE_STRING                0x02
DECL|macro|ACPI_TYPE_BUFFER
mdefine_line|#define ACPI_TYPE_BUFFER                0x03
DECL|macro|ACPI_TYPE_PACKAGE
mdefine_line|#define ACPI_TYPE_PACKAGE               0x04  /* Byte_const, multiple Data_term/Constant/Super_name */
DECL|macro|ACPI_TYPE_FIELD_UNIT
mdefine_line|#define ACPI_TYPE_FIELD_UNIT            0x05
DECL|macro|ACPI_TYPE_DEVICE
mdefine_line|#define ACPI_TYPE_DEVICE                0x06  /* Name, multiple Node */
DECL|macro|ACPI_TYPE_EVENT
mdefine_line|#define ACPI_TYPE_EVENT                 0x07
DECL|macro|ACPI_TYPE_METHOD
mdefine_line|#define ACPI_TYPE_METHOD                0x08  /* Name, Byte_const, multiple Code */
DECL|macro|ACPI_TYPE_MUTEX
mdefine_line|#define ACPI_TYPE_MUTEX                 0x09
DECL|macro|ACPI_TYPE_REGION
mdefine_line|#define ACPI_TYPE_REGION                0x0A
DECL|macro|ACPI_TYPE_POWER
mdefine_line|#define ACPI_TYPE_POWER                 0x0B  /* Name,Byte_const,Word_const,multi Node */
DECL|macro|ACPI_TYPE_PROCESSOR
mdefine_line|#define ACPI_TYPE_PROCESSOR             0x0C  /* Name,Byte_const,DWord_const,Byte_const,multi Nm_o */
DECL|macro|ACPI_TYPE_THERMAL
mdefine_line|#define ACPI_TYPE_THERMAL               0x0D  /* Name, multiple Node */
DECL|macro|ACPI_TYPE_BUFFER_FIELD
mdefine_line|#define ACPI_TYPE_BUFFER_FIELD          0x0E
DECL|macro|ACPI_TYPE_DDB_HANDLE
mdefine_line|#define ACPI_TYPE_DDB_HANDLE            0x0F
DECL|macro|ACPI_TYPE_DEBUG_OBJECT
mdefine_line|#define ACPI_TYPE_DEBUG_OBJECT          0x10
DECL|macro|ACPI_TYPE_MAX
mdefine_line|#define ACPI_TYPE_MAX                   0x10
multiline_comment|/*&n; * This section contains object types that do not relate to the ACPI Object_type operator.&n; * They are used for various internal purposes only.  If new predefined ACPI_TYPEs are&n; * added (via the ACPI specification), these internal types must move upwards.&n; * Also, values exceeding the largest official ACPI Object_type must not overlap with&n; * defined AML opcodes.&n; */
DECL|macro|INTERNAL_TYPE_BEGIN
mdefine_line|#define INTERNAL_TYPE_BEGIN             0x11
DECL|macro|INTERNAL_TYPE_REGION_FIELD
mdefine_line|#define INTERNAL_TYPE_REGION_FIELD      0x11
DECL|macro|INTERNAL_TYPE_BANK_FIELD
mdefine_line|#define INTERNAL_TYPE_BANK_FIELD        0x12
DECL|macro|INTERNAL_TYPE_INDEX_FIELD
mdefine_line|#define INTERNAL_TYPE_INDEX_FIELD       0x13
DECL|macro|INTERNAL_TYPE_REFERENCE
mdefine_line|#define INTERNAL_TYPE_REFERENCE         0x14  /* Arg#, Local#, Name, Debug; used only in descriptors */
DECL|macro|INTERNAL_TYPE_ALIAS
mdefine_line|#define INTERNAL_TYPE_ALIAS             0x15
DECL|macro|INTERNAL_TYPE_NOTIFY
mdefine_line|#define INTERNAL_TYPE_NOTIFY            0x16
DECL|macro|INTERNAL_TYPE_ADDRESS_HANDLER
mdefine_line|#define INTERNAL_TYPE_ADDRESS_HANDLER   0x17
DECL|macro|INTERNAL_TYPE_RESOURCE
mdefine_line|#define INTERNAL_TYPE_RESOURCE          0x18
DECL|macro|INTERNAL_TYPE_RESOURCE_FIELD
mdefine_line|#define INTERNAL_TYPE_RESOURCE_FIELD    0x19
DECL|macro|INTERNAL_TYPE_NODE_MAX
mdefine_line|#define INTERNAL_TYPE_NODE_MAX          0x19
multiline_comment|/* These are pseudo-types because there are never any namespace nodes with these types */
DECL|macro|INTERNAL_TYPE_FIELD_DEFN
mdefine_line|#define INTERNAL_TYPE_FIELD_DEFN        0x1A  /* Name, Byte_const, multiple Field_element */
DECL|macro|INTERNAL_TYPE_BANK_FIELD_DEFN
mdefine_line|#define INTERNAL_TYPE_BANK_FIELD_DEFN   0x1B  /* 2 Name,DWord_const,Byte_const,multi Field_element */
DECL|macro|INTERNAL_TYPE_INDEX_FIELD_DEFN
mdefine_line|#define INTERNAL_TYPE_INDEX_FIELD_DEFN  0x1C  /* 2 Name, Byte_const, multiple Field_element */
DECL|macro|INTERNAL_TYPE_IF
mdefine_line|#define INTERNAL_TYPE_IF                0x1D
DECL|macro|INTERNAL_TYPE_ELSE
mdefine_line|#define INTERNAL_TYPE_ELSE              0x1E
DECL|macro|INTERNAL_TYPE_WHILE
mdefine_line|#define INTERNAL_TYPE_WHILE             0x1F
DECL|macro|INTERNAL_TYPE_SCOPE
mdefine_line|#define INTERNAL_TYPE_SCOPE             0x20  /* Name, multiple Node */
DECL|macro|INTERNAL_TYPE_DEF_ANY
mdefine_line|#define INTERNAL_TYPE_DEF_ANY           0x21  /* type is Any, suppress search of enclosing scopes */
DECL|macro|INTERNAL_TYPE_EXTRA
mdefine_line|#define INTERNAL_TYPE_EXTRA             0x22
DECL|macro|INTERNAL_TYPE_DATA
mdefine_line|#define INTERNAL_TYPE_DATA              0x23
DECL|macro|INTERNAL_TYPE_MAX
mdefine_line|#define INTERNAL_TYPE_MAX               0x23
DECL|macro|INTERNAL_TYPE_INVALID
mdefine_line|#define INTERNAL_TYPE_INVALID           0x24
DECL|macro|ACPI_TYPE_NOT_FOUND
mdefine_line|#define ACPI_TYPE_NOT_FOUND             0xFF
multiline_comment|/*&n; * Bitmapped ACPI types&n; * Used internally only&n; */
DECL|macro|ACPI_BTYPE_ANY
mdefine_line|#define ACPI_BTYPE_ANY                  0x00000000
DECL|macro|ACPI_BTYPE_INTEGER
mdefine_line|#define ACPI_BTYPE_INTEGER              0x00000001
DECL|macro|ACPI_BTYPE_STRING
mdefine_line|#define ACPI_BTYPE_STRING               0x00000002
DECL|macro|ACPI_BTYPE_BUFFER
mdefine_line|#define ACPI_BTYPE_BUFFER               0x00000004
DECL|macro|ACPI_BTYPE_PACKAGE
mdefine_line|#define ACPI_BTYPE_PACKAGE              0x00000008
DECL|macro|ACPI_BTYPE_FIELD_UNIT
mdefine_line|#define ACPI_BTYPE_FIELD_UNIT           0x00000010
DECL|macro|ACPI_BTYPE_DEVICE
mdefine_line|#define ACPI_BTYPE_DEVICE               0x00000020
DECL|macro|ACPI_BTYPE_EVENT
mdefine_line|#define ACPI_BTYPE_EVENT                0x00000040
DECL|macro|ACPI_BTYPE_METHOD
mdefine_line|#define ACPI_BTYPE_METHOD               0x00000080
DECL|macro|ACPI_BTYPE_MUTEX
mdefine_line|#define ACPI_BTYPE_MUTEX                0x00000100
DECL|macro|ACPI_BTYPE_REGION
mdefine_line|#define ACPI_BTYPE_REGION               0x00000200
DECL|macro|ACPI_BTYPE_POWER
mdefine_line|#define ACPI_BTYPE_POWER                0x00000400
DECL|macro|ACPI_BTYPE_PROCESSOR
mdefine_line|#define ACPI_BTYPE_PROCESSOR            0x00000800
DECL|macro|ACPI_BTYPE_THERMAL
mdefine_line|#define ACPI_BTYPE_THERMAL              0x00001000
DECL|macro|ACPI_BTYPE_BUFFER_FIELD
mdefine_line|#define ACPI_BTYPE_BUFFER_FIELD         0x00002000
DECL|macro|ACPI_BTYPE_DDB_HANDLE
mdefine_line|#define ACPI_BTYPE_DDB_HANDLE           0x00004000
DECL|macro|ACPI_BTYPE_DEBUG_OBJECT
mdefine_line|#define ACPI_BTYPE_DEBUG_OBJECT         0x00008000
DECL|macro|ACPI_BTYPE_REFERENCE
mdefine_line|#define ACPI_BTYPE_REFERENCE            0x00010000
DECL|macro|ACPI_BTYPE_RESOURCE
mdefine_line|#define ACPI_BTYPE_RESOURCE             0x00020000
DECL|macro|ACPI_BTYPE_COMPUTE_DATA
mdefine_line|#define ACPI_BTYPE_COMPUTE_DATA         (ACPI_BTYPE_INTEGER | ACPI_BTYPE_STRING | ACPI_BTYPE_BUFFER)
DECL|macro|ACPI_BTYPE_DATA
mdefine_line|#define ACPI_BTYPE_DATA                 (ACPI_BTYPE_COMPUTE_DATA  | ACPI_BTYPE_PACKAGE)
DECL|macro|ACPI_BTYPE_DATA_REFERENCE
mdefine_line|#define ACPI_BTYPE_DATA_REFERENCE       (ACPI_BTYPE_DATA | ACPI_BTYPE_REFERENCE | ACPI_BTYPE_DDB_HANDLE)
DECL|macro|ACPI_BTYPE_DEVICE_OBJECTS
mdefine_line|#define ACPI_BTYPE_DEVICE_OBJECTS       (ACPI_BTYPE_DEVICE | ACPI_BTYPE_THERMAL | ACPI_BTYPE_PROCESSOR)
DECL|macro|ACPI_BTYPE_OBJECTS_AND_REFS
mdefine_line|#define ACPI_BTYPE_OBJECTS_AND_REFS     0x0001FFFF  /* ARG or LOCAL */
DECL|macro|ACPI_BTYPE_ALL_OBJECTS
mdefine_line|#define ACPI_BTYPE_ALL_OBJECTS          0x0000FFFF
multiline_comment|/*&n; * All I/O&n; */
DECL|macro|ACPI_READ
mdefine_line|#define ACPI_READ                       0
DECL|macro|ACPI_WRITE
mdefine_line|#define ACPI_WRITE                      1
multiline_comment|/*&n; * Acpi_event Types: Fixed &amp; General Purpose&n; */
DECL|typedef|acpi_event_type
r_typedef
id|u32
id|acpi_event_type
suffix:semicolon
DECL|macro|ACPI_EVENT_FIXED
mdefine_line|#define ACPI_EVENT_FIXED                0
DECL|macro|ACPI_EVENT_GPE
mdefine_line|#define ACPI_EVENT_GPE                  1
multiline_comment|/*&n; * Fixed events&n; */
DECL|macro|ACPI_EVENT_PMTIMER
mdefine_line|#define ACPI_EVENT_PMTIMER              0
DECL|macro|ACPI_EVENT_GLOBAL
mdefine_line|#define ACPI_EVENT_GLOBAL               1
DECL|macro|ACPI_EVENT_POWER_BUTTON
mdefine_line|#define ACPI_EVENT_POWER_BUTTON         2
DECL|macro|ACPI_EVENT_SLEEP_BUTTON
mdefine_line|#define ACPI_EVENT_SLEEP_BUTTON         3
DECL|macro|ACPI_EVENT_RTC
mdefine_line|#define ACPI_EVENT_RTC                  4
DECL|macro|ACPI_EVENT_MAX
mdefine_line|#define ACPI_EVENT_MAX                  4
DECL|macro|ACPI_NUM_FIXED_EVENTS
mdefine_line|#define ACPI_NUM_FIXED_EVENTS           ACPI_EVENT_MAX + 1
DECL|macro|ACPI_GPE_INVALID
mdefine_line|#define ACPI_GPE_INVALID                0xFF
DECL|macro|ACPI_GPE_MAX
mdefine_line|#define ACPI_GPE_MAX                    0xFF
DECL|macro|ACPI_NUM_GPE
mdefine_line|#define ACPI_NUM_GPE                    256
DECL|macro|ACPI_EVENT_LEVEL_TRIGGERED
mdefine_line|#define ACPI_EVENT_LEVEL_TRIGGERED      1
DECL|macro|ACPI_EVENT_EDGE_TRIGGERED
mdefine_line|#define ACPI_EVENT_EDGE_TRIGGERED       2
multiline_comment|/*&n; * GPEs&n; */
DECL|macro|ACPI_EVENT_WAKE_ENABLE
mdefine_line|#define ACPI_EVENT_WAKE_ENABLE          0x1
DECL|macro|ACPI_EVENT_WAKE_DISABLE
mdefine_line|#define ACPI_EVENT_WAKE_DISABLE         0x1
multiline_comment|/*&n; * Acpi_event Status:&n; * -------------&n; * The encoding of acpi_event_status is illustrated below.&n; * Note that a set bit (1) indicates the property is TRUE&n; * (e.g. if bit 0 is set then the event is enabled).&n; * +-------------+-+-+-+&n; * |   Bits 31:3 |2|1|0|&n; * +-------------+-+-+-+&n; *          |     | | |&n; *          |     | | +- Enabled?&n; *          |     | +--- Enabled for wake?&n; *          |     +----- Set?&n; *          +----------- &lt;Reserved&gt;&n; */
DECL|typedef|acpi_event_status
r_typedef
id|u32
id|acpi_event_status
suffix:semicolon
DECL|macro|ACPI_EVENT_FLAG_DISABLED
mdefine_line|#define ACPI_EVENT_FLAG_DISABLED        (acpi_event_status) 0x00
DECL|macro|ACPI_EVENT_FLAG_ENABLED
mdefine_line|#define ACPI_EVENT_FLAG_ENABLED         (acpi_event_status) 0x01
DECL|macro|ACPI_EVENT_FLAG_WAKE_ENABLED
mdefine_line|#define ACPI_EVENT_FLAG_WAKE_ENABLED    (acpi_event_status) 0x02
DECL|macro|ACPI_EVENT_FLAG_SET
mdefine_line|#define ACPI_EVENT_FLAG_SET             (acpi_event_status) 0x04
multiline_comment|/* Notify types */
DECL|macro|ACPI_SYSTEM_NOTIFY
mdefine_line|#define ACPI_SYSTEM_NOTIFY              0
DECL|macro|ACPI_DEVICE_NOTIFY
mdefine_line|#define ACPI_DEVICE_NOTIFY              1
DECL|macro|ACPI_MAX_NOTIFY_HANDLER_TYPE
mdefine_line|#define ACPI_MAX_NOTIFY_HANDLER_TYPE    1
DECL|macro|ACPI_MAX_SYS_NOTIFY
mdefine_line|#define ACPI_MAX_SYS_NOTIFY                  0x7f
multiline_comment|/* Address Space (Operation Region) Types */
DECL|typedef|ACPI_ADR_SPACE_TYPE
r_typedef
id|u8
id|ACPI_ADR_SPACE_TYPE
suffix:semicolon
DECL|macro|ACPI_ADR_SPACE_SYSTEM_MEMORY
mdefine_line|#define ACPI_ADR_SPACE_SYSTEM_MEMORY    (ACPI_ADR_SPACE_TYPE) 0
DECL|macro|ACPI_ADR_SPACE_SYSTEM_IO
mdefine_line|#define ACPI_ADR_SPACE_SYSTEM_IO        (ACPI_ADR_SPACE_TYPE) 1
DECL|macro|ACPI_ADR_SPACE_PCI_CONFIG
mdefine_line|#define ACPI_ADR_SPACE_PCI_CONFIG       (ACPI_ADR_SPACE_TYPE) 2
DECL|macro|ACPI_ADR_SPACE_EC
mdefine_line|#define ACPI_ADR_SPACE_EC               (ACPI_ADR_SPACE_TYPE) 3
DECL|macro|ACPI_ADR_SPACE_SMBUS
mdefine_line|#define ACPI_ADR_SPACE_SMBUS            (ACPI_ADR_SPACE_TYPE) 4
DECL|macro|ACPI_ADR_SPACE_CMOS
mdefine_line|#define ACPI_ADR_SPACE_CMOS             (ACPI_ADR_SPACE_TYPE) 5
DECL|macro|ACPI_ADR_SPACE_PCI_BAR_TARGET
mdefine_line|#define ACPI_ADR_SPACE_PCI_BAR_TARGET   (ACPI_ADR_SPACE_TYPE) 6
DECL|macro|ACPI_ADR_SPACE_DATA_TABLE
mdefine_line|#define ACPI_ADR_SPACE_DATA_TABLE       (ACPI_ADR_SPACE_TYPE) 7
multiline_comment|/*&n; * External ACPI object definition&n; */
DECL|union|acpi_obj
r_typedef
r_union
id|acpi_obj
(brace
DECL|member|type
id|acpi_object_type
id|type
suffix:semicolon
multiline_comment|/* See definition of Acpi_ns_type for values */
r_struct
(brace
DECL|member|type
id|acpi_object_type
id|type
suffix:semicolon
DECL|member|value
id|acpi_integer
id|value
suffix:semicolon
multiline_comment|/* The actual number */
DECL|member|integer
)brace
id|integer
suffix:semicolon
r_struct
(brace
DECL|member|type
id|acpi_object_type
id|type
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* # of bytes in string, excluding trailing null */
DECL|member|pointer
id|NATIVE_CHAR
op_star
id|pointer
suffix:semicolon
multiline_comment|/* points to the string value */
DECL|member|string
)brace
id|string
suffix:semicolon
r_struct
(brace
DECL|member|type
id|acpi_object_type
id|type
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
multiline_comment|/* # of bytes in buffer */
DECL|member|pointer
id|u8
op_star
id|pointer
suffix:semicolon
multiline_comment|/* points to the buffer */
DECL|member|buffer
)brace
id|buffer
suffix:semicolon
r_struct
(brace
DECL|member|type
id|acpi_object_type
id|type
suffix:semicolon
DECL|member|fill1
id|u32
id|fill1
suffix:semicolon
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
multiline_comment|/* object reference */
DECL|member|reference
)brace
id|reference
suffix:semicolon
r_struct
(brace
DECL|member|type
id|acpi_object_type
id|type
suffix:semicolon
DECL|member|count
id|u32
id|count
suffix:semicolon
multiline_comment|/* # of elements in package */
DECL|member|elements
r_union
id|acpi_obj
op_star
id|elements
suffix:semicolon
multiline_comment|/* Pointer to an array of ACPI_OBJECTs */
DECL|member|package
)brace
id|package
suffix:semicolon
r_struct
(brace
DECL|member|type
id|acpi_object_type
id|type
suffix:semicolon
DECL|member|proc_id
id|u32
id|proc_id
suffix:semicolon
DECL|member|pblk_address
id|ACPI_IO_ADDRESS
id|pblk_address
suffix:semicolon
DECL|member|pblk_length
id|u32
id|pblk_length
suffix:semicolon
DECL|member|processor
)brace
id|processor
suffix:semicolon
r_struct
(brace
DECL|member|type
id|acpi_object_type
id|type
suffix:semicolon
DECL|member|system_level
id|u32
id|system_level
suffix:semicolon
DECL|member|resource_order
id|u32
id|resource_order
suffix:semicolon
DECL|member|power_resource
)brace
id|power_resource
suffix:semicolon
DECL|typedef|acpi_object
)brace
id|acpi_object
suffix:semicolon
multiline_comment|/*&n; * List of objects, used as a parameter list for control method evaluation&n; */
DECL|struct|acpi_obj_list
r_typedef
r_struct
id|acpi_obj_list
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|pointer
id|acpi_object
op_star
id|pointer
suffix:semicolon
DECL|typedef|acpi_object_list
)brace
id|acpi_object_list
suffix:semicolon
multiline_comment|/*&n; * Miscellaneous common Data Structures used by the interfaces&n; */
DECL|macro|ACPI_NO_BUFFER
mdefine_line|#define ACPI_NO_BUFFER              0
DECL|macro|ACPI_ALLOCATE_BUFFER
mdefine_line|#define ACPI_ALLOCATE_BUFFER        (ACPI_SIZE) (-1)
DECL|macro|ACPI_ALLOCATE_LOCAL_BUFFER
mdefine_line|#define ACPI_ALLOCATE_LOCAL_BUFFER  (ACPI_SIZE) (-2)
r_typedef
r_struct
(brace
DECL|member|length
id|ACPI_SIZE
id|length
suffix:semicolon
multiline_comment|/* Length in bytes of the buffer */
DECL|member|pointer
r_void
op_star
id|pointer
suffix:semicolon
multiline_comment|/* pointer to buffer */
DECL|typedef|acpi_buffer
)brace
id|acpi_buffer
suffix:semicolon
multiline_comment|/*&n; * Name_type for Acpi_get_name&n; */
DECL|macro|ACPI_FULL_PATHNAME
mdefine_line|#define ACPI_FULL_PATHNAME              0
DECL|macro|ACPI_SINGLE_NAME
mdefine_line|#define ACPI_SINGLE_NAME                1
DECL|macro|ACPI_NAME_TYPE_MAX
mdefine_line|#define ACPI_NAME_TYPE_MAX              1
multiline_comment|/*&n; * Structure and flags for Acpi_get_system_info&n; */
DECL|macro|ACPI_SYS_MODE_UNKNOWN
mdefine_line|#define ACPI_SYS_MODE_UNKNOWN           0x0000
DECL|macro|ACPI_SYS_MODE_ACPI
mdefine_line|#define ACPI_SYS_MODE_ACPI              0x0001
DECL|macro|ACPI_SYS_MODE_LEGACY
mdefine_line|#define ACPI_SYS_MODE_LEGACY            0x0002
DECL|macro|ACPI_SYS_MODES_MASK
mdefine_line|#define ACPI_SYS_MODES_MASK             0x0003
multiline_comment|/*&n; * ACPI Table Info.  One per ACPI table _type_&n; */
DECL|struct|acpi_table_info
r_typedef
r_struct
id|acpi_table_info
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|typedef|acpi_table_info
)brace
id|acpi_table_info
suffix:semicolon
multiline_comment|/*&n; * System info returned by Acpi_get_system_info()&n; */
DECL|struct|_acpi_sys_info
r_typedef
r_struct
id|_acpi_sys_info
(brace
DECL|member|acpi_ca_version
id|u32
id|acpi_ca_version
suffix:semicolon
DECL|member|flags
id|u32
id|flags
suffix:semicolon
DECL|member|timer_resolution
id|u32
id|timer_resolution
suffix:semicolon
DECL|member|reserved1
id|u32
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u32
id|reserved2
suffix:semicolon
DECL|member|debug_level
id|u32
id|debug_level
suffix:semicolon
DECL|member|debug_layer
id|u32
id|debug_layer
suffix:semicolon
DECL|member|num_table_types
id|u32
id|num_table_types
suffix:semicolon
DECL|member|table_info
id|acpi_table_info
id|table_info
(braket
id|NUM_ACPI_TABLES
)braket
suffix:semicolon
DECL|typedef|acpi_system_info
)brace
id|acpi_system_info
suffix:semicolon
multiline_comment|/*&n; * Various handlers and callback procedures&n; */
r_typedef
DECL|typedef|acpi_event_handler
id|u32
(paren
op_star
id|acpi_event_handler
)paren
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
r_typedef
DECL|typedef|acpi_gpe_handler
r_void
(paren
op_star
id|acpi_gpe_handler
)paren
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
r_typedef
DECL|typedef|acpi_notify_handler
r_void
(paren
op_star
id|acpi_notify_handler
)paren
(paren
id|acpi_handle
id|device
comma
id|u32
id|value
comma
r_void
op_star
id|context
)paren
suffix:semicolon
r_typedef
DECL|typedef|ACPI_OBJECT_HANDLER
r_void
(paren
op_star
id|ACPI_OBJECT_HANDLER
)paren
(paren
id|acpi_handle
id|object
comma
id|u32
id|function
comma
r_void
op_star
id|data
)paren
suffix:semicolon
multiline_comment|/* Address Spaces (Operation Regions */
r_typedef
DECL|typedef|acpi_adr_space_handler
id|acpi_status
(paren
op_star
id|acpi_adr_space_handler
)paren
(paren
id|u32
id|function
comma
id|ACPI_PHYSICAL_ADDRESS
id|address
comma
id|u32
id|bit_width
comma
id|acpi_integer
op_star
id|value
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
id|region_context
)paren
suffix:semicolon
DECL|macro|ACPI_DEFAULT_HANDLER
mdefine_line|#define ACPI_DEFAULT_HANDLER        ((acpi_adr_space_handler) NULL)
r_typedef
DECL|typedef|acpi_adr_space_setup
id|acpi_status
(paren
op_star
id|acpi_adr_space_setup
)paren
(paren
id|acpi_handle
id|region_handle
comma
id|u32
id|function
comma
r_void
op_star
id|handler_context
comma
r_void
op_star
op_star
id|region_context
)paren
suffix:semicolon
DECL|macro|ACPI_REGION_ACTIVATE
mdefine_line|#define ACPI_REGION_ACTIVATE    0
DECL|macro|ACPI_REGION_DEACTIVATE
mdefine_line|#define ACPI_REGION_DEACTIVATE  1
r_typedef
DECL|typedef|acpi_walk_callback
id|acpi_status
(paren
op_star
id|acpi_walk_callback
)paren
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
multiline_comment|/* Interrupt handler return values */
DECL|macro|ACPI_INTERRUPT_NOT_HANDLED
mdefine_line|#define ACPI_INTERRUPT_NOT_HANDLED      0x00
DECL|macro|ACPI_INTERRUPT_HANDLED
mdefine_line|#define ACPI_INTERRUPT_HANDLED          0x01
multiline_comment|/* Structure and flags for Acpi_get_device_info */
DECL|macro|ACPI_VALID_HID
mdefine_line|#define ACPI_VALID_HID                  0x1
DECL|macro|ACPI_VALID_UID
mdefine_line|#define ACPI_VALID_UID                  0x2
DECL|macro|ACPI_VALID_ADR
mdefine_line|#define ACPI_VALID_ADR                  0x4
DECL|macro|ACPI_VALID_STA
mdefine_line|#define ACPI_VALID_STA                  0x8
DECL|macro|ACPI_COMMON_OBJ_INFO
mdefine_line|#define ACPI_COMMON_OBJ_INFO &bslash;&n;&t;acpi_object_type            type;           /* ACPI object type */ &bslash;&n;&t;acpi_name                   name            /* ACPI object Name */
r_typedef
r_struct
(brace
DECL|member|ACPI_COMMON_OBJ_INFO
id|ACPI_COMMON_OBJ_INFO
suffix:semicolon
DECL|typedef|acpi_obj_info_header
)brace
id|acpi_obj_info_header
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|ACPI_COMMON_OBJ_INFO
id|ACPI_COMMON_OBJ_INFO
suffix:semicolon
DECL|member|valid
id|u32
id|valid
suffix:semicolon
multiline_comment|/*  Are the next bits legit? */
DECL|member|hardware_id
id|NATIVE_CHAR
id|hardware_id
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/*  _HID value if any */
DECL|member|unique_id
id|NATIVE_CHAR
id|unique_id
(braket
l_int|9
)braket
suffix:semicolon
multiline_comment|/*  _UID value if any */
DECL|member|address
id|acpi_integer
id|address
suffix:semicolon
multiline_comment|/*  _ADR value if any */
DECL|member|current_status
id|u32
id|current_status
suffix:semicolon
multiline_comment|/*  _STA value */
DECL|typedef|acpi_device_info
)brace
id|acpi_device_info
suffix:semicolon
multiline_comment|/* Context structs for address space handlers */
r_typedef
r_struct
(brace
DECL|member|segment
id|u16
id|segment
suffix:semicolon
DECL|member|bus
id|u16
id|bus
suffix:semicolon
DECL|member|device
id|u16
id|device
suffix:semicolon
DECL|member|function
id|u16
id|function
suffix:semicolon
DECL|typedef|acpi_pci_id
)brace
id|acpi_pci_id
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|address
id|ACPI_PHYSICAL_ADDRESS
id|address
suffix:semicolon
DECL|member|mapped_physical_address
id|ACPI_PHYSICAL_ADDRESS
id|mapped_physical_address
suffix:semicolon
DECL|member|mapped_logical_address
id|u8
op_star
id|mapped_logical_address
suffix:semicolon
DECL|member|mapped_length
id|u32
id|mapped_length
suffix:semicolon
DECL|typedef|acpi_mem_space_context
)brace
id|acpi_mem_space_context
suffix:semicolon
multiline_comment|/* Sleep states */
DECL|macro|ACPI_NUM_SLEEP_STATES
mdefine_line|#define ACPI_NUM_SLEEP_STATES           7
multiline_comment|/*&n; * Definitions for Resource Attributes&n; */
multiline_comment|/*&n; *  Memory Attributes&n; */
DECL|macro|ACPI_READ_ONLY_MEMORY
mdefine_line|#define ACPI_READ_ONLY_MEMORY           (u8) 0x00
DECL|macro|ACPI_READ_WRITE_MEMORY
mdefine_line|#define ACPI_READ_WRITE_MEMORY          (u8) 0x01
DECL|macro|ACPI_NON_CACHEABLE_MEMORY
mdefine_line|#define ACPI_NON_CACHEABLE_MEMORY       (u8) 0x00
DECL|macro|ACPI_CACHABLE_MEMORY
mdefine_line|#define ACPI_CACHABLE_MEMORY            (u8) 0x01
DECL|macro|ACPI_WRITE_COMBINING_MEMORY
mdefine_line|#define ACPI_WRITE_COMBINING_MEMORY     (u8) 0x02
DECL|macro|ACPI_PREFETCHABLE_MEMORY
mdefine_line|#define ACPI_PREFETCHABLE_MEMORY        (u8) 0x03
multiline_comment|/*&n; *  IO Attributes&n; *  The ISA IO ranges are:     n000-n0_fFh, n400-n4_fFh, n800-n8_fFh, n_c00-n_cFFh.&n; *  The non-ISA IO ranges are: n100-n3_fFh, n500-n7_fFh, n900-n_bFFh, n_cD0-n_fFFh.&n; */
DECL|macro|ACPI_NON_ISA_ONLY_RANGES
mdefine_line|#define ACPI_NON_ISA_ONLY_RANGES        (u8) 0x01
DECL|macro|ACPI_ISA_ONLY_RANGES
mdefine_line|#define ACPI_ISA_ONLY_RANGES            (u8) 0x02
DECL|macro|ACPI_ENTIRE_RANGE
mdefine_line|#define ACPI_ENTIRE_RANGE               (ACPI_NON_ISA_ONLY_RANGES | ACPI_ISA_ONLY_RANGES)
multiline_comment|/*&n; *  IO Port Descriptor Decode&n; */
DECL|macro|ACPI_DECODE_10
mdefine_line|#define ACPI_DECODE_10                  (u8) 0x00    /* 10-bit IO address decode */
DECL|macro|ACPI_DECODE_16
mdefine_line|#define ACPI_DECODE_16                  (u8) 0x01    /* 16-bit IO address decode */
multiline_comment|/*&n; *  IRQ Attributes&n; */
DECL|macro|ACPI_EDGE_SENSITIVE
mdefine_line|#define ACPI_EDGE_SENSITIVE             (u8) 0x00
DECL|macro|ACPI_LEVEL_SENSITIVE
mdefine_line|#define ACPI_LEVEL_SENSITIVE            (u8) 0x01
DECL|macro|ACPI_ACTIVE_HIGH
mdefine_line|#define ACPI_ACTIVE_HIGH                (u8) 0x00
DECL|macro|ACPI_ACTIVE_LOW
mdefine_line|#define ACPI_ACTIVE_LOW                 (u8) 0x01
DECL|macro|ACPI_EXCLUSIVE
mdefine_line|#define ACPI_EXCLUSIVE                  (u8) 0x00
DECL|macro|ACPI_SHARED
mdefine_line|#define ACPI_SHARED                     (u8) 0x01
multiline_comment|/*&n; *  DMA Attributes&n; */
DECL|macro|ACPI_COMPATIBILITY
mdefine_line|#define ACPI_COMPATIBILITY              (u8) 0x00
DECL|macro|ACPI_TYPE_A
mdefine_line|#define ACPI_TYPE_A                     (u8) 0x01
DECL|macro|ACPI_TYPE_B
mdefine_line|#define ACPI_TYPE_B                     (u8) 0x02
DECL|macro|ACPI_TYPE_F
mdefine_line|#define ACPI_TYPE_F                     (u8) 0x03
DECL|macro|ACPI_NOT_BUS_MASTER
mdefine_line|#define ACPI_NOT_BUS_MASTER             (u8) 0x00
DECL|macro|ACPI_BUS_MASTER
mdefine_line|#define ACPI_BUS_MASTER                 (u8) 0x01
DECL|macro|ACPI_TRANSFER_8
mdefine_line|#define ACPI_TRANSFER_8                 (u8) 0x00
DECL|macro|ACPI_TRANSFER_8_16
mdefine_line|#define ACPI_TRANSFER_8_16              (u8) 0x01
DECL|macro|ACPI_TRANSFER_16
mdefine_line|#define ACPI_TRANSFER_16                (u8) 0x02
multiline_comment|/*&n; * Start Dependent Functions Priority definitions&n; */
DECL|macro|ACPI_GOOD_CONFIGURATION
mdefine_line|#define ACPI_GOOD_CONFIGURATION         (u8) 0x00
DECL|macro|ACPI_ACCEPTABLE_CONFIGURATION
mdefine_line|#define ACPI_ACCEPTABLE_CONFIGURATION   (u8) 0x01
DECL|macro|ACPI_SUB_OPTIMAL_CONFIGURATION
mdefine_line|#define ACPI_SUB_OPTIMAL_CONFIGURATION  (u8) 0x02
multiline_comment|/*&n; *  16, 32 and 64-bit Address Descriptor resource types&n; */
DECL|macro|ACPI_MEMORY_RANGE
mdefine_line|#define ACPI_MEMORY_RANGE               (u8) 0x00
DECL|macro|ACPI_IO_RANGE
mdefine_line|#define ACPI_IO_RANGE                   (u8) 0x01
DECL|macro|ACPI_BUS_NUMBER_RANGE
mdefine_line|#define ACPI_BUS_NUMBER_RANGE           (u8) 0x02
DECL|macro|ACPI_ADDRESS_NOT_FIXED
mdefine_line|#define ACPI_ADDRESS_NOT_FIXED          (u8) 0x00
DECL|macro|ACPI_ADDRESS_FIXED
mdefine_line|#define ACPI_ADDRESS_FIXED              (u8) 0x01
DECL|macro|ACPI_POS_DECODE
mdefine_line|#define ACPI_POS_DECODE                 (u8) 0x00
DECL|macro|ACPI_SUB_DECODE
mdefine_line|#define ACPI_SUB_DECODE                 (u8) 0x01
DECL|macro|ACPI_PRODUCER
mdefine_line|#define ACPI_PRODUCER                   (u8) 0x00
DECL|macro|ACPI_CONSUMER
mdefine_line|#define ACPI_CONSUMER                   (u8) 0x01
multiline_comment|/*&n; *  Structures used to describe device resources&n; */
r_typedef
r_struct
(brace
DECL|member|edge_level
id|u32
id|edge_level
suffix:semicolon
DECL|member|active_high_low
id|u32
id|active_high_low
suffix:semicolon
DECL|member|shared_exclusive
id|u32
id|shared_exclusive
suffix:semicolon
DECL|member|number_of_interrupts
id|u32
id|number_of_interrupts
suffix:semicolon
DECL|member|interrupts
id|u32
id|interrupts
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|acpi_resource_irq
)brace
id|acpi_resource_irq
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|type
id|u32
id|type
suffix:semicolon
DECL|member|bus_master
id|u32
id|bus_master
suffix:semicolon
DECL|member|transfer
id|u32
id|transfer
suffix:semicolon
DECL|member|number_of_channels
id|u32
id|number_of_channels
suffix:semicolon
DECL|member|channels
id|u32
id|channels
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|acpi_resource_dma
)brace
id|acpi_resource_dma
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|compatibility_priority
id|u32
id|compatibility_priority
suffix:semicolon
DECL|member|performance_robustness
id|u32
id|performance_robustness
suffix:semicolon
DECL|typedef|acpi_resource_start_dpf
)brace
id|acpi_resource_start_dpf
suffix:semicolon
multiline_comment|/*&n; * END_DEPENDENT_FUNCTIONS_RESOURCE struct is not&n; *  needed because it has no fields&n; */
r_typedef
r_struct
(brace
DECL|member|io_decode
id|u32
id|io_decode
suffix:semicolon
DECL|member|min_base_address
id|u32
id|min_base_address
suffix:semicolon
DECL|member|max_base_address
id|u32
id|max_base_address
suffix:semicolon
DECL|member|alignment
id|u32
id|alignment
suffix:semicolon
DECL|member|range_length
id|u32
id|range_length
suffix:semicolon
DECL|typedef|acpi_resource_io
)brace
id|acpi_resource_io
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|base_address
id|u32
id|base_address
suffix:semicolon
DECL|member|range_length
id|u32
id|range_length
suffix:semicolon
DECL|typedef|acpi_resource_fixed_io
)brace
id|acpi_resource_fixed_io
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|reserved
id|u8
id|reserved
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|acpi_resource_vendor
)brace
id|acpi_resource_vendor
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
DECL|typedef|ACPI_RESOURCE_END_TAG
)brace
id|ACPI_RESOURCE_END_TAG
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|read_write_attribute
id|u32
id|read_write_attribute
suffix:semicolon
DECL|member|min_base_address
id|u32
id|min_base_address
suffix:semicolon
DECL|member|max_base_address
id|u32
id|max_base_address
suffix:semicolon
DECL|member|alignment
id|u32
id|alignment
suffix:semicolon
DECL|member|range_length
id|u32
id|range_length
suffix:semicolon
DECL|typedef|acpi_resource_mem24
)brace
id|acpi_resource_mem24
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|read_write_attribute
id|u32
id|read_write_attribute
suffix:semicolon
DECL|member|min_base_address
id|u32
id|min_base_address
suffix:semicolon
DECL|member|max_base_address
id|u32
id|max_base_address
suffix:semicolon
DECL|member|alignment
id|u32
id|alignment
suffix:semicolon
DECL|member|range_length
id|u32
id|range_length
suffix:semicolon
DECL|typedef|acpi_resource_mem32
)brace
id|acpi_resource_mem32
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|read_write_attribute
id|u32
id|read_write_attribute
suffix:semicolon
DECL|member|range_base_address
id|u32
id|range_base_address
suffix:semicolon
DECL|member|range_length
id|u32
id|range_length
suffix:semicolon
DECL|typedef|acpi_resource_fixed_mem32
)brace
id|acpi_resource_fixed_mem32
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|cache_attribute
id|u16
id|cache_attribute
suffix:semicolon
DECL|member|read_write_attribute
id|u16
id|read_write_attribute
suffix:semicolon
DECL|typedef|acpi_memory_attribute
)brace
id|acpi_memory_attribute
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|range_attribute
id|u16
id|range_attribute
suffix:semicolon
DECL|member|reserved
id|u16
id|reserved
suffix:semicolon
DECL|typedef|acpi_io_attribute
)brace
id|acpi_io_attribute
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u16
id|reserved2
suffix:semicolon
DECL|typedef|acpi_bus_attribute
)brace
id|acpi_bus_attribute
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|memory
id|acpi_memory_attribute
id|memory
suffix:semicolon
DECL|member|io
id|acpi_io_attribute
id|io
suffix:semicolon
DECL|member|bus
id|acpi_bus_attribute
id|bus
suffix:semicolon
DECL|typedef|acpi_resource_attribute
)brace
id|acpi_resource_attribute
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|index
id|u32
id|index
suffix:semicolon
DECL|member|string_length
id|u32
id|string_length
suffix:semicolon
DECL|member|string_ptr
id|NATIVE_CHAR
op_star
id|string_ptr
suffix:semicolon
DECL|typedef|acpi_resource_source
)brace
id|acpi_resource_source
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|resource_type
id|u32
id|resource_type
suffix:semicolon
DECL|member|producer_consumer
id|u32
id|producer_consumer
suffix:semicolon
DECL|member|decode
id|u32
id|decode
suffix:semicolon
DECL|member|min_address_fixed
id|u32
id|min_address_fixed
suffix:semicolon
DECL|member|max_address_fixed
id|u32
id|max_address_fixed
suffix:semicolon
DECL|member|attribute
id|acpi_resource_attribute
id|attribute
suffix:semicolon
DECL|member|granularity
id|u32
id|granularity
suffix:semicolon
DECL|member|min_address_range
id|u32
id|min_address_range
suffix:semicolon
DECL|member|max_address_range
id|u32
id|max_address_range
suffix:semicolon
DECL|member|address_translation_offset
id|u32
id|address_translation_offset
suffix:semicolon
DECL|member|address_length
id|u32
id|address_length
suffix:semicolon
DECL|member|resource_source
id|acpi_resource_source
id|resource_source
suffix:semicolon
DECL|typedef|acpi_resource_address16
)brace
id|acpi_resource_address16
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|resource_type
id|u32
id|resource_type
suffix:semicolon
DECL|member|producer_consumer
id|u32
id|producer_consumer
suffix:semicolon
DECL|member|decode
id|u32
id|decode
suffix:semicolon
DECL|member|min_address_fixed
id|u32
id|min_address_fixed
suffix:semicolon
DECL|member|max_address_fixed
id|u32
id|max_address_fixed
suffix:semicolon
DECL|member|attribute
id|acpi_resource_attribute
id|attribute
suffix:semicolon
DECL|member|granularity
id|u32
id|granularity
suffix:semicolon
DECL|member|min_address_range
id|u32
id|min_address_range
suffix:semicolon
DECL|member|max_address_range
id|u32
id|max_address_range
suffix:semicolon
DECL|member|address_translation_offset
id|u32
id|address_translation_offset
suffix:semicolon
DECL|member|address_length
id|u32
id|address_length
suffix:semicolon
DECL|member|resource_source
id|acpi_resource_source
id|resource_source
suffix:semicolon
DECL|typedef|acpi_resource_address32
)brace
id|acpi_resource_address32
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|resource_type
id|u32
id|resource_type
suffix:semicolon
DECL|member|producer_consumer
id|u32
id|producer_consumer
suffix:semicolon
DECL|member|decode
id|u32
id|decode
suffix:semicolon
DECL|member|min_address_fixed
id|u32
id|min_address_fixed
suffix:semicolon
DECL|member|max_address_fixed
id|u32
id|max_address_fixed
suffix:semicolon
DECL|member|attribute
id|acpi_resource_attribute
id|attribute
suffix:semicolon
DECL|member|granularity
id|u64
id|granularity
suffix:semicolon
DECL|member|min_address_range
id|u64
id|min_address_range
suffix:semicolon
DECL|member|max_address_range
id|u64
id|max_address_range
suffix:semicolon
DECL|member|address_translation_offset
id|u64
id|address_translation_offset
suffix:semicolon
DECL|member|address_length
id|u64
id|address_length
suffix:semicolon
DECL|member|resource_source
id|acpi_resource_source
id|resource_source
suffix:semicolon
DECL|typedef|acpi_resource_address64
)brace
id|acpi_resource_address64
suffix:semicolon
r_typedef
r_struct
(brace
DECL|member|producer_consumer
id|u32
id|producer_consumer
suffix:semicolon
DECL|member|edge_level
id|u32
id|edge_level
suffix:semicolon
DECL|member|active_high_low
id|u32
id|active_high_low
suffix:semicolon
DECL|member|shared_exclusive
id|u32
id|shared_exclusive
suffix:semicolon
DECL|member|number_of_interrupts
id|u32
id|number_of_interrupts
suffix:semicolon
DECL|member|resource_source
id|acpi_resource_source
id|resource_source
suffix:semicolon
DECL|member|interrupts
id|u32
id|interrupts
(braket
l_int|1
)braket
suffix:semicolon
DECL|typedef|acpi_resource_ext_irq
)brace
id|acpi_resource_ext_irq
suffix:semicolon
multiline_comment|/* ACPI_RESOURCE_TYPEs */
DECL|macro|ACPI_RSTYPE_IRQ
mdefine_line|#define ACPI_RSTYPE_IRQ                 0
DECL|macro|ACPI_RSTYPE_DMA
mdefine_line|#define ACPI_RSTYPE_DMA                 1
DECL|macro|ACPI_RSTYPE_START_DPF
mdefine_line|#define ACPI_RSTYPE_START_DPF           2
DECL|macro|ACPI_RSTYPE_END_DPF
mdefine_line|#define ACPI_RSTYPE_END_DPF             3
DECL|macro|ACPI_RSTYPE_IO
mdefine_line|#define ACPI_RSTYPE_IO                  4
DECL|macro|ACPI_RSTYPE_FIXED_IO
mdefine_line|#define ACPI_RSTYPE_FIXED_IO            5
DECL|macro|ACPI_RSTYPE_VENDOR
mdefine_line|#define ACPI_RSTYPE_VENDOR              6
DECL|macro|ACPI_RSTYPE_END_TAG
mdefine_line|#define ACPI_RSTYPE_END_TAG             7
DECL|macro|ACPI_RSTYPE_MEM24
mdefine_line|#define ACPI_RSTYPE_MEM24               8
DECL|macro|ACPI_RSTYPE_MEM32
mdefine_line|#define ACPI_RSTYPE_MEM32               9
DECL|macro|ACPI_RSTYPE_FIXED_MEM32
mdefine_line|#define ACPI_RSTYPE_FIXED_MEM32         10
DECL|macro|ACPI_RSTYPE_ADDRESS16
mdefine_line|#define ACPI_RSTYPE_ADDRESS16           11
DECL|macro|ACPI_RSTYPE_ADDRESS32
mdefine_line|#define ACPI_RSTYPE_ADDRESS32           12
DECL|macro|ACPI_RSTYPE_ADDRESS64
mdefine_line|#define ACPI_RSTYPE_ADDRESS64           13
DECL|macro|ACPI_RSTYPE_EXT_IRQ
mdefine_line|#define ACPI_RSTYPE_EXT_IRQ             14
DECL|typedef|acpi_resource_type
r_typedef
id|u32
id|acpi_resource_type
suffix:semicolon
r_typedef
r_union
(brace
DECL|member|irq
id|acpi_resource_irq
id|irq
suffix:semicolon
DECL|member|dma
id|acpi_resource_dma
id|dma
suffix:semicolon
DECL|member|start_dpf
id|acpi_resource_start_dpf
id|start_dpf
suffix:semicolon
DECL|member|io
id|acpi_resource_io
id|io
suffix:semicolon
DECL|member|fixed_io
id|acpi_resource_fixed_io
id|fixed_io
suffix:semicolon
DECL|member|vendor_specific
id|acpi_resource_vendor
id|vendor_specific
suffix:semicolon
DECL|member|end_tag
id|ACPI_RESOURCE_END_TAG
id|end_tag
suffix:semicolon
DECL|member|memory24
id|acpi_resource_mem24
id|memory24
suffix:semicolon
DECL|member|memory32
id|acpi_resource_mem32
id|memory32
suffix:semicolon
DECL|member|fixed_memory32
id|acpi_resource_fixed_mem32
id|fixed_memory32
suffix:semicolon
DECL|member|address16
id|acpi_resource_address16
id|address16
suffix:semicolon
DECL|member|address32
id|acpi_resource_address32
id|address32
suffix:semicolon
DECL|member|address64
id|acpi_resource_address64
id|address64
suffix:semicolon
DECL|member|extended_irq
id|acpi_resource_ext_irq
id|extended_irq
suffix:semicolon
DECL|typedef|acpi_resource_data
)brace
id|acpi_resource_data
suffix:semicolon
DECL|struct|acpi_resource
r_typedef
r_struct
id|acpi_resource
(brace
DECL|member|id
id|acpi_resource_type
id|id
suffix:semicolon
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|data
id|acpi_resource_data
id|data
suffix:semicolon
DECL|typedef|acpi_resource
)brace
id|acpi_resource
suffix:semicolon
DECL|macro|ACPI_RESOURCE_LENGTH
mdefine_line|#define ACPI_RESOURCE_LENGTH                12
DECL|macro|ACPI_RESOURCE_LENGTH_NO_DATA
mdefine_line|#define ACPI_RESOURCE_LENGTH_NO_DATA        8       /* Id + Length fields */
DECL|macro|ACPI_SIZEOF_RESOURCE
mdefine_line|#define ACPI_SIZEOF_RESOURCE(type)          (ACPI_RESOURCE_LENGTH_NO_DATA + sizeof (type))
DECL|macro|ACPI_NEXT_RESOURCE
mdefine_line|#define ACPI_NEXT_RESOURCE(res)             (acpi_resource *)((u8 *) res + res-&gt;length)
macro_line|#ifdef _HW_ALIGNMENT_SUPPORT
DECL|macro|ACPI_ALIGN_RESOURCE_SIZE
mdefine_line|#define ACPI_ALIGN_RESOURCE_SIZE(length)    (length)
macro_line|#else
DECL|macro|ACPI_ALIGN_RESOURCE_SIZE
mdefine_line|#define ACPI_ALIGN_RESOURCE_SIZE(length)    ACPI_ROUND_UP_TO_NATIVE_WORD(length)
macro_line|#endif
multiline_comment|/*&n; * END: of definitions for Resource Attributes&n; */
DECL|struct|acpi_pci_routing_table
r_typedef
r_struct
id|acpi_pci_routing_table
(brace
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|pin
id|u32
id|pin
suffix:semicolon
DECL|member|address
id|acpi_integer
id|address
suffix:semicolon
multiline_comment|/* here for 64-bit alignment */
DECL|member|source_index
id|u32
id|source_index
suffix:semicolon
DECL|member|source
id|NATIVE_CHAR
id|source
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* pad to 64 bits so sizeof() works in all cases */
DECL|typedef|acpi_pci_routing_table
)brace
id|acpi_pci_routing_table
suffix:semicolon
multiline_comment|/*&n; * END: of definitions for PCI Routing tables&n; */
macro_line|#endif /* __ACTYPES_H__ */
eof
