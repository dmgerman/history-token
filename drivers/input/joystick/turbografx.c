multiline_comment|/*&n; * $Id: turbografx.c,v 1.14 2002/01/22 20:30:39 vojtech Exp $&n; *&n; *  Copyright (c) 1998-2001 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *&t;Steffen Schwenke&n; */
multiline_comment|/*&n; * TurboGraFX parallel port interface driver for Linux.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/module.h&gt;
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
l_string|&quot;TurboGraFX parallel port interface driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|tgfx
comma
l_string|&quot;2-8i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|tgfx_2
comma
l_string|&quot;2-8i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|tgfx_3
comma
l_string|&quot;2-8i&quot;
)paren
suffix:semicolon
DECL|macro|TGFX_REFRESH_TIME
mdefine_line|#define TGFX_REFRESH_TIME&t;HZ/100&t;/* 10 ms */
DECL|macro|TGFX_TRIGGER
mdefine_line|#define TGFX_TRIGGER&t;&t;0x08
DECL|macro|TGFX_UP
mdefine_line|#define TGFX_UP&t;&t;&t;0x10
DECL|macro|TGFX_DOWN
mdefine_line|#define TGFX_DOWN&t;&t;0x20&t;
DECL|macro|TGFX_LEFT
mdefine_line|#define TGFX_LEFT&t;&t;0x40
DECL|macro|TGFX_RIGHT
mdefine_line|#define TGFX_RIGHT&t;&t;0x80
DECL|macro|TGFX_THUMB
mdefine_line|#define TGFX_THUMB&t;&t;0x02
DECL|macro|TGFX_THUMB2
mdefine_line|#define TGFX_THUMB2&t;&t;0x04
DECL|macro|TGFX_TOP
mdefine_line|#define TGFX_TOP&t;&t;0x01
DECL|macro|TGFX_TOP2
mdefine_line|#define TGFX_TOP2&t;&t;0x08
DECL|variable|__initdata
r_static
r_int
id|tgfx
(braket
)braket
id|__initdata
op_assign
(brace
op_minus
l_int|1
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
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|tgfx_2
(braket
)braket
id|__initdata
op_assign
(brace
op_minus
l_int|1
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
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|tgfx_3
(braket
)braket
id|__initdata
op_assign
(brace
op_minus
l_int|1
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
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|tgfx_buttons
r_static
r_int
id|tgfx_buttons
(braket
)braket
op_assign
(brace
id|BTN_TRIGGER
comma
id|BTN_THUMB
comma
id|BTN_THUMB2
comma
id|BTN_TOP
comma
id|BTN_TOP2
)brace
suffix:semicolon
DECL|variable|tgfx_name
r_static
r_char
op_star
id|tgfx_name
op_assign
l_string|&quot;TurboGraFX Multisystem joystick&quot;
suffix:semicolon
DECL|struct|tgfx
r_struct
id|tgfx
(brace
DECL|member|pd
r_struct
id|pardevice
op_star
id|pd
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
l_int|7
)braket
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|7
)braket
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|sticks
r_int
id|sticks
suffix:semicolon
DECL|member|used
r_int
id|used
suffix:semicolon
DECL|variable|tgfx_base
)brace
op_star
id|tgfx_base
(braket
l_int|3
)braket
suffix:semicolon
multiline_comment|/*&n; * tgfx_timer() reads and analyzes TurboGraFX joystick data.&n; */
DECL|function|tgfx_timer
r_static
r_void
id|tgfx_timer
c_func
(paren
r_int
r_int
r_private
)paren
(brace
r_struct
id|tgfx
op_star
id|tgfx
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
id|data1
comma
id|data2
comma
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
l_int|7
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|tgfx-&gt;sticks
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
id|tgfx-&gt;dev
op_plus
id|i
suffix:semicolon
id|parport_write_data
c_func
(paren
id|tgfx-&gt;pd-&gt;port
comma
op_complement
(paren
l_int|1
op_lshift
id|i
)paren
)paren
suffix:semicolon
id|data1
op_assign
id|parport_read_status
c_func
(paren
id|tgfx-&gt;pd-&gt;port
)paren
op_xor
l_int|0x7f
suffix:semicolon
id|data2
op_assign
id|parport_read_control
c_func
(paren
id|tgfx-&gt;pd-&gt;port
)paren
op_xor
l_int|0x04
suffix:semicolon
multiline_comment|/* CAVEAT parport */
id|input_report_abs
c_func
(paren
id|dev
comma
id|ABS_X
comma
op_logical_neg
op_logical_neg
(paren
id|data1
op_amp
id|TGFX_RIGHT
)paren
op_minus
op_logical_neg
op_logical_neg
(paren
id|data1
op_amp
id|TGFX_LEFT
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
op_logical_neg
op_logical_neg
(paren
id|data1
op_amp
id|TGFX_DOWN
)paren
op_minus
op_logical_neg
op_logical_neg
(paren
id|data1
op_amp
id|TGFX_UP
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
(paren
id|data1
op_amp
id|TGFX_TRIGGER
)paren
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
id|data2
op_amp
id|TGFX_THUMB
)paren
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
id|dev
comma
id|BTN_THUMB2
comma
(paren
id|data2
op_amp
id|TGFX_THUMB2
)paren
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
id|data2
op_amp
id|TGFX_TOP
)paren
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
id|data2
op_amp
id|TGFX_TOP2
)paren
)paren
suffix:semicolon
id|input_sync
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
id|mod_timer
c_func
(paren
op_amp
id|tgfx-&gt;timer
comma
id|jiffies
op_plus
id|TGFX_REFRESH_TIME
)paren
suffix:semicolon
)brace
DECL|function|tgfx_open
r_static
r_int
id|tgfx_open
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|tgfx
op_star
id|tgfx
op_assign
id|dev
op_member_access_from_pointer
r_private
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tgfx-&gt;used
op_increment
)paren
(brace
id|parport_claim
c_func
(paren
id|tgfx-&gt;pd
)paren
suffix:semicolon
id|parport_write_control
c_func
(paren
id|tgfx-&gt;pd-&gt;port
comma
l_int|0x04
)paren
suffix:semicolon
id|mod_timer
c_func
(paren
op_amp
id|tgfx-&gt;timer
comma
id|jiffies
op_plus
id|TGFX_REFRESH_TIME
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|tgfx_close
r_static
r_void
id|tgfx_close
c_func
(paren
r_struct
id|input_dev
op_star
id|dev
)paren
(brace
r_struct
id|tgfx
op_star
id|tgfx
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
id|tgfx-&gt;used
)paren
(brace
id|del_timer
c_func
(paren
op_amp
id|tgfx-&gt;timer
)paren
suffix:semicolon
id|parport_write_control
c_func
(paren
id|tgfx-&gt;pd-&gt;port
comma
l_int|0x00
)paren
suffix:semicolon
id|parport_release
c_func
(paren
id|tgfx-&gt;pd
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * tgfx_probe() probes for tg gamepads.&n; */
DECL|function|tgfx_probe
r_static
r_struct
id|tgfx
id|__init
op_star
id|tgfx_probe
c_func
(paren
r_int
op_star
id|config
)paren
(brace
r_struct
id|tgfx
op_star
id|tgfx
suffix:semicolon
r_struct
id|parport
op_star
id|pp
suffix:semicolon
r_int
id|i
comma
id|j
suffix:semicolon
r_if
c_cond
(paren
id|config
(braket
l_int|0
)braket
OL
l_int|0
)paren
r_return
l_int|NULL
suffix:semicolon
r_for
c_loop
(paren
id|pp
op_assign
id|parport_enumerate
c_func
(paren
)paren
suffix:semicolon
id|pp
op_logical_and
(paren
id|config
(braket
l_int|0
)braket
OG
l_int|0
)paren
suffix:semicolon
id|pp
op_assign
id|pp-&gt;next
)paren
id|config
(braket
l_int|0
)braket
op_decrement
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pp
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;turbografx.c: no such parport&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|tgfx
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|tgfx
)paren
comma
id|GFP_KERNEL
)paren
)paren
)paren
r_return
l_int|NULL
suffix:semicolon
id|memset
c_func
(paren
id|tgfx
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|tgfx
)paren
)paren
suffix:semicolon
id|tgfx-&gt;pd
op_assign
id|parport_register_device
c_func
(paren
id|pp
comma
l_string|&quot;turbografx&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
l_int|NULL
comma
id|PARPORT_DEV_EXCL
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tgfx-&gt;pd
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;turbografx.c: parport busy already - lp.o loaded?&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tgfx
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|init_timer
c_func
(paren
op_amp
id|tgfx-&gt;timer
)paren
suffix:semicolon
id|tgfx-&gt;timer.data
op_assign
(paren
r_int
)paren
id|tgfx
suffix:semicolon
id|tgfx-&gt;timer.function
op_assign
id|tgfx_timer
suffix:semicolon
id|tgfx-&gt;sticks
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
l_int|7
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|config
(braket
id|i
op_plus
l_int|1
)braket
OG
l_int|0
op_logical_and
id|config
(braket
id|i
op_plus
l_int|1
)braket
OL
l_int|6
)paren
(brace
id|tgfx-&gt;sticks
op_or_assign
(paren
l_int|1
op_lshift
id|i
)paren
suffix:semicolon
id|tgfx-&gt;dev
(braket
id|i
)braket
dot
r_private
op_assign
id|tgfx
suffix:semicolon
id|tgfx-&gt;dev
(braket
id|i
)braket
dot
id|open
op_assign
id|tgfx_open
suffix:semicolon
id|tgfx-&gt;dev
(braket
id|i
)braket
dot
id|close
op_assign
id|tgfx_close
suffix:semicolon
id|sprintf
c_func
(paren
id|tgfx-&gt;phys
(braket
id|i
)braket
comma
l_string|&quot;%s/input0&quot;
comma
id|tgfx-&gt;pd-&gt;port-&gt;name
)paren
suffix:semicolon
id|tgfx-&gt;dev
(braket
id|i
)braket
dot
id|name
op_assign
id|tgfx_name
suffix:semicolon
id|tgfx-&gt;dev
(braket
id|i
)braket
dot
id|phys
op_assign
id|tgfx-&gt;phys
(braket
id|i
)braket
suffix:semicolon
id|tgfx-&gt;dev
(braket
id|i
)braket
dot
id|id.bustype
op_assign
id|BUS_PARPORT
suffix:semicolon
id|tgfx-&gt;dev
(braket
id|i
)braket
dot
id|id.vendor
op_assign
l_int|0x0003
suffix:semicolon
id|tgfx-&gt;dev
(braket
id|i
)braket
dot
id|id.product
op_assign
id|config
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|tgfx-&gt;dev
(braket
id|i
)braket
dot
id|id.version
op_assign
l_int|0x0100
suffix:semicolon
id|tgfx-&gt;dev
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
id|tgfx-&gt;dev
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
id|j
OL
id|config
(braket
id|i
op_plus
l_int|1
)braket
suffix:semicolon
id|j
op_increment
)paren
id|set_bit
c_func
(paren
id|tgfx_buttons
(braket
id|j
)braket
comma
id|tgfx-&gt;dev
(braket
id|i
)braket
dot
id|keybit
)paren
suffix:semicolon
id|tgfx-&gt;dev
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
id|tgfx-&gt;dev
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
id|tgfx-&gt;dev
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
id|tgfx-&gt;dev
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
id|tgfx-&gt;dev
op_plus
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %d-button Multisystem joystick on %s&bslash;n&quot;
comma
id|config
(braket
id|i
op_plus
l_int|1
)braket
comma
id|tgfx-&gt;pd-&gt;port-&gt;name
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|tgfx-&gt;sticks
)paren
(brace
id|parport_unregister_device
c_func
(paren
id|tgfx-&gt;pd
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|tgfx
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|tgfx
suffix:semicolon
)brace
macro_line|#ifndef MODULE
DECL|function|tgfx_setup
r_static
r_int
id|__init
id|tgfx_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|i
comma
id|ints
(braket
l_int|9
)braket
suffix:semicolon
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|tgfx
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
DECL|function|tgfx_setup_2
r_static
r_int
id|__init
id|tgfx_setup_2
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|i
comma
id|ints
(braket
l_int|9
)braket
suffix:semicolon
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|tgfx_2
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
DECL|function|tgfx_setup_3
r_static
r_int
id|__init
id|tgfx_setup_3
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_int
id|i
comma
id|ints
(braket
l_int|9
)braket
suffix:semicolon
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
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|tgfx_3
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
l_string|&quot;tgfx=&quot;
comma
id|tgfx_setup
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;tgfx_2=&quot;
comma
id|tgfx_setup_2
)paren
suffix:semicolon
id|__setup
c_func
(paren
l_string|&quot;tgfx_3=&quot;
comma
id|tgfx_setup_3
)paren
suffix:semicolon
macro_line|#endif
DECL|function|tgfx_init
r_int
id|__init
id|tgfx_init
c_func
(paren
r_void
)paren
(brace
id|tgfx_base
(braket
l_int|0
)braket
op_assign
id|tgfx_probe
c_func
(paren
id|tgfx
)paren
suffix:semicolon
id|tgfx_base
(braket
l_int|1
)braket
op_assign
id|tgfx_probe
c_func
(paren
id|tgfx_2
)paren
suffix:semicolon
id|tgfx_base
(braket
l_int|2
)braket
op_assign
id|tgfx_probe
c_func
(paren
id|tgfx_3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tgfx_base
(braket
l_int|0
)braket
op_logical_or
id|tgfx_base
(braket
l_int|1
)braket
op_logical_or
id|tgfx_base
(braket
l_int|2
)braket
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|tgfx_exit
r_void
id|__exit
id|tgfx_exit
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
r_if
c_cond
(paren
id|tgfx_base
(braket
id|i
)braket
)paren
(brace
r_for
c_loop
(paren
id|j
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|7
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|tgfx_base
(braket
id|i
)braket
op_member_access_from_pointer
id|sticks
op_amp
(paren
l_int|1
op_lshift
id|j
)paren
)paren
id|input_unregister_device
c_func
(paren
id|tgfx_base
(braket
id|i
)braket
op_member_access_from_pointer
id|dev
op_plus
id|j
)paren
suffix:semicolon
id|parport_unregister_device
c_func
(paren
id|tgfx_base
(braket
id|i
)braket
op_member_access_from_pointer
id|pd
)paren
suffix:semicolon
)brace
)brace
DECL|variable|tgfx_init
id|module_init
c_func
(paren
id|tgfx_init
)paren
suffix:semicolon
DECL|variable|tgfx_exit
id|module_exit
c_func
(paren
id|tgfx_exit
)paren
suffix:semicolon
eof
