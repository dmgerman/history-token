multiline_comment|/*&n; * $Id: sunkbd.c,v 1.14 2001/09/25 10:12:07 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * Sun keyboard driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Sun keyboard driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|sunkbd_keycode
r_static
r_int
r_char
id|sunkbd_keycode
(braket
l_int|128
)braket
op_assign
(brace
l_int|0
comma
l_int|128
comma
l_int|114
comma
l_int|129
comma
l_int|115
comma
l_int|59
comma
l_int|60
comma
l_int|68
comma
l_int|61
comma
l_int|87
comma
l_int|62
comma
l_int|88
comma
l_int|63
comma
l_int|100
comma
l_int|64
comma
l_int|0
comma
l_int|65
comma
l_int|66
comma
l_int|67
comma
l_int|56
comma
l_int|103
comma
l_int|119
comma
l_int|99
comma
l_int|70
comma
l_int|105
comma
l_int|130
comma
l_int|131
comma
l_int|108
comma
l_int|106
comma
l_int|1
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
l_int|12
comma
l_int|13
comma
l_int|41
comma
l_int|14
comma
l_int|110
comma
l_int|113
comma
l_int|98
comma
l_int|55
comma
l_int|116
comma
l_int|132
comma
l_int|83
comma
l_int|133
comma
l_int|102
comma
l_int|15
comma
l_int|16
comma
l_int|17
comma
l_int|18
comma
l_int|19
comma
l_int|20
comma
l_int|21
comma
l_int|22
comma
l_int|23
comma
l_int|24
comma
l_int|25
comma
l_int|26
comma
l_int|27
comma
l_int|111
comma
l_int|127
comma
l_int|71
comma
l_int|72
comma
l_int|73
comma
l_int|74
comma
l_int|134
comma
l_int|135
comma
l_int|107
comma
l_int|0
comma
l_int|29
comma
l_int|30
comma
l_int|31
comma
l_int|32
comma
l_int|33
comma
l_int|34
comma
l_int|35
comma
l_int|36
comma
l_int|37
comma
l_int|38
comma
l_int|39
comma
l_int|40
comma
l_int|43
comma
l_int|28
comma
l_int|96
comma
l_int|75
comma
l_int|76
comma
l_int|77
comma
l_int|82
comma
l_int|136
comma
l_int|104
comma
l_int|137
comma
l_int|69
comma
l_int|42
comma
l_int|44
comma
l_int|45
comma
l_int|46
comma
l_int|47
comma
l_int|48
comma
l_int|49
comma
l_int|50
comma
l_int|51
comma
l_int|52
comma
l_int|53
comma
l_int|54
comma
l_int|101
comma
l_int|79
comma
l_int|80
comma
l_int|81
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|138
comma
l_int|58
comma
l_int|125
comma
l_int|57
comma
l_int|126
comma
l_int|109
comma
l_int|86
comma
l_int|78
)brace
suffix:semicolon
DECL|macro|SUNKBD_CMD_RESET
mdefine_line|#define SUNKBD_CMD_RESET&t;0x1
DECL|macro|SUNKBD_CMD_BELLON
mdefine_line|#define SUNKBD_CMD_BELLON&t;0x2
DECL|macro|SUNKBD_CMD_BELLOFF
mdefine_line|#define SUNKBD_CMD_BELLOFF&t;0x3
DECL|macro|SUNKBD_CMD_CLICK
mdefine_line|#define SUNKBD_CMD_CLICK&t;0xa
DECL|macro|SUNKBD_CMD_NOCLICK
mdefine_line|#define SUNKBD_CMD_NOCLICK&t;0xb
DECL|macro|SUNKBD_CMD_SETLED
mdefine_line|#define SUNKBD_CMD_SETLED&t;0xe
DECL|macro|SUNKBD_CMD_LAYOUT
mdefine_line|#define SUNKBD_CMD_LAYOUT&t;0xf
DECL|macro|SUNKBD_RET_RESET
mdefine_line|#define SUNKBD_RET_RESET&t;0xff
DECL|macro|SUNKBD_RET_ALLUP
mdefine_line|#define SUNKBD_RET_ALLUP&t;0x7f
DECL|macro|SUNKBD_RET_LAYOUT
mdefine_line|#define SUNKBD_RET_LAYOUT&t;0xfe
DECL|macro|SUNKBD_LAYOUT_5_MASK
mdefine_line|#define SUNKBD_LAYOUT_5_MASK&t;0x20
DECL|macro|SUNKBD_RELEASE
mdefine_line|#define SUNKBD_RELEASE&t;&t;0x80
DECL|macro|SUNKBD_KEY
mdefine_line|#define SUNKBD_KEY&t;&t;0x7f
multiline_comment|/*&n; * Per-keyboard data.&n; */
DECL|struct|sunkbd
r_struct
id|sunkbd
(brace
DECL|member|keycode
r_int
r_char
id|keycode
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|serio
r_struct
id|serio
op_star
id|serio
suffix:semicolon
DECL|member|tq
r_struct
id|tq_struct
id|tq
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|64
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|type
r_char
id|type
suffix:semicolon
DECL|member|reset
r_char
id|reset
suffix:semicolon
DECL|member|layout
r_char
id|layout
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * sunkbd_interrupt() is called by the low level driver when a character&n; * is received.&n; */
DECL|function|sunkbd_interrupt
r_static
r_void
id|sunkbd_interrupt
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_int
r_char
id|data
comma
r_int
r_int
id|flags
)paren
(brace
r_struct
id|sunkbd
op_star
id|sunkbd
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|sunkbd-&gt;reset
op_le
op_minus
l_int|1
)paren
(brace
multiline_comment|/* If cp[i] is 0xff, sunkbd-&gt;reset will stay -1. */
id|sunkbd-&gt;reset
op_assign
id|data
suffix:semicolon
multiline_comment|/* The keyboard sends 0xff 0xff 0xID on powerup */
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sunkbd-&gt;layout
op_eq
op_minus
l_int|1
)paren
(brace
id|sunkbd-&gt;layout
op_assign
id|data
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|data
)paren
(brace
r_case
id|SUNKBD_RET_RESET
suffix:colon
id|queue_task
c_func
(paren
op_amp
id|sunkbd-&gt;tq
comma
op_amp
id|tq_immediate
)paren
suffix:semicolon
id|mark_bh
c_func
(paren
id|IMMEDIATE_BH
)paren
suffix:semicolon
id|sunkbd-&gt;reset
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
suffix:semicolon
r_case
id|SUNKBD_RET_LAYOUT
suffix:colon
id|sunkbd-&gt;layout
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
suffix:semicolon
r_case
id|SUNKBD_RET_ALLUP
suffix:colon
multiline_comment|/* All keys released */
r_return
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|sunkbd-&gt;keycode
(braket
id|data
op_amp
id|SUNKBD_KEY
)braket
)paren
(brace
id|input_report_key
c_func
(paren
op_amp
id|sunkbd-&gt;dev
comma
id|sunkbd-&gt;keycode
(braket
id|data
op_amp
id|SUNKBD_KEY
)braket
comma
op_logical_neg
(paren
id|data
op_amp
id|SUNKBD_RELEASE
)paren
)paren
suffix:semicolon
id|input_sync
c_func
(paren
op_amp
id|sunkbd-&gt;dev
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sunkbd.c: Unknown key (scancode %#x) %s.&bslash;n&quot;
comma
id|data
op_amp
id|SUNKBD_KEY
comma
id|data
op_amp
id|SUNKBD_RELEASE
ques
c_cond
l_string|&quot;released&quot;
suffix:colon
l_string|&quot;pressed&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; * sunkbd_event() handles events from the input module.&n; */
DECL|function|sunkbd_event
r_static
r_int
id|sunkbd_event
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
id|sunkbd
op_star
id|sunkbd
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|EV_LED
suffix:colon
id|sunkbd-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|sunkbd-&gt;serio
comma
id|SUNKBD_CMD_SETLED
)paren
suffix:semicolon
id|sunkbd-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|sunkbd-&gt;serio
comma
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
id|LED_COMPOSE
comma
id|dev-&gt;led
)paren
op_lshift
l_int|1
)paren
op_or
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
r_return
l_int|0
suffix:semicolon
r_case
id|EV_SND
suffix:colon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|SND_CLICK
suffix:colon
id|sunkbd-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|sunkbd-&gt;serio
comma
id|SUNKBD_CMD_NOCLICK
op_minus
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|SND_BELL
suffix:colon
id|sunkbd-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|sunkbd-&gt;serio
comma
id|SUNKBD_CMD_BELLOFF
op_minus
id|value
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * sunkbd_initialize() checks for a Sun keyboard attached, and determines&n; * its type.&n; */
DECL|function|sunkbd_initialize
r_static
r_int
id|sunkbd_initialize
c_func
(paren
r_struct
id|sunkbd
op_star
id|sunkbd
)paren
(brace
r_int
id|t
suffix:semicolon
id|t
op_assign
l_int|1000
suffix:semicolon
id|sunkbd-&gt;reset
op_assign
op_minus
l_int|2
suffix:semicolon
id|sunkbd-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|sunkbd-&gt;serio
comma
id|SUNKBD_CMD_RESET
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sunkbd-&gt;reset
OL
l_int|0
op_logical_and
op_decrement
id|t
)paren
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|sunkbd-&gt;type
op_assign
id|sunkbd-&gt;reset
suffix:semicolon
r_if
c_cond
(paren
id|sunkbd-&gt;type
op_eq
l_int|4
)paren
(brace
multiline_comment|/* Type 4 keyboard */
id|t
op_assign
l_int|250
suffix:semicolon
id|sunkbd-&gt;layout
op_assign
op_minus
l_int|2
suffix:semicolon
id|sunkbd-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|sunkbd-&gt;serio
comma
id|SUNKBD_CMD_LAYOUT
)paren
suffix:semicolon
r_while
c_loop
(paren
id|sunkbd-&gt;layout
OL
l_int|0
op_logical_and
op_decrement
id|t
)paren
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|t
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|sunkbd-&gt;layout
op_amp
id|SUNKBD_LAYOUT_5_MASK
)paren
id|sunkbd-&gt;type
op_assign
l_int|5
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * sunkbd_reinit() sets leds and beeps to a state the computer remembers they&n; * were in.&n; */
DECL|function|sunkbd_reinit
r_static
r_void
id|sunkbd_reinit
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|sunkbd
op_star
id|sunkbd
op_assign
id|data
suffix:semicolon
r_int
id|t
op_assign
l_int|1000
suffix:semicolon
r_while
c_loop
(paren
id|sunkbd-&gt;reset
OL
l_int|0
op_logical_and
op_decrement
id|t
)paren
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|sunkbd-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|sunkbd-&gt;serio
comma
id|SUNKBD_CMD_SETLED
)paren
suffix:semicolon
id|sunkbd-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|sunkbd-&gt;serio
comma
(paren
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|LED_CAPSL
comma
id|sunkbd-&gt;dev.led
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
id|sunkbd-&gt;dev.led
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
id|LED_COMPOSE
comma
id|sunkbd-&gt;dev.led
)paren
op_lshift
l_int|1
)paren
op_or
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|LED_NUML
comma
id|sunkbd-&gt;dev.led
)paren
)paren
suffix:semicolon
id|sunkbd-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|sunkbd-&gt;serio
comma
id|SUNKBD_CMD_NOCLICK
op_minus
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|SND_CLICK
comma
id|sunkbd-&gt;dev.snd
)paren
)paren
suffix:semicolon
id|sunkbd-&gt;serio
op_member_access_from_pointer
id|write
c_func
(paren
id|sunkbd-&gt;serio
comma
id|SUNKBD_CMD_BELLOFF
op_minus
op_logical_neg
op_logical_neg
id|test_bit
c_func
(paren
id|SND_BELL
comma
id|sunkbd-&gt;dev.snd
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sunkbd_connect() probes for a Sun keyboard and fills the necessary structures.&n; */
DECL|function|sunkbd_connect
r_static
r_void
id|sunkbd_connect
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_dev
op_star
id|dev
)paren
(brace
r_struct
id|sunkbd
op_star
id|sunkbd
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
(paren
id|serio-&gt;type
op_amp
id|SERIO_TYPE
)paren
op_ne
id|SERIO_RS232
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
(paren
id|serio-&gt;type
op_amp
id|SERIO_PROTO
)paren
op_logical_and
(paren
id|serio-&gt;type
op_amp
id|SERIO_PROTO
)paren
op_ne
id|SERIO_SUNKBD
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sunkbd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sunkbd
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
suffix:semicolon
id|memset
c_func
(paren
id|sunkbd
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|sunkbd
)paren
)paren
suffix:semicolon
id|sunkbd-&gt;dev.evbit
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
id|EV_SND
)paren
op_or
id|BIT
c_func
(paren
id|EV_REP
)paren
suffix:semicolon
id|sunkbd-&gt;dev.ledbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|LED_CAPSL
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
id|LED_SCROLLL
)paren
op_or
id|BIT
c_func
(paren
id|LED_NUML
)paren
suffix:semicolon
id|sunkbd-&gt;dev.sndbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|SND_CLICK
)paren
op_or
id|BIT
c_func
(paren
id|SND_BELL
)paren
suffix:semicolon
id|sunkbd-&gt;serio
op_assign
id|serio
suffix:semicolon
id|sunkbd-&gt;tq.routine
op_assign
id|sunkbd_reinit
suffix:semicolon
id|sunkbd-&gt;tq.data
op_assign
id|sunkbd
suffix:semicolon
id|sunkbd-&gt;dev.keycode
op_assign
id|sunkbd-&gt;keycode
suffix:semicolon
id|sunkbd-&gt;dev.keycodesize
op_assign
r_sizeof
(paren
r_int
r_char
)paren
suffix:semicolon
id|sunkbd-&gt;dev.keycodemax
op_assign
id|ARRAY_SIZE
c_func
(paren
id|sunkbd_keycode
)paren
suffix:semicolon
id|sunkbd-&gt;dev.event
op_assign
id|sunkbd_event
suffix:semicolon
id|sunkbd-&gt;dev
dot
r_private
op_assign
id|sunkbd
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|sunkbd
suffix:semicolon
r_if
c_cond
(paren
id|serio_open
c_func
(paren
id|serio
comma
id|dev
)paren
)paren
(brace
id|kfree
c_func
(paren
id|sunkbd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|sunkbd_initialize
c_func
(paren
id|sunkbd
)paren
OL
l_int|0
)paren
(brace
id|serio_close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sunkbd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|sunkbd-&gt;name
comma
l_string|&quot;Sun Type %d keyboard&quot;
comma
id|sunkbd-&gt;type
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|sunkbd-&gt;keycode
comma
id|sunkbd_keycode
comma
r_sizeof
(paren
id|sunkbd-&gt;keycode
)paren
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
id|sunkbd-&gt;keycode
(braket
id|i
)braket
comma
id|sunkbd-&gt;dev.keybit
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
id|sunkbd-&gt;dev.keybit
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|sunkbd-&gt;name
comma
l_string|&quot;%s/input&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|sunkbd-&gt;dev.name
op_assign
id|sunkbd-&gt;name
suffix:semicolon
id|sunkbd-&gt;dev.phys
op_assign
id|sunkbd-&gt;phys
suffix:semicolon
id|sunkbd-&gt;dev.id.bustype
op_assign
id|BUS_RS232
suffix:semicolon
id|sunkbd-&gt;dev.id.vendor
op_assign
id|SERIO_SUNKBD
suffix:semicolon
id|sunkbd-&gt;dev.id.product
op_assign
id|sunkbd-&gt;type
suffix:semicolon
id|sunkbd-&gt;dev.id.version
op_assign
l_int|0x0100
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|sunkbd-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|sunkbd-&gt;name
comma
id|serio-&gt;phys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sunkbd_disconnect() unregisters and closes behind us.&n; */
DECL|function|sunkbd_disconnect
r_static
r_void
id|sunkbd_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|sunkbd
op_star
id|sunkbd
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|sunkbd-&gt;dev
)paren
suffix:semicolon
id|serio_close
c_func
(paren
id|serio
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|sunkbd
)paren
suffix:semicolon
)brace
DECL|variable|sunkbd_dev
r_static
r_struct
id|serio_dev
id|sunkbd_dev
op_assign
(brace
dot
id|interrupt
op_assign
id|sunkbd_interrupt
comma
dot
id|connect
op_assign
id|sunkbd_connect
comma
dot
id|disconnect
op_assign
id|sunkbd_disconnect
)brace
suffix:semicolon
multiline_comment|/*&n; * The functions for insering/removing us as a module.&n; */
DECL|function|sunkbd_init
r_int
id|__init
id|sunkbd_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_device
c_func
(paren
op_amp
id|sunkbd_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sunkbd_exit
r_void
id|__exit
id|sunkbd_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_device
c_func
(paren
op_amp
id|sunkbd_dev
)paren
suffix:semicolon
)brace
DECL|variable|sunkbd_init
id|module_init
c_func
(paren
id|sunkbd_init
)paren
suffix:semicolon
DECL|variable|sunkbd_exit
id|module_exit
c_func
(paren
id|sunkbd_exit
)paren
suffix:semicolon
eof
