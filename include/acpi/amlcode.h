multiline_comment|/******************************************************************************&n; *&n; * Name: amlcode.h - Definitions for AML, as included in &quot;definition blocks&quot;&n; *                   Declarations and definitions contained herein are derived&n; *                   directly from the ACPI specification.&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
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
DECL|macro|AML_INT_EVAL_SUBTREE_OP
mdefine_line|#define AML_INT_EVAL_SUBTREE_OP     (u16) 0x0037
DECL|macro|ARG_NONE
mdefine_line|#define ARG_NONE                    0x0
multiline_comment|/*&n; * Argument types for the AML Parser&n; * Each field in the arg_types u32 is 5 bits, allowing for a maximum of 6 arguments.&n; * There can be up to 31 unique argument types&n; * Zero is reserved as end-of-list indicator&n; */
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
multiline_comment|/*&n; * Resolved argument types for the AML Interpreter&n; * Each field in the arg_types u32 is 5 bits, allowing for a maximum of 6 arguments.&n; * There can be up to 31 unique argument types (0 is end-of-arg-list indicator)&n; *&n; * Note1: These values are completely independent from the ACPI_TYPEs&n; *        i.e., ARGI_INTEGER != ACPI_TYPE_INTEGER&n; *&n; * Note2: If and when 5 bits becomes insufficient, it would probably be best&n; * to convert to a 6-byte array of argument types, allowing 8 bits per argument.&n; */
multiline_comment|/* Single, simple types */
DECL|macro|ARGI_ANYTYPE
mdefine_line|#define ARGI_ANYTYPE                0x01    /* Don&squot;t care */
DECL|macro|ARGI_PACKAGE
mdefine_line|#define ARGI_PACKAGE                0x02
DECL|macro|ARGI_EVENT
mdefine_line|#define ARGI_EVENT                  0x03
DECL|macro|ARGI_MUTEX
mdefine_line|#define ARGI_MUTEX                  0x04
DECL|macro|ARGI_DDBHANDLE
mdefine_line|#define ARGI_DDBHANDLE              0x05
multiline_comment|/* Interchangeable types (via implicit conversion) */
DECL|macro|ARGI_INTEGER
mdefine_line|#define ARGI_INTEGER                0x06
DECL|macro|ARGI_STRING
mdefine_line|#define ARGI_STRING                 0x07
DECL|macro|ARGI_BUFFER
mdefine_line|#define ARGI_BUFFER                 0x08
DECL|macro|ARGI_BUFFER_OR_STRING
mdefine_line|#define ARGI_BUFFER_OR_STRING       0x09    /* Used by MID op only */
DECL|macro|ARGI_COMPUTEDATA
mdefine_line|#define ARGI_COMPUTEDATA            0x0A    /* Buffer, String, or Integer */
multiline_comment|/* Reference objects */
DECL|macro|ARGI_INTEGER_REF
mdefine_line|#define ARGI_INTEGER_REF            0x0B
DECL|macro|ARGI_OBJECT_REF
mdefine_line|#define ARGI_OBJECT_REF             0x0C
DECL|macro|ARGI_DEVICE_REF
mdefine_line|#define ARGI_DEVICE_REF             0x0D
DECL|macro|ARGI_REFERENCE
mdefine_line|#define ARGI_REFERENCE              0x0E
DECL|macro|ARGI_TARGETREF
mdefine_line|#define ARGI_TARGETREF              0x0F    /* Target, subject to implicit conversion */
DECL|macro|ARGI_FIXED_TARGET
mdefine_line|#define ARGI_FIXED_TARGET           0x10    /* Target, no implicit conversion */
DECL|macro|ARGI_SIMPLE_TARGET
mdefine_line|#define ARGI_SIMPLE_TARGET          0x11    /* Name, Local, Arg -- no implicit conversion */
multiline_comment|/* Multiple/complex types */
DECL|macro|ARGI_DATAOBJECT
mdefine_line|#define ARGI_DATAOBJECT             0x12    /* Buffer, String, package or reference to a Node - Used only by size_of operator*/
DECL|macro|ARGI_COMPLEXOBJ
mdefine_line|#define ARGI_COMPLEXOBJ             0x13    /* Buffer, String, or package (Used by INDEX op only) */
DECL|macro|ARGI_REF_OR_STRING
mdefine_line|#define ARGI_REF_OR_STRING          0x14    /* Reference or String (Used by DEREFOF op only) */
DECL|macro|ARGI_REGION_OR_FIELD
mdefine_line|#define ARGI_REGION_OR_FIELD        0x15    /* Used by LOAD op only */
multiline_comment|/* Note: types above can expand to 0x1F maximum */
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
multiline_comment|/*&n; * Opcode information&n; */
multiline_comment|/* Opcode flags */
DECL|macro|AML_HAS_ARGS
mdefine_line|#define AML_HAS_ARGS                0x0800
DECL|macro|AML_HAS_TARGET
mdefine_line|#define AML_HAS_TARGET              0x0400
DECL|macro|AML_HAS_RETVAL
mdefine_line|#define AML_HAS_RETVAL              0x0200
DECL|macro|AML_NSOBJECT
mdefine_line|#define AML_NSOBJECT                0x0100
DECL|macro|AML_NSOPCODE
mdefine_line|#define AML_NSOPCODE                0x0080
DECL|macro|AML_NSNODE
mdefine_line|#define AML_NSNODE                  0x0040
DECL|macro|AML_NAMED
mdefine_line|#define AML_NAMED                   0x0020
DECL|macro|AML_DEFER
mdefine_line|#define AML_DEFER                   0x0010
DECL|macro|AML_FIELD
mdefine_line|#define AML_FIELD                   0x0008
DECL|macro|AML_CREATE
mdefine_line|#define AML_CREATE                  0x0004
DECL|macro|AML_MATH
mdefine_line|#define AML_MATH                    0x0002
DECL|macro|AML_LOGICAL
mdefine_line|#define AML_LOGICAL                 0x0001
DECL|macro|AML_CONSTANT
mdefine_line|#define AML_CONSTANT                0x1000
multiline_comment|/* Convenient flag groupings */
DECL|macro|AML_FLAGS_EXEC_1A_0T_0R
mdefine_line|#define AML_FLAGS_EXEC_1A_0T_0R     AML_HAS_ARGS                                   /* Monadic1  */
DECL|macro|AML_FLAGS_EXEC_1A_0T_1R
mdefine_line|#define AML_FLAGS_EXEC_1A_0T_1R     AML_HAS_ARGS |                  AML_HAS_RETVAL /* Monadic2  */
DECL|macro|AML_FLAGS_EXEC_1A_1T_0R
mdefine_line|#define AML_FLAGS_EXEC_1A_1T_0R     AML_HAS_ARGS | AML_HAS_TARGET
DECL|macro|AML_FLAGS_EXEC_1A_1T_1R
mdefine_line|#define AML_FLAGS_EXEC_1A_1T_1R     AML_HAS_ARGS | AML_HAS_TARGET | AML_HAS_RETVAL /* monadic2_r */
DECL|macro|AML_FLAGS_EXEC_2A_0T_0R
mdefine_line|#define AML_FLAGS_EXEC_2A_0T_0R     AML_HAS_ARGS                                   /* Dyadic1   */
DECL|macro|AML_FLAGS_EXEC_2A_0T_1R
mdefine_line|#define AML_FLAGS_EXEC_2A_0T_1R     AML_HAS_ARGS |                  AML_HAS_RETVAL /* Dyadic2   */
DECL|macro|AML_FLAGS_EXEC_2A_1T_1R
mdefine_line|#define AML_FLAGS_EXEC_2A_1T_1R     AML_HAS_ARGS | AML_HAS_TARGET | AML_HAS_RETVAL /* dyadic2_r  */
DECL|macro|AML_FLAGS_EXEC_2A_2T_1R
mdefine_line|#define AML_FLAGS_EXEC_2A_2T_1R     AML_HAS_ARGS | AML_HAS_TARGET | AML_HAS_RETVAL
DECL|macro|AML_FLAGS_EXEC_3A_0T_0R
mdefine_line|#define AML_FLAGS_EXEC_3A_0T_0R     AML_HAS_ARGS
DECL|macro|AML_FLAGS_EXEC_3A_1T_1R
mdefine_line|#define AML_FLAGS_EXEC_3A_1T_1R     AML_HAS_ARGS | AML_HAS_TARGET | AML_HAS_RETVAL
DECL|macro|AML_FLAGS_EXEC_6A_0T_1R
mdefine_line|#define AML_FLAGS_EXEC_6A_0T_1R     AML_HAS_ARGS |                  AML_HAS_RETVAL
multiline_comment|/*&n; * The opcode Type is used in a dispatch table, do not change&n; * without updating the table.&n; */
DECL|macro|AML_TYPE_EXEC_1A_0T_0R
mdefine_line|#define AML_TYPE_EXEC_1A_0T_0R      0x00 /* Monadic1  */
DECL|macro|AML_TYPE_EXEC_1A_0T_1R
mdefine_line|#define AML_TYPE_EXEC_1A_0T_1R      0x01 /* Monadic2  */
DECL|macro|AML_TYPE_EXEC_1A_1T_0R
mdefine_line|#define AML_TYPE_EXEC_1A_1T_0R      0x02
DECL|macro|AML_TYPE_EXEC_1A_1T_1R
mdefine_line|#define AML_TYPE_EXEC_1A_1T_1R      0x03 /* monadic2_r */
DECL|macro|AML_TYPE_EXEC_2A_0T_0R
mdefine_line|#define AML_TYPE_EXEC_2A_0T_0R      0x04 /* Dyadic1   */
DECL|macro|AML_TYPE_EXEC_2A_0T_1R
mdefine_line|#define AML_TYPE_EXEC_2A_0T_1R      0x05 /* Dyadic2   */
DECL|macro|AML_TYPE_EXEC_2A_1T_1R
mdefine_line|#define AML_TYPE_EXEC_2A_1T_1R      0x06 /* dyadic2_r  */
DECL|macro|AML_TYPE_EXEC_2A_2T_1R
mdefine_line|#define AML_TYPE_EXEC_2A_2T_1R      0x07
DECL|macro|AML_TYPE_EXEC_3A_0T_0R
mdefine_line|#define AML_TYPE_EXEC_3A_0T_0R      0x08
DECL|macro|AML_TYPE_EXEC_3A_1T_1R
mdefine_line|#define AML_TYPE_EXEC_3A_1T_1R      0x09
DECL|macro|AML_TYPE_EXEC_6A_0T_1R
mdefine_line|#define AML_TYPE_EXEC_6A_0T_1R      0x0A
multiline_comment|/* End of types used in dispatch table */
DECL|macro|AML_TYPE_LITERAL
mdefine_line|#define AML_TYPE_LITERAL            0x0B
DECL|macro|AML_TYPE_CONSTANT
mdefine_line|#define AML_TYPE_CONSTANT           0x0C
DECL|macro|AML_TYPE_METHOD_ARGUMENT
mdefine_line|#define AML_TYPE_METHOD_ARGUMENT    0x0D
DECL|macro|AML_TYPE_LOCAL_VARIABLE
mdefine_line|#define AML_TYPE_LOCAL_VARIABLE     0x0E
DECL|macro|AML_TYPE_DATA_TERM
mdefine_line|#define AML_TYPE_DATA_TERM          0x0F
multiline_comment|/* Generic for an op that returns a value */
DECL|macro|AML_TYPE_METHOD_CALL
mdefine_line|#define AML_TYPE_METHOD_CALL        0x10
multiline_comment|/* Misc */
DECL|macro|AML_TYPE_CREATE_FIELD
mdefine_line|#define AML_TYPE_CREATE_FIELD       0x11
DECL|macro|AML_TYPE_CREATE_OBJECT
mdefine_line|#define AML_TYPE_CREATE_OBJECT      0x12
DECL|macro|AML_TYPE_CONTROL
mdefine_line|#define AML_TYPE_CONTROL            0x13
DECL|macro|AML_TYPE_NAMED_NO_OBJ
mdefine_line|#define AML_TYPE_NAMED_NO_OBJ       0x14
DECL|macro|AML_TYPE_NAMED_FIELD
mdefine_line|#define AML_TYPE_NAMED_FIELD        0x15
DECL|macro|AML_TYPE_NAMED_SIMPLE
mdefine_line|#define AML_TYPE_NAMED_SIMPLE       0x16
DECL|macro|AML_TYPE_NAMED_COMPLEX
mdefine_line|#define AML_TYPE_NAMED_COMPLEX      0x17
DECL|macro|AML_TYPE_RETURN
mdefine_line|#define AML_TYPE_RETURN             0x18
DECL|macro|AML_TYPE_UNDEFINED
mdefine_line|#define AML_TYPE_UNDEFINED          0x19
DECL|macro|AML_TYPE_BOGUS
mdefine_line|#define AML_TYPE_BOGUS              0x1A
multiline_comment|/*&n; * Opcode classes&n; */
DECL|macro|AML_CLASS_EXECUTE
mdefine_line|#define AML_CLASS_EXECUTE           0x00
DECL|macro|AML_CLASS_CREATE
mdefine_line|#define AML_CLASS_CREATE            0x01
DECL|macro|AML_CLASS_ARGUMENT
mdefine_line|#define AML_CLASS_ARGUMENT          0x02
DECL|macro|AML_CLASS_NAMED_OBJECT
mdefine_line|#define AML_CLASS_NAMED_OBJECT      0x03
DECL|macro|AML_CLASS_CONTROL
mdefine_line|#define AML_CLASS_CONTROL           0x04
DECL|macro|AML_CLASS_ASCII
mdefine_line|#define AML_CLASS_ASCII             0x05
DECL|macro|AML_CLASS_PREFIX
mdefine_line|#define AML_CLASS_PREFIX            0x06
DECL|macro|AML_CLASS_INTERNAL
mdefine_line|#define AML_CLASS_INTERNAL          0x07
DECL|macro|AML_CLASS_RETURN_VALUE
mdefine_line|#define AML_CLASS_RETURN_VALUE      0x08
DECL|macro|AML_CLASS_METHOD_CALL
mdefine_line|#define AML_CLASS_METHOD_CALL       0x09
DECL|macro|AML_CLASS_UNKNOWN
mdefine_line|#define AML_CLASS_UNKNOWN           0x0A
multiline_comment|/* Predefined Operation Region space_iDs */
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
DECL|enumerator|REGION_DATA_TABLE
id|REGION_DATA_TABLE
comma
multiline_comment|/* Internal use only */
DECL|enumerator|REGION_FIXED_HW
id|REGION_FIXED_HW
op_assign
l_int|0x7F
DECL|typedef|AML_REGION_TYPES
)brace
id|AML_REGION_TYPES
suffix:semicolon
multiline_comment|/* Comparison operation codes for match_op operator */
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
multiline_comment|/*&n; * field_flags&n; *&n; * This byte is extracted from the AML and includes three separate&n; * pieces of information about the field:&n; * 1) The field access type&n; * 2) The field update rule&n; * 3) The lock rule for the field&n; *&n; * Bits 00 - 03 : access_type (any_acc, byte_acc, etc.)&n; *      04      : lock_rule (1 == Lock)&n; *      05 - 06 : update_rule&n; */
DECL|macro|AML_FIELD_ACCESS_TYPE_MASK
mdefine_line|#define AML_FIELD_ACCESS_TYPE_MASK  0x0F
DECL|macro|AML_FIELD_LOCK_RULE_MASK
mdefine_line|#define AML_FIELD_LOCK_RULE_MASK    0x10
DECL|macro|AML_FIELD_UPDATE_RULE_MASK
mdefine_line|#define AML_FIELD_UPDATE_RULE_MASK  0x60
multiline_comment|/* 1) Field Access Types */
r_typedef
r_enum
(brace
DECL|enumerator|AML_FIELD_ACCESS_ANY
id|AML_FIELD_ACCESS_ANY
op_assign
l_int|0x00
comma
DECL|enumerator|AML_FIELD_ACCESS_BYTE
id|AML_FIELD_ACCESS_BYTE
op_assign
l_int|0x01
comma
DECL|enumerator|AML_FIELD_ACCESS_WORD
id|AML_FIELD_ACCESS_WORD
op_assign
l_int|0x02
comma
DECL|enumerator|AML_FIELD_ACCESS_DWORD
id|AML_FIELD_ACCESS_DWORD
op_assign
l_int|0x03
comma
DECL|enumerator|AML_FIELD_ACCESS_QWORD
id|AML_FIELD_ACCESS_QWORD
op_assign
l_int|0x04
comma
multiline_comment|/* ACPI 2.0 */
DECL|enumerator|AML_FIELD_ACCESS_BUFFER
id|AML_FIELD_ACCESS_BUFFER
op_assign
l_int|0x05
multiline_comment|/* ACPI 2.0 */
DECL|typedef|AML_ACCESS_TYPE
)brace
id|AML_ACCESS_TYPE
suffix:semicolon
multiline_comment|/* 2) Field Lock Rules */
r_typedef
r_enum
(brace
DECL|enumerator|AML_FIELD_LOCK_NEVER
id|AML_FIELD_LOCK_NEVER
op_assign
l_int|0x00
comma
DECL|enumerator|AML_FIELD_LOCK_ALWAYS
id|AML_FIELD_LOCK_ALWAYS
op_assign
l_int|0x10
DECL|typedef|AML_LOCK_RULE
)brace
id|AML_LOCK_RULE
suffix:semicolon
multiline_comment|/* 3) Field Update Rules */
r_typedef
r_enum
(brace
DECL|enumerator|AML_FIELD_UPDATE_PRESERVE
id|AML_FIELD_UPDATE_PRESERVE
op_assign
l_int|0x00
comma
DECL|enumerator|AML_FIELD_UPDATE_WRITE_AS_ONES
id|AML_FIELD_UPDATE_WRITE_AS_ONES
op_assign
l_int|0x20
comma
DECL|enumerator|AML_FIELD_UPDATE_WRITE_AS_ZEROS
id|AML_FIELD_UPDATE_WRITE_AS_ZEROS
op_assign
l_int|0x40
DECL|typedef|AML_UPDATE_RULE
)brace
id|AML_UPDATE_RULE
suffix:semicolon
multiline_comment|/*&n; * Field Access Attributes.&n; * This byte is extracted from the AML via the&n; * access_as keyword&n; */
r_typedef
r_enum
(brace
DECL|enumerator|AML_FIELD_ATTRIB_SMB_QUICK
id|AML_FIELD_ATTRIB_SMB_QUICK
op_assign
l_int|0x02
comma
DECL|enumerator|AML_FIELD_ATTRIB_SMB_SEND_RCV
id|AML_FIELD_ATTRIB_SMB_SEND_RCV
op_assign
l_int|0x04
comma
DECL|enumerator|AML_FIELD_ATTRIB_SMB_BYTE
id|AML_FIELD_ATTRIB_SMB_BYTE
op_assign
l_int|0x06
comma
DECL|enumerator|AML_FIELD_ATTRIB_SMB_WORD
id|AML_FIELD_ATTRIB_SMB_WORD
op_assign
l_int|0x08
comma
DECL|enumerator|AML_FIELD_ATTRIB_SMB_BLOCK
id|AML_FIELD_ATTRIB_SMB_BLOCK
op_assign
l_int|0x0A
comma
DECL|enumerator|AML_FIELD_ATTRIB_SMB_WORD_CALL
id|AML_FIELD_ATTRIB_SMB_WORD_CALL
op_assign
l_int|0x0C
comma
DECL|enumerator|AML_FIELD_ATTRIB_SMB_BLOCK_CALL
id|AML_FIELD_ATTRIB_SMB_BLOCK_CALL
op_assign
l_int|0x0D
DECL|typedef|AML_ACCESS_ATTRIBUTE
)brace
id|AML_ACCESS_ATTRIBUTE
suffix:semicolon
multiline_comment|/* Bit fields in method_flags byte */
DECL|macro|AML_METHOD_ARG_COUNT
mdefine_line|#define AML_METHOD_ARG_COUNT        0x07
DECL|macro|AML_METHOD_SERIALIZED
mdefine_line|#define AML_METHOD_SERIALIZED       0x08
DECL|macro|AML_METHOD_SYNCH_LEVEL
mdefine_line|#define AML_METHOD_SYNCH_LEVEL      0xF0
multiline_comment|/* METHOD_FLAGS_ARG_COUNT is not used internally, define additional flags */
DECL|macro|AML_METHOD_INTERNAL_ONLY
mdefine_line|#define AML_METHOD_INTERNAL_ONLY    0x01
DECL|macro|AML_METHOD_RESERVED1
mdefine_line|#define AML_METHOD_RESERVED1        0x02
DECL|macro|AML_METHOD_RESERVED2
mdefine_line|#define AML_METHOD_RESERVED2        0x04
macro_line|#endif /* __AMLCODE_H__ */
eof
