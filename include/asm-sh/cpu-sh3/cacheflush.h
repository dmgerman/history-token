multiline_comment|/*&n; * include/asm-sh/cpu-sh3/cacheflush.h&n; *&n; * Copyright (C) 1999 Niibe Yutaka&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH3_CACHEFLUSH_H
DECL|macro|__ASM_CPU_SH3_CACHEFLUSH_H
mdefine_line|#define __ASM_CPU_SH3_CACHEFLUSH_H
multiline_comment|/* &n; * Cache flushing:&n; *&n; *  - flush_cache_all() flushes entire cache&n; *  - flush_cache_mm(mm) flushes the specified mm context&squot;s cache lines&n; *  - flush_cache_page(mm, vmaddr) flushes a single page&n; *  - flush_cache_range(vma, start, end) flushes a range of pages&n; *&n; *  - flush_dcache_page(pg) flushes(wback&amp;invalidates) a page for dcache&n; *  - flush_icache_range(start, end) flushes(invalidates) a range for icache&n; *  - flush_icache_page(vma, pg) flushes(invalidates) a page for icache&n; *&n; *  Caches are indexed (effectively) by physical address on SH-3, so&n; *  we don&squot;t need them.&n; */
macro_line|#if defined(CONFIG_SH7705_CACHE_32KB)
multiline_comment|/* SH7705 is an SH3 processor with 32KB cache. This has alias issues like the&n; * SH4. Unlike the SH4 this is a unified cache so we need to do some work&n; * in mmap when &squot;exec&squot;ing a new binary&n; */
multiline_comment|/* 32KB cache, 4kb PAGE sizes need to check bit 12 */
DECL|macro|CACHE_ALIAS
mdefine_line|#define CACHE_ALIAS 0x00001000
r_struct
id|page
suffix:semicolon
r_struct
id|mm_struct
suffix:semicolon
r_struct
id|vm_area_struct
suffix:semicolon
r_extern
r_void
id|flush_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|flush_cache_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|flush_cache_range
c_func
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
id|flush_cache_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
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
id|pg
)paren
suffix:semicolon
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
DECL|macro|flush_dcache_mmap_lock
mdefine_line|#define flush_dcache_mmap_lock(mapping)&t;&t;do { } while (0)
DECL|macro|flush_dcache_mmap_unlock
mdefine_line|#define flush_dcache_mmap_unlock(mapping)&t;do { } while (0)
multiline_comment|/* SH3 has unified cache so no special action needed here */
DECL|macro|flush_cache_sigtramp
mdefine_line|#define flush_cache_sigtramp(vaddr)&t;&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,pg,adr,len)&t;do { } while (0)
DECL|macro|p3_cache_init
mdefine_line|#define p3_cache_init()&t;&t;&t;&t;do { } while (0)
DECL|macro|PG_mapped
mdefine_line|#define PG_mapped&t;PG_arch_1
multiline_comment|/* We provide our own get_unmapped_area to avoid cache alias issue */
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
macro_line|#else
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
DECL|macro|flush_cache_sigtramp
mdefine_line|#define flush_cache_sigtramp(vaddr)&t;&t;do { } while (0)
DECL|macro|p3_cache_init
mdefine_line|#define p3_cache_init()&t;&t;&t;&t;do { } while (0)
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
macro_line|#endif
macro_line|#endif /* __ASM_CPU_SH3_CACHEFLUSH_H */
eof
