macro_line|#ifndef _SPARC64_CACHEFLUSH_H
DECL|macro|_SPARC64_CACHEFLUSH_H
mdefine_line|#define _SPARC64_CACHEFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/* Cache flush operations. */
multiline_comment|/* These are the same regardless of whether this is an SMP kernel or not. */
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(__mm) &bslash;&n;&t;do { if ((__mm) == current-&gt;mm) flushw_user(); } while(0)
r_extern
r_void
id|flush_cache_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
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
r_extern
r_void
id|__flush_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#ifndef CONFIG_SMP
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;__flush_cache_all()
macro_line|#else /* CONFIG_SMP */
r_extern
r_void
id|smp_flush_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif /* ! CONFIG_SMP */
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma, pg)&t;do { } while(0)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,pg,adr,len)&t;do { } while (0)
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
multiline_comment|/* This is unnecessary on the SpitFire since D-CACHE is write-through. */
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
macro_line|#endif /* _SPARC64_CACHEFLUSH_H */
eof
