multiline_comment|/*&n; * $Id: cobra.c,v 1.10 2000/06/08 10:23:45 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2000 Vojtech Pavlik&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * Creative Labd Blaster GamePad Cobra driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@suse.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
macro_line|#include &lt;linux/input.h&gt;
DECL|macro|COBRA_MAX_STROBE
mdefine_line|#define COBRA_MAX_STROBE&t;45&t;/* 45 us max wait for first strobe */
DECL|macro|COBRA_REFRESH_TIME
mdefine_line|#define COBRA_REFRESH_TIME&t;HZ/50&t;/* 20 ms between reads */
DECL|macro|COBRA_LENGTH
mdefine_line|#define COBRA_LENGTH&t;&t;36
DECL|variable|cobra_name
r_static
r_char
op_star
id|cobra_name
op_assign
l_string|&quot;Creative Labs Blaster GamePad Cobra&quot;
suffix:semicolon
DECL|variable|cobra_btn
r_static
r_int
id|cobra_btn
(braket
)braket
op_assign
(brace
id|BTN_START
comma
id|BTN_SELECT
comma
id|BTN_TL
comma
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
id|BTN_TL2
comma
id|BTN_TR2
comma
l_int|0
)brace
suffix:semicolon
DECL|struct|cobra
r_struct
id|cobra
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
DECL|function|cobra_read_packet
r_static
r_int
r_char
id|cobra_read_packet
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
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
comma
id|w
suffix:semicolon
id|__u64
id|buf
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|r
(braket
l_int|2
)braket
comma
id|t
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|ret
suffix:semicolon
r_int
id|strobe
op_assign
id|gameport_time
c_func
(paren
id|gameport
comma
id|COBRA_MAX_STROBE
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
(brace
id|r
(braket
id|i
)braket
op_assign
id|buf
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
id|t
(braket
id|i
)braket
op_assign
id|COBRA_MAX_STROBE
suffix:semicolon
)brace
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
id|u
op_assign
id|gameport_read
c_func
(paren
id|gameport
)paren
suffix:semicolon
r_do
(brace
id|t
(braket
l_int|0
)braket
op_decrement
suffix:semicolon
id|t
(braket
l_int|1
)braket
op_decrement
suffix:semicolon
id|v
op_assign
id|gameport_read
c_func
(paren
id|gameport
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
comma
id|w
op_assign
id|u
op_xor
id|v
suffix:semicolon
id|i
OL
l_int|2
op_logical_and
id|w
suffix:semicolon
id|i
op_increment
comma
id|w
op_rshift_assign
l_int|2
)paren
r_if
c_cond
(paren
id|w
op_amp
l_int|0x30
)paren
(brace
r_if
c_cond
(paren
(paren
id|w
op_amp
l_int|0x30
)paren
OL
l_int|0x30
op_logical_and
id|r
(braket
id|i
)braket
template_param
l_int|0
)paren
(brace
id|buf
(braket
id|i
)braket
op_or_assign
(paren
id|__u64
)paren
(paren
(paren
id|w
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
op_lshift
id|r
(braket
id|i
)braket
op_increment
suffix:semicolon
id|t
(braket
id|i
)braket
op_assign
id|strobe
suffix:semicolon
id|u
op_assign
id|v
suffix:semicolon
)brace
r_else
id|t
(braket
id|i
)braket
op_assign
l_int|0
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
id|__restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|ret
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|r
(braket
id|i
)braket
op_ne
id|COBRA_LENGTH
)paren
r_continue
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
id|COBRA_LENGTH
op_logical_and
(paren
id|buf
(braket
id|i
)braket
op_amp
l_int|0x04104107f
)paren
op_xor
l_int|0x041041040
suffix:semicolon
id|j
op_increment
)paren
id|buf
(braket
id|i
)braket
op_assign
(paren
id|buf
(braket
id|i
)braket
op_rshift
l_int|1
)paren
op_or
(paren
(paren
id|__u64
)paren
(paren
id|buf
(braket
id|i
)braket
op_amp
l_int|1
)paren
op_lshift
(paren
id|COBRA_LENGTH
op_minus
l_int|1
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|j
OL
id|COBRA_LENGTH
)paren
id|ret
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
id|data
(braket
id|i
)braket
op_assign
(paren
(paren
id|buf
(braket
id|i
)braket
op_rshift
l_int|7
)paren
op_amp
l_int|0x000001f
)paren
op_or
(paren
(paren
id|buf
(braket
id|i
)braket
op_rshift
l_int|8
)paren
op_amp
l_int|0x00003e0
)paren
op_or
(paren
(paren
id|buf
(braket
id|i
)braket
op_rshift
l_int|9
)paren
op_amp
l_int|0x0007c00
)paren
op_or
(paren
(paren
id|buf
(braket
id|i
)braket
op_rshift
l_int|10
)paren
op_amp
l_int|0x00f8000
)paren
op_or
(paren
(paren
id|buf
(braket
id|i
)braket
op_rshift
l_int|11
)paren
op_amp
l_int|0x1f00000
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|cobra_timer
r_static
r_void
id|cobra_timer
c_func
(paren
r_int
r_int
r_private
)paren
(brace
r_struct
id|cobra
op_star
id|cobra
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
r_int
id|data
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|r
suffix:semicolon
id|cobra-&gt;reads
op_increment
suffix:semicolon
r_if
c_cond
(paren
(paren
id|r
op_assign
id|cobra_read_packet
c_func
(paren
id|cobra-&gt;gameport
comma
id|data
)paren
)paren
op_ne
id|cobra-&gt;exists
)paren
id|cobra-&gt;bads
op_increment
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
id|cobra-&gt;exists
op_amp
id|r
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
id|dev
op_assign
id|cobra-&gt;dev
op_plus
id|i
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
id|data
(braket
id|i
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|1
)paren
op_minus
(paren
(paren
id|data
(braket
id|i
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
id|ABS_Y
comma
(paren
(paren
id|data
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
(paren
id|data
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
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|cobra_btn
(braket
id|j
)braket
suffix:semicolon
id|j
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|cobra_btn
(braket
id|j
)braket
comma
id|data
(braket
id|i
)braket
op_amp
(paren
l_int|0x20
op_lshift
id|j
)paren
)paren
suffix:semicolon
)brace
id|mod_timer
c_func
(paren
op_amp
id|cobra-&gt;timer
comma
id|jiffies
op_plus
id|COBRA_REFRESH_TIME
)paren
suffix:semicolon
)brace
DECL|function|cobra_open
r_static
r_int
id|cobra_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|cobra
op_star
id|cobra
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cobra-&gt;used
op_increment
)paren
id|mod_timer
c_func
(paren
op_amp
id|cobra-&gt;timer
comma
id|jiffies
op_plus
id|COBRA_REFRESH_TIME
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cobra_close
r_static
r_void
id|cobra_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|cobra
op_star
id|cobra
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
id|cobra-&gt;used
)paren
id|del_timer
c_func
(paren
op_amp
id|cobra-&gt;timer
)paren
suffix:semicolon
)brace
DECL|function|cobra_connect
r_static
r_void
id|cobra_connect
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
id|cobra
op_star
id|cobra
suffix:semicolon
r_int
r_int
id|data
(braket
l_int|2
)braket
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|cobra
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|cobra
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
id|cobra
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|cobra
)paren
)paren
suffix:semicolon
id|gameport
op_member_access_from_pointer
r_private
op_assign
id|cobra
suffix:semicolon
id|cobra-&gt;gameport
op_assign
id|gameport
suffix:semicolon
id|init_timer
c_func
(paren
op_amp
id|cobra-&gt;timer
)paren
suffix:semicolon
id|cobra-&gt;timer.data
op_assign
(paren
r_int
)paren
id|cobra
suffix:semicolon
id|cobra-&gt;timer.function
op_assign
id|cobra_timer
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
id|cobra-&gt;exists
op_assign
id|cobra_read_packet
c_func
(paren
id|gameport
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|cobra-&gt;exists
op_rshift
id|i
)paren
op_amp
id|data
(braket
id|i
)braket
op_amp
l_int|1
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;cobra.c: Device on gameport%d.%d has the Ext bit set. ID is: %d&quot;
l_string|&quot; Contact vojtech@suse.cz&bslash;n&quot;
comma
id|gameport-&gt;number
comma
id|i
comma
(paren
id|data
(braket
id|i
)braket
op_rshift
l_int|2
)paren
op_amp
l_int|7
)paren
suffix:semicolon
id|cobra-&gt;exists
op_and_assign
op_complement
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|cobra-&gt;exists
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
(paren
id|cobra-&gt;exists
op_rshift
id|i
)paren
op_amp
l_int|1
)paren
(brace
id|cobra-&gt;dev
(braket
id|i
)braket
dot
r_private
op_assign
id|cobra
suffix:semicolon
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|open
op_assign
id|cobra_open
suffix:semicolon
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|close
op_assign
id|cobra_close
suffix:semicolon
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|name
op_assign
id|cobra_name
suffix:semicolon
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|idbus
op_assign
id|BUS_GAMEPORT
suffix:semicolon
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|idvendor
op_assign
id|GAMEPORT_ID_VENDOR_CREATIVE
suffix:semicolon
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|idproduct
op_assign
l_int|0x0008
suffix:semicolon
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|idversion
op_assign
l_int|0x0100
suffix:semicolon
id|cobra-&gt;dev
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
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|absbit
(braket
l_int|0
)braket
op_assign
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
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|cobra_btn
(braket
id|j
)braket
suffix:semicolon
id|j
op_increment
)paren
id|set_bit
c_func
(paren
id|cobra_btn
(braket
id|j
)braket
comma
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|keybit
)paren
suffix:semicolon
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|absmin
(braket
id|ABS_X
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|absmax
(braket
id|ABS_X
)braket
op_assign
l_int|1
suffix:semicolon
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|absmin
(braket
id|ABS_Y
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|absmax
(braket
id|ABS_Y
)braket
op_assign
l_int|1
suffix:semicolon
id|input_register_device
c_func
(paren
id|cobra-&gt;dev
op_plus
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input%d: %s on gameport%d.%d&bslash;n&quot;
comma
id|cobra-&gt;dev
(braket
id|i
)braket
dot
id|number
comma
id|cobra_name
comma
id|gameport-&gt;number
comma
id|i
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
id|cobra
)paren
suffix:semicolon
)brace
DECL|function|cobra_disconnect
r_static
r_void
id|cobra_disconnect
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
id|cobra
op_star
id|cobra
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
(paren
id|cobra-&gt;exists
op_rshift
id|i
)paren
op_amp
l_int|1
)paren
id|input_unregister_device
c_func
(paren
id|cobra-&gt;dev
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
id|cobra
)paren
suffix:semicolon
)brace
DECL|variable|cobra_dev
r_static
r_struct
id|gameport_dev
id|cobra_dev
op_assign
(brace
id|connect
suffix:colon
id|cobra_connect
comma
id|disconnect
suffix:colon
id|cobra_disconnect
comma
)brace
suffix:semicolon
DECL|function|cobra_init
r_int
id|__init
id|cobra_init
c_func
(paren
r_void
)paren
(brace
id|gameport_register_device
c_func
(paren
op_amp
id|cobra_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cobra_exit
r_void
id|__exit
id|cobra_exit
c_func
(paren
r_void
)paren
(brace
id|gameport_unregister_device
c_func
(paren
op_amp
id|cobra_dev
)paren
suffix:semicolon
)brace
DECL|variable|cobra_init
id|module_init
c_func
(paren
id|cobra_init
)paren
suffix:semicolon
DECL|variable|cobra_exit
id|module_exit
c_func
(paren
id|cobra_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof