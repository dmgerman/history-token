multiline_comment|/******************************************************************************&n; *&n; * Name: acexcep.h - Exception codes returned by the ACPI subsystem&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#ifndef __ACEXCEP_H__
DECL|macro|__ACEXCEP_H__
mdefine_line|#define __ACEXCEP_H__
multiline_comment|/*&n; * Exceptions returned by external ACPI interfaces&n; */
DECL|macro|AE_CODE_ENVIRONMENTAL
mdefine_line|#define AE_CODE_ENVIRONMENTAL           0x0000
DECL|macro|AE_CODE_PROGRAMMER
mdefine_line|#define AE_CODE_PROGRAMMER              0x1000
DECL|macro|AE_CODE_ACPI_TABLES
mdefine_line|#define AE_CODE_ACPI_TABLES             0x2000
DECL|macro|AE_CODE_AML
mdefine_line|#define AE_CODE_AML                     0x3000
DECL|macro|AE_CODE_CONTROL
mdefine_line|#define AE_CODE_CONTROL                 0x4000
DECL|macro|AE_CODE_MASK
mdefine_line|#define AE_CODE_MASK                    0xF000
DECL|macro|ACPI_SUCCESS
mdefine_line|#define ACPI_SUCCESS(a)                 (!(a))
DECL|macro|ACPI_FAILURE
mdefine_line|#define ACPI_FAILURE(a)                 (a)
DECL|macro|AE_OK
mdefine_line|#define AE_OK                           (acpi_status) 0x0000
multiline_comment|/*&n; * Environmental exceptions&n; */
DECL|macro|AE_ERROR
mdefine_line|#define AE_ERROR                        (acpi_status) (0x0001 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NO_ACPI_TABLES
mdefine_line|#define AE_NO_ACPI_TABLES               (acpi_status) (0x0002 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NO_NAMESPACE
mdefine_line|#define AE_NO_NAMESPACE                 (acpi_status) (0x0003 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NO_MEMORY
mdefine_line|#define AE_NO_MEMORY                    (acpi_status) (0x0004 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NOT_FOUND
mdefine_line|#define AE_NOT_FOUND                    (acpi_status) (0x0005 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NOT_EXIST
mdefine_line|#define AE_NOT_EXIST                    (acpi_status) (0x0006 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_ALREADY_EXISTS
mdefine_line|#define AE_ALREADY_EXISTS               (acpi_status) (0x0007 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_TYPE
mdefine_line|#define AE_TYPE                         (acpi_status) (0x0008 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NULL_OBJECT
mdefine_line|#define AE_NULL_OBJECT                  (acpi_status) (0x0009 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NULL_ENTRY
mdefine_line|#define AE_NULL_ENTRY                   (acpi_status) (0x000A | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_BUFFER_OVERFLOW
mdefine_line|#define AE_BUFFER_OVERFLOW              (acpi_status) (0x000B | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_STACK_OVERFLOW
mdefine_line|#define AE_STACK_OVERFLOW               (acpi_status) (0x000C | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_STACK_UNDERFLOW
mdefine_line|#define AE_STACK_UNDERFLOW              (acpi_status) (0x000D | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NOT_IMPLEMENTED
mdefine_line|#define AE_NOT_IMPLEMENTED              (acpi_status) (0x000E | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_VERSION_MISMATCH
mdefine_line|#define AE_VERSION_MISMATCH             (acpi_status) (0x000F | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_SUPPORT
mdefine_line|#define AE_SUPPORT                      (acpi_status) (0x0010 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_SHARE
mdefine_line|#define AE_SHARE                        (acpi_status) (0x0011 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_LIMIT
mdefine_line|#define AE_LIMIT                        (acpi_status) (0x0012 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_TIME
mdefine_line|#define AE_TIME                         (acpi_status) (0x0013 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_UNKNOWN_STATUS
mdefine_line|#define AE_UNKNOWN_STATUS               (acpi_status) (0x0014 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_ACQUIRE_DEADLOCK
mdefine_line|#define AE_ACQUIRE_DEADLOCK             (acpi_status) (0x0015 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_RELEASE_DEADLOCK
mdefine_line|#define AE_RELEASE_DEADLOCK             (acpi_status) (0x0016 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NOT_ACQUIRED
mdefine_line|#define AE_NOT_ACQUIRED                 (acpi_status) (0x0017 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_ALREADY_ACQUIRED
mdefine_line|#define AE_ALREADY_ACQUIRED             (acpi_status) (0x0018 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NO_HARDWARE_RESPONSE
mdefine_line|#define AE_NO_HARDWARE_RESPONSE         (acpi_status) (0x0019 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NO_GLOBAL_LOCK
mdefine_line|#define AE_NO_GLOBAL_LOCK               (acpi_status) (0x001A | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_LOGICAL_ADDRESS
mdefine_line|#define AE_LOGICAL_ADDRESS              (acpi_status) (0x001B | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_ABORT_METHOD
mdefine_line|#define AE_ABORT_METHOD                 (acpi_status) (0x001C | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_CODE_ENV_MAX
mdefine_line|#define AE_CODE_ENV_MAX                 0x001C
multiline_comment|/*&n; * Programmer exceptions&n; */
DECL|macro|AE_BAD_PARAMETER
mdefine_line|#define AE_BAD_PARAMETER                (acpi_status) (0x0001 | AE_CODE_PROGRAMMER)
DECL|macro|AE_BAD_CHARACTER
mdefine_line|#define AE_BAD_CHARACTER                (acpi_status) (0x0002 | AE_CODE_PROGRAMMER)
DECL|macro|AE_BAD_PATHNAME
mdefine_line|#define AE_BAD_PATHNAME                 (acpi_status) (0x0003 | AE_CODE_PROGRAMMER)
DECL|macro|AE_BAD_DATA
mdefine_line|#define AE_BAD_DATA                     (acpi_status) (0x0004 | AE_CODE_PROGRAMMER)
DECL|macro|AE_BAD_ADDRESS
mdefine_line|#define AE_BAD_ADDRESS                  (acpi_status) (0x0005 | AE_CODE_PROGRAMMER)
DECL|macro|AE_ALIGNMENT
mdefine_line|#define AE_ALIGNMENT                    (acpi_status) (0x0006 | AE_CODE_PROGRAMMER)
DECL|macro|AE_BAD_HEX_CONSTANT
mdefine_line|#define AE_BAD_HEX_CONSTANT             (acpi_status) (0x0007 | AE_CODE_PROGRAMMER)
DECL|macro|AE_BAD_OCTAL_CONSTANT
mdefine_line|#define AE_BAD_OCTAL_CONSTANT           (acpi_status) (0x0008 | AE_CODE_PROGRAMMER)
DECL|macro|AE_BAD_DECIMAL_CONSTANT
mdefine_line|#define AE_BAD_DECIMAL_CONSTANT         (acpi_status) (0x0009 | AE_CODE_PROGRAMMER)
DECL|macro|AE_CODE_PGM_MAX
mdefine_line|#define AE_CODE_PGM_MAX                 0x0009
multiline_comment|/*&n; * Acpi table exceptions&n; */
DECL|macro|AE_BAD_SIGNATURE
mdefine_line|#define AE_BAD_SIGNATURE                (acpi_status) (0x0001 | AE_CODE_ACPI_TABLES)
DECL|macro|AE_BAD_HEADER
mdefine_line|#define AE_BAD_HEADER                   (acpi_status) (0x0002 | AE_CODE_ACPI_TABLES)
DECL|macro|AE_BAD_CHECKSUM
mdefine_line|#define AE_BAD_CHECKSUM                 (acpi_status) (0x0003 | AE_CODE_ACPI_TABLES)
DECL|macro|AE_BAD_VALUE
mdefine_line|#define AE_BAD_VALUE                    (acpi_status) (0x0004 | AE_CODE_ACPI_TABLES)
DECL|macro|AE_TABLE_NOT_SUPPORTED
mdefine_line|#define AE_TABLE_NOT_SUPPORTED          (acpi_status) (0x0005 | AE_CODE_ACPI_TABLES)
DECL|macro|AE_INVALID_TABLE_LENGTH
mdefine_line|#define AE_INVALID_TABLE_LENGTH         (acpi_status) (0x0006 | AE_CODE_ACPI_TABLES)
DECL|macro|AE_CODE_TBL_MAX
mdefine_line|#define AE_CODE_TBL_MAX                 0x0006
multiline_comment|/*&n; * AML exceptions.  These are caused by problems with&n; * the actual AML byte stream&n; */
DECL|macro|AE_AML_ERROR
mdefine_line|#define AE_AML_ERROR                    (acpi_status) (0x0001 | AE_CODE_AML)
DECL|macro|AE_AML_PARSE
mdefine_line|#define AE_AML_PARSE                    (acpi_status) (0x0002 | AE_CODE_AML)
DECL|macro|AE_AML_BAD_OPCODE
mdefine_line|#define AE_AML_BAD_OPCODE               (acpi_status) (0x0003 | AE_CODE_AML)
DECL|macro|AE_AML_NO_OPERAND
mdefine_line|#define AE_AML_NO_OPERAND               (acpi_status) (0x0004 | AE_CODE_AML)
DECL|macro|AE_AML_OPERAND_TYPE
mdefine_line|#define AE_AML_OPERAND_TYPE             (acpi_status) (0x0005 | AE_CODE_AML)
DECL|macro|AE_AML_OPERAND_VALUE
mdefine_line|#define AE_AML_OPERAND_VALUE            (acpi_status) (0x0006 | AE_CODE_AML)
DECL|macro|AE_AML_UNINITIALIZED_LOCAL
mdefine_line|#define AE_AML_UNINITIALIZED_LOCAL      (acpi_status) (0x0007 | AE_CODE_AML)
DECL|macro|AE_AML_UNINITIALIZED_ARG
mdefine_line|#define AE_AML_UNINITIALIZED_ARG        (acpi_status) (0x0008 | AE_CODE_AML)
DECL|macro|AE_AML_UNINITIALIZED_ELEMENT
mdefine_line|#define AE_AML_UNINITIALIZED_ELEMENT    (acpi_status) (0x0009 | AE_CODE_AML)
DECL|macro|AE_AML_NUMERIC_OVERFLOW
mdefine_line|#define AE_AML_NUMERIC_OVERFLOW         (acpi_status) (0x000A | AE_CODE_AML)
DECL|macro|AE_AML_REGION_LIMIT
mdefine_line|#define AE_AML_REGION_LIMIT             (acpi_status) (0x000B | AE_CODE_AML)
DECL|macro|AE_AML_BUFFER_LIMIT
mdefine_line|#define AE_AML_BUFFER_LIMIT             (acpi_status) (0x000C | AE_CODE_AML)
DECL|macro|AE_AML_PACKAGE_LIMIT
mdefine_line|#define AE_AML_PACKAGE_LIMIT            (acpi_status) (0x000D | AE_CODE_AML)
DECL|macro|AE_AML_DIVIDE_BY_ZERO
mdefine_line|#define AE_AML_DIVIDE_BY_ZERO           (acpi_status) (0x000E | AE_CODE_AML)
DECL|macro|AE_AML_BAD_NAME
mdefine_line|#define AE_AML_BAD_NAME                 (acpi_status) (0x000F | AE_CODE_AML)
DECL|macro|AE_AML_NAME_NOT_FOUND
mdefine_line|#define AE_AML_NAME_NOT_FOUND           (acpi_status) (0x0010 | AE_CODE_AML)
DECL|macro|AE_AML_INTERNAL
mdefine_line|#define AE_AML_INTERNAL                 (acpi_status) (0x0011 | AE_CODE_AML)
DECL|macro|AE_AML_INVALID_SPACE_ID
mdefine_line|#define AE_AML_INVALID_SPACE_ID         (acpi_status) (0x0012 | AE_CODE_AML)
DECL|macro|AE_AML_STRING_LIMIT
mdefine_line|#define AE_AML_STRING_LIMIT             (acpi_status) (0x0013 | AE_CODE_AML)
DECL|macro|AE_AML_NO_RETURN_VALUE
mdefine_line|#define AE_AML_NO_RETURN_VALUE          (acpi_status) (0x0014 | AE_CODE_AML)
DECL|macro|AE_AML_METHOD_LIMIT
mdefine_line|#define AE_AML_METHOD_LIMIT             (acpi_status) (0x0015 | AE_CODE_AML)
DECL|macro|AE_AML_NOT_OWNER
mdefine_line|#define AE_AML_NOT_OWNER                (acpi_status) (0x0016 | AE_CODE_AML)
DECL|macro|AE_AML_MUTEX_ORDER
mdefine_line|#define AE_AML_MUTEX_ORDER              (acpi_status) (0x0017 | AE_CODE_AML)
DECL|macro|AE_AML_MUTEX_NOT_ACQUIRED
mdefine_line|#define AE_AML_MUTEX_NOT_ACQUIRED       (acpi_status) (0x0018 | AE_CODE_AML)
DECL|macro|AE_AML_INVALID_RESOURCE_TYPE
mdefine_line|#define AE_AML_INVALID_RESOURCE_TYPE    (acpi_status) (0x0019 | AE_CODE_AML)
DECL|macro|AE_AML_INVALID_INDEX
mdefine_line|#define AE_AML_INVALID_INDEX            (acpi_status) (0x001A | AE_CODE_AML)
DECL|macro|AE_AML_REGISTER_LIMIT
mdefine_line|#define AE_AML_REGISTER_LIMIT           (acpi_status) (0x001B | AE_CODE_AML)
DECL|macro|AE_AML_NO_WHILE
mdefine_line|#define AE_AML_NO_WHILE                 (acpi_status) (0x001C | AE_CODE_AML)
DECL|macro|AE_AML_ALIGNMENT
mdefine_line|#define AE_AML_ALIGNMENT                (acpi_status) (0x001D | AE_CODE_AML)
DECL|macro|AE_AML_NO_RESOURCE_END_TAG
mdefine_line|#define AE_AML_NO_RESOURCE_END_TAG      (acpi_status) (0x001E | AE_CODE_AML)
DECL|macro|AE_AML_BAD_RESOURCE_VALUE
mdefine_line|#define AE_AML_BAD_RESOURCE_VALUE       (acpi_status) (0x001F | AE_CODE_AML)
DECL|macro|AE_AML_CIRCULAR_REFERENCE
mdefine_line|#define AE_AML_CIRCULAR_REFERENCE       (acpi_status) (0x0020 | AE_CODE_AML)
DECL|macro|AE_CODE_AML_MAX
mdefine_line|#define AE_CODE_AML_MAX                 0x0020
multiline_comment|/*&n; * Internal exceptions used for control&n; */
DECL|macro|AE_CTRL_RETURN_VALUE
mdefine_line|#define AE_CTRL_RETURN_VALUE            (acpi_status) (0x0001 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_PENDING
mdefine_line|#define AE_CTRL_PENDING                 (acpi_status) (0x0002 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_TERMINATE
mdefine_line|#define AE_CTRL_TERMINATE               (acpi_status) (0x0003 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_TRUE
mdefine_line|#define AE_CTRL_TRUE                    (acpi_status) (0x0004 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_FALSE
mdefine_line|#define AE_CTRL_FALSE                   (acpi_status) (0x0005 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_DEPTH
mdefine_line|#define AE_CTRL_DEPTH                   (acpi_status) (0x0006 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_END
mdefine_line|#define AE_CTRL_END                     (acpi_status) (0x0007 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_TRANSFER
mdefine_line|#define AE_CTRL_TRANSFER                (acpi_status) (0x0008 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_BREAK
mdefine_line|#define AE_CTRL_BREAK                   (acpi_status) (0x0009 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_CONTINUE
mdefine_line|#define AE_CTRL_CONTINUE                (acpi_status) (0x000A | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_SKIP
mdefine_line|#define AE_CTRL_SKIP                    (acpi_status) (0x000B | AE_CODE_CONTROL)
DECL|macro|AE_CODE_CTRL_MAX
mdefine_line|#define AE_CODE_CTRL_MAX                0x000B
macro_line|#ifdef DEFINE_ACPI_GLOBALS
multiline_comment|/*&n; * String versions of the exception codes above&n; * These strings must match the corresponding defines exactly&n; */
DECL|variable|acpi_gbl_exception_names_env
r_char
r_const
op_star
id|acpi_gbl_exception_names_env
(braket
)braket
op_assign
(brace
l_string|&quot;AE_OK&quot;
comma
l_string|&quot;AE_ERROR&quot;
comma
l_string|&quot;AE_NO_ACPI_TABLES&quot;
comma
l_string|&quot;AE_NO_NAMESPACE&quot;
comma
l_string|&quot;AE_NO_MEMORY&quot;
comma
l_string|&quot;AE_NOT_FOUND&quot;
comma
l_string|&quot;AE_NOT_EXIST&quot;
comma
l_string|&quot;AE_ALREADY_EXISTS&quot;
comma
l_string|&quot;AE_TYPE&quot;
comma
l_string|&quot;AE_NULL_OBJECT&quot;
comma
l_string|&quot;AE_NULL_ENTRY&quot;
comma
l_string|&quot;AE_BUFFER_OVERFLOW&quot;
comma
l_string|&quot;AE_STACK_OVERFLOW&quot;
comma
l_string|&quot;AE_STACK_UNDERFLOW&quot;
comma
l_string|&quot;AE_NOT_IMPLEMENTED&quot;
comma
l_string|&quot;AE_VERSION_MISMATCH&quot;
comma
l_string|&quot;AE_SUPPORT&quot;
comma
l_string|&quot;AE_SHARE&quot;
comma
l_string|&quot;AE_LIMIT&quot;
comma
l_string|&quot;AE_TIME&quot;
comma
l_string|&quot;AE_UNKNOWN_STATUS&quot;
comma
l_string|&quot;AE_ACQUIRE_DEADLOCK&quot;
comma
l_string|&quot;AE_RELEASE_DEADLOCK&quot;
comma
l_string|&quot;AE_NOT_ACQUIRED&quot;
comma
l_string|&quot;AE_ALREADY_ACQUIRED&quot;
comma
l_string|&quot;AE_NO_HARDWARE_RESPONSE&quot;
comma
l_string|&quot;AE_NO_GLOBAL_LOCK&quot;
comma
l_string|&quot;AE_LOGICAL_ADDRESS&quot;
comma
l_string|&quot;AE_ABORT_METHOD&quot;
)brace
suffix:semicolon
DECL|variable|acpi_gbl_exception_names_pgm
r_char
r_const
op_star
id|acpi_gbl_exception_names_pgm
(braket
)braket
op_assign
(brace
l_string|&quot;AE_BAD_PARAMETER&quot;
comma
l_string|&quot;AE_BAD_CHARACTER&quot;
comma
l_string|&quot;AE_BAD_PATHNAME&quot;
comma
l_string|&quot;AE_BAD_DATA&quot;
comma
l_string|&quot;AE_BAD_ADDRESS&quot;
comma
l_string|&quot;AE_ALIGNMENT&quot;
comma
l_string|&quot;AE_BAD_HEX_CONSTANT&quot;
comma
l_string|&quot;AE_BAD_OCTAL_CONSTANT&quot;
comma
l_string|&quot;AE_BAD_DECIMAL_CONSTANT&quot;
)brace
suffix:semicolon
DECL|variable|acpi_gbl_exception_names_tbl
r_char
r_const
op_star
id|acpi_gbl_exception_names_tbl
(braket
)braket
op_assign
(brace
l_string|&quot;AE_BAD_SIGNATURE&quot;
comma
l_string|&quot;AE_BAD_HEADER&quot;
comma
l_string|&quot;AE_BAD_CHECKSUM&quot;
comma
l_string|&quot;AE_BAD_VALUE&quot;
comma
l_string|&quot;AE_TABLE_NOT_SUPPORTED&quot;
comma
l_string|&quot;AE_INVALID_TABLE_LENGTH&quot;
)brace
suffix:semicolon
DECL|variable|acpi_gbl_exception_names_aml
r_char
r_const
op_star
id|acpi_gbl_exception_names_aml
(braket
)braket
op_assign
(brace
l_string|&quot;AE_AML_ERROR&quot;
comma
l_string|&quot;AE_AML_PARSE&quot;
comma
l_string|&quot;AE_AML_BAD_OPCODE&quot;
comma
l_string|&quot;AE_AML_NO_OPERAND&quot;
comma
l_string|&quot;AE_AML_OPERAND_TYPE&quot;
comma
l_string|&quot;AE_AML_OPERAND_VALUE&quot;
comma
l_string|&quot;AE_AML_UNINITIALIZED_LOCAL&quot;
comma
l_string|&quot;AE_AML_UNINITIALIZED_ARG&quot;
comma
l_string|&quot;AE_AML_UNINITIALIZED_ELEMENT&quot;
comma
l_string|&quot;AE_AML_NUMERIC_OVERFLOW&quot;
comma
l_string|&quot;AE_AML_REGION_LIMIT&quot;
comma
l_string|&quot;AE_AML_BUFFER_LIMIT&quot;
comma
l_string|&quot;AE_AML_PACKAGE_LIMIT&quot;
comma
l_string|&quot;AE_AML_DIVIDE_BY_ZERO&quot;
comma
l_string|&quot;AE_AML_BAD_NAME&quot;
comma
l_string|&quot;AE_AML_NAME_NOT_FOUND&quot;
comma
l_string|&quot;AE_AML_INTERNAL&quot;
comma
l_string|&quot;AE_AML_INVALID_SPACE_ID&quot;
comma
l_string|&quot;AE_AML_STRING_LIMIT&quot;
comma
l_string|&quot;AE_AML_NO_RETURN_VALUE&quot;
comma
l_string|&quot;AE_AML_METHOD_LIMIT&quot;
comma
l_string|&quot;AE_AML_NOT_OWNER&quot;
comma
l_string|&quot;AE_AML_MUTEX_ORDER&quot;
comma
l_string|&quot;AE_AML_MUTEX_NOT_ACQUIRED&quot;
comma
l_string|&quot;AE_AML_INVALID_RESOURCE_TYPE&quot;
comma
l_string|&quot;AE_AML_INVALID_INDEX&quot;
comma
l_string|&quot;AE_AML_REGISTER_LIMIT&quot;
comma
l_string|&quot;AE_AML_NO_WHILE&quot;
comma
l_string|&quot;AE_AML_ALIGNMENT&quot;
comma
l_string|&quot;AE_AML_NO_RESOURCE_END_TAG&quot;
comma
l_string|&quot;AE_AML_BAD_RESOURCE_VALUE&quot;
comma
l_string|&quot;AE_AML_CIRCULAR_REFERENCE&quot;
)brace
suffix:semicolon
DECL|variable|acpi_gbl_exception_names_ctrl
r_char
r_const
op_star
id|acpi_gbl_exception_names_ctrl
(braket
)braket
op_assign
(brace
l_string|&quot;AE_CTRL_RETURN_VALUE&quot;
comma
l_string|&quot;AE_CTRL_PENDING&quot;
comma
l_string|&quot;AE_CTRL_TERMINATE&quot;
comma
l_string|&quot;AE_CTRL_TRUE&quot;
comma
l_string|&quot;AE_CTRL_FALSE&quot;
comma
l_string|&quot;AE_CTRL_DEPTH&quot;
comma
l_string|&quot;AE_CTRL_END&quot;
comma
l_string|&quot;AE_CTRL_TRANSFER&quot;
comma
l_string|&quot;AE_CTRL_BREAK&quot;
comma
l_string|&quot;AE_CTRL_CONTINUE&quot;
comma
l_string|&quot;AE_CTRL_SKIP&quot;
)brace
suffix:semicolon
macro_line|#endif /* ACPI GLOBALS */
macro_line|#endif /* __ACEXCEP_H__ */
eof
