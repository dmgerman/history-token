macro_line|#ifndef _I386_CACHEFLUSH_H
DECL|macro|_I386_CACHEFLUSH_H
mdefine_line|#define _I386_CACHEFLUSH_H
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
macro_line|#ifdef CONFIG_DEBUG_PAGEALLOC
multiline_comment|/* internal debugging function */
r_void
id|kernel_map_pages
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
r_int
id|enable
)paren
suffix:semicolon
macro_line|#endif
macro_line|#endif /* _I386_CACHEFLUSH_H */
eof
