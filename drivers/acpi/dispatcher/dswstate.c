multiline_comment|/******************************************************************************&n; *&n; * Module Name: dswstate - Dispatcher parse tree walk management routines&n; *              $Revision: 45 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_DISPATCHER
id|MODULE_NAME
(paren
l_string|&quot;dswstate&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_result_insert&n; *&n; * PARAMETERS:  Object              - Object to push&n; *              Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Push an object onto this walk&squot;s result stack&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_result_insert
id|acpi_ds_result_insert
(paren
r_void
op_star
id|object
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_GENERIC_STATE
op_star
id|state
suffix:semicolon
id|PROC_NAME
(paren
l_string|&quot;Ds_result_insert&quot;
)paren
suffix:semicolon
id|state
op_assign
id|walk_state-&gt;results
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
(brace
r_return
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|index
op_ge
id|OBJ_NUM_OPERANDS
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|state-&gt;results.obj_desc
(braket
id|index
)braket
op_assign
id|object
suffix:semicolon
id|state-&gt;results.num_results
op_increment
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_result_remove&n; *&n; * PARAMETERS:  Object              - Where to return the popped object&n; *              Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Pop an object off the bottom of this walk&squot;s result stack.  In&n; *              other words, this is a FIFO.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_result_remove
id|acpi_ds_result_remove
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|object
comma
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_GENERIC_STATE
op_star
id|state
suffix:semicolon
id|PROC_NAME
(paren
l_string|&quot;Ds_result_remove&quot;
)paren
suffix:semicolon
id|state
op_assign
id|walk_state-&gt;results
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
(brace
r_return
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
multiline_comment|/* Check for a valid result object */
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;results.obj_desc
(braket
id|index
)braket
)paren
(brace
r_return
(paren
id|AE_AML_NO_RETURN_VALUE
)paren
suffix:semicolon
)brace
multiline_comment|/* Remove the object */
id|state-&gt;results.num_results
op_decrement
suffix:semicolon
op_star
id|object
op_assign
id|state-&gt;results.obj_desc
(braket
id|index
)braket
suffix:semicolon
id|state-&gt;results.obj_desc
(braket
id|index
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_result_pop&n; *&n; * PARAMETERS:  Object              - Where to return the popped object&n; *              Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Pop an object off the bottom of this walk&squot;s result stack.  In&n; *              other words, this is a FIFO.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_result_pop
id|acpi_ds_result_pop
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|u32
id|index
suffix:semicolon
id|ACPI_GENERIC_STATE
op_star
id|state
suffix:semicolon
id|PROC_NAME
(paren
l_string|&quot;Ds_result_pop&quot;
)paren
suffix:semicolon
id|state
op_assign
id|walk_state-&gt;results
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
(brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;results.num_results
)paren
(brace
r_return
(paren
id|AE_AML_NO_RETURN_VALUE
)paren
suffix:semicolon
)brace
multiline_comment|/* Remove top element */
id|state-&gt;results.num_results
op_decrement
suffix:semicolon
r_for
c_loop
(paren
id|index
op_assign
id|OBJ_NUM_OPERANDS
suffix:semicolon
id|index
suffix:semicolon
id|index
op_decrement
)paren
(brace
multiline_comment|/* Check for a valid result object */
r_if
c_cond
(paren
id|state-&gt;results.obj_desc
(braket
id|index
op_minus
l_int|1
)braket
)paren
(brace
op_star
id|object
op_assign
id|state-&gt;results.obj_desc
(braket
id|index
op_minus
l_int|1
)braket
suffix:semicolon
id|state-&gt;results.obj_desc
(braket
id|index
op_minus
l_int|1
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
id|AE_AML_NO_RETURN_VALUE
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_result_pop_from_bottom&n; *&n; * PARAMETERS:  Object              - Where to return the popped object&n; *              Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Pop an object off the bottom of this walk&squot;s result stack.  In&n; *              other words, this is a FIFO.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_result_pop_from_bottom
id|acpi_ds_result_pop_from_bottom
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|u32
id|index
suffix:semicolon
id|ACPI_GENERIC_STATE
op_star
id|state
suffix:semicolon
id|PROC_NAME
(paren
l_string|&quot;Ds_result_pop_from_bottom&quot;
)paren
suffix:semicolon
id|state
op_assign
id|walk_state-&gt;results
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
(brace
r_return
(paren
id|AE_NOT_EXIST
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|state-&gt;results.num_results
)paren
(brace
r_return
(paren
id|AE_AML_NO_RETURN_VALUE
)paren
suffix:semicolon
)brace
multiline_comment|/* Remove Bottom element */
op_star
id|object
op_assign
id|state-&gt;results.obj_desc
(braket
l_int|0
)braket
suffix:semicolon
multiline_comment|/* Push entire stack down one element */
r_for
c_loop
(paren
id|index
op_assign
l_int|0
suffix:semicolon
id|index
OL
id|state-&gt;results.num_results
suffix:semicolon
id|index
op_increment
)paren
(brace
id|state-&gt;results.obj_desc
(braket
id|index
)braket
op_assign
id|state-&gt;results.obj_desc
(braket
id|index
op_plus
l_int|1
)braket
suffix:semicolon
)brace
id|state-&gt;results.num_results
op_decrement
suffix:semicolon
multiline_comment|/* Check for a valid result object */
r_if
c_cond
(paren
op_logical_neg
op_star
id|object
)paren
(brace
r_return
(paren
id|AE_AML_NO_RETURN_VALUE
)paren
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_result_push&n; *&n; * PARAMETERS:  Object              - Where to return the popped object&n; *              Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Push an object onto the current result stack&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_result_push
id|acpi_ds_result_push
(paren
id|ACPI_OPERAND_OBJECT
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_GENERIC_STATE
op_star
id|state
suffix:semicolon
id|PROC_NAME
(paren
l_string|&quot;Ds_result_push&quot;
)paren
suffix:semicolon
id|state
op_assign
id|walk_state-&gt;results
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
(brace
r_return
(paren
id|AE_AML_INTERNAL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|state-&gt;results.num_results
op_eq
id|OBJ_NUM_OPERANDS
)paren
(brace
r_return
(paren
id|AE_STACK_OVERFLOW
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|state-&gt;results.obj_desc
(braket
id|state-&gt;results.num_results
)braket
op_assign
id|object
suffix:semicolon
id|state-&gt;results.num_results
op_increment
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_result_stack_push&n; *&n; * PARAMETERS:  Object              - Object to push&n; *              Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION:&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_result_stack_push
id|acpi_ds_result_stack_push
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_GENERIC_STATE
op_star
id|state
suffix:semicolon
id|state
op_assign
id|acpi_ut_create_generic_state
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|state
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|acpi_ut_push_generic_state
(paren
op_amp
id|walk_state-&gt;results
comma
id|state
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_result_stack_pop&n; *&n; * PARAMETERS:  Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION:&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_result_stack_pop
id|acpi_ds_result_stack_pop
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_GENERIC_STATE
op_star
id|state
suffix:semicolon
multiline_comment|/* Check for stack underflow */
r_if
c_cond
(paren
id|walk_state-&gt;results
op_eq
l_int|NULL
)paren
(brace
r_return
(paren
id|AE_AML_NO_OPERAND
)paren
suffix:semicolon
)brace
id|state
op_assign
id|acpi_ut_pop_generic_state
(paren
op_amp
id|walk_state-&gt;results
)paren
suffix:semicolon
id|acpi_ut_delete_generic_state
(paren
id|state
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_obj_stack_delete_all&n; *&n; * PARAMETERS:  Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Clear the object stack by deleting all objects that are on it.&n; *              Should be used with great care, if at all!&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_obj_stack_delete_all
id|acpi_ds_obj_stack_delete_all
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|u32
id|i
suffix:semicolon
multiline_comment|/* The stack size is configurable, but fixed */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|OBJ_NUM_OPERANDS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|walk_state-&gt;operands
(braket
id|i
)braket
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|walk_state-&gt;operands
(braket
id|i
)braket
)paren
suffix:semicolon
id|walk_state-&gt;operands
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_obj_stack_push&n; *&n; * PARAMETERS:  Object              - Object to push&n; *              Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Push an object onto this walk&squot;s object/operand stack&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_obj_stack_push
id|acpi_ds_obj_stack_push
(paren
r_void
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
multiline_comment|/* Check for stack overflow */
r_if
c_cond
(paren
id|walk_state-&gt;num_operands
op_ge
id|OBJ_NUM_OPERANDS
)paren
(brace
r_return
(paren
id|AE_STACK_OVERFLOW
)paren
suffix:semicolon
)brace
multiline_comment|/* Put the object onto the stack */
id|walk_state-&gt;operands
(braket
id|walk_state-&gt;num_operands
)braket
op_assign
id|object
suffix:semicolon
id|walk_state-&gt;num_operands
op_increment
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_obj_stack_pop_object&n; *&n; * PARAMETERS:  Pop_count           - Number of objects/entries to pop&n; *              Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Pop this walk&squot;s object stack.  Objects on the stack are NOT&n; *              deleted by this routine.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_obj_stack_pop_object
id|acpi_ds_obj_stack_pop_object
(paren
id|ACPI_OPERAND_OBJECT
op_star
op_star
id|object
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
multiline_comment|/* Check for stack underflow */
r_if
c_cond
(paren
id|walk_state-&gt;num_operands
op_eq
l_int|0
)paren
(brace
op_star
id|object
op_assign
l_int|NULL
suffix:semicolon
r_return
(paren
id|AE_AML_NO_OPERAND
)paren
suffix:semicolon
)brace
multiline_comment|/* Pop the stack */
id|walk_state-&gt;num_operands
op_decrement
suffix:semicolon
multiline_comment|/* Check for a valid operand */
r_if
c_cond
(paren
op_logical_neg
id|walk_state-&gt;operands
(braket
id|walk_state-&gt;num_operands
)braket
)paren
(brace
op_star
id|object
op_assign
l_int|NULL
suffix:semicolon
r_return
(paren
id|AE_AML_NO_OPERAND
)paren
suffix:semicolon
)brace
multiline_comment|/* Get operand and set stack entry to null */
op_star
id|object
op_assign
id|walk_state-&gt;operands
(braket
id|walk_state-&gt;num_operands
)braket
suffix:semicolon
id|walk_state-&gt;operands
(braket
id|walk_state-&gt;num_operands
)braket
op_assign
l_int|NULL
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_obj_stack_pop&n; *&n; * PARAMETERS:  Pop_count           - Number of objects/entries to pop&n; *              Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Pop this walk&squot;s object stack.  Objects on the stack are NOT&n; *              deleted by this routine.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_obj_stack_pop
id|acpi_ds_obj_stack_pop
(paren
id|u32
id|pop_count
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|u32
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pop_count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Check for stack underflow */
r_if
c_cond
(paren
id|walk_state-&gt;num_operands
op_eq
l_int|0
)paren
(brace
r_return
(paren
id|AE_STACK_UNDERFLOW
)paren
suffix:semicolon
)brace
multiline_comment|/* Just set the stack entry to null */
id|walk_state-&gt;num_operands
op_decrement
suffix:semicolon
id|walk_state-&gt;operands
(braket
id|walk_state-&gt;num_operands
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_obj_stack_pop_and_delete&n; *&n; * PARAMETERS:  Pop_count           - Number of objects/entries to pop&n; *              Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Pop this walk&squot;s object stack and delete each object that is&n; *              popped off.&n; *&n; ******************************************************************************/
id|ACPI_STATUS
DECL|function|acpi_ds_obj_stack_pop_and_delete
id|acpi_ds_obj_stack_pop_and_delete
(paren
id|u32
id|pop_count
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|u32
id|i
suffix:semicolon
id|ACPI_OPERAND_OBJECT
op_star
id|obj_desc
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|pop_count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/* Check for stack underflow */
r_if
c_cond
(paren
id|walk_state-&gt;num_operands
op_eq
l_int|0
)paren
(brace
r_return
(paren
id|AE_STACK_UNDERFLOW
)paren
suffix:semicolon
)brace
multiline_comment|/* Pop the stack and delete an object if present in this stack entry */
id|walk_state-&gt;num_operands
op_decrement
suffix:semicolon
id|obj_desc
op_assign
id|walk_state-&gt;operands
(braket
id|walk_state-&gt;num_operands
)braket
suffix:semicolon
r_if
c_cond
(paren
id|obj_desc
)paren
(brace
id|acpi_ut_remove_reference
(paren
id|walk_state-&gt;operands
(braket
id|walk_state-&gt;num_operands
)braket
)paren
suffix:semicolon
id|walk_state-&gt;operands
(braket
id|walk_state-&gt;num_operands
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_obj_stack_get_value&n; *&n; * PARAMETERS:  Index               - Stack index whose value is desired.  Based&n; *                                    on the top of the stack (index=0 == top)&n; *              Walk_state          - Current Walk state&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Retrieve an object from this walk&squot;s object stack.  Index must&n; *              be within the range of the current stack pointer.&n; *&n; ******************************************************************************/
r_void
op_star
DECL|function|acpi_ds_obj_stack_get_value
id|acpi_ds_obj_stack_get_value
(paren
id|u32
id|index
comma
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
multiline_comment|/* Can&squot;t do it if the stack is empty */
r_if
c_cond
(paren
id|walk_state-&gt;num_operands
op_eq
l_int|0
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* or if the index is past the top of the stack */
r_if
c_cond
(paren
id|index
OG
(paren
id|walk_state-&gt;num_operands
op_minus
(paren
id|u32
)paren
l_int|1
)paren
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
(paren
id|walk_state-&gt;operands
(braket
(paren
id|NATIVE_UINT
)paren
(paren
id|walk_state-&gt;num_operands
op_minus
l_int|1
)paren
op_minus
id|index
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_get_current_walk_state&n; *&n; * PARAMETERS:  Walk_list       - Get current active state for this walk list&n; *&n; * RETURN:      Pointer to the current walk state&n; *&n; * DESCRIPTION: Get the walk state that is at the head of the list (the &quot;current&quot;&n; *              walk state.&n; *&n; ******************************************************************************/
id|ACPI_WALK_STATE
op_star
DECL|function|acpi_ds_get_current_walk_state
id|acpi_ds_get_current_walk_state
(paren
id|ACPI_WALK_LIST
op_star
id|walk_list
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|walk_list
)paren
(brace
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
r_return
(paren
id|walk_list-&gt;walk_state
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_push_walk_state&n; *&n; * PARAMETERS:  Walk_state      - State to push&n; *              Walk_list       - The list that owns the walk stack&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Place the Walk_state at the head of the state list.&n; *&n; ******************************************************************************/
r_static
r_void
DECL|function|acpi_ds_push_walk_state
id|acpi_ds_push_walk_state
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
comma
id|ACPI_WALK_LIST
op_star
id|walk_list
)paren
(brace
id|walk_state-&gt;next
op_assign
id|walk_list-&gt;walk_state
suffix:semicolon
id|walk_list-&gt;walk_state
op_assign
id|walk_state
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_pop_walk_state&n; *&n; * PARAMETERS:  Walk_list       - The list that owns the walk stack&n; *&n; * RETURN:      A Walk_state object popped from the stack&n; *&n; * DESCRIPTION: Remove and return the walkstate object that is at the head of&n; *              the walk stack for the given walk list.  NULL indicates that&n; *              the list is empty.&n; *&n; ******************************************************************************/
id|ACPI_WALK_STATE
op_star
DECL|function|acpi_ds_pop_walk_state
id|acpi_ds_pop_walk_state
(paren
id|ACPI_WALK_LIST
op_star
id|walk_list
)paren
(brace
id|ACPI_WALK_STATE
op_star
id|walk_state
suffix:semicolon
id|walk_state
op_assign
id|walk_list-&gt;walk_state
suffix:semicolon
r_if
c_cond
(paren
id|walk_state
)paren
(brace
multiline_comment|/* Next walk state becomes the current walk state */
id|walk_list-&gt;walk_state
op_assign
id|walk_state-&gt;next
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Don&squot;t clear the NEXT field, this serves as an indicator&n;&t;&t; * that there is a parent WALK STATE&n;&t;&t; *     Walk_state-&gt;Next = NULL;&n;&t;&t; */
)brace
r_return
(paren
id|walk_state
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_create_walk_state&n; *&n; * PARAMETERS:  Origin          - Starting point for this walk&n; *              Walk_list       - Owning walk list&n; *&n; * RETURN:      Pointer to the new walk state.&n; *&n; * DESCRIPTION: Allocate and initialize a new walk state.  The current walk state&n; *              is set to this new state.&n; *&n; ******************************************************************************/
id|ACPI_WALK_STATE
op_star
DECL|function|acpi_ds_create_walk_state
id|acpi_ds_create_walk_state
(paren
id|ACPI_OWNER_ID
id|owner_id
comma
id|ACPI_PARSE_OBJECT
op_star
id|origin
comma
id|ACPI_OPERAND_OBJECT
op_star
id|mth_desc
comma
id|ACPI_WALK_LIST
op_star
id|walk_list
)paren
(brace
id|ACPI_WALK_STATE
op_star
id|walk_state
suffix:semicolon
id|ACPI_STATUS
id|status
suffix:semicolon
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_CACHES
)paren
suffix:semicolon
id|acpi_gbl_walk_state_cache_requests
op_increment
suffix:semicolon
multiline_comment|/* Check the cache first */
r_if
c_cond
(paren
id|acpi_gbl_walk_state_cache
)paren
(brace
multiline_comment|/* There is an object available, use it */
id|walk_state
op_assign
id|acpi_gbl_walk_state_cache
suffix:semicolon
id|acpi_gbl_walk_state_cache
op_assign
id|walk_state-&gt;next
suffix:semicolon
id|acpi_gbl_walk_state_cache_hits
op_increment
suffix:semicolon
id|acpi_gbl_walk_state_cache_depth
op_decrement
suffix:semicolon
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_CACHES
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* The cache is empty, create a new object */
multiline_comment|/* Avoid deadlock with Acpi_ut_callocate */
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_CACHES
)paren
suffix:semicolon
id|walk_state
op_assign
id|acpi_ut_callocate
(paren
r_sizeof
(paren
id|ACPI_WALK_STATE
)paren
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
l_int|NULL
)paren
suffix:semicolon
)brace
)brace
id|walk_state-&gt;data_type
op_assign
id|ACPI_DESC_TYPE_WALK
suffix:semicolon
id|walk_state-&gt;owner_id
op_assign
id|owner_id
suffix:semicolon
id|walk_state-&gt;origin
op_assign
id|origin
suffix:semicolon
id|walk_state-&gt;method_desc
op_assign
id|mth_desc
suffix:semicolon
id|walk_state-&gt;walk_list
op_assign
id|walk_list
suffix:semicolon
multiline_comment|/* Init the method args/local */
macro_line|#ifndef _ACPI_ASL_COMPILER
id|acpi_ds_method_data_init
(paren
id|walk_state
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Create an initial result stack entry */
id|status
op_assign
id|acpi_ds_result_stack_push
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
r_return
(paren
l_int|NULL
)paren
suffix:semicolon
)brace
multiline_comment|/* Put the new state at the head of the walk list */
id|acpi_ds_push_walk_state
(paren
id|walk_state
comma
id|walk_list
)paren
suffix:semicolon
r_return
(paren
id|walk_state
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_delete_walk_state&n; *&n; * PARAMETERS:  Walk_state      - State to delete&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Delete a walk state including all internal data structures&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ds_delete_walk_state
id|acpi_ds_delete_walk_state
(paren
id|ACPI_WALK_STATE
op_star
id|walk_state
)paren
(brace
id|ACPI_GENERIC_STATE
op_star
id|state
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|walk_state
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|walk_state-&gt;data_type
op_ne
id|ACPI_DESC_TYPE_WALK
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/* Always must free any linked control states */
r_while
c_loop
(paren
id|walk_state-&gt;control_state
)paren
(brace
id|state
op_assign
id|walk_state-&gt;control_state
suffix:semicolon
id|walk_state-&gt;control_state
op_assign
id|state-&gt;common.next
suffix:semicolon
id|acpi_ut_delete_generic_state
(paren
id|state
)paren
suffix:semicolon
)brace
multiline_comment|/* Always must free any linked parse states */
r_while
c_loop
(paren
id|walk_state-&gt;scope_info
)paren
(brace
id|state
op_assign
id|walk_state-&gt;scope_info
suffix:semicolon
id|walk_state-&gt;scope_info
op_assign
id|state-&gt;common.next
suffix:semicolon
id|acpi_ut_delete_generic_state
(paren
id|state
)paren
suffix:semicolon
)brace
multiline_comment|/* Always must free any stacked result states */
r_while
c_loop
(paren
id|walk_state-&gt;results
)paren
(brace
id|state
op_assign
id|walk_state-&gt;results
suffix:semicolon
id|walk_state-&gt;results
op_assign
id|state-&gt;common.next
suffix:semicolon
id|acpi_ut_delete_generic_state
(paren
id|state
)paren
suffix:semicolon
)brace
multiline_comment|/* If walk cache is full, just free this wallkstate object */
r_if
c_cond
(paren
id|acpi_gbl_walk_state_cache_depth
op_ge
id|MAX_WALK_CACHE_DEPTH
)paren
(brace
id|acpi_ut_free
(paren
id|walk_state
)paren
suffix:semicolon
)brace
multiline_comment|/* Otherwise put this object back into the cache */
r_else
(brace
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_CACHES
)paren
suffix:semicolon
multiline_comment|/* Clear the state */
id|MEMSET
(paren
id|walk_state
comma
l_int|0
comma
r_sizeof
(paren
id|ACPI_WALK_STATE
)paren
)paren
suffix:semicolon
id|walk_state-&gt;data_type
op_assign
id|ACPI_DESC_TYPE_WALK
suffix:semicolon
multiline_comment|/* Put the object at the head of the global cache list */
id|walk_state-&gt;next
op_assign
id|acpi_gbl_walk_state_cache
suffix:semicolon
id|acpi_gbl_walk_state_cache
op_assign
id|walk_state
suffix:semicolon
id|acpi_gbl_walk_state_cache_depth
op_increment
suffix:semicolon
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_CACHES
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    Acpi_ds_delete_walk_state_cache&n; *&n; * PARAMETERS:  None&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Purge the global state object cache.  Used during subsystem&n; *              termination.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ds_delete_walk_state_cache
id|acpi_ds_delete_walk_state_cache
(paren
r_void
)paren
(brace
id|ACPI_WALK_STATE
op_star
id|next
suffix:semicolon
multiline_comment|/* Traverse the global cache list */
r_while
c_loop
(paren
id|acpi_gbl_walk_state_cache
)paren
(brace
multiline_comment|/* Delete one cached state object */
id|next
op_assign
id|acpi_gbl_walk_state_cache-&gt;next
suffix:semicolon
id|acpi_ut_free
(paren
id|acpi_gbl_walk_state_cache
)paren
suffix:semicolon
id|acpi_gbl_walk_state_cache
op_assign
id|next
suffix:semicolon
id|acpi_gbl_walk_state_cache_depth
op_decrement
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
eof
