multiline_comment|/*******************************************************************************&n; *&n; * Module Name: rsxface - Public interfaces to the resource manager&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acresrc.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_RESOURCES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;rsxface&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_get_irq_routing_table&n; *&n; * PARAMETERS:  device_handle   - a handle to the Bus device we are querying&n; *              ret_buffer      - a pointer to a buffer to receive the&n; *                                current resources for the device&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get the IRQ routing table for a&n; *              specific bus.  The caller must first acquire a handle for the&n; *              desired bus.  The routine table is placed in the buffer pointed&n; *              to by the ret_buffer variable parameter.&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the value of ret_buffer is undefined.&n; *&n; *              This function attempts to execute the _PRT method contained in&n; *              the object indicated by the passed device_handle.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_irq_routing_table
id|acpi_get_irq_routing_table
(paren
id|acpi_handle
id|device_handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_irq_routing_table &quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Must have a valid handle and buffer, So we have to have a handle&n;&t; * and a return buffer structure, and if there is a non-zero buffer length&n;&t; * we also need a valid pointer in the buffer. If it&squot;s a zero buffer length,&n;&t; * we&squot;ll be returning the needed buffer size, so keep going.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|device_handle
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_validate_buffer
(paren
id|ret_buffer
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
id|acpi_rs_get_prt_method_data
(paren
id|device_handle
comma
id|ret_buffer
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_get_current_resources&n; *&n; * PARAMETERS:  device_handle   - a handle to the device object for the&n; *                                device we are querying&n; *              ret_buffer      - a pointer to a buffer to receive the&n; *                                current resources for the device&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get the current resources for a&n; *              specific device.  The caller must first acquire a handle for&n; *              the desired device.  The resource data is placed in the buffer&n; *              pointed to by the ret_buffer variable parameter.&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the value of ret_buffer is undefined.&n; *&n; *              This function attempts to execute the _CRS method contained in&n; *              the object indicated by the passed device_handle.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_current_resources
id|acpi_get_current_resources
(paren
id|acpi_handle
id|device_handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_current_resources&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Must have a valid handle and buffer, So we have to have a handle&n;&t; * and a return buffer structure, and if there is a non-zero buffer length&n;&t; * we also need a valid pointer in the buffer. If it&squot;s a zero buffer length,&n;&t; * we&squot;ll be returning the needed buffer size, so keep going.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|device_handle
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_validate_buffer
(paren
id|ret_buffer
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
id|acpi_rs_get_crs_method_data
(paren
id|device_handle
comma
id|ret_buffer
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_get_possible_resources&n; *&n; * PARAMETERS:  device_handle   - a handle to the device object for the&n; *                                device we are querying&n; *              ret_buffer      - a pointer to a buffer to receive the&n; *                                resources for the device&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to get a list of the possible resources&n; *              for a specific device.  The caller must first acquire a handle&n; *              for the desired device.  The resource data is placed in the&n; *              buffer pointed to by the ret_buffer variable.&n; *&n; *              If the function fails an appropriate status will be returned&n; *              and the value of ret_buffer is undefined.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_get_possible_resources
id|acpi_get_possible_resources
(paren
id|acpi_handle
id|device_handle
comma
r_struct
id|acpi_buffer
op_star
id|ret_buffer
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_get_possible_resources&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Must have a valid handle and buffer, So we have to have a handle&n;&t; * and a return buffer structure, and if there is a non-zero buffer length&n;&t; * we also need a valid pointer in the buffer. If it&squot;s a zero buffer length,&n;&t; * we&squot;ll be returning the needed buffer size, so keep going.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|device_handle
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_validate_buffer
(paren
id|ret_buffer
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
id|acpi_rs_get_prs_method_data
(paren
id|device_handle
comma
id|ret_buffer
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_walk_resources&n; *&n; * PARAMETERS:  device_handle   - a handle to the device object for the&n; *                                device we are querying&n; *              Path            - method name of the resources we want&n; *                                (METHOD_NAME__CRS or METHOD_NAME__PRS)&n; *              user_function   - called for each resource&n; *              Context         - passed to user_function&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Retrieves the current or possible resource list for the&n; *              specified device.  The user_function is called once for&n; *              each resource in the list.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_walk_resources
id|acpi_walk_resources
(paren
id|acpi_handle
id|device_handle
comma
r_char
op_star
id|path
comma
id|ACPI_WALK_RESOURCE_CALLBACK
id|user_function
comma
r_void
op_star
id|context
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_buffer
id|buffer
op_assign
(brace
id|ACPI_ALLOCATE_BUFFER
comma
l_int|NULL
)brace
suffix:semicolon
r_struct
id|acpi_resource
op_star
id|resource
suffix:semicolon
r_struct
id|acpi_resource
op_star
id|buffer_end
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_walk_resources&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device_handle
op_logical_or
(paren
id|ACPI_STRNCMP
(paren
id|path
comma
id|METHOD_NAME__CRS
comma
r_sizeof
(paren
id|METHOD_NAME__CRS
)paren
)paren
op_logical_and
id|ACPI_STRNCMP
(paren
id|path
comma
id|METHOD_NAME__PRS
comma
r_sizeof
(paren
id|METHOD_NAME__PRS
)paren
)paren
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_rs_get_method_data
(paren
id|device_handle
comma
id|path
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
multiline_comment|/* Setup pointers */
id|resource
op_assign
(paren
r_struct
id|acpi_resource
op_star
)paren
id|buffer.pointer
suffix:semicolon
id|buffer_end
op_assign
id|ACPI_CAST_PTR
(paren
r_struct
id|acpi_resource
comma
(paren
(paren
id|u8
op_star
)paren
id|buffer.pointer
op_plus
id|buffer.length
)paren
)paren
suffix:semicolon
multiline_comment|/* Walk the resource list */
r_for
c_loop
(paren
suffix:semicolon
suffix:semicolon
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|resource
op_logical_or
id|resource-&gt;id
op_eq
id|ACPI_RSTYPE_END_TAG
)paren
(brace
r_break
suffix:semicolon
)brace
id|status
op_assign
id|user_function
(paren
id|resource
comma
id|context
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|status
)paren
(brace
r_case
id|AE_OK
suffix:colon
r_case
id|AE_CTRL_DEPTH
suffix:colon
multiline_comment|/* Just keep going */
id|status
op_assign
id|AE_OK
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AE_CTRL_TERMINATE
suffix:colon
multiline_comment|/* Exit now, with OK stats */
id|status
op_assign
id|AE_OK
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All others are valid exceptions */
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Get the next resource descriptor */
id|resource
op_assign
id|ACPI_NEXT_RESOURCE
(paren
id|resource
)paren
suffix:semicolon
multiline_comment|/* Check for end-of-buffer */
r_if
c_cond
(paren
id|resource
op_ge
id|buffer_end
)paren
(brace
r_goto
id|cleanup
suffix:semicolon
)brace
)brace
id|cleanup
suffix:colon
id|acpi_os_free
(paren
id|buffer.pointer
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_set_current_resources&n; *&n; * PARAMETERS:  device_handle   - a handle to the device object for the&n; *                                device we are changing the resources of&n; *              in_buffer       - a pointer to a buffer containing the&n; *                                resources to be set for the device&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to set the current resources for a&n; *              specific device.  The caller must first acquire a handle for&n; *              the desired device.  The resource data is passed to the routine&n; *              the buffer pointed to by the in_buffer variable.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_set_current_resources
id|acpi_set_current_resources
(paren
id|acpi_handle
id|device_handle
comma
r_struct
id|acpi_buffer
op_star
id|in_buffer
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_set_current_resources&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Must have a valid handle and buffer&n;&t; */
r_if
c_cond
(paren
(paren
op_logical_neg
id|device_handle
)paren
op_logical_or
(paren
op_logical_neg
id|in_buffer
)paren
op_logical_or
(paren
op_logical_neg
id|in_buffer-&gt;pointer
)paren
op_logical_or
(paren
op_logical_neg
id|in_buffer-&gt;length
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_rs_set_srs_method_data
(paren
id|device_handle
comma
id|in_buffer
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
DECL|macro|ACPI_COPY_FIELD
mdefine_line|#define ACPI_COPY_FIELD(out, in, field)  ((out)-&gt;field = (in)-&gt;field)
DECL|macro|ACPI_COPY_ADDRESS
mdefine_line|#define ACPI_COPY_ADDRESS(out, in)                      &bslash;&n;&t;ACPI_COPY_FIELD(out, in, resource_type);             &bslash;&n;&t;ACPI_COPY_FIELD(out, in, producer_consumer);         &bslash;&n;&t;ACPI_COPY_FIELD(out, in, decode);                    &bslash;&n;&t;ACPI_COPY_FIELD(out, in, min_address_fixed);         &bslash;&n;&t;ACPI_COPY_FIELD(out, in, max_address_fixed);         &bslash;&n;&t;ACPI_COPY_FIELD(out, in, attribute);                 &bslash;&n;&t;ACPI_COPY_FIELD(out, in, granularity);               &bslash;&n;&t;ACPI_COPY_FIELD(out, in, min_address_range);         &bslash;&n;&t;ACPI_COPY_FIELD(out, in, max_address_range);         &bslash;&n;&t;ACPI_COPY_FIELD(out, in, address_translation_offset); &bslash;&n;&t;ACPI_COPY_FIELD(out, in, address_length);            &bslash;&n;&t;ACPI_COPY_FIELD(out, in, resource_source);
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_resource_to_address64&n; *&n; * PARAMETERS:  resource                - Pointer to a resource&n; *              out                     - Pointer to the users&squot;s return&n; *                                        buffer (a struct&n; *                                        struct acpi_resource_address64)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: If the resource is an address16, address32, or address64,&n; *              copy it to the address64 return buffer.  This saves the&n; *              caller from having to duplicate code for different-sized&n; *              addresses.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_resource_to_address64
id|acpi_resource_to_address64
(paren
r_struct
id|acpi_resource
op_star
id|resource
comma
r_struct
id|acpi_resource_address64
op_star
id|out
)paren
(brace
r_struct
id|acpi_resource_address16
op_star
id|address16
suffix:semicolon
r_struct
id|acpi_resource_address32
op_star
id|address32
suffix:semicolon
r_switch
c_cond
(paren
id|resource-&gt;id
)paren
(brace
r_case
id|ACPI_RSTYPE_ADDRESS16
suffix:colon
id|address16
op_assign
(paren
r_struct
id|acpi_resource_address16
op_star
)paren
op_amp
id|resource-&gt;data
suffix:semicolon
id|ACPI_COPY_ADDRESS
c_func
(paren
id|out
comma
id|address16
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_ADDRESS32
suffix:colon
id|address32
op_assign
(paren
r_struct
id|acpi_resource_address32
op_star
)paren
op_amp
id|resource-&gt;data
suffix:semicolon
id|ACPI_COPY_ADDRESS
c_func
(paren
id|out
comma
id|address32
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_RSTYPE_ADDRESS64
suffix:colon
multiline_comment|/* Simple copy for 64 bit source */
id|ACPI_MEMCPY
(paren
id|out
comma
op_amp
id|resource-&gt;data
comma
r_sizeof
(paren
r_struct
id|acpi_resource_address64
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
