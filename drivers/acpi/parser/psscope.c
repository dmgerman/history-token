multiline_comment|/******************************************************************************&n; *&n; * Module Name: psscope - Parser scope stack management routines&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acparser.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_PARSER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;psscope&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_get_parent_scope&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *&n; * RETURN:      Pointer to an Op object&n; *&n; * DESCRIPTION: Get parent of current op being parsed&n; *&n; ******************************************************************************/
r_union
id|acpi_parse_object
op_star
DECL|function|acpi_ps_get_parent_scope
id|acpi_ps_get_parent_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
(brace
r_return
(paren
id|parser_state-&gt;scope-&gt;parse_scope.op
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_has_completed_scope&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *&n; * RETURN:      Boolean, TRUE = scope completed.&n; *&n; * DESCRIPTION: Is parsing of current argument complete?  Determined by&n; *              1) AML pointer is at or beyond the end of the scope&n; *              2) The scope argument count has reached zero.&n; *&n; ******************************************************************************/
id|u8
DECL|function|acpi_ps_has_completed_scope
id|acpi_ps_has_completed_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
(brace
r_return
(paren
(paren
id|u8
)paren
(paren
(paren
id|parser_state-&gt;aml
op_ge
id|parser_state-&gt;scope-&gt;parse_scope.arg_end
op_logical_or
op_logical_neg
id|parser_state-&gt;scope-&gt;parse_scope.arg_count
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_init_scope&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *              Root                - the Root Node of this new scope&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Allocate and init a new scope object&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ps_init_scope
id|acpi_ps_init_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
r_union
id|acpi_parse_object
op_star
id|root_op
)paren
(brace
r_union
id|acpi_generic_state
op_star
id|scope
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ps_init_scope&quot;
comma
id|root_op
)paren
suffix:semicolon
id|scope
op_assign
id|acpi_ut_create_generic_state
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scope
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|scope-&gt;common.data_type
op_assign
id|ACPI_DESC_TYPE_STATE_RPSCOPE
suffix:semicolon
id|scope-&gt;parse_scope.op
op_assign
id|root_op
suffix:semicolon
id|scope-&gt;parse_scope.arg_count
op_assign
id|ACPI_VAR_ARGS
suffix:semicolon
id|scope-&gt;parse_scope.arg_end
op_assign
id|parser_state-&gt;aml_end
suffix:semicolon
id|scope-&gt;parse_scope.pkg_end
op_assign
id|parser_state-&gt;aml_end
suffix:semicolon
id|parser_state-&gt;scope
op_assign
id|scope
suffix:semicolon
id|parser_state-&gt;start_op
op_assign
id|root_op
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_push_scope&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *              Op                  - Current op to be pushed&n; *              remaining_args      - List of args remaining&n; *              arg_count           - Fixed or variable number of args&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Push current op to begin parsing its argument&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ps_push_scope
id|acpi_ps_push_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
r_union
id|acpi_parse_object
op_star
id|op
comma
id|u32
id|remaining_args
comma
id|u32
id|arg_count
)paren
(brace
r_union
id|acpi_generic_state
op_star
id|scope
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ps_push_scope&quot;
comma
id|op
)paren
suffix:semicolon
id|scope
op_assign
id|acpi_ut_create_generic_state
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scope
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|scope-&gt;common.data_type
op_assign
id|ACPI_DESC_TYPE_STATE_PSCOPE
suffix:semicolon
id|scope-&gt;parse_scope.op
op_assign
id|op
suffix:semicolon
id|scope-&gt;parse_scope.arg_list
op_assign
id|remaining_args
suffix:semicolon
id|scope-&gt;parse_scope.arg_count
op_assign
id|arg_count
suffix:semicolon
id|scope-&gt;parse_scope.pkg_end
op_assign
id|parser_state-&gt;pkg_end
suffix:semicolon
multiline_comment|/* Push onto scope stack */
id|acpi_ut_push_generic_state
(paren
op_amp
id|parser_state-&gt;scope
comma
id|scope
)paren
suffix:semicolon
r_if
c_cond
(paren
id|arg_count
op_eq
id|ACPI_VAR_ARGS
)paren
(brace
multiline_comment|/* multiple arguments */
id|scope-&gt;parse_scope.arg_end
op_assign
id|parser_state-&gt;pkg_end
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* single argument */
id|scope-&gt;parse_scope.arg_end
op_assign
id|ACPI_TO_POINTER
(paren
id|ACPI_MAX_PTR
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_pop_scope&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *              Op                  - Where the popped op is returned&n; *              arg_list            - Where the popped &quot;next argument&quot; is&n; *                                    returned&n; *              arg_count           - Count of objects in arg_list&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Return to parsing a previous op&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ps_pop_scope
id|acpi_ps_pop_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
comma
r_union
id|acpi_parse_object
op_star
op_star
id|op
comma
id|u32
op_star
id|arg_list
comma
id|u32
op_star
id|arg_count
)paren
(brace
r_union
id|acpi_generic_state
op_star
id|scope
op_assign
id|parser_state-&gt;scope
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ps_pop_scope&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Only pop the scope if there is in fact a next scope&n;&t; */
r_if
c_cond
(paren
id|scope-&gt;common.next
)paren
(brace
id|scope
op_assign
id|acpi_ut_pop_generic_state
(paren
op_amp
id|parser_state-&gt;scope
)paren
suffix:semicolon
multiline_comment|/* return to parsing previous op */
op_star
id|op
op_assign
id|scope-&gt;parse_scope.op
suffix:semicolon
op_star
id|arg_list
op_assign
id|scope-&gt;parse_scope.arg_list
suffix:semicolon
op_star
id|arg_count
op_assign
id|scope-&gt;parse_scope.arg_count
suffix:semicolon
id|parser_state-&gt;pkg_end
op_assign
id|scope-&gt;parse_scope.pkg_end
suffix:semicolon
multiline_comment|/* All done with this scope state structure */
id|acpi_ut_delete_generic_state
(paren
id|scope
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* empty parse stack, prepare to fetch next opcode */
op_star
id|op
op_assign
l_int|NULL
suffix:semicolon
op_star
id|arg_list
op_assign
l_int|0
suffix:semicolon
op_star
id|arg_count
op_assign
l_int|0
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_PARSE
comma
l_string|&quot;Popped Op %p Args %X&bslash;n&quot;
comma
op_star
id|op
comma
op_star
id|arg_count
)paren
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ps_cleanup_scope&n; *&n; * PARAMETERS:  parser_state        - Current parser state object&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Destroy available list, remaining stack levels, and return&n; *              root scope&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ps_cleanup_scope
id|acpi_ps_cleanup_scope
(paren
r_struct
id|acpi_parse_state
op_star
id|parser_state
)paren
(brace
r_union
id|acpi_generic_state
op_star
id|scope
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ps_cleanup_scope&quot;
comma
id|parser_state
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parser_state
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* Delete anything on the scope stack */
r_while
c_loop
(paren
id|parser_state-&gt;scope
)paren
(brace
id|scope
op_assign
id|acpi_ut_pop_generic_state
(paren
op_amp
id|parser_state-&gt;scope
)paren
suffix:semicolon
id|acpi_ut_delete_generic_state
(paren
id|scope
)paren
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
eof
