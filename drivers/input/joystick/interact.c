multiline_comment|/*&n; * $Id: interact.c,v 1.16 2002/01/22 20:28:25 vojtech Exp $&n; *&n; *  Copyright (c) 2001 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *&t;Toby Deshane&n; */
multiline_comment|/*&n; * InterAct digital gamepad/joystick driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
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
l_string|&quot;InterAct digital joystick driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|INTERACT_MAX_START
mdefine_line|#define INTERACT_MAX_START&t;400&t;/* 400 us */
DECL|macro|INTERACT_MAX_STROBE
mdefine_line|#define INTERACT_MAX_STROBE&t;40&t;/* 40 us */
DECL|macro|INTERACT_MAX_LENGTH
mdefine_line|#define INTERACT_MAX_LENGTH&t;32&t;/* 32 bits */
DECL|macro|INTERACT_REFRESH_TIME
mdefine_line|#define INTERACT_REFRESH_TIME&t;HZ/50&t;/* 20 ms */
DECL|macro|INTERACT_TYPE_HHFX
mdefine_line|#define INTERACT_TYPE_HHFX&t;0&t;/* HammerHead/FX */
DECL|macro|INTERACT_TYPE_PP8D
mdefine_line|#define INTERACT_TYPE_PP8D&t;1&t;/* ProPad 8 */
DECL|struct|interact
r_struct
id|interact
(brace
DECL|member|gameport
r_struct
id|gameport
op_star
id|gameport
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
DECL|member|used
r_int
id|used
suffix:semicolon
DECL|member|bads
r_int
id|bads
suffix:semicolon
DECL|member|reads
r_int
id|reads
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
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
DECL|variable|interact_abs_hhfx
r_static
r_int
id|interact_abs_hhfx
(braket
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
comma
id|ABS_HAT0X
comma
id|ABS_HAT0Y
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|interact_abs_pp8d
r_static
r_int
id|interact_abs_pp8d
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
DECL|variable|interact_btn_hhfx
r_static
r_int
id|interact_btn_hhfx
(braket
)braket
op_assign
(brace
id|BTN_TR
comma
id|BTN_X
comma
id|BTN_Y
comma
id|BTN_Z
comma
id|BTN_A
comma
id|BTN_B
comma
id|BTN_C
comma
id|BTN_TL
comma
id|BTN_TL2
comma
id|BTN_TR2
comma
id|BTN_MODE
comma
id|BTN_SELECT
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|variable|interact_btn_pp8d
r_static
r_int
id|interact_btn_pp8d
(braket
)braket
op_assign
(brace
id|BTN_C
comma
id|BTN_TL
comma
id|BTN_TR
comma
id|BTN_A
comma
id|BTN_B
comma
id|BTN_Y
comma
id|BTN_Z
comma
id|BTN_X
comma
op_minus
l_int|1
)brace
suffix:semicolon
DECL|struct|interact_type
r_struct
id|interact_type
(brace
DECL|member|id
r_int
id|id
suffix:semicolon
DECL|member|abs
r_int
op_star
id|abs
suffix:semicolon
DECL|member|btn
r_int
op_star
id|btn
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
DECL|member|length
r_int
r_char
id|length
suffix:semicolon
DECL|member|b8
r_int
r_char
id|b8
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|interact_type
r_static
r_struct
id|interact_type
id|interact_type
(braket
)braket
op_assign
(brace
(brace
l_int|0x6202
comma
id|interact_abs_hhfx
comma
id|interact_btn_hhfx
comma
l_string|&quot;InterAct HammerHead/FX&quot;
comma
l_int|32
comma
l_int|4
)brace
comma
(brace
l_int|0x53f8
comma
id|interact_abs_pp8d
comma
id|interact_btn_pp8d
comma
l_string|&quot;InterAct ProPad 8 Digital&quot;
comma
l_int|16
comma
l_int|0
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * interact_read_packet() reads and InterAct joystick data.&n; */
DECL|function|interact_read_packet
r_static
r_int
id|interact_read_packet
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
id|u32
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
l_int|0
suffix:semicolon
id|t
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|INTERACT_MAX_START
)paren
suffix:semicolon
id|s
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|INTERACT_MAX_STROBE
)paren
suffix:semicolon
id|local_save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|local_irq_disable
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
id|v
op_amp
op_complement
id|u
op_amp
l_int|0x40
)paren
(brace
id|data
(braket
l_int|0
)braket
op_assign
(paren
id|data
(braket
l_int|0
)braket
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|v
op_rshift
l_int|4
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|data
(braket
l_int|1
)braket
op_assign
(paren
id|data
(braket
l_int|1
)braket
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|v
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|data
(braket
l_int|2
)braket
op_assign
(paren
id|data
(braket
l_int|2
)braket
op_lshift
l_int|1
)paren
op_or
(paren
(paren
id|v
op_rshift
l_int|7
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|i
op_increment
suffix:semicolon
id|t
op_assign
id|s
suffix:semicolon
)brace
)brace
id|local_irq_restore
c_func
(paren
id|flags
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
multiline_comment|/*&n; * interact_timer() reads and analyzes InterAct joystick data.&n; */
DECL|function|interact_timer
r_static
r_void
id|interact_timer
c_func
(paren
r_int
r_int
r_private
)paren
(brace
r_struct
id|interact
op_star
id|interact
op_assign
(paren
r_struct
id|interact
op_star
)paren
r_private
suffix:semicolon
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|interact-&gt;dev
suffix:semicolon
id|u32
id|data
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|i
suffix:semicolon
id|interact-&gt;reads
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|interact_read_packet
c_func
(paren
id|interact-&gt;gameport
comma
id|interact-&gt;length
comma
id|data
)paren
OL
id|interact-&gt;length
)paren
(brace
id|interact-&gt;bads
op_increment
suffix:semicolon
)brace
r_else
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
id|data
(braket
id|i
)braket
op_lshift_assign
id|INTERACT_MAX_LENGTH
op_minus
id|interact-&gt;length
suffix:semicolon
r_switch
c_cond
(paren
id|interact-&gt;type
)paren
(brace
r_case
id|INTERACT_TYPE_HHFX
suffix:colon
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
id|input_report_abs
c_func
(paren
id|dev
comma
id|interact_abs_hhfx
(braket
id|i
)braket
comma
(paren
id|data
(braket
id|i
op_amp
l_int|1
)braket
op_rshift
(paren
(paren
id|i
op_rshift
l_int|1
)paren
op_lshift
l_int|3
)paren
)paren
op_amp
l_int|0xff
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
suffix:semicolon
id|i
op_increment
)paren
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_HAT0Y
op_minus
id|i
comma
(paren
(paren
id|data
(braket
l_int|1
)braket
op_rshift
(paren
(paren
id|i
op_lshift
l_int|1
)paren
op_plus
l_int|17
)paren
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|1
)braket
op_rshift
(paren
(paren
id|i
op_lshift
l_int|1
)paren
op_plus
l_int|16
)paren
)paren
op_amp
l_int|1
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|interact_btn_hhfx
(braket
id|i
)braket
comma
(paren
id|data
(braket
l_int|0
)braket
op_rshift
(paren
id|i
op_plus
l_int|16
)paren
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
l_int|4
suffix:semicolon
id|i
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|interact_btn_hhfx
(braket
id|i
op_plus
l_int|8
)braket
comma
(paren
id|data
(braket
l_int|1
)braket
op_rshift
(paren
id|i
op_plus
l_int|20
)paren
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|INTERACT_TYPE_PP8D
suffix:colon
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
id|input_report_abs
c_func
(paren
id|dev
comma
id|interact_abs_pp8d
(braket
id|i
)braket
comma
(paren
(paren
id|data
(braket
l_int|0
)braket
op_rshift
(paren
(paren
id|i
op_lshift
l_int|1
)paren
op_plus
l_int|20
)paren
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|0
)braket
op_rshift
(paren
(paren
id|i
op_lshift
l_int|1
)paren
op_plus
l_int|21
)paren
)paren
op_amp
l_int|1
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|interact_btn_pp8d
(braket
id|i
)braket
comma
(paren
id|data
(braket
l_int|1
)braket
op_rshift
(paren
id|i
op_plus
l_int|16
)paren
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|mod_timer
c_func
(paren
op_amp
id|interact-&gt;timer
comma
id|jiffies
op_plus
id|INTERACT_REFRESH_TIME
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * interact_open() is a callback from the input open routine.&n; */
DECL|function|interact_open
r_static
r_int
id|interact_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|interact
op_star
id|interact
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|interact-&gt;used
op_increment
)paren
id|mod_timer
c_func
(paren
op_amp
id|interact-&gt;timer
comma
id|jiffies
op_plus
id|INTERACT_REFRESH_TIME
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * interact_close() is a callback from the input close routine.&n; */
DECL|function|interact_close
r_static
r_void
id|interact_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|interact
op_star
id|interact
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
id|interact-&gt;used
)paren
id|del_timer
c_func
(paren
op_amp
id|interact-&gt;timer
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * interact_connect() probes for InterAct joysticks.&n; */
DECL|function|interact_connect
r_static
r_void
id|interact_connect
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
id|interact
op_star
id|interact
suffix:semicolon
id|__u32
id|data
(braket
l_int|3
)braket
suffix:semicolon
r_int
id|i
comma
id|t
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|interact
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|interact
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
id|interact
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|interact
)paren
)paren
suffix:semicolon
id|gameport
op_member_access_from_pointer
r_private
op_assign
id|interact
suffix:semicolon
id|interact-&gt;gameport
op_assign
id|gameport
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|interact-&gt;timer
)paren
suffix:semicolon
id|interact-&gt;timer.data
op_assign
(paren
r_int
)paren
id|interact
suffix:semicolon
id|interact-&gt;timer.function
op_assign
id|interact_timer
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
id|interact_read_packet
c_func
(paren
id|gameport
comma
id|INTERACT_MAX_LENGTH
op_star
l_int|2
comma
id|data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
l_int|32
op_logical_or
(paren
id|data
(braket
l_int|0
)braket
op_rshift
l_int|24
)paren
op_ne
l_int|0x0c
op_logical_or
(paren
id|data
(braket
l_int|1
)braket
op_rshift
l_int|24
)paren
op_ne
l_int|0x02
)paren
(brace
r_goto
id|fail2
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|interact_type
(braket
id|i
)braket
dot
id|length
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|interact_type
(braket
id|i
)braket
dot
id|id
op_eq
(paren
id|data
(braket
l_int|2
)braket
op_rshift
l_int|16
)paren
)paren
r_break
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|interact_type
(braket
id|i
)braket
dot
id|length
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;interact.c: Unknown joystick on %s. [len %d d0 %08x d1 %08x i2 %08x]&bslash;n&quot;
comma
id|gameport-&gt;phys
comma
id|i
comma
id|data
(braket
l_int|0
)braket
comma
id|data
(braket
l_int|1
)braket
comma
id|data
(braket
l_int|2
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
id|interact-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|gameport-&gt;phys
)paren
suffix:semicolon
id|interact-&gt;type
op_assign
id|i
suffix:semicolon
id|interact-&gt;length
op_assign
id|interact_type
(braket
id|i
)braket
dot
id|length
suffix:semicolon
id|interact-&gt;dev
dot
r_private
op_assign
id|interact
suffix:semicolon
id|interact-&gt;dev.open
op_assign
id|interact_open
suffix:semicolon
id|interact-&gt;dev.close
op_assign
id|interact_close
suffix:semicolon
id|interact-&gt;dev.name
op_assign
id|interact_type
(braket
id|i
)braket
dot
id|name
suffix:semicolon
id|interact-&gt;dev.phys
op_assign
id|interact-&gt;phys
suffix:semicolon
id|interact-&gt;dev.idbus
op_assign
id|BUS_GAMEPORT
suffix:semicolon
id|interact-&gt;dev.idvendor
op_assign
id|GAMEPORT_ID_VENDOR_INTERACT
suffix:semicolon
id|interact-&gt;dev.idproduct
op_assign
id|interact_type
(braket
id|i
)braket
dot
id|id
suffix:semicolon
id|interact-&gt;dev.idversion
op_assign
l_int|0x0100
suffix:semicolon
id|interact-&gt;dev.evbit
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
(paren
id|t
op_assign
id|interact_type
(braket
id|interact-&gt;type
)braket
dot
id|abs
(braket
id|i
)braket
)paren
op_ge
l_int|0
suffix:semicolon
id|i
op_increment
)paren
(brace
id|set_bit
c_func
(paren
id|t
comma
id|interact-&gt;dev.absbit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
id|interact_type
(braket
id|interact-&gt;type
)braket
dot
id|b8
)paren
(brace
id|interact-&gt;dev.absmin
(braket
id|t
)braket
op_assign
l_int|0
suffix:semicolon
id|interact-&gt;dev.absmax
(braket
id|t
)braket
op_assign
l_int|255
suffix:semicolon
)brace
r_else
(brace
id|interact-&gt;dev.absmin
(braket
id|t
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|interact-&gt;dev.absmax
(braket
id|t
)braket
op_assign
l_int|1
suffix:semicolon
)brace
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|t
op_assign
id|interact_type
(braket
id|interact-&gt;type
)braket
dot
id|btn
(braket
id|i
)braket
)paren
op_ge
l_int|0
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|t
comma
id|interact-&gt;dev.keybit
)paren
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|interact-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|interact_type
(braket
id|interact-&gt;type
)braket
dot
id|name
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
id|interact
)paren
suffix:semicolon
)brace
DECL|function|interact_disconnect
r_static
r_void
id|interact_disconnect
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_struct
id|interact
op_star
id|interact
op_assign
id|gameport
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|interact-&gt;dev
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
id|interact
)paren
suffix:semicolon
)brace
DECL|variable|interact_dev
r_static
r_struct
id|gameport_dev
id|interact_dev
op_assign
(brace
id|connect
suffix:colon
id|interact_connect
comma
id|disconnect
suffix:colon
id|interact_disconnect
comma
)brace
suffix:semicolon
DECL|function|interact_init
r_int
id|__init
id|interact_init
c_func
(paren
r_void
)paren
(brace
id|gameport_register_device
c_func
(paren
op_amp
id|interact_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|interact_exit
r_void
id|__exit
id|interact_exit
c_func
(paren
r_void
)paren
(brace
id|gameport_unregister_device
c_func
(paren
op_amp
id|interact_dev
)paren
suffix:semicolon
)brace
DECL|variable|interact_init
id|module_init
c_func
(paren
id|interact_init
)paren
suffix:semicolon
DECL|variable|interact_exit
id|module_exit
c_func
(paren
id|interact_exit
)paren
suffix:semicolon
eof
