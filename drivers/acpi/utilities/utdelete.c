multiline_comment|/*******************************************************************************&n; *&n; * Module Name: utdelete - object deletion and reference count utilities&n; *&n; ******************************************************************************/
multiline_comment|/*&n; * Copyright (C) 2000 - 2004, R. Byron Moore&n; * All rights reserved.&n; *&n; * Redistribution and use in source and binary forms, with or without&n; * modification, are permitted provided that the following conditions&n; * are met:&n; * 1. Redistributions of source code must retain the above copyright&n; *    notice, this list of conditions, and the following disclaimer,&n; *    without modification.&n; * 2. Redistributions in binary form must reproduce at minimum a disclaimer&n; *    substantially similar to the &quot;NO WARRANTY&quot; disclaimer below&n; *    (&quot;Disclaimer&quot;) and any redistribution must be conditioned upon&n; *    including a substantially similar Disclaimer requirement for further&n; *    binary redistribution.&n; * 3. Neither the names of the above-listed copyright holders nor the names&n; *    of any contributors may be used to endorse or promote products derived&n; *    from this software without specific prior written permission.&n; *&n; * Alternatively, this software may be distributed under the terms of the&n; * GNU General Public License (&quot;GPL&quot;) version 2 as published by the Free&n; * Software Foundation.&n; *&n; * NO WARRANTY&n; * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS&n; * &quot;AS IS&quot; AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT&n; * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR&n; * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT&n; * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL&n; * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS&n; * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)&n; * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,&n; * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING&n; * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE&n; * POSSIBILITY OF SUCH DAMAGES.&n; */
macro_line|#include &lt;acpi/acpi.h&gt;
macro_line|#include &lt;acpi/acinterp.h&gt;
macro_line|#include &lt;acpi/acnamesp.h&gt;
macro_line|#include &lt;acpi/acevents.h&gt;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_UTILITIES
id|ACPI_MODULE_NAME
(paren
l_string|&quot;utdelete&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_delete_internal_obj&n; *&n; * PARAMETERS:  *Object        - Pointer to the list to be deleted&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Low level object deletion, after reference counts have been&n; *              updated (All reference counts, including sub-objects!)&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_delete_internal_obj
id|acpi_ut_delete_internal_obj
(paren
r_union
id|acpi_operand_object
op_star
id|object
)paren
(brace
r_void
op_star
id|obj_pointer
op_assign
l_int|NULL
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|handler_desc
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|second_desc
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|next_desc
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ut_delete_internal_obj&quot;
comma
id|object
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Must delete or free any pointers within the object that are not&n;&t; * actual ACPI objects (for example, a raw buffer pointer).&n;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|object
)paren
)paren
(brace
r_case
id|ACPI_TYPE_STRING
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;**** String %p, ptr %p&bslash;n&quot;
comma
id|object
comma
id|object-&gt;string.pointer
)paren
)paren
suffix:semicolon
multiline_comment|/* Free the actual string buffer */
r_if
c_cond
(paren
op_logical_neg
(paren
id|object-&gt;common.flags
op_amp
id|AOPOBJ_STATIC_POINTER
)paren
)paren
(brace
multiline_comment|/* But only if it is NOT a pointer into an ACPI table */
id|obj_pointer
op_assign
id|object-&gt;string.pointer
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;**** Buffer %p, ptr %p&bslash;n&quot;
comma
id|object
comma
id|object-&gt;buffer.pointer
)paren
)paren
suffix:semicolon
multiline_comment|/* Free the actual buffer */
r_if
c_cond
(paren
op_logical_neg
(paren
id|object-&gt;common.flags
op_amp
id|AOPOBJ_STATIC_POINTER
)paren
)paren
(brace
multiline_comment|/* But only if it is NOT a pointer into an ACPI table */
id|obj_pointer
op_assign
id|object-&gt;buffer.pointer
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot; **** Package of count %X&bslash;n&quot;
comma
id|object-&gt;package.count
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Elements of the package are not handled here, they are deleted&n;&t;&t; * separately&n;&t;&t; */
multiline_comment|/* Free the (variable length) element pointer array */
id|obj_pointer
op_assign
id|object-&gt;package.elements
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_DEVICE
suffix:colon
r_if
c_cond
(paren
id|object-&gt;device.gpe_block
)paren
(brace
(paren
r_void
)paren
id|acpi_ev_delete_gpe_block
(paren
id|object-&gt;device.gpe_block
)paren
suffix:semicolon
)brace
multiline_comment|/* Walk the handler list for this device */
id|handler_desc
op_assign
id|object-&gt;device.handler
suffix:semicolon
r_while
c_loop
(paren
id|handler_desc
)paren
(brace
id|next_desc
op_assign
id|handler_desc-&gt;address_space.next
suffix:semicolon
id|acpi_ut_remove_reference
(paren
id|handler_desc
)paren
suffix:semicolon
id|handler_desc
op_assign
id|next_desc
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_MUTEX
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;***** Mutex %p, Semaphore %p&bslash;n&quot;
comma
id|object
comma
id|object-&gt;mutex.semaphore
)paren
)paren
suffix:semicolon
id|acpi_ex_unlink_mutex
(paren
id|object
)paren
suffix:semicolon
(paren
r_void
)paren
id|acpi_os_delete_semaphore
(paren
id|object-&gt;mutex.semaphore
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_EVENT
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;***** Event %p, Semaphore %p&bslash;n&quot;
comma
id|object
comma
id|object-&gt;event.semaphore
)paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|acpi_os_delete_semaphore
(paren
id|object-&gt;event.semaphore
)paren
suffix:semicolon
id|object-&gt;event.semaphore
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_METHOD
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;***** Method %p&bslash;n&quot;
comma
id|object
)paren
)paren
suffix:semicolon
multiline_comment|/* Delete the method semaphore if it exists */
r_if
c_cond
(paren
id|object-&gt;method.semaphore
)paren
(brace
(paren
r_void
)paren
id|acpi_os_delete_semaphore
(paren
id|object-&gt;method.semaphore
)paren
suffix:semicolon
id|object-&gt;method.semaphore
op_assign
l_int|NULL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_REGION
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;***** Region %p&bslash;n&quot;
comma
id|object
)paren
)paren
suffix:semicolon
id|second_desc
op_assign
id|acpi_ns_get_secondary_object
(paren
id|object
)paren
suffix:semicolon
r_if
c_cond
(paren
id|second_desc
)paren
(brace
multiline_comment|/*&n;&t;&t;&t; * Free the region_context if and only if the handler is one of the&n;&t;&t;&t; * default handlers -- and therefore, we created the context object&n;&t;&t;&t; * locally, it was not created by an external caller.&n;&t;&t;&t; */
id|handler_desc
op_assign
id|object-&gt;region.handler
suffix:semicolon
r_if
c_cond
(paren
id|handler_desc
)paren
(brace
r_if
c_cond
(paren
id|handler_desc-&gt;address_space.hflags
op_amp
id|ACPI_ADDR_HANDLER_DEFAULT_INSTALLED
)paren
(brace
id|obj_pointer
op_assign
id|second_desc-&gt;extra.region_context
suffix:semicolon
)brace
id|acpi_ut_remove_reference
(paren
id|handler_desc
)paren
suffix:semicolon
)brace
multiline_comment|/* Now we can free the Extra object */
id|acpi_ut_delete_object_desc
(paren
id|second_desc
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;***** Buffer Field %p&bslash;n&quot;
comma
id|object
)paren
)paren
suffix:semicolon
id|second_desc
op_assign
id|acpi_ns_get_secondary_object
(paren
id|object
)paren
suffix:semicolon
r_if
c_cond
(paren
id|second_desc
)paren
(brace
id|acpi_ut_delete_object_desc
(paren
id|second_desc
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
r_break
suffix:semicolon
)brace
multiline_comment|/* Free any allocated memory (pointer within the object) found above */
r_if
c_cond
(paren
id|obj_pointer
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Deleting Object Subptr %p&bslash;n&quot;
comma
id|obj_pointer
)paren
)paren
suffix:semicolon
id|ACPI_MEM_FREE
(paren
id|obj_pointer
)paren
suffix:semicolon
)brace
multiline_comment|/* Now the object can be safely deleted */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Deleting Object %p [%s]&bslash;n&quot;
comma
id|object
comma
id|acpi_ut_get_object_type_name
(paren
id|object
)paren
)paren
)paren
suffix:semicolon
id|acpi_ut_delete_object_desc
(paren
id|object
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_delete_internal_object_list&n; *&n; * PARAMETERS:  *obj_list       - Pointer to the list to be deleted&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: This function deletes an internal object list, including both&n; *              simple objects and package objects&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_delete_internal_object_list
id|acpi_ut_delete_internal_object_list
(paren
r_union
id|acpi_operand_object
op_star
op_star
id|obj_list
)paren
(brace
r_union
id|acpi_operand_object
op_star
op_star
id|internal_obj
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ut_delete_internal_object_list&quot;
)paren
suffix:semicolon
multiline_comment|/* Walk the null-terminated internal list */
r_for
c_loop
(paren
id|internal_obj
op_assign
id|obj_list
suffix:semicolon
op_star
id|internal_obj
suffix:semicolon
id|internal_obj
op_increment
)paren
(brace
id|acpi_ut_remove_reference
(paren
op_star
id|internal_obj
)paren
suffix:semicolon
)brace
multiline_comment|/* Free the combined parameter pointer list and object array */
id|ACPI_MEM_FREE
(paren
id|obj_list
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_update_ref_count&n; *&n; * PARAMETERS:  *Object         - Object whose ref count is to be updated&n; *              Action          - What to do&n; *&n; * RETURN:      New ref count&n; *&n; * DESCRIPTION: Modify the ref count and return it.&n; *&n; ******************************************************************************/
r_static
r_void
DECL|function|acpi_ut_update_ref_count
id|acpi_ut_update_ref_count
(paren
r_union
id|acpi_operand_object
op_star
id|object
comma
id|u32
id|action
)paren
(brace
id|u16
id|count
suffix:semicolon
id|u16
id|new_count
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ut_update_ref_count&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
r_return
suffix:semicolon
)brace
id|count
op_assign
id|object-&gt;common.reference_count
suffix:semicolon
id|new_count
op_assign
id|count
suffix:semicolon
multiline_comment|/*&n;&t; * Perform the reference count action (increment, decrement, or force delete)&n;&t; */
r_switch
c_cond
(paren
id|action
)paren
(brace
r_case
id|REF_INCREMENT
suffix:colon
id|new_count
op_increment
suffix:semicolon
id|object-&gt;common.reference_count
op_assign
id|new_count
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Obj %p Refs=%X, [Incremented]&bslash;n&quot;
comma
id|object
comma
id|new_count
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|REF_DECREMENT
suffix:colon
r_if
c_cond
(paren
id|count
OL
l_int|1
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Obj %p Refs=%X, can&squot;t decrement! (Set to 0)&bslash;n&quot;
comma
id|object
comma
id|new_count
)paren
)paren
suffix:semicolon
id|new_count
op_assign
l_int|0
suffix:semicolon
)brace
r_else
(brace
id|new_count
op_decrement
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Obj %p Refs=%X, [Decremented]&bslash;n&quot;
comma
id|object
comma
id|new_count
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|object
)paren
op_eq
id|ACPI_TYPE_METHOD
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Method Obj %p Refs=%X, [Decremented]&bslash;n&quot;
comma
id|object
comma
id|new_count
)paren
)paren
suffix:semicolon
)brace
id|object-&gt;common.reference_count
op_assign
id|new_count
suffix:semicolon
r_if
c_cond
(paren
id|new_count
op_eq
l_int|0
)paren
(brace
id|acpi_ut_delete_internal_obj
(paren
id|object
)paren
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|REF_FORCE_DELETE
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Obj %p Refs=%X, Force delete! (Set to 0)&bslash;n&quot;
comma
id|object
comma
id|count
)paren
)paren
suffix:semicolon
id|new_count
op_assign
l_int|0
suffix:semicolon
id|object-&gt;common.reference_count
op_assign
id|new_count
suffix:semicolon
id|acpi_ut_delete_internal_obj
(paren
id|object
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
l_string|&quot;Unknown action (%X)&bslash;n&quot;
comma
id|action
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Sanity check the reference count, for debug purposes only.&n;&t; * (A deleted object will have a huge reference count)&n;&t; */
r_if
c_cond
(paren
id|count
OG
id|ACPI_MAX_REFERENCE_COUNT
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;**** Warning **** Large Reference Count (%X) in object %p&bslash;n&bslash;n&quot;
comma
id|count
comma
id|object
)paren
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_update_object_reference&n; *&n; * PARAMETERS:  *Object             - Increment ref count for this object&n; *                                    and all sub-objects&n; *              Action              - Either REF_INCREMENT or REF_DECREMENT or&n; *                                    REF_FORCE_DELETE&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Increment the object reference count&n; *&n; * Object references are incremented when:&n; * 1) An object is attached to a Node (namespace object)&n; * 2) An object is copied (all subobjects must be incremented)&n; *&n; * Object references are decremented when:&n; * 1) An object is detached from an Node&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ut_update_object_reference
id|acpi_ut_update_object_reference
(paren
r_union
id|acpi_operand_object
op_star
id|object
comma
id|u16
id|action
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|u32
id|i
suffix:semicolon
r_union
id|acpi_generic_state
op_star
id|state_list
op_assign
l_int|NULL
suffix:semicolon
r_union
id|acpi_generic_state
op_star
id|state
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|tmp
suffix:semicolon
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ut_update_object_reference&quot;
comma
id|object
)paren
suffix:semicolon
multiline_comment|/* Ignore a null object ptr */
r_if
c_cond
(paren
op_logical_neg
id|object
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* Make sure that this isn&squot;t a namespace handle */
r_if
c_cond
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|object
)paren
op_eq
id|ACPI_DESC_TYPE_NAMED
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Object %p is NS handle&bslash;n&quot;
comma
id|object
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
id|state
op_assign
id|acpi_ut_create_update_state
(paren
id|object
comma
id|action
)paren
suffix:semicolon
r_while
c_loop
(paren
id|state
)paren
(brace
id|object
op_assign
id|state-&gt;update.object
suffix:semicolon
id|action
op_assign
id|state-&gt;update.value
suffix:semicolon
id|acpi_ut_delete_generic_state
(paren
id|state
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * All sub-objects must have their reference count incremented also.&n;&t;&t; * Different object types have different subobjects.&n;&t;&t; */
r_switch
c_cond
(paren
id|ACPI_GET_OBJECT_TYPE
(paren
id|object
)paren
)paren
(brace
r_case
id|ACPI_TYPE_DEVICE
suffix:colon
id|tmp
op_assign
id|object-&gt;device.system_notify
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
(paren
id|tmp-&gt;common.reference_count
op_le
l_int|1
)paren
op_logical_and
id|action
op_eq
id|REF_DECREMENT
)paren
id|object-&gt;device.system_notify
op_assign
l_int|NULL
suffix:semicolon
id|acpi_ut_update_ref_count
(paren
id|tmp
comma
id|action
)paren
suffix:semicolon
id|tmp
op_assign
id|object-&gt;device.device_notify
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
(paren
id|tmp-&gt;common.reference_count
op_le
l_int|1
)paren
op_logical_and
id|action
op_eq
id|REF_DECREMENT
)paren
id|object-&gt;device.device_notify
op_assign
l_int|NULL
suffix:semicolon
id|acpi_ut_update_ref_count
(paren
id|tmp
comma
id|action
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_PACKAGE
suffix:colon
multiline_comment|/*&n;&t;&t;&t; * We must update all the sub-objects of the package&n;&t;&t;&t; * (Each of whom may have their own sub-objects, etc.&n;&t;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|object-&gt;package.count
suffix:semicolon
id|i
op_increment
)paren
(brace
multiline_comment|/*&n;&t;&t;&t;&t; * Push each element onto the stack for later processing.&n;&t;&t;&t;&t; * Note: There can be null elements within the package,&n;&t;&t;&t;&t; * these are simply ignored&n;&t;&t;&t;&t; */
id|status
op_assign
id|acpi_ut_create_update_state_and_push
(paren
id|object-&gt;package.elements
(braket
id|i
)braket
comma
id|action
comma
op_amp
id|state_list
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
id|error_exit
suffix:semicolon
)brace
id|tmp
op_assign
id|object-&gt;package.elements
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
(paren
id|tmp-&gt;common.reference_count
op_le
l_int|1
)paren
op_logical_and
id|action
op_eq
id|REF_DECREMENT
)paren
id|object-&gt;package.elements
(braket
id|i
)braket
op_assign
l_int|NULL
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_BUFFER_FIELD
suffix:colon
id|status
op_assign
id|acpi_ut_create_update_state_and_push
(paren
id|object-&gt;buffer_field.buffer_obj
comma
id|action
comma
op_amp
id|state_list
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
id|error_exit
suffix:semicolon
)brace
id|tmp
op_assign
id|object-&gt;buffer_field.buffer_obj
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
(paren
id|tmp-&gt;common.reference_count
op_le
l_int|1
)paren
op_logical_and
id|action
op_eq
id|REF_DECREMENT
)paren
id|object-&gt;buffer_field.buffer_obj
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_REGION_FIELD
suffix:colon
id|status
op_assign
id|acpi_ut_create_update_state_and_push
(paren
id|object-&gt;field.region_obj
comma
id|action
comma
op_amp
id|state_list
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
id|error_exit
suffix:semicolon
)brace
id|tmp
op_assign
id|object-&gt;field.region_obj
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
(paren
id|tmp-&gt;common.reference_count
op_le
l_int|1
)paren
op_logical_and
id|action
op_eq
id|REF_DECREMENT
)paren
id|object-&gt;field.region_obj
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_BANK_FIELD
suffix:colon
id|status
op_assign
id|acpi_ut_create_update_state_and_push
(paren
id|object-&gt;bank_field.bank_obj
comma
id|action
comma
op_amp
id|state_list
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
id|error_exit
suffix:semicolon
)brace
id|tmp
op_assign
id|object-&gt;bank_field.bank_obj
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
(paren
id|tmp-&gt;common.reference_count
op_le
l_int|1
)paren
op_logical_and
id|action
op_eq
id|REF_DECREMENT
)paren
id|object-&gt;bank_field.bank_obj
op_assign
l_int|NULL
suffix:semicolon
id|status
op_assign
id|acpi_ut_create_update_state_and_push
(paren
id|object-&gt;bank_field.region_obj
comma
id|action
comma
op_amp
id|state_list
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
id|error_exit
suffix:semicolon
)brace
id|tmp
op_assign
id|object-&gt;bank_field.region_obj
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
(paren
id|tmp-&gt;common.reference_count
op_le
l_int|1
)paren
op_logical_and
id|action
op_eq
id|REF_DECREMENT
)paren
id|object-&gt;bank_field.region_obj
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_LOCAL_INDEX_FIELD
suffix:colon
id|status
op_assign
id|acpi_ut_create_update_state_and_push
(paren
id|object-&gt;index_field.index_obj
comma
id|action
comma
op_amp
id|state_list
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
id|error_exit
suffix:semicolon
)brace
id|tmp
op_assign
id|object-&gt;index_field.index_obj
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
(paren
id|tmp-&gt;common.reference_count
op_le
l_int|1
)paren
op_logical_and
id|action
op_eq
id|REF_DECREMENT
)paren
id|object-&gt;index_field.index_obj
op_assign
l_int|NULL
suffix:semicolon
id|status
op_assign
id|acpi_ut_create_update_state_and_push
(paren
id|object-&gt;index_field.data_obj
comma
id|action
comma
op_amp
id|state_list
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
id|error_exit
suffix:semicolon
)brace
id|tmp
op_assign
id|object-&gt;index_field.data_obj
suffix:semicolon
r_if
c_cond
(paren
id|tmp
op_logical_and
(paren
id|tmp-&gt;common.reference_count
op_le
l_int|1
)paren
op_logical_and
id|action
op_eq
id|REF_DECREMENT
)paren
id|object-&gt;index_field.data_obj
op_assign
l_int|NULL
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_TYPE_REGION
suffix:colon
r_case
id|ACPI_TYPE_LOCAL_REFERENCE
suffix:colon
r_default
suffix:colon
multiline_comment|/* No subobjects */
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t;&t; * Now we can update the count in the main object.  This can only&n;&t;&t; * happen after we update the sub-objects in case this causes the&n;&t;&t; * main object to be deleted.&n;&t;&t; */
id|acpi_ut_update_ref_count
(paren
id|object
comma
id|action
)paren
suffix:semicolon
multiline_comment|/* Move on to the next object to be updated */
id|state
op_assign
id|acpi_ut_pop_generic_state
(paren
op_amp
id|state_list
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
id|error_exit
suffix:colon
id|ACPI_REPORT_ERROR
(paren
(paren
l_string|&quot;Could not update object reference count, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_add_reference&n; *&n; * PARAMETERS:  *Object        - Object whose reference count is to be&n; *                                  incremented&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Add one reference to an ACPI object&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_add_reference
id|acpi_ut_add_reference
(paren
r_union
id|acpi_operand_object
op_star
id|object
)paren
(brace
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ut_add_reference&quot;
comma
id|object
)paren
suffix:semicolon
multiline_comment|/* Ensure that we have a valid object */
r_if
c_cond
(paren
op_logical_neg
id|acpi_ut_valid_internal_object
(paren
id|object
)paren
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Obj %p Current Refs=%X [To Be Incremented]&bslash;n&quot;
comma
id|object
comma
id|object-&gt;common.reference_count
)paren
)paren
suffix:semicolon
multiline_comment|/* Increment the reference count */
(paren
r_void
)paren
id|acpi_ut_update_object_reference
(paren
id|object
comma
id|REF_INCREMENT
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ut_remove_reference&n; *&n; * PARAMETERS:  *Object        - Object whose ref count will be decremented&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Decrement the reference count of an ACPI internal object&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ut_remove_reference
id|acpi_ut_remove_reference
(paren
r_union
id|acpi_operand_object
op_star
id|object
)paren
(brace
id|ACPI_FUNCTION_TRACE_PTR
(paren
l_string|&quot;ut_remove_reference&quot;
comma
id|object
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Allow a NULL pointer to be passed in, just ignore it.  This saves&n;&t; * each caller from having to check.  Also, ignore NS nodes.&n;&t; *&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|object
op_logical_or
(paren
id|ACPI_GET_DESCRIPTOR_TYPE
(paren
id|object
)paren
op_eq
id|ACPI_DESC_TYPE_NAMED
)paren
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
multiline_comment|/* Ensure that we have a valid object */
r_if
c_cond
(paren
op_logical_neg
id|acpi_ut_valid_internal_object
(paren
id|object
)paren
)paren
(brace
id|return_VOID
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ALLOCATIONS
comma
l_string|&quot;Obj %p Current Refs=%X [To Be Decremented]&bslash;n&quot;
comma
id|object
comma
id|object-&gt;common.reference_count
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Decrement the reference count, and only actually delete the object&n;&t; * if the reference count becomes 0.  (Must also decrement the ref count&n;&t; * of all subobjects!)&n;&t; */
(paren
r_void
)paren
id|acpi_ut_update_object_reference
(paren
id|object
comma
id|REF_DECREMENT
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
eof
