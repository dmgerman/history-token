multiline_comment|/*&n; * $Id: usbmouse.c,v 1.15 2001/12/27 10:37:41 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; *&n; *  USB HIDBP Mouse support&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v1.6&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB HID Boot Protocol mouse driver&quot;
DECL|macro|DRIVER_LICENSE
mdefine_line|#define DRIVER_LICENSE &quot;GPL&quot;
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
DECL|variable|DRIVER_LICENSE
id|MODULE_LICENSE
c_func
(paren
id|DRIVER_LICENSE
)paren
suffix:semicolon
DECL|struct|usb_mouse
r_struct
id|usb_mouse
(brace
DECL|member|name
r_char
id|name
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|usbdev
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|irq
r_struct
id|urb
op_star
id|irq
suffix:semicolon
DECL|member|open
r_int
id|open
suffix:semicolon
DECL|member|data
r_int
r_char
op_star
id|data
suffix:semicolon
DECL|member|data_dma
id|dma_addr_t
id|data_dma
suffix:semicolon
)brace
suffix:semicolon
DECL|function|usb_mouse_irq
r_static
r_void
id|usb_mouse_irq
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usb_mouse
op_star
id|mouse
op_assign
id|urb-&gt;context
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|mouse-&gt;data
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|mouse-&gt;dev
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
r_return
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x02
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x04
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_SIDE
comma
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x08
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_EXTRA
comma
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x10
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_X
comma
id|data
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_Y
comma
id|data
(braket
l_int|2
)braket
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_WHEEL
comma
id|data
(braket
l_int|3
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
DECL|function|usb_mouse_open
r_static
r_int
id|usb_mouse_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|usb_mouse
op_star
id|mouse
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|mouse-&gt;open
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|mouse-&gt;irq-&gt;dev
op_assign
id|mouse-&gt;usbdev
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|mouse-&gt;irq
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
DECL|function|usb_mouse_close
r_static
r_void
id|usb_mouse_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|usb_mouse
op_star
id|mouse
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
id|mouse-&gt;open
)paren
id|usb_unlink_urb
c_func
(paren
id|mouse-&gt;irq
)paren
suffix:semicolon
)brace
DECL|function|usb_mouse_probe
r_static
r_void
op_star
id|usb_mouse_probe
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_int
r_int
id|ifnum
comma
r_const
r_struct
id|usb_device_id
op_star
id|id
)paren
(brace
r_struct
id|usb_interface
op_star
id|iface
suffix:semicolon
r_struct
id|usb_interface_descriptor
op_star
id|interface
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_struct
id|usb_mouse
op_star
id|mouse
suffix:semicolon
r_int
id|pipe
comma
id|maxp
suffix:semicolon
r_char
id|path
(braket
l_int|64
)braket
suffix:semicolon
r_char
op_star
id|buf
suffix:semicolon
id|iface
op_assign
op_amp
id|dev-&gt;actconfig-&gt;interface
(braket
id|ifnum
)braket
suffix:semicolon
id|interface
op_assign
op_amp
id|iface-&gt;altsetting
(braket
id|iface-&gt;act_altsetting
)braket
suffix:semicolon
r_if
c_cond
(paren
id|interface-&gt;bNumEndpoints
op_ne
l_int|1
)paren
r_return
l_int|NULL
suffix:semicolon
id|endpoint
op_assign
id|interface-&gt;endpoint
op_plus
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|endpoint-&gt;bEndpointAddress
op_amp
l_int|0x80
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
r_if
c_cond
(paren
(paren
id|endpoint-&gt;bmAttributes
op_amp
l_int|3
)paren
op_ne
l_int|3
)paren
r_return
l_int|NULL
suffix:semicolon
id|pipe
op_assign
id|usb_rcvintpipe
c_func
(paren
id|dev
comma
id|endpoint-&gt;bEndpointAddress
)paren
suffix:semicolon
id|maxp
op_assign
id|usb_maxpacket
c_func
(paren
id|dev
comma
id|pipe
comma
id|usb_pipeout
c_func
(paren
id|pipe
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|mouse
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|usb_mouse
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|mouse
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|usb_mouse
)paren
)paren
suffix:semicolon
id|mouse-&gt;data
op_assign
id|usb_buffer_alloc
c_func
(paren
id|dev
comma
l_int|8
comma
id|SLAB_ATOMIC
comma
op_amp
id|mouse-&gt;data_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mouse-&gt;data
)paren
(brace
id|kfree
c_func
(paren
id|mouse
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|mouse-&gt;irq
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
id|mouse-&gt;irq
)paren
(brace
id|usb_buffer_free
c_func
(paren
id|dev
comma
l_int|8
comma
id|mouse-&gt;data
comma
id|mouse-&gt;data_dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mouse
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|mouse-&gt;usbdev
op_assign
id|dev
suffix:semicolon
id|mouse-&gt;dev.evbit
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
id|EV_REL
)paren
suffix:semicolon
id|mouse-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_MOUSE
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_LEFT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_MIDDLE
)paren
suffix:semicolon
id|mouse-&gt;dev.relbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|REL_X
)paren
op_or
id|BIT
c_func
(paren
id|REL_Y
)paren
suffix:semicolon
id|mouse-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_MOUSE
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_SIDE
)paren
op_or
id|BIT
c_func
(paren
id|BTN_EXTRA
)paren
suffix:semicolon
id|mouse-&gt;dev.relbit
(braket
l_int|0
)braket
op_or_assign
id|BIT
c_func
(paren
id|REL_WHEEL
)paren
suffix:semicolon
id|mouse-&gt;dev
dot
r_private
op_assign
id|mouse
suffix:semicolon
id|mouse-&gt;dev.open
op_assign
id|usb_mouse_open
suffix:semicolon
id|mouse-&gt;dev.close
op_assign
id|usb_mouse_close
suffix:semicolon
id|usb_make_path
c_func
(paren
id|dev
comma
id|path
comma
l_int|64
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|mouse-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|path
)paren
suffix:semicolon
id|mouse-&gt;dev.name
op_assign
id|mouse-&gt;name
suffix:semicolon
id|mouse-&gt;dev.phys
op_assign
id|mouse-&gt;phys
suffix:semicolon
id|mouse-&gt;dev.id.bustype
op_assign
id|BUS_USB
suffix:semicolon
id|mouse-&gt;dev.id.vendor
op_assign
id|dev-&gt;descriptor.idVendor
suffix:semicolon
id|mouse-&gt;dev.id.product
op_assign
id|dev-&gt;descriptor.idProduct
suffix:semicolon
id|mouse-&gt;dev.id.version
op_assign
id|dev-&gt;descriptor.bcdDevice
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|buf
op_assign
id|kmalloc
c_func
(paren
l_int|63
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|usb_buffer_free
c_func
(paren
id|dev
comma
l_int|8
comma
id|mouse-&gt;data
comma
id|mouse-&gt;data_dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mouse
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;descriptor.iManufacturer
op_logical_and
id|usb_string
c_func
(paren
id|dev
comma
id|dev-&gt;descriptor.iManufacturer
comma
id|buf
comma
l_int|63
)paren
OG
l_int|0
)paren
id|strcat
c_func
(paren
id|mouse-&gt;name
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;descriptor.iProduct
op_logical_and
id|usb_string
c_func
(paren
id|dev
comma
id|dev-&gt;descriptor.iProduct
comma
id|buf
comma
l_int|63
)paren
OG
l_int|0
)paren
id|sprintf
c_func
(paren
id|mouse-&gt;name
comma
l_string|&quot;%s %s&quot;
comma
id|mouse-&gt;name
comma
id|buf
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|strlen
c_func
(paren
id|mouse-&gt;name
)paren
)paren
id|sprintf
c_func
(paren
id|mouse-&gt;name
comma
l_string|&quot;USB HIDBP Mouse %04x:%04x&quot;
comma
id|mouse-&gt;dev.id.vendor
comma
id|mouse-&gt;dev.id.product
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|usb_fill_int_urb
c_func
(paren
id|mouse-&gt;irq
comma
id|dev
comma
id|pipe
comma
id|mouse-&gt;data
comma
(paren
id|maxp
OG
l_int|8
ques
c_cond
l_int|8
suffix:colon
id|maxp
)paren
comma
id|usb_mouse_irq
comma
id|mouse
comma
id|endpoint-&gt;bInterval
)paren
suffix:semicolon
id|mouse-&gt;irq-&gt;transfer_dma
op_assign
id|mouse-&gt;data_dma
suffix:semicolon
id|mouse-&gt;irq-&gt;transfer_flags
op_or_assign
id|URB_NO_DMA_MAP
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|mouse-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|mouse-&gt;name
comma
id|path
)paren
suffix:semicolon
r_return
id|mouse
suffix:semicolon
)brace
DECL|function|usb_mouse_disconnect
r_static
r_void
id|usb_mouse_disconnect
c_func
(paren
r_struct
id|usb_device
op_star
id|dev
comma
r_void
op_star
id|ptr
)paren
(brace
r_struct
id|usb_mouse
op_star
id|mouse
op_assign
id|ptr
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|mouse-&gt;irq
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|mouse-&gt;dev
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|mouse-&gt;irq
)paren
suffix:semicolon
id|usb_buffer_free
c_func
(paren
id|dev
comma
l_int|8
comma
id|mouse-&gt;data
comma
id|mouse-&gt;data_dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mouse
)paren
suffix:semicolon
)brace
DECL|variable|usb_mouse_id_table
r_static
r_struct
id|usb_device_id
id|usb_mouse_id_table
(braket
)braket
op_assign
(brace
(brace
id|USB_INTERFACE_INFO
c_func
(paren
l_int|3
comma
l_int|1
comma
l_int|2
)paren
)brace
comma
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|usb_mouse_id_table
)paren
suffix:semicolon
DECL|variable|usb_mouse_driver
r_static
r_struct
id|usb_driver
id|usb_mouse_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;usb_mouse&quot;
comma
dot
id|probe
op_assign
id|usb_mouse_probe
comma
dot
id|disconnect
op_assign
id|usb_mouse_disconnect
comma
dot
id|id_table
op_assign
id|usb_mouse_id_table
comma
)brace
suffix:semicolon
DECL|function|usb_mouse_init
r_static
r_int
id|__init
id|usb_mouse_init
c_func
(paren
r_void
)paren
(brace
id|usb_register
c_func
(paren
op_amp
id|usb_mouse_driver
)paren
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_VERSION
l_string|&quot;:&quot;
id|DRIVER_DESC
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_mouse_exit
r_static
r_void
id|__exit
id|usb_mouse_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|usb_mouse_driver
)paren
suffix:semicolon
)brace
DECL|variable|usb_mouse_init
id|module_init
c_func
(paren
id|usb_mouse_init
)paren
suffix:semicolon
DECL|variable|usb_mouse_exit
id|module_exit
c_func
(paren
id|usb_mouse_exit
)paren
suffix:semicolon
eof
