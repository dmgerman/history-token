multiline_comment|/*&n; * ALPS touchpad PS/2 mouse driver&n; *&n; * Copyright (c) 2003 Neil Brown &lt;neilb@cse.unsw.edu.au&gt;&n; * Copyright (c) 2003 Peter Osterlund &lt;petero2@telia.com&gt;&n; * Copyright (c) 2004 Dmitry Torokhov &lt;dtor@mail.ru&gt;&n; * Copyright (c) 2005 Vojtech Pavlik &lt;vojtech@suse.cz&gt;&n; *&n; * ALPS detection, tap switching and status querying info is taken from&n; * tpconfig utility (by C. Scott Ananian and Bruce Kall).&n; *&n; * This program is free software; you can redistribute it and/or modify it&n; * under the terms of the GNU General Public License version 2 as published by&n; * the Free Software Foundation.&n; */
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/libps2.h&gt;
macro_line|#include &quot;psmouse.h&quot;
macro_line|#include &quot;alps.h&quot;
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#ifdef DEBUG
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) printk(KERN_INFO &quot;alps.c: &quot; format &quot;&bslash;n&quot;, ## arg)
macro_line|#else
DECL|macro|dbg
mdefine_line|#define dbg(format, arg...) do {} while (0)
macro_line|#endif
DECL|macro|ALPS_DUALPOINT
mdefine_line|#define ALPS_DUALPOINT&t;0x01
DECL|macro|ALPS_WHEEL
mdefine_line|#define ALPS_WHEEL&t;0x02
DECL|macro|ALPS_FW_BK
mdefine_line|#define ALPS_FW_BK&t;0x04
DECL|macro|ALPS_4BTN
mdefine_line|#define ALPS_4BTN&t;0x08
DECL|macro|ALPS_OLDPROTO
mdefine_line|#define ALPS_OLDPROTO&t;0x10
DECL|struct|alps_model_info
r_static
r_struct
id|alps_model_info
(brace
DECL|member|signature
r_int
r_char
id|signature
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|flags
r_int
r_char
id|flags
suffix:semicolon
DECL|variable|alps_model_data
)brace
id|alps_model_data
(braket
)braket
op_assign
(brace
(brace
(brace
l_int|0x33
comma
l_int|0x02
comma
l_int|0x0a
)brace
comma
id|ALPS_OLDPROTO
)brace
comma
(brace
(brace
l_int|0x53
comma
l_int|0x02
comma
l_int|0x0a
)brace
comma
l_int|0
)brace
comma
(brace
(brace
l_int|0x53
comma
l_int|0x02
comma
l_int|0x14
)brace
comma
l_int|0
)brace
comma
(brace
(brace
l_int|0x63
comma
l_int|0x02
comma
l_int|0x0a
)brace
comma
l_int|0
)brace
comma
(brace
(brace
l_int|0x63
comma
l_int|0x02
comma
l_int|0x14
)brace
comma
l_int|0
)brace
comma
(brace
(brace
l_int|0x63
comma
l_int|0x02
comma
l_int|0x28
)brace
comma
l_int|0
)brace
comma
(brace
(brace
l_int|0x63
comma
l_int|0x02
comma
l_int|0x3c
)brace
comma
id|ALPS_WHEEL
)brace
comma
(brace
(brace
l_int|0x63
comma
l_int|0x02
comma
l_int|0x50
)brace
comma
id|ALPS_FW_BK
)brace
comma
(brace
(brace
l_int|0x63
comma
l_int|0x02
comma
l_int|0x64
)brace
comma
l_int|0
)brace
comma
(brace
(brace
l_int|0x63
comma
l_int|0x03
comma
l_int|0xc8
)brace
comma
l_int|0
)brace
comma
(brace
(brace
l_int|0x73
comma
l_int|0x02
comma
l_int|0x0a
)brace
comma
l_int|0
)brace
comma
(brace
(brace
l_int|0x73
comma
l_int|0x02
comma
l_int|0x14
)brace
comma
l_int|0
)brace
comma
(brace
(brace
l_int|0x20
comma
l_int|0x02
comma
l_int|0x0e
)brace
comma
id|ALPS_DUALPOINT
)brace
comma
multiline_comment|/* XXX */
(brace
(brace
l_int|0x22
comma
l_int|0x02
comma
l_int|0x0a
)brace
comma
id|ALPS_DUALPOINT
)brace
comma
(brace
(brace
l_int|0x22
comma
l_int|0x02
comma
l_int|0x14
)brace
comma
id|ALPS_DUALPOINT
)brace
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * XXX - this entry is suspicious. First byte has zero lower nibble,&n; * which is what a normal mouse would report. Also, the value 0x0e&n; * isn&squot;t valid per PS/2 spec.&n; */
multiline_comment|/*&n; * ALPS abolute Mode - new format&n; * &n; * byte 0:  1    ?    ?    ?    1    ?    ?    ? &n; * byte 1:  0   x6   x5   x4   x3   x2   x1   x0&n; * byte 2:  0   x10  x9   x8   x7    ?  fin  ges&n; * byte 3:  0   y9   y8   y7    1    M    R    L &n; * byte 4:  0   y6   y5   y4   y3   y2   y1   y0&n; * byte 5:  0   z6   z5   z4   z3   z2   z1   z0&n; *&n; * ?&squot;s can have different meanings on different models,&n; * such as wheel rotation, extra buttons, stick buttons&n; * on a dualpoint, etc.&n; */
DECL|function|alps_process_packet
r_static
r_void
id|alps_process_packet
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|alps_data
op_star
id|priv
op_assign
id|psmouse
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
r_char
op_star
id|packet
op_assign
id|psmouse-&gt;packet
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|psmouse-&gt;dev
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev2
op_assign
op_amp
id|priv-&gt;dev2
suffix:semicolon
r_int
id|x
comma
id|y
comma
id|z
comma
id|ges
comma
id|fin
comma
id|left
comma
id|right
comma
id|middle
suffix:semicolon
id|input_regs
c_func
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|packet
(braket
l_int|0
)braket
op_amp
l_int|0xc8
)paren
op_eq
l_int|0x08
)paren
(brace
multiline_comment|/* 3-byte PS/2 packet */
id|input_report_key
c_func
(paren
id|dev2
comma
id|BTN_LEFT
comma
id|packet
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev2
comma
id|BTN_RIGHT
comma
id|packet
(braket
l_int|0
)braket
op_amp
l_int|2
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev2
comma
id|BTN_MIDDLE
comma
id|packet
(braket
l_int|0
)braket
op_amp
l_int|4
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev2
comma
id|REL_X
comma
id|packet
(braket
l_int|1
)braket
ques
c_cond
(paren
r_int
)paren
id|packet
(braket
l_int|1
)braket
op_minus
(paren
r_int
)paren
(paren
(paren
id|packet
(braket
l_int|0
)braket
op_lshift
l_int|4
)paren
op_amp
l_int|0x100
)paren
suffix:colon
l_int|0
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev2
comma
id|REL_Y
comma
id|packet
(braket
l_int|2
)braket
ques
c_cond
(paren
r_int
)paren
(paren
(paren
id|packet
(braket
l_int|0
)braket
op_lshift
l_int|3
)paren
op_amp
l_int|0x100
)paren
op_minus
(paren
r_int
)paren
id|packet
(braket
l_int|2
)braket
suffix:colon
l_int|0
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|priv-&gt;flags
op_amp
id|ALPS_OLDPROTO
)paren
(brace
id|left
op_assign
id|packet
(braket
l_int|2
)braket
op_amp
l_int|0x08
suffix:semicolon
id|right
op_assign
id|packet
(braket
l_int|2
)braket
op_amp
l_int|0x10
suffix:semicolon
id|middle
op_assign
l_int|0
suffix:semicolon
id|x
op_assign
(paren
id|packet
(braket
l_int|1
)braket
op_amp
l_int|0x7f
)paren
op_or
(paren
(paren
id|packet
(braket
l_int|0
)braket
op_amp
l_int|0x07
)paren
op_lshift
l_int|7
)paren
suffix:semicolon
id|y
op_assign
(paren
id|packet
(braket
l_int|4
)braket
op_amp
l_int|0x7f
)paren
op_or
(paren
(paren
id|packet
(braket
l_int|3
)braket
op_amp
l_int|0x07
)paren
op_lshift
l_int|7
)paren
suffix:semicolon
id|z
op_assign
id|packet
(braket
l_int|5
)braket
suffix:semicolon
)brace
r_else
(brace
id|left
op_assign
id|packet
(braket
l_int|3
)braket
op_amp
l_int|1
suffix:semicolon
id|right
op_assign
id|packet
(braket
l_int|3
)braket
op_amp
l_int|2
suffix:semicolon
id|middle
op_assign
id|packet
(braket
l_int|3
)braket
op_amp
l_int|4
suffix:semicolon
id|x
op_assign
(paren
id|packet
(braket
l_int|1
)braket
op_amp
l_int|0x7f
)paren
op_or
(paren
(paren
id|packet
(braket
l_int|2
)braket
op_amp
l_int|0x78
)paren
op_lshift
(paren
l_int|7
op_minus
l_int|3
)paren
)paren
suffix:semicolon
id|y
op_assign
(paren
id|packet
(braket
l_int|4
)braket
op_amp
l_int|0x7f
)paren
op_or
(paren
(paren
id|packet
(braket
l_int|3
)braket
op_amp
l_int|0x70
)paren
op_lshift
(paren
l_int|7
op_minus
l_int|4
)paren
)paren
suffix:semicolon
id|z
op_assign
id|packet
(braket
l_int|5
)braket
suffix:semicolon
)brace
id|ges
op_assign
id|packet
(braket
l_int|2
)braket
op_amp
l_int|1
suffix:semicolon
id|fin
op_assign
id|packet
(braket
l_int|2
)braket
op_amp
l_int|2
suffix:semicolon
multiline_comment|/* Dualpoint has stick buttons in byte 0 */
r_if
c_cond
(paren
id|priv-&gt;flags
op_amp
id|ALPS_DUALPOINT
)paren
(brace
id|input_report_key
c_func
(paren
id|dev2
comma
id|BTN_LEFT
comma
id|packet
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev2
comma
id|BTN_MIDDLE
comma
(paren
id|packet
(braket
l_int|0
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev2
comma
id|BTN_RIGHT
comma
(paren
id|packet
(braket
l_int|0
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Relative movement packet */
r_if
c_cond
(paren
id|z
op_eq
l_int|127
)paren
(brace
id|input_report_rel
c_func
(paren
id|dev2
comma
id|REL_X
comma
(paren
id|x
OG
l_int|383
ques
c_cond
id|x
suffix:colon
(paren
id|x
op_minus
l_int|768
)paren
)paren
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev2
comma
id|REL_Y
comma
op_minus
(paren
id|y
OG
l_int|255
ques
c_cond
id|y
suffix:colon
(paren
id|x
op_minus
l_int|512
)paren
)paren
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev2
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/* Convert hardware tap to a reasonable Z value */
r_if
c_cond
(paren
id|ges
op_logical_and
op_logical_neg
id|fin
)paren
id|z
op_assign
l_int|40
suffix:semicolon
multiline_comment|/*&n;&t; * A &quot;tap and drag&quot; operation is reported by the hardware as a transition&n;&t; * from (!fin &amp;&amp; ges) to (fin &amp;&amp; ges). This should be translated to the&n;&t; * sequence Z&gt;0, Z==0, Z&gt;0, so the Z==0 event has to be generated manually.&n;&t; */
r_if
c_cond
(paren
id|ges
op_logical_and
id|fin
op_logical_and
op_logical_neg
id|priv-&gt;prev_fin
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
l_int|0
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOOL_FINGER
comma
l_int|0
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|priv-&gt;prev_fin
op_assign
id|fin
suffix:semicolon
r_if
c_cond
(paren
id|z
OG
l_int|30
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOUCH
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z
OL
l_int|25
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOUCH
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|z
OG
l_int|0
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
)brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_PRESSURE
comma
id|z
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOOL_FINGER
comma
id|z
OG
l_int|0
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
id|left
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|right
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|middle
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;flags
op_amp
id|ALPS_WHEEL
)paren
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_WHEEL
comma
(paren
(paren
id|packet
(braket
l_int|0
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|0x07
)paren
op_or
(paren
(paren
id|packet
(braket
l_int|2
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x08
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;flags
op_amp
id|ALPS_FW_BK
)paren
(brace
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_FORWARD
comma
id|packet
(braket
l_int|0
)braket
op_amp
l_int|0x10
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_BACK
comma
id|packet
(braket
l_int|2
)braket
op_amp
l_int|0x04
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
DECL|function|alps_process_byte
r_static
id|psmouse_ret_t
id|alps_process_byte
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_if
c_cond
(paren
(paren
id|psmouse-&gt;packet
(braket
l_int|0
)braket
op_amp
l_int|0xc8
)paren
op_eq
l_int|0x08
)paren
(brace
multiline_comment|/* PS/2 packet */
r_if
c_cond
(paren
id|psmouse-&gt;pktcnt
op_eq
l_int|3
)paren
(brace
id|alps_process_packet
c_func
(paren
id|psmouse
comma
id|regs
)paren
suffix:semicolon
r_return
id|PSMOUSE_FULL_PACKET
suffix:semicolon
)brace
r_return
id|PSMOUSE_GOOD_DATA
suffix:semicolon
)brace
multiline_comment|/* ALPS absolute mode packets start with 0b11111mrl */
r_if
c_cond
(paren
(paren
id|psmouse-&gt;packet
(braket
l_int|0
)braket
op_amp
l_int|0x88
)paren
op_ne
l_int|0x88
)paren
r_return
id|PSMOUSE_BAD_DATA
suffix:semicolon
multiline_comment|/* Bytes 2 - 6 should have 0 in the highest bit */
r_if
c_cond
(paren
id|psmouse-&gt;pktcnt
op_ge
l_int|2
op_logical_and
id|psmouse-&gt;pktcnt
op_le
l_int|6
op_logical_and
(paren
id|psmouse-&gt;packet
(braket
id|psmouse-&gt;pktcnt
op_minus
l_int|1
)braket
op_amp
l_int|0x80
)paren
)paren
r_return
id|PSMOUSE_BAD_DATA
suffix:semicolon
r_if
c_cond
(paren
id|psmouse-&gt;pktcnt
op_eq
l_int|6
)paren
(brace
id|alps_process_packet
c_func
(paren
id|psmouse
comma
id|regs
)paren
suffix:semicolon
r_return
id|PSMOUSE_FULL_PACKET
suffix:semicolon
)brace
r_return
id|PSMOUSE_GOOD_DATA
suffix:semicolon
)brace
DECL|function|alps_get_model
r_static
r_int
id|alps_get_model
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
op_star
id|version
)paren
(brace
r_struct
id|ps2dev
op_star
id|ps2dev
op_assign
op_amp
id|psmouse-&gt;ps2dev
suffix:semicolon
r_int
r_char
id|rates
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|10
comma
l_int|20
comma
l_int|40
comma
l_int|60
comma
l_int|80
comma
l_int|100
comma
l_int|200
)brace
suffix:semicolon
r_int
r_char
id|param
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;&t; * First try &quot;E6 report&quot;.&n;&t; * ALPS should return 0,0,10 or 0,0,100&n;&t; */
id|param
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE11
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
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
id|param
(braket
l_int|2
)braket
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_GETINFO
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;E6 report: %2.2x %2.2x %2.2x&quot;
comma
id|param
(braket
l_int|0
)braket
comma
id|param
(braket
l_int|1
)braket
comma
id|param
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|param
(braket
l_int|0
)braket
op_ne
l_int|0
op_logical_or
id|param
(braket
l_int|1
)braket
op_ne
l_int|0
op_logical_or
(paren
id|param
(braket
l_int|2
)braket
op_ne
l_int|10
op_logical_and
id|param
(braket
l_int|2
)braket
op_ne
l_int|100
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Now try &quot;E7 report&quot;. Allowed responses are in&n;&t; * alps_model_data[].signature&n;&t; */
id|param
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_SETRES
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE21
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE21
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETSCALE21
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
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
id|param
(braket
l_int|2
)braket
op_assign
l_int|0xff
suffix:semicolon
r_if
c_cond
(paren
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_GETINFO
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;E7 report: %2.2x %2.2x %2.2x&quot;
comma
id|param
(braket
l_int|0
)braket
comma
id|param
(braket
l_int|1
)braket
comma
id|param
(braket
l_int|2
)braket
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
id|ARRAY_SIZE
c_func
(paren
id|rates
)paren
op_logical_and
id|param
(braket
l_int|2
)braket
op_ne
id|rates
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
suffix:semicolon
op_star
id|version
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
(paren
id|param
(braket
l_int|1
)braket
op_lshift
l_int|4
)paren
op_or
id|i
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
id|ARRAY_SIZE
c_func
(paren
id|alps_model_data
)paren
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_logical_neg
id|memcmp
c_func
(paren
id|param
comma
id|alps_model_data
(braket
id|i
)braket
dot
id|signature
comma
r_sizeof
(paren
id|alps_model_data
(braket
id|i
)braket
dot
id|signature
)paren
)paren
)paren
r_return
id|alps_model_data
(braket
id|i
)braket
dot
id|flags
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * For DualPoint devices select the device that should respond to&n; * subsequent commands. It looks like glidepad is behind stickpointer,&n; * I&squot;d thought it would be other way around...&n; */
DECL|function|alps_passthrough_mode
r_static
r_int
id|alps_passthrough_mode
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
id|enable
)paren
(brace
r_struct
id|ps2dev
op_star
id|ps2dev
op_assign
op_amp
id|psmouse-&gt;ps2dev
suffix:semicolon
r_int
r_char
id|param
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|cmd
op_assign
id|enable
ques
c_cond
id|PSMOUSE_CMD_SETSCALE21
suffix:colon
id|PSMOUSE_CMD_SETSCALE11
suffix:semicolon
r_if
c_cond
(paren
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|cmd
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|cmd
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|cmd
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_DISABLE
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* we may get 3 more bytes, just ignore them */
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
l_int|0x0300
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alps_absolute_mode
r_static
r_int
id|alps_absolute_mode
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_struct
id|ps2dev
op_star
id|ps2dev
op_assign
op_amp
id|psmouse-&gt;ps2dev
suffix:semicolon
multiline_comment|/* Try ALPS magic knock - 4 disable before enable */
r_if
c_cond
(paren
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_DISABLE
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_DISABLE
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_DISABLE
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_DISABLE
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_ENABLE
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/*&n;&t; * Switch mouse to poll (remote) mode so motion data will not&n;&t; * get in our way&n;&t; */
r_return
id|ps2_command
c_func
(paren
op_amp
id|psmouse-&gt;ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_SETPOLL
)paren
suffix:semicolon
)brace
DECL|function|alps_get_status
r_static
r_int
id|alps_get_status
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_char
op_star
id|param
)paren
(brace
r_struct
id|ps2dev
op_star
id|ps2dev
op_assign
op_amp
id|psmouse-&gt;ps2dev
suffix:semicolon
multiline_comment|/* Get status: 0xF5 0xF5 0xF5 0xE9 */
r_if
c_cond
(paren
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_DISABLE
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_DISABLE
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_DISABLE
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_GETINFO
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|dbg
c_func
(paren
l_string|&quot;Status: %2.2x %2.2x %2.2x&quot;
comma
id|param
(braket
l_int|0
)braket
comma
id|param
(braket
l_int|1
)braket
comma
id|param
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Turn touchpad tapping on or off. The sequences are:&n; * 0xE9 0xF5 0xF5 0xF3 0x0A to enable,&n; * 0xE9 0xF5 0xF5 0xE8 0x00 to disable.&n; * My guess that 0xE9 (GetInfo) is here as a sync point.&n; * For models that also have stickpointer (DualPoints) its tapping&n; * is controlled separately (0xE6 0xE6 0xE6 0xF3 0x14|0x0A) but&n; * we don&squot;t fiddle with it.&n; */
DECL|function|alps_tap_mode
r_static
r_int
id|alps_tap_mode
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
id|enable
)paren
(brace
r_struct
id|ps2dev
op_star
id|ps2dev
op_assign
op_amp
id|psmouse-&gt;ps2dev
suffix:semicolon
r_int
id|cmd
op_assign
id|enable
ques
c_cond
id|PSMOUSE_CMD_SETRATE
suffix:colon
id|PSMOUSE_CMD_SETRES
suffix:semicolon
r_int
r_char
id|tap_arg
op_assign
id|enable
ques
c_cond
l_int|0x0A
suffix:colon
l_int|0x00
suffix:semicolon
r_int
r_char
id|param
(braket
l_int|4
)braket
suffix:semicolon
r_if
c_cond
(paren
id|ps2_command
c_func
(paren
id|ps2dev
comma
id|param
comma
id|PSMOUSE_CMD_GETINFO
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_DISABLE
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
l_int|NULL
comma
id|PSMOUSE_CMD_DISABLE
)paren
op_logical_or
id|ps2_command
c_func
(paren
id|ps2dev
comma
op_amp
id|tap_arg
comma
id|cmd
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|alps_get_status
c_func
(paren
id|psmouse
comma
id|param
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alps_reconnect
r_static
r_int
id|alps_reconnect
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_struct
id|alps_data
op_star
id|priv
op_assign
id|psmouse
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
r_char
id|param
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|version
suffix:semicolon
r_if
c_cond
(paren
(paren
id|priv-&gt;flags
op_assign
id|alps_get_model
c_func
(paren
id|psmouse
comma
op_amp
id|version
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;flags
op_amp
id|ALPS_DUALPOINT
op_logical_and
id|alps_passthrough_mode
c_func
(paren
id|psmouse
comma
l_int|1
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|alps_get_status
c_func
(paren
id|psmouse
comma
id|param
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|param
(braket
l_int|0
)braket
op_amp
l_int|0x04
)paren
id|alps_tap_mode
c_func
(paren
id|psmouse
comma
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alps_absolute_mode
c_func
(paren
id|psmouse
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;alps.c: Failed to enable absolute mode&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|priv-&gt;flags
op_eq
id|ALPS_DUALPOINT
op_logical_and
id|alps_passthrough_mode
c_func
(paren
id|psmouse
comma
l_int|0
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|alps_disconnect
r_static
r_void
id|alps_disconnect
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_struct
id|alps_data
op_star
id|priv
op_assign
id|psmouse
op_member_access_from_pointer
r_private
suffix:semicolon
id|psmouse_reset
c_func
(paren
id|psmouse
)paren
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|priv-&gt;dev2
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
)brace
DECL|function|alps_init
r_int
id|alps_init
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
)paren
(brace
r_struct
id|alps_data
op_star
id|priv
suffix:semicolon
r_int
r_char
id|param
(braket
l_int|4
)braket
suffix:semicolon
r_int
id|version
suffix:semicolon
id|psmouse
op_member_access_from_pointer
r_private
op_assign
id|priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|alps_data
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|priv
)paren
r_goto
id|init_fail
suffix:semicolon
id|memset
c_func
(paren
id|priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|alps_data
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|priv-&gt;flags
op_assign
id|alps_get_model
c_func
(paren
id|psmouse
comma
op_amp
id|version
)paren
)paren
OL
l_int|0
)paren
r_goto
id|init_fail
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;ALPS Touchpad (%s) detected&bslash;n&quot;
comma
(paren
id|priv-&gt;flags
op_amp
id|ALPS_DUALPOINT
)paren
ques
c_cond
l_string|&quot;DualPoint&quot;
suffix:colon
l_string|&quot;GlidePoint&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|priv-&gt;flags
op_amp
id|ALPS_DUALPOINT
)paren
op_logical_and
id|alps_passthrough_mode
c_func
(paren
id|psmouse
comma
l_int|1
)paren
)paren
r_goto
id|init_fail
suffix:semicolon
r_if
c_cond
(paren
id|alps_get_status
c_func
(paren
id|psmouse
comma
id|param
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;alps.c: touchpad status report request failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|init_fail
suffix:semicolon
)brace
r_if
c_cond
(paren
id|param
(braket
l_int|0
)braket
op_amp
l_int|0x04
)paren
(brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;  Enabling hardware tapping&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|alps_tap_mode
c_func
(paren
id|psmouse
comma
l_int|1
)paren
)paren
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;alps.c: Failed to enable hardware tapping&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|alps_absolute_mode
c_func
(paren
id|psmouse
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;alps.c: Failed to enable absolute mode&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|init_fail
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|priv-&gt;flags
op_amp
id|ALPS_DUALPOINT
)paren
op_logical_and
id|alps_passthrough_mode
c_func
(paren
id|psmouse
comma
l_int|0
)paren
)paren
r_goto
id|init_fail
suffix:semicolon
id|psmouse-&gt;dev.evbit
(braket
id|LONG
c_func
(paren
id|EV_KEY
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|EV_KEY
)paren
suffix:semicolon
id|psmouse-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_TOUCH
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_TOUCH
)paren
suffix:semicolon
id|psmouse-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_TOOL_FINGER
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_TOOL_FINGER
)paren
suffix:semicolon
id|psmouse-&gt;dev.keybit
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
id|BTN_MIDDLE
)paren
op_or
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
suffix:semicolon
id|psmouse-&gt;dev.evbit
(braket
id|LONG
c_func
(paren
id|EV_ABS
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|EV_ABS
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
op_amp
id|psmouse-&gt;dev
comma
id|ABS_X
comma
l_int|0
comma
l_int|1023
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
op_amp
id|psmouse-&gt;dev
comma
id|ABS_Y
comma
l_int|0
comma
l_int|767
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
id|input_set_abs_params
c_func
(paren
op_amp
id|psmouse-&gt;dev
comma
id|ABS_PRESSURE
comma
l_int|0
comma
l_int|127
comma
l_int|0
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|priv-&gt;flags
op_amp
id|ALPS_WHEEL
)paren
(brace
id|psmouse-&gt;dev.evbit
(braket
id|LONG
c_func
(paren
id|EV_REL
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|EV_REL
)paren
suffix:semicolon
id|psmouse-&gt;dev.relbit
(braket
id|LONG
c_func
(paren
id|REL_WHEEL
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|REL_WHEEL
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|priv-&gt;flags
op_amp
id|ALPS_FW_BK
)paren
(brace
id|psmouse-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_FORWARD
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_FORWARD
)paren
suffix:semicolon
id|psmouse-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_BACK
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_BACK
)paren
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|priv-&gt;phys
comma
l_string|&quot;%s/input1&quot;
comma
id|psmouse-&gt;ps2dev.serio-&gt;phys
)paren
suffix:semicolon
id|priv-&gt;dev2.phys
op_assign
id|priv-&gt;phys
suffix:semicolon
id|priv-&gt;dev2.name
op_assign
(paren
id|priv-&gt;flags
op_amp
id|ALPS_DUALPOINT
)paren
ques
c_cond
l_string|&quot;DualPoint Stick&quot;
suffix:colon
l_string|&quot;PS/2 Mouse&quot;
suffix:semicolon
id|priv-&gt;dev2.id.bustype
op_assign
id|BUS_I8042
suffix:semicolon
id|priv-&gt;dev2.id.vendor
op_assign
l_int|0x0002
suffix:semicolon
id|priv-&gt;dev2.id.product
op_assign
id|PSMOUSE_ALPS
suffix:semicolon
id|priv-&gt;dev2.id.version
op_assign
l_int|0x0000
suffix:semicolon
id|priv-&gt;dev2.evbit
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
id|priv-&gt;dev2.relbit
(braket
id|LONG
c_func
(paren
id|REL_X
)paren
)braket
op_or_assign
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
id|priv-&gt;dev2.keybit
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
id|BTN_MIDDLE
)paren
op_or
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|priv-&gt;dev2
)paren
suffix:semicolon
id|psmouse-&gt;protocol_handler
op_assign
id|alps_process_byte
suffix:semicolon
id|psmouse-&gt;disconnect
op_assign
id|alps_disconnect
suffix:semicolon
id|psmouse-&gt;reconnect
op_assign
id|alps_reconnect
suffix:semicolon
id|psmouse-&gt;pktsize
op_assign
l_int|6
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|init_fail
suffix:colon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
DECL|function|alps_detect
r_int
id|alps_detect
c_func
(paren
r_struct
id|psmouse
op_star
id|psmouse
comma
r_int
id|set_properties
)paren
(brace
r_int
id|version
suffix:semicolon
r_int
id|model
suffix:semicolon
r_if
c_cond
(paren
(paren
id|model
op_assign
id|alps_get_model
c_func
(paren
id|psmouse
comma
op_amp
id|version
)paren
)paren
OL
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|set_properties
)paren
(brace
id|psmouse-&gt;vendor
op_assign
l_string|&quot;ALPS&quot;
suffix:semicolon
r_if
c_cond
(paren
id|model
op_amp
id|ALPS_DUALPOINT
)paren
id|psmouse-&gt;name
op_assign
l_string|&quot;DualPoint TouchPad&quot;
suffix:semicolon
r_else
id|psmouse-&gt;name
op_assign
l_string|&quot;GlidePoint&quot;
suffix:semicolon
id|psmouse-&gt;model
op_assign
id|version
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
eof
