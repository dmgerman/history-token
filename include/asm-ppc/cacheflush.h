multiline_comment|/*&n; * BK Id: %F% %I% %G% %U% %#%&n; */
multiline_comment|/*&n; * include/asm-ppc/cacheflush.h&n; *&n; *  This program is free software; you can redistribute it and/or&n; *  modify it under the terms of the GNU General Public License&n; *  as published by the Free Software Foundation; either version&n; *  2 of the License, or (at your option) any later version.&n; */
macro_line|#ifdef __KERNEL__
macro_line|#ifndef _PPC_CACHEFLUSH_H
DECL|macro|_PPC_CACHEFLUSH_H
mdefine_line|#define _PPC_CACHEFLUSH_H
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/*&n; * No cache flushing is required when address mappings are&n; * changed, because the caches on PowerPCs are physically&n; * addressed.  -- paulus&n; * Also, when SMP we use the coherency (M) bit of the&n; * BATs and PTEs.  -- Cort&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma, a, b)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, p)&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;do { } while (0)
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
r_extern
r_void
id|__flush_dcache_icache_phys
c_func
(paren
r_int
r_int
id|physaddr
)paren
suffix:semicolon
macro_line|#endif /* _PPC_CACHEFLUSH_H */
macro_line|#endif /* __KERNEL__ */
eof
