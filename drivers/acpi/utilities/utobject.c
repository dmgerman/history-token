multiline_comment|/******************************************************************************&n; *&n; * Module Name: utobject - ACPI object create/delete/size/cache routines&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_UTILITIES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;utobject&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_create_internal_object_dbg&n; *&n; * PARAMETERS:  module_name         - Source file name of caller&n; *              line_number         - Line number of caller&n; *              component_id        - Component type of caller&n; *              Type                - ACPI Type of the new object&n; *&n; * RETURN:      Object              - The new object.  Null on failure&n; *&n; * DESCRIPTION: Create and initialize a new internal object.&n; *&n; * NOTE:        We always allocate the worst-case object descriptor because&n; *              these objects are cached, and we want them to be&n; *              one-size-satisifies-any-request.  This in itself may not be&n; *              the most memory efficient, but the efficiency of the object&n; *              cache should more than make up for this!&n; *&n; ******************************************************************************/
r_union
id|acpi_operand_object
op_star
DECL|function|acpi_ut_create_internal_object_dbg
id|acpi_ut_create_internal_object_dbg
(paren
r_char
op_star
id|module_name
comma
id|u32
id|line_number
comma
id|u32
id|component_id
comma
id|acpi_object_type
id|type
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|object
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|second_object
suffix:semicolon
id|ACPI_FUNCTION_TRACE_STR
(paren
l_string|&quot;ut_create_internal_object_dbg&quot;
comma
id|acpi_ut_get_type_name
(paren
id|type
)paren
)paren
suffix:semicolon
multiline_comment|/* Allocate the raw object descriptor */
id|object
op_assign
id|acpi_ut_allocate_object_desc_dbg
(paren
id|module_name
comma
id|line_number
comma
id|component_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|ACPI_TYPE_REGION
suffix:colon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
multiline_comment|/* These types require a secondary object */
id|second_object
op_assign
id|acpi_ut_allocate_object_desc_dbg
(paren
id|module_name
comma
id|line_number
comma
id|component_id
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|second_object
)paren
(brace
id|acpi_ut_delete_object_desc
(paren
id|object
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|second_object-&gt;common.type
op_assign
id|ACPI_TYPE_LOCAL_EXTRA
suffix:semicolon
id|second_object-&gt;common.reference_count
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Link the second object to the first */
id|object-&gt;common.next_object
op_assign
id|second_object
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All others have no secondary object */
r_break
suffix:semicolon
)brace
multiline_comment|/* Save the object type in the object descriptor */
id|object-&gt;common.type
op_assign
(paren
id|u8
)paren
id|type
suffix:semicolon
multiline_comment|/* Init the reference count */
id|object-&gt;common.reference_count
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* Any per-type initialization should go here */
id|return_PTR
(paren
id|object
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_create_buffer_object&n; *&n; * PARAMETERS:  buffer_size            - Size of buffer to be created&n; *&n; * RETURN:      Pointer to a new Buffer object&n; *&n; * DESCRIPTION: Create a fully initialized buffer object&n; *&n; ******************************************************************************/
r_union
id|acpi_operand_object
op_star
DECL|function|acpi_ut_create_buffer_object
id|acpi_ut_create_buffer_object
(paren
id|acpi_size
id|buffer_size
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|buffer_desc
suffix:semicolon
id|u8
op_star
id|buffer
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE_U32
(paren
l_string|&quot;ut_create_buffer_object&quot;
comma
id|buffer_size
)paren
suffix:semicolon
multiline_comment|/* Create a new Buffer object */
id|buffer_desc
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
id|buffer_desc
)paren
(brace
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Create an actual buffer only if size &gt; 0 */
r_if
c_cond
(paren
id|buffer_size
OG
l_int|0
)paren
(brace
multiline_comment|/* Allocate the actual buffer */
id|buffer
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|buffer_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;create_buffer: could not allocate size %X&bslash;n&quot;
comma
(paren
id|u32
)paren
id|buffer_size
)paren
)paren
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|buffer_desc
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Complete buffer object initialization */
id|buffer_desc-&gt;buffer.flags
op_or_assign
id|AOPOBJ_DATA_VALID
suffix:semicolon
id|buffer_desc-&gt;buffer.pointer
op_assign
id|buffer
suffix:semicolon
id|buffer_desc-&gt;buffer.length
op_assign
(paren
id|u32
)paren
id|buffer_size
suffix:semicolon
multiline_comment|/* Return the new buffer descriptor */
id|return_PTR
(paren
id|buffer_desc
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_create_string_object&n; *&n; * PARAMETERS:  string_size            - Size of string to be created.  Does not&n; *                                       include NULL terminator, this is added&n; *                                       automatically.&n; *&n; * RETURN:      Pointer to a new String object&n; *&n; * DESCRIPTION: Create a fully initialized string object&n; *&n; ******************************************************************************/
r_union
id|acpi_operand_object
op_star
DECL|function|acpi_ut_create_string_object
id|acpi_ut_create_string_object
(paren
id|acpi_size
id|string_size
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|string_desc
suffix:semicolon
r_char
op_star
id|string
suffix:semicolon
id|ACPI_FUNCTION_TRACE_U32
(paren
l_string|&quot;ut_create_string_object&quot;
comma
id|string_size
)paren
suffix:semicolon
multiline_comment|/* Create a new String object */
id|string_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_STRING
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|string_desc
)paren
(brace
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allocate the actual string buffer -- (Size + 1) for NULL terminator.&n;&t; * NOTE: Zero-length strings are NULL terminated&n;&t; */
id|string
op_assign
id|ACPI_MEM_CALLOCATE
(paren
id|string_size
op_plus
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|string
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;create_string: could not allocate size %X&bslash;n&quot;
comma
(paren
id|u32
)paren
id|string_size
)paren
)paren
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|string_desc
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Complete string object initialization */
id|string_desc-&gt;string.pointer
op_assign
id|string
suffix:semicolon
id|string_desc-&gt;string.length
op_assign
(paren
id|u32
)paren
id|string_size
suffix:semicolon
multiline_comment|/* Return the new string descriptor */
id|return_PTR
(paren
id|string_desc
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_valid_internal_object&n; *&n; * PARAMETERS:  Object              - Object to be validated&n; *&n; * RETURN:      Validate a pointer to be an union acpi_operand_object&n; *&n; ******************************************************************************/
id|u8
DECL|function|acpi_ut_valid_internal_object
id|acpi_ut_valid_internal_object
(paren
r_void
op_star
id|object
)paren
(brace
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ut_valid_internal_object&quot;
)paren
suffix:semicolon
multiline_comment|/* Check for a null pointer */
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;**** Null Object Ptr&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/* Check the descriptor type field */
r_switch
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|object
)paren
)paren
(brace
r_case
id|ACPI_DESC_TYPE_OPERAND
suffix:colon
multiline_comment|/* The object appears to be a valid union acpi_operand_object    */
r_return
(paren
id|TRUE
)paren
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;%p is not not an ACPI operand obj [%s]&bslash;n&quot;
comma
id|object
comma
id|acpi_ut_get_descriptor_name
(paren
id|object
)paren
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_allocate_object_desc_dbg&n; *&n; * PARAMETERS:  module_name         - Caller&squot;s module name (for error output)&n; *              line_number         - Caller&squot;s line number (for error output)&n; *              component_id        - Caller&squot;s component ID (for error output)&n; *&n; * RETURN:      Pointer to newly allocated object descriptor.  Null on error&n; *&n; * DESCRIPTION: Allocate a new object descriptor.  Gracefully handle&n; *              error conditions.&n; *&n; ******************************************************************************/
r_void
op_star
DECL|function|acpi_ut_allocate_object_desc_dbg
id|acpi_ut_allocate_object_desc_dbg
(paren
r_char
op_star
id|module_name
comma
id|u32
id|line_number
comma
id|u32
id|component_id
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|object
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_allocate_object_desc_dbg&quot;
)paren
suffix:semicolon
id|object
op_assign
id|acpi_ut_acquire_from_cache
(paren
id|ACPI_MEM_LIST_OPERAND
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
id|_ACPI_REPORT_ERROR
(paren
id|module_name
comma
id|line_number
comma
id|component_id
comma
(paren
l_string|&quot;Could not allocate an object descriptor&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Mark the descriptor type */
id|ACPI_SET_DESCRIPTOR_TYPE
(paren
id|object
comma
id|ACPI_DESC_TYPE_OPERAND
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;%p Size %X&bslash;n&quot;
comma
id|object
comma
(paren
id|u32
)paren
r_sizeof
(paren
r_union
id|acpi_operand_object
)paren
)paren
)paren
suffix:semicolon
id|return_PTR
(paren
id|object
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_delete_object_desc&n; *&n; * PARAMETERS:  Object          - An Acpi internal object to be deleted&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Free an ACPI object descriptor or add it to the object cache&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_delete_object_desc
id|acpi_ut_delete_object_desc
(paren
r_union
id|acpi_operand_object
op_star
id|object
)paren
(brace
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ut_delete_object_desc&quot;
comma
id|object
)paren
suffix:semicolon
multiline_comment|/* Object must be an union acpi_operand_object    */
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|object
)paren
op_ne
id|ACPI_DESC_TYPE_OPERAND
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;%p is not an ACPI Operand object [%s]&bslash;n&quot;
comma
id|object
comma
id|acpi_ut_get_descriptor_name
(paren
id|object
)paren
)paren
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
id|acpi_ut_release_to_cache
(paren
id|ACPI_MEM_LIST_OPERAND
comma
id|object
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
macro_line|#ifdef ACPI_ENABLE_OBJECT_CACHE
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_delete_object_cache&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Purge the global state object cache.  Used during subsystem&n; *              termination.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_delete_object_cache
id|acpi_ut_delete_object_cache
(paren
r_void
)paren
(brace
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_delete_object_cache&quot;
)paren
suffix:semicolon
id|acpi_ut_delete_generic_cache
(paren
id|ACPI_MEM_LIST_OPERAND
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_get_simple_object_size&n; *&n; * PARAMETERS:  *internal_object    - Pointer to the object we are examining&n; *              *obj_length         - Where the length is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to determine the space required to&n; *              contain a simple object for return to an external user.&n; *&n; *              The length includes the object structure plus any additional&n; *              needed space.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_get_simple_object_size
id|acpi_ut_get_simple_object_size
(paren
r_union
id|acpi_operand_object
op_star
id|internal_object
comma
id|acpi_size
op_star
id|obj_length
)paren
(brace
id|acpi_size
id|length
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ut_get_simple_object_size&quot;
comma
id|internal_object
)paren
suffix:semicolon
multiline_comment|/* Handle a null object (Could be a uninitialized package element -- which is legal) */
r_if
c_cond
(paren
op_logical_neg
id|internal_object
)paren
(brace
op_star
id|obj_length
op_assign
l_int|0
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Start with the length of the Acpi object */
id|length
op_assign
r_sizeof
(paren
r_union
id|acpi_object
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|internal_object
)paren
op_eq
id|ACPI_DESC_TYPE_NAMED
)paren
(brace
multiline_comment|/* Object is a named object (reference), just return the length */
op_star
id|obj_length
op_assign
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
id|length
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The final length depends on the object type&n;&t; * Strings and Buffers are packed right up against the parent object and&n;&t; * must be accessed bytewise or there may be alignment problems on&n;&t; * certain processors&n;&t; */
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
id|length
op_add_assign
(paren
id|acpi_size
)paren
id|internal_object-&gt;string.length
op_plus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|length
op_add_assign
(paren
id|acpi_size
)paren
id|internal_object-&gt;buffer.length
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
r_case
id|ACPI_TYPE_PROCESSOR
suffix:colon
r_case
id|ACPI_TYPE_POWER
suffix:colon
multiline_comment|/*&n;&t;&t; * No extra data for these types&n;&t;&t; */
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_REFERENCE
suffix:colon
r_switch
c_cond
(paren
id|internal_object-&gt;reference.opcode
)paren
(brace
r_case
id|AML_INT_NAMEPATH_OP
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Get the actual length of the full pathname to this object.&n;&t;&t;&t; * The reference will be converted to the pathname to the object&n;&t;&t;&t; */
id|length
op_add_assign
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
id|acpi_ns_get_pathname_length
(paren
id|internal_object-&gt;reference.node
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * No other reference opcodes are supported.&n;&t;&t;&t; * Notably, Locals and Args are not supported, but this may be&n;&t;&t;&t; * required eventually.&n;&t;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unsupported Reference opcode=%X in object %p&bslash;n&quot;
comma
id|internal_object-&gt;reference.opcode
comma
id|internal_object
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_TYPE
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unsupported type=%X in object %p&bslash;n&quot;
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|internal_object
)paren
comma
id|internal_object
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_TYPE
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Account for the space required by the object rounded up to the next&n;&t; * multiple of the machine word size.  This keeps each object aligned&n;&t; * on a machine word boundary. (preventing alignment faults on some&n;&t; * machines.)&n;&t; */
op_star
id|obj_length
op_assign
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
id|length
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_get_element_length&n; *&n; * PARAMETERS:  acpi_pkg_callback&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Get the length of one package element.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_get_element_length
id|acpi_ut_get_element_length
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
r_switch
c_cond
(paren
id|object_type
)paren
(brace
r_case
id|ACPI_COPY_TYPE_SIMPLE
suffix:colon
multiline_comment|/*&n;&t;&t; * Simple object - just get the size (Null object/entry is handled&n;&t;&t; * here also) and sum it into the running package length&n;&t;&t; */
id|status
op_assign
id|acpi_ut_get_simple_object_size
(paren
id|source_object
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
id|info-&gt;length
op_add_assign
id|object_space
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_COPY_TYPE_PACKAGE
suffix:colon
multiline_comment|/* Package object - nothing much to do here, let the walk handle it */
id|info-&gt;num_packages
op_increment
suffix:semicolon
id|state-&gt;pkg.this_target_obj
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* No other types allowed */
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_get_package_object_size&n; *&n; * PARAMETERS:  *internal_object    - Pointer to the object we are examining&n; *              *obj_length         - Where the length is returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to determine the space required to&n; *              contain a package object for return to an external user.&n; *&n; *              This is moderately complex since a package contains other&n; *              objects including packages.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_get_package_object_size
id|acpi_ut_get_package_object_size
(paren
r_union
id|acpi_operand_object
op_star
id|internal_object
comma
id|acpi_size
op_star
id|obj_length
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_pkg_info
id|info
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ut_get_package_object_size&quot;
comma
id|internal_object
)paren
suffix:semicolon
id|info.length
op_assign
l_int|0
suffix:semicolon
id|info.object_space
op_assign
l_int|0
suffix:semicolon
id|info.num_packages
op_assign
l_int|1
suffix:semicolon
id|status
op_assign
id|acpi_ut_walk_package_tree
(paren
id|internal_object
comma
l_int|NULL
comma
id|acpi_ut_get_element_length
comma
op_amp
id|info
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
multiline_comment|/*&n;&t; * We have handled all of the objects in all levels of the package.&n;&t; * just add the length of the package objects themselves.&n;&t; * Round up to the next machine word.&n;&t; */
id|info.length
op_add_assign
id|ACPI_ROUND_UP_TO_NATIVE_WORD
(paren
r_sizeof
(paren
r_union
id|acpi_object
)paren
)paren
op_star
(paren
id|acpi_size
)paren
id|info.num_packages
suffix:semicolon
multiline_comment|/* Return the total package length */
op_star
id|obj_length
op_assign
id|info.length
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_get_object_size&n; *&n; * PARAMETERS:  *internal_object    - Pointer to the object we are examining&n; *              *obj_length         - Where the length will be returned&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: This function is called to determine the space required to&n; *              contain an object for return to an API user.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_get_object_size
id|acpi_ut_get_object_size
c_func
(paren
r_union
id|acpi_operand_object
op_star
id|internal_object
comma
id|acpi_size
op_star
id|obj_length
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|internal_object
)paren
op_eq
id|ACPI_DESC_TYPE_OPERAND
)paren
op_logical_and
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|internal_object
)paren
op_eq
id|ACPI_TYPE_PACKAGE
)paren
)paren
(brace
id|status
op_assign
id|acpi_ut_get_package_object_size
(paren
id|internal_object
comma
id|obj_length
)paren
suffix:semicolon
)brace
r_else
(brace
id|status
op_assign
id|acpi_ut_get_simple_object_size
(paren
id|internal_object
comma
id|obj_length
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
