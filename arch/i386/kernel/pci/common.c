multiline_comment|/*&n; *&t;Low-Level PCI Support for PC&n; *&n; *&t;(c) 1999--2000 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/smp.h&gt;
macro_line|#include &quot;pci.h&quot;
macro_line|#ifdef CONFIG_PCI_BIOS
r_extern
r_void
id|pcibios_sort
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
DECL|variable|pci_probe
r_int
r_int
id|pci_probe
op_assign
id|PCI_PROBE_BIOS
op_or
id|PCI_PROBE_CONF1
op_or
id|PCI_PROBE_CONF2
suffix:semicolon
DECL|variable|pcibios_last_bus
r_int
id|pcibios_last_bus
op_assign
op_minus
l_int|1
suffix:semicolon
DECL|variable|pci_root_bus
r_struct
id|pci_bus
op_star
id|pci_root_bus
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pci_root_ops
r_struct
id|pci_ops
op_star
id|pci_root_ops
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pci_config_read
r_int
(paren
op_star
id|pci_config_read
)paren
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
op_star
id|value
)paren
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pci_config_write
r_int
(paren
op_star
id|pci_config_write
)paren
(paren
r_int
id|seg
comma
r_int
id|bus
comma
r_int
id|dev
comma
r_int
id|fn
comma
r_int
id|reg
comma
r_int
id|len
comma
id|u32
id|value
)paren
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/*&n; * This interrupt-safe spinlock protects all accesses to PCI&n; * configuration space.&n; */
DECL|variable|pci_config_lock
id|spinlock_t
id|pci_config_lock
op_assign
id|SPIN_LOCK_UNLOCKED
suffix:semicolon
multiline_comment|/*&n; * Several buggy motherboards address only 16 devices and mirror&n; * them to next 16 IDs. We try to detect this `feature&squot; on all&n; * primary buses (those containing host bridges as they are&n; * expected to be unique) and remove the ghost devices.&n; */
DECL|function|pcibios_fixup_ghosts
r_static
r_void
id|__devinit
id|pcibios_fixup_ghosts
c_func
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
r_struct
id|list_head
op_star
id|ln
comma
op_star
id|mn
suffix:semicolon
r_struct
id|pci_dev
op_star
id|d
comma
op_star
id|e
suffix:semicolon
r_int
id|mirror
op_assign
id|PCI_DEVFN
c_func
(paren
l_int|16
comma
l_int|0
)paren
suffix:semicolon
r_int
id|seen_host_bridge
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: Scanning for ghost devices on bus %d&bslash;n&quot;
comma
id|b-&gt;number
)paren
suffix:semicolon
r_for
c_loop
(paren
id|ln
op_assign
id|b-&gt;devices.next
suffix:semicolon
id|ln
op_ne
op_amp
id|b-&gt;devices
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
id|d
op_assign
id|pci_dev_b
c_func
(paren
id|ln
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|d
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
op_eq
id|PCI_CLASS_BRIDGE_HOST
)paren
id|seen_host_bridge
op_increment
suffix:semicolon
r_for
c_loop
(paren
id|mn
op_assign
id|ln-&gt;next
suffix:semicolon
id|mn
op_ne
op_amp
id|b-&gt;devices
suffix:semicolon
id|mn
op_assign
id|mn-&gt;next
)paren
(brace
id|e
op_assign
id|pci_dev_b
c_func
(paren
id|mn
)paren
suffix:semicolon
r_if
c_cond
(paren
id|e-&gt;devfn
op_ne
id|d-&gt;devfn
op_plus
id|mirror
op_logical_or
id|e-&gt;vendor
op_ne
id|d-&gt;vendor
op_logical_or
id|e-&gt;device
op_ne
id|d-&gt;device
op_logical_or
id|e
op_member_access_from_pointer
r_class
op_ne
id|d
op_member_access_from_pointer
r_class
)paren
r_continue
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
id|PCI_NUM_RESOURCES
suffix:semicolon
id|i
op_increment
)paren
r_if
c_cond
(paren
id|e-&gt;resource
(braket
id|i
)braket
dot
id|start
op_ne
id|d-&gt;resource
(braket
id|i
)braket
dot
id|start
op_logical_or
id|e-&gt;resource
(braket
id|i
)braket
dot
id|end
op_ne
id|d-&gt;resource
(braket
id|i
)braket
dot
id|end
op_logical_or
id|e-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_ne
id|d-&gt;resource
(braket
id|i
)braket
dot
id|flags
)paren
r_continue
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mn
op_eq
op_amp
id|b-&gt;devices
)paren
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|seen_host_bridge
)paren
r_return
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Ignoring ghost devices on bus %02x&bslash;n&quot;
comma
id|b-&gt;number
)paren
suffix:semicolon
id|ln
op_assign
op_amp
id|b-&gt;devices
suffix:semicolon
r_while
c_loop
(paren
id|ln-&gt;next
op_ne
op_amp
id|b-&gt;devices
)paren
(brace
id|d
op_assign
id|pci_dev_b
c_func
(paren
id|ln-&gt;next
)paren
suffix:semicolon
r_if
c_cond
(paren
id|d-&gt;devfn
op_ge
id|mirror
)paren
(brace
id|list_del
c_func
(paren
op_amp
id|d-&gt;global_list
)paren
suffix:semicolon
id|list_del
c_func
(paren
op_amp
id|d-&gt;bus_list
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|d
)paren
suffix:semicolon
)brace
r_else
id|ln
op_assign
id|ln-&gt;next
suffix:semicolon
)brace
)brace
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
multiline_comment|/*&n; *  Called after each bus is probed, but before its children&n; *  are examined.&n; */
DECL|function|pcibios_fixup_bus
r_void
id|__devinit
id|pcibios_fixup_bus
c_func
(paren
r_struct
id|pci_bus
op_star
id|b
)paren
(brace
id|pcibios_fixup_ghosts
c_func
(paren
id|b
)paren
suffix:semicolon
id|pci_read_bridge_bases
c_func
(paren
id|b
)paren
suffix:semicolon
)brace
DECL|function|pcibios_scan_root
r_struct
id|pci_bus
op_star
id|__devinit
id|pcibios_scan_root
c_func
(paren
r_int
id|busnum
)paren
(brace
r_struct
id|list_head
op_star
id|list
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
id|list_for_each
c_func
(paren
id|list
comma
op_amp
id|pci_root_buses
)paren
(brace
id|bus
op_assign
id|pci_bus_b
c_func
(paren
id|list
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;number
op_eq
id|busnum
)paren
(brace
multiline_comment|/* Already scanned */
r_return
id|bus
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;PCI: Probing PCI hardware (bus %02x)&bslash;n&quot;
comma
id|busnum
)paren
suffix:semicolon
r_return
id|pci_scan_bus
c_func
(paren
id|busnum
comma
id|pci_root_ops
comma
l_int|NULL
)paren
suffix:semicolon
)brace
DECL|function|pcibios_init
r_static
r_int
id|__init
id|pcibios_init
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
id|pcibios_irq_init
c_func
(paren
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
id|pcibios_fixup_irqs
c_func
(paren
)paren
suffix:semicolon
id|pcibios_resource_survey
c_func
(paren
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_PCI_BIOS
r_if
c_cond
(paren
(paren
id|pci_probe
op_amp
id|PCI_BIOS_SORT
)paren
op_logical_and
op_logical_neg
(paren
id|pci_probe
op_amp
id|PCI_NO_SORT
)paren
)paren
id|pcibios_sort
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pcibios_init
id|subsys_initcall
c_func
(paren
id|pcibios_init
)paren
suffix:semicolon
DECL|function|pcibios_setup
r_char
op_star
id|__devinit
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;off&quot;
)paren
)paren
(brace
id|pci_probe
op_assign
l_int|0
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_PCI_BIOS
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;bios&quot;
)paren
)paren
(brace
id|pci_probe
op_assign
id|PCI_PROBE_BIOS
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;nobios&quot;
)paren
)paren
(brace
id|pci_probe
op_and_assign
op_complement
id|PCI_PROBE_BIOS
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;nosort&quot;
)paren
)paren
(brace
id|pci_probe
op_or_assign
id|PCI_NO_SORT
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;biosirq&quot;
)paren
)paren
(brace
id|pci_probe
op_or_assign
id|PCI_BIOS_IRQ_SCAN
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_PCI_DIRECT
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;conf1&quot;
)paren
)paren
(brace
id|pci_probe
op_assign
id|PCI_PROBE_CONF1
op_or
id|PCI_NO_CHECKS
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;conf2&quot;
)paren
)paren
(brace
id|pci_probe
op_assign
id|PCI_PROBE_CONF2
op_or
id|PCI_NO_CHECKS
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef CONFIG_ACPI_PCI
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;noacpi&quot;
)paren
)paren
(brace
id|pci_probe
op_or_assign
id|PCI_NO_ACPI_ROUTING
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
macro_line|#endif
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;rom&quot;
)paren
)paren
(brace
id|pci_probe
op_or_assign
id|PCI_ASSIGN_ROMS
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;assign-busses&quot;
)paren
)paren
(brace
id|pci_probe
op_or_assign
id|PCI_ASSIGN_ALL_BUSSES
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strcmp
c_func
(paren
id|str
comma
l_string|&quot;usepirqmask&quot;
)paren
)paren
(brace
id|pci_probe
op_or_assign
id|PCI_USE_PIRQ_MASK
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;irqmask=&quot;
comma
l_int|8
)paren
)paren
(brace
id|pcibios_irq_mask
op_assign
id|simple_strtol
c_func
(paren
id|str
op_plus
l_int|8
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
op_logical_neg
id|strncmp
c_func
(paren
id|str
comma
l_string|&quot;lastbus=&quot;
comma
l_int|8
)paren
)paren
(brace
id|pcibios_last_bus
op_assign
id|simple_strtol
c_func
(paren
id|str
op_plus
l_int|8
comma
l_int|NULL
comma
l_int|0
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
r_return
id|str
suffix:semicolon
)brace
DECL|function|pcibios_assign_all_busses
r_int
r_int
id|pcibios_assign_all_busses
c_func
(paren
r_void
)paren
(brace
r_return
(paren
id|pci_probe
op_amp
id|PCI_ASSIGN_ALL_BUSSES
)paren
ques
c_cond
l_int|1
suffix:colon
l_int|0
suffix:semicolon
)brace
DECL|function|pcibios_enable_device
r_int
id|pcibios_enable_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
(paren
id|err
op_assign
id|pcibios_enable_resources
c_func
(paren
id|dev
)paren
)paren
OL
l_int|0
)paren
r_return
id|err
suffix:semicolon
id|pcibios_enable_irq
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
