multiline_comment|/*&n; *  acpi_fan.c - ACPI Fan Driver ($Revision: 29 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;acpi/acpi_bus.h&gt;
macro_line|#include &lt;acpi/acpi_drivers.h&gt;
DECL|macro|ACPI_FAN_COMPONENT
mdefine_line|#define ACPI_FAN_COMPONENT&t;&t;0x00200000
DECL|macro|ACPI_FAN_CLASS
mdefine_line|#define ACPI_FAN_CLASS&t;&t;&t;&quot;fan&quot;
DECL|macro|ACPI_FAN_HID
mdefine_line|#define ACPI_FAN_HID&t;&t;&t;&quot;PNP0C0B&quot;
DECL|macro|ACPI_FAN_DRIVER_NAME
mdefine_line|#define ACPI_FAN_DRIVER_NAME&t;&t;&quot;ACPI Fan Driver&quot;
DECL|macro|ACPI_FAN_DEVICE_NAME
mdefine_line|#define ACPI_FAN_DEVICE_NAME&t;&t;&quot;Fan&quot;
DECL|macro|ACPI_FAN_FILE_STATE
mdefine_line|#define ACPI_FAN_FILE_STATE&t;&t;&quot;state&quot;
DECL|macro|ACPI_FAN_NOTIFY_STATUS
mdefine_line|#define ACPI_FAN_NOTIFY_STATUS&t;&t;0x80
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_FAN_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;acpi_fan&quot;
)paren
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Paul Diefenbaugh&quot;
)paren
suffix:semicolon
DECL|variable|ACPI_FAN_DRIVER_NAME
id|MODULE_DESCRIPTION
c_func
(paren
id|ACPI_FAN_DRIVER_NAME
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_int
id|acpi_fan_add
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_int
id|acpi_fan_remove
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
DECL|variable|acpi_fan_driver
r_static
r_struct
id|acpi_driver
id|acpi_fan_driver
op_assign
(brace
dot
id|name
op_assign
id|ACPI_FAN_DRIVER_NAME
comma
dot
r_class
op_assign
id|ACPI_FAN_CLASS
comma
dot
id|ids
op_assign
id|ACPI_FAN_HID
comma
dot
id|ops
op_assign
(brace
dot
id|add
op_assign
id|acpi_fan_add
comma
dot
id|remove
op_assign
id|acpi_fan_remove
comma
)brace
comma
)brace
suffix:semicolon
DECL|struct|acpi_fan
r_struct
id|acpi_fan
(brace
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                              FS Interface (/proc)&n;   -------------------------------------------------------------------------- */
DECL|variable|acpi_fan_dir
r_struct
id|proc_dir_entry
op_star
id|acpi_fan_dir
suffix:semicolon
r_static
r_int
DECL|function|acpi_fan_read_state
id|acpi_fan_read_state
(paren
r_char
op_star
id|page
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|off
comma
r_int
id|count
comma
r_int
op_star
id|eof
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|acpi_fan
op_star
id|fan
op_assign
(paren
r_struct
id|acpi_fan
op_star
)paren
id|data
suffix:semicolon
r_char
op_star
id|p
op_assign
id|page
suffix:semicolon
r_int
id|len
op_assign
l_int|0
suffix:semicolon
r_int
id|state
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_fan_read_state&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fan
op_logical_or
(paren
id|off
op_ne
l_int|0
)paren
)paren
r_goto
id|end
suffix:semicolon
r_if
c_cond
(paren
id|acpi_bus_get_power
c_func
(paren
id|fan-&gt;handle
comma
op_amp
id|state
)paren
)paren
r_goto
id|end
suffix:semicolon
id|p
op_add_assign
id|sprintf
c_func
(paren
id|p
comma
l_string|&quot;status:                  %s&bslash;n&quot;
comma
op_logical_neg
id|state
ques
c_cond
l_string|&quot;on&quot;
suffix:colon
l_string|&quot;off&quot;
)paren
suffix:semicolon
id|end
suffix:colon
id|len
op_assign
(paren
id|p
op_minus
id|page
)paren
suffix:semicolon
r_if
c_cond
(paren
id|len
op_le
id|off
op_plus
id|count
)paren
op_star
id|eof
op_assign
l_int|1
suffix:semicolon
op_star
id|start
op_assign
id|page
op_plus
id|off
suffix:semicolon
id|len
op_sub_assign
id|off
suffix:semicolon
r_if
c_cond
(paren
id|len
OG
id|count
)paren
id|len
op_assign
id|count
suffix:semicolon
r_if
c_cond
(paren
id|len
OL
l_int|0
)paren
id|len
op_assign
l_int|0
suffix:semicolon
id|return_VALUE
c_func
(paren
id|len
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_fan_write_state
id|acpi_fan_write_state
(paren
r_struct
id|file
op_star
id|file
comma
r_const
r_char
op_star
id|buffer
comma
r_int
r_int
id|count
comma
r_void
op_star
id|data
)paren
(brace
r_int
id|result
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_fan
op_star
id|fan
op_assign
(paren
r_struct
id|acpi_fan
op_star
)paren
id|data
suffix:semicolon
r_char
id|state_string
(braket
l_int|12
)braket
op_assign
(brace
l_char|&squot;&bslash;0&squot;
)brace
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_fan_write_state&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fan
op_logical_or
(paren
id|count
OG
r_sizeof
(paren
id|state_string
)paren
op_minus
l_int|1
)paren
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
id|copy_from_user
c_func
(paren
id|state_string
comma
id|buffer
comma
id|count
)paren
)paren
id|return_VALUE
c_func
(paren
op_minus
id|EFAULT
)paren
suffix:semicolon
id|state_string
(braket
id|count
)braket
op_assign
l_char|&squot;&bslash;0&squot;
suffix:semicolon
id|result
op_assign
id|acpi_bus_set_power
c_func
(paren
id|fan-&gt;handle
comma
id|simple_strtoul
c_func
(paren
id|state_string
comma
l_int|NULL
comma
l_int|0
)paren
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
id|return_VALUE
c_func
(paren
id|count
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|acpi_fan_add_fs
id|acpi_fan_add_fs
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
l_string|&quot;acpi_fan_add_fs&quot;
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
id|acpi_fan_dir
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
id|acpi_device_dir
c_func
(paren
id|device
)paren
op_member_access_from_pointer
id|owner
op_assign
id|THIS_MODULE
suffix:semicolon
)brace
multiline_comment|/* &squot;status&squot; [R/W] */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
id|ACPI_FAN_FILE_STATE
comma
id|S_IFREG
op_or
id|S_IRUGO
op_or
id|S_IWUSR
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
id|ACPI_FAN_FILE_STATE
)paren
)paren
suffix:semicolon
r_else
(brace
id|entry-&gt;read_proc
op_assign
id|acpi_fan_read_state
suffix:semicolon
id|entry-&gt;write_proc
op_assign
id|acpi_fan_write_state
suffix:semicolon
id|entry-&gt;data
op_assign
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
id|entry-&gt;owner
op_assign
id|THIS_MODULE
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
DECL|function|acpi_fan_remove_fs
id|acpi_fan_remove_fs
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
l_string|&quot;acpi_fan_remove_fs&quot;
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
id|acpi_fan_dir
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
multiline_comment|/* --------------------------------------------------------------------------&n;                                 Driver Interface&n;   -------------------------------------------------------------------------- */
r_int
DECL|function|acpi_fan_add
id|acpi_fan_add
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
id|acpi_fan
op_star
id|fan
op_assign
l_int|NULL
suffix:semicolon
r_int
id|state
op_assign
l_int|0
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_fan_add&quot;
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
id|fan
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_fan
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|fan
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
id|fan
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_fan
)paren
)paren
suffix:semicolon
id|fan-&gt;handle
op_assign
id|device-&gt;handle
suffix:semicolon
id|strcpy
c_func
(paren
id|acpi_device_name
c_func
(paren
id|device
)paren
comma
id|ACPI_FAN_DEVICE_NAME
)paren
suffix:semicolon
id|strcpy
c_func
(paren
id|acpi_device_class
c_func
(paren
id|device
)paren
comma
id|ACPI_FAN_CLASS
)paren
suffix:semicolon
id|acpi_driver_data
c_func
(paren
id|device
)paren
op_assign
id|fan
suffix:semicolon
id|result
op_assign
id|acpi_bus_get_power
c_func
(paren
id|fan-&gt;handle
comma
op_amp
id|state
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
id|ACPI_DB_ERROR
comma
l_string|&quot;Error reading power state&bslash;n&quot;
)paren
)paren
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|result
op_assign
id|acpi_fan_add_fs
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
op_logical_neg
id|device-&gt;power.state
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
id|fan
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
DECL|function|acpi_fan_remove
id|acpi_fan_remove
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
id|acpi_fan
op_star
id|fan
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_fan_remove&quot;
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
id|fan
op_assign
(paren
r_struct
id|acpi_fan
op_star
)paren
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
id|acpi_fan_remove_fs
c_func
(paren
id|device
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|fan
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
r_int
id|__init
DECL|function|acpi_fan_init
id|acpi_fan_init
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
l_string|&quot;acpi_fan_init&quot;
)paren
suffix:semicolon
id|acpi_fan_dir
op_assign
id|proc_mkdir
c_func
(paren
id|ACPI_FAN_CLASS
comma
id|acpi_root_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_fan_dir
)paren
id|return_VALUE
c_func
(paren
op_minus
id|ENODEV
)paren
suffix:semicolon
id|acpi_fan_dir-&gt;owner
op_assign
id|THIS_MODULE
suffix:semicolon
id|result
op_assign
id|acpi_bus_register_driver
c_func
(paren
op_amp
id|acpi_fan_driver
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
id|ACPI_FAN_CLASS
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
r_void
id|__exit
DECL|function|acpi_fan_exit
id|acpi_fan_exit
(paren
r_void
)paren
(brace
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_fan_exit&quot;
)paren
suffix:semicolon
id|acpi_bus_unregister_driver
c_func
(paren
op_amp
id|acpi_fan_driver
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|ACPI_FAN_CLASS
comma
id|acpi_root_dir
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
DECL|variable|acpi_fan_init
id|module_init
c_func
(paren
id|acpi_fan_init
)paren
suffix:semicolon
DECL|variable|acpi_fan_exit
id|module_exit
c_func
(paren
id|acpi_fan_exit
)paren
suffix:semicolon
eof
