multiline_comment|/*&n; * $Id: a3d.c,v 1.14 2001/04/26 10:24:46 vojtech Exp $&n; *&n; *  Copyright (c) 1998-2001 Vojtech Pavlik&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * FP-Gaming Assasin 3D joystick driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
macro_line|#include &lt;linux/input.h&gt;
DECL|macro|A3D_MAX_START
mdefine_line|#define A3D_MAX_START&t;&t;400&t;/* 400 us */ 
DECL|macro|A3D_MAX_STROBE
mdefine_line|#define A3D_MAX_STROBE&t;&t;60&t;/* 40 us */ 
DECL|macro|A3D_DELAY_READ
mdefine_line|#define A3D_DELAY_READ&t;&t;3&t;/* 3 ms */
DECL|macro|A3D_MAX_LENGTH
mdefine_line|#define A3D_MAX_LENGTH&t;&t;40&t;/* 40*3 bits */
DECL|macro|A3D_REFRESH_TIME
mdefine_line|#define A3D_REFRESH_TIME&t;HZ/50&t;/* 20 ms */
DECL|macro|A3D_MODE_A3D
mdefine_line|#define A3D_MODE_A3D&t;&t;1&t;/* Assassin 3D */
DECL|macro|A3D_MODE_PAN
mdefine_line|#define A3D_MODE_PAN&t;&t;2&t;/* Panther */
DECL|macro|A3D_MODE_OEM
mdefine_line|#define A3D_MODE_OEM&t;&t;3&t;/* Panther OEM version */
DECL|macro|A3D_MODE_PXL
mdefine_line|#define A3D_MODE_PXL&t;&t;4&t;/* Panther XL */
DECL|variable|a3d_names
r_char
op_star
id|a3d_names
(braket
)braket
op_assign
(brace
l_int|NULL
comma
l_string|&quot;FP-Gaming Assassin 3D&quot;
comma
l_string|&quot;MadCatz Panther&quot;
comma
l_string|&quot;OEM Panther&quot;
comma
l_string|&quot;MadCatz Panther XL&quot;
comma
l_string|&quot;MadCatz Panther XL w/ rudder&quot;
)brace
suffix:semicolon
DECL|struct|a3d
r_struct
id|a3d
(brace
DECL|member|gameport
r_struct
id|gameport
op_star
id|gameport
suffix:semicolon
DECL|member|adc
r_struct
id|gameport
id|adc
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|timer
r_struct
id|timer_list
id|timer
suffix:semicolon
DECL|member|axes
r_int
id|axes
(braket
l_int|4
)braket
suffix:semicolon
DECL|member|buttons
r_int
id|buttons
suffix:semicolon
DECL|member|mode
r_int
id|mode
suffix:semicolon
DECL|member|length
r_int
id|length
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
)brace
suffix:semicolon
multiline_comment|/*&n; * a3d_read_packet() reads an Assassin 3D packet.&n; */
DECL|function|a3d_read_packet
r_static
r_int
id|a3d_read_packet
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
id|length
comma
r_char
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
comma
id|s
suffix:semicolon
r_int
id|i
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
id|t
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|A3D_MAX_START
)paren
suffix:semicolon
id|s
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|A3D_MAX_STROBE
)paren
suffix:semicolon
id|__save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|__cli
c_func
(paren
)paren
suffix:semicolon
id|gameport_trigger
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|v
op_assign
id|gameport_read
c_func
(paren
id|gameport
)paren
suffix:semicolon
r_while
c_loop
(paren
id|t
OG
l_int|0
op_logical_and
id|i
OL
id|length
)paren
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
id|gameport_read
c_func
(paren
id|gameport
)paren
suffix:semicolon
r_if
c_cond
(paren
op_complement
id|v
op_amp
id|u
op_amp
l_int|0x10
)paren
(brace
id|data
(braket
id|i
op_increment
)braket
op_assign
id|v
op_rshift
l_int|5
suffix:semicolon
id|t
op_assign
id|s
suffix:semicolon
)brace
)brace
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * a3d_csum() computes checksum of triplet packet&n; */
DECL|function|a3d_csum
r_static
r_int
id|a3d_csum
c_func
(paren
r_char
op_star
id|data
comma
r_int
id|count
)paren
(brace
r_int
id|i
comma
id|csum
op_assign
l_int|0
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
id|count
op_minus
l_int|2
suffix:semicolon
id|i
op_increment
)paren
id|csum
op_add_assign
id|data
(braket
id|i
)braket
suffix:semicolon
r_return
(paren
id|csum
op_amp
l_int|0x3f
)paren
op_ne
(paren
(paren
id|data
(braket
id|count
op_minus
l_int|2
)braket
op_lshift
l_int|3
)paren
op_or
id|data
(braket
id|count
op_minus
l_int|1
)braket
)paren
suffix:semicolon
)brace
DECL|function|a3d_read
r_static
r_void
id|a3d_read
c_func
(paren
r_struct
id|a3d
op_star
id|a3d
comma
r_int
r_char
op_star
id|data
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|a3d-&gt;dev
suffix:semicolon
r_switch
c_cond
(paren
id|a3d-&gt;mode
)paren
(brace
r_case
id|A3D_MODE_A3D
suffix:colon
r_case
id|A3D_MODE_OEM
suffix:colon
r_case
id|A3D_MODE_PAN
suffix:colon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_X
comma
(paren
(paren
id|data
(braket
l_int|5
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|6
)braket
op_lshift
l_int|3
)paren
op_or
id|data
(braket
l_int|7
)braket
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|5
)braket
op_amp
l_int|4
)paren
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_Y
comma
(paren
(paren
id|data
(braket
l_int|8
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|9
)braket
op_lshift
l_int|3
)paren
op_or
id|data
(braket
l_int|10
)braket
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|8
)braket
op_amp
l_int|4
)paren
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|data
(braket
l_int|2
)braket
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
id|data
(braket
l_int|3
)braket
op_amp
l_int|2
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|data
(braket
l_int|3
)braket
op_amp
l_int|4
)paren
suffix:semicolon
id|a3d-&gt;axes
(braket
l_int|0
)braket
op_assign
(paren
(paren
r_int
r_char
)paren
(paren
(paren
id|data
(braket
l_int|11
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|12
)braket
op_lshift
l_int|3
)paren
op_or
(paren
id|data
(braket
l_int|13
)braket
)paren
)paren
)paren
op_plus
l_int|128
suffix:semicolon
id|a3d-&gt;axes
(braket
l_int|1
)braket
op_assign
(paren
(paren
r_int
r_char
)paren
(paren
(paren
id|data
(braket
l_int|14
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|15
)braket
op_lshift
l_int|3
)paren
op_or
(paren
id|data
(braket
l_int|16
)braket
)paren
)paren
)paren
op_plus
l_int|128
suffix:semicolon
id|a3d-&gt;axes
(braket
l_int|2
)braket
op_assign
(paren
(paren
r_int
r_char
)paren
(paren
(paren
id|data
(braket
l_int|17
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|18
)braket
op_lshift
l_int|3
)paren
op_or
(paren
id|data
(braket
l_int|19
)braket
)paren
)paren
)paren
op_plus
l_int|128
suffix:semicolon
id|a3d-&gt;axes
(braket
l_int|3
)braket
op_assign
(paren
(paren
r_int
r_char
)paren
(paren
(paren
id|data
(braket
l_int|20
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|21
)braket
op_lshift
l_int|3
)paren
op_or
(paren
id|data
(braket
l_int|22
)braket
)paren
)paren
)paren
op_plus
l_int|128
suffix:semicolon
id|a3d-&gt;buttons
op_assign
(paren
(paren
id|data
(braket
l_int|3
)braket
op_lshift
l_int|3
)paren
op_or
id|data
(braket
l_int|4
)braket
)paren
op_amp
l_int|0xf
suffix:semicolon
r_return
suffix:semicolon
r_case
id|A3D_MODE_PXL
suffix:colon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_X
comma
(paren
(paren
id|data
(braket
l_int|9
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|10
)braket
op_lshift
l_int|3
)paren
op_or
id|data
(braket
l_int|11
)braket
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|9
)braket
op_amp
l_int|4
)paren
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_Y
comma
(paren
(paren
id|data
(braket
l_int|12
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|13
)braket
op_lshift
l_int|3
)paren
op_or
id|data
(braket
l_int|14
)braket
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|12
)braket
op_amp
l_int|4
)paren
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_RIGHT
comma
id|data
(braket
l_int|2
)braket
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
id|data
(braket
l_int|3
)braket
op_amp
l_int|2
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
id|data
(braket
l_int|3
)braket
op_amp
l_int|4
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_SIDE
comma
id|data
(braket
l_int|7
)braket
op_amp
l_int|2
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_EXTRA
comma
id|data
(braket
l_int|7
)braket
op_amp
l_int|4
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
(paren
(paren
r_int
r_char
)paren
(paren
(paren
id|data
(braket
l_int|15
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|16
)braket
op_lshift
l_int|3
)paren
op_or
(paren
id|data
(braket
l_int|17
)braket
)paren
)paren
)paren
op_plus
l_int|128
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
r_int
r_char
)paren
(paren
(paren
id|data
(braket
l_int|18
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|19
)braket
op_lshift
l_int|3
)paren
op_or
(paren
id|data
(braket
l_int|20
)braket
)paren
)paren
)paren
op_plus
l_int|128
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_RUDDER
comma
(paren
(paren
r_int
r_char
)paren
(paren
(paren
id|data
(braket
l_int|21
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|22
)braket
op_lshift
l_int|3
)paren
op_or
(paren
id|data
(braket
l_int|23
)braket
)paren
)paren
)paren
op_plus
l_int|128
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
(paren
r_int
r_char
)paren
(paren
(paren
id|data
(braket
l_int|24
)braket
op_lshift
l_int|6
)paren
op_or
(paren
id|data
(braket
l_int|25
)braket
op_lshift
l_int|3
)paren
op_or
(paren
id|data
(braket
l_int|26
)braket
)paren
)paren
)paren
op_plus
l_int|128
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
id|data
(braket
l_int|5
)braket
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|5
)braket
op_rshift
l_int|2
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
l_int|5
)braket
op_rshift
l_int|1
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|6
)braket
op_rshift
l_int|2
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
l_int|4
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
l_int|3
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
id|ABS_HAT1Y
comma
(paren
(paren
id|data
(braket
l_int|4
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
l_int|4
)braket
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TRIGGER
comma
id|data
(braket
l_int|8
)braket
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_THUMB
comma
id|data
(braket
l_int|8
)braket
op_amp
l_int|2
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TOP
comma
id|data
(braket
l_int|8
)braket
op_amp
l_int|4
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_PINKIE
comma
id|data
(braket
l_int|7
)braket
op_amp
l_int|1
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * a3d_timer() reads and analyzes A3D joystick data.&n; */
DECL|function|a3d_timer
r_static
r_void
id|a3d_timer
c_func
(paren
r_int
r_int
r_private
)paren
(brace
r_struct
id|a3d
op_star
id|a3d
op_assign
(paren
r_void
op_star
)paren
r_private
suffix:semicolon
r_int
r_char
id|data
(braket
id|A3D_MAX_LENGTH
)braket
suffix:semicolon
id|a3d-&gt;reads
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|a3d_read_packet
c_func
(paren
id|a3d-&gt;gameport
comma
id|a3d-&gt;length
comma
id|data
)paren
op_ne
id|a3d-&gt;length
op_logical_or
id|data
(braket
l_int|0
)braket
op_ne
id|a3d-&gt;mode
op_logical_or
id|a3d_csum
c_func
(paren
id|data
comma
id|a3d-&gt;length
)paren
)paren
id|a3d-&gt;bads
op_increment
suffix:semicolon
r_else
id|a3d_read
c_func
(paren
id|a3d
comma
id|data
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|a3d-&gt;timer
comma
id|jiffies
op_plus
id|A3D_REFRESH_TIME
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * a3d_adc_cooked_read() copies the acis and button data to the&n; * callers arrays. It could do the read itself, but the caller could&n; * call this more than 50 times a second, which would use too much CPU.&n; */
DECL|function|a3d_adc_cooked_read
r_int
id|a3d_adc_cooked_read
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
op_star
id|axes
comma
r_int
op_star
id|buttons
)paren
(brace
r_struct
id|a3d
op_star
id|a3d
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|axes
(braket
id|i
)braket
op_assign
(paren
id|a3d-&gt;axes
(braket
id|i
)braket
OL
l_int|254
)paren
ques
c_cond
id|a3d-&gt;axes
(braket
id|i
)braket
suffix:colon
op_minus
l_int|1
suffix:semicolon
op_star
id|buttons
op_assign
id|a3d-&gt;buttons
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * a3d_adc_open() is the gameport open routine. It refuses to serve&n; * any but cooked data.&n; */
DECL|function|a3d_adc_open
r_int
id|a3d_adc_open
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
id|mode
)paren
(brace
r_struct
id|a3d
op_star
id|a3d
op_assign
id|gameport
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|mode
op_ne
id|GAMEPORT_MODE_COOKED
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a3d-&gt;used
op_increment
)paren
id|mod_timer
c_func
(paren
op_amp
id|a3d-&gt;timer
comma
id|jiffies
op_plus
id|A3D_REFRESH_TIME
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * a3d_adc_close() is a callback from the input close routine.&n; */
DECL|function|a3d_adc_close
r_static
r_void
id|a3d_adc_close
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_struct
id|a3d
op_star
id|a3d
op_assign
id|gameport
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
op_decrement
id|a3d-&gt;used
)paren
id|del_timer
c_func
(paren
op_amp
id|a3d-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * a3d_open() is a callback from the input open routine.&n; */
DECL|function|a3d_open
r_static
r_int
id|a3d_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|a3d
op_star
id|a3d
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a3d-&gt;used
op_increment
)paren
id|mod_timer
c_func
(paren
op_amp
id|a3d-&gt;timer
comma
id|jiffies
op_plus
id|A3D_REFRESH_TIME
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * a3d_close() is a callback from the input close routine.&n; */
DECL|function|a3d_close
r_static
r_void
id|a3d_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|a3d
op_star
id|a3d
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
id|a3d-&gt;used
)paren
id|del_timer
c_func
(paren
op_amp
id|a3d-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * a3d_connect() probes for A3D joysticks.&n; */
DECL|function|a3d_connect
r_static
r_void
id|a3d_connect
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
id|a3d
op_star
id|a3d
suffix:semicolon
r_int
r_char
id|data
(braket
id|A3D_MAX_LENGTH
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|a3d
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|a3d
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
id|a3d
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|a3d
)paren
)paren
suffix:semicolon
id|gameport
op_member_access_from_pointer
r_private
op_assign
id|a3d
suffix:semicolon
id|a3d-&gt;gameport
op_assign
id|gameport
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|a3d-&gt;timer
)paren
suffix:semicolon
id|a3d-&gt;timer.data
op_assign
(paren
r_int
)paren
id|a3d
suffix:semicolon
id|a3d-&gt;timer.function
op_assign
id|a3d_timer
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
id|i
op_assign
id|a3d_read_packet
c_func
(paren
id|gameport
comma
id|A3D_MAX_LENGTH
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
op_logical_or
id|a3d_csum
c_func
(paren
id|data
comma
id|i
)paren
)paren
r_goto
id|fail2
suffix:semicolon
id|a3d-&gt;mode
op_assign
id|data
(braket
l_int|0
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|a3d-&gt;mode
op_logical_or
id|a3d-&gt;mode
OG
l_int|5
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;a3d.c: Unknown A3D device detected &quot;
l_string|&quot;(gameport%d, id=%d), contact &lt;vojtech@suse.cz&gt;&bslash;n&quot;
comma
id|gameport-&gt;number
comma
id|a3d-&gt;mode
)paren
suffix:semicolon
r_goto
id|fail2
suffix:semicolon
)brace
r_if
c_cond
(paren
id|a3d-&gt;mode
op_eq
id|A3D_MODE_PXL
)paren
(brace
r_int
id|axes
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
id|ABS_RUDDER
)brace
suffix:semicolon
id|a3d-&gt;length
op_assign
l_int|33
suffix:semicolon
id|a3d-&gt;dev.evbit
(braket
l_int|0
)braket
op_or_assign
id|BIT
c_func
(paren
id|EV_ABS
)paren
op_or
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
id|a3d-&gt;dev.relbit
(braket
l_int|0
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
id|a3d-&gt;dev.absbit
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
id|ABS_THROTTLE
)paren
op_or
id|BIT
c_func
(paren
id|ABS_RUDDER
)paren
op_or
id|BIT
c_func
(paren
id|ABS_HAT0X
)paren
op_or
id|BIT
c_func
(paren
id|ABS_HAT0Y
)paren
op_or
id|BIT
c_func
(paren
id|ABS_HAT1X
)paren
op_or
id|BIT
c_func
(paren
id|ABS_HAT1Y
)paren
suffix:semicolon
id|a3d-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_MOUSE
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
op_or
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
id|BTN_SIDE
)paren
op_or
id|BIT
c_func
(paren
id|BTN_EXTRA
)paren
suffix:semicolon
id|a3d-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_JOYSTICK
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_TRIGGER
)paren
op_or
id|BIT
c_func
(paren
id|BTN_THUMB
)paren
op_or
id|BIT
c_func
(paren
id|BTN_TOP
)paren
op_or
id|BIT
c_func
(paren
id|BTN_PINKIE
)paren
suffix:semicolon
id|a3d_read
c_func
(paren
id|a3d
comma
id|data
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|i
OL
l_int|2
)paren
(brace
id|a3d-&gt;dev.absmin
(braket
id|axes
(braket
id|i
)braket
)braket
op_assign
l_int|48
suffix:semicolon
id|a3d-&gt;dev.absmax
(braket
id|axes
(braket
id|i
)braket
)braket
op_assign
id|a3d-&gt;dev.abs
(braket
id|axes
(braket
id|i
)braket
)braket
op_star
l_int|2
op_minus
l_int|48
suffix:semicolon
id|a3d-&gt;dev.absflat
(braket
id|axes
(braket
id|i
)braket
)braket
op_assign
l_int|8
suffix:semicolon
)brace
r_else
(brace
id|a3d-&gt;dev.absmin
(braket
id|axes
(braket
id|i
)braket
)braket
op_assign
l_int|2
suffix:semicolon
id|a3d-&gt;dev.absmax
(braket
id|axes
(braket
id|i
)braket
)braket
op_assign
l_int|253
suffix:semicolon
)brace
id|a3d-&gt;dev.absmin
(braket
id|ABS_HAT0X
op_plus
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|a3d-&gt;dev.absmax
(braket
id|ABS_HAT0X
op_plus
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_else
(brace
id|a3d-&gt;length
op_assign
l_int|29
suffix:semicolon
id|a3d-&gt;dev.evbit
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
id|EV_REL
)paren
suffix:semicolon
id|a3d-&gt;dev.relbit
(braket
l_int|0
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
id|a3d-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_MOUSE
)paren
)braket
op_or_assign
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
op_or
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
suffix:semicolon
id|a3d-&gt;adc
dot
r_private
op_assign
id|a3d
suffix:semicolon
id|a3d-&gt;adc.open
op_assign
id|a3d_adc_open
suffix:semicolon
id|a3d-&gt;adc.close
op_assign
id|a3d_adc_close
suffix:semicolon
id|a3d-&gt;adc.cooked_read
op_assign
id|a3d_adc_cooked_read
suffix:semicolon
id|a3d-&gt;adc.fuzz
op_assign
l_int|1
suffix:semicolon
id|a3d_read
c_func
(paren
id|a3d
comma
id|data
)paren
suffix:semicolon
id|gameport_register_port
c_func
(paren
op_amp
id|a3d-&gt;adc
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;gameport%d: %s on gameport%d.0&bslash;n&quot;
comma
id|a3d-&gt;adc.number
comma
id|a3d_names
(braket
id|a3d-&gt;mode
)braket
comma
id|gameport-&gt;number
)paren
suffix:semicolon
)brace
id|a3d-&gt;dev
dot
r_private
op_assign
id|a3d
suffix:semicolon
id|a3d-&gt;dev.open
op_assign
id|a3d_open
suffix:semicolon
id|a3d-&gt;dev.close
op_assign
id|a3d_close
suffix:semicolon
id|a3d-&gt;dev.name
op_assign
id|a3d_names
(braket
id|a3d-&gt;mode
)braket
suffix:semicolon
id|a3d-&gt;dev.idbus
op_assign
id|BUS_GAMEPORT
suffix:semicolon
id|a3d-&gt;dev.idvendor
op_assign
id|GAMEPORT_ID_VENDOR_MADCATZ
suffix:semicolon
id|a3d-&gt;dev.idproduct
op_assign
id|a3d-&gt;mode
suffix:semicolon
id|a3d-&gt;dev.idversion
op_assign
l_int|0x0100
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|a3d-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input%d: %s on gameport%d.0&bslash;n&quot;
comma
id|a3d-&gt;dev.number
comma
id|a3d_names
(braket
id|a3d-&gt;mode
)braket
comma
id|gameport-&gt;number
)paren
suffix:semicolon
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
id|a3d
)paren
suffix:semicolon
)brace
DECL|function|a3d_disconnect
r_static
r_void
id|a3d_disconnect
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_struct
id|a3d
op_star
id|a3d
op_assign
id|gameport
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|a3d-&gt;dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|a3d-&gt;mode
OL
id|A3D_MODE_PXL
)paren
id|gameport_unregister_port
c_func
(paren
op_amp
id|a3d-&gt;adc
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
id|a3d
)paren
suffix:semicolon
)brace
DECL|variable|a3d_dev
r_static
r_struct
id|gameport_dev
id|a3d_dev
op_assign
(brace
id|connect
suffix:colon
id|a3d_connect
comma
id|disconnect
suffix:colon
id|a3d_disconnect
comma
)brace
suffix:semicolon
DECL|function|a3d_init
r_int
id|__init
id|a3d_init
c_func
(paren
r_void
)paren
(brace
id|gameport_register_device
c_func
(paren
op_amp
id|a3d_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|a3d_exit
r_void
id|__exit
id|a3d_exit
c_func
(paren
r_void
)paren
(brace
id|gameport_unregister_device
c_func
(paren
op_amp
id|a3d_dev
)paren
suffix:semicolon
)brace
DECL|variable|a3d_init
id|module_init
c_func
(paren
id|a3d_init
)paren
suffix:semicolon
DECL|variable|a3d_exit
id|module_exit
c_func
(paren
id|a3d_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
