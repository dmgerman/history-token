multiline_comment|/******************************************************************************&n; *&n; * Module Name: exresop - AML Interpreter operand/object resolution&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
macro_line|#include &lt;acpi/acparser.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exresop&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_check_object_type&n; *&n; * PARAMETERS:  type_needed         Object type needed&n; *              this_type           Actual object type&n; *              Object              Object pointer&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Check required type against actual type&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_check_object_type
id|acpi_ex_check_object_type
(paren
id|acpi_object_type
id|type_needed
comma
id|acpi_object_type
id|this_type
comma
r_void
op_star
id|object
)paren
(brace
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ex_check_object_type&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|type_needed
op_eq
id|ACPI_TYPE_ANY
)paren
(brace
multiline_comment|/* All types OK, so we don&squot;t perform any typechecks */
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|type_needed
op_eq
id|ACPI_TYPE_LOCAL_REFERENCE
)paren
(brace
multiline_comment|/*&n;&t;&t; * Allow the AML &quot;Constant&quot; opcodes (Zero, One, etc.) to be reference&n;&t;&t; * objects and thus allow them to be targets.  (As per the ACPI&n;&t;&t; * specification, a store to a constant is a noop.)&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|this_type
op_eq
id|ACPI_TYPE_INTEGER
)paren
op_logical_and
(paren
(paren
(paren
r_union
id|acpi_operand_object
op_star
)paren
id|object
)paren
op_member_access_from_pointer
id|common.flags
op_amp
id|AOPOBJ_AML_CONSTANT
)paren
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|type_needed
op_ne
id|this_type
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Needed [%s], found [%s] %p&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
id|type_needed
)paren
comma
id|acpi_ut_get_type_name
(paren
id|this_type
)paren
comma
id|object
)paren
)paren
suffix:semicolon
r_return
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ex_resolve_operands&n; *&n; * PARAMETERS:  Opcode              - Opcode being interpreted&n; *              stack_ptr           - Pointer to the operand stack to be&n; *                                    resolved&n; *              walk_state          - Current state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Convert multiple input operands to the types required by the&n; *              target operator.&n; *&n; *      Each 5-bit group in arg_types represents one required&n; *      operand and indicates the required Type. The corresponding operand&n; *      will be converted to the required type if possible, otherwise we&n; *      abort with an exception.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_resolve_operands
id|acpi_ex_resolve_operands
(paren
id|u16
id|opcode
comma
r_union
id|acpi_operand_object
op_star
op_star
id|stack_ptr
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u8
id|object_type
suffix:semicolon
r_void
op_star
id|temp_node
suffix:semicolon
id|u32
id|arg_types
suffix:semicolon
r_const
r_struct
id|acpi_opcode_info
op_star
id|op_info
suffix:semicolon
id|u32
id|this_arg_type
suffix:semicolon
id|acpi_object_type
id|type_needed
suffix:semicolon
id|ACPI_FUNCTION_TRACE_U32
(paren
l_string|&quot;ex_resolve_operands&quot;
comma
id|opcode
)paren
suffix:semicolon
id|op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|opcode
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
id|return_ACPI_STATUS
(paren
id|AE_AML_BAD_OPCODE
)paren
suffix:semicolon
)brace
id|arg_types
op_assign
id|op_info-&gt;runtime_args
suffix:semicolon
r_if
c_cond
(paren
id|arg_types
op_eq
id|ARGI_INVALID_OPCODE
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;resolve_operands: %X is not a valid AML opcode&bslash;n&quot;
comma
id|opcode
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_INTERNAL
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Opcode %X [%s] required_operand_types=%8.8X &bslash;n&quot;
comma
id|opcode
comma
id|op_info-&gt;name
comma
id|arg_types
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Normal exit is with (arg_types == 0) at end of argument list.&n;&t; * Function will return an exception from within the loop upon&n;&t; * finding an entry which is not (or cannot be converted&n;&t; * to) the required type; if stack underflows; or upon&n;&t; * finding a NULL stack entry (which should not happen).&n;&t; */
r_while
c_loop
(paren
id|GET_CURRENT_ARG_TYPE
(paren
id|arg_types
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|stack_ptr
op_logical_or
op_logical_neg
op_star
id|stack_ptr
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;resolve_operands: Null stack entry at %p&bslash;n&quot;
comma
id|stack_ptr
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_INTERNAL
)paren
suffix:semicolon
)brace
multiline_comment|/* Extract useful items */
id|obj_desc
op_assign
op_star
id|stack_ptr
suffix:semicolon
multiline_comment|/* Decode the descriptor type */
r_switch
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_DESC_TYPE_NAMED
suffix:colon
multiline_comment|/* Node */
id|object_type
op_assign
(paren
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|obj_desc
)paren
op_member_access_from_pointer
id|type
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_DESC_TYPE_OPERAND
suffix:colon
multiline_comment|/* ACPI internal object */
id|object_type
op_assign
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
suffix:semicolon
multiline_comment|/* Check for bad acpi_object_type */
r_if
c_cond
(paren
op_logical_neg
id|acpi_ut_valid_object_type
(paren
id|object_type
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Bad operand object type [%X]&bslash;n&quot;
comma
id|object_type
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|object_type
op_eq
(paren
id|u8
)paren
id|ACPI_TYPE_LOCAL_REFERENCE
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Decode the Reference&n;&t;&t;&t;&t; */
id|op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|opcode
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
id|return_ACPI_STATUS
(paren
id|AE_AML_BAD_OPCODE
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|obj_desc-&gt;reference.opcode
)paren
(brace
r_case
id|AML_DEBUG_OP
suffix:colon
r_case
id|AML_NAME_OP
suffix:colon
r_case
id|AML_INDEX_OP
suffix:colon
r_case
id|AML_REF_OF_OP
suffix:colon
r_case
id|AML_ARG_OP
suffix:colon
r_case
id|AML_LOCAL_OP
suffix:colon
r_case
id|AML_LOAD_OP
suffix:colon
multiline_comment|/* ddb_handle from LOAD_OP or LOAD_TABLE_OP */
id|ACPI_DEBUG_ONLY_MEMBERS
(paren
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Operand is a Reference, ref_opcode [%s]&bslash;n&quot;
comma
(paren
id|acpi_ps_get_opcode_info
(paren
id|obj_desc-&gt;reference.opcode
)paren
)paren
op_member_access_from_pointer
id|name
)paren
)paren
)paren
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
l_string|&quot;Operand is a Reference, Unknown Reference Opcode %X [%s]&bslash;n&quot;
comma
id|obj_desc-&gt;reference.opcode
comma
(paren
id|acpi_ps_get_opcode_info
(paren
id|obj_desc-&gt;reference.opcode
)paren
)paren
op_member_access_from_pointer
id|name
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Invalid descriptor */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Invalid descriptor %p [%s]&bslash;n&quot;
comma
id|obj_desc
comma
id|acpi_ut_get_descriptor_name
(paren
id|obj_desc
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
multiline_comment|/*&n;&t;&t; * Get one argument type, point to the next&n;&t;&t; */
id|this_arg_type
op_assign
id|GET_CURRENT_ARG_TYPE
(paren
id|arg_types
)paren
suffix:semicolon
id|INCREMENT_ARG_LIST
(paren
id|arg_types
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Handle cases where the object does not need to be&n;&t;&t; * resolved to a value&n;&t;&t; */
r_switch
c_cond
(paren
id|this_arg_type
)paren
(brace
r_case
id|ARGI_REF_OR_STRING
suffix:colon
multiline_comment|/* Can be a String or Reference */
r_if
c_cond
(paren
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_DESC_TYPE_OPERAND
)paren
op_logical_and
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_TYPE_STRING
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * String found - the string references a named object and must be&n;&t;&t;&t;&t; * resolved to a node&n;&t;&t;&t;&t; */
r_goto
id|next_operand
suffix:semicolon
)brace
multiline_comment|/* Else not a string - fall through to the normal Reference case below */
multiline_comment|/*lint -fallthrough */
r_case
id|ARGI_REFERENCE
suffix:colon
multiline_comment|/* References: */
r_case
id|ARGI_INTEGER_REF
suffix:colon
r_case
id|ARGI_OBJECT_REF
suffix:colon
r_case
id|ARGI_DEVICE_REF
suffix:colon
r_case
id|ARGI_TARGETREF
suffix:colon
multiline_comment|/* Allows implicit conversion rules before store */
r_case
id|ARGI_FIXED_TARGET
suffix:colon
multiline_comment|/* No implicit conversion before store to target */
r_case
id|ARGI_SIMPLE_TARGET
suffix:colon
multiline_comment|/* Name, Local, or Arg - no implicit conversion  */
multiline_comment|/* Need an operand of type ACPI_TYPE_LOCAL_REFERENCE */
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|obj_desc
)paren
op_eq
id|ACPI_DESC_TYPE_NAMED
)paren
multiline_comment|/* Node (name) ptr OK as-is */
(brace
r_goto
id|next_operand
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ex_check_object_type
(paren
id|ACPI_TYPE_LOCAL_REFERENCE
comma
id|object_type
comma
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
id|AML_NAME_OP
op_eq
id|obj_desc-&gt;reference.opcode
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Convert an indirect name ptr to direct name ptr and put&n;&t;&t;&t;&t; * it on the stack&n;&t;&t;&t;&t; */
id|temp_node
op_assign
id|obj_desc-&gt;reference.object
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|obj_desc
)paren
suffix:semicolon
(paren
op_star
id|stack_ptr
)paren
op_assign
id|temp_node
suffix:semicolon
)brace
r_goto
id|next_operand
suffix:semicolon
r_case
id|ARGI_ANYTYPE
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * We don&squot;t want to resolve index_op reference objects during&n;&t;&t;&t; * a store because this would be an implicit de_ref_of operation.&n;&t;&t;&t; * Instead, we just want to store the reference object.&n;&t;&t;&t; * -- All others must be resolved below.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
id|opcode
op_eq
id|AML_STORE_OP
)paren
op_logical_and
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
op_star
id|stack_ptr
)paren
op_eq
id|ACPI_TYPE_LOCAL_REFERENCE
)paren
op_logical_and
(paren
(paren
op_star
id|stack_ptr
)paren
op_member_access_from_pointer
id|reference.opcode
op_eq
id|AML_INDEX_OP
)paren
)paren
(brace
r_goto
id|next_operand
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All cases covered above */
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Resolve this object to a value&n;&t;&t; */
id|status
op_assign
id|acpi_ex_resolve_to_value
(paren
id|stack_ptr
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
multiline_comment|/* Get the resolved object */
id|obj_desc
op_assign
op_star
id|stack_ptr
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Check the resulting object (value) type&n;&t;&t; */
r_switch
c_cond
(paren
id|this_arg_type
)paren
(brace
multiline_comment|/*&n;&t;&t; * For the simple cases, only one type of resolved object&n;&t;&t; * is allowed&n;&t;&t; */
r_case
id|ARGI_MUTEX
suffix:colon
multiline_comment|/* Need an operand of type ACPI_TYPE_MUTEX */
id|type_needed
op_assign
id|ACPI_TYPE_MUTEX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGI_EVENT
suffix:colon
multiline_comment|/* Need an operand of type ACPI_TYPE_EVENT */
id|type_needed
op_assign
id|ACPI_TYPE_EVENT
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGI_PACKAGE
suffix:colon
multiline_comment|/* Package */
multiline_comment|/* Need an operand of type ACPI_TYPE_PACKAGE */
id|type_needed
op_assign
id|ACPI_TYPE_PACKAGE
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGI_ANYTYPE
suffix:colon
multiline_comment|/* Any operand type will do */
id|type_needed
op_assign
id|ACPI_TYPE_ANY
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGI_DDBHANDLE
suffix:colon
multiline_comment|/* Need an operand of type ACPI_TYPE_DDB_HANDLE */
id|type_needed
op_assign
id|ACPI_TYPE_LOCAL_REFERENCE
suffix:semicolon
r_break
suffix:semicolon
multiline_comment|/*&n;&t;&t; * The more complex cases allow multiple resolved object types&n;&t;&t; */
r_case
id|ARGI_INTEGER
suffix:colon
multiline_comment|/* Number */
multiline_comment|/*&n;&t;&t;&t; * Need an operand of type ACPI_TYPE_INTEGER,&n;&t;&t;&t; * But we can implicitly convert from a STRING or BUFFER&n;&t;&t;&t; * Aka - &quot;Implicit Source Operand Conversion&quot;&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ex_convert_to_integer
(paren
id|obj_desc
comma
id|stack_ptr
comma
l_int|16
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
r_if
c_cond
(paren
id|status
op_eq
id|AE_TYPE
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Needed [Integer/String/Buffer], found [%s] %p&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_goto
id|next_operand
suffix:semicolon
r_case
id|ARGI_BUFFER
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Need an operand of type ACPI_TYPE_BUFFER,&n;&t;&t;&t; * But we can implicitly convert from a STRING or INTEGER&n;&t;&t;&t; * Aka - &quot;Implicit Source Operand Conversion&quot;&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ex_convert_to_buffer
(paren
id|obj_desc
comma
id|stack_ptr
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
r_if
c_cond
(paren
id|status
op_eq
id|AE_TYPE
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Needed [Integer/String/Buffer], found [%s] %p&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_goto
id|next_operand
suffix:semicolon
r_case
id|ARGI_STRING
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * Need an operand of type ACPI_TYPE_STRING,&n;&t;&t;&t; * But we can implicitly convert from a BUFFER or INTEGER&n;&t;&t;&t; * Aka - &quot;Implicit Source Operand Conversion&quot;&n;&t;&t;&t; */
id|status
op_assign
id|acpi_ex_convert_to_string
(paren
id|obj_desc
comma
id|stack_ptr
comma
id|ACPI_IMPLICIT_CONVERT_HEX
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
r_if
c_cond
(paren
id|status
op_eq
id|AE_TYPE
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Needed [Integer/String/Buffer], found [%s] %p&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
r_goto
id|next_operand
suffix:semicolon
r_case
id|ARGI_COMPUTEDATA
suffix:colon
multiline_comment|/* Need an operand of type INTEGER, STRING or BUFFER */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/* Valid operand */
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Needed [Integer/String/Buffer], found [%s] %p&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
r_goto
id|next_operand
suffix:semicolon
r_case
id|ARGI_BUFFER_OR_STRING
suffix:colon
multiline_comment|/* Need an operand of type STRING or BUFFER */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/* Valid operand */
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
multiline_comment|/* Highest priority conversion is to type Buffer */
id|status
op_assign
id|acpi_ex_convert_to_buffer
(paren
id|obj_desc
comma
id|stack_ptr
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
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Needed [Integer/String/Buffer], found [%s] %p&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
r_goto
id|next_operand
suffix:semicolon
r_case
id|ARGI_DATAOBJECT
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * ARGI_DATAOBJECT is only used by the size_of operator.&n;&t;&t;&t; * Need a buffer, string, package, or ref_of reference.&n;&t;&t;&t; *&n;&t;&t;&t; * The only reference allowed here is a direct reference to&n;&t;&t;&t; * a namespace node.&n;&t;&t;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_REFERENCE
suffix:colon
multiline_comment|/* Valid operand */
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Needed [Buffer/String/Package/Reference], found [%s] %p&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
r_goto
id|next_operand
suffix:semicolon
r_case
id|ARGI_COMPLEXOBJ
suffix:colon
multiline_comment|/* Need a buffer or package or (ACPI 2.0) String */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
multiline_comment|/* Valid operand */
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Needed [Buffer/String/Package], found [%s] %p&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
r_goto
id|next_operand
suffix:semicolon
r_case
id|ARGI_REGION_OR_FIELD
suffix:colon
multiline_comment|/* Need an operand of type ACPI_TYPE_REGION or a FIELD in a region */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_REGION
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
multiline_comment|/* Valid operand */
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Needed [Region/region_field], found [%s] %p&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
r_goto
id|next_operand
suffix:semicolon
r_case
id|ARGI_DATAREFOBJ
suffix:colon
multiline_comment|/* Used by the Store() operator only */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|obj_desc
)paren
)paren
(brace
r_case
id|ACPI_TYPE_INTEGER
suffix:colon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
r_case
id|ACPI_TYPE_STRING
suffix:colon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_REFERENCE
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
r_case
id|ACPI_TYPE_DDB_HANDLE
suffix:colon
multiline_comment|/* Valid operand */
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|acpi_gbl_enable_interpreter_slack
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t;&t; * Enable original behavior of Store(), allowing any and all&n;&t;&t;&t;&t;&t; * objects as the source operand.  The ACPI spec does not&n;&t;&t;&t;&t;&t; * allow this, however.&n;&t;&t;&t;&t;&t; */
r_break
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Needed Integer/Buffer/String/Package/Ref/Ddb], found [%s] %p&bslash;n&quot;
comma
id|acpi_ut_get_object_type_name
(paren
id|obj_desc
)paren
comma
id|obj_desc
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_OPERAND_TYPE
)paren
suffix:semicolon
)brace
r_goto
id|next_operand
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Unknown type */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Internal - Unknown ARGI (required operand) type %X&bslash;n&quot;
comma
id|this_arg_type
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Make sure that the original object was resolved to the&n;&t;&t; * required object type (Simple cases only).&n;&t;&t; */
id|status
op_assign
id|acpi_ex_check_object_type
(paren
id|type_needed
comma
id|ACPI_GET_OBJECT_TYPE
(paren
op_star
id|stack_ptr
)paren
comma
op_star
id|stack_ptr
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
id|next_operand
suffix:colon
multiline_comment|/*&n;&t;&t; * If more operands needed, decrement stack_ptr to point&n;&t;&t; * to next operand on stack&n;&t;&t; */
r_if
c_cond
(paren
id|GET_CURRENT_ARG_TYPE
(paren
id|arg_types
)paren
)paren
(brace
id|stack_ptr
op_decrement
suffix:semicolon
)brace
)brace
multiline_comment|/* while (*Types) */
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
