multiline_comment|/******************************************************************************&n; *&n; * Module Name: pstree - Parser op tree manipulation/traversal/search&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2003, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acparser.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_PARSER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;pstree&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_get_arg&n; *&n; * PARAMETERS:  Op              - Get an argument for this op&n; *              Argn            - Nth argument to get&n; *&n; * RETURN:      The argument (as an Op object).  NULL if argument does not exist&n; *&n; * DESCRIPTION: Get the specified op&squot;s argument.&n; *&n; ******************************************************************************/
r_union
id|acpi_parse_object
op_star
DECL|function|acpi_ps_get_arg
id|acpi_ps_get_arg
(paren
r_union
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|argn
)paren
(brace
r_union
id|acpi_parse_object
op_star
id|arg
op_assign
l_int|NULL
suffix:semicolon
r_const
r_struct
id|acpi_opcode_info
op_star
id|op_info
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/* Get the info structure for this opcode */
id|op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|op-&gt;common.aml_opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op_info
op_member_access_from_pointer
r_class
op_eq
id|AML_CLASS_UNKNOWN
)paren
(brace
multiline_comment|/* Invalid opcode or ASCII character */
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Check if this opcode requires argument sub-objects */
r_if
c_cond
(paren
op_logical_neg
(paren
id|op_info-&gt;flags
op_amp
id|AML_HAS_ARGS
)paren
)paren
(brace
multiline_comment|/* Has no linked argument objects */
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Get the requested argument object */
id|arg
op_assign
id|op-&gt;common.value.arg
suffix:semicolon
r_while
c_loop
(paren
id|arg
op_logical_and
id|argn
)paren
(brace
id|argn
op_decrement
suffix:semicolon
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
)brace
r_return
(paren
id|arg
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_append_arg&n; *&n; * PARAMETERS:  Op              - Append an argument to this Op.&n; *              Arg             - Argument Op to append&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Append an argument to an op&squot;s argument list (a NULL arg is OK)&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ps_append_arg
id|acpi_ps_append_arg
(paren
r_union
id|acpi_parse_object
op_star
id|op
comma
r_union
id|acpi_parse_object
op_star
id|arg
)paren
(brace
r_union
id|acpi_parse_object
op_star
id|prev_arg
suffix:semicolon
r_const
r_struct
id|acpi_opcode_info
op_star
id|op_info
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Get the info structure for this opcode */
id|op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|op-&gt;common.aml_opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
id|op_info
op_member_access_from_pointer
r_class
op_eq
id|AML_CLASS_UNKNOWN
)paren
(brace
multiline_comment|/* Invalid opcode */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ps_append_arg: Invalid AML Opcode: 0x%2.2X&bslash;n&quot;
comma
id|op-&gt;common.aml_opcode
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Check if this opcode requires argument sub-objects */
r_if
c_cond
(paren
op_logical_neg
(paren
id|op_info-&gt;flags
op_amp
id|AML_HAS_ARGS
)paren
)paren
(brace
multiline_comment|/* Has no linked argument objects */
r_return
suffix:semicolon
)brace
multiline_comment|/* Append the argument to the linked argument list */
r_if
c_cond
(paren
id|op-&gt;common.value.arg
)paren
(brace
multiline_comment|/* Append to existing argument list */
id|prev_arg
op_assign
id|op-&gt;common.value.arg
suffix:semicolon
r_while
c_loop
(paren
id|prev_arg-&gt;common.next
)paren
(brace
id|prev_arg
op_assign
id|prev_arg-&gt;common.next
suffix:semicolon
)brace
id|prev_arg-&gt;common.next
op_assign
id|arg
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* No argument list, this will be the first argument */
id|op-&gt;common.value.arg
op_assign
id|arg
suffix:semicolon
)brace
multiline_comment|/* Set the parent in this arg and any args linked after it */
r_while
c_loop
(paren
id|arg
)paren
(brace
id|arg-&gt;common.parent
op_assign
id|op
suffix:semicolon
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_get_child&n; *&n; * PARAMETERS:  Op              - Get the child of this Op&n; *&n; * RETURN:      Child Op, Null if none is found.&n; *&n; * DESCRIPTION: Get op&squot;s children or NULL if none&n; *&n; ******************************************************************************/
r_union
id|acpi_parse_object
op_star
DECL|function|acpi_ps_get_child
id|acpi_ps_get_child
(paren
r_union
id|acpi_parse_object
op_star
id|op
)paren
(brace
r_union
id|acpi_parse_object
op_star
id|child
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|op-&gt;common.aml_opcode
)paren
(brace
r_case
id|AML_SCOPE_OP
suffix:colon
r_case
id|AML_ELSE_OP
suffix:colon
r_case
id|AML_DEVICE_OP
suffix:colon
r_case
id|AML_THERMAL_ZONE_OP
suffix:colon
r_case
id|AML_INT_METHODCALL_OP
suffix:colon
id|child
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|0
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_BUFFER_OP
suffix:colon
r_case
id|AML_PACKAGE_OP
suffix:colon
r_case
id|AML_METHOD_OP
suffix:colon
r_case
id|AML_IF_OP
suffix:colon
r_case
id|AML_WHILE_OP
suffix:colon
r_case
id|AML_FIELD_OP
suffix:colon
id|child
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_POWER_RES_OP
suffix:colon
r_case
id|AML_INDEX_FIELD_OP
suffix:colon
id|child
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|2
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_PROCESSOR_OP
suffix:colon
r_case
id|AML_BANK_FIELD_OP
suffix:colon
id|child
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|3
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All others have no children */
r_break
suffix:semicolon
)brace
r_return
(paren
id|child
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_get_depth_next&n; *&n; * PARAMETERS:  Origin          - Root of subtree to search&n; *              Op              - Last (previous) Op that was found&n; *&n; * RETURN:      Next Op found in the search.&n; *&n; * DESCRIPTION: Get next op in tree (walking the tree in depth-first order)&n; *              Return NULL when reaching &quot;origin&quot; or when walking up from root&n; *&n; ******************************************************************************/
r_union
id|acpi_parse_object
op_star
DECL|function|acpi_ps_get_depth_next
id|acpi_ps_get_depth_next
(paren
r_union
id|acpi_parse_object
op_star
id|origin
comma
r_union
id|acpi_parse_object
op_star
id|op
)paren
(brace
r_union
id|acpi_parse_object
op_star
id|next
op_assign
l_int|NULL
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|parent
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|arg
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* look for an argument or child */
id|next
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
(brace
r_return
(paren
id|next
)paren
suffix:semicolon
)brace
multiline_comment|/* look for a sibling */
id|next
op_assign
id|op-&gt;common.next
suffix:semicolon
r_if
c_cond
(paren
id|next
)paren
(brace
r_return
(paren
id|next
)paren
suffix:semicolon
)brace
multiline_comment|/* look for a sibling of parent */
id|parent
op_assign
id|op-&gt;common.parent
suffix:semicolon
r_while
c_loop
(paren
id|parent
)paren
(brace
id|arg
op_assign
id|acpi_ps_get_arg
(paren
id|parent
comma
l_int|0
)paren
suffix:semicolon
r_while
c_loop
(paren
id|arg
op_logical_and
(paren
id|arg
op_ne
id|origin
)paren
op_logical_and
(paren
id|arg
op_ne
id|op
)paren
)paren
(brace
id|arg
op_assign
id|arg-&gt;common.next
suffix:semicolon
)brace
r_if
c_cond
(paren
id|arg
op_eq
id|origin
)paren
(brace
multiline_comment|/* reached parent of origin, end search */
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|parent-&gt;common.next
)paren
(brace
multiline_comment|/* found sibling of parent */
r_return
(paren
id|parent-&gt;common.next
)paren
suffix:semicolon
)brace
id|op
op_assign
id|parent
suffix:semicolon
id|parent
op_assign
id|parent-&gt;common.parent
suffix:semicolon
)brace
r_return
(paren
id|next
)paren
suffix:semicolon
)brace
eof
