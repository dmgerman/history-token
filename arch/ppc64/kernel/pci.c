multiline_comment|/*&n; * Port for PPC64 David Engebretsen, IBM Corp.&n; * Contains common pci routines for ppc64 platform, pSeries and iSeries brands.&n; * &n; * Copyright (C) 2003 Anton Blanchard &lt;anton@au.ibm.com&gt;, IBM&n; *   Rework, based on alpha PCI code.&n; *&n; *      This program is free software; you can redistribute it and/or&n; *      modify it under the terms of the GNU General Public License&n; *      as published by the Free Software Foundation; either version&n; *      2 of the License, or (at your option) any later version.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/capability.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/bootmem.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/prom.h&gt;
macro_line|#include &lt;asm/pci-bridge.h&gt;
macro_line|#include &lt;asm/byteorder.h&gt;
macro_line|#include &lt;asm/irq.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
macro_line|#include &lt;asm/ppcdebug.h&gt;
macro_line|#include &lt;asm/naca.h&gt;
macro_line|#include &lt;asm/pci_dma.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|variable|pci_probe_only
r_int
r_int
id|pci_probe_only
op_assign
l_int|1
suffix:semicolon
DECL|variable|pci_assign_all_buses
r_int
r_int
id|pci_assign_all_buses
op_assign
l_int|0
suffix:semicolon
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
id|pci_assign_all_buses
suffix:semicolon
)brace
multiline_comment|/* pci_io_base -- the base address from which io bars are offsets.&n; * This is the lowest I/O base address (so bar values are always positive),&n; * and it *must* be the start of ISA space if an ISA bus exists because&n; * ISA drivers use hard coded offsets.  If no ISA bus exists a dummy&n; * page is mapped and isa_io_limit prevents access to it.&n; */
DECL|variable|isa_io_base
r_int
r_int
id|isa_io_base
suffix:semicolon
multiline_comment|/* NULL if no ISA bus */
DECL|variable|pci_io_base
r_int
r_int
id|pci_io_base
suffix:semicolon
r_void
id|pcibios_name_device
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|pcibios_final_fixup
c_func
(paren
r_void
)paren
suffix:semicolon
r_static
r_void
id|fixup_broken_pcnet32
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|fixup_windbond_82c105
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
suffix:semicolon
r_void
id|iSeries_pcibios_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|variable|hose_head
r_struct
id|pci_controller
op_star
id|hose_head
suffix:semicolon
DECL|variable|hose_tail
r_struct
id|pci_controller
op_star
op_star
id|hose_tail
op_assign
op_amp
id|hose_head
suffix:semicolon
DECL|variable|global_phb_number
r_int
id|global_phb_number
suffix:semicolon
multiline_comment|/* Global phb counter */
multiline_comment|/* Cached ISA bridge dev. */
DECL|variable|ppc64_isabridge_dev
r_struct
id|pci_dev
op_star
id|ppc64_isabridge_dev
op_assign
l_int|NULL
suffix:semicolon
DECL|variable|pcibios_fixups
r_struct
id|pci_fixup
id|pcibios_fixups
(braket
)braket
op_assign
(brace
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_TRIDENT
comma
id|PCI_ANY_ID
comma
id|fixup_broken_pcnet32
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_VENDOR_ID_WINBOND
comma
id|PCI_DEVICE_ID_WINBOND_82C105
comma
id|fixup_windbond_82c105
)brace
comma
(brace
id|PCI_FIXUP_HEADER
comma
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|pcibios_name_device
)brace
comma
(brace
l_int|0
)brace
)brace
suffix:semicolon
DECL|function|fixup_broken_pcnet32
r_static
r_void
id|fixup_broken_pcnet32
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
r_if
c_cond
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
op_eq
id|PCI_CLASS_NETWORK_ETHERNET
)paren
)paren
(brace
id|dev-&gt;vendor
op_assign
id|PCI_VENDOR_ID_AMD
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_VENDOR_ID
comma
id|PCI_VENDOR_ID_AMD
)paren
suffix:semicolon
id|pci_name_device
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
DECL|function|fixup_windbond_82c105
r_static
r_void
id|fixup_windbond_82c105
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* Assume the windbond 82c105 is the IDE controller on a&n;&t; * p610.  We should probably be more careful in case&n;&t; * someone tries to plug in a similar adapter.&n;&t; */
r_int
id|i
suffix:semicolon
r_int
r_int
id|reg
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;Using INTC for W82c105 IDE controller.&bslash;n&quot;
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
op_amp
id|reg
)paren
suffix:semicolon
multiline_comment|/* Enable LEGIRQ to use INTC instead of ISA interrupts */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
l_int|0x40
comma
id|reg
op_or
(paren
l_int|1
op_lshift
l_int|11
)paren
)paren
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
id|DEVICE_COUNT_RESOURCE
suffix:semicolon
op_increment
id|i
)paren
(brace
multiline_comment|/* zap the 2nd function of the winbond chip */
r_if
c_cond
(paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_amp
id|IORESOURCE_IO
op_logical_and
id|dev-&gt;bus-&gt;number
op_eq
l_int|0
op_logical_and
id|dev-&gt;devfn
op_eq
l_int|0x81
)paren
id|dev-&gt;resource
(braket
id|i
)braket
dot
id|flags
op_and_assign
op_complement
id|IORESOURCE_IO
suffix:semicolon
)brace
)brace
multiline_comment|/* Given an mmio phys address, find a pci device that implements&n; * this address.  This is of course expensive, but only used&n; * for device initialization or error paths.&n; * For io BARs it is assumed the pci_io_base has already been added&n; * into addr.&n; *&n; * Bridges are ignored although they could be used to optimize the search.&n; */
DECL|function|pci_find_dev_by_addr
r_struct
id|pci_dev
op_star
id|pci_find_dev_by_addr
c_func
(paren
r_int
r_int
id|addr
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
l_int|NULL
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
r_int
id|ioaddr
suffix:semicolon
id|ioaddr
op_assign
(paren
id|addr
OG
id|isa_io_base
)paren
ques
c_cond
id|addr
op_minus
id|isa_io_base
suffix:colon
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|dev
op_assign
id|pci_find_device
c_func
(paren
id|PCI_ANY_ID
comma
id|PCI_ANY_ID
comma
id|dev
)paren
)paren
op_ne
l_int|NULL
)paren
(brace
r_if
c_cond
(paren
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|16
)paren
op_eq
id|PCI_BASE_CLASS_BRIDGE
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
id|DEVICE_COUNT_RESOURCE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|start
op_assign
id|pci_resource_start
c_func
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
r_int
r_int
id|end
op_assign
id|pci_resource_end
c_func
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
r_int
r_int
id|flags
op_assign
id|pci_resource_flags
c_func
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
id|start
op_eq
l_int|0
op_logical_or
op_complement
id|start
op_eq
l_int|0
op_logical_or
id|end
op_eq
l_int|0
op_logical_or
op_complement
id|end
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|IORESOURCE_IO
)paren
op_logical_and
(paren
id|ioaddr
op_ge
id|start
op_logical_and
id|ioaddr
op_le
id|end
)paren
)paren
r_return
id|dev
suffix:semicolon
r_else
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|IORESOURCE_MEM
)paren
op_logical_and
(paren
id|addr
op_ge
id|start
op_logical_and
id|addr
op_le
id|end
)paren
)paren
r_return
id|dev
suffix:semicolon
)brace
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
r_void
id|__devinit
DECL|function|pcibios_resource_to_bus
id|pcibios_resource_to_bus
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|pci_bus_region
op_star
id|region
comma
r_struct
id|resource
op_star
id|res
)paren
(brace
r_int
r_int
id|offset
op_assign
l_int|0
suffix:semicolon
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|PCI_GET_PHB_PTR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hose
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|offset
op_assign
(paren
r_int
r_int
)paren
id|hose-&gt;io_base_virt
op_minus
id|pci_io_base
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|offset
op_assign
id|hose-&gt;pci_mem_offset
suffix:semicolon
id|region-&gt;start
op_assign
id|res-&gt;start
op_minus
id|offset
suffix:semicolon
id|region-&gt;end
op_assign
id|res-&gt;end
op_minus
id|offset
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_HOTPLUG
DECL|variable|pcibios_resource_to_bus
id|EXPORT_SYMBOL
c_func
(paren
id|pcibios_resource_to_bus
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * We need to avoid collisions with `mirrored&squot; VGA ports&n; * and other strange ISA hardware, so we always want the&n; * addresses to be allocated in the 0x000-0x0ff region&n; * modulo 0x400.&n; *&n; * Why? Because some silly external IO cards only decode&n; * the low 10 bits of the IO address. The 0x00-0xff region&n; * is reserved for motherboard devices that decode all 16&n; * bits, so it&squot;s ok to allocate at, say, 0x2800-0x28ff,&n; * but we want to try to avoid allocating at 0x2900-0x2bff&n; * which might have be mirrored at 0x0100-0x03ff..&n; */
DECL|function|pcibios_align_resource
r_void
id|pcibios_align_resource
c_func
(paren
r_void
op_star
id|data
comma
r_struct
id|resource
op_star
id|res
comma
r_int
r_int
id|size
comma
r_int
r_int
id|align
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|data
suffix:semicolon
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|PCI_GET_PHB_PTR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|start
op_assign
id|res-&gt;start
suffix:semicolon
r_int
r_int
id|alignto
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
(brace
r_int
r_int
id|offset
op_assign
(paren
r_int
r_int
)paren
id|hose-&gt;io_base_virt
op_minus
id|pci_io_base
suffix:semicolon
multiline_comment|/* Make sure we start at our min on all hoses */
r_if
c_cond
(paren
id|start
op_minus
id|offset
OL
id|PCIBIOS_MIN_IO
)paren
id|start
op_assign
id|PCIBIOS_MIN_IO
op_plus
id|offset
suffix:semicolon
multiline_comment|/*&n;&t;&t; * Put everything into 0x00-0xff region modulo 0x400&n;&t;&t; */
r_if
c_cond
(paren
id|start
op_amp
l_int|0x300
)paren
id|start
op_assign
(paren
id|start
op_plus
l_int|0x3ff
)paren
op_amp
op_complement
l_int|0x3ff
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
(brace
multiline_comment|/* Make sure we start at our min on all hoses */
r_if
c_cond
(paren
id|start
op_minus
id|hose-&gt;pci_mem_offset
OL
id|PCIBIOS_MIN_MEM
)paren
id|start
op_assign
id|PCIBIOS_MIN_MEM
op_plus
id|hose-&gt;pci_mem_offset
suffix:semicolon
multiline_comment|/* Align to multiple of size of minimum base.  */
id|alignto
op_assign
id|max
c_func
(paren
l_int|0x1000UL
comma
id|align
)paren
suffix:semicolon
id|start
op_assign
id|ALIGN
c_func
(paren
id|start
comma
id|alignto
)paren
suffix:semicolon
)brace
id|res-&gt;start
op_assign
id|start
suffix:semicolon
)brace
multiline_comment|/* &n; * Allocate pci_controller(phb) initialized common variables. &n; */
r_struct
id|pci_controller
op_star
id|__init
DECL|function|pci_alloc_pci_controller
id|pci_alloc_pci_controller
c_func
(paren
r_enum
id|phb_types
id|controller_type
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_char
op_star
id|model
suffix:semicolon
id|hose
op_assign
(paren
r_struct
id|pci_controller
op_star
)paren
id|alloc_bootmem
c_func
(paren
r_sizeof
(paren
r_struct
id|pci_controller
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hose
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Allocate pci_controller failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|NULL
suffix:semicolon
)brace
id|memset
c_func
(paren
id|hose
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|pci_controller
)paren
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|controller_type
)paren
(brace
r_case
id|phb_type_python
suffix:colon
id|model
op_assign
l_string|&quot;PHB PY&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|phb_type_speedwagon
suffix:colon
id|model
op_assign
l_string|&quot;PHB SW&quot;
suffix:semicolon
r_break
suffix:semicolon
r_case
id|phb_type_winnipeg
suffix:colon
id|model
op_assign
l_string|&quot;PHB WP&quot;
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|model
op_assign
l_string|&quot;PHB UK&quot;
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|strlen
c_func
(paren
id|model
)paren
OL
l_int|8
)paren
(brace
id|strcpy
c_func
(paren
id|hose-&gt;what
comma
id|model
)paren
suffix:semicolon
)brace
r_else
id|memcpy
c_func
(paren
id|hose-&gt;what
comma
id|model
comma
l_int|7
)paren
suffix:semicolon
id|hose-&gt;type
op_assign
id|controller_type
suffix:semicolon
id|hose-&gt;global_number
op_assign
id|global_phb_number
op_increment
suffix:semicolon
op_star
id|hose_tail
op_assign
id|hose
suffix:semicolon
id|hose_tail
op_assign
op_amp
id|hose-&gt;next
suffix:semicolon
r_return
id|hose
suffix:semicolon
)brace
DECL|function|pcibios_claim_one_bus
r_static
r_void
id|__init
id|pcibios_claim_one_bus
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
id|ld
suffix:semicolon
r_struct
id|pci_bus
op_star
id|child_bus
suffix:semicolon
r_for
c_loop
(paren
id|ld
op_assign
id|b-&gt;devices.next
suffix:semicolon
id|ld
op_ne
op_amp
id|b-&gt;devices
suffix:semicolon
id|ld
op_assign
id|ld-&gt;next
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
op_assign
id|pci_dev_b
c_func
(paren
id|ld
)paren
suffix:semicolon
r_int
id|i
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
(brace
r_struct
id|resource
op_star
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;parent
op_logical_or
op_logical_neg
id|r-&gt;start
op_logical_or
op_logical_neg
id|r-&gt;flags
)paren
r_continue
suffix:semicolon
id|pci_claim_resource
c_func
(paren
id|dev
comma
id|i
)paren
suffix:semicolon
)brace
)brace
id|list_for_each_entry
c_func
(paren
id|child_bus
comma
op_amp
id|b-&gt;children
comma
id|node
)paren
id|pcibios_claim_one_bus
c_func
(paren
id|child_bus
)paren
suffix:semicolon
)brace
DECL|function|pcibios_claim_of_setup
r_static
r_void
id|__init
id|pcibios_claim_of_setup
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|lb
suffix:semicolon
r_for
c_loop
(paren
id|lb
op_assign
id|pci_root_buses.next
suffix:semicolon
id|lb
op_ne
op_amp
id|pci_root_buses
suffix:semicolon
id|lb
op_assign
id|lb-&gt;next
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
op_assign
id|pci_bus_b
c_func
(paren
id|lb
)paren
suffix:semicolon
id|pcibios_claim_one_bus
c_func
(paren
id|b
)paren
suffix:semicolon
)brace
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
r_struct
id|pci_controller
op_star
id|hose
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
macro_line|#ifdef CONFIG_PPC_ISERIES
id|iSeries_pcibios_init
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
singleline_comment|//ppc64_boot_msg(0x40, &quot;PCI Probe&quot;);
id|printk
c_func
(paren
l_string|&quot;PCI: Probing PCI hardware&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Scan all of the recorded PCI controllers.  */
r_for
c_loop
(paren
id|hose
op_assign
id|hose_head
suffix:semicolon
id|hose
suffix:semicolon
id|hose
op_assign
id|hose-&gt;next
)paren
(brace
id|hose-&gt;last_busno
op_assign
l_int|0xff
suffix:semicolon
id|bus
op_assign
id|pci_scan_bus
c_func
(paren
id|hose-&gt;first_busno
comma
id|hose-&gt;ops
comma
id|hose-&gt;arch_data
)paren
suffix:semicolon
id|hose-&gt;bus
op_assign
id|bus
suffix:semicolon
id|hose-&gt;last_busno
op_assign
id|bus-&gt;subordinate
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pci_probe_only
)paren
id|pcibios_claim_of_setup
c_func
(paren
)paren
suffix:semicolon
r_else
multiline_comment|/* FIXME: `else&squot; will be removed when&n;&t;&t;   pci_assign_unassigned_resources() is able to work&n;&t;&t;   correctly with [partially] allocated PCI tree. */
id|pci_assign_unassigned_resources
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Call machine dependent fixup */
id|pcibios_final_fixup
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Cache the location of the ISA bridge (if we have one) */
id|ppc64_isabridge_dev
op_assign
id|pci_find_class
c_func
(paren
id|PCI_CLASS_BRIDGE_ISA
op_lshift
l_int|8
comma
l_int|NULL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ppc64_isabridge_dev
op_ne
l_int|NULL
)paren
id|printk
c_func
(paren
l_string|&quot;ISA bridge at %s&bslash;n&quot;
comma
id|ppc64_isabridge_dev-&gt;slot_name
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Probing PCI hardware done&bslash;n&quot;
)paren
suffix:semicolon
singleline_comment|//ppc64_boot_msg(0x41, &quot;PCI Done&quot;);
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
id|__init
op_star
id|pcibios_setup
c_func
(paren
r_char
op_star
id|str
)paren
(brace
r_return
id|str
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
comma
r_int
id|mask
)paren
(brace
id|u16
id|cmd
comma
id|oldcmd
suffix:semicolon
r_int
id|i
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|cmd
)paren
suffix:semicolon
id|oldcmd
op_assign
id|cmd
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
(brace
r_struct
id|resource
op_star
id|res
op_assign
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
multiline_comment|/* Only set up the requested stuff */
r_if
c_cond
(paren
op_logical_neg
(paren
id|mask
op_amp
(paren
l_int|1
op_lshift
id|i
)paren
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_IO
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
)brace
r_if
c_cond
(paren
id|cmd
op_ne
id|oldcmd
)paren
(brace
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PCI: Enabling device: (%s), cmd %x&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|cmd
)paren
suffix:semicolon
multiline_comment|/* Enable the appropriate bits in the PCI command register.  */
id|pci_write_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
id|cmd
)paren
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Return the domain number for this bus.&n; */
DECL|function|pci_domain_nr
r_int
id|pci_domain_nr
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|PCI_GET_PHB_PTR
c_func
(paren
id|bus
)paren
suffix:semicolon
r_return
id|hose-&gt;global_number
suffix:semicolon
)brace
multiline_comment|/* Set the name of the bus as it appears in /proc/bus/pci */
DECL|function|pci_name_bus
r_int
id|pci_name_bus
c_func
(paren
r_char
op_star
id|name
comma
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|PCI_GET_PHB_PTR
c_func
(paren
id|bus
)paren
suffix:semicolon
r_if
c_cond
(paren
id|hose-&gt;buid
)paren
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%04x:%02x&quot;
comma
id|pci_domain_nr
c_func
(paren
id|bus
)paren
comma
id|bus-&gt;number
)paren
suffix:semicolon
r_else
id|sprintf
c_func
(paren
id|name
comma
l_string|&quot;%02x&quot;
comma
id|bus-&gt;number
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * Platform support for /proc/bus/pci/X/Y mmap()s,&n; * modelled on the sparc64 implementation by Dave Miller.&n; *  -- paulus.&n; */
multiline_comment|/*&n; * Adjust vm_pgoff of VMA such that it is the physical page offset&n; * corresponding to the 32-bit pci bus offset for DEV requested by the user.&n; *&n; * Basically, the user finds the base address for his device which he wishes&n; * to mmap.  They read the 32-bit value from the config space base register,&n; * add whatever PAGE_SIZE multiple offset they wish, and feed this into the&n; * offset parameter of mmap on /proc/bus/pci/XXX for that device.&n; *&n; * Returns negative error code on failure, zero on success.&n; */
r_static
id|__inline__
r_int
DECL|function|__pci_mmap_make_offset
id|__pci_mmap_make_offset
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
)paren
(brace
r_struct
id|pci_controller
op_star
id|hose
op_assign
id|PCI_GET_PHB_PTR
c_func
(paren
id|dev
)paren
suffix:semicolon
r_int
r_int
id|offset
op_assign
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
suffix:semicolon
r_int
r_int
id|io_offset
op_assign
l_int|0
suffix:semicolon
r_int
id|i
comma
id|res_bit
suffix:semicolon
r_if
c_cond
(paren
id|hose
op_eq
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* should never happen */
multiline_comment|/* If memory, add on the PCI bridge address offset */
r_if
c_cond
(paren
id|mmap_state
op_eq
id|pci_mmap_mem
)paren
(brace
id|offset
op_add_assign
id|hose-&gt;pci_mem_offset
suffix:semicolon
id|res_bit
op_assign
id|IORESOURCE_MEM
suffix:semicolon
)brace
r_else
(brace
id|io_offset
op_assign
(paren
r_int
r_int
)paren
id|hose-&gt;io_base_virt
suffix:semicolon
id|offset
op_add_assign
id|io_offset
suffix:semicolon
id|res_bit
op_assign
id|IORESOURCE_IO
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Check that the offset requested corresponds to one of the&n;&t; * resources of the device.&n;&t; */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
op_le
id|PCI_ROM_RESOURCE
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|resource
op_star
id|rp
op_assign
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_int
id|flags
op_assign
id|rp-&gt;flags
suffix:semicolon
multiline_comment|/* treat ROM as memory (should be already) */
r_if
c_cond
(paren
id|i
op_eq
id|PCI_ROM_RESOURCE
)paren
id|flags
op_or_assign
id|IORESOURCE_MEM
suffix:semicolon
multiline_comment|/* Active and same type? */
r_if
c_cond
(paren
(paren
id|flags
op_amp
id|res_bit
)paren
op_eq
l_int|0
)paren
r_continue
suffix:semicolon
multiline_comment|/* In the range of this resource? */
r_if
c_cond
(paren
id|offset
template_param
id|rp-&gt;end
)paren
r_continue
suffix:semicolon
multiline_comment|/* found it! construct the final physical address */
r_if
c_cond
(paren
id|mmap_state
op_eq
id|pci_mmap_io
)paren
id|offset
op_add_assign
id|hose-&gt;io_base_phys
op_minus
id|io_offset
suffix:semicolon
id|vma-&gt;vm_pgoff
op_assign
id|offset
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
multiline_comment|/*&n; * Set vm_flags of VMA, as appropriate for this architecture, for a pci device&n; * mapping.&n; */
r_static
id|__inline__
r_void
DECL|function|__pci_mmap_set_flags
id|__pci_mmap_set_flags
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
)paren
(brace
id|vma-&gt;vm_flags
op_or_assign
id|VM_SHM
op_or
id|VM_LOCKED
op_or
id|VM_IO
suffix:semicolon
)brace
multiline_comment|/*&n; * Set vm_page_prot of VMA, as appropriate for this architecture, for a pci&n; * device mapping.&n; */
r_static
id|__inline__
r_void
DECL|function|__pci_mmap_set_pgprot
id|__pci_mmap_set_pgprot
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
comma
r_int
id|write_combine
)paren
(brace
r_int
id|prot
op_assign
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
multiline_comment|/* XXX would be nice to have a way to ask for write-through */
id|prot
op_or_assign
id|_PAGE_NO_CACHE
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|write_combine
)paren
id|prot
op_or_assign
id|_PAGE_GUARDED
suffix:semicolon
id|vma-&gt;vm_page_prot
op_assign
id|__pgprot
c_func
(paren
id|prot
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Perform the actual remap of the pages for a PCI device mapping, as&n; * appropriate for this architecture.  The region in the process to map&n; * is described by vm_start and vm_end members of VMA, the base physical&n; * address is found in vm_pgoff.&n; * The pci device structure is provided so that architectures may make mapping&n; * decisions on a per-device or per-bus basis.&n; *&n; * Returns a negative error code on failure, zero on success.&n; */
DECL|function|pci_mmap_page_range
r_int
id|pci_mmap_page_range
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_enum
id|pci_mmap_state
id|mmap_state
comma
r_int
id|write_combine
)paren
(brace
r_int
id|ret
suffix:semicolon
id|ret
op_assign
id|__pci_mmap_make_offset
c_func
(paren
id|dev
comma
id|vma
comma
id|mmap_state
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
)paren
r_return
id|ret
suffix:semicolon
id|__pci_mmap_set_flags
c_func
(paren
id|dev
comma
id|vma
comma
id|mmap_state
)paren
suffix:semicolon
id|__pci_mmap_set_pgprot
c_func
(paren
id|dev
comma
id|vma
comma
id|mmap_state
comma
id|write_combine
)paren
suffix:semicolon
id|ret
op_assign
id|remap_page_range
c_func
(paren
id|vma
comma
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_pgoff
op_lshift
id|PAGE_SHIFT
comma
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
comma
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
eof
