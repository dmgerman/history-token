multiline_comment|/******************************************************************************&n; *&n; * Name: amlcode.h - Definitions for AML, as included in &quot;definition blocks&quot;&n; *                   Declarations and definitions contained herein are derived&n; *                   directly from the ACPI specification.&n; *       $Revision: 52 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#ifndef __AMLCODE_H__
DECL|macro|__AMLCODE_H__
mdefine_line|#define __AMLCODE_H__
multiline_comment|/* primary opcodes */
DECL|macro|AML_NULL_CHAR
mdefine_line|#define AML_NULL_CHAR               (u16) 0x00
DECL|macro|AML_ZERO_OP
mdefine_line|#define AML_ZERO_OP                 (u16) 0x00
DECL|macro|AML_ONE_OP
mdefine_line|#define AML_ONE_OP                  (u16) 0x01
DECL|macro|AML_UNASSIGNED
mdefine_line|#define AML_UNASSIGNED              (u16) 0x02
DECL|macro|AML_ALIAS_OP
mdefine_line|#define AML_ALIAS_OP                (u16) 0x06
DECL|macro|AML_NAME_OP
mdefine_line|#define AML_NAME_OP                 (u16) 0x08
DECL|macro|AML_BYTE_OP
mdefine_line|#define AML_BYTE_OP                 (u16) 0x0a
DECL|macro|AML_WORD_OP
mdefine_line|#define AML_WORD_OP                 (u16) 0x0b
DECL|macro|AML_DWORD_OP
mdefine_line|#define AML_DWORD_OP                (u16) 0x0c
DECL|macro|AML_STRING_OP
mdefine_line|#define AML_STRING_OP               (u16) 0x0d
DECL|macro|AML_QWORD_OP
mdefine_line|#define AML_QWORD_OP                (u16) 0x0e     /* ACPI 2.0 */
DECL|macro|AML_SCOPE_OP
mdefine_line|#define AML_SCOPE_OP                (u16) 0x10
DECL|macro|AML_BUFFER_OP
mdefine_line|#define AML_BUFFER_OP               (u16) 0x11
DECL|macro|AML_PACKAGE_OP
mdefine_line|#define AML_PACKAGE_OP              (u16) 0x12
DECL|macro|AML_VAR_PACKAGE_OP
mdefine_line|#define AML_VAR_PACKAGE_OP          (u16) 0x13     /* ACPI 2.0 */
DECL|macro|AML_METHOD_OP
mdefine_line|#define AML_METHOD_OP               (u16) 0x14
DECL|macro|AML_DUAL_NAME_PREFIX
mdefine_line|#define AML_DUAL_NAME_PREFIX        (u16) 0x2e
DECL|macro|AML_MULTI_NAME_PREFIX_OP
mdefine_line|#define AML_MULTI_NAME_PREFIX_OP    (u16) 0x2f
DECL|macro|AML_NAME_CHAR_SUBSEQ
mdefine_line|#define AML_NAME_CHAR_SUBSEQ        (u16) 0x30
DECL|macro|AML_NAME_CHAR_FIRST
mdefine_line|#define AML_NAME_CHAR_FIRST         (u16) 0x41
DECL|macro|AML_OP_PREFIX
mdefine_line|#define AML_OP_PREFIX               (u16) 0x5b
DECL|macro|AML_ROOT_PREFIX
mdefine_line|#define AML_ROOT_PREFIX             (u16) 0x5c
DECL|macro|AML_PARENT_PREFIX
mdefine_line|#define AML_PARENT_PREFIX           (u16) 0x5e
DECL|macro|AML_LOCAL_OP
mdefine_line|#define AML_LOCAL_OP                (u16) 0x60
DECL|macro|AML_LOCAL0
mdefine_line|#define AML_LOCAL0                  (u16) 0x60
DECL|macro|AML_LOCAL1
mdefine_line|#define AML_LOCAL1                  (u16) 0x61
DECL|macro|AML_LOCAL2
mdefine_line|#define AML_LOCAL2                  (u16) 0x62
DECL|macro|AML_LOCAL3
mdefine_line|#define AML_LOCAL3                  (u16) 0x63
DECL|macro|AML_LOCAL4
mdefine_line|#define AML_LOCAL4                  (u16) 0x64
DECL|macro|AML_LOCAL5
mdefine_line|#define AML_LOCAL5                  (u16) 0x65
DECL|macro|AML_LOCAL6
mdefine_line|#define AML_LOCAL6                  (u16) 0x66
DECL|macro|AML_LOCAL7
mdefine_line|#define AML_LOCAL7                  (u16) 0x67
DECL|macro|AML_ARG_OP
mdefine_line|#define AML_ARG_OP                  (u16) 0x68
DECL|macro|AML_ARG0
mdefine_line|#define AML_ARG0                    (u16) 0x68
DECL|macro|AML_ARG1
mdefine_line|#define AML_ARG1                    (u16) 0x69
DECL|macro|AML_ARG2
mdefine_line|#define AML_ARG2                    (u16) 0x6a
DECL|macro|AML_ARG3
mdefine_line|#define AML_ARG3                    (u16) 0x6b
DECL|macro|AML_ARG4
mdefine_line|#define AML_ARG4                    (u16) 0x6c
DECL|macro|AML_ARG5
mdefine_line|#define AML_ARG5                    (u16) 0x6d
DECL|macro|AML_ARG6
mdefine_line|#define AML_ARG6                    (u16) 0x6e
DECL|macro|AML_STORE_OP
mdefine_line|#define AML_STORE_OP                (u16) 0x70
DECL|macro|AML_REF_OF_OP
mdefine_line|#define AML_REF_OF_OP               (u16) 0x71
DECL|macro|AML_ADD_OP
mdefine_line|#define AML_ADD_OP                  (u16) 0x72
DECL|macro|AML_CONCAT_OP
mdefine_line|#define AML_CONCAT_OP               (u16) 0x73
DECL|macro|AML_SUBTRACT_OP
mdefine_line|#define AML_SUBTRACT_OP             (u16) 0x74
DECL|macro|AML_INCREMENT_OP
mdefine_line|#define AML_INCREMENT_OP            (u16) 0x75
DECL|macro|AML_DECREMENT_OP
mdefine_line|#define AML_DECREMENT_OP            (u16) 0x76
DECL|macro|AML_MULTIPLY_OP
mdefine_line|#define AML_MULTIPLY_OP             (u16) 0x77
DECL|macro|AML_DIVIDE_OP
mdefine_line|#define AML_DIVIDE_OP               (u16) 0x78
DECL|macro|AML_SHIFT_LEFT_OP
mdefine_line|#define AML_SHIFT_LEFT_OP           (u16) 0x79
DECL|macro|AML_SHIFT_RIGHT_OP
mdefine_line|#define AML_SHIFT_RIGHT_OP          (u16) 0x7a
DECL|macro|AML_BIT_AND_OP
mdefine_line|#define AML_BIT_AND_OP              (u16) 0x7b
DECL|macro|AML_BIT_NAND_OP
mdefine_line|#define AML_BIT_NAND_OP             (u16) 0x7c
DECL|macro|AML_BIT_OR_OP
mdefine_line|#define AML_BIT_OR_OP               (u16) 0x7d
DECL|macro|AML_BIT_NOR_OP
mdefine_line|#define AML_BIT_NOR_OP              (u16) 0x7e
DECL|macro|AML_BIT_XOR_OP
mdefine_line|#define AML_BIT_XOR_OP              (u16) 0x7f
DECL|macro|AML_BIT_NOT_OP
mdefine_line|#define AML_BIT_NOT_OP              (u16) 0x80
DECL|macro|AML_FIND_SET_LEFT_BIT_OP
mdefine_line|#define AML_FIND_SET_LEFT_BIT_OP    (u16) 0x81
DECL|macro|AML_FIND_SET_RIGHT_BIT_OP
mdefine_line|#define AML_FIND_SET_RIGHT_BIT_OP   (u16) 0x82
DECL|macro|AML_DEREF_OF_OP
mdefine_line|#define AML_DEREF_OF_OP             (u16) 0x83
DECL|macro|AML_CONCAT_RES_OP
mdefine_line|#define AML_CONCAT_RES_OP           (u16) 0x84     /* ACPI 2.0 */
DECL|macro|AML_MOD_OP
mdefine_line|#define AML_MOD_OP                  (u16) 0x85     /* ACPI 2.0 */
DECL|macro|AML_NOTIFY_OP
mdefine_line|#define AML_NOTIFY_OP               (u16) 0x86
DECL|macro|AML_SIZE_OF_OP
mdefine_line|#define AML_SIZE_OF_OP              (u16) 0x87
DECL|macro|AML_INDEX_OP
mdefine_line|#define AML_INDEX_OP                (u16) 0x88
DECL|macro|AML_MATCH_OP
mdefine_line|#define AML_MATCH_OP                (u16) 0x89
DECL|macro|AML_CREATE_DWORD_FIELD_OP
mdefine_line|#define AML_CREATE_DWORD_FIELD_OP   (u16) 0x8a
DECL|macro|AML_CREATE_WORD_FIELD_OP
mdefine_line|#define AML_CREATE_WORD_FIELD_OP    (u16) 0x8b
DECL|macro|AML_CREATE_BYTE_FIELD_OP
mdefine_line|#define AML_CREATE_BYTE_FIELD_OP    (u16) 0x8c
DECL|macro|AML_CREATE_BIT_FIELD_OP
mdefine_line|#define AML_CREATE_BIT_FIELD_OP     (u16) 0x8d
DECL|macro|AML_TYPE_OP
mdefine_line|#define AML_TYPE_OP                 (u16) 0x8e
DECL|macro|AML_CREATE_QWORD_FIELD_OP
mdefine_line|#define AML_CREATE_QWORD_FIELD_OP   (u16) 0x8f     /* ACPI 2.0 */
DECL|macro|AML_LAND_OP
mdefine_line|#define AML_LAND_OP                 (u16) 0x90
DECL|macro|AML_LOR_OP
mdefine_line|#define AML_LOR_OP                  (u16) 0x91
DECL|macro|AML_LNOT_OP
mdefine_line|#define AML_LNOT_OP                 (u16) 0x92
DECL|macro|AML_LEQUAL_OP
mdefine_line|#define AML_LEQUAL_OP               (u16) 0x93
DECL|macro|AML_LGREATER_OP
mdefine_line|#define AML_LGREATER_OP             (u16) 0x94
DECL|macro|AML_LLESS_OP
mdefine_line|#define AML_LLESS_OP                (u16) 0x95
DECL|macro|AML_TO_BUFFER_OP
mdefine_line|#define AML_TO_BUFFER_OP            (u16) 0x96     /* ACPI 2.0 */
DECL|macro|AML_TO_DECSTRING_OP
mdefine_line|#define AML_TO_DECSTRING_OP         (u16) 0x97     /* ACPI 2.0 */
DECL|macro|AML_TO_HEXSTRING_OP
mdefine_line|#define AML_TO_HEXSTRING_OP         (u16) 0x98     /* ACPI 2.0 */
DECL|macro|AML_TO_INTEGER_OP
mdefine_line|#define AML_TO_INTEGER_OP           (u16) 0x99     /* ACPI 2.0 */
DECL|macro|AML_TO_STRING_OP
mdefine_line|#define AML_TO_STRING_OP            (u16) 0x9c     /* ACPI 2.0 */
DECL|macro|AML_COPY_OP
mdefine_line|#define AML_COPY_OP                 (u16) 0x9d     /* ACPI 2.0 */
DECL|macro|AML_MID_OP
mdefine_line|#define AML_MID_OP                  (u16) 0x9e     /* ACPI 2.0 */
DECL|macro|AML_CONTINUE_OP
mdefine_line|#define AML_CONTINUE_OP             (u16) 0x9f     /* ACPI 2.0 */
DECL|macro|AML_IF_OP
mdefine_line|#define AML_IF_OP                   (u16) 0xa0
DECL|macro|AML_ELSE_OP
mdefine_line|#define AML_ELSE_OP                 (u16) 0xa1
DECL|macro|AML_WHILE_OP
mdefine_line|#define AML_WHILE_OP                (u16) 0xa2
DECL|macro|AML_NOOP_OP
mdefine_line|#define AML_NOOP_OP                 (u16) 0xa3
DECL|macro|AML_RETURN_OP
mdefine_line|#define AML_RETURN_OP               (u16) 0xa4
DECL|macro|AML_BREAK_OP
mdefine_line|#define AML_BREAK_OP                (u16) 0xa5
DECL|macro|AML_BREAK_POINT_OP
mdefine_line|#define AML_BREAK_POINT_OP          (u16) 0xcc
DECL|macro|AML_ONES_OP
mdefine_line|#define AML_ONES_OP                 (u16) 0xff
multiline_comment|/* prefixed opcodes */
DECL|macro|AML_EXTOP
mdefine_line|#define AML_EXTOP                   (u16) 0x005b
DECL|macro|AML_MUTEX_OP
mdefine_line|#define AML_MUTEX_OP                (u16) 0x5b01
DECL|macro|AML_EVENT_OP
mdefine_line|#define AML_EVENT_OP                (u16) 0x5b02
DECL|macro|AML_SHIFT_RIGHT_BIT_OP
mdefine_line|#define AML_SHIFT_RIGHT_BIT_OP      (u16) 0x5b10
DECL|macro|AML_SHIFT_LEFT_BIT_OP
mdefine_line|#define AML_SHIFT_LEFT_BIT_OP       (u16) 0x5b11
DECL|macro|AML_COND_REF_OF_OP
mdefine_line|#define AML_COND_REF_OF_OP          (u16) 0x5b12
DECL|macro|AML_CREATE_FIELD_OP
mdefine_line|#define AML_CREATE_FIELD_OP         (u16) 0x5b13
DECL|macro|AML_LOAD_TABLE_OP
mdefine_line|#define AML_LOAD_TABLE_OP           (u16) 0x5b1f     /* ACPI 2.0 */
DECL|macro|AML_LOAD_OP
mdefine_line|#define AML_LOAD_OP                 (u16) 0x5b20
DECL|macro|AML_STALL_OP
mdefine_line|#define AML_STALL_OP                (u16) 0x5b21
DECL|macro|AML_SLEEP_OP
mdefine_line|#define AML_SLEEP_OP                (u16) 0x5b22
DECL|macro|AML_ACQUIRE_OP
mdefine_line|#define AML_ACQUIRE_OP              (u16) 0x5b23
DECL|macro|AML_SIGNAL_OP
mdefine_line|#define AML_SIGNAL_OP               (u16) 0x5b24
DECL|macro|AML_WAIT_OP
mdefine_line|#define AML_WAIT_OP                 (u16) 0x5b25
DECL|macro|AML_RESET_OP
mdefine_line|#define AML_RESET_OP                (u16) 0x5b26
DECL|macro|AML_RELEASE_OP
mdefine_line|#define AML_RELEASE_OP              (u16) 0x5b27
DECL|macro|AML_FROM_BCD_OP
mdefine_line|#define AML_FROM_BCD_OP             (u16) 0x5b28
DECL|macro|AML_TO_BCD_OP
mdefine_line|#define AML_TO_BCD_OP               (u16) 0x5b29
DECL|macro|AML_UNLOAD_OP
mdefine_line|#define AML_UNLOAD_OP               (u16) 0x5b2a
DECL|macro|AML_REVISION_OP
mdefine_line|#define AML_REVISION_OP             (u16) 0x5b30
DECL|macro|AML_DEBUG_OP
mdefine_line|#define AML_DEBUG_OP                (u16) 0x5b31
DECL|macro|AML_FATAL_OP
mdefine_line|#define AML_FATAL_OP                (u16) 0x5b32
DECL|macro|AML_REGION_OP
mdefine_line|#define AML_REGION_OP               (u16) 0x5b80
DECL|macro|AML_FIELD_OP
mdefine_line|#define AML_FIELD_OP                (u16) 0x5b81
DECL|macro|AML_DEVICE_OP
mdefine_line|#define AML_DEVICE_OP               (u16) 0x5b82
DECL|macro|AML_PROCESSOR_OP
mdefine_line|#define AML_PROCESSOR_OP            (u16) 0x5b83
DECL|macro|AML_POWER_RES_OP
mdefine_line|#define AML_POWER_RES_OP            (u16) 0x5b84
DECL|macro|AML_THERMAL_ZONE_OP
mdefine_line|#define AML_THERMAL_ZONE_OP         (u16) 0x5b85
DECL|macro|AML_INDEX_FIELD_OP
mdefine_line|#define AML_INDEX_FIELD_OP          (u16) 0x5b86
DECL|macro|AML_BANK_FIELD_OP
mdefine_line|#define AML_BANK_FIELD_OP           (u16) 0x5b87
DECL|macro|AML_DATA_REGION_OP
mdefine_line|#define AML_DATA_REGION_OP          (u16) 0x5b88     /* ACPI 2.0 */
multiline_comment|/* Bogus opcodes (they are actually two separate opcodes) */
DECL|macro|AML_LGREATEREQUAL_OP
mdefine_line|#define AML_LGREATEREQUAL_OP        (u16) 0x9295
DECL|macro|AML_LLESSEQUAL_OP
mdefine_line|#define AML_LLESSEQUAL_OP           (u16) 0x9294
DECL|macro|AML_LNOTEQUAL_OP
mdefine_line|#define AML_LNOTEQUAL_OP            (u16) 0x9293
multiline_comment|/*&n; * Internal opcodes&n; * Use only &quot;Unknown&quot; AML opcodes, don&squot;t attempt to use&n; * any valid ACPI ASCII values (A-Z, 0-9, &squot;-&squot;)&n; */
DECL|macro|AML_INT_NAMEPATH_OP
mdefine_line|#define AML_INT_NAMEPATH_OP         (u16) 0x002d
DECL|macro|AML_INT_NAMEDFIELD_OP
mdefine_line|#define AML_INT_NAMEDFIELD_OP       (u16) 0x0030
DECL|macro|AML_INT_RESERVEDFIELD_OP
mdefine_line|#define AML_INT_RESERVEDFIELD_OP    (u16) 0x0031
DECL|macro|AML_INT_ACCESSFIELD_OP
mdefine_line|#define AML_INT_ACCESSFIELD_OP      (u16) 0x0032
DECL|macro|AML_INT_BYTELIST_OP
mdefine_line|#define AML_INT_BYTELIST_OP         (u16) 0x0033
DECL|macro|AML_INT_STATICSTRING_OP
mdefine_line|#define AML_INT_STATICSTRING_OP     (u16) 0x0034
DECL|macro|AML_INT_METHODCALL_OP
mdefine_line|#define AML_INT_METHODCALL_OP       (u16) 0x0035
DECL|macro|AML_INT_RETURN_VALUE_OP
mdefine_line|#define AML_INT_RETURN_VALUE_OP     (u16) 0x0036
DECL|macro|ARG_NONE
mdefine_line|#define ARG_NONE                    0x0
multiline_comment|/*&n; * Argument types for the AML Parser&n; * Each field in the Arg_types u32 is 5 bits, allowing for a maximum of 6 arguments.&n; * There can be up to 31 unique argument types&n; */
DECL|macro|ARGP_BYTEDATA
mdefine_line|#define ARGP_BYTEDATA               0x01
DECL|macro|ARGP_BYTELIST
mdefine_line|#define ARGP_BYTELIST               0x02
DECL|macro|ARGP_CHARLIST
mdefine_line|#define ARGP_CHARLIST               0x03
DECL|macro|ARGP_DATAOBJ
mdefine_line|#define ARGP_DATAOBJ                0x04
DECL|macro|ARGP_DATAOBJLIST
mdefine_line|#define ARGP_DATAOBJLIST            0x05
DECL|macro|ARGP_DWORDDATA
mdefine_line|#define ARGP_DWORDDATA              0x06
DECL|macro|ARGP_FIELDLIST
mdefine_line|#define ARGP_FIELDLIST              0x07
DECL|macro|ARGP_NAME
mdefine_line|#define ARGP_NAME                   0x08
DECL|macro|ARGP_NAMESTRING
mdefine_line|#define ARGP_NAMESTRING             0x09
DECL|macro|ARGP_OBJLIST
mdefine_line|#define ARGP_OBJLIST                0x0A
DECL|macro|ARGP_PKGLENGTH
mdefine_line|#define ARGP_PKGLENGTH              0x0B
DECL|macro|ARGP_SUPERNAME
mdefine_line|#define ARGP_SUPERNAME              0x0C
DECL|macro|ARGP_TARGET
mdefine_line|#define ARGP_TARGET                 0x0D
DECL|macro|ARGP_TERMARG
mdefine_line|#define ARGP_TERMARG                0x0E
DECL|macro|ARGP_TERMLIST
mdefine_line|#define ARGP_TERMLIST               0x0F
DECL|macro|ARGP_WORDDATA
mdefine_line|#define ARGP_WORDDATA               0x10
DECL|macro|ARGP_QWORDDATA
mdefine_line|#define ARGP_QWORDDATA              0x11
DECL|macro|ARGP_SIMPLENAME
mdefine_line|#define ARGP_SIMPLENAME             0x12
multiline_comment|/*&n; * Resolved argument types for the AML Interpreter&n; * Each field in the Arg_types u32 is 5 bits, allowing for a maximum of 6 arguments.&n; * There can be up to 31 unique argument types (0 is end-of-arg-list indicator)&n; */
multiline_comment|/* &quot;Standard&quot; ACPI types are 1-15 (0x0F) */
DECL|macro|ARGI_INTEGER
mdefine_line|#define ARGI_INTEGER                ACPI_TYPE_INTEGER       /* 1 */
DECL|macro|ARGI_STRING
mdefine_line|#define ARGI_STRING                 ACPI_TYPE_STRING        /* 2 */
DECL|macro|ARGI_BUFFER
mdefine_line|#define ARGI_BUFFER                 ACPI_TYPE_BUFFER        /* 3 */
DECL|macro|ARGI_PACKAGE
mdefine_line|#define ARGI_PACKAGE                ACPI_TYPE_PACKAGE       /* 4 */
DECL|macro|ARGI_EVENT
mdefine_line|#define ARGI_EVENT                  ACPI_TYPE_EVENT
DECL|macro|ARGI_MUTEX
mdefine_line|#define ARGI_MUTEX                  ACPI_TYPE_MUTEX
DECL|macro|ARGI_REGION
mdefine_line|#define ARGI_REGION                 ACPI_TYPE_REGION
DECL|macro|ARGI_DDBHANDLE
mdefine_line|#define ARGI_DDBHANDLE              ACPI_TYPE_DDB_HANDLE
multiline_comment|/* Custom types are 0x10 through 0x1F */
DECL|macro|ARGI_IF
mdefine_line|#define ARGI_IF                     0x10
DECL|macro|ARGI_ANYOBJECT
mdefine_line|#define ARGI_ANYOBJECT              0x11
DECL|macro|ARGI_ANYTYPE
mdefine_line|#define ARGI_ANYTYPE                0x12
DECL|macro|ARGI_COMPUTEDATA
mdefine_line|#define ARGI_COMPUTEDATA            0x13     /* Buffer, String, or Integer */
DECL|macro|ARGI_DATAOBJECT
mdefine_line|#define ARGI_DATAOBJECT             0x14     /* Buffer, String, package or reference to a Node - Used only by Size_of operator*/
DECL|macro|ARGI_COMPLEXOBJ
mdefine_line|#define ARGI_COMPLEXOBJ             0x15     /* Buffer, String, or package (Used by INDEX op only) */
DECL|macro|ARGI_INTEGER_REF
mdefine_line|#define ARGI_INTEGER_REF            0x16
DECL|macro|ARGI_OBJECT_REF
mdefine_line|#define ARGI_OBJECT_REF             0x17
DECL|macro|ARGI_DEVICE_REF
mdefine_line|#define ARGI_DEVICE_REF             0x18
DECL|macro|ARGI_REFERENCE
mdefine_line|#define ARGI_REFERENCE              0x19
DECL|macro|ARGI_TARGETREF
mdefine_line|#define ARGI_TARGETREF              0x1A     /* Target, subject to implicit conversion */
DECL|macro|ARGI_FIXED_TARGET
mdefine_line|#define ARGI_FIXED_TARGET           0x1B     /* Target, no implicit conversion */
DECL|macro|ARGI_SIMPLE_TARGET
mdefine_line|#define ARGI_SIMPLE_TARGET          0x1C     /* Name, Local, Arg -- no implicit conversion */
DECL|macro|ARGI_BUFFERSTRING
mdefine_line|#define ARGI_BUFFERSTRING           0x1D
DECL|macro|ARGI_INVALID_OPCODE
mdefine_line|#define ARGI_INVALID_OPCODE         0xFFFFFFFF
multiline_comment|/*&n; * hash offsets&n; */
DECL|macro|AML_EXTOP_HASH_OFFSET
mdefine_line|#define AML_EXTOP_HASH_OFFSET       22
DECL|macro|AML_LNOT_HASH_OFFSET
mdefine_line|#define AML_LNOT_HASH_OFFSET        19
multiline_comment|/*&n; * opcode groups and types&n; */
DECL|macro|OPGRP_NAMED
mdefine_line|#define OPGRP_NAMED                 0x01
DECL|macro|OPGRP_FIELD
mdefine_line|#define OPGRP_FIELD                 0x02
DECL|macro|OPGRP_BYTELIST
mdefine_line|#define OPGRP_BYTELIST              0x04
DECL|macro|OPTYPE_UNDEFINED
mdefine_line|#define OPTYPE_UNDEFINED            0
DECL|macro|OPTYPE_LITERAL
mdefine_line|#define OPTYPE_LITERAL              1
DECL|macro|OPTYPE_CONSTANT
mdefine_line|#define OPTYPE_CONSTANT             2
DECL|macro|OPTYPE_METHOD_ARGUMENT
mdefine_line|#define OPTYPE_METHOD_ARGUMENT      3
DECL|macro|OPTYPE_LOCAL_VARIABLE
mdefine_line|#define OPTYPE_LOCAL_VARIABLE       4
DECL|macro|OPTYPE_DATA_TERM
mdefine_line|#define OPTYPE_DATA_TERM            5
multiline_comment|/* Type 1 opcodes */
DECL|macro|OPTYPE_MONADIC1
mdefine_line|#define OPTYPE_MONADIC1             6
DECL|macro|OPTYPE_DYADIC1
mdefine_line|#define OPTYPE_DYADIC1              7
multiline_comment|/* Type 2 opcodes */
DECL|macro|OPTYPE_MONADIC2
mdefine_line|#define OPTYPE_MONADIC2             8
DECL|macro|OPTYPE_MONADIC2_r
mdefine_line|#define OPTYPE_MONADIC2_r            9
DECL|macro|OPTYPE_DYADIC2
mdefine_line|#define OPTYPE_DYADIC2              10
DECL|macro|OPTYPE_DYADIC2_r
mdefine_line|#define OPTYPE_DYADIC2_r             11
DECL|macro|OPTYPE_DYADIC2_s
mdefine_line|#define OPTYPE_DYADIC2_s             12
DECL|macro|OPTYPE_INDEX
mdefine_line|#define OPTYPE_INDEX                13
DECL|macro|OPTYPE_MATCH
mdefine_line|#define OPTYPE_MATCH                14
multiline_comment|/* Generic for an op that returns a value */
DECL|macro|OPTYPE_METHOD_CALL
mdefine_line|#define OPTYPE_METHOD_CALL          15
multiline_comment|/* Misc */
DECL|macro|OPTYPE_CREATE_FIELD
mdefine_line|#define OPTYPE_CREATE_FIELD         16
DECL|macro|OPTYPE_FATAL
mdefine_line|#define OPTYPE_FATAL                17
DECL|macro|OPTYPE_CONTROL
mdefine_line|#define OPTYPE_CONTROL              18
DECL|macro|OPTYPE_RECONFIGURATION
mdefine_line|#define OPTYPE_RECONFIGURATION      19
DECL|macro|OPTYPE_NAMED_OBJECT
mdefine_line|#define OPTYPE_NAMED_OBJECT         20
DECL|macro|OPTYPE_RETURN
mdefine_line|#define OPTYPE_RETURN               21
DECL|macro|OPTYPE_BOGUS
mdefine_line|#define OPTYPE_BOGUS                22
multiline_comment|/* Predefined Operation Region Space_iDs */
r_typedef
r_enum
(brace
DECL|enumerator|REGION_MEMORY
id|REGION_MEMORY
op_assign
l_int|0
comma
DECL|enumerator|REGION_IO
id|REGION_IO
comma
DECL|enumerator|REGION_PCI_CONFIG
id|REGION_PCI_CONFIG
comma
DECL|enumerator|REGION_EC
id|REGION_EC
comma
DECL|enumerator|REGION_SMBUS
id|REGION_SMBUS
comma
DECL|enumerator|REGION_CMOS
id|REGION_CMOS
comma
DECL|enumerator|REGION_PCI_BAR
id|REGION_PCI_BAR
comma
DECL|enumerator|REGION_FIXED_HW
id|REGION_FIXED_HW
op_assign
l_int|0x7F
comma
DECL|typedef|AML_REGION_TYPES
)brace
id|AML_REGION_TYPES
suffix:semicolon
multiline_comment|/* Comparison operation codes for Match_op operator */
r_typedef
r_enum
(brace
DECL|enumerator|MATCH_MTR
id|MATCH_MTR
op_assign
l_int|0
comma
DECL|enumerator|MATCH_MEQ
id|MATCH_MEQ
op_assign
l_int|1
comma
DECL|enumerator|MATCH_MLE
id|MATCH_MLE
op_assign
l_int|2
comma
DECL|enumerator|MATCH_MLT
id|MATCH_MLT
op_assign
l_int|3
comma
DECL|enumerator|MATCH_MGE
id|MATCH_MGE
op_assign
l_int|4
comma
DECL|enumerator|MATCH_MGT
id|MATCH_MGT
op_assign
l_int|5
DECL|typedef|AML_MATCH_OPERATOR
)brace
id|AML_MATCH_OPERATOR
suffix:semicolon
DECL|macro|MAX_MATCH_OPERATOR
mdefine_line|#define MAX_MATCH_OPERATOR          5
multiline_comment|/* Field Access Types */
DECL|macro|ACCESS_TYPE_MASK
mdefine_line|#define ACCESS_TYPE_MASK            0x0f
DECL|macro|ACCESS_TYPE_SHIFT
mdefine_line|#define ACCESS_TYPE_SHIFT           0
r_typedef
r_enum
(brace
DECL|enumerator|ACCESS_ANY_ACC
id|ACCESS_ANY_ACC
op_assign
l_int|0
comma
DECL|enumerator|ACCESS_BYTE_ACC
id|ACCESS_BYTE_ACC
op_assign
l_int|1
comma
DECL|enumerator|ACCESS_WORD_ACC
id|ACCESS_WORD_ACC
op_assign
l_int|2
comma
DECL|enumerator|ACCESS_DWORD_ACC
id|ACCESS_DWORD_ACC
op_assign
l_int|3
comma
DECL|enumerator|ACCESS_QWORD_ACC
id|ACCESS_QWORD_ACC
op_assign
l_int|4
comma
multiline_comment|/* ACPI 2.0 */
DECL|enumerator|ACCESS_BLOCK_ACC
id|ACCESS_BLOCK_ACC
op_assign
l_int|4
comma
DECL|enumerator|ACCESS_SMBSEND_RECV_ACC
id|ACCESS_SMBSEND_RECV_ACC
op_assign
l_int|5
comma
DECL|enumerator|ACCESS_SMBQUICK_ACC
id|ACCESS_SMBQUICK_ACC
op_assign
l_int|6
DECL|typedef|AML_ACCESS_TYPE
)brace
id|AML_ACCESS_TYPE
suffix:semicolon
multiline_comment|/* Field Lock Rules */
DECL|macro|LOCK_RULE_MASK
mdefine_line|#define LOCK_RULE_MASK              0x10
DECL|macro|LOCK_RULE_SHIFT
mdefine_line|#define LOCK_RULE_SHIFT             4
r_typedef
r_enum
(brace
DECL|enumerator|GLOCK_NEVER_LOCK
id|GLOCK_NEVER_LOCK
op_assign
l_int|0
comma
DECL|enumerator|GLOCK_ALWAYS_LOCK
id|GLOCK_ALWAYS_LOCK
op_assign
l_int|1
DECL|typedef|AML_LOCK_RULE
)brace
id|AML_LOCK_RULE
suffix:semicolon
multiline_comment|/* Field Update Rules */
DECL|macro|UPDATE_RULE_MASK
mdefine_line|#define UPDATE_RULE_MASK            0x060
DECL|macro|UPDATE_RULE_SHIFT
mdefine_line|#define UPDATE_RULE_SHIFT           5
r_typedef
r_enum
(brace
DECL|enumerator|UPDATE_PRESERVE
id|UPDATE_PRESERVE
op_assign
l_int|0
comma
DECL|enumerator|UPDATE_WRITE_AS_ONES
id|UPDATE_WRITE_AS_ONES
op_assign
l_int|1
comma
DECL|enumerator|UPDATE_WRITE_AS_ZEROS
id|UPDATE_WRITE_AS_ZEROS
op_assign
l_int|2
DECL|typedef|AML_UPDATE_RULE
)brace
id|AML_UPDATE_RULE
suffix:semicolon
multiline_comment|/* bit fields in Method_flags byte */
DECL|macro|METHOD_FLAGS_ARG_COUNT
mdefine_line|#define METHOD_FLAGS_ARG_COUNT      0x07
DECL|macro|METHOD_FLAGS_SERIALIZED
mdefine_line|#define METHOD_FLAGS_SERIALIZED     0x08
DECL|macro|METHOD_FLAGS_SYNCH_LEVEL
mdefine_line|#define METHOD_FLAGS_SYNCH_LEVEL    0xF0
multiline_comment|/* Array sizes.  Used for range checking also */
DECL|macro|NUM_REGION_TYPES
mdefine_line|#define NUM_REGION_TYPES            7
DECL|macro|NUM_ACCESS_TYPES
mdefine_line|#define NUM_ACCESS_TYPES            7
DECL|macro|NUM_UPDATE_RULES
mdefine_line|#define NUM_UPDATE_RULES            3
DECL|macro|NUM_MATCH_OPS
mdefine_line|#define NUM_MATCH_OPS               7
DECL|macro|NUM_OPCODES
mdefine_line|#define NUM_OPCODES                 256
DECL|macro|NUM_FIELD_NAMES
mdefine_line|#define NUM_FIELD_NAMES             2
DECL|macro|USER_REGION_BEGIN
mdefine_line|#define USER_REGION_BEGIN           0x80
multiline_comment|/*&n; * AML tables&n; */
macro_line|#ifdef DEFINE_AML_GLOBALS
multiline_comment|/* External declarations for the AML tables */
r_extern
id|u8
id|acpi_gbl_aml
(braket
id|NUM_OPCODES
)braket
suffix:semicolon
r_extern
id|u16
id|acpi_gbl_pfx
(braket
id|NUM_OPCODES
)braket
suffix:semicolon
macro_line|#endif /* DEFINE_AML_GLOBALS */
macro_line|#endif /* __AMLCODE_H__ */
eof
