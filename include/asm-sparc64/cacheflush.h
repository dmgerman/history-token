macro_line|#ifndef _SPARC64_CACHEFLUSH_H
DECL|macro|_SPARC64_CACHEFLUSH_H
mdefine_line|#define _SPARC64_CACHEFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/* Cache flush operations. */
multiline_comment|/* These are the same regardless of whether this is an SMP kernel or not. */
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(__mm) &bslash;&n;&t;do { if ((__mm) == current-&gt;mm) flushw_user(); } while(0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma, start, end) &bslash;&n;&t;flush_cache_mm((vma)-&gt;vm_mm)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, page) &bslash;&n;&t;flush_cache_mm((vma)-&gt;vm_mm)
multiline_comment|/* &n; * On spitfire, the icache doesn&squot;t snoop local stores and we don&squot;t&n; * use block commit stores (which invalidate icache lines) during&n; * module load, so we need this.&n; */
r_extern
r_void
id|flush_icache_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
r_extern
r_void
id|__flush_dcache_page
c_func
(paren
r_void
op_star
id|addr
comma
r_int
id|flush_icache
)paren
suffix:semicolon
r_extern
r_void
id|__flush_icache_page
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|flush_dcache_page_impl
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
r_extern
r_void
id|smp_flush_dcache_page_impl
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|cpu
)paren
suffix:semicolon
r_extern
r_void
id|flush_dcache_page_all
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
macro_line|#else
DECL|macro|smp_flush_dcache_page_impl
mdefine_line|#define smp_flush_dcache_page_impl(page,cpu) flush_dcache_page_impl(page)
DECL|macro|flush_dcache_page_all
mdefine_line|#define flush_dcache_page_all(mm,page) flush_dcache_page_impl(page)
macro_line|#endif
r_extern
r_void
id|__flush_dcache_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma, pg)&t;do { } while(0)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,pg,adr,len)&t;do { } while (0)
DECL|macro|copy_to_user_page
mdefine_line|#define copy_to_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;flush_cache_page(vma, vaddr);&t;&bslash;&n;&t;&t;memcpy(dst, src, len);&t;&t;&bslash;&n;&t;} while (0)
DECL|macro|copy_from_user_page
mdefine_line|#define copy_from_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;do {&t;&t;&t;&t;&t;&bslash;&n;&t;&t;flush_cache_page(vma, vaddr);&t;&bslash;&n;&t;&t;memcpy(dst, src, len);&t;&t;&bslash;&n;&t;} while (0)
r_extern
r_void
id|flush_dcache_page
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
DECL|macro|flush_dcache_mmap_lock
mdefine_line|#define flush_dcache_mmap_lock(mapping)&t;&t;do { } while (0)
DECL|macro|flush_dcache_mmap_unlock
mdefine_line|#define flush_dcache_mmap_unlock(mapping)&t;do { } while (0)
DECL|macro|flush_cache_vmap
mdefine_line|#define flush_cache_vmap(start, end)&t;&t;do { } while (0)
DECL|macro|flush_cache_vunmap
mdefine_line|#define flush_cache_vunmap(start, end)&t;&t;do { } while (0)
macro_line|#endif /* _SPARC64_CACHEFLUSH_H */
eof
