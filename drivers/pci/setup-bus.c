multiline_comment|/*&n; *&t;drivers/pci/setup-bus.c&n; *&n; * Extruded from code written by&n; *      Dave Rusling (david.rusling@reo.mts.dec.com)&n; *      David Mosberger (davidm@cs.arizona.edu)&n; *&t;David Miller (davem@redhat.com)&n; *&n; * Support routines for initializing a PCI subsystem.&n; */
multiline_comment|/*&n; * Nov 2000, Ivan Kokshaysky &lt;ink@jurassic.park.msu.ru&gt;&n; *&t;     PCI-PCI bridges cleanup, sorted resource allocation.&n; * Feb 2002, Ivan Kokshaysky &lt;ink@jurassic.park.msu.ru&gt;&n; *&t;     Converted to allocation in 3 passes, which gives&n; *&t;     tighter packing. Prefetchable range support.&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
DECL|macro|DEBUG_CONFIG
mdefine_line|#define DEBUG_CONFIG 1
macro_line|#if DEBUG_CONFIG
DECL|macro|DBGC
macro_line|# define DBGC(args)     printk args
macro_line|#else
DECL|macro|DBGC
macro_line|# define DBGC(args)
macro_line|#endif
DECL|macro|ROUND_UP
mdefine_line|#define ROUND_UP(x, a)&t;&t;(((x) + (a) - 1) &amp; ~((a) - 1))
multiline_comment|/*&n; * FIXME: IO should be max 256 bytes.  However, since we may&n; * have a P2P bridge below a cardbus bridge, we need 4K.&n; */
DECL|macro|CARDBUS_IO_SIZE
mdefine_line|#define CARDBUS_IO_SIZE&t;&t;(4096)
DECL|macro|CARDBUS_MEM_SIZE
mdefine_line|#define CARDBUS_MEM_SIZE&t;(32*1024*1024)
r_static
r_int
id|__devinit
DECL|function|pbus_assign_resources_sorted
id|pbus_assign_resources_sorted
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
id|resource
op_star
id|res
suffix:semicolon
r_struct
id|resource_list
id|head
comma
op_star
id|list
comma
op_star
id|tmp
suffix:semicolon
r_int
id|idx
comma
id|found_vga
op_assign
l_int|0
suffix:semicolon
id|head.next
op_assign
l_int|NULL
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|bus-&gt;devices
comma
id|bus_list
)paren
(brace
id|u16
r_class
op_assign
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
suffix:semicolon
r_if
c_cond
(paren
r_class
op_eq
id|PCI_CLASS_DISPLAY_VGA
op_logical_or
r_class
op_eq
id|PCI_CLASS_NOT_DEFINED_VGA
)paren
id|found_vga
op_assign
l_int|1
suffix:semicolon
id|pdev_sort_resources
c_func
(paren
id|dev
comma
op_amp
id|head
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|list
op_assign
id|head.next
suffix:semicolon
id|list
suffix:semicolon
)paren
(brace
id|res
op_assign
id|list-&gt;res
suffix:semicolon
id|idx
op_assign
id|res
op_minus
op_amp
id|list-&gt;dev-&gt;resource
(braket
l_int|0
)braket
suffix:semicolon
id|pci_assign_resource
c_func
(paren
id|list-&gt;dev
comma
id|idx
)paren
suffix:semicolon
id|tmp
op_assign
id|list
suffix:semicolon
id|list
op_assign
id|list-&gt;next
suffix:semicolon
id|kfree
c_func
(paren
id|tmp
)paren
suffix:semicolon
)brace
r_return
id|found_vga
suffix:semicolon
)brace
r_static
r_void
id|__devinit
DECL|function|pci_setup_cardbus
id|pci_setup_cardbus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_dev
op_star
id|bridge
op_assign
id|bus-&gt;self
suffix:semicolon
r_struct
id|pci_bus_region
id|region
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;PCI: Bus %d, cardbus bridge: %s&bslash;n&quot;
comma
id|bus-&gt;number
comma
id|pci_name
c_func
(paren
id|bridge
)paren
)paren
suffix:semicolon
id|pcibios_resource_to_bus
c_func
(paren
id|bridge
comma
op_amp
id|region
comma
id|bus-&gt;resource
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|flags
op_amp
id|IORESOURCE_IO
)paren
(brace
multiline_comment|/*&n;&t;&t; * The IO resource is allocated a range twice as large as it&n;&t;&t; * would normally need.  This allows us to set both IO regs.&n;&t;&t; */
id|printk
c_func
(paren
l_string|&quot;  IO window: %08lx-%08lx&bslash;n&quot;
comma
id|region.start
comma
id|region.end
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_CB_IO_BASE_0
comma
id|region.start
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_CB_IO_LIMIT_0
comma
id|region.end
)paren
suffix:semicolon
)brace
id|pcibios_resource_to_bus
c_func
(paren
id|bridge
comma
op_amp
id|region
comma
id|bus-&gt;resource
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;resource
(braket
l_int|1
)braket
op_member_access_from_pointer
id|flags
op_amp
id|IORESOURCE_IO
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;  IO window: %08lx-%08lx&bslash;n&quot;
comma
id|region.start
comma
id|region.end
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_CB_IO_BASE_1
comma
id|region.start
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_CB_IO_LIMIT_1
comma
id|region.end
)paren
suffix:semicolon
)brace
id|pcibios_resource_to_bus
c_func
(paren
id|bridge
comma
op_amp
id|region
comma
id|bus-&gt;resource
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;resource
(braket
l_int|2
)braket
op_member_access_from_pointer
id|flags
op_amp
id|IORESOURCE_MEM
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;  PREFETCH window: %08lx-%08lx&bslash;n&quot;
comma
id|region.start
comma
id|region.end
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_CB_MEMORY_BASE_0
comma
id|region.start
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_CB_MEMORY_LIMIT_0
comma
id|region.end
)paren
suffix:semicolon
)brace
id|pcibios_resource_to_bus
c_func
(paren
id|bridge
comma
op_amp
id|region
comma
id|bus-&gt;resource
(braket
l_int|3
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;resource
(braket
l_int|3
)braket
op_member_access_from_pointer
id|flags
op_amp
id|IORESOURCE_MEM
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;  MEM window: %08lx-%08lx&bslash;n&quot;
comma
id|region.start
comma
id|region.end
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_CB_MEMORY_BASE_1
comma
id|region.start
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_CB_MEMORY_LIMIT_1
comma
id|region.end
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/* Initialize bridges with base/limit values we have collected.&n;   PCI-to-PCI Bridge Architecture Specification rev. 1.1 (1998)&n;   requires that if there is no I/O ports or memory behind the&n;   bridge, corresponding range must be turned off by writing base&n;   value greater than limit to the bridge&squot;s base/limit registers.  */
r_static
r_void
id|__devinit
DECL|function|pci_setup_bridge
id|pci_setup_bridge
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_dev
op_star
id|bridge
op_assign
id|bus-&gt;self
suffix:semicolon
r_struct
id|pci_bus_region
id|region
suffix:semicolon
id|u32
id|l
suffix:semicolon
id|DBGC
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;PCI: Bus %d, bridge: %s&bslash;n&quot;
comma
id|bus-&gt;number
comma
id|bridge-&gt;dev.name
)paren
)paren
suffix:semicolon
multiline_comment|/* Set up the top and bottom of the PCI I/O segment for this bus. */
id|pcibios_resource_to_bus
c_func
(paren
id|bridge
comma
op_amp
id|region
comma
id|bus-&gt;resource
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|flags
op_amp
id|IORESOURCE_IO
)paren
(brace
id|pci_read_config_dword
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE
comma
op_amp
id|l
)paren
suffix:semicolon
id|l
op_and_assign
l_int|0xffff0000
suffix:semicolon
id|l
op_or_assign
(paren
id|region.start
op_rshift
l_int|8
)paren
op_amp
l_int|0x00f0
suffix:semicolon
id|l
op_or_assign
id|region.end
op_amp
l_int|0xf000
suffix:semicolon
multiline_comment|/* Set up upper 16 bits of I/O base/limit. */
id|pci_write_config_word
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE_UPPER16
comma
id|region.start
op_rshift
l_int|16
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|bridge
comma
id|PCI_IO_LIMIT_UPPER16
comma
id|region.end
op_rshift
l_int|16
)paren
suffix:semicolon
id|DBGC
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;  IO window: %04lx-%04lx&bslash;n&quot;
comma
id|region.start
comma
id|region.end
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Clear upper 16 bits of I/O base/limit. */
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE_UPPER16
comma
l_int|0
)paren
suffix:semicolon
id|l
op_assign
l_int|0x00f0
suffix:semicolon
id|DBGC
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;  IO window: disabled.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE
comma
id|l
)paren
suffix:semicolon
multiline_comment|/* Set up the top and bottom of the PCI Memory segment&n;&t;   for this bus. */
id|pcibios_resource_to_bus
c_func
(paren
id|bridge
comma
op_amp
id|region
comma
id|bus-&gt;resource
(braket
l_int|1
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;resource
(braket
l_int|1
)braket
op_member_access_from_pointer
id|flags
op_amp
id|IORESOURCE_MEM
)paren
(brace
id|l
op_assign
(paren
id|region.start
op_rshift
l_int|16
)paren
op_amp
l_int|0xfff0
suffix:semicolon
id|l
op_or_assign
id|region.end
op_amp
l_int|0xfff00000
suffix:semicolon
id|DBGC
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;  MEM window: %08lx-%08lx&bslash;n&quot;
comma
id|region.start
comma
id|region.end
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|l
op_assign
l_int|0x0000fff0
suffix:semicolon
id|DBGC
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;  MEM window: disabled.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_MEMORY_BASE
comma
id|l
)paren
suffix:semicolon
multiline_comment|/* Clear out the upper 32 bits of PREF base/limit. */
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_PREF_BASE_UPPER32
comma
l_int|0
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_PREF_LIMIT_UPPER32
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Set up PREF base/limit. */
id|pcibios_resource_to_bus
c_func
(paren
id|bridge
comma
op_amp
id|region
comma
id|bus-&gt;resource
(braket
l_int|2
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|bus-&gt;resource
(braket
l_int|2
)braket
op_member_access_from_pointer
id|flags
op_amp
id|IORESOURCE_PREFETCH
)paren
(brace
id|l
op_assign
(paren
id|region.start
op_rshift
l_int|16
)paren
op_amp
l_int|0xfff0
suffix:semicolon
id|l
op_or_assign
id|region.end
op_amp
l_int|0xfff00000
suffix:semicolon
id|DBGC
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;  PREFETCH window: %08lx-%08lx&bslash;n&quot;
comma
id|region.start
comma
id|region.end
)paren
)paren
suffix:semicolon
)brace
r_else
(brace
id|l
op_assign
l_int|0x0000fff0
suffix:semicolon
id|DBGC
c_func
(paren
(paren
id|KERN_INFO
l_string|&quot;  PREFETCH window: disabled.&bslash;n&quot;
)paren
)paren
suffix:semicolon
)brace
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_PREF_MEMORY_BASE
comma
id|l
)paren
suffix:semicolon
multiline_comment|/* Check if we have VGA behind the bridge.&n;&t;   Enable ISA in either case (FIXME!). */
id|l
op_assign
(paren
id|bus-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|flags
op_amp
id|IORESOURCE_BUS_HAS_VGA
)paren
ques
c_cond
l_int|0x0c
suffix:colon
l_int|0x04
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|bridge
comma
id|PCI_BRIDGE_CONTROL
comma
id|l
)paren
suffix:semicolon
)brace
multiline_comment|/* Check whether the bridge supports optional I/O and&n;   prefetchable memory ranges. If not, the respective&n;   base/limit registers must be read-only and read as 0. */
r_static
r_void
id|__devinit
DECL|function|pci_bridge_check_ranges
id|pci_bridge_check_ranges
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
id|u16
id|io
suffix:semicolon
id|u32
id|pmem
suffix:semicolon
r_struct
id|pci_dev
op_star
id|bridge
op_assign
id|bus-&gt;self
suffix:semicolon
r_struct
id|resource
op_star
id|b_res
suffix:semicolon
id|b_res
op_assign
op_amp
id|bridge-&gt;resource
(braket
id|PCI_BRIDGE_RESOURCES
)braket
suffix:semicolon
id|b_res
(braket
l_int|1
)braket
dot
id|flags
op_or_assign
id|IORESOURCE_MEM
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE
comma
op_amp
id|io
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|io
)paren
(brace
id|pci_write_config_word
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE
comma
l_int|0xf0f0
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE
comma
op_amp
id|io
)paren
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|bridge
comma
id|PCI_IO_BASE
comma
l_int|0x0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|io
)paren
id|b_res
(braket
l_int|0
)braket
dot
id|flags
op_or_assign
id|IORESOURCE_IO
suffix:semicolon
multiline_comment|/*  DECchip 21050 pass 2 errata: the bridge may miss an address&n;&t;    disconnect boundary by one PCI data phase.&n;&t;    Workaround: do not use prefetching on this device. */
r_if
c_cond
(paren
id|bridge-&gt;vendor
op_eq
id|PCI_VENDOR_ID_DEC
op_logical_and
id|bridge-&gt;device
op_eq
l_int|0x0001
)paren
r_return
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|bridge
comma
id|PCI_PREF_MEMORY_BASE
comma
op_amp
id|pmem
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmem
)paren
(brace
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_PREF_MEMORY_BASE
comma
l_int|0xfff0fff0
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|bridge
comma
id|PCI_PREF_MEMORY_BASE
comma
op_amp
id|pmem
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|bridge
comma
id|PCI_PREF_MEMORY_BASE
comma
l_int|0x0
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pmem
)paren
id|b_res
(braket
l_int|2
)braket
dot
id|flags
op_or_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_PREFETCH
suffix:semicolon
)brace
multiline_comment|/* Helper function for sizing routines: find first available&n;   bus resource of a given type. Note: we intentionally skip&n;   the bus resources which have already been assigned (that is,&n;   have non-NULL parent resource). */
r_static
r_struct
id|resource
op_star
id|__devinit
DECL|function|find_free_bus_resource
id|find_free_bus_resource
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|type
)paren
(brace
r_int
id|i
suffix:semicolon
r_struct
id|resource
op_star
id|r
suffix:semicolon
r_int
r_int
id|type_mask
op_assign
id|IORESOURCE_IO
op_or
id|IORESOURCE_MEM
op_or
id|IORESOURCE_PREFETCH
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
id|PCI_BUS_NUM_RESOURCES
suffix:semicolon
id|i
op_increment
)paren
(brace
id|r
op_assign
id|bus-&gt;resource
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|r
op_logical_and
(paren
id|r-&gt;flags
op_amp
id|type_mask
)paren
op_eq
id|type
op_logical_and
op_logical_neg
id|r-&gt;parent
)paren
r_return
id|r
suffix:semicolon
)brace
r_return
l_int|NULL
suffix:semicolon
)brace
multiline_comment|/* Sizing the IO windows of the PCI-PCI bridge is trivial,&n;   since these windows have 4K granularity and the IO ranges&n;   of non-bridge PCI devices are limited to 256 bytes.&n;   We must be careful with the ISA aliasing though. */
r_static
r_void
id|__devinit
DECL|function|pbus_size_io
id|pbus_size_io
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_struct
id|resource
op_star
id|b_res
op_assign
id|find_free_bus_resource
c_func
(paren
id|bus
comma
id|IORESOURCE_IO
)paren
suffix:semicolon
r_int
r_int
id|size
op_assign
l_int|0
comma
id|size1
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b_res
)paren
r_return
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|bus-&gt;devices
comma
id|bus_list
)paren
(brace
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
r_int
r_int
id|r_size
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;parent
op_logical_or
op_logical_neg
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
)paren
r_continue
suffix:semicolon
id|r_size
op_assign
id|r-&gt;end
op_minus
id|r-&gt;start
op_plus
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|r_size
OL
l_int|0x400
)paren
multiline_comment|/* Might be re-aligned for ISA */
id|size
op_add_assign
id|r_size
suffix:semicolon
r_else
id|size1
op_add_assign
id|r_size
suffix:semicolon
)brace
)brace
multiline_comment|/* To be fixed in 2.5: we should have sort of HAVE_ISA&n;   flag in the struct pci_bus. */
macro_line|#if defined(CONFIG_ISA) || defined(CONFIG_EISA)
id|size
op_assign
(paren
id|size
op_amp
l_int|0xff
)paren
op_plus
(paren
(paren
id|size
op_amp
op_complement
l_int|0xffUL
)paren
op_lshift
l_int|2
)paren
suffix:semicolon
macro_line|#endif
id|size
op_assign
id|ROUND_UP
c_func
(paren
id|size
op_plus
id|size1
comma
l_int|4096
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|b_res-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* Alignment of the IO window is always 4K */
id|b_res-&gt;start
op_assign
l_int|4096
suffix:semicolon
id|b_res-&gt;end
op_assign
id|b_res-&gt;start
op_plus
id|size
op_minus
l_int|1
suffix:semicolon
)brace
multiline_comment|/* Calculate the size of the bus and minimal alignment which&n;   guarantees that all child resources fit in this size. */
r_static
r_int
id|__devinit
DECL|function|pbus_size_mem
id|pbus_size_mem
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
comma
r_int
r_int
id|mask
comma
r_int
r_int
id|type
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
r_int
id|min_align
comma
id|align
comma
id|size
suffix:semicolon
r_int
r_int
id|aligns
(braket
l_int|12
)braket
suffix:semicolon
multiline_comment|/* Alignments from 1Mb to 2Gb */
r_int
id|order
comma
id|max_order
suffix:semicolon
r_struct
id|resource
op_star
id|b_res
op_assign
id|find_free_bus_resource
c_func
(paren
id|bus
comma
id|type
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b_res
)paren
r_return
l_int|0
suffix:semicolon
id|memset
c_func
(paren
id|aligns
comma
l_int|0
comma
r_sizeof
(paren
id|aligns
)paren
)paren
suffix:semicolon
id|max_order
op_assign
l_int|0
suffix:semicolon
id|size
op_assign
l_int|0
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|bus-&gt;devices
comma
id|bus_list
)paren
(brace
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
r_int
r_int
id|r_size
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;parent
op_logical_or
(paren
id|r-&gt;flags
op_amp
id|mask
)paren
op_ne
id|type
)paren
r_continue
suffix:semicolon
id|r_size
op_assign
id|r-&gt;end
op_minus
id|r-&gt;start
op_plus
l_int|1
suffix:semicolon
multiline_comment|/* For bridges size != alignment */
id|align
op_assign
(paren
id|i
OL
id|PCI_BRIDGE_RESOURCES
)paren
ques
c_cond
id|r_size
suffix:colon
id|r-&gt;start
suffix:semicolon
id|order
op_assign
id|__ffs
c_func
(paren
id|align
)paren
op_minus
l_int|20
suffix:semicolon
r_if
c_cond
(paren
id|order
OG
l_int|11
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: region %s/%d &quot;
l_string|&quot;too large: %lx-%lx&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|i
comma
id|r-&gt;start
comma
id|r-&gt;end
)paren
suffix:semicolon
id|r-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|size
op_add_assign
id|r_size
suffix:semicolon
r_if
c_cond
(paren
id|order
OL
l_int|0
)paren
id|order
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Exclude ranges with size &gt; align from&n;&t;&t;&t;   calculation of the alignment. */
r_if
c_cond
(paren
id|r_size
op_eq
id|align
)paren
id|aligns
(braket
id|order
)braket
op_add_assign
id|align
suffix:semicolon
r_if
c_cond
(paren
id|order
OG
id|max_order
)paren
id|max_order
op_assign
id|order
suffix:semicolon
)brace
)brace
id|align
op_assign
l_int|0
suffix:semicolon
id|min_align
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|order
op_assign
l_int|0
suffix:semicolon
id|order
op_le
id|max_order
suffix:semicolon
id|order
op_increment
)paren
(brace
r_int
r_int
id|align1
op_assign
l_int|1UL
op_lshift
(paren
id|order
op_plus
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|align
)paren
id|min_align
op_assign
id|align1
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ROUND_UP
c_func
(paren
id|align
op_plus
id|min_align
comma
id|min_align
)paren
OL
id|align1
)paren
id|min_align
op_assign
id|align1
op_rshift
l_int|1
suffix:semicolon
id|align
op_add_assign
id|aligns
(braket
id|order
)braket
suffix:semicolon
)brace
id|size
op_assign
id|ROUND_UP
c_func
(paren
id|size
comma
id|min_align
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
(brace
id|b_res-&gt;flags
op_assign
l_int|0
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|b_res-&gt;start
op_assign
id|min_align
suffix:semicolon
id|b_res-&gt;end
op_assign
id|size
op_plus
id|min_align
op_minus
l_int|1
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_static
r_void
id|__devinit
DECL|function|pci_bus_size_cardbus
id|pci_bus_size_cardbus
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_dev
op_star
id|bridge
op_assign
id|bus-&gt;self
suffix:semicolon
r_struct
id|resource
op_star
id|b_res
op_assign
op_amp
id|bridge-&gt;resource
(braket
id|PCI_BRIDGE_RESOURCES
)braket
suffix:semicolon
id|u16
id|ctrl
suffix:semicolon
multiline_comment|/*&n;&t; * Reserve some resources for CardBus.  We reserve&n;&t; * a fixed amount of bus space for CardBus bridges.&n;&t; */
id|b_res
(braket
l_int|0
)braket
dot
id|start
op_assign
id|CARDBUS_IO_SIZE
suffix:semicolon
id|b_res
(braket
l_int|0
)braket
dot
id|end
op_assign
id|b_res
(braket
l_int|0
)braket
dot
id|start
op_plus
id|CARDBUS_IO_SIZE
op_minus
l_int|1
suffix:semicolon
id|b_res
(braket
l_int|0
)braket
dot
id|flags
op_or_assign
id|IORESOURCE_IO
suffix:semicolon
id|b_res
(braket
l_int|1
)braket
dot
id|start
op_assign
id|CARDBUS_IO_SIZE
suffix:semicolon
id|b_res
(braket
l_int|1
)braket
dot
id|end
op_assign
id|b_res
(braket
l_int|1
)braket
dot
id|start
op_plus
id|CARDBUS_IO_SIZE
op_minus
l_int|1
suffix:semicolon
id|b_res
(braket
l_int|1
)braket
dot
id|flags
op_or_assign
id|IORESOURCE_IO
suffix:semicolon
multiline_comment|/*&n;&t; * Check whether prefetchable memory is supported&n;&t; * by this bridge.&n;&t; */
id|pci_read_config_word
c_func
(paren
id|bridge
comma
id|PCI_CB_BRIDGE_CONTROL
comma
op_amp
id|ctrl
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|ctrl
op_amp
id|PCI_CB_BRIDGE_CTL_PREFETCH_MEM0
)paren
)paren
(brace
id|ctrl
op_or_assign
id|PCI_CB_BRIDGE_CTL_PREFETCH_MEM0
suffix:semicolon
id|pci_write_config_word
c_func
(paren
id|bridge
comma
id|PCI_CB_BRIDGE_CONTROL
comma
id|ctrl
)paren
suffix:semicolon
id|pci_read_config_word
c_func
(paren
id|bridge
comma
id|PCI_CB_BRIDGE_CONTROL
comma
op_amp
id|ctrl
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * If we have prefetchable memory support, allocate&n;&t; * two regions.  Otherwise, allocate one region of&n;&t; * twice the size.&n;&t; */
r_if
c_cond
(paren
id|ctrl
op_amp
id|PCI_CB_BRIDGE_CTL_PREFETCH_MEM0
)paren
(brace
id|b_res
(braket
l_int|2
)braket
dot
id|start
op_assign
id|CARDBUS_MEM_SIZE
suffix:semicolon
id|b_res
(braket
l_int|2
)braket
dot
id|end
op_assign
id|b_res
(braket
l_int|2
)braket
dot
id|start
op_plus
id|CARDBUS_MEM_SIZE
op_minus
l_int|1
suffix:semicolon
id|b_res
(braket
l_int|2
)braket
dot
id|flags
op_or_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_PREFETCH
suffix:semicolon
id|b_res
(braket
l_int|3
)braket
dot
id|start
op_assign
id|CARDBUS_MEM_SIZE
suffix:semicolon
id|b_res
(braket
l_int|3
)braket
dot
id|end
op_assign
id|b_res
(braket
l_int|3
)braket
dot
id|start
op_plus
id|CARDBUS_MEM_SIZE
op_minus
l_int|1
suffix:semicolon
id|b_res
(braket
l_int|3
)braket
dot
id|flags
op_or_assign
id|IORESOURCE_MEM
suffix:semicolon
)brace
r_else
(brace
id|b_res
(braket
l_int|3
)braket
dot
id|start
op_assign
id|CARDBUS_MEM_SIZE
op_star
l_int|2
suffix:semicolon
id|b_res
(braket
l_int|3
)braket
dot
id|end
op_assign
id|b_res
(braket
l_int|3
)braket
dot
id|start
op_plus
id|CARDBUS_MEM_SIZE
op_star
l_int|2
op_minus
l_int|1
suffix:semicolon
id|b_res
(braket
l_int|3
)braket
dot
id|flags
op_or_assign
id|IORESOURCE_MEM
suffix:semicolon
)brace
)brace
r_void
id|__devinit
DECL|function|pci_bus_size_bridges
id|pci_bus_size_bridges
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
r_int
id|mask
comma
id|prefmask
suffix:semicolon
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|bus-&gt;devices
comma
id|bus_list
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
op_assign
id|dev-&gt;subordinate
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b
)paren
r_continue
suffix:semicolon
r_switch
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
(brace
r_case
id|PCI_CLASS_BRIDGE_CARDBUS
suffix:colon
id|pci_bus_size_cardbus
c_func
(paren
id|b
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLASS_BRIDGE_PCI
suffix:colon
r_default
suffix:colon
id|pci_bus_size_bridges
c_func
(paren
id|b
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* The root bus? */
r_if
c_cond
(paren
op_logical_neg
id|bus-&gt;self
)paren
r_return
suffix:semicolon
r_switch
c_cond
(paren
id|bus-&gt;self
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
(brace
r_case
id|PCI_CLASS_BRIDGE_CARDBUS
suffix:colon
multiline_comment|/* don&squot;t size cardbuses yet. */
r_break
suffix:semicolon
r_case
id|PCI_CLASS_BRIDGE_PCI
suffix:colon
id|pci_bridge_check_ranges
c_func
(paren
id|bus
)paren
suffix:semicolon
r_default
suffix:colon
id|pbus_size_io
c_func
(paren
id|bus
)paren
suffix:semicolon
multiline_comment|/* If the bridge supports prefetchable range, size it&n;&t;&t;   separately. If it doesn&squot;t, or its prefetchable window&n;&t;&t;   has already been allocated by arch code, try&n;&t;&t;   non-prefetchable range for both types of PCI memory&n;&t;&t;   resources. */
id|mask
op_assign
id|IORESOURCE_MEM
suffix:semicolon
id|prefmask
op_assign
id|IORESOURCE_MEM
op_or
id|IORESOURCE_PREFETCH
suffix:semicolon
r_if
c_cond
(paren
id|pbus_size_mem
c_func
(paren
id|bus
comma
id|prefmask
comma
id|prefmask
)paren
)paren
id|mask
op_assign
id|prefmask
suffix:semicolon
multiline_comment|/* Success, size non-prefetch only. */
id|pbus_size_mem
c_func
(paren
id|bus
comma
id|mask
comma
id|IORESOURCE_MEM
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
DECL|variable|pci_bus_size_bridges
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_size_bridges
)paren
suffix:semicolon
r_void
id|__devinit
DECL|function|pci_bus_assign_resources
id|pci_bus_assign_resources
c_func
(paren
r_struct
id|pci_bus
op_star
id|bus
)paren
(brace
r_struct
id|pci_bus
op_star
id|b
suffix:semicolon
r_int
id|found_vga
op_assign
id|pbus_assign_resources_sorted
c_func
(paren
id|bus
)paren
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_if
c_cond
(paren
id|found_vga
)paren
(brace
multiline_comment|/* Propagate presence of the VGA to upstream bridges */
r_for
c_loop
(paren
id|b
op_assign
id|bus
suffix:semicolon
id|b-&gt;parent
suffix:semicolon
id|b
op_assign
id|b-&gt;parent
)paren
(brace
id|b-&gt;resource
(braket
l_int|0
)braket
op_member_access_from_pointer
id|flags
op_or_assign
id|IORESOURCE_BUS_HAS_VGA
suffix:semicolon
)brace
)brace
id|list_for_each_entry
c_func
(paren
id|dev
comma
op_amp
id|bus-&gt;devices
comma
id|bus_list
)paren
(brace
id|b
op_assign
id|dev-&gt;subordinate
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|b
)paren
r_continue
suffix:semicolon
id|pci_bus_assign_resources
c_func
(paren
id|b
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
)paren
(brace
r_case
id|PCI_CLASS_BRIDGE_PCI
suffix:colon
id|pci_setup_bridge
c_func
(paren
id|b
)paren
suffix:semicolon
r_break
suffix:semicolon
r_case
id|PCI_CLASS_BRIDGE_CARDBUS
suffix:colon
id|pci_setup_cardbus
c_func
(paren
id|b
)paren
suffix:semicolon
r_break
suffix:semicolon
r_default
suffix:colon
id|printk
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: not setting up bridge %s &quot;
l_string|&quot;for bus %d&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|b-&gt;number
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
DECL|variable|pci_bus_assign_resources
id|EXPORT_SYMBOL
c_func
(paren
id|pci_bus_assign_resources
)paren
suffix:semicolon
r_void
id|__init
DECL|function|pci_assign_unassigned_resources
id|pci_assign_unassigned_resources
c_func
(paren
r_void
)paren
(brace
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
multiline_comment|/* Depth first, calculate sizes and alignments of all&n;&t;   subordinate buses. */
r_for
c_loop
(paren
id|ln
op_assign
id|pci_root_buses.next
suffix:semicolon
id|ln
op_ne
op_amp
id|pci_root_buses
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
id|pci_bus_size_bridges
c_func
(paren
id|pci_bus_b
c_func
(paren
id|ln
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Depth last, allocate resources and update the hardware. */
r_for
c_loop
(paren
id|ln
op_assign
id|pci_root_buses.next
suffix:semicolon
id|ln
op_ne
op_amp
id|pci_root_buses
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
id|pci_bus_assign_resources
c_func
(paren
id|pci_bus_b
c_func
(paren
id|ln
)paren
)paren
suffix:semicolon
)brace
)brace
eof
