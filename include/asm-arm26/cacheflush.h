multiline_comment|/*&n; *  linux/include/asm-arm/cacheflush.h&n; *&n; *  Copyright (C) 2000-2002 Russell King&n; *  Copyright (C) 2003 Ian Molton&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; * ARM26 cache &squot;functions&squot;&n; *&n; */
macro_line|#ifndef _ASMARM_CACHEFLUSH_H
DECL|macro|_ASMARM_CACHEFLUSH_H
mdefine_line|#define _ASMARM_CACHEFLUSH_H
macro_line|#if 1     
singleline_comment|//FIXME - BAD INCLUDES!!!
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#endif
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()                       do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)                      do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma,start,end)        do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma,vmaddr)            do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)                 do { } while (0)
DECL|macro|invalidate_dcache_range
mdefine_line|#define invalidate_dcache_range(start,end)      do { } while (0)
DECL|macro|clean_dcache_range
mdefine_line|#define clean_dcache_range(start,end)           do { } while (0)
DECL|macro|flush_dcache_range
mdefine_line|#define flush_dcache_range(start,end)           do { } while (0)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)                 do { } while (0)
DECL|macro|clean_dcache_entry
mdefine_line|#define clean_dcache_entry(_s)                  do { } while (0)
DECL|macro|clean_cache_entry
mdefine_line|#define clean_cache_entry(_start)               do { } while (0)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(start,end, bob, fred) do { } while (0)
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start,end)           do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,page)             do { } while (0)
multiline_comment|/* DAG: ARM3 will flush cache on MEMC updates anyway? so don&squot;t bother */
multiline_comment|/* IM : Yes, it will, but only if setup to do so (we do this). */
DECL|macro|clean_cache_area
mdefine_line|#define clean_cache_area(_start,_size)          do { } while (0)
macro_line|#endif
eof
