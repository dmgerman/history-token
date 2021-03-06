multiline_comment|/*&n; * Minimalist driver for a generic PCI-to-EISA bridge.&n; *&n; * (C) 2003 Marc Zyngier &lt;maz@wild-wind.fr.eu.org&gt;&n; *&n; * This code is released under the GPL version 2.&n; *&n; * Ivan Kokshaysky &lt;ink@jurassic.park.msu.ru&gt; :&n; * Generalisation from i82375 to PCI_CLASS_BRIDGE_EISA.&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/device.h&gt;
macro_line|#include &lt;linux/eisa.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/init.h&gt;
multiline_comment|/* There is only *one* pci_eisa device per machine, right ? */
DECL|variable|pci_eisa_root
r_static
r_struct
id|eisa_root_device
id|pci_eisa_root
suffix:semicolon
DECL|function|pci_eisa_init
r_static
r_int
id|__devinit
id|pci_eisa_init
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
id|rc
suffix:semicolon
r_if
c_cond
(paren
(paren
id|rc
op_assign
id|pci_enable_device
(paren
id|pdev
)paren
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;pci_eisa : Could not enable device %s&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|pdev
)paren
)paren
suffix:semicolon
r_return
id|rc
suffix:semicolon
)brace
id|pci_eisa_root.dev
op_assign
op_amp
id|pdev-&gt;dev
suffix:semicolon
id|pci_eisa_root.dev-&gt;driver_data
op_assign
op_amp
id|pci_eisa_root
suffix:semicolon
id|pci_eisa_root.res
op_assign
id|pdev-&gt;bus-&gt;resource
(braket
l_int|0
)braket
suffix:semicolon
id|pci_eisa_root.bus_base_addr
op_assign
id|pdev-&gt;bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|start
suffix:semicolon
id|pci_eisa_root.slots
op_assign
id|EISA_MAX_SLOTS
suffix:semicolon
id|pci_eisa_root.dma_mask
op_assign
id|pdev-&gt;dma_mask
suffix:semicolon
r_if
c_cond
(paren
id|eisa_root_register
(paren
op_amp
id|pci_eisa_root
)paren
)paren
(brace
id|printk
(paren
id|KERN_ERR
l_string|&quot;pci_eisa : Could not register EISA root&bslash;n&quot;
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
DECL|variable|pci_eisa_pci_tbl
r_static
r_struct
id|pci_device_id
id|pci_eisa_pci_tbl
(braket
)braket
op_assign
(brace
(brace
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|PCI_CLASS_BRIDGE_EISA
op_lshift
l_int|8
comma
l_int|0xffff00
comma
l_int|0
)brace
comma
(brace
l_int|0
comma
)brace
)brace
suffix:semicolon
DECL|variable|pci_eisa_driver
r_static
r_struct
id|pci_driver
id|pci_eisa_driver
op_assign
(brace
dot
id|name
op_assign
l_string|&quot;pci_eisa&quot;
comma
dot
id|id_table
op_assign
id|pci_eisa_pci_tbl
comma
dot
id|probe
op_assign
id|pci_eisa_init
comma
)brace
suffix:semicolon
DECL|function|pci_eisa_init_module
r_static
r_int
id|__init
id|pci_eisa_init_module
(paren
r_void
)paren
(brace
r_return
id|pci_register_driver
(paren
op_amp
id|pci_eisa_driver
)paren
suffix:semicolon
)brace
DECL|variable|pci_eisa_init_module
id|device_initcall
c_func
(paren
id|pci_eisa_init_module
)paren
suffix:semicolon
id|MODULE_DEVICE_TABLE
c_func
(paren
id|pci
comma
id|pci_eisa_pci_tbl
)paren
suffix:semicolon
eof
