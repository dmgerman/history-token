multiline_comment|/*&n; * $Id: gf2k.c,v 1.19 2002/01/22 20:27:43 vojtech Exp $&n; *&n; *  Copyright (c) 1998-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * Genius Flight 2000 joystick driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Genius Flight 2000 joystick driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|GF2K_START
mdefine_line|#define GF2K_START&t;&t;400&t;/* The time we wait for the first bit [400 us] */
DECL|macro|GF2K_STROBE
mdefine_line|#define GF2K_STROBE&t;&t;40&t;/* The time we wait for the first bit [40 us] */
DECL|macro|GF2K_TIMEOUT
mdefine_line|#define GF2K_TIMEOUT&t;&t;4&t;/* Wait for everything to settle [4 ms] */
DECL|macro|GF2K_LENGTH
mdefine_line|#define GF2K_LENGTH&t;&t;80&t;/* Max number of triplets in a packet */
DECL|macro|GF2K_REFRESH
mdefine_line|#define GF2K_REFRESH&t;&t;HZ/50&t;/* Time between joystick polls [20 ms] */
multiline_comment|/*&n; * Genius joystick ids ...&n; */
DECL|macro|GF2K_ID_G09
mdefine_line|#define GF2K_ID_G09&t;&t;1
DECL|macro|GF2K_ID_F30D
mdefine_line|#define GF2K_ID_F30D&t;&t;2
DECL|macro|GF2K_ID_F30
mdefine_line|#define GF2K_ID_F30&t;&t;3
DECL|macro|GF2K_ID_F31D
mdefine_line|#define GF2K_ID_F31D&t;&t;4
DECL|macro|GF2K_ID_F305
mdefine_line|#define GF2K_ID_F305&t;&t;5
DECL|macro|GF2K_ID_F23P
mdefine_line|#define GF2K_ID_F23P&t;&t;6
DECL|macro|GF2K_ID_F31
mdefine_line|#define GF2K_ID_F31&t;&t;7
DECL|macro|GF2K_ID_MAX
mdefine_line|#define GF2K_ID_MAX&t;&t;7
DECL|variable|gf2k_length
r_static
r_char
id|gf2k_length
(braket
)braket
op_assign
(brace
l_int|40
comma
l_int|40
comma
l_int|40
comma
l_int|40
comma
l_int|40
comma
l_int|40
comma
l_int|40
comma
l_int|40
)brace
suffix:semicolon
DECL|variable|gf2k_hat_to_axis
r_static
r_char
id|gf2k_hat_to_axis
(braket
)braket
(braket
l_int|2
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
DECL|variable|gf2k_names
r_static
r_char
op_star
id|gf2k_names
(braket
)braket
op_assign
(brace
l_string|&quot;&quot;
comma
l_string|&quot;Genius G-09D&quot;
comma
l_string|&quot;Genius F-30D&quot;
comma
l_string|&quot;Genius F-30&quot;
comma
l_string|&quot;Genius MaxFighter F-31D&quot;
comma
l_string|&quot;Genius F-30-5&quot;
comma
l_string|&quot;Genius Flight2000 F-23&quot;
comma
l_string|&quot;Genius F-31&quot;
)brace
suffix:semicolon
DECL|variable|gf2k_hats
r_static
r_int
r_char
id|gf2k_hats
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|2
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|gf2k_axes
r_static
r_int
r_char
id|gf2k_axes
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|2
comma
l_int|0
comma
l_int|0
comma
l_int|4
comma
l_int|0
comma
l_int|4
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|gf2k_joys
r_static
r_int
r_char
id|gf2k_joys
(braket
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
l_int|10
comma
l_int|0
comma
l_int|8
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|gf2k_pads
r_static
r_int
r_char
id|gf2k_pads
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|6
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|gf2k_lens
r_static
r_int
r_char
id|gf2k_lens
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|18
comma
l_int|0
comma
l_int|0
comma
l_int|18
comma
l_int|0
comma
l_int|18
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|gf2k_abs
r_static
r_int
r_char
id|gf2k_abs
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
comma
id|ABS_GAS
comma
id|ABS_BRAKE
)brace
suffix:semicolon
DECL|variable|gf2k_btn_joy
r_static
r_int
id|gf2k_btn_joy
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
)brace
suffix:semicolon
DECL|variable|gf2k_btn_pad
r_static
r_int
id|gf2k_btn_pad
(braket
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
id|BTN_TL
comma
id|BTN_TR
comma
id|BTN_TL2
comma
id|BTN_TR2
comma
id|BTN_START
comma
id|BTN_SELECT
)brace
suffix:semicolon
DECL|variable|gf2k_seq_reset
r_static
r_int
id|gf2k_seq_reset
(braket
)braket
op_assign
(brace
l_int|240
comma
l_int|340
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|gf2k_seq_digital
r_static
r_int
id|gf2k_seq_digital
(braket
)braket
op_assign
(brace
l_int|590
comma
l_int|320
comma
l_int|860
comma
l_int|0
)brace
suffix:semicolon
DECL|struct|gf2k
r_struct
id|gf2k
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
suffix:semicolon
DECL|member|reads
r_int
id|reads
suffix:semicolon
DECL|member|bads
r_int
id|bads
suffix:semicolon
DECL|member|used
r_int
id|used
suffix:semicolon
DECL|member|id
r_int
r_char
id|id
suffix:semicolon
DECL|member|length
r_int
r_char
id|length
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * gf2k_read_packet() reads a Genius Flight2000 packet.&n; */
DECL|function|gf2k_read_packet
r_static
r_int
id|gf2k_read_packet
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
r_char
id|u
comma
id|v
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|t
comma
id|p
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|t
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|GF2K_START
)paren
suffix:semicolon
id|p
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|GF2K_STROBE
)paren
suffix:semicolon
id|i
op_assign
l_int|0
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
id|v
op_amp
op_complement
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
id|p
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
multiline_comment|/*&n; * gf2k_trigger_seq() initializes a Genius Flight2000 joystick&n; * into digital mode.&n; */
DECL|function|gf2k_trigger_seq
r_static
r_void
id|gf2k_trigger_seq
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
op_star
id|seq
)paren
(brace
r_int
r_int
id|flags
suffix:semicolon
r_int
id|i
comma
id|t
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
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|gameport_trigger
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|t
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|GF2K_TIMEOUT
op_star
l_int|1000
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|gameport_read
c_func
(paren
id|gameport
)paren
op_amp
l_int|1
)paren
op_logical_and
id|t
)paren
id|t
op_decrement
suffix:semicolon
id|udelay
c_func
(paren
id|seq
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|seq
(braket
op_increment
id|i
)braket
)paren
suffix:semicolon
id|gameport_trigger
c_func
(paren
id|gameport
)paren
suffix:semicolon
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * js_sw_get_bits() composes bits from the triplet buffer into a __u64.&n; * Parameter &squot;pos&squot; is bit number inside packet where to start at, &squot;num&squot; is number&n; * of bits to be read, &squot;shift&squot; is offset in the resulting __u64 to start at, bits&n; * is number of bits per triplet.&n; */
DECL|macro|GB
mdefine_line|#define GB(p,n,s)&t;gf2k_get_bits(data, p, n, s)
DECL|function|gf2k_get_bits
r_static
r_int
id|gf2k_get_bits
c_func
(paren
r_int
r_char
op_star
id|buf
comma
r_int
id|pos
comma
r_int
id|num
comma
r_int
id|shift
)paren
(brace
id|__u64
id|data
op_assign
l_int|0
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
id|num
op_div
l_int|3
op_plus
l_int|2
suffix:semicolon
id|i
op_increment
)paren
id|data
op_or_assign
id|buf
(braket
id|pos
op_div
l_int|3
op_plus
id|i
)braket
op_lshift
(paren
id|i
op_star
l_int|3
)paren
suffix:semicolon
id|data
op_rshift_assign
id|pos
op_mod
l_int|3
suffix:semicolon
id|data
op_and_assign
(paren
l_int|1
op_lshift
id|num
)paren
op_minus
l_int|1
suffix:semicolon
id|data
op_lshift_assign
id|shift
suffix:semicolon
r_return
id|data
suffix:semicolon
)brace
DECL|function|gf2k_read
r_static
r_void
id|gf2k_read
c_func
(paren
r_struct
id|gf2k
op_star
id|gf2k
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
id|gf2k-&gt;dev
suffix:semicolon
r_int
id|i
comma
id|t
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
op_logical_and
id|i
OL
id|gf2k_axes
(braket
id|gf2k-&gt;id
)braket
suffix:semicolon
id|i
op_increment
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
id|gf2k_abs
(braket
id|i
)braket
comma
id|GB
c_func
(paren
id|i
op_lshift
l_int|3
comma
l_int|8
comma
l_int|0
)paren
op_or
id|GB
c_func
(paren
id|i
op_plus
l_int|46
comma
l_int|1
comma
l_int|8
)paren
op_or
id|GB
c_func
(paren
id|i
op_plus
l_int|50
comma
l_int|1
comma
l_int|9
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
l_int|2
op_logical_and
id|i
OL
id|gf2k_axes
(braket
id|gf2k-&gt;id
)braket
op_minus
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
id|gf2k_abs
(braket
id|i
)braket
comma
id|GB
c_func
(paren
id|i
op_star
l_int|9
op_plus
l_int|60
comma
l_int|8
comma
l_int|0
)paren
op_or
id|GB
c_func
(paren
id|i
op_plus
l_int|54
comma
l_int|1
comma
l_int|9
)paren
)paren
suffix:semicolon
id|t
op_assign
id|GB
c_func
(paren
l_int|40
comma
l_int|4
comma
l_int|0
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
id|gf2k_hats
(braket
id|gf2k-&gt;id
)braket
suffix:semicolon
id|i
op_increment
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0X
op_plus
id|i
comma
id|gf2k_hat_to_axis
(braket
id|t
)braket
(braket
id|i
)braket
)paren
suffix:semicolon
id|t
op_assign
id|GB
c_func
(paren
l_int|44
comma
l_int|2
comma
l_int|0
)paren
op_or
id|GB
c_func
(paren
l_int|32
comma
l_int|8
comma
l_int|2
)paren
op_or
id|GB
c_func
(paren
l_int|78
comma
l_int|2
comma
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
id|gf2k_joys
(braket
id|gf2k-&gt;id
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
id|gf2k_btn_joy
(braket
id|i
)braket
comma
(paren
id|t
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
l_int|0
suffix:semicolon
id|i
OL
id|gf2k_pads
(braket
id|gf2k-&gt;id
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
id|gf2k_btn_pad
(braket
id|i
)braket
comma
(paren
id|t
op_rshift
id|i
)paren
op_amp
l_int|1
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * gf2k_timer() reads and analyzes Genius joystick data.&n; */
DECL|function|gf2k_timer
r_static
r_void
id|gf2k_timer
c_func
(paren
r_int
r_int
r_private
)paren
(brace
r_struct
id|gf2k
op_star
id|gf2k
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
id|GF2K_LENGTH
)braket
suffix:semicolon
id|gf2k-&gt;reads
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|gf2k_read_packet
c_func
(paren
id|gf2k-&gt;gameport
comma
id|gf2k_length
(braket
id|gf2k-&gt;id
)braket
comma
id|data
)paren
OL
id|gf2k_length
(braket
id|gf2k-&gt;id
)braket
)paren
(brace
id|gf2k-&gt;bads
op_increment
suffix:semicolon
)brace
r_else
id|gf2k_read
c_func
(paren
id|gf2k
comma
id|data
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|gf2k-&gt;timer
comma
id|jiffies
op_plus
id|GF2K_REFRESH
)paren
suffix:semicolon
)brace
DECL|function|gf2k_open
r_static
r_int
id|gf2k_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|gf2k
op_star
id|gf2k
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|gf2k-&gt;used
op_increment
)paren
id|mod_timer
c_func
(paren
op_amp
id|gf2k-&gt;timer
comma
id|jiffies
op_plus
id|GF2K_REFRESH
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gf2k_close
r_static
r_void
id|gf2k_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|gf2k
op_star
id|gf2k
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
id|gf2k-&gt;used
)paren
id|del_timer
c_func
(paren
op_amp
id|gf2k-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * gf2k_connect() probes for Genius id joysticks.&n; */
DECL|function|gf2k_connect
r_static
r_void
id|gf2k_connect
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
id|gf2k
op_star
id|gf2k
suffix:semicolon
r_int
r_char
id|data
(braket
id|GF2K_LENGTH
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
id|gf2k
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|gf2k
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
id|gf2k
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|gf2k
)paren
)paren
suffix:semicolon
id|gameport
op_member_access_from_pointer
r_private
op_assign
id|gf2k
suffix:semicolon
id|gf2k-&gt;gameport
op_assign
id|gameport
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|gf2k-&gt;timer
)paren
suffix:semicolon
id|gf2k-&gt;timer.data
op_assign
(paren
r_int
)paren
id|gf2k
suffix:semicolon
id|gf2k-&gt;timer.function
op_assign
id|gf2k_timer
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
id|gf2k_trigger_seq
c_func
(paren
id|gameport
comma
id|gf2k_seq_reset
)paren
suffix:semicolon
id|wait_ms
c_func
(paren
id|GF2K_TIMEOUT
)paren
suffix:semicolon
id|gf2k_trigger_seq
c_func
(paren
id|gameport
comma
id|gf2k_seq_digital
)paren
suffix:semicolon
id|wait_ms
c_func
(paren
id|GF2K_TIMEOUT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gf2k_read_packet
c_func
(paren
id|gameport
comma
id|GF2K_LENGTH
comma
id|data
)paren
OL
l_int|12
)paren
r_goto
id|fail2
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|gf2k-&gt;id
op_assign
id|GB
c_func
(paren
l_int|7
comma
l_int|2
comma
l_int|0
)paren
op_or
id|GB
c_func
(paren
l_int|3
comma
l_int|3
comma
l_int|2
)paren
op_or
id|GB
c_func
(paren
l_int|0
comma
l_int|3
comma
l_int|5
)paren
)paren
)paren
r_goto
id|fail2
suffix:semicolon
macro_line|#ifdef RESET_WORKS
r_if
c_cond
(paren
(paren
id|gf2k-&gt;id
op_ne
(paren
id|GB
c_func
(paren
l_int|19
comma
l_int|2
comma
l_int|0
)paren
op_or
id|GB
c_func
(paren
l_int|15
comma
l_int|3
comma
l_int|2
)paren
op_or
id|GB
c_func
(paren
l_int|12
comma
l_int|3
comma
l_int|5
)paren
)paren
)paren
op_logical_or
(paren
id|gf2k-&gt;id
op_ne
(paren
id|GB
c_func
(paren
l_int|31
comma
l_int|2
comma
l_int|0
)paren
op_or
id|GB
c_func
(paren
l_int|27
comma
l_int|3
comma
l_int|2
)paren
op_or
id|GB
c_func
(paren
l_int|24
comma
l_int|3
comma
l_int|5
)paren
)paren
)paren
)paren
r_goto
id|fail2
suffix:semicolon
macro_line|#else
id|gf2k-&gt;id
op_assign
l_int|6
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|gf2k-&gt;id
OG
id|GF2K_ID_MAX
op_logical_or
op_logical_neg
id|gf2k_axes
(braket
id|gf2k-&gt;id
)braket
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;gf2k.c: Not yet supported joystick on %s. [id: %d type:%s]&bslash;n&quot;
comma
id|gameport-&gt;phys
comma
id|gf2k-&gt;id
comma
id|gf2k-&gt;id
OG
id|GF2K_ID_MAX
ques
c_cond
l_string|&quot;Unknown&quot;
suffix:colon
id|gf2k_names
(braket
id|gf2k-&gt;id
)braket
)paren
suffix:semicolon
r_goto
id|fail2
suffix:semicolon
)brace
id|sprintf
c_func
(paren
id|gf2k-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|gameport-&gt;phys
)paren
suffix:semicolon
id|gf2k-&gt;length
op_assign
id|gf2k_lens
(braket
id|gf2k-&gt;id
)braket
suffix:semicolon
id|gf2k-&gt;dev
dot
r_private
op_assign
id|gf2k
suffix:semicolon
id|gf2k-&gt;dev.open
op_assign
id|gf2k_open
suffix:semicolon
id|gf2k-&gt;dev.close
op_assign
id|gf2k_close
suffix:semicolon
id|gf2k-&gt;dev.evbit
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
id|gf2k-&gt;dev.name
op_assign
id|gf2k_names
(braket
id|gf2k-&gt;id
)braket
suffix:semicolon
id|gf2k-&gt;dev.phys
op_assign
id|gf2k-&gt;phys
suffix:semicolon
id|gf2k-&gt;dev.idbus
op_assign
id|BUS_GAMEPORT
suffix:semicolon
id|gf2k-&gt;dev.idvendor
op_assign
id|GAMEPORT_ID_VENDOR_GENIUS
suffix:semicolon
id|gf2k-&gt;dev.idproduct
op_assign
id|gf2k-&gt;id
suffix:semicolon
id|gf2k-&gt;dev.idversion
op_assign
l_int|0x0100
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
id|gf2k_axes
(braket
id|gf2k-&gt;id
)braket
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|gf2k_abs
(braket
id|i
)braket
comma
id|gf2k-&gt;dev.absbit
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
id|gf2k_hats
(braket
id|gf2k-&gt;id
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set_bit
c_func
(paren
id|ABS_HAT0X
op_plus
id|i
comma
id|gf2k-&gt;dev.absbit
)paren
suffix:semicolon
id|gf2k-&gt;dev.absmin
(braket
id|ABS_HAT0X
op_plus
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|gf2k-&gt;dev.absmax
(braket
id|ABS_HAT0X
op_plus
id|i
)braket
op_assign
l_int|1
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
id|gf2k_joys
(braket
id|gf2k-&gt;id
)braket
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|gf2k_btn_joy
(braket
id|i
)braket
comma
id|gf2k-&gt;dev.keybit
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
id|gf2k_pads
(braket
id|gf2k-&gt;id
)braket
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|gf2k_btn_pad
(braket
id|i
)braket
comma
id|gf2k-&gt;dev.keybit
)paren
suffix:semicolon
id|gf2k_read_packet
c_func
(paren
id|gameport
comma
id|gf2k-&gt;length
comma
id|data
)paren
suffix:semicolon
id|gf2k_read
c_func
(paren
id|gf2k
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
id|gf2k_axes
(braket
id|gf2k-&gt;id
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
id|gf2k-&gt;dev.absmax
(braket
id|gf2k_abs
(braket
id|i
)braket
)braket
op_assign
(paren
id|i
OL
l_int|2
)paren
ques
c_cond
id|gf2k-&gt;dev.abs
(braket
id|gf2k_abs
(braket
id|i
)braket
)braket
op_star
l_int|2
op_minus
l_int|32
suffix:colon
id|gf2k-&gt;dev.abs
(braket
id|gf2k_abs
(braket
l_int|0
)braket
)braket
op_plus
id|gf2k-&gt;dev.abs
(braket
id|gf2k_abs
(braket
l_int|1
)braket
)braket
op_minus
l_int|32
suffix:semicolon
id|gf2k-&gt;dev.absmin
(braket
id|gf2k_abs
(braket
id|i
)braket
)braket
op_assign
l_int|32
suffix:semicolon
id|gf2k-&gt;dev.absfuzz
(braket
id|gf2k_abs
(braket
id|i
)braket
)braket
op_assign
l_int|8
suffix:semicolon
id|gf2k-&gt;dev.absflat
(braket
id|gf2k_abs
(braket
id|i
)braket
)braket
op_assign
(paren
id|i
OL
l_int|2
)paren
ques
c_cond
l_int|24
suffix:colon
l_int|0
suffix:semicolon
)brace
id|input_register_device
c_func
(paren
op_amp
id|gf2k-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|gf2k_names
(braket
id|gf2k-&gt;id
)braket
comma
id|gameport-&gt;phys
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
id|gf2k
)paren
suffix:semicolon
)brace
DECL|function|gf2k_disconnect
r_static
r_void
id|gf2k_disconnect
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_struct
id|gf2k
op_star
id|gf2k
op_assign
id|gameport
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|gf2k-&gt;dev
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
id|gf2k
)paren
suffix:semicolon
)brace
DECL|variable|gf2k_dev
r_static
r_struct
id|gameport_dev
id|gf2k_dev
op_assign
(brace
id|connect
suffix:colon
id|gf2k_connect
comma
id|disconnect
suffix:colon
id|gf2k_disconnect
comma
)brace
suffix:semicolon
DECL|function|gf2k_init
r_int
id|__init
id|gf2k_init
c_func
(paren
r_void
)paren
(brace
id|gameport_register_device
c_func
(paren
op_amp
id|gf2k_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|gf2k_exit
r_void
id|__exit
id|gf2k_exit
c_func
(paren
r_void
)paren
(brace
id|gameport_unregister_device
c_func
(paren
op_amp
id|gf2k_dev
)paren
suffix:semicolon
)brace
DECL|variable|gf2k_init
id|module_init
c_func
(paren
id|gf2k_init
)paren
suffix:semicolon
DECL|variable|gf2k_exit
id|module_exit
c_func
(paren
id|gf2k_exit
)paren
suffix:semicolon
eof
