multiline_comment|/******************************************************************************&n; *&n; * Module Name: pswalk - Parser routines to walk parsed op tree(s)&n; *              $Revision: 58 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;amlcode.h&quot;
macro_line|#include &quot;acparser.h&quot;
macro_line|#include &quot;acdispat.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_PARSER
id|MODULE_NAME
(paren
l_string|&quot;pswalk&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_get_next_walk_op&n; *&n; * PARAMETERS:  Walk_state          - Current state of the walk&n; *              Op                  - Current Op to be walked&n; *              Ascending_callback  - Procedure called when Op is complete&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Get the next Op in a walk of the parse tree.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ps_get_next_walk_op
id|acpi_ps_get_next_walk_op
(paren
id|acpi_walk_state
op_star
id|walk_state
comma
id|acpi_parse_object
op_star
id|op
comma
id|acpi_parse_upwards
id|ascending_callback
)paren
(brace
id|acpi_parse_object
op_star
id|next
suffix:semicolon
id|acpi_parse_object
op_star
id|parent
suffix:semicolon
id|acpi_parse_object
op_star
id|grand_parent
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ps_get_next_walk_op&quot;
comma
id|op
)paren
suffix:semicolon
multiline_comment|/* Check for a argument only if we are descending in the tree */
r_if
c_cond
(paren
id|walk_state-&gt;next_op_info
op_ne
id|NEXT_OP_UPWARD
)paren
(brace
multiline_comment|/* Look for an argument or child of the current op */
id|next
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
id|next
)paren
(brace
multiline_comment|/* Still going downward in tree (Op is not completed yet) */
id|walk_state-&gt;prev_op
op_assign
id|op
suffix:semicolon
id|walk_state-&gt;next_op
op_assign
id|next
suffix:semicolon
id|walk_state-&gt;next_op_info
op_assign
id|NEXT_OP_DOWNWARD
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * No more children, this Op is complete.  Save Next and Parent&n;&t;&t; * in case the Op object gets deleted by the callback routine&n;&t;&t; */
id|next
op_assign
id|op-&gt;next
suffix:semicolon
id|parent
op_assign
id|op-&gt;parent
suffix:semicolon
id|walk_state-&gt;op
op_assign
id|op
suffix:semicolon
id|walk_state-&gt;op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|op-&gt;opcode
)paren
suffix:semicolon
id|walk_state-&gt;opcode
op_assign
id|op-&gt;opcode
suffix:semicolon
id|status
op_assign
id|ascending_callback
(paren
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we are back to the starting point, the walk is complete.&n;&t;&t; */
r_if
c_cond
(paren
id|op
op_eq
id|walk_state-&gt;origin
)paren
(brace
multiline_comment|/* Reached the point of origin, the walk is complete */
id|walk_state-&gt;prev_op
op_assign
id|op
suffix:semicolon
id|walk_state-&gt;next_op
op_assign
l_int|NULL
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Check for a sibling to the current op.  A sibling means&n;&t;&t; * we are still going &quot;downward&quot; in the tree.&n;&t;&t; */
r_if
c_cond
(paren
id|next
)paren
(brace
multiline_comment|/* There is a sibling, it will be next */
id|walk_state-&gt;prev_op
op_assign
id|op
suffix:semicolon
id|walk_state-&gt;next_op
op_assign
id|next
suffix:semicolon
id|walk_state-&gt;next_op_info
op_assign
id|NEXT_OP_DOWNWARD
suffix:semicolon
multiline_comment|/* Continue downward */
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Drop into the loop below because we are moving upwards in&n;&t;&t; * the tree&n;&t;&t; */
)brace
r_else
(brace
multiline_comment|/*&n;&t;&t; * We are resuming a walk, and we were (are) going upward in the tree.&n;&t;&t; * So, we want to drop into the parent loop below.&n;&t;&t; */
id|parent
op_assign
id|op
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Look for a sibling of the current Op&squot;s parent&n;&t; * Continue moving up the tree until we find a node that has not been&n;&t; * visited, or we get back to where we started.&n;&t; */
r_while
c_loop
(paren
id|parent
)paren
(brace
multiline_comment|/* We are moving up the tree, therefore this parent Op is complete */
id|grand_parent
op_assign
id|parent-&gt;parent
suffix:semicolon
id|next
op_assign
id|parent-&gt;next
suffix:semicolon
id|walk_state-&gt;op
op_assign
id|parent
suffix:semicolon
id|walk_state-&gt;op_info
op_assign
id|acpi_ps_get_opcode_info
(paren
id|parent-&gt;opcode
)paren
suffix:semicolon
id|walk_state-&gt;opcode
op_assign
id|parent-&gt;opcode
suffix:semicolon
id|status
op_assign
id|ascending_callback
(paren
id|walk_state
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * If we are back to the starting point, the walk is complete.&n;&t;&t; */
r_if
c_cond
(paren
id|parent
op_eq
id|walk_state-&gt;origin
)paren
(brace
multiline_comment|/* Reached the point of origin, the walk is complete */
id|walk_state-&gt;prev_op
op_assign
id|parent
suffix:semicolon
id|walk_state-&gt;next_op
op_assign
l_int|NULL
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * If there is a sibling to this parent (it is not the starting point&n;&t;&t; * Op), then we will visit it.&n;&t;&t; */
r_if
c_cond
(paren
id|next
)paren
(brace
multiline_comment|/* found sibling of parent */
id|walk_state-&gt;prev_op
op_assign
id|parent
suffix:semicolon
id|walk_state-&gt;next_op
op_assign
id|next
suffix:semicolon
id|walk_state-&gt;next_op_info
op_assign
id|NEXT_OP_DOWNWARD
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* No siblings, no errors, just move up one more level in the tree */
id|op
op_assign
id|parent
suffix:semicolon
id|parent
op_assign
id|grand_parent
suffix:semicolon
id|walk_state-&gt;prev_op
op_assign
id|op
suffix:semicolon
)brace
multiline_comment|/* Got all the way to the top of the tree, we must be done! */
multiline_comment|/* However, the code should have terminated in the loop above */
id|walk_state-&gt;next_op
op_assign
l_int|NULL
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_delete_completed_op&n; *&n; * PARAMETERS:  State           - Walk state&n; *              Op              - Completed op&n; *&n; * RETURN:      AE_OK&n; *&n; * DESCRIPTION: Callback function for Acpi_ps_get_next_walk_op(). Used during&n; *              Acpi_ps_delete_parse tree to delete Op objects when all sub-objects&n; *              have been visited (and deleted.)&n; *&n; ******************************************************************************/
r_static
id|acpi_status
DECL|function|acpi_ps_delete_completed_op
id|acpi_ps_delete_completed_op
(paren
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_ps_free_op
(paren
id|walk_state-&gt;op
)paren
suffix:semicolon
r_return
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ps_delete_parse_tree&n; *&n; * PARAMETERS:  Subtree_root        - Root of tree (or subtree) to delete&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Delete a portion of or an entire parse tree.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ps_delete_parse_tree
id|acpi_ps_delete_parse_tree
(paren
id|acpi_parse_object
op_star
id|subtree_root
)paren
(brace
id|acpi_walk_state
op_star
id|walk_state
suffix:semicolon
id|acpi_walk_list
id|walk_list
suffix:semicolon
id|FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ps_delete_parse_tree&quot;
comma
id|subtree_root
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|subtree_root
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* Create and initialize a new walk list */
id|walk_list.walk_state
op_assign
l_int|NULL
suffix:semicolon
id|walk_list.acquired_mutex_list.prev
op_assign
l_int|NULL
suffix:semicolon
id|walk_list.acquired_mutex_list.next
op_assign
l_int|NULL
suffix:semicolon
id|walk_state
op_assign
id|acpi_ds_create_walk_state
(paren
id|TABLE_ID_DSDT
comma
l_int|NULL
comma
l_int|NULL
comma
op_amp
id|walk_list
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|walk_state
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
id|walk_state-&gt;parse_flags
op_assign
l_int|0
suffix:semicolon
id|walk_state-&gt;descending_callback
op_assign
l_int|NULL
suffix:semicolon
id|walk_state-&gt;ascending_callback
op_assign
l_int|NULL
suffix:semicolon
id|walk_state-&gt;origin
op_assign
id|subtree_root
suffix:semicolon
id|walk_state-&gt;next_op
op_assign
id|subtree_root
suffix:semicolon
multiline_comment|/* Head downward in the tree */
id|walk_state-&gt;next_op_info
op_assign
id|NEXT_OP_DOWNWARD
suffix:semicolon
multiline_comment|/* Visit all nodes in the subtree */
r_while
c_loop
(paren
id|walk_state-&gt;next_op
)paren
(brace
id|acpi_ps_get_next_walk_op
(paren
id|walk_state
comma
id|walk_state-&gt;next_op
comma
id|acpi_ps_delete_completed_op
)paren
suffix:semicolon
)brace
multiline_comment|/* We are done with this walk */
id|acpi_ex_release_all_mutexes
(paren
(paren
id|acpi_operand_object
op_star
)paren
op_amp
id|walk_list.acquired_mutex_list
)paren
suffix:semicolon
id|acpi_ds_delete_walk_state
(paren
id|walk_state
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
eof
