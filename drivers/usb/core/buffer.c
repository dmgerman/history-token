multiline_comment|/*&n; * DMA memory management for framework level HCD code (hc_driver)&n; *&n; * This implementation plugs in through generic &quot;usb_bus&quot; level methods,&n; * and works with real PCI, or when &quot;pci device == null&quot; makes sense.&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#ifdef CONFIG_USB_DEBUG
DECL|macro|DEBUG
mdefine_line|#define DEBUG
macro_line|#else
DECL|macro|DEBUG
macro_line|#undef DEBUG
macro_line|#endif
macro_line|#include &lt;linux/usb.h&gt;
macro_line|#include &quot;hcd.h&quot;
multiline_comment|/*&n; * DMA-Consistent Buffers&n; */
multiline_comment|/* FIXME tune these based on pool statistics ... */
DECL|variable|pool_max
r_static
r_const
r_int
id|pool_max
(braket
id|HCD_BUFFER_POOLS
)braket
op_assign
(brace
l_int|32
comma
l_int|128
comma
l_int|512
comma
id|PAGE_SIZE
op_div
l_int|2
multiline_comment|/* bigger --&gt; allocate pages */
)brace
suffix:semicolon
multiline_comment|/* SETUP primitives */
multiline_comment|/**&n; * hcd_buffer_create - initialize buffer pools&n; * @hcd: the bus whose buffer pools are to be initialized&n; *&n; * Call this as part of initializing a host controller that uses the pci dma&n; * memory allocators.  It initializes some pools of dma-consistent memory that&n; * will be shared by all drivers using that controller, or returns a negative&n; * errno value on error.&n; *&n; * Call hcd_buffer_destroy() to clean up after using those pools.&n; */
DECL|function|hcd_buffer_create
r_int
id|hcd_buffer_create
(paren
r_struct
id|usb_hcd
op_star
id|hcd
)paren
(brace
r_char
id|name
(braket
l_int|16
)braket
suffix:semicolon
r_int
id|i
comma
id|size
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
id|HCD_BUFFER_POOLS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
(paren
id|size
op_assign
id|pool_max
(braket
id|i
)braket
)paren
)paren
r_continue
suffix:semicolon
id|snprintf
(paren
id|name
comma
r_sizeof
id|name
comma
l_string|&quot;buffer-%d&quot;
comma
id|size
)paren
suffix:semicolon
id|hcd-&gt;pool
(braket
id|i
)braket
op_assign
id|pci_pool_create
(paren
id|name
comma
id|hcd-&gt;pdev
comma
id|size
comma
id|size
comma
l_int|0
comma
id|SLAB_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|hcd-&gt;pool
(braket
id|i
)braket
)paren
(brace
id|hcd_buffer_destroy
(paren
id|hcd
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|hcd_buffer_create
id|EXPORT_SYMBOL
(paren
id|hcd_buffer_create
)paren
suffix:semicolon
multiline_comment|/**&n; * hcd_buffer_destroy - deallocate buffer pools&n; * @hcd: the bus whose buffer pools are to be destroyed&n; *&n; * This frees the buffer pools created by hcd_buffer_create().&n; */
DECL|function|hcd_buffer_destroy
r_void
id|hcd_buffer_destroy
(paren
r_struct
id|usb_hcd
op_star
id|hcd
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
id|HCD_BUFFER_POOLS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_struct
id|pci_pool
op_star
id|pool
op_assign
id|hcd-&gt;pool
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|pool
)paren
(brace
id|pci_pool_destroy
(paren
id|pool
)paren
suffix:semicolon
id|hcd-&gt;pool
(braket
id|i
)braket
op_assign
l_int|0
suffix:semicolon
)brace
)brace
)brace
DECL|variable|hcd_buffer_destroy
id|EXPORT_SYMBOL
(paren
id|hcd_buffer_destroy
)paren
suffix:semicolon
multiline_comment|/* sometimes alloc/free could use kmalloc with SLAB_DMA, for&n; * better sharing and to leverage mm/slab.c intelligence.&n; */
DECL|function|hcd_buffer_alloc
r_void
op_star
id|hcd_buffer_alloc
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_int
id|size
comma
r_int
id|mem_flags
comma
id|dma_addr_t
op_star
id|dma
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|bus-&gt;hcpriv
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
id|HCD_BUFFER_POOLS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|size
op_le
id|pool_max
(braket
id|i
)braket
)paren
r_return
id|pci_pool_alloc
(paren
id|hcd-&gt;pool
(braket
id|i
)braket
comma
id|mem_flags
comma
id|dma
)paren
suffix:semicolon
)brace
r_return
id|pci_alloc_consistent
(paren
id|hcd-&gt;pdev
comma
id|size
comma
id|dma
)paren
suffix:semicolon
)brace
DECL|function|hcd_buffer_free
r_void
id|hcd_buffer_free
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_int
id|size
comma
r_void
op_star
id|addr
comma
id|dma_addr_t
id|dma
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|bus-&gt;hcpriv
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
id|HCD_BUFFER_POOLS
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|size
op_le
id|pool_max
(braket
id|i
)braket
)paren
(brace
id|pci_pool_free
(paren
id|hcd-&gt;pool
(braket
id|i
)braket
comma
id|addr
comma
id|dma
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
)brace
id|pci_free_consistent
(paren
id|hcd-&gt;pdev
comma
id|size
comma
id|addr
comma
id|dma
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * DMA-Mappings for arbitrary memory buffers&n; */
DECL|function|hcd_buffer_map
r_int
id|hcd_buffer_map
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_void
op_star
id|addr
comma
id|dma_addr_t
op_star
id|dma
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|bus-&gt;hcpriv
suffix:semicolon
singleline_comment|// FIXME pci_map_single() has no standard failure mode!
op_star
id|dma
op_assign
id|pci_map_single
(paren
id|hcd-&gt;pdev
comma
id|addr
comma
id|size
comma
(paren
id|direction
op_eq
id|USB_DIR_IN
)paren
ques
c_cond
id|PCI_DMA_FROMDEVICE
suffix:colon
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hcd_buffer_dmasync
r_void
id|hcd_buffer_dmasync
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
id|dma_addr_t
id|dma
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|bus-&gt;hcpriv
suffix:semicolon
id|pci_dma_sync_single
(paren
id|hcd-&gt;pdev
comma
id|dma
comma
id|size
comma
(paren
id|direction
op_eq
id|USB_DIR_IN
)paren
ques
c_cond
id|PCI_DMA_FROMDEVICE
suffix:colon
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
)brace
DECL|function|hcd_buffer_unmap
r_void
id|hcd_buffer_unmap
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
id|dma_addr_t
id|dma
comma
r_int
id|size
comma
r_int
id|direction
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|bus-&gt;hcpriv
suffix:semicolon
id|pci_unmap_single
(paren
id|hcd-&gt;pdev
comma
id|dma
comma
id|size
comma
(paren
id|direction
op_eq
id|USB_DIR_IN
)paren
ques
c_cond
id|PCI_DMA_FROMDEVICE
suffix:colon
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
)brace
DECL|function|hcd_buffer_map_sg
r_int
id|hcd_buffer_map_sg
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
op_star
id|n_hw_ents
comma
r_int
id|nents
comma
r_int
id|direction
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|bus-&gt;hcpriv
suffix:semicolon
singleline_comment|// FIXME pci_map_sg() has no standard failure mode!
op_star
id|n_hw_ents
op_assign
id|pci_map_sg
c_func
(paren
id|hcd-&gt;pdev
comma
id|sg
comma
id|nents
comma
(paren
id|direction
op_eq
id|USB_DIR_IN
)paren
ques
c_cond
id|PCI_DMA_FROMDEVICE
suffix:colon
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|hcd_buffer_sync_sg
r_void
id|hcd_buffer_sync_sg
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|n_hw_ents
comma
r_int
id|direction
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|bus-&gt;hcpriv
suffix:semicolon
id|pci_dma_sync_sg
c_func
(paren
id|hcd-&gt;pdev
comma
id|sg
comma
id|n_hw_ents
comma
(paren
id|direction
op_eq
id|USB_DIR_IN
)paren
ques
c_cond
id|PCI_DMA_FROMDEVICE
suffix:colon
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
)brace
DECL|function|hcd_buffer_unmap_sg
r_void
id|hcd_buffer_unmap_sg
(paren
r_struct
id|usb_bus
op_star
id|bus
comma
r_struct
id|scatterlist
op_star
id|sg
comma
r_int
id|n_hw_ents
comma
r_int
id|direction
)paren
(brace
r_struct
id|usb_hcd
op_star
id|hcd
op_assign
id|bus-&gt;hcpriv
suffix:semicolon
id|pci_unmap_sg
c_func
(paren
id|hcd-&gt;pdev
comma
id|sg
comma
id|n_hw_ents
comma
(paren
id|direction
op_eq
id|USB_DIR_IN
)paren
ques
c_cond
id|PCI_DMA_FROMDEVICE
suffix:colon
id|PCI_DMA_TODEVICE
)paren
suffix:semicolon
)brace
eof
