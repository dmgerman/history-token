multiline_comment|/******************************************************************************&n; *&n; * Module Name: evxface - External interfaces for ACPI events&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000 - 2003, R. Byron Moore&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &quot;acpi.h&quot;
macro_line|#include &quot;acnamesp.h&quot;
macro_line|#include &quot;acevents.h&quot;
macro_line|#include &quot;acinterp.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT          ACPI_EVENTS
id|ACPI_MODULE_NAME
(paren
l_string|&quot;evxface&quot;
)paren
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_install_fixed_event_handler&n; *&n; * PARAMETERS:  Event           - Event type to enable.&n; *              Handler         - Pointer to the handler function for the&n; *                                event&n; *              Context         - Value passed to the handler on each GPE&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Saves the pointer to the handler function and then enables the&n; *              event.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_install_fixed_event_handler
id|acpi_install_fixed_event_handler
(paren
id|u32
id|event
comma
id|acpi_event_handler
id|handler
comma
r_void
op_star
id|context
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_install_fixed_event_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
id|event
OG
id|ACPI_EVENT_MAX
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_EVENTS
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
multiline_comment|/* Don&squot;t allow two handlers. */
r_if
c_cond
(paren
l_int|NULL
op_ne
id|acpi_gbl_fixed_event_handlers
(braket
id|event
)braket
dot
id|handler
)paren
(brace
id|status
op_assign
id|AE_ALREADY_EXISTS
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Install the handler before enabling the event */
id|acpi_gbl_fixed_event_handlers
(braket
id|event
)braket
dot
id|handler
op_assign
id|handler
suffix:semicolon
id|acpi_gbl_fixed_event_handlers
(braket
id|event
)braket
dot
id|context
op_assign
id|context
suffix:semicolon
id|status
op_assign
id|acpi_enable_event
(paren
id|event
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
id|ACPI_DB_WARN
comma
l_string|&quot;Could not enable fixed event.&bslash;n&quot;
)paren
)paren
suffix:semicolon
multiline_comment|/* Remove the handler */
id|acpi_gbl_fixed_event_handlers
(braket
id|event
)braket
dot
id|handler
op_assign
l_int|NULL
suffix:semicolon
id|acpi_gbl_fixed_event_handlers
(braket
id|event
)braket
dot
id|context
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Enabled fixed event %X, Handler=%p&bslash;n&quot;
comma
id|event
comma
id|handler
)paren
)paren
suffix:semicolon
)brace
id|cleanup
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_EVENTS
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_remove_fixed_event_handler&n; *&n; * PARAMETERS:  Event           - Event type to disable.&n; *              Handler         - Address of the handler&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Disables the event and unregisters the event handler.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_remove_fixed_event_handler
id|acpi_remove_fixed_event_handler
(paren
id|u32
id|event
comma
id|acpi_event_handler
id|handler
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_remove_fixed_event_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
id|event
OG
id|ACPI_EVENT_MAX
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_EVENTS
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
multiline_comment|/* Disable the event before removing the handler */
id|status
op_assign
id|acpi_disable_event
c_func
(paren
id|event
comma
id|ACPI_EVENT_FIXED
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Always Remove the handler */
id|acpi_gbl_fixed_event_handlers
(braket
id|event
)braket
dot
id|handler
op_assign
l_int|NULL
suffix:semicolon
id|acpi_gbl_fixed_event_handlers
(braket
id|event
)braket
dot
id|context
op_assign
l_int|NULL
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
l_string|&quot;Could not write to fixed event enable register.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Disabled fixed event %X.&bslash;n&quot;
comma
id|event
)paren
)paren
suffix:semicolon
)brace
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_EVENTS
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_install_notify_handler&n; *&n; * PARAMETERS:  Device          - The device for which notifies will be handled&n; *              handler_type    - The type of handler:&n; *                                  ACPI_SYSTEM_NOTIFY: system_handler (00-7f)&n; *                                  ACPI_DEVICE_NOTIFY: driver_handler (80-ff)&n; *              Handler         - Address of the handler&n; *              Context         - Value passed to the handler on each GPE&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install a handler for notifies on an ACPI device&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_install_notify_handler
id|acpi_install_notify_handler
(paren
id|acpi_handle
id|device
comma
id|u32
id|handler_type
comma
id|acpi_notify_handler
id|handler
comma
r_void
op_star
id|context
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
id|notify_obj
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_install_notify_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
(paren
op_logical_neg
id|device
)paren
op_logical_or
(paren
op_logical_neg
id|handler
)paren
op_logical_or
(paren
id|handler_type
OG
id|ACPI_MAX_NOTIFY_HANDLER_TYPE
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
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
multiline_comment|/* Convert and validate the device handle */
id|node
op_assign
id|acpi_ns_map_handle_to_node
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Root Object:&n;&t; * Registering a notify handler on the root object indicates that the&n;&t; * caller wishes to receive notifications for all objects.  Note that&n;&t; * only one &lt;external&gt; global handler can be regsitered (per notify type).&n;&t; */
r_if
c_cond
(paren
id|device
op_eq
id|ACPI_ROOT_OBJECT
)paren
(brace
multiline_comment|/* Make sure the handler is not already installed */
r_if
c_cond
(paren
(paren
(paren
id|handler_type
op_eq
id|ACPI_SYSTEM_NOTIFY
)paren
op_logical_and
id|acpi_gbl_sys_notify.handler
)paren
op_logical_or
(paren
(paren
id|handler_type
op_eq
id|ACPI_DEVICE_NOTIFY
)paren
op_logical_and
id|acpi_gbl_drv_notify.handler
)paren
)paren
(brace
id|status
op_assign
id|AE_ALREADY_EXISTS
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
r_if
c_cond
(paren
id|handler_type
op_eq
id|ACPI_SYSTEM_NOTIFY
)paren
(brace
id|acpi_gbl_sys_notify.node
op_assign
id|node
suffix:semicolon
id|acpi_gbl_sys_notify.handler
op_assign
id|handler
suffix:semicolon
id|acpi_gbl_sys_notify.context
op_assign
id|context
suffix:semicolon
)brace
r_else
multiline_comment|/* ACPI_DEVICE_NOTIFY */
(brace
id|acpi_gbl_drv_notify.node
op_assign
id|node
suffix:semicolon
id|acpi_gbl_drv_notify.handler
op_assign
id|handler
suffix:semicolon
id|acpi_gbl_drv_notify.context
op_assign
id|context
suffix:semicolon
)brace
multiline_comment|/* Global notify handler installed */
)brace
multiline_comment|/*&n;&t; * All Other Objects:&n;&t; * Caller will only receive notifications specific to the target object.&n;&t; * Note that only certain object types can receive notifications.&n;&t; */
r_else
(brace
multiline_comment|/* Notifies allowed on this object? */
r_if
c_cond
(paren
op_logical_neg
id|acpi_ev_is_notify_object
(paren
id|node
)paren
)paren
(brace
id|status
op_assign
id|AE_TYPE
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Check for an existing internal object */
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
multiline_comment|/* Object exists - make sure there&squot;s no handler */
r_if
c_cond
(paren
(paren
(paren
id|handler_type
op_eq
id|ACPI_SYSTEM_NOTIFY
)paren
op_logical_and
id|obj_desc-&gt;common_notify.sys_handler
)paren
op_logical_or
(paren
(paren
id|handler_type
op_eq
id|ACPI_DEVICE_NOTIFY
)paren
op_logical_and
id|obj_desc-&gt;common_notify.drv_handler
)paren
)paren
(brace
id|status
op_assign
id|AE_ALREADY_EXISTS
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
)brace
r_else
(brace
multiline_comment|/* Create a new object */
id|obj_desc
op_assign
id|acpi_ut_create_internal_object
(paren
id|node-&gt;type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|obj_desc
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Attach new object to the Node */
id|status
op_assign
id|acpi_ns_attach_object
(paren
id|device
comma
id|obj_desc
comma
id|node-&gt;type
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
id|unlock_and_exit
suffix:semicolon
)brace
)brace
multiline_comment|/* Install the handler */
id|notify_obj
op_assign
id|acpi_ut_create_internal_object
(paren
id|ACPI_TYPE_LOCAL_NOTIFY
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|notify_obj
)paren
(brace
id|status
op_assign
id|AE_NO_MEMORY
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
id|notify_obj-&gt;notify_handler.node
op_assign
id|node
suffix:semicolon
id|notify_obj-&gt;notify_handler.handler
op_assign
id|handler
suffix:semicolon
id|notify_obj-&gt;notify_handler.context
op_assign
id|context
suffix:semicolon
r_if
c_cond
(paren
id|handler_type
op_eq
id|ACPI_SYSTEM_NOTIFY
)paren
(brace
id|obj_desc-&gt;common_notify.sys_handler
op_assign
id|notify_obj
suffix:semicolon
)brace
r_else
multiline_comment|/* ACPI_DEVICE_NOTIFY */
(brace
id|obj_desc-&gt;common_notify.drv_handler
op_assign
id|notify_obj
suffix:semicolon
)brace
)brace
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_remove_notify_handler&n; *&n; * PARAMETERS:  Device          - The device for which notifies will be handled&n; *              handler_type    - The type of handler:&n; *                                  ACPI_SYSTEM_NOTIFY: system_handler (00-7f)&n; *                                  ACPI_DEVICE_NOTIFY: driver_handler (80-ff)&n; *              Handler         - Address of the handler&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Remove a handler for notifies on an ACPI device&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_remove_notify_handler
id|acpi_remove_notify_handler
(paren
id|acpi_handle
id|device
comma
id|u32
id|handler_type
comma
id|acpi_notify_handler
id|handler
)paren
(brace
r_union
id|acpi_operand_object
op_star
id|notify_obj
suffix:semicolon
r_union
id|acpi_operand_object
op_star
id|obj_desc
suffix:semicolon
r_struct
id|acpi_namespace_node
op_star
id|node
suffix:semicolon
id|acpi_status
id|status
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_remove_notify_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
(paren
op_logical_neg
id|device
)paren
op_logical_or
(paren
op_logical_neg
id|handler
)paren
op_logical_or
(paren
id|handler_type
OG
id|ACPI_MAX_NOTIFY_HANDLER_TYPE
)paren
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
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
multiline_comment|/* Convert and validate the device handle */
id|node
op_assign
id|acpi_ns_map_handle_to_node
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|node
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Root Object&n;&t; */
r_if
c_cond
(paren
id|device
op_eq
id|ACPI_ROOT_OBJECT
)paren
(brace
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Removing notify handler for ROOT object.&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|handler_type
op_eq
id|ACPI_SYSTEM_NOTIFY
)paren
op_logical_and
op_logical_neg
id|acpi_gbl_sys_notify.handler
)paren
op_logical_or
(paren
(paren
id|handler_type
op_eq
id|ACPI_DEVICE_NOTIFY
)paren
op_logical_and
op_logical_neg
id|acpi_gbl_drv_notify.handler
)paren
)paren
(brace
id|status
op_assign
id|AE_NOT_EXIST
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
r_if
c_cond
(paren
id|handler_type
op_eq
id|ACPI_SYSTEM_NOTIFY
)paren
(brace
id|acpi_gbl_sys_notify.node
op_assign
l_int|NULL
suffix:semicolon
id|acpi_gbl_sys_notify.handler
op_assign
l_int|NULL
suffix:semicolon
id|acpi_gbl_sys_notify.context
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|acpi_gbl_drv_notify.node
op_assign
l_int|NULL
suffix:semicolon
id|acpi_gbl_drv_notify.handler
op_assign
l_int|NULL
suffix:semicolon
id|acpi_gbl_drv_notify.context
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * All Other Objects&n;&t; */
r_else
(brace
multiline_comment|/* Notifies allowed on this object? */
r_if
c_cond
(paren
op_logical_neg
id|acpi_ev_is_notify_object
(paren
id|node
)paren
)paren
(brace
id|status
op_assign
id|AE_TYPE
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Check for an existing internal object */
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
id|status
op_assign
id|AE_NOT_EXIST
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Object exists - make sure there&squot;s an existing handler */
r_if
c_cond
(paren
id|handler_type
op_eq
id|ACPI_SYSTEM_NOTIFY
)paren
(brace
id|notify_obj
op_assign
id|obj_desc-&gt;common_notify.sys_handler
suffix:semicolon
)brace
r_else
(brace
id|notify_obj
op_assign
id|obj_desc-&gt;common_notify.drv_handler
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
op_logical_neg
id|notify_obj
)paren
op_logical_or
(paren
id|notify_obj-&gt;notify_handler.handler
op_ne
id|handler
)paren
)paren
(brace
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|unlock_and_exit
suffix:semicolon
)brace
multiline_comment|/* Remove the handler */
r_if
c_cond
(paren
id|handler_type
op_eq
id|ACPI_SYSTEM_NOTIFY
)paren
(brace
id|obj_desc-&gt;common_notify.sys_handler
op_assign
l_int|NULL
suffix:semicolon
)brace
r_else
(brace
id|obj_desc-&gt;common_notify.drv_handler
op_assign
l_int|NULL
suffix:semicolon
)brace
id|acpi_ut_remove_reference
(paren
id|notify_obj
)paren
suffix:semicolon
)brace
id|unlock_and_exit
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_NAMESPACE
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_install_gpe_handler&n; *&n; * PARAMETERS:  gpe_number      - The GPE number.  The numbering scheme is&n; *                                bank 0 first, then bank 1.&n; *              Type            - Whether this GPE should be treated as an&n; *                                edge- or level-triggered interrupt.&n; *              Handler         - Address of the handler&n; *              Context         - Value passed to the handler on each GPE&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Install a handler for a General Purpose Event.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_install_gpe_handler
id|acpi_install_gpe_handler
(paren
id|u32
id|gpe_number
comma
id|u32
id|type
comma
id|acpi_gpe_handler
id|handler
comma
r_void
op_star
id|context
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|u32
id|gpe_number_index
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_install_gpe_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Ensure that we have a valid GPE number */
id|gpe_number_index
op_assign
id|acpi_ev_get_gpe_number_index
(paren
id|gpe_number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpe_number_index
op_eq
id|ACPI_GPE_INVALID
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_EVENTS
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
multiline_comment|/* Make sure that there isn&squot;t a handler there already */
r_if
c_cond
(paren
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
dot
id|handler
)paren
(brace
id|status
op_assign
id|AE_ALREADY_EXISTS
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Install the handler */
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
dot
id|handler
op_assign
id|handler
suffix:semicolon
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
dot
id|context
op_assign
id|context
suffix:semicolon
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
dot
id|type
op_assign
(paren
id|u8
)paren
id|type
suffix:semicolon
multiline_comment|/* Clear the GPE (of stale events), the enable it */
id|status
op_assign
id|acpi_hw_clear_gpe
(paren
id|gpe_number
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
id|status
op_assign
id|acpi_hw_enable_gpe
(paren
id|gpe_number
)paren
suffix:semicolon
id|cleanup
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_EVENTS
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_remove_gpe_handler&n; *&n; * PARAMETERS:  gpe_number      - The event to remove a handler&n; *              Handler         - Address of the handler&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Remove a handler for a General Purpose acpi_event.&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_remove_gpe_handler
id|acpi_remove_gpe_handler
(paren
id|u32
id|gpe_number
comma
id|acpi_gpe_handler
id|handler
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
id|u32
id|gpe_number_index
suffix:semicolon
id|ACPI_FUNCTION_TRACE
(paren
l_string|&quot;acpi_remove_gpe_handler&quot;
)paren
suffix:semicolon
multiline_comment|/* Parameter validation */
r_if
c_cond
(paren
op_logical_neg
id|handler
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Ensure that we have a valid GPE number */
id|gpe_number_index
op_assign
id|acpi_ev_get_gpe_number_index
(paren
id|gpe_number
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gpe_number_index
op_eq
id|ACPI_GPE_INVALID
)paren
(brace
id|return_ACPI_STATUS
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/* Disable the GPE before removing the handler */
id|status
op_assign
id|acpi_hw_disable_gpe
(paren
id|gpe_number
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
id|status
op_assign
id|acpi_ut_acquire_mutex
(paren
id|ACPI_MTX_EVENTS
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
multiline_comment|/* Make sure that the installed handler is the same */
r_if
c_cond
(paren
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
dot
id|handler
op_ne
id|handler
)paren
(brace
(paren
r_void
)paren
id|acpi_hw_enable_gpe
(paren
id|gpe_number
)paren
suffix:semicolon
id|status
op_assign
id|AE_BAD_PARAMETER
suffix:semicolon
r_goto
id|cleanup
suffix:semicolon
)brace
multiline_comment|/* Remove the handler */
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
dot
id|handler
op_assign
l_int|NULL
suffix:semicolon
id|acpi_gbl_gpe_number_info
(braket
id|gpe_number_index
)braket
dot
id|context
op_assign
l_int|NULL
suffix:semicolon
id|cleanup
suffix:colon
(paren
r_void
)paren
id|acpi_ut_release_mutex
(paren
id|ACPI_MTX_EVENTS
)paren
suffix:semicolon
id|return_ACPI_STATUS
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_acquire_global_lock&n; *&n; * PARAMETERS:  Timeout         - How long the caller is willing to wait&n; *              out_handle      - A handle to the lock if acquired&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Acquire the ACPI Global Lock&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_acquire_global_lock
id|acpi_acquire_global_lock
(paren
id|u16
id|timeout
comma
id|u32
op_star
id|handle
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|handle
)paren
(brace
r_return
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ex_enter_interpreter
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
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ev_acquire_global_lock
(paren
id|timeout
)paren
suffix:semicolon
id|acpi_ex_exit_interpreter
(paren
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
id|acpi_gbl_global_lock_handle
op_increment
suffix:semicolon
op_star
id|handle
op_assign
id|acpi_gbl_global_lock_handle
suffix:semicolon
)brace
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*******************************************************************************&n; *&n; * FUNCTION:    acpi_release_global_lock&n; *&n; * PARAMETERS:  Handle      - Returned from acpi_acquire_global_lock&n; *&n; * RETURN:      Status&n; *&n; * DESCRIPTION: Release the ACPI Global Lock&n; *&n; ******************************************************************************/
id|acpi_status
DECL|function|acpi_release_global_lock
id|acpi_release_global_lock
(paren
id|u32
id|handle
)paren
(brace
id|acpi_status
id|status
suffix:semicolon
r_if
c_cond
(paren
id|handle
op_ne
id|acpi_gbl_global_lock_handle
)paren
(brace
r_return
(paren
id|AE_NOT_ACQUIRED
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_ev_release_global_lock
(paren
)paren
suffix:semicolon
r_return
(paren
id|status
)paren
suffix:semicolon
)brace
eof
