macro_line|#ifndef _X8664_CACHEFLUSH_H
DECL|macro|_X8664_CACHEFLUSH_H
mdefine_line|#define _X8664_CACHEFLUSH_H
multiline_comment|/* Keep includes the same across arches.  */
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/* Caches aren&squot;t brain-dead on the intel. */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma, start, end)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr)&t;&t;do { } while (0)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;do { } while (0)
DECL|macro|flush_dcache_mmap_lock
mdefine_line|#define flush_dcache_mmap_lock(mapping)&t;&t;do { } while (0)
DECL|macro|flush_dcache_mmap_unlock
mdefine_line|#define flush_dcache_mmap_unlock(mapping)&t;do { } while (0)
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)&t;&t;do { } while (0)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,pg,adr,len)&t;do { } while (0)
DECL|macro|flush_cache_vmap
mdefine_line|#define flush_cache_vmap(start, end)&t;&t;do { } while (0)
DECL|macro|flush_cache_vunmap
mdefine_line|#define flush_cache_vunmap(start, end)&t;&t;do { } while (0)
DECL|macro|copy_to_user_page
mdefine_line|#define copy_to_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;memcpy(dst, src, len)
DECL|macro|copy_from_user_page
mdefine_line|#define copy_from_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;memcpy(dst, src, len)
r_void
id|global_flush_tlb
c_func
(paren
r_void
)paren
suffix:semicolon
r_int
id|change_page_attr
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_int
id|numpages
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
r_int
id|change_page_attr_addr
c_func
(paren
r_int
r_int
id|addr
comma
r_int
id|numpages
comma
id|pgprot_t
id|prot
)paren
suffix:semicolon
macro_line|#endif /* _X8664_CACHEFLUSH_H */
eof
