multiline_comment|/*****************************************************************************&n; *&n; * Module Name: bt.c&n; *   $Revision: 24 $&n; *&n; *****************************************************************************/
multiline_comment|/*&n; *  Copyright (C) 2000, 2001 Andrew Grover&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; */
macro_line|#include &lt;acpi.h&gt;
macro_line|#include &quot;bt.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_BATTERY
id|MODULE_NAME
(paren
l_string|&quot;bt&quot;
)paren
multiline_comment|/****************************************************************************&n; *                            Internal Functions&n; ****************************************************************************/
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bt_print&n; *&n; * PARAMETERS:&t;&n; *&n; * RETURN:&t;&n; *&n; * DESCRIPTION: Prints out information on a specific battery.&n; *&n; ****************************************************************************/
r_void
DECL|function|bt_print
id|bt_print
(paren
id|BT_CONTEXT
op_star
id|battery
)paren
(brace
r_return
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bt_get_info&n; *&n; * PARAMETERS:&t;&n; *&n; * RETURN:&t;&n; *&n; * DESCRIPTION:&n; *&n; * NOTES:&t;Allocates battery_info - which must be freed by the caller.&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bt_get_info
id|bt_get_info
(paren
id|BT_CONTEXT
op_star
id|battery
comma
id|BT_BATTERY_INFO
op_star
op_star
id|battery_info
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_BUFFER
id|bif_buffer
comma
id|package_format
comma
id|package_data
suffix:semicolon
id|ACPI_OBJECT
op_star
id|package
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|battery
op_logical_or
op_logical_neg
id|battery_info
op_logical_or
op_star
id|battery_info
)paren
(brace
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
)brace
id|MEMSET
c_func
(paren
op_amp
id|bif_buffer
comma
l_int|0
comma
r_sizeof
(paren
id|ACPI_BUFFER
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Evalute _BIF:&n;&t; * -------------&n;&t; * And be sure to deallocate bif_buffer.pointer!&n;&t; */
id|status
op_assign
id|bm_evaluate_object
c_func
(paren
id|battery-&gt;acpi_handle
comma
l_string|&quot;_BIF&quot;
comma
l_int|NULL
comma
op_amp
id|bif_buffer
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
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Extract Package Data:&n;&t; * ---------------------&n;&t; * Type-cast this bif_buffer to a package and use helper&n;&t; * functions to convert results into BT_BATTERY_INFO structure.&n;&t; * The first attempt is just to get the size of the package&n;&t; * data; the second gets the data (once we know the required&n;&t; * bif_buffer size).&n;&t; */
id|status
op_assign
id|bm_cast_buffer
c_func
(paren
op_amp
id|bif_buffer
comma
(paren
r_void
op_star
op_star
)paren
op_amp
id|package
comma
r_sizeof
(paren
id|ACPI_OBJECT
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
id|package_format.length
op_assign
r_sizeof
(paren
l_string|&quot;NNNNNNNNNSSSS&quot;
)paren
suffix:semicolon
id|package_format.pointer
op_assign
l_string|&quot;NNNNNNNNNSSSS&quot;
suffix:semicolon
id|MEMSET
c_func
(paren
op_amp
id|package_data
comma
l_int|0
comma
r_sizeof
(paren
id|ACPI_BUFFER
)paren
)paren
suffix:semicolon
id|status
op_assign
id|bm_extract_package_data
c_func
(paren
id|package
comma
op_amp
id|package_format
comma
op_amp
id|package_data
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
r_if
c_cond
(paren
id|status
op_eq
id|AE_OK
)paren
(brace
id|status
op_assign
id|AE_ERROR
suffix:semicolon
)brace
r_goto
id|end
suffix:semicolon
)brace
id|package_data.pointer
op_assign
id|acpi_os_callocate
c_func
(paren
id|package_data.length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|package_data.pointer
)paren
(brace
r_return
id|AE_NO_MEMORY
suffix:semicolon
)brace
id|status
op_assign
id|bm_extract_package_data
c_func
(paren
id|package
comma
op_amp
id|package_format
comma
op_amp
id|package_data
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
id|acpi_os_free
c_func
(paren
id|package_data.pointer
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
op_star
id|battery_info
op_assign
id|package_data.pointer
suffix:semicolon
id|end
suffix:colon
id|acpi_os_free
c_func
(paren
id|bif_buffer.pointer
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bt_get_status&n; *&n; * PARAMETERS:&t;&n; *&n; * RETURN:&t;&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bt_get_status
id|bt_get_status
(paren
id|BT_CONTEXT
op_star
id|battery
comma
id|BT_BATTERY_STATUS
op_star
op_star
id|battery_status
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
id|ACPI_BUFFER
id|bst_buffer
comma
id|package_format
comma
id|package_data
suffix:semicolon
id|ACPI_OBJECT
op_star
id|package
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|battery
op_logical_or
op_logical_neg
id|battery_status
op_logical_or
op_star
id|battery_status
)paren
(brace
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
)brace
id|MEMSET
c_func
(paren
op_amp
id|bst_buffer
comma
l_int|0
comma
r_sizeof
(paren
id|ACPI_BUFFER
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Evalute _BST:&n;&t; * -------------&n;&t; * And be sure to deallocate bst_buffer.pointer!&n;&t; */
id|status
op_assign
id|bm_evaluate_object
c_func
(paren
id|battery-&gt;acpi_handle
comma
l_string|&quot;_BST&quot;
comma
l_int|NULL
comma
op_amp
id|bst_buffer
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
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Extract Package Data:&n;&t; * ---------------------&n;&t; * Type-cast this bst_buffer to a package and use helper&n;&t; * functions to convert results into BT_BATTERY_STATUS structure.&n;&t; * The first attempt is just to get the size of the package data;&n;&t; * the second gets the data (once we know the required bst_buffer&n;&t; * size).&n;&t; */
id|status
op_assign
id|bm_cast_buffer
c_func
(paren
op_amp
id|bst_buffer
comma
(paren
r_void
op_star
op_star
)paren
op_amp
id|package
comma
r_sizeof
(paren
id|ACPI_OBJECT
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
id|package_format.length
op_assign
r_sizeof
(paren
l_string|&quot;NNNN&quot;
)paren
suffix:semicolon
id|package_format.pointer
op_assign
l_string|&quot;NNNN&quot;
suffix:semicolon
id|MEMSET
c_func
(paren
op_amp
id|package_data
comma
l_int|0
comma
r_sizeof
(paren
id|ACPI_BUFFER
)paren
)paren
suffix:semicolon
id|status
op_assign
id|bm_extract_package_data
c_func
(paren
id|package
comma
op_amp
id|package_format
comma
op_amp
id|package_data
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
r_if
c_cond
(paren
id|status
op_eq
id|AE_OK
)paren
(brace
id|status
op_assign
id|AE_ERROR
suffix:semicolon
)brace
r_goto
id|end
suffix:semicolon
)brace
id|package_data.pointer
op_assign
id|acpi_os_callocate
c_func
(paren
id|package_data.length
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|package_data.pointer
)paren
(brace
r_return
id|AE_NO_MEMORY
suffix:semicolon
)brace
id|status
op_assign
id|bm_extract_package_data
c_func
(paren
id|package
comma
op_amp
id|package_format
comma
op_amp
id|package_data
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
id|acpi_os_free
c_func
(paren
id|package_data.pointer
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
op_star
id|battery_status
op_assign
id|package_data.pointer
suffix:semicolon
id|end
suffix:colon
id|acpi_os_free
c_func
(paren
id|bst_buffer.pointer
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bt_check_device&n; *&n; * PARAMETERS:&t;&n; *&n; * RETURN:&t;&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bt_check_device
id|bt_check_device
(paren
id|BT_CONTEXT
op_star
id|battery
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
id|BM_DEVICE_STATUS
id|battery_status
op_assign
id|BM_STATUS_UNKNOWN
suffix:semicolon
id|u32
id|was_present
op_assign
id|FALSE
suffix:semicolon
id|BT_BATTERY_INFO
op_star
id|battery_info
op_assign
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|battery
)paren
(brace
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
)brace
id|was_present
op_assign
id|battery-&gt;is_present
suffix:semicolon
multiline_comment|/*&n;&t; * Battery Present?&n;&t; * ----------------&n;&t; * Get the device status and check if battery slot is occupied.&n;&t; */
id|status
op_assign
id|bm_get_device_status
c_func
(paren
id|battery-&gt;device_handle
comma
op_amp
id|battery_status
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
r_return
id|status
suffix:semicolon
)brace
r_if
c_cond
(paren
id|battery_status
op_amp
id|BM_STATUS_BATTERY_PRESENT
)paren
(brace
id|battery-&gt;is_present
op_assign
id|TRUE
suffix:semicolon
)brace
r_else
(brace
id|battery-&gt;is_present
op_assign
id|FALSE
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Battery Appeared?&n;&t; * -----------------&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|was_present
op_logical_and
id|battery-&gt;is_present
)paren
(brace
multiline_comment|/*&n;&t;&t; * Units of Power?&n;&t;&t; * ---------------&n;&t;&t; * Get the &squot;units of power&squot;, as we&squot;ll need this to report&n;&t;&t; * status information.&n;&t;&t; */
id|status
op_assign
id|bt_get_info
c_func
(paren
id|battery
comma
op_amp
id|battery_info
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
(brace
id|battery-&gt;power_units
op_assign
(paren
id|battery_info-&gt;power_unit
)paren
ques
c_cond
id|BT_POWER_UNITS_AMPS
suffix:colon
id|BT_POWER_UNITS_WATTS
suffix:semicolon
id|acpi_os_free
c_func
(paren
id|battery_info
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n;&t; * Battery Disappeared?&n;&t; * --------------------&n;&t; */
r_else
r_if
c_cond
(paren
id|was_present
op_logical_and
op_logical_neg
id|battery-&gt;is_present
)paren
(brace
id|battery-&gt;power_units
op_assign
id|BT_POWER_UNITS_DEFAULT
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:&t;bt_add_device&n; *&n; * PARAMETERS:&t;&n; *&n; * RETURN:&t;&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bt_add_device
id|bt_add_device
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
id|ACPI_STATUS
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
id|BT_CONTEXT
op_star
id|battery
op_assign
l_int|NULL
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
r_return
id|AE_BAD_PARAMETER
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
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Allocate a new BT_CONTEXT structure.&n;&t; */
id|battery
op_assign
id|acpi_os_callocate
c_func
(paren
r_sizeof
(paren
id|BT_CONTEXT
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|battery
)paren
(brace
r_return
id|AE_NO_MEMORY
suffix:semicolon
)brace
id|battery-&gt;device_handle
op_assign
id|device-&gt;handle
suffix:semicolon
id|battery-&gt;acpi_handle
op_assign
id|device-&gt;acpi_handle
suffix:semicolon
id|strncpy
c_func
(paren
id|battery-&gt;uid
comma
id|device-&gt;id.uid
comma
r_sizeof
(paren
id|battery-&gt;uid
)paren
)paren
suffix:semicolon
id|battery-&gt;power_units
op_assign
id|BT_POWER_UNITS_DEFAULT
suffix:semicolon
id|battery-&gt;is_present
op_assign
id|FALSE
suffix:semicolon
multiline_comment|/*&n;&t; * See if battery is really present.&n;&t; */
id|status
op_assign
id|bt_check_device
c_func
(paren
id|battery
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
id|status
op_assign
id|bt_osl_add_device
c_func
(paren
id|battery
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
op_star
id|context
op_assign
id|battery
suffix:semicolon
id|bt_print
c_func
(paren
id|battery
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
id|acpi_os_free
c_func
(paren
id|battery
)paren
suffix:semicolon
)brace
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:&t;bt_remove_device&n; *&n; * PARAMETERS:&t;&n; *&n; * RETURN:&t;&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bt_remove_device
id|bt_remove_device
(paren
r_void
op_star
op_star
id|context
)paren
(brace
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
id|BT_CONTEXT
op_star
id|battery
op_assign
l_int|NULL
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
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
)brace
id|battery
op_assign
(paren
id|BT_CONTEXT
op_star
)paren
op_star
id|context
suffix:semicolon
id|bt_osl_remove_device
c_func
(paren
id|battery
)paren
suffix:semicolon
id|acpi_os_free
c_func
(paren
id|battery
)paren
suffix:semicolon
op_star
id|context
op_assign
l_int|NULL
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/*****************************************************************************&n; *                               External Functions&n; *****************************************************************************/
multiline_comment|/*****************************************************************************&n; *&n; * FUNCTION:&t;bt_initialize&n; *&n; * PARAMETERS:&t;&lt;none&gt;&n; *&n; * RETURN:&t;&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bt_initialize
id|bt_initialize
(paren
r_void
)paren
(brace
id|ACPI_STATUS
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
multiline_comment|/*&n;&t; * Register driver for driver method battery devices.&n;&t; */
id|MEMCPY
c_func
(paren
id|criteria.hid
comma
id|BT_HID_CM_BATTERY
comma
r_sizeof
(paren
id|BT_HID_CM_BATTERY
)paren
)paren
suffix:semicolon
id|driver.notify
op_assign
op_amp
id|bt_notify
suffix:semicolon
id|driver.request
op_assign
op_amp
id|bt_request
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
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bt_terminate&n; *&n; * PARAMETERS:&t;&lt;none&gt;&n; *&n; * RETURN:&t;&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bt_terminate
id|bt_terminate
(paren
r_void
)paren
(brace
id|ACPI_STATUS
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
multiline_comment|/*&n;&t; * Unregister driver for driver method battery devices.&n;&t; */
id|MEMCPY
c_func
(paren
id|criteria.hid
comma
id|BT_HID_CM_BATTERY
comma
r_sizeof
(paren
id|BT_HID_CM_BATTERY
)paren
)paren
suffix:semicolon
id|driver.notify
op_assign
op_amp
id|bt_notify
suffix:semicolon
id|driver.request
op_assign
op_amp
id|bt_request
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
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bt_notify&n; *&n; * PARAMETERS:&t;&lt;none&gt;&n; *&n; * RETURN:&t;&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bt_notify
id|bt_notify
(paren
id|BM_NOTIFY
id|notify_type
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
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|context
)paren
(brace
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|notify_type
)paren
(brace
r_case
id|BM_NOTIFY_DEVICE_ADDED
suffix:colon
id|status
op_assign
id|bt_add_device
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
id|bt_remove_device
c_func
(paren
id|context
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BT_NOTIFY_STATUS_CHANGE
suffix:colon
id|status
op_assign
id|bt_osl_generate_event
c_func
(paren
id|notify_type
comma
(paren
(paren
id|BT_CONTEXT
op_star
)paren
op_star
id|context
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BT_NOTIFY_INFORMATION_CHANGE
suffix:colon
id|status
op_assign
id|bt_check_device
c_func
(paren
(paren
id|BT_CONTEXT
op_star
)paren
op_star
id|context
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ACPI_SUCCESS
c_func
(paren
id|status
)paren
)paren
(brace
id|status
op_assign
id|bt_osl_generate_event
c_func
(paren
id|notify_type
comma
(paren
(paren
id|BT_CONTEXT
op_star
)paren
op_star
id|context
)paren
)paren
suffix:semicolon
)brace
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
r_return
id|status
suffix:semicolon
)brace
multiline_comment|/****************************************************************************&n; *&n; * FUNCTION:&t;bt_request&n; *&n; * PARAMETERS:&t;&n; *&n; * RETURN:&t;&n; *&n; * DESCRIPTION:&n; *&n; ****************************************************************************/
id|ACPI_STATUS
DECL|function|bt_request
id|bt_request
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
id|ACPI_STATUS
id|status
op_assign
id|AE_OK
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
r_return
id|AE_BAD_PARAMETER
suffix:semicolon
multiline_comment|/*&n;&t; * Handle request:&n;&t; * ---------------&n;&t; */
r_switch
c_cond
(paren
id|request-&gt;command
)paren
(brace
r_default
suffix:colon
id|status
op_assign
id|AE_SUPPORT
suffix:semicolon
r_break
suffix:semicolon
)brace
id|request-&gt;status
op_assign
id|status
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
eof
