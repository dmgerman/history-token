macro_line|#ifndef _PPC64_CACHEFLUSH_H
DECL|macro|_PPC64_CACHEFLUSH_H
mdefine_line|#define _PPC64_CACHEFLUSH_H
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/cputable.h&gt;
multiline_comment|/*&n; * No cache flushing is required when address mappings are&n; * changed, because the caches on PowerPCs are physically&n; * addressed.&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma, start, end)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr)&t;&t;do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma, page)&t;&t;do { } while (0)
DECL|macro|flush_cache_vmap
mdefine_line|#define flush_cache_vmap(start, end)&t;&t;do { } while (0)
DECL|macro|flush_cache_vunmap
mdefine_line|#define flush_cache_vunmap(start, end)&t;&t;do { } while (0)
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
r_extern
r_void
id|__flush_icache_range
c_func
(paren
r_int
r_int
comma
r_int
r_int
)paren
suffix:semicolon
r_extern
r_void
id|flush_icache_user_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
comma
r_int
r_int
id|addr
comma
r_int
id|len
)paren
suffix:semicolon
r_extern
r_void
id|flush_dcache_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|stop
)paren
suffix:semicolon
r_extern
r_void
id|flush_dcache_phys_range
c_func
(paren
r_int
r_int
id|start
comma
r_int
r_int
id|stop
)paren
suffix:semicolon
DECL|macro|copy_to_user_page
mdefine_line|#define copy_to_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;do { memcpy(dst, src, len); &bslash;&n;     flush_icache_user_range(vma, page, vaddr, len); &bslash;&n;} while (0)
DECL|macro|copy_from_user_page
mdefine_line|#define copy_from_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;memcpy(dst, src, len)
r_extern
r_void
id|__flush_dcache_icache
c_func
(paren
r_void
op_star
id|page_va
)paren
suffix:semicolon
DECL|function|flush_icache_range
r_static
r_inline
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
id|stop
)paren
(brace
r_if
c_cond
(paren
op_logical_neg
id|cpu_has_feature
c_func
(paren
id|CPU_FTR_COHERENT_ICACHE
)paren
)paren
id|__flush_icache_range
c_func
(paren
id|start
comma
id|stop
)paren
suffix:semicolon
)brace
macro_line|#endif /* _PPC64_CACHEFLUSH_H */
eof
