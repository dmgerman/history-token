multiline_comment|/*&n; *  acpi_power.c - ACPI Bus Power Management ($Revision: 39 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/compatmac.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/seq_file.h&gt;
macro_line|#include &quot;acpi_bus.h&quot;
macro_line|#include &quot;acpi_drivers.h&quot;
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_POWER_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;acpi_power&quot;
)paren
DECL|macro|ACPI_POWER_COMPONENT
mdefine_line|#define ACPI_POWER_COMPONENT&t;&t;0x00800000
DECL|macro|ACPI_POWER_CLASS
mdefine_line|#define ACPI_POWER_CLASS&t;&t;&quot;power_resource&quot;
DECL|macro|ACPI_POWER_DRIVER_NAME
mdefine_line|#define ACPI_POWER_DRIVER_NAME&t;&t;&quot;ACPI Power Resource Driver&quot;
DECL|macro|ACPI_POWER_DEVICE_NAME
mdefine_line|#define ACPI_POWER_DEVICE_NAME&t;&t;&quot;Power Resource&quot;
DECL|macro|ACPI_POWER_FILE_INFO
mdefine_line|#define ACPI_POWER_FILE_INFO&t;&t;&quot;info&quot;
DECL|macro|ACPI_POWER_FILE_STATUS
mdefine_line|#define ACPI_POWER_FILE_STATUS&t;&t;&quot;state&quot;
DECL|macro|ACPI_POWER_RESOURCE_STATE_OFF
mdefine_line|#define ACPI_POWER_RESOURCE_STATE_OFF&t;0x00
DECL|macro|ACPI_POWER_RESOURCE_STATE_ON
mdefine_line|#define ACPI_POWER_RESOURCE_STATE_ON&t;0x01
DECL|macro|ACPI_POWER_RESOURCE_STATE_UNKNOWN
mdefine_line|#define ACPI_POWER_RESOURCE_STATE_UNKNOWN 0xFF
r_int
id|acpi_power_add
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_int
id|acpi_power_remove
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|type
)paren
suffix:semicolon
r_static
r_int
id|acpi_power_open_fs
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
suffix:semicolon
DECL|variable|acpi_power_driver
r_static
r_struct
id|acpi_driver
id|acpi_power_driver
op_assign
(brace
dot
id|name
op_assign
id|ACPI_POWER_DRIVER_NAME
comma
dot
r_class
op_assign
id|ACPI_POWER_CLASS
comma
dot
id|ids
op_assign
id|ACPI_POWER_HID
comma
dot
id|ops
op_assign
(brace
dot
id|add
op_assign
id|acpi_power_add
comma
dot
id|remove
op_assign
id|acpi_power_remove
comma
)brace
comma
)brace
suffix:semicolon
DECL|struct|acpi_power_resource
r_struct
id|acpi_power_resource
(brace
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
DECL|member|name
id|acpi_bus_id
id|name
suffix:semicolon
DECL|member|system_level
id|u32
id|system_level
suffix:semicolon
DECL|member|order
id|u32
id|order
suffix:semicolon
DECL|member|state
r_int
id|state
suffix:semicolon
DECL|member|references
r_int
id|references
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|acpi_power_resource_list
r_static
r_struct
id|list_head
id|acpi_power_resource_list
suffix:semicolon
DECL|variable|acpi_power_fops
r_static
r_struct
id|file_operations
id|acpi_power_fops
op_assign
(brace
dot
id|open
op_assign
id|acpi_power_open_fs
comma
dot
id|read
op_assign
id|seq_read
comma
dot
id|llseek
op_assign
id|seq_lseek
comma
dot
id|release
op_assign
id|single_release
comma
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                             Power Resource Management&n;   -------------------------------------------------------------------------- */
r_static
r_int
DECL|function|acpi_power_get_context
id|acpi_power_get_context
(paren
id|acpi_handle
id|handle
comma
r_struct
id|acpi_power_resource
op_star
op_star
id|resource
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_device
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_get_context&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resource
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|result
op_assign
id|acpi_bus_get_device
c_func
(paren
id|handle
comma
op_amp
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Error getting context [%p]&bslash;n&quot;
comma
id|handle
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
op_star
id|resource
op_assign
(paren
r_struct
id|acpi_power_resource
op_star
)paren
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resource
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_power_get_state
id|acpi_power_get_state
(paren
r_struct
id|acpi_power_resource
op_star
id|resource
)paren
(brace
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_int
r_int
id|sta
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_get_state&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resource
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|status
op_assign
id|acpi_evaluate_integer
c_func
(paren
id|resource-&gt;handle
comma
l_string|&quot;_STA&quot;
comma
l_int|NULL
comma
op_amp
id|sta
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
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sta
op_amp
l_int|0x01
)paren
id|resource-&gt;state
op_assign
id|ACPI_POWER_RESOURCE_STATE_ON
suffix:semicolon
r_else
id|resource-&gt;state
op_assign
id|ACPI_POWER_RESOURCE_STATE_OFF
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Resource [%s] is %s&bslash;n&quot;
comma
id|resource-&gt;name
comma
id|resource-&gt;state
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_power_get_list_state
id|acpi_power_get_list_state
(paren
r_struct
id|acpi_handle_list
op_star
id|list
comma
r_int
op_star
id|state
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_power_resource
op_star
id|resource
op_assign
l_int|NULL
suffix:semicolon
id|u32
id|i
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_get_list_state&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|list
op_logical_or
op_logical_neg
id|state
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
multiline_comment|/* The state of the list is &squot;on&squot; IFF all resources are &squot;on&squot;. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|list-&gt;count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|result
op_assign
id|acpi_power_get_context
c_func
(paren
id|list-&gt;handles
(braket
id|i
)braket
comma
op_amp
id|resource
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
id|result
op_assign
id|acpi_power_get_state
c_func
(paren
id|resource
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
op_star
id|state
op_assign
id|resource-&gt;state
suffix:semicolon
r_if
c_cond
(paren
op_star
id|state
op_ne
id|ACPI_POWER_RESOURCE_STATE_ON
)paren
r_break
suffix:semicolon
)brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Resource list is %s&bslash;n&quot;
comma
op_star
id|state
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_power_on
id|acpi_power_on
(paren
id|acpi_handle
id|handle
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_device
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_power_resource
op_star
id|resource
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_on&quot;
)paren
suffix:semicolon
id|result
op_assign
id|acpi_power_get_context
c_func
(paren
id|handle
comma
op_amp
id|resource
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
id|resource-&gt;references
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|resource-&gt;references
OG
l_int|1
)paren
op_logical_or
(paren
id|resource-&gt;state
op_eq
id|ACPI_POWER_RESOURCE_STATE_ON
)paren
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Resource [%s] already on&bslash;n&quot;
comma
id|resource-&gt;name
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
id|resource-&gt;handle
comma
l_string|&quot;_ON&quot;
comma
l_int|NULL
comma
l_int|NULL
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
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|result
op_assign
id|acpi_power_get_state
c_func
(paren
id|resource
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resource-&gt;state
op_ne
id|ACPI_POWER_RESOURCE_STATE_ON
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENOEXEC
)paren
suffix:semicolon
multiline_comment|/* Update the power resource&squot;s _device_ power state */
id|result
op_assign
id|acpi_bus_get_device
c_func
(paren
id|resource-&gt;handle
comma
op_amp
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
id|device-&gt;power.state
op_assign
id|ACPI_STATE_D0
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Resource [%s] turned on&bslash;n&quot;
comma
id|resource-&gt;name
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_power_off_device
id|acpi_power_off_device
(paren
id|acpi_handle
id|handle
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_device
op_star
id|device
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|acpi_power_resource
op_star
id|resource
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_off_device&quot;
)paren
suffix:semicolon
id|result
op_assign
id|acpi_power_get_context
c_func
(paren
id|handle
comma
op_amp
id|resource
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resource-&gt;references
)paren
id|resource-&gt;references
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|resource-&gt;references
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Resource [%s] is still in use, dereferencing&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|resource-&gt;state
op_eq
id|ACPI_POWER_RESOURCE_STATE_OFF
)paren
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Resource [%s] already off&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
id|resource-&gt;handle
comma
l_string|&quot;_OFF&quot;
comma
l_int|NULL
comma
l_int|NULL
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
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|result
op_assign
id|acpi_power_get_state
c_func
(paren
id|resource
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|resource-&gt;state
op_ne
id|ACPI_POWER_RESOURCE_STATE_OFF
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENOEXEC
)paren
suffix:semicolon
multiline_comment|/* Update the power resource&squot;s _device_ power state */
id|result
op_assign
id|acpi_bus_get_device
c_func
(paren
id|resource-&gt;handle
comma
op_amp
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
id|device-&gt;power.state
op_assign
id|ACPI_STATE_D3
suffix:semicolon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Resource [%s] turned off&bslash;n&quot;
comma
id|resource-&gt;name
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                             Device Power Management&n;   -------------------------------------------------------------------------- */
r_int
DECL|function|acpi_power_get_inferred_state
id|acpi_power_get_inferred_state
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_handle_list
op_star
id|list
op_assign
l_int|NULL
suffix:semicolon
r_int
id|list_state
op_assign
l_int|0
suffix:semicolon
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_get_inferred_state&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|device-&gt;power.state
op_assign
id|ACPI_STATE_UNKNOWN
suffix:semicolon
multiline_comment|/*&n;&t; * We know a device&squot;s inferred power state when all the resources&n;&t; * required for a given D-state are &squot;on&squot;.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
id|ACPI_STATE_D0
suffix:semicolon
id|i
OL
id|ACPI_STATE_D3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|list
op_assign
op_amp
id|device-&gt;power.states
(braket
id|i
)braket
dot
id|resources
suffix:semicolon
r_if
c_cond
(paren
id|list-&gt;count
OL
l_int|1
)paren
r_continue
suffix:semicolon
id|result
op_assign
id|acpi_power_get_list_state
c_func
(paren
id|list
comma
op_amp
id|list_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
r_if
c_cond
(paren
id|list_state
op_eq
id|ACPI_POWER_RESOURCE_STATE_ON
)paren
(brace
id|device-&gt;power.state
op_assign
id|i
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
)brace
id|device-&gt;power.state
op_assign
id|ACPI_STATE_D3
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
DECL|function|acpi_power_transition
id|acpi_power_transition
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|state
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_handle_list
op_star
id|cl
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Current Resources */
r_struct
id|acpi_handle_list
op_star
id|tl
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* Target Resources */
r_int
id|i
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_transition&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
op_logical_or
(paren
id|state
OL
id|ACPI_STATE_D0
)paren
op_logical_or
(paren
id|state
OG
id|ACPI_STATE_D3
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|cl
op_assign
op_amp
id|device-&gt;power.states
(braket
id|device-&gt;power.state
)braket
dot
id|resources
suffix:semicolon
id|tl
op_assign
op_amp
id|device-&gt;power.states
(braket
id|state
)braket
dot
id|resources
suffix:semicolon
id|device-&gt;power.state
op_assign
id|ACPI_STATE_UNKNOWN
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cl-&gt;count
op_logical_and
op_logical_neg
id|tl-&gt;count
)paren
(brace
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
multiline_comment|/* TBD: Resources must be ordered. */
multiline_comment|/*&n;&t; * First we reference all power resources required in the target list&n;&t; * (e.g. so the device doesn&squot;t loose power while transitioning).&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|tl-&gt;count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|result
op_assign
id|acpi_power_on
c_func
(paren
id|tl-&gt;handles
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|end
suffix:semicolon
)brace
id|device-&gt;power.state
op_assign
id|state
suffix:semicolon
multiline_comment|/*&n;&t; * Then we dereference all power resources used in the current list.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|cl-&gt;count
suffix:semicolon
id|i
op_increment
)paren
(brace
id|result
op_assign
id|acpi_power_off_device
c_func
(paren
id|cl-&gt;handles
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|end
suffix:semicolon
)brace
id|end
suffix:colon
r_if
c_cond
(paren
id|result
)paren
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_WARN
comma
l_string|&quot;Error transitioning device [%s] to D%d&bslash;n&quot;
comma
id|device-&gt;pnp.bus_id
comma
id|state
)paren
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                              FS Interface (/proc)&n;   -------------------------------------------------------------------------- */
DECL|variable|acpi_power_dir
r_struct
id|proc_dir_entry
op_star
id|acpi_power_dir
op_assign
l_int|NULL
suffix:semicolon
DECL|function|acpi_power_seq_show
r_static
r_int
id|acpi_power_seq_show
c_func
(paren
r_struct
id|seq_file
op_star
id|seq
comma
r_void
op_star
id|offset
)paren
(brace
r_struct
id|acpi_power_resource
op_star
id|resource
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_seq_show&quot;
)paren
suffix:semicolon
id|resource
op_assign
(paren
r_struct
id|acpi_power_resource
op_star
)paren
id|seq
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resource
)paren
r_goto
id|end
suffix:semicolon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;state:                   &quot;
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|resource-&gt;state
)paren
(brace
r_case
id|ACPI_POWER_RESOURCE_STATE_ON
suffix:colon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;on&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_POWER_RESOURCE_STATE_OFF
suffix:colon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;off&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|seq_puts
c_func
(paren
id|seq
comma
l_string|&quot;unknown&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|seq_printf
c_func
(paren
id|seq
comma
l_string|&quot;system level:            S%d&bslash;n&quot;
l_string|&quot;order:                   %d&bslash;n&quot;
l_string|&quot;reference count:         %d&bslash;n&quot;
comma
id|resource-&gt;system_level
comma
id|resource-&gt;order
comma
id|resource-&gt;references
)paren
suffix:semicolon
id|end
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|acpi_power_open_fs
r_static
r_int
id|acpi_power_open_fs
c_func
(paren
r_struct
id|inode
op_star
id|inode
comma
r_struct
id|file
op_star
id|file
)paren
(brace
r_return
id|single_open
c_func
(paren
id|file
comma
id|acpi_power_seq_show
comma
id|PDE
c_func
(paren
id|inode
)paren
op_member_access_from_pointer
id|data
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_power_add_fs
id|acpi_power_add_fs
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
r_struct
id|proc_dir_entry
op_star
id|entry
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_add_fs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_device_dir
c_func
(paren
id|device
)paren
)paren
(brace
id|acpi_device_dir
c_func
(paren
id|device
)paren
op_assign
id|proc_mkdir
c_func
(paren
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|acpi_power_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_device_dir
c_func
(paren
id|device
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
multiline_comment|/* &squot;status&squot; [R] */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
id|ACPI_POWER_FILE_STATUS
comma
id|S_IRUGO
comma
id|acpi_device_dir
c_func
(paren
id|device
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|entry
)paren
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unable to create &squot;%s&squot; fs entry&bslash;n&quot;
comma
id|ACPI_POWER_FILE_STATUS
)paren
)paren
suffix:semicolon
r_else
(brace
id|entry-&gt;proc_fops
op_assign
op_amp
id|acpi_power_fops
suffix:semicolon
id|entry-&gt;data
op_assign
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
)brace
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_power_remove_fs
id|acpi_power_remove_fs
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_remove_fs&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_device_dir
c_func
(paren
id|device
)paren
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|acpi_power_dir
)paren
suffix:semicolon
id|acpi_device_dir
c_func
(paren
id|device
)paren
op_assign
l_int|NULL
suffix:semicolon
)brace
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                                Driver Interface&n;   -------------------------------------------------------------------------- */
r_int
DECL|function|acpi_power_add
id|acpi_power_add
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|acpi_status
id|status
op_assign
id|AE_OK
suffix:semicolon
r_struct
id|acpi_power_resource
op_star
id|resource
op_assign
l_int|NULL
suffix:semicolon
id|acpi_object
id|acpi_object
suffix:semicolon
id|acpi_buffer
id|buffer
op_assign
(brace
r_sizeof
(paren
id|acpi_object
)paren
comma
op_amp
id|acpi_object
)brace
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_add&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|resource
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_power_resource
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|resource
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENOMEM
)paren
suffix:semicolon
id|memset
c_func
(paren
id|resource
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_power_resource
)paren
)paren
suffix:semicolon
id|resource-&gt;handle
op_assign
id|device-&gt;handle
suffix:semicolon
id|sprintf
c_func
(paren
id|resource-&gt;name
comma
l_string|&quot;%s&quot;
comma
id|device-&gt;pnp.bus_id
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|acpi_device_name
c_func
(paren
id|device
)paren
comma
l_string|&quot;%s&quot;
comma
id|ACPI_POWER_DEVICE_NAME
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|acpi_device_class
c_func
(paren
id|device
)paren
comma
l_string|&quot;%s&quot;
comma
id|ACPI_POWER_CLASS
)paren
suffix:semicolon
id|acpi_driver_data
c_func
(paren
id|device
)paren
op_assign
id|resource
suffix:semicolon
multiline_comment|/* Evalute the object to get the system level and resource order. */
id|status
op_assign
id|acpi_evaluate_object
c_func
(paren
id|resource-&gt;handle
comma
l_int|NULL
comma
l_int|NULL
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
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|resource-&gt;system_level
op_assign
id|acpi_object.power_resource.system_level
suffix:semicolon
id|resource-&gt;order
op_assign
id|acpi_object.power_resource.resource_order
suffix:semicolon
id|result
op_assign
id|acpi_power_get_state
c_func
(paren
id|resource
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|end
suffix:semicolon
r_switch
c_cond
(paren
id|resource-&gt;state
)paren
(brace
r_case
id|ACPI_POWER_RESOURCE_STATE_ON
suffix:colon
id|device-&gt;power.state
op_assign
id|ACPI_STATE_D0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_POWER_RESOURCE_STATE_OFF
suffix:colon
id|device-&gt;power.state
op_assign
id|ACPI_STATE_D3
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|device-&gt;power.state
op_assign
id|ACPI_STATE_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
id|result
op_assign
id|acpi_power_add_fs
c_func
(paren
id|device
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
)paren
r_goto
id|end
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;%s [%s] (%s)&bslash;n&quot;
comma
id|acpi_device_name
c_func
(paren
id|device
)paren
comma
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|resource-&gt;state
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
id|end
suffix:colon
r_if
c_cond
(paren
id|result
)paren
id|kfree
c_func
(paren
id|resource
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_int
DECL|function|acpi_power_remove
id|acpi_power_remove
(paren
r_struct
id|acpi_device
op_star
id|device
comma
r_int
id|type
)paren
(brace
r_struct
id|acpi_power_resource
op_star
id|resource
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_remove&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|device
op_logical_or
op_logical_neg
id|acpi_driver_data
c_func
(paren
id|device
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|resource
op_assign
(paren
r_struct
id|acpi_power_resource
op_star
)paren
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
id|acpi_power_remove_fs
c_func
(paren
id|device
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|resource
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|acpi_power_init
r_static
r_int
id|__init
id|acpi_power_init
(paren
r_void
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_power_init&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|acpi_disabled
)paren
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|INIT_LIST_HEAD
c_func
(paren
op_amp
id|acpi_power_resource_list
)paren
suffix:semicolon
id|acpi_power_dir
op_assign
id|proc_mkdir
c_func
(paren
id|ACPI_POWER_CLASS
comma
id|acpi_root_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_power_dir
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|result
op_assign
id|acpi_bus_register_driver
c_func
(paren
op_amp
id|acpi_power_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|result
OL
l_int|0
)paren
(brace
id|remove_proc_entry
c_func
(paren
id|ACPI_POWER_CLASS
comma
id|acpi_root_dir
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
)brace
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
DECL|variable|acpi_power_init
id|subsys_initcall
c_func
(paren
id|acpi_power_init
)paren
suffix:semicolon
eof
