multiline_comment|/*&n; * $Id: xtkbd.c,v 1.11 2001/09/25 10:12:07 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * XT keyboard driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/input.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/serio.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;XT keyboard driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|XTKBD_EMUL0
mdefine_line|#define XTKBD_EMUL0&t;0xe0
DECL|macro|XTKBD_EMUL1
mdefine_line|#define XTKBD_EMUL1&t;0xe1
DECL|macro|XTKBD_KEY
mdefine_line|#define XTKBD_KEY&t;0x7f
DECL|macro|XTKBD_RELEASE
mdefine_line|#define XTKBD_RELEASE&t;0x80
DECL|variable|xtkbd_keycode
r_static
r_int
r_char
id|xtkbd_keycode
(braket
l_int|256
)braket
op_assign
(brace
l_int|0
comma
l_int|1
comma
l_int|2
comma
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|6
comma
l_int|7
comma
l_int|8
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|12
comma
l_int|13
comma
l_int|14
comma
l_int|15
comma
l_int|16
comma
l_int|17
comma
l_int|18
comma
l_int|19
comma
l_int|20
comma
l_int|21
comma
l_int|22
comma
l_int|23
comma
l_int|24
comma
l_int|25
comma
l_int|26
comma
l_int|27
comma
l_int|28
comma
l_int|29
comma
l_int|30
comma
l_int|31
comma
l_int|32
comma
l_int|33
comma
l_int|34
comma
l_int|35
comma
l_int|36
comma
l_int|37
comma
l_int|38
comma
l_int|39
comma
l_int|40
comma
l_int|41
comma
l_int|42
comma
l_int|43
comma
l_int|44
comma
l_int|45
comma
l_int|46
comma
l_int|47
comma
l_int|48
comma
l_int|49
comma
l_int|50
comma
l_int|51
comma
l_int|52
comma
l_int|53
comma
l_int|54
comma
l_int|55
comma
l_int|56
comma
l_int|57
comma
l_int|58
comma
l_int|59
comma
l_int|60
comma
l_int|61
comma
l_int|62
comma
l_int|63
comma
l_int|64
comma
l_int|65
comma
l_int|66
comma
l_int|67
comma
l_int|68
comma
l_int|69
comma
l_int|70
comma
l_int|71
comma
l_int|72
comma
l_int|73
comma
l_int|74
comma
l_int|75
comma
l_int|76
comma
l_int|77
comma
l_int|78
comma
l_int|79
comma
l_int|80
comma
l_int|81
comma
l_int|82
comma
l_int|83
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|87
comma
l_int|88
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
l_int|87
comma
l_int|88
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|110
comma
l_int|111
comma
l_int|103
comma
l_int|108
comma
l_int|105
comma
l_int|106
)brace
suffix:semicolon
DECL|variable|xtkbd_name
r_static
r_char
op_star
id|xtkbd_name
op_assign
l_string|&quot;XT Keyboard&quot;
suffix:semicolon
DECL|struct|xtkbd
r_struct
id|xtkbd
(brace
DECL|member|keycode
r_int
r_char
id|keycode
(braket
l_int|256
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
DECL|function|xtkbd_interrupt
r_void
id|xtkbd_interrupt
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
id|xtkbd
op_star
id|xtkbd
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
r_switch
c_cond
(paren
id|data
)paren
(brace
r_case
id|XTKBD_EMUL0
suffix:colon
r_case
id|XTKBD_EMUL1
suffix:colon
r_return
suffix:semicolon
r_default
suffix:colon
(brace
)brace
r_if
c_cond
(paren
id|xtkbd-&gt;keycode
(braket
id|data
op_amp
id|XTKBD_KEY
)braket
)paren
(brace
id|input_regs
c_func
(paren
op_amp
id|xtkbd-&gt;dev
comma
id|regs
)paren
suffix:semicolon
id|input_report_key
c_func
(paren
op_amp
id|xtkbd-&gt;dev
comma
id|xtkbd-&gt;keycode
(braket
id|data
op_amp
id|XTKBD_KEY
)braket
comma
op_logical_neg
(paren
id|data
op_amp
id|XTKBD_RELEASE
)paren
)paren
suffix:semicolon
id|input_sync
c_func
(paren
op_amp
id|xtkbd-&gt;dev
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;xtkbd.c: Unknown key (scancode %#x) %s.&bslash;n&quot;
comma
id|data
op_amp
id|XTKBD_KEY
comma
id|data
op_amp
id|XTKBD_RELEASE
ques
c_cond
l_string|&quot;released&quot;
suffix:colon
l_string|&quot;pressed&quot;
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|xtkbd_connect
r_void
id|xtkbd_connect
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
id|xtkbd
op_star
id|xtkbd
suffix:semicolon
r_int
id|i
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
id|SERIO_XT
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|xtkbd
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|xtkbd
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
id|xtkbd
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|xtkbd
)paren
)paren
suffix:semicolon
id|xtkbd-&gt;dev.evbit
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
id|xtkbd-&gt;serio
op_assign
id|serio
suffix:semicolon
id|init_input_dev
c_func
(paren
op_amp
id|xtkbd-&gt;dev
)paren
suffix:semicolon
id|xtkbd-&gt;dev.keycode
op_assign
id|xtkbd-&gt;keycode
suffix:semicolon
id|xtkbd-&gt;dev.keycodesize
op_assign
r_sizeof
(paren
r_int
r_char
)paren
suffix:semicolon
id|xtkbd-&gt;dev.keycodemax
op_assign
id|ARRAY_SIZE
c_func
(paren
id|xtkbd_keycode
)paren
suffix:semicolon
id|xtkbd-&gt;dev
dot
r_private
op_assign
id|xtkbd
suffix:semicolon
id|serio
op_member_access_from_pointer
r_private
op_assign
id|xtkbd
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
id|xtkbd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|xtkbd-&gt;keycode
comma
id|xtkbd_keycode
comma
r_sizeof
(paren
id|xtkbd-&gt;keycode
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
l_int|255
suffix:semicolon
id|i
op_increment
)paren
id|set_bit
c_func
(paren
id|xtkbd-&gt;keycode
(braket
id|i
)braket
comma
id|xtkbd-&gt;dev.keybit
)paren
suffix:semicolon
id|clear_bit
c_func
(paren
l_int|0
comma
id|xtkbd-&gt;dev.keybit
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|xtkbd-&gt;phys
comma
l_string|&quot;%s/input0&quot;
comma
id|serio-&gt;phys
)paren
suffix:semicolon
id|xtkbd-&gt;dev.name
op_assign
id|xtkbd_name
suffix:semicolon
id|xtkbd-&gt;dev.phys
op_assign
id|xtkbd-&gt;phys
suffix:semicolon
id|xtkbd-&gt;dev.id.bustype
op_assign
id|BUS_XTKBD
suffix:semicolon
id|xtkbd-&gt;dev.id.vendor
op_assign
l_int|0x0001
suffix:semicolon
id|xtkbd-&gt;dev.id.product
op_assign
l_int|0x0001
suffix:semicolon
id|xtkbd-&gt;dev.id.version
op_assign
l_int|0x0100
suffix:semicolon
id|input_register_device
c_func
(paren
op_amp
id|xtkbd-&gt;dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;input: %s on %s&bslash;n&quot;
comma
id|xtkbd_name
comma
id|serio-&gt;phys
)paren
suffix:semicolon
)brace
DECL|function|xtkbd_disconnect
r_void
id|xtkbd_disconnect
c_func
(paren
r_struct
id|serio
op_star
id|serio
)paren
(brace
r_struct
id|xtkbd
op_star
id|xtkbd
op_assign
id|serio
op_member_access_from_pointer
r_private
suffix:semicolon
id|input_unregister_device
c_func
(paren
op_amp
id|xtkbd-&gt;dev
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
id|xtkbd
)paren
suffix:semicolon
)brace
DECL|variable|xtkbd_dev
r_struct
id|serio_dev
id|xtkbd_dev
op_assign
(brace
dot
id|interrupt
op_assign
id|xtkbd_interrupt
comma
dot
id|connect
op_assign
id|xtkbd_connect
comma
dot
id|disconnect
op_assign
id|xtkbd_disconnect
)brace
suffix:semicolon
DECL|function|xtkbd_init
r_int
id|__init
id|xtkbd_init
c_func
(paren
r_void
)paren
(brace
id|serio_register_device
c_func
(paren
op_amp
id|xtkbd_dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|xtkbd_exit
r_void
id|__exit
id|xtkbd_exit
c_func
(paren
r_void
)paren
(brace
id|serio_unregister_device
c_func
(paren
op_amp
id|xtkbd_dev
)paren
suffix:semicolon
)brace
DECL|variable|xtkbd_init
id|module_init
c_func
(paren
id|xtkbd_init
)paren
suffix:semicolon
DECL|variable|xtkbd_exit
id|module_exit
c_func
(paren
id|xtkbd_exit
)paren
suffix:semicolon
eof
