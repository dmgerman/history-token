multiline_comment|/******************************************************************************&n; *&n; * Module Name: dswscope - Scope stack manipulation&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acdispat.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DISPATCHER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;dswscope&quot;
)paren
DECL|macro|STACK_POP
mdefine_line|#define STACK_POP(head) head
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    acpi_ds_scope_stack_clear&n; *&n; * PARAMETERS:  None&n; *&n; * DESCRIPTION: Pop (and free) everything on the scope stack except the&n; *              root scope object (which remains at the stack top.)&n; *&n; ***************************************************************************/
r_void
DECL|function|acpi_ds_scope_stack_clear
id|acpi_ds_scope_stack_clear
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
r_union
id|acpi_generic_state
op_star
id|scope_info
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ds_scope_stack_clear&quot;
)paren
suffix:semicolon
r_while
c_loop
(paren
id|walk_state-&gt;scope_info
)paren
(brace
multiline_comment|/* Pop a scope off the stack */
id|scope_info
op_assign
id|walk_state-&gt;scope_info
suffix:semicolon
id|walk_state-&gt;scope_info
op_assign
id|scope_info-&gt;scope.next
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Popped object type (%s)&bslash;n&quot;
comma
id|acpi_ut_get_type_name
(paren
id|scope_info-&gt;common.value
)paren
)paren
)paren
suffix:semicolon
id|acpi_ut_delete_generic_state
(paren
id|scope_info
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    acpi_ds_scope_stack_push&n; *&n; * PARAMETERS:  *Node,              - Name to be made current&n; *              Type,               - Type of frame being pushed&n; *&n; * DESCRIPTION: Push the current scope on the scope stack, and make the&n; *              passed Node current.&n; *&n; ***************************************************************************/
id|acpi_status
DECL|function|acpi_ds_scope_stack_push
id|acpi_ds_scope_stack_push
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
comma
id|acpi_object_type
id|type
comma
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
r_union
id|acpi_generic_state
op_star
id|scope_info
suffix:semicolon
r_union
id|acpi_generic_state
op_star
id|old_scope_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ds_scope_stack_push&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
multiline_comment|/* Invalid scope   */
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;ds_scope_stack_push: null scope passed&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Make sure object type is valid */
r_if
c_cond
(paren
op_logical_neg
id|acpi_ut_valid_object_type
(paren
id|type
)paren
)paren
(brace
id|ACPI_REPORT_WARNING
(paren
(paren
l_string|&quot;ds_scope_stack_push: Invalid object type: 0x%X&bslash;n&quot;
comma
id|type
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Allocate a new scope object */
id|scope_info
op_assign
id|acpi_ut_create_generic_state
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scope_info
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Init new scope object */
id|scope_info-&gt;common.data_type
op_assign
id|ACPI_DESC_TYPE_STATE_WSCOPE
suffix:semicolon
id|scope_info-&gt;scope.node
op_assign
id|node
suffix:semicolon
id|scope_info-&gt;common.value
op_assign
(paren
id|u16
)paren
id|type
suffix:semicolon
id|walk_state-&gt;scope_depth
op_increment
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[%.2d] Pushed scope &quot;
comma
(paren
id|u32
)paren
id|walk_state-&gt;scope_depth
)paren
)paren
suffix:semicolon
id|old_scope_info
op_assign
id|walk_state-&gt;scope_info
suffix:semicolon
r_if
c_cond
(paren
id|old_scope_info
)paren
(brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[%4.4s] (%s)&quot;
comma
id|acpi_ut_get_node_name
(paren
id|old_scope_info-&gt;scope.node
)paren
comma
id|acpi_ut_get_type_name
(paren
id|old_scope_info-&gt;common.value
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[&bslash;&bslash;___] (%s)&quot;
comma
l_string|&quot;ROOT&quot;
)paren
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;, New scope -&gt; [%4.4s] (%s)&bslash;n&quot;
comma
id|acpi_ut_get_node_name
(paren
id|scope_info-&gt;scope.node
)paren
comma
id|acpi_ut_get_type_name
(paren
id|scope_info-&gt;common.value
)paren
)paren
)paren
suffix:semicolon
multiline_comment|/* Push new scope object onto stack */
id|acpi_ut_push_generic_state
(paren
op_amp
id|walk_state-&gt;scope_info
comma
id|scope_info
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    acpi_ds_scope_stack_pop&n; *&n; * PARAMETERS:  Type                - The type of frame to be found&n; *&n; * DESCRIPTION: Pop the scope stack until a frame of the requested type&n; *              is found.&n; *&n; * RETURN:      Count of frames popped.  If no frame of the requested type&n; *              was found, the count is returned as a negative number and&n; *              the scope stack is emptied (which sets the current scope&n; *              to the root).  If the scope stack was empty at entry, the&n; *              function is a no-op and returns 0.&n; *&n; ***************************************************************************/
id|acpi_status
DECL|function|acpi_ds_scope_stack_pop
id|acpi_ds_scope_stack_pop
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
r_union
id|acpi_generic_state
op_star
id|scope_info
suffix:semicolon
r_union
id|acpi_generic_state
op_star
id|new_scope_info
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ds_scope_stack_pop&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Pop scope info object off the stack.&n;&t; */
id|scope_info
op_assign
id|acpi_ut_pop_generic_state
(paren
op_amp
id|walk_state-&gt;scope_info
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|scope_info
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_STACK_UNDERFLOW
)paren
suffix:semicolon
)brace
id|walk_state-&gt;scope_depth
op_decrement
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[%.2d] Popped scope [%4.4s] (%s), New scope -&gt; &quot;
comma
(paren
id|u32
)paren
id|walk_state-&gt;scope_depth
comma
id|acpi_ut_get_node_name
(paren
id|scope_info-&gt;scope.node
)paren
comma
id|acpi_ut_get_type_name
(paren
id|scope_info-&gt;common.value
)paren
)paren
)paren
suffix:semicolon
id|new_scope_info
op_assign
id|walk_state-&gt;scope_info
suffix:semicolon
r_if
c_cond
(paren
id|new_scope_info
)paren
(brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[%4.4s] (%s)&bslash;n&quot;
comma
id|acpi_ut_get_node_name
(paren
id|new_scope_info-&gt;scope.node
)paren
comma
id|acpi_ut_get_type_name
(paren
id|new_scope_info-&gt;common.value
)paren
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;[&bslash;&bslash;___] (ROOT)&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|acpi_ut_delete_generic_state
(paren
id|scope_info
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
eof
