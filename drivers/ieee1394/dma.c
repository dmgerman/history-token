multiline_comment|/*&n; * DMA region bookkeeping routines&n; *&n; * Copyright (C) 2002 Maas Digital LLC&n; *&n; * This code is licensed under the GPL.  See the file COPYING in the root&n; * directory of the kernel sources for details.&n; */
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/vmalloc.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &quot;dma.h&quot;
multiline_comment|/* dma_prog_region */
DECL|function|dma_prog_region_init
r_void
id|dma_prog_region_init
c_func
(paren
r_struct
id|dma_prog_region
op_star
id|prog
)paren
(brace
id|prog-&gt;kvirt
op_assign
l_int|NULL
suffix:semicolon
id|prog-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|prog-&gt;n_pages
op_assign
l_int|0
suffix:semicolon
id|prog-&gt;bus_addr
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|dma_prog_region_alloc
r_int
id|dma_prog_region_alloc
c_func
(paren
r_struct
id|dma_prog_region
op_star
id|prog
comma
r_int
r_int
id|n_bytes
comma
r_struct
id|pci_dev
op_star
id|dev
)paren
(brace
multiline_comment|/* round up to page size */
id|n_bytes
op_assign
id|PAGE_ALIGN
c_func
(paren
id|n_bytes
)paren
suffix:semicolon
id|prog-&gt;n_pages
op_assign
id|n_bytes
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|prog-&gt;kvirt
op_assign
id|pci_alloc_consistent
c_func
(paren
id|dev
comma
id|n_bytes
comma
op_amp
id|prog-&gt;bus_addr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|prog-&gt;kvirt
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dma_prog_region_alloc: pci_alloc_consistent() failed&bslash;n&quot;
)paren
suffix:semicolon
id|dma_prog_region_free
c_func
(paren
id|prog
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|prog-&gt;dev
op_assign
id|dev
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|dma_prog_region_free
r_void
id|dma_prog_region_free
c_func
(paren
r_struct
id|dma_prog_region
op_star
id|prog
)paren
(brace
r_if
c_cond
(paren
id|prog-&gt;kvirt
)paren
(brace
id|pci_free_consistent
c_func
(paren
id|prog-&gt;dev
comma
id|prog-&gt;n_pages
op_lshift
id|PAGE_SHIFT
comma
id|prog-&gt;kvirt
comma
id|prog-&gt;bus_addr
)paren
suffix:semicolon
)brace
id|prog-&gt;kvirt
op_assign
l_int|NULL
suffix:semicolon
id|prog-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|prog-&gt;n_pages
op_assign
l_int|0
suffix:semicolon
id|prog-&gt;bus_addr
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* dma_region */
DECL|function|dma_region_init
r_void
id|dma_region_init
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
)paren
(brace
id|dma-&gt;kvirt
op_assign
l_int|NULL
suffix:semicolon
id|dma-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
id|dma-&gt;n_pages
op_assign
l_int|0
suffix:semicolon
id|dma-&gt;n_dma_pages
op_assign
l_int|0
suffix:semicolon
id|dma-&gt;sglist
op_assign
l_int|NULL
suffix:semicolon
)brace
DECL|function|dma_region_alloc
r_int
id|dma_region_alloc
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
comma
r_int
r_int
id|n_bytes
comma
r_struct
id|pci_dev
op_star
id|dev
comma
r_int
id|direction
)paren
(brace
r_int
r_int
id|i
suffix:semicolon
multiline_comment|/* round up to page size */
id|n_bytes
op_assign
id|PAGE_ALIGN
c_func
(paren
id|n_bytes
)paren
suffix:semicolon
id|dma-&gt;n_pages
op_assign
id|n_bytes
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|dma-&gt;kvirt
op_assign
id|vmalloc_32
c_func
(paren
id|n_bytes
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma-&gt;kvirt
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dma_region_alloc: vmalloc_32() failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
multiline_comment|/* Clear the ram out, no junk to the user */
id|memset
c_func
(paren
id|dma-&gt;kvirt
comma
l_int|0
comma
id|n_bytes
)paren
suffix:semicolon
multiline_comment|/* allocate scatter/gather list */
id|dma-&gt;sglist
op_assign
id|vmalloc
c_func
(paren
id|dma-&gt;n_pages
op_star
r_sizeof
(paren
op_star
id|dma-&gt;sglist
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma-&gt;sglist
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dma_region_alloc: vmalloc(sglist) failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
multiline_comment|/* just to be safe - this will become unnecessary once sglist-&gt;address goes away */
id|memset
c_func
(paren
id|dma-&gt;sglist
comma
l_int|0
comma
id|dma-&gt;n_pages
op_star
r_sizeof
(paren
op_star
id|dma-&gt;sglist
)paren
)paren
suffix:semicolon
multiline_comment|/* fill scatter/gather list with pages */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|dma-&gt;n_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_int
id|va
op_assign
(paren
r_int
r_int
)paren
id|dma-&gt;kvirt
op_plus
(paren
id|i
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|dma-&gt;sglist
(braket
id|i
)braket
dot
id|page
op_assign
id|vmalloc_to_page
c_func
(paren
(paren
r_void
op_star
)paren
id|va
)paren
suffix:semicolon
id|dma-&gt;sglist
(braket
id|i
)braket
dot
id|length
op_assign
id|PAGE_SIZE
suffix:semicolon
)brace
multiline_comment|/* map sglist to the IOMMU */
id|dma-&gt;n_dma_pages
op_assign
id|pci_map_sg
c_func
(paren
id|dev
comma
id|dma-&gt;sglist
comma
id|dma-&gt;n_pages
comma
id|direction
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dma-&gt;n_dma_pages
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;dma_region_alloc: pci_map_sg() failed&bslash;n&quot;
)paren
suffix:semicolon
r_goto
id|err
suffix:semicolon
)brace
id|dma-&gt;dev
op_assign
id|dev
suffix:semicolon
id|dma-&gt;direction
op_assign
id|direction
suffix:semicolon
r_return
l_int|0
suffix:semicolon
id|err
suffix:colon
id|dma_region_free
c_func
(paren
id|dma
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
DECL|function|dma_region_free
r_void
id|dma_region_free
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
)paren
(brace
r_if
c_cond
(paren
id|dma-&gt;n_dma_pages
)paren
(brace
id|pci_unmap_sg
c_func
(paren
id|dma-&gt;dev
comma
id|dma-&gt;sglist
comma
id|dma-&gt;n_pages
comma
id|dma-&gt;direction
)paren
suffix:semicolon
id|dma-&gt;n_dma_pages
op_assign
l_int|0
suffix:semicolon
id|dma-&gt;dev
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dma-&gt;sglist
)paren
(brace
id|vfree
c_func
(paren
id|dma-&gt;sglist
)paren
suffix:semicolon
id|dma-&gt;sglist
op_assign
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dma-&gt;kvirt
)paren
(brace
id|vfree
c_func
(paren
id|dma-&gt;kvirt
)paren
suffix:semicolon
id|dma-&gt;kvirt
op_assign
l_int|NULL
suffix:semicolon
id|dma-&gt;n_pages
op_assign
l_int|0
suffix:semicolon
)brace
)brace
multiline_comment|/* find the scatterlist index and remaining offset corresponding to a&n;   given offset from the beginning of the buffer */
DECL|function|dma_region_find
r_static
r_inline
r_int
id|dma_region_find
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
comma
r_int
r_int
id|offset
comma
r_int
r_int
op_star
id|rem
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_int
id|off
op_assign
id|offset
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
id|dma-&gt;n_dma_pages
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|off
OL
id|sg_dma_len
c_func
(paren
op_amp
id|dma-&gt;sglist
(braket
id|i
)braket
)paren
)paren
(brace
op_star
id|rem
op_assign
id|off
suffix:semicolon
r_break
suffix:semicolon
)brace
id|off
op_sub_assign
id|sg_dma_len
c_func
(paren
op_amp
id|dma-&gt;sglist
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
id|BUG_ON
c_func
(paren
id|i
op_ge
id|dma-&gt;n_dma_pages
)paren
suffix:semicolon
r_return
id|i
suffix:semicolon
)brace
DECL|function|dma_region_offset_to_bus
id|dma_addr_t
id|dma_region_offset_to_bus
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
comma
r_int
r_int
id|offset
)paren
(brace
r_int
r_int
id|rem
suffix:semicolon
r_struct
id|scatterlist
op_star
id|sg
op_assign
op_amp
id|dma-&gt;sglist
(braket
id|dma_region_find
c_func
(paren
id|dma
comma
id|offset
comma
op_amp
id|rem
)paren
)braket
suffix:semicolon
r_return
id|sg_dma_address
c_func
(paren
id|sg
)paren
op_plus
id|rem
suffix:semicolon
)brace
DECL|function|dma_region_sync_for_cpu
r_void
id|dma_region_sync_for_cpu
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|first
comma
id|last
suffix:semicolon
r_int
r_int
id|rem
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
id|len
op_assign
l_int|1
suffix:semicolon
id|first
op_assign
id|dma_region_find
c_func
(paren
id|dma
comma
id|offset
comma
op_amp
id|rem
)paren
suffix:semicolon
id|last
op_assign
id|dma_region_find
c_func
(paren
id|dma
comma
id|offset
op_plus
id|len
op_minus
l_int|1
comma
op_amp
id|rem
)paren
suffix:semicolon
id|pci_dma_sync_sg_for_cpu
c_func
(paren
id|dma-&gt;dev
comma
op_amp
id|dma-&gt;sglist
(braket
id|first
)braket
comma
id|last
op_minus
id|first
op_plus
l_int|1
comma
id|dma-&gt;direction
)paren
suffix:semicolon
)brace
DECL|function|dma_region_sync_for_device
r_void
id|dma_region_sync_for_device
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
comma
r_int
r_int
id|offset
comma
r_int
r_int
id|len
)paren
(brace
r_int
id|first
comma
id|last
suffix:semicolon
r_int
r_int
id|rem
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|len
)paren
id|len
op_assign
l_int|1
suffix:semicolon
id|first
op_assign
id|dma_region_find
c_func
(paren
id|dma
comma
id|offset
comma
op_amp
id|rem
)paren
suffix:semicolon
id|last
op_assign
id|dma_region_find
c_func
(paren
id|dma
comma
id|offset
op_plus
id|len
op_minus
l_int|1
comma
op_amp
id|rem
)paren
suffix:semicolon
id|pci_dma_sync_sg_for_device
c_func
(paren
id|dma-&gt;dev
comma
op_amp
id|dma-&gt;sglist
(braket
id|first
)braket
comma
id|last
op_minus
id|first
op_plus
l_int|1
comma
id|dma-&gt;direction
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_MMU
multiline_comment|/* nopage() handler for mmap access */
r_static
r_struct
id|page
op_star
DECL|function|dma_region_pagefault
id|dma_region_pagefault
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|area
comma
r_int
r_int
id|address
comma
r_int
op_star
id|type
)paren
(brace
r_int
r_int
id|offset
suffix:semicolon
r_int
r_int
id|kernel_virt_addr
suffix:semicolon
r_struct
id|page
op_star
id|ret
op_assign
id|NOPAGE_SIGBUS
suffix:semicolon
r_struct
id|dma_region
op_star
id|dma
op_assign
(paren
r_struct
id|dma_region
op_star
)paren
id|area-&gt;vm_private_data
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma-&gt;kvirt
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
(paren
id|address
OL
(paren
r_int
r_int
)paren
id|area-&gt;vm_start
)paren
op_logical_or
(paren
id|address
OG
(paren
r_int
r_int
)paren
id|area-&gt;vm_start
op_plus
(paren
id|dma-&gt;n_pages
op_lshift
id|PAGE_SHIFT
)paren
)paren
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|type
)paren
op_star
id|type
op_assign
id|VM_FAULT_MINOR
suffix:semicolon
id|offset
op_assign
id|address
op_minus
id|area-&gt;vm_start
suffix:semicolon
id|kernel_virt_addr
op_assign
(paren
r_int
r_int
)paren
id|dma-&gt;kvirt
op_plus
id|offset
suffix:semicolon
id|ret
op_assign
id|vmalloc_to_page
c_func
(paren
(paren
r_void
op_star
)paren
id|kernel_virt_addr
)paren
suffix:semicolon
id|get_page
c_func
(paren
id|ret
)paren
suffix:semicolon
id|out
suffix:colon
r_return
id|ret
suffix:semicolon
)brace
DECL|variable|dma_region_vm_ops
r_static
r_struct
id|vm_operations_struct
id|dma_region_vm_ops
op_assign
(brace
dot
id|nopage
op_assign
id|dma_region_pagefault
comma
)brace
suffix:semicolon
DECL|function|dma_region_mmap
r_int
id|dma_region_mmap
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_int
r_int
id|size
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dma-&gt;kvirt
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* must be page-aligned */
r_if
c_cond
(paren
id|vma-&gt;vm_pgoff
op_ne
l_int|0
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
multiline_comment|/* check the length */
id|size
op_assign
id|vma-&gt;vm_end
op_minus
id|vma-&gt;vm_start
suffix:semicolon
r_if
c_cond
(paren
id|size
OG
(paren
id|dma-&gt;n_pages
op_lshift
id|PAGE_SHIFT
)paren
)paren
r_return
op_minus
id|EINVAL
suffix:semicolon
id|vma-&gt;vm_ops
op_assign
op_amp
id|dma_region_vm_ops
suffix:semicolon
id|vma-&gt;vm_private_data
op_assign
id|dma
suffix:semicolon
id|vma-&gt;vm_file
op_assign
id|file
suffix:semicolon
id|vma-&gt;vm_flags
op_or_assign
id|VM_RESERVED
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#else /* CONFIG_MMU */
DECL|function|dma_region_mmap
r_int
id|dma_region_mmap
c_func
(paren
r_struct
id|dma_region
op_star
id|dma
comma
r_struct
id|file
op_star
id|file
comma
r_struct
id|vm_area_struct
op_star
id|vma
)paren
(brace
r_return
op_minus
id|EINVAL
suffix:semicolon
)brace
macro_line|#endif /* CONFIG_MMU */
eof
