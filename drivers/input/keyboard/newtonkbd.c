multiline_comment|/*&n; *  Copyright (c) 2000 Justin Cormack&n; */
multiline_comment|/*&n; * Newton keyboard driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;j.cormack@doc.ic.ac.uk&gt;, or by paper mail:&n; * Justin Cormack, 68 Dartmouth Park Road, London NW5 1SN, UK.&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Justin Cormack &lt;j.cormack@doc.ic.ac.uk&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Newton keyboard driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|NKBD_KEY
mdefine_line|#define NKBD_KEY&t;0x7f
DECL|macro|NKBD_PRESS
mdefine_line|#define NKBD_PRESS&t;0x80
DECL|variable|nkbd_keycode
r_static
r_int
r_char
id|nkbd_keycode
(braket
l_int|128
)braket
op_assign
(brace
id|KEY_A
comma
id|KEY_S
comma
id|KEY_D
comma
id|KEY_F
comma
id|KEY_H
comma
id|KEY_G
comma
id|KEY_Z
comma
id|KEY_X
comma
id|KEY_C
comma
id|KEY_V
comma
l_int|0
comma
id|KEY_B
comma
id|KEY_Q
comma
id|KEY_W
comma
id|KEY_E
comma
id|KEY_R
comma
id|KEY_Y
comma
id|KEY_T
comma
id|KEY_1
comma
id|KEY_2
comma
id|KEY_3
comma
id|KEY_4
comma
id|KEY_6
comma
id|KEY_5
comma
id|KEY_EQUAL
comma
id|KEY_9
comma
id|KEY_7
comma
id|KEY_MINUS
comma
id|KEY_8
comma
id|KEY_0
comma
id|KEY_RIGHTBRACE
comma
id|KEY_O
comma
id|KEY_U
comma
id|KEY_LEFTBRACE
comma
id|KEY_I
comma
id|KEY_P
comma
id|KEY_ENTER
comma
id|KEY_L
comma
id|KEY_J
comma
id|KEY_APOSTROPHE
comma
id|KEY_K
comma
id|KEY_SEMICOLON
comma
id|KEY_BACKSLASH
comma
id|KEY_COMMA
comma
id|KEY_SLASH
comma
id|KEY_N
comma
id|KEY_M
comma
id|KEY_DOT
comma
id|KEY_TAB
comma
id|KEY_SPACE
comma
id|KEY_GRAVE
comma
id|KEY_DELETE
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
id|KEY_LEFTMETA
comma
id|KEY_LEFTSHIFT
comma
id|KEY_CAPSLOCK
comma
id|KEY_LEFTALT
comma
id|KEY_LEFTCTRL
comma
id|KEY_RIGHTSHIFT
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
id|KEY_LEFT
comma
id|KEY_RIGHT
comma
id|KEY_DOWN
comma
id|KEY_UP
comma
l_int|0
)brace
suffix:semicolon
DECL|variable|nkbd_name
r_static
r_char
op_star
id|nkbd_name
op_assign
l_string|&quot;Newton Keyboard&quot;
suffix:semicolon
DECL|struct|nkbd
r_struct
id|nkbd
(brace
DECL|member|keycode
r_int
r_char
id|keycode
(braket
l_int|128
)braket
suffix:semicolon
DECL|member|dev
r_struct
id|input_dev
id|dev
suffix:semicolon
DECL|member|serio
r_struct
id|serio
op_star
id|serio
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
DECL|function|nkbd_interrupt
id|irqreturn_t
id|nkbd_interrupt
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
id|nkbd
op_star
id|nkbd
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
multiline_comment|/* invalid scan codes are probably the init sequence, so we ignore them */
r_if
c_cond
(paren
id|nkbd-&gt;keycode
(braket
id|data
op_amp
id|NKBD_KEY
)braket
)paren
(brace
id|input_regs
c_func
(paren
op_amp
id|nkbd-&gt;dev
comma
id|regs
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|nkbd-&gt;dev
comma
id|nkbd-&gt;keycode
(braket
id|data
op_amp
id|NKBD_KEY
)braket
comma
id|data
op_amp
id|NKBD_PRESS
)paren
suffix:semicolon
id|input_sync
c_func
(paren
op_amp
id|nkbd-&gt;dev
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|data
op_eq
l_int|0xe7
)paren
multiline_comment|/* end of init sequence */
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|nkbd_name
comma
id|serio-&gt;phys
)paren
suffix:semicolon
r_return
id|IRQ_HANDLED
suffix:semicolon
)brace
DECL|function|nkbd_connect
r_void
id|nkbd_connect
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
id|nkbd
op_star
id|nkbd
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
id|SERIO_NEWTON
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|nkbd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|nkbd
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
id|nkbd
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|nkbd
)paren
)paren
suffix:semicolon
id|nkbd-&gt;dev.evbit
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
id|EV_REP
)paren
suffix:semicolon
id|nkbd-&gt;serio
op_assign
id|serio
suffix:semicolon
id|init_input_dev
c_func
(paren
op_amp
id|nkbd-&gt;dev
)paren
suffix:semicolon
id|nkbd-&gt;dev.keycode
op_assign
id|nkbd-&gt;keycode
suffix:semicolon
id|nkbd-&gt;dev.keycodesize
op_assign
r_sizeof
(paren
r_int
r_char
)paren
suffix:semicolon
id|nkbd-&gt;dev.keycodemax
op_assign
id|ARRAY_SIZE
c_func
(paren
id|nkbd_keycode
)paren
suffix:semicolon
id|nkbd-&gt;dev
dot
r_private
op_assign
id|nkbd
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|nkbd
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
id|nkbd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|nkbd-&gt;keycode
comma
id|nkbd_keycode
comma
r_sizeof
(paren
id|nkbd-&gt;keycode
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
l_int|128
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|nkbd-&gt;keycode
(braket
id|i
)braket
comma
id|nkbd-&gt;dev.keybit
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
id|nkbd-&gt;dev.keybit
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|nkbd-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|nkbd-&gt;dev.name
op_assign
id|nkbd_name
suffix:semicolon
id|nkbd-&gt;dev.phys
op_assign
id|nkbd-&gt;phys
suffix:semicolon
id|nkbd-&gt;dev.id.bustype
op_assign
id|BUS_RS232
suffix:semicolon
id|nkbd-&gt;dev.id.vendor
op_assign
id|SERIO_NEWTON
suffix:semicolon
id|nkbd-&gt;dev.id.product
op_assign
l_int|0x0001
suffix:semicolon
id|nkbd-&gt;dev.id.version
op_assign
l_int|0x0100
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|nkbd-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|nkbd_name
comma
id|serio-&gt;phys
)paren
suffix:semicolon
)brace
DECL|function|nkbd_disconnect
r_void
id|nkbd_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|nkbd
op_star
id|nkbd
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|nkbd-&gt;dev
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
id|nkbd
)paren
suffix:semicolon
)brace
DECL|variable|nkbd_drv
r_struct
id|serio_driver
id|nkbd_drv
op_assign
(brace
dot
id|interrupt
op_assign
id|nkbd_interrupt
comma
dot
id|connect
op_assign
id|nkbd_connect
comma
dot
id|disconnect
op_assign
id|nkbd_disconnect
)brace
suffix:semicolon
DECL|function|nkbd_init
r_int
id|__init
id|nkbd_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_driver
c_func
(paren
op_amp
id|nkbd_drv
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|nkbd_exit
r_void
id|__exit
id|nkbd_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_driver
c_func
(paren
op_amp
id|nkbd_drv
)paren
suffix:semicolon
)brace
DECL|variable|nkbd_init
id|module_init
c_func
(paren
id|nkbd_init
)paren
suffix:semicolon
DECL|variable|nkbd_exit
id|module_exit
c_func
(paren
id|nkbd_exit
)paren
suffix:semicolon
eof
