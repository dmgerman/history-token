multiline_comment|/******************************************************************************&n; *&n; * Module Name: exresop - AML Interpreter operand/object resolution&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acinterp.h&quot;
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
id|acpi_operand_object
op_star
op_star
id|stack_ptr
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Internal - %X is not a valid AML opcode&bslash;n&quot;
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
l_string|&quot;Opcode %X [%s] operand_types=%X &bslash;n&quot;
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Internal - null stack entry at %p&bslash;n&quot;
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
id|ACPI_DEBUG_ONLY_MEMBERS
(paren
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Reference Opcode: %s&bslash;n&quot;
comma
id|op_info-&gt;name
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
l_string|&quot;Unknown Reference Opcode %X&bslash;n&quot;
comma
id|obj_desc-&gt;reference.opcode
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
l_string|&quot;Bad descriptor type %X in Obj %p&bslash;n&quot;
comma
id|ACPI_GET_DESCRIPTOR_TYPE
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
id|ARGI_REGION
suffix:colon
multiline_comment|/* Need an operand of type ACPI_TYPE_REGION */
id|type_needed
op_assign
id|ACPI_TYPE_REGION
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
l_int|16
comma
id|ACPI_UINT32_MAX
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
l_string|&quot;Needed [Buf/Str/Pkg], found [%s] %p&bslash;n&quot;
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
l_string|&quot;Needed [Buf/Str/Pkg], found [%s] %p&bslash;n&quot;
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
