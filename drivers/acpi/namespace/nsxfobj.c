multiline_comment|/*******************************************************************************&n; *&n; * Module Name: nsxfobj - Public interfaces to the ACPI subsystem&n; *                         ACPI Object oriented interfaces&n; *              $Revision: 114 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nsxfobj&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_get_type&n; *&n; * PARAMETERS:  Handle          - Handle of object whose type is desired&n; *              *Ret_type       - Where the type will be placed&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This routine returns the type associatd with a particular handle&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_type
id|acpi_get_type
(paren
id|acpi_handle
id|handle
comma
id|acpi_object_type
op_star
id|ret_type
)paren
(brace
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
multiline_comment|/* Parameter Validation */
r_if
c_cond
(paren
op_logical_neg
id|ret_type
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Special case for the predefined Root Node&n;&t; * (return type ANY)&n;&t; */
r_if
c_cond
(paren
id|handle
op_eq
id|ACPI_ROOT_OBJECT
)paren
(brace
op_star
id|ret_type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_NAMESPACE
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert and validate the handle */
id|node
op_assign
id|acpi_ns_map_handle_to_node
(paren
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
op_star
id|ret_type
op_assign
id|node-&gt;type
suffix:semicolon
id|status
op_assign
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_get_parent&n; *&n; * PARAMETERS:  Handle          - Handle of object whose parent is desired&n; *              Ret_handle      - Where the parent handle will be placed&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Returns a handle to the parent of the object represented by&n; *              Handle.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_parent
id|acpi_get_parent
(paren
id|acpi_handle
id|handle
comma
id|acpi_handle
op_star
id|ret_handle
)paren
(brace
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ret_handle
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Special case for the predefined Root Node (no parent) */
r_if
c_cond
(paren
id|handle
op_eq
id|ACPI_ROOT_OBJECT
)paren
(brace
r_return
(paren
id|AE_NULL_ENTRY
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_NAMESPACE
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert and validate the handle */
id|node
op_assign
id|acpi_ns_map_handle_to_node
(paren
id|handle
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Get the parent entry */
op_star
id|ret_handle
op_assign
id|acpi_ns_convert_entry_to_handle
(paren
id|acpi_ns_get_parent_node
(paren
id|node
)paren
)paren
suffix:semicolon
multiline_comment|/* Return exception if parent is null */
r_if
c_cond
(paren
op_logical_neg
id|acpi_ns_get_parent_node
(paren
id|node
)paren
)paren
(brace
id|status
op_assign
id|AE_NULL_ENTRY
suffix:semicolon
)brace
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_get_next_object&n; *&n; * PARAMETERS:  Type            - Type of object to be searched for&n; *              Parent          - Parent object whose children we are getting&n; *              Last_child      - Previous child that was found.&n; *                                The NEXT child will be returned&n; *              Ret_handle      - Where handle to the next object is placed&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Return the next peer object within the namespace.  If Handle is&n; *              valid, Scope is ignored.  Otherwise, the first object within&n; *              Scope is returned.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_next_object
id|acpi_get_next_object
(paren
id|acpi_object_type
id|type
comma
id|acpi_handle
id|parent
comma
id|acpi_handle
id|child
comma
id|acpi_handle
op_star
id|ret_handle
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_namespace_node
op_star
id|parent_node
op_assign
l_int|NULL
suffix:semicolon
id|acpi_namespace_node
op_star
id|child_node
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
id|type
OG
id|ACPI_TYPE_EXTERNAL_MAX
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_NAMESPACE
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* If null handle, use the parent */
r_if
c_cond
(paren
op_logical_neg
id|child
)paren
(brace
multiline_comment|/* Start search at the beginning of the specified scope */
id|parent_node
op_assign
id|acpi_ns_map_handle_to_node
(paren
id|parent
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parent_node
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Non-null handle, ignore the parent */
multiline_comment|/* Convert and validate the handle */
id|child_node
op_assign
id|acpi_ns_map_handle_to_node
(paren
id|child
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|child_node
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
)brace
multiline_comment|/* Internal function does the real work */
id|node
op_assign
id|acpi_ns_get_next_node
(paren
id|type
comma
id|parent_node
comma
id|child_node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|status
op_assign
id|AE_NOT_FOUND
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret_handle
)paren
(brace
op_star
id|ret_handle
op_assign
id|acpi_ns_convert_entry_to_handle
(paren
id|node
)paren
suffix:semicolon
)brace
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
