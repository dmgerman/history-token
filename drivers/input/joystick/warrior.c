multiline_comment|/*&n; * $Id: warrior.c,v 1.14 2002/01/22 20:32:10 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * Logitech WingMan Warrior joystick driver for Linux&n; */
multiline_comment|/*&n; * This program is free warftware; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; *  Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
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
l_string|&quot;Logitech WingMan Warrior joystick driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Constants.&n; */
DECL|macro|WARRIOR_MAX_LENGTH
mdefine_line|#define WARRIOR_MAX_LENGTH&t;16
DECL|variable|warrior_lengths
r_static
r_char
id|warrior_lengths
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|4
comma
l_int|12
comma
l_int|3
comma
l_int|4
comma
l_int|4
comma
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|warrior_name
r_static
r_char
op_star
id|warrior_name
op_assign
l_string|&quot;Logitech WingMan Warrior&quot;
suffix:semicolon
multiline_comment|/*&n; * Per-Warrior data.&n; */
DECL|struct|warrior
r_struct
id|warrior
(brace
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|idx
DECL|member|len
r_int
id|idx
comma
id|len
suffix:semicolon
DECL|member|data
r_int
r_char
id|data
(braket
id|WARRIOR_MAX_LENGTH
)braket
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
multiline_comment|/*&n; * warrior_process_packet() decodes packets the driver receives from the&n; * Warrior. It updates the data accordingly.&n; */
DECL|function|warrior_process_packet
r_static
r_void
id|warrior_process_packet
c_func
(paren
r_struct
id|warrior
op_star
id|warrior
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|warrior-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|warrior-&gt;data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|warrior-&gt;idx
)paren
r_return
suffix:semicolon
id|input_regs
c_func
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
r_switch
c_cond
(paren
(paren
id|data
(braket
l_int|0
)braket
op_rshift
l_int|4
)paren
op_amp
l_int|7
)paren
(brace
r_case
l_int|1
suffix:colon
multiline_comment|/* Button data */
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_TRIGGER
comma
id|data
(braket
l_int|3
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
(paren
id|data
(braket
l_int|3
)braket
op_rshift
l_int|1
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
id|BTN_TOP
comma
(paren
id|data
(braket
l_int|3
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
id|dev
comma
id|BTN_TOP2
comma
(paren
id|data
(braket
l_int|3
)braket
op_rshift
l_int|3
)paren
op_amp
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|3
suffix:colon
multiline_comment|/* XY-axis info-&gt;data */
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
l_int|0
)braket
op_amp
l_int|8
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
op_or
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|4
)paren
op_lshift
l_int|5
)paren
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
id|data
(braket
l_int|1
)braket
op_or
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
op_lshift
l_int|7
)paren
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|2
)paren
op_lshift
l_int|7
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|5
suffix:colon
multiline_comment|/* Throttle, spinner, hat info-&gt;data */
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
l_int|1
)braket
op_or
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|1
)paren
op_lshift
l_int|7
)paren
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|2
)paren
op_lshift
l_int|7
)paren
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
l_int|3
)braket
op_amp
l_int|2
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_minus
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|1
ques
c_cond
l_int|1
suffix:colon
l_int|0
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
id|data
(braket
l_int|3
)braket
op_amp
l_int|8
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
op_minus
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|4
ques
c_cond
l_int|1
suffix:colon
l_int|0
)paren
)paren
suffix:semicolon
id|input_report_rel
c_func
(paren
id|dev
comma
id|REL_DIAL
comma
(paren
id|data
(braket
l_int|2
)braket
op_or
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|4
)paren
op_lshift
l_int|5
)paren
)paren
op_minus
(paren
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|8
)paren
op_lshift
l_int|5
)paren
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
multiline_comment|/*&n; * warrior_interrupt() is called by the low level driver when characters&n; * are ready for us. We then buffer them for further processing, or call the&n; * packet processing routine.&n; */
DECL|function|warrior_interrupt
r_static
r_void
id|warrior_interrupt
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
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|warrior
op_star
id|warrior
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
id|data
op_amp
l_int|0x80
)paren
(brace
r_if
c_cond
(paren
id|warrior-&gt;idx
)paren
id|warrior_process_packet
c_func
(paren
id|warrior
comma
id|regs
)paren
suffix:semicolon
id|warrior-&gt;idx
op_assign
l_int|0
suffix:semicolon
id|warrior-&gt;len
op_assign
id|warrior_lengths
(braket
(paren
id|data
op_rshift
l_int|4
)paren
op_amp
l_int|7
)braket
suffix:semicolon
)brace
r_if
c_cond
(paren
id|warrior-&gt;idx
OL
id|warrior-&gt;len
)paren
id|warrior-&gt;data
(braket
id|warrior-&gt;idx
op_increment
)braket
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|warrior-&gt;idx
op_eq
id|warrior-&gt;len
)paren
(brace
r_if
c_cond
(paren
id|warrior-&gt;idx
)paren
id|warrior_process_packet
c_func
(paren
id|warrior
comma
id|regs
)paren
suffix:semicolon
id|warrior-&gt;idx
op_assign
l_int|0
suffix:semicolon
id|warrior-&gt;len
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * warrior_disconnect() is the opposite of warrior_connect()&n; */
DECL|function|warrior_disconnect
r_static
r_void
id|warrior_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|warrior
op_star
id|warrior
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|warrior-&gt;dev
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
id|warrior
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * warrior_connect() is the routine that is called when someone adds a&n; * new serio device. It looks for the Warrior, and if found, registers&n; * it as an input device.&n; */
DECL|function|warrior_connect
r_static
r_void
id|warrior_connect
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
id|warrior
op_star
id|warrior
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
id|SERIO_WARRIOR
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|warrior
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|warrior
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
id|warrior
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|warrior
)paren
)paren
suffix:semicolon
id|warrior-&gt;dev.evbit
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
op_or
id|BIT
c_func
(paren
id|EV_ABS
)paren
suffix:semicolon
id|warrior-&gt;dev.keybit
(braket
id|LONG
c_func
(paren
id|BTN_TRIGGER
)paren
)braket
op_assign
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
id|BTN_TOP2
)paren
suffix:semicolon
id|warrior-&gt;dev.relbit
(braket
l_int|0
)braket
op_assign
id|BIT
c_func
(paren
id|REL_DIAL
)paren
suffix:semicolon
id|warrior-&gt;dev.absbit
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
id|ABS_HAT0X
)paren
op_or
id|BIT
c_func
(paren
id|ABS_HAT0Y
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|warrior-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|init_input_dev
c_func
(paren
op_amp
id|warrior-&gt;dev
)paren
suffix:semicolon
id|warrior-&gt;dev.name
op_assign
id|warrior_name
suffix:semicolon
id|warrior-&gt;dev.phys
op_assign
id|warrior-&gt;phys
suffix:semicolon
id|warrior-&gt;dev.id.bustype
op_assign
id|BUS_RS232
suffix:semicolon
id|warrior-&gt;dev.id.vendor
op_assign
id|SERIO_WARRIOR
suffix:semicolon
id|warrior-&gt;dev.id.product
op_assign
l_int|0x0001
suffix:semicolon
id|warrior-&gt;dev.id.version
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
id|warrior-&gt;dev.absmax
(braket
id|ABS_X
op_plus
id|i
)braket
op_assign
op_minus
l_int|64
suffix:semicolon
id|warrior-&gt;dev.absmin
(braket
id|ABS_X
op_plus
id|i
)braket
op_assign
l_int|64
suffix:semicolon
id|warrior-&gt;dev.absflat
(braket
id|ABS_X
op_plus
id|i
)braket
op_assign
l_int|8
suffix:semicolon
)brace
id|warrior-&gt;dev.absmax
(braket
id|ABS_THROTTLE
)braket
op_assign
op_minus
l_int|112
suffix:semicolon
id|warrior-&gt;dev.absmin
(braket
id|ABS_THROTTLE
)braket
op_assign
l_int|112
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
id|warrior-&gt;dev.absmax
(braket
id|ABS_HAT0X
op_plus
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|warrior-&gt;dev.absmin
(braket
id|ABS_HAT0X
op_plus
id|i
)braket
op_assign
l_int|1
suffix:semicolon
)brace
id|warrior-&gt;dev
dot
r_private
op_assign
id|warrior
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|warrior
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
id|warrior
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|input_register_device
c_func
(paren
op_amp
id|warrior-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: Logitech WingMan Warrior on %s&bslash;n&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The serio device structure.&n; */
DECL|variable|warrior_dev
r_static
r_struct
id|serio_dev
id|warrior_dev
op_assign
(brace
dot
id|interrupt
op_assign
id|warrior_interrupt
comma
dot
id|connect
op_assign
id|warrior_connect
comma
dot
id|disconnect
op_assign
id|warrior_disconnect
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * The functions for inserting/removing us as a module.&n; */
DECL|function|warrior_init
r_int
id|__init
id|warrior_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_device
c_func
(paren
op_amp
id|warrior_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|warrior_exit
r_void
id|__exit
id|warrior_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_device
c_func
(paren
op_amp
id|warrior_dev
)paren
suffix:semicolon
)brace
DECL|variable|warrior_init
id|module_init
c_func
(paren
id|warrior_init
)paren
suffix:semicolon
DECL|variable|warrior_exit
id|module_exit
c_func
(paren
id|warrior_exit
)paren
suffix:semicolon
eof
