multiline_comment|/*&n; * $Id: stinger.c,v 1.4 2001/05/23 09:25:02 vojtech Exp $&n; *&n; *  Copyright (c) 2000-2001 Vojtech Pavlik&n; *  Copyright (c) 2000 Mark Fletcher&n; *&n; *  Sponsored by SuSE&n; */
multiline_comment|/*&n; * Gravis Stinger gamepad driver for Linux&n; */
multiline_comment|/*&n; * This program is free warftware; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; *  Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Ucitelska 1576, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/*&n; * Constants.&n; */
DECL|macro|STINGER_MAX_LENGTH
mdefine_line|#define STINGER_MAX_LENGTH 8
DECL|variable|stinger_name
r_static
r_char
op_star
id|stinger_name
op_assign
l_string|&quot;Gravis Stinger&quot;
suffix:semicolon
multiline_comment|/*&n; * Per-Stinger data.&n; */
DECL|struct|stinger
r_struct
id|stinger
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|idx
r_int
id|idx
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
id|STINGER_MAX_LENGTH
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/*&n; * stinger_process_packet() decodes packets the driver receives from the&n; * Stinger. It updates the data accordingly.&n; */
DECL|function|stinger_process_packet
r_static
r_void
id|stinger_process_packet
c_func
(paren
r_struct
id|stinger
op_star
id|stinger
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|stinger-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|stinger-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|stinger-&gt;idx
)paren
r_return
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_A
comma
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x20
)paren
op_rshift
l_int|5
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_B
comma
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x10
)paren
op_rshift
l_int|4
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_C
comma
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x08
)paren
op_rshift
l_int|3
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_X
comma
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x04
)paren
op_rshift
l_int|2
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_Y
comma
(paren
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|0x20
)paren
op_rshift
l_int|5
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_Z
comma
(paren
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|0x10
)paren
op_rshift
l_int|4
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TL
comma
(paren
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|0x08
)paren
op_rshift
l_int|3
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TR
comma
(paren
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|0x04
)paren
op_rshift
l_int|2
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_SELECT
comma
(paren
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|0x02
)paren
op_rshift
l_int|1
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_START
comma
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|0x01
)paren
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
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x3F
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x01
)paren
op_lshift
l_int|6
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
l_int|0
)braket
op_amp
l_int|0x02
)paren
op_lshift
l_int|5
)paren
op_minus
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|0x3F
)paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * stinger_interrupt() is called by the low level driver when characters&n; * are ready for us. We then buffer them for further processing, or call the&n; * packet processing routine.&n; */
DECL|function|stinger_interrupt
r_static
r_void
id|stinger_interrupt
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
id|stinger
op_star
id|stinger
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
multiline_comment|/* All Stinger packets are 4 bytes */
r_if
c_cond
(paren
id|stinger-&gt;idx
OL
id|STINGER_MAX_LENGTH
)paren
id|stinger-&gt;data
(braket
id|stinger-&gt;idx
op_increment
)braket
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|stinger-&gt;idx
op_eq
l_int|4
)paren
(brace
id|stinger_process_packet
c_func
(paren
id|stinger
)paren
suffix:semicolon
id|stinger-&gt;idx
op_assign
l_int|0
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * stinger_disconnect() is the opposite of stinger_connect()&n; */
DECL|function|stinger_disconnect
r_static
r_void
id|stinger_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|stinger
op_star
id|stinger
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|stinger-&gt;dev
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
id|stinger
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * stinger_connect() is the routine that is called when someone adds a&n; * new serio device. It looks for the Stinger, and if found, registers&n; * it as an input device.&n; */
DECL|function|stinger_connect
r_static
r_void
id|stinger_connect
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
id|stinger
op_star
id|stinger
suffix:semicolon
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|serio-&gt;type
op_ne
(paren
id|SERIO_RS232
op_or
id|SERIO_STINGER
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|stinger
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|stinger
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
id|stinger
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|stinger
)paren
)paren
suffix:semicolon
id|stinger-&gt;dev.evbit
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
id|stinger-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_A
)paren
)braket
op_assign
id|BIT
c_func
(paren
id|BTN_A
)paren
op_or
id|BIT
c_func
(paren
id|BTN_B
)paren
op_or
id|BIT
c_func
(paren
id|BTN_C
)paren
op_or
id|BIT
c_func
(paren
id|BTN_X
)paren
op_or
"&bslash;"
id|BIT
c_func
(paren
id|BTN_Y
)paren
op_or
id|BIT
c_func
(paren
id|BTN_Z
)paren
op_or
id|BIT
c_func
(paren
id|BTN_TL
)paren
op_or
id|BIT
c_func
(paren
id|BTN_TR
)paren
op_or
"&bslash;"
id|BIT
c_func
(paren
id|BTN_START
)paren
op_or
id|BIT
c_func
(paren
id|BTN_SELECT
)paren
suffix:semicolon
id|stinger-&gt;dev.absbit
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
id|stinger-&gt;dev.name
op_assign
id|stinger_name
suffix:semicolon
id|stinger-&gt;dev.idbus
op_assign
id|BUS_RS232
suffix:semicolon
id|stinger-&gt;dev.idvendor
op_assign
id|SERIO_STINGER
suffix:semicolon
id|stinger-&gt;dev.idproduct
op_assign
l_int|0x0001
suffix:semicolon
id|stinger-&gt;dev.idversion
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
l_int|2
suffix:semicolon
id|i
op_increment
)paren
(brace
id|stinger-&gt;dev.absmax
(braket
id|ABS_X
op_plus
id|i
)braket
op_assign
l_int|64
suffix:semicolon
id|stinger-&gt;dev.absmin
(braket
id|ABS_X
op_plus
id|i
)braket
op_assign
op_minus
l_int|64
suffix:semicolon
id|stinger-&gt;dev.absflat
(braket
id|ABS_X
op_plus
id|i
)braket
op_assign
l_int|4
suffix:semicolon
)brace
id|stinger-&gt;dev
dot
r_private
op_assign
id|stinger
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|stinger
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
id|stinger
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|input_register_device
c_func
(paren
op_amp
id|stinger-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input%d: %s on serio%d&bslash;n&quot;
comma
id|stinger-&gt;dev.number
comma
id|stinger_name
comma
id|serio-&gt;number
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The serio device structure.&n; */
DECL|variable|stinger_dev
r_static
r_struct
id|serio_dev
id|stinger_dev
op_assign
(brace
id|interrupt
suffix:colon
id|stinger_interrupt
comma
id|connect
suffix:colon
id|stinger_connect
comma
id|disconnect
suffix:colon
id|stinger_disconnect
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * The functions for inserting/removing us as a module.&n; */
DECL|function|stinger_init
r_int
id|__init
id|stinger_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_device
c_func
(paren
op_amp
id|stinger_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|stinger_exit
r_void
id|__exit
id|stinger_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_device
c_func
(paren
op_amp
id|stinger_dev
)paren
suffix:semicolon
)brace
DECL|variable|stinger_init
id|module_init
c_func
(paren
id|stinger_init
)paren
suffix:semicolon
DECL|variable|stinger_exit
id|module_exit
c_func
(paren
id|stinger_exit
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof