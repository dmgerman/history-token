multiline_comment|/*&n; * $Id: parkbd.c,v 1.10 2002/03/13 10:09:20 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; *  Parallel port to Keyboard port adapter driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/parport.h&gt;
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
l_string|&quot;Parallel port to Keyboard port adapter driver&quot;
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
id|parkbd
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|parkbd_mode
comma
l_string|&quot;1i&quot;
)paren
suffix:semicolon
DECL|macro|PARKBD_CLOCK
mdefine_line|#define PARKBD_CLOCK&t;0x01&t;/* Strobe &amp; Ack */
DECL|macro|PARKBD_DATA
mdefine_line|#define PARKBD_DATA&t;0x02&t;/* AutoFd &amp; Busy */
DECL|variable|parkbd
r_static
r_int
id|parkbd
suffix:semicolon
DECL|variable|parkbd_mode
r_static
r_int
id|parkbd_mode
op_assign
id|SERIO_8042
suffix:semicolon
DECL|variable|parkbd_buffer
r_static
r_int
id|parkbd_buffer
suffix:semicolon
DECL|variable|parkbd_counter
r_static
r_int
id|parkbd_counter
suffix:semicolon
DECL|variable|parkbd_last
r_static
r_int
r_int
id|parkbd_last
suffix:semicolon
DECL|variable|parkbd_writing
r_static
r_int
id|parkbd_writing
suffix:semicolon
DECL|variable|parkbd_start
r_static
r_int
r_int
id|parkbd_start
suffix:semicolon
DECL|variable|parkbd_dev
r_static
r_struct
id|pardevice
op_star
id|parkbd_dev
suffix:semicolon
DECL|variable|parkbd_name
r_static
r_char
id|parkbd_name
(braket
)braket
op_assign
l_string|&quot;PARKBD AT/XT keyboard adapter&quot;
suffix:semicolon
DECL|variable|parkbd_phys
r_static
r_char
id|parkbd_phys
(braket
l_int|32
)braket
suffix:semicolon
DECL|function|parkbd_readlines
r_static
r_int
id|parkbd_readlines
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|parport_read_status
c_func
(paren
id|parkbd_dev-&gt;port
)paren
op_rshift
l_int|6
)paren
op_xor
l_int|2
suffix:semicolon
)brace
DECL|function|parkbd_writelines
r_static
r_void
id|parkbd_writelines
c_func
(paren
r_int
id|data
)paren
(brace
id|parport_write_control
c_func
(paren
id|parkbd_dev-&gt;port
comma
(paren
op_complement
id|data
op_amp
l_int|3
)paren
op_or
l_int|0x10
)paren
suffix:semicolon
)brace
DECL|function|parkbd_write
r_static
r_int
id|parkbd_write
c_func
(paren
r_struct
id|serio
op_star
id|port
comma
r_int
r_char
id|c
)paren
(brace
r_int
r_char
id|p
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|parkbd_mode
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|p
op_assign
id|c
op_xor
(paren
id|c
op_rshift
l_int|4
)paren
suffix:semicolon
id|p
op_assign
id|p
op_xor
(paren
id|p
op_rshift
l_int|2
)paren
suffix:semicolon
id|p
op_assign
id|p
op_xor
(paren
id|p
op_rshift
l_int|1
)paren
suffix:semicolon
id|parkbd_counter
op_assign
l_int|0
suffix:semicolon
id|parkbd_writing
op_assign
l_int|1
suffix:semicolon
id|parkbd_buffer
op_assign
id|c
op_or
(paren
(paren
(paren
r_int
)paren
(paren
op_complement
id|p
op_amp
l_int|1
)paren
)paren
op_lshift
l_int|8
)paren
op_or
l_int|0x600
suffix:semicolon
id|parkbd_writelines
c_func
(paren
l_int|2
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parkbd_open
r_static
r_int
id|parkbd_open
c_func
(paren
r_struct
id|serio
op_star
id|port
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parkbd_close
r_static
r_void
id|parkbd_close
c_func
(paren
r_struct
id|serio
op_star
id|port
)paren
(brace
)brace
DECL|variable|parkbd_port
r_static
r_struct
id|serio
id|parkbd_port
op_assign
(brace
dot
id|write
op_assign
id|parkbd_write
comma
dot
id|open
op_assign
id|parkbd_open
comma
dot
id|close
op_assign
id|parkbd_close
comma
dot
id|name
op_assign
id|parkbd_name
comma
dot
id|phys
op_assign
id|parkbd_phys
comma
)brace
suffix:semicolon
DECL|function|parkbd_interrupt
r_static
r_void
id|parkbd_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
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
id|parkbd_writing
)paren
(brace
r_if
c_cond
(paren
id|parkbd_counter
op_logical_and
(paren
(paren
id|parkbd_counter
op_eq
l_int|11
)paren
op_logical_or
id|time_after
c_func
(paren
id|jiffies
comma
id|parkbd_last
op_plus
id|HZ
op_div
l_int|100
)paren
)paren
)paren
(brace
id|parkbd_counter
op_assign
l_int|0
suffix:semicolon
id|parkbd_buffer
op_assign
l_int|0
suffix:semicolon
id|parkbd_writing
op_assign
l_int|0
suffix:semicolon
id|parkbd_writelines
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|parkbd_writelines
c_func
(paren
(paren
(paren
id|parkbd_buffer
op_rshift
id|parkbd_counter
op_increment
)paren
op_amp
l_int|1
)paren
op_or
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
id|parkbd_counter
op_eq
l_int|11
)paren
(brace
id|parkbd_counter
op_assign
l_int|0
suffix:semicolon
id|parkbd_buffer
op_assign
l_int|0
suffix:semicolon
id|parkbd_writing
op_assign
l_int|0
suffix:semicolon
id|parkbd_writelines
c_func
(paren
l_int|3
)paren
suffix:semicolon
)brace
)brace
r_else
(brace
r_if
c_cond
(paren
(paren
id|parkbd_counter
op_eq
id|parkbd_mode
op_plus
l_int|10
)paren
op_logical_or
id|time_after
c_func
(paren
id|jiffies
comma
id|parkbd_last
op_plus
id|HZ
op_div
l_int|100
)paren
)paren
(brace
id|parkbd_counter
op_assign
l_int|0
suffix:semicolon
id|parkbd_buffer
op_assign
l_int|0
suffix:semicolon
)brace
id|parkbd_buffer
op_or_assign
(paren
id|parkbd_readlines
c_func
(paren
)paren
op_rshift
l_int|1
)paren
op_lshift
id|parkbd_counter
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|parkbd_counter
op_eq
id|parkbd_mode
op_plus
l_int|10
)paren
id|serio_interrupt
c_func
(paren
op_amp
id|parkbd_port
comma
(paren
id|parkbd_buffer
op_rshift
(paren
l_int|2
op_minus
id|parkbd_mode
)paren
)paren
op_amp
l_int|0xff
comma
l_int|0
comma
id|regs
)paren
suffix:semicolon
)brace
id|parkbd_last
op_assign
id|jiffies
suffix:semicolon
)brace
DECL|function|parkbd_getport
r_static
r_int
id|parkbd_getport
c_func
(paren
r_void
)paren
(brace
r_struct
id|parport
op_star
id|pp
suffix:semicolon
r_if
c_cond
(paren
id|parkbd
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;parkbd: no port specified&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
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
op_ne
l_int|NULL
op_logical_and
(paren
id|parkbd
OG
l_int|0
)paren
suffix:semicolon
id|pp
op_assign
id|pp-&gt;next
)paren
id|parkbd
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|pp
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;parkbd: no such parport&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|parkbd_dev
op_assign
id|parport_register_device
c_func
(paren
id|pp
comma
l_string|&quot;parkbd&quot;
comma
l_int|NULL
comma
l_int|NULL
comma
id|parkbd_interrupt
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
id|parkbd_dev
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|parport_claim
c_func
(paren
id|parkbd_dev
)paren
)paren
(brace
id|parport_unregister_device
c_func
(paren
id|parkbd_dev
)paren
suffix:semicolon
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|parkbd_start
op_assign
id|jiffies
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parkbd_init
r_int
id|__init
id|parkbd_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|parkbd_getport
c_func
(paren
)paren
)paren
r_return
op_minus
l_int|1
suffix:semicolon
id|parkbd_writelines
c_func
(paren
l_int|3
)paren
suffix:semicolon
id|parkbd_port.type
op_assign
id|parkbd_mode
suffix:semicolon
id|sprintf
c_func
(paren
id|parkbd_phys
comma
l_string|&quot;%s/serio0&quot;
comma
id|parkbd_dev-&gt;port-&gt;name
)paren
suffix:semicolon
id|serio_register_port
c_func
(paren
op_amp
id|parkbd_port
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;serio: PARKBD %s adapter on %s&bslash;n&quot;
comma
id|parkbd_mode
ques
c_cond
l_string|&quot;AT&quot;
suffix:colon
l_string|&quot;XT&quot;
comma
id|parkbd_dev-&gt;port-&gt;name
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|parkbd_exit
r_void
id|__exit
id|parkbd_exit
c_func
(paren
r_void
)paren
(brace
id|parport_release
c_func
(paren
id|parkbd_dev
)paren
suffix:semicolon
id|serio_unregister_port
c_func
(paren
op_amp
id|parkbd_port
)paren
suffix:semicolon
id|parport_unregister_device
c_func
(paren
id|parkbd_dev
)paren
suffix:semicolon
)brace
DECL|variable|parkbd_init
id|module_init
c_func
(paren
id|parkbd_init
)paren
suffix:semicolon
DECL|variable|parkbd_exit
id|module_exit
c_func
(paren
id|parkbd_exit
)paren
suffix:semicolon
eof
