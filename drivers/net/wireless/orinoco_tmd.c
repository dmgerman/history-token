multiline_comment|/* orinoco_tmd.c 0.01&n; * &n; * Driver for Prism II devices which would usually be driven by orinoco_cs,&n; * but are connected to the PCI bus by a TMD7160. &n; *&n; * Copyright (C) 2003 Joerg Dorchain &lt;joerg@dorchain.net&gt;&n; * based heavily upon orinoco_plx.c Copyright (C) 2001 Daniel Barlow &lt;dan@telent.net&gt;&n; *&n; * The contents of this file are subject to the Mozilla Public License&n; * Version 1.1 (the &quot;License&quot;); you may not use this file except in&n; * compliance with the License. You may obtain a copy of the License&n; * at http://www.mozilla.org/MPL/&n; *&n; * Software distributed under the License is distributed on an &quot;AS IS&quot;&n; * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See&n; * the License for the specific language governing rights and&n; * limitations under the License.&n; *&n; * Alternatively, the contents of this file may be used under the&n; * terms of the GNU General Public License version 2 (the &quot;GPL&quot;), in&n; * which case the provisions of the GPL are applicable instead of the&n; * above.  If you wish to allow the use of your version of this file&n; * only under the terms of the GPL and not to allow others to use your&n; * version of this file under the MPL, indicate your decision by&n; * deleting the provisions above and replace them with the notice and&n; * other provisions required by the GPL.  If you do not delete the&n; * provisions above, a recipient may use your version of this file&n; * under either the MPL or the GPL.&n;&n; * Caution: this is experimental and probably buggy.  For success and&n; * failure reports for different cards and adaptors, see&n; * orinoco_tmd_pci_id_table near the end of the file.  If you have a&n; * card we don&squot;t have the PCI id for, and looks like it should work,&n; * drop me mail with the id and &quot;it works&quot;/&quot;it doesn&squot;t work&quot;.&n; *&n; * Note: if everything gets detected fine but it doesn&squot;t actually send&n; * or receive packets, your first port of call should probably be to   &n; * try newer firmware in the card.  Especially if you&squot;re doing Ad-Hoc&n; * modes&n; *&n; * The actual driving is done by orinoco.c, this is just resource&n; * allocation stuff.&n; *&n; * This driver is modeled after the orinoco_plx driver. The main&n; * difference is that the TMD chip has only IO port ranges and no&n; * memory space, i.e.  no access to the CIS. Compared to the PLX chip,&n; * the io range functionalities are exchanged.&n; *&n; * Pheecom sells cards with the TMD chip as &quot;ASIC version&quot;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/timer.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/if_arp.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/wireless.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/wireless.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;pcmcia/cisreg.h&gt;
macro_line|#include &quot;hermes.h&quot;
macro_line|#include &quot;orinoco.h&quot;
DECL|variable|dev_info
r_static
r_char
id|dev_info
(braket
)braket
op_assign
l_string|&quot;orinoco_tmd&quot;
suffix:semicolon
DECL|macro|COR_VALUE
mdefine_line|#define COR_VALUE     (COR_LEVEL_REQ | COR_FUNC_ENA | COR_FUNC_ENA) /* Enable PC card with level triggered irqs and irq requests */
DECL|function|orinoco_tmd_init_one
r_static
r_int
id|orinoco_tmd_init_one
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
id|err
op_assign
l_int|0
suffix:semicolon
id|u32
id|reg
comma
id|addr
suffix:semicolon
r_struct
id|orinoco_private
op_star
id|priv
op_assign
l_int|NULL
suffix:semicolon
r_int
r_int
id|pccard_ioaddr
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|pccard_iolen
op_assign
l_int|0
suffix:semicolon
r_struct
id|net_device
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
id|err
op_assign
id|pci_enable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_return
op_minus
id|EIO
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;TMD setup&bslash;n&quot;
)paren
suffix:semicolon
id|pccard_ioaddr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|2
)paren
suffix:semicolon
id|pccard_iolen
op_assign
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|pccard_ioaddr
comma
id|pccard_iolen
comma
id|dev_info
)paren
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;orinoco_tmd: I/O resource at 0x%lx len 0x%lx busy&bslash;n&quot;
comma
id|pccard_ioaddr
comma
id|pccard_iolen
)paren
suffix:semicolon
id|pccard_ioaddr
op_assign
l_int|0
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|addr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|COR_VALUE
comma
id|addr
)paren
suffix:semicolon
id|mdelay
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|reg
op_assign
id|inb
c_func
(paren
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg
op_ne
id|COR_VALUE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;orinoco_tmd: Error setting TMD COR values %x should be %x&bslash;n&quot;
comma
id|reg
comma
id|COR_VALUE
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|dev
op_assign
id|alloc_orinocodev
c_func
(paren
l_int|0
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|pccard_ioaddr
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;Detected Orinoco/Prism2 TMD device at %s irq:%d, io addr:0x%lx&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
comma
id|pdev-&gt;irq
comma
id|pccard_ioaddr
)paren
suffix:semicolon
id|hermes_struct_init
c_func
(paren
op_amp
(paren
id|priv-&gt;hw
)paren
comma
id|dev-&gt;base_addr
comma
id|HERMES_IO
comma
id|HERMES_16BIT_REGSPACING
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|dev
)paren
suffix:semicolon
id|err
op_assign
id|request_irq
c_func
(paren
id|pdev-&gt;irq
comma
id|orinoco_interrupt
comma
id|SA_SHIRQ
comma
id|dev-&gt;name
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;orinoco_tmd: Error allocating IRQ %d.&bslash;n&quot;
comma
id|pdev-&gt;irq
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|fail
suffix:semicolon
)brace
id|dev-&gt;irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
id|err
op_assign
id|register_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
r_goto
id|fail
suffix:semicolon
r_return
l_int|0
suffix:semicolon
multiline_comment|/* succeeded */
id|fail
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;orinoco_tmd: init_one(), FAIL!&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
)paren
(brace
r_if
c_cond
(paren
id|dev-&gt;irq
)paren
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pccard_ioaddr
)paren
id|release_region
c_func
(paren
id|pccard_ioaddr
comma
id|pccard_iolen
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|orinoco_tmd_remove_one
r_static
r_void
id|__devexit
id|orinoco_tmd_remove_one
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
)paren
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
l_int|NULL
)paren
suffix:semicolon
id|free_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|2
)paren
comma
id|pci_resource_len
c_func
(paren
id|pdev
comma
l_int|2
)paren
)paren
suffix:semicolon
id|pci_disable_device
c_func
(paren
id|pdev
)paren
suffix:semicolon
)brace
DECL|variable|orinoco_tmd_pci_id_table
r_static
r_struct
id|pci_device_id
id|orinoco_tmd_pci_id_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x15e8
comma
l_int|0x0131
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
)brace
comma
multiline_comment|/* NDC and OEMs, e.g. pheecom */
(brace
l_int|0
comma
)brace
comma
)brace
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|orinoco_tmd_pci_id_table
)paren
suffix:semicolon
DECL|variable|orinoco_tmd_driver
r_static
r_struct
id|pci_driver
id|orinoco_tmd_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;orinoco_tmd&quot;
comma
dot
id|id_table
op_assign
id|orinoco_tmd_pci_id_table
comma
dot
id|probe
op_assign
id|orinoco_tmd_init_one
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|orinoco_tmd_remove_one
)paren
comma
dot
id|suspend
op_assign
l_int|0
comma
dot
id|resume
op_assign
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_char
id|version
(braket
)braket
id|__initdata
op_assign
l_string|&quot;orinoco_tmd.c 0.01 (Joerg Dorchain &lt;joerg@dorchain.net&gt;)&quot;
suffix:semicolon
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Joerg Dorchain &lt;joerg@dorchain.net&gt;&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Driver for wireless LAN cards using the TMD7160 PCI bridge&quot;
)paren
suffix:semicolon
macro_line|#ifdef MODULE_LICENSE
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;Dual MPL/GPL&quot;
)paren
suffix:semicolon
macro_line|#endif
DECL|function|orinoco_tmd_init
r_static
r_int
id|__init
id|orinoco_tmd_init
c_func
(paren
r_void
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;%s&bslash;n&quot;
comma
id|version
)paren
suffix:semicolon
r_return
id|pci_module_init
c_func
(paren
op_amp
id|orinoco_tmd_driver
)paren
suffix:semicolon
)brace
DECL|function|orinoco_tmd_exit
r_extern
r_void
id|__exit
id|orinoco_tmd_exit
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|orinoco_tmd_driver
)paren
suffix:semicolon
id|current-&gt;state
op_assign
id|TASK_UNINTERRUPTIBLE
suffix:semicolon
id|schedule_timeout
c_func
(paren
id|HZ
)paren
suffix:semicolon
)brace
DECL|variable|orinoco_tmd_init
id|module_init
c_func
(paren
id|orinoco_tmd_init
)paren
suffix:semicolon
DECL|variable|orinoco_tmd_exit
id|module_exit
c_func
(paren
id|orinoco_tmd_exit
)paren
suffix:semicolon
multiline_comment|/*&n; * Local variables:&n; *  c-indent-level: 8&n; *  c-basic-offset: 8&n; *  tab-width: 8&n; * End:&n; */
eof
