multiline_comment|/******************************************************************************&n; *&n; * Module Name: exstore - AML Interpreter object store support&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acdispat.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exstore&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_store&n; *&n; * PARAMETERS:  *source_desc        - Value to be stored&n; *              *dest_desc          - Where to store it.  Must be an NS node&n; *                                    or an union acpi_operand_object of type&n; *                                    Reference;&n; *              walk_state          - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Store the value described by source_desc into the location&n; *              described by dest_desc. Called by various interpreter&n; *              functions to store the result of an operation into&n; *              the destination operand -- not just simply the actual &quot;Store&quot;&n; *              ASL operator.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_store
id|acpi_ex_store
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
r_union
id|acpi_operand_object
op_star
id|ref_desc
op_assign
id|dest_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ex_store&quot;
comma
id|dest_desc
)paren
suffix:semicolon
multiline_comment|/* Validate parameters */
r_if
c_cond
(paren
op_logical_neg
id|source_desc
op_logical_or
op_logical_neg
id|dest_desc
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Null parameter&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_NO_OPERAND
)paren
suffix:semicolon
)brace
multiline_comment|/* dest_desc can be either a namespace node or an ACPI object */
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|dest_desc
)paren
op_eq
id|ACPI_DESC_TYPE_NAMED
)paren
(brace
multiline_comment|/*&n;&t;&t; * Dest is a namespace node,&n;&t;&t; * Storing an object into a Named node.&n;&t;&t; */
id|status
op_assign
id|acpi_ex_store_object_to_node
(paren
id|source_desc
comma
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|dest_desc
comma
id|walk_state
comma
id|ACPI_IMPLICIT_CONVERSION
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Destination object must be a Reference or a Constant object */
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
id|ACPI_TYPE_LOCAL_REFERENCE
suffix:colon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
multiline_comment|/* Allow stores to Constants -- a Noop as per ACPI spec */
r_if
c_cond
(paren
id|dest_desc-&gt;common.flags
op_amp
id|AOPOBJ_AML_CONSTANT
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*lint -fallthrough */
r_default
suffix:colon
multiline_comment|/* Destination is not a Reference object */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Target is not a Reference or Constant object - %s [%p]&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|dest_desc
)paren
comma
id|dest_desc
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_STACK_ENTRY
(paren
id|source_desc
)paren
suffix:semicolon
id|ACPI_DUMP_STACK_ENTRY
(paren
id|dest_desc
)paren
suffix:semicolon
id|ACPI_DUMP_OPERANDS
(paren
op_amp
id|dest_desc
comma
id|ACPI_IMODE_EXECUTE
comma
l_string|&quot;ex_store&quot;
comma
l_int|2
comma
l_string|&quot;Target is not a Reference or Constant object&quot;
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Examine the Reference opcode.  These cases are handled:&n;&t; *&n;&t; * 1) Store to Name (Change the object associated with a name)&n;&t; * 2) Store to an indexed area of a Buffer or Package&n;&t; * 3) Store to a Method Local or Arg&n;&t; * 4) Store to the debug object&n;&t; */
r_switch
c_cond
(paren
id|ref_desc-&gt;reference.opcode
)paren
(brace
r_case
id|AML_NAME_OP
suffix:colon
r_case
id|AML_REF_OF_OP
suffix:colon
multiline_comment|/* Storing an object into a Name &quot;container&quot; */
id|status
op_assign
id|acpi_ex_store_object_to_node
(paren
id|source_desc
comma
id|ref_desc-&gt;reference.object
comma
id|walk_state
comma
id|ACPI_IMPLICIT_CONVERSION
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INDEX_OP
suffix:colon
multiline_comment|/* Storing to an Index (pointer into a packager or buffer) */
id|status
op_assign
id|acpi_ex_store_object_to_index
(paren
id|source_desc
comma
id|ref_desc
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_LOCAL_OP
suffix:colon
r_case
id|AML_ARG_OP
suffix:colon
multiline_comment|/* Store to a method local/arg  */
id|status
op_assign
id|acpi_ds_store_object_to_local
(paren
id|ref_desc-&gt;reference.opcode
comma
id|ref_desc-&gt;reference.offset
comma
id|source_desc
comma
id|walk_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_DEBUG_OP
suffix:colon
multiline_comment|/*&n;&t;&t; * Storing to the Debug object causes the value stored to be&n;&t;&t; * displayed and otherwise has no effect -- see ACPI Specification&n;&t;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;**** Write to Debug Object: Object %p %s ****:&bslash;n&bslash;n&quot;
comma
id|source_desc
comma
id|acpi_ut_get_object_type_name
(paren
id|source_desc
)paren
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_DEBUG_OBJECT
comma
l_string|&quot;[ACPI Debug] %s: &quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|source_desc
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_ut_valid_internal_object
(paren
id|source_desc
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_DEBUG_OBJECT
comma
l_string|&quot;%p, Invalid Internal Object!&bslash;n&quot;
comma
id|source_desc
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
r_if
c_cond
(paren
id|acpi_gbl_integer_byte_width
op_eq
l_int|4
)paren
(brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_DEBUG_OBJECT
comma
l_string|&quot;0x%8.8X&bslash;n&quot;
comma
(paren
id|u32
)paren
id|source_desc-&gt;integer.value
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_DEBUG_OBJECT
comma
l_string|&quot;0x%8.8X%8.8X&bslash;n&quot;
comma
id|ACPI_FORMAT_UINT64
(paren
id|source_desc-&gt;integer.value
)paren
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_DEBUG_OBJECT
comma
l_string|&quot;[0x%.2X]&quot;
comma
(paren
id|u32
)paren
id|source_desc-&gt;buffer.length
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_BUFFER
(paren
id|source_desc-&gt;buffer.pointer
comma
(paren
id|source_desc-&gt;buffer.length
OL
l_int|32
)paren
ques
c_cond
id|source_desc-&gt;buffer.length
suffix:colon
l_int|32
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_DEBUG_OBJECT
comma
l_string|&quot;[0x%.2X] &bslash;&quot;%s&bslash;&quot;&bslash;n&quot;
comma
id|source_desc-&gt;string.length
comma
id|source_desc-&gt;string.pointer
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_DEBUG_OBJECT
comma
l_string|&quot;[0x%.2X] Elements Ptr - %p&bslash;n&quot;
comma
id|source_desc-&gt;package.count
comma
id|source_desc-&gt;package.elements
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_DEBUG_OBJECT
comma
l_string|&quot;%p&bslash;n&quot;
comma
id|source_desc
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ex_store: Unknown Reference opcode %X&bslash;n&quot;
comma
id|ref_desc-&gt;reference.opcode
)paren
)paren
suffix:semicolon
id|ACPI_DUMP_ENTRY
(paren
id|ref_desc
comma
id|ACPI_LV_ERROR
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_INTERNAL
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_store_object_to_index&n; *&n; * PARAMETERS:  *source_desc            - Value to be stored&n; *              *dest_desc              - Named object to receive the value&n; *              walk_state              - Current walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Store the object to indexed Buffer or Package element&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_store_object_to_index
id|acpi_ex_store_object_to_index
(paren
r_union
id|acpi_operand_object
op_star
id|source_desc
comma
r_union
id|acpi_operand_object
op_star
id|index_desc
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
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|new_desc
suffix:semicolon
id|u8
id|value
op_assign
l_int|0
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ex_store_object_to_index&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Destination must be a reference pointer, and&n;&t; * must point to either a buffer or a package&n;&t; */
r_switch
c_cond
(paren
id|index_desc-&gt;reference.target_type
)paren
(brace
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
multiline_comment|/*&n;&t;&t; * Storing to a package element. Copy the object and replace&n;&t;&t; * any existing object with the new object. No implicit&n;&t;&t; * conversion is performed.&n;&t;&t; *&n;&t;&t; * The object at *(index_desc-&gt;Reference.Where) is the&n;&t;&t; * element within the package that is to be modified.&n;&t;&t; * The parent package object is at index_desc-&gt;Reference.Object&n;&t;&t; */
id|obj_desc
op_assign
op_star
(paren
id|index_desc-&gt;reference.where
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_copy_iobject_to_iobject
(paren
id|source_desc
comma
op_amp
id|new_desc
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj_desc
)paren
(brace
multiline_comment|/* Decrement reference count by the ref count of the parent package */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
(paren
(paren
r_union
id|acpi_operand_object
op_star
)paren
id|index_desc-&gt;reference.object
)paren
op_member_access_from_pointer
id|common.reference_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
)brace
)brace
op_star
(paren
id|index_desc-&gt;reference.where
)paren
op_assign
id|new_desc
suffix:semicolon
multiline_comment|/* Increment reference count by the ref count of the parent package -1 */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
(paren
(paren
r_union
id|acpi_operand_object
op_star
)paren
id|index_desc-&gt;reference.object
)paren
op_member_access_from_pointer
id|common.reference_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_ut_add_reference
(paren
id|new_desc
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
multiline_comment|/*&n;&t;&t; * Store into a Buffer or String (not actually a real buffer_field)&n;&t;&t; * at a location defined by an Index.&n;&t;&t; *&n;&t;&t; * The first 8-bit element of the source object is written to the&n;&t;&t; * 8-bit Buffer location defined by the Index destination object,&n;&t;&t; * according to the ACPI 2.0 specification.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Make sure the target is a Buffer or String. An error should&n;&t;&t; * not happen here, since the reference_object was constructed&n;&t;&t; * by the INDEX_OP code.&n;&t;&t; */
id|obj_desc
op_assign
id|index_desc-&gt;reference.object
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_ne
id|ACPI_TYPE_BUFFER
)paren
op_logical_and
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_ne
id|ACPI_TYPE_STRING
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * The assignment of the individual elements will be slightly&n;&t;&t; * different for each source type.&n;&t;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
multiline_comment|/* Use the least-significant byte of the integer */
id|value
op_assign
(paren
id|u8
)paren
(paren
id|source_desc-&gt;integer.value
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
r_case
id|ACPI_TYPE_STRING
suffix:colon
multiline_comment|/* Note: Takes advantage of common string/buffer fields */
id|value
op_assign
id|source_desc-&gt;buffer.pointer
(braket
l_int|0
)braket
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All other types are invalid */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Source must be Integer/Buffer/String type, not %s&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|source_desc
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
multiline_comment|/* Store the source value into the target buffer byte */
id|obj_desc-&gt;buffer.pointer
(braket
id|index_desc-&gt;reference.offset
)braket
op_assign
id|value
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Target is not a Package or buffer_field&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_AML_OPERAND_TYPE
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_store_object_to_node&n; *&n; * PARAMETERS:  source_desc             - Value to be stored&n; *              Node                    - Named object to receive the value&n; *              walk_state              - Current walk state&n; *              implicit_conversion     - Perform implicit conversion (yes/no)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Store the object to the named object.&n; *&n; *              The Assignment of an object to a named object is handled here&n; *              The value passed in will replace the current value (if any)&n; *              with the input value.&n; *&n; *              When storing into an object the data is converted to the&n; *              target object type then stored in the object.  This means&n; *              that the target object type (for an initialized target) will&n; *              not be changed by a store operation.&n; *&n; *              Assumes parameters are already validated.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_store_object_to_node
id|acpi_ex_store_object_to_node
(paren
r_union
id|acpi_operand_object
op_star
id|source_desc
comma
r_struct
id|acpi_namespace_node
op_star
id|node
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
id|u8
id|implicit_conversion
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|target_desc
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|new_desc
suffix:semicolon
id|acpi_object_type
id|target_type
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ex_store_object_to_node&quot;
comma
id|source_desc
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get current type of the node, and object attached to Node&n;&t; */
id|target_type
op_assign
id|acpi_ns_get_type
(paren
id|node
)paren
suffix:semicolon
id|target_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|node
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Storing %p(%s) into node %p(%s)&bslash;n&quot;
comma
id|source_desc
comma
id|acpi_ut_get_object_type_name
(paren
id|source_desc
)paren
comma
id|node
comma
id|acpi_ut_get_type_name
(paren
id|target_type
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Resolve the source object to an actual value&n;&t; * (If it is a reference object)&n;&t; */
id|status
op_assign
id|acpi_ex_resolve_object
(paren
op_amp
id|source_desc
comma
id|target_type
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* If no implicit conversion, drop into the default case below */
r_if
c_cond
(paren
op_logical_neg
id|implicit_conversion
)paren
(brace
multiline_comment|/* Force execution of default (no implicit conversion) */
id|target_type
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Do the actual store operation&n;&t; */
r_switch
c_cond
(paren
id|target_type
)paren
(brace
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_REGION_FIELD
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_BANK_FIELD
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_INDEX_FIELD
suffix:colon
multiline_comment|/*&n;&t;&t; * For fields, copy the source data to the target field.&n;&t;&t; */
id|status
op_assign
id|acpi_ex_write_data_to_field
(paren
id|source_desc
comma
id|target_desc
comma
op_amp
id|walk_state-&gt;result_obj
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/*&n;&t;&t; * These target types are all of type Integer/String/Buffer, and&n;&t;&t; * therefore support implicit conversion before the store.&n;&t;&t; *&n;&t;&t; * Copy and/or convert the source object to a new target object&n;&t;&t; */
id|status
op_assign
id|acpi_ex_store_object_to_object
(paren
id|source_desc
comma
id|target_desc
comma
op_amp
id|new_desc
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
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|new_desc
op_ne
id|target_desc
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Store the new new_desc as the new value of the Name, and set&n;&t;&t;&t; * the Name&squot;s type to that of the value being stored in it.&n;&t;&t;&t; * source_desc reference count is incremented by attach_object.&n;&t;&t;&t; *&n;&t;&t;&t; * Note: This may change the type of the node if an explicit store&n;&t;&t;&t; * has been performed such that the node/object type has been&n;&t;&t;&t; * changed.&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|node
comma
id|new_desc
comma
id|new_desc-&gt;common.type
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Store %s into %s via Convert/Attach&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|source_desc
)paren
comma
id|acpi_ut_get_object_type_name
(paren
id|new_desc
)paren
)paren
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Storing %s (%p) directly into node (%p), no implicit conversion&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|source_desc
)paren
comma
id|source_desc
comma
id|node
)paren
)paren
suffix:semicolon
multiline_comment|/* No conversions for all other types.  Just attach the source object */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|node
comma
id|source_desc
comma
id|ACPI_GET_OBJECT_TYPE
(paren
id|source_desc
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
