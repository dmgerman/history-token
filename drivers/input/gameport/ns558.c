multiline_comment|/*&n; * $Id: ns558.c,v 1.43 2002/01/24 19:23:21 vojtech Exp $&n; *&n; *  Copyright (c) 1999-2001 Vojtech Pavlik&n; *  Copyright (c) 1999 Brian Gerst&n; */
multiline_comment|/*&n; * NS558 based standard IBM game port driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pnp.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Classic gameport (ISA/PnP) driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|variable|ns558_isa_portlist
r_static
r_int
id|ns558_isa_portlist
(braket
)braket
op_assign
(brace
l_int|0x201
comma
l_int|0x200
comma
l_int|0x202
comma
l_int|0x203
comma
l_int|0x204
comma
l_int|0x205
comma
l_int|0x207
comma
l_int|0x209
comma
l_int|0x20b
comma
l_int|0x20c
comma
l_int|0x20e
comma
l_int|0x20f
comma
l_int|0x211
comma
l_int|0x219
comma
l_int|0x101
comma
l_int|0
)brace
suffix:semicolon
DECL|struct|ns558
r_struct
id|ns558
(brace
DECL|member|type
r_int
id|type
suffix:semicolon
DECL|member|io
r_int
id|io
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|dev
r_struct
id|pnp_dev
op_star
id|dev
suffix:semicolon
DECL|member|gameport
r_struct
id|gameport
op_star
id|gameport
suffix:semicolon
DECL|member|node
r_struct
id|list_head
id|node
suffix:semicolon
)brace
suffix:semicolon
r_static
id|LIST_HEAD
c_func
(paren
id|ns558_list
)paren
suffix:semicolon
multiline_comment|/*&n; * ns558_isa_probe() tries to find an isa gameport at the&n; * specified address, and also checks for mirrors.&n; * A joystick must be attached for this to work.&n; */
DECL|function|ns558_isa_probe
r_static
r_int
id|ns558_isa_probe
c_func
(paren
r_int
id|io
)paren
(brace
r_int
id|i
comma
id|j
comma
id|b
suffix:semicolon
r_int
r_char
id|c
comma
id|u
comma
id|v
suffix:semicolon
r_struct
id|ns558
op_star
id|ns558
suffix:semicolon
r_struct
id|gameport
op_star
id|port
suffix:semicolon
multiline_comment|/*&n; * No one should be using this address.&n; */
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|io
comma
l_int|1
comma
l_string|&quot;ns558-isa&quot;
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
multiline_comment|/*&n; * We must not be able to write arbitrary values to the port.&n; * The lower two axis bits must be 1 after a write.&n; */
id|c
op_assign
id|inb
c_func
(paren
id|io
)paren
suffix:semicolon
id|outb
c_func
(paren
op_complement
id|c
op_amp
op_complement
l_int|3
comma
id|io
)paren
suffix:semicolon
r_if
c_cond
(paren
op_complement
(paren
id|u
op_assign
id|v
op_assign
id|inb
c_func
(paren
id|io
)paren
)paren
op_amp
l_int|3
)paren
(brace
id|outb
c_func
(paren
id|c
comma
id|io
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n; * After a trigger, there must be at least some bits changing.&n; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|1000
suffix:semicolon
id|i
op_increment
)paren
id|v
op_and_assign
id|inb
c_func
(paren
id|io
)paren
suffix:semicolon
r_if
c_cond
(paren
id|u
op_eq
id|v
)paren
(brace
id|outb
c_func
(paren
id|c
comma
id|io
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|msleep
c_func
(paren
l_int|3
)paren
suffix:semicolon
multiline_comment|/*&n; * After some time (4ms) the axes shouldn&squot;t change anymore.&n; */
id|u
op_assign
id|inb
c_func
(paren
id|io
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
l_int|1000
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
(paren
id|u
op_xor
id|inb
c_func
(paren
id|io
)paren
)paren
op_amp
l_int|0xf
)paren
(brace
id|outb
c_func
(paren
id|c
comma
id|io
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
comma
l_int|1
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n; * And now find the number of mirrors of the port.&n; */
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
l_int|5
suffix:semicolon
id|i
op_increment
)paren
(brace
id|release_region
c_func
(paren
id|io
op_amp
(paren
op_minus
l_int|1
op_lshift
(paren
id|i
op_minus
l_int|1
)paren
)paren
comma
(paren
l_int|1
op_lshift
(paren
id|i
op_minus
l_int|1
)paren
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|io
op_amp
(paren
op_minus
l_int|1
op_lshift
id|i
)paren
comma
(paren
l_int|1
op_lshift
id|i
)paren
comma
l_string|&quot;ns558-isa&quot;
)paren
)paren
r_break
suffix:semicolon
multiline_comment|/* Don&squot;t disturb anyone */
id|outb
c_func
(paren
l_int|0xff
comma
id|io
op_amp
(paren
op_minus
l_int|1
op_lshift
id|i
)paren
)paren
suffix:semicolon
r_for
c_loop
(paren
id|j
op_assign
id|b
op_assign
l_int|0
suffix:semicolon
id|j
OL
l_int|1000
suffix:semicolon
id|j
op_increment
)paren
r_if
c_cond
(paren
id|inb
c_func
(paren
id|io
op_amp
(paren
op_minus
l_int|1
op_lshift
id|i
)paren
)paren
op_ne
id|inb
c_func
(paren
(paren
id|io
op_amp
(paren
op_minus
l_int|1
op_lshift
id|i
)paren
)paren
op_plus
(paren
l_int|1
op_lshift
id|i
)paren
op_minus
l_int|1
)paren
)paren
id|b
op_increment
suffix:semicolon
id|msleep
c_func
(paren
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
OG
l_int|300
)paren
(brace
multiline_comment|/* We allow 30% difference */
id|release_region
c_func
(paren
id|io
op_amp
(paren
op_minus
l_int|1
op_lshift
id|i
)paren
comma
(paren
l_int|1
op_lshift
id|i
)paren
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
id|i
op_decrement
suffix:semicolon
r_if
c_cond
(paren
id|i
op_ne
l_int|4
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|io
op_amp
(paren
op_minus
l_int|1
op_lshift
id|i
)paren
comma
(paren
l_int|1
op_lshift
id|i
)paren
comma
l_string|&quot;ns558-isa&quot;
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
)brace
id|ns558
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|ns558
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|port
op_assign
id|gameport_allocate_port
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ns558
op_logical_or
op_logical_neg
id|port
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ns558: Memory allocation failed.&bslash;n&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|io
op_amp
(paren
op_minus
l_int|1
op_lshift
id|i
)paren
comma
(paren
l_int|1
op_lshift
id|i
)paren
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ns558
)paren
suffix:semicolon
id|gameport_free_port
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|ns558
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|ns558
)paren
)paren
suffix:semicolon
id|ns558-&gt;io
op_assign
id|io
suffix:semicolon
id|ns558-&gt;size
op_assign
l_int|1
op_lshift
id|i
suffix:semicolon
id|ns558-&gt;gameport
op_assign
id|port
suffix:semicolon
id|port-&gt;io
op_assign
id|io
suffix:semicolon
id|gameport_set_name
c_func
(paren
id|port
comma
l_string|&quot;NS558 ISA Gameport&quot;
)paren
suffix:semicolon
id|gameport_set_phys
c_func
(paren
id|port
comma
l_string|&quot;isa%04x/gameport0&quot;
comma
id|io
op_amp
(paren
op_minus
l_int|1
op_lshift
id|i
)paren
)paren
suffix:semicolon
id|gameport_register_port
c_func
(paren
id|port
)paren
suffix:semicolon
id|list_add
c_func
(paren
op_amp
id|ns558-&gt;node
comma
op_amp
id|ns558_list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PNP
DECL|variable|pnp_devids
r_static
r_struct
id|pnp_device_id
id|pnp_devids
(braket
)braket
op_assign
(brace
(brace
dot
id|id
op_assign
l_string|&quot;@P@0001&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* ALS 100 */
(brace
dot
id|id
op_assign
l_string|&quot;@P@0020&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* ALS 200 */
(brace
dot
id|id
op_assign
l_string|&quot;@P@1001&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* ALS 100+ */
(brace
dot
id|id
op_assign
l_string|&quot;@P@2001&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* ALS 120 */
(brace
dot
id|id
op_assign
l_string|&quot;ASB16fd&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* AdLib NSC16 */
(brace
dot
id|id
op_assign
l_string|&quot;AZT3001&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* AZT1008 */
(brace
dot
id|id
op_assign
l_string|&quot;CDC0001&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* Opl3-SAx */
(brace
dot
id|id
op_assign
l_string|&quot;CSC0001&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* CS4232 */
(brace
dot
id|id
op_assign
l_string|&quot;CSC000f&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* CS4236 */
(brace
dot
id|id
op_assign
l_string|&quot;CSC0101&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* CS4327 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL7001&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* SB16 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL7002&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* AWE64 */
(brace
dot
id|id
op_assign
l_string|&quot;CTL7005&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* Vibra16 */
(brace
dot
id|id
op_assign
l_string|&quot;ENS2020&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* SoundscapeVIVO */
(brace
dot
id|id
op_assign
l_string|&quot;ESS0001&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* ES1869 */
(brace
dot
id|id
op_assign
l_string|&quot;ESS0005&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* ES1878 */
(brace
dot
id|id
op_assign
l_string|&quot;ESS6880&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* ES688 */
(brace
dot
id|id
op_assign
l_string|&quot;IBM0012&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* CS4232 */
(brace
dot
id|id
op_assign
l_string|&quot;OPT0001&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* OPTi Audio16 */
(brace
dot
id|id
op_assign
l_string|&quot;YMH0006&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* Opl3-SA */
(brace
dot
id|id
op_assign
l_string|&quot;YMH0022&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* Opl3-SAx */
(brace
dot
id|id
op_assign
l_string|&quot;PNPb02f&quot;
comma
dot
id|driver_data
op_assign
l_int|0
)brace
comma
multiline_comment|/* Generic */
(brace
dot
id|id
op_assign
l_string|&quot;&quot;
comma
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pnp
comma
id|pnp_devids
)paren
suffix:semicolon
DECL|function|ns558_pnp_probe
r_static
r_int
id|ns558_pnp_probe
c_func
(paren
r_struct
id|pnp_dev
op_star
id|dev
comma
r_const
r_struct
id|pnp_device_id
op_star
id|did
)paren
(brace
r_int
id|ioport
comma
id|iolen
suffix:semicolon
r_struct
id|ns558
op_star
id|ns558
suffix:semicolon
r_struct
id|gameport
op_star
id|port
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pnp_port_valid
c_func
(paren
id|dev
comma
l_int|0
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ns558: No i/o ports on a gameport? Weird&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|ioport
op_assign
id|pnp_port_start
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
id|iolen
op_assign
id|pnp_port_len
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ioport
comma
id|iolen
comma
l_string|&quot;ns558-pnp&quot;
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|ns558
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|ns558
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
id|port
op_assign
id|gameport_allocate_port
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|ns558
op_logical_or
op_logical_neg
id|port
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;ns558: Memory allocation failed&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ns558
)paren
suffix:semicolon
id|gameport_free_port
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|ns558-&gt;io
op_assign
id|ioport
suffix:semicolon
id|ns558-&gt;size
op_assign
id|iolen
suffix:semicolon
id|ns558-&gt;dev
op_assign
id|dev
suffix:semicolon
id|ns558-&gt;gameport
op_assign
id|port
suffix:semicolon
id|gameport_set_name
c_func
(paren
id|port
comma
l_string|&quot;NS558 PnP Gameport&quot;
)paren
suffix:semicolon
id|gameport_set_phys
c_func
(paren
id|port
comma
l_string|&quot;pnp%s/gameport0&quot;
comma
id|dev-&gt;dev.bus_id
)paren
suffix:semicolon
id|port-&gt;dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|port-&gt;io
op_assign
id|ioport
suffix:semicolon
id|gameport_register_port
c_func
(paren
id|port
)paren
suffix:semicolon
id|list_add_tail
c_func
(paren
op_amp
id|ns558-&gt;node
comma
op_amp
id|ns558_list
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|ns558_pnp_driver
r_static
r_struct
id|pnp_driver
id|ns558_pnp_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;ns558&quot;
comma
dot
id|id_table
op_assign
id|pnp_devids
comma
dot
id|probe
op_assign
id|ns558_pnp_probe
comma
)brace
suffix:semicolon
macro_line|#else
DECL|variable|ns558_pnp_driver
r_static
r_struct
id|pnp_driver
id|ns558_pnp_driver
suffix:semicolon
macro_line|#endif
DECL|variable|pnp_registered
r_static
r_int
id|pnp_registered
op_assign
l_int|0
suffix:semicolon
DECL|function|ns558_init
r_static
r_int
id|__init
id|ns558_init
c_func
(paren
r_void
)paren
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n; * Probe ISA ports first so that PnP gets to choose free port addresses&n; * not occupied by the ISA ports.&n; */
r_while
c_loop
(paren
id|ns558_isa_portlist
(braket
id|i
)braket
)paren
id|ns558_isa_probe
c_func
(paren
id|ns558_isa_portlist
(braket
id|i
op_increment
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pnp_register_driver
c_func
(paren
op_amp
id|ns558_pnp_driver
)paren
op_ge
l_int|0
)paren
id|pnp_registered
op_assign
l_int|1
suffix:semicolon
r_return
(paren
id|list_empty
c_func
(paren
op_amp
id|ns558_list
)paren
op_logical_and
op_logical_neg
id|pnp_registered
)paren
ques
c_cond
op_minus
id|ENODEV
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|ns558_exit
r_static
r_void
id|__exit
id|ns558_exit
c_func
(paren
r_void
)paren
(brace
r_struct
id|ns558
op_star
id|ns558
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|ns558
comma
op_amp
id|ns558_list
comma
id|node
)paren
(brace
id|gameport_unregister_port
c_func
(paren
id|ns558-&gt;gameport
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ns558-&gt;io
op_amp
op_complement
(paren
id|ns558-&gt;size
op_minus
l_int|1
)paren
comma
id|ns558-&gt;size
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|ns558
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pnp_registered
)paren
id|pnp_unregister_driver
c_func
(paren
op_amp
id|ns558_pnp_driver
)paren
suffix:semicolon
)brace
DECL|variable|ns558_init
id|module_init
c_func
(paren
id|ns558_init
)paren
suffix:semicolon
DECL|variable|ns558_exit
id|module_exit
c_func
(paren
id|ns558_exit
)paren
suffix:semicolon
eof
