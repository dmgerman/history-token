multiline_comment|/*******************************************************************************&n; *&n; * Module Name: rsutils - Utilities for the resource manager&n; *              $Revision: 33 $&n; *&n; ******************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acresrc.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_RESOURCES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;rsutils&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_rs_get_prt_method_data&n; *&n; * PARAMETERS:  Handle          - a handle to the containing object&n; *              Ret_buffer      - a pointer to a buffer structure for the&n; *                                  results&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get the _PRT value of an object&n; *              contained in an object specified by the handle passed in&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the contents of the callers buffer is undefined.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_get_prt_method_data
id|acpi_rs_get_prt_method_data
(paren
id|acpi_handle
id|handle
comma
id|acpi_buffer
op_star
id|ret_buffer
)paren
(brace
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Rs_get_prt_method_data&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameters guaranteed valid by caller */
multiline_comment|/*&n;&t; *  Execute the method, no parameters&n;&t; */
id|status
op_assign
id|acpi_ns_evaluate_relative
(paren
id|handle
comma
l_string|&quot;_PRT&quot;
comma
l_int|NULL
comma
op_amp
id|obj_desc
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
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
multiline_comment|/* Return object is required */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;No object was returned from _PRT&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The return object must be a package, so check the parameters.  If the&n;&t; * return object is not a package, then the underlying AML code is corrupt&n;&t; * or improperly written.&n;&t; */
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_ne
id|ACPI_TYPE_PACKAGE
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;_PRT did not return a Package, returned %s&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_OPERAND_TYPE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Create a resource linked list from the byte stream buffer that comes&n;&t; * back from the _CRS method execution.&n;&t; */
id|status
op_assign
id|acpi_rs_create_pci_routing_table
(paren
id|obj_desc
comma
id|ret_buffer
)paren
suffix:semicolon
multiline_comment|/* On exit, we must delete the object returned by Evaluate_object */
id|cleanup
suffix:colon
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_rs_get_crs_method_data&n; *&n; * PARAMETERS:  Handle          - a handle to the containing object&n; *              Ret_buffer      - a pointer to a buffer structure for the&n; *                                  results&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get the _CRS value of an object&n; *              contained in an object specified by the handle passed in&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the contents of the callers buffer is undefined.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_get_crs_method_data
id|acpi_rs_get_crs_method_data
(paren
id|acpi_handle
id|handle
comma
id|acpi_buffer
op_star
id|ret_buffer
)paren
(brace
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Rs_get_crs_method_data&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameters guaranteed valid by caller */
multiline_comment|/*&n;&t; * Execute the method, no parameters&n;&t; */
id|status
op_assign
id|acpi_ns_evaluate_relative
(paren
id|handle
comma
l_string|&quot;_CRS&quot;
comma
l_int|NULL
comma
op_amp
id|obj_desc
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
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
multiline_comment|/* Return object is required */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;No object was returned from _CRS&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The return object will be a buffer, but check the&n;&t; * parameters.  If the return object is not a buffer,&n;&t; * then the underlying AML code is corrupt or improperly&n;&t; * written.&n;&t; */
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_ne
id|ACPI_TYPE_BUFFER
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;_CRS did not return a Buffer, returned %s&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_OPERAND_TYPE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Make the call to create a resource linked list from the&n;&t; * byte stream buffer that comes back from the _CRS method&n;&t; * execution.&n;&t; */
id|status
op_assign
id|acpi_rs_create_resource_list
(paren
id|obj_desc
comma
id|ret_buffer
)paren
suffix:semicolon
multiline_comment|/* On exit, we must delete the object returned by evaluate_object */
id|cleanup
suffix:colon
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_rs_get_prs_method_data&n; *&n; * PARAMETERS:  Handle          - a handle to the containing object&n; *              Ret_buffer      - a pointer to a buffer structure for the&n; *                                  results&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get the _PRS value of an object&n; *              contained in an object specified by the handle passed in&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the contents of the callers buffer is undefined.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_get_prs_method_data
id|acpi_rs_get_prs_method_data
(paren
id|acpi_handle
id|handle
comma
id|acpi_buffer
op_star
id|ret_buffer
)paren
(brace
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Rs_get_prs_method_data&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameters guaranteed valid by caller */
multiline_comment|/*&n;&t; * Execute the method, no parameters&n;&t; */
id|status
op_assign
id|acpi_ns_evaluate_relative
(paren
id|handle
comma
l_string|&quot;_PRS&quot;
comma
l_int|NULL
comma
op_amp
id|obj_desc
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
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
multiline_comment|/* Return object is required */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;No object was returned from _PRS&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The return object will be a buffer, but check the&n;&t; * parameters.  If the return object is not a buffer,&n;&t; * then the underlying AML code is corrupt or improperly&n;&t; * written..&n;&t; */
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_ne
id|ACPI_TYPE_BUFFER
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;_PRS did not return a Buffer, returned %s&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_OPERAND_TYPE
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Make the call to create a resource linked list from the&n;&t; * byte stream buffer that comes back from the _CRS method&n;&t; * execution.&n;&t; */
id|status
op_assign
id|acpi_rs_create_resource_list
(paren
id|obj_desc
comma
id|ret_buffer
)paren
suffix:semicolon
multiline_comment|/* On exit, we must delete the object returned by evaluate_object */
id|cleanup
suffix:colon
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_rs_set_srs_method_data&n; *&n; * PARAMETERS:  Handle          - a handle to the containing object&n; *              In_buffer       - a pointer to a buffer structure of the&n; *                                  parameter&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to set the _SRS of an object contained&n; *              in an object specified by the handle passed in&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the contents of the callers buffer is undefined.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_set_srs_method_data
id|acpi_rs_set_srs_method_data
(paren
id|acpi_handle
id|handle
comma
id|acpi_buffer
op_star
id|in_buffer
)paren
(brace
id|acpi_operand_object
op_star
id|params
(braket
l_int|2
)braket
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_buffer
id|buffer
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Rs_set_srs_method_data&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameters guaranteed valid by caller */
multiline_comment|/*&n;&t; * The In_buffer parameter will point to a linked list of&n;&t; * resource parameters.  It needs to be formatted into a&n;&t; * byte stream to be sent in as an input parameter to _SRS&n;&t; *&n;&t; * Convert the linked list into a byte stream&n;&t; */
id|buffer.length
op_assign
id|ACPI_ALLOCATE_LOCAL_BUFFER
suffix:semicolon
id|status
op_assign
id|acpi_rs_create_byte_stream
(paren
id|in_buffer-&gt;pointer
comma
op_amp
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Init the param object&n;&t; */
id|params
(braket
l_int|0
)braket
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_BUFFER
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|params
(braket
l_int|0
)braket
)paren
(brace
id|acpi_os_free
(paren
id|buffer.pointer
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Set up the parameter object&n;&t; */
id|params
(braket
l_int|0
)braket
op_member_access_from_pointer
id|buffer.length
op_assign
(paren
id|u32
)paren
id|buffer.length
suffix:semicolon
id|params
(braket
l_int|0
)braket
op_member_access_from_pointer
id|buffer.pointer
op_assign
id|buffer.pointer
suffix:semicolon
id|params
(braket
l_int|0
)braket
op_member_access_from_pointer
id|common.flags
op_assign
id|AOPOBJ_DATA_VALID
suffix:semicolon
id|params
(braket
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n;&t; * Execute the method, no return value&n;&t; */
id|status
op_assign
id|acpi_ns_evaluate_relative
(paren
id|handle
comma
l_string|&quot;_SRS&quot;
comma
id|params
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Clean up and return the status from Acpi_ns_evaluate_relative&n;&t; */
id|acpi_ut_remove_reference
(paren
id|params
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
