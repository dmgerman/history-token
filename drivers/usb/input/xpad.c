multiline_comment|/*&n; * X-Box gamepad - v0.0.5&n; *&n; * Copyright (c) 2002 Marko Friedemann &lt;mfr@bmx-chemnitz.de&gt;&n; *&n; *&n; * This program is free software; you can redistribute it and/or&n; * modify it under the terms of the GNU General Public License as&n; * published by the Free Software Foundation; either version 2 of&n; * the License, or (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; *&n; * This driver is based on:&n; *  - information from     http://euc.jp/periphs/xbox-controller.ja.html&n; *  - the iForce driver    drivers/char/joystick/iforce.c&n; *  - the skeleton-driver  drivers/usb/usb-skeleton.c&n; *&n; * Thanks to:&n; *  - ITO Takayuki for providing essential xpad information on his website&n; *  - Vojtech Pavlik     - iforce driver / input subsystem&n; *  - Greg Kroah-Hartman - usb-skeleton driver&n; *&n; * TODO:&n; *  - fine tune axes&n; *  - fix &quot;analog&quot; buttons (reported as digital now)&n; *  - get rumble working&n; *&n; * History:&n; *&n; * 2002-06-27 - 0.0.1 : first version, just said &quot;XBOX HID controller&quot;&n; *&n; * 2002-07-02 - 0.0.2 : basic working version&n; *  - all axes and 9 of the 10 buttons work (german InterAct device)&n; *  - the black button does not work&n; *&n; * 2002-07-14 - 0.0.3 : rework by Vojtech Pavlik&n; *  - indentation fixes&n; *  - usb + input init sequence fixes&n; *&n; * 2002-07-16 - 0.0.4 : minor changes, merge with Vojtech&squot;s v0.0.3&n; *  - verified the lack of HID and report descriptors&n; *  - verified that ALL buttons WORK&n; *  - fixed d-pad to axes mapping&n; *&n; * 2002-07-17 - 0.0.5 : simplified d-pad handling&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/smp_lock.h&gt;
macro_line|#include &lt;linux/devfs_fs_kernel.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.0.5&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Marko Friedemann &lt;mfr@bmx-chemnitz.de&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;X-Box pad driver&quot;
DECL|macro|XPAD_PKT_LEN
mdefine_line|#define XPAD_PKT_LEN 32
DECL|struct|xpad_device
r_static
r_struct
id|xpad_device
(brace
DECL|member|idVendor
id|u16
id|idVendor
suffix:semicolon
DECL|member|idProduct
id|u16
id|idProduct
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|variable|xpad_device
)brace
id|xpad_device
(braket
)braket
op_assign
(brace
(brace
l_int|0x045e
comma
l_int|0x0202
comma
l_string|&quot;Microsoft X-Box pad (US)&quot;
)brace
comma
(brace
l_int|0x045e
comma
l_int|0x0285
comma
l_string|&quot;Microsoft X-Box pad (Japan)&quot;
)brace
comma
(brace
l_int|0x05fd
comma
l_int|0x107a
comma
l_string|&quot;InterAct &squot;PowerPad Pro&squot; X-Box pad (Germany)&quot;
)brace
comma
(brace
l_int|0x0000
comma
l_int|0x0000
comma
l_string|&quot;X-Box pad&quot;
)brace
)brace
suffix:semicolon
DECL|variable|xpad_btn
r_static
r_int
r_int
id|xpad_btn
(braket
)braket
op_assign
(brace
id|BTN_A
comma
id|BTN_B
comma
id|BTN_C
comma
id|BTN_X
comma
id|BTN_Y
comma
id|BTN_Z
comma
multiline_comment|/* &quot;analog&quot; buttons */
id|BTN_START
comma
id|BTN_BACK
comma
id|BTN_THUMBL
comma
id|BTN_THUMBR
comma
multiline_comment|/* start/back/sticks */
op_minus
l_int|1
multiline_comment|/* terminating entry */
)brace
suffix:semicolon
DECL|variable|xpad_abs
r_static
r_int
r_int
id|xpad_abs
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
multiline_comment|/* left stick */
id|ABS_RX
comma
id|ABS_RY
comma
multiline_comment|/* right stick */
id|ABS_Z
comma
id|ABS_RZ
comma
multiline_comment|/* triggers left/right */
id|ABS_HAT0X
comma
id|ABS_HAT0Y
comma
multiline_comment|/* digital pad */
op_minus
l_int|1
multiline_comment|/* terminating entry */
)brace
suffix:semicolon
DECL|variable|xpad_table
r_static
r_struct
id|usb_device_id
id|xpad_table
(braket
)braket
op_assign
(brace
(brace
id|USB_INTERFACE_INFO
c_func
(paren
l_char|&squot;X&squot;
comma
l_char|&squot;B&squot;
comma
l_int|0
)paren
)brace
comma
multiline_comment|/* X-Box USB-IF not approved class */
(brace
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|xpad_table
)paren
suffix:semicolon
DECL|struct|usb_xpad
r_struct
id|usb_xpad
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
multiline_comment|/* input device interface */
DECL|member|udev
r_struct
id|usb_device
op_star
id|udev
suffix:semicolon
multiline_comment|/* usb device */
DECL|member|irq_in
r_struct
id|urb
op_star
id|irq_in
suffix:semicolon
multiline_comment|/* urb for interrupt in report */
DECL|member|idata
r_int
r_char
op_star
id|idata
suffix:semicolon
multiline_comment|/* input data */
DECL|member|idata_dma
id|dma_addr_t
id|idata_dma
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|65
)braket
suffix:semicolon
multiline_comment|/* physical device path */
DECL|member|open_count
r_int
id|open_count
suffix:semicolon
multiline_comment|/* reference count */
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;xpad_process_packet&n; *&n; *&t;Completes a request by converting the data into events for the&n; *&t;input subsystem.&n; *&n; *&t;The used report descriptor was taken from ITO Takayukis website:&n; *&t; http://euc.jp/periphs/xbox-controller.ja.html&n; */
DECL|function|xpad_process_packet
r_static
r_void
id|xpad_process_packet
c_func
(paren
r_struct
id|usb_xpad
op_star
id|xpad
comma
id|u16
id|cmd
comma
r_int
r_char
op_star
id|data
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|xpad-&gt;dev
suffix:semicolon
multiline_comment|/* left stick */
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
(paren
id|__s16
)paren
(paren
(paren
(paren
id|__s16
)paren
id|data
(braket
l_int|13
)braket
op_lshift
l_int|8
)paren
op_or
id|data
(braket
l_int|12
)braket
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Y
comma
(paren
id|__s16
)paren
(paren
(paren
(paren
id|__s16
)paren
id|data
(braket
l_int|15
)braket
op_lshift
l_int|8
)paren
op_or
id|data
(braket
l_int|14
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* right stick */
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_RX
comma
(paren
id|__s16
)paren
(paren
(paren
(paren
id|__s16
)paren
id|data
(braket
l_int|17
)braket
op_lshift
l_int|8
)paren
op_or
id|data
(braket
l_int|16
)braket
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_RY
comma
(paren
id|__s16
)paren
(paren
(paren
(paren
id|__s16
)paren
id|data
(braket
l_int|19
)braket
op_lshift
l_int|8
)paren
op_or
id|data
(braket
l_int|18
)braket
)paren
)paren
suffix:semicolon
multiline_comment|/* triggers left/right */
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Z
comma
id|data
(braket
l_int|10
)braket
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_RZ
comma
id|data
(braket
l_int|11
)braket
)paren
suffix:semicolon
multiline_comment|/* digital pad */
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0X
comma
op_logical_neg
op_logical_neg
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|0x08
)paren
op_minus
op_logical_neg
op_logical_neg
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|0x04
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0Y
comma
op_logical_neg
op_logical_neg
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|0x02
)paren
op_minus
op_logical_neg
op_logical_neg
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|0x01
)paren
)paren
suffix:semicolon
multiline_comment|/* start/back buttons and stick press left/right */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_START
comma
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|0x10
)paren
op_rshift
l_int|4
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_BACK
comma
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|0x20
)paren
op_rshift
l_int|5
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_THUMBL
comma
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|0x40
)paren
op_rshift
l_int|6
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_THUMBR
comma
id|data
(braket
l_int|2
)braket
op_rshift
l_int|7
)paren
suffix:semicolon
multiline_comment|/* &quot;analog&quot; buttons A, B, X, Y */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_A
comma
id|data
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_B
comma
id|data
(braket
l_int|5
)braket
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_X
comma
id|data
(braket
l_int|6
)braket
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_Y
comma
id|data
(braket
l_int|7
)braket
)paren
suffix:semicolon
multiline_comment|/* &quot;analog&quot; buttons black, white */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_C
comma
id|data
(braket
l_int|8
)braket
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_Z
comma
id|data
(braket
l_int|9
)braket
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|function|xpad_irq_in
r_static
r_void
id|xpad_irq_in
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usb_xpad
op_star
id|xpad
op_assign
id|urb-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
r_return
suffix:semicolon
id|xpad_process_packet
c_func
(paren
id|xpad
comma
l_int|0
comma
id|xpad-&gt;idata
)paren
suffix:semicolon
)brace
DECL|function|xpad_open
r_static
r_int
id|xpad_open
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|usb_xpad
op_star
id|xpad
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|xpad-&gt;open_count
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|xpad-&gt;irq_in-&gt;dev
op_assign
id|xpad-&gt;udev
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|xpad-&gt;irq_in
comma
id|GFP_KERNEL
)paren
)paren
r_return
op_minus
id|EIO
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xpad_close
r_static
r_void
id|xpad_close
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|usb_xpad
op_star
id|xpad
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|xpad-&gt;open_count
)paren
id|usb_unlink_urb
c_func
(paren
id|xpad-&gt;irq_in
)paren
suffix:semicolon
)brace
DECL|function|xpad_probe
r_static
r_int
id|xpad_probe
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
r_struct
id|usb_device
op_star
id|udev
op_assign
id|interface_to_usbdev
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|usb_xpad
op_star
id|xpad
op_assign
l_int|NULL
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|ep_irq_in
suffix:semicolon
r_char
id|path
(braket
l_int|64
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|xpad_device
(braket
id|i
)braket
dot
id|idVendor
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|udev-&gt;descriptor.idVendor
op_eq
id|xpad_device
(braket
id|i
)braket
dot
id|idVendor
)paren
op_logical_and
(paren
id|udev-&gt;descriptor.idProduct
op_eq
id|xpad_device
(braket
id|i
)braket
dot
id|idProduct
)paren
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|xpad
op_assign
id|kmalloc
(paren
r_sizeof
(paren
r_struct
id|usb_xpad
)paren
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|err
c_func
(paren
l_string|&quot;cannot allocate memory for new pad&quot;
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
id|xpad
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|usb_xpad
)paren
)paren
suffix:semicolon
id|xpad-&gt;idata
op_assign
id|usb_buffer_alloc
c_func
(paren
id|udev
comma
id|XPAD_PKT_LEN
comma
id|SLAB_ATOMIC
comma
op_amp
id|xpad-&gt;idata_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|xpad-&gt;idata
)paren
(brace
id|kfree
c_func
(paren
id|xpad
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|xpad-&gt;irq_in
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
id|xpad-&gt;irq_in
)paren
(brace
id|err
c_func
(paren
l_string|&quot;cannot allocate memory for new pad irq urb&quot;
)paren
suffix:semicolon
id|usb_buffer_free
c_func
(paren
id|udev
comma
id|XPAD_PKT_LEN
comma
id|xpad-&gt;idata
comma
id|xpad-&gt;idata_dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|xpad
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ep_irq_in
op_assign
id|intf-&gt;altsetting
(braket
l_int|0
)braket
dot
id|endpoint
op_plus
l_int|0
suffix:semicolon
id|usb_fill_int_urb
c_func
(paren
id|xpad-&gt;irq_in
comma
id|udev
comma
id|usb_rcvintpipe
c_func
(paren
id|udev
comma
id|ep_irq_in-&gt;bEndpointAddress
)paren
comma
id|xpad-&gt;idata
comma
id|XPAD_PKT_LEN
comma
id|xpad_irq_in
comma
id|xpad
comma
id|ep_irq_in-&gt;bInterval
)paren
suffix:semicolon
id|xpad-&gt;irq_in-&gt;transfer_dma
op_assign
id|xpad-&gt;idata_dma
suffix:semicolon
id|xpad-&gt;irq_in-&gt;transfer_flags
op_or_assign
id|URB_NO_DMA_MAP
suffix:semicolon
id|xpad-&gt;udev
op_assign
id|udev
suffix:semicolon
id|xpad-&gt;dev.id.bustype
op_assign
id|BUS_USB
suffix:semicolon
id|xpad-&gt;dev.id.vendor
op_assign
id|udev-&gt;descriptor.idVendor
suffix:semicolon
id|xpad-&gt;dev.id.product
op_assign
id|udev-&gt;descriptor.idProduct
suffix:semicolon
id|xpad-&gt;dev.id.version
op_assign
id|udev-&gt;descriptor.bcdDevice
suffix:semicolon
id|xpad-&gt;dev
dot
r_private
op_assign
id|xpad
suffix:semicolon
id|xpad-&gt;dev.name
op_assign
id|xpad_device
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|xpad-&gt;dev.phys
op_assign
id|xpad-&gt;phys
suffix:semicolon
id|xpad-&gt;dev.open
op_assign
id|xpad_open
suffix:semicolon
id|xpad-&gt;dev.close
op_assign
id|xpad_close
suffix:semicolon
id|usb_make_path
c_func
(paren
id|udev
comma
id|path
comma
l_int|64
)paren
suffix:semicolon
id|snprintf
c_func
(paren
id|xpad-&gt;phys
comma
l_int|64
comma
l_string|&quot;%s/input0&quot;
comma
id|path
)paren
suffix:semicolon
id|xpad-&gt;dev.evbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|EV_KEY
)paren
op_or
id|BIT
c_func
(paren
id|EV_ABS
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|xpad_btn
(braket
id|i
)braket
op_ge
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|xpad_btn
(braket
id|i
)braket
comma
id|xpad-&gt;dev.keybit
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|xpad_abs
(braket
id|i
)braket
op_ge
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|t
op_assign
id|xpad_abs
(braket
id|i
)braket
suffix:semicolon
id|set_bit
c_func
(paren
id|t
comma
id|xpad-&gt;dev.absbit
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|t
)paren
(brace
r_case
id|ABS_X
suffix:colon
r_case
id|ABS_Y
suffix:colon
r_case
id|ABS_RX
suffix:colon
r_case
id|ABS_RY
suffix:colon
multiline_comment|/* the two sticks */
id|xpad-&gt;dev.absmax
(braket
id|t
)braket
op_assign
l_int|32767
suffix:semicolon
id|xpad-&gt;dev.absmin
(braket
id|t
)braket
op_assign
op_minus
l_int|32768
suffix:semicolon
id|xpad-&gt;dev.absflat
(braket
id|t
)braket
op_assign
l_int|128
suffix:semicolon
id|xpad-&gt;dev.absfuzz
(braket
id|t
)braket
op_assign
l_int|16
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ABS_Z
suffix:colon
r_case
id|ABS_RZ
suffix:colon
multiline_comment|/* the triggers */
id|xpad-&gt;dev.absmax
(braket
id|t
)braket
op_assign
l_int|255
suffix:semicolon
id|xpad-&gt;dev.absmin
(braket
id|t
)braket
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
id|ABS_HAT0X
suffix:colon
r_case
id|ABS_HAT0Y
suffix:colon
multiline_comment|/* the d-pad */
id|xpad-&gt;dev.absmax
(braket
id|t
)braket
op_assign
l_int|1
suffix:semicolon
id|xpad-&gt;dev.absmin
(braket
id|t
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|input_register_device
c_func
(paren
op_amp
id|xpad-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&quot;
comma
id|xpad-&gt;dev.name
comma
id|path
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
op_amp
id|intf-&gt;dev
comma
id|xpad
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xpad_disconnect
r_static
r_void
id|xpad_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|usb_xpad
op_star
id|xpad
op_assign
id|dev_get_drvdata
c_func
(paren
op_amp
id|intf-&gt;dev
)paren
suffix:semicolon
id|dev_set_drvdata
c_func
(paren
op_amp
id|intf-&gt;dev
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xpad
)paren
(brace
id|usb_unlink_urb
c_func
(paren
id|xpad-&gt;irq_in
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|xpad-&gt;dev
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|xpad-&gt;irq_in
)paren
suffix:semicolon
id|usb_buffer_free
c_func
(paren
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
comma
id|XPAD_PKT_LEN
comma
id|xpad-&gt;idata
comma
id|xpad-&gt;idata_dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|xpad
)paren
suffix:semicolon
)brace
)brace
DECL|variable|xpad_driver
r_static
r_struct
id|usb_driver
id|xpad_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;xpad&quot;
comma
dot
id|probe
op_assign
id|xpad_probe
comma
dot
id|disconnect
op_assign
id|xpad_disconnect
comma
dot
id|id_table
op_assign
id|xpad_table
comma
)brace
suffix:semicolon
DECL|function|usb_xpad_init
r_static
r_int
id|__init
id|usb_xpad_init
c_func
(paren
r_void
)paren
(brace
id|usb_register
c_func
(paren
op_amp
id|xpad_driver
)paren
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_DESC
l_string|&quot;:&quot;
id|DRIVER_VERSION
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_xpad_exit
r_static
r_void
id|__exit
id|usb_xpad_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|xpad_driver
)paren
suffix:semicolon
)brace
DECL|variable|usb_xpad_init
id|module_init
c_func
(paren
id|usb_xpad_init
)paren
suffix:semicolon
DECL|variable|usb_xpad_exit
id|module_exit
c_func
(paren
id|usb_xpad_exit
)paren
suffix:semicolon
DECL|variable|DRIVER_AUTHOR
id|MODULE_AUTHOR
c_func
(paren
id|DRIVER_AUTHOR
)paren
suffix:semicolon
DECL|variable|DRIVER_DESC
id|MODULE_DESCRIPTION
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
