multiline_comment|/******************************************************************************&n; *&n; * Module Name: psargs - Parse AML opcode arguments&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2003, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acparser.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_PARSER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;psargs&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_get_next_package_length&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *&n; * RETURN:      Decoded package length.  On completion, the AML pointer points&n; *              past the length byte or bytes.&n; *&n; * DESCRIPTION: Decode and return a package length field&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ps_get_next_package_length
id|acpi_ps_get_next_package_length
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
(brace
id|u32
id|encoded_length
suffix:semicolon
id|u32
id|length
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ps_get_next_package_length&quot;
)paren
suffix:semicolon
id|encoded_length
op_assign
(paren
id|u32
)paren
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
)paren
suffix:semicolon
id|parser_state-&gt;aml
op_increment
suffix:semicolon
r_switch
c_cond
(paren
id|encoded_length
op_rshift
l_int|6
)paren
multiline_comment|/* bits 6-7 contain encoding scheme */
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* 1-byte encoding (bits 0-5) */
id|length
op_assign
(paren
id|encoded_length
op_amp
l_int|0x3F
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
multiline_comment|/* 2-byte encoding (next byte + bits 0-3) */
id|length
op_assign
(paren
(paren
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
)paren
op_lshift
l_int|04
)paren
op_or
(paren
id|encoded_length
op_amp
l_int|0x0F
)paren
)paren
suffix:semicolon
id|parser_state-&gt;aml
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* 3-byte encoding (next 2 bytes + bits 0-3) */
id|length
op_assign
(paren
(paren
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
op_plus
l_int|1
)paren
op_lshift
l_int|12
)paren
op_or
(paren
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
)paren
op_lshift
l_int|04
)paren
op_or
(paren
id|encoded_length
op_amp
l_int|0x0F
)paren
)paren
suffix:semicolon
id|parser_state-&gt;aml
op_add_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* 4-byte encoding (next 3 bytes + bits 0-3) */
id|length
op_assign
(paren
(paren
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
op_plus
l_int|2
)paren
op_lshift
l_int|20
)paren
op_or
(paren
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
op_plus
l_int|1
)paren
op_lshift
l_int|12
)paren
op_or
(paren
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
)paren
op_lshift
l_int|04
)paren
op_or
(paren
id|encoded_length
op_amp
l_int|0x0F
)paren
)paren
suffix:semicolon
id|parser_state-&gt;aml
op_add_assign
l_int|3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Can&squot;t get here, only 2 bits / 4 cases */
r_break
suffix:semicolon
)brace
id|return_VALUE
(paren
id|length
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_get_next_package_end&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *&n; * RETURN:      Pointer to end-of-package +1&n; *&n; * DESCRIPTION: Get next package length and return a pointer past the end of&n; *              the package.  Consumes the package length field&n; *&n; ******************************************************************************/
id|u8
op_star
DECL|function|acpi_ps_get_next_package_end
id|acpi_ps_get_next_package_end
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
(brace
id|u8
op_star
id|start
op_assign
id|parser_state-&gt;aml
suffix:semicolon
id|acpi_native_uint
id|length
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ps_get_next_package_end&quot;
)paren
suffix:semicolon
multiline_comment|/* Function below changes parser_state-&gt;Aml */
id|length
op_assign
(paren
id|acpi_native_uint
)paren
id|acpi_ps_get_next_package_length
(paren
id|parser_state
)paren
suffix:semicolon
id|return_PTR
(paren
id|start
op_plus
id|length
)paren
suffix:semicolon
multiline_comment|/* end of package */
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_get_next_namestring&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *&n; * RETURN:      Pointer to the start of the name string (pointer points into&n; *              the AML.&n; *&n; * DESCRIPTION: Get next raw namestring within the AML stream.  Handles all name&n; *              prefix characters.  Set parser state to point past the string.&n; *              (Name is consumed from the AML.)&n; *&n; ******************************************************************************/
r_char
op_star
DECL|function|acpi_ps_get_next_namestring
id|acpi_ps_get_next_namestring
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
(brace
id|u8
op_star
id|start
op_assign
id|parser_state-&gt;aml
suffix:semicolon
id|u8
op_star
id|end
op_assign
id|parser_state-&gt;aml
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ps_get_next_namestring&quot;
)paren
suffix:semicolon
multiline_comment|/* Handle multiple prefix characters */
r_while
c_loop
(paren
id|acpi_ps_is_prefix_char
(paren
id|ACPI_GET8
(paren
id|end
)paren
)paren
)paren
(brace
multiline_comment|/* Include prefix &squot;&bslash;&bslash;&squot; or &squot;^&squot; */
id|end
op_increment
suffix:semicolon
)brace
multiline_comment|/* Decode the path */
r_switch
c_cond
(paren
id|ACPI_GET8
(paren
id|end
)paren
)paren
(brace
r_case
l_int|0
suffix:colon
multiline_comment|/* null_name */
r_if
c_cond
(paren
id|end
op_eq
id|start
)paren
(brace
id|start
op_assign
l_int|NULL
suffix:semicolon
)brace
id|end
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_DUAL_NAME_PREFIX
suffix:colon
multiline_comment|/* Two name segments */
id|end
op_add_assign
l_int|1
op_plus
(paren
l_int|2
op_star
id|ACPI_NAME_SIZE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_MULTI_NAME_PREFIX_OP
suffix:colon
multiline_comment|/* Multiple name segments, 4 chars each */
id|end
op_add_assign
l_int|2
op_plus
(paren
(paren
id|acpi_size
)paren
id|ACPI_GET8
(paren
id|end
op_plus
l_int|1
)paren
op_star
id|ACPI_NAME_SIZE
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Single name segment */
id|end
op_add_assign
id|ACPI_NAME_SIZE
suffix:semicolon
r_break
suffix:semicolon
)brace
id|parser_state-&gt;aml
op_assign
(paren
id|u8
op_star
)paren
id|end
suffix:semicolon
id|return_PTR
(paren
(paren
r_char
op_star
)paren
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_get_next_namepath&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *              Arg                 - Where the namepath will be stored&n; *              arg_count           - If the namepath points to a control method&n; *                                    the method&squot;s argument is returned here.&n; *              method_call         - Whether the namepath can possibly be the&n; *                                    start of a method call&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Get next name (if method call, return # of required args).&n; *              Names are looked up in the internal namespace to determine&n; *              if the name represents a control method.  If a method&n; *              is found, the number of arguments to the method is returned.&n; *              This information is critical for parsing to continue correctly.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ps_get_next_namepath
id|acpi_ps_get_next_namepath
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
r_union
id|acpi_parse_object
op_star
id|arg
comma
id|u8
id|method_call
)paren
(brace
r_char
op_star
id|path
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|name_op
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|method_desc
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
r_union
id|acpi_generic_state
id|scope_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ps_get_next_namepath&quot;
)paren
suffix:semicolon
id|path
op_assign
id|acpi_ps_get_next_namestring
(paren
id|parser_state
)paren
suffix:semicolon
multiline_comment|/* Null path case is allowed */
r_if
c_cond
(paren
id|path
)paren
(brace
multiline_comment|/*&n;&t;&t; * Lookup the name in the internal namespace&n;&t;&t; */
id|scope_info.scope.node
op_assign
l_int|NULL
suffix:semicolon
id|node
op_assign
id|parser_state-&gt;start_node
suffix:semicolon
r_if
c_cond
(paren
id|node
)paren
(brace
id|scope_info.scope.node
op_assign
id|node
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Lookup object.  We don&squot;t want to add anything new to the namespace&n;&t;&t; * here, however.  So we use MODE_EXECUTE.  Allow searching of the&n;&t;&t; * parent tree, but don&squot;t open a new scope -- we just want to lookup the&n;&t;&t; * object  (MUST BE mode EXECUTE to perform upsearch)&n;&t;&t; */
id|status
op_assign
id|acpi_ns_lookup
(paren
op_amp
id|scope_info
comma
id|path
comma
id|ACPI_TYPE_ANY
comma
id|ACPI_IMODE_EXECUTE
comma
id|ACPI_NS_SEARCH_PARENT
op_or
id|ACPI_NS_DONT_OPEN_SCOPE
comma
l_int|NULL
comma
op_amp
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
(paren
id|status
)paren
op_logical_and
id|method_call
)paren
(brace
r_if
c_cond
(paren
id|node-&gt;type
op_eq
id|ACPI_TYPE_METHOD
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * This name is actually a control method invocation&n;&t;&t;&t;&t; */
id|method_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|node
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_PARSE
comma
l_string|&quot;Control Method - %p Desc %p Path=%p&bslash;n&quot;
comma
id|node
comma
id|method_desc
comma
id|path
)paren
)paren
suffix:semicolon
id|name_op
op_assign
id|acpi_ps_alloc_op
(paren
id|AML_INT_NAMEPATH_OP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|name_op
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Change arg into a METHOD CALL and attach name to it */
id|acpi_ps_init_op
(paren
id|arg
comma
id|AML_INT_METHODCALL_OP
)paren
suffix:semicolon
id|name_op-&gt;common.value.name
op_assign
id|path
suffix:semicolon
multiline_comment|/* Point METHODCALL/NAME to the METHOD Node */
id|name_op-&gt;common.node
op_assign
id|node
suffix:semicolon
id|acpi_ps_append_arg
(paren
id|arg
comma
id|name_op
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|method_desc
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_PARSE
comma
l_string|&quot;Control Method - %p has no attached object&bslash;n&quot;
comma
id|node
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
id|ACPI_DB_PARSE
comma
l_string|&quot;Control Method - %p Args %X&bslash;n&quot;
comma
id|node
comma
id|method_desc-&gt;method.param_count
)paren
)paren
suffix:semicolon
multiline_comment|/* Get the number of arguments to expect */
id|walk_state-&gt;arg_count
op_assign
id|method_desc-&gt;method.param_count
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Else this is normal named object reference.&n;&t;&t;&t; * Just init the NAMEPATH object with the pathname.&n;&t;&t;&t; * (See code below)&n;&t;&t;&t; */
)brace
r_if
c_cond
(paren
id|ACPI_FAILURE
(paren
id|status
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * 1) Any error other than NOT_FOUND is always severe&n;&t;&t;&t; * 2) NOT_FOUND is only important if we are executing a method.&n;&t;&t;&t; * 3) If executing a cond_ref_of opcode, NOT_FOUND is ok.&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
(paren
(paren
id|walk_state-&gt;parse_flags
op_amp
id|ACPI_PARSE_MODE_MASK
)paren
op_eq
id|ACPI_PARSE_EXECUTE
)paren
op_logical_and
(paren
id|status
op_eq
id|AE_NOT_FOUND
)paren
op_logical_and
(paren
id|walk_state-&gt;op-&gt;common.aml_opcode
op_ne
id|AML_COND_REF_OF_OP
)paren
)paren
op_logical_or
(paren
id|status
op_ne
id|AE_NOT_FOUND
)paren
)paren
(brace
id|ACPI_REPORT_NSERROR
(paren
id|path
comma
id|status
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * We got a NOT_FOUND during table load or we encountered&n;&t;&t;&t;&t; * a cond_ref_of(x) where the target does not exist.&n;&t;&t;&t;&t; * -- either case is ok&n;&t;&t;&t;&t; */
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t; * Regardless of success/failure above,&n;&t; * Just initialize the Op with the pathname.&n;&t; */
id|acpi_ps_init_op
(paren
id|arg
comma
id|AML_INT_NAMEPATH_OP
)paren
suffix:semicolon
id|arg-&gt;common.value.name
op_assign
id|path
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_get_next_simple_arg&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *              arg_type            - The argument type (AML_*_ARG)&n; *              Arg                 - Where the argument is returned&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Get the next simple argument (constant, string, or namestring)&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ps_get_next_simple_arg
id|acpi_ps_get_next_simple_arg
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
id|u32
id|arg_type
comma
r_union
id|acpi_parse_object
op_star
id|arg
)paren
(brace
id|ACPI_FUNCTION_TRACE_U32
(paren
l_string|&quot;ps_get_next_simple_arg&quot;
comma
id|arg_type
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|arg_type
)paren
(brace
r_case
id|ARGP_BYTEDATA
suffix:colon
id|acpi_ps_init_op
(paren
id|arg
comma
id|AML_BYTE_OP
)paren
suffix:semicolon
id|arg-&gt;common.value.integer
op_assign
(paren
id|u32
)paren
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
)paren
suffix:semicolon
id|parser_state-&gt;aml
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGP_WORDDATA
suffix:colon
id|acpi_ps_init_op
(paren
id|arg
comma
id|AML_WORD_OP
)paren
suffix:semicolon
multiline_comment|/* Get 2 bytes from the AML stream */
id|ACPI_MOVE_UNALIGNED16_TO_32
(paren
op_amp
id|arg-&gt;common.value.integer
comma
id|parser_state-&gt;aml
)paren
suffix:semicolon
id|parser_state-&gt;aml
op_add_assign
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGP_DWORDDATA
suffix:colon
id|acpi_ps_init_op
(paren
id|arg
comma
id|AML_DWORD_OP
)paren
suffix:semicolon
multiline_comment|/* Get 4 bytes from the AML stream */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|arg-&gt;common.value.integer
comma
id|parser_state-&gt;aml
)paren
suffix:semicolon
id|parser_state-&gt;aml
op_add_assign
l_int|4
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGP_QWORDDATA
suffix:colon
id|acpi_ps_init_op
(paren
id|arg
comma
id|AML_QWORD_OP
)paren
suffix:semicolon
multiline_comment|/* Get 8 bytes from the AML stream */
id|ACPI_MOVE_UNALIGNED64_TO_64
(paren
op_amp
id|arg-&gt;common.value.integer
comma
id|parser_state-&gt;aml
)paren
suffix:semicolon
id|parser_state-&gt;aml
op_add_assign
l_int|8
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGP_CHARLIST
suffix:colon
id|acpi_ps_init_op
(paren
id|arg
comma
id|AML_STRING_OP
)paren
suffix:semicolon
id|arg-&gt;common.value.string
op_assign
(paren
r_char
op_star
)paren
id|parser_state-&gt;aml
suffix:semicolon
r_while
c_loop
(paren
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
)paren
op_ne
l_char|&squot;&bslash;0&squot;
)paren
(brace
id|parser_state-&gt;aml
op_increment
suffix:semicolon
)brace
id|parser_state-&gt;aml
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGP_NAME
suffix:colon
r_case
id|ARGP_NAMESTRING
suffix:colon
id|acpi_ps_init_op
(paren
id|arg
comma
id|AML_INT_NAMEPATH_OP
)paren
suffix:semicolon
id|arg-&gt;common.value.name
op_assign
id|acpi_ps_get_next_namestring
(paren
id|parser_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid arg_type %X&bslash;n&quot;
comma
id|arg_type
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_get_next_field&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *&n; * RETURN:      A newly allocated FIELD op&n; *&n; * DESCRIPTION: Get next field (named_field, reserved_field, or access_field)&n; *&n; ******************************************************************************/
r_union
id|acpi_parse_object
op_star
DECL|function|acpi_ps_get_next_field
id|acpi_ps_get_next_field
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
(brace
id|u32
id|aml_offset
op_assign
id|ACPI_PTR_DIFF
(paren
id|parser_state-&gt;aml
comma
id|parser_state-&gt;aml_start
)paren
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|field
suffix:semicolon
id|u16
id|opcode
suffix:semicolon
id|u32
id|name
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ps_get_next_field&quot;
)paren
suffix:semicolon
multiline_comment|/* determine field type */
r_switch
c_cond
(paren
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
)paren
)paren
(brace
r_default
suffix:colon
id|opcode
op_assign
id|AML_INT_NAMEDFIELD_OP
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x00
suffix:colon
id|opcode
op_assign
id|AML_INT_RESERVEDFIELD_OP
suffix:semicolon
id|parser_state-&gt;aml
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x01
suffix:colon
id|opcode
op_assign
id|AML_INT_ACCESSFIELD_OP
suffix:semicolon
id|parser_state-&gt;aml
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/* Allocate a new field op */
id|field
op_assign
id|acpi_ps_alloc_op
(paren
id|opcode
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|field
)paren
(brace
id|return_PTR
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
id|field-&gt;common.aml_offset
op_assign
id|aml_offset
suffix:semicolon
multiline_comment|/* Decode the field type */
r_switch
c_cond
(paren
id|opcode
)paren
(brace
r_case
id|AML_INT_NAMEDFIELD_OP
suffix:colon
multiline_comment|/* Get the 4-character name */
id|ACPI_MOVE_UNALIGNED32_TO_32
(paren
op_amp
id|name
comma
id|parser_state-&gt;aml
)paren
suffix:semicolon
id|acpi_ps_set_name
(paren
id|field
comma
id|name
)paren
suffix:semicolon
id|parser_state-&gt;aml
op_add_assign
id|ACPI_NAME_SIZE
suffix:semicolon
multiline_comment|/* Get the length which is encoded as a package length */
id|field-&gt;common.value.size
op_assign
id|acpi_ps_get_next_package_length
(paren
id|parser_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INT_RESERVEDFIELD_OP
suffix:colon
multiline_comment|/* Get the length which is encoded as a package length */
id|field-&gt;common.value.size
op_assign
id|acpi_ps_get_next_package_length
(paren
id|parser_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|AML_INT_ACCESSFIELD_OP
suffix:colon
multiline_comment|/*&n;&t;&t; * Get access_type and access_attrib and merge into the field Op&n;&t;&t; * access_type is first operand, access_attribute is second&n;&t;&t; */
id|field-&gt;common.value.integer32
op_assign
(paren
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|parser_state-&gt;aml
op_increment
suffix:semicolon
id|field-&gt;common.value.integer32
op_or_assign
id|ACPI_GET8
(paren
id|parser_state-&gt;aml
)paren
suffix:semicolon
id|parser_state-&gt;aml
op_increment
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Opcode was set in previous switch */
r_break
suffix:semicolon
)brace
id|return_PTR
(paren
id|field
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_get_next_arg&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *              arg_type            - The argument type (AML_*_ARG)&n; *              arg_count           - If the argument points to a control method&n; *                                    the method&squot;s argument is returned here.&n; *&n; * RETURN:      Status, and an op object containing the next argument.&n; *&n; * DESCRIPTION: Get next argument (including complex list arguments that require&n; *              pushing the parser stack)&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ps_get_next_arg
id|acpi_ps_get_next_arg
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
id|u32
id|arg_type
comma
r_union
id|acpi_parse_object
op_star
op_star
id|return_arg
)paren
(brace
r_union
id|acpi_parse_object
op_star
id|arg
op_assign
l_int|NULL
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|prev
op_assign
l_int|NULL
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|field
suffix:semicolon
id|u32
id|subop
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ps_get_next_arg&quot;
comma
id|parser_state
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|arg_type
)paren
(brace
r_case
id|ARGP_BYTEDATA
suffix:colon
r_case
id|ARGP_WORDDATA
suffix:colon
r_case
id|ARGP_DWORDDATA
suffix:colon
r_case
id|ARGP_CHARLIST
suffix:colon
r_case
id|ARGP_NAME
suffix:colon
r_case
id|ARGP_NAMESTRING
suffix:colon
multiline_comment|/* constants, strings, and namestrings are all the same size */
id|arg
op_assign
id|acpi_ps_alloc_op
(paren
id|AML_BYTE_OP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|acpi_ps_get_next_simple_arg
(paren
id|parser_state
comma
id|arg_type
comma
id|arg
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGP_PKGLENGTH
suffix:colon
multiline_comment|/* Package length, nothing returned */
id|parser_state-&gt;pkg_end
op_assign
id|acpi_ps_get_next_package_end
(paren
id|parser_state
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGP_FIELDLIST
suffix:colon
r_if
c_cond
(paren
id|parser_state-&gt;aml
OL
id|parser_state-&gt;pkg_end
)paren
(brace
multiline_comment|/* Non-empty list */
r_while
c_loop
(paren
id|parser_state-&gt;aml
OL
id|parser_state-&gt;pkg_end
)paren
(brace
id|field
op_assign
id|acpi_ps_get_next_field
(paren
id|parser_state
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|field
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|prev
)paren
(brace
id|prev-&gt;common.next
op_assign
id|field
suffix:semicolon
)brace
r_else
(brace
id|arg
op_assign
id|field
suffix:semicolon
)brace
id|prev
op_assign
id|field
suffix:semicolon
)brace
multiline_comment|/* Skip to End of byte data */
id|parser_state-&gt;aml
op_assign
id|parser_state-&gt;pkg_end
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ARGP_BYTELIST
suffix:colon
r_if
c_cond
(paren
id|parser_state-&gt;aml
OL
id|parser_state-&gt;pkg_end
)paren
(brace
multiline_comment|/* Non-empty list */
id|arg
op_assign
id|acpi_ps_alloc_op
(paren
id|AML_INT_BYTELIST_OP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Fill in bytelist data */
id|arg-&gt;common.value.size
op_assign
id|ACPI_PTR_DIFF
(paren
id|parser_state-&gt;pkg_end
comma
id|parser_state-&gt;aml
)paren
suffix:semicolon
id|arg-&gt;named.data
op_assign
id|parser_state-&gt;aml
suffix:semicolon
multiline_comment|/* Skip to End of byte data */
id|parser_state-&gt;aml
op_assign
id|parser_state-&gt;pkg_end
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ARGP_TARGET
suffix:colon
r_case
id|ARGP_SUPERNAME
suffix:colon
r_case
id|ARGP_SIMPLENAME
suffix:colon
id|subop
op_assign
id|acpi_ps_peek_opcode
(paren
id|parser_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|subop
op_eq
l_int|0
op_logical_or
id|acpi_ps_is_leading_char
(paren
id|subop
)paren
op_logical_or
id|acpi_ps_is_prefix_char
(paren
id|subop
)paren
)paren
(brace
multiline_comment|/* null_name or name_string */
id|arg
op_assign
id|acpi_ps_alloc_op
(paren
id|AML_INT_NAMEPATH_OP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|arg
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ps_get_next_namepath
(paren
id|walk_state
comma
id|parser_state
comma
id|arg
comma
l_int|0
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* single complex argument, nothing returned */
id|walk_state-&gt;arg_count
op_assign
l_int|1
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ARGP_DATAOBJ
suffix:colon
r_case
id|ARGP_TERMARG
suffix:colon
multiline_comment|/* single complex argument, nothing returned */
id|walk_state-&gt;arg_count
op_assign
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ARGP_DATAOBJLIST
suffix:colon
r_case
id|ARGP_TERMLIST
suffix:colon
r_case
id|ARGP_OBJLIST
suffix:colon
r_if
c_cond
(paren
id|parser_state-&gt;aml
OL
id|parser_state-&gt;pkg_end
)paren
(brace
multiline_comment|/* non-empty list of variable arguments, nothing returned */
id|walk_state-&gt;arg_count
op_assign
id|ACPI_VAR_ARGS
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Invalid arg_type: %X&bslash;n&quot;
comma
id|arg_type
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
op_star
id|return_arg
op_assign
id|arg
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
