multiline_comment|/*&n; * $Id: twidjoy.c,v 1.5 2002/01/22 20:31:53 vojtech Exp $&n; *&n; *  derived from CVS-ID &quot;stinger.c,v 1.5 2001/05/29 12:57:18 vojtech Exp&quot;&n; *&n; *  Copyright (c) 2001 Arndt Schoenewald&n; *  Copyright (c) 2000-2001 Vojtech Pavlik&n; *  Copyright (c) 2000 Mark Fletcher&n; *&n; *  Sponsored by Quelltext AG (http://www.quelltext-ag.de), Dortmund, Germany&n; */
multiline_comment|/*&n; * Driver to use Handykey&squot;s Twiddler (the first edition, i.e. the one with&n; * the RS232 interface) as a joystick under Linux&n; *&n; * The Twiddler is a one-handed chording keyboard featuring twelve buttons on&n; * the front, six buttons on the top, and a built-in tilt sensor. The buttons&n; * on the front, which are grouped as four rows of three buttons, are pressed&n; * by the four fingers (this implies only one button per row can be held down&n; * at the same time) and the buttons on the top are for the thumb. The tilt&n; * sensor delivers X and Y axis data depending on how the Twiddler is held.&n; * Additional information can be found at http://www.handykey.com.&n; *&n; * This driver does not use the Twiddler for its intended purpose, i.e. as&n; * a chording keyboard, but as a joystick: pressing and releasing a button&n; * immediately sends a corresponding button event, and tilting it generates&n; * corresponding ABS_X and ABS_Y events. This turns the Twiddler into a game&n; * controller with amazing 18 buttons :-)&n; *&n; * Note: The Twiddler2 (the successor of the Twiddler that connects directly&n; * to the PS/2 keyboard and mouse ports) is NOT supported by this driver!&n; *&n; * For questions or feedback regarding this driver module please contact:&n; * Arndt Schoenewald &lt;arndt@quelltext.com&gt;&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
macro_line|#include &lt;linux/init.h&gt;
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Handykey Twiddler keyboard as a joystick driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
multiline_comment|/*&n; * Constants.&n; */
DECL|macro|TWIDJOY_MAX_LENGTH
mdefine_line|#define TWIDJOY_MAX_LENGTH 5
DECL|variable|twidjoy_name
r_static
r_char
op_star
id|twidjoy_name
op_assign
l_string|&quot;Handykey Twiddler&quot;
suffix:semicolon
DECL|struct|twidjoy_button_spec
r_static
r_struct
id|twidjoy_button_spec
(brace
DECL|member|bitshift
r_int
id|bitshift
suffix:semicolon
DECL|member|bitmask
r_int
id|bitmask
suffix:semicolon
DECL|member|buttons
r_int
id|buttons
(braket
l_int|3
)braket
suffix:semicolon
)brace
DECL|variable|twidjoy_buttons
id|twidjoy_buttons
(braket
)braket
op_assign
(brace
(brace
l_int|0
comma
l_int|3
comma
(brace
id|BTN_A
comma
id|BTN_B
comma
id|BTN_C
)brace
)brace
comma
(brace
l_int|2
comma
l_int|3
comma
(brace
id|BTN_X
comma
id|BTN_Y
comma
id|BTN_Z
)brace
)brace
comma
(brace
l_int|4
comma
l_int|3
comma
(brace
id|BTN_TL
comma
id|BTN_TR
comma
id|BTN_TR2
)brace
)brace
comma
(brace
l_int|6
comma
l_int|3
comma
(brace
id|BTN_SELECT
comma
id|BTN_START
comma
id|BTN_MODE
)brace
)brace
comma
(brace
l_int|8
comma
l_int|1
comma
(brace
id|BTN_BASE5
)brace
)brace
comma
(brace
l_int|9
comma
l_int|1
comma
(brace
id|BTN_BASE
)brace
)brace
comma
(brace
l_int|10
comma
l_int|1
comma
(brace
id|BTN_BASE3
)brace
)brace
comma
(brace
l_int|11
comma
l_int|1
comma
(brace
id|BTN_BASE4
)brace
)brace
comma
(brace
l_int|12
comma
l_int|1
comma
(brace
id|BTN_BASE2
)brace
)brace
comma
(brace
l_int|13
comma
l_int|1
comma
(brace
id|BTN_BASE6
)brace
)brace
comma
(brace
l_int|0
comma
l_int|0
comma
(brace
l_int|0
)brace
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * Per-Twiddler data.&n; */
DECL|struct|twidjoy
r_struct
id|twidjoy
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
id|TWIDJOY_MAX_LENGTH
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
multiline_comment|/*&n; * twidjoy_process_packet() decodes packets the driver receives from the&n; * Twiddler. It updates the data accordingly.&n; */
DECL|function|twidjoy_process_packet
r_static
r_void
id|twidjoy_process_packet
c_func
(paren
r_struct
id|twidjoy
op_star
id|twidjoy
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
id|twidjoy-&gt;idx
op_eq
id|TWIDJOY_MAX_LENGTH
)paren
(brace
r_struct
id|input_dev
op_star
id|dev
op_assign
op_amp
id|twidjoy-&gt;dev
suffix:semicolon
r_int
r_char
op_star
id|data
op_assign
id|twidjoy-&gt;data
suffix:semicolon
r_struct
id|twidjoy_button_spec
op_star
id|bp
suffix:semicolon
r_int
id|button_bits
comma
id|abs_x
comma
id|abs_y
suffix:semicolon
id|button_bits
op_assign
(paren
(paren
id|data
(braket
l_int|1
)braket
op_amp
l_int|0x7f
)paren
op_lshift
l_int|7
)paren
op_or
(paren
id|data
(braket
l_int|0
)braket
op_amp
l_int|0x7f
)paren
suffix:semicolon
id|input_regs
c_func
(paren
id|dev
comma
id|regs
)paren
suffix:semicolon
r_for
c_loop
(paren
id|bp
op_assign
id|twidjoy_buttons
suffix:semicolon
id|bp-&gt;bitmask
suffix:semicolon
id|bp
op_increment
)paren
(brace
r_int
id|value
op_assign
(paren
id|button_bits
op_amp
(paren
id|bp-&gt;bitmask
op_lshift
id|bp-&gt;bitshift
)paren
)paren
op_rshift
id|bp-&gt;bitshift
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
id|bp-&gt;bitmask
suffix:semicolon
id|i
op_increment
)paren
id|input_report_key
c_func
(paren
id|dev
comma
id|bp-&gt;buttons
(braket
id|i
)braket
comma
id|i
op_plus
l_int|1
op_eq
id|value
)paren
suffix:semicolon
)brace
id|abs_x
op_assign
(paren
(paren
id|data
(braket
l_int|4
)braket
op_amp
l_int|0x07
)paren
op_lshift
l_int|5
)paren
op_or
(paren
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|0x7C
)paren
op_rshift
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
l_int|4
)braket
op_amp
l_int|0x08
)paren
id|abs_x
op_sub_assign
l_int|256
suffix:semicolon
id|abs_y
op_assign
(paren
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|0x01
)paren
op_lshift
l_int|7
)paren
op_or
(paren
(paren
id|data
(braket
l_int|2
)braket
op_amp
l_int|0x7F
)paren
op_rshift
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|data
(braket
l_int|3
)braket
op_amp
l_int|0x02
)paren
id|abs_y
op_sub_assign
l_int|256
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
op_minus
id|abs_x
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_Y
comma
op_plus
id|abs_y
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; * twidjoy_interrupt() is called by the low level driver when characters&n; * are ready for us. We then buffer them for further processing, or call the&n; * packet processing routine.&n; */
DECL|function|twidjoy_interrupt
r_static
id|irqreturn_t
id|twidjoy_interrupt
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
id|twidjoy
op_star
id|twidjoy
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
multiline_comment|/* All Twiddler packets are 5 bytes. The fact that the first byte&n;&t; * has a MSB of 0 and all other bytes have a MSB of 1 can be used&n;&t; * to check and regain sync. */
r_if
c_cond
(paren
(paren
id|data
op_amp
l_int|0x80
)paren
op_eq
l_int|0
)paren
id|twidjoy-&gt;idx
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* this byte starts a new packet */
r_else
r_if
c_cond
(paren
id|twidjoy-&gt;idx
op_eq
l_int|0
)paren
r_return
id|IRQ_HANDLED
suffix:semicolon
multiline_comment|/* wrong MSB -- ignore this byte */
r_if
c_cond
(paren
id|twidjoy-&gt;idx
OL
id|TWIDJOY_MAX_LENGTH
)paren
id|twidjoy-&gt;data
(braket
id|twidjoy-&gt;idx
op_increment
)braket
op_assign
id|data
suffix:semicolon
r_if
c_cond
(paren
id|twidjoy-&gt;idx
op_eq
id|TWIDJOY_MAX_LENGTH
)paren
(brace
id|twidjoy_process_packet
c_func
(paren
id|twidjoy
comma
id|regs
)paren
suffix:semicolon
id|twidjoy-&gt;idx
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
multiline_comment|/*&n; * twidjoy_disconnect() is the opposite of twidjoy_connect()&n; */
DECL|function|twidjoy_disconnect
r_static
r_void
id|twidjoy_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|twidjoy
op_star
id|twidjoy
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|twidjoy-&gt;dev
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
id|twidjoy
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * twidjoy_connect() is the routine that is called when someone adds a&n; * new serio device. It looks for the Twiddler, and if found, registers&n; * it as an input device.&n; */
DECL|function|twidjoy_connect
r_static
r_void
id|twidjoy_connect
c_func
(paren
r_struct
id|serio
op_star
id|serio
comma
r_struct
id|serio_driver
op_star
id|drv
)paren
(brace
r_struct
id|twidjoy_button_spec
op_star
id|bp
suffix:semicolon
r_struct
id|twidjoy
op_star
id|twidjoy
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
id|SERIO_TWIDJOY
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|twidjoy
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|twidjoy
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
id|twidjoy
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|twidjoy
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|twidjoy-&gt;phys
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
id|twidjoy-&gt;dev
)paren
suffix:semicolon
id|twidjoy-&gt;dev.name
op_assign
id|twidjoy_name
suffix:semicolon
id|twidjoy-&gt;dev.phys
op_assign
id|twidjoy-&gt;phys
suffix:semicolon
id|twidjoy-&gt;dev.id.bustype
op_assign
id|BUS_RS232
suffix:semicolon
id|twidjoy-&gt;dev.id.vendor
op_assign
id|SERIO_TWIDJOY
suffix:semicolon
id|twidjoy-&gt;dev.id.product
op_assign
l_int|0x0001
suffix:semicolon
id|twidjoy-&gt;dev.id.version
op_assign
l_int|0x0100
suffix:semicolon
id|twidjoy-&gt;dev.dev
op_assign
op_amp
id|serio-&gt;dev
suffix:semicolon
id|twidjoy-&gt;dev.evbit
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
id|bp
op_assign
id|twidjoy_buttons
suffix:semicolon
id|bp-&gt;bitmask
suffix:semicolon
id|bp
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
id|bp-&gt;bitmask
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|bp-&gt;buttons
(braket
id|i
)braket
comma
id|twidjoy-&gt;dev.keybit
)paren
suffix:semicolon
)brace
id|twidjoy-&gt;dev.absbit
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
id|twidjoy-&gt;dev.absmax
(braket
id|ABS_X
op_plus
id|i
)braket
op_assign
l_int|50
suffix:semicolon
id|twidjoy-&gt;dev.absmin
(braket
id|ABS_X
op_plus
id|i
)braket
op_assign
op_minus
l_int|50
suffix:semicolon
multiline_comment|/* TODO: arndt 20010708: Are these values appropriate? */
id|twidjoy-&gt;dev.absfuzz
(braket
id|ABS_X
op_plus
id|i
)braket
op_assign
l_int|4
suffix:semicolon
id|twidjoy-&gt;dev.absflat
(braket
id|ABS_X
op_plus
id|i
)braket
op_assign
l_int|4
suffix:semicolon
)brace
id|twidjoy-&gt;dev
dot
r_private
op_assign
id|twidjoy
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|twidjoy
suffix:semicolon
r_if
c_cond
(paren
id|serio_open
c_func
(paren
id|serio
comma
id|drv
)paren
)paren
(brace
id|kfree
c_func
(paren
id|twidjoy
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|input_register_device
c_func
(paren
op_amp
id|twidjoy-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|twidjoy_name
comma
id|serio-&gt;phys
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The serio device structure.&n; */
DECL|variable|twidjoy_drv
r_static
r_struct
id|serio_driver
id|twidjoy_drv
op_assign
(brace
dot
id|driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;twidjoy&quot;
comma
)brace
comma
dot
id|description
op_assign
id|DRIVER_DESC
comma
dot
id|interrupt
op_assign
id|twidjoy_interrupt
comma
dot
id|connect
op_assign
id|twidjoy_connect
comma
dot
id|disconnect
op_assign
id|twidjoy_disconnect
comma
)brace
suffix:semicolon
multiline_comment|/*&n; * The functions for inserting/removing us as a module.&n; */
DECL|function|twidjoy_init
r_int
id|__init
id|twidjoy_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_driver
c_func
(paren
op_amp
id|twidjoy_drv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|twidjoy_exit
r_void
id|__exit
id|twidjoy_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_driver
c_func
(paren
op_amp
id|twidjoy_drv
)paren
suffix:semicolon
)brace
DECL|variable|twidjoy_init
id|module_init
c_func
(paren
id|twidjoy_init
)paren
suffix:semicolon
DECL|variable|twidjoy_exit
id|module_exit
c_func
(paren
id|twidjoy_exit
)paren
suffix:semicolon
eof
