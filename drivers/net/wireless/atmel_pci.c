multiline_comment|/*** -*- linux-c -*- **********************************************************&n;&n;     Driver for Atmel at76c502 at76c504 and at76c506 wireless cards.&n;&n;         Copyright 2004 Simon Kelley.&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 2 of the License, or&n;    (at your option) any later version.&n;&n;    This software is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with Atmel wireless lan drivers; if not, write to the Free Software&n;    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA&n;&n;******************************************************************************/
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;atmel.h&quot;
id|MODULE_AUTHOR
c_func
(paren
l_string|&quot;Simon Kelley&quot;
)paren
suffix:semicolon
id|MODULE_DESCRIPTION
c_func
(paren
l_string|&quot;Support for Atmel at76c50x 802.11 wireless ethernet cards.&quot;
)paren
suffix:semicolon
id|MODULE_LICENSE
c_func
(paren
l_string|&quot;GPL&quot;
)paren
suffix:semicolon
id|MODULE_SUPPORTED_DEVICE
c_func
(paren
l_string|&quot;Atmel at76c506 PCI wireless cards&quot;
)paren
suffix:semicolon
DECL|variable|card_ids
r_static
r_struct
id|pci_device_id
id|card_ids
(braket
)braket
op_assign
(brace
(brace
l_int|0x1114
comma
l_int|0x0506
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
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
id|card_ids
)paren
suffix:semicolon
r_static
r_int
id|atmel_pci_probe
c_func
(paren
r_struct
id|pci_dev
op_star
comma
r_const
r_struct
id|pci_device_id
op_star
)paren
suffix:semicolon
r_static
r_void
id|atmel_pci_remove
c_func
(paren
r_struct
id|pci_dev
op_star
)paren
suffix:semicolon
DECL|variable|atmel_driver
r_static
r_struct
id|pci_driver
id|atmel_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;atmel&quot;
comma
dot
id|id_table
op_assign
id|card_ids
comma
dot
id|probe
op_assign
id|atmel_pci_probe
comma
dot
id|remove
op_assign
id|__devexit_p
c_func
(paren
id|atmel_pci_remove
)paren
comma
)brace
suffix:semicolon
DECL|function|atmel_pci_probe
r_static
r_int
id|__devinit
id|atmel_pci_probe
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
id|pent
)paren
(brace
r_struct
id|net_device
op_star
id|dev
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
id|ENODEV
suffix:semicolon
id|pci_set_master
c_func
(paren
id|pdev
)paren
suffix:semicolon
id|dev
op_assign
id|init_atmel_card
c_func
(paren
id|pdev-&gt;irq
comma
id|pdev-&gt;resource
(braket
l_int|1
)braket
dot
id|start
comma
id|ATMEL_FW_TYPE_506
comma
op_amp
id|pdev-&gt;dev
comma
l_int|NULL
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
r_return
op_minus
id|ENODEV
suffix:semicolon
id|pci_set_drvdata
c_func
(paren
id|pdev
comma
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|atmel_pci_remove
r_static
r_void
id|__devexit
id|atmel_pci_remove
c_func
(paren
r_struct
id|pci_dev
op_star
id|pdev
)paren
(brace
id|stop_atmel_card
c_func
(paren
id|pci_get_drvdata
c_func
(paren
id|pdev
)paren
comma
l_int|1
)paren
suffix:semicolon
)brace
DECL|function|atmel_init_module
r_static
r_int
id|__init
id|atmel_init_module
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
id|atmel_driver
)paren
suffix:semicolon
)brace
DECL|function|atmel_cleanup_module
r_static
r_void
id|__exit
id|atmel_cleanup_module
c_func
(paren
r_void
)paren
(brace
id|pci_unregister_driver
c_func
(paren
op_amp
id|atmel_driver
)paren
suffix:semicolon
)brace
DECL|variable|atmel_init_module
id|module_init
c_func
(paren
id|atmel_init_module
)paren
suffix:semicolon
DECL|variable|atmel_cleanup_module
id|module_exit
c_func
(paren
id|atmel_cleanup_module
)paren
suffix:semicolon
eof
