multiline_comment|/*&n; * $Id: atkbd.c,v 1.33 2002/02/12 09:34:34 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;AT and PS/2 keyboard driver&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|atkbd_set
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|atkbd_set
r_static
r_int
id|atkbd_set
op_assign
l_int|2
suffix:semicolon
multiline_comment|/*&n; * Scancode to keycode tables. These are just the default setting, and&n; * are loadable via an userland utility.&n; */
DECL|variable|atkbd_set2_keycode
r_static
r_int
r_char
id|atkbd_set2_keycode
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
l_int|255
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
DECL|variable|atkbd_set3_keycode
r_static
r_int
r_char
id|atkbd_set3_keycode
(braket
l_int|512
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
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|59
comma
l_int|1
comma
l_int|138
comma
l_int|128
comma
l_int|129
comma
l_int|130
comma
l_int|15
comma
l_int|41
comma
l_int|60
comma
l_int|131
comma
l_int|29
comma
l_int|42
comma
l_int|86
comma
l_int|58
comma
l_int|16
comma
l_int|2
comma
l_int|61
comma
l_int|133
comma
l_int|56
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
l_int|62
comma
l_int|134
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
l_int|63
comma
l_int|135
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
l_int|64
comma
l_int|136
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
l_int|65
comma
l_int|137
comma
l_int|100
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
l_int|66
comma
l_int|125
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
l_int|67
comma
l_int|126
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
l_int|68
comma
l_int|113
comma
l_int|114
comma
l_int|40
comma
l_int|84
comma
l_int|26
comma
l_int|13
comma
l_int|87
comma
l_int|99
comma
l_int|100
comma
l_int|54
comma
l_int|28
comma
l_int|27
comma
l_int|43
comma
l_int|84
comma
l_int|88
comma
l_int|70
comma
l_int|108
comma
l_int|105
comma
l_int|119
comma
l_int|103
comma
l_int|111
comma
l_int|107
comma
l_int|14
comma
l_int|110
comma
l_int|0
comma
l_int|79
comma
l_int|106
comma
l_int|75
comma
l_int|71
comma
l_int|109
comma
l_int|102
comma
l_int|104
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
l_int|69
comma
l_int|98
comma
l_int|0
comma
l_int|96
comma
l_int|81
comma
l_int|0
comma
l_int|78
comma
l_int|73
comma
l_int|55
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
l_int|74
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
l_int|125
comma
l_int|126
comma
l_int|127
comma
l_int|112
comma
l_int|0
comma
l_int|0
comma
l_int|139
comma
l_int|150
comma
l_int|163
comma
l_int|165
comma
l_int|115
comma
l_int|152
comma
l_int|150
comma
l_int|166
comma
l_int|140
comma
l_int|160
comma
l_int|154
comma
l_int|113
comma
l_int|114
comma
l_int|167
comma
l_int|168
comma
l_int|148
comma
l_int|149
comma
l_int|147
comma
l_int|140
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
)brace
suffix:semicolon
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
multiline_comment|/*&n; * The atkbd control structure&n; */
DECL|struct|atkbd
r_struct
id|atkbd
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
multiline_comment|/*&n; * atkbd_interrupt(). Here takes place processing of data received from&n; * the keyboard into events.&n; */
DECL|function|atkbd_interrupt
r_static
r_void
id|atkbd_interrupt
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
id|atkbd
op_star
id|atkbd
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
macro_line|#ifdef ATKBD_DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;atkbd.c: Received %02x&bslash;n&quot;
comma
id|data
)paren
suffix:semicolon
macro_line|#endif
r_switch
c_cond
(paren
id|code
)paren
(brace
r_case
id|ATKBD_RET_ACK
suffix:colon
id|atkbd-&gt;ack
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
r_case
id|ATKBD_RET_NAK
suffix:colon
id|atkbd-&gt;ack
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
id|atkbd-&gt;cmdcnt
)paren
(brace
id|atkbd-&gt;cmdbuf
(braket
op_decrement
id|atkbd-&gt;cmdcnt
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
id|atkbd-&gt;keycode
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
id|atkbd-&gt;tq
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
id|atkbd-&gt;emul
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
r_case
id|ATKBD_KEY_EMUL1
suffix:colon
id|atkbd-&gt;emul
op_assign
l_int|2
suffix:semicolon
r_return
suffix:semicolon
r_case
id|ATKBD_KEY_RELEASE
suffix:colon
id|atkbd-&gt;release
op_assign
l_int|1
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atkbd-&gt;emul
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|atkbd-&gt;emul
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
id|atkbd-&gt;keycode
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
l_string|&quot;atkbd.c: Unknown key (set %d, scancode %#x, on %s) %s.&bslash;n&quot;
comma
id|atkbd-&gt;set
comma
id|code
comma
id|serio-&gt;phys
comma
id|atkbd-&gt;release
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
id|atkbd-&gt;dev
comma
id|atkbd-&gt;keycode
(braket
id|code
)braket
comma
op_logical_neg
id|atkbd-&gt;release
)paren
suffix:semicolon
)brace
id|atkbd-&gt;release
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * atkbd_sendbyte() sends a byte to the keyboard, and waits for&n; * acknowledge. It doesn&squot;t handle resends according to the keyboard&n; * protocol specs, because if these are needed, the keyboard needs&n; * replacement anyway, and they only make a mess in the protocol.&n; */
DECL|function|atkbd_sendbyte
r_static
r_int
id|atkbd_sendbyte
c_func
(paren
r_struct
id|atkbd
op_star
id|atkbd
comma
r_int
r_char
id|byte
)paren
(brace
r_int
id|timeout
op_assign
l_int|10000
suffix:semicolon
multiline_comment|/* 100 msec */
id|atkbd-&gt;ack
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef ATKBD_DEBUG
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;atkbd.c: Sent: %02x&bslash;n&quot;
comma
id|byte
)paren
suffix:semicolon
macro_line|#endif
id|serio_write
c_func
(paren
id|atkbd-&gt;serio
comma
id|byte
)paren
suffix:semicolon
r_while
c_loop
(paren
op_logical_neg
id|atkbd-&gt;ack
op_logical_and
id|timeout
op_decrement
)paren
id|udelay
c_func
(paren
l_int|10
)paren
suffix:semicolon
r_return
op_minus
(paren
id|atkbd-&gt;ack
op_le
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * atkbd_command() sends a command, and its parameters to the keyboard,&n; * then waits for the response and puts it in the param array.&n; */
DECL|function|atkbd_command
r_static
r_int
id|atkbd_command
c_func
(paren
r_struct
id|atkbd
op_star
id|atkbd
comma
r_int
r_char
op_star
id|param
comma
r_int
id|command
)paren
(brace
r_int
id|timeout
op_assign
l_int|50000
suffix:semicolon
multiline_comment|/* 500 msec */
r_int
id|send
op_assign
(paren
id|command
op_rshift
l_int|12
)paren
op_amp
l_int|0xf
suffix:semicolon
r_int
id|receive
op_assign
(paren
id|command
op_rshift
l_int|8
)paren
op_amp
l_int|0xf
suffix:semicolon
r_int
id|i
suffix:semicolon
id|atkbd-&gt;cmdcnt
op_assign
id|receive
suffix:semicolon
r_if
c_cond
(paren
id|command
op_amp
l_int|0xff
)paren
r_if
c_cond
(paren
id|atkbd_sendbyte
c_func
(paren
id|atkbd
comma
id|command
op_amp
l_int|0xff
)paren
)paren
r_return
(paren
id|atkbd-&gt;cmdcnt
op_assign
l_int|0
)paren
op_minus
l_int|1
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
id|send
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|atkbd_sendbyte
c_func
(paren
id|atkbd
comma
id|param
(braket
id|i
)braket
)paren
)paren
r_return
(paren
id|atkbd-&gt;cmdcnt
op_assign
l_int|0
)paren
op_minus
l_int|1
suffix:semicolon
r_while
c_loop
(paren
id|atkbd-&gt;cmdcnt
op_logical_and
id|timeout
op_decrement
)paren
id|udelay
c_func
(paren
l_int|10
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
id|receive
suffix:semicolon
id|i
op_increment
)paren
id|param
(braket
id|i
)braket
op_assign
id|atkbd-&gt;cmdbuf
(braket
(paren
id|receive
op_minus
l_int|1
)paren
op_minus
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|atkbd-&gt;cmdcnt
)paren
r_return
(paren
id|atkbd-&gt;cmdcnt
op_assign
l_int|0
)paren
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Event callback from the input module. Events that change the state of&n; * the hardware are processed here.&n; */
DECL|function|atkbd_event
r_static
r_int
id|atkbd_event
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
id|atkbd
op_star
id|atkbd
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_char
id|param
(braket
l_int|2
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atkbd-&gt;serio-&gt;write
)paren
r_return
op_minus
l_int|1
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
op_star
id|param
op_assign
(paren
id|test_bit
c_func
(paren
id|LED_SCROLLL
comma
id|dev-&gt;led
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_or
(paren
id|test_bit
c_func
(paren
id|LED_NUML
comma
id|dev-&gt;led
)paren
ques
c_cond
l_int|2
suffix:colon
l_int|0
)paren
op_or
(paren
id|test_bit
c_func
(paren
id|LED_CAPSL
comma
id|dev-&gt;led
)paren
ques
c_cond
l_int|4
suffix:colon
l_int|0
)paren
suffix:semicolon
id|atkbd_command
c_func
(paren
id|atkbd
comma
id|param
comma
id|ATKBD_CMD_SETLEDS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atkbd-&gt;set
op_eq
l_int|4
)paren
(brace
id|param
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|param
(braket
l_int|1
)braket
op_assign
(paren
id|test_bit
c_func
(paren
id|LED_COMPOSE
comma
id|dev-&gt;led
)paren
ques
c_cond
l_int|0x01
suffix:colon
l_int|0
)paren
op_or
(paren
id|test_bit
c_func
(paren
id|LED_SLEEP
comma
id|dev-&gt;led
)paren
ques
c_cond
l_int|0x02
suffix:colon
l_int|0
)paren
op_or
(paren
id|test_bit
c_func
(paren
id|LED_SUSPEND
comma
id|dev-&gt;led
)paren
ques
c_cond
l_int|0x04
suffix:colon
l_int|0
)paren
op_or
(paren
id|test_bit
c_func
(paren
id|LED_MUTE
comma
id|dev-&gt;led
)paren
ques
c_cond
l_int|0x20
suffix:colon
l_int|0
)paren
suffix:semicolon
id|atkbd_command
c_func
(paren
id|atkbd
comma
id|param
comma
id|ATKBD_CMD_EX_SETLEDS
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * atkbd_set_3 checks if a keyboard has a working Set 3 support, and&n; * sets it into that. Unfortunately there are keyboards that can be switched&n; * to Set 3, but don&squot;t work well in that (BTC Multimedia ...)&n; */
DECL|function|atkbd_set_3
r_static
r_int
id|atkbd_set_3
c_func
(paren
r_struct
id|atkbd
op_star
id|atkbd
)paren
(brace
r_int
r_char
id|param
suffix:semicolon
multiline_comment|/*&n; * For known special keyboards we can go ahead and set the correct set.&n; */
r_if
c_cond
(paren
id|atkbd-&gt;id
op_eq
l_int|0xaca1
)paren
(brace
id|param
op_assign
l_int|3
suffix:semicolon
id|atkbd_command
c_func
(paren
id|atkbd
comma
op_amp
id|param
comma
id|ATKBD_CMD_SSCANSET
)paren
suffix:semicolon
r_return
l_int|3
suffix:semicolon
)brace
multiline_comment|/*&n; * We check for the extra keys on an some keyboards that need extra&n; * command to get enabled. This shouldn&squot;t harm any keyboards not&n; * knowing the command.&n; */
id|param
op_assign
l_int|0x71
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|atkbd_command
c_func
(paren
id|atkbd
comma
op_amp
id|param
comma
id|ATKBD_CMD_EX_ENABLE
)paren
)paren
r_return
l_int|4
suffix:semicolon
multiline_comment|/*&n; * Try to set the set we want.&n; */
id|param
op_assign
id|atkbd_set
suffix:semicolon
r_if
c_cond
(paren
id|atkbd_command
c_func
(paren
id|atkbd
comma
op_amp
id|param
comma
id|ATKBD_CMD_SSCANSET
)paren
)paren
r_return
l_int|2
suffix:semicolon
multiline_comment|/*&n; * Read set number. Beware here. Some keyboards always send &squot;2&squot;&n; * or some other number regardless into what mode they have been&n; * attempted to be set. Other keyboards treat the &squot;0&squot; command as&n; * &squot;set to set 0&squot;, and not &squot;report current set&squot; as they should.&n; * In that case we time out, and return 2.&n; */
id|param
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|atkbd_command
c_func
(paren
id|atkbd
comma
op_amp
id|param
comma
id|ATKBD_CMD_GSCANSET
)paren
)paren
r_return
l_int|2
suffix:semicolon
multiline_comment|/*&n; * Here we return the set number the keyboard reports about&n; * itself.&n; */
r_return
(paren
id|param
op_eq
l_int|3
)paren
ques
c_cond
l_int|3
suffix:colon
l_int|2
suffix:semicolon
)brace
multiline_comment|/*&n; * atkbd_probe() probes for an AT keyboard on a serio port.&n; */
DECL|function|atkbd_probe
r_static
r_int
id|atkbd_probe
c_func
(paren
r_struct
id|atkbd
op_star
id|atkbd
)paren
(brace
r_int
r_char
id|param
(braket
l_int|2
)braket
suffix:semicolon
multiline_comment|/*&n; * Full reset with selftest can on some keyboards be annoyingly slow,&n; * so we just do a reset-and-disable on the keyboard, which&n; * is considerably faster, but doesn&squot;t have to reset everything.&n; */
r_if
c_cond
(paren
id|atkbd_command
c_func
(paren
id|atkbd
comma
l_int|NULL
comma
id|ATKBD_CMD_RESET_DIS
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n; * Next, we check if it&squot;s a keyboard. It should send 0xab83&n; * (0xab84 on IBM ThinkPad, and 0xaca1 on a NCD Sun layout keyboard,&n; * 0xab02 on unxlated i8042 and 0xab03 on unxlated ThinkPad, 0xab7f&n; * on Fujitsu Lifebook).&n; * If it&squot;s a mouse, it&squot;ll only send 0x00 (0x03 if it&squot;s MS mouse),&n; * and we&squot;ll time out here, and report an error.&n; */
id|param
(braket
l_int|0
)braket
op_assign
id|param
(braket
l_int|1
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|atkbd_command
c_func
(paren
id|atkbd
comma
id|param
comma
id|ATKBD_CMD_GETID
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|atkbd-&gt;id
op_assign
(paren
id|param
(braket
l_int|0
)braket
op_lshift
l_int|8
)paren
op_or
id|param
(braket
l_int|1
)braket
suffix:semicolon
r_if
c_cond
(paren
id|atkbd-&gt;id
op_ne
l_int|0xab83
op_logical_and
id|atkbd-&gt;id
op_ne
l_int|0xab84
op_logical_and
id|atkbd-&gt;id
op_ne
l_int|0xaca1
op_logical_and
id|atkbd-&gt;id
op_ne
l_int|0xab7f
op_logical_and
id|atkbd-&gt;id
op_ne
l_int|0xab02
op_logical_and
id|atkbd-&gt;id
op_ne
l_int|0xab03
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;atkbd.c: Unusual keyboard ID: %#x on %s&bslash;n&quot;
comma
id|atkbd-&gt;id
comma
id|atkbd-&gt;serio-&gt;phys
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * atkbd_initialize() sets the keyboard into a sane state.&n; */
DECL|function|atkbd_initialize
r_static
r_void
id|atkbd_initialize
c_func
(paren
r_struct
id|atkbd
op_star
id|atkbd
)paren
(brace
r_int
r_char
id|param
suffix:semicolon
multiline_comment|/*&n; * Disable autorepeat. We don&squot;t need it, as we do it in software anyway,&n; * because that way can get faster repeat, and have less system load&n; * (less accesses to the slow ISA hardware). If this fails, we don&squot;t care,&n; * and will just ignore the repeated keys.&n; */
id|atkbd_command
c_func
(paren
id|atkbd
comma
l_int|NULL
comma
id|ATKBD_CMD_SETALL_MB
)paren
suffix:semicolon
multiline_comment|/*&n; * We also shut off all the leds. The console code will turn them back on,&n; * if needed.&n; */
id|param
op_assign
l_int|0
suffix:semicolon
id|atkbd_command
c_func
(paren
id|atkbd
comma
op_amp
id|param
comma
id|ATKBD_CMD_SETLEDS
)paren
suffix:semicolon
multiline_comment|/*&n; * Last, we enable the keyboard so that we get keypresses from it.&n; */
r_if
c_cond
(paren
id|atkbd_command
c_func
(paren
id|atkbd
comma
l_int|NULL
comma
id|ATKBD_CMD_ENABLE
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;atkbd.c: Failed to enable keyboard on %s&bslash;n&quot;
comma
id|atkbd-&gt;serio-&gt;phys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * atkbd_disconnect() cleans up behind us ...&n; */
DECL|function|atkbd_disconnect
r_static
r_void
id|atkbd_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|atkbd
op_star
id|atkbd
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|atkbd-&gt;dev
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
id|atkbd
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * atkbd_powerup() is called when the keyboard sends the 0xaa character,&n; * meaning that it was disconnected and reconnected. We close the port&n; * in that case and let the upper layer find an appropriate driver for&n; * the device that was connected. It may be a mouse, or a keyboard, we&n; * don&squot;t know yet.&n; */
DECL|function|atkbd_powerup
r_static
r_void
id|atkbd_powerup
c_func
(paren
r_void
op_star
id|data
)paren
(brace
r_struct
id|atkbd
op_star
id|atkbd
op_assign
id|data
suffix:semicolon
id|mdelay
c_func
(paren
l_int|40
)paren
suffix:semicolon
multiline_comment|/* FIXME!!! Wait some nicer way */
id|serio_rescan
c_func
(paren
id|atkbd-&gt;serio
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * atkbd_connect() is called when the serio module finds and interface&n; * that isn&squot;t handled yet by an appropriate device driver. We check if&n; * there is an AT keyboard out there and if yes, we register ourselves&n; * to the input module.&n; */
DECL|function|atkbd_connect
r_static
r_void
id|atkbd_connect
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
id|atkbd
op_star
id|atkbd
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
id|SERIO_8042
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|atkbd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|atkbd
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
id|atkbd
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|atkbd
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serio-&gt;write
)paren
(brace
id|atkbd-&gt;dev.evbit
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
id|atkbd-&gt;dev.ledbit
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
)brace
r_else
id|atkbd-&gt;dev.evbit
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
id|EV_REP
)paren
suffix:semicolon
id|atkbd-&gt;serio
op_assign
id|serio
suffix:semicolon
id|atkbd-&gt;dev.keycode
op_assign
id|atkbd-&gt;keycode
suffix:semicolon
id|atkbd-&gt;dev.event
op_assign
id|atkbd_event
suffix:semicolon
id|atkbd-&gt;dev
dot
r_private
op_assign
id|atkbd
suffix:semicolon
id|atkbd-&gt;tq.routine
op_assign
id|atkbd_powerup
suffix:semicolon
id|atkbd-&gt;tq.data
op_assign
id|atkbd
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|atkbd
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
id|atkbd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|serio-&gt;write
)paren
(brace
r_if
c_cond
(paren
id|atkbd_probe
c_func
(paren
id|atkbd
)paren
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
id|atkbd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|atkbd-&gt;set
op_assign
id|atkbd_set_3
c_func
(paren
id|atkbd
)paren
suffix:semicolon
)brace
r_else
(brace
id|atkbd-&gt;set
op_assign
l_int|2
suffix:semicolon
id|atkbd-&gt;id
op_assign
l_int|0xab00
suffix:semicolon
)brace
r_if
c_cond
(paren
id|atkbd-&gt;set
op_eq
l_int|4
)paren
(brace
id|atkbd-&gt;dev.ledbit
(braket
l_int|0
)braket
op_or_assign
id|BIT
c_func
(paren
id|LED_COMPOSE
)paren
op_or
id|BIT
c_func
(paren
id|LED_SUSPEND
)paren
op_or
id|BIT
c_func
(paren
id|LED_SLEEP
)paren
op_or
id|BIT
c_func
(paren
id|LED_MUTE
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|atkbd-&gt;name
comma
l_string|&quot;AT Set 2 Extended keyboard&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
id|sprintf
c_func
(paren
id|atkbd-&gt;name
comma
l_string|&quot;AT Set %d keyboard&quot;
comma
id|atkbd-&gt;set
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|atkbd-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|atkbd-&gt;set
op_eq
l_int|3
)paren
id|memcpy
c_func
(paren
id|atkbd-&gt;keycode
comma
id|atkbd_set3_keycode
comma
r_sizeof
(paren
id|atkbd-&gt;keycode
)paren
)paren
suffix:semicolon
r_else
id|memcpy
c_func
(paren
id|atkbd-&gt;keycode
comma
id|atkbd_set2_keycode
comma
r_sizeof
(paren
id|atkbd-&gt;keycode
)paren
)paren
suffix:semicolon
id|atkbd-&gt;dev.name
op_assign
id|atkbd-&gt;name
suffix:semicolon
id|atkbd-&gt;dev.phys
op_assign
id|atkbd-&gt;phys
suffix:semicolon
id|atkbd-&gt;dev.idbus
op_assign
id|BUS_I8042
suffix:semicolon
id|atkbd-&gt;dev.idvendor
op_assign
l_int|0x0001
suffix:semicolon
id|atkbd-&gt;dev.idproduct
op_assign
id|atkbd-&gt;set
suffix:semicolon
id|atkbd-&gt;dev.idversion
op_assign
id|atkbd-&gt;id
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
id|atkbd-&gt;keycode
(braket
id|i
)braket
op_logical_and
id|atkbd-&gt;keycode
(braket
id|i
)braket
op_le
l_int|250
)paren
id|set_bit
c_func
(paren
id|atkbd-&gt;keycode
(braket
id|i
)braket
comma
id|atkbd-&gt;dev.keybit
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|atkbd-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|atkbd-&gt;name
comma
id|serio-&gt;phys
)paren
suffix:semicolon
r_if
c_cond
(paren
id|serio-&gt;write
)paren
id|atkbd_initialize
c_func
(paren
id|atkbd
)paren
suffix:semicolon
)brace
DECL|variable|atkbd_dev
r_static
r_struct
id|serio_dev
id|atkbd_dev
op_assign
(brace
id|interrupt
suffix:colon
id|atkbd_interrupt
comma
id|connect
suffix:colon
id|atkbd_connect
comma
id|disconnect
suffix:colon
id|atkbd_disconnect
)brace
suffix:semicolon
multiline_comment|/*&n; * Module init and exit.&n; */
DECL|function|atkbd_setup
r_void
id|__init
id|atkbd_setup
c_func
(paren
r_char
op_star
id|str
comma
r_int
op_star
id|ints
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|ints
(braket
l_int|0
)braket
)paren
id|atkbd_set
op_assign
id|ints
(braket
l_int|1
)braket
suffix:semicolon
)brace
DECL|function|atkbd_init
r_int
id|__init
id|atkbd_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_device
c_func
(paren
op_amp
id|atkbd_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atkbd_exit
r_void
id|__exit
id|atkbd_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_device
c_func
(paren
op_amp
id|atkbd_dev
)paren
suffix:semicolon
)brace
DECL|variable|atkbd_init
id|module_init
c_func
(paren
id|atkbd_init
)paren
suffix:semicolon
DECL|variable|atkbd_exit
id|module_exit
c_func
(paren
id|atkbd_exit
)paren
suffix:semicolon
eof
