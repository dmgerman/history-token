multiline_comment|/*&n; * $Id: lightning.c,v 1.20 2002/01/22 20:41:31 vojtech Exp $&n; *&n; *  Copyright (c) 1998-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * PDPI Lightning 4 gamecard driver for Linux.&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
DECL|macro|L4_PORT
mdefine_line|#define L4_PORT&t;&t;&t;0x201
DECL|macro|L4_SELECT_ANALOG
mdefine_line|#define L4_SELECT_ANALOG&t;0xa4
DECL|macro|L4_SELECT_DIGITAL
mdefine_line|#define L4_SELECT_DIGITAL&t;0xa5
DECL|macro|L4_SELECT_SECONDARY
mdefine_line|#define L4_SELECT_SECONDARY&t;0xa6
DECL|macro|L4_CMD_ID
mdefine_line|#define L4_CMD_ID&t;&t;0x80
DECL|macro|L4_CMD_GETCAL
mdefine_line|#define L4_CMD_GETCAL&t;&t;0x92
DECL|macro|L4_CMD_SETCAL
mdefine_line|#define L4_CMD_SETCAL&t;&t;0x93
DECL|macro|L4_ID
mdefine_line|#define L4_ID&t;&t;&t;0x04
DECL|macro|L4_BUSY
mdefine_line|#define L4_BUSY&t;&t;&t;0x01
DECL|macro|L4_TIMEOUT
mdefine_line|#define L4_TIMEOUT&t;&t;80&t;/* 80 us */
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;PDPI Lightning 4 gamecard driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|struct|l4
r_struct
id|l4
(brace
DECL|member|gameport
r_struct
id|gameport
id|gameport
suffix:semicolon
DECL|member|port
r_int
r_char
id|port
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
DECL|variable|l4_port
)brace
op_star
id|l4_port
(braket
l_int|8
)braket
suffix:semicolon
DECL|variable|l4_name
r_char
id|l4_name
(braket
)braket
op_assign
l_string|&quot;PDPI Lightning 4&quot;
suffix:semicolon
multiline_comment|/*&n; * l4_wait_ready() waits for the L4 to become ready.&n; */
DECL|function|l4_wait_ready
r_static
r_int
id|l4_wait_ready
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|t
suffix:semicolon
id|t
op_assign
id|L4_TIMEOUT
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|L4_PORT
)paren
op_amp
id|L4_BUSY
)paren
op_logical_and
id|t
OG
l_int|0
)paren
id|t
op_decrement
suffix:semicolon
r_return
op_minus
(paren
id|t
op_le
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * l4_cooked_read() reads data from the Lightning 4.&n; */
DECL|function|l4_cooked_read
r_static
r_int
id|l4_cooked_read
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
op_star
id|axes
comma
r_int
op_star
id|buttons
)paren
(brace
r_struct
id|l4
op_star
id|l4
op_assign
id|gameport-&gt;driver
suffix:semicolon
r_int
r_char
id|status
suffix:semicolon
r_int
id|i
comma
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|L4_SELECT_ANALOG
comma
id|L4_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|L4_SELECT_DIGITAL
op_plus
(paren
id|l4-&gt;port
op_rshift
l_int|2
)paren
comma
id|L4_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|L4_PORT
)paren
op_amp
id|L4_BUSY
)paren
r_goto
id|fail
suffix:semicolon
id|outb
c_func
(paren
id|l4-&gt;port
op_amp
l_int|3
comma
id|L4_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|L4_PORT
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
r_if
c_cond
(paren
id|status
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
(brace
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|axes
(braket
id|i
)braket
op_assign
id|inb
c_func
(paren
id|L4_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|axes
(braket
id|i
)braket
OG
l_int|252
)paren
id|axes
(braket
id|i
)braket
op_assign
op_minus
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
l_int|0x10
)paren
(brace
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
op_star
id|buttons
op_assign
id|inb
c_func
(paren
id|L4_PORT
)paren
op_amp
l_int|0x0f
suffix:semicolon
)brace
id|result
op_assign
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|outb
c_func
(paren
id|L4_SELECT_ANALOG
comma
id|L4_PORT
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
DECL|function|l4_open
r_static
r_int
id|l4_open
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
id|mode
)paren
(brace
r_struct
id|l4
op_star
id|l4
op_assign
id|gameport-&gt;driver
suffix:semicolon
r_if
c_cond
(paren
id|l4-&gt;port
op_ne
l_int|0
op_logical_and
id|mode
op_ne
id|GAMEPORT_MODE_COOKED
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|L4_SELECT_ANALOG
comma
id|L4_PORT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * l4_getcal() reads the L4 with calibration values.&n; */
DECL|function|l4_getcal
r_static
r_int
id|l4_getcal
c_func
(paren
r_int
id|port
comma
r_int
op_star
id|cal
)paren
(brace
r_int
id|i
comma
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|L4_SELECT_ANALOG
comma
id|L4_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|L4_SELECT_DIGITAL
op_plus
(paren
id|port
op_rshift
l_int|2
)paren
comma
id|L4_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|L4_PORT
)paren
op_amp
id|L4_BUSY
)paren
r_goto
id|fail
suffix:semicolon
id|outb
c_func
(paren
id|L4_CMD_GETCAL
comma
id|L4_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|L4_PORT
)paren
op_ne
id|L4_SELECT_DIGITAL
op_plus
(paren
id|port
op_rshift
l_int|2
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|outb
c_func
(paren
id|port
op_amp
l_int|3
comma
id|L4_PORT
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
(brace
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|cal
(braket
id|i
)braket
op_assign
id|inb
c_func
(paren
id|L4_PORT
)paren
suffix:semicolon
)brace
id|result
op_assign
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|outb
c_func
(paren
id|L4_SELECT_ANALOG
comma
id|L4_PORT
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * l4_setcal() programs the L4 with calibration values.&n; */
DECL|function|l4_setcal
r_static
r_int
id|l4_setcal
c_func
(paren
r_int
id|port
comma
r_int
op_star
id|cal
)paren
(brace
r_int
id|i
comma
id|result
op_assign
op_minus
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|L4_SELECT_ANALOG
comma
id|L4_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|L4_SELECT_DIGITAL
op_plus
(paren
id|port
op_rshift
l_int|2
)paren
comma
id|L4_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|L4_PORT
)paren
op_amp
id|L4_BUSY
)paren
r_goto
id|fail
suffix:semicolon
id|outb
c_func
(paren
id|L4_CMD_SETCAL
comma
id|L4_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|L4_PORT
)paren
op_ne
id|L4_SELECT_DIGITAL
op_plus
(paren
id|port
op_rshift
l_int|2
)paren
)paren
r_goto
id|fail
suffix:semicolon
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|outb
c_func
(paren
id|port
op_amp
l_int|3
comma
id|L4_PORT
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
(brace
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_goto
id|fail
suffix:semicolon
id|outb
c_func
(paren
id|cal
(braket
id|i
)braket
comma
id|L4_PORT
)paren
suffix:semicolon
)brace
id|result
op_assign
l_int|0
suffix:semicolon
id|fail
suffix:colon
id|outb
c_func
(paren
id|L4_SELECT_ANALOG
comma
id|L4_PORT
)paren
suffix:semicolon
r_return
id|result
suffix:semicolon
)brace
multiline_comment|/*&n; * l4_calibrate() calibrates the L4 for the attached device, so&n; * that the device&squot;s resistance fits into the L4&squot;s 8-bit range.&n; */
DECL|function|l4_calibrate
r_static
r_int
id|l4_calibrate
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
comma
r_int
op_star
id|axes
comma
r_int
op_star
id|max
)paren
(brace
r_int
id|i
comma
id|t
suffix:semicolon
r_int
id|cal
(braket
l_int|4
)braket
suffix:semicolon
r_struct
id|l4
op_star
id|l4
op_assign
id|gameport-&gt;driver
suffix:semicolon
r_if
c_cond
(paren
id|l4_getcal
c_func
(paren
id|l4-&gt;port
comma
id|cal
)paren
)paren
r_return
op_minus
l_int|1
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
(brace
id|t
op_assign
(paren
id|max
(braket
id|i
)braket
op_star
id|cal
(braket
id|i
)braket
)paren
op_div
l_int|200
suffix:semicolon
id|t
op_assign
(paren
id|t
OL
l_int|1
)paren
ques
c_cond
l_int|1
suffix:colon
(paren
(paren
id|t
OG
l_int|255
)paren
ques
c_cond
l_int|255
suffix:colon
id|t
)paren
suffix:semicolon
id|axes
(braket
id|i
)braket
op_assign
(paren
id|axes
(braket
id|i
)braket
OL
l_int|0
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
(paren
id|axes
(braket
id|i
)braket
op_star
id|cal
(braket
id|i
)braket
)paren
op_div
id|t
suffix:semicolon
id|axes
(braket
id|i
)braket
op_assign
(paren
id|axes
(braket
id|i
)braket
OG
l_int|252
)paren
ques
c_cond
l_int|252
suffix:colon
id|axes
(braket
id|i
)braket
suffix:semicolon
id|cal
(braket
id|i
)braket
op_assign
id|t
suffix:semicolon
)brace
r_if
c_cond
(paren
id|l4_setcal
c_func
(paren
id|l4-&gt;port
comma
id|cal
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|l4_init
r_static
r_int
id|__init
id|l4_init
c_func
(paren
r_void
)paren
(brace
r_int
id|cal
(braket
l_int|4
)braket
op_assign
(brace
l_int|255
comma
l_int|255
comma
l_int|255
comma
l_int|255
)brace
suffix:semicolon
r_int
id|i
comma
id|j
comma
id|rev
comma
id|cards
op_assign
l_int|0
suffix:semicolon
r_struct
id|gameport
op_star
id|gameport
suffix:semicolon
r_struct
id|l4
op_star
id|l4
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|L4_PORT
comma
l_int|1
comma
l_string|&quot;lightning&quot;
)paren
)paren
r_return
op_minus
l_int|1
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
id|outb
c_func
(paren
id|L4_SELECT_ANALOG
comma
id|L4_PORT
)paren
suffix:semicolon
id|outb
c_func
(paren
id|L4_SELECT_DIGITAL
op_plus
id|i
comma
id|L4_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|L4_PORT
)paren
op_amp
id|L4_BUSY
)paren
r_continue
suffix:semicolon
id|outb
c_func
(paren
id|L4_CMD_ID
comma
id|L4_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|L4_PORT
)paren
op_ne
id|L4_SELECT_DIGITAL
op_plus
id|i
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|L4_PORT
)paren
op_ne
id|L4_ID
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|l4_wait_ready
c_func
(paren
)paren
)paren
r_continue
suffix:semicolon
id|rev
op_assign
id|inb
c_func
(paren
id|L4_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|rev
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|l4_port
(braket
id|i
op_star
l_int|4
)braket
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|l4
)paren
op_star
l_int|4
comma
id|GFP_KERNEL
)paren
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;lightning: Out of memory allocating ports.&bslash;n&quot;
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|memset
c_func
(paren
id|l4_port
(braket
id|i
op_star
l_int|4
)braket
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|l4
)paren
op_star
l_int|4
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
l_int|4
suffix:semicolon
id|j
op_increment
)paren
(brace
id|l4
op_assign
id|l4_port
(braket
id|i
op_star
l_int|4
op_plus
id|j
)braket
op_assign
id|l4_port
(braket
id|i
op_star
l_int|4
)braket
op_plus
id|j
suffix:semicolon
id|l4-&gt;port
op_assign
id|i
op_star
l_int|4
op_plus
id|j
suffix:semicolon
id|sprintf
c_func
(paren
id|l4-&gt;phys
comma
l_string|&quot;isa%04x/gameport%d&quot;
comma
id|L4_PORT
comma
l_int|4
op_star
id|i
op_plus
id|j
)paren
suffix:semicolon
id|gameport
op_assign
op_amp
id|l4-&gt;gameport
suffix:semicolon
id|gameport-&gt;driver
op_assign
id|l4
suffix:semicolon
id|gameport-&gt;open
op_assign
id|l4_open
suffix:semicolon
id|gameport-&gt;cooked_read
op_assign
id|l4_cooked_read
suffix:semicolon
id|gameport-&gt;calibrate
op_assign
id|l4_calibrate
suffix:semicolon
id|gameport-&gt;name
op_assign
id|l4_name
suffix:semicolon
id|gameport-&gt;phys
op_assign
id|l4-&gt;phys
suffix:semicolon
id|gameport-&gt;id.bustype
op_assign
id|BUS_ISA
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|i
op_logical_and
op_logical_neg
id|j
)paren
id|gameport-&gt;io
op_assign
id|L4_PORT
suffix:semicolon
r_if
c_cond
(paren
id|rev
OG
l_int|0x28
)paren
multiline_comment|/* on 2.9+ the setcal command works correctly */
id|l4_setcal
c_func
(paren
id|l4-&gt;port
comma
id|cal
)paren
suffix:semicolon
id|gameport_register_port
c_func
(paren
id|gameport
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;gameport: PDPI Lightning 4 %s card v%d.%d at %#x&bslash;n&quot;
comma
id|i
ques
c_cond
l_string|&quot;secondary&quot;
suffix:colon
l_string|&quot;primary&quot;
comma
id|rev
op_rshift
l_int|4
comma
id|rev
comma
id|L4_PORT
)paren
suffix:semicolon
id|cards
op_increment
suffix:semicolon
)brace
id|outb
c_func
(paren
id|L4_SELECT_ANALOG
comma
id|L4_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|cards
)paren
(brace
id|release_region
c_func
(paren
id|L4_PORT
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|l4_exit
r_static
r_void
id|__exit
id|l4_exit
c_func
(paren
r_void
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|cal
(braket
l_int|4
)braket
op_assign
(brace
l_int|59
comma
l_int|59
comma
l_int|59
comma
l_int|59
)brace
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
r_if
c_cond
(paren
id|l4_port
(braket
id|i
)braket
)paren
(brace
id|l4_setcal
c_func
(paren
id|l4_port
(braket
id|i
)braket
op_member_access_from_pointer
id|port
comma
id|cal
)paren
suffix:semicolon
id|gameport_unregister_port
c_func
(paren
op_amp
id|l4_port
(braket
id|i
)braket
op_member_access_from_pointer
id|gameport
)paren
suffix:semicolon
)brace
id|outb
c_func
(paren
id|L4_SELECT_ANALOG
comma
id|L4_PORT
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|L4_PORT
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|variable|l4_init
id|module_init
c_func
(paren
id|l4_init
)paren
suffix:semicolon
DECL|variable|l4_exit
id|module_exit
c_func
(paren
id|l4_exit
)paren
suffix:semicolon
eof
