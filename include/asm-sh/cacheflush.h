macro_line|#ifndef __ASM_SH_CACHEFLUSH_H
DECL|macro|__ASM_SH_CACHEFLUSH_H
mdefine_line|#define __ASM_SH_CACHEFLUSH_H
macro_line|#include &lt;asm/cpu/cacheflush.h&gt;
multiline_comment|/* Flush (write-back only) a region (smaller than a page) */
r_extern
r_void
id|__flush_wback_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Flush (write-back &amp; invalidate) a region (smaller than a page) */
r_extern
r_void
id|__flush_purge_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
suffix:semicolon
multiline_comment|/* Flush (invalidate only) a region (smaller than a page) */
r_extern
r_void
id|__flush_invalidate_region
c_func
(paren
r_void
op_star
id|start
comma
r_int
id|size
)paren
suffix:semicolon
DECL|macro|flush_cache_vmap
mdefine_line|#define flush_cache_vmap(start, end)&t;&t;flush_cache_all()
DECL|macro|flush_cache_vunmap
mdefine_line|#define flush_cache_vunmap(start, end)&t;&t;flush_cache_all()
DECL|macro|copy_to_user_page
mdefine_line|#define copy_to_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;do { memcpy(dst, src, len); &bslash;&n;     flush_icache_user_range(vma, page, vaddr, len); &bslash;&n;} while (0)
DECL|macro|copy_from_user_page
mdefine_line|#define copy_from_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;memcpy(dst, src, len)
macro_line|#endif /* __ASM_SH_CACHEFLUSH_H */
eof
