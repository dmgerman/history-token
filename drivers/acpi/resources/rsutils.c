multiline_comment|/*******************************************************************************&n; *&n; * Module Name: rsutils - Utilities for the resource manager&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acresrc.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_RESOURCES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;rsutils&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_get_prt_method_data&n; *&n; * PARAMETERS:  Handle          - a handle to the containing object&n; *              ret_buffer      - a pointer to a buffer structure for the&n; *                                  results&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get the _PRT value of an object&n; *              contained in an object specified by the handle passed in&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the contents of the callers buffer is undefined.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_get_prt_method_data
id|acpi_rs_get_prt_method_data
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_get_prt_method_data&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameters guaranteed valid by caller */
multiline_comment|/*&n;&t; * Execute the method, no parameters&n;&t; */
id|status
op_assign
id|acpi_ut_evaluate_object
(paren
id|handle
comma
l_string|&quot;_PRT&quot;
comma
id|ACPI_BTYPE_PACKAGE
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
multiline_comment|/* On exit, we must delete the object returned by evaluate_object */
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_get_crs_method_data&n; *&n; * PARAMETERS:  Handle          - a handle to the containing object&n; *              ret_buffer      - a pointer to a buffer structure for the&n; *                                  results&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get the _CRS value of an object&n; *              contained in an object specified by the handle passed in&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the contents of the callers buffer is undefined.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_get_crs_method_data
id|acpi_rs_get_crs_method_data
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_get_crs_method_data&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameters guaranteed valid by caller */
multiline_comment|/*&n;&t; * Execute the method, no parameters&n;&t; */
id|status
op_assign
id|acpi_ut_evaluate_object
(paren
id|handle
comma
l_string|&quot;_CRS&quot;
comma
id|ACPI_BTYPE_BUFFER
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
multiline_comment|/* on exit, we must delete the object returned by evaluate_object */
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_get_prs_method_data&n; *&n; * PARAMETERS:  Handle          - a handle to the containing object&n; *              ret_buffer      - a pointer to a buffer structure for the&n; *                                  results&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get the _PRS value of an object&n; *              contained in an object specified by the handle passed in&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the contents of the callers buffer is undefined.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_get_prs_method_data
id|acpi_rs_get_prs_method_data
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_get_prs_method_data&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameters guaranteed valid by caller */
multiline_comment|/*&n;&t; * Execute the method, no parameters&n;&t; */
id|status
op_assign
id|acpi_ut_evaluate_object
(paren
id|handle
comma
l_string|&quot;_PRS&quot;
comma
id|ACPI_BTYPE_BUFFER
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
multiline_comment|/* on exit, we must delete the object returned by evaluate_object */
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_get_method_data&n; *&n; * PARAMETERS:  Handle          - a handle to the containing object&n; *              ret_buffer      - a pointer to a buffer structure for the&n; *                                  results&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get the _CRS or _PRS value of an&n; *              object contained in an object specified by the handle passed in&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the contents of the callers buffer is undefined.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_get_method_data
id|acpi_rs_get_method_data
(paren
id|acpi_handle
id|handle
comma
r_char
op_star
id|path
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_get_method_data&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameters guaranteed valid by caller */
multiline_comment|/*&n;&t; * Execute the method, no parameters&n;&t; */
id|status
op_assign
id|acpi_ut_evaluate_object
(paren
id|handle
comma
id|path
comma
id|ACPI_BTYPE_BUFFER
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
multiline_comment|/*&n;&t; * Make the call to create a resource linked list from the&n;&t; * byte stream buffer that comes back from the method&n;&t; * execution.&n;&t; */
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_rs_set_srs_method_data&n; *&n; * PARAMETERS:  Handle          - a handle to the containing object&n; *              in_buffer       - a pointer to a buffer structure of the&n; *                                  parameter&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to set the _SRS of an object contained&n; *              in an object specified by the handle passed in&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the contents of the callers buffer is undefined.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_rs_set_srs_method_data
id|acpi_rs_set_srs_method_data
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_buffer
op_star
id|in_buffer
)paren
(brace
r_union
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
r_struct
id|acpi_buffer
id|buffer
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;rs_set_srs_method_data&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameters guaranteed valid by caller */
multiline_comment|/*&n;&t; * The in_buffer parameter will point to a linked list of&n;&t; * resource parameters.  It needs to be formatted into a&n;&t; * byte stream to be sent in as an input parameter to _SRS&n;&t; *&n;&t; * Convert the linked list into a byte stream&n;&t; */
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
multiline_comment|/*&n;&t; * Clean up and return the status from acpi_ns_evaluate_relative&n;&t; */
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
