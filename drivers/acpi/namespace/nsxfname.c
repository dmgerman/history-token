multiline_comment|/******************************************************************************&n; *&n; * Module Name: nsxfname - Public interfaces to the ACPI subsystem&n; *                         ACPI Namespace oriented interfaces&n; *              $Revision: 93 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_NAMESPACE
id|ACPI_MODULE_NAME
(paren
l_string|&quot;nsxfname&quot;
)paren
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    Acpi_get_handle&n; *&n; * PARAMETERS:  Parent          - Object to search under (search scope).&n; *              Path_name       - Pointer to an asciiz string containing the&n; *                                  name&n; *              Ret_handle      - Where the return handle is placed&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This routine will search for a caller specified name in the&n; *              name space.  The caller can restrict the search region by&n; *              specifying a non NULL parent.  The parent value is itself a&n; *              namespace handle.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_handle
id|acpi_get_handle
(paren
id|acpi_handle
id|parent
comma
id|acpi_string
id|pathname
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
op_assign
l_int|NULL
suffix:semicolon
id|acpi_namespace_node
op_star
id|prefix_node
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/* Parameter Validation */
r_if
c_cond
(paren
op_logical_neg
id|ret_handle
op_logical_or
op_logical_neg
id|pathname
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Convert a parent handle to a prefix node */
r_if
c_cond
(paren
id|parent
)paren
(brace
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
id|prefix_node
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
id|prefix_node
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
id|status
op_assign
id|acpi_ut_release_mutex
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
)brace
multiline_comment|/* Special case for root, since we can&squot;t search for it */
r_if
c_cond
(paren
id|ACPI_STRCMP
(paren
id|pathname
comma
id|ACPI_NS_ROOT_PATH
)paren
op_eq
l_int|0
)paren
(brace
op_star
id|ret_handle
op_assign
id|acpi_ns_convert_entry_to_handle
(paren
id|acpi_gbl_root_node
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *  Find the Node and convert to a handle&n;&t; */
id|status
op_assign
id|acpi_ns_get_node_by_path
(paren
id|pathname
comma
id|prefix_node
comma
id|ACPI_NS_NO_UPSEARCH
comma
op_amp
id|node
)paren
suffix:semicolon
op_star
id|ret_handle
op_assign
l_int|NULL
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
op_star
id|ret_handle
op_assign
id|acpi_ns_convert_entry_to_handle
(paren
id|node
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    Acpi_get_name&n; *&n; * PARAMETERS:  Handle          - Handle to be converted to a pathname&n; *              Name_type       - Full pathname or single segment&n; *              Buffer          - Buffer for returned path&n; *&n; * RETURN:      Pointer to a string containing the fully qualified Name.&n; *&n; * DESCRIPTION: This routine returns the fully qualified name associated with&n; *              the Handle parameter.  This and the Acpi_pathname_to_handle are&n; *              complementary functions.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_name
id|acpi_get_name
(paren
id|acpi_handle
id|handle
comma
id|u32
id|name_type
comma
id|acpi_buffer
op_star
id|buffer
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
id|name_type
OG
id|ACPI_NAME_TYPE_MAX
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
id|acpi_ut_validate_buffer
(paren
id|buffer
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
r_if
c_cond
(paren
id|name_type
op_eq
id|ACPI_FULL_PATHNAME
)paren
(brace
multiline_comment|/* Get the full pathname (From the namespace root) */
id|status
op_assign
id|acpi_ns_handle_to_pathname
(paren
id|handle
comma
id|buffer
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Wants the single segment ACPI name.&n;&t; * Validate handle and convert to a namespace Node&n;&t; */
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
multiline_comment|/* Validate/Allocate/Clear caller buffer */
id|status
op_assign
id|acpi_ut_initialize_buffer
(paren
id|buffer
comma
id|ACPI_PATH_SEGMENT_LENGTH
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
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Just copy the ACPI name from the Node and zero terminate it */
id|ACPI_STRNCPY
(paren
id|buffer-&gt;pointer
comma
id|node-&gt;name.ascii
comma
id|ACPI_NAME_SIZE
)paren
suffix:semicolon
(paren
(paren
r_char
op_star
)paren
id|buffer-&gt;pointer
)paren
(braket
id|ACPI_NAME_SIZE
)braket
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|AE_OK
suffix:semicolon
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
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    Acpi_get_object_info&n; *&n; * PARAMETERS:  Handle          - Object Handle&n; *              Info            - Where the info is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Returns information about an object as gleaned from the&n; *              namespace node and possibly by running several standard&n; *              control methods (Such as in the case of a device.)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_object_info
id|acpi_get_object_info
(paren
id|acpi_handle
id|handle
comma
id|acpi_device_info
op_star
id|info
)paren
(brace
id|acpi_device_id
id|hid
suffix:semicolon
id|acpi_device_id
id|uid
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|u32
id|device_status
op_assign
l_int|0
suffix:semicolon
id|acpi_integer
id|address
op_assign
l_int|0
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
op_logical_neg
id|handle
op_logical_or
op_logical_neg
id|info
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
id|info-&gt;type
op_assign
id|node-&gt;type
suffix:semicolon
id|info-&gt;name
op_assign
id|node-&gt;name.integer
suffix:semicolon
id|status
op_assign
id|acpi_ut_release_mutex
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
multiline_comment|/*&n;&t; * If not a device, we are all done.&n;&t; */
r_if
c_cond
(paren
id|info-&gt;type
op_ne
id|ACPI_TYPE_DEVICE
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get extra info for ACPI devices only.  Run the&n;&t; * _HID, _UID, _STA, and _ADR methods.  Note: none&n;&t; * of these methods are required, so they may or may&n;&t; * not be present.  The Info-&gt;Valid bits are used&n;&t; * to indicate which methods ran successfully.&n;&t; */
id|info-&gt;valid
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Execute the _HID method and save the result */
id|status
op_assign
id|acpi_ut_execute_HID
(paren
id|node
comma
op_amp
id|hid
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
id|ACPI_STRNCPY
(paren
id|info-&gt;hardware_id
comma
id|hid.buffer
comma
r_sizeof
(paren
id|info-&gt;hardware_id
)paren
)paren
suffix:semicolon
id|info-&gt;valid
op_or_assign
id|ACPI_VALID_HID
suffix:semicolon
)brace
multiline_comment|/* Execute the _UID method and save the result */
id|status
op_assign
id|acpi_ut_execute_UID
(paren
id|node
comma
op_amp
id|uid
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
id|ACPI_STRCPY
(paren
id|info-&gt;unique_id
comma
id|uid.buffer
)paren
suffix:semicolon
id|info-&gt;valid
op_or_assign
id|ACPI_VALID_UID
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Execute the _STA method and save the result&n;&t; * _STA is not always present&n;&t; */
id|status
op_assign
id|acpi_ut_execute_STA
(paren
id|node
comma
op_amp
id|device_status
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
id|info-&gt;current_status
op_assign
id|device_status
suffix:semicolon
id|info-&gt;valid
op_or_assign
id|ACPI_VALID_STA
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Execute the _ADR method and save result if successful&n;&t; * _ADR is not always present&n;&t; */
id|status
op_assign
id|acpi_ut_evaluate_numeric_object
(paren
id|METHOD_NAME__ADR
comma
id|node
comma
op_amp
id|address
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
id|info-&gt;address
op_assign
id|address
suffix:semicolon
id|info-&gt;valid
op_or_assign
id|ACPI_VALID_ADR
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
