multiline_comment|/******************************************************************************&n; *&n; * Name: acexcep.h - Exception codes returned by the ACPI subsystem&n; *       $Revision: 41 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
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
mdefine_line|#define AE_OK                           (ACPI_STATUS) 0x0000
multiline_comment|/*&n; * Environmental exceptions&n; */
DECL|macro|AE_ERROR
mdefine_line|#define AE_ERROR                        (ACPI_STATUS) (0x0001 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NO_ACPI_TABLES
mdefine_line|#define AE_NO_ACPI_TABLES               (ACPI_STATUS) (0x0002 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NO_NAMESPACE
mdefine_line|#define AE_NO_NAMESPACE                 (ACPI_STATUS) (0x0003 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NO_MEMORY
mdefine_line|#define AE_NO_MEMORY                    (ACPI_STATUS) (0x0004 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NOT_FOUND
mdefine_line|#define AE_NOT_FOUND                    (ACPI_STATUS) (0x0005 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NOT_EXIST
mdefine_line|#define AE_NOT_EXIST                    (ACPI_STATUS) (0x0006 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_EXIST
mdefine_line|#define AE_EXIST                        (ACPI_STATUS) (0x0007 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_TYPE
mdefine_line|#define AE_TYPE                         (ACPI_STATUS) (0x0008 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NULL_OBJECT
mdefine_line|#define AE_NULL_OBJECT                  (ACPI_STATUS) (0x0009 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NULL_ENTRY
mdefine_line|#define AE_NULL_ENTRY                   (ACPI_STATUS) (0x000A | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_BUFFER_OVERFLOW
mdefine_line|#define AE_BUFFER_OVERFLOW              (ACPI_STATUS) (0x000B | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_STACK_OVERFLOW
mdefine_line|#define AE_STACK_OVERFLOW               (ACPI_STATUS) (0x000C | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_STACK_UNDERFLOW
mdefine_line|#define AE_STACK_UNDERFLOW              (ACPI_STATUS) (0x000D | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_NOT_IMPLEMENTED
mdefine_line|#define AE_NOT_IMPLEMENTED              (ACPI_STATUS) (0x000E | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_VERSION_MISMATCH
mdefine_line|#define AE_VERSION_MISMATCH             (ACPI_STATUS) (0x000F | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_SUPPORT
mdefine_line|#define AE_SUPPORT                      (ACPI_STATUS) (0x0010 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_SHARE
mdefine_line|#define AE_SHARE                        (ACPI_STATUS) (0x0011 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_LIMIT
mdefine_line|#define AE_LIMIT                        (ACPI_STATUS) (0x0012 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_TIME
mdefine_line|#define AE_TIME                         (ACPI_STATUS) (0x0013 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_UNKNOWN_STATUS
mdefine_line|#define AE_UNKNOWN_STATUS               (ACPI_STATUS) (0x0014 | AE_CODE_ENVIRONMENTAL)
DECL|macro|AE_CODE_ENV_MAX
mdefine_line|#define AE_CODE_ENV_MAX                 0x0014
multiline_comment|/*&n; * Programmer exceptions&n; */
DECL|macro|AE_BAD_PARAMETER
mdefine_line|#define AE_BAD_PARAMETER                (ACPI_STATUS) (0x0001 | AE_CODE_PROGRAMMER)
DECL|macro|AE_BAD_CHARACTER
mdefine_line|#define AE_BAD_CHARACTER                (ACPI_STATUS) (0x0002 | AE_CODE_PROGRAMMER)
DECL|macro|AE_BAD_PATHNAME
mdefine_line|#define AE_BAD_PATHNAME                 (ACPI_STATUS) (0x0003 | AE_CODE_PROGRAMMER)
DECL|macro|AE_BAD_DATA
mdefine_line|#define AE_BAD_DATA                     (ACPI_STATUS) (0x0004 | AE_CODE_PROGRAMMER)
DECL|macro|AE_BAD_ADDRESS
mdefine_line|#define AE_BAD_ADDRESS                  (ACPI_STATUS) (0x0005 | AE_CODE_PROGRAMMER)
DECL|macro|AE_CODE_PGM_MAX
mdefine_line|#define AE_CODE_PGM_MAX                 0x0005
multiline_comment|/*&n; * Acpi table exceptions&n; */
DECL|macro|AE_BAD_SIGNATURE
mdefine_line|#define AE_BAD_SIGNATURE                (ACPI_STATUS) (0x0001 | AE_CODE_ACPI_TABLES)
DECL|macro|AE_BAD_HEADER
mdefine_line|#define AE_BAD_HEADER                   (ACPI_STATUS) (0x0002 | AE_CODE_ACPI_TABLES)
DECL|macro|AE_BAD_CHECKSUM
mdefine_line|#define AE_BAD_CHECKSUM                 (ACPI_STATUS) (0x0003 | AE_CODE_ACPI_TABLES)
DECL|macro|AE_BAD_VALUE
mdefine_line|#define AE_BAD_VALUE                    (ACPI_STATUS) (0x0004 | AE_CODE_ACPI_TABLES)
DECL|macro|AE_CODE_TBL_MAX
mdefine_line|#define AE_CODE_TBL_MAX                 0x0003
multiline_comment|/*&n; * AML exceptions.  These are caused by problems with&n; * the actual AML byte stream&n; */
DECL|macro|AE_AML_ERROR
mdefine_line|#define AE_AML_ERROR                    (ACPI_STATUS) (0x0001 | AE_CODE_AML)
DECL|macro|AE_AML_PARSE
mdefine_line|#define AE_AML_PARSE                    (ACPI_STATUS) (0x0002 | AE_CODE_AML)
DECL|macro|AE_AML_BAD_OPCODE
mdefine_line|#define AE_AML_BAD_OPCODE               (ACPI_STATUS) (0x0003 | AE_CODE_AML)
DECL|macro|AE_AML_NO_OPERAND
mdefine_line|#define AE_AML_NO_OPERAND               (ACPI_STATUS) (0x0004 | AE_CODE_AML)
DECL|macro|AE_AML_OPERAND_TYPE
mdefine_line|#define AE_AML_OPERAND_TYPE             (ACPI_STATUS) (0x0005 | AE_CODE_AML)
DECL|macro|AE_AML_OPERAND_VALUE
mdefine_line|#define AE_AML_OPERAND_VALUE            (ACPI_STATUS) (0x0006 | AE_CODE_AML)
DECL|macro|AE_AML_UNINITIALIZED_LOCAL
mdefine_line|#define AE_AML_UNINITIALIZED_LOCAL      (ACPI_STATUS) (0x0007 | AE_CODE_AML)
DECL|macro|AE_AML_UNINITIALIZED_ARG
mdefine_line|#define AE_AML_UNINITIALIZED_ARG        (ACPI_STATUS) (0x0008 | AE_CODE_AML)
DECL|macro|AE_AML_UNINITIALIZED_ELEMENT
mdefine_line|#define AE_AML_UNINITIALIZED_ELEMENT    (ACPI_STATUS) (0x0009 | AE_CODE_AML)
DECL|macro|AE_AML_NUMERIC_OVERFLOW
mdefine_line|#define AE_AML_NUMERIC_OVERFLOW         (ACPI_STATUS) (0x000A | AE_CODE_AML)
DECL|macro|AE_AML_REGION_LIMIT
mdefine_line|#define AE_AML_REGION_LIMIT             (ACPI_STATUS) (0x000B | AE_CODE_AML)
DECL|macro|AE_AML_BUFFER_LIMIT
mdefine_line|#define AE_AML_BUFFER_LIMIT             (ACPI_STATUS) (0x000C | AE_CODE_AML)
DECL|macro|AE_AML_PACKAGE_LIMIT
mdefine_line|#define AE_AML_PACKAGE_LIMIT            (ACPI_STATUS) (0x000D | AE_CODE_AML)
DECL|macro|AE_AML_DIVIDE_BY_ZERO
mdefine_line|#define AE_AML_DIVIDE_BY_ZERO           (ACPI_STATUS) (0x000E | AE_CODE_AML)
DECL|macro|AE_AML_BAD_NAME
mdefine_line|#define AE_AML_BAD_NAME                 (ACPI_STATUS) (0x000F | AE_CODE_AML)
DECL|macro|AE_AML_NAME_NOT_FOUND
mdefine_line|#define AE_AML_NAME_NOT_FOUND           (ACPI_STATUS) (0x0010 | AE_CODE_AML)
DECL|macro|AE_AML_INTERNAL
mdefine_line|#define AE_AML_INTERNAL                 (ACPI_STATUS) (0x0011 | AE_CODE_AML)
DECL|macro|AE_AML_INVALID_SPACE_ID
mdefine_line|#define AE_AML_INVALID_SPACE_ID         (ACPI_STATUS) (0x0012 | AE_CODE_AML)
DECL|macro|AE_AML_STRING_LIMIT
mdefine_line|#define AE_AML_STRING_LIMIT             (ACPI_STATUS) (0x0013 | AE_CODE_AML)
DECL|macro|AE_AML_NO_RETURN_VALUE
mdefine_line|#define AE_AML_NO_RETURN_VALUE          (ACPI_STATUS) (0x0014 | AE_CODE_AML)
DECL|macro|AE_CODE_AML_MAX
mdefine_line|#define AE_CODE_AML_MAX                 0x0014
multiline_comment|/*&n; * Internal exceptions used for control&n; */
DECL|macro|AE_CTRL_RETURN_VALUE
mdefine_line|#define AE_CTRL_RETURN_VALUE            (ACPI_STATUS) (0x0001 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_PENDING
mdefine_line|#define AE_CTRL_PENDING                 (ACPI_STATUS) (0x0002 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_TERMINATE
mdefine_line|#define AE_CTRL_TERMINATE               (ACPI_STATUS) (0x0003 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_TRUE
mdefine_line|#define AE_CTRL_TRUE                    (ACPI_STATUS) (0x0004 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_FALSE
mdefine_line|#define AE_CTRL_FALSE                   (ACPI_STATUS) (0x0005 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_DEPTH
mdefine_line|#define AE_CTRL_DEPTH                   (ACPI_STATUS) (0x0006 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_END
mdefine_line|#define AE_CTRL_END                     (ACPI_STATUS) (0x0007 | AE_CODE_CONTROL)
DECL|macro|AE_CTRL_TRANSFER
mdefine_line|#define AE_CTRL_TRANSFER                (ACPI_STATUS) (0x0008 | AE_CODE_CONTROL)
DECL|macro|AE_CODE_CTRL_MAX
mdefine_line|#define AE_CODE_CTRL_MAX                0x0008
macro_line|#ifdef DEFINE_ACPI_GLOBALS
multiline_comment|/*&n; * String versions of the exception codes above&n; * These strings must match the corresponding defines exactly&n; */
DECL|variable|acpi_gbl_exception_names_env
r_static
id|NATIVE_CHAR
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
l_string|&quot;AE_EXIST&quot;
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
)brace
suffix:semicolon
DECL|variable|acpi_gbl_exception_names_pgm
r_static
id|NATIVE_CHAR
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
)brace
suffix:semicolon
DECL|variable|acpi_gbl_exception_names_tbl
r_static
id|NATIVE_CHAR
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
)brace
suffix:semicolon
DECL|variable|acpi_gbl_exception_names_aml
r_static
id|NATIVE_CHAR
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
)brace
suffix:semicolon
DECL|variable|acpi_gbl_exception_names_ctrl
r_static
id|NATIVE_CHAR
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
)brace
suffix:semicolon
macro_line|#endif /* DEFINE_ACPI_GLOBALS */
macro_line|#endif /* __ACEXCEP_H__ */
eof
