macro_line|#ifndef _ASM_IA64_CACHEFLUSH_H
DECL|macro|_ASM_IA64_CACHEFLUSH_H
mdefine_line|#define _ASM_IA64_CACHEFLUSH_H
multiline_comment|/*&n; * Copyright (C) 2002 Hewlett-Packard Co&n; *&t;David Mosberger-Tang &lt;davidm@hpl.hp.com&gt;&n; */
macro_line|#include &lt;linux/mm.h&gt;
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
mdefine_line|#define flush_cache_page(vma, vmaddr)&t;&t;do { } while (0)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;&t;do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,page)&t;&t;do { } while (0)
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&bslash;&n;&t;clear_bit(PG_arch_1, &amp;page-&gt;flags);&t;&bslash;&n;} while (0)
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
mdefine_line|#define flush_icache_user_range(vma, page, user_addr, len)&t;&t;&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;unsigned long _addr = page_address(page) + ((user_addr) &amp; ~PAGE_MASK);&t;&bslash;&n;&t;flush_icache_range(_addr, _addr + (len));&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* _ASM_IA64_CACHEFLUSH_H */
eof
