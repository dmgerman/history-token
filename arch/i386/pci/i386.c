multiline_comment|/*&n; *&t;Low-Level PCI Access for i386 machines&n; *&n; * Copyright 1993, 1994 Drew Eckhardt&n; *      Visionary Computing&n; *      (Unix and Linux consulting and custom programming)&n; *      Drew@Colorado.EDU&n; *      +1 (303) 786-7975&n; *&n; * Drew&squot;s work was sponsored by:&n; *&t;iX Multiuser Multitasking Magazine&n; *&t;Hannover, Germany&n; *&t;hm@ix.de&n; *&n; * Copyright 1997--2000 Martin Mares &lt;mj@ucw.cz&gt;&n; *&n; * For more information, please consult the following manuals (look at&n; * http://www.pcisig.com/ for how to get them):&n; *&n; * PCI BIOS Specification&n; * PCI Local Bus Specification&n; * PCI to PCI Bridge Specification&n; * PCI System Design Guide&n; *&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &quot;pci.h&quot;
multiline_comment|/*&n; * We need to avoid collisions with `mirrored&squot; VGA ports&n; * and other strange ISA hardware, so we always want the&n; * addresses to be allocated in the 0x000-0x0ff region&n; * modulo 0x400.&n; *&n; * Why? Because some silly external IO cards only decode&n; * the low 10 bits of the IO address. The 0x00-0xff region&n; * is reserved for motherboard devices that decode all 16&n; * bits, so it&squot;s ok to allocate at, say, 0x2800-0x28ff,&n; * but we want to try to avoid allocating at 0x2900-0x2bff&n; * which might have be mirrored at 0x0100-0x03ff..&n; */
r_void
DECL|function|pcibios_align_resource
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
id|start
op_assign
id|res-&gt;start
suffix:semicolon
r_if
c_cond
(paren
id|start
op_amp
l_int|0x300
)paren
(brace
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
id|res-&gt;start
op_assign
id|start
suffix:semicolon
)brace
)brace
)brace
multiline_comment|/*&n; *  Handle resources of PCI devices.  If the world were perfect, we could&n; *  just allocate all the resource regions and do nothing more.  It isn&squot;t.&n; *  On the other hand, we cannot just re-allocate all devices, as it would&n; *  require us to know lots of host bridge internals.  So we attempt to&n; *  keep as much of the original configuration as possible, but tweak it&n; *  when it&squot;s found to be wrong.&n; *&n; *  Known BIOS problems we have to work around:&n; *&t;- I/O or memory regions not configured&n; *&t;- regions configured, but not enabled in the command register&n; *&t;- bogus I/O addresses above 64K used&n; *&t;- expansion ROMs left enabled (this may sound harmless, but given&n; *&t;  the fact the PCI specs explicitly allow address decoders to be&n; *&t;  shared between expansion ROMs and other resource regions, it&squot;s&n; *&t;  at least dangerous)&n; *&n; *  Our solution:&n; *&t;(1) Allocate resources for all buses behind PCI-to-PCI bridges.&n; *&t;    This gives us fixed barriers on where we can allocate.&n; *&t;(2) Allocate resources for all enabled devices.  If there is&n; *&t;    a collision, just mark the resource as unallocated. Also&n; *&t;    disable expansion ROMs during this step.&n; *&t;(3) Try to allocate resources for disabled devices.  If the&n; *&t;    resources were assigned correctly, everything goes well,&n; *&t;    if they weren&squot;t, they won&squot;t disturb allocation of other&n; *&t;    resources.&n; *&t;(4) Assign new addresses to resources which were either&n; *&t;    not configured at all or misconfigured.  If explicitly&n; *&t;    requested by the user, configure expansion ROM address&n; *&t;    as well.&n; */
DECL|function|pcibios_allocate_bus_resources
r_static
r_void
id|__init
id|pcibios_allocate_bus_resources
c_func
(paren
r_struct
id|list_head
op_star
id|bus_list
)paren
(brace
r_struct
id|list_head
op_star
id|ln
suffix:semicolon
r_struct
id|pci_bus
op_star
id|bus
suffix:semicolon
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_struct
id|resource
op_star
id|r
comma
op_star
id|pr
suffix:semicolon
multiline_comment|/* Depth-First Search on bus tree */
r_for
c_loop
(paren
id|ln
op_assign
id|bus_list-&gt;next
suffix:semicolon
id|ln
op_ne
id|bus_list
suffix:semicolon
id|ln
op_assign
id|ln-&gt;next
)paren
(brace
id|bus
op_assign
id|pci_bus_b
c_func
(paren
id|ln
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|dev
op_assign
id|bus-&gt;self
)paren
)paren
(brace
r_for
c_loop
(paren
id|idx
op_assign
id|PCI_BRIDGE_RESOURCES
suffix:semicolon
id|idx
OL
id|PCI_NUM_RESOURCES
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
)paren
r_continue
suffix:semicolon
id|pr
op_assign
id|pci_find_parent_resource
c_func
(paren
id|dev
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr
op_logical_or
id|request_resource
c_func
(paren
id|pr
comma
id|r
)paren
OL
l_int|0
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Cannot allocate resource region %d of bridge %s&bslash;n&quot;
comma
id|idx
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
)brace
)brace
id|pcibios_allocate_bus_resources
c_func
(paren
op_amp
id|bus-&gt;children
)paren
suffix:semicolon
)brace
)brace
DECL|function|pcibios_allocate_resources
r_static
r_void
id|__init
id|pcibios_allocate_resources
c_func
(paren
r_int
id|pass
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|idx
comma
id|disabled
suffix:semicolon
id|u16
id|command
suffix:semicolon
r_struct
id|resource
op_star
id|r
comma
op_star
id|pr
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
id|pci_read_config_word
c_func
(paren
id|dev
comma
id|PCI_COMMAND
comma
op_amp
id|command
)paren
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|6
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;parent
)paren
multiline_comment|/* Already allocated */
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
)paren
multiline_comment|/* Address not assigned at all */
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|disabled
op_assign
op_logical_neg
(paren
id|command
op_amp
id|PCI_COMMAND_IO
)paren
suffix:semicolon
r_else
id|disabled
op_assign
op_logical_neg
(paren
id|command
op_amp
id|PCI_COMMAND_MEMORY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pass
op_eq
id|disabled
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI: Resource %08lx-%08lx (f=%lx, d=%d, p=%d)&bslash;n&quot;
comma
id|r-&gt;start
comma
id|r-&gt;end
comma
id|r-&gt;flags
comma
id|disabled
comma
id|pass
)paren
suffix:semicolon
id|pr
op_assign
id|pci_find_parent_resource
c_func
(paren
id|dev
comma
id|r
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pr
op_logical_or
id|request_resource
c_func
(paren
id|pr
comma
id|r
)paren
OL
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Cannot allocate resource region %d of device %s&bslash;n&quot;
comma
id|idx
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
multiline_comment|/* We&squot;ll assign a new address later */
id|r-&gt;end
op_sub_assign
id|r-&gt;start
suffix:semicolon
id|r-&gt;start
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
r_if
c_cond
(paren
op_logical_neg
id|pass
)paren
(brace
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;flags
op_amp
id|PCI_ROM_ADDRESS_ENABLE
)paren
(brace
multiline_comment|/* Turn the ROM off, leave the resource region, but keep it unregistered. */
id|u32
id|reg
suffix:semicolon
id|DBG
c_func
(paren
l_string|&quot;PCI: Switching off ROM of %s&bslash;n&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
id|r-&gt;flags
op_and_assign
op_complement
id|PCI_ROM_ADDRESS_ENABLE
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|dev-&gt;rom_base_reg
comma
op_amp
id|reg
)paren
suffix:semicolon
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|dev-&gt;rom_base_reg
comma
id|reg
op_amp
op_complement
id|PCI_ROM_ADDRESS_ENABLE
)paren
suffix:semicolon
)brace
)brace
)brace
)brace
DECL|function|pcibios_assign_resources
r_static
r_void
id|__init
id|pcibios_assign_resources
c_func
(paren
r_void
)paren
(brace
r_struct
id|pci_dev
op_star
id|dev
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_struct
id|resource
op_star
id|r
suffix:semicolon
id|pci_for_each_dev
c_func
(paren
id|dev
)paren
(brace
r_int
r_class
op_assign
id|dev
op_member_access_from_pointer
r_class
op_rshift
l_int|8
suffix:semicolon
multiline_comment|/* Don&squot;t touch classless devices and host bridges */
r_if
c_cond
(paren
op_logical_neg
r_class
op_logical_or
r_class
op_eq
id|PCI_CLASS_BRIDGE_HOST
)paren
r_continue
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|6
suffix:semicolon
id|idx
op_increment
)paren
(brace
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|idx
)braket
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *  Don&squot;t touch IDE controllers and I/O ports of video cards!&n;&t;&t;&t; */
r_if
c_cond
(paren
(paren
r_class
op_eq
id|PCI_CLASS_STORAGE_IDE
op_logical_and
id|idx
OL
l_int|4
)paren
op_logical_or
(paren
r_class
op_eq
id|PCI_CLASS_DISPLAY_VGA
op_logical_and
(paren
id|r-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
)paren
)paren
r_continue
suffix:semicolon
multiline_comment|/*&n;&t;&t;&t; *  We shall assign a new address to this resource, either because&n;&t;&t;&t; *  the BIOS forgot to do so or because we have decided the old&n;&t;&t;&t; *  address was unusable for some reason.&n;&t;&t;&t; */
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
op_logical_and
id|r-&gt;end
)paren
id|pci_assign_resource
c_func
(paren
id|dev
comma
id|idx
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|pci_probe
op_amp
id|PCI_ASSIGN_ROMS
)paren
(brace
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
suffix:semicolon
id|r-&gt;end
op_sub_assign
id|r-&gt;start
suffix:semicolon
id|r-&gt;start
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|r-&gt;end
)paren
id|pci_assign_resource
c_func
(paren
id|dev
comma
id|PCI_ROM_RESOURCE
)paren
suffix:semicolon
)brace
)brace
)brace
DECL|function|pcibios_resource_survey
r_void
id|__init
id|pcibios_resource_survey
c_func
(paren
r_void
)paren
(brace
id|DBG
c_func
(paren
l_string|&quot;PCI: Allocating resources&bslash;n&quot;
)paren
suffix:semicolon
id|pcibios_allocate_bus_resources
c_func
(paren
op_amp
id|pci_root_buses
)paren
suffix:semicolon
id|pcibios_allocate_resources
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|pcibios_allocate_resources
c_func
(paren
l_int|1
)paren
suffix:semicolon
id|pcibios_assign_resources
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|pcibios_enable_resources
r_int
id|pcibios_enable_resources
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
id|old_cmd
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_struct
id|resource
op_star
id|r
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
id|old_cmd
op_assign
id|cmd
suffix:semicolon
r_for
c_loop
(paren
id|idx
op_assign
l_int|0
suffix:semicolon
id|idx
OL
l_int|6
suffix:semicolon
id|idx
op_increment
)paren
(brace
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
id|idx
)paren
)paren
)paren
r_continue
suffix:semicolon
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|idx
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r-&gt;start
op_logical_and
id|r-&gt;end
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Device %s not available because of resource collisions&bslash;n&quot;
comma
id|dev-&gt;slot_name
)paren
suffix:semicolon
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r-&gt;flags
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
id|r-&gt;flags
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
id|dev-&gt;resource
(braket
id|PCI_ROM_RESOURCE
)braket
dot
id|start
)paren
id|cmd
op_or_assign
id|PCI_COMMAND_MEMORY
suffix:semicolon
r_if
c_cond
(paren
id|cmd
op_ne
id|old_cmd
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;PCI: Enabling device %s (%04x -&gt; %04x)&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|old_cmd
comma
id|cmd
)paren
suffix:semicolon
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
multiline_comment|/*&n; *  If we set up a device for bus mastering, we need to check the latency&n; *  timer as certain crappy BIOSes forget to set it properly.&n; */
DECL|variable|pcibios_max_latency
r_int
r_int
id|pcibios_max_latency
op_assign
l_int|255
suffix:semicolon
DECL|function|pcibios_set_master
r_void
id|pcibios_set_master
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
id|u8
id|lat
suffix:semicolon
id|pci_read_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
op_amp
id|lat
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lat
OL
l_int|16
)paren
id|lat
op_assign
(paren
l_int|64
op_le
id|pcibios_max_latency
)paren
ques
c_cond
l_int|64
suffix:colon
id|pcibios_max_latency
suffix:semicolon
r_else
r_if
c_cond
(paren
id|lat
OG
id|pcibios_max_latency
)paren
id|lat
op_assign
id|pcibios_max_latency
suffix:semicolon
r_else
r_return
suffix:semicolon
id|printk
c_func
(paren
id|KERN_DEBUG
l_string|&quot;PCI: Setting latency timer of device %s to %d&bslash;n&quot;
comma
id|dev-&gt;slot_name
comma
id|lat
)paren
suffix:semicolon
id|pci_write_config_byte
c_func
(paren
id|dev
comma
id|PCI_LATENCY_TIMER
comma
id|lat
)paren
suffix:semicolon
)brace
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
r_int
id|prot
suffix:semicolon
multiline_comment|/* I/O space cannot be accessed via normal processor loads and&n;&t; * stores on this platform.&n;&t; */
r_if
c_cond
(paren
id|mmap_state
op_eq
id|pci_mmap_io
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* Leave vm_pgoff as-is, the PCI space address is the physical&n;&t; * address on this platform.&n;&t; */
id|vma-&gt;vm_flags
op_or_assign
(paren
id|VM_SHM
op_or
id|VM_LOCKED
op_or
id|VM_IO
)paren
suffix:semicolon
id|prot
op_assign
id|pgprot_val
c_func
(paren
id|vma-&gt;vm_page_prot
)paren
suffix:semicolon
r_if
c_cond
(paren
id|boot_cpu_data.x86
OG
l_int|3
)paren
id|prot
op_or_assign
id|_PAGE_PCD
op_or
id|_PAGE_PWT
suffix:semicolon
id|vma-&gt;vm_page_prot
op_assign
id|__pgprot
c_func
(paren
id|prot
)paren
suffix:semicolon
multiline_comment|/* Write-combine setting is ignored, it is changed via the mtrr&n;&t; * interfaces on this platform.&n;&t; */
r_if
c_cond
(paren
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
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
eof
