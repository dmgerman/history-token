multiline_comment|/******************************************************************************&n; *&n; * Module Name: exmutex - ASL Mutex Acquire/Release functions&n; *              $Revision: 16 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2002, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EXECUTER
id|ACPI_MODULE_NAME
(paren
l_string|&quot;exmutex&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_unlink_mutex&n; *&n; * PARAMETERS:  *Obj_desc           - The mutex to be unlinked&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Remove a mutex from the &quot;Acquired_mutex&quot; list&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ex_unlink_mutex
id|acpi_ex_unlink_mutex
(paren
id|acpi_operand_object
op_star
id|obj_desc
)paren
(brace
id|ACPI_THREAD_STATE
op_star
id|thread
op_assign
id|obj_desc-&gt;mutex.owner_thread
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|thread
)paren
(brace
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj_desc-&gt;mutex.next
)paren
(brace
(paren
id|obj_desc-&gt;mutex.next
)paren
op_member_access_from_pointer
id|mutex.prev
op_assign
id|obj_desc-&gt;mutex.prev
suffix:semicolon
)brace
r_if
c_cond
(paren
id|obj_desc-&gt;mutex.prev
)paren
(brace
(paren
id|obj_desc-&gt;mutex.prev
)paren
op_member_access_from_pointer
id|mutex.next
op_assign
id|obj_desc-&gt;mutex.next
suffix:semicolon
)brace
r_else
(brace
id|thread-&gt;acquired_mutex_list
op_assign
id|obj_desc-&gt;mutex.next
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_link_mutex&n; *&n; * PARAMETERS:  *Obj_desc           - The mutex to be linked&n; *              *List_head          - head of the &quot;Acquired_mutex&quot; list&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Add a mutex to the &quot;Acquired_mutex&quot; list for this walk&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ex_link_mutex
id|acpi_ex_link_mutex
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|ACPI_THREAD_STATE
op_star
id|thread
)paren
(brace
id|acpi_operand_object
op_star
id|list_head
suffix:semicolon
id|list_head
op_assign
id|thread-&gt;acquired_mutex_list
suffix:semicolon
multiline_comment|/* This object will be the first object in the list */
id|obj_desc-&gt;mutex.prev
op_assign
l_int|NULL
suffix:semicolon
id|obj_desc-&gt;mutex.next
op_assign
id|list_head
suffix:semicolon
multiline_comment|/* Update old first object to point back to this object */
r_if
c_cond
(paren
id|list_head
)paren
(brace
id|list_head-&gt;mutex.prev
op_assign
id|obj_desc
suffix:semicolon
)brace
multiline_comment|/* Update list head */
id|thread-&gt;acquired_mutex_list
op_assign
id|obj_desc
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_acquire_mutex&n; *&n; * PARAMETERS:  *Time_desc          - The &squot;time to delay&squot; object descriptor&n; *              *Obj_desc           - The object descriptor for this op&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Acquire an AML mutex&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_acquire_mutex
id|acpi_ex_acquire_mutex
(paren
id|acpi_operand_object
op_star
id|time_desc
comma
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;Ex_acquire_mutex&quot;
comma
id|obj_desc
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
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Sanity check -- we must have a valid thread ID */
r_if
c_cond
(paren
op_logical_neg
id|walk_state-&gt;thread
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Cannot acquire Mutex [%4.4s], null thread info&bslash;n&quot;
comma
id|obj_desc-&gt;mutex.node-&gt;name.ascii
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_INTERNAL
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Current Sync must be less than or equal to the sync level of the&n;&t; * mutex.  This mechanism provides some deadlock prevention&n;&t; */
r_if
c_cond
(paren
id|walk_state-&gt;thread-&gt;current_sync_level
OG
id|obj_desc-&gt;mutex.sync_level
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Cannot acquire Mutex [%4.4s], incorrect Sync_level&bslash;n&quot;
comma
id|obj_desc-&gt;mutex.node-&gt;name.ascii
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_MUTEX_ORDER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Support for multiple acquires by the owning thread&n;&t; */
r_if
c_cond
(paren
(paren
id|obj_desc-&gt;mutex.owner_thread
)paren
op_logical_and
(paren
id|obj_desc-&gt;mutex.owner_thread-&gt;thread_id
op_eq
id|walk_state-&gt;thread-&gt;thread_id
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * The mutex is already owned by this thread,&n;&t;&t; * just increment the acquisition depth&n;&t;&t; */
id|obj_desc-&gt;mutex.acquisition_depth
op_increment
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Acquire the mutex, wait if necessary */
id|status
op_assign
id|acpi_ex_system_acquire_mutex
(paren
id|time_desc
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
multiline_comment|/* Includes failure from a timeout on Time_desc */
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/* Have the mutex, update mutex and walk info */
id|obj_desc-&gt;mutex.owner_thread
op_assign
id|walk_state-&gt;thread
suffix:semicolon
id|obj_desc-&gt;mutex.acquisition_depth
op_assign
l_int|1
suffix:semicolon
id|walk_state-&gt;thread-&gt;current_sync_level
op_assign
id|obj_desc-&gt;mutex.sync_level
suffix:semicolon
multiline_comment|/* Link the mutex to the current thread for force-unlock at method exit */
id|acpi_ex_link_mutex
(paren
id|obj_desc
comma
id|walk_state-&gt;thread
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_release_mutex&n; *&n; * PARAMETERS:  *Obj_desc           - The object descriptor for this op&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Release a previously acquired Mutex.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ex_release_mutex
id|acpi_ex_release_mutex
(paren
id|acpi_operand_object
op_star
id|obj_desc
comma
id|acpi_walk_state
op_star
id|walk_state
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;Ex_release_mutex&quot;
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
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* The mutex must have been previously acquired in order to release it */
r_if
c_cond
(paren
op_logical_neg
id|obj_desc-&gt;mutex.owner_thread
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Cannot release Mutex [%4.4s], not acquired&bslash;n&quot;
comma
id|obj_desc-&gt;mutex.node-&gt;name.ascii
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_MUTEX_NOT_ACQUIRED
)paren
suffix:semicolon
)brace
multiline_comment|/* Sanity check -- we must have a valid thread ID */
r_if
c_cond
(paren
op_logical_neg
id|walk_state-&gt;thread
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Cannot release Mutex [%4.4s], null thread info&bslash;n&quot;
comma
id|obj_desc-&gt;mutex.node-&gt;name.ascii
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_INTERNAL
)paren
suffix:semicolon
)brace
multiline_comment|/* The Mutex is owned, but this thread must be the owner */
r_if
c_cond
(paren
id|obj_desc-&gt;mutex.owner_thread-&gt;thread_id
op_ne
id|walk_state-&gt;thread-&gt;thread_id
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Thread %X cannot release Mutex [%4.4s] acquired by thread %X&bslash;n&quot;
comma
id|walk_state-&gt;thread-&gt;thread_id
comma
id|obj_desc-&gt;mutex.node-&gt;name.ascii
comma
id|obj_desc-&gt;mutex.owner_thread-&gt;thread_id
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_NOT_OWNER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * The sync level of the mutex must be less than or&n;&t; * equal to the current sync level&n;&t; */
r_if
c_cond
(paren
id|obj_desc-&gt;mutex.sync_level
OG
id|walk_state-&gt;thread-&gt;current_sync_level
)paren
(brace
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Cannot release Mutex [%4.4s], incorrect Sync_level&bslash;n&quot;
comma
id|obj_desc-&gt;mutex.node-&gt;name.ascii
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_AML_MUTEX_ORDER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Match multiple Acquires with multiple Releases&n;&t; */
id|obj_desc-&gt;mutex.acquisition_depth
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|obj_desc-&gt;mutex.acquisition_depth
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Just decrement the depth and return */
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Unlink the mutex from the owner&squot;s list */
id|acpi_ex_unlink_mutex
(paren
id|obj_desc
)paren
suffix:semicolon
multiline_comment|/* Release the mutex */
id|status
op_assign
id|acpi_ex_system_release_mutex
(paren
id|obj_desc
)paren
suffix:semicolon
multiline_comment|/* Update the mutex and walk state */
id|obj_desc-&gt;mutex.owner_thread
op_assign
l_int|NULL
suffix:semicolon
id|walk_state-&gt;thread-&gt;current_sync_level
op_assign
id|obj_desc-&gt;mutex.sync_level
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    Acpi_ex_release_all_mutexes&n; *&n; * PARAMETERS:  *Mutex_list           - Head of the mutex list&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Release all mutexes in the list&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ex_release_all_mutexes
id|acpi_ex_release_all_mutexes
(paren
id|ACPI_THREAD_STATE
op_star
id|thread
)paren
(brace
id|acpi_operand_object
op_star
id|next
op_assign
id|thread-&gt;acquired_mutex_list
suffix:semicolon
id|acpi_operand_object
op_star
id|this
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Traverse the list of owned mutexes, releasing each one.&n;&t; */
r_while
c_loop
(paren
id|next
)paren
(brace
id|this
op_assign
id|next
suffix:semicolon
id|next
op_assign
id|this-&gt;mutex.next
suffix:semicolon
id|this-&gt;mutex.acquisition_depth
op_assign
l_int|1
suffix:semicolon
id|this-&gt;mutex.prev
op_assign
l_int|NULL
suffix:semicolon
id|this-&gt;mutex.next
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Release the mutex */
id|status
op_assign
id|acpi_ex_system_release_mutex
(paren
id|this
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
r_continue
suffix:semicolon
)brace
multiline_comment|/* Mark mutex unowned */
id|this-&gt;mutex.owner_thread
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
eof
