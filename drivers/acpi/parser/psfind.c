multiline_comment|/******************************************************************************&n; *&n; * Module Name: psfind - Parse tree search routine&n; *              $Revision: 24 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;amlcode.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_PARSER
id|MODULE_NAME
(paren
l_string|&quot;psfind&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_parent&n; *&n; * PARAMETERS:  Op              - Get the parent of this Op&n; *&n; * RETURN:      The Parent op.&n; *&n; * DESCRIPTION: Get op&squot;s parent&n; *&n; ******************************************************************************/
r_static
id|ACPI_PARSE_OBJECT
op_star
DECL|function|acpi_ps_get_parent
id|acpi_ps_get_parent
(paren
id|ACPI_PARSE_OBJECT
op_star
id|op
)paren
(brace
id|ACPI_PARSE_OBJECT
op_star
id|parent
op_assign
id|op
suffix:semicolon
multiline_comment|/* Traverse the tree upward (to root if necessary) */
r_while
c_loop
(paren
id|parent
)paren
(brace
r_switch
c_cond
(paren
id|parent-&gt;opcode
)paren
(brace
r_case
id|AML_SCOPE_OP
suffix:colon
r_case
id|AML_PACKAGE_OP
suffix:colon
r_case
id|AML_METHOD_OP
suffix:colon
r_case
id|AML_DEVICE_OP
suffix:colon
r_case
id|AML_POWER_RES_OP
suffix:colon
r_case
id|AML_THERMAL_ZONE_OP
suffix:colon
r_return
(paren
id|parent-&gt;parent
)paren
suffix:semicolon
)brace
id|parent
op_assign
id|parent-&gt;parent
suffix:semicolon
)brace
r_return
(paren
id|parent
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_find_name&n; *&n; * PARAMETERS:  Scope           - Scope to search&n; *              Name            - ACPI name to search for&n; *              Opcode          - Opcode to search for&n; *&n; * RETURN:      Op containing the name&n; *&n; * DESCRIPTION: Find name segment from a list of acpi_ops.  Searches a single&n; *              scope, no more.&n; *&n; ******************************************************************************/
r_static
id|ACPI_PARSE_OBJECT
op_star
DECL|function|acpi_ps_find_name
id|acpi_ps_find_name
(paren
id|ACPI_PARSE_OBJECT
op_star
id|scope
comma
id|u32
id|name
comma
id|u32
id|opcode
)paren
(brace
id|ACPI_PARSE_OBJECT
op_star
id|op
suffix:semicolon
id|ACPI_PARSE_OBJECT
op_star
id|field
suffix:semicolon
multiline_comment|/* search scope level for matching name segment */
id|op
op_assign
id|acpi_ps_get_child
(paren
id|scope
)paren
suffix:semicolon
r_while
c_loop
(paren
id|op
)paren
(brace
r_if
c_cond
(paren
id|acpi_ps_is_field_op
(paren
id|op-&gt;opcode
)paren
)paren
(brace
multiline_comment|/* Field, search named fields */
id|field
op_assign
id|acpi_ps_get_child
(paren
id|op
)paren
suffix:semicolon
r_while
c_loop
(paren
id|field
)paren
(brace
r_if
c_cond
(paren
id|acpi_ps_is_named_op
(paren
id|field-&gt;opcode
)paren
op_logical_and
id|acpi_ps_get_name
(paren
id|field
)paren
op_eq
id|name
op_logical_and
(paren
op_logical_neg
id|opcode
op_logical_or
id|field-&gt;opcode
op_eq
id|opcode
)paren
)paren
(brace
r_return
(paren
id|field
)paren
suffix:semicolon
)brace
id|field
op_assign
id|field-&gt;next
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|acpi_ps_is_create_field_op
(paren
id|op-&gt;opcode
)paren
)paren
(brace
r_if
c_cond
(paren
id|op-&gt;opcode
op_eq
id|AML_CREATE_FIELD_OP
)paren
(brace
id|field
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|3
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Create_xXXField, check name */
id|field
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|2
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|field
)paren
op_logical_and
(paren
id|field-&gt;value.string
)paren
op_logical_and
(paren
op_logical_neg
id|STRNCMP
(paren
id|field-&gt;value.string
comma
(paren
r_char
op_star
)paren
op_amp
id|name
comma
id|ACPI_NAME_SIZE
)paren
)paren
)paren
(brace
r_return
(paren
id|op
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
(paren
id|acpi_ps_is_named_op
(paren
id|op-&gt;opcode
)paren
)paren
op_logical_and
(paren
id|acpi_ps_get_name
(paren
id|op
)paren
op_eq
id|name
)paren
op_logical_and
(paren
op_logical_neg
id|opcode
op_logical_or
id|op-&gt;opcode
op_eq
id|opcode
op_logical_or
id|opcode
op_eq
id|AML_SCOPE_OP
)paren
)paren
(brace
r_break
suffix:semicolon
)brace
id|op
op_assign
id|op-&gt;next
suffix:semicolon
)brace
r_return
(paren
id|op
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_find&n; *&n; * PARAMETERS:  Scope           - Where to begin the search&n; *              Path            - ACPI Path to the named object&n; *              Opcode          - Opcode associated with the object&n; *              Create          - if TRUE, create the object if not found.&n; *&n; * RETURN:      Op if found, NULL otherwise.&n; *&n; * DESCRIPTION: Find object within scope&n; *&n; ******************************************************************************/
id|ACPI_PARSE_OBJECT
op_star
DECL|function|acpi_ps_find
id|acpi_ps_find
(paren
id|ACPI_PARSE_OBJECT
op_star
id|scope
comma
id|NATIVE_CHAR
op_star
id|path
comma
id|u16
id|opcode
comma
id|u32
id|create
)paren
(brace
id|u32
id|seg_count
suffix:semicolon
id|u32
id|name
suffix:semicolon
id|u32
id|name_op
suffix:semicolon
id|ACPI_PARSE_OBJECT
op_star
id|op
op_assign
l_int|NULL
suffix:semicolon
id|u8
id|unprefixed
op_assign
id|TRUE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scope
op_logical_or
op_logical_neg
id|path
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|acpi_gbl_ps_find_count
op_increment
suffix:semicolon
multiline_comment|/* Handle all prefixes in the name path */
r_while
c_loop
(paren
id|acpi_ps_is_prefix_char
(paren
id|GET8
(paren
id|path
)paren
)paren
)paren
(brace
r_switch
c_cond
(paren
id|GET8
(paren
id|path
)paren
)paren
(brace
r_case
l_char|&squot;&bslash;&bslash;&squot;
suffix:colon
multiline_comment|/* Could just use a global for &quot;root scope&quot; here */
r_while
c_loop
(paren
id|scope-&gt;parent
)paren
(brace
id|scope
op_assign
id|scope-&gt;parent
suffix:semicolon
)brace
multiline_comment|/* get first object within the scope */
multiline_comment|/* TBD: [Investigate] OR - set next in root scope to point to the same value as arg */
multiline_comment|/* Scope = Scope-&gt;Value.Arg; */
r_break
suffix:semicolon
r_case
l_char|&squot;^&squot;
suffix:colon
multiline_comment|/* Go up to the next valid scoping Op (method, scope, etc.) */
r_if
c_cond
(paren
id|acpi_ps_get_parent
(paren
id|scope
)paren
)paren
(brace
id|scope
op_assign
id|acpi_ps_get_parent
(paren
id|scope
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|unprefixed
op_assign
id|FALSE
suffix:semicolon
id|path
op_increment
suffix:semicolon
)brace
multiline_comment|/* get name segment count */
r_switch
c_cond
(paren
id|GET8
(paren
id|path
)paren
)paren
(brace
r_case
l_char|&squot;&bslash;0&squot;
suffix:colon
id|seg_count
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Null name case */
r_if
c_cond
(paren
id|unprefixed
)paren
(brace
id|op
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|op
op_assign
id|scope
suffix:semicolon
)brace
r_return
(paren
id|op
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_DUAL_NAME_PREFIX
suffix:colon
id|seg_count
op_assign
l_int|2
suffix:semicolon
id|path
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_MULTI_NAME_PREFIX_OP
suffix:colon
id|seg_count
op_assign
id|GET8
(paren
id|path
op_plus
l_int|1
)paren
suffix:semicolon
id|path
op_add_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|seg_count
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* match each name segment */
r_while
c_loop
(paren
id|scope
op_logical_and
id|seg_count
)paren
(brace
id|MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|name
comma
id|path
)paren
suffix:semicolon
id|path
op_add_assign
l_int|4
suffix:semicolon
id|seg_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|seg_count
)paren
(brace
id|name_op
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|name_op
op_assign
id|opcode
suffix:semicolon
)brace
id|op
op_assign
id|acpi_ps_find_name
(paren
id|scope
comma
id|name
comma
id|name_op
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
r_if
c_cond
(paren
id|create
)paren
(brace
multiline_comment|/* Create a new Scope level */
r_if
c_cond
(paren
id|seg_count
)paren
(brace
id|op
op_assign
id|acpi_ps_alloc_op
(paren
id|AML_SCOPE_OP
)paren
suffix:semicolon
)brace
r_else
(brace
id|op
op_assign
id|acpi_ps_alloc_op
(paren
id|opcode
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op
)paren
(brace
id|acpi_ps_set_name
(paren
id|op
comma
id|name
)paren
suffix:semicolon
id|acpi_ps_append_arg
(paren
id|scope
comma
id|op
)paren
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|unprefixed
)paren
(brace
multiline_comment|/* Search higher scopes for unprefixed name */
r_while
c_loop
(paren
op_logical_neg
id|op
op_logical_and
id|scope-&gt;parent
)paren
(brace
id|scope
op_assign
id|scope-&gt;parent
suffix:semicolon
id|op
op_assign
id|acpi_ps_find_name
(paren
id|scope
comma
id|name
comma
id|opcode
)paren
suffix:semicolon
)brace
)brace
)brace
id|unprefixed
op_assign
id|FALSE
suffix:semicolon
id|scope
op_assign
id|op
suffix:semicolon
)brace
r_return
(paren
id|op
)paren
suffix:semicolon
)brace
eof
