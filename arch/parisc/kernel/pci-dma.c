multiline_comment|/*&n;** PARISC 1.1 Dynamic DMA mapping support.&n;** This implementation is for PA-RISC platforms that do not support&n;** I/O TLBs (aka DMA address translation hardware).&n;** See Documentation/DMA-mapping.txt for interface definitions.&n;**&n;**      (c) Copyright 1999,2000 Hewlett-Packard Company&n;**      (c) Copyright 2000 Grant Grundler&n;**&t;(c) Copyright 2000 Philipp Rumpf &lt;prumpf@tux.org&gt;&n;**      (c) Copyright 2000 John Marvin&n;**&n;** &quot;leveraged&quot; from 2.3.47: arch/ia64/kernel/pci-dma.c.&n;** (I assume it&squot;s from David Mosberger-Tang but there was no Copyright)&n;**&n;** AFAIK, all PA7100LC and PA7300LC platforms can use this code.&n;**&n;** - ggg&n;*/
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;linux/pci.h&gt;
macro_line|#include &lt;linux/proc_fs.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;asm/cacheflush.h&gt;
macro_line|#include &lt;asm/dma.h&gt;    /* for DMA_CHUNK_SIZE */
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/page.h&gt;&t;/* get_order */
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/uaccess.h&gt;
DECL|variable|proc_gsc_root
r_static
r_struct
id|proc_dir_entry
op_star
id|proc_gsc_root
op_assign
l_int|NULL
suffix:semicolon
r_static
r_int
id|pcxl_proc_info
c_func
(paren
r_char
op_star
id|buffer
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|length
)paren
suffix:semicolon
DECL|variable|pcxl_used_bytes
r_static
r_int
r_int
id|pcxl_used_bytes
op_assign
l_int|0
suffix:semicolon
DECL|variable|pcxl_used_pages
r_static
r_int
r_int
id|pcxl_used_pages
op_assign
l_int|0
suffix:semicolon
r_extern
r_int
r_int
id|pcxl_dma_start
suffix:semicolon
multiline_comment|/* Start of pcxl dma mapping area */
DECL|variable|pcxl_res_lock
r_static
id|spinlock_t
id|pcxl_res_lock
suffix:semicolon
DECL|variable|pcxl_res_map
r_static
r_char
op_star
id|pcxl_res_map
suffix:semicolon
DECL|variable|pcxl_res_hint
r_static
r_int
id|pcxl_res_hint
suffix:semicolon
DECL|variable|pcxl_res_size
r_static
r_int
id|pcxl_res_size
suffix:semicolon
macro_line|#ifdef DEBUG_PCXL_RESOURCE
DECL|macro|DBG_RES
mdefine_line|#define DBG_RES(x...)&t;printk(x)
macro_line|#else
DECL|macro|DBG_RES
mdefine_line|#define DBG_RES(x...)
macro_line|#endif
multiline_comment|/*&n;** Dump a hex representation of the resource map.&n;*/
macro_line|#ifdef DUMP_RESMAP
r_static
DECL|function|dump_resmap
r_void
id|dump_resmap
c_func
(paren
r_void
)paren
(brace
id|u_long
op_star
id|res_ptr
op_assign
(paren
r_int
r_int
op_star
)paren
id|pcxl_res_map
suffix:semicolon
id|u_long
id|i
op_assign
l_int|0
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;res_map: &quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
(paren
id|pcxl_res_size
op_div
r_sizeof
(paren
r_int
r_int
)paren
)paren
suffix:semicolon
op_increment
id|i
comma
op_increment
id|res_ptr
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%08lx &quot;
comma
op_star
id|res_ptr
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
)brace
macro_line|#else
DECL|function|dump_resmap
r_static
r_inline
r_void
id|dump_resmap
c_func
(paren
r_void
)paren
(brace
suffix:semicolon
)brace
macro_line|#endif
DECL|function|pa11_dma_supported
r_static
r_int
id|pa11_dma_supported
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|u64
id|mask
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|map_pte_uncached
r_static
r_inline
r_int
id|map_pte_uncached
c_func
(paren
id|pte_t
op_star
id|pte
comma
r_int
r_int
id|vaddr
comma
r_int
r_int
id|size
comma
r_int
r_int
op_star
id|paddr_ptr
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
r_int
r_int
id|orig_vaddr
op_assign
id|vaddr
suffix:semicolon
id|vaddr
op_and_assign
op_complement
id|PMD_MASK
suffix:semicolon
id|end
op_assign
id|vaddr
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PMD_SIZE
)paren
id|end
op_assign
id|PMD_SIZE
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
id|pte
)paren
)paren
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;map_pte_uncached: page already exists&bslash;n&quot;
)paren
suffix:semicolon
id|set_pte
c_func
(paren
id|pte
comma
id|__mk_pte
c_func
(paren
op_star
id|paddr_ptr
comma
id|PAGE_KERNEL_UNC
)paren
)paren
suffix:semicolon
id|pdtlb_kernel
c_func
(paren
id|orig_vaddr
)paren
suffix:semicolon
id|vaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|orig_vaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
(paren
op_star
id|paddr_ptr
)paren
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pte
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|vaddr
OL
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|map_pmd_uncached
r_static
r_inline
r_int
id|map_pmd_uncached
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|vaddr
comma
r_int
r_int
id|size
comma
r_int
r_int
op_star
id|paddr_ptr
)paren
(brace
r_int
r_int
id|end
suffix:semicolon
r_int
r_int
id|orig_vaddr
op_assign
id|vaddr
suffix:semicolon
id|vaddr
op_and_assign
op_complement
id|PGDIR_MASK
suffix:semicolon
id|end
op_assign
id|vaddr
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PGDIR_SIZE
)paren
id|end
op_assign
id|PGDIR_SIZE
suffix:semicolon
r_do
(brace
id|pte_t
op_star
id|pte
op_assign
id|pte_alloc_kernel
c_func
(paren
op_amp
id|init_mm
comma
id|pmd
comma
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|map_pte_uncached
c_func
(paren
id|pte
comma
id|orig_vaddr
comma
id|end
op_minus
id|vaddr
comma
id|paddr_ptr
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|vaddr
op_assign
(paren
id|vaddr
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|orig_vaddr
op_add_assign
id|PMD_SIZE
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|vaddr
OL
id|end
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|map_uncached_pages
r_static
r_inline
r_int
id|map_uncached_pages
c_func
(paren
r_int
r_int
id|vaddr
comma
r_int
r_int
id|size
comma
r_int
r_int
id|paddr
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
r_int
r_int
id|end
op_assign
id|vaddr
op_plus
id|size
suffix:semicolon
id|dir
op_assign
id|pgd_offset_k
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_do
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
id|pmd
op_assign
id|pmd_alloc
c_func
(paren
l_int|NULL
comma
id|dir
comma
id|vaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pmd
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
r_if
c_cond
(paren
id|map_pmd_uncached
c_func
(paren
id|pmd
comma
id|vaddr
comma
id|end
op_minus
id|vaddr
comma
op_amp
id|paddr
)paren
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|vaddr
op_assign
id|vaddr
op_plus
id|PGDIR_SIZE
suffix:semicolon
id|dir
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|vaddr
op_logical_and
(paren
id|vaddr
OL
id|end
)paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|unmap_uncached_pte
r_static
r_inline
r_void
id|unmap_uncached_pte
c_func
(paren
id|pmd_t
op_star
id|pmd
comma
r_int
r_int
id|vaddr
comma
r_int
r_int
id|size
)paren
(brace
id|pte_t
op_star
id|pte
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_int
r_int
id|orig_vaddr
op_assign
id|vaddr
suffix:semicolon
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
(brace
id|pmd_ERROR
c_func
(paren
op_star
id|pmd
)paren
suffix:semicolon
id|pmd_clear
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pte
op_assign
id|pte_offset_map
c_func
(paren
id|pmd
comma
id|vaddr
)paren
suffix:semicolon
id|vaddr
op_and_assign
op_complement
id|PMD_MASK
suffix:semicolon
id|end
op_assign
id|vaddr
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PMD_SIZE
)paren
id|end
op_assign
id|PMD_SIZE
suffix:semicolon
r_do
(brace
id|pte_t
id|page
op_assign
op_star
id|pte
suffix:semicolon
id|pte_clear
c_func
(paren
id|pte
)paren
suffix:semicolon
id|pdtlb_kernel
c_func
(paren
id|orig_vaddr
)paren
suffix:semicolon
id|vaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|orig_vaddr
op_add_assign
id|PAGE_SIZE
suffix:semicolon
id|pte
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|pte_none
c_func
(paren
id|page
)paren
op_logical_or
id|pte_present
c_func
(paren
id|page
)paren
)paren
r_continue
suffix:semicolon
id|printk
c_func
(paren
id|KERN_CRIT
l_string|&quot;Whee.. Swapped out page in kernel page table&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
id|vaddr
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|unmap_uncached_pmd
r_static
r_inline
r_void
id|unmap_uncached_pmd
c_func
(paren
id|pgd_t
op_star
id|dir
comma
r_int
r_int
id|vaddr
comma
r_int
r_int
id|size
)paren
(brace
id|pmd_t
op_star
id|pmd
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
r_int
r_int
id|orig_vaddr
op_assign
id|vaddr
suffix:semicolon
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|dir
)paren
)paren
r_return
suffix:semicolon
r_if
c_cond
(paren
id|pgd_bad
c_func
(paren
op_star
id|dir
)paren
)paren
(brace
id|pgd_ERROR
c_func
(paren
op_star
id|dir
)paren
suffix:semicolon
id|pgd_clear
c_func
(paren
id|dir
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|pmd
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|vaddr
)paren
suffix:semicolon
id|vaddr
op_and_assign
op_complement
id|PGDIR_MASK
suffix:semicolon
id|end
op_assign
id|vaddr
op_plus
id|size
suffix:semicolon
r_if
c_cond
(paren
id|end
OG
id|PGDIR_SIZE
)paren
id|end
op_assign
id|PGDIR_SIZE
suffix:semicolon
r_do
(brace
id|unmap_uncached_pte
c_func
(paren
id|pmd
comma
id|orig_vaddr
comma
id|end
op_minus
id|vaddr
)paren
suffix:semicolon
id|vaddr
op_assign
(paren
id|vaddr
op_plus
id|PMD_SIZE
)paren
op_amp
id|PMD_MASK
suffix:semicolon
id|orig_vaddr
op_add_assign
id|PMD_SIZE
suffix:semicolon
id|pmd
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|vaddr
OL
id|end
)paren
suffix:semicolon
)brace
DECL|function|unmap_uncached_pages
r_static
r_void
id|unmap_uncached_pages
c_func
(paren
r_int
r_int
id|vaddr
comma
r_int
r_int
id|size
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
r_int
r_int
id|end
op_assign
id|vaddr
op_plus
id|size
suffix:semicolon
id|dir
op_assign
id|pgd_offset_k
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_do
(brace
id|unmap_uncached_pmd
c_func
(paren
id|dir
comma
id|vaddr
comma
id|end
op_minus
id|vaddr
)paren
suffix:semicolon
id|vaddr
op_assign
id|vaddr
op_plus
id|PGDIR_SIZE
suffix:semicolon
id|dir
op_increment
suffix:semicolon
)brace
r_while
c_loop
(paren
id|vaddr
op_logical_and
(paren
id|vaddr
OL
id|end
)paren
)paren
suffix:semicolon
)brace
DECL|macro|PCXL_SEARCH_LOOP
mdefine_line|#define PCXL_SEARCH_LOOP(idx, mask, size)  &bslash;&n;       for(; res_ptr &lt; res_end; ++res_ptr) &bslash;&n;       { &bslash;&n;               if(0 == ((*res_ptr) &amp; mask)) { &bslash;&n;                       *res_ptr |= mask; &bslash;&n;&t;&t;       idx = (int)((u_long)res_ptr - (u_long)pcxl_res_map); &bslash;&n;&t;&t;       pcxl_res_hint = idx + (size &gt;&gt; 3); &bslash;&n;                       goto resource_found; &bslash;&n;               } &bslash;&n;       }
DECL|macro|PCXL_FIND_FREE_MAPPING
mdefine_line|#define PCXL_FIND_FREE_MAPPING(idx, mask, size)  { &bslash;&n;       u##size *res_ptr = (u##size *)&amp;(pcxl_res_map[pcxl_res_hint &amp; ~((size &gt;&gt; 3) - 1)]); &bslash;&n;       u##size *res_end = (u##size *)&amp;pcxl_res_map[pcxl_res_size]; &bslash;&n;       PCXL_SEARCH_LOOP(idx, mask, size); &bslash;&n;       res_ptr = (u##size *)&amp;pcxl_res_map[0]; &bslash;&n;       PCXL_SEARCH_LOOP(idx, mask, size); &bslash;&n;}
r_int
r_int
DECL|function|pcxl_alloc_range
id|pcxl_alloc_range
c_func
(paren
r_int
id|size
)paren
(brace
r_int
id|res_idx
suffix:semicolon
id|u_long
id|mask
comma
id|flags
suffix:semicolon
r_int
r_int
id|pages_needed
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|ASSERT
c_func
(paren
id|pages_needed
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
id|pages_needed
op_star
id|PAGE_SIZE
)paren
OL
id|DMA_CHUNK_SIZE
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|pages_needed
OL
(paren
id|BITS_PER_LONG
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
id|mask
op_assign
(paren
id|u_long
)paren
op_minus
l_int|1L
suffix:semicolon
id|mask
op_rshift_assign
id|BITS_PER_LONG
op_minus
id|pages_needed
suffix:semicolon
id|DBG_RES
c_func
(paren
l_string|&quot;pcxl_alloc_range() size: %d pages_needed %d pages_mask 0x%08lx&bslash;n&quot;
comma
id|size
comma
id|pages_needed
comma
id|mask
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pcxl_res_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pages_needed
op_le
l_int|8
)paren
(brace
id|PCXL_FIND_FREE_MAPPING
c_func
(paren
id|res_idx
comma
id|mask
comma
l_int|8
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pages_needed
op_le
l_int|16
)paren
(brace
id|PCXL_FIND_FREE_MAPPING
c_func
(paren
id|res_idx
comma
id|mask
comma
l_int|16
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pages_needed
op_le
l_int|32
)paren
(brace
id|PCXL_FIND_FREE_MAPPING
c_func
(paren
id|res_idx
comma
id|mask
comma
l_int|32
)paren
suffix:semicolon
)brace
r_else
(brace
id|panic
c_func
(paren
l_string|&quot;%s: pcxl_alloc_range() Too many pages to map.&bslash;n&quot;
comma
id|__FILE__
)paren
suffix:semicolon
)brace
id|dump_resmap
c_func
(paren
)paren
suffix:semicolon
id|panic
c_func
(paren
l_string|&quot;%s: pcxl_alloc_range() out of dma mapping resources&bslash;n&quot;
comma
id|__FILE__
)paren
suffix:semicolon
id|resource_found
suffix:colon
id|DBG_RES
c_func
(paren
l_string|&quot;pcxl_alloc_range() res_idx %d mask 0x%08lx res_hint: %d&bslash;n&quot;
comma
id|res_idx
comma
id|mask
comma
id|pcxl_res_hint
)paren
suffix:semicolon
id|pcxl_used_pages
op_add_assign
id|pages_needed
suffix:semicolon
id|pcxl_used_bytes
op_add_assign
(paren
(paren
id|pages_needed
op_rshift
l_int|3
)paren
ques
c_cond
(paren
id|pages_needed
op_rshift
l_int|3
)paren
suffix:colon
l_int|1
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pcxl_res_lock
comma
id|flags
)paren
suffix:semicolon
id|dump_resmap
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* &n;&t;** return the corresponding vaddr in the pcxl dma map&n;&t;*/
r_return
(paren
id|pcxl_dma_start
op_plus
(paren
id|res_idx
op_lshift
(paren
id|PAGE_SHIFT
op_plus
l_int|3
)paren
)paren
)paren
suffix:semicolon
)brace
DECL|macro|PCXL_FREE_MAPPINGS
mdefine_line|#define PCXL_FREE_MAPPINGS(idx, m, size) &bslash;&n;&t;&t;u##size *res_ptr = (u##size *)&amp;(pcxl_res_map[(idx) + (((size &gt;&gt; 3) - 1) &amp; (~((size &gt;&gt; 3) - 1)))]); &bslash;&n;&t;&t;ASSERT((*res_ptr &amp; m) == m); &bslash;&n;&t;&t;*res_ptr &amp;= ~m;
multiline_comment|/*&n;** clear bits in the pcxl resource map&n;*/
r_static
r_void
DECL|function|pcxl_free_range
id|pcxl_free_range
c_func
(paren
r_int
r_int
id|vaddr
comma
r_int
id|size
)paren
(brace
id|u_long
id|mask
comma
id|flags
suffix:semicolon
r_int
r_int
id|res_idx
op_assign
(paren
id|vaddr
op_minus
id|pcxl_dma_start
)paren
op_rshift
(paren
id|PAGE_SHIFT
op_plus
l_int|3
)paren
suffix:semicolon
r_int
r_int
id|pages_mapped
op_assign
id|size
op_rshift
id|PAGE_SHIFT
suffix:semicolon
id|ASSERT
c_func
(paren
id|pages_mapped
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
(paren
id|pages_mapped
op_star
id|PAGE_SIZE
)paren
OL
id|DMA_CHUNK_SIZE
)paren
suffix:semicolon
id|ASSERT
c_func
(paren
id|pages_mapped
OL
(paren
id|BITS_PER_LONG
op_minus
id|PAGE_SHIFT
)paren
)paren
suffix:semicolon
id|mask
op_assign
(paren
id|u_long
)paren
op_minus
l_int|1L
suffix:semicolon
id|mask
op_rshift_assign
id|BITS_PER_LONG
op_minus
id|pages_mapped
suffix:semicolon
id|DBG_RES
c_func
(paren
l_string|&quot;pcxl_free_range() res_idx: %d size: %d pages_mapped %d mask 0x%08lx&bslash;n&quot;
comma
id|res_idx
comma
id|size
comma
id|pages_mapped
comma
id|mask
)paren
suffix:semicolon
id|spin_lock_irqsave
c_func
(paren
op_amp
id|pcxl_res_lock
comma
id|flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pages_mapped
op_le
l_int|8
)paren
(brace
id|PCXL_FREE_MAPPINGS
c_func
(paren
id|res_idx
comma
id|mask
comma
l_int|8
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pages_mapped
op_le
l_int|16
)paren
(brace
id|PCXL_FREE_MAPPINGS
c_func
(paren
id|res_idx
comma
id|mask
comma
l_int|16
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|pages_mapped
op_le
l_int|32
)paren
(brace
id|PCXL_FREE_MAPPINGS
c_func
(paren
id|res_idx
comma
id|mask
comma
l_int|32
)paren
suffix:semicolon
)brace
r_else
(brace
id|panic
c_func
(paren
l_string|&quot;%s: pcxl_free_range() Too many pages to unmap.&bslash;n&quot;
comma
id|__FILE__
)paren
suffix:semicolon
)brace
id|pcxl_used_pages
op_sub_assign
(paren
id|pages_mapped
ques
c_cond
id|pages_mapped
suffix:colon
l_int|1
)paren
suffix:semicolon
id|pcxl_used_bytes
op_sub_assign
(paren
(paren
id|pages_mapped
op_rshift
l_int|3
)paren
ques
c_cond
(paren
id|pages_mapped
op_rshift
l_int|3
)paren
suffix:colon
l_int|1
)paren
suffix:semicolon
id|spin_unlock_irqrestore
c_func
(paren
op_amp
id|pcxl_res_lock
comma
id|flags
)paren
suffix:semicolon
id|dump_resmap
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
id|__init
DECL|function|pcxl_dma_init
id|pcxl_dma_init
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|pcxl_dma_start
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|spin_lock_init
c_func
(paren
op_amp
id|pcxl_res_lock
)paren
suffix:semicolon
id|pcxl_res_size
op_assign
id|PCXL_DMA_MAP_SIZE
op_rshift
(paren
id|PAGE_SHIFT
op_plus
l_int|3
)paren
suffix:semicolon
id|pcxl_res_hint
op_assign
l_int|0
suffix:semicolon
id|pcxl_res_map
op_assign
(paren
r_char
op_star
)paren
id|__get_free_pages
c_func
(paren
id|GFP_KERNEL
comma
id|get_order
c_func
(paren
id|pcxl_res_size
)paren
)paren
suffix:semicolon
id|memset
c_func
(paren
id|pcxl_res_map
comma
l_int|0
comma
id|pcxl_res_size
)paren
suffix:semicolon
id|proc_gsc_root
op_assign
id|proc_mkdir
c_func
(paren
l_string|&quot;gsc&quot;
comma
l_int|0
)paren
suffix:semicolon
id|create_proc_info_entry
c_func
(paren
l_string|&quot;dino&quot;
comma
l_int|0
comma
id|proc_gsc_root
comma
id|pcxl_proc_info
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|variable|pcxl_dma_init
id|__initcall
c_func
(paren
id|pcxl_dma_init
)paren
suffix:semicolon
DECL|function|pa11_dma_alloc_consistent
r_static
r_void
op_star
id|pa11_dma_alloc_consistent
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
id|flag
)paren
(brace
r_int
r_int
id|vaddr
suffix:semicolon
r_int
r_int
id|paddr
suffix:semicolon
r_int
id|order
suffix:semicolon
id|order
op_assign
id|get_order
c_func
(paren
id|size
)paren
suffix:semicolon
id|size
op_assign
l_int|1
op_lshift
(paren
id|order
op_plus
id|PAGE_SHIFT
)paren
suffix:semicolon
id|vaddr
op_assign
id|pcxl_alloc_range
c_func
(paren
id|size
)paren
suffix:semicolon
id|paddr
op_assign
id|__get_free_pages
c_func
(paren
id|flag
comma
id|order
)paren
suffix:semicolon
id|flush_kernel_dcache_range
c_func
(paren
id|paddr
comma
id|size
)paren
suffix:semicolon
id|paddr
op_assign
id|__pa
c_func
(paren
id|paddr
)paren
suffix:semicolon
id|map_uncached_pages
c_func
(paren
id|vaddr
comma
id|size
comma
id|paddr
)paren
suffix:semicolon
op_star
id|dma_handle
op_assign
(paren
id|dma_addr_t
)paren
id|paddr
suffix:semicolon
macro_line|#if 0
multiline_comment|/* This probably isn&squot;t needed to support EISA cards.&n;** ISA cards will certainly only support 24-bit DMA addressing.&n;** Not clear if we can, want, or need to support ISA.&n;*/
r_if
c_cond
(paren
op_logical_neg
id|dev
op_logical_or
op_star
id|dev-&gt;dma_mask
op_ne
l_int|0xffffffff
)paren
id|gfp
op_or_assign
id|GFP_DMA
suffix:semicolon
macro_line|#endif
r_return
(paren
r_void
op_star
)paren
id|vaddr
suffix:semicolon
)brace
DECL|function|pa11_dma_free_consistent
r_static
r_void
id|pa11_dma_free_consistent
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
r_int
id|order
suffix:semicolon
id|order
op_assign
id|get_order
c_func
(paren
id|size
)paren
suffix:semicolon
id|size
op_assign
l_int|1
op_lshift
(paren
id|order
op_plus
id|PAGE_SHIFT
)paren
suffix:semicolon
id|unmap_uncached_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
comma
id|size
)paren
suffix:semicolon
id|pcxl_free_range
c_func
(paren
(paren
r_int
r_int
)paren
id|vaddr
comma
id|size
)paren
suffix:semicolon
id|free_pages
c_func
(paren
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|dma_handle
)paren
comma
id|order
)paren
suffix:semicolon
)brace
DECL|function|pa11_dma_map_single
r_static
id|dma_addr_t
id|pa11_dma_map_single
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_void
op_star
id|addr
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_NONE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pa11_dma_map_single(PCI_DMA_NONE) called by %p&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
id|flush_kernel_dcache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|addr
comma
id|size
)paren
suffix:semicolon
r_return
id|virt_to_phys
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
DECL|function|pa11_dma_unmap_single
r_static
r_void
id|pa11_dma_unmap_single
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|dma_handle
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_NONE
)paren
(brace
id|printk
c_func
(paren
id|KERN_ERR
l_string|&quot;pa11_dma_unmap_single(PCI_DMA_NONE) called by %p&bslash;n&quot;
comma
id|__builtin_return_address
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_TO_DEVICE
)paren
r_return
suffix:semicolon
multiline_comment|/*&n;&t; * For PCI_DMA_FROMDEVICE this flush is not necessary for the&n;&t; * simple map/unmap case. However, it IS necessary if if&n;&t; * pci_dma_sync_single_* has been called and the buffer reused.&n;&t; */
id|flush_kernel_dcache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|dma_handle
)paren
comma
id|size
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|pa11_dma_map_sg
r_static
r_int
id|pa11_dma_map_sg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nents
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_NONE
)paren
id|BUG
c_func
(paren
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
id|nents
suffix:semicolon
id|i
op_increment
comma
id|sglist
op_increment
)paren
(brace
r_int
r_int
id|vaddr
op_assign
id|sg_virt_addr
c_func
(paren
id|sglist
)paren
suffix:semicolon
id|sg_dma_address
c_func
(paren
id|sglist
)paren
op_assign
(paren
id|dma_addr_t
)paren
id|virt_to_phys
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|sg_dma_len
c_func
(paren
id|sglist
)paren
op_assign
id|sglist-&gt;length
suffix:semicolon
id|flush_kernel_dcache_range
c_func
(paren
id|vaddr
comma
id|sglist-&gt;length
)paren
suffix:semicolon
)brace
r_return
id|nents
suffix:semicolon
)brace
DECL|function|pa11_dma_unmap_sg
r_static
r_void
id|pa11_dma_unmap_sg
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nents
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_int
id|i
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_TO_DEVICE
)paren
r_return
suffix:semicolon
multiline_comment|/* once we do combining we&squot;ll need to use phys_to_virt(sg_dma_address(sglist)) */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nents
suffix:semicolon
id|i
op_increment
comma
id|sglist
op_increment
)paren
id|flush_kernel_dcache_range
c_func
(paren
id|sg_virt_addr
c_func
(paren
id|sglist
)paren
comma
id|sglist-&gt;length
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|function|pa11_dma_sync_single_for_cpu
r_static
r_void
id|pa11_dma_sync_single_for_cpu
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|dma_handle
comma
r_int
r_int
id|offset
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|flush_kernel_dcache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|dma_handle
)paren
op_plus
id|offset
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|pa11_dma_sync_single_for_device
r_static
r_void
id|pa11_dma_sync_single_for_device
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
id|dma_addr_t
id|dma_handle
comma
r_int
r_int
id|offset
comma
r_int
id|size
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_if
c_cond
(paren
id|direction
op_eq
id|DMA_NONE
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
id|flush_kernel_dcache_range
c_func
(paren
(paren
r_int
r_int
)paren
id|phys_to_virt
c_func
(paren
id|dma_handle
)paren
op_plus
id|offset
comma
id|size
)paren
suffix:semicolon
)brace
DECL|function|pa11_dma_sync_sg_for_cpu
r_static
r_void
id|pa11_dma_sync_sg_for_cpu
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nents
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* once we do combining we&squot;ll need to use phys_to_virt(sg_dma_address(sglist)) */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nents
suffix:semicolon
id|i
op_increment
comma
id|sglist
op_increment
)paren
id|flush_kernel_dcache_range
c_func
(paren
id|sg_virt_addr
c_func
(paren
id|sglist
)paren
comma
id|sglist-&gt;length
)paren
suffix:semicolon
)brace
DECL|function|pa11_dma_sync_sg_for_device
r_static
r_void
id|pa11_dma_sync_sg_for_device
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_struct
id|scatterlist
op_star
id|sglist
comma
r_int
id|nents
comma
r_enum
id|dma_data_direction
id|direction
)paren
(brace
r_int
id|i
suffix:semicolon
multiline_comment|/* once we do combining we&squot;ll need to use phys_to_virt(sg_dma_address(sglist)) */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|nents
suffix:semicolon
id|i
op_increment
comma
id|sglist
op_increment
)paren
id|flush_kernel_dcache_range
c_func
(paren
id|sg_virt_addr
c_func
(paren
id|sglist
)paren
comma
id|sglist-&gt;length
)paren
suffix:semicolon
)brace
DECL|variable|pcxl_dma_ops
r_struct
id|hppa_dma_ops
id|pcxl_dma_ops
op_assign
(brace
dot
id|dma_supported
op_assign
id|pa11_dma_supported
comma
dot
id|alloc_consistent
op_assign
id|pa11_dma_alloc_consistent
comma
dot
id|alloc_noncoherent
op_assign
id|pa11_dma_alloc_consistent
comma
dot
id|free_consistent
op_assign
id|pa11_dma_free_consistent
comma
dot
id|map_single
op_assign
id|pa11_dma_map_single
comma
dot
id|unmap_single
op_assign
id|pa11_dma_unmap_single
comma
dot
id|map_sg
op_assign
id|pa11_dma_map_sg
comma
dot
id|unmap_sg
op_assign
id|pa11_dma_unmap_sg
comma
dot
id|dma_sync_single_for_cpu
op_assign
id|pa11_dma_sync_single_for_cpu
comma
dot
id|dma_sync_single_for_device
op_assign
id|pa11_dma_sync_single_for_device
comma
dot
id|dma_sync_sg_for_cpu
op_assign
id|pa11_dma_sync_sg_for_cpu
comma
dot
id|dma_sync_sg_for_device
op_assign
id|pa11_dma_sync_sg_for_device
comma
)brace
suffix:semicolon
DECL|function|fail_alloc_consistent
r_static
r_void
op_star
id|fail_alloc_consistent
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
id|flag
)paren
(brace
r_return
l_int|NULL
suffix:semicolon
)brace
DECL|function|pa11_dma_alloc_noncoherent
r_static
r_void
op_star
id|pa11_dma_alloc_noncoherent
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
id|flag
)paren
(brace
r_void
op_star
id|addr
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* rely on kmalloc to be cacheline aligned */
id|addr
op_assign
id|kmalloc
c_func
(paren
id|size
comma
id|flag
)paren
suffix:semicolon
r_if
c_cond
(paren
id|addr
)paren
(brace
op_star
id|dma_handle
op_assign
(paren
id|dma_addr_t
)paren
id|virt_to_phys
c_func
(paren
id|addr
)paren
suffix:semicolon
)brace
r_return
id|addr
suffix:semicolon
)brace
DECL|function|pa11_dma_free_noncoherent
r_static
r_void
id|pa11_dma_free_noncoherent
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
id|iova
)paren
(brace
id|kfree
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
DECL|variable|pcx_dma_ops
r_struct
id|hppa_dma_ops
id|pcx_dma_ops
op_assign
(brace
dot
id|dma_supported
op_assign
id|pa11_dma_supported
comma
dot
id|alloc_consistent
op_assign
id|fail_alloc_consistent
comma
dot
id|alloc_noncoherent
op_assign
id|pa11_dma_alloc_noncoherent
comma
dot
id|free_consistent
op_assign
id|pa11_dma_free_noncoherent
comma
dot
id|map_single
op_assign
id|pa11_dma_map_single
comma
dot
id|unmap_single
op_assign
id|pa11_dma_unmap_single
comma
dot
id|map_sg
op_assign
id|pa11_dma_map_sg
comma
dot
id|unmap_sg
op_assign
id|pa11_dma_unmap_sg
comma
dot
id|dma_sync_single_cpu
op_assign
id|pa11_dma_sync_single_cpu
comma
dot
id|dma_sync_single_device
op_assign
id|pa11_dma_sync_single_device
comma
dot
id|dma_sync_sg_cpu
op_assign
id|pa11_dma_sync_sg_cpu
comma
dot
id|dma_sync_sg_device
op_assign
id|pa11_dma_sync_sg_device
comma
)brace
suffix:semicolon
DECL|function|pcxl_proc_info
r_static
r_int
id|pcxl_proc_info
c_func
(paren
r_char
op_star
id|buf
comma
r_char
op_star
op_star
id|start
comma
id|off_t
id|offset
comma
r_int
id|len
)paren
(brace
id|u_long
id|i
op_assign
l_int|0
suffix:semicolon
r_int
r_int
op_star
id|res_ptr
op_assign
(paren
id|u_long
op_star
)paren
id|pcxl_res_map
suffix:semicolon
r_int
r_int
id|total_pages
op_assign
id|pcxl_res_size
op_lshift
l_int|3
suffix:semicolon
multiline_comment|/* 8 bits per byte */
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;nDMA Mapping Area size    : %d bytes (%d pages)&bslash;n&quot;
comma
id|PCXL_DMA_MAP_SIZE
comma
(paren
id|pcxl_res_size
op_lshift
l_int|3
)paren
)paren
suffix:semicolon
multiline_comment|/* 1 bit per page */
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%sResource bitmap : %d bytes (%d pages)&bslash;n&quot;
comma
id|buf
comma
id|pcxl_res_size
comma
id|pcxl_res_size
op_lshift
l_int|3
)paren
suffix:semicolon
multiline_comment|/* 8 bits per byte */
id|strcat
c_func
(paren
id|buf
comma
l_string|&quot;     &t;  total:    free:    used:   % used:&bslash;n&quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%sblocks  %8d %8ld %8ld %8ld%%&bslash;n&quot;
comma
id|buf
comma
id|pcxl_res_size
comma
id|pcxl_res_size
op_minus
id|pcxl_used_bytes
comma
id|pcxl_used_bytes
comma
(paren
id|pcxl_used_bytes
op_star
l_int|100
)paren
op_div
id|pcxl_res_size
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%spages   %8ld %8ld %8ld %8ld%%&bslash;n&quot;
comma
id|buf
comma
id|total_pages
comma
id|total_pages
op_minus
id|pcxl_used_pages
comma
id|pcxl_used_pages
comma
(paren
id|pcxl_used_pages
op_star
l_int|100
op_div
id|total_pages
)paren
)paren
suffix:semicolon
id|strcat
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;nResource bitmap:&quot;
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|i
OL
(paren
id|pcxl_res_size
op_div
r_sizeof
(paren
id|u_long
)paren
)paren
suffix:semicolon
op_increment
id|i
comma
op_increment
id|res_ptr
)paren
(brace
r_if
c_cond
(paren
(paren
id|i
op_amp
l_int|7
)paren
op_eq
l_int|0
)paren
id|strcat
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n   &quot;
)paren
suffix:semicolon
id|sprintf
c_func
(paren
id|buf
comma
l_string|&quot;%s %08lx&quot;
comma
id|buf
comma
op_star
id|res_ptr
)paren
suffix:semicolon
)brace
id|strcat
c_func
(paren
id|buf
comma
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|strlen
c_func
(paren
id|buf
)paren
suffix:semicolon
)brace
eof
