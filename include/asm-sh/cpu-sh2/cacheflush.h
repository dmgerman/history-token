multiline_comment|/*&n; * include/asm-sh/cpu-sh2/cacheflush.h&n; *&n; * Copyright (C) 2003 Paul Mundt&n; *&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; */
macro_line|#ifndef __ASM_CPU_SH2_CACHEFLUSH_H
DECL|macro|__ASM_CPU_SH2_CACHEFLUSH_H
mdefine_line|#define __ASM_CPU_SH2_CACHEFLUSH_H
multiline_comment|/* &n; * Cache flushing:&n; *&n; *  - flush_cache_all() flushes entire cache&n; *  - flush_cache_mm(mm) flushes the specified mm context&squot;s cache lines&n; *  - flush_cache_page(mm, vmaddr) flushes a single page&n; *  - flush_cache_range(vma, start, end) flushes a range of pages&n; *&n; *  - flush_dcache_page(pg) flushes(wback&amp;invalidates) a page for dcache&n; *  - flush_icache_range(start, end) flushes(invalidates) a range for icache&n; *  - flush_icache_page(vma, pg) flushes(invalidates) a page for icache&n; *&n; *  Caches are indexed (effectively) by physical address on SH-2, so&n; *  we don&squot;t need them.&n; */
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
DECL|macro|flush_cache_sigtramp
mdefine_line|#define flush_cache_sigtramp(vaddr)&t;&t;do { } while (0)
DECL|macro|p3_cache_init
mdefine_line|#define p3_cache_init()&t;&t;&t;&t;do { } while (0)
macro_line|#endif /* __ASM_CPU_SH2_CACHEFLUSH_H */
eof
