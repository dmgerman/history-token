multiline_comment|/*&n; * $Id: grip.c,v 1.21 2002/01/22 20:27:57 vojtech Exp $&n; *&n; *  Copyright (c) 1998-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * Gravis/Kensington GrIP protocol joystick and gamepad driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
macro_line|#include &lt;linux/input.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Gravis GrIP protocol joystick driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|GRIP_MODE_GPP
mdefine_line|#define GRIP_MODE_GPP&t;&t;1
DECL|macro|GRIP_MODE_BD
mdefine_line|#define GRIP_MODE_BD&t;&t;2
DECL|macro|GRIP_MODE_XT
mdefine_line|#define GRIP_MODE_XT&t;&t;3
DECL|macro|GRIP_MODE_DC
mdefine_line|#define GRIP_MODE_DC&t;&t;4
DECL|macro|GRIP_LENGTH_GPP
mdefine_line|#define GRIP_LENGTH_GPP&t;&t;24
DECL|macro|GRIP_STROBE_GPP
mdefine_line|#define GRIP_STROBE_GPP&t;&t;200&t;/* 200 us */
DECL|macro|GRIP_LENGTH_XT
mdefine_line|#define GRIP_LENGTH_XT&t;&t;4
DECL|macro|GRIP_STROBE_XT
mdefine_line|#define GRIP_STROBE_XT&t;&t;64&t;/* 64 us */
DECL|macro|GRIP_MAX_CHUNKS_XT
mdefine_line|#define GRIP_MAX_CHUNKS_XT&t;10
DECL|macro|GRIP_MAX_BITS_XT
mdefine_line|#define GRIP_MAX_BITS_XT&t;30
DECL|macro|GRIP_REFRESH_TIME
mdefine_line|#define GRIP_REFRESH_TIME&t;HZ/50&t;/* 20 ms */
DECL|struct|grip
r_struct
id|grip
(brace
DECL|member|gameport
r_struct
id|gameport
op_star
id|gameport
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
id|dev
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|mode
r_int
r_char
id|mode
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|used
r_int
id|used
suffix:semicolon
DECL|member|reads
r_int
id|reads
suffix:semicolon
DECL|member|bads
r_int
id|bads
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|2
)braket
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|grip_btn_gpp
r_static
r_int
id|grip_btn_gpp
(braket
)braket
op_assign
(brace
id|BTN_START
comma
id|BTN_SELECT
comma
id|BTN_TR2
comma
id|BTN_Y
comma
l_int|0
comma
id|BTN_TL2
comma
id|BTN_A
comma
id|BTN_B
comma
id|BTN_X
comma
l_int|0
comma
id|BTN_TL
comma
id|BTN_TR
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|grip_btn_bd
r_static
r_int
id|grip_btn_bd
(braket
)braket
op_assign
(brace
id|BTN_THUMB
comma
id|BTN_THUMB2
comma
id|BTN_TRIGGER
comma
id|BTN_TOP
comma
id|BTN_BASE
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|grip_btn_xt
r_static
r_int
id|grip_btn_xt
(braket
)braket
op_assign
(brace
id|BTN_TRIGGER
comma
id|BTN_THUMB
comma
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
id|BTN_SELECT
comma
id|BTN_START
comma
id|BTN_MODE
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|grip_btn_dc
r_static
r_int
id|grip_btn_dc
(braket
)braket
op_assign
(brace
id|BTN_TRIGGER
comma
id|BTN_THUMB
comma
id|BTN_TOP
comma
id|BTN_TOP2
comma
id|BTN_BASE
comma
id|BTN_BASE2
comma
id|BTN_BASE3
comma
id|BTN_BASE4
comma
id|BTN_BASE5
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|grip_abs_gpp
r_static
r_int
id|grip_abs_gpp
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|grip_abs_bd
r_static
r_int
id|grip_abs_bd
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
id|ABS_THROTTLE
comma
id|ABS_HAT0X
comma
id|ABS_HAT0Y
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|grip_abs_xt
r_static
r_int
id|grip_abs_xt
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
id|ABS_BRAKE
comma
id|ABS_GAS
comma
id|ABS_THROTTLE
comma
id|ABS_HAT0X
comma
id|ABS_HAT0Y
comma
id|ABS_HAT1X
comma
id|ABS_HAT1Y
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|grip_abs_dc
r_static
r_int
id|grip_abs_dc
(braket
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
id|ABS_RX
comma
id|ABS_RY
comma
id|ABS_THROTTLE
comma
id|ABS_HAT0X
comma
id|ABS_HAT0Y
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|grip_name
r_static
r_char
op_star
id|grip_name
(braket
)braket
op_assign
(brace
l_int|NULL
comma
l_string|&quot;Gravis GamePad Pro&quot;
comma
l_string|&quot;Gravis Blackhawk Digital&quot;
comma
l_string|&quot;Gravis Xterminator Digital&quot;
comma
l_string|&quot;Gravis Xterminator DualControl&quot;
)brace
suffix:semicolon
DECL|variable|grip_abs
r_static
r_int
op_star
id|grip_abs
(braket
)braket
op_assign
(brace
l_int|0
comma
id|grip_abs_gpp
comma
id|grip_abs_bd
comma
id|grip_abs_xt
comma
id|grip_abs_dc
)brace
suffix:semicolon
DECL|variable|grip_btn
r_static
r_int
op_star
id|grip_btn
(braket
)braket
op_assign
(brace
l_int|0
comma
id|grip_btn_gpp
comma
id|grip_btn_bd
comma
id|grip_btn_xt
comma
id|grip_btn_dc
)brace
suffix:semicolon
DECL|variable|grip_anx
r_static
r_char
id|grip_anx
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|3
comma
l_int|5
comma
l_int|5
)brace
suffix:semicolon
DECL|variable|grip_cen
r_static
r_char
id|grip_cen
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|0
comma
l_int|2
comma
l_int|2
comma
l_int|4
)brace
suffix:semicolon
multiline_comment|/*&n; * grip_gpp_read_packet() reads a Gravis GamePad Pro packet.&n; */
DECL|function|grip_gpp_read_packet
r_static
r_int
id|grip_gpp_read_packet
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
id|shift
comma
r_int
r_int
op_star
id|data
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
r_char
id|u
comma
id|v
suffix:semicolon
r_int
r_int
id|t
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|strobe
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|GRIP_STROBE_GPP
)paren
suffix:semicolon
id|data
(braket
l_int|0
)braket
op_assign
l_int|0
suffix:semicolon
id|t
op_assign
id|strobe
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|v
op_assign
id|gameport_read
c_func
(paren
id|gameport
)paren
op_rshift
id|shift
suffix:semicolon
r_do
(brace
id|t
op_decrement
suffix:semicolon
id|u
op_assign
id|v
suffix:semicolon
id|v
op_assign
(paren
id|gameport_read
c_func
(paren
id|gameport
)paren
op_rshift
id|shift
)paren
op_amp
l_int|3
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|v
op_amp
id|u
op_amp
l_int|1
)paren
(brace
id|data
(braket
l_int|0
)braket
op_or_assign
(paren
id|v
op_rshift
l_int|1
)paren
op_lshift
id|i
op_increment
suffix:semicolon
id|t
op_assign
id|strobe
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|i
template_param
l_int|0
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|GRIP_LENGTH_GPP
)paren
r_return
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
id|GRIP_LENGTH_GPP
op_logical_and
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|0xfe4210
)paren
op_xor
l_int|0x7c0000
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
l_int|0
)braket
op_assign
id|data
(braket
l_int|0
)braket
op_rshift
l_int|1
op_or
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
op_lshift
(paren
id|GRIP_LENGTH_GPP
op_minus
l_int|1
)paren
suffix:semicolon
r_return
op_minus
(paren
id|i
op_eq
id|GRIP_LENGTH_GPP
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * grip_xt_read_packet() reads a Gravis Xterminator packet.&n; */
DECL|function|grip_xt_read_packet
r_static
r_int
id|grip_xt_read_packet
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
id|shift
comma
r_int
r_int
op_star
id|data
)paren
(brace
r_int
r_int
id|i
comma
id|j
comma
id|buf
comma
id|crc
suffix:semicolon
r_int
r_char
id|u
comma
id|v
comma
id|w
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
r_int
id|t
suffix:semicolon
r_char
id|status
suffix:semicolon
r_int
id|strobe
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|GRIP_STROBE_XT
)paren
suffix:semicolon
id|data
(braket
l_int|0
)braket
op_assign
id|data
(braket
l_int|1
)braket
op_assign
id|data
(braket
l_int|2
)braket
op_assign
id|data
(braket
l_int|3
)braket
op_assign
l_int|0
suffix:semicolon
id|status
op_assign
id|buf
op_assign
id|i
op_assign
id|j
op_assign
l_int|0
suffix:semicolon
id|t
op_assign
id|strobe
suffix:semicolon
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|v
op_assign
id|w
op_assign
(paren
id|gameport_read
c_func
(paren
id|gameport
)paren
op_rshift
id|shift
)paren
op_amp
l_int|3
suffix:semicolon
r_do
(brace
id|t
op_decrement
suffix:semicolon
id|u
op_assign
(paren
id|gameport_read
c_func
(paren
id|gameport
)paren
op_rshift
id|shift
)paren
op_amp
l_int|3
suffix:semicolon
r_if
c_cond
(paren
id|u
op_xor
id|v
)paren
(brace
r_if
c_cond
(paren
(paren
id|u
op_xor
id|v
)paren
op_amp
l_int|1
)paren
(brace
id|buf
op_assign
(paren
id|buf
op_lshift
l_int|1
)paren
op_or
(paren
id|u
op_rshift
l_int|1
)paren
suffix:semicolon
id|t
op_assign
id|strobe
suffix:semicolon
id|i
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
(paren
(paren
(paren
id|u
op_xor
id|v
)paren
op_amp
(paren
id|v
op_xor
id|w
)paren
)paren
op_rshift
l_int|1
)paren
op_amp
op_complement
(paren
id|u
op_or
id|v
op_or
id|w
)paren
op_amp
l_int|1
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
l_int|20
)paren
(brace
id|crc
op_assign
id|buf
op_xor
(paren
id|buf
op_rshift
l_int|7
)paren
op_xor
(paren
id|buf
op_rshift
l_int|14
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
(paren
id|crc
op_xor
(paren
l_int|0x25cb9e70
op_rshift
(paren
(paren
id|crc
op_rshift
l_int|2
)paren
op_amp
l_int|0x1c
)paren
)paren
)paren
op_amp
l_int|0xf
)paren
)paren
(brace
id|data
(braket
id|buf
op_rshift
l_int|18
)braket
op_assign
id|buf
op_rshift
l_int|4
suffix:semicolon
id|status
op_or_assign
l_int|1
op_lshift
(paren
id|buf
op_rshift
l_int|18
)paren
suffix:semicolon
)brace
id|j
op_increment
suffix:semicolon
)brace
id|t
op_assign
id|strobe
suffix:semicolon
id|buf
op_assign
l_int|0
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
)brace
id|w
op_assign
id|v
suffix:semicolon
id|v
op_assign
id|u
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|status
op_ne
l_int|0xf
op_logical_and
id|i
OL
id|GRIP_MAX_BITS_XT
op_logical_and
id|j
template_param
l_int|0
)paren
suffix:semicolon
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
op_minus
(paren
id|status
op_ne
l_int|0xf
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * grip_timer() repeatedly polls the joysticks and generates events.&n; */
DECL|function|grip_timer
r_static
r_void
id|grip_timer
c_func
(paren
r_int
r_int
r_private
)paren
(brace
r_struct
id|grip
op_star
id|grip
op_assign
(paren
r_void
op_star
)paren
r_private
suffix:semicolon
r_int
r_int
id|data
(braket
id|GRIP_LENGTH_XT
)braket
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
suffix:semicolon
r_int
id|i
comma
id|j
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev
op_assign
id|grip-&gt;dev
op_plus
id|i
suffix:semicolon
id|grip-&gt;reads
op_increment
suffix:semicolon
r_switch
c_cond
(paren
id|grip-&gt;mode
(braket
id|i
)braket
)paren
(brace
r_case
id|GRIP_MODE_GPP
suffix:colon
r_if
c_cond
(paren
id|grip_gpp_read_packet
c_func
(paren
id|grip-&gt;gameport
comma
(paren
id|i
op_lshift
l_int|1
)paren
op_plus
l_int|4
comma
id|data
)paren
)paren
(brace
id|grip-&gt;bads
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
(paren
(paren
op_star
id|data
op_rshift
l_int|15
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
op_star
id|data
op_rshift
l_int|16
)paren
op_amp
l_int|1
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
(paren
op_star
id|data
op_rshift
l_int|13
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
op_star
id|data
op_rshift
l_int|12
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|12
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|grip_btn_gpp
(braket
id|j
)braket
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|grip_btn_gpp
(braket
id|j
)braket
comma
(paren
op_star
id|data
op_rshift
id|j
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GRIP_MODE_BD
suffix:colon
r_if
c_cond
(paren
id|grip_xt_read_packet
c_func
(paren
id|grip-&gt;gameport
comma
(paren
id|i
op_lshift
l_int|1
)paren
op_plus
l_int|4
comma
id|data
)paren
)paren
(brace
id|grip-&gt;bads
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
(paren
id|data
(braket
l_int|0
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Y
comma
l_int|63
op_minus
(paren
(paren
id|data
(braket
l_int|0
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_THROTTLE
comma
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0X
comma
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|1
)paren
op_minus
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|1
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
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|5
suffix:semicolon
id|j
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|grip_btn_bd
(braket
id|j
)braket
comma
(paren
id|data
(braket
l_int|3
)braket
op_rshift
(paren
id|j
op_plus
l_int|4
)paren
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GRIP_MODE_XT
suffix:colon
r_if
c_cond
(paren
id|grip_xt_read_packet
c_func
(paren
id|grip-&gt;gameport
comma
(paren
id|i
op_lshift
l_int|1
)paren
op_plus
l_int|4
comma
id|data
)paren
)paren
(brace
id|grip-&gt;bads
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
(paren
id|data
(braket
l_int|0
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Y
comma
l_int|63
op_minus
(paren
(paren
id|data
(braket
l_int|0
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_BRAKE
comma
(paren
id|data
(braket
l_int|1
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_GAS
comma
(paren
id|data
(braket
l_int|1
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_THROTTLE
comma
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0X
comma
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|1
)paren
op_minus
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|1
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
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT1X
comma
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT1Y
comma
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|6
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|7
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|11
suffix:semicolon
id|j
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|grip_btn_xt
(braket
id|j
)braket
comma
(paren
id|data
(braket
l_int|3
)braket
op_rshift
(paren
id|j
op_plus
l_int|3
)paren
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|GRIP_MODE_DC
suffix:colon
r_if
c_cond
(paren
id|grip_xt_read_packet
c_func
(paren
id|grip-&gt;gameport
comma
(paren
id|i
op_lshift
l_int|1
)paren
op_plus
l_int|4
comma
id|data
)paren
)paren
(brace
id|grip-&gt;bads
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
(paren
id|data
(braket
l_int|0
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x3f
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
id|data
(braket
l_int|0
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_RX
comma
(paren
id|data
(braket
l_int|1
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|0x3f
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
id|data
(braket
l_int|1
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_THROTTLE
comma
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0X
comma
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|1
)paren
op_minus
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|1
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
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|9
suffix:semicolon
id|j
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|grip_btn_dc
(braket
id|j
)braket
comma
(paren
id|data
(braket
l_int|3
)braket
op_rshift
(paren
id|j
op_plus
l_int|3
)paren
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|mod_timer
c_func
(paren
op_amp
id|grip-&gt;timer
comma
id|jiffies
op_plus
id|GRIP_REFRESH_TIME
)paren
suffix:semicolon
)brace
DECL|function|grip_open
r_static
r_int
id|grip_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|grip
op_star
id|grip
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|grip-&gt;used
op_increment
)paren
id|mod_timer
c_func
(paren
op_amp
id|grip-&gt;timer
comma
id|jiffies
op_plus
id|GRIP_REFRESH_TIME
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|grip_close
r_static
r_void
id|grip_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|grip
op_star
id|grip
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
id|grip-&gt;used
)paren
id|del_timer
c_func
(paren
op_amp
id|grip-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|grip_connect
r_static
r_void
id|grip_connect
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_struct
id|gameport_dev
op_star
id|dev
)paren
(brace
r_struct
id|grip
op_star
id|grip
suffix:semicolon
r_int
r_int
id|data
(braket
id|GRIP_LENGTH_XT
)braket
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|t
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|grip
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|grip
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
id|grip
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|grip
)paren
)paren
suffix:semicolon
id|gameport
op_member_access_from_pointer
r_private
op_assign
id|grip
suffix:semicolon
id|grip-&gt;gameport
op_assign
id|gameport
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|grip-&gt;timer
)paren
suffix:semicolon
id|grip-&gt;timer.data
op_assign
(paren
r_int
)paren
id|grip
suffix:semicolon
id|grip-&gt;timer.function
op_assign
id|grip_timer
suffix:semicolon
r_if
c_cond
(paren
id|gameport_open
c_func
(paren
id|gameport
comma
id|dev
comma
id|GAMEPORT_MODE_RAW
)paren
)paren
r_goto
id|fail1
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|grip_gpp_read_packet
c_func
(paren
id|gameport
comma
(paren
id|i
op_lshift
l_int|1
)paren
op_plus
l_int|4
comma
id|data
)paren
)paren
(brace
id|grip-&gt;mode
(braket
id|i
)braket
op_assign
id|GRIP_MODE_GPP
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|grip_xt_read_packet
c_func
(paren
id|gameport
comma
(paren
id|i
op_lshift
l_int|1
)paren
op_plus
l_int|4
comma
id|data
)paren
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|7
)paren
)paren
(brace
id|grip-&gt;mode
(braket
id|i
)braket
op_assign
id|GRIP_MODE_BD
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|0xf0
)paren
)paren
(brace
id|grip-&gt;mode
(braket
id|i
)braket
op_assign
id|GRIP_MODE_XT
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|grip-&gt;mode
(braket
id|i
)braket
op_assign
id|GRIP_MODE_DC
suffix:semicolon
r_continue
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|grip-&gt;mode
(braket
l_int|0
)braket
op_logical_and
op_logical_neg
id|grip-&gt;mode
(braket
l_int|1
)braket
)paren
r_goto
id|fail2
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|grip-&gt;mode
(braket
id|i
)braket
)paren
(brace
id|sprintf
c_func
(paren
id|grip-&gt;phys
(braket
id|i
)braket
comma
l_string|&quot;%s/input%d&quot;
comma
id|gameport-&gt;phys
comma
id|i
)paren
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
r_private
op_assign
id|grip
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|open
op_assign
id|grip_open
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|close
op_assign
id|grip_close
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|name
op_assign
id|grip_name
(braket
id|grip-&gt;mode
(braket
id|i
)braket
)braket
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|phys
op_assign
id|grip-&gt;phys
(braket
id|i
)braket
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|id.bustype
op_assign
id|BUS_GAMEPORT
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|id.vendor
op_assign
id|GAMEPORT_ID_VENDOR_GRAVIS
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|id.product
op_assign
id|grip-&gt;mode
(braket
id|i
)braket
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|id.version
op_assign
l_int|0x0100
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|evbit
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
id|j
op_assign
l_int|0
suffix:semicolon
(paren
id|t
op_assign
id|grip_abs
(braket
id|grip-&gt;mode
(braket
id|i
)braket
)braket
(braket
id|j
)braket
)paren
op_ge
l_int|0
suffix:semicolon
id|j
op_increment
)paren
(brace
id|set_bit
c_func
(paren
id|t
comma
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|absbit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
id|grip_cen
(braket
id|grip-&gt;mode
(braket
id|i
)braket
)braket
)paren
(brace
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|absmin
(braket
id|t
)braket
op_assign
l_int|14
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|absmax
(braket
id|t
)braket
op_assign
l_int|52
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|absfuzz
(braket
id|t
)braket
op_assign
l_int|1
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|absflat
(braket
id|t
)braket
op_assign
l_int|2
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|j
OL
id|grip_anx
(braket
id|grip-&gt;mode
(braket
id|i
)braket
)braket
)paren
(brace
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|absmin
(braket
id|t
)braket
op_assign
l_int|3
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|absmax
(braket
id|t
)braket
op_assign
l_int|57
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|absfuzz
(braket
id|t
)braket
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|absmin
(braket
id|t
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|absmax
(braket
id|t
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
(paren
id|t
op_assign
id|grip_btn
(braket
id|grip-&gt;mode
(braket
id|i
)braket
)braket
(braket
id|j
)braket
)paren
op_ge
l_int|0
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|t
OG
l_int|0
)paren
id|set_bit
c_func
(paren
id|t
comma
id|grip-&gt;dev
(braket
id|i
)braket
dot
id|keybit
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
id|grip-&gt;dev
op_plus
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|grip_name
(braket
id|grip-&gt;mode
(braket
id|i
)braket
)braket
comma
id|gameport-&gt;phys
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
id|fail2
suffix:colon
id|gameport_close
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|fail1
suffix:colon
id|kfree
c_func
(paren
id|grip
)paren
suffix:semicolon
)brace
DECL|function|grip_disconnect
r_static
r_void
id|grip_disconnect
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|grip
op_star
id|grip
op_assign
id|gameport
op_member_access_from_pointer
r_private
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|grip-&gt;mode
(braket
id|i
)braket
)paren
id|input_unregister_device
c_func
(paren
id|grip-&gt;dev
op_plus
id|i
)paren
suffix:semicolon
id|gameport_close
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|grip
)paren
suffix:semicolon
)brace
DECL|variable|grip_dev
r_static
r_struct
id|gameport_dev
id|grip_dev
op_assign
(brace
dot
id|connect
op_assign
id|grip_connect
comma
dot
id|disconnect
op_assign
id|grip_disconnect
comma
)brace
suffix:semicolon
DECL|function|grip_init
r_int
id|__init
id|grip_init
c_func
(paren
r_void
)paren
(brace
id|gameport_register_device
c_func
(paren
op_amp
id|grip_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|grip_exit
r_void
id|__exit
id|grip_exit
c_func
(paren
r_void
)paren
(brace
id|gameport_unregister_device
c_func
(paren
op_amp
id|grip_dev
)paren
suffix:semicolon
)brace
DECL|variable|grip_init
id|module_init
c_func
(paren
id|grip_init
)paren
suffix:semicolon
DECL|variable|grip_exit
id|module_exit
c_func
(paren
id|grip_exit
)paren
suffix:semicolon
eof
