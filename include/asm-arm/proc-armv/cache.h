multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/cache.h&n; *&n; *  Copyright (C) 1999-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;asm/mman.h&gt;
macro_line|#include &lt;asm/glue.h&gt;
multiline_comment|/*&n; * This flag is used to indicate that the page pointed to by a pte&n; * is dirty and requires cleaning before returning it to the user.&n; */
DECL|macro|PG_dcache_dirty
mdefine_line|#define PG_dcache_dirty PG_arch_1
multiline_comment|/*&n; * Cache handling for 32-bit ARM processors.&n; *&n; * Note that on ARM, we have a more accurate specification than that&n; * Linux&squot;s &quot;flush&quot;.  We therefore do not use &quot;flush&quot; here, but instead&n; * use:&n; *&n; * clean:      the act of pushing dirty cache entries out to memory.&n; * invalidate: the act of discarding data held within the cache,&n; *             whether it is dirty or not.&n; */
multiline_comment|/*&n; * These are private to the dma-mapping API.  Do not use directly.&n; * Their sole purpose is to ensure that data held in the cache&n; * is visible to DMA, or data written by DMA to system memory is&n; * visible to the CPU.&n; */
DECL|macro|dmac_inv_range
mdefine_line|#define dmac_inv_range&t;&t;&t;cpu_dcache_invalidate_range
DECL|macro|dmac_clean_range
mdefine_line|#define dmac_clean_range&t;&t;cpu_dcache_clean_range
DECL|macro|dmac_flush_range
mdefine_line|#define dmac_flush_range(_s,_e)&t;&t;cpu_cache_clean_invalidate_range((_s),(_e),0)
multiline_comment|/*&n; * Convert calls to our calling convention.&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;cpu_cache_clean_invalidate_all()
DECL|function|flush_cache_mm
r_static
r_inline
r_void
id|flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;active_mm
op_eq
id|mm
)paren
id|cpu_cache_clean_invalidate_all
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|flush_cache_range
id|flush_cache_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;active_mm
op_eq
id|vma-&gt;vm_mm
)paren
id|cpu_cache_clean_invalidate_range
c_func
(paren
id|start
op_amp
id|PAGE_MASK
comma
id|PAGE_ALIGN
c_func
(paren
id|end
)paren
comma
id|vma-&gt;vm_flags
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|flush_cache_page
id|flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|user_addr
)paren
(brace
r_if
c_cond
(paren
id|current-&gt;active_mm
op_eq
id|vma-&gt;vm_mm
)paren
(brace
r_int
r_int
id|addr
op_assign
id|user_addr
op_amp
id|PAGE_MASK
suffix:semicolon
id|cpu_cache_clean_invalidate_range
c_func
(paren
id|addr
comma
id|addr
op_plus
id|PAGE_SIZE
comma
id|vma-&gt;vm_flags
op_amp
id|VM_EXEC
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * Perform necessary cache operations to ensure that data previously&n; * stored within this range of addresses can be executed by the CPU.&n; */
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(s,e)&t;&t;cpu_icache_invalidate_range(s,e)
multiline_comment|/*&n; * Perform necessary cache operations to ensure that the TLB will&n; * see data written in the specified area.&n; */
DECL|macro|clean_dcache_area
mdefine_line|#define clean_dcache_area(start,size) &bslash;&n;&t;cpu_cache_clean_invalidate_range((unsigned long)start, &bslash;&n;&t;&t;&t;&t;&t; ((unsigned long)start) + size, 0);
multiline_comment|/*&n; * flush_dcache_page is used when the kernel has written to the page&n; * cache page at virtual address page-&gt;virtual.&n; *&n; * If this page isn&squot;t mapped (ie, page-&gt;mapping = NULL), or it has&n; * userspace mappings (page-&gt;mapping-&gt;i_mmap or page-&gt;mapping-&gt;i_mmap_shared)&n; * then we _must_ always clean + invalidate the dcache entries associated&n; * with the kernel mapping.&n; *&n; * Otherwise we can defer the operation, and clean the cache when we are&n; * about to change to user space.  This is the same method as used on SPARC64.&n; * See update_mmu_cache for the user space part.&n; */
DECL|macro|mapping_mapped
mdefine_line|#define mapping_mapped(map)&t;(!list_empty(&amp;(map)-&gt;i_mmap) || &bslash;&n;&t;&t;&t;&t; !list_empty(&amp;(map)-&gt;i_mmap_shared))
r_extern
r_void
id|__flush_dcache_page
c_func
(paren
r_struct
id|page
op_star
)paren
suffix:semicolon
DECL|function|flush_dcache_page
r_static
r_inline
r_void
id|flush_dcache_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|page-&gt;mapping
op_logical_and
op_logical_neg
id|mapping_mapped
c_func
(paren
id|page-&gt;mapping
)paren
)paren
id|set_bit
c_func
(paren
id|PG_dcache_dirty
comma
op_amp
id|page-&gt;flags
)paren
suffix:semicolon
r_else
id|__flush_dcache_page
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,page,addr,len) &bslash;&n;&t;flush_dcache_page(page)
multiline_comment|/*&n; * We don&squot;t appear to need to do anything here.  In fact, if we did, we&squot;d&n; * duplicate cache flushing elsewhere performed by flush_dcache_page().&n; */
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,page)&t;do { } while (0)
eof
