multiline_comment|/*&n; * $Id: iforce-usb.c,v 1.16 2002/06/09 11:08:04 jdeneux Exp $&n; *&n; *  Copyright (c) 2000-2002 Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&n; *  Copyright (c) 2001-2002 Johann Deneux &lt;deneux@ifrance.com&gt;&n; *&n; *  USB/RS232 I-Force joysticks and wheels.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &quot;iforce.h&quot;
DECL|function|iforce_usb_xmit
r_void
id|iforce_usb_xmit
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
)paren
(brace
r_int
id|n
comma
id|c
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|iforce-&gt;xmit_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iforce-&gt;xmit.head
op_eq
id|iforce-&gt;xmit.tail
)paren
(brace
id|clear_bit
c_func
(paren
id|IFORCE_XMIT_RUNNING
comma
id|iforce-&gt;xmit_flags
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iforce-&gt;xmit_lock
comma
id|flags
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
(paren
(paren
r_char
op_star
)paren
id|iforce-&gt;out-&gt;transfer_buffer
)paren
(braket
l_int|0
)braket
op_assign
id|iforce-&gt;xmit.buf
(braket
id|iforce-&gt;xmit.tail
)braket
suffix:semicolon
id|XMIT_INC
c_func
(paren
id|iforce-&gt;xmit.tail
comma
l_int|1
)paren
suffix:semicolon
id|n
op_assign
id|iforce-&gt;xmit.buf
(braket
id|iforce-&gt;xmit.tail
)braket
suffix:semicolon
id|XMIT_INC
c_func
(paren
id|iforce-&gt;xmit.tail
comma
l_int|1
)paren
suffix:semicolon
id|iforce-&gt;out-&gt;transfer_buffer_length
op_assign
id|n
op_plus
l_int|1
suffix:semicolon
id|iforce-&gt;out-&gt;dev
op_assign
id|iforce-&gt;usbdev
suffix:semicolon
multiline_comment|/* Copy rest of data then */
id|c
op_assign
id|CIRC_CNT_TO_END
c_func
(paren
id|iforce-&gt;xmit.head
comma
id|iforce-&gt;xmit.tail
comma
id|XMIT_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
OL
id|c
)paren
id|c
op_assign
id|n
suffix:semicolon
id|memcpy
c_func
(paren
id|iforce-&gt;out-&gt;transfer_buffer
op_plus
l_int|1
comma
op_amp
id|iforce-&gt;xmit.buf
(braket
id|iforce-&gt;xmit.tail
)braket
comma
id|c
)paren
suffix:semicolon
r_if
c_cond
(paren
id|n
op_ne
id|c
)paren
(brace
id|memcpy
c_func
(paren
id|iforce-&gt;out-&gt;transfer_buffer
op_plus
l_int|1
op_plus
id|c
comma
op_amp
id|iforce-&gt;xmit.buf
(braket
l_int|0
)braket
comma
id|n
op_minus
id|c
)paren
suffix:semicolon
)brace
id|XMIT_INC
c_func
(paren
id|iforce-&gt;xmit.tail
comma
id|n
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|n
op_assign
id|usb_submit_urb
c_func
(paren
id|iforce-&gt;out
comma
id|GFP_ATOMIC
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;iforce-usb.c: iforce_usb_xmit: usb_submit_urb failed %d&bslash;n&quot;
comma
id|n
)paren
suffix:semicolon
)brace
multiline_comment|/* The IFORCE_XMIT_RUNNING bit is not cleared here. That&squot;s intended.&n;&t; * As long as the urb completion handler is not called, the transmiting&n;&t; * is considered to be running */
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|iforce-&gt;xmit_lock
comma
id|flags
)paren
suffix:semicolon
)brace
DECL|function|iforce_usb_irq
r_static
r_void
id|iforce_usb_irq
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
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
id|iforce_process_packet
c_func
(paren
id|iforce
comma
(paren
id|iforce-&gt;data
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_or
(paren
id|urb-&gt;actual_length
op_minus
l_int|1
)paren
comma
id|iforce-&gt;data
op_plus
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|iforce_usb_out
r_static
r_void
id|iforce_usb_out
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
op_assign
id|urb-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;iforce_usb_out: urb-&gt;status %d, exiting&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|iforce_usb_xmit
c_func
(paren
id|iforce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|iforce-&gt;wait
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|iforce-&gt;wait
)paren
suffix:semicolon
)brace
DECL|function|iforce_usb_ctrl
r_static
r_void
id|iforce_usb_ctrl
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
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
id|iforce-&gt;ecmd
op_assign
l_int|0xff00
op_or
id|urb-&gt;actual_length
suffix:semicolon
r_if
c_cond
(paren
id|waitqueue_active
c_func
(paren
op_amp
id|iforce-&gt;wait
)paren
)paren
id|wake_up
c_func
(paren
op_amp
id|iforce-&gt;wait
)paren
suffix:semicolon
)brace
DECL|function|iforce_usb_probe
r_static
r_int
id|iforce_usb_probe
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
id|dev
op_assign
id|interface_to_usbdev
c_func
(paren
id|intf
)paren
suffix:semicolon
r_struct
id|usb_endpoint_descriptor
op_star
id|epirq
comma
op_star
id|epout
suffix:semicolon
r_struct
id|iforce
op_star
id|iforce
suffix:semicolon
id|epirq
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
id|epout
op_assign
id|intf-&gt;altsetting
(braket
l_int|0
)braket
dot
id|endpoint
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|iforce
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|iforce
)paren
op_plus
l_int|32
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|memset
c_func
(paren
id|iforce
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|iforce
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|iforce-&gt;irq
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|iforce-&gt;out
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|iforce-&gt;ctrl
op_assign
id|usb_alloc_urb
c_func
(paren
l_int|0
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
r_goto
id|fail
suffix:semicolon
)brace
id|iforce-&gt;bus
op_assign
id|IFORCE_USB
suffix:semicolon
id|iforce-&gt;usbdev
op_assign
id|dev
suffix:semicolon
id|iforce-&gt;cr.bRequestType
op_assign
id|USB_TYPE_VENDOR
op_or
id|USB_DIR_IN
op_or
id|USB_RECIP_INTERFACE
suffix:semicolon
id|iforce-&gt;cr.wIndex
op_assign
l_int|0
suffix:semicolon
id|iforce-&gt;cr.wLength
op_assign
l_int|16
suffix:semicolon
id|usb_fill_int_urb
c_func
(paren
id|iforce-&gt;irq
comma
id|dev
comma
id|usb_rcvintpipe
c_func
(paren
id|dev
comma
id|epirq-&gt;bEndpointAddress
)paren
comma
id|iforce-&gt;data
comma
l_int|16
comma
id|iforce_usb_irq
comma
id|iforce
comma
id|epirq-&gt;bInterval
)paren
suffix:semicolon
id|usb_fill_bulk_urb
c_func
(paren
id|iforce-&gt;out
comma
id|dev
comma
id|usb_sndbulkpipe
c_func
(paren
id|dev
comma
id|epout-&gt;bEndpointAddress
)paren
comma
id|iforce
op_plus
l_int|1
comma
l_int|32
comma
id|iforce_usb_out
comma
id|iforce
)paren
suffix:semicolon
id|usb_fill_control_urb
c_func
(paren
id|iforce-&gt;ctrl
comma
id|dev
comma
id|usb_rcvctrlpipe
c_func
(paren
id|dev
comma
l_int|0
)paren
comma
(paren
r_void
op_star
)paren
op_amp
id|iforce-&gt;cr
comma
id|iforce-&gt;edata
comma
l_int|16
comma
id|iforce_usb_ctrl
comma
id|iforce
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iforce_init_device
c_func
(paren
id|iforce
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|dev_set_drvdata
(paren
op_amp
id|intf-&gt;dev
comma
id|iforce
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|fail
suffix:colon
r_if
c_cond
(paren
id|iforce
)paren
(brace
r_if
c_cond
(paren
id|iforce-&gt;irq
)paren
id|usb_free_urb
c_func
(paren
id|iforce-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iforce-&gt;out
)paren
id|usb_free_urb
c_func
(paren
id|iforce-&gt;out
)paren
suffix:semicolon
r_if
c_cond
(paren
id|iforce-&gt;ctrl
)paren
id|usb_free_urb
c_func
(paren
id|iforce-&gt;ctrl
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|iforce
)paren
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* Called by iforce_delete() */
DECL|function|iforce_usb_delete
r_void
id|iforce_usb_delete
c_func
(paren
r_struct
id|iforce
op_star
id|iforce
)paren
(brace
id|usb_unlink_urb
c_func
(paren
id|iforce-&gt;irq
)paren
suffix:semicolon
multiline_comment|/* Is it ok to unlink those ? */
id|usb_unlink_urb
c_func
(paren
id|iforce-&gt;out
)paren
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|iforce-&gt;ctrl
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|iforce-&gt;irq
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|iforce-&gt;out
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|iforce-&gt;ctrl
)paren
suffix:semicolon
)brace
DECL|function|iforce_usb_disconnect
r_static
r_void
id|iforce_usb_disconnect
c_func
(paren
r_struct
id|usb_interface
op_star
id|intf
)paren
(brace
r_struct
id|iforce
op_star
id|iforce
op_assign
id|dev_get_drvdata
(paren
op_amp
id|intf-&gt;dev
)paren
suffix:semicolon
r_int
id|open
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* FIXME! iforce-&gt;dev.handle-&gt;open; */
id|dev_set_drvdata
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
id|iforce
)paren
(brace
id|iforce-&gt;usbdev
op_assign
l_int|NULL
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|iforce-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|open
)paren
(brace
id|iforce_delete_device
c_func
(paren
id|iforce
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|iforce
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|variable|iforce_usb_ids
r_static
r_struct
id|usb_device_id
id|iforce_usb_ids
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x044f
comma
l_int|0xa01c
)paren
)brace
comma
multiline_comment|/* Thrustmaster Motor Sport GT */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x046d
comma
l_int|0xc281
)paren
)brace
comma
multiline_comment|/* Logitech WingMan Force */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x046d
comma
l_int|0xc291
)paren
)brace
comma
multiline_comment|/* Logitech WingMan Formula Force */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x05ef
comma
l_int|0x020a
)paren
)brace
comma
multiline_comment|/* AVB Top Shot Pegasus */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x05ef
comma
l_int|0x8884
)paren
)brace
comma
multiline_comment|/* AVB Mag Turbo Force */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x05ef
comma
l_int|0x8888
)paren
)brace
comma
multiline_comment|/* AVB Top Shot FFB Racing Wheel */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x061c
comma
l_int|0xc0a4
)paren
)brace
comma
multiline_comment|/* ACT LABS Force RS */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06f8
comma
l_int|0x0001
)paren
)brace
comma
multiline_comment|/* Guillemot Race Leader Force Feedback */
(brace
id|USB_DEVICE
c_func
(paren
l_int|0x06f8
comma
l_int|0x0004
)paren
)brace
comma
multiline_comment|/* Guillemot Force Feedback Racing Wheel */
(brace
)brace
multiline_comment|/* Terminating entry */
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
(paren
id|usb
comma
id|iforce_usb_ids
)paren
suffix:semicolon
DECL|variable|iforce_usb_driver
r_struct
id|usb_driver
id|iforce_usb_driver
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
l_string|&quot;iforce&quot;
comma
dot
id|probe
op_assign
id|iforce_usb_probe
comma
dot
id|disconnect
op_assign
id|iforce_usb_disconnect
comma
dot
id|id_table
op_assign
id|iforce_usb_ids
comma
)brace
suffix:semicolon
eof
