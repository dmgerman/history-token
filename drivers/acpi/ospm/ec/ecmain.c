multiline_comment|/*****************************************************************************&n; *&n; * Module Name: ecmain.c&n; *   $Revision: 29 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;acpi.h&gt;
macro_line|#include &quot;ec.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_EC
id|MODULE_NAME
(paren
l_string|&quot;ecmain&quot;
)paren
multiline_comment|/****************************************************************************&n; *                            Internal Functions&n; ****************************************************************************/
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    ec_print&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION: Prints out information on a specific ec.&n; *&n; ****************************************************************************/
r_void
DECL|function|ec_print
id|ec_print
(paren
id|EC_CONTEXT
op_star
id|ec
)paren
(brace
macro_line|#ifdef ACPI_DEBUG
id|acpi_buffer
id|buffer
suffix:semicolon
macro_line|#endif /*ACPI_DEBUG*/
id|PROC_NAME
c_func
(paren
l_string|&quot;ec_print&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ec
)paren
(brace
r_return
suffix:semicolon
)brace
id|acpi_os_printf
c_func
(paren
l_string|&quot;EC: found, GPE %d&bslash;n&quot;
comma
id|ec-&gt;gpe_bit
)paren
suffix:semicolon
macro_line|#ifdef ACPI_DEBUG
id|buffer.length
op_assign
l_int|256
suffix:semicolon
id|buffer.pointer
op_assign
id|acpi_os_callocate
c_func
(paren
id|buffer.length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer.pointer
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get the full pathname for this ACPI object.&n;&t; */
id|acpi_get_name
c_func
(paren
id|ec-&gt;acpi_handle
comma
id|ACPI_FULL_PATHNAME
comma
op_amp
id|buffer
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Print out basic thermal zone information.&n;&t; */
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;+------------------------------------------------------------&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;| Embedded_controller[%02x]:[%p] %s&bslash;n&quot;
comma
id|ec-&gt;device_handle
comma
id|ec-&gt;acpi_handle
comma
(paren
r_char
op_star
)paren
id|buffer.pointer
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;|   gpe_bit[%02x] status/command_port[%02x] data_port[%02x]&bslash;n&quot;
comma
id|ec-&gt;gpe_bit
comma
id|ec-&gt;status_port
comma
id|ec-&gt;data_port
)paren
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT_RAW
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;+------------------------------------------------------------&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|acpi_os_free
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
macro_line|#endif /*ACPI_DEBUG*/
r_return
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    ec_get_port_values&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION: Evaluate _CRS to get the current resources (I/O port&n; *              addresses) for this EC.&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|ec_get_port_values
id|ec_get_port_values
c_func
(paren
id|EC_CONTEXT
op_star
id|ec
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|acpi_buffer
id|buffer
suffix:semicolon
id|acpi_resource
op_star
id|resource
op_assign
l_int|NULL
suffix:semicolon
id|FUNCTION_TRACE
c_func
(paren
l_string|&quot;ec_get_port_values&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ec
)paren
(brace
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|buffer.length
op_assign
l_int|0
suffix:semicolon
id|buffer.pointer
op_assign
l_int|NULL
suffix:semicolon
id|status
op_assign
id|acpi_get_current_resources
c_func
(paren
id|ec-&gt;acpi_handle
comma
op_amp
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_ne
id|AE_BUFFER_OVERFLOW
)paren
(brace
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
id|buffer.pointer
op_assign
id|acpi_os_callocate
c_func
(paren
id|buffer.length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|buffer.pointer
)paren
(brace
id|return_ACPI_STATUS
c_func
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_get_current_resources
c_func
(paren
id|ec-&gt;acpi_handle
comma
op_amp
id|buffer
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
r_goto
id|end
suffix:semicolon
)brace
id|resource
op_assign
(paren
id|acpi_resource
op_star
)paren
id|buffer.pointer
suffix:semicolon
id|ec-&gt;data_port
op_assign
id|resource-&gt;data.io.min_base_address
suffix:semicolon
id|resource
op_assign
id|NEXT_RESOURCE
c_func
(paren
id|resource
)paren
suffix:semicolon
id|ec-&gt;status_port
op_assign
id|ec-&gt;command_port
op_assign
id|resource-&gt;data.io.min_base_address
suffix:semicolon
id|end
suffix:colon
id|acpi_os_free
c_func
(paren
id|buffer.pointer
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    ec_add_device&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|ec_add_device
id|ec_add_device
c_func
(paren
id|BM_HANDLE
id|device_handle
comma
r_void
op_star
op_star
id|context
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|BM_DEVICE
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
id|EC_CONTEXT
op_star
id|ec
op_assign
l_int|NULL
suffix:semicolon
id|u8
id|gpe_handler
op_assign
id|FALSE
suffix:semicolon
id|u8
id|space_handler
op_assign
id|FALSE
suffix:semicolon
id|FUNCTION_TRACE
c_func
(paren
l_string|&quot;ec_add_device&quot;
)paren
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Adding EC device [%02x].&bslash;n&quot;
comma
id|device_handle
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|context
op_logical_or
op_star
id|context
)paren
(brace
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Get information on this device.&n;&t; */
id|status
op_assign
id|bm_get_device_info
c_func
(paren
id|device_handle
comma
op_amp
id|device
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
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allocate a new EC_CONTEXT structure.&n;&t; */
id|ec
op_assign
id|acpi_os_callocate
c_func
(paren
r_sizeof
(paren
id|EC_CONTEXT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ec
)paren
(brace
id|return_ACPI_STATUS
c_func
(paren
id|AE_NO_MEMORY
)paren
suffix:semicolon
)brace
id|ec-&gt;device_handle
op_assign
id|device-&gt;handle
suffix:semicolon
id|ec-&gt;acpi_handle
op_assign
id|device-&gt;acpi_handle
suffix:semicolon
multiline_comment|/*&n;&t; * Get the I/O port addresses for the command/status and data ports.&n;&t; */
id|status
op_assign
id|ec_get_port_values
c_func
(paren
id|ec
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
r_goto
id|end
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * See if we need to obtain the global lock for EC transactions.&n;&t; */
id|status
op_assign
id|bm_evaluate_simple_integer
c_func
(paren
id|ec-&gt;acpi_handle
comma
l_string|&quot;_GLK&quot;
comma
op_amp
id|ec-&gt;use_global_lock
)paren
suffix:semicolon
r_if
c_cond
(paren
id|status
op_eq
id|AE_NOT_FOUND
)paren
(brace
id|ec-&gt;use_global_lock
op_assign
l_int|0
suffix:semicolon
)brace
r_else
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
l_string|&quot;EC _GLK failed&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Install a handler for servicing this EC&squot;s GPE.&n;&t; */
id|status
op_assign
id|ec_install_gpe_handler
c_func
(paren
id|ec
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
r_goto
id|end
suffix:semicolon
)brace
r_else
(brace
id|gpe_handler
op_assign
id|TRUE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Install a handler for servicing this EC&squot;s address space.&n;&t; */
id|status
op_assign
id|ec_install_space_handler
c_func
(paren
id|ec
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
r_goto
id|end
suffix:semicolon
)brace
r_else
(brace
id|space_handler
op_assign
id|TRUE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Create a semaphore to serialize EC transactions.&n;&t; */
id|status
op_assign
id|acpi_os_create_semaphore
c_func
(paren
l_int|1
comma
l_int|1
comma
op_amp
(paren
id|ec-&gt;mutex
)paren
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
r_goto
id|end
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Context now contains information specific to this EC.  Note&n;&t; * that we&squot;ll get this pointer back on every ec_request() and&n;&t; * ec_notify().&n;&t; */
op_star
id|context
op_assign
id|ec
suffix:semicolon
id|ec_print
c_func
(paren
id|ec
)paren
suffix:semicolon
id|end
suffix:colon
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
r_if
c_cond
(paren
id|gpe_handler
)paren
(brace
id|ec_remove_gpe_handler
c_func
(paren
id|ec
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|space_handler
)paren
(brace
id|ec_remove_space_handler
c_func
(paren
id|ec
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ec-&gt;mutex
)paren
(brace
id|acpi_os_delete_semaphore
c_func
(paren
id|ec-&gt;mutex
)paren
suffix:semicolon
)brace
id|acpi_os_free
c_func
(paren
id|ec
)paren
suffix:semicolon
)brace
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    ec_remove_device&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|ec_remove_device
id|ec_remove_device
c_func
(paren
r_void
op_star
op_star
id|context
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|EC_CONTEXT
op_star
id|ec
op_assign
l_int|NULL
suffix:semicolon
id|FUNCTION_TRACE
c_func
(paren
l_string|&quot;ec_remove_device&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|context
op_logical_or
op_logical_neg
op_star
id|context
)paren
(brace
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
)brace
id|ec
op_assign
(paren
id|EC_CONTEXT
op_star
)paren
op_star
id|context
suffix:semicolon
id|ACPI_DEBUG_PRINT
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Removing EC device [%02x].&bslash;n&quot;
comma
id|ec-&gt;device_handle
)paren
)paren
suffix:semicolon
id|ec_remove_space_handler
c_func
(paren
id|ec
)paren
suffix:semicolon
id|ec_remove_gpe_handler
c_func
(paren
id|ec
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ec-&gt;mutex
)paren
(brace
id|acpi_os_delete_semaphore
c_func
(paren
id|ec-&gt;mutex
)paren
suffix:semicolon
)brace
id|acpi_os_free
c_func
(paren
id|ec
)paren
suffix:semicolon
op_star
id|context
op_assign
l_int|NULL
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *                             External Functions&n; ****************************************************************************/
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    ec_initialize&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|ec_initialize
id|ec_initialize
(paren
r_void
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|BM_DEVICE_ID
id|criteria
suffix:semicolon
id|BM_DRIVER
id|driver
suffix:semicolon
id|FUNCTION_TRACE
c_func
(paren
l_string|&quot;ec_initialize&quot;
)paren
suffix:semicolon
id|MEMSET
c_func
(paren
op_amp
id|criteria
comma
l_int|0
comma
r_sizeof
(paren
id|BM_DEVICE_ID
)paren
)paren
suffix:semicolon
id|MEMSET
c_func
(paren
op_amp
id|driver
comma
l_int|0
comma
r_sizeof
(paren
id|BM_DRIVER
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Register driver for AC Adapter devices.&n;&t; */
id|MEMCPY
c_func
(paren
id|criteria.hid
comma
id|EC_HID_EC
comma
r_sizeof
(paren
id|EC_HID_EC
)paren
)paren
suffix:semicolon
id|driver.notify
op_assign
op_amp
id|ec_notify
suffix:semicolon
id|driver.request
op_assign
op_amp
id|ec_request
suffix:semicolon
id|status
op_assign
id|bm_register_driver
c_func
(paren
op_amp
id|criteria
comma
op_amp
id|driver
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    ec_terminate&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|ec_terminate
id|ec_terminate
c_func
(paren
r_void
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|BM_DEVICE_ID
id|criteria
suffix:semicolon
id|BM_DRIVER
id|driver
suffix:semicolon
id|FUNCTION_TRACE
c_func
(paren
l_string|&quot;ec_terminate&quot;
)paren
suffix:semicolon
id|MEMSET
c_func
(paren
op_amp
id|criteria
comma
l_int|0
comma
r_sizeof
(paren
id|BM_DEVICE_ID
)paren
)paren
suffix:semicolon
id|MEMSET
c_func
(paren
op_amp
id|driver
comma
l_int|0
comma
r_sizeof
(paren
id|BM_DRIVER
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Unregister driver for AC Adapter devices.&n;&t; */
id|MEMCPY
c_func
(paren
id|criteria.hid
comma
id|EC_HID_EC
comma
r_sizeof
(paren
id|EC_HID_EC
)paren
)paren
suffix:semicolon
id|driver.notify
op_assign
op_amp
id|ec_notify
suffix:semicolon
id|driver.request
op_assign
op_amp
id|ec_request
suffix:semicolon
id|status
op_assign
id|bm_unregister_driver
c_func
(paren
op_amp
id|criteria
comma
op_amp
id|driver
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    ec_notify&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|ec_notify
id|ec_notify
(paren
id|BM_NOTIFY
id|notify
comma
id|BM_HANDLE
id|device_handle
comma
r_void
op_star
op_star
id|context
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|FUNCTION_TRACE
c_func
(paren
l_string|&quot;ec_notify&quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|notify
)paren
(brace
r_case
id|BM_NOTIFY_DEVICE_ADDED
suffix:colon
id|status
op_assign
id|ec_add_device
c_func
(paren
id|device_handle
comma
id|context
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BM_NOTIFY_DEVICE_REMOVED
suffix:colon
id|status
op_assign
id|ec_remove_device
c_func
(paren
id|context
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|AE_SUPPORT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:    ec_request&n; *&n; * PARAMETERS:&n; *&n; * RETURN:&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|acpi_status
DECL|function|ec_request
id|ec_request
(paren
id|BM_REQUEST
op_star
id|request
comma
r_void
op_star
id|context
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
id|EC_REQUEST
op_star
id|ec_request
op_assign
l_int|NULL
suffix:semicolon
id|EC_CONTEXT
op_star
id|ec
op_assign
l_int|NULL
suffix:semicolon
id|FUNCTION_TRACE
c_func
(paren
l_string|&quot;ec_request&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Must have a valid request structure and context.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|request
op_logical_or
op_logical_neg
id|context
)paren
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * buffer must contain a valid EC_REQUEST structure.&n;&t; */
id|status
op_assign
id|bm_cast_buffer
c_func
(paren
op_amp
(paren
id|request-&gt;buffer
)paren
comma
(paren
r_void
op_star
op_star
)paren
op_amp
id|ec_request
comma
r_sizeof
(paren
id|EC_REQUEST
)paren
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
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * context contains information specific to this EC.&n;&t; */
id|ec
op_assign
(paren
id|EC_CONTEXT
op_star
)paren
id|context
suffix:semicolon
multiline_comment|/*&n;&t; * Perform the Transaction.&n;&t; */
id|status
op_assign
id|ec_transaction
c_func
(paren
id|ec
comma
id|ec_request
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|status
)paren
suffix:semicolon
)brace
eof
