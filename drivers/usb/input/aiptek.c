multiline_comment|/*&n; *  Native support for the Aiptek 8000U&n; *&n; *  Copyright (c) 2001 Chris Atenasio&t;&t;&lt;chris@crud.net&gt;&n; *&n; *  based on wacom.c by&n; *     Vojtech Pavlik      &lt;vojtech@suse.cz&gt;&n; *     Andreas Bach Aaen   &lt;abach@stofanet.dk&gt;&n; *     Clifford Wolf       &lt;clifford@clifford.at&gt;&n; *     Sam Mosel           &lt;sam.mosel@computer.org&gt;&n; *     James E. Blair      &lt;corvus@gnu.org&gt;&n; *     Daniel Egger        &lt;egger@suse.de&gt;&n; *&n; *&n; *  Many thanks to Oliver Kuechemann for his support.&n; *&n; *  ChangeLog:&n; *      v0.1 - Initial release&n; *      v0.2 - Hack to get around fake event 28&squot;s.&n; *      v0.3 - Make URB dynamic (Bryan W. Headley, Jun-8-2002)&n; *             (kernel 2.5.x variant, June-14-2002)&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;v0.3&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Chris Atenasio &lt;chris@crud.net&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB Aiptek 6000U/8000U tablet driver (Linux 2.5.x)&quot;
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
multiline_comment|/*&n; * Aiptek status packet:&n; *&n; *        bit7  bit6  bit5  bit4  bit3  bit2  bit1  bit0&n; * byte0   0     0     0     0     0     0     1     0&n; * byte1  X7    X6    X5    X4    X3    X2    X1    X0&n; * byte2  X15   X14   X13   X12   X11   X10   X9    X8&n; * byte3  Y7    Y6    Y5    Y4    Y3    Y2    Y1    Y0&n; * byte4  Y15   Y14   Y13   Y12   Y11   Y10   Y9    Y8&n; * byte5   *     *     *    BS2   BS1   Tip   DV    IR&n; * byte6  P7    P6    P5    P4    P3    P2    P1    P0&n; * byte7  P15   P14   P13   P12   P11   P10   P9    P8&n; *&n; * IR: In Range = Proximity on&n; * DV = Data Valid&n; *&n; * &n; * Command Summary:&n; *&n; * Command/Data    Description     Return Bytes    Return Value&n; * 0x10/0x00       SwitchToMouse       0&n; * 0x10/0x01       SwitchToTablet      0&n; * 0x18/0x04       Resolution500LPI    0&n; * 0x17/0x00       FilterOn            0&n; * 0x12/0xFF       AutoGainOn          0&n; * 0x01/0x00       GetXExtension       2           MaxX&n; * 0x01/0x01       GetYExtension       2           MaxY&n; * 0x02/0x00       GetModelCode        2           ModelCode = LOBYTE&n; * 0x03/0x00       GetODMCode          2           ODMCode&n; * 0x08/0x00       GetPressureLevels   2           =512&n; * 0x04/0x00       GetFirmwareVersion  2           Firmware Version&n; *&n; *&n; * To initialize the tablet:&n; *&n; * (1) Send command Resolution500LPI&n; * (2) Option Commands (GetXExtension, GetYExtension)&n; * (3) Send command SwitchToTablet&n; */
DECL|macro|USB_VENDOR_ID_AIPTEK
mdefine_line|#define USB_VENDOR_ID_AIPTEK   0x08ca
DECL|struct|aiptek_features
r_struct
id|aiptek_features
(brace
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|pktlen
r_int
id|pktlen
suffix:semicolon
DECL|member|x_max
r_int
id|x_max
suffix:semicolon
DECL|member|y_max
r_int
id|y_max
suffix:semicolon
DECL|member|pressure_min
r_int
id|pressure_min
suffix:semicolon
DECL|member|pressure_max
r_int
id|pressure_max
suffix:semicolon
DECL|member|irq
r_void
(paren
op_star
id|irq
)paren
(paren
r_struct
id|urb
op_star
id|urb
)paren
suffix:semicolon
DECL|member|evbit
r_int
r_int
id|evbit
suffix:semicolon
DECL|member|absbit
r_int
r_int
id|absbit
suffix:semicolon
DECL|member|relbit
r_int
r_int
id|relbit
suffix:semicolon
DECL|member|btnbit
r_int
r_int
id|btnbit
suffix:semicolon
DECL|member|digibit
r_int
r_int
id|digibit
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|aiptek
r_struct
id|aiptek
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|usbdev
r_struct
id|usb_device
op_star
id|usbdev
suffix:semicolon
DECL|member|irq
r_struct
id|urb
op_star
id|irq
suffix:semicolon
DECL|member|features
r_struct
id|aiptek_features
op_star
id|features
suffix:semicolon
DECL|member|tool
r_int
id|tool
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
r_static
r_void
DECL|function|aiptek_irq
id|aiptek_irq
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|aiptek
op_star
id|aiptek
op_assign
id|urb-&gt;context
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|aiptek-&gt;data
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|aiptek-&gt;dev
suffix:semicolon
r_int
id|x
suffix:semicolon
r_int
id|y
suffix:semicolon
r_int
id|pressure
suffix:semicolon
r_int
id|proximity
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|2
)paren
op_eq
l_int|0
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;received unknown report #%d&quot;
comma
id|data
(braket
l_int|0
)braket
)paren
suffix:semicolon
)brace
id|proximity
op_assign
id|data
(braket
l_int|5
)braket
op_amp
l_int|0x01
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOOL_PEN
comma
id|proximity
)paren
suffix:semicolon
id|x
op_assign
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|1
)braket
)paren
op_or
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|2
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
id|y
op_assign
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|3
)braket
)paren
op_or
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|4
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
id|pressure
op_assign
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|6
)braket
)paren
op_or
(paren
(paren
id|__u32
)paren
id|data
(braket
l_int|7
)braket
op_lshift
l_int|8
)paren
suffix:semicolon
id|pressure
op_sub_assign
id|aiptek-&gt;features-&gt;pressure_min
suffix:semicolon
r_if
c_cond
(paren
id|pressure
OL
l_int|0
)paren
(brace
id|pressure
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|proximity
)paren
(brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
id|x
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Y
comma
id|y
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_PRESSURE
comma
id|pressure
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOUCH
comma
id|data
(braket
l_int|5
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
id|BTN_STYLUS
comma
id|data
(braket
l_int|5
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
id|BTN_STYLUS2
comma
id|data
(braket
l_int|5
)braket
op_amp
l_int|0x10
)paren
suffix:semicolon
)brace
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
DECL|variable|aiptek_features
r_struct
id|aiptek_features
id|aiptek_features
(braket
)braket
op_assign
(brace
(brace
l_string|&quot;Aiptek 6000U/8000U&quot;
comma
l_int|8
comma
l_int|3000
comma
l_int|2250
comma
l_int|26
comma
l_int|511
comma
id|aiptek_irq
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|NULL
comma
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|aiptek_ids
r_struct
id|usb_device_id
id|aiptek_ids
(braket
)braket
op_assign
(brace
(brace
id|USB_DEVICE
c_func
(paren
id|USB_VENDOR_ID_AIPTEK
comma
l_int|0x20
)paren
comma
dot
id|driver_info
op_assign
l_int|0
)brace
comma
(brace
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|usb
comma
id|aiptek_ids
)paren
suffix:semicolon
r_static
r_int
DECL|function|aiptek_open
id|aiptek_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|aiptek
op_star
id|aiptek
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|aiptek-&gt;open
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|aiptek-&gt;irq-&gt;dev
op_assign
id|aiptek-&gt;usbdev
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|aiptek-&gt;irq
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
r_static
r_void
DECL|function|aiptek_close
id|aiptek_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|aiptek
op_star
id|aiptek
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
id|aiptek-&gt;open
)paren
id|usb_unlink_urb
c_func
(paren
id|aiptek-&gt;irq
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|aiptek_command
id|aiptek_command
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
r_int
r_char
id|command
comma
r_int
r_char
id|data
)paren
(brace
id|__u8
id|buf
(braket
l_int|3
)braket
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
l_int|4
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|command
suffix:semicolon
id|buf
(braket
l_int|2
)braket
op_assign
id|data
suffix:semicolon
multiline_comment|/* &n;&t; * FIXME, either remove this call, or talk the maintainer into &n;&t; * adding it back into the core.&n;&t; */
macro_line|#if 0
r_if
c_cond
(paren
id|usb_set_report
c_func
(paren
id|dev
comma
id|ifnum
comma
l_int|3
comma
l_int|2
comma
id|buf
comma
l_int|3
)paren
op_ne
l_int|3
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;aiptek_command: 0x%x 0x%x&bslash;n&quot;
comma
id|command
comma
id|data
)paren
suffix:semicolon
)brace
macro_line|#endif
)brace
r_static
r_void
op_star
DECL|function|aiptek_probe
id|aiptek_probe
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
id|usb_endpoint_descriptor
op_star
id|endpoint
suffix:semicolon
r_struct
id|aiptek
op_star
id|aiptek
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|aiptek
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|aiptek
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
id|aiptek
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|aiptek
)paren
)paren
suffix:semicolon
id|aiptek-&gt;data
op_assign
id|usb_buffer_alloc
c_func
(paren
id|dev
comma
l_int|10
comma
id|SLAB_ATOMIC
comma
op_amp
id|aiptek-&gt;data_dma
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|aiptek-&gt;data
)paren
(brace
id|kfree
c_func
(paren
id|aiptek
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|aiptek-&gt;irq
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
id|aiptek-&gt;irq
)paren
(brace
id|usb_buffer_free
c_func
(paren
id|dev
comma
l_int|10
comma
id|aiptek-&gt;data
comma
id|aiptek-&gt;data_dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|aiptek
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
singleline_comment|// Resolution500LPI
id|aiptek_command
c_func
(paren
id|dev
comma
id|ifnum
comma
l_int|0x18
comma
l_int|0x04
)paren
suffix:semicolon
singleline_comment|// SwitchToTablet
id|aiptek_command
c_func
(paren
id|dev
comma
id|ifnum
comma
l_int|0x10
comma
l_int|0x01
)paren
suffix:semicolon
id|aiptek-&gt;features
op_assign
id|aiptek_features
op_plus
id|id-&gt;driver_info
suffix:semicolon
id|aiptek-&gt;dev.evbit
(braket
l_int|0
)braket
op_or_assign
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
op_or
id|BIT
c_func
(paren
id|EV_MSC
)paren
op_or
id|aiptek-&gt;features-&gt;evbit
suffix:semicolon
id|aiptek-&gt;dev.absbit
(braket
l_int|0
)braket
op_or_assign
id|BIT
c_func
(paren
id|ABS_X
)paren
op_or
id|BIT
c_func
(paren
id|ABS_Y
)paren
op_or
id|BIT
c_func
(paren
id|ABS_PRESSURE
)paren
op_or
id|BIT
c_func
(paren
id|ABS_MISC
)paren
op_or
id|aiptek-&gt;features-&gt;absbit
suffix:semicolon
id|aiptek-&gt;dev.relbit
(braket
l_int|0
)braket
op_or_assign
id|aiptek-&gt;features-&gt;relbit
suffix:semicolon
id|aiptek-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_LEFT
)paren
)braket
op_or_assign
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
op_or
id|aiptek-&gt;features-&gt;btnbit
suffix:semicolon
id|aiptek-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_DIGI
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_TOOL_PEN
)paren
op_or
id|BIT
c_func
(paren
id|BTN_TOOL_MOUSE
)paren
op_or
id|BIT
c_func
(paren
id|BTN_TOUCH
)paren
op_or
id|BIT
c_func
(paren
id|BTN_STYLUS
)paren
op_or
id|BIT
c_func
(paren
id|BTN_STYLUS2
)paren
op_or
id|aiptek-&gt;features-&gt;digibit
suffix:semicolon
id|aiptek-&gt;dev.mscbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|MSC_SERIAL
)paren
suffix:semicolon
id|aiptek-&gt;dev.absmax
(braket
id|ABS_X
)braket
op_assign
id|aiptek-&gt;features-&gt;x_max
suffix:semicolon
id|aiptek-&gt;dev.absmax
(braket
id|ABS_Y
)braket
op_assign
id|aiptek-&gt;features-&gt;y_max
suffix:semicolon
id|aiptek-&gt;dev.absmax
(braket
id|ABS_PRESSURE
)braket
op_assign
id|aiptek-&gt;features-&gt;pressure_max
op_minus
id|aiptek-&gt;features-&gt;pressure_min
suffix:semicolon
id|aiptek-&gt;dev.absfuzz
(braket
id|ABS_X
)braket
op_assign
l_int|0
suffix:semicolon
id|aiptek-&gt;dev.absfuzz
(braket
id|ABS_Y
)braket
op_assign
l_int|0
suffix:semicolon
id|aiptek-&gt;dev
dot
r_private
op_assign
id|aiptek
suffix:semicolon
id|aiptek-&gt;dev.open
op_assign
id|aiptek_open
suffix:semicolon
id|aiptek-&gt;dev.close
op_assign
id|aiptek_close
suffix:semicolon
id|aiptek-&gt;dev.name
op_assign
id|aiptek-&gt;features-&gt;name
suffix:semicolon
id|aiptek-&gt;dev.id.bustype
op_assign
id|BUS_USB
suffix:semicolon
id|aiptek-&gt;dev.id.vendor
op_assign
id|dev-&gt;descriptor.idVendor
suffix:semicolon
id|aiptek-&gt;dev.id.product
op_assign
id|dev-&gt;descriptor.idProduct
suffix:semicolon
id|aiptek-&gt;dev.id.version
op_assign
id|dev-&gt;descriptor.bcdDevice
suffix:semicolon
id|aiptek-&gt;usbdev
op_assign
id|dev
suffix:semicolon
id|endpoint
op_assign
id|dev-&gt;config
(braket
l_int|0
)braket
dot
id|interface
(braket
id|ifnum
)braket
dot
id|altsetting
(braket
l_int|0
)braket
dot
id|endpoint
op_plus
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|aiptek-&gt;features-&gt;pktlen
OG
l_int|10
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|usb_fill_int_urb
c_func
(paren
id|aiptek-&gt;irq
comma
id|dev
comma
id|usb_rcvintpipe
c_func
(paren
id|dev
comma
id|endpoint-&gt;bEndpointAddress
)paren
comma
id|aiptek-&gt;data
comma
id|aiptek-&gt;features-&gt;pktlen
comma
id|aiptek-&gt;features-&gt;irq
comma
id|aiptek
comma
id|endpoint-&gt;bInterval
)paren
suffix:semicolon
id|aiptek-&gt;irq-&gt;transfer_dma
op_assign
id|aiptek-&gt;data_dma
suffix:semicolon
id|aiptek-&gt;irq-&gt;transfer_flags
op_or_assign
id|URB_NO_DMA_MAP
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|aiptek-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on usb%d:%d.%d&bslash;n&quot;
comma
id|aiptek-&gt;features-&gt;name
comma
id|dev-&gt;bus-&gt;busnum
comma
id|dev-&gt;devnum
comma
id|ifnum
)paren
suffix:semicolon
r_return
id|aiptek
suffix:semicolon
)brace
r_static
r_void
DECL|function|aiptek_disconnect
id|aiptek_disconnect
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
id|aiptek
op_star
id|aiptek
op_assign
id|ptr
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|aiptek-&gt;irq
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|aiptek-&gt;dev
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|aiptek-&gt;irq
)paren
suffix:semicolon
id|usb_buffer_free
c_func
(paren
id|dev
comma
l_int|10
comma
id|aiptek-&gt;data
comma
id|aiptek-&gt;data_dma
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|aiptek
)paren
suffix:semicolon
)brace
DECL|variable|aiptek_driver
r_static
r_struct
id|usb_driver
id|aiptek_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;aiptek&quot;
comma
dot
id|probe
op_assign
id|aiptek_probe
comma
dot
id|disconnect
op_assign
id|aiptek_disconnect
comma
dot
id|id_table
op_assign
id|aiptek_ids
comma
)brace
suffix:semicolon
r_static
r_int
id|__init
DECL|function|aiptek_init
id|aiptek_init
c_func
(paren
r_void
)paren
(brace
id|usb_register
c_func
(paren
op_amp
id|aiptek_driver
)paren
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_VERSION
l_string|&quot; &quot;
id|DRIVER_AUTHOR
)paren
suffix:semicolon
id|info
c_func
(paren
id|DRIVER_DESC
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
id|__exit
DECL|function|aiptek_exit
id|aiptek_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|aiptek_driver
)paren
suffix:semicolon
)brace
DECL|variable|aiptek_init
id|module_init
c_func
(paren
id|aiptek_init
)paren
suffix:semicolon
DECL|variable|aiptek_exit
id|module_exit
c_func
(paren
id|aiptek_exit
)paren
suffix:semicolon
eof
