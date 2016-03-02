multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000, 01, 02, 03 by Ralf Baechle&n; * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_CACHEFLUSH_H
DECL|macro|_ASM_CACHEFLUSH_H
mdefine_line|#define _ASM_CACHEFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Keep includes the same across arches.  */
macro_line|#include &lt;linux/mm.h&gt;
multiline_comment|/* Cache flushing:&n; *&n; *  - flush_cache_all() flushes entire cache&n; *  - flush_cache_mm(mm) flushes the specified mm context&squot;s cache lines&n; *  - flush_cache_page(mm, vmaddr) flushes a single page&n; *  - flush_cache_range(vma, start, end) flushes a range of pages&n; *  - flush_icache_range(start, end) flush a range of instructions&n; *  - flush_dcache_page(pg) flushes(wback&amp;invalidates) a page for dcache&n; *  - flush_icache_page(vma, pg) flushes(invalidates) a page for icache&n; *&n; * MIPS specific flush operations:&n; *&n; *  - flush_cache_sigtramp() flush signal trampoline&n; *  - flush_icache_all() flush the entire instruction cache&n; *  - flush_data_cache_page() flushes a page from the data cache&n; */
r_extern
r_void
(paren
op_star
id|flush_cache_all
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|__flush_cache_all
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_cache_mm
)paren
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_cache_range
)paren
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
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_cache_page
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
suffix:semicolon
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
(paren
op_star
id|flush_icache_page
)paren
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
(paren
op_star
id|flush_icache_range
)paren
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
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma, page, addr, len)   &bslash;&n;&t;&t;&t;&t;&t;flush_icache_page(vma, page)
DECL|macro|flush_cache_vmap
mdefine_line|#define flush_cache_vmap(start, end)&t;&t;flush_cache_all()
DECL|macro|flush_cache_vunmap
mdefine_line|#define flush_cache_vunmap(start, end)&t;&t;flush_cache_all()
DECL|macro|copy_to_user_page
mdefine_line|#define copy_to_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;do { memcpy(dst, src, len); &bslash;&n;     flush_icache_user_range(vma, page, vaddr, len); &bslash;&n;} while (0)
DECL|macro|copy_from_user_page
mdefine_line|#define copy_from_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;memcpy(dst, src, len)
r_extern
r_void
(paren
op_star
id|flush_cache_sigtramp
)paren
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_icache_all
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|flush_data_cache_page
)paren
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
multiline_comment|/*&n; * This flag is used to indicate that the page pointed to by a pte&n; * is dirty and requires cleaning before returning it to the user.&n; */
DECL|macro|PG_dcache_dirty
mdefine_line|#define PG_dcache_dirty&t;&t;&t;PG_arch_1
DECL|macro|Page_dcache_dirty
mdefine_line|#define Page_dcache_dirty(page)&t;&t;&bslash;&n;&t;test_bit(PG_dcache_dirty, &amp;(page)-&gt;flags)
DECL|macro|SetPageDcacheDirty
mdefine_line|#define SetPageDcacheDirty(page)&t;&bslash;&n;&t;set_bit(PG_dcache_dirty, &amp;(page)-&gt;flags)
DECL|macro|ClearPageDcacheDirty
mdefine_line|#define ClearPageDcacheDirty(page)&t;&bslash;&n;&t;clear_bit(PG_dcache_dirty, &amp;(page)-&gt;flags)
macro_line|#endif /* _ASM_CACHEFLUSH_H */
eof
