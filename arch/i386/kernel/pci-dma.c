multiline_comment|/*&n; * Dynamic DMA mapping support.&n; *&n; * On i386 there is no hardware dynamic DMA address translation,&n; * so consistent alloc/free are merely page allocation/freeing.&n; * The rest of the dynamic DMA mapping interface is implemented&n; * in asm/pci.h.&n; */
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|struct|dma_coherent_mem
r_struct
id|dma_coherent_mem
(brace
DECL|member|virt_base
r_void
op_star
id|virt_base
suffix:semicolon
DECL|member|device_base
id|u32
id|device_base
suffix:semicolon
DECL|member|size
r_int
id|size
suffix:semicolon
DECL|member|flags
r_int
id|flags
suffix:semicolon
DECL|member|bitmap
r_int
r_int
op_star
id|bitmap
suffix:semicolon
)brace
suffix:semicolon
DECL|function|dma_alloc_coherent
r_void
op_star
id|dma_alloc_coherent
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|size
comma
id|dma_addr_t
op_star
id|dma_handle
comma
r_int
id|gfp
)paren
(brace
r_void
op_star
id|ret
suffix:semicolon
r_struct
id|dma_coherent_mem
op_star
id|mem
op_assign
id|dev
ques
c_cond
id|dev-&gt;dma_mem
suffix:colon
l_int|NULL
suffix:semicolon
r_int
id|order
op_assign
id|get_order
c_func
(paren
id|size
)paren
suffix:semicolon
multiline_comment|/* ignore region specifiers */
id|gfp
op_and_assign
op_complement
(paren
id|__GFP_DMA
op_or
id|__GFP_HIGHMEM
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem
)paren
(brace
r_int
id|page
op_assign
id|bitmap_find_free_region
c_func
(paren
id|mem-&gt;bitmap
comma
id|mem-&gt;size
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|page
op_ge
l_int|0
)paren
(brace
op_star
id|dma_handle
op_assign
id|mem-&gt;device_base
op_plus
(paren
id|page
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|ret
op_assign
id|mem-&gt;virt_base
op_plus
(paren
id|page
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
r_return
id|ret
suffix:semicolon
)brace
r_if
c_cond
(paren
id|mem-&gt;flags
op_amp
id|DMA_MEMORY_EXCLUSIVE
)paren
r_return
l_int|NULL
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
op_logical_or
(paren
id|dev-&gt;coherent_dma_mask
OL
l_int|0xffffffff
)paren
)paren
id|gfp
op_or_assign
id|GFP_DMA
suffix:semicolon
id|ret
op_assign
(paren
r_void
op_star
)paren
id|__get_free_pages
c_func
(paren
id|gfp
comma
id|order
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ret
op_ne
l_int|NULL
)paren
(brace
id|memset
c_func
(paren
id|ret
comma
l_int|0
comma
id|size
)paren
suffix:semicolon
op_star
id|dma_handle
op_assign
id|virt_to_phys
c_func
(paren
id|ret
)paren
suffix:semicolon
)brace
r_return
id|ret
suffix:semicolon
)brace
DECL|function|dma_free_coherent
r_void
id|dma_free_coherent
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|size
comma
r_void
op_star
id|vaddr
comma
id|dma_addr_t
id|dma_handle
)paren
(brace
r_struct
id|dma_coherent_mem
op_star
id|mem
op_assign
id|dev
ques
c_cond
id|dev-&gt;dma_mem
suffix:colon
l_int|NULL
suffix:semicolon
r_int
id|order
op_assign
id|get_order
c_func
(paren
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
id|mem
op_logical_and
id|vaddr
op_ge
id|mem-&gt;virt_base
op_logical_and
id|vaddr
OL
(paren
id|mem-&gt;virt_base
op_plus
(paren
id|mem-&gt;size
op_lshift
id|PAGE_SHIFT
)paren
)paren
)paren
(brace
r_int
id|page
op_assign
(paren
id|vaddr
op_minus
id|mem-&gt;virt_base
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|bitmap_release_region
c_func
(paren
id|mem-&gt;bitmap
comma
id|page
comma
id|order
)paren
suffix:semicolon
)brace
r_else
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
comma
id|order
)paren
suffix:semicolon
)brace
DECL|function|dma_declare_coherent_memory
r_int
id|dma_declare_coherent_memory
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|bus_addr
comma
id|dma_addr_t
id|device_addr
comma
r_int
id|size
comma
r_int
id|flags
)paren
(brace
r_void
op_star
id|mem_base
suffix:semicolon
r_int
id|pages
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_int
id|bitmap_size
op_assign
(paren
id|pages
op_plus
l_int|31
)paren
op_div
l_int|32
suffix:semicolon
r_if
c_cond
(paren
(paren
id|flags
op_amp
(paren
id|DMA_MEMORY_MAP
op_or
id|DMA_MEMORY_IO
)paren
)paren
op_eq
l_int|0
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|size
)paren
r_goto
id|out
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;dma_mem
)paren
r_goto
id|out
suffix:semicolon
multiline_comment|/* FIXME: this routine just ignores DMA_MEMORY_INCLUDES_CHILDREN */
id|mem_base
op_assign
id|ioremap
c_func
(paren
id|bus_addr
comma
id|size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem_base
)paren
r_goto
id|out
suffix:semicolon
id|dev-&gt;dma_mem
op_assign
id|kmalloc
c_func
(paren
id|GFP_KERNEL
comma
r_sizeof
(paren
r_struct
id|dma_coherent_mem
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;dma_mem
)paren
r_goto
id|out
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;dma_mem
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|dma_coherent_mem
)paren
)paren
suffix:semicolon
id|dev-&gt;dma_mem-&gt;bitmap
op_assign
id|kmalloc
c_func
(paren
id|GFP_KERNEL
comma
id|bitmap_size
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|dev-&gt;dma_mem-&gt;bitmap
)paren
r_goto
id|free1_out
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;dma_mem-&gt;bitmap
comma
l_int|0
comma
id|bitmap_size
)paren
suffix:semicolon
id|dev-&gt;dma_mem-&gt;virt_base
op_assign
id|mem_base
suffix:semicolon
id|dev-&gt;dma_mem-&gt;device_base
op_assign
id|device_addr
suffix:semicolon
id|dev-&gt;dma_mem-&gt;size
op_assign
id|pages
suffix:semicolon
id|dev-&gt;dma_mem-&gt;flags
op_assign
id|flags
suffix:semicolon
r_if
c_cond
(paren
id|flags
op_amp
id|DMA_MEMORY_MAP
)paren
r_return
id|DMA_MEMORY_MAP
suffix:semicolon
r_return
id|DMA_MEMORY_IO
suffix:semicolon
id|free1_out
suffix:colon
id|kfree
c_func
(paren
id|dev-&gt;dma_mem-&gt;bitmap
)paren
suffix:semicolon
id|out
suffix:colon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|dma_declare_coherent_memory
id|EXPORT_SYMBOL
c_func
(paren
id|dma_declare_coherent_memory
)paren
suffix:semicolon
DECL|function|dma_release_declared_memory
r_void
id|dma_release_declared_memory
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|dma_coherent_mem
op_star
id|mem
op_assign
id|dev-&gt;dma_mem
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem
)paren
(brace
r_return
suffix:semicolon
)brace
id|dev-&gt;dma_mem
op_assign
l_int|NULL
suffix:semicolon
id|kfree
c_func
(paren
id|mem-&gt;bitmap
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|mem
)paren
suffix:semicolon
)brace
DECL|variable|dma_release_declared_memory
id|EXPORT_SYMBOL
c_func
(paren
id|dma_release_declared_memory
)paren
suffix:semicolon
DECL|function|dma_mark_declared_memory_occupied
r_void
op_star
id|dma_mark_declared_memory_occupied
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|device_addr
comma
r_int
id|size
)paren
(brace
r_struct
id|dma_coherent_mem
op_star
id|mem
op_assign
id|dev-&gt;dma_mem
suffix:semicolon
r_int
id|pages
op_assign
(paren
id|size
op_plus
(paren
id|device_addr
op_amp
op_complement
id|PAGE_MASK
)paren
op_plus
id|PAGE_SIZE
op_minus
l_int|1
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
r_int
id|pos
comma
id|err
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|mem
)paren
r_return
id|ERR_PTR
c_func
(paren
op_minus
id|EINVAL
)paren
suffix:semicolon
id|pos
op_assign
(paren
id|device_addr
op_minus
id|mem-&gt;device_base
)paren
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|err
op_assign
id|bitmap_allocate_region
c_func
(paren
id|mem-&gt;bitmap
comma
id|pos
comma
id|get_order
c_func
(paren
id|pages
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|err
op_ne
l_int|0
)paren
r_return
id|ERR_PTR
c_func
(paren
id|err
)paren
suffix:semicolon
r_return
id|mem-&gt;virt_base
op_plus
(paren
id|pos
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
)brace
DECL|variable|dma_mark_declared_memory_occupied
id|EXPORT_SYMBOL
c_func
(paren
id|dma_mark_declared_memory_occupied
)paren
suffix:semicolon
eof
