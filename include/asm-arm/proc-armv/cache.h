multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/cache.h&n; *&n; *  Copyright (C) 1999-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#include &lt;asm/mman.h&gt;
macro_line|#include &lt;asm/glue.h&gt;
multiline_comment|/*&n; * This flag is used to indicate that the page pointed to by a pte&n; * is dirty and requires cleaning before returning it to the user.&n; */
DECL|macro|PG_dcache_dirty
mdefine_line|#define PG_dcache_dirty PG_arch_1
multiline_comment|/*&n; * Cache handling for 32-bit ARM processors.&n; *&n; * Note that on ARM, we have a more accurate specification than that&n; * Linux&squot;s &quot;flush&quot;.  We therefore do not use &quot;flush&quot; here, but instead&n; * use:&n; *&n; * clean:      the act of pushing dirty cache entries out to memory.&n; * invalidate: the act of discarding data held within the cache,&n; *             whether it is dirty or not.&n; */
multiline_comment|/*&n; * Generic I + D cache&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_cache_clean_invalidate_all();&t;&t;&t;&bslash;&n;&t;} while (0)
multiline_comment|/* This is always called for current-&gt;mm */
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(_mm)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_mm) == current-&gt;active_mm)&t;&t;&t;&bslash;&n;&t;&t;&t;cpu_cache_clean_invalidate_all();&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(_vma,_start,_end)&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_vma)-&gt;vm_mm == current-&gt;active_mm)&t;&t;&bslash;&n;&t;&t;&t;cpu_cache_clean_invalidate_range((_start), (_end), 1); &bslash;&n;&t;} while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(_vma,_vmaddr)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;if ((_vma)-&gt;vm_mm == current-&gt;active_mm) {&t;&t;&bslash;&n;&t;&t;&t;cpu_cache_clean_invalidate_range((_vmaddr),&t;&bslash;&n;&t;&t;&t;&t;(_vmaddr) + PAGE_SIZE,&t;&t;&t;&bslash;&n;&t;&t;&t;&t;((_vma)-&gt;vm_flags &amp; VM_EXEC));&t;&t;&bslash;&n;&t;&t;} &bslash;&n;&t;} while (0)
multiline_comment|/*&n; * D cache only&n; */
DECL|macro|invalidate_dcache_range
mdefine_line|#define invalidate_dcache_range(_s,_e)&t;cpu_dcache_invalidate_range((_s),(_e))
DECL|macro|clean_dcache_range
mdefine_line|#define clean_dcache_range(_s,_e)&t;cpu_dcache_clean_range((_s),(_e))
DECL|macro|flush_dcache_range
mdefine_line|#define flush_dcache_range(_s,_e)&t;cpu_cache_clean_invalidate_range((_s),(_e),0)
DECL|macro|clean_dcache_area
mdefine_line|#define clean_dcache_area(start,size) &bslash;&n;&t;cpu_cache_clean_invalidate_range((unsigned long)start, &bslash;&n;&t;&t;&t;&t;&t; ((unsigned long)start) + size, 0);
multiline_comment|/*&n; * This is an obsolete interface; the functionality that was provided by this&n; * function is now merged into our flush_dcache_page, flush_icache_page,&n; * copy_user_page and clear_user_page functions.&n; */
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;do { } while (0)
multiline_comment|/*&n; * flush_dcache_page is used when the kernel has written to the page&n; * cache page at virtual address page-&gt;virtual.&n; *&n; * If this page isn&squot;t mapped (ie, page-&gt;mapping = NULL), or it has&n; * userspace mappings (page-&gt;mapping-&gt;i_mmap or page-&gt;mapping-&gt;i_mmap_shared)&n; * then we _must_ always clean + invalidate the dcache entries associated&n; * with the kernel mapping.&n; *&n; * Otherwise we can defer the operation, and clean the cache when we are&n; * about to change to user space.  This is the same method as used on SPARC64.&n; * See update_mmu_cache for the user space part.&n; */
DECL|macro|mapping_mapped
mdefine_line|#define mapping_mapped(map)&t;(!list_empty(&amp;(map)-&gt;i_mmap) || &bslash;&n;&t;&t;&t;&t; !list_empty(&amp;(map)-&gt;i_mmap_shared))
DECL|function|__flush_dcache_page
r_static
r_inline
r_void
id|__flush_dcache_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_int
r_int
id|virt
op_assign
(paren
r_int
r_int
)paren
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|cpu_cache_clean_invalidate_range
c_func
(paren
id|virt
comma
id|virt
op_plus
id|PAGE_SIZE
comma
l_int|0
)paren
suffix:semicolon
)brace
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
DECL|macro|clean_dcache_entry
mdefine_line|#define clean_dcache_entry(_s)&t;&t;cpu_dcache_clean_entry((unsigned long)(_s))
multiline_comment|/*&n; * I cache coherency stuff.&n; *&n; * This *is not* just icache.  It is to make data written to memory&n; * consistent such that instructions fetched from the region are what&n; * we expect.&n; *&n; * This generally means that we have to clean out the Dcache and write&n; * buffers, and maybe flush the Icache in the specified range.&n; */
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(_s,_e)&t;&t;&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;cpu_icache_invalidate_range((_s), (_e));&t;&t;&bslash;&n;&t;} while (0)
eof
