multiline_comment|/*&n; * $Id: usbkbd.c,v 1.27 2001/12/27 10:37:41 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; *&n; *  USB HIDBP Keyboard support&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
multiline_comment|/*&n; * Version Information&n; */
DECL|macro|DRIVER_VERSION
mdefine_line|#define DRIVER_VERSION &quot;&quot;
DECL|macro|DRIVER_AUTHOR
mdefine_line|#define DRIVER_AUTHOR &quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
DECL|macro|DRIVER_DESC
mdefine_line|#define DRIVER_DESC &quot;USB HID Boot Protocol keyboard driver&quot;
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
DECL|variable|usb_kbd_keycode
r_static
r_int
r_char
id|usb_kbd_keycode
(braket
l_int|256
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|30
comma
l_int|48
comma
l_int|46
comma
l_int|32
comma
l_int|18
comma
l_int|33
comma
l_int|34
comma
l_int|35
comma
l_int|23
comma
l_int|36
comma
l_int|37
comma
l_int|38
comma
l_int|50
comma
l_int|49
comma
l_int|24
comma
l_int|25
comma
l_int|16
comma
l_int|19
comma
l_int|31
comma
l_int|20
comma
l_int|22
comma
l_int|47
comma
l_int|17
comma
l_int|45
comma
l_int|21
comma
l_int|44
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|28
comma
l_int|1
comma
l_int|14
comma
l_int|15
comma
l_int|57
comma
l_int|12
comma
l_int|13
comma
l_int|26
comma
l_int|27
comma
l_int|43
comma
l_int|84
comma
l_int|39
comma
l_int|40
comma
l_int|41
comma
l_int|51
comma
l_int|52
comma
l_int|53
comma
l_int|58
comma
l_int|59
comma
l_int|60
comma
l_int|61
comma
l_int|62
comma
l_int|63
comma
l_int|64
comma
l_int|65
comma
l_int|66
comma
l_int|67
comma
l_int|68
comma
l_int|87
comma
l_int|88
comma
l_int|99
comma
l_int|70
comma
l_int|119
comma
l_int|110
comma
l_int|102
comma
l_int|104
comma
l_int|111
comma
l_int|107
comma
l_int|109
comma
l_int|106
comma
l_int|105
comma
l_int|108
comma
l_int|103
comma
l_int|69
comma
l_int|98
comma
l_int|55
comma
l_int|74
comma
l_int|78
comma
l_int|96
comma
l_int|79
comma
l_int|80
comma
l_int|81
comma
l_int|75
comma
l_int|76
comma
l_int|77
comma
l_int|71
comma
l_int|72
comma
l_int|73
comma
l_int|82
comma
l_int|83
comma
l_int|86
comma
l_int|127
comma
l_int|116
comma
l_int|117
comma
l_int|85
comma
l_int|89
comma
l_int|90
comma
l_int|91
comma
l_int|92
comma
l_int|93
comma
l_int|94
comma
l_int|95
comma
l_int|120
comma
l_int|121
comma
l_int|122
comma
l_int|123
comma
l_int|134
comma
l_int|138
comma
l_int|130
comma
l_int|132
comma
l_int|128
comma
l_int|129
comma
l_int|131
comma
l_int|137
comma
l_int|133
comma
l_int|135
comma
l_int|136
comma
l_int|113
comma
l_int|115
comma
l_int|114
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|124
comma
l_int|0
comma
l_int|181
comma
l_int|182
comma
l_int|183
comma
l_int|184
comma
l_int|185
comma
l_int|186
comma
l_int|187
comma
l_int|188
comma
l_int|189
comma
l_int|190
comma
l_int|191
comma
l_int|192
comma
l_int|193
comma
l_int|194
comma
l_int|195
comma
l_int|196
comma
l_int|197
comma
l_int|198
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|29
comma
l_int|42
comma
l_int|56
comma
l_int|125
comma
l_int|97
comma
l_int|54
comma
l_int|100
comma
l_int|126
comma
l_int|164
comma
l_int|166
comma
l_int|165
comma
l_int|163
comma
l_int|161
comma
l_int|115
comma
l_int|114
comma
l_int|113
comma
l_int|150
comma
l_int|158
comma
l_int|159
comma
l_int|128
comma
l_int|136
comma
l_int|177
comma
l_int|178
comma
l_int|176
comma
l_int|142
comma
l_int|152
comma
l_int|173
comma
l_int|140
)brace
suffix:semicolon
DECL|struct|usb_kbd
r_struct
id|usb_kbd
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
DECL|member|new
r_int
r_char
r_new
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|old
r_int
r_char
id|old
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|irq
DECL|member|led
r_struct
id|urb
op_star
id|irq
comma
op_star
id|led
suffix:semicolon
DECL|member|cr
r_struct
id|usb_ctrlrequest
id|cr
suffix:semicolon
DECL|member|leds
DECL|member|newleds
r_int
r_char
id|leds
comma
id|newleds
suffix:semicolon
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
DECL|member|open
r_int
id|open
suffix:semicolon
)brace
suffix:semicolon
DECL|function|usb_kbd_irq
r_static
r_void
id|usb_kbd_irq
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usb_kbd
op_star
id|kbd
op_assign
id|urb-&gt;context
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
r_return
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|input_report_key
c_func
(paren
op_amp
id|kbd-&gt;dev
comma
id|usb_kbd_keycode
(braket
id|i
op_plus
l_int|224
)braket
comma
(paren
id|kbd
op_member_access_from_pointer
r_new
(braket
l_int|0
)braket
op_rshift
id|i
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|2
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|kbd-&gt;old
(braket
id|i
)braket
OG
l_int|3
op_logical_and
id|memscan
c_func
(paren
id|kbd
op_member_access_from_pointer
r_new
op_plus
l_int|2
comma
id|kbd-&gt;old
(braket
id|i
)braket
comma
l_int|6
)paren
op_eq
id|kbd
op_member_access_from_pointer
r_new
op_plus
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|usb_kbd_keycode
(braket
id|kbd-&gt;old
(braket
id|i
)braket
)braket
)paren
id|input_report_key
c_func
(paren
op_amp
id|kbd-&gt;dev
comma
id|usb_kbd_keycode
(braket
id|kbd-&gt;old
(braket
id|i
)braket
)braket
comma
l_int|0
)paren
suffix:semicolon
r_else
id|info
c_func
(paren
l_string|&quot;Unknown key (scancode %#x) released.&quot;
comma
id|kbd-&gt;old
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|kbd
op_member_access_from_pointer
r_new
(braket
id|i
)braket
OG
l_int|3
op_logical_and
id|memscan
c_func
(paren
id|kbd-&gt;old
op_plus
l_int|2
comma
id|kbd
op_member_access_from_pointer
r_new
(braket
id|i
)braket
comma
l_int|6
)paren
op_eq
id|kbd-&gt;old
op_plus
l_int|8
)paren
(brace
r_if
c_cond
(paren
id|usb_kbd_keycode
(braket
id|kbd
op_member_access_from_pointer
r_new
(braket
id|i
)braket
)braket
)paren
id|input_report_key
c_func
(paren
op_amp
id|kbd-&gt;dev
comma
id|usb_kbd_keycode
(braket
id|kbd
op_member_access_from_pointer
r_new
(braket
id|i
)braket
)braket
comma
l_int|1
)paren
suffix:semicolon
r_else
id|info
c_func
(paren
l_string|&quot;Unknown key (scancode %#x) pressed.&quot;
comma
id|kbd
op_member_access_from_pointer
r_new
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
)brace
id|memcpy
c_func
(paren
id|kbd-&gt;old
comma
id|kbd
op_member_access_from_pointer
r_new
comma
l_int|8
)paren
suffix:semicolon
)brace
DECL|function|usb_kbd_event
r_int
id|usb_kbd_event
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
comma
r_int
r_int
id|type
comma
r_int
r_int
id|code
comma
r_int
id|value
)paren
(brace
r_struct
id|usb_kbd
op_star
id|kbd
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|type
op_ne
id|EV_LED
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|kbd-&gt;newleds
op_assign
(paren
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|LED_KANA
comma
id|dev-&gt;led
)paren
op_lshift
l_int|3
)paren
op_or
(paren
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|LED_COMPOSE
comma
id|dev-&gt;led
)paren
op_lshift
l_int|3
)paren
op_or
(paren
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|LED_SCROLLL
comma
id|dev-&gt;led
)paren
op_lshift
l_int|2
)paren
op_or
(paren
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|LED_CAPSL
comma
id|dev-&gt;led
)paren
op_lshift
l_int|1
)paren
op_or
(paren
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|LED_NUML
comma
id|dev-&gt;led
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kbd-&gt;led-&gt;status
op_eq
op_minus
id|EINPROGRESS
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|kbd-&gt;leds
op_eq
id|kbd-&gt;newleds
)paren
r_return
l_int|0
suffix:semicolon
id|kbd-&gt;leds
op_assign
id|kbd-&gt;newleds
suffix:semicolon
id|kbd-&gt;led-&gt;dev
op_assign
id|kbd-&gt;usbdev
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|kbd-&gt;led
comma
id|GFP_ATOMIC
)paren
)paren
id|err
c_func
(paren
l_string|&quot;usb_submit_urb(leds) failed&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|usb_kbd_led
r_static
r_void
id|usb_kbd_led
c_func
(paren
r_struct
id|urb
op_star
id|urb
)paren
(brace
r_struct
id|usb_kbd
op_star
id|kbd
op_assign
id|urb-&gt;context
suffix:semicolon
r_if
c_cond
(paren
id|urb-&gt;status
)paren
id|warn
c_func
(paren
l_string|&quot;led urb status %d received&quot;
comma
id|urb-&gt;status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|kbd-&gt;leds
op_eq
id|kbd-&gt;newleds
)paren
r_return
suffix:semicolon
id|kbd-&gt;leds
op_assign
id|kbd-&gt;newleds
suffix:semicolon
id|kbd-&gt;led-&gt;dev
op_assign
id|kbd-&gt;usbdev
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|kbd-&gt;led
comma
id|GFP_ATOMIC
)paren
)paren
id|err
c_func
(paren
l_string|&quot;usb_submit_urb(leds) failed&quot;
)paren
suffix:semicolon
)brace
DECL|function|usb_kbd_open
r_static
r_int
id|usb_kbd_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|usb_kbd
op_star
id|kbd
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|kbd-&gt;open
op_increment
)paren
r_return
l_int|0
suffix:semicolon
id|kbd-&gt;irq-&gt;dev
op_assign
id|kbd-&gt;usbdev
suffix:semicolon
r_if
c_cond
(paren
id|usb_submit_urb
c_func
(paren
id|kbd-&gt;irq
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
DECL|function|usb_kbd_close
r_static
r_void
id|usb_kbd_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|usb_kbd
op_star
id|kbd
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
id|kbd-&gt;open
)paren
id|usb_unlink_urb
c_func
(paren
id|kbd-&gt;irq
)paren
suffix:semicolon
)brace
DECL|function|usb_kbd_probe
r_static
r_void
op_star
id|usb_kbd_probe
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
id|usb_kbd
op_star
id|kbd
suffix:semicolon
r_int
id|i
comma
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
id|kbd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|usb_kbd
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
id|kbd
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|usb_kbd
)paren
)paren
suffix:semicolon
id|kbd-&gt;irq
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
id|kbd-&gt;irq
)paren
(brace
id|kfree
c_func
(paren
id|kbd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|kbd-&gt;led
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
id|kbd-&gt;led
)paren
(brace
id|usb_free_urb
c_func
(paren
id|kbd-&gt;irq
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbd
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|kbd-&gt;usbdev
op_assign
id|dev
suffix:semicolon
id|kbd-&gt;dev.evbit
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
id|EV_LED
)paren
op_or
id|BIT
c_func
(paren
id|EV_REP
)paren
suffix:semicolon
id|kbd-&gt;dev.ledbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|LED_NUML
)paren
op_or
id|BIT
c_func
(paren
id|LED_CAPSL
)paren
op_or
id|BIT
c_func
(paren
id|LED_SCROLLL
)paren
op_or
id|BIT
c_func
(paren
id|LED_COMPOSE
)paren
op_or
id|BIT
c_func
(paren
id|LED_KANA
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|255
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|usb_kbd_keycode
(braket
id|i
)braket
comma
id|kbd-&gt;dev.keybit
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
id|kbd-&gt;dev.keybit
)paren
suffix:semicolon
id|kbd-&gt;dev
dot
r_private
op_assign
id|kbd
suffix:semicolon
id|kbd-&gt;dev.event
op_assign
id|usb_kbd_event
suffix:semicolon
id|kbd-&gt;dev.open
op_assign
id|usb_kbd_open
suffix:semicolon
id|kbd-&gt;dev.close
op_assign
id|usb_kbd_close
suffix:semicolon
id|FILL_INT_URB
c_func
(paren
id|kbd-&gt;irq
comma
id|dev
comma
id|pipe
comma
id|kbd
op_member_access_from_pointer
r_new
comma
id|maxp
OG
l_int|8
ques
c_cond
l_int|8
suffix:colon
id|maxp
comma
id|usb_kbd_irq
comma
id|kbd
comma
id|endpoint-&gt;bInterval
)paren
suffix:semicolon
id|kbd-&gt;cr.bRequestType
op_assign
id|USB_TYPE_CLASS
op_or
id|USB_RECIP_INTERFACE
suffix:semicolon
id|kbd-&gt;cr.bRequest
op_assign
l_int|0x09
suffix:semicolon
id|kbd-&gt;cr.wValue
op_assign
l_int|0x200
suffix:semicolon
id|kbd-&gt;cr.wIndex
op_assign
id|interface-&gt;bInterfaceNumber
suffix:semicolon
id|kbd-&gt;cr.wLength
op_assign
l_int|1
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
id|kbd-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|path
)paren
suffix:semicolon
id|kbd-&gt;dev.name
op_assign
id|kbd-&gt;name
suffix:semicolon
id|kbd-&gt;dev.phys
op_assign
id|kbd-&gt;phys
suffix:semicolon
id|kbd-&gt;dev.idbus
op_assign
id|BUS_USB
suffix:semicolon
id|kbd-&gt;dev.idvendor
op_assign
id|dev-&gt;descriptor.idVendor
suffix:semicolon
id|kbd-&gt;dev.idproduct
op_assign
id|dev-&gt;descriptor.idProduct
suffix:semicolon
id|kbd-&gt;dev.idversion
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
id|kfree
c_func
(paren
id|kbd
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
id|kbd-&gt;name
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
id|kbd-&gt;name
comma
l_string|&quot;%s %s&quot;
comma
id|kbd-&gt;name
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
id|kbd-&gt;name
)paren
)paren
id|sprintf
c_func
(paren
id|kbd-&gt;name
comma
l_string|&quot;USB HIDBP Keyboard %04x:%04x&quot;
comma
id|kbd-&gt;dev.idvendor
comma
id|kbd-&gt;dev.idproduct
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|buf
)paren
suffix:semicolon
id|FILL_CONTROL_URB
c_func
(paren
id|kbd-&gt;led
comma
id|dev
comma
id|usb_sndctrlpipe
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
id|kbd-&gt;cr
comma
op_amp
id|kbd-&gt;leds
comma
l_int|1
comma
id|usb_kbd_led
comma
id|kbd
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|kbd-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|kbd-&gt;name
comma
id|path
)paren
suffix:semicolon
r_return
id|kbd
suffix:semicolon
)brace
DECL|function|usb_kbd_disconnect
r_static
r_void
id|usb_kbd_disconnect
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
id|usb_kbd
op_star
id|kbd
op_assign
id|ptr
suffix:semicolon
id|usb_unlink_urb
c_func
(paren
id|kbd-&gt;irq
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|kbd-&gt;dev
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|kbd-&gt;irq
)paren
suffix:semicolon
id|usb_free_urb
c_func
(paren
id|kbd-&gt;led
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|kbd
)paren
suffix:semicolon
)brace
DECL|variable|usb_kbd_id_table
r_static
r_struct
id|usb_device_id
id|usb_kbd_id_table
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
l_int|1
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
id|usb_kbd_id_table
)paren
suffix:semicolon
DECL|variable|usb_kbd_driver
r_static
r_struct
id|usb_driver
id|usb_kbd_driver
op_assign
(brace
id|name
suffix:colon
l_string|&quot;keyboard&quot;
comma
id|probe
suffix:colon
id|usb_kbd_probe
comma
id|disconnect
suffix:colon
id|usb_kbd_disconnect
comma
id|id_table
suffix:colon
id|usb_kbd_id_table
comma
)brace
suffix:semicolon
DECL|function|usb_kbd_init
r_static
r_int
id|__init
id|usb_kbd_init
c_func
(paren
r_void
)paren
(brace
id|usb_register
c_func
(paren
op_amp
id|usb_kbd_driver
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
DECL|function|usb_kbd_exit
r_static
r_void
id|__exit
id|usb_kbd_exit
c_func
(paren
r_void
)paren
(brace
id|usb_deregister
c_func
(paren
op_amp
id|usb_kbd_driver
)paren
suffix:semicolon
)brace
DECL|variable|usb_kbd_init
id|module_init
c_func
(paren
id|usb_kbd_init
)paren
suffix:semicolon
DECL|variable|usb_kbd_exit
id|module_exit
c_func
(paren
id|usb_kbd_exit
)paren
suffix:semicolon
eof