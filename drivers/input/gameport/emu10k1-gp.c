multiline_comment|/*&n; * $Id: emu10k1-gp.c,v 1.8 2002/01/22 20:40:46 vojtech Exp $&n; *&n; *  Copyright (c) 2001 Vojtech Pavlik&n; */
multiline_comment|/*&n; * EMU10k1 - SB Live / Audigy - gameport driver for Linux&n; */
multiline_comment|/*&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License as published by&n; * the Free Software Foundation; either version 2 of the License, or &n; * (at your option) any later version.&n; * &n; * This program is distributed in the hope that it will be useful,&n; * but WITHOUT ANY WARRANTY; without even the implied warranty of&n; * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; * GNU General Public License for more details.&n; * &n; * You should have received a copy of the GNU General Public License&n; * along with this program; if not, write to the Free Software&n; * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA&n; * &n; * Should you need to contact me, the author, you can do so either by&n; * e-mail - mail your message to &lt;vojtech@ucw.cz&gt;, or by paper mail:&n; * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Vojtech Pavlik &lt;vojtech@ucw.cz&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;EMU10k1 gameport driver&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|struct|emu
r_struct
id|emu
(brace
DECL|member|dev
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
DECL|member|next
r_struct
id|emu
op_star
id|next
suffix:semicolon
DECL|member|gameport
r_struct
id|gameport
id|gameport
suffix:semicolon
DECL|member|size
r_int
id|size
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
DECL|variable|__devinitdata
r_static
r_struct
id|pci_device_id
id|emu_tbl
(braket
)braket
id|__devinitdata
op_assign
(brace
(brace
l_int|0x1102
comma
l_int|0x7002
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
)brace
comma
multiline_comment|/* SB Live gameport */
(brace
l_int|0x1102
comma
l_int|0x7003
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
)brace
comma
multiline_comment|/* Audigy gameport */
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|emu_tbl
)paren
suffix:semicolon
DECL|function|emu_probe
r_static
r_int
id|__devinit
id|emu_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
comma
r_const
r_struct
id|pci_device_id
op_star
id|ent
)paren
(brace
r_int
id|ioport
comma
id|iolen
suffix:semicolon
r_struct
id|emu
op_star
id|emu
suffix:semicolon
r_if
c_cond
(paren
id|pci_enable_device
c_func
(paren
id|pdev
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
id|ioport
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|0
)paren
suffix:semicolon
id|iolen
op_assign
id|pci_resource_len
c_func
(paren
id|pdev
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
l_string|&quot;emu10k1-gp&quot;
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|emu
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|emu
)paren
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
l_string|&quot;emu10k1-gp: Memory allocation failed.&bslash;n&quot;
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|ioport
comma
id|iolen
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
id|emu
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|emu
)paren
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|emu-&gt;phys
comma
l_string|&quot;pci%s/gameport0&quot;
comma
id|pdev-&gt;slot_name
)paren
suffix:semicolon
id|emu-&gt;size
op_assign
id|iolen
suffix:semicolon
id|emu-&gt;dev
op_assign
id|pdev
suffix:semicolon
id|emu-&gt;gameport.io
op_assign
id|ioport
suffix:semicolon
id|emu-&gt;gameport.name
op_assign
id|pdev-&gt;name
suffix:semicolon
id|emu-&gt;gameport.phys
op_assign
id|emu-&gt;phys
suffix:semicolon
id|emu-&gt;gameport.id.bustype
op_assign
id|BUS_PCI
suffix:semicolon
id|emu-&gt;gameport.id.vendor
op_assign
id|pdev-&gt;vendor
suffix:semicolon
id|emu-&gt;gameport.id.product
op_assign
id|pdev-&gt;device
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|emu
)paren
suffix:semicolon
id|gameport_register_port
c_func
(paren
op_amp
id|emu-&gt;gameport
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;gameport: %s at pci%s speed %d kHz&bslash;n&quot;
comma
id|pdev-&gt;name
comma
id|pdev-&gt;slot_name
comma
id|emu-&gt;gameport.speed
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|emu_remove
r_static
r_void
id|__devexit
id|emu_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|emu
op_star
id|emu
op_assign
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|gameport_unregister_port
c_func
(paren
op_amp
id|emu-&gt;gameport
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|emu-&gt;gameport.io
comma
id|emu-&gt;size
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|emu
)paren
suffix:semicolon
)brace
DECL|variable|emu_driver
r_static
r_struct
id|pci_driver
id|emu_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;Emu10k1 Gameport&quot;
comma
dot
id|id_table
op_assign
id|emu_tbl
comma
dot
id|probe
op_assign
id|emu_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|emu_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|emu_init
r_int
id|__init
id|emu_init
c_func
(paren
r_void
)paren
(brace
r_return
id|pci_module_init
c_func
(paren
op_amp
id|emu_driver
)paren
suffix:semicolon
)brace
DECL|function|emu_exit
r_void
id|__exit
id|emu_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|emu_driver
)paren
suffix:semicolon
)brace
DECL|variable|emu_init
id|module_init
c_func
(paren
id|emu_init
)paren
suffix:semicolon
DECL|variable|emu_exit
id|module_exit
c_func
(paren
id|emu_exit
)paren
suffix:semicolon
eof
