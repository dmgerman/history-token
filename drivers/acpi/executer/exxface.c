multiline_comment|/******************************************************************************&n; *&n; * Module Name: exxface - External interpreter interfaces&n; *              $Revision: 29 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|MODULE_NAME
(paren
l_string|&quot;exxface&quot;
)paren
macro_line|#if 0
multiline_comment|/*&n; * DEFINE_AML_GLOBALS is tested in amlcode.h&n; * to determine whether certain global names should be &quot;defined&quot; or only&n; * &quot;declared&quot; in the current compilation.  This enhances maintainability&n; * by enabling a single header file to embody all knowledge of the names&n; * in question.&n; *&n; * Exactly one module of any executable should #define DEFINE_GLOBALS&n; * before #including the header files which use this convention.  The&n; * names in question will be defined and initialized in that module,&n; * and declared as extern in all other modules which #include those&n; * header files.&n; */
mdefine_line|#define DEFINE_AML_GLOBALS
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_execute_method&n; *&n; * PARAMETERS:  Pcode               - Pointer to the pcode stream&n; *              Pcode_length        - Length of pcode that comprises the method&n; *              **Params            - List of parameters to pass to method,&n; *                                    terminated by NULL. Params itself may be&n; *                                    NULL if no parameters are being passed.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute a control method&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_execute_method
id|acpi_ex_execute_method
(paren
id|acpi_namespace_node
op_star
id|method_node
comma
id|acpi_operand_object
op_star
op_star
id|params
comma
id|acpi_operand_object
op_star
op_star
id|return_obj_desc
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|FUNCTION_TRACE
(paren
l_string|&quot;Ex_execute_method&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * The point here is to lock the interpreter and call the low&n;&t; * level execute.&n;&t; */
id|status
op_assign
id|acpi_ex_enter_interpreter
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_psx_execute
(paren
id|method_node
comma
id|params
comma
id|return_obj_desc
)paren
suffix:semicolon
id|acpi_ex_exit_interpreter
(paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
