multiline_comment|/******************************************************************************&n; *&n; * Name: actypes.h - Common data types for the entire ACPI subsystem&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACTYPES_H__
DECL|macro|__ACTYPES_H__
mdefine_line|#define __ACTYPES_H__
multiline_comment|/*! [Begin] no source code translation (keep the typedefs) */
multiline_comment|/*&n; * Data type ranges&n; * Note: These macros are designed to be compiler independent as well as&n; * working around problems that some 32-bit compilers have with 64-bit&n; * constants.&n; */
DECL|macro|ACPI_UINT8_MAX
mdefine_line|#define ACPI_UINT8_MAX                  (UINT8) (~((UINT8)  0)) /* 0xFF               */
DECL|macro|ACPI_UINT16_MAX
mdefine_line|#define ACPI_UINT16_MAX                 (UINT16)(~((UINT16) 0)) /* 0xFFFF             */
DECL|macro|ACPI_UINT32_MAX
mdefine_line|#define ACPI_UINT32_MAX                 (UINT32)(~((UINT32) 0)) /* 0xFFFFFFFF         */
DECL|macro|ACPI_UINT64_MAX
mdefine_line|#define ACPI_UINT64_MAX                 (UINT64)(~((UINT64) 0)) /* 0xFFFFFFFFFFFFFFFF */
DECL|macro|ACPI_ASCII_MAX
mdefine_line|#define ACPI_ASCII_MAX                  0x7F
macro_line|#ifdef DEFINE_ALTERNATE_TYPES
multiline_comment|/*&n; * Types used only in translated source, defined here to enable&n; * cross-platform compilation only.&n; */
DECL|typedef|s32
r_typedef
r_int
id|s32
suffix:semicolon
DECL|typedef|u8
r_typedef
r_int
r_char
id|u8
suffix:semicolon
DECL|typedef|u16
r_typedef
r_int
r_int
id|u16
suffix:semicolon
DECL|typedef|u32
r_typedef
r_int
r_int
id|u32
suffix:semicolon
DECL|typedef|u64
r_typedef
id|COMPILER_DEPENDENT_UINT64
id|u64
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Data types - Fixed across all compilation models (16/32/64)&n; *&n; * BOOLEAN          Logical Boolean.&n; * INT8             8-bit  (1 byte) signed value&n; * UINT8            8-bit  (1 byte) unsigned value&n; * INT16            16-bit (2 byte) signed value&n; * UINT16           16-bit (2 byte) unsigned value&n; * INT32            32-bit (4 byte) signed value&n; * UINT32           32-bit (4 byte) unsigned value&n; * INT64            64-bit (8 byte) signed value&n; * UINT64           64-bit (8 byte) unsigned value&n; * ACPI_NATIVE_INT  32-bit on IA-32, 64-bit on IA-64 signed value&n; * ACPI_NATIVE_UINT 32-bit on IA-32, 64-bit on IA-64 unsigned value&n; */
macro_line|#ifndef ACPI_MACHINE_WIDTH
macro_line|#error ACPI_MACHINE_WIDTH not defined
macro_line|#endif
macro_line|#if ACPI_MACHINE_WIDTH == 64
multiline_comment|/*! [Begin] no source code translation (keep the typedefs) */
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
DECL|typedef|INT64
r_typedef
id|COMPILER_DEPENDENT_INT64
id|INT64
suffix:semicolon
DECL|typedef|UINT64
r_typedef
id|COMPILER_DEPENDENT_UINT64
id|UINT64
suffix:semicolon
multiline_comment|/*! [End] no source code translation !*/
DECL|typedef|acpi_native_int
r_typedef
id|s64
id|acpi_native_int
suffix:semicolon
DECL|typedef|acpi_native_uint
r_typedef
id|u64
id|acpi_native_uint
suffix:semicolon
DECL|typedef|acpi_table_ptr
r_typedef
id|u64
id|acpi_table_ptr
suffix:semicolon
DECL|typedef|acpi_io_address
r_typedef
id|u64
id|acpi_io_address
suffix:semicolon
DECL|typedef|acpi_physical_address
r_typedef
id|u64
id|acpi_physical_address
suffix:semicolon
DECL|typedef|acpi_size
r_typedef
id|u64
id|acpi_size
suffix:semicolon
DECL|macro|ALIGNED_ADDRESS_BOUNDARY
mdefine_line|#define ALIGNED_ADDRESS_BOUNDARY        0x00000008      /* No hardware alignment support in IA64 */
DECL|macro|ACPI_USE_NATIVE_DIVIDE
mdefine_line|#define ACPI_USE_NATIVE_DIVIDE                          /* Native 64-bit integer support */
DECL|macro|ACPI_MAX_PTR
mdefine_line|#define ACPI_MAX_PTR                    ACPI_UINT64_MAX
DECL|macro|ACPI_SIZE_MAX
mdefine_line|#define ACPI_SIZE_MAX                   ACPI_UINT64_MAX
macro_line|#elif ACPI_MACHINE_WIDTH == 16
multiline_comment|/*! [Begin] no source code translation (keep the typedefs) */
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
)brace
suffix:semicolon
multiline_comment|/*! [End] no source code translation !*/
DECL|typedef|acpi_native_uint
r_typedef
id|u16
id|acpi_native_uint
suffix:semicolon
DECL|typedef|acpi_native_int
r_typedef
id|s16
id|acpi_native_int
suffix:semicolon
DECL|typedef|acpi_table_ptr
r_typedef
id|u32
id|acpi_table_ptr
suffix:semicolon
DECL|typedef|acpi_io_address
r_typedef
id|u32
id|acpi_io_address
suffix:semicolon
DECL|typedef|acpi_physical_address
r_typedef
r_char
op_star
id|acpi_physical_address
suffix:semicolon
DECL|typedef|acpi_size
r_typedef
id|u16
id|acpi_size
suffix:semicolon
DECL|macro|ALIGNED_ADDRESS_BOUNDARY
mdefine_line|#define ALIGNED_ADDRESS_BOUNDARY        0x00000002
DECL|macro|ACPI_MISALIGNED_TRANSFERS
mdefine_line|#define ACPI_MISALIGNED_TRANSFERS
DECL|macro|ACPI_USE_NATIVE_DIVIDE
mdefine_line|#define ACPI_USE_NATIVE_DIVIDE                          /* No 64-bit integers, ok to use native divide */
DECL|macro|ACPI_MAX_PTR
mdefine_line|#define ACPI_MAX_PTR                    ACPI_UINT16_MAX
DECL|macro|ACPI_SIZE_MAX
mdefine_line|#define ACPI_SIZE_MAX                   ACPI_UINT16_MAX
multiline_comment|/*&n; * (16-bit only) internal integers must be 32-bits, so&n; * 64-bit integers cannot be supported&n; */
DECL|macro|ACPI_NO_INTEGER64_SUPPORT
mdefine_line|#define ACPI_NO_INTEGER64_SUPPORT
macro_line|#elif ACPI_MACHINE_WIDTH == 32
multiline_comment|/*! [Begin] no source code translation (keep the typedefs) */
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
DECL|typedef|INT64
r_typedef
id|COMPILER_DEPENDENT_INT64
id|INT64
suffix:semicolon
DECL|typedef|UINT64
r_typedef
id|COMPILER_DEPENDENT_UINT64
id|UINT64
suffix:semicolon
multiline_comment|/*! [End] no source code translation !*/
DECL|typedef|acpi_native_int
r_typedef
id|s32
id|acpi_native_int
suffix:semicolon
DECL|typedef|acpi_native_uint
r_typedef
id|u32
id|acpi_native_uint
suffix:semicolon
DECL|typedef|acpi_table_ptr
r_typedef
id|u64
id|acpi_table_ptr
suffix:semicolon
DECL|typedef|acpi_io_address
r_typedef
id|u32
id|acpi_io_address
suffix:semicolon
DECL|typedef|acpi_physical_address
r_typedef
id|u64
id|acpi_physical_address
suffix:semicolon
DECL|typedef|acpi_size
r_typedef
id|u32
id|acpi_size
suffix:semicolon
DECL|macro|ALIGNED_ADDRESS_BOUNDARY
mdefine_line|#define ALIGNED_ADDRESS_BOUNDARY        0x00000004
DECL|macro|ACPI_MISALIGNED_TRANSFERS
mdefine_line|#define ACPI_MISALIGNED_TRANSFERS
DECL|macro|ACPI_MAX_PTR
mdefine_line|#define ACPI_MAX_PTR                    ACPI_UINT32_MAX
DECL|macro|ACPI_SIZE_MAX
mdefine_line|#define ACPI_SIZE_MAX                   ACPI_UINT32_MAX
macro_line|#else
macro_line|#error unknown ACPI_MACHINE_WIDTH
macro_line|#endif
multiline_comment|/*&n; * Miscellaneous common types&n; */
DECL|typedef|UINT16_BIT
r_typedef
id|u16
id|UINT16_BIT
suffix:semicolon
DECL|typedef|UINT32_BIT
r_typedef
id|u32
id|UINT32_BIT
suffix:semicolon
DECL|typedef|ACPI_PTRDIFF
r_typedef
id|acpi_native_uint
id|ACPI_PTRDIFF
suffix:semicolon
multiline_comment|/*&n; * Pointer overlays to avoid lots of typecasting for&n; * code that accepts both physical and logical pointers.&n; */
DECL|union|acpi_pointers
r_union
id|acpi_pointers
(brace
DECL|member|physical
id|acpi_physical_address
id|physical
suffix:semicolon
DECL|member|logical
r_void
op_star
id|logical
suffix:semicolon
DECL|member|value
id|acpi_table_ptr
id|value
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_pointer
r_struct
id|acpi_pointer
(brace
DECL|member|pointer_type
id|u32
id|pointer_type
suffix:semicolon
DECL|member|pointer
r_union
id|acpi_pointers
id|pointer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* pointer_types for above */
DECL|macro|ACPI_PHYSICAL_POINTER
mdefine_line|#define ACPI_PHYSICAL_POINTER           0x01
DECL|macro|ACPI_LOGICAL_POINTER
mdefine_line|#define ACPI_LOGICAL_POINTER            0x02
multiline_comment|/* Processor mode */
DECL|macro|ACPI_PHYSICAL_ADDRESSING
mdefine_line|#define ACPI_PHYSICAL_ADDRESSING        0x04
DECL|macro|ACPI_LOGICAL_ADDRESSING
mdefine_line|#define ACPI_LOGICAL_ADDRESSING         0x08
DECL|macro|ACPI_MEMORY_MODE
mdefine_line|#define ACPI_MEMORY_MODE                0x0C
DECL|macro|ACPI_PHYSMODE_PHYSPTR
mdefine_line|#define ACPI_PHYSMODE_PHYSPTR           ACPI_PHYSICAL_ADDRESSING | ACPI_PHYSICAL_POINTER
DECL|macro|ACPI_LOGMODE_PHYSPTR
mdefine_line|#define ACPI_LOGMODE_PHYSPTR            ACPI_LOGICAL_ADDRESSING  | ACPI_PHYSICAL_POINTER
DECL|macro|ACPI_LOGMODE_LOGPTR
mdefine_line|#define ACPI_LOGMODE_LOGPTR             ACPI_LOGICAL_ADDRESSING  | ACPI_LOGICAL_POINTER
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
DECL|struct|uint64_struct
r_struct
id|uint64_struct
(brace
DECL|member|lo
id|u32
id|lo
suffix:semicolon
DECL|member|hi
id|u32
id|hi
suffix:semicolon
)brace
suffix:semicolon
DECL|union|uint64_overlay
r_union
id|uint64_overlay
(brace
DECL|member|full
id|u64
id|full
suffix:semicolon
DECL|member|part
r_struct
id|uint64_struct
id|part
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|uint32_struct
r_struct
id|uint32_struct
(brace
DECL|member|lo
id|u32
id|lo
suffix:semicolon
DECL|member|hi
id|u32
id|hi
suffix:semicolon
)brace
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
DECL|macro|ACPI_MAX_DECIMAL_DIGITS
mdefine_line|#define ACPI_MAX_DECIMAL_DIGITS         10  /* 2^32 = 4,294,967,296 */
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
DECL|macro|ACPI_MAX_DECIMAL_DIGITS
mdefine_line|#define ACPI_MAX_DECIMAL_DIGITS         20  /* 2^64 = 18,446,744,073,709,551,616 */
macro_line|#if ACPI_MACHINE_WIDTH == 64
DECL|macro|ACPI_USE_NATIVE_DIVIDE
mdefine_line|#define ACPI_USE_NATIVE_DIVIDE          /* Use compiler native 64-bit divide */
macro_line|#endif
macro_line|#endif
DECL|macro|ACPI_MAX64_DECIMAL_DIGITS
mdefine_line|#define ACPI_MAX64_DECIMAL_DIGITS       20
DECL|macro|ACPI_MAX32_DECIMAL_DIGITS
mdefine_line|#define ACPI_MAX32_DECIMAL_DIGITS       10
DECL|macro|ACPI_MAX16_DECIMAL_DIGITS
mdefine_line|#define ACPI_MAX16_DECIMAL_DIGITS        5
DECL|macro|ACPI_MAX8_DECIMAL_DIGITS
mdefine_line|#define ACPI_MAX8_DECIMAL_DIGITS         3
multiline_comment|/*&n; * Constants with special meanings&n; */
DECL|macro|ACPI_ROOT_OBJECT
mdefine_line|#define ACPI_ROOT_OBJECT                (acpi_handle) ACPI_PTR_ADD (char, NULL, ACPI_MAX_PTR)
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
DECL|macro|NUM_ACPI_TABLE_TYPES
mdefine_line|#define NUM_ACPI_TABLE_TYPES            (ACPI_TABLE_MAX+1)
multiline_comment|/*&n; * Types associated with ACPI names and objects.  The first group of&n; * values (up to ACPI_TYPE_EXTERNAL_MAX) correspond to the definition&n; * of the ACPI object_type() operator (See the ACPI Spec). Therefore,&n; * only add to the first group if the spec changes.&n; *&n; * NOTE: Types must be kept in sync with the global acpi_ns_properties&n; * and acpi_ns_type_names arrays.&n; */
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
mdefine_line|#define ACPI_TYPE_PACKAGE               0x04  /* byte_const, multiple data_term/Constant/super_name */
DECL|macro|ACPI_TYPE_FIELD_UNIT
mdefine_line|#define ACPI_TYPE_FIELD_UNIT            0x05
DECL|macro|ACPI_TYPE_DEVICE
mdefine_line|#define ACPI_TYPE_DEVICE                0x06  /* Name, multiple Node */
DECL|macro|ACPI_TYPE_EVENT
mdefine_line|#define ACPI_TYPE_EVENT                 0x07
DECL|macro|ACPI_TYPE_METHOD
mdefine_line|#define ACPI_TYPE_METHOD                0x08  /* Name, byte_const, multiple Code */
DECL|macro|ACPI_TYPE_MUTEX
mdefine_line|#define ACPI_TYPE_MUTEX                 0x09
DECL|macro|ACPI_TYPE_REGION
mdefine_line|#define ACPI_TYPE_REGION                0x0A
DECL|macro|ACPI_TYPE_POWER
mdefine_line|#define ACPI_TYPE_POWER                 0x0B  /* Name,byte_const,word_const,multi Node */
DECL|macro|ACPI_TYPE_PROCESSOR
mdefine_line|#define ACPI_TYPE_PROCESSOR             0x0C  /* Name,byte_const,Dword_const,byte_const,multi nm_o */
DECL|macro|ACPI_TYPE_THERMAL
mdefine_line|#define ACPI_TYPE_THERMAL               0x0D  /* Name, multiple Node */
DECL|macro|ACPI_TYPE_BUFFER_FIELD
mdefine_line|#define ACPI_TYPE_BUFFER_FIELD          0x0E
DECL|macro|ACPI_TYPE_DDB_HANDLE
mdefine_line|#define ACPI_TYPE_DDB_HANDLE            0x0F
DECL|macro|ACPI_TYPE_DEBUG_OBJECT
mdefine_line|#define ACPI_TYPE_DEBUG_OBJECT          0x10
DECL|macro|ACPI_TYPE_EXTERNAL_MAX
mdefine_line|#define ACPI_TYPE_EXTERNAL_MAX          0x10
multiline_comment|/*&n; * These are object types that do not map directly to the ACPI&n; * object_type() operator. They are used for various internal purposes only.&n; * If new predefined ACPI_TYPEs are added (via the ACPI specification), these&n; * internal types must move upwards. (There is code that depends on these&n; * values being contiguous with the external types above.)&n; */
DECL|macro|ACPI_TYPE_LOCAL_REGION_FIELD
mdefine_line|#define ACPI_TYPE_LOCAL_REGION_FIELD    0x11
DECL|macro|ACPI_TYPE_LOCAL_BANK_FIELD
mdefine_line|#define ACPI_TYPE_LOCAL_BANK_FIELD      0x12
DECL|macro|ACPI_TYPE_LOCAL_INDEX_FIELD
mdefine_line|#define ACPI_TYPE_LOCAL_INDEX_FIELD     0x13
DECL|macro|ACPI_TYPE_LOCAL_REFERENCE
mdefine_line|#define ACPI_TYPE_LOCAL_REFERENCE       0x14  /* Arg#, Local#, Name, Debug, ref_of, Index */
DECL|macro|ACPI_TYPE_LOCAL_ALIAS
mdefine_line|#define ACPI_TYPE_LOCAL_ALIAS           0x15
DECL|macro|ACPI_TYPE_LOCAL_METHOD_ALIAS
mdefine_line|#define ACPI_TYPE_LOCAL_METHOD_ALIAS    0x16
DECL|macro|ACPI_TYPE_LOCAL_NOTIFY
mdefine_line|#define ACPI_TYPE_LOCAL_NOTIFY          0x17
DECL|macro|ACPI_TYPE_LOCAL_ADDRESS_HANDLER
mdefine_line|#define ACPI_TYPE_LOCAL_ADDRESS_HANDLER 0x18
DECL|macro|ACPI_TYPE_LOCAL_RESOURCE
mdefine_line|#define ACPI_TYPE_LOCAL_RESOURCE        0x19
DECL|macro|ACPI_TYPE_LOCAL_RESOURCE_FIELD
mdefine_line|#define ACPI_TYPE_LOCAL_RESOURCE_FIELD  0x1A
DECL|macro|ACPI_TYPE_LOCAL_SCOPE
mdefine_line|#define ACPI_TYPE_LOCAL_SCOPE           0x1B  /* 1 Name, multiple object_list Nodes */
DECL|macro|ACPI_TYPE_NS_NODE_MAX
mdefine_line|#define ACPI_TYPE_NS_NODE_MAX           0x1B  /* Last typecode used within a NS Node */
multiline_comment|/*&n; * These are special object types that never appear in&n; * a Namespace node, only in an union acpi_operand_object&n; */
DECL|macro|ACPI_TYPE_LOCAL_EXTRA
mdefine_line|#define ACPI_TYPE_LOCAL_EXTRA           0x1C
DECL|macro|ACPI_TYPE_LOCAL_DATA
mdefine_line|#define ACPI_TYPE_LOCAL_DATA            0x1D
DECL|macro|ACPI_TYPE_LOCAL_MAX
mdefine_line|#define ACPI_TYPE_LOCAL_MAX             0x1D
multiline_comment|/* All types above here are invalid */
DECL|macro|ACPI_TYPE_INVALID
mdefine_line|#define ACPI_TYPE_INVALID               0x1E
DECL|macro|ACPI_TYPE_NOT_FOUND
mdefine_line|#define ACPI_TYPE_NOT_FOUND             0xFF
multiline_comment|/*&n; * Bitmapped ACPI types.  Used internally only&n; */
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
DECL|macro|ACPI_IO_MASK
mdefine_line|#define ACPI_IO_MASK                    1
multiline_comment|/*&n; * Event Types: Fixed &amp; General Purpose&n; */
DECL|typedef|acpi_event_type
r_typedef
id|u32
id|acpi_event_type
suffix:semicolon
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
multiline_comment|/*&n; * Event Status - Per event&n; * -------------&n; * The encoding of acpi_event_status is illustrated below.&n; * Note that a set bit (1) indicates the property is TRUE&n; * (e.g. if bit 0 is set then the event is enabled).&n; * +-------------+-+-+-+&n; * |   Bits 31:3 |2|1|0|&n; * +-------------+-+-+-+&n; *          |     | | |&n; *          |     | | +- Enabled?&n; *          |     | +--- Enabled for wake?&n; *          |     +----- Set?&n; *          +----------- &lt;Reserved&gt;&n; */
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
multiline_comment|/*&n; * General Purpose Events (GPE)&n; */
DECL|macro|ACPI_GPE_INVALID
mdefine_line|#define ACPI_GPE_INVALID                0xFF
DECL|macro|ACPI_GPE_MAX
mdefine_line|#define ACPI_GPE_MAX                    0xFF
DECL|macro|ACPI_NUM_GPE
mdefine_line|#define ACPI_NUM_GPE                    256
DECL|macro|ACPI_GPE_ENABLE
mdefine_line|#define ACPI_GPE_ENABLE                 0
DECL|macro|ACPI_GPE_DISABLE
mdefine_line|#define ACPI_GPE_DISABLE                1
multiline_comment|/*&n; * GPE info flags - Per GPE&n; * +-+-+-+---+---+-+&n; * |7|6|5|4:3|2:1|0|&n; * +-+-+-+---+---+-+&n; *  | | |  |   |  |&n; *  | | |  |   |  +--- Interrupt type: Edge or Level Triggered&n; *  | | |  |   +--- Type: Wake-only, Runtime-only, or wake/runtime&n; *  | | |  +--- Type of dispatch -- to method, handler, or none&n; *  | | +--- Enabled for runtime?&n; *  | +--- Enabled for wake?&n; *  +--- System state when GPE ocurred (running/waking)&n; */
DECL|macro|ACPI_GPE_XRUPT_TYPE_MASK
mdefine_line|#define ACPI_GPE_XRUPT_TYPE_MASK        (u8) 0x01
DECL|macro|ACPI_GPE_LEVEL_TRIGGERED
mdefine_line|#define ACPI_GPE_LEVEL_TRIGGERED        (u8) 0x01
DECL|macro|ACPI_GPE_EDGE_TRIGGERED
mdefine_line|#define ACPI_GPE_EDGE_TRIGGERED         (u8) 0x00
DECL|macro|ACPI_GPE_TYPE_MASK
mdefine_line|#define ACPI_GPE_TYPE_MASK              (u8) 0x06
DECL|macro|ACPI_GPE_TYPE_WAKE_RUN
mdefine_line|#define ACPI_GPE_TYPE_WAKE_RUN          (u8) 0x06
DECL|macro|ACPI_GPE_TYPE_WAKE
mdefine_line|#define ACPI_GPE_TYPE_WAKE              (u8) 0x02
DECL|macro|ACPI_GPE_TYPE_RUNTIME
mdefine_line|#define ACPI_GPE_TYPE_RUNTIME           (u8) 0x04    /* Default */
DECL|macro|ACPI_GPE_DISPATCH_MASK
mdefine_line|#define ACPI_GPE_DISPATCH_MASK          (u8) 0x18
DECL|macro|ACPI_GPE_DISPATCH_HANDLER
mdefine_line|#define ACPI_GPE_DISPATCH_HANDLER       (u8) 0x08
DECL|macro|ACPI_GPE_DISPATCH_METHOD
mdefine_line|#define ACPI_GPE_DISPATCH_METHOD        (u8) 0x10
DECL|macro|ACPI_GPE_DISPATCH_NOT_USED
mdefine_line|#define ACPI_GPE_DISPATCH_NOT_USED      (u8) 0x00    /* Default */
DECL|macro|ACPI_GPE_RUN_ENABLE_MASK
mdefine_line|#define ACPI_GPE_RUN_ENABLE_MASK        (u8) 0x20
DECL|macro|ACPI_GPE_RUN_ENABLED
mdefine_line|#define ACPI_GPE_RUN_ENABLED            (u8) 0x20
DECL|macro|ACPI_GPE_RUN_DISABLED
mdefine_line|#define ACPI_GPE_RUN_DISABLED           (u8) 0x00    /* Default */
DECL|macro|ACPI_GPE_WAKE_ENABLE_MASK
mdefine_line|#define ACPI_GPE_WAKE_ENABLE_MASK       (u8) 0x40
DECL|macro|ACPI_GPE_WAKE_ENABLED
mdefine_line|#define ACPI_GPE_WAKE_ENABLED           (u8) 0x40
DECL|macro|ACPI_GPE_WAKE_DISABLED
mdefine_line|#define ACPI_GPE_WAKE_DISABLED          (u8) 0x00    /* Default */
DECL|macro|ACPI_GPE_ENABLE_MASK
mdefine_line|#define ACPI_GPE_ENABLE_MASK            (u8) 0x60    /* Both run/wake */
DECL|macro|ACPI_GPE_SYSTEM_MASK
mdefine_line|#define ACPI_GPE_SYSTEM_MASK            (u8) 0x80
DECL|macro|ACPI_GPE_SYSTEM_RUNNING
mdefine_line|#define ACPI_GPE_SYSTEM_RUNNING         (u8) 0x80
DECL|macro|ACPI_GPE_SYSTEM_WAKING
mdefine_line|#define ACPI_GPE_SYSTEM_WAKING          (u8) 0x00
multiline_comment|/*&n; * Flags for GPE and Lock interfaces&n; */
DECL|macro|ACPI_EVENT_WAKE_ENABLE
mdefine_line|#define ACPI_EVENT_WAKE_ENABLE          0x2             /* acpi_gpe_enable */
DECL|macro|ACPI_EVENT_WAKE_DISABLE
mdefine_line|#define ACPI_EVENT_WAKE_DISABLE         0x2             /* acpi_gpe_disable */
DECL|macro|ACPI_NOT_ISR
mdefine_line|#define ACPI_NOT_ISR                    0x1
DECL|macro|ACPI_ISR
mdefine_line|#define ACPI_ISR                        0x0
multiline_comment|/* Notify types */
DECL|macro|ACPI_SYSTEM_NOTIFY
mdefine_line|#define ACPI_SYSTEM_NOTIFY              0x1
DECL|macro|ACPI_DEVICE_NOTIFY
mdefine_line|#define ACPI_DEVICE_NOTIFY              0x2
DECL|macro|ACPI_ALL_NOTIFY
mdefine_line|#define ACPI_ALL_NOTIFY                 0x3
DECL|macro|ACPI_MAX_NOTIFY_HANDLER_TYPE
mdefine_line|#define ACPI_MAX_NOTIFY_HANDLER_TYPE    0x3
DECL|macro|ACPI_MAX_SYS_NOTIFY
mdefine_line|#define ACPI_MAX_SYS_NOTIFY             0x7f
multiline_comment|/* Address Space (Operation Region) Types */
DECL|typedef|acpi_adr_space_type
r_typedef
id|u8
id|acpi_adr_space_type
suffix:semicolon
DECL|macro|ACPI_ADR_SPACE_SYSTEM_MEMORY
mdefine_line|#define ACPI_ADR_SPACE_SYSTEM_MEMORY    (acpi_adr_space_type) 0
DECL|macro|ACPI_ADR_SPACE_SYSTEM_IO
mdefine_line|#define ACPI_ADR_SPACE_SYSTEM_IO        (acpi_adr_space_type) 1
DECL|macro|ACPI_ADR_SPACE_PCI_CONFIG
mdefine_line|#define ACPI_ADR_SPACE_PCI_CONFIG       (acpi_adr_space_type) 2
DECL|macro|ACPI_ADR_SPACE_EC
mdefine_line|#define ACPI_ADR_SPACE_EC               (acpi_adr_space_type) 3
DECL|macro|ACPI_ADR_SPACE_SMBUS
mdefine_line|#define ACPI_ADR_SPACE_SMBUS            (acpi_adr_space_type) 4
DECL|macro|ACPI_ADR_SPACE_CMOS
mdefine_line|#define ACPI_ADR_SPACE_CMOS             (acpi_adr_space_type) 5
DECL|macro|ACPI_ADR_SPACE_PCI_BAR_TARGET
mdefine_line|#define ACPI_ADR_SPACE_PCI_BAR_TARGET   (acpi_adr_space_type) 6
DECL|macro|ACPI_ADR_SPACE_DATA_TABLE
mdefine_line|#define ACPI_ADR_SPACE_DATA_TABLE       (acpi_adr_space_type) 7
DECL|macro|ACPI_ADR_SPACE_FIXED_HARDWARE
mdefine_line|#define ACPI_ADR_SPACE_FIXED_HARDWARE   (acpi_adr_space_type) 127
multiline_comment|/*&n; * bit_register IDs&n; * These are bitfields defined within the full ACPI registers&n; */
DECL|macro|ACPI_BITREG_TIMER_STATUS
mdefine_line|#define ACPI_BITREG_TIMER_STATUS                0x00
DECL|macro|ACPI_BITREG_BUS_MASTER_STATUS
mdefine_line|#define ACPI_BITREG_BUS_MASTER_STATUS           0x01
DECL|macro|ACPI_BITREG_GLOBAL_LOCK_STATUS
mdefine_line|#define ACPI_BITREG_GLOBAL_LOCK_STATUS          0x02
DECL|macro|ACPI_BITREG_POWER_BUTTON_STATUS
mdefine_line|#define ACPI_BITREG_POWER_BUTTON_STATUS         0x03
DECL|macro|ACPI_BITREG_SLEEP_BUTTON_STATUS
mdefine_line|#define ACPI_BITREG_SLEEP_BUTTON_STATUS         0x04
DECL|macro|ACPI_BITREG_RT_CLOCK_STATUS
mdefine_line|#define ACPI_BITREG_RT_CLOCK_STATUS             0x05
DECL|macro|ACPI_BITREG_WAKE_STATUS
mdefine_line|#define ACPI_BITREG_WAKE_STATUS                 0x06
DECL|macro|ACPI_BITREG_TIMER_ENABLE
mdefine_line|#define ACPI_BITREG_TIMER_ENABLE                0x07
DECL|macro|ACPI_BITREG_GLOBAL_LOCK_ENABLE
mdefine_line|#define ACPI_BITREG_GLOBAL_LOCK_ENABLE          0x08
DECL|macro|ACPI_BITREG_POWER_BUTTON_ENABLE
mdefine_line|#define ACPI_BITREG_POWER_BUTTON_ENABLE         0x09
DECL|macro|ACPI_BITREG_SLEEP_BUTTON_ENABLE
mdefine_line|#define ACPI_BITREG_SLEEP_BUTTON_ENABLE         0x0A
DECL|macro|ACPI_BITREG_RT_CLOCK_ENABLE
mdefine_line|#define ACPI_BITREG_RT_CLOCK_ENABLE             0x0B
DECL|macro|ACPI_BITREG_WAKE_ENABLE
mdefine_line|#define ACPI_BITREG_WAKE_ENABLE                 0x0C
DECL|macro|ACPI_BITREG_SCI_ENABLE
mdefine_line|#define ACPI_BITREG_SCI_ENABLE                  0x0D
DECL|macro|ACPI_BITREG_BUS_MASTER_RLD
mdefine_line|#define ACPI_BITREG_BUS_MASTER_RLD              0x0E
DECL|macro|ACPI_BITREG_GLOBAL_LOCK_RELEASE
mdefine_line|#define ACPI_BITREG_GLOBAL_LOCK_RELEASE         0x0F
DECL|macro|ACPI_BITREG_SLEEP_TYPE_A
mdefine_line|#define ACPI_BITREG_SLEEP_TYPE_A                0x10
DECL|macro|ACPI_BITREG_SLEEP_TYPE_B
mdefine_line|#define ACPI_BITREG_SLEEP_TYPE_B                0x11
DECL|macro|ACPI_BITREG_SLEEP_ENABLE
mdefine_line|#define ACPI_BITREG_SLEEP_ENABLE                0x12
DECL|macro|ACPI_BITREG_ARB_DISABLE
mdefine_line|#define ACPI_BITREG_ARB_DISABLE                 0x13
DECL|macro|ACPI_BITREG_MAX
mdefine_line|#define ACPI_BITREG_MAX                         0x13
DECL|macro|ACPI_NUM_BITREG
mdefine_line|#define ACPI_NUM_BITREG                         ACPI_BITREG_MAX + 1
multiline_comment|/*&n; * External ACPI object definition&n; */
DECL|union|acpi_object
r_union
id|acpi_object
(brace
DECL|member|type
id|acpi_object_type
id|type
suffix:semicolon
multiline_comment|/* See definition of acpi_ns_type for values */
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
r_char
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
id|acpi_object
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
id|acpi_io_address
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
)brace
suffix:semicolon
multiline_comment|/*&n; * List of objects, used as a parameter list for control method evaluation&n; */
DECL|struct|acpi_object_list
r_struct
id|acpi_object_list
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|pointer
r_union
id|acpi_object
op_star
id|pointer
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Miscellaneous common Data Structures used by the interfaces&n; */
DECL|macro|ACPI_NO_BUFFER
mdefine_line|#define ACPI_NO_BUFFER              0
DECL|macro|ACPI_ALLOCATE_BUFFER
mdefine_line|#define ACPI_ALLOCATE_BUFFER        (acpi_size) (-1)
DECL|macro|ACPI_ALLOCATE_LOCAL_BUFFER
mdefine_line|#define ACPI_ALLOCATE_LOCAL_BUFFER  (acpi_size) (-2)
DECL|struct|acpi_buffer
r_struct
id|acpi_buffer
(brace
DECL|member|length
id|acpi_size
id|length
suffix:semicolon
multiline_comment|/* Length in bytes of the buffer */
DECL|member|pointer
r_void
op_star
id|pointer
suffix:semicolon
multiline_comment|/* pointer to buffer */
)brace
suffix:semicolon
multiline_comment|/*&n; * name_type for acpi_get_name&n; */
DECL|macro|ACPI_FULL_PATHNAME
mdefine_line|#define ACPI_FULL_PATHNAME              0
DECL|macro|ACPI_SINGLE_NAME
mdefine_line|#define ACPI_SINGLE_NAME                1
DECL|macro|ACPI_NAME_TYPE_MAX
mdefine_line|#define ACPI_NAME_TYPE_MAX              1
multiline_comment|/*&n; * Structure and flags for acpi_get_system_info&n; */
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
r_struct
id|acpi_table_info
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * System info returned by acpi_get_system_info()&n; */
DECL|struct|acpi_system_info
r_struct
id|acpi_system_info
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
r_struct
id|acpi_table_info
id|table_info
(braket
id|NUM_ACPI_TABLE_TYPES
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * Types specific to the OS service interfaces&n; */
r_typedef
id|u32
DECL|typedef|acpi_osd_handler
(paren
id|ACPI_SYSTEM_XFACE
op_star
id|acpi_osd_handler
)paren
(paren
r_void
op_star
id|context
)paren
suffix:semicolon
r_typedef
r_void
DECL|typedef|acpi_osd_exec_callback
(paren
id|ACPI_SYSTEM_XFACE
op_star
id|acpi_osd_exec_callback
)paren
(paren
r_void
op_star
id|context
)paren
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
DECL|typedef|acpi_object_handler
r_void
(paren
op_star
id|acpi_object_handler
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
r_typedef
DECL|typedef|acpi_init_handler
id|acpi_status
(paren
op_star
id|acpi_init_handler
)paren
(paren
id|acpi_handle
id|object
comma
id|u32
id|function
)paren
suffix:semicolon
DECL|macro|ACPI_INIT_DEVICE_INI
mdefine_line|#define ACPI_INIT_DEVICE_INI        1
r_typedef
DECL|typedef|acpi_exception_handler
id|acpi_status
(paren
op_star
id|acpi_exception_handler
)paren
(paren
id|acpi_status
id|aml_status
comma
id|acpi_name
id|name
comma
id|u16
id|opcode
comma
id|u32
id|aml_offset
comma
r_void
op_star
id|context
)paren
suffix:semicolon
multiline_comment|/* Address Spaces (For Operation Regions) */
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
id|acpi_physical_address
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
mdefine_line|#define ACPI_DEFAULT_HANDLER        NULL
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
multiline_comment|/* Common string version of device HIDs and UIDs */
DECL|struct|acpi_device_id
r_struct
id|acpi_device_id
(brace
DECL|member|value
r_char
id|value
(braket
id|ACPI_DEVICE_ID_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Common string version of device CIDs */
DECL|struct|acpi_compatible_id
r_struct
id|acpi_compatible_id
(brace
DECL|member|value
r_char
id|value
(braket
id|ACPI_MAX_CID_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_compatible_id_list
r_struct
id|acpi_compatible_id_list
(brace
DECL|member|count
id|u32
id|count
suffix:semicolon
DECL|member|size
id|u32
id|size
suffix:semicolon
DECL|member|id
r_struct
id|acpi_compatible_id
id|id
(braket
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Structure and flags for acpi_get_object_info */
DECL|macro|ACPI_VALID_STA
mdefine_line|#define ACPI_VALID_STA                  0x0001
DECL|macro|ACPI_VALID_ADR
mdefine_line|#define ACPI_VALID_ADR                  0x0002
DECL|macro|ACPI_VALID_HID
mdefine_line|#define ACPI_VALID_HID                  0x0004
DECL|macro|ACPI_VALID_UID
mdefine_line|#define ACPI_VALID_UID                  0x0008
DECL|macro|ACPI_VALID_CID
mdefine_line|#define ACPI_VALID_CID                  0x0010
DECL|macro|ACPI_VALID_SXDS
mdefine_line|#define ACPI_VALID_SXDS                 0x0020
DECL|macro|ACPI_COMMON_OBJ_INFO
mdefine_line|#define ACPI_COMMON_OBJ_INFO &bslash;&n;&t;acpi_object_type                    type;           /* ACPI object type */ &bslash;&n;&t;acpi_name                           name            /* ACPI object Name */
DECL|struct|acpi_obj_info_header
r_struct
id|acpi_obj_info_header
(brace
DECL|member|ACPI_COMMON_OBJ_INFO
id|ACPI_COMMON_OBJ_INFO
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Structure returned from Get Object Info */
DECL|struct|acpi_device_info
r_struct
id|acpi_device_info
(brace
DECL|member|ACPI_COMMON_OBJ_INFO
id|ACPI_COMMON_OBJ_INFO
suffix:semicolon
DECL|member|valid
id|u32
id|valid
suffix:semicolon
multiline_comment|/* Indicates which fields below are valid */
DECL|member|current_status
id|u32
id|current_status
suffix:semicolon
multiline_comment|/* _STA value */
DECL|member|address
id|acpi_integer
id|address
suffix:semicolon
multiline_comment|/* _ADR value if any */
DECL|member|hardware_id
r_struct
id|acpi_device_id
id|hardware_id
suffix:semicolon
multiline_comment|/* _HID value if any */
DECL|member|unique_id
r_struct
id|acpi_device_id
id|unique_id
suffix:semicolon
multiline_comment|/* _UID value if any */
DECL|member|highest_dstates
id|u8
id|highest_dstates
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* _sx_d values: 0xFF indicates not valid */
DECL|member|compatibility_id
r_struct
id|acpi_compatible_id_list
id|compatibility_id
suffix:semicolon
multiline_comment|/* List of _CIDs if any */
)brace
suffix:semicolon
multiline_comment|/* Context structs for address space handlers */
DECL|struct|acpi_pci_id
r_struct
id|acpi_pci_id
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
)brace
suffix:semicolon
DECL|struct|acpi_mem_space_context
r_struct
id|acpi_mem_space_context
(brace
DECL|member|length
id|u32
id|length
suffix:semicolon
DECL|member|address
id|acpi_physical_address
id|address
suffix:semicolon
DECL|member|mapped_physical_address
id|acpi_physical_address
id|mapped_physical_address
suffix:semicolon
DECL|member|mapped_logical_address
id|u8
op_star
id|mapped_logical_address
suffix:semicolon
DECL|member|mapped_length
id|acpi_size
id|mapped_length
suffix:semicolon
)brace
suffix:semicolon
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
multiline_comment|/*&n; *  IO Attributes&n; *  The ISA Io ranges are:     n000-n0_ffh, n400-n4_ffh, n800-n8_ffh, n_c00-n_cFFh.&n; *  The non-ISA Io ranges are: n100-n3_ffh, n500-n7_ffh, n900-n_bFfh, n_cd0-n_fFFh.&n; */
DECL|macro|ACPI_NON_ISA_ONLY_RANGES
mdefine_line|#define ACPI_NON_ISA_ONLY_RANGES        (u8) 0x01
DECL|macro|ACPI_ISA_ONLY_RANGES
mdefine_line|#define ACPI_ISA_ONLY_RANGES            (u8) 0x02
DECL|macro|ACPI_ENTIRE_RANGE
mdefine_line|#define ACPI_ENTIRE_RANGE               (ACPI_NON_ISA_ONLY_RANGES | ACPI_ISA_ONLY_RANGES)
DECL|macro|ACPI_SPARSE_TRANSLATION
mdefine_line|#define ACPI_SPARSE_TRANSLATION         (u8) 0x03
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
DECL|struct|acpi_resource_irq
r_struct
id|acpi_resource_irq
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
)brace
suffix:semicolon
DECL|struct|acpi_resource_dma
r_struct
id|acpi_resource_dma
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
)brace
suffix:semicolon
DECL|struct|acpi_resource_start_dpf
r_struct
id|acpi_resource_start_dpf
(brace
DECL|member|compatibility_priority
id|u32
id|compatibility_priority
suffix:semicolon
DECL|member|performance_robustness
id|u32
id|performance_robustness
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * END_DEPENDENT_FUNCTIONS_RESOURCE struct is not&n; * needed because it has no fields&n; */
DECL|struct|acpi_resource_io
r_struct
id|acpi_resource_io
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
)brace
suffix:semicolon
DECL|struct|acpi_resource_fixed_io
r_struct
id|acpi_resource_fixed_io
(brace
DECL|member|base_address
id|u32
id|base_address
suffix:semicolon
DECL|member|range_length
id|u32
id|range_length
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_resource_vendor
r_struct
id|acpi_resource_vendor
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
)brace
suffix:semicolon
DECL|struct|acpi_resource_end_tag
r_struct
id|acpi_resource_end_tag
(brace
DECL|member|checksum
id|u8
id|checksum
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_resource_mem24
r_struct
id|acpi_resource_mem24
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
)brace
suffix:semicolon
DECL|struct|acpi_resource_mem32
r_struct
id|acpi_resource_mem32
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
)brace
suffix:semicolon
DECL|struct|acpi_resource_fixed_mem32
r_struct
id|acpi_resource_fixed_mem32
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
)brace
suffix:semicolon
DECL|struct|acpi_memory_attribute
r_struct
id|acpi_memory_attribute
(brace
DECL|member|cache_attribute
id|u16
id|cache_attribute
suffix:semicolon
DECL|member|read_write_attribute
id|u16
id|read_write_attribute
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_io_attribute
r_struct
id|acpi_io_attribute
(brace
DECL|member|range_attribute
id|u16
id|range_attribute
suffix:semicolon
DECL|member|translation_attribute
id|u16
id|translation_attribute
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_bus_attribute
r_struct
id|acpi_bus_attribute
(brace
DECL|member|reserved1
id|u16
id|reserved1
suffix:semicolon
DECL|member|reserved2
id|u16
id|reserved2
suffix:semicolon
)brace
suffix:semicolon
DECL|union|acpi_resource_attribute
r_union
id|acpi_resource_attribute
(brace
DECL|member|memory
r_struct
id|acpi_memory_attribute
id|memory
suffix:semicolon
DECL|member|io
r_struct
id|acpi_io_attribute
id|io
suffix:semicolon
DECL|member|bus
r_struct
id|acpi_bus_attribute
id|bus
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_resource_source
r_struct
id|acpi_resource_source
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
r_char
op_star
id|string_ptr
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_resource_address16
r_struct
id|acpi_resource_address16
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
r_union
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
r_struct
id|acpi_resource_source
id|resource_source
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_resource_address32
r_struct
id|acpi_resource_address32
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
r_union
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
r_struct
id|acpi_resource_source
id|resource_source
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_resource_address64
r_struct
id|acpi_resource_address64
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
r_union
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
r_struct
id|acpi_resource_source
id|resource_source
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_resource_ext_irq
r_struct
id|acpi_resource_ext_irq
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
r_struct
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
)brace
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
DECL|union|acpi_resource_data
r_union
id|acpi_resource_data
(brace
DECL|member|irq
r_struct
id|acpi_resource_irq
id|irq
suffix:semicolon
DECL|member|dma
r_struct
id|acpi_resource_dma
id|dma
suffix:semicolon
DECL|member|start_dpf
r_struct
id|acpi_resource_start_dpf
id|start_dpf
suffix:semicolon
DECL|member|io
r_struct
id|acpi_resource_io
id|io
suffix:semicolon
DECL|member|fixed_io
r_struct
id|acpi_resource_fixed_io
id|fixed_io
suffix:semicolon
DECL|member|vendor_specific
r_struct
id|acpi_resource_vendor
id|vendor_specific
suffix:semicolon
DECL|member|end_tag
r_struct
id|acpi_resource_end_tag
id|end_tag
suffix:semicolon
DECL|member|memory24
r_struct
id|acpi_resource_mem24
id|memory24
suffix:semicolon
DECL|member|memory32
r_struct
id|acpi_resource_mem32
id|memory32
suffix:semicolon
DECL|member|fixed_memory32
r_struct
id|acpi_resource_fixed_mem32
id|fixed_memory32
suffix:semicolon
DECL|member|address16
r_struct
id|acpi_resource_address16
id|address16
suffix:semicolon
DECL|member|address32
r_struct
id|acpi_resource_address32
id|address32
suffix:semicolon
DECL|member|address64
r_struct
id|acpi_resource_address64
id|address64
suffix:semicolon
DECL|member|extended_irq
r_struct
id|acpi_resource_ext_irq
id|extended_irq
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|acpi_resource
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
r_union
id|acpi_resource_data
id|data
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|ACPI_RESOURCE_LENGTH
mdefine_line|#define ACPI_RESOURCE_LENGTH                12
DECL|macro|ACPI_RESOURCE_LENGTH_NO_DATA
mdefine_line|#define ACPI_RESOURCE_LENGTH_NO_DATA        8       /* Id + Length fields */
DECL|macro|ACPI_SIZEOF_RESOURCE
mdefine_line|#define ACPI_SIZEOF_RESOURCE(type)          (ACPI_RESOURCE_LENGTH_NO_DATA + sizeof (type))
DECL|macro|ACPI_NEXT_RESOURCE
mdefine_line|#define ACPI_NEXT_RESOURCE(res)             (struct acpi_resource *)((u8 *) res + res-&gt;length)
macro_line|#ifdef ACPI_MISALIGNED_TRANSFERS
DECL|macro|ACPI_ALIGN_RESOURCE_SIZE
mdefine_line|#define ACPI_ALIGN_RESOURCE_SIZE(length)    (length)
macro_line|#else
DECL|macro|ACPI_ALIGN_RESOURCE_SIZE
mdefine_line|#define ACPI_ALIGN_RESOURCE_SIZE(length)    ACPI_ROUND_UP_TO_NATIVE_WORD(length)
macro_line|#endif
multiline_comment|/*&n; * END: of definitions for Resource Attributes&n; */
DECL|struct|acpi_pci_routing_table
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
r_char
id|source
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* pad to 64 bits so sizeof() works in all cases */
)brace
suffix:semicolon
multiline_comment|/*&n; * END: of definitions for PCI Routing tables&n; */
macro_line|#endif /* __ACTYPES_H__ */
eof
