macro_line|#ifndef _PPC64_CACHEFLUSH_H
DECL|macro|_PPC64_CACHEFLUSH_H
mdefine_line|#define _PPC64_CACHEFLUSH_H
multiline_comment|/* Keep includes the same across arches.  */
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/*&n; * No cache flushing is required when address mappings are&n; * changed, because the caches on PowerPCs are physically&n; * addressed.&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma, start, end)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr)&t;&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
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
r_extern
r_void
id|flush_icache_range
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
id|flush_icache_page
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
id|__flush_dcache_icache
c_func
(paren
r_void
op_star
id|page_va
)paren
suffix:semicolon
macro_line|#endif /* _PPC64_CACHEFLUSH_H */
eof
