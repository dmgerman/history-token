multiline_comment|/*&n; *&t;Low-Level PCI Support for SGI Visual Workstation&n; *&n; *&t;(c) 1999--2000 Martin Mares &lt;mj@ucw.cz&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &quot;cobalt.h&quot;
macro_line|#include &quot;lithium.h&quot;
macro_line|#include &quot;pci.h&quot;
DECL|variable|broken_hp_bios_irq9
r_int
id|broken_hp_bios_irq9
suffix:semicolon
r_extern
r_struct
id|pci_ops
id|pci_direct_conf1
suffix:semicolon
DECL|function|pci_visws_enable_irq
r_static
r_int
id|pci_visws_enable_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pcibios_enable_irq
r_int
(paren
op_star
id|pcibios_enable_irq
)paren
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
op_assign
op_amp
id|pci_visws_enable_irq
suffix:semicolon
DECL|function|pcibios_penalize_isa_irq
r_void
id|__init
id|pcibios_penalize_isa_irq
c_func
(paren
r_int
id|irq
)paren
(brace
)brace
DECL|variable|pci_bus0
DECL|variable|pci_bus1
r_int
r_int
id|pci_bus0
comma
id|pci_bus1
suffix:semicolon
DECL|function|bridge_swizzle
r_static
r_inline
id|u8
id|bridge_swizzle
c_func
(paren
id|u8
id|pin
comma
id|u8
id|slot
)paren
(brace
r_return
(paren
(paren
(paren
id|pin
op_minus
l_int|1
)paren
op_plus
id|slot
)paren
op_mod
l_int|4
)paren
op_plus
l_int|1
suffix:semicolon
)brace
DECL|function|visws_swizzle
r_static
id|u8
id|__init
id|visws_swizzle
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
op_star
id|pinp
)paren
(brace
id|u8
id|pin
op_assign
op_star
id|pinp
suffix:semicolon
r_while
c_loop
(paren
id|dev-&gt;bus-&gt;self
)paren
(brace
multiline_comment|/* Move up the chain of bridges. */
id|pin
op_assign
id|bridge_swizzle
c_func
(paren
id|pin
comma
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
)paren
suffix:semicolon
id|dev
op_assign
id|dev-&gt;bus-&gt;self
suffix:semicolon
)brace
op_star
id|pinp
op_assign
id|pin
suffix:semicolon
r_return
id|PCI_SLOT
c_func
(paren
id|dev-&gt;devfn
)paren
suffix:semicolon
)brace
DECL|function|visws_map_irq
r_static
r_int
id|__init
id|visws_map_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
id|u8
id|slot
comma
id|u8
id|pin
)paren
(brace
r_int
id|irq
comma
id|bus
op_assign
id|dev-&gt;bus-&gt;number
suffix:semicolon
id|pin
op_decrement
suffix:semicolon
multiline_comment|/* Nothing useful at PIIX4 pin 1 */
r_if
c_cond
(paren
id|bus
op_eq
id|pci_bus0
op_logical_and
id|slot
op_eq
l_int|4
op_logical_and
id|pin
op_eq
l_int|0
)paren
r_return
op_minus
l_int|1
suffix:semicolon
multiline_comment|/* PIIX4 USB is on Bus 0, Slot 4, Line 3 */
r_if
c_cond
(paren
id|bus
op_eq
id|pci_bus0
op_logical_and
id|slot
op_eq
l_int|4
op_logical_and
id|pin
op_eq
l_int|3
)paren
(brace
id|irq
op_assign
id|CO_IRQ
c_func
(paren
id|CO_APIC_PIIX4_USB
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* First pin spread down 1 APIC entry per slot */
r_if
c_cond
(paren
id|pin
op_eq
l_int|0
)paren
(brace
id|irq
op_assign
id|CO_IRQ
c_func
(paren
(paren
id|bus
op_eq
id|pci_bus0
ques
c_cond
id|CO_APIC_PCIB_BASE0
suffix:colon
id|CO_APIC_PCIA_BASE0
)paren
op_plus
id|slot
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* lines 1,2,3 from any slot is shared in this twirly pattern */
r_if
c_cond
(paren
id|bus
op_eq
id|pci_bus1
)paren
(brace
multiline_comment|/* lines 1-3 from devices 0 1 rotate over 2 apic entries */
id|irq
op_assign
id|CO_IRQ
c_func
(paren
id|CO_APIC_PCIA_BASE123
op_plus
(paren
(paren
id|slot
op_plus
(paren
id|pin
op_minus
l_int|1
)paren
)paren
op_mod
l_int|2
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* bus == pci_bus0 */
multiline_comment|/* lines 1-3 from devices 0-3 rotate over 3 apic entries */
r_if
c_cond
(paren
id|slot
op_eq
l_int|0
)paren
id|slot
op_assign
l_int|3
suffix:semicolon
multiline_comment|/* same pattern */
id|irq
op_assign
id|CO_IRQ
c_func
(paren
id|CO_APIC_PCIA_BASE123
op_plus
(paren
(paren
l_int|3
op_minus
id|slot
)paren
op_plus
(paren
id|pin
op_minus
l_int|1
)paren
op_mod
l_int|3
)paren
)paren
suffix:semicolon
)brace
id|out
suffix:colon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PCI: Bus %d Slot %d Line %d -&gt; IRQ %d&bslash;n&quot;
comma
id|bus
comma
id|slot
comma
id|pin
comma
id|irq
)paren
suffix:semicolon
r_return
id|irq
suffix:semicolon
)brace
DECL|function|pcibios_update_irq
r_void
id|__init
id|pcibios_update_irq
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|irq
)paren
(brace
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
multiline_comment|/* The VISWS supports configuration access type 1 only */
id|pci_probe
op_assign
(paren
id|pci_probe
op_or
id|PCI_PROBE_CONF1
)paren
op_amp
op_complement
(paren
id|PCI_PROBE_BIOS
op_or
id|PCI_PROBE_CONF2
)paren
suffix:semicolon
id|pci_bus0
op_assign
id|li_pcib_read16
c_func
(paren
id|LI_PCI_BUSNUM
)paren
op_amp
l_int|0xff
suffix:semicolon
id|pci_bus1
op_assign
id|li_pcia_read16
c_func
(paren
id|LI_PCI_BUSNUM
)paren
op_amp
l_int|0xff
suffix:semicolon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: Lithium bridge A bus: %u, &quot;
l_string|&quot;bridge B (PIIX4) bus: %u&bslash;n&quot;
comma
id|pci_bus1
comma
id|pci_bus0
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
id|pci_bus0
comma
op_amp
id|pci_direct_conf1
comma
l_int|NULL
)paren
suffix:semicolon
id|pci_scan_bus
c_func
(paren
id|pci_bus1
comma
op_amp
id|pci_direct_conf1
comma
l_int|NULL
)paren
suffix:semicolon
id|pci_fixup_irqs
c_func
(paren
id|visws_swizzle
comma
id|visws_map_irq
)paren
suffix:semicolon
id|pcibios_resource_survey
c_func
(paren
)paren
suffix:semicolon
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
eof
