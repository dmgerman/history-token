multiline_comment|/*&n; * legacy.c - traditional, old school PCI bus probing&n; */
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/*&n; * Discover remaining PCI buses in case there are peer host bridges.&n; * We use the number of last PCI bus provided by the PCI BIOS.&n; */
DECL|function|pcibios_fixup_peer_bridges
r_static
r_void
id|__devinit
id|pcibios_fixup_peer_bridges
c_func
(paren
r_void
)paren
(brace
r_int
id|n
suffix:semicolon
r_struct
id|pci_bus
id|bus
suffix:semicolon
r_struct
id|pci_dev
id|dev
suffix:semicolon
id|u16
id|l
suffix:semicolon
r_if
c_cond
(paren
id|pcibios_last_bus
op_le
l_int|0
op_logical_or
id|pcibios_last_bus
op_ge
l_int|0xff
)paren
r_return
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: Peer bridge fixup&bslash;n&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
id|n
op_assign
l_int|0
suffix:semicolon
id|n
op_le
id|pcibios_last_bus
suffix:semicolon
id|n
op_increment
)paren
(brace
r_if
c_cond
(paren
id|pci_bus_exists
c_func
(paren
op_amp
id|pci_root_buses
comma
id|n
)paren
)paren
r_continue
suffix:semicolon
id|bus.number
op_assign
id|n
suffix:semicolon
id|bus.ops
op_assign
id|pci_root_ops
suffix:semicolon
id|dev.bus
op_assign
op_amp
id|bus
suffix:semicolon
r_for
c_loop
(paren
id|dev.devfn
op_assign
l_int|0
suffix:semicolon
id|dev.devfn
OL
l_int|256
suffix:semicolon
id|dev.devfn
op_add_assign
l_int|8
)paren
r_if
c_cond
(paren
op_logical_neg
id|pci_read_config_word
c_func
(paren
op_amp
id|dev
comma
id|PCI_VENDOR_ID
comma
op_amp
id|l
)paren
op_logical_and
id|l
op_ne
l_int|0x0000
op_logical_and
id|l
op_ne
l_int|0xffff
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;Found device at %02x:%02x [%04x]&bslash;n&quot;
comma
id|n
comma
id|dev.devfn
comma
id|l
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Discovered peer bus %02x&bslash;n&quot;
comma
id|n
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
id|n
comma
id|pci_root_ops
comma
l_int|NULL
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|function|pci_legacy_init
r_static
r_int
id|__init
id|pci_legacy_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|pci_root_ops
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: System does not support PCI&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;PCI: Probing PCI hardware&bslash;n&quot;
)paren
suffix:semicolon
id|pci_root_bus
op_assign
id|pcibios_scan_root
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pci_use_acpi_routing
)paren
id|pcibios_fixup_peer_bridges
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pci_legacy_init
id|subsys_initcall
c_func
(paren
id|pci_legacy_init
)paren
suffix:semicolon
eof
