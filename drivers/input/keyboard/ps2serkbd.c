multiline_comment|/*&n; * based on: sunkbd.c and ps2serkbd.c&n; *&n; * $Id: ps2serkbd.c,v 1.5 2001/09/25 10:12:07 vojtech Exp $&n; */
multiline_comment|/*&n; * PS/2 keyboard via adapter at serial port driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/tqueue.h&gt;
DECL|macro|ATKBD_CMD_SETLEDS
mdefine_line|#define ATKBD_CMD_SETLEDS&t;0x10ed
DECL|macro|ATKBD_CMD_GSCANSET
mdefine_line|#define ATKBD_CMD_GSCANSET&t;0x11f0
DECL|macro|ATKBD_CMD_SSCANSET
mdefine_line|#define ATKBD_CMD_SSCANSET&t;0x10f0
DECL|macro|ATKBD_CMD_GETID
mdefine_line|#define ATKBD_CMD_GETID&t;&t;0x02f2
DECL|macro|ATKBD_CMD_ENABLE
mdefine_line|#define ATKBD_CMD_ENABLE&t;0x00f4
DECL|macro|ATKBD_CMD_RESET_DIS
mdefine_line|#define ATKBD_CMD_RESET_DIS&t;0x00f5
DECL|macro|ATKBD_CMD_SETALL_MB
mdefine_line|#define ATKBD_CMD_SETALL_MB&t;0x00f8
DECL|macro|ATKBD_CMD_EX_ENABLE
mdefine_line|#define ATKBD_CMD_EX_ENABLE&t;0x10ea
DECL|macro|ATKBD_CMD_EX_SETLEDS
mdefine_line|#define ATKBD_CMD_EX_SETLEDS&t;0x20eb
DECL|macro|ATKBD_RET_ACK
mdefine_line|#define ATKBD_RET_ACK&t;&t;0xfa
DECL|macro|ATKBD_RET_NAK
mdefine_line|#define ATKBD_RET_NAK&t;&t;0xfe
DECL|macro|ATKBD_KEY_UNKNOWN
mdefine_line|#define ATKBD_KEY_UNKNOWN&t;  0
DECL|macro|ATKBD_KEY_BAT
mdefine_line|#define ATKBD_KEY_BAT&t;&t;251
DECL|macro|ATKBD_KEY_EMUL0
mdefine_line|#define ATKBD_KEY_EMUL0&t;&t;252
DECL|macro|ATKBD_KEY_EMUL1
mdefine_line|#define ATKBD_KEY_EMUL1&t;&t;253
DECL|macro|ATKBD_KEY_RELEASE
mdefine_line|#define ATKBD_KEY_RELEASE&t;254
DECL|macro|ATKBD_KEY_NULL
mdefine_line|#define ATKBD_KEY_NULL&t;&t;255
DECL|variable|ps2serkbd_set2_keycode
r_static
r_int
r_char
id|ps2serkbd_set2_keycode
(braket
l_int|512
)braket
op_assign
(brace
l_int|0
comma
l_int|67
comma
l_int|65
comma
l_int|63
comma
l_int|61
comma
l_int|59
comma
l_int|60
comma
l_int|88
comma
l_int|0
comma
l_int|68
comma
l_int|66
comma
l_int|64
comma
l_int|62
comma
l_int|15
comma
l_int|41
comma
l_int|85
comma
l_int|0
comma
l_int|56
comma
l_int|42
comma
l_int|0
comma
l_int|29
comma
l_int|16
comma
l_int|2
comma
l_int|89
comma
l_int|0
comma
l_int|0
comma
l_int|44
comma
l_int|31
comma
l_int|30
comma
l_int|17
comma
l_int|3
comma
l_int|90
comma
l_int|0
comma
l_int|46
comma
l_int|45
comma
l_int|32
comma
l_int|18
comma
l_int|5
comma
l_int|4
comma
l_int|91
comma
l_int|0
comma
l_int|57
comma
l_int|47
comma
l_int|33
comma
l_int|20
comma
l_int|19
comma
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|49
comma
l_int|48
comma
l_int|35
comma
l_int|34
comma
l_int|21
comma
l_int|7
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|50
comma
l_int|36
comma
l_int|22
comma
l_int|8
comma
l_int|9
comma
l_int|0
comma
l_int|0
comma
l_int|51
comma
l_int|37
comma
l_int|23
comma
l_int|24
comma
l_int|11
comma
l_int|10
comma
l_int|0
comma
l_int|0
comma
l_int|52
comma
l_int|53
comma
l_int|38
comma
l_int|39
comma
l_int|25
comma
l_int|12
comma
l_int|0
comma
l_int|122
comma
l_int|89
comma
l_int|40
comma
l_int|120
comma
l_int|26
comma
l_int|13
comma
l_int|0
comma
l_int|0
comma
l_int|58
comma
l_int|54
comma
l_int|28
comma
l_int|27
comma
l_int|0
comma
l_int|43
comma
l_int|0
comma
l_int|0
comma
l_int|85
comma
l_int|86
comma
l_int|90
comma
l_int|91
comma
l_int|92
comma
l_int|93
comma
l_int|14
comma
l_int|94
comma
l_int|95
comma
l_int|79
comma
l_int|0
comma
l_int|75
comma
l_int|71
comma
l_int|121
comma
l_int|0
comma
l_int|123
comma
l_int|82
comma
l_int|83
comma
l_int|80
comma
l_int|76
comma
l_int|77
comma
l_int|72
comma
l_int|1
comma
l_int|69
comma
l_int|87
comma
l_int|78
comma
l_int|81
comma
l_int|74
comma
l_int|55
comma
l_int|73
comma
l_int|70
comma
l_int|99
comma
l_int|252
comma
l_int|0
comma
l_int|0
comma
l_int|65
comma
l_int|99
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
l_int|251
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
l_int|252
comma
l_int|253
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
l_int|254
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
l_int|255
comma
l_int|0
comma
l_int|0
comma
l_int|92
comma
l_int|90
comma
l_int|85
comma
l_int|0
comma
l_int|137
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|91
comma
l_int|89
comma
l_int|144
comma
l_int|115
comma
l_int|0
comma
l_int|136
comma
l_int|100
comma
l_int|255
comma
l_int|0
comma
l_int|97
comma
l_int|149
comma
l_int|164
comma
l_int|0
comma
l_int|156
comma
l_int|0
comma
l_int|0
comma
l_int|140
comma
l_int|115
comma
l_int|0
comma
l_int|0
comma
l_int|125
comma
l_int|0
comma
l_int|150
comma
l_int|0
comma
l_int|154
comma
l_int|152
comma
l_int|163
comma
l_int|151
comma
l_int|126
comma
l_int|112
comma
l_int|166
comma
l_int|0
comma
l_int|140
comma
l_int|0
comma
l_int|147
comma
l_int|0
comma
l_int|127
comma
l_int|159
comma
l_int|167
comma
l_int|139
comma
l_int|160
comma
l_int|163
comma
l_int|0
comma
l_int|0
comma
l_int|116
comma
l_int|158
comma
l_int|0
comma
l_int|150
comma
l_int|165
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|142
comma
l_int|157
comma
l_int|0
comma
l_int|114
comma
l_int|166
comma
l_int|168
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|155
comma
l_int|0
comma
l_int|98
comma
l_int|113
comma
l_int|0
comma
l_int|148
comma
l_int|0
comma
l_int|138
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
l_int|153
comma
l_int|140
comma
l_int|0
comma
l_int|0
comma
l_int|96
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|143
comma
l_int|0
comma
l_int|133
comma
l_int|0
comma
l_int|116
comma
l_int|0
comma
l_int|143
comma
l_int|0
comma
l_int|174
comma
l_int|133
comma
l_int|0
comma
l_int|107
comma
l_int|0
comma
l_int|105
comma
l_int|102
comma
l_int|0
comma
l_int|0
comma
l_int|112
comma
l_int|110
comma
l_int|111
comma
l_int|108
comma
l_int|112
comma
l_int|106
comma
l_int|103
comma
l_int|0
comma
l_int|119
comma
l_int|0
comma
l_int|118
comma
l_int|109
comma
l_int|0
comma
l_int|99
comma
l_int|104
comma
l_int|119
)brace
suffix:semicolon
multiline_comment|/*&n; * Per-keyboard data.&n; */
DECL|struct|ps2serkbd
r_struct
id|ps2serkbd
(brace
DECL|member|keycode
r_int
r_char
id|keycode
(braket
l_int|512
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
DECL|member|tq
r_struct
id|tq_struct
id|tq
suffix:semicolon
DECL|member|cmdbuf
r_int
r_char
id|cmdbuf
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|cmdcnt
r_int
r_char
id|cmdcnt
suffix:semicolon
DECL|member|set
r_int
r_char
id|set
suffix:semicolon
DECL|member|release
r_char
id|release
suffix:semicolon
DECL|member|ack
r_char
id|ack
suffix:semicolon
DECL|member|emul
r_char
id|emul
suffix:semicolon
DECL|member|error
r_char
id|error
suffix:semicolon
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * ps2serkbd_interrupt() is called by the low level driver when a character&n; * is received.&n; */
DECL|function|ps2serkbd_interrupt
r_static
r_void
id|ps2serkbd_interrupt
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
r_static
r_int
id|event_count
op_assign
l_int|0
suffix:semicolon
r_struct
id|ps2serkbd
op_star
id|ps2serkbd
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
id|code
op_assign
id|data
suffix:semicolon
macro_line|#if 0
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ps2serkbd.c(%8d): (scancode %#x)&bslash;n&quot;
comma
id|event_count
comma
id|data
)paren
suffix:semicolon
macro_line|#endif
id|event_count
op_increment
suffix:semicolon
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|ATKBD_RET_ACK
suffix:colon
id|ps2serkbd-&gt;ack
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
r_case
id|ATKBD_RET_NAK
suffix:colon
id|ps2serkbd-&gt;ack
op_assign
op_minus
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ps2serkbd-&gt;cmdcnt
)paren
(brace
id|ps2serkbd-&gt;cmdbuf
(braket
op_decrement
id|ps2serkbd-&gt;cmdcnt
)braket
op_assign
id|code
suffix:semicolon
r_return
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ps2serkbd-&gt;keycode
(braket
id|code
)braket
)paren
(brace
r_case
id|ATKBD_KEY_BAT
suffix:colon
id|queue_task
c_func
(paren
op_amp
id|ps2serkbd-&gt;tq
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
r_return
suffix:semicolon
r_case
id|ATKBD_KEY_EMUL0
suffix:colon
id|ps2serkbd-&gt;emul
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
r_case
id|ATKBD_KEY_EMUL1
suffix:colon
id|ps2serkbd-&gt;emul
op_assign
l_int|2
suffix:semicolon
r_return
suffix:semicolon
r_case
id|ATKBD_KEY_RELEASE
suffix:colon
id|ps2serkbd-&gt;release
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ps2serkbd-&gt;emul
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|ps2serkbd-&gt;emul
)paren
r_return
suffix:semicolon
id|code
op_or_assign
l_int|0x100
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|ps2serkbd-&gt;keycode
(braket
id|code
)braket
)paren
(brace
r_case
id|ATKBD_KEY_NULL
suffix:colon
r_break
suffix:semicolon
r_case
id|ATKBD_KEY_UNKNOWN
suffix:colon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ps2serkbd.c: Unknown key (set %d, scancode %#x) %s.&bslash;n&quot;
comma
id|ps2serkbd-&gt;set
comma
id|code
comma
id|ps2serkbd-&gt;release
ques
c_cond
l_string|&quot;released&quot;
suffix:colon
l_string|&quot;pressed&quot;
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|input_report_key
c_func
(paren
op_amp
id|ps2serkbd-&gt;dev
comma
id|ps2serkbd-&gt;keycode
(braket
id|code
)braket
comma
op_logical_neg
id|ps2serkbd-&gt;release
)paren
suffix:semicolon
)brace
id|ps2serkbd-&gt;release
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * ps2serkbd_event() handles events from the input module.&n; */
DECL|function|ps2serkbd_event
r_static
r_int
id|ps2serkbd_event
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
r_switch
c_cond
(paren
id|type
)paren
(brace
r_case
id|EV_LED
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|ps2serkbd_initialize
r_static
r_int
id|ps2serkbd_initialize
c_func
(paren
r_struct
id|ps2serkbd
op_star
id|ps2serkbd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ps2serkbd_reinit
r_static
r_void
id|ps2serkbd_reinit
c_func
(paren
r_void
op_star
id|data
)paren
(brace
)brace
DECL|function|ps2serkbd_connect
r_static
r_void
id|ps2serkbd_connect
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
id|ps2serkbd
op_star
id|ps2serkbd
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
id|SERIO_PS2SER
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ps2serkbd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|ps2serkbd
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
id|ps2serkbd
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ps2serkbd
)paren
)paren
suffix:semicolon
id|ps2serkbd-&gt;dev.evbit
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
id|ps2serkbd-&gt;dev.ledbit
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
suffix:semicolon
id|ps2serkbd-&gt;serio
op_assign
id|serio
suffix:semicolon
id|ps2serkbd-&gt;dev.keycode
op_assign
id|ps2serkbd-&gt;keycode
suffix:semicolon
id|ps2serkbd-&gt;dev.event
op_assign
id|ps2serkbd_event
suffix:semicolon
id|ps2serkbd-&gt;dev
dot
r_private
op_assign
id|ps2serkbd
suffix:semicolon
id|ps2serkbd-&gt;tq.routine
op_assign
id|ps2serkbd_reinit
suffix:semicolon
id|ps2serkbd-&gt;tq.data
op_assign
id|ps2serkbd
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|ps2serkbd
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
id|ps2serkbd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ps2serkbd_initialize
c_func
(paren
id|ps2serkbd
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
id|ps2serkbd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ps2serkbd-&gt;set
op_assign
l_int|4
suffix:semicolon
r_if
c_cond
(paren
id|ps2serkbd-&gt;set
op_eq
l_int|4
)paren
(brace
id|ps2serkbd-&gt;dev.ledbit
(braket
l_int|0
)braket
op_or_assign
l_int|0
suffix:semicolon
id|sprintf
c_func
(paren
id|ps2serkbd-&gt;name
comma
l_string|&quot;AT Set 2 Extended keyboard&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|ps2serkbd-&gt;keycode
comma
id|ps2serkbd_set2_keycode
comma
r_sizeof
(paren
id|ps2serkbd-&gt;keycode
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|ps2serkbd-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|ps2serkbd-&gt;dev.name
op_assign
id|ps2serkbd-&gt;name
suffix:semicolon
id|ps2serkbd-&gt;dev.phys
op_assign
id|ps2serkbd-&gt;phys
suffix:semicolon
id|ps2serkbd-&gt;dev.id.bustype
op_assign
id|BUS_RS232
suffix:semicolon
id|ps2serkbd-&gt;dev.id.vendor
op_assign
id|SERIO_PS2SER
suffix:semicolon
id|ps2serkbd-&gt;dev.id.product
op_assign
id|ps2serkbd-&gt;set
suffix:semicolon
id|ps2serkbd-&gt;dev.id.version
op_assign
id|ps2serkbd-&gt;id
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
l_int|512
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|ps2serkbd-&gt;keycode
(braket
id|i
)braket
op_logical_and
id|ps2serkbd-&gt;keycode
(braket
id|i
)braket
op_le
l_int|250
)paren
id|set_bit
c_func
(paren
id|ps2serkbd-&gt;keycode
(braket
id|i
)braket
comma
id|ps2serkbd-&gt;dev.keybit
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|ps2serkbd-&gt;dev
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * ps2serkbd_disconnect() unregisters and closes behind us.&n; */
DECL|function|ps2serkbd_disconnect
r_static
r_void
id|ps2serkbd_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|ps2serkbd
op_star
id|ps2serkbd
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|ps2serkbd-&gt;dev
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
id|ps2serkbd
)paren
suffix:semicolon
)brace
DECL|variable|ps2serkbd_dev
r_static
r_struct
id|serio_dev
id|ps2serkbd_dev
op_assign
(brace
id|interrupt
suffix:colon
id|ps2serkbd_interrupt
comma
id|connect
suffix:colon
id|ps2serkbd_connect
comma
id|disconnect
suffix:colon
id|ps2serkbd_disconnect
)brace
suffix:semicolon
multiline_comment|/*&n; * The functions for insering/removing us as a module.&n; */
DECL|function|ps2serkbd_init
r_int
id|__init
id|ps2serkbd_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_device
c_func
(paren
op_amp
id|ps2serkbd_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ps2serkbd_exit
r_void
id|__exit
id|ps2serkbd_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_device
c_func
(paren
op_amp
id|ps2serkbd_dev
)paren
suffix:semicolon
)brace
DECL|variable|ps2serkbd_init
id|module_init
c_func
(paren
id|ps2serkbd_init
)paren
suffix:semicolon
DECL|variable|ps2serkbd_exit
id|module_exit
c_func
(paren
id|ps2serkbd_exit
)paren
suffix:semicolon
eof
