multiline_comment|/*&n; * $Id: vortex.c,v 1.5 2002/07/01 15:39:30 vojtech Exp $&n; *&n; *  Copyright (c) 2000-2001 Vojtech Pavlik&n; *&n; *  Based on the work of:&n; *&t;Raymond Ingles&n; */
multiline_comment|/*&n; * Trident 4DWave and Aureal Vortex gameport driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or&n; * (at your option) any later version.&n; *&n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; *&n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; *&n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Aureal Vortex and Vortex2 gameport driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|macro|VORTEX_GCR
mdefine_line|#define VORTEX_GCR&t;&t;0x0c&t;/* Gameport control register */
DECL|macro|VORTEX_LEG
mdefine_line|#define VORTEX_LEG&t;&t;0x08&t;/* Legacy port location */
DECL|macro|VORTEX_AXD
mdefine_line|#define VORTEX_AXD&t;&t;0x10&t;/* Axes start */
DECL|macro|VORTEX_DATA_WAIT
mdefine_line|#define VORTEX_DATA_WAIT&t;20&t;/* 20 ms */
DECL|struct|vortex
r_struct
id|vortex
(brace
DECL|member|gameport
r_struct
id|gameport
op_star
id|gameport
suffix:semicolon
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|base
r_int
r_char
id|__iomem
op_star
id|base
suffix:semicolon
DECL|member|io
r_int
r_char
id|__iomem
op_star
id|io
suffix:semicolon
)brace
suffix:semicolon
DECL|function|vortex_read
r_static
r_int
r_char
id|vortex_read
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_struct
id|vortex
op_star
id|vortex
op_assign
id|gameport-&gt;port_data
suffix:semicolon
r_return
id|readb
c_func
(paren
id|vortex-&gt;io
op_plus
id|VORTEX_LEG
)paren
suffix:semicolon
)brace
DECL|function|vortex_trigger
r_static
r_void
id|vortex_trigger
c_func
(paren
r_struct
id|gameport
op_star
id|gameport
)paren
(brace
r_struct
id|vortex
op_star
id|vortex
op_assign
id|gameport-&gt;port_data
suffix:semicolon
id|writeb
c_func
(paren
l_int|0xff
comma
id|vortex-&gt;io
op_plus
id|VORTEX_LEG
)paren
suffix:semicolon
)brace
DECL|function|vortex_cooked_read
r_static
r_int
id|vortex_cooked_read
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
id|vortex
op_star
id|vortex
op_assign
id|gameport-&gt;port_data
suffix:semicolon
r_int
id|i
suffix:semicolon
op_star
id|buttons
op_assign
(paren
op_complement
id|readb
c_func
(paren
id|vortex-&gt;base
op_plus
id|VORTEX_LEG
)paren
op_rshift
l_int|4
)paren
op_amp
l_int|0xf
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
id|axes
(braket
id|i
)braket
op_assign
id|readw
c_func
(paren
id|vortex-&gt;io
op_plus
id|VORTEX_AXD
op_plus
id|i
op_star
r_sizeof
(paren
id|u32
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|axes
(braket
id|i
)braket
op_eq
l_int|0x1fff
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
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vortex_open
r_static
r_int
id|vortex_open
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
id|vortex
op_star
id|vortex
op_assign
id|gameport-&gt;port_data
suffix:semicolon
r_switch
c_cond
(paren
id|mode
)paren
(brace
r_case
id|GAMEPORT_MODE_COOKED
suffix:colon
id|writeb
c_func
(paren
l_int|0x40
comma
id|vortex-&gt;io
op_plus
id|VORTEX_GCR
)paren
suffix:semicolon
id|msleep
c_func
(paren
id|VORTEX_DATA_WAIT
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_case
id|GAMEPORT_MODE_RAW
suffix:colon
id|writeb
c_func
(paren
l_int|0x00
comma
id|vortex-&gt;io
op_plus
id|VORTEX_GCR
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
r_default
suffix:colon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vortex_probe
r_static
r_int
id|__devinit
id|vortex_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_struct
id|vortex
op_star
id|vortex
suffix:semicolon
r_struct
id|gameport
op_star
id|port
suffix:semicolon
r_int
id|i
suffix:semicolon
id|vortex
op_assign
id|kcalloc
c_func
(paren
l_int|1
comma
r_sizeof
(paren
r_struct
id|vortex
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
id|vortex
op_logical_or
op_logical_neg
id|port
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;vortex: Memory allocation failed.&bslash;n&quot;
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|vortex
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
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
op_complement
id|pci_resource_flags
c_func
(paren
id|dev
comma
id|i
)paren
op_amp
id|IORESOURCE_IO
)paren
r_break
suffix:semicolon
id|pci_enable_device
c_func
(paren
id|dev
)paren
suffix:semicolon
id|vortex-&gt;dev
op_assign
id|dev
suffix:semicolon
id|vortex-&gt;gameport
op_assign
id|port
suffix:semicolon
id|vortex-&gt;base
op_assign
id|ioremap
c_func
(paren
id|pci_resource_start
c_func
(paren
id|vortex-&gt;dev
comma
id|i
)paren
comma
id|pci_resource_len
c_func
(paren
id|vortex-&gt;dev
comma
id|i
)paren
)paren
suffix:semicolon
id|vortex-&gt;io
op_assign
id|vortex-&gt;base
op_plus
id|id-&gt;driver_data
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|dev
comma
id|vortex
)paren
suffix:semicolon
id|port-&gt;port_data
op_assign
id|vortex
suffix:semicolon
id|port-&gt;fuzz
op_assign
l_int|64
suffix:semicolon
id|gameport_set_name
c_func
(paren
id|port
comma
l_string|&quot;AU88x0&quot;
)paren
suffix:semicolon
id|gameport_set_phys
c_func
(paren
id|port
comma
l_string|&quot;pci%s/gameport0&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
id|port-&gt;dev.parent
op_assign
op_amp
id|dev-&gt;dev
suffix:semicolon
id|port-&gt;read
op_assign
id|vortex_read
suffix:semicolon
id|port-&gt;trigger
op_assign
id|vortex_trigger
suffix:semicolon
id|port-&gt;cooked_read
op_assign
id|vortex_cooked_read
suffix:semicolon
id|port-&gt;open
op_assign
id|vortex_open
suffix:semicolon
id|gameport_register_port
c_func
(paren
id|port
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|vortex_remove
r_static
r_void
id|__devexit
id|vortex_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_struct
id|vortex
op_star
id|vortex
op_assign
id|pci_get_drvdata
c_func
(paren
id|dev
)paren
suffix:semicolon
id|gameport_unregister_port
c_func
(paren
id|vortex-&gt;gameport
)paren
suffix:semicolon
id|iounmap
c_func
(paren
id|vortex-&gt;base
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|vortex
)paren
suffix:semicolon
)brace
DECL|variable|vortex_id_table
r_static
r_struct
id|pci_device_id
id|vortex_id_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x12eb
comma
l_int|0x0001
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0x11000
)brace
comma
(brace
l_int|0x12eb
comma
l_int|0x0002
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0x28800
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|vortex_driver
r_static
r_struct
id|pci_driver
id|vortex_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;vortex_gameport&quot;
comma
dot
id|id_table
op_assign
id|vortex_id_table
comma
dot
id|probe
op_assign
id|vortex_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|vortex_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|vortex_init
r_static
r_int
id|__init
id|vortex_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_register_driver
c_func
(paren
op_amp
id|vortex_driver
)paren
suffix:semicolon
)brace
DECL|function|vortex_exit
r_static
r_void
id|__exit
id|vortex_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|vortex_driver
)paren
suffix:semicolon
)brace
DECL|variable|vortex_init
id|module_init
c_func
(paren
id|vortex_init
)paren
suffix:semicolon
DECL|variable|vortex_exit
id|module_exit
c_func
(paren
id|vortex_exit
)paren
suffix:semicolon
eof
