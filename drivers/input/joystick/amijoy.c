multiline_comment|/*&n; * $Id: amijoy.c,v 1.13 2002/01/22 20:26:32 vojtech Exp $&n; *&n; *  Copyright (c) 1998-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * Driver for Amiga joysticks for Linux/m68k&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/amigahw.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for Amiga joysticks&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|amijoy
comma
l_string|&quot;1-2i&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|amijoy
r_static
r_int
id|amijoy
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|1
)brace
suffix:semicolon
DECL|variable|amijoy_used
r_static
r_int
id|amijoy_used
(braket
l_int|2
)braket
op_assign
(brace
l_int|0
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|amijoy_dev
r_static
r_struct
id|input_dev
id|amijoy_dev
(braket
l_int|2
)braket
suffix:semicolon
DECL|variable|amijoy_phys
r_static
r_char
op_star
id|amijoy_phys
(braket
l_int|2
)braket
op_assign
(brace
l_string|&quot;amijoy/input0&quot;
comma
l_string|&quot;amijoy/input1&quot;
)brace
suffix:semicolon
DECL|variable|amijoy_name
r_static
r_char
op_star
id|amijoy_name
op_assign
l_string|&quot;Amiga joystick&quot;
suffix:semicolon
DECL|function|amijoy_interrupt
r_static
r_void
id|amijoy_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dummy
comma
r_struct
id|pt_regs
op_star
id|fp
)paren
(brace
r_int
id|i
comma
id|data
op_assign
l_int|0
comma
id|button
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
r_if
c_cond
(paren
id|amijoy
(braket
id|i
)braket
)paren
(brace
r_switch
c_cond
(paren
id|i
)paren
(brace
r_case
l_int|0
suffix:colon
id|data
op_assign
op_complement
id|custom.joy0dat
suffix:semicolon
id|button
op_assign
(paren
op_complement
id|ciaa.pra
op_rshift
l_int|6
)paren
op_amp
l_int|1
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|1
suffix:colon
id|data
op_assign
op_complement
id|custom.joy1dat
suffix:semicolon
id|button
op_assign
(paren
op_complement
id|ciaa.pra
op_rshift
l_int|7
)paren
op_amp
l_int|1
suffix:semicolon
r_break
suffix:semicolon
)brace
id|input_report_key
c_func
(paren
id|amijoy_dev
op_plus
id|i
comma
id|BTN_TRIGGER
comma
id|button
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|amijoy_dev
op_plus
id|i
comma
id|ABS_X
comma
(paren
(paren
id|data
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
op_rshift
l_int|9
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|data
op_assign
op_complement
(paren
id|data
op_xor
(paren
id|data
op_lshift
l_int|1
)paren
)paren
suffix:semicolon
id|input_report_abs
c_func
(paren
id|amijoy_dev
op_plus
id|i
comma
id|ABS_Y
comma
(paren
(paren
id|data
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
op_rshift
l_int|9
)paren
op_amp
l_int|1
)paren
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|amijoy_dev
op_plus
id|i
)paren
suffix:semicolon
)brace
)brace
DECL|function|amijoy_open
r_static
r_int
id|amijoy_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_int
op_star
id|used
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
(paren
op_star
id|used
)paren
op_increment
)paren
r_return
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|IRQ_AMIGA_VERTB
comma
id|amijoy_interrupt
comma
l_int|0
comma
l_string|&quot;amijoy&quot;
comma
l_int|NULL
)paren
)paren
(brace
(paren
op_star
id|used
)paren
op_decrement
suffix:semicolon
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;amijoy.c: Can&squot;t allocate irq %d&bslash;n&quot;
comma
id|amijoy_irq
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amijoy_close
r_static
r_void
id|amijoy_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_int
op_star
id|used
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
(paren
op_star
id|used
)paren
)paren
id|free_irq
c_func
(paren
id|IRQ_AMIGA_VERTB
comma
id|amijoy_interrupt
)paren
suffix:semicolon
)brace
DECL|function|amijoy_setup
r_static
r_int
id|__init
id|amijoy_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|ints
(braket
l_int|4
)braket
id|str
op_assign
id|get_options
c_func
(paren
id|str
comma
id|ARRAY_SIZE
c_func
(paren
id|ints
)paren
comma
id|ints
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
op_le
id|ints
(braket
l_int|0
)braket
op_logical_and
id|i
OL
l_int|2
suffix:semicolon
id|i
op_increment
)paren
id|amijoy
(braket
id|i
)braket
op_assign
id|ints
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|__setup
c_func
(paren
l_string|&quot;amijoy=&quot;
comma
id|amijoy_setup
)paren
suffix:semicolon
DECL|function|amijoy_init
r_static
r_int
id|__init
id|amijoy_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
comma
id|j
suffix:semicolon
id|init_timer
c_func
(paren
id|amijoy_timer
)paren
suffix:semicolon
id|port-&gt;timer.function
op_assign
id|amijoy_timer
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
id|amijoy
(braket
id|i
)braket
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_mem_region
c_func
(paren
id|CUSTOM_PHYSADDR
op_plus
l_int|10
op_plus
id|i
op_star
l_int|2
comma
l_int|2
comma
l_string|&quot;amijoy [Denise]&quot;
)paren
)paren
(brace
r_if
c_cond
(paren
id|i
op_eq
l_int|1
op_logical_and
id|amijoy
(braket
l_int|0
)braket
)paren
(brace
id|input_unregister_device
c_func
(paren
id|amijoy_dev
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|CUSTOM_PHYSADDR
op_plus
l_int|10
comma
l_int|2
)paren
suffix:semicolon
)brace
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|amijoy_dev
(braket
id|i
)braket
dot
id|open
op_assign
id|amijoy_open
suffix:semicolon
id|amijoy_dev
(braket
id|i
)braket
dot
id|close
op_assign
id|amijoy_close
suffix:semicolon
id|amijoy_dev
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
id|amijoy_dev
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
id|amijoy_dev
(braket
id|i
)braket
dot
id|keybit
(braket
id|LONG
c_func
(paren
id|BTN_LEFT
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
id|BTN_MIDDLE
)paren
op_or
id|BIT
c_func
(paren
id|BTN_RIGHT
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
l_int|2
suffix:semicolon
id|j
op_increment
)paren
(brace
id|amijoy_dev
(braket
id|i
)braket
dot
id|absmin
(braket
id|ABS_X
op_plus
id|j
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
id|amijoy_dev
(braket
id|i
)braket
dot
id|absmax
(braket
id|ABS_X
op_plus
id|j
)braket
op_assign
l_int|1
suffix:semicolon
)brace
id|amijoy-&gt;dev
(braket
id|i
)braket
dot
id|name
op_assign
id|amijoy_name
suffix:semicolon
id|amijoy-&gt;dev
(braket
id|i
)braket
dot
id|phys
op_assign
id|amijoy_phys
(braket
id|i
)braket
suffix:semicolon
id|amijoy-&gt;dev
(braket
id|i
)braket
dot
id|id.bustype
op_assign
id|BUS_AMIGA
suffix:semicolon
id|amijoy-&gt;dev
(braket
id|i
)braket
dot
id|id.vendor
op_assign
l_int|0x0001
suffix:semicolon
id|amijoy-&gt;dev
(braket
id|i
)braket
dot
id|id.product
op_assign
l_int|0x0003
suffix:semicolon
id|amijoy-&gt;dev
(braket
id|i
)braket
dot
id|id.version
op_assign
l_int|0x0100
suffix:semicolon
id|amijoy_dev
(braket
id|i
)braket
dot
r_private
op_assign
id|amijoy_used
op_plus
id|i
suffix:semicolon
id|input_register_device
c_func
(paren
id|amijoy_dev
op_plus
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s at joy%ddat&bslash;n&quot;
comma
id|amijoy_name
comma
id|i
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|amijoy_exit
r_static
r_void
id|_exit
id|amijoy_exit
c_func
(paren
r_void
)paren
(brace
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
id|amijoy
(braket
id|i
)braket
)paren
(brace
id|input_unregister_device
c_func
(paren
id|amijoy_dev
op_plus
id|i
)paren
suffix:semicolon
id|release_mem_region
c_func
(paren
id|CUSTOM_PHYSADDR
op_plus
l_int|10
op_plus
id|i
op_star
l_int|2
comma
l_int|2
)paren
suffix:semicolon
)brace
)brace
DECL|variable|amijoy_init
id|module_init
c_func
(paren
id|amijoy_init
)paren
suffix:semicolon
DECL|variable|amijoy_exit
id|module_exit
c_func
(paren
id|amijoy_exit
)paren
suffix:semicolon
eof
