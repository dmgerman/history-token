multiline_comment|/******************************************************************************&n; *&n; * Module Name: amxface - External interpreter interfaces&n; *              $Revision: 22 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          INTERPRETER
id|MODULE_NAME
(paren
l_string|&quot;amxface&quot;
)paren
multiline_comment|/*&n; * DEFINE_AML_GLOBALS is tested in amlcode.h&n; * to determine whether certain global names should be &quot;defined&quot; or only&n; * &quot;declared&quot; in the current compilation.  This enhances maintainability&n; * by enabling a single header file to embody all knowledge of the names&n; * in question.&n; *&n; * Exactly one module of any executable should #define DEFINE_GLOBALS&n; * before #including the header files which use this convention.  The&n; * names in question will be defined and initialized in that module,&n; * and declared as extern in all other modules which #include those&n; * header files.&n; */
DECL|macro|DEFINE_AML_GLOBALS
mdefine_line|#define DEFINE_AML_GLOBALS
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_aml_execute_method&n; *&n; * PARAMETERS:  Pcode               - Pointer to the pcode stream&n; *              Pcode_length        - Length of pcode that comprises the method&n; *              **Params            - List of parameters to pass to method,&n; *                                    terminated by NULL. Params itself may be&n; *                                    NULL if no parameters are being passed.&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Execute a control method&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_aml_execute_method
id|acpi_aml_execute_method
(paren
id|ACPI_NAMESPACE_NODE
op_star
id|method_node
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|params
comma
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|return_obj_desc
)paren
(brace
id|ACPI_STATUS
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * The point here is to lock the interpreter and call the low&n;&t; * level execute.&n;&t; */
id|acpi_aml_enter_interpreter
(paren
)paren
suffix:semicolon
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
id|acpi_aml_exit_interpreter
(paren
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
