multiline_comment|/*&n; *&n; *  Broadcom Blutonium firmware driver&n; *&n; *  Copyright (C) 2003  Marcel Holtmann &lt;marcel@holtmann.org&gt;&n; *&n; *&n; *  This program is free software; you can redistribute it and/or modify&n; *  it under the terms of the GNU General Public License as published by&n; *  the Free Software Foundation; either version 2 of the License, or&n; *  (at your option) any later version.&n; *&n; *  This program is distributed in the hope that it will be useful,&n; *  but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *  GNU General Public License for more details.&n; *&n; *  You should have received a copy of the GNU General Public License&n; *  along with this program; if not, write to the Free Software&n; *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n; *&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/firmware.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &lt;net/bluetooth/bluetooth.h&gt;
macro_line|#ifndef CONFIG_BT_HCIBCM203X_DEBUG
DECL|macro|BT_DBG
macro_line|#undef  BT_DBG
DECL|macro|BT_DBG
mdefine_line|#define BT_DBG(D...)
macro_line|#endif
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;1.0&quot;
DECL|variable|bcm203x_table
r_static
r_struct
id|usb_device_id
id|bcm203x_table
(braket
)braket
op_assign
(brace
multiline_comment|/* Broadcom Blutonium (BCM2033) */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x0a5c
comma
l_int|0x2033
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|usb
comma
id|bcm203x_table
)paren
suffix:semicolon
DECL|macro|BCM203X_ERROR
mdefine_line|#define BCM203X_ERROR&t;&t;0
DECL|macro|BCM203X_RESET
mdefine_line|#define BCM203X_RESET&t;&t;1
DECL|macro|BCM203X_LOAD_MINIDRV
mdefine_line|#define BCM203X_LOAD_MINIDRV&t;2
DECL|macro|BCM203X_SELECT_MEMORY
mdefine_line|#define BCM203X_SELECT_MEMORY&t;3
DECL|macro|BCM203X_CHECK_MEMORY
mdefine_line|#define BCM203X_CHECK_MEMORY&t;4
DECL|macro|BCM203X_LOAD_FIRMWARE
mdefine_line|#define BCM203X_LOAD_FIRMWARE&t;5
DECL|macro|BCM203X_CHECK_FIRMWARE
mdefine_line|#define BCM203X_CHECK_FIRMWARE&t;6
DECL|macro|BCM203X_IN_EP
mdefine_line|#define BCM203X_IN_EP&t;&t;0x81
DECL|macro|BCM203X_OUT_EP
mdefine_line|#define BCM203X_OUT_EP&t;&t;0x02
DECL|struct|bcm203x_data
r_struct
id|bcm203x_data
(brace
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|urb
r_struct
id|urb
op_star
id|urb
suffix:semicolon
DECL|member|buffer
r_int
r_char
op_star
id|buffer
suffix:semicolon
DECL|member|fw_data
r_int
r_char
op_star
id|fw_data
suffix:semicolon
DECL|member|fw_size
r_int
r_int
id|fw_size
suffix:semicolon
DECL|member|fw_sent
r_int
r_int
id|fw_sent
suffix:semicolon
)brace
suffix:semicolon
DECL|function|bcm203x_complete
r_static
r_void
id|bcm203x_complete
c_func
(paren
r_struct
id|urb
op_star
id|urb
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|bcm203x_data
op_star
id|data
op_assign
id|urb-&gt;context
suffix:semicolon
r_struct
id|usb_device
op_star
id|udev
op_assign
id|urb-&gt;dev
suffix:semicolon
r_int
id|len
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;udev %p urb %p&quot;
comma
id|udev
comma
id|urb
)paren
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;URB failed with status %d&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
id|data-&gt;state
op_assign
id|BCM203X_ERROR
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|data-&gt;state
)paren
(brace
r_case
id|BCM203X_LOAD_MINIDRV
suffix:colon
id|memcpy
c_func
(paren
id|data-&gt;buffer
comma
l_string|&quot;#&quot;
comma
l_int|1
)paren
suffix:semicolon
id|usb_fill_bulk_urb
c_func
(paren
id|urb
comma
id|udev
comma
id|usb_sndbulkpipe
c_func
(paren
id|udev
comma
id|BCM203X_OUT_EP
)paren
comma
id|data-&gt;buffer
comma
l_int|1
comma
id|bcm203x_complete
comma
id|data
)paren
suffix:semicolon
id|data-&gt;state
op_assign
id|BCM203X_SELECT_MEMORY
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|data-&gt;timer
comma
id|jiffies
op_plus
(paren
id|HZ
op_div
l_int|10
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BCM203X_SELECT_MEMORY
suffix:colon
id|usb_fill_int_urb
c_func
(paren
id|urb
comma
id|udev
comma
id|usb_rcvintpipe
c_func
(paren
id|udev
comma
id|BCM203X_IN_EP
)paren
comma
id|data-&gt;buffer
comma
l_int|32
comma
id|bcm203x_complete
comma
id|data
comma
l_int|1
)paren
suffix:semicolon
id|data-&gt;state
op_assign
id|BCM203X_CHECK_MEMORY
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|data-&gt;urb
comma
id|GFP_ATOMIC
)paren
OL
l_int|0
)paren
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t submit URB&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BCM203X_CHECK_MEMORY
suffix:colon
r_if
c_cond
(paren
id|data-&gt;buffer
(braket
l_int|0
)braket
op_ne
l_char|&squot;#&squot;
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Memory select failed&quot;
)paren
suffix:semicolon
id|data-&gt;state
op_assign
id|BCM203X_ERROR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|data-&gt;state
op_assign
id|BCM203X_LOAD_FIRMWARE
suffix:semicolon
r_case
id|BCM203X_LOAD_FIRMWARE
suffix:colon
r_if
c_cond
(paren
id|data-&gt;fw_sent
op_eq
id|data-&gt;fw_size
)paren
(brace
id|usb_fill_int_urb
c_func
(paren
id|urb
comma
id|udev
comma
id|usb_rcvintpipe
c_func
(paren
id|udev
comma
id|BCM203X_IN_EP
)paren
comma
id|data-&gt;buffer
comma
l_int|32
comma
id|bcm203x_complete
comma
id|data
comma
l_int|1
)paren
suffix:semicolon
id|data-&gt;state
op_assign
id|BCM203X_CHECK_FIRMWARE
suffix:semicolon
)brace
r_else
(brace
id|len
op_assign
id|min_t
c_func
(paren
id|uint
comma
id|data-&gt;fw_size
op_minus
id|data-&gt;fw_sent
comma
l_int|4096
)paren
suffix:semicolon
id|usb_fill_bulk_urb
c_func
(paren
id|urb
comma
id|udev
comma
id|usb_sndbulkpipe
c_func
(paren
id|udev
comma
id|BCM203X_OUT_EP
)paren
comma
id|data-&gt;fw_data
op_plus
id|data-&gt;fw_sent
comma
id|len
comma
id|bcm203x_complete
comma
id|data
)paren
suffix:semicolon
id|data-&gt;fw_sent
op_add_assign
id|len
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|data-&gt;urb
comma
id|GFP_ATOMIC
)paren
OL
l_int|0
)paren
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t submit URB&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|BCM203X_CHECK_FIRMWARE
suffix:colon
r_if
c_cond
(paren
id|data-&gt;buffer
(braket
l_int|0
)braket
op_ne
l_char|&squot;.&squot;
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Firmware loading failed&quot;
)paren
suffix:semicolon
id|data-&gt;state
op_assign
id|BCM203X_ERROR
suffix:semicolon
r_break
suffix:semicolon
)brace
id|data-&gt;state
op_assign
id|BCM203X_RESET
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|function|bcm203x_timer
r_static
r_void
id|bcm203x_timer
c_func
(paren
r_int
r_int
id|user_data
)paren
(brace
r_struct
id|bcm203x_data
op_star
id|data
op_assign
(paren
r_struct
id|bcm203x_data
op_star
)paren
id|user_data
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|data-&gt;urb
comma
id|GFP_ATOMIC
)paren
OL
l_int|0
)paren
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t submit URB&quot;
)paren
suffix:semicolon
)brace
DECL|function|bcm203x_probe
r_static
r_int
id|bcm203x_probe
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_const
r_struct
id|firmware
op_star
id|firmware
suffix:semicolon
r_struct
id|usb_device
op_star
id|udev
op_assign
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|bcm203x_data
op_star
id|data
suffix:semicolon
r_int
id|size
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;intf %p id %p&quot;
comma
id|intf
comma
id|id
)paren
suffix:semicolon
r_if
c_cond
(paren
id|intf-&gt;cur_altsetting-&gt;desc.bInterfaceNumber
op_ne
l_int|0
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|data
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate memory for data structure&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|data
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|data
)paren
)paren
suffix:semicolon
id|data-&gt;udev
op_assign
id|udev
suffix:semicolon
id|data-&gt;state
op_assign
id|BCM203X_LOAD_MINIDRV
suffix:semicolon
id|data-&gt;urb
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;urb
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate URB&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_firmware
c_func
(paren
op_amp
id|firmware
comma
l_string|&quot;BCM2033-MD.hex&quot;
comma
op_amp
id|udev-&gt;dev
)paren
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Mini driver request failed&quot;
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|data-&gt;urb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|BT_DBG
c_func
(paren
l_string|&quot;minidrv data %p size %d&quot;
comma
id|firmware-&gt;data
comma
id|firmware-&gt;size
)paren
suffix:semicolon
id|size
op_assign
id|max_t
c_func
(paren
id|uint
comma
id|firmware-&gt;size
comma
l_int|4096
)paren
suffix:semicolon
id|data-&gt;buffer
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;buffer
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate memory for mini driver&quot;
)paren
suffix:semicolon
id|release_firmware
c_func
(paren
id|firmware
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|data-&gt;urb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|data-&gt;buffer
comma
id|firmware-&gt;data
comma
id|firmware-&gt;size
)paren
suffix:semicolon
id|usb_fill_bulk_urb
c_func
(paren
id|data-&gt;urb
comma
id|udev
comma
id|usb_sndbulkpipe
c_func
(paren
id|udev
comma
id|BCM203X_OUT_EP
)paren
comma
id|data-&gt;buffer
comma
id|firmware-&gt;size
comma
id|bcm203x_complete
comma
id|data
)paren
suffix:semicolon
id|release_firmware
c_func
(paren
id|firmware
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_firmware
c_func
(paren
op_amp
id|firmware
comma
l_string|&quot;BCM2033-FW.bin&quot;
comma
op_amp
id|udev-&gt;dev
)paren
OL
l_int|0
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Firmware request failed&quot;
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|data-&gt;urb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data-&gt;buffer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
id|BT_DBG
c_func
(paren
l_string|&quot;firmware data %p size %d&quot;
comma
id|firmware-&gt;data
comma
id|firmware-&gt;size
)paren
suffix:semicolon
id|data-&gt;fw_data
op_assign
id|kmalloc
c_func
(paren
id|firmware-&gt;size
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|data-&gt;fw_data
)paren
(brace
id|BT_ERR
c_func
(paren
l_string|&quot;Can&squot;t allocate memory for firmware image&quot;
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|data-&gt;urb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data-&gt;buffer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|data-&gt;fw_data
comma
id|firmware-&gt;data
comma
id|firmware-&gt;size
)paren
suffix:semicolon
id|data-&gt;fw_size
op_assign
id|firmware-&gt;size
suffix:semicolon
id|data-&gt;fw_sent
op_assign
l_int|0
suffix:semicolon
id|release_firmware
c_func
(paren
id|firmware
)paren
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|data-&gt;timer
)paren
suffix:semicolon
id|data-&gt;timer.function
op_assign
id|bcm203x_timer
suffix:semicolon
id|data-&gt;timer.data
op_assign
(paren
r_int
r_int
)paren
id|data
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
id|data
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|data-&gt;timer
comma
id|jiffies
op_plus
id|HZ
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|bcm203x_disconnect
r_static
r_void
id|bcm203x_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|bcm203x_data
op_star
id|data
op_assign
id|usb_get_intfdata
c_func
(paren
id|intf
)paren
suffix:semicolon
id|BT_DBG
c_func
(paren
l_string|&quot;intf %p&quot;
comma
id|intf
)paren
suffix:semicolon
id|usb_kill_urb
c_func
(paren
id|data-&gt;urb
)paren
suffix:semicolon
id|usb_set_intfdata
c_func
(paren
id|intf
comma
l_int|NULL
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|data-&gt;urb
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data-&gt;fw_data
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data-&gt;buffer
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|data
)paren
suffix:semicolon
)brace
DECL|variable|bcm203x_driver
r_static
r_struct
id|usb_driver
id|bcm203x_driver
op_assign
(brace
dot
id|owner
op_assign
id|THIS_MODULE
comma
dot
id|name
op_assign
l_string|&quot;bcm203x&quot;
comma
dot
id|probe
op_assign
id|bcm203x_probe
comma
dot
id|disconnect
op_assign
id|bcm203x_disconnect
comma
dot
id|id_table
op_assign
id|bcm203x_table
comma
)brace
suffix:semicolon
DECL|function|bcm203x_init
r_static
r_int
id|__init
id|bcm203x_init
c_func
(paren
r_void
)paren
(brace
r_int
id|err
suffix:semicolon
id|BT_INFO
c_func
(paren
l_string|&quot;Broadcom Blutonium firmware driver ver %s&quot;
comma
id|VERSION
)paren
suffix:semicolon
id|err
op_assign
id|usb_register
c_func
(paren
op_amp
id|bcm203x_driver
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
OL
l_int|0
)paren
id|BT_ERR
c_func
(paren
l_string|&quot;Failed to register USB driver&quot;
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|bcm203x_exit
r_static
r_void
id|__exit
id|bcm203x_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|bcm203x_driver
)paren
suffix:semicolon
)brace
DECL|variable|bcm203x_init
id|module_init
c_func
(paren
id|bcm203x_init
)paren
suffix:semicolon
DECL|variable|bcm203x_exit
id|module_exit
c_func
(paren
id|bcm203x_exit
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Marcel Holtmann &lt;marcel@holtmann.org&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Broadcom Blutonium firmware driver ver &quot;
id|VERSION
)paren
suffix:semicolon
DECL|variable|VERSION
id|MODULE_VERSION
c_func
(paren
id|VERSION
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
