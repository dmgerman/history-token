multiline_comment|/*&n; * Linux ARCnet driver - COM20020 PCI support&n; * Contemporary Controls PCI20 and SOHARD SH-ARC PCI&n; * &n; * Written 1994-1999 by Avery Pennarun,&n; *    based on an ISA version by David Woodhouse.&n; * Written 1999-2000 by Martin Mares &lt;mj@ucw.cz&gt;.&n; * Derived from skeleton.c by Donald Becker.&n; *&n; * Special thanks to Contemporary Controls, Inc. (www.ccontrols.com)&n; *  for sponsoring the further development of this driver.&n; *&n; * **********************&n; *&n; * The original copyright of skeleton.c was as follows:&n; *&n; * skeleton.c Written 1993 by Donald Becker.&n; * Copyright 1993 United States Government as represented by the&n; * Director, National Security Agency.  This software may only be used&n; * and distributed according to the terms of the GNU General Public License as&n; * modified by SRC, incorporated herein by reference.&n; *&n; * **********************&n; *&n; * For more details, see drivers/net/arcnet.c&n; *&n; * **********************&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/arcdevice.h&gt;
macro_line|#include &lt;linux/com20020.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|macro|VERSION
mdefine_line|#define VERSION &quot;arcnet: COM20020 PCI support&bslash;n&quot;
multiline_comment|/* Module parameters */
DECL|variable|node
r_static
r_int
id|node
suffix:semicolon
DECL|variable|device
r_static
r_char
op_star
id|device
suffix:semicolon
multiline_comment|/* use eg. device=&quot;arc1&quot; to change name */
DECL|variable|timeout
r_static
r_int
id|timeout
op_assign
l_int|3
suffix:semicolon
DECL|variable|backplane
r_static
r_int
id|backplane
suffix:semicolon
DECL|variable|clockp
r_static
r_int
id|clockp
suffix:semicolon
DECL|variable|clockm
r_static
r_int
id|clockm
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|node
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|device
comma
l_string|&quot;s&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|timeout
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|backplane
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|clockp
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|clockm
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
DECL|function|com20020pci_probe
r_static
r_int
id|__devinit
id|com20020pci_probe
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
id|id
)paren
(brace
r_struct
id|net_device
op_star
id|dev
suffix:semicolon
r_struct
id|arcnet_local
op_star
id|lp
suffix:semicolon
r_int
id|ioaddr
comma
id|err
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
id|EIO
suffix:semicolon
id|dev
op_assign
id|dev_alloc
c_func
(paren
id|device
ques
c_cond
suffix:colon
l_string|&quot;arc%d&quot;
comma
op_amp
id|err
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev
)paren
r_return
id|err
suffix:semicolon
id|lp
op_assign
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|arcnet_local
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|lp
)paren
(brace
id|err
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out_dev
suffix:semicolon
)brace
id|memset
c_func
(paren
id|lp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|arcnet_local
)paren
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
singleline_comment|// SOHARD needs PCI base addr 4
r_if
c_cond
(paren
id|pdev-&gt;vendor
op_eq
l_int|0x10B5
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;SOHARD&bslash;n&quot;
)paren
suffix:semicolon
id|ioaddr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|4
)paren
suffix:semicolon
)brace
r_else
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;Contemporary Controls&bslash;n&quot;
)paren
suffix:semicolon
id|ioaddr
op_assign
id|pci_resource_start
c_func
(paren
id|pdev
comma
l_int|2
)paren
suffix:semicolon
)brace
singleline_comment|// Dummy access after Reset
singleline_comment|// ARCNET controller needs this access to detect bustype
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
l_int|1
)paren
suffix:semicolon
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|1
)paren
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|dev-&gt;irq
op_assign
id|pdev-&gt;irq
suffix:semicolon
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_assign
id|node
suffix:semicolon
id|lp-&gt;card_name
op_assign
l_string|&quot;PCI COM20020&quot;
suffix:semicolon
id|lp-&gt;card_flags
op_assign
id|id-&gt;driver_data
suffix:semicolon
id|lp-&gt;backplane
op_assign
id|backplane
suffix:semicolon
id|lp-&gt;clockp
op_assign
id|clockp
op_amp
l_int|7
suffix:semicolon
id|lp-&gt;clockm
op_assign
id|clockm
op_amp
l_int|3
suffix:semicolon
id|lp-&gt;timeout
op_assign
id|timeout
suffix:semicolon
id|lp-&gt;hw.owner
op_assign
id|THIS_MODULE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|ioaddr
comma
id|ARCNET_TOTAL_SIZE
comma
l_string|&quot;com20020-pci&quot;
)paren
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_INIT
comma
l_string|&quot;IO region %xh-%xh already allocated.&bslash;n&quot;
comma
id|ioaddr
comma
id|ioaddr
op_plus
id|ARCNET_TOTAL_SIZE
op_minus
l_int|1
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EBUSY
suffix:semicolon
r_goto
id|out_priv
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ASTATUS
c_func
(paren
)paren
op_eq
l_int|0xFF
)paren
(brace
id|BUGMSG
c_func
(paren
id|D_NORMAL
comma
l_string|&quot;IO address %Xh was reported by PCI BIOS, &quot;
l_string|&quot;but seems empty!&bslash;n&quot;
comma
id|ioaddr
)paren
suffix:semicolon
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_priv
suffix:semicolon
)brace
r_if
c_cond
(paren
id|com20020_check
c_func
(paren
id|dev
)paren
)paren
(brace
id|err
op_assign
op_minus
id|EIO
suffix:semicolon
r_goto
id|out_priv
suffix:semicolon
)brace
id|release_region
c_func
(paren
id|ioaddr
comma
id|ARCNET_TOTAL_SIZE
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|com20020_found
c_func
(paren
id|dev
comma
id|SA_SHIRQ
)paren
)paren
op_ne
l_int|0
)paren
r_goto
id|out_priv
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|out_priv
suffix:colon
id|kfree
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
id|out_dev
suffix:colon
id|kfree
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
id|err
suffix:semicolon
)brace
DECL|function|com20020pci_remove
r_static
r_void
id|__devexit
id|com20020pci_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|com20020_remove
c_func
(paren
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
)paren
suffix:semicolon
)brace
DECL|variable|com20020pci_id_table
r_static
r_struct
id|pci_device_id
id|com20020pci_id_table
(braket
)braket
op_assign
(brace
(brace
l_int|0x1571
comma
l_int|0xa001
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
l_int|0x1571
comma
l_int|0xa002
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
l_int|0x1571
comma
l_int|0xa003
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
l_int|0x1571
comma
l_int|0xa004
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
l_int|0x1571
comma
l_int|0xa005
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
l_int|0x1571
comma
l_int|0xa006
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
l_int|0x1571
comma
l_int|0xa007
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
l_int|0x1571
comma
l_int|0xa008
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
l_int|0x1571
comma
l_int|0xa009
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_IS_5MBIT
)brace
comma
(brace
l_int|0x1571
comma
l_int|0xa00a
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_IS_5MBIT
)brace
comma
(brace
l_int|0x1571
comma
l_int|0xa00b
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_IS_5MBIT
)brace
comma
(brace
l_int|0x1571
comma
l_int|0xa00c
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_IS_5MBIT
)brace
comma
(brace
l_int|0x1571
comma
l_int|0xa00d
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_IS_5MBIT
)brace
comma
(brace
l_int|0x1571
comma
l_int|0xa201
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_CAN_10MBIT
)brace
comma
(brace
l_int|0x1571
comma
l_int|0xa202
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_CAN_10MBIT
)brace
comma
(brace
l_int|0x1571
comma
l_int|0xa203
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_CAN_10MBIT
)brace
comma
(brace
l_int|0x1571
comma
l_int|0xa204
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_CAN_10MBIT
)brace
comma
(brace
l_int|0x1571
comma
l_int|0xa205
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_CAN_10MBIT
)brace
comma
(brace
l_int|0x1571
comma
l_int|0xa206
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_CAN_10MBIT
)brace
comma
(brace
l_int|0x10B5
comma
l_int|0x9050
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
l_int|0
comma
l_int|0
comma
id|ARC_CAN_10MBIT
)brace
comma
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
id|com20020pci_id_table
)paren
suffix:semicolon
DECL|variable|com20020pci_driver
r_static
r_struct
id|pci_driver
id|com20020pci_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;com20020&quot;
comma
dot
id|id_table
op_assign
id|com20020pci_id_table
comma
dot
id|probe
op_assign
id|com20020pci_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|com20020pci_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|com20020pci_init
r_static
r_int
id|__init
id|com20020pci_init
c_func
(paren
r_void
)paren
(brace
id|BUGLVL
c_func
(paren
id|D_NORMAL
)paren
id|printk
c_func
(paren
id|VERSION
)paren
suffix:semicolon
r_return
id|pci_module_init
c_func
(paren
op_amp
id|com20020pci_driver
)paren
suffix:semicolon
)brace
DECL|function|com20020pci_cleanup
r_static
r_void
id|__exit
id|com20020pci_cleanup
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|com20020pci_driver
)paren
suffix:semicolon
)brace
id|module_init
c_func
(paren
id|com20020pci_init
)paren
id|module_exit
c_func
(paren
id|com20020pci_cleanup
)paren
eof
