multiline_comment|/******************************************************************************&n; *&n; * Module Name: psargs - Parse AML opcode arguments&n; *              $Revision: 62 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_PARSER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;psargs&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_next_package_length&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *&n; * RETURN:      Decoded package length.  On completion, the AML pointer points&n; *              past the length byte or bytes.&n; *&n; * DESCRIPTION: Decode and return a package length field&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ps_get_next_package_length
id|acpi_ps_get_next_package_length
(paren
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
l_string|&quot;Ps_get_next_package_length&quot;
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_next_package_end&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *&n; * RETURN:      Pointer to end-of-package +1&n; *&n; * DESCRIPTION: Get next package length and return a pointer past the end of&n; *              the package.  Consumes the package length field&n; *&n; ******************************************************************************/
id|u8
op_star
DECL|function|acpi_ps_get_next_package_end
id|acpi_ps_get_next_package_end
(paren
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
id|NATIVE_UINT
id|length
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ps_get_next_package_end&quot;
)paren
suffix:semicolon
id|length
op_assign
(paren
id|NATIVE_UINT
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_next_namestring&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *&n; * RETURN:      Pointer to the start of the name string (pointer points into&n; *              the AML.&n; *&n; * DESCRIPTION: Get next raw namestring within the AML stream.  Handles all name&n; *              prefix characters.  Set parser state to point past the string.&n; *              (Name is consumed from the AML.)&n; *&n; ******************************************************************************/
id|NATIVE_CHAR
op_star
DECL|function|acpi_ps_get_next_namestring
id|acpi_ps_get_next_namestring
(paren
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
l_string|&quot;Ps_get_next_namestring&quot;
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
multiline_comment|/* include prefix &squot;&bslash;&bslash;&squot; or &squot;^&squot; */
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
multiline_comment|/* Null_name */
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
l_int|9
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
id|ACPI_SIZE
)paren
id|ACPI_GET8
(paren
id|end
op_plus
l_int|1
)paren
op_star
l_int|4
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* Single name segment */
id|end
op_add_assign
l_int|4
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
id|NATIVE_CHAR
op_star
)paren
id|start
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_next_namepath&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *              Arg                 - Where the namepath will be stored&n; *              Arg_count           - If the namepath points to a control method&n; *                                    the method&squot;s argument is returned here.&n; *              Method_call         - Whether the namepath can be the start&n; *                                    of a method call&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Get next name (if method call, push appropriate # args).  Names&n; *              are looked up in either the parsed or internal namespace to&n; *              determine if the name represents a control method.  If a method&n; *              is found, the number of arguments to the method is returned.&n; *              This information is critical for parsing to continue correctly.&n; *&n; ******************************************************************************/
macro_line|#ifdef PARSER_ONLY
r_void
DECL|function|acpi_ps_get_next_namepath
id|acpi_ps_get_next_namepath
(paren
id|acpi_parse_state
op_star
id|parser_state
comma
id|acpi_parse_object
op_star
id|arg
comma
id|u32
op_star
id|arg_count
comma
id|u8
id|method_call
)paren
(brace
id|NATIVE_CHAR
op_star
id|path
suffix:semicolon
id|acpi_parse_object
op_star
id|name_op
suffix:semicolon
id|acpi_parse_object
op_star
id|op
suffix:semicolon
id|acpi_parse_object
op_star
id|count
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ps_get_next_namepath&quot;
)paren
suffix:semicolon
id|path
op_assign
id|acpi_ps_get_next_namestring
(paren
id|parser_state
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
op_logical_or
op_logical_neg
id|method_call
)paren
(brace
multiline_comment|/* Null name case, create a null namepath object */
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
id|return_VOID
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_gbl_parsed_namespace_root
)paren
(brace
multiline_comment|/*&n;&t;&t; * Lookup the name in the parsed namespace&n;&t;&t; */
id|op
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
id|method_call
)paren
(brace
id|op
op_assign
id|acpi_ps_find
(paren
id|acpi_ps_get_parent_scope
(paren
id|parser_state
)paren
comma
id|path
comma
id|AML_METHOD_OP
comma
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|op
)paren
(brace
r_if
c_cond
(paren
id|op-&gt;common.aml_opcode
op_eq
id|AML_METHOD_OP
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * The name refers to a control method, so this namepath is a&n;&t;&t;&t;&t; * method invocation.  We need to 1) Get the number of arguments&n;&t;&t;&t;&t; * associated with this method, and 2) Change the NAMEPATH&n;&t;&t;&t;&t; * object into a METHODCALL object.&n;&t;&t;&t;&t; */
id|count
op_assign
id|acpi_ps_get_arg
(paren
id|op
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_logical_and
id|count-&gt;common.aml_opcode
op_eq
id|AML_BYTE_OP
)paren
(brace
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
id|name_op
)paren
(brace
multiline_comment|/* Change arg into a METHOD CALL and attach the name */
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
(paren
id|acpi_namespace_node
op_star
)paren
id|op
suffix:semicolon
id|acpi_ps_append_arg
(paren
id|arg
comma
id|name_op
)paren
suffix:semicolon
op_star
id|arg_count
op_assign
(paren
id|u32
)paren
id|count-&gt;common.value.integer
op_amp
id|METHOD_FLAGS_ARG_COUNT
suffix:semicolon
)brace
)brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Else this is normal named object reference.&n;&t;&t;&t; * Just init the NAMEPATH object with the pathname.&n;&t;&t;&t; * (See code below)&n;&t;&t;&t; */
)brace
)brace
multiline_comment|/*&n;&t; * Either we didn&squot;t find the object in the namespace, or the object is&n;&t; * something other than a control method.  Just initialize the Op with the&n;&t; * pathname&n;&t; */
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
id|return_VOID
suffix:semicolon
)brace
macro_line|#else
r_void
DECL|function|acpi_ps_get_next_namepath
id|acpi_ps_get_next_namepath
(paren
id|acpi_parse_state
op_star
id|parser_state
comma
id|acpi_parse_object
op_star
id|arg
comma
id|u32
op_star
id|arg_count
comma
id|u8
id|method_call
)paren
(brace
id|NATIVE_CHAR
op_star
id|path
suffix:semicolon
id|acpi_parse_object
op_star
id|name_op
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|acpi_operand_object
op_star
id|method_desc
suffix:semicolon
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_generic_state
id|scope_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ps_get_next_namepath&quot;
)paren
suffix:semicolon
id|path
op_assign
id|acpi_ps_get_next_namestring
(paren
id|parser_state
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|path
op_logical_or
op_logical_neg
id|method_call
)paren
(brace
multiline_comment|/* Null name case, create a null namepath object */
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
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Lookup the name in the internal namespace&n;&t; */
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
multiline_comment|/*&n;&t; * Lookup object.  We don&squot;t want to add anything new to the namespace&n;&t; * here, however.  So we use MODE_EXECUTE.  Allow searching of the&n;&t; * parent tree, but don&squot;t open a new scope -- we just want to lookup the&n;&t; * object  (MUST BE mode EXECUTE to perform upsearch)&n;&t; */
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
id|return_VOID
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
id|return_VOID
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
op_star
id|arg_count
op_assign
id|method_desc-&gt;method.param_count
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Else this is normal named object reference.&n;&t;&t; * Just init the NAMEPATH object with the pathname.&n;&t;&t; * (See code below)&n;&t;&t; */
)brace
multiline_comment|/*&n;&t; * Either we didn&squot;t find the object in the namespace, or the object is&n;&t; * something other than a control method.  Just initialize the Op with the&n;&t; * pathname.&n;&t; */
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
id|return_VOID
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_next_simple_arg&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *              Arg_type            - The argument type (AML_*_ARG)&n; *              Arg                 - Where the argument is returned&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Get the next simple argument (constant, string, or namestring)&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ps_get_next_simple_arg
id|acpi_ps_get_next_simple_arg
(paren
id|acpi_parse_state
op_star
id|parser_state
comma
id|u32
id|arg_type
comma
id|acpi_parse_object
op_star
id|arg
)paren
(brace
id|ACPI_FUNCTION_TRACE_U32
(paren
l_string|&quot;Ps_get_next_simple_arg&quot;
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
l_string|&quot;Invalid Arg_type %X&bslash;n&quot;
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_next_field&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *&n; * RETURN:      A newly allocated FIELD op&n; *&n; * DESCRIPTION: Get next field (Named_field, Reserved_field, or Access_field)&n; *&n; ******************************************************************************/
id|acpi_parse_object
op_star
DECL|function|acpi_ps_get_next_field
id|acpi_ps_get_next_field
(paren
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
l_string|&quot;Ps_get_next_field&quot;
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
l_int|4
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
multiline_comment|/*&n;&t;&t; * Get Access_type and Access_attrib and merge into the field Op&n;&t;&t; * Access_type is first operand, Access_attribute is second&n;&t;&t; */
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
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_next_arg&n; *&n; * PARAMETERS:  Parser_state        - Current parser state object&n; *              Arg_type            - The argument type (AML_*_ARG)&n; *              Arg_count           - If the argument points to a control method&n; *                                    the method&squot;s argument is returned here.&n; *&n; * RETURN:      An op object containing the next argument.&n; *&n; * DESCRIPTION: Get next argument (including complex list arguments that require&n; *              pushing the parser stack)&n; *&n; ******************************************************************************/
id|acpi_parse_object
op_star
DECL|function|acpi_ps_get_next_arg
id|acpi_ps_get_next_arg
(paren
id|acpi_parse_state
op_star
id|parser_state
comma
id|u32
id|arg_type
comma
id|u32
op_star
id|arg_count
)paren
(brace
id|acpi_parse_object
op_star
id|arg
op_assign
l_int|NULL
suffix:semicolon
id|acpi_parse_object
op_star
id|prev
op_assign
l_int|NULL
suffix:semicolon
id|acpi_parse_object
op_star
id|field
suffix:semicolon
id|u32
id|subop
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ps_get_next_arg&quot;
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
id|arg
)paren
(brace
id|acpi_ps_get_next_simple_arg
(paren
id|parser_state
comma
id|arg_type
comma
id|arg
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ARGP_PKGLENGTH
suffix:colon
multiline_comment|/* package length, nothing returned */
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
multiline_comment|/* non-empty list */
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
r_break
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
multiline_comment|/* skip to End of byte data */
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
multiline_comment|/* non-empty list */
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
id|arg
)paren
(brace
multiline_comment|/* fill in bytelist data */
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
)brace
multiline_comment|/* skip to End of byte data */
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
(brace
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
multiline_comment|/* Null_name or Name_string */
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
id|arg
)paren
(brace
id|acpi_ps_get_next_namepath
(paren
id|parser_state
comma
id|arg
comma
id|arg_count
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* single complex argument, nothing returned */
op_star
id|arg_count
op_assign
l_int|1
suffix:semicolon
)brace
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
op_star
id|arg_count
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
op_star
id|arg_count
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
l_string|&quot;Invalid Arg_type: %X&bslash;n&quot;
comma
id|arg_type
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_PTR
(paren
id|arg
)paren
suffix:semicolon
)brace
eof
