macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
DECL|function|pci_range_ck
r_int
id|pci_range_ck
c_func
(paren
r_int
r_char
id|bus
comma
r_int
r_char
id|dev
)paren
(brace
r_if
c_cond
(paren
(paren
(paren
id|bus
op_eq
l_int|0
)paren
op_logical_or
(paren
id|bus
op_eq
l_int|1
)paren
)paren
op_logical_and
(paren
id|dev
op_ge
l_int|6
)paren
op_logical_and
(paren
id|dev
op_le
l_int|8
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/*&n; * After detecting all agents over the PCI , this function is called&n; * in order to give an interrupt number for each PCI device starting&n; * from IRQ 20. It does also enables master for each device.&n; */
DECL|function|pcibios_fixup_bus
r_void
id|__devinit
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_int
r_int
id|irq
op_assign
l_int|20
suffix:semicolon
r_struct
id|pci_bus
op_star
id|current_bus
op_assign
id|bus
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
id|list_head
op_star
id|devices_link
suffix:semicolon
id|list_for_each
c_func
(paren
id|devices_link
comma
op_amp
(paren
id|current_bus-&gt;devices
)paren
)paren
(brace
id|dev
op_assign
id|pci_dev_b
c_func
(paren
id|devices_link
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_ne
l_int|NULL
)paren
(brace
id|dev-&gt;irq
op_assign
id|irq
op_increment
suffix:semicolon
multiline_comment|/* Assign an interrupt number for the device */
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_INTERRUPT_LINE
comma
id|irq
)paren
suffix:semicolon
id|pcibios_set_master
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
)brace
eof
