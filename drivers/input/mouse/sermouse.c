multiline_comment|/*&n; * $Id: sermouse.c,v 1.17 2002/03/13 10:03:43 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; *  Serial mouse driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/init.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Serial mouse driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|sermouse_protocols
r_static
r_char
op_star
id|sermouse_protocols
(braket
)braket
op_assign
(brace
l_string|&quot;None&quot;
comma
l_string|&quot;Mouse Systems Mouse&quot;
comma
l_string|&quot;Sun Mouse&quot;
comma
l_string|&quot;Microsoft Mouse&quot;
comma
l_string|&quot;Logitech M+ Mouse&quot;
comma
l_string|&quot;Microsoft MZ Mouse&quot;
comma
l_string|&quot;Logitech MZ+ Mouse&quot;
comma
l_string|&quot;Logitech MZ++ Mouse&quot;
)brace
suffix:semicolon
DECL|struct|sermouse
r_struct
id|sermouse
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|buf
r_int
r_char
id|buf
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|count
r_int
r_char
id|count
suffix:semicolon
DECL|member|type
r_int
r_char
id|type
suffix:semicolon
DECL|member|last
r_int
r_int
id|last
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
multiline_comment|/*&n; * sermouse_process_msc() analyzes the incoming MSC/Sun bytestream and&n; * applies some prediction to the data, resulting in 96 updates per&n; * second, which is as good as a PS/2 or USB mouse.&n; */
DECL|function|sermouse_process_msc
r_static
r_void
id|sermouse_process_msc
c_func
(paren
r_struct
id|sermouse
op_star
id|sermouse
comma
r_int
r_char
id|data
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|sermouse-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|buf
op_assign
id|sermouse-&gt;buf
suffix:semicolon
r_switch
c_cond
(paren
id|sermouse-&gt;count
)paren
(brace
r_case
l_int|0
suffix:colon
r_if
c_cond
(paren
(paren
id|data
op_amp
l_int|0xf8
)paren
op_ne
l_int|0x80
)paren
r_return
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
op_logical_neg
(paren
id|data
op_amp
l_int|4
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
op_logical_neg
(paren
id|data
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
id|BTN_MIDDLE
comma
op_logical_neg
(paren
id|data
op_amp
l_int|2
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
r_case
l_int|3
suffix:colon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_X
comma
id|data
op_div
l_int|2
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_Y
comma
op_minus
id|buf
(braket
l_int|1
)braket
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
id|data
op_minus
id|data
op_div
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
r_case
l_int|4
suffix:colon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_X
comma
id|buf
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_Y
comma
id|buf
(braket
l_int|1
)braket
op_minus
id|data
)paren
suffix:semicolon
id|buf
(braket
l_int|1
)braket
op_assign
id|data
op_div
l_int|2
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
op_increment
id|sermouse-&gt;count
op_eq
(paren
l_int|5
op_minus
(paren
(paren
id|sermouse-&gt;type
op_eq
id|SERIO_SUN
)paren
op_lshift
l_int|1
)paren
)paren
)paren
id|sermouse-&gt;count
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * sermouse_process_ms() anlyzes the incoming MS(Z/+/++) bytestream and&n; * generates events. With prediction it gets 80 updates/sec, assuming&n; * standard 3-byte packets and 1200 bps.&n; */
DECL|function|sermouse_process_ms
r_static
r_void
id|sermouse_process_ms
c_func
(paren
r_struct
id|sermouse
op_star
id|sermouse
comma
r_int
r_char
id|data
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|sermouse-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|buf
op_assign
id|sermouse-&gt;buf
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
l_int|0x40
)paren
id|sermouse-&gt;count
op_assign
l_int|0
suffix:semicolon
r_switch
c_cond
(paren
id|sermouse-&gt;count
)paren
(brace
r_case
l_int|0
suffix:colon
id|buf
(braket
l_int|1
)braket
op_assign
id|data
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_LEFT
comma
(paren
id|data
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_RIGHT
comma
(paren
id|data
op_rshift
l_int|4
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|buf
(braket
l_int|2
)braket
op_assign
id|data
suffix:semicolon
id|data
op_assign
(paren
r_int
r_char
)paren
(paren
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_lshift
l_int|6
)paren
op_amp
l_int|0xc0
)paren
op_or
(paren
id|data
op_amp
l_int|0x3f
)paren
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_X
comma
id|data
op_div
l_int|2
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_Y
comma
id|buf
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|buf
(braket
l_int|3
)braket
op_assign
id|data
op_minus
id|data
op_div
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|2
suffix:colon
multiline_comment|/* Guessing the state of the middle button on 3-button MS-protocol mice - ugly. */
r_if
c_cond
(paren
(paren
id|sermouse-&gt;type
op_eq
id|SERIO_MS
)paren
op_logical_and
op_logical_neg
id|data
op_logical_and
op_logical_neg
id|buf
(braket
l_int|2
)braket
op_logical_and
op_logical_neg
(paren
(paren
id|buf
(braket
l_int|0
)braket
op_amp
l_int|0xf0
)paren
op_xor
id|buf
(braket
l_int|1
)braket
)paren
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
op_logical_neg
id|test_bit
c_func
(paren
id|BTN_MIDDLE
comma
id|dev-&gt;key
)paren
)paren
suffix:semicolon
id|buf
(braket
l_int|0
)braket
op_assign
id|buf
(braket
l_int|1
)braket
suffix:semicolon
id|data
op_assign
(paren
r_int
r_char
)paren
(paren
(paren
(paren
id|buf
(braket
l_int|1
)braket
op_lshift
l_int|4
)paren
op_amp
l_int|0xc0
)paren
op_or
(paren
id|data
op_amp
l_int|0x3f
)paren
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_X
comma
id|buf
(braket
l_int|3
)braket
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_Y
comma
id|data
op_minus
id|buf
(braket
l_int|4
)braket
)paren
suffix:semicolon
id|buf
(braket
l_int|4
)braket
op_assign
id|data
op_div
l_int|2
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
r_switch
c_cond
(paren
id|sermouse-&gt;type
)paren
(brace
r_case
id|SERIO_MS
suffix:colon
id|sermouse-&gt;type
op_assign
id|SERIO_MP
suffix:semicolon
r_case
id|SERIO_MP
suffix:colon
r_if
c_cond
(paren
(paren
id|data
op_rshift
l_int|2
)paren
op_amp
l_int|3
)paren
r_break
suffix:semicolon
multiline_comment|/* M++ Wireless Extension packet. */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
(paren
id|data
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_SIDE
comma
(paren
id|data
op_rshift
l_int|4
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|SERIO_MZP
suffix:colon
r_case
id|SERIO_MZPP
suffix:colon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_SIDE
comma
(paren
id|data
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_case
id|SERIO_MZ
suffix:colon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_MIDDLE
comma
(paren
id|data
op_rshift
l_int|4
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_WHEEL
comma
(paren
id|data
op_amp
l_int|7
)paren
op_minus
(paren
id|data
op_amp
l_int|8
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
r_case
l_int|4
suffix:colon
r_case
l_int|6
suffix:colon
multiline_comment|/* MZ++ packet type. We can get these bytes for M++ too but we ignore them later. */
id|buf
(braket
l_int|1
)braket
op_assign
(paren
id|data
op_rshift
l_int|2
)paren
op_amp
l_int|0x0f
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
r_case
l_int|7
suffix:colon
multiline_comment|/* Ignore anything besides MZ++ */
r_if
c_cond
(paren
id|sermouse-&gt;type
op_ne
id|SERIO_MZPP
)paren
r_break
suffix:semicolon
r_switch
c_cond
(paren
id|buf
(braket
l_int|1
)braket
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* Extra mouse info */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_SIDE
comma
(paren
id|data
op_rshift
l_int|4
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_EXTRA
comma
(paren
id|data
op_rshift
l_int|5
)paren
op_amp
l_int|1
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|data
op_amp
l_int|0x80
ques
c_cond
id|REL_HWHEEL
suffix:colon
id|REL_WHEEL
comma
(paren
id|data
op_amp
l_int|7
)paren
op_minus
(paren
id|data
op_amp
l_int|8
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
multiline_comment|/* We don&squot;t decode anything else yet. */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;sermouse.c: Received MZ++ packet %x, don&squot;t know how to handle.&bslash;n&quot;
comma
id|buf
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
r_break
suffix:semicolon
)brace
id|sermouse-&gt;count
op_increment
suffix:semicolon
)brace
multiline_comment|/*&n; * sermouse_interrupt() handles incoming characters, either gathering them into&n; * packets or passing them to the command routine as command output.&n; */
DECL|function|sermouse_interrupt
r_static
r_void
id|sermouse_interrupt
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
id|sermouse
op_star
id|sermouse
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|time_after
c_func
(paren
id|jiffies
comma
id|sermouse-&gt;last
op_plus
id|HZ
op_div
l_int|20
)paren
)paren
id|sermouse-&gt;count
op_assign
l_int|0
suffix:semicolon
id|sermouse-&gt;last
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|sermouse-&gt;type
OG
id|SERIO_SUN
)paren
id|sermouse_process_ms
c_func
(paren
id|sermouse
comma
id|data
)paren
suffix:semicolon
r_else
id|sermouse_process_msc
c_func
(paren
id|sermouse
comma
id|data
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sermouse_disconnect() cleans up after we don&squot;t want talk&n; * to the mouse anymore.&n; */
DECL|function|sermouse_disconnect
r_static
r_void
id|sermouse_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|sermouse
op_star
id|sermouse
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|sermouse-&gt;dev
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
id|sermouse
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * sermouse_connect() is a callback form the serio module when&n; * an unhandled serio port is found.&n; */
DECL|function|sermouse_connect
r_static
r_void
id|sermouse_connect
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
id|sermouse
op_star
id|sermouse
suffix:semicolon
r_int
r_char
id|c
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
op_logical_neg
(paren
id|serio-&gt;type
op_amp
id|SERIO_PROTO
)paren
op_logical_or
(paren
(paren
id|serio-&gt;type
op_amp
id|SERIO_PROTO
)paren
OG
id|SERIO_MZPP
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|sermouse
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|sermouse
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
id|sermouse
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|sermouse
)paren
)paren
suffix:semicolon
id|sermouse-&gt;dev.evbit
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
id|sermouse-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_MOUSE
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_LEFT
)paren
op_or
id|BIT
c_func
(paren
id|BTN_RIGHT
)paren
suffix:semicolon
id|sermouse-&gt;dev.relbit
(braket
l_int|0
)braket
op_assign
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
id|sermouse-&gt;dev
dot
r_private
op_assign
id|sermouse
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|sermouse
suffix:semicolon
id|sermouse-&gt;type
op_assign
id|serio-&gt;type
op_amp
id|SERIO_PROTO
suffix:semicolon
id|c
op_assign
(paren
id|serio-&gt;type
op_amp
id|SERIO_EXTRA
)paren
op_rshift
l_int|16
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
l_int|0x01
)paren
id|set_bit
c_func
(paren
id|BTN_MIDDLE
comma
op_amp
id|sermouse-&gt;dev.keybit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
l_int|0x02
)paren
id|set_bit
c_func
(paren
id|BTN_SIDE
comma
op_amp
id|sermouse-&gt;dev.keybit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
l_int|0x04
)paren
id|set_bit
c_func
(paren
id|BTN_EXTRA
comma
op_amp
id|sermouse-&gt;dev.keybit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
l_int|0x10
)paren
id|set_bit
c_func
(paren
id|REL_WHEEL
comma
op_amp
id|sermouse-&gt;dev.relbit
)paren
suffix:semicolon
r_if
c_cond
(paren
id|c
op_amp
l_int|0x20
)paren
id|set_bit
c_func
(paren
id|REL_HWHEEL
comma
op_amp
id|sermouse-&gt;dev.relbit
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|sermouse-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|sermouse-&gt;dev.name
op_assign
id|sermouse_protocols
(braket
id|sermouse-&gt;type
)braket
suffix:semicolon
id|sermouse-&gt;dev.phys
op_assign
id|sermouse-&gt;phys
suffix:semicolon
id|sermouse-&gt;dev.idbus
op_assign
id|BUS_RS232
suffix:semicolon
id|sermouse-&gt;dev.idvendor
op_assign
id|sermouse-&gt;type
suffix:semicolon
id|sermouse-&gt;dev.idproduct
op_assign
id|c
suffix:semicolon
id|sermouse-&gt;dev.idversion
op_assign
l_int|0x0100
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
id|sermouse
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|input_register_device
c_func
(paren
op_amp
id|sermouse-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|sermouse_protocols
(braket
id|sermouse-&gt;type
)braket
comma
id|serio-&gt;phys
)paren
suffix:semicolon
)brace
DECL|variable|sermouse_dev
r_static
r_struct
id|serio_dev
id|sermouse_dev
op_assign
(brace
id|interrupt
suffix:colon
id|sermouse_interrupt
comma
id|connect
suffix:colon
id|sermouse_connect
comma
id|disconnect
suffix:colon
id|sermouse_disconnect
)brace
suffix:semicolon
DECL|function|sermouse_init
r_int
id|__init
id|sermouse_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_device
c_func
(paren
op_amp
id|sermouse_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|sermouse_exit
r_void
id|__exit
id|sermouse_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_device
c_func
(paren
op_amp
id|sermouse_dev
)paren
suffix:semicolon
)brace
DECL|variable|sermouse_init
id|module_init
c_func
(paren
id|sermouse_init
)paren
suffix:semicolon
DECL|variable|sermouse_exit
id|module_exit
c_func
(paren
id|sermouse_exit
)paren
suffix:semicolon
eof
