multiline_comment|/******************************************************************************&n; *&n; * Module Name: dsmethod - Parser/Interpreter interface - control method parsing&n; *&n; *****************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2005, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acparser.h&gt;
macro_line|#include &lt;acpi/amlcode.h&gt;
macro_line|#include &lt;acpi/acdispat.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DISPATCHER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;dsmethod&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ds_parse_method&n; *&n; * PARAMETERS:  obj_handle      - Method node&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Call the parser and parse the AML that is associated with the&n; *              method.&n; *&n; * MUTEX:       Assumes parser is locked&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_parse_method
id|acpi_ds_parse_method
(paren
id|acpi_handle
id|obj_handle
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
r_union
id|acpi_parse_object
op_star
id|op
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_owner_id
id|owner_id
suffix:semicolon
r_struct
id|acpi_walk_state
op_star
id|walk_state
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ds_parse_method&quot;
comma
id|obj_handle
)paren
suffix:semicolon
multiline_comment|/* Parameter Validation */
r_if
c_cond
(paren
op_logical_neg
id|obj_handle
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NULL_ENTRY
)paren
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_PARSE
comma
l_string|&quot;**** Parsing [%4.4s] **** named_obj=%p&bslash;n&quot;
comma
id|acpi_ut_get_node_name
(paren
id|obj_handle
)paren
comma
id|obj_handle
)paren
)paren
suffix:semicolon
multiline_comment|/* Extract the method object from the method Node */
id|node
op_assign
(paren
r_struct
id|acpi_namespace_node
op_star
)paren
id|obj_handle
suffix:semicolon
id|obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NULL_OBJECT
)paren
suffix:semicolon
)brace
multiline_comment|/* Create a mutex for the method if there is a concurrency limit */
r_if
c_cond
(paren
(paren
id|obj_desc-&gt;method.concurrency
op_ne
id|ACPI_INFINITE_CONCURRENCY
)paren
op_logical_and
(paren
op_logical_neg
id|obj_desc-&gt;method.semaphore
)paren
)paren
(brace
id|status
op_assign
id|acpi_os_create_semaphore
(paren
id|obj_desc-&gt;method.concurrency
comma
id|obj_desc-&gt;method.concurrency
comma
op_amp
id|obj_desc-&gt;method.semaphore
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
)brace
multiline_comment|/*&n;&t; * Allocate a new parser op to be the root of the parsed&n;&t; * method tree&n;&t; */
id|op
op_assign
id|acpi_ps_alloc_op
(paren
id|AML_METHOD_OP
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Init new op with the method name and pointer back to the Node */
id|acpi_ps_set_name
(paren
id|op
comma
id|node-&gt;name.integer
)paren
suffix:semicolon
id|op-&gt;common.node
op_assign
id|node
suffix:semicolon
multiline_comment|/*&n;&t; * Get a new owner_id for objects created by this method. Namespace&n;&t; * objects (such as Operation Regions) can be created during the&n;&t; * first pass parse.&n;&t; */
id|owner_id
op_assign
id|acpi_ut_allocate_owner_id
(paren
id|ACPI_OWNER_TYPE_METHOD
)paren
suffix:semicolon
id|obj_desc-&gt;method.owning_id
op_assign
id|owner_id
suffix:semicolon
multiline_comment|/* Create and initialize a new walk state */
id|walk_state
op_assign
id|acpi_ds_create_walk_state
(paren
id|owner_id
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|walk_state
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
id|acpi_ds_init_aml_walk
(paren
id|walk_state
comma
id|op
comma
id|node
comma
id|obj_desc-&gt;method.aml_start
comma
id|obj_desc-&gt;method.aml_length
comma
l_int|NULL
comma
l_int|1
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
id|acpi_ds_delete_walk_state
(paren
id|walk_state
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Parse the method, first pass&n;&t; *&n;&t; * The first pass load is where newly declared named objects are&n;&t; * added into the namespace.  Actual evaluation of&n;&t; * the named objects (what would be called a &quot;second&n;&t; * pass&quot;) happens during the actual execution of the&n;&t; * method so that operands to the named objects can&n;&t; * take on dynamic run-time values.&n;&t; */
id|status
op_assign
id|acpi_ps_parse_aml
(paren
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_PARSE
comma
l_string|&quot;**** [%4.4s] Parsed **** named_obj=%p Op=%p&bslash;n&quot;
comma
id|acpi_ut_get_node_name
(paren
id|obj_handle
)paren
comma
id|obj_handle
comma
id|op
)paren
)paren
suffix:semicolon
id|acpi_ps_delete_parse_tree
(paren
id|op
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ds_begin_method_execution&n; *&n; * PARAMETERS:  method_node         - Node of the method&n; *              obj_desc            - The method object&n; *              calling_method_node - Caller of this method (if non-null)&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Prepare a method for execution.  Parses the method if necessary,&n; *              increments the thread count, and waits at the method semaphore&n; *              for clearance to execute.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_begin_method_execution
id|acpi_ds_begin_method_execution
(paren
r_struct
id|acpi_namespace_node
op_star
id|method_node
comma
r_union
id|acpi_operand_object
op_star
id|obj_desc
comma
r_struct
id|acpi_namespace_node
op_star
id|calling_method_node
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ds_begin_method_execution&quot;
comma
id|method_node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|method_node
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NULL_ENTRY
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If there is a concurrency limit on this method, we need to&n;&t; * obtain a unit from the method semaphore.&n;&t; */
r_if
c_cond
(paren
id|obj_desc-&gt;method.semaphore
)paren
(brace
multiline_comment|/*&n;&t;&t; * Allow recursive method calls, up to the reentrancy/concurrency&n;&t;&t; * limit imposed by the SERIALIZED rule and the sync_level method&n;&t;&t; * parameter.&n;&t;&t; *&n;&t;&t; * The point of this code is to avoid permanently blocking a&n;&t;&t; * thread that is making recursive method calls.&n;&t;&t; */
r_if
c_cond
(paren
id|method_node
op_eq
id|calling_method_node
)paren
(brace
r_if
c_cond
(paren
id|obj_desc-&gt;method.thread_count
op_ge
id|obj_desc-&gt;method.concurrency
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_AML_METHOD_LIMIT
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Get a unit from the method semaphore. This releases the&n;&t;&t; * interpreter if we block&n;&t;&t; */
id|status
op_assign
id|acpi_ex_system_wait_semaphore
(paren
id|obj_desc-&gt;method.semaphore
comma
id|ACPI_WAIT_FOREVER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Increment the method parse tree thread count since it has been&n;&t; * reentered one more time (even if it is the same thread)&n;&t; */
id|obj_desc-&gt;method.thread_count
op_increment
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ds_call_control_method&n; *&n; * PARAMETERS:  Thread              - Info for this thread&n; *              this_walk_state     - Current walk state&n; *              Op                  - Current Op to be walked&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Transfer execution to a called control method&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_call_control_method
id|acpi_ds_call_control_method
(paren
r_struct
id|acpi_thread_state
op_star
id|thread
comma
r_struct
id|acpi_walk_state
op_star
id|this_walk_state
comma
r_union
id|acpi_parse_object
op_star
id|op
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|method_node
suffix:semicolon
r_struct
id|acpi_walk_state
op_star
id|next_walk_state
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
r_struct
id|acpi_parameter_info
id|info
suffix:semicolon
id|u32
id|i
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ds_call_control_method&quot;
comma
id|this_walk_state
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Execute method %p, currentstate=%p&bslash;n&quot;
comma
id|this_walk_state-&gt;prev_op
comma
id|this_walk_state
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Get the namespace entry for the control method we are about to call&n;&t; */
id|method_node
op_assign
id|this_walk_state-&gt;method_call_node
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|method_node
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NULL_ENTRY
)paren
suffix:semicolon
)brace
id|obj_desc
op_assign
id|acpi_ns_get_attached_object
(paren
id|method_node
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NULL_OBJECT
)paren
suffix:semicolon
)brace
id|obj_desc-&gt;method.owning_id
op_assign
id|acpi_ut_allocate_owner_id
(paren
id|ACPI_OWNER_TYPE_METHOD
)paren
suffix:semicolon
multiline_comment|/* Init for new method, wait on concurrency semaphore */
id|status
op_assign
id|acpi_ds_begin_method_execution
(paren
id|method_node
comma
id|obj_desc
comma
id|this_walk_state-&gt;method_node
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
op_logical_neg
(paren
id|obj_desc-&gt;method.method_flags
op_amp
id|AML_METHOD_INTERNAL_ONLY
)paren
)paren
(brace
multiline_comment|/* 1) Parse: Create a new walk state for the preempting walk */
id|next_walk_state
op_assign
id|acpi_ds_create_walk_state
(paren
id|obj_desc-&gt;method.owning_id
comma
id|op
comma
id|obj_desc
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next_walk_state
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
multiline_comment|/* Create and init a Root Node */
id|op
op_assign
id|acpi_ps_create_scope_op
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|op
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ds_init_aml_walk
(paren
id|next_walk_state
comma
id|op
comma
id|method_node
comma
id|obj_desc-&gt;method.aml_start
comma
id|obj_desc-&gt;method.aml_length
comma
l_int|NULL
comma
l_int|1
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
id|acpi_ds_delete_walk_state
(paren
id|next_walk_state
)paren
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Begin AML parse */
id|status
op_assign
id|acpi_ps_parse_aml
(paren
id|next_walk_state
)paren
suffix:semicolon
id|acpi_ps_delete_parse_tree
(paren
id|op
)paren
suffix:semicolon
)brace
multiline_comment|/* 2) Execute: Create a new state for the preempting walk */
id|next_walk_state
op_assign
id|acpi_ds_create_walk_state
(paren
id|obj_desc-&gt;method.owning_id
comma
l_int|NULL
comma
id|obj_desc
comma
id|thread
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|next_walk_state
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The resolved arguments were put on the previous walk state&squot;s operand&n;&t; * stack.  Operands on the previous walk state stack always&n;&t; * start at index 0.&n;&t; * Null terminate the list of arguments&n;&t; */
id|this_walk_state-&gt;operands
(braket
id|this_walk_state-&gt;num_operands
)braket
op_assign
l_int|NULL
suffix:semicolon
id|info.parameters
op_assign
op_amp
id|this_walk_state-&gt;operands
(braket
l_int|0
)braket
suffix:semicolon
id|info.parameter_type
op_assign
id|ACPI_PARAM_ARGS
suffix:semicolon
id|status
op_assign
id|acpi_ds_init_aml_walk
(paren
id|next_walk_state
comma
l_int|NULL
comma
id|method_node
comma
id|obj_desc-&gt;method.aml_start
comma
id|obj_desc-&gt;method.aml_length
comma
op_amp
id|info
comma
l_int|3
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
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Delete the operands on the previous walkstate operand stack&n;&t; * (they were copied to new objects)&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|obj_desc-&gt;method.param_count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|this_walk_state-&gt;operands
(braket
id|i
)braket
)paren
suffix:semicolon
id|this_walk_state-&gt;operands
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Clear the operand stack */
id|this_walk_state-&gt;num_operands
op_assign
l_int|0
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;Starting nested execution, newstate=%p&bslash;n&quot;
comma
id|next_walk_state
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|obj_desc-&gt;method.method_flags
op_amp
id|AML_METHOD_INTERNAL_ONLY
)paren
(brace
id|status
op_assign
id|obj_desc-&gt;method.implementation
(paren
id|next_walk_state
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
multiline_comment|/* On error, we must delete the new walk state */
id|cleanup
suffix:colon
r_if
c_cond
(paren
id|next_walk_state
op_logical_and
(paren
id|next_walk_state-&gt;method_desc
)paren
)paren
(brace
multiline_comment|/* Decrement the thread count on the method parse tree */
id|next_walk_state-&gt;method_desc-&gt;method.thread_count
op_decrement
suffix:semicolon
)brace
(paren
r_void
)paren
id|acpi_ds_terminate_control_method
(paren
id|next_walk_state
)paren
suffix:semicolon
id|acpi_ds_delete_walk_state
(paren
id|next_walk_state
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ds_restart_control_method&n; *&n; * PARAMETERS:  walk_state          - State for preempted method (caller)&n; *              return_desc         - Return value from the called method&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Restart a method that was preempted by another (nested) method&n; *              invocation.  Handle the return value (if any) from the callee.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_restart_control_method
id|acpi_ds_restart_control_method
(paren
r_struct
id|acpi_walk_state
op_star
id|walk_state
comma
r_union
id|acpi_operand_object
op_star
id|return_desc
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ds_restart_control_method&quot;
comma
id|walk_state
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;****Restart [%4.4s] Op %p return_value_from_callee %p&bslash;n&quot;
comma
(paren
r_char
op_star
)paren
op_amp
id|walk_state-&gt;method_node-&gt;name
comma
id|walk_state-&gt;method_call_op
comma
id|return_desc
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;    return_from_this_method_used?=%X res_stack %p Walk %p&bslash;n&quot;
comma
id|walk_state-&gt;return_used
comma
id|walk_state-&gt;results
comma
id|walk_state
)paren
)paren
suffix:semicolon
multiline_comment|/* Did the called method return a value? */
r_if
c_cond
(paren
id|return_desc
)paren
(brace
multiline_comment|/* Are we actually going to use the return value? */
r_if
c_cond
(paren
id|walk_state-&gt;return_used
)paren
(brace
multiline_comment|/* Save the return value from the previous method */
id|status
op_assign
id|acpi_ds_result_push
(paren
id|return_desc
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
id|acpi_ut_remove_reference
(paren
id|return_desc
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t;&t; * Save as THIS method&squot;s return value in case it is returned&n;&t;&t;&t; * immediately to yet another method&n;&t;&t;&t; */
id|walk_state-&gt;return_desc
op_assign
id|return_desc
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * The following code is the&n;&t;&t; * optional support for a so-called &quot;implicit return&quot;. Some AML code&n;&t;&t; * assumes that the last value of the method is &quot;implicitly&quot; returned&n;&t;&t; * to the caller. Just save the last result as the return value.&n;&t;&t; * NOTE: this is optional because the ASL language does not actually&n;&t;&t; * support this behavior.&n;&t;&t; */
r_else
r_if
c_cond
(paren
op_logical_neg
id|acpi_ds_do_implicit_return
(paren
id|return_desc
comma
id|walk_state
comma
id|FALSE
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Delete the return value if it will not be used by the&n;&t;&t;&t; * calling method&n;&t;&t;&t; */
id|acpi_ut_remove_reference
(paren
id|return_desc
)paren
suffix:semicolon
)brace
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ds_terminate_control_method&n; *&n; * PARAMETERS:  walk_state          - State of the method&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Terminate a control method.  Delete everything that the method&n; *              created, delete all locals and arguments, and delete the parse&n; *              tree if requested.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ds_terminate_control_method
id|acpi_ds_terminate_control_method
(paren
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
r_struct
id|acpi_namespace_node
op_star
id|method_node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ds_terminate_control_method&quot;
comma
id|walk_state
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|walk_state
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* The current method object was saved in the walk state */
id|obj_desc
op_assign
id|walk_state-&gt;method_desc
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Delete all arguments and locals */
id|acpi_ds_method_data_delete_all
(paren
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Lock the parser while we terminate this method.&n;&t; * If this is the last thread executing the method,&n;&t; * we have additional cleanup to perform&n;&t; */
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_PARSER
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
multiline_comment|/* Signal completion of the execution of this method if necessary */
r_if
c_cond
(paren
id|walk_state-&gt;method_desc-&gt;method.semaphore
)paren
(brace
id|status
op_assign
id|acpi_os_signal_semaphore
(paren
id|walk_state-&gt;method_desc-&gt;method.semaphore
comma
l_int|1
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
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not signal method semaphore&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|status
op_assign
id|AE_OK
suffix:semicolon
multiline_comment|/* Ignore error and continue cleanup */
)brace
)brace
r_if
c_cond
(paren
id|walk_state-&gt;method_desc-&gt;method.thread_count
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_DISPATCH
comma
l_string|&quot;*** Not deleting method namespace, there are still %d threads&bslash;n&quot;
comma
id|walk_state-&gt;method_desc-&gt;method.thread_count
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|walk_state-&gt;method_desc-&gt;method.thread_count
)paren
(brace
multiline_comment|/*&n;&t;&t; * Support to dynamically change a method from not_serialized to&n;&t;&t; * Serialized if it appears that the method is written foolishly and&n;&t;&t; * does not support multiple thread execution.  The best example of this&n;&t;&t; * is if such a method creates namespace objects and blocks.  A second&n;&t;&t; * thread will fail with an AE_ALREADY_EXISTS exception&n;&t;&t; *&n;&t;&t; * This code is here because we must wait until the last thread exits&n;&t;&t; * before creating the synchronization semaphore.&n;&t;&t; */
r_if
c_cond
(paren
(paren
id|walk_state-&gt;method_desc-&gt;method.concurrency
op_eq
l_int|1
)paren
op_logical_and
(paren
op_logical_neg
id|walk_state-&gt;method_desc-&gt;method.semaphore
)paren
)paren
(brace
id|status
op_assign
id|acpi_os_create_semaphore
(paren
l_int|1
comma
l_int|1
comma
op_amp
id|walk_state-&gt;method_desc-&gt;method.semaphore
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * There are no more threads executing this method.  Perform&n;&t;&t; * additional cleanup.&n;&t;&t; *&n;&t;&t; * The method Node is stored in the walk state&n;&t;&t; */
id|method_node
op_assign
id|walk_state-&gt;method_node
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Delete any namespace entries created immediately underneath&n;&t;&t; * the method&n;&t;&t; */
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_NAMESPACE
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
id|method_node-&gt;child
)paren
(brace
id|acpi_ns_delete_namespace_subtree
(paren
id|method_node
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Delete any namespace entries created anywhere else within&n;&t;&t; * the namespace&n;&t;&t; */
id|acpi_ns_delete_namespace_by_owner
(paren
id|walk_state-&gt;method_desc-&gt;method.owning_id
)paren
suffix:semicolon
id|status
op_assign
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
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
)brace
id|status
op_assign
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_PARSER
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
eof
