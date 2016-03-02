macro_line|#ifndef _ASM_IA64_CACHEFLUSH_H
DECL|macro|_ASM_IA64_CACHEFLUSH_H
mdefine_line|#define _ASM_IA64_CACHEFLUSH_H
multiline_comment|/*&n; * Copyright (C) 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/page-flags.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/page.h&gt;
multiline_comment|/*&n; * Cache flushing routines.  This is the kind of stuff that can be very expensive, so try&n; * to avoid them whenever possible.&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma, start, end)&t;do { } while (0)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma, vmaddr, pfn)&t;do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,page)&t;&t;do { } while (0)
DECL|macro|flush_cache_vmap
mdefine_line|#define flush_cache_vmap(start, end)&t;&t;do { } while (0)
DECL|macro|flush_cache_vunmap
mdefine_line|#define flush_cache_vunmap(start, end)&t;&t;do { } while (0)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;clear_bit(PG_arch_1, &amp;(page)-&gt;flags);&t;&bslash;&n;} while (0)
DECL|macro|flush_dcache_mmap_lock
mdefine_line|#define flush_dcache_mmap_lock(mapping)&t;&t;do { } while (0)
DECL|macro|flush_dcache_mmap_unlock
mdefine_line|#define flush_dcache_mmap_unlock(mapping)&t;do { } while (0)
r_extern
r_void
id|flush_icache_range
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
mdefine_line|#define flush_icache_user_range(vma, page, user_addr, len)&t;&t;&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long _addr = (unsigned long) page_address(page) + ((user_addr) &amp; ~PAGE_MASK);&t;&bslash;&n;&t;flush_icache_range(_addr, _addr + (len));&t;&t;&t;&t;&t;&t;&bslash;&n;} while (0)
DECL|macro|copy_to_user_page
mdefine_line|#define copy_to_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;do { memcpy(dst, src, len); &bslash;&n;     flush_icache_user_range(vma, page, vaddr, len); &bslash;&n;} while (0)
DECL|macro|copy_from_user_page
mdefine_line|#define copy_from_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;memcpy(dst, src, len)
macro_line|#endif /* _ASM_IA64_CACHEFLUSH_H */
eof
