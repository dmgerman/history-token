multiline_comment|/******************************************************************************&n; *&n; * Module Name: utcopy - Internal to external object translation utilities&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_UTILITIES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;utcopy&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_isimple_to_esimple&n; *&n; * PARAMETERS:  *internal_object    - Pointer to the object we are examining&n; *              *Buffer             - Where the object is returned&n; *              *space_used         - Where the data length is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to place a simple object in a user&n; *              buffer.&n; *&n; *              The buffer is assumed to have sufficient space for the object.&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ut_copy_isimple_to_esimple
id|acpi_ut_copy_isimple_to_esimple
(paren
r_union
id|acpi_operand_object
op_star
id|internal_object
comma
r_union
id|acpi_object
op_star
id|external_object
comma
id|u8
op_star
id|data_space
comma
id|acpi_size
op_star
id|buffer_space_used
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_copy_isimple_to_esimple&quot;
)paren
suffix:semicolon
op_star
id|buffer_space_used
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; * Check for NULL object case (could be an uninitialized&n;&t; * package element)&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|internal_object
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Always clear the external object */
id|ACPI_MEMSET
(paren
id|external_object
comma
l_int|0
comma
r_sizeof
(paren
r_union
id|acpi_object
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * In general, the external object will be the same type as&n;&t; * the internal object&n;&t; */
id|external_object-&gt;type
op_assign
id|ACPI_GET_OBJECT_TYPE
(paren
id|internal_object
)paren
suffix:semicolon
multiline_comment|/* However, only a limited number of external types are supported */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|internal_object
)paren
)paren
(brace
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|external_object-&gt;string.pointer
op_assign
(paren
r_char
op_star
)paren
id|data_space
suffix:semicolon
id|external_object-&gt;string.length
op_assign
id|internal_object-&gt;string.length
suffix:semicolon
op_star
id|buffer_space_used
op_assign
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
(paren
id|acpi_size
)paren
id|internal_object-&gt;string.length
op_plus
l_int|1
)paren
suffix:semicolon
id|ACPI_MEMCPY
(paren
(paren
r_void
op_star
)paren
id|data_space
comma
(paren
r_void
op_star
)paren
id|internal_object-&gt;string.pointer
comma
(paren
id|acpi_size
)paren
id|internal_object-&gt;string.length
op_plus
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|external_object-&gt;buffer.pointer
op_assign
id|data_space
suffix:semicolon
id|external_object-&gt;buffer.length
op_assign
id|internal_object-&gt;buffer.length
suffix:semicolon
op_star
id|buffer_space_used
op_assign
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
id|internal_object-&gt;string.length
)paren
suffix:semicolon
id|ACPI_MEMCPY
(paren
(paren
r_void
op_star
)paren
id|data_space
comma
(paren
r_void
op_star
)paren
id|internal_object-&gt;buffer.pointer
comma
id|internal_object-&gt;buffer.length
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|external_object-&gt;integer.value
op_assign
id|internal_object-&gt;integer.value
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_REFERENCE
suffix:colon
multiline_comment|/*&n;&t;&t; * This is an object reference.  Attempt to dereference it.&n;&t;&t; */
r_switch
c_cond
(paren
id|internal_object-&gt;reference.opcode
)paren
(brace
r_case
id|AML_INT_NAMEPATH_OP
suffix:colon
multiline_comment|/* For namepath, return the object handle (&quot;reference&quot;) */
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Use the object type of &quot;Any&quot; to indicate a reference&n;&t;&t;&t; * to object containing a handle to an ACPI named object.&n;&t;&t;&t; */
id|external_object-&gt;type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
id|external_object-&gt;reference.handle
op_assign
id|internal_object-&gt;reference.node
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PROCESSOR
suffix:colon
id|external_object-&gt;processor.proc_id
op_assign
id|internal_object-&gt;processor.proc_id
suffix:semicolon
id|external_object-&gt;processor.pblk_address
op_assign
id|internal_object-&gt;processor.address
suffix:semicolon
id|external_object-&gt;processor.pblk_length
op_assign
id|internal_object-&gt;processor.length
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_POWER
suffix:colon
id|external_object-&gt;power_resource.system_level
op_assign
id|internal_object-&gt;power_resource.system_level
suffix:semicolon
id|external_object-&gt;power_resource.resource_order
op_assign
id|internal_object-&gt;power_resource.resource_order
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t; * There is no corresponding external object type&n;&t;&t; */
id|return_ACPI_STATUS
(paren
id|AE_SUPPORT
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_ielement_to_eelement&n; *&n; * PARAMETERS:  acpi_pkg_callback&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Copy one package element to another package element&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_copy_ielement_to_eelement
id|acpi_ut_copy_ielement_to_eelement
(paren
id|u8
id|object_type
comma
r_union
id|acpi_operand_object
op_star
id|source_object
comma
r_union
id|acpi_generic_state
op_star
id|state
comma
r_void
op_star
id|context
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_pkg_info
op_star
id|info
op_assign
(paren
r_struct
id|acpi_pkg_info
op_star
)paren
id|context
suffix:semicolon
id|acpi_size
id|object_space
suffix:semicolon
id|u32
id|this_index
suffix:semicolon
r_union
id|acpi_object
op_star
id|target_object
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
id|this_index
op_assign
id|state-&gt;pkg.index
suffix:semicolon
id|target_object
op_assign
(paren
r_union
id|acpi_object
op_star
)paren
op_amp
(paren
(paren
r_union
id|acpi_object
op_star
)paren
(paren
id|state-&gt;pkg.dest_object
)paren
)paren
op_member_access_from_pointer
id|package.elements
(braket
id|this_index
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|object_type
)paren
(brace
r_case
id|ACPI_COPY_TYPE_SIMPLE
suffix:colon
multiline_comment|/*&n;&t;&t; * This is a simple or null object&n;&t;&t; */
id|status
op_assign
id|acpi_ut_copy_isimple_to_esimple
(paren
id|source_object
comma
id|target_object
comma
id|info-&gt;free_space
comma
op_amp
id|object_space
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
r_break
suffix:semicolon
r_case
id|ACPI_COPY_TYPE_PACKAGE
suffix:colon
multiline_comment|/*&n;&t;&t; * Build the package object&n;&t;&t; */
id|target_object-&gt;type
op_assign
id|ACPI_TYPE_PACKAGE
suffix:semicolon
id|target_object-&gt;package.count
op_assign
id|source_object-&gt;package.count
suffix:semicolon
id|target_object-&gt;package.elements
op_assign
id|ACPI_CAST_PTR
(paren
r_union
id|acpi_object
comma
id|info-&gt;free_space
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Pass the new package object back to the package walk routine&n;&t;&t; */
id|state-&gt;pkg.this_target_obj
op_assign
id|target_object
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Save space for the array of objects (Package elements)&n;&t;&t; * update the buffer length counter&n;&t;&t; */
id|object_space
op_assign
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
(paren
id|acpi_size
)paren
id|target_object-&gt;package.count
op_star
r_sizeof
(paren
r_union
id|acpi_object
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
id|info-&gt;free_space
op_add_assign
id|object_space
suffix:semicolon
id|info-&gt;length
op_add_assign
id|object_space
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_ipackage_to_epackage&n; *&n; * PARAMETERS:  *internal_object    - Pointer to the object we are returning&n; *              *Buffer             - Where the object is returned&n; *              *space_used         - Where the object length is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to place a package object in a user&n; *              buffer.  A package object by definition contains other objects.&n; *&n; *              The buffer is assumed to have sufficient space for the object.&n; *              The caller must have verified the buffer length needed using the&n; *              acpi_ut_get_object_size function before calling this function.&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ut_copy_ipackage_to_epackage
id|acpi_ut_copy_ipackage_to_epackage
(paren
r_union
id|acpi_operand_object
op_star
id|internal_object
comma
id|u8
op_star
id|buffer
comma
id|acpi_size
op_star
id|space_used
)paren
(brace
r_union
id|acpi_object
op_star
id|external_object
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_pkg_info
id|info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_copy_ipackage_to_epackage&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * First package at head of the buffer&n;&t; */
id|external_object
op_assign
id|ACPI_CAST_PTR
(paren
r_union
id|acpi_object
comma
id|buffer
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Free space begins right after the first package&n;&t; */
id|info.length
op_assign
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
r_sizeof
(paren
r_union
id|acpi_object
)paren
)paren
suffix:semicolon
id|info.free_space
op_assign
id|buffer
op_plus
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
r_sizeof
(paren
r_union
id|acpi_object
)paren
)paren
suffix:semicolon
id|info.object_space
op_assign
l_int|0
suffix:semicolon
id|info.num_packages
op_assign
l_int|1
suffix:semicolon
id|external_object-&gt;type
op_assign
id|ACPI_GET_OBJECT_TYPE
(paren
id|internal_object
)paren
suffix:semicolon
id|external_object-&gt;package.count
op_assign
id|internal_object-&gt;package.count
suffix:semicolon
id|external_object-&gt;package.elements
op_assign
id|ACPI_CAST_PTR
(paren
r_union
id|acpi_object
comma
id|info.free_space
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Leave room for an array of ACPI_OBJECTS in the buffer&n;&t; * and move the free space past it&n;&t; */
id|info.length
op_add_assign
(paren
id|acpi_size
)paren
id|external_object-&gt;package.count
op_star
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
r_sizeof
(paren
r_union
id|acpi_object
)paren
)paren
suffix:semicolon
id|info.free_space
op_add_assign
id|external_object-&gt;package.count
op_star
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
r_sizeof
(paren
r_union
id|acpi_object
)paren
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_walk_package_tree
(paren
id|internal_object
comma
id|external_object
comma
id|acpi_ut_copy_ielement_to_eelement
comma
op_amp
id|info
)paren
suffix:semicolon
op_star
id|space_used
op_assign
id|info.length
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_iobject_to_eobject&n; *&n; * PARAMETERS:  *internal_object    - The internal object to be converted&n; *              *buffer_ptr         - Where the object is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to build an API object to be returned to&n; *              the caller.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_copy_iobject_to_eobject
id|acpi_ut_copy_iobject_to_eobject
(paren
r_union
id|acpi_operand_object
op_star
id|internal_object
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
l_string|&quot;ut_copy_iobject_to_eobject&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|internal_object
)paren
op_eq
id|ACPI_TYPE_PACKAGE
)paren
(brace
multiline_comment|/*&n;&t;&t; * Package object:  Copy all subobjects (including&n;&t;&t; * nested packages)&n;&t;&t; */
id|status
op_assign
id|acpi_ut_copy_ipackage_to_epackage
(paren
id|internal_object
comma
id|ret_buffer-&gt;pointer
comma
op_amp
id|ret_buffer-&gt;length
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Build a simple object (no nested objects)&n;&t;&t; */
id|status
op_assign
id|acpi_ut_copy_isimple_to_esimple
(paren
id|internal_object
comma
(paren
r_union
id|acpi_object
op_star
)paren
id|ret_buffer-&gt;pointer
comma
(paren
(paren
id|u8
op_star
)paren
id|ret_buffer-&gt;pointer
op_plus
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
r_sizeof
(paren
r_union
id|acpi_object
)paren
)paren
)paren
comma
op_amp
id|ret_buffer-&gt;length
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * build simple does not include the object size in the length&n;&t;&t; * so we add it in here&n;&t;&t; */
id|ret_buffer-&gt;length
op_add_assign
r_sizeof
(paren
r_union
id|acpi_object
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_esimple_to_isimple&n; *&n; * PARAMETERS:  *external_object   - The external object to be converted&n; *              *internal_object   - Where the internal object is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function copies an external object to an internal one.&n; *              NOTE: Pointers can be copied, we don&squot;t need to copy data.&n; *              (The pointers have to be valid in our address space no matter&n; *              what we do with them!)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_copy_esimple_to_isimple
id|acpi_ut_copy_esimple_to_isimple
(paren
r_union
id|acpi_object
op_star
id|external_object
comma
r_union
id|acpi_operand_object
op_star
op_star
id|ret_internal_object
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|internal_object
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_copy_esimple_to_isimple&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Simple types supported are: String, Buffer, Integer&n;&t; */
r_switch
c_cond
(paren
id|external_object-&gt;type
)paren
(brace
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|internal_object
op_assign
id|acpi_ut_create_internal_object
(paren
(paren
id|u8
)paren
id|external_object-&gt;type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|internal_object
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t; * Whatever other type -- it is not supported&n;&t;&t; */
id|return_ACPI_STATUS
(paren
id|AE_SUPPORT
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|external_object-&gt;type
)paren
(brace
multiline_comment|/* Must COPY string and buffer contents */
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|internal_object-&gt;string.pointer
op_assign
id|ACPI_MEM_CALLOCATE
(paren
(paren
id|acpi_size
)paren
id|external_object-&gt;string.length
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|internal_object-&gt;string.pointer
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|ACPI_MEMCPY
(paren
id|internal_object-&gt;string.pointer
comma
id|external_object-&gt;string.pointer
comma
id|external_object-&gt;string.length
)paren
suffix:semicolon
id|internal_object-&gt;string.length
op_assign
id|external_object-&gt;string.length
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|internal_object-&gt;buffer.pointer
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|external_object-&gt;buffer.length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|internal_object-&gt;buffer.pointer
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|ACPI_MEMCPY
(paren
id|internal_object-&gt;buffer.pointer
comma
id|external_object-&gt;buffer.pointer
comma
id|external_object-&gt;buffer.length
)paren
suffix:semicolon
id|internal_object-&gt;buffer.length
op_assign
id|external_object-&gt;buffer.length
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
id|internal_object-&gt;integer.value
op_assign
id|external_object-&gt;integer.value
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Other types can&squot;t get here */
r_break
suffix:semicolon
)brace
op_star
id|ret_internal_object
op_assign
id|internal_object
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
macro_line|#ifdef ACPI_FUTURE_IMPLEMENTATION
multiline_comment|/* Code to convert packages that are parameters to control methods */
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_epackage_to_ipackage&n; *&n; * PARAMETERS:  *internal_object   - Pointer to the object we are returning&n; *              *Buffer            - Where the object is returned&n; *              *space_used        - Where the length of the object is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to place a package object in a user&n; *              buffer.  A package object by definition contains other objects.&n; *&n; *              The buffer is assumed to have sufficient space for the object.&n; *              The caller must have verified the buffer length needed using the&n; *              acpi_ut_get_object_size function before calling this function.&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ut_copy_epackage_to_ipackage
id|acpi_ut_copy_epackage_to_ipackage
(paren
r_union
id|acpi_operand_object
op_star
id|internal_object
comma
id|u8
op_star
id|buffer
comma
id|u32
op_star
id|space_used
)paren
(brace
id|u8
op_star
id|free_space
suffix:semicolon
r_union
id|acpi_object
op_star
id|external_object
suffix:semicolon
id|u32
id|length
op_assign
l_int|0
suffix:semicolon
id|u32
id|this_index
suffix:semicolon
id|u32
id|object_space
op_assign
l_int|0
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|this_internal_obj
suffix:semicolon
r_union
id|acpi_object
op_star
id|this_external_obj
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_copy_epackage_to_ipackage&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * First package at head of the buffer&n;&t; */
id|external_object
op_assign
(paren
r_union
id|acpi_object
op_star
)paren
id|buffer
suffix:semicolon
multiline_comment|/*&n;&t; * Free space begins right after the first package&n;&t; */
id|free_space
op_assign
id|buffer
op_plus
r_sizeof
(paren
r_union
id|acpi_object
)paren
suffix:semicolon
id|external_object-&gt;type
op_assign
id|ACPI_GET_OBJECT_TYPE
(paren
id|internal_object
)paren
suffix:semicolon
id|external_object-&gt;package.count
op_assign
id|internal_object-&gt;package.count
suffix:semicolon
id|external_object-&gt;package.elements
op_assign
(paren
r_union
id|acpi_object
op_star
)paren
id|free_space
suffix:semicolon
multiline_comment|/*&n;&t; * Build an array of ACPI_OBJECTS in the buffer&n;&t; * and move the free space past it&n;&t; */
id|free_space
op_add_assign
id|external_object-&gt;package.count
op_star
r_sizeof
(paren
r_union
id|acpi_object
)paren
suffix:semicolon
multiline_comment|/* Call walk_package */
)brace
macro_line|#endif /* Future implementation */
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_eobject_to_iobject&n; *&n; * PARAMETERS:  *internal_object   - The external object to be converted&n; *              *buffer_ptr     - Where the internal object is returned&n; *&n; * RETURN:      Status          - the status of the call&n; *&n; * DESCRIPTION: Converts an external object to an internal object.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_copy_eobject_to_iobject
id|acpi_ut_copy_eobject_to_iobject
(paren
r_union
id|acpi_object
op_star
id|external_object
comma
r_union
id|acpi_operand_object
op_star
op_star
id|internal_object
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_copy_eobject_to_iobject&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|external_object-&gt;type
op_eq
id|ACPI_TYPE_PACKAGE
)paren
(brace
multiline_comment|/*&n;&t;&t; * Packages as external input to control methods are not supported,&n;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Packages as parameters not implemented!&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_IMPLEMENTED
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * Build a simple object (no nested objects)&n;&t;&t; */
id|status
op_assign
id|acpi_ut_copy_esimple_to_isimple
(paren
id|external_object
comma
id|internal_object
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_simple_object&n; *&n; * PARAMETERS:  source_desc         - The internal object to be copied&n; *              dest_desc           - New target object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Simple copy of one internal object to another.  Reference count&n; *              of the destination object is preserved.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_copy_simple_object
id|acpi_ut_copy_simple_object
(paren
r_union
id|acpi_operand_object
op_star
id|source_desc
comma
r_union
id|acpi_operand_object
op_star
id|dest_desc
)paren
(brace
id|u16
id|reference_count
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|next_object
suffix:semicolon
multiline_comment|/* Save fields from destination that we don&squot;t want to overwrite */
id|reference_count
op_assign
id|dest_desc-&gt;common.reference_count
suffix:semicolon
id|next_object
op_assign
id|dest_desc-&gt;common.next_object
suffix:semicolon
multiline_comment|/* Copy the entire source object over the destination object*/
id|ACPI_MEMCPY
(paren
(paren
r_char
op_star
)paren
id|dest_desc
comma
(paren
r_char
op_star
)paren
id|source_desc
comma
r_sizeof
(paren
r_union
id|acpi_operand_object
)paren
)paren
suffix:semicolon
multiline_comment|/* Restore the saved fields */
id|dest_desc-&gt;common.reference_count
op_assign
id|reference_count
suffix:semicolon
id|dest_desc-&gt;common.next_object
op_assign
id|next_object
suffix:semicolon
multiline_comment|/* Handle the objects with extra data */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|dest_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|dest_desc-&gt;buffer.node
op_assign
l_int|NULL
suffix:semicolon
id|dest_desc-&gt;common.flags
op_assign
id|source_desc-&gt;common.flags
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Allocate and copy the actual buffer if and only if:&n;&t;&t; * 1) There is a valid buffer pointer&n;&t;&t; * 2) The buffer is not static (not in an ACPI table) (in this case,&n;&t;&t; *    the actual pointer was already copied above)&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|source_desc-&gt;buffer.pointer
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|source_desc-&gt;common.flags
op_amp
id|AOPOBJ_STATIC_POINTER
)paren
)paren
)paren
(brace
id|dest_desc-&gt;buffer.pointer
op_assign
id|ACPI_MEM_ALLOCATE
(paren
id|source_desc-&gt;buffer.length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dest_desc-&gt;buffer.pointer
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|ACPI_MEMCPY
(paren
id|dest_desc-&gt;buffer.pointer
comma
id|source_desc-&gt;buffer.pointer
comma
id|source_desc-&gt;buffer.length
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/*&n;&t;&t; * Allocate and copy the actual string if and only if:&n;&t;&t; * 1) There is a valid string pointer&n;&t;&t; * 2) The string is not static (not in an ACPI table) (in this case,&n;&t;&t; *    the actual pointer was already copied above)&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|source_desc-&gt;string.pointer
)paren
op_logical_and
(paren
op_logical_neg
(paren
id|source_desc-&gt;common.flags
op_amp
id|AOPOBJ_STATIC_POINTER
)paren
)paren
)paren
(brace
id|dest_desc-&gt;string.pointer
op_assign
id|ACPI_MEM_ALLOCATE
(paren
(paren
id|acpi_size
)paren
id|source_desc-&gt;string.length
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dest_desc-&gt;string.pointer
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|ACPI_MEMCPY
(paren
id|dest_desc-&gt;string.pointer
comma
id|source_desc-&gt;string.pointer
comma
(paren
id|acpi_size
)paren
id|source_desc-&gt;string.length
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Nothing to do for other simple objects */
r_break
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_ielement_to_ielement&n; *&n; * PARAMETERS:  acpi_pkg_callback&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Copy one package element to another package element&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_copy_ielement_to_ielement
id|acpi_ut_copy_ielement_to_ielement
(paren
id|u8
id|object_type
comma
r_union
id|acpi_operand_object
op_star
id|source_object
comma
r_union
id|acpi_generic_state
op_star
id|state
comma
r_void
op_star
id|context
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u32
id|this_index
suffix:semicolon
r_union
id|acpi_operand_object
op_star
op_star
id|this_target_ptr
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|target_object
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
id|this_index
op_assign
id|state-&gt;pkg.index
suffix:semicolon
id|this_target_ptr
op_assign
(paren
r_union
id|acpi_operand_object
op_star
op_star
)paren
op_amp
id|state-&gt;pkg.dest_object-&gt;package.elements
(braket
id|this_index
)braket
suffix:semicolon
r_switch
c_cond
(paren
id|object_type
)paren
(brace
r_case
id|ACPI_COPY_TYPE_SIMPLE
suffix:colon
multiline_comment|/* A null source object indicates a (legal) null package element */
r_if
c_cond
(paren
id|source_object
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * This is a simple object, just copy it&n;&t;&t;&t; */
id|target_object
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_object
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target_object
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_copy_simple_object
(paren
id|source_object
comma
id|target_object
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
op_star
id|this_target_ptr
op_assign
id|target_object
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Pass through a null element */
op_star
id|this_target_ptr
op_assign
l_int|NULL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_COPY_TYPE_PACKAGE
suffix:colon
multiline_comment|/*&n;&t;&t; * This object is a package - go down another nesting level&n;&t;&t; * Create and build the package object&n;&t;&t; */
id|target_object
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_PACKAGE
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target_object
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|target_object-&gt;package.count
op_assign
id|source_object-&gt;package.count
suffix:semicolon
id|target_object-&gt;common.flags
op_assign
id|source_object-&gt;common.flags
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Create the object array&n;&t;&t; */
id|target_object-&gt;package.elements
op_assign
id|ACPI_MEM_CALLOCATE
(paren
(paren
(paren
id|acpi_size
)paren
id|source_object-&gt;package.count
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|target_object-&gt;package.elements
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|target_object
)paren
suffix:semicolon
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Pass the new package object back to the package walk routine&n;&t;&t; */
id|state-&gt;pkg.this_target_obj
op_assign
id|target_object
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Store the object pointer in the parent package object&n;&t;&t; */
op_star
id|this_target_ptr
op_assign
id|target_object
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
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_ipackage_to_ipackage&n; *&n; * PARAMETERS:  *source_obj     - Pointer to the source package object&n; *              *dest_obj       - Where the internal object is returned&n; *&n; * RETURN:      Status          - the status of the call&n; *&n; * DESCRIPTION: This function is called to copy an internal package object&n; *              into another internal package object.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_copy_ipackage_to_ipackage
id|acpi_ut_copy_ipackage_to_ipackage
(paren
r_union
id|acpi_operand_object
op_star
id|source_obj
comma
r_union
id|acpi_operand_object
op_star
id|dest_obj
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_copy_ipackage_to_ipackage&quot;
)paren
suffix:semicolon
id|dest_obj-&gt;common.type
op_assign
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_obj
)paren
suffix:semicolon
id|dest_obj-&gt;common.flags
op_assign
id|source_obj-&gt;common.flags
suffix:semicolon
id|dest_obj-&gt;package.count
op_assign
id|source_obj-&gt;package.count
suffix:semicolon
multiline_comment|/*&n;&t; * Create the object array and walk the source package tree&n;&t; */
id|dest_obj-&gt;package.elements
op_assign
id|ACPI_MEM_CALLOCATE
(paren
(paren
(paren
id|acpi_size
)paren
id|source_obj-&gt;package.count
op_plus
l_int|1
)paren
op_star
r_sizeof
(paren
r_void
op_star
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dest_obj-&gt;package.elements
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;aml_build_copy_internal_package_object: Package allocation failure&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Copy the package element-by-element by walking the package &quot;tree&quot;.&n;&t; * This handles nested packages of arbitrary depth.&n;&t; */
id|status
op_assign
id|acpi_ut_walk_package_tree
(paren
id|source_obj
comma
id|dest_obj
comma
id|acpi_ut_copy_ielement_to_ielement
comma
id|walk_state
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
multiline_comment|/* On failure, delete the destination package object */
id|acpi_ut_remove_reference
(paren
id|dest_obj
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_copy_iobject_to_iobject&n; *&n; * PARAMETERS:  walk_state          - Current walk state&n; *              source_desc         - The internal object to be copied&n; *              dest_desc           - Where the copied object is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Copy an internal object to a new internal object&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_copy_iobject_to_iobject
id|acpi_ut_copy_iobject_to_iobject
(paren
r_union
id|acpi_operand_object
op_star
id|source_desc
comma
r_union
id|acpi_operand_object
op_star
op_star
id|dest_desc
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_copy_iobject_to_iobject&quot;
)paren
suffix:semicolon
multiline_comment|/* Create the top level object */
op_star
id|dest_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_desc
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_star
id|dest_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Copy the object and possible subobjects */
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_desc
)paren
op_eq
id|ACPI_TYPE_PACKAGE
)paren
(brace
id|status
op_assign
id|acpi_ut_copy_ipackage_to_ipackage
(paren
id|source_desc
comma
op_star
id|dest_desc
comma
id|walk_state
)paren
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|acpi_ut_copy_simple_object
(paren
id|source_desc
comma
op_star
id|dest_desc
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
