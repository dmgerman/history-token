multiline_comment|/******************************************************************************&n; *&n; * Module Name: evmisc - Miscellaneous event manager support functions&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2003, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EVENTS
id|ACPI_MODULE_NAME
(paren
l_string|&quot;evmisc&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_is_notify_object&n; *&n; * PARAMETERS:  Node            - Node to check&n; *&n; * RETURN:      TRUE if notifies allowed on this object&n; *&n; * DESCRIPTION: Check type of node for a object that supports notifies.&n; *&n; *              TBD: This could be replaced by a flag bit in the node.&n; *&n; ******************************************************************************/
id|u8
DECL|function|acpi_ev_is_notify_object
id|acpi_ev_is_notify_object
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
)paren
(brace
r_switch
c_cond
(paren
id|node-&gt;type
)paren
(brace
r_case
id|ACPI_TYPE_DEVICE
suffix:colon
r_case
id|ACPI_TYPE_PROCESSOR
suffix:colon
r_case
id|ACPI_TYPE_POWER
suffix:colon
r_case
id|ACPI_TYPE_THERMAL
suffix:colon
multiline_comment|/*&n;&t;&t; * These are the ONLY objects that can receive ACPI notifications&n;&t;&t; */
r_return
(paren
id|TRUE
)paren
suffix:semicolon
r_default
suffix:colon
r_return
(paren
id|FALSE
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_get_gpe_register_index&n; *&n; * PARAMETERS:  gpe_number      - Raw GPE number&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Returns the register index (index into the GPE register info&n; *              table) associated with this GPE.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ev_get_gpe_register_index
id|acpi_ev_get_gpe_register_index
(paren
id|u32
id|gpe_number
)paren
(brace
r_if
c_cond
(paren
id|gpe_number
OG
id|acpi_gbl_gpe_number_max
)paren
(brace
r_return
(paren
id|ACPI_GPE_INVALID
)paren
suffix:semicolon
)brace
r_return
(paren
id|ACPI_DIV_8
(paren
id|acpi_gbl_gpe_number_to_index
(braket
id|gpe_number
)braket
dot
id|number_index
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_get_gpe_number_index&n; *&n; * PARAMETERS:  gpe_number      - Raw GPE number&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Returns the number index (index into the GPE number info table)&n; *              associated with this GPE.&n; *&n; ******************************************************************************/
id|u32
DECL|function|acpi_ev_get_gpe_number_index
id|acpi_ev_get_gpe_number_index
(paren
id|u32
id|gpe_number
)paren
(brace
r_if
c_cond
(paren
id|gpe_number
OG
id|acpi_gbl_gpe_number_max
)paren
(brace
r_return
(paren
id|ACPI_GPE_INVALID
)paren
suffix:semicolon
)brace
r_return
(paren
id|acpi_gbl_gpe_number_to_index
(braket
id|gpe_number
)braket
dot
id|number_index
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_queue_notify_request&n; *&n; * PARAMETERS:&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Dispatch a device notification event to a previously&n; *              installed handler.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_queue_notify_request
id|acpi_ev_queue_notify_request
(paren
r_struct
id|acpi_namespace_node
op_star
id|node
comma
id|u32
id|notify_value
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|handler_obj
op_assign
l_int|NULL
suffix:semicolon
r_union
id|acpi_generic_state
op_star
id|notify_info
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_NAME
(paren
l_string|&quot;ev_queue_notify_request&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * For value 1 (Ejection Request), some device method may need to be run.&n;&t; * For value 2 (Device Wake) if _PRW exists, the _PS0 method may need to be run.&n;&t; * For value 0x80 (Status Change) on the power button or sleep button,&n;&t; * initiate soft-off or sleep operation?&n;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Dispatching Notify(%X) on node %p&bslash;n&quot;
comma
id|notify_value
comma
id|node
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|notify_value
)paren
(brace
r_case
l_int|0
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Notify value: Re-enumerate Devices&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Notify value: Ejection Request&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Notify value: Device Wake&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x80
suffix:colon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Notify value: Status Change&bslash;n&quot;
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
id|ACPI_DB_INFO
comma
l_string|&quot;Unknown Notify Value: %X &bslash;n&quot;
comma
id|notify_value
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get the notify object attached to the NS Node&n;&t; */
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
id|obj_desc
)paren
(brace
multiline_comment|/* We have the notify object, Get the right handler */
r_switch
c_cond
(paren
id|node-&gt;type
)paren
(brace
r_case
id|ACPI_TYPE_DEVICE
suffix:colon
r_case
id|ACPI_TYPE_THERMAL
suffix:colon
r_case
id|ACPI_TYPE_PROCESSOR
suffix:colon
r_case
id|ACPI_TYPE_POWER
suffix:colon
r_if
c_cond
(paren
id|notify_value
op_le
id|ACPI_MAX_SYS_NOTIFY
)paren
(brace
id|handler_obj
op_assign
id|obj_desc-&gt;common_notify.sys_handler
suffix:semicolon
)brace
r_else
(brace
id|handler_obj
op_assign
id|obj_desc-&gt;common_notify.drv_handler
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* All other types are not supported */
r_return
(paren
id|AE_TYPE
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* If there is any handler to run, schedule the dispatcher */
r_if
c_cond
(paren
(paren
id|acpi_gbl_sys_notify.handler
op_logical_and
(paren
id|notify_value
op_le
id|ACPI_MAX_SYS_NOTIFY
)paren
)paren
op_logical_or
(paren
id|acpi_gbl_drv_notify.handler
op_logical_and
(paren
id|notify_value
OG
id|ACPI_MAX_SYS_NOTIFY
)paren
)paren
op_logical_or
id|handler_obj
)paren
(brace
id|notify_info
op_assign
id|acpi_ut_create_generic_state
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|notify_info
)paren
(brace
r_return
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|notify_info-&gt;common.data_type
op_assign
id|ACPI_DESC_TYPE_STATE_NOTIFY
suffix:semicolon
id|notify_info-&gt;notify.node
op_assign
id|node
suffix:semicolon
id|notify_info-&gt;notify.value
op_assign
(paren
id|u16
)paren
id|notify_value
suffix:semicolon
id|notify_info-&gt;notify.handler_obj
op_assign
id|handler_obj
suffix:semicolon
id|status
op_assign
id|acpi_os_queue_for_execution
(paren
id|OSD_PRIORITY_HIGH
comma
id|acpi_ev_notify_dispatch
comma
id|notify_info
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
id|acpi_ut_delete_generic_state
(paren
id|notify_info
)paren
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|handler_obj
)paren
(brace
multiline_comment|/* There is no per-device notify handler for this device */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;No notify handler for [%4.4s] node %p&bslash;n&quot;
comma
id|node-&gt;name.ascii
comma
id|node
)paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_notify_dispatch&n; *&n; * PARAMETERS:&n; *&n; * RETURN:      None.&n; *&n; * DESCRIPTION: Dispatch a device notification event to a previously&n; *              installed handler.&n; *&n; ******************************************************************************/
r_void
id|ACPI_SYSTEM_XFACE
DECL|function|acpi_ev_notify_dispatch
id|acpi_ev_notify_dispatch
(paren
r_void
op_star
id|context
)paren
(brace
r_union
id|acpi_generic_state
op_star
id|notify_info
op_assign
(paren
r_union
id|acpi_generic_state
op_star
)paren
id|context
suffix:semicolon
id|acpi_notify_handler
id|global_handler
op_assign
l_int|NULL
suffix:semicolon
r_void
op_star
id|global_context
op_assign
l_int|NULL
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|handler_obj
suffix:semicolon
id|ACPI_FUNCTION_ENTRY
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * We will invoke a global notify handler if installed.&n;&t; * This is done _before_ we invoke the per-device handler attached to the device.&n;&t; */
r_if
c_cond
(paren
id|notify_info-&gt;notify.value
op_le
id|ACPI_MAX_SYS_NOTIFY
)paren
(brace
multiline_comment|/* Global system notification handler */
r_if
c_cond
(paren
id|acpi_gbl_sys_notify.handler
)paren
(brace
id|global_handler
op_assign
id|acpi_gbl_sys_notify.handler
suffix:semicolon
id|global_context
op_assign
id|acpi_gbl_sys_notify.context
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Global driver notification handler */
r_if
c_cond
(paren
id|acpi_gbl_drv_notify.handler
)paren
(brace
id|global_handler
op_assign
id|acpi_gbl_drv_notify.handler
suffix:semicolon
id|global_context
op_assign
id|acpi_gbl_drv_notify.context
suffix:semicolon
)brace
)brace
multiline_comment|/* Invoke the system handler first, if present */
r_if
c_cond
(paren
id|global_handler
)paren
(brace
id|global_handler
(paren
id|notify_info-&gt;notify.node
comma
id|notify_info-&gt;notify.value
comma
id|global_context
)paren
suffix:semicolon
)brace
multiline_comment|/* Now invoke the per-device handler, if present */
id|handler_obj
op_assign
id|notify_info-&gt;notify.handler_obj
suffix:semicolon
r_if
c_cond
(paren
id|handler_obj
)paren
(brace
id|handler_obj-&gt;notify_handler.handler
(paren
id|notify_info-&gt;notify.node
comma
id|notify_info-&gt;notify.value
comma
id|handler_obj-&gt;notify_handler.context
)paren
suffix:semicolon
)brace
multiline_comment|/* All done with the info object */
id|acpi_ut_delete_generic_state
(paren
id|notify_info
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_global_lock_thread&n; *&n; * RETURN:      None&n; *&n; * DESCRIPTION: Invoked by SCI interrupt handler upon acquisition of the&n; *              Global Lock.  Simply signal all threads that are waiting&n; *              for the lock.&n; *&n; ******************************************************************************/
r_static
r_void
id|ACPI_SYSTEM_XFACE
DECL|function|acpi_ev_global_lock_thread
id|acpi_ev_global_lock_thread
(paren
r_void
op_star
id|context
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
multiline_comment|/* Signal threads that are waiting for the lock */
r_if
c_cond
(paren
id|acpi_gbl_global_lock_thread_count
)paren
(brace
multiline_comment|/* Send sufficient units to the semaphore */
id|status
op_assign
id|acpi_os_signal_semaphore
(paren
id|acpi_gbl_global_lock_semaphore
comma
id|acpi_gbl_global_lock_thread_count
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
l_string|&quot;Could not signal Global Lock semaphore&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_global_lock_handler&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Invoked directly from the SCI handler when a global lock&n; *              release interrupt occurs.  Grab the global lock and queue&n; *              the global lock thread for execution&n; *&n; ******************************************************************************/
r_static
id|u32
DECL|function|acpi_ev_global_lock_handler
id|acpi_ev_global_lock_handler
(paren
r_void
op_star
id|context
)paren
(brace
id|u8
id|acquired
op_assign
id|FALSE
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
multiline_comment|/*&n;&t; * Attempt to get the lock&n;&t; * If we don&squot;t get it now, it will be marked pending and we will&n;&t; * take another interrupt when it becomes free.&n;&t; */
id|ACPI_ACQUIRE_GLOBAL_LOCK
(paren
id|acpi_gbl_common_fACS.global_lock
comma
id|acquired
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acquired
)paren
(brace
multiline_comment|/* Got the lock, now wake all threads waiting for it */
id|acpi_gbl_global_lock_acquired
op_assign
id|TRUE
suffix:semicolon
multiline_comment|/* Run the Global Lock thread which will signal all waiting threads */
id|status
op_assign
id|acpi_os_queue_for_execution
(paren
id|OSD_PRIORITY_HIGH
comma
id|acpi_ev_global_lock_thread
comma
id|context
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
l_string|&quot;Could not queue Global Lock thread, %s&bslash;n&quot;
comma
id|acpi_format_exception
(paren
id|status
)paren
)paren
)paren
suffix:semicolon
r_return
(paren
id|ACPI_INTERRUPT_NOT_HANDLED
)paren
suffix:semicolon
)brace
)brace
r_return
(paren
id|ACPI_INTERRUPT_HANDLED
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_init_global_lock_handler&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install a handler for the global lock release event&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_init_global_lock_handler
id|acpi_ev_init_global_lock_handler
(paren
r_void
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_init_global_lock_handler&quot;
)paren
suffix:semicolon
id|acpi_gbl_global_lock_present
op_assign
id|TRUE
suffix:semicolon
id|status
op_assign
id|acpi_install_fixed_event_handler
(paren
id|ACPI_EVENT_GLOBAL
comma
id|acpi_ev_global_lock_handler
comma
l_int|NULL
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If the global lock does not exist on this platform, the attempt&n;&t; * to enable GBL_STATUS will fail (the GBL_ENABLE bit will not stick)&n;&t; * Map to AE_OK, but mark global lock as not present.&n;&t; * Any attempt to actually use the global lock will be flagged&n;&t; * with an error.&n;&t; */
r_if
c_cond
(paren
id|status
op_eq
id|AE_NO_HARDWARE_RESPONSE
)paren
(brace
id|acpi_gbl_global_lock_present
op_assign
id|FALSE
suffix:semicolon
id|status
op_assign
id|AE_OK
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_acquire_global_lock&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Attempt to gain ownership of the Global Lock.&n; *&n; *****************************************************************************/
id|acpi_status
DECL|function|acpi_ev_acquire_global_lock
id|acpi_ev_acquire_global_lock
(paren
id|u16
id|timeout
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|u8
id|acquired
op_assign
id|FALSE
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_acquire_global_lock&quot;
)paren
suffix:semicolon
macro_line|#ifndef ACPI_APPLICATION
multiline_comment|/* Make sure that we actually have a global lock */
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_global_lock_present
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_NO_GLOBAL_LOCK
)paren
suffix:semicolon
)brace
macro_line|#endif
multiline_comment|/* One more thread wants the global lock */
id|acpi_gbl_global_lock_thread_count
op_increment
suffix:semicolon
multiline_comment|/* If we (OS side vs. BIOS side) have the hardware lock already, we are done */
r_if
c_cond
(paren
id|acpi_gbl_global_lock_acquired
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/* We must acquire the actual hardware lock */
id|ACPI_ACQUIRE_GLOBAL_LOCK
(paren
id|acpi_gbl_common_fACS.global_lock
comma
id|acquired
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acquired
)paren
(brace
multiline_comment|/* We got the lock */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Acquired the HW Global Lock&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|acpi_gbl_global_lock_acquired
op_assign
id|TRUE
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Did not get the lock.  The pending bit was set above, and we must now&n;&t; * wait until we get the global lock released interrupt.&n;&t; */
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_EXEC
comma
l_string|&quot;Waiting for the HW Global Lock&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Acquire the global lock semaphore first.&n;&t; * Since this wait will block, we must release the interpreter&n;&t; */
id|status
op_assign
id|acpi_ex_system_wait_semaphore
(paren
id|acpi_gbl_global_lock_semaphore
comma
id|timeout
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_release_global_lock&n; *&n; * DESCRIPTION: Releases ownership of the Global Lock.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_ev_release_global_lock
id|acpi_ev_release_global_lock
(paren
r_void
)paren
(brace
id|u8
id|pending
op_assign
id|FALSE
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_release_global_lock&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_gbl_global_lock_thread_count
)paren
(brace
id|ACPI_REPORT_WARNING
c_func
(paren
(paren
l_string|&quot;Cannot release HW Global Lock, it has not been acquired&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|AE_NOT_ACQUIRED
)paren
suffix:semicolon
)brace
multiline_comment|/* One fewer thread has the global lock */
id|acpi_gbl_global_lock_thread_count
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_global_lock_thread_count
)paren
(brace
multiline_comment|/* There are still some threads holding the lock, cannot release */
id|return_ACPI_STATUS
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * No more threads holding lock, we can do the actual hardware&n;&t; * release&n;&t; */
id|ACPI_RELEASE_GLOBAL_LOCK
(paren
id|acpi_gbl_common_fACS.global_lock
comma
id|pending
)paren
suffix:semicolon
id|acpi_gbl_global_lock_acquired
op_assign
id|FALSE
suffix:semicolon
multiline_comment|/*&n;&t; * If the pending bit was set, we must write GBL_RLS to the control&n;&t; * register&n;&t; */
r_if
c_cond
(paren
id|pending
)paren
(brace
id|status
op_assign
id|acpi_set_register
(paren
id|ACPI_BITREG_GLOBAL_LOCK_RELEASE
comma
l_int|1
comma
id|ACPI_MTX_LOCK
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/******************************************************************************&n; *&n; * FUNCTION:    acpi_ev_terminate&n; *&n; * PARAMETERS:  none&n; *&n; * RETURN:      none&n; *&n; * DESCRIPTION: Disable events and free memory allocated for table storage.&n; *&n; ******************************************************************************/
r_void
DECL|function|acpi_ev_terminate
id|acpi_ev_terminate
(paren
r_void
)paren
(brace
id|acpi_native_uint
id|i
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;ev_terminate&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_gbl_events_initialized
)paren
(brace
multiline_comment|/*&n;&t;&t; * Disable all event-related functionality.&n;&t;&t; * In all cases, on error, print a message but obviously we don&squot;t abort.&n;&t;&t; */
multiline_comment|/*&n;&t;&t; * Disable all fixed events&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ACPI_NUM_FIXED_EVENTS
suffix:semicolon
id|i
op_increment
)paren
(brace
id|status
op_assign
id|acpi_disable_event
(paren
(paren
id|u32
)paren
id|i
comma
id|ACPI_EVENT_FIXED
comma
l_int|0
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not disable fixed event %d&bslash;n&quot;
comma
(paren
id|u32
)paren
id|i
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t;&t; * Disable all GPEs&n;&t;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|acpi_gbl_gpe_number_max
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|acpi_ev_get_gpe_number_index
(paren
(paren
id|u32
)paren
id|i
)paren
op_ne
id|ACPI_GPE_INVALID
)paren
(brace
id|status
op_assign
id|acpi_hw_disable_gpe
c_func
(paren
(paren
id|u32
)paren
id|i
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not disable GPE %d&bslash;n&quot;
comma
(paren
id|u32
)paren
id|i
)paren
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n;&t;&t; * Remove SCI handler&n;&t;&t; */
id|status
op_assign
id|acpi_ev_remove_sci_handler
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Could not remove SCI handler&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Return to original mode if necessary&n;&t; */
r_if
c_cond
(paren
id|acpi_gbl_original_mode
op_eq
id|ACPI_SYS_MODE_LEGACY
)paren
(brace
id|status
op_assign
id|acpi_disable
(paren
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
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;acpi_disable failed&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Free global tables, etc.&n;&t; */
r_if
c_cond
(paren
id|acpi_gbl_gpe_register_info
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|acpi_gbl_gpe_register_info
)paren
suffix:semicolon
id|acpi_gbl_gpe_register_info
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_gbl_gpe_number_info
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|acpi_gbl_gpe_number_info
)paren
suffix:semicolon
id|acpi_gbl_gpe_number_info
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|acpi_gbl_gpe_number_to_index
)paren
(brace
id|ACPI_MEM_FREE
(paren
id|acpi_gbl_gpe_number_to_index
)paren
suffix:semicolon
id|acpi_gbl_gpe_number_to_index
op_assign
l_int|NULL
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
eof
