multiline_comment|/*&n; *  linux/include/asm-arm/proc-armo/cache.h&n; *&n; *  Copyright (C) 1999-2001 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  Cache handling for 26-bit ARM processors.&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma,start,end)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma,vmaddr)&t;&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
DECL|macro|invalidate_dcache_range
mdefine_line|#define invalidate_dcache_range(start,end)&t;do { } while (0)
DECL|macro|clean_dcache_range
mdefine_line|#define clean_dcache_range(start,end)&t;&t;do { } while (0)
DECL|macro|flush_dcache_range
mdefine_line|#define flush_dcache_range(start,end)&t;&t;do { } while (0)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;do { } while (0)
DECL|macro|clean_dcache_entry
mdefine_line|#define clean_dcache_entry(_s)      do { } while (0)
DECL|macro|clean_cache_entry
mdefine_line|#define clean_cache_entry(_start)&t;&t;do { } while (0)
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start,end)&t;&t;do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,page)&t;&t;do { } while (0)
multiline_comment|/* DAG: ARM3 will flush cache on MEMC updates anyway? so don&squot;t bother */
DECL|macro|clean_cache_area
mdefine_line|#define clean_cache_area(_start,_size) do { } while (0)
eof
