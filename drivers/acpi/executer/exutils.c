multiline_comment|/******************************************************************************&n; *&n; * Module Name: exutils - interpreter/scanner utilities&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
multiline_comment|/*&n; * DEFINE_AML_GLOBALS is tested in amlcode.h&n; * to determine whether certain global names should be &quot;defined&quot; or only&n; * &quot;declared&quot; in the current compilation.  This enhances maintainability&n; * by enabling a single header file to embody all knowledge of the names&n; * in question.&n; *&n; * Exactly one module of any executable should #define DEFINE_GLOBALS&n; * before #including the header files which use this convention.  The&n; * names in question will be defined and initialized in that module,&n; * and declared as extern in all other modules which #include those&n; * header files.&n; */
DECL|macro|DEFINE_AML_GLOBALS
mdefine_line|#define DEFINE_AML_GLOBALS
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exutils&quot;
)paren
macro_line|#ifndef ACPI_NO_METHOD_EXECUTION
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_enter_interpreter&n; *&n; * PARAMETERS:  None&n; *&n; * DESCRIPTION: Enter the interpreter execution region.  Failure to enter&n; *              the interpreter region is a fatal system error&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_enter_interpreter
id|acpi_ex_enter_interpreter
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_enter_interpreter&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_EXECUTE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not acquire interpreter mutex&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_exit_interpreter&n; *&n; * PARAMETERS:  None&n; *&n; * DESCRIPTION: Exit the interpreter execution region&n; *&n; * Cases where the interpreter is unlocked:&n; *      1) Completion of the execution of a control method&n; *      2) Method blocked on a Sleep() AML opcode&n; *      3) Method blocked on an Acquire() AML opcode&n; *      4) Method blocked on a Wait() AML opcode&n; *      5) Method blocked to acquire the global lock&n; *      6) Method blocked to execute a serialized control method that is&n; *          already executing&n; *      7) About to invoke a user-installed opregion handler&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ex_exit_interpreter
id|acpi_ex_exit_interpreter
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_exit_interpreter&quot;
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_EXECUTE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not release interpreter mutex&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_truncate_for32bit_table&n; *&n; * PARAMETERS:  obj_desc        - Object to be truncated&n; *&n; * RETURN:      none&n; *&n; * DESCRIPTION: Truncate a number to 32-bits if the currently executing method&n; *              belongs to a 32-bit ACPI table.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ex_truncate_for32bit_table
id|acpi_ex_truncate_for32bit_table
(paren
r_union
id|acpi_operand_object
op_star
id|obj_desc
)paren
(brace
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Object must be a valid number and we must be executing&n;&t; * a control method&n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|obj_desc
)paren
op_logical_or
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_ne
id|ACPI_TYPE_INTEGER
)paren
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_gbl_integer_byte_width
op_eq
l_int|4
)paren
(brace
multiline_comment|/*&n;&t;&t; * We are running a method that exists in a 32-bit ACPI table.&n;&t;&t; * Truncate the value to 32 bits by zeroing out the upper 32-bit field&n;&t;&t; */
id|obj_desc-&gt;integer.value
op_and_assign
(paren
id|acpi_integer
)paren
id|ACPI_UINT32_MAX
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_acquire_global_lock&n; *&n; * PARAMETERS:  field_flags           - Flags with Lock rule:&n; *                                      always_lock or never_lock&n; *&n; * RETURN:      TRUE/FALSE indicating whether the lock was actually acquired&n; *&n; * DESCRIPTION: Obtain the global lock and keep track of this fact via two&n; *              methods.  A global variable keeps the state of the lock, and&n; *              the state is returned to the caller.&n; *&n; ******************************************************************************/
id|u8
DECL|function|acpi_ex_acquire_global_lock
id|acpi_ex_acquire_global_lock
(paren
id|u32
id|field_flags
)paren
(brace
id|u8
id|locked
op_assign
id|FALSE
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_acquire_global_lock&quot;
)paren
suffix:semicolon
multiline_comment|/* Only attempt lock if the always_lock bit is set */
r_if
c_cond
(paren
id|field_flags
op_amp
id|AML_FIELD_LOCK_RULE_MASK
)paren
(brace
multiline_comment|/* We should attempt to get the lock, wait forever */
id|status
op_assign
id|acpi_ev_acquire_global_lock
(paren
id|ACPI_WAIT_FOREVER
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
)paren
(brace
id|locked
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not acquire Global Lock, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
id|return_VALUE
(paren
id|locked
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_release_global_lock&n; *&n; * PARAMETERS:  locked_by_me    - Return value from corresponding call to&n; *                                acquire_global_lock.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Release the global lock if it is locked.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ex_release_global_lock
id|acpi_ex_release_global_lock
(paren
id|u8
id|locked_by_me
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_release_global_lock&quot;
)paren
suffix:semicolon
multiline_comment|/* Only attempt unlock if the caller locked it */
r_if
c_cond
(paren
id|locked_by_me
)paren
(brace
multiline_comment|/* OK, now release the lock */
id|status
op_assign
id|acpi_ev_release_global_lock
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
multiline_comment|/* Report the error, but there isn&squot;t much else we can do */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not release ACPI Global Lock, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
)brace
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_digits_needed&n; *&n; * PARAMETERS:  Value           - Value to be represented&n; *              Base            - Base of representation&n; *&n; * RETURN:      the number of digits needed to represent Value in Base&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ex_digits_needed
id|acpi_ex_digits_needed
(paren
id|acpi_integer
id|value
comma
id|u32
id|base
)paren
(brace
id|u32
id|num_digits
suffix:semicolon
id|acpi_integer
id|current_value
suffix:semicolon
id|acpi_integer
id|quotient
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_digits_needed&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * acpi_integer is unsigned, so we don&squot;t worry about a &squot;-&squot;&n;&t; */
r_if
c_cond
(paren
(paren
id|current_value
op_assign
id|value
)paren
op_eq
l_int|0
)paren
(brace
id|return_VALUE
(paren
l_int|1
)paren
suffix:semicolon
)brace
id|num_digits
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|current_value
)paren
(brace
(paren
r_void
)paren
id|acpi_ut_short_divide
(paren
op_amp
id|current_value
comma
id|base
comma
op_amp
id|quotient
comma
l_int|NULL
)paren
suffix:semicolon
id|num_digits
op_increment
suffix:semicolon
id|current_value
op_assign
id|quotient
suffix:semicolon
)brace
id|return_VALUE
(paren
id|num_digits
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_eisa_id_to_string&n; *&n; * PARAMETERS:  numeric_id      - EISA ID to be converted&n; *              out_string      - Where to put the converted string (8 bytes)&n; *&n; * DESCRIPTION: Convert a numeric EISA ID to string representation&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ex_eisa_id_to_string
id|acpi_ex_eisa_id_to_string
(paren
id|u32
id|numeric_id
comma
r_char
op_star
id|out_string
)paren
(brace
id|u32
id|eisa_id
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/* Swap ID to big-endian to get contiguous bits */
id|eisa_id
op_assign
id|acpi_ut_dword_byte_swap
(paren
id|numeric_id
)paren
suffix:semicolon
id|out_string
(braket
l_int|0
)braket
op_assign
(paren
r_char
)paren
(paren
l_char|&squot;@&squot;
op_plus
(paren
(paren
(paren
r_int
r_int
)paren
id|eisa_id
op_rshift
l_int|26
)paren
op_amp
l_int|0x1f
)paren
)paren
suffix:semicolon
id|out_string
(braket
l_int|1
)braket
op_assign
(paren
r_char
)paren
(paren
l_char|&squot;@&squot;
op_plus
(paren
(paren
id|eisa_id
op_rshift
l_int|21
)paren
op_amp
l_int|0x1f
)paren
)paren
suffix:semicolon
id|out_string
(braket
l_int|2
)braket
op_assign
(paren
r_char
)paren
(paren
l_char|&squot;@&squot;
op_plus
(paren
(paren
id|eisa_id
op_rshift
l_int|16
)paren
op_amp
l_int|0x1f
)paren
)paren
suffix:semicolon
id|out_string
(braket
l_int|3
)braket
op_assign
id|acpi_ut_hex_to_ascii_char
(paren
(paren
id|acpi_integer
)paren
id|eisa_id
comma
l_int|12
)paren
suffix:semicolon
id|out_string
(braket
l_int|4
)braket
op_assign
id|acpi_ut_hex_to_ascii_char
(paren
(paren
id|acpi_integer
)paren
id|eisa_id
comma
l_int|8
)paren
suffix:semicolon
id|out_string
(braket
l_int|5
)braket
op_assign
id|acpi_ut_hex_to_ascii_char
(paren
(paren
id|acpi_integer
)paren
id|eisa_id
comma
l_int|4
)paren
suffix:semicolon
id|out_string
(braket
l_int|6
)braket
op_assign
id|acpi_ut_hex_to_ascii_char
(paren
(paren
id|acpi_integer
)paren
id|eisa_id
comma
l_int|0
)paren
suffix:semicolon
id|out_string
(braket
l_int|7
)braket
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_unsigned_integer_to_string&n; *&n; * PARAMETERS:  Value           - Value to be converted&n; *              out_string      - Where to put the converted string (8 bytes)&n; *&n; * RETURN:      Convert a number to string representation&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ex_unsigned_integer_to_string
id|acpi_ex_unsigned_integer_to_string
(paren
id|acpi_integer
id|value
comma
r_char
op_star
id|out_string
)paren
(brace
id|u32
id|count
suffix:semicolon
id|u32
id|digits_needed
suffix:semicolon
id|u32
id|remainder
suffix:semicolon
id|acpi_integer
id|quotient
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
id|digits_needed
op_assign
id|acpi_ex_digits_needed
(paren
id|value
comma
l_int|10
)paren
suffix:semicolon
id|out_string
(braket
id|digits_needed
)braket
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|count
op_assign
id|digits_needed
suffix:semicolon
id|count
OG
l_int|0
suffix:semicolon
id|count
op_decrement
)paren
(brace
(paren
r_void
)paren
id|acpi_ut_short_divide
(paren
op_amp
id|value
comma
l_int|10
comma
op_amp
id|quotient
comma
op_amp
id|remainder
)paren
suffix:semicolon
id|out_string
(braket
id|count
op_minus
l_int|1
)braket
op_assign
(paren
r_char
)paren
(paren
l_char|&squot;0&squot;
op_plus
id|remainder
)paren
suffix:semicolon
"&bslash;"
id|value
op_assign
id|quotient
suffix:semicolon
)brace
)brace
macro_line|#endif
eof
