multiline_comment|/*&n; * $Id: tmdc.c,v 1.31 2002/01/22 20:29:52 vojtech Exp $&n; *&n; *  Copyright (c) 1998-2001 Vojtech Pavlik&n; *&n; *   Based on the work of:&n; *&t;Trystan Larey-Williams &n; */
multiline_comment|/*&n; * ThrustMaster DirectConnect (BSP) joystick family driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
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
l_string|&quot;ThrustMaster DirectConnect joystick driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|TMDC_MAX_START
mdefine_line|#define TMDC_MAX_START&t;&t;400&t;/* 400 us */
DECL|macro|TMDC_MAX_STROBE
mdefine_line|#define TMDC_MAX_STROBE&t;&t;45&t;/* 45 us */
DECL|macro|TMDC_MAX_LENGTH
mdefine_line|#define TMDC_MAX_LENGTH&t;&t;13
DECL|macro|TMDC_REFRESH_TIME
mdefine_line|#define TMDC_REFRESH_TIME&t;HZ/50&t;/* 20 ms */
DECL|macro|TMDC_MODE_M3DI
mdefine_line|#define TMDC_MODE_M3DI&t;&t;1
DECL|macro|TMDC_MODE_3DRP
mdefine_line|#define TMDC_MODE_3DRP&t;&t;3
DECL|macro|TMDC_MODE_AT
mdefine_line|#define TMDC_MODE_AT&t;&t;4
DECL|macro|TMDC_MODE_FM
mdefine_line|#define TMDC_MODE_FM&t;&t;8
DECL|macro|TMDC_MODE_FGP
mdefine_line|#define TMDC_MODE_FGP&t;&t;163
DECL|macro|TMDC_BYTE_ID
mdefine_line|#define TMDC_BYTE_ID&t;&t;10
DECL|macro|TMDC_BYTE_REV
mdefine_line|#define TMDC_BYTE_REV&t;&t;11
DECL|macro|TMDC_BYTE_DEF
mdefine_line|#define TMDC_BYTE_DEF&t;&t;12
DECL|macro|TMDC_ABS
mdefine_line|#define TMDC_ABS&t;&t;7&t;
DECL|macro|TMDC_ABS_HAT
mdefine_line|#define TMDC_ABS_HAT&t;&t;4
DECL|macro|TMDC_BTN
mdefine_line|#define TMDC_BTN&t;&t;16
DECL|variable|tmdc_byte_a
r_static
r_int
r_char
id|tmdc_byte_a
(braket
l_int|16
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|3
comma
l_int|4
comma
l_int|6
comma
l_int|7
)brace
suffix:semicolon
DECL|variable|tmdc_byte_d
r_static
r_int
r_char
id|tmdc_byte_d
(braket
l_int|16
)braket
op_assign
(brace
l_int|2
comma
l_int|5
comma
l_int|8
comma
l_int|9
)brace
suffix:semicolon
DECL|variable|tmdc_abs
r_static
r_int
r_char
id|tmdc_abs
(braket
id|TMDC_ABS
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
id|ABS_RUDDER
comma
id|ABS_THROTTLE
comma
id|ABS_RX
comma
id|ABS_RY
comma
id|ABS_RZ
)brace
suffix:semicolon
DECL|variable|tmdc_abs_hat
r_static
r_int
r_char
id|tmdc_abs_hat
(braket
id|TMDC_ABS_HAT
)braket
op_assign
(brace
id|ABS_HAT0X
comma
id|ABS_HAT0Y
comma
id|ABS_HAT1X
comma
id|ABS_HAT1Y
)brace
suffix:semicolon
DECL|variable|tmdc_abs_at
r_static
r_int
r_char
id|tmdc_abs_at
(braket
id|TMDC_ABS
)braket
op_assign
(brace
id|ABS_X
comma
id|ABS_Y
comma
id|ABS_RUDDER
comma
op_minus
l_int|1
comma
id|ABS_THROTTLE
)brace
suffix:semicolon
DECL|variable|tmdc_abs_fm
r_static
r_int
r_char
id|tmdc_abs_fm
(braket
id|TMDC_ABS
)braket
op_assign
(brace
id|ABS_RX
comma
id|ABS_RY
comma
id|ABS_X
comma
id|ABS_Y
)brace
suffix:semicolon
DECL|variable|tmdc_btn_pad
r_static
r_int
id|tmdc_btn_pad
(braket
id|TMDC_BTN
)braket
op_assign
(brace
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
id|BTN_START
comma
id|BTN_SELECT
comma
id|BTN_TL
comma
id|BTN_TR
)brace
suffix:semicolon
DECL|variable|tmdc_btn_joy
r_static
r_int
id|tmdc_btn_joy
(braket
id|TMDC_BTN
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
id|BTN_THUMB2
comma
id|BTN_PINKIE
comma
id|BTN_BASE3
comma
id|BTN_BASE4
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
)brace
suffix:semicolon
DECL|variable|tmdc_btn_fm
r_static
r_int
id|tmdc_btn_fm
(braket
id|TMDC_BTN
)braket
op_assign
(brace
id|BTN_TRIGGER
comma
id|BTN_C
comma
id|BTN_B
comma
id|BTN_A
comma
id|BTN_THUMB
comma
id|BTN_X
comma
id|BTN_Y
comma
id|BTN_Z
comma
id|BTN_TOP
comma
id|BTN_TOP2
)brace
suffix:semicolon
DECL|variable|tmdc_btn_at
r_static
r_int
id|tmdc_btn_at
(braket
id|TMDC_BTN
)braket
op_assign
(brace
id|BTN_TRIGGER
comma
id|BTN_THUMB2
comma
id|BTN_PINKIE
comma
id|BTN_THUMB
comma
id|BTN_BASE6
comma
id|BTN_BASE5
comma
id|BTN_BASE4
comma
id|BTN_BASE3
comma
id|BTN_BASE2
comma
id|BTN_BASE
)brace
suffix:semicolon
r_static
r_struct
(brace
DECL|member|x
r_int
id|x
suffix:semicolon
DECL|member|y
r_int
id|y
suffix:semicolon
DECL|variable|tmdc_hat_to_axis
)brace
id|tmdc_hat_to_axis
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
l_int|1
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
op_minus
l_int|1
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|1
)brace
)brace
suffix:semicolon
DECL|struct|tmdc
r_struct
id|tmdc
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
DECL|member|name
r_char
id|name
(braket
l_int|2
)braket
(braket
l_int|64
)braket
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
DECL|member|mode
r_int
id|mode
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|abs
r_int
r_char
op_star
id|abs
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|btn
r_int
op_star
id|btn
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|absc
r_int
r_char
id|absc
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|btnc
r_int
r_char
id|btnc
(braket
l_int|2
)braket
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|btno
r_int
r_char
id|btno
(braket
l_int|2
)braket
(braket
l_int|4
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
DECL|member|exists
r_int
r_char
id|exists
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * tmdc_read_packet() reads a ThrustMaster packet.&n; */
DECL|function|tmdc_read_packet
r_static
r_int
id|tmdc_read_packet
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
r_char
id|data
(braket
l_int|2
)braket
(braket
id|TMDC_MAX_LENGTH
)braket
)paren
(brace
r_int
r_char
id|u
comma
id|v
comma
id|w
comma
id|x
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
(braket
l_int|2
)braket
comma
id|j
(braket
l_int|2
)braket
comma
id|t
(braket
l_int|2
)braket
comma
id|p
comma
id|k
suffix:semicolon
id|p
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|TMDC_MAX_STROBE
)paren
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|2
suffix:semicolon
id|k
op_increment
)paren
(brace
id|t
(braket
id|k
)braket
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|TMDC_MAX_START
)paren
suffix:semicolon
id|i
(braket
id|k
)braket
op_assign
id|j
(braket
id|k
)braket
op_assign
l_int|0
suffix:semicolon
)brace
id|local_irq_save
c_func
(paren
id|flags
)paren
suffix:semicolon
id|gameport_trigger
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|w
op_assign
id|gameport_read
c_func
(paren
id|gameport
)paren
op_rshift
l_int|4
suffix:semicolon
r_do
(brace
id|x
op_assign
id|w
suffix:semicolon
id|w
op_assign
id|gameport_read
c_func
(paren
id|gameport
)paren
op_rshift
l_int|4
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
comma
id|v
op_assign
id|w
comma
id|u
op_assign
id|x
suffix:semicolon
id|k
OL
l_int|2
suffix:semicolon
id|k
op_increment
comma
id|v
op_rshift_assign
l_int|2
comma
id|u
op_rshift_assign
l_int|2
)paren
(brace
r_if
c_cond
(paren
op_complement
id|v
op_amp
id|u
op_amp
l_int|2
)paren
(brace
r_if
c_cond
(paren
id|t
(braket
id|k
)braket
op_le
l_int|0
op_logical_or
id|i
(braket
id|k
)braket
op_ge
id|TMDC_MAX_LENGTH
)paren
r_continue
suffix:semicolon
id|t
(braket
id|k
)braket
op_assign
id|p
suffix:semicolon
r_if
c_cond
(paren
id|j
(braket
id|k
)braket
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Start bit */
r_if
c_cond
(paren
op_complement
id|v
op_amp
l_int|1
)paren
id|t
(braket
id|k
)braket
op_assign
l_int|0
suffix:semicolon
id|data
(braket
id|k
)braket
(braket
id|i
(braket
id|k
)braket
)braket
op_assign
l_int|0
suffix:semicolon
id|j
(braket
id|k
)braket
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
r_if
c_cond
(paren
id|j
(braket
id|k
)braket
op_eq
l_int|9
)paren
(brace
multiline_comment|/* Stop bit */
r_if
c_cond
(paren
id|v
op_amp
l_int|1
)paren
id|t
(braket
id|k
)braket
op_assign
l_int|0
suffix:semicolon
id|j
(braket
id|k
)braket
op_assign
l_int|0
suffix:semicolon
id|i
(braket
id|k
)braket
op_increment
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|data
(braket
id|k
)braket
(braket
id|i
(braket
id|k
)braket
)braket
op_or_assign
(paren
op_complement
id|v
op_amp
l_int|1
)paren
op_lshift
(paren
id|j
(braket
id|k
)braket
op_increment
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Data bit */
)brace
id|t
(braket
id|k
)braket
op_decrement
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|t
(braket
l_int|0
)braket
OG
l_int|0
op_logical_or
id|t
(braket
l_int|1
)braket
OG
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
(paren
id|i
(braket
l_int|0
)braket
op_eq
id|TMDC_MAX_LENGTH
)paren
op_or
(paren
(paren
id|i
(braket
l_int|1
)braket
op_eq
id|TMDC_MAX_LENGTH
)paren
op_lshift
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * tmdc_read() reads and analyzes ThrustMaster joystick data.&n; */
DECL|function|tmdc_timer
r_static
r_void
id|tmdc_timer
c_func
(paren
r_int
r_int
r_private
)paren
(brace
r_int
r_char
id|data
(braket
l_int|2
)braket
(braket
id|TMDC_MAX_LENGTH
)braket
suffix:semicolon
r_struct
id|tmdc
op_star
id|tmdc
op_assign
(paren
r_void
op_star
)paren
r_private
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
suffix:semicolon
r_int
r_char
id|r
comma
id|bad
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
comma
id|l
suffix:semicolon
id|tmdc-&gt;reads
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|tmdc_read_packet
c_func
(paren
id|tmdc-&gt;gameport
comma
id|data
)paren
)paren
op_ne
id|tmdc-&gt;exists
)paren
id|bad
op_assign
l_int|1
suffix:semicolon
r_else
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|2
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|r
op_amp
(paren
l_int|1
op_lshift
id|j
)paren
op_amp
id|tmdc-&gt;exists
)paren
(brace
r_if
c_cond
(paren
id|data
(braket
id|j
)braket
(braket
id|TMDC_BYTE_ID
)braket
op_ne
id|tmdc-&gt;mode
(braket
id|j
)braket
)paren
(brace
id|bad
op_assign
l_int|1
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|dev
op_assign
id|tmdc-&gt;dev
op_plus
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
id|tmdc-&gt;absc
(braket
id|j
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|tmdc-&gt;abs
(braket
id|j
)braket
(braket
id|i
)braket
OL
l_int|0
)paren
r_continue
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|tmdc-&gt;abs
(braket
id|j
)braket
(braket
id|i
)braket
comma
id|data
(braket
id|j
)braket
(braket
id|tmdc_byte_a
(braket
id|i
)braket
)braket
)paren
suffix:semicolon
)brace
r_switch
c_cond
(paren
id|tmdc-&gt;mode
(braket
id|j
)braket
)paren
(brace
r_case
id|TMDC_MODE_M3DI
suffix:colon
id|i
op_assign
id|tmdc_byte_d
(braket
l_int|0
)braket
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
id|j
)braket
(braket
id|i
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
id|j
)braket
(braket
id|i
)braket
op_rshift
l_int|1
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
id|ABS_HAT0Y
comma
(paren
(paren
id|data
(braket
id|j
)braket
(braket
id|i
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|1
)paren
op_minus
(paren
id|data
(braket
id|j
)braket
(braket
id|i
)braket
op_amp
l_int|1
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|TMDC_MODE_AT
suffix:colon
id|i
op_assign
id|tmdc_byte_a
(braket
l_int|3
)braket
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0X
comma
id|tmdc_hat_to_axis
(braket
(paren
id|data
(braket
id|j
)braket
(braket
id|i
)braket
op_minus
l_int|141
)paren
op_div
l_int|25
)braket
dot
id|x
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0Y
comma
id|tmdc_hat_to_axis
(braket
(paren
id|data
(braket
id|j
)braket
(braket
id|i
)braket
op_minus
l_int|141
)paren
op_div
l_int|25
)braket
dot
id|y
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_for
c_loop
(paren
id|k
op_assign
id|l
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|4
suffix:semicolon
id|k
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|tmdc-&gt;btnc
(braket
id|j
)braket
(braket
id|k
)braket
suffix:semicolon
id|i
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|tmdc-&gt;btn
(braket
id|j
)braket
(braket
id|i
op_plus
id|l
)braket
comma
(paren
(paren
id|data
(braket
id|j
)braket
(braket
id|tmdc_byte_d
(braket
id|k
)braket
)braket
op_rshift
(paren
id|i
op_plus
id|tmdc-&gt;btno
(braket
id|j
)braket
(braket
id|k
)braket
)paren
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|l
op_add_assign
id|tmdc-&gt;btnc
(braket
id|j
)braket
(braket
id|k
)braket
suffix:semicolon
)brace
)brace
id|tmdc-&gt;bads
op_add_assign
id|bad
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|tmdc-&gt;timer
comma
id|jiffies
op_plus
id|TMDC_REFRESH_TIME
)paren
suffix:semicolon
)brace
DECL|function|tmdc_open
r_static
r_int
id|tmdc_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|tmdc
op_star
id|tmdc
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmdc-&gt;used
op_increment
)paren
id|mod_timer
c_func
(paren
op_amp
id|tmdc-&gt;timer
comma
id|jiffies
op_plus
id|TMDC_REFRESH_TIME
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tmdc_close
r_static
r_void
id|tmdc_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|tmdc
op_star
id|tmdc
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
id|tmdc-&gt;used
)paren
id|del_timer
c_func
(paren
op_amp
id|tmdc-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * tmdc_probe() probes for ThrustMaster type joysticks.&n; */
DECL|function|tmdc_connect
r_static
r_void
id|tmdc_connect
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
id|models
(brace
r_int
r_char
id|id
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_char
id|abs
suffix:semicolon
r_char
id|hats
suffix:semicolon
r_char
id|btnc
(braket
l_int|4
)braket
suffix:semicolon
r_char
id|btno
(braket
l_int|4
)braket
suffix:semicolon
r_int
r_char
op_star
id|axes
suffix:semicolon
r_int
op_star
id|buttons
suffix:semicolon
)brace
id|models
(braket
)braket
op_assign
(brace
(brace
l_int|1
comma
l_string|&quot;ThrustMaster Millenium 3D Inceptor&quot;
comma
l_int|6
comma
l_int|2
comma
(brace
l_int|4
comma
l_int|2
)brace
comma
(brace
l_int|4
comma
l_int|6
)brace
comma
id|tmdc_abs
comma
id|tmdc_btn_joy
)brace
comma
(brace
l_int|3
comma
l_string|&quot;ThrustMaster Rage 3D Gamepad&quot;
comma
l_int|2
comma
l_int|0
comma
(brace
l_int|8
comma
l_int|2
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
id|tmdc_abs
comma
id|tmdc_btn_pad
)brace
comma
(brace
l_int|4
comma
l_string|&quot;ThrustMaster Attack Throttle&quot;
comma
l_int|5
comma
l_int|2
comma
(brace
l_int|4
comma
l_int|6
)brace
comma
(brace
l_int|4
comma
l_int|2
)brace
comma
id|tmdc_abs_at
comma
id|tmdc_btn_at
)brace
comma
(brace
l_int|8
comma
l_string|&quot;ThrustMaster FragMaster&quot;
comma
l_int|4
comma
l_int|0
comma
(brace
l_int|8
comma
l_int|2
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
id|tmdc_abs_fm
comma
id|tmdc_btn_fm
)brace
comma
(brace
l_int|163
comma
l_string|&quot;Thrustmaster Fusion GamePad&quot;
comma
l_int|2
comma
l_int|0
comma
(brace
l_int|8
comma
l_int|2
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
id|tmdc_abs
comma
id|tmdc_btn_pad
)brace
comma
(brace
l_int|0
comma
l_string|&quot;Unknown %d-axis, %d-button TM device %d&quot;
comma
l_int|0
comma
l_int|0
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
comma
id|tmdc_abs
comma
id|tmdc_btn_joy
)brace
)brace
suffix:semicolon
r_int
r_char
id|data
(braket
l_int|2
)braket
(braket
id|TMDC_MAX_LENGTH
)braket
suffix:semicolon
r_struct
id|tmdc
op_star
id|tmdc
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|k
comma
id|l
comma
id|m
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmdc
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|tmdc
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
id|tmdc
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tmdc
)paren
)paren
suffix:semicolon
id|gameport
op_member_access_from_pointer
r_private
op_assign
id|tmdc
suffix:semicolon
id|tmdc-&gt;gameport
op_assign
id|gameport
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|tmdc-&gt;timer
)paren
suffix:semicolon
id|tmdc-&gt;timer.data
op_assign
(paren
r_int
)paren
id|tmdc
suffix:semicolon
id|tmdc-&gt;timer.function
op_assign
id|tmdc_timer
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
r_if
c_cond
(paren
op_logical_neg
(paren
id|tmdc-&gt;exists
op_assign
id|tmdc_read_packet
c_func
(paren
id|gameport
comma
id|data
)paren
)paren
)paren
r_goto
id|fail2
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
l_int|2
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|tmdc-&gt;exists
op_amp
(paren
l_int|1
op_lshift
id|j
)paren
)paren
(brace
id|tmdc-&gt;mode
(braket
id|j
)braket
op_assign
id|data
(braket
id|j
)braket
(braket
id|TMDC_BYTE_ID
)braket
suffix:semicolon
r_for
c_loop
(paren
id|m
op_assign
l_int|0
suffix:semicolon
id|models
(braket
id|m
)braket
dot
id|id
op_logical_and
id|models
(braket
id|m
)braket
dot
id|id
op_ne
id|tmdc-&gt;mode
(braket
id|j
)braket
suffix:semicolon
id|m
op_increment
)paren
suffix:semicolon
id|tmdc-&gt;abs
(braket
id|j
)braket
op_assign
id|models
(braket
id|m
)braket
dot
id|axes
suffix:semicolon
id|tmdc-&gt;btn
(braket
id|j
)braket
op_assign
id|models
(braket
id|m
)braket
dot
id|buttons
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|models
(braket
id|m
)braket
dot
id|id
)paren
(brace
id|models
(braket
id|m
)braket
dot
id|abs
op_assign
id|data
(braket
id|j
)braket
(braket
id|TMDC_BYTE_DEF
)braket
op_rshift
l_int|4
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|4
suffix:semicolon
id|k
op_increment
)paren
id|models
(braket
id|m
)braket
dot
id|btnc
(braket
id|k
)braket
op_assign
id|k
OL
(paren
id|data
(braket
id|j
)braket
(braket
id|TMDC_BYTE_DEF
)braket
op_amp
l_int|0xf
)paren
ques
c_cond
l_int|8
suffix:colon
l_int|0
suffix:semicolon
)brace
id|tmdc-&gt;absc
(braket
id|j
)braket
op_assign
id|models
(braket
id|m
)braket
dot
id|abs
suffix:semicolon
r_for
c_loop
(paren
id|k
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|4
suffix:semicolon
id|k
op_increment
)paren
(brace
id|tmdc-&gt;btnc
(braket
id|j
)braket
(braket
id|k
)braket
op_assign
id|models
(braket
id|m
)braket
dot
id|btnc
(braket
id|k
)braket
suffix:semicolon
id|tmdc-&gt;btno
(braket
id|j
)braket
(braket
id|k
)braket
op_assign
id|models
(braket
id|m
)braket
dot
id|btno
(braket
id|k
)braket
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|tmdc-&gt;name
(braket
id|j
)braket
comma
id|models
(braket
id|m
)braket
dot
id|name
comma
id|models
(braket
id|m
)braket
dot
id|abs
comma
(paren
id|data
(braket
id|j
)braket
(braket
id|TMDC_BYTE_DEF
)braket
op_amp
l_int|0xf
)paren
op_lshift
l_int|3
comma
id|tmdc-&gt;mode
(braket
id|j
)braket
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|tmdc-&gt;phys
(braket
id|j
)braket
comma
l_string|&quot;%s/input%d&quot;
comma
id|gameport-&gt;phys
comma
id|j
)paren
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
r_private
op_assign
id|tmdc
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|open
op_assign
id|tmdc_open
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|close
op_assign
id|tmdc_close
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|name
op_assign
id|tmdc-&gt;name
(braket
id|j
)braket
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|phys
op_assign
id|tmdc-&gt;phys
(braket
id|j
)braket
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|id.bustype
op_assign
id|BUS_GAMEPORT
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|id.vendor
op_assign
id|GAMEPORT_ID_VENDOR_THRUSTMASTER
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|id.product
op_assign
id|models
(braket
id|m
)braket
dot
id|id
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|id.version
op_assign
l_int|0x0100
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
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
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|models
(braket
id|m
)braket
dot
id|abs
op_logical_and
id|i
OL
id|TMDC_ABS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|tmdc-&gt;abs
(braket
id|i
)braket
OL
l_int|0
)paren
r_continue
suffix:semicolon
id|set_bit
c_func
(paren
id|tmdc-&gt;abs
(braket
id|j
)braket
(braket
id|i
)braket
comma
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|absbit
)paren
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|absmin
(braket
id|tmdc-&gt;abs
(braket
id|j
)braket
(braket
id|i
)braket
)braket
op_assign
l_int|8
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|absmax
(braket
id|tmdc-&gt;abs
(braket
id|j
)braket
(braket
id|i
)braket
)braket
op_assign
l_int|248
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|absfuzz
(braket
id|tmdc-&gt;abs
(braket
id|j
)braket
(braket
id|i
)braket
)braket
op_assign
l_int|2
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|absflat
(braket
id|tmdc-&gt;abs
(braket
id|j
)braket
(braket
id|i
)braket
)braket
op_assign
l_int|4
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|models
(braket
id|m
)braket
dot
id|hats
op_logical_and
id|i
OL
id|TMDC_ABS_HAT
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set_bit
c_func
(paren
id|tmdc_abs_hat
(braket
id|i
)braket
comma
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|absbit
)paren
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|absmin
(braket
id|tmdc_abs_hat
(braket
id|i
)braket
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|absmax
(braket
id|tmdc_abs_hat
(braket
id|i
)braket
)braket
op_assign
l_int|1
suffix:semicolon
)brace
r_for
c_loop
(paren
id|k
op_assign
id|l
op_assign
l_int|0
suffix:semicolon
id|k
OL
l_int|4
suffix:semicolon
id|k
op_increment
)paren
(brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|models
(braket
id|m
)braket
dot
id|btnc
(braket
id|k
)braket
op_logical_and
id|i
OL
id|TMDC_BTN
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|tmdc-&gt;btn
(braket
id|j
)braket
(braket
id|i
op_plus
id|l
)braket
comma
id|tmdc-&gt;dev
(braket
id|j
)braket
dot
id|keybit
)paren
suffix:semicolon
id|l
op_add_assign
id|models
(braket
id|m
)braket
dot
id|btnc
(braket
id|k
)braket
suffix:semicolon
)brace
id|input_register_device
c_func
(paren
id|tmdc-&gt;dev
op_plus
id|j
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|tmdc-&gt;name
(braket
id|j
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
id|tmdc
)paren
suffix:semicolon
)brace
DECL|function|tmdc_disconnect
r_static
r_void
id|tmdc_disconnect
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_struct
id|tmdc
op_star
id|tmdc
op_assign
id|gameport
op_member_access_from_pointer
r_private
suffix:semicolon
r_int
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|tmdc-&gt;exists
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
id|input_unregister_device
c_func
(paren
id|tmdc-&gt;dev
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
id|tmdc
)paren
suffix:semicolon
)brace
DECL|variable|tmdc_dev
r_static
r_struct
id|gameport_dev
id|tmdc_dev
op_assign
(brace
id|connect
suffix:colon
id|tmdc_connect
comma
id|disconnect
suffix:colon
id|tmdc_disconnect
comma
)brace
suffix:semicolon
DECL|function|tmdc_init
r_int
id|__init
id|tmdc_init
c_func
(paren
r_void
)paren
(brace
id|gameport_register_device
c_func
(paren
op_amp
id|tmdc_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tmdc_exit
r_void
id|__exit
id|tmdc_exit
c_func
(paren
r_void
)paren
(brace
id|gameport_unregister_device
c_func
(paren
op_amp
id|tmdc_dev
)paren
suffix:semicolon
)brace
DECL|variable|tmdc_init
id|module_init
c_func
(paren
id|tmdc_init
)paren
suffix:semicolon
DECL|variable|tmdc_exit
id|module_exit
c_func
(paren
id|tmdc_exit
)paren
suffix:semicolon
eof
