multiline_comment|/*&n; *  FM801 gameport driver for Linux&n; *&n; *  Copyright (c) by Takashi Iwai &lt;tiwai@suse.de&gt;&n; *&n; *&n; *   This program is free software; you can redistribute it and/or modify&n; *   it under the terms of the GNU General Public License as published by&n; *   the Free Software Foundation; either version 2 of the License, or&n; *   (at your option) any later version.&n; *&n; *   This program is distributed in the hope that it will be useful,&n; *   but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *   GNU General Public License for more details.&n; *&n; *   You should have received a copy of the GNU General Public License&n; *   along with this program; if not, write to the Free Software&n; *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.&n; *&n; */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/gameport.h&gt;
DECL|macro|PCI_VENDOR_ID_FORTEMEDIA
mdefine_line|#define PCI_VENDOR_ID_FORTEMEDIA&t;0x1319
DECL|macro|PCI_DEVICE_ID_FM801_GP
mdefine_line|#define PCI_DEVICE_ID_FM801_GP&t;0x0802
DECL|macro|HAVE_COOKED
mdefine_line|#define HAVE_COOKED
DECL|struct|fm801_gp
r_struct
id|fm801_gp
(brace
DECL|member|gameport
r_struct
id|gameport
id|gameport
suffix:semicolon
DECL|member|res_port
r_struct
id|resource
op_star
id|res_port
suffix:semicolon
DECL|member|phys
r_char
id|phys
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|name
r_char
id|name
(braket
l_int|32
)braket
suffix:semicolon
)brace
suffix:semicolon
macro_line|#ifdef HAVE_COOKED
DECL|function|fm801_gp_cooked_read
r_static
r_int
id|fm801_gp_cooked_read
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
r_int
r_int
id|w
suffix:semicolon
id|w
op_assign
id|inw
c_func
(paren
id|gameport-&gt;io
op_plus
l_int|2
)paren
suffix:semicolon
op_star
id|buttons
op_assign
(paren
op_complement
id|w
op_rshift
l_int|14
)paren
op_amp
l_int|0x03
suffix:semicolon
id|axes
(braket
l_int|0
)braket
op_assign
(paren
id|w
op_eq
l_int|0xffff
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
(paren
(paren
id|w
op_amp
l_int|0x1fff
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
id|w
op_assign
id|inw
c_func
(paren
id|gameport-&gt;io
op_plus
l_int|4
)paren
suffix:semicolon
id|axes
(braket
l_int|1
)braket
op_assign
(paren
id|w
op_eq
l_int|0xffff
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
(paren
(paren
id|w
op_amp
l_int|0x1fff
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
id|w
op_assign
id|inw
c_func
(paren
id|gameport-&gt;io
op_plus
l_int|6
)paren
suffix:semicolon
op_star
id|buttons
op_or_assign
(paren
(paren
op_complement
id|w
op_rshift
l_int|14
)paren
op_amp
l_int|0x03
)paren
op_lshift
l_int|2
suffix:semicolon
id|axes
(braket
l_int|2
)braket
op_assign
(paren
id|w
op_eq
l_int|0xffff
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
(paren
(paren
id|w
op_amp
l_int|0x1fff
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
id|w
op_assign
id|inw
c_func
(paren
id|gameport-&gt;io
op_plus
l_int|8
)paren
suffix:semicolon
id|axes
(braket
l_int|3
)braket
op_assign
(paren
id|w
op_eq
l_int|0xffff
)paren
ques
c_cond
op_minus
l_int|1
suffix:colon
(paren
(paren
id|w
op_amp
l_int|0x1fff
)paren
op_lshift
l_int|5
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0xff
comma
id|gameport-&gt;io
)paren
suffix:semicolon
multiline_comment|/* reset */
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
DECL|function|fm801_gp_open
r_static
r_int
id|fm801_gp_open
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
r_switch
c_cond
(paren
id|mode
)paren
(brace
macro_line|#ifdef HAVE_COOKED
r_case
id|GAMEPORT_MODE_COOKED
suffix:colon
r_return
l_int|0
suffix:semicolon
macro_line|#endif
r_case
id|GAMEPORT_MODE_RAW
suffix:colon
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
DECL|function|fm801_gp_probe
r_static
r_int
id|__devinit
id|fm801_gp_probe
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
comma
r_const
r_struct
id|pci_device_id
op_star
id|id
)paren
(brace
r_struct
id|fm801_gp
op_star
id|gp
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|gp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|gp
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
l_string|&quot;cannot malloc for fm801-gp&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|memset
c_func
(paren
id|gp
comma
l_int|0
comma
r_sizeof
(paren
op_star
id|gp
)paren
)paren
suffix:semicolon
id|gp-&gt;gameport.open
op_assign
id|fm801_gp_open
suffix:semicolon
macro_line|#ifdef HAVE_COOKED
id|gp-&gt;gameport.cooked_read
op_assign
id|fm801_gp_cooked_read
suffix:semicolon
macro_line|#endif
id|pci_enable_device
c_func
(paren
id|pci
)paren
suffix:semicolon
id|gp-&gt;gameport.io
op_assign
id|pci_resource_start
c_func
(paren
id|pci
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|gp-&gt;res_port
op_assign
id|request_region
c_func
(paren
id|gp-&gt;gameport.io
comma
l_int|0x10
comma
l_string|&quot;FM801 GP&quot;
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|kfree
c_func
(paren
id|gp
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;unable to grab region 0x%x-0x%x&bslash;n&quot;
comma
id|gp-&gt;gameport.io
comma
id|gp-&gt;gameport.io
op_plus
l_int|0x0f
)paren
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
id|gp-&gt;gameport.phys
op_assign
id|gp-&gt;phys
suffix:semicolon
id|gp-&gt;gameport.name
op_assign
id|gp-&gt;name
suffix:semicolon
id|gp-&gt;gameport.id.bustype
op_assign
id|BUS_PCI
suffix:semicolon
id|gp-&gt;gameport.id.vendor
op_assign
id|pci-&gt;vendor
suffix:semicolon
id|gp-&gt;gameport.id.product
op_assign
id|pci-&gt;device
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pci
comma
id|gp
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x60
comma
id|gp-&gt;gameport.io
op_plus
l_int|0x0d
)paren
suffix:semicolon
multiline_comment|/* enable joystick 1 and 2 */
id|gameport_register_port
c_func
(paren
op_amp
id|gp-&gt;gameport
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;gameport: at pci%s speed %d kHz&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|pci
)paren
comma
id|gp-&gt;gameport.speed
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|fm801_gp_remove
r_static
r_void
id|__devexit
id|fm801_gp_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pci
)paren
(brace
r_struct
id|fm801_gp
op_star
id|gp
op_assign
id|pci_get_drvdata
c_func
(paren
id|pci
)paren
suffix:semicolon
r_if
c_cond
(paren
id|gp
)paren
(brace
id|gameport_unregister_port
c_func
(paren
op_amp
id|gp-&gt;gameport
)paren
suffix:semicolon
id|release_resource
c_func
(paren
id|gp-&gt;res_port
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|gp
)paren
suffix:semicolon
)brace
)brace
DECL|variable|fm801_gp_id_table
r_static
r_struct
id|pci_device_id
id|fm801_gp_id_table
(braket
)braket
op_assign
(brace
(brace
id|PCI_VENDOR_ID_FORTEMEDIA
comma
id|PCI_DEVICE_ID_FM801_GP
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
l_int|0
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|variable|fm801_gp_driver
r_static
r_struct
id|pci_driver
id|fm801_gp_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;FM801 GP&quot;
comma
dot
id|id_table
op_assign
id|fm801_gp_id_table
comma
dot
id|probe
op_assign
id|fm801_gp_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|fm801_gp_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|fm801_gp_init
r_int
id|__init
id|fm801_gp_init
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
id|fm801_gp_driver
)paren
suffix:semicolon
)brace
DECL|function|fm801_gp_exit
r_void
id|__exit
id|fm801_gp_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|fm801_gp_driver
)paren
suffix:semicolon
)brace
DECL|variable|fm801_gp_init
id|module_init
c_func
(paren
id|fm801_gp_init
)paren
suffix:semicolon
DECL|variable|fm801_gp_exit
id|module_exit
c_func
(paren
id|fm801_gp_exit
)paren
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|fm801_gp_id_table
)paren
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Takashi Iwai &lt;tiwai@suse.de&gt;&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
eof
