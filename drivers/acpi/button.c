multiline_comment|/*&n; *  acpi_button.c - ACPI Button Driver ($Revision: 30 $)&n; *&n; *  Copyright (C) 2001, 2002 Andy Grover &lt;andrew.grover@intel.com&gt;&n; *  Copyright (C) 2001, 2002 Paul Diefenbaugh &lt;paul.s.diefenbaugh@intel.com&gt;&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or (at&n; *  your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful, but&n; *  WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU&n; *  General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License along&n; *  with this program; if not, write to the Free Software Foundation, Inc.,&n; *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.&n; *&n; * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/compatmac.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &quot;acpi_bus.h&quot;
macro_line|#include &quot;acpi_drivers.h&quot;
DECL|macro|ACPI_BUTTON_COMPONENT
mdefine_line|#define ACPI_BUTTON_COMPONENT&t;&t;0x00080000
DECL|macro|ACPI_BUTTON_DRIVER_NAME
mdefine_line|#define ACPI_BUTTON_DRIVER_NAME&t;&t;&quot;ACPI Button Driver&quot;
DECL|macro|ACPI_BUTTON_CLASS
mdefine_line|#define ACPI_BUTTON_CLASS&t;&t;&quot;button&quot;
DECL|macro|ACPI_BUTTON_FILE_INFO
mdefine_line|#define ACPI_BUTTON_FILE_INFO&t;&t;&quot;info&quot;
DECL|macro|ACPI_BUTTON_TYPE_UNKNOWN
mdefine_line|#define ACPI_BUTTON_TYPE_UNKNOWN&t;0x00
DECL|macro|ACPI_BUTTON_NOTIFY_STATUS
mdefine_line|#define ACPI_BUTTON_NOTIFY_STATUS&t;0x80
DECL|macro|ACPI_BUTTON_SUBCLASS_POWER
mdefine_line|#define ACPI_BUTTON_SUBCLASS_POWER&t;&quot;power&quot;
DECL|macro|ACPI_BUTTON_HID_POWER
mdefine_line|#define ACPI_BUTTON_HID_POWER&t;&t;&quot;PNP0C0C&quot;&t;
DECL|macro|ACPI_BUTTON_DEVICE_NAME_POWER
mdefine_line|#define ACPI_BUTTON_DEVICE_NAME_POWER&t;&quot;Power Button (CM)&quot;
DECL|macro|ACPI_BUTTON_DEVICE_NAME_POWERF
mdefine_line|#define ACPI_BUTTON_DEVICE_NAME_POWERF&t;&quot;Power Button (FF)&quot;
DECL|macro|ACPI_BUTTON_TYPE_POWER
mdefine_line|#define ACPI_BUTTON_TYPE_POWER&t;&t;0x01
DECL|macro|ACPI_BUTTON_TYPE_POWERF
mdefine_line|#define ACPI_BUTTON_TYPE_POWERF&t;&t;0x02
DECL|macro|ACPI_BUTTON_SUBCLASS_SLEEP
mdefine_line|#define ACPI_BUTTON_SUBCLASS_SLEEP&t;&quot;sleep&quot;
DECL|macro|ACPI_BUTTON_HID_SLEEP
mdefine_line|#define ACPI_BUTTON_HID_SLEEP&t;&t;&quot;PNP0C0E&quot;
DECL|macro|ACPI_BUTTON_DEVICE_NAME_SLEEP
mdefine_line|#define ACPI_BUTTON_DEVICE_NAME_SLEEP&t;&quot;Sleep Button (CM)&quot;
DECL|macro|ACPI_BUTTON_DEVICE_NAME_SLEEPF
mdefine_line|#define ACPI_BUTTON_DEVICE_NAME_SLEEPF&t;&quot;Sleep Button (FF)&quot;
DECL|macro|ACPI_BUTTON_TYPE_SLEEP
mdefine_line|#define ACPI_BUTTON_TYPE_SLEEP&t;&t;0x03
DECL|macro|ACPI_BUTTON_TYPE_SLEEPF
mdefine_line|#define ACPI_BUTTON_TYPE_SLEEPF&t;&t;0x04
DECL|macro|ACPI_BUTTON_SUBCLASS_LID
mdefine_line|#define ACPI_BUTTON_SUBCLASS_LID&t;&quot;lid&quot;
DECL|macro|ACPI_BUTTON_HID_LID
mdefine_line|#define ACPI_BUTTON_HID_LID&t;&t;&quot;PNP0C0D&quot;
DECL|macro|ACPI_BUTTON_DEVICE_NAME_LID
mdefine_line|#define ACPI_BUTTON_DEVICE_NAME_LID&t;&quot;Lid Switch&quot;
DECL|macro|ACPI_BUTTON_TYPE_LID
mdefine_line|#define ACPI_BUTTON_TYPE_LID&t;&t;0x05
DECL|macro|_COMPONENT
mdefine_line|#define _COMPONENT&t;&t;ACPI_BUTTON_COMPONENT
id|ACPI_MODULE_NAME
(paren
l_string|&quot;acpi_button&quot;
)paren
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Paul Diefenbaugh&quot;
)paren
suffix:semicolon
DECL|variable|ACPI_BUTTON_DRIVER_NAME
id|MODULE_DESCRIPTION
c_func
(paren
id|ACPI_BUTTON_DRIVER_NAME
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
r_int
id|acpi_button_add
(paren
r_struct
id|acpi_device
op_star
id|device
)paren
suffix:semicolon
r_int
id|acpi_button_remove
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
DECL|variable|acpi_button_driver
r_static
r_struct
id|acpi_driver
id|acpi_button_driver
op_assign
(brace
dot
id|name
op_assign
id|ACPI_BUTTON_DRIVER_NAME
comma
dot
r_class
op_assign
id|ACPI_BUTTON_CLASS
comma
dot
id|ids
op_assign
l_string|&quot;ACPI_FPB,ACPI_FSB,PNP0C0D,PNP0C0C,PNP0C0E&quot;
comma
dot
id|ops
op_assign
(brace
dot
id|add
op_assign
id|acpi_button_add
comma
dot
id|remove
op_assign
id|acpi_button_remove
comma
)brace
comma
)brace
suffix:semicolon
DECL|struct|acpi_button
r_struct
id|acpi_button
(brace
DECL|member|handle
id|acpi_handle
id|handle
suffix:semicolon
DECL|member|device
r_struct
id|acpi_device
op_star
id|device
suffix:semicolon
multiline_comment|/* Fixed button kludge */
DECL|member|type
id|u8
id|type
suffix:semicolon
DECL|member|pushed
r_int
r_int
id|pushed
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* --------------------------------------------------------------------------&n;                              FS Interface (/proc)&n;   -------------------------------------------------------------------------- */
DECL|variable|acpi_button_dir
r_static
r_struct
id|proc_dir_entry
op_star
id|acpi_button_dir
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
DECL|function|acpi_button_read_info
id|acpi_button_read_info
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
id|acpi_button
op_star
id|button
op_assign
(paren
r_struct
id|acpi_button
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
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_button_read_info&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|button
op_logical_or
op_logical_neg
id|button-&gt;device
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
l_string|&quot;type:                    %s&bslash;n&quot;
comma
id|acpi_device_name
c_func
(paren
id|button-&gt;device
)paren
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
DECL|function|acpi_button_add_fs
id|acpi_button_add_fs
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
r_struct
id|acpi_button
op_star
id|button
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_button_add_fs&quot;
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
id|button
op_assign
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|button-&gt;type
)paren
(brace
r_case
id|ACPI_BUTTON_TYPE_POWER
suffix:colon
r_case
id|ACPI_BUTTON_TYPE_POWERF
suffix:colon
id|entry
op_assign
id|proc_mkdir
c_func
(paren
id|ACPI_BUTTON_SUBCLASS_POWER
comma
id|acpi_button_dir
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_BUTTON_TYPE_SLEEP
suffix:colon
r_case
id|ACPI_BUTTON_TYPE_SLEEPF
suffix:colon
id|entry
op_assign
id|proc_mkdir
c_func
(paren
id|ACPI_BUTTON_SUBCLASS_SLEEP
comma
id|acpi_button_dir
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_BUTTON_TYPE_LID
suffix:colon
id|entry
op_assign
id|proc_mkdir
c_func
(paren
id|ACPI_BUTTON_SUBCLASS_LID
comma
id|acpi_button_dir
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
id|entry
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
multiline_comment|/* &squot;info&squot; [R] */
id|entry
op_assign
id|create_proc_entry
c_func
(paren
id|ACPI_BUTTON_FILE_INFO
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
id|ACPI_BUTTON_FILE_INFO
)paren
)paren
suffix:semicolon
r_else
(brace
id|entry-&gt;read_proc
op_assign
id|acpi_button_read_info
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
DECL|function|acpi_button_remove_fs
id|acpi_button_remove_fs
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
l_string|&quot;acpi_button_remove_fs&quot;
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
id|remove_proc_entry
c_func
(paren
id|acpi_device_bid
c_func
(paren
id|device
)paren
comma
id|acpi_button_dir
)paren
suffix:semicolon
id|return_VALUE
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/* --------------------------------------------------------------------------&n;                                Driver Interface&n;   -------------------------------------------------------------------------- */
r_void
DECL|function|acpi_button_notify
id|acpi_button_notify
(paren
id|acpi_handle
id|handle
comma
id|u32
id|event
comma
r_void
op_star
id|data
)paren
(brace
r_struct
id|acpi_button
op_star
id|button
op_assign
(paren
r_struct
id|acpi_button
op_star
)paren
id|data
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_button_notify&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|button
op_logical_or
op_logical_neg
id|button-&gt;device
)paren
id|return_VOID
suffix:semicolon
r_switch
c_cond
(paren
id|event
)paren
(brace
r_case
id|ACPI_BUTTON_NOTIFY_STATUS
suffix:colon
id|acpi_bus_generate_event
c_func
(paren
id|button-&gt;device
comma
id|event
comma
op_increment
id|button-&gt;pushed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_INFO
comma
l_string|&quot;Unsupported event [0x%x]&bslash;n&quot;
comma
id|event
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|return_VOID
suffix:semicolon
)brace
id|acpi_status
DECL|function|acpi_button_notify_fixed
id|acpi_button_notify_fixed
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|acpi_button
op_star
id|button
op_assign
(paren
r_struct
id|acpi_button
op_star
)paren
id|data
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_button_notify_fixed&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|button
)paren
id|return_ACPI_STATUS
c_func
(paren
id|AE_BAD_PARAMETER
)paren
suffix:semicolon
id|acpi_button_notify
c_func
(paren
id|button-&gt;handle
comma
id|ACPI_BUTTON_NOTIFY_STATUS
comma
id|button
)paren
suffix:semicolon
id|return_ACPI_STATUS
c_func
(paren
id|AE_OK
)paren
suffix:semicolon
)brace
r_int
DECL|function|acpi_button_add
id|acpi_button_add
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
id|acpi_button
op_star
id|button
op_assign
l_int|NULL
suffix:semicolon
r_static
r_struct
id|acpi_device
op_star
id|power_button
suffix:semicolon
r_static
r_struct
id|acpi_device
op_star
id|sleep_button
suffix:semicolon
r_static
r_struct
id|acpi_device
op_star
id|lid_button
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_button_add&quot;
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
id|button
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|acpi_button
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|button
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
id|button
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|acpi_button
)paren
)paren
suffix:semicolon
id|button-&gt;device
op_assign
id|device
suffix:semicolon
id|button-&gt;handle
op_assign
id|device-&gt;handle
suffix:semicolon
id|acpi_driver_data
c_func
(paren
id|device
)paren
op_assign
id|button
suffix:semicolon
multiline_comment|/*&n;&t; * Determine the button type (via hid), as fixed-feature buttons&n;&t; * need to be handled a bit differently than generic-space.&n;&t; */
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|acpi_device_hid
c_func
(paren
id|device
)paren
comma
id|ACPI_BUTTON_HID_POWER
)paren
)paren
(brace
id|button-&gt;type
op_assign
id|ACPI_BUTTON_TYPE_POWER
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
id|ACPI_BUTTON_DEVICE_NAME_POWER
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
l_string|&quot;%s/%s&quot;
comma
id|ACPI_BUTTON_CLASS
comma
id|ACPI_BUTTON_SUBCLASS_POWER
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|acpi_device_hid
c_func
(paren
id|device
)paren
comma
id|ACPI_BUTTON_HID_POWERF
)paren
)paren
(brace
id|button-&gt;type
op_assign
id|ACPI_BUTTON_TYPE_POWERF
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
id|ACPI_BUTTON_DEVICE_NAME_POWERF
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
l_string|&quot;%s/%s&quot;
comma
id|ACPI_BUTTON_CLASS
comma
id|ACPI_BUTTON_SUBCLASS_POWER
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|acpi_device_hid
c_func
(paren
id|device
)paren
comma
id|ACPI_BUTTON_HID_SLEEP
)paren
)paren
(brace
id|button-&gt;type
op_assign
id|ACPI_BUTTON_TYPE_SLEEP
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
id|ACPI_BUTTON_DEVICE_NAME_SLEEP
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
l_string|&quot;%s/%s&quot;
comma
id|ACPI_BUTTON_CLASS
comma
id|ACPI_BUTTON_SUBCLASS_SLEEP
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|acpi_device_hid
c_func
(paren
id|device
)paren
comma
id|ACPI_BUTTON_HID_SLEEPF
)paren
)paren
(brace
id|button-&gt;type
op_assign
id|ACPI_BUTTON_TYPE_SLEEPF
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
id|ACPI_BUTTON_DEVICE_NAME_SLEEPF
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
l_string|&quot;%s/%s&quot;
comma
id|ACPI_BUTTON_CLASS
comma
id|ACPI_BUTTON_SUBCLASS_SLEEP
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|acpi_device_hid
c_func
(paren
id|device
)paren
comma
id|ACPI_BUTTON_HID_LID
)paren
)paren
(brace
id|button-&gt;type
op_assign
id|ACPI_BUTTON_TYPE_LID
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
id|ACPI_BUTTON_DEVICE_NAME_LID
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
l_string|&quot;%s/%s&quot;
comma
id|ACPI_BUTTON_CLASS
comma
id|ACPI_BUTTON_SUBCLASS_LID
)paren
suffix:semicolon
)brace
r_else
(brace
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Unsupported hid [%s]&bslash;n&quot;
comma
id|acpi_device_hid
c_func
(paren
id|device
)paren
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Ensure only one button of each type is used.&n;&t; */
r_switch
c_cond
(paren
id|button-&gt;type
)paren
(brace
r_case
id|ACPI_BUTTON_TYPE_POWER
suffix:colon
r_case
id|ACPI_BUTTON_TYPE_POWERF
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|power_button
)paren
id|power_button
op_assign
id|device
suffix:semicolon
r_else
(brace
id|kfree
c_func
(paren
id|button
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
r_break
suffix:semicolon
r_case
id|ACPI_BUTTON_TYPE_SLEEP
suffix:colon
r_case
id|ACPI_BUTTON_TYPE_SLEEPF
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|sleep_button
)paren
id|sleep_button
op_assign
id|device
suffix:semicolon
r_else
(brace
id|kfree
c_func
(paren
id|button
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
r_break
suffix:semicolon
r_case
id|ACPI_BUTTON_TYPE_LID
suffix:colon
r_if
c_cond
(paren
op_logical_neg
id|lid_button
)paren
id|lid_button
op_assign
id|device
suffix:semicolon
r_else
(brace
id|kfree
c_func
(paren
id|button
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
r_break
suffix:semicolon
)brace
id|result
op_assign
id|acpi_button_add_fs
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
r_switch
c_cond
(paren
id|button-&gt;type
)paren
(brace
r_case
id|ACPI_BUTTON_TYPE_POWERF
suffix:colon
id|status
op_assign
id|acpi_install_fixed_event_handler
(paren
id|ACPI_EVENT_POWER_BUTTON
comma
id|acpi_button_notify_fixed
comma
id|button
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_BUTTON_TYPE_SLEEPF
suffix:colon
id|status
op_assign
id|acpi_install_fixed_event_handler
(paren
id|ACPI_EVENT_SLEEP_BUTTON
comma
id|acpi_button_notify_fixed
comma
id|button
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|acpi_install_notify_handler
(paren
id|button-&gt;handle
comma
id|ACPI_DEVICE_NOTIFY
comma
id|acpi_button_notify
comma
id|button
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
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
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Error installing notify handler&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|result
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|end
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
id|PREFIX
l_string|&quot;%s [%s]&bslash;n&quot;
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
)paren
suffix:semicolon
id|end
suffix:colon
r_if
c_cond
(paren
id|result
)paren
(brace
id|acpi_button_remove_fs
c_func
(paren
id|device
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|button
)paren
suffix:semicolon
)brace
id|return_VALUE
c_func
(paren
id|result
)paren
suffix:semicolon
)brace
r_int
DECL|function|acpi_button_remove
id|acpi_button_remove
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
id|acpi_status
id|status
op_assign
l_int|0
suffix:semicolon
r_struct
id|acpi_button
op_star
id|button
op_assign
l_int|NULL
suffix:semicolon
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_button_remove&quot;
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
id|button
op_assign
id|acpi_driver_data
c_func
(paren
id|device
)paren
suffix:semicolon
multiline_comment|/* Unregister for device notifications. */
r_switch
c_cond
(paren
id|button-&gt;type
)paren
(brace
r_case
id|ACPI_BUTTON_TYPE_POWERF
suffix:colon
id|status
op_assign
id|acpi_remove_fixed_event_handler
c_func
(paren
id|ACPI_EVENT_POWER_BUTTON
comma
id|acpi_button_notify_fixed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ACPI_BUTTON_TYPE_SLEEPF
suffix:colon
id|status
op_assign
id|acpi_remove_fixed_event_handler
c_func
(paren
id|ACPI_EVENT_SLEEP_BUTTON
comma
id|acpi_button_notify_fixed
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|status
op_assign
id|acpi_remove_notify_handler
c_func
(paren
id|button-&gt;handle
comma
id|ACPI_DEVICE_NOTIFY
comma
id|acpi_button_notify
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ACPI_FAILURE
c_func
(paren
id|status
)paren
)paren
id|ACPI_DEBUG_PRINT
c_func
(paren
(paren
id|ACPI_DB_ERROR
comma
l_string|&quot;Error removing notify handler&bslash;n&quot;
)paren
)paren
suffix:semicolon
id|acpi_button_remove_fs
c_func
(paren
id|device
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|button
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
id|__init
DECL|function|acpi_button_init
id|acpi_button_init
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
l_string|&quot;acpi_button_init&quot;
)paren
suffix:semicolon
id|acpi_button_dir
op_assign
id|proc_mkdir
c_func
(paren
id|ACPI_BUTTON_CLASS
comma
id|acpi_root_dir
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|acpi_button_dir
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
id|acpi_button_driver
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
id|ACPI_BUTTON_CLASS
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
r_static
r_void
id|__exit
DECL|function|acpi_button_exit
id|acpi_button_exit
(paren
r_void
)paren
(brace
id|ACPI_FUNCTION_TRACE
c_func
(paren
l_string|&quot;acpi_button_exit&quot;
)paren
suffix:semicolon
id|acpi_bus_unregister_driver
c_func
(paren
op_amp
id|acpi_button_driver
)paren
suffix:semicolon
id|remove_proc_entry
c_func
(paren
id|ACPI_BUTTON_CLASS
comma
id|acpi_root_dir
)paren
suffix:semicolon
id|return_VOID
suffix:semicolon
)brace
DECL|variable|acpi_button_init
id|module_init
c_func
(paren
id|acpi_button_init
)paren
suffix:semicolon
DECL|variable|acpi_button_exit
id|module_exit
c_func
(paren
id|acpi_button_exit
)paren
suffix:semicolon
eof
