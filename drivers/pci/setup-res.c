multiline_comment|/*&n; *&t;drivers/pci/setup-res.c&n; *&n; * Extruded from code written by&n; *      Dave Rusling (david.rusling@reo.mts.dec.com)&n; *      David Mosberger (davidm@cs.arizona.edu)&n; *&t;David Miller (davem@redhat.com)&n; *&n; * Support routines for initializing a PCI subsystem.&n; */
multiline_comment|/* fixed for multiple pci buses, 1999 Andrea Arcangeli &lt;andrea@suse.de&gt; */
multiline_comment|/*&n; * Nov 2000, Ivan Kokshaysky &lt;ink@jurassic.park.msu.ru&gt;&n; *&t;     Resource sorting&n; */
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/cache.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &quot;pci.h&quot;
DECL|macro|DEBUG_CONFIG
mdefine_line|#define DEBUG_CONFIG 0
macro_line|#if DEBUG_CONFIG
DECL|macro|DBG
mdefine_line|#define DBG(x...)     printk(x)
macro_line|#else
DECL|macro|DBG
mdefine_line|#define DBG(x...)
macro_line|#endif
r_static
r_void
DECL|function|pci_update_resource
id|pci_update_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource
op_star
id|res
comma
r_int
id|resno
)paren
(brace
r_struct
id|pci_bus_region
id|region
suffix:semicolon
id|u32
r_new
comma
id|check
comma
id|mask
suffix:semicolon
r_int
id|reg
suffix:semicolon
id|pcibios_resource_to_bus
c_func
(paren
id|dev
comma
op_amp
id|region
comma
id|res
)paren
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_ERR
l_string|&quot;  got res [%lx:%lx] bus [%lx:%lx] flags %lx for &quot;
l_string|&quot;BAR %d of %s&bslash;n&quot;
comma
id|res-&gt;start
comma
id|res-&gt;end
comma
id|region.start
comma
id|region.end
comma
id|res-&gt;flags
comma
id|resno
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_new
op_assign
id|region.start
op_or
(paren
id|res-&gt;flags
op_amp
id|PCI_REGION_FLAG_MASK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|mask
op_assign
(paren
id|u32
)paren
id|PCI_BASE_ADDRESS_IO_MASK
suffix:semicolon
r_else
id|mask
op_assign
(paren
id|u32
)paren
id|PCI_BASE_ADDRESS_MEM_MASK
suffix:semicolon
r_if
c_cond
(paren
id|resno
OL
l_int|6
)paren
(brace
id|reg
op_assign
id|PCI_BASE_ADDRESS_0
op_plus
l_int|4
op_star
id|resno
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|resno
op_eq
id|PCI_ROM_RESOURCE
)paren
(brace
r_new
op_or_assign
id|res-&gt;flags
op_amp
id|IORESOURCE_ROM_ENABLE
suffix:semicolon
id|reg
op_assign
id|dev-&gt;rom_base_reg
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Hmm, non-standard resource. */
r_return
suffix:semicolon
multiline_comment|/* kill uninitialised var warning */
)brace
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
r_new
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
comma
op_amp
id|check
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_new
op_xor
id|check
)paren
op_amp
id|mask
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Error while updating region &quot;
l_string|&quot;%s/%d (%08x != %08x)&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|resno
comma
r_new
comma
id|check
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
r_new
op_amp
(paren
id|PCI_BASE_ADDRESS_SPACE
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_MASK
)paren
)paren
op_eq
(paren
id|PCI_BASE_ADDRESS_SPACE_MEMORY
op_or
id|PCI_BASE_ADDRESS_MEM_TYPE_64
)paren
)paren
(brace
r_new
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* currently everyone zeros the high address */
id|pci_write_config_dword
c_func
(paren
id|dev
comma
id|reg
op_plus
l_int|4
comma
r_new
)paren
suffix:semicolon
id|pci_read_config_dword
c_func
(paren
id|dev
comma
id|reg
op_plus
l_int|4
comma
op_amp
id|check
)paren
suffix:semicolon
r_if
c_cond
(paren
id|check
op_ne
r_new
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Error updating region &quot;
l_string|&quot;%s/%d (high %08x != %08x)&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|resno
comma
r_new
comma
id|check
)paren
suffix:semicolon
)brace
)brace
id|res-&gt;flags
op_and_assign
op_complement
id|IORESOURCE_UNSET
suffix:semicolon
id|DBG
c_func
(paren
id|KERN_INFO
l_string|&quot;PCI: moved device %s resource %d (%lx) to %x&bslash;n&quot;
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|resno
comma
id|res-&gt;flags
comma
r_new
op_amp
op_complement
id|PCI_REGION_FLAG_MASK
)paren
suffix:semicolon
)brace
r_int
id|__devinit
DECL|function|pci_claim_resource
id|pci_claim_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|resource
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
id|resource
)braket
suffix:semicolon
r_struct
id|resource
op_star
id|root
op_assign
l_int|NULL
suffix:semicolon
r_char
op_star
id|dtype
op_assign
id|resource
OL
id|PCI_BRIDGE_RESOURCES
ques
c_cond
l_string|&quot;device&quot;
suffix:colon
l_string|&quot;bridge&quot;
suffix:semicolon
r_int
id|err
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
id|root
op_assign
op_amp
id|ioport_resource
suffix:semicolon
r_if
c_cond
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_MEM
)paren
id|root
op_assign
op_amp
id|iomem_resource
suffix:semicolon
id|err
op_assign
op_minus
id|EINVAL
suffix:semicolon
r_if
c_cond
(paren
id|root
op_ne
l_int|NULL
)paren
id|err
op_assign
id|insert_resource
c_func
(paren
id|root
comma
id|res
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: %s region %d of %s %s [%lx:%lx]&bslash;n&quot;
comma
id|root
ques
c_cond
l_string|&quot;Address space collision on&quot;
suffix:colon
l_string|&quot;No parent found for&quot;
comma
id|resource
comma
id|dtype
comma
id|pci_name
c_func
(paren
id|dev
)paren
comma
id|res-&gt;start
comma
id|res-&gt;end
)paren
suffix:semicolon
)brace
r_return
id|err
suffix:semicolon
)brace
DECL|function|pci_assign_resource
r_int
id|pci_assign_resource
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|resno
)paren
(brace
r_struct
id|pci_bus
op_star
id|bus
op_assign
id|dev-&gt;bus
suffix:semicolon
r_struct
id|resource
op_star
id|res
op_assign
id|dev-&gt;resource
op_plus
id|resno
suffix:semicolon
r_int
r_int
id|size
comma
id|min
comma
id|align
suffix:semicolon
r_int
id|ret
suffix:semicolon
id|size
op_assign
id|res-&gt;end
op_minus
id|res-&gt;start
op_plus
l_int|1
suffix:semicolon
id|min
op_assign
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
)paren
ques
c_cond
id|PCIBIOS_MIN_IO
suffix:colon
id|PCIBIOS_MIN_MEM
suffix:semicolon
multiline_comment|/* The bridge resources are special, as their&n;&t;   size != alignment. Sizing routines return&n;&t;   required alignment in the &quot;start&quot; field. */
id|align
op_assign
(paren
id|resno
OL
id|PCI_BRIDGE_RESOURCES
)paren
ques
c_cond
id|size
suffix:colon
id|res-&gt;start
suffix:semicolon
multiline_comment|/* First, try exact prefetching match.. */
id|ret
op_assign
id|pci_bus_alloc_resource
c_func
(paren
id|bus
comma
id|res
comma
id|size
comma
id|align
comma
id|min
comma
id|IORESOURCE_PREFETCH
comma
id|pcibios_align_resource
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
OL
l_int|0
op_logical_and
(paren
id|res-&gt;flags
op_amp
id|IORESOURCE_PREFETCH
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; * That failed.&n;&t;&t; *&n;&t;&t; * But a prefetching area can handle a non-prefetching&n;&t;&t; * window (it will just not perform as well).&n;&t;&t; */
id|ret
op_assign
id|pci_bus_alloc_resource
c_func
(paren
id|bus
comma
id|res
comma
id|size
comma
id|align
comma
id|min
comma
l_int|0
comma
id|pcibios_align_resource
comma
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|ret
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;PCI: Failed to allocate %s resource #%d:%lx@%lx for %s&bslash;n&quot;
comma
id|res-&gt;flags
op_amp
id|IORESOURCE_IO
ques
c_cond
l_string|&quot;I/O&quot;
suffix:colon
l_string|&quot;mem&quot;
comma
id|resno
comma
id|size
comma
id|res-&gt;start
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|resno
OL
id|PCI_BRIDGE_RESOURCES
)paren
(brace
id|pci_update_resource
c_func
(paren
id|dev
comma
id|res
comma
id|resno
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
multiline_comment|/* Sort resources by alignment */
r_void
id|__devinit
DECL|function|pdev_sort_resources
id|pdev_sort_resources
c_func
(paren
r_struct
id|pci_dev
op_star
id|dev
comma
r_struct
id|resource_list
op_star
id|head
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
suffix:semicolon
r_struct
id|resource_list
op_star
id|list
comma
op_star
id|tmp
suffix:semicolon
r_int
r_int
id|r_align
suffix:semicolon
id|r
op_assign
op_amp
id|dev-&gt;resource
(braket
id|i
)braket
suffix:semicolon
id|r_align
op_assign
id|r-&gt;end
op_minus
id|r-&gt;start
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|r-&gt;flags
)paren
op_logical_or
id|r-&gt;parent
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|r_align
)paren
(brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;PCI: Ignore bogus resource %d &quot;
l_string|&quot;[%lx:%lx] of %s&bslash;n&quot;
comma
id|i
comma
id|r-&gt;start
comma
id|r-&gt;end
comma
id|pci_name
c_func
(paren
id|dev
)paren
)paren
suffix:semicolon
r_continue
suffix:semicolon
)brace
id|r_align
op_assign
(paren
id|i
OL
id|PCI_BRIDGE_RESOURCES
)paren
ques
c_cond
id|r_align
op_plus
l_int|1
suffix:colon
id|r-&gt;start
suffix:semicolon
r_for
c_loop
(paren
id|list
op_assign
id|head
suffix:semicolon
suffix:semicolon
id|list
op_assign
id|list-&gt;next
)paren
(brace
r_int
r_int
id|align
op_assign
l_int|0
suffix:semicolon
r_struct
id|resource_list
op_star
id|ln
op_assign
id|list-&gt;next
suffix:semicolon
r_int
id|idx
suffix:semicolon
r_if
c_cond
(paren
id|ln
)paren
(brace
id|idx
op_assign
id|ln-&gt;res
op_minus
op_amp
id|ln-&gt;dev-&gt;resource
(braket
l_int|0
)braket
suffix:semicolon
id|align
op_assign
(paren
id|idx
OL
id|PCI_BRIDGE_RESOURCES
)paren
ques
c_cond
id|ln-&gt;res-&gt;end
op_minus
id|ln-&gt;res-&gt;start
op_plus
l_int|1
suffix:colon
id|ln-&gt;res-&gt;start
suffix:semicolon
)brace
r_if
c_cond
(paren
id|r_align
OG
id|align
)paren
(brace
id|tmp
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|tmp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|tmp
)paren
id|panic
c_func
(paren
l_string|&quot;pdev_sort_resources(): &quot;
l_string|&quot;kmalloc() failed!&bslash;n&quot;
)paren
suffix:semicolon
id|tmp-&gt;next
op_assign
id|ln
suffix:semicolon
id|tmp-&gt;res
op_assign
id|r
suffix:semicolon
id|tmp-&gt;dev
op_assign
id|dev
suffix:semicolon
id|list-&gt;next
op_assign
id|tmp
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
)brace
)brace
eof
