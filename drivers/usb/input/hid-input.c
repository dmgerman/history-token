multiline_comment|/*&n; * $Id: hid-input.c,v 1.2 2002/04/23 00:59:25 rdamazio Exp $&n; *&n; *  Copyright (c) 2000-2001 Vojtech Pavlik&n; *&n; *  USB HID to Linux Input mapping&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;hid.h&quot;
DECL|macro|unk
mdefine_line|#define unk&t;KEY_UNKNOWN
DECL|variable|hid_keyboard
r_static
r_int
r_char
id|hid_keyboard
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
id|unk
comma
id|unk
comma
id|unk
comma
l_int|124
comma
id|unk
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
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
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
comma
id|unk
comma
id|unk
comma
id|unk
comma
id|unk
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|x
id|__s32
id|x
suffix:semicolon
DECL|member|y
id|__s32
id|y
suffix:semicolon
DECL|variable|hid_hat_to_axis
)brace
id|hid_hat_to_axis
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
op_minus
l_int|1
)brace
comma
(brace
l_int|1
comma
op_minus
l_int|1
)brace
comma
(brace
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|1
comma
l_int|1
)brace
comma
(brace
l_int|0
comma
l_int|1
)brace
comma
(brace
op_minus
l_int|1
comma
l_int|1
)brace
comma
(brace
op_minus
l_int|1
comma
l_int|0
)brace
comma
(brace
op_minus
l_int|1
comma
op_minus
l_int|1
)brace
)brace
suffix:semicolon
DECL|function|hidinput_configure_usage
r_static
r_void
id|hidinput_configure_usage
c_func
(paren
r_struct
id|hid_device
op_star
id|device
comma
r_struct
id|hid_field
op_star
id|field
comma
r_struct
id|hid_usage
op_star
id|usage
)paren
(brace
r_struct
id|input_dev
op_star
id|input
op_assign
op_amp
id|device-&gt;input
suffix:semicolon
r_int
id|max
suffix:semicolon
r_int
id|is_abs
op_assign
l_int|0
suffix:semicolon
r_int
r_int
op_star
id|bit
suffix:semicolon
r_switch
c_cond
(paren
id|usage-&gt;hid
op_amp
id|HID_USAGE_PAGE
)paren
(brace
r_case
id|HID_UP_KEYBOARD
suffix:colon
id|set_bit
c_func
(paren
id|EV_REP
comma
id|input-&gt;evbit
)paren
suffix:semicolon
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
r_if
c_cond
(paren
(paren
id|usage-&gt;hid
op_amp
id|HID_USAGE
)paren
OL
l_int|256
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|usage-&gt;code
op_assign
id|hid_keyboard
(braket
id|usage-&gt;hid
op_amp
id|HID_USAGE
)braket
)paren
)paren
r_return
suffix:semicolon
id|clear_bit
c_func
(paren
id|usage-&gt;code
comma
id|bit
)paren
suffix:semicolon
)brace
r_else
id|usage-&gt;code
op_assign
id|KEY_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HID_UP_BUTTON
suffix:colon
id|usage-&gt;code
op_assign
(paren
(paren
id|usage-&gt;hid
op_minus
l_int|1
)paren
op_amp
l_int|0xf
)paren
op_plus
l_int|0x100
suffix:semicolon
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
r_switch
c_cond
(paren
id|field-&gt;application
)paren
(brace
r_case
id|HID_GD_GAMEPAD
suffix:colon
id|usage-&gt;code
op_add_assign
l_int|0x10
suffix:semicolon
r_case
id|HID_GD_JOYSTICK
suffix:colon
id|usage-&gt;code
op_add_assign
l_int|0x10
suffix:semicolon
r_case
id|HID_GD_MOUSE
suffix:colon
id|usage-&gt;code
op_add_assign
l_int|0x10
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|field-&gt;physical
op_eq
id|HID_GD_POINTER
)paren
id|usage-&gt;code
op_add_assign
l_int|0x10
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HID_UP_GENDESK
suffix:colon
r_if
c_cond
(paren
(paren
id|usage-&gt;hid
op_amp
l_int|0xf0
)paren
op_eq
l_int|0x80
)paren
(brace
multiline_comment|/* SystemControl */
r_switch
c_cond
(paren
id|usage-&gt;hid
op_amp
l_int|0xf
)paren
(brace
r_case
l_int|0x1
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_POWER
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x2
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_SLEEP
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x3
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_WAKEUP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
r_break
suffix:semicolon
)brace
id|usage-&gt;code
op_assign
id|usage-&gt;hid
op_amp
l_int|0xf
suffix:semicolon
r_if
c_cond
(paren
id|field-&gt;report_size
op_eq
l_int|1
)paren
(brace
id|usage-&gt;code
op_assign
id|BTN_MISC
suffix:semicolon
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|field-&gt;flags
op_amp
id|HID_MAIN_ITEM_RELATIVE
)paren
(brace
id|usage-&gt;type
op_assign
id|EV_REL
suffix:semicolon
id|bit
op_assign
id|input-&gt;relbit
suffix:semicolon
id|max
op_assign
id|REL_MAX
suffix:semicolon
r_break
suffix:semicolon
)brace
id|usage-&gt;type
op_assign
id|EV_ABS
suffix:semicolon
id|bit
op_assign
id|input-&gt;absbit
suffix:semicolon
id|max
op_assign
id|ABS_MAX
suffix:semicolon
r_if
c_cond
(paren
id|usage-&gt;hid
op_eq
id|HID_GD_HATSWITCH
)paren
(brace
id|usage-&gt;code
op_assign
id|ABS_HAT0X
suffix:semicolon
id|usage-&gt;hat_min
op_assign
id|field-&gt;logical_minimum
suffix:semicolon
id|usage-&gt;hat_max
op_assign
id|field-&gt;logical_maximum
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HID_UP_LED
suffix:colon
id|usage-&gt;code
op_assign
(paren
id|usage-&gt;hid
op_minus
l_int|1
)paren
op_amp
l_int|0xf
suffix:semicolon
id|usage-&gt;type
op_assign
id|EV_LED
suffix:semicolon
id|bit
op_assign
id|input-&gt;ledbit
suffix:semicolon
id|max
op_assign
id|LED_MAX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HID_UP_DIGITIZER
suffix:colon
r_switch
c_cond
(paren
id|usage-&gt;hid
op_amp
l_int|0xff
)paren
(brace
r_case
l_int|0x30
suffix:colon
multiline_comment|/* TipPressure */
r_if
c_cond
(paren
op_logical_neg
id|test_bit
c_func
(paren
id|BTN_TOUCH
comma
id|input-&gt;keybit
)paren
)paren
(brace
id|device-&gt;quirks
op_or_assign
id|HID_QUIRK_NOTOUCH
suffix:semicolon
id|set_bit
c_func
(paren
id|EV_KEY
comma
id|input-&gt;evbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|BTN_TOUCH
comma
id|input-&gt;keybit
)paren
suffix:semicolon
)brace
id|usage-&gt;type
op_assign
id|EV_ABS
suffix:semicolon
id|bit
op_assign
id|input-&gt;absbit
suffix:semicolon
id|max
op_assign
id|ABS_MAX
suffix:semicolon
id|usage-&gt;code
op_assign
id|ABS_PRESSURE
suffix:semicolon
id|clear_bit
c_func
(paren
id|usage-&gt;code
comma
id|bit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x32
suffix:colon
multiline_comment|/* InRange */
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
r_switch
c_cond
(paren
id|field-&gt;physical
op_amp
l_int|0xff
)paren
(brace
r_case
l_int|0x21
suffix:colon
id|usage-&gt;code
op_assign
id|BTN_TOOL_MOUSE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x22
suffix:colon
id|usage-&gt;code
op_assign
id|BTN_TOOL_FINGER
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage-&gt;code
op_assign
id|BTN_TOOL_PEN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|0x3c
suffix:colon
multiline_comment|/* Invert */
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
id|usage-&gt;code
op_assign
id|BTN_TOOL_RUBBER
suffix:semicolon
id|clear_bit
c_func
(paren
id|usage-&gt;code
comma
id|bit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x33
suffix:colon
multiline_comment|/* Touch */
r_case
l_int|0x42
suffix:colon
multiline_comment|/* TipSwitch */
r_case
l_int|0x43
suffix:colon
multiline_comment|/* TipSwitch2 */
id|device-&gt;quirks
op_and_assign
op_complement
id|HID_QUIRK_NOTOUCH
suffix:semicolon
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
id|usage-&gt;code
op_assign
id|BTN_TOUCH
suffix:semicolon
id|clear_bit
c_func
(paren
id|usage-&gt;code
comma
id|bit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x44
suffix:colon
multiline_comment|/* BarrelSwitch */
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
id|usage-&gt;code
op_assign
id|BTN_STYLUS
suffix:semicolon
id|clear_bit
c_func
(paren
id|usage-&gt;code
comma
id|bit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
r_goto
id|unknown
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HID_UP_CONSUMER
suffix:colon
multiline_comment|/* USB HUT v1.1, pages 56-62 */
id|set_bit
c_func
(paren
id|EV_REP
comma
id|input-&gt;evbit
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|usage-&gt;hid
op_amp
id|HID_USAGE
)paren
(brace
r_case
l_int|0x000
suffix:colon
id|usage-&gt;code
op_assign
l_int|0
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x034
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_SLEEP
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x036
suffix:colon
id|usage-&gt;code
op_assign
id|BTN_MISC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x08a
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_WWW
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x095
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_HELP
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0b0
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_PLAY
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0b1
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_PAUSE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0b2
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_RECORD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0b3
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_FASTFORWARD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0b4
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_REWIND
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0b5
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_NEXTSONG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0b6
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_PREVIOUSSONG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0b7
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_STOPCD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0b8
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_EJECTCD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0cd
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_PLAYPAUSE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0e0
suffix:colon
id|is_abs
op_assign
l_int|1
suffix:semicolon
id|usage-&gt;code
op_assign
id|ABS_VOLUME
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0e2
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_MUTE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0e5
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_BASSBOOST
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0e9
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_VOLUMEUP
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x0ea
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_VOLUMEDOWN
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x183
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_CONFIG
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x18a
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_MAIL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x192
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_CALC
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x194
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_FILE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x21a
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_UNDO
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x21b
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_COPY
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x21c
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_CUT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x21d
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_PASTE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x221
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_FIND
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x223
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_HOMEPAGE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x224
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_BACK
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x225
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_FORWARD
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x226
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_STOP
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x227
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_REFRESH
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x22a
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_BOOKMARKS
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|is_abs
)paren
(brace
id|usage-&gt;type
op_assign
id|EV_ABS
suffix:semicolon
id|bit
op_assign
id|input-&gt;absbit
suffix:semicolon
id|max
op_assign
id|ABS_MAX
suffix:semicolon
)brace
r_else
(brace
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
id|HID_UP_HPVENDOR
suffix:colon
multiline_comment|/* Reported on a Dutch layout HP5308 */
id|set_bit
c_func
(paren
id|EV_REP
comma
id|input-&gt;evbit
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|usage-&gt;hid
op_amp
id|HID_USAGE
)paren
(brace
r_case
l_int|0x021
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_PRINT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x070
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_HP
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x071
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_CAMERA
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x072
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_SOUND
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x073
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_QUESTION
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x080
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_EMAIL
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x081
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_CHAT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x082
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_SEARCH
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x083
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_CONNECT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x084
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_FINANCE
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x085
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_SPORT
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x086
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_SHOP
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|usage-&gt;code
op_assign
id|KEY_UNKNOWN
suffix:semicolon
r_break
suffix:semicolon
)brace
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
r_break
suffix:semicolon
r_case
id|HID_UP_PID
suffix:colon
id|usage-&gt;type
op_assign
id|EV_FF
suffix:semicolon
id|bit
op_assign
id|input-&gt;ffbit
suffix:semicolon
id|max
op_assign
id|FF_MAX
suffix:semicolon
r_switch
c_cond
(paren
id|usage-&gt;hid
op_amp
id|HID_USAGE
)paren
(brace
r_case
l_int|0x26
suffix:colon
id|set_bit
c_func
(paren
id|FF_CONSTANT
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x27
suffix:colon
id|set_bit
c_func
(paren
id|FF_RAMP
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x28
suffix:colon
id|set_bit
c_func
(paren
id|FF_CUSTOM
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x30
suffix:colon
id|set_bit
c_func
(paren
id|FF_SQUARE
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|FF_PERIODIC
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x31
suffix:colon
id|set_bit
c_func
(paren
id|FF_SINE
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|FF_PERIODIC
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x32
suffix:colon
id|set_bit
c_func
(paren
id|FF_TRIANGLE
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|FF_PERIODIC
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x33
suffix:colon
id|set_bit
c_func
(paren
id|FF_SAW_UP
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|FF_PERIODIC
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x34
suffix:colon
id|set_bit
c_func
(paren
id|FF_SAW_DOWN
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
id|set_bit
c_func
(paren
id|FF_PERIODIC
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x40
suffix:colon
id|set_bit
c_func
(paren
id|FF_SPRING
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x41
suffix:colon
id|set_bit
c_func
(paren
id|FF_DAMPER
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x42
suffix:colon
id|set_bit
c_func
(paren
id|FF_INERTIA
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x43
suffix:colon
id|set_bit
c_func
(paren
id|FF_FRICTION
comma
id|input-&gt;ffbit
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x7e
suffix:colon
id|usage-&gt;code
op_assign
id|FF_GAIN
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x83
suffix:colon
multiline_comment|/* Simultaneous Effects Max */
id|input-&gt;ff_effects_max
op_assign
(paren
id|field-&gt;value
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Maximum Effects - %d&quot;
comma
id|input-&gt;ff_effects_max
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x98
suffix:colon
multiline_comment|/* Device Control */
id|usage-&gt;code
op_assign
id|FF_AUTOCENTER
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0xa4
suffix:colon
multiline_comment|/* Safety Switch */
id|usage-&gt;code
op_assign
id|BTN_DEAD
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Safety Switch Report&bslash;n&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x9f
suffix:colon
multiline_comment|/* Device Paused */
r_case
l_int|0xa0
suffix:colon
multiline_comment|/* Actuators Enabled */
id|dbg
c_func
(paren
l_string|&quot;Not telling the input API about &quot;
)paren
suffix:semicolon
id|resolv_usage
c_func
(paren
id|usage-&gt;hid
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_break
suffix:semicolon
r_default
suffix:colon
id|unknown
suffix:colon
id|resolv_usage
c_func
(paren
id|usage-&gt;hid
)paren
suffix:semicolon
r_if
c_cond
(paren
id|field-&gt;report_size
op_eq
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|field-&gt;report-&gt;type
op_eq
id|HID_OUTPUT_REPORT
)paren
(brace
id|usage-&gt;code
op_assign
id|LED_MISC
suffix:semicolon
id|usage-&gt;type
op_assign
id|EV_LED
suffix:semicolon
id|bit
op_assign
id|input-&gt;ledbit
suffix:semicolon
id|max
op_assign
id|LED_MAX
suffix:semicolon
r_break
suffix:semicolon
)brace
id|usage-&gt;code
op_assign
id|BTN_MISC
suffix:semicolon
id|usage-&gt;type
op_assign
id|EV_KEY
suffix:semicolon
id|bit
op_assign
id|input-&gt;keybit
suffix:semicolon
id|max
op_assign
id|KEY_MAX
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|field-&gt;flags
op_amp
id|HID_MAIN_ITEM_RELATIVE
)paren
(brace
id|usage-&gt;code
op_assign
id|REL_MISC
suffix:semicolon
id|usage-&gt;type
op_assign
id|EV_REL
suffix:semicolon
id|bit
op_assign
id|input-&gt;relbit
suffix:semicolon
id|max
op_assign
id|REL_MAX
suffix:semicolon
r_break
suffix:semicolon
)brace
id|usage-&gt;code
op_assign
id|ABS_MISC
suffix:semicolon
id|usage-&gt;type
op_assign
id|EV_ABS
suffix:semicolon
id|bit
op_assign
id|input-&gt;absbit
suffix:semicolon
id|max
op_assign
id|ABS_MAX
suffix:semicolon
r_break
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|usage-&gt;type
comma
id|input-&gt;evbit
)paren
suffix:semicolon
r_while
c_loop
(paren
id|usage-&gt;code
op_le
id|max
op_logical_and
id|test_and_set_bit
c_func
(paren
id|usage-&gt;code
comma
id|bit
)paren
)paren
(brace
id|usage-&gt;code
op_assign
id|find_next_zero_bit
c_func
(paren
id|bit
comma
id|usage-&gt;code
comma
id|max
op_plus
l_int|1
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usage-&gt;code
OG
id|max
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|usage-&gt;type
op_eq
id|EV_ABS
)paren
(brace
r_int
id|a
op_assign
id|field-&gt;logical_minimum
suffix:semicolon
r_int
id|b
op_assign
id|field-&gt;logical_maximum
suffix:semicolon
id|input-&gt;absmin
(braket
id|usage-&gt;code
)braket
op_assign
id|a
suffix:semicolon
id|input-&gt;absmax
(braket
id|usage-&gt;code
)braket
op_assign
id|b
suffix:semicolon
id|input-&gt;absfuzz
(braket
id|usage-&gt;code
)braket
op_assign
(paren
id|b
op_minus
id|a
)paren
op_rshift
l_int|8
suffix:semicolon
id|input-&gt;absflat
(braket
id|usage-&gt;code
)braket
op_assign
(paren
id|b
op_minus
id|a
)paren
op_rshift
l_int|4
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usage-&gt;hat_min
op_ne
id|usage-&gt;hat_max
)paren
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|usage-&gt;code
suffix:semicolon
id|i
OL
id|usage-&gt;code
op_plus
l_int|2
op_logical_and
id|i
op_le
id|max
suffix:semicolon
id|i
op_increment
)paren
(brace
id|input-&gt;absmax
(braket
id|i
)braket
op_assign
l_int|1
suffix:semicolon
id|input-&gt;absmin
(braket
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|input-&gt;absfuzz
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|input-&gt;absflat
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|set_bit
c_func
(paren
id|usage-&gt;code
op_plus
l_int|1
comma
id|input-&gt;absbit
)paren
suffix:semicolon
)brace
)brace
DECL|function|hidinput_hid_event
r_void
id|hidinput_hid_event
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
comma
r_struct
id|hid_field
op_star
id|field
comma
r_struct
id|hid_usage
op_star
id|usage
comma
id|__s32
id|value
)paren
(brace
r_struct
id|input_dev
op_star
id|input
op_assign
op_amp
id|hid-&gt;input
suffix:semicolon
r_int
op_star
id|quirks
op_assign
op_amp
id|hid-&gt;quirks
suffix:semicolon
r_if
c_cond
(paren
id|usage-&gt;hat_min
op_ne
id|usage-&gt;hat_max
)paren
(brace
id|value
op_assign
(paren
id|value
op_minus
id|usage-&gt;hat_min
)paren
op_star
l_int|8
op_div
(paren
id|usage-&gt;hat_max
op_minus
id|usage-&gt;hat_min
op_plus
l_int|1
)paren
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|value
template_param
l_int|8
)paren
id|value
op_assign
l_int|0
suffix:semicolon
id|input_event
c_func
(paren
id|input
comma
id|usage-&gt;type
comma
id|usage-&gt;code
comma
id|hid_hat_to_axis
(braket
id|value
)braket
dot
id|x
)paren
suffix:semicolon
id|input_event
c_func
(paren
id|input
comma
id|usage-&gt;type
comma
id|usage-&gt;code
op_plus
l_int|1
comma
id|hid_hat_to_axis
(braket
id|value
)braket
dot
id|y
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usage-&gt;hid
op_eq
(paren
id|HID_UP_DIGITIZER
op_or
l_int|0x003c
)paren
)paren
(brace
multiline_comment|/* Invert */
op_star
id|quirks
op_assign
id|value
ques
c_cond
(paren
op_star
id|quirks
op_or
id|HID_QUIRK_INVERT
)paren
suffix:colon
(paren
op_star
id|quirks
op_amp
op_complement
id|HID_QUIRK_INVERT
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usage-&gt;hid
op_eq
(paren
id|HID_UP_DIGITIZER
op_or
l_int|0x0032
)paren
)paren
(brace
multiline_comment|/* InRange */
r_if
c_cond
(paren
id|value
)paren
(brace
id|input_event
c_func
(paren
id|input
comma
id|usage-&gt;type
comma
(paren
op_star
id|quirks
op_amp
id|HID_QUIRK_INVERT
)paren
ques
c_cond
id|BTN_TOOL_RUBBER
suffix:colon
id|usage-&gt;code
comma
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|input_event
c_func
(paren
id|input
comma
id|usage-&gt;type
comma
id|usage-&gt;code
comma
l_int|0
)paren
suffix:semicolon
id|input_event
c_func
(paren
id|input
comma
id|usage-&gt;type
comma
id|BTN_TOOL_RUBBER
comma
l_int|0
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usage-&gt;hid
op_eq
(paren
id|HID_UP_DIGITIZER
op_or
l_int|0x0030
)paren
op_logical_and
(paren
op_star
id|quirks
op_amp
id|HID_QUIRK_NOTOUCH
)paren
)paren
(brace
multiline_comment|/* Pressure */
r_int
id|a
op_assign
id|field-&gt;logical_minimum
suffix:semicolon
r_int
id|b
op_assign
id|field-&gt;logical_maximum
suffix:semicolon
id|input_event
c_func
(paren
id|input
comma
id|EV_KEY
comma
id|BTN_TOUCH
comma
id|value
OG
id|a
op_plus
(paren
(paren
id|b
op_minus
id|a
)paren
op_rshift
l_int|3
)paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usage-&gt;hid
op_eq
(paren
id|HID_UP_PID
op_or
l_int|0x83UL
)paren
)paren
(brace
multiline_comment|/* Simultaneous Effects Max */
id|input-&gt;ff_effects_max
op_assign
id|value
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Maximum Effects - %d&quot;
comma
id|input-&gt;ff_effects_max
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|usage-&gt;hid
op_eq
(paren
id|HID_UP_PID
op_or
l_int|0x7fUL
)paren
)paren
(brace
id|dbg
c_func
(paren
l_string|&quot;PID Pool Report&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|usage-&gt;type
op_eq
id|EV_KEY
)paren
op_logical_and
(paren
id|usage-&gt;code
op_eq
l_int|0
)paren
)paren
(brace
multiline_comment|/* Key 0 is &quot;unassigned&quot;, not KEY_UKNOWN */
r_return
suffix:semicolon
)brace
id|input_event
c_func
(paren
id|input
comma
id|usage-&gt;type
comma
id|usage-&gt;code
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|field-&gt;flags
op_amp
id|HID_MAIN_ITEM_RELATIVE
)paren
op_logical_and
(paren
id|usage-&gt;type
op_eq
id|EV_KEY
)paren
)paren
id|input_event
c_func
(paren
id|input
comma
id|usage-&gt;type
comma
id|usage-&gt;code
comma
l_int|0
)paren
suffix:semicolon
)brace
DECL|function|hidinput_report_event
r_void
id|hidinput_report_event
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
comma
r_struct
id|hid_report
op_star
id|report
)paren
(brace
id|input_sync
c_func
(paren
op_amp
id|hid-&gt;input
)paren
suffix:semicolon
)brace
DECL|function|hidinput_input_event
r_static
r_int
id|hidinput_input_event
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
id|hid_device
op_star
id|hid
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_struct
id|hid_field
op_star
id|field
op_assign
l_int|NULL
suffix:semicolon
r_int
id|offset
suffix:semicolon
r_if
c_cond
(paren
id|type
op_eq
id|EV_FF
)paren
r_return
id|hid_ff_event
c_func
(paren
id|hid
comma
id|dev
comma
id|type
comma
id|code
comma
id|value
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|offset
op_assign
id|hid_find_field
c_func
(paren
id|hid
comma
id|type
comma
id|code
comma
op_amp
id|field
)paren
)paren
op_eq
op_minus
l_int|1
)paren
(brace
id|warn
c_func
(paren
l_string|&quot;event field not found&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|hid_set_field
c_func
(paren
id|field
comma
id|offset
comma
id|value
)paren
suffix:semicolon
id|hid_submit_report
c_func
(paren
id|hid
comma
id|field-&gt;report
comma
id|USB_DIR_OUT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hidinput_open
r_static
r_int
id|hidinput_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|hid_device
op_star
id|hid
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_return
id|hid_open
c_func
(paren
id|hid
)paren
suffix:semicolon
)brace
DECL|function|hidinput_close
r_static
r_void
id|hidinput_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|hid_device
op_star
id|hid
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
id|hid_close
c_func
(paren
id|hid
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Register the input device; print a message.&n; * Configure the input layer interface&n; * Read all reports and initalize the absoulte field values.&n; */
DECL|function|hidinput_connect
r_int
id|hidinput_connect
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
r_struct
id|usb_device
op_star
id|dev
op_assign
id|hid-&gt;dev
suffix:semicolon
r_struct
id|hid_report_enum
op_star
id|report_enum
suffix:semicolon
r_struct
id|hid_report
op_star
id|report
suffix:semicolon
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
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
id|hid-&gt;maxcollection
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|hid-&gt;collection
(braket
id|i
)braket
dot
id|type
op_eq
id|HID_COLLECTION_APPLICATION
op_logical_and
id|IS_INPUT_APPLICATION
c_func
(paren
id|hid-&gt;collection
(braket
id|i
)braket
dot
id|usage
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
id|i
op_eq
id|hid-&gt;maxcollection
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|hid-&gt;input
dot
r_private
op_assign
id|hid
suffix:semicolon
id|hid-&gt;input.event
op_assign
id|hidinput_input_event
suffix:semicolon
id|hid-&gt;input.open
op_assign
id|hidinput_open
suffix:semicolon
id|hid-&gt;input.close
op_assign
id|hidinput_close
suffix:semicolon
id|hid-&gt;input.name
op_assign
id|hid-&gt;name
suffix:semicolon
id|hid-&gt;input.phys
op_assign
id|hid-&gt;phys
suffix:semicolon
id|hid-&gt;input.uniq
op_assign
id|hid-&gt;uniq
suffix:semicolon
id|hid-&gt;input.id.bustype
op_assign
id|BUS_USB
suffix:semicolon
id|hid-&gt;input.id.vendor
op_assign
id|dev-&gt;descriptor.idVendor
suffix:semicolon
id|hid-&gt;input.id.product
op_assign
id|dev-&gt;descriptor.idProduct
suffix:semicolon
id|hid-&gt;input.id.version
op_assign
id|dev-&gt;descriptor.bcdDevice
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
id|HID_INPUT_REPORT
suffix:semicolon
id|k
op_le
id|HID_OUTPUT_REPORT
suffix:semicolon
id|k
op_increment
)paren
(brace
id|report_enum
op_assign
id|hid-&gt;report_enum
op_plus
id|k
suffix:semicolon
id|list
op_assign
id|report_enum-&gt;report_list.next
suffix:semicolon
r_while
c_loop
(paren
id|list
op_ne
op_amp
id|report_enum-&gt;report_list
)paren
(brace
id|report
op_assign
(paren
r_struct
id|hid_report
op_star
)paren
id|list
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
id|report-&gt;maxfield
suffix:semicolon
id|i
op_increment
)paren
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
id|report-&gt;field
(braket
id|i
)braket
op_member_access_from_pointer
id|maxusage
suffix:semicolon
id|j
op_increment
)paren
id|hidinput_configure_usage
c_func
(paren
id|hid
comma
id|report-&gt;field
(braket
id|i
)braket
comma
id|report-&gt;field
(braket
id|i
)braket
op_member_access_from_pointer
id|usage
op_plus
id|j
)paren
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
)brace
)brace
id|input_register_device
c_func
(paren
op_amp
id|hid-&gt;input
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hidinput_disconnect
r_void
id|hidinput_disconnect
c_func
(paren
r_struct
id|hid_device
op_star
id|hid
)paren
(brace
id|input_unregister_device
c_func
(paren
op_amp
id|hid-&gt;input
)paren
suffix:semicolon
)brace
eof
