macro_line|#ifndef _M68KNOMMU_CACHEFLUSH_H
DECL|macro|_M68KNOMMU_CACHEFLUSH_H
mdefine_line|#define _M68KNOMMU_CACHEFLUSH_H
multiline_comment|/*&n; * (C) Copyright 2000-2002, Greg Ungerer &lt;gerg@snapgear.com&gt;&n; */
macro_line|#include &lt;asm/io.h&gt;
multiline_comment|/*&n; * Cache handling functions&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all() __flush_cache_all()
DECL|function|__flush_cache_all
r_extern
r_inline
r_void
id|__flush_cache_all
c_func
(paren
r_void
)paren
(brace
macro_line|#ifdef CONFIG_M5407
id|__asm__
id|__volatile__
(paren
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;clrl&t;%%d0&bslash;n&bslash;t&quot;
l_string|&quot;1:&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;%%d0,%%a0&bslash;n&bslash;t&quot;
l_string|&quot;2:&bslash;n&bslash;t&quot;
l_string|&quot;.word&t;0xf4e8&bslash;n&bslash;t&quot;
l_string|&quot;addl&t;#0x10,%%a0&bslash;n&bslash;t&quot;
l_string|&quot;cmpl&t;#0x00000800,%%a0&bslash;n&bslash;t&quot;
l_string|&quot;blt&t;2b&bslash;n&bslash;t&quot;
l_string|&quot;addql&t;#1,%%d0&bslash;n&bslash;t&quot;
l_string|&quot;cmpil&t;#4,%%d0&bslash;n&bslash;t&quot;
l_string|&quot;bne&t;1b&bslash;n&bslash;t&quot;
l_string|&quot;movel  #0x01040100,%%d0&bslash;n&bslash;t&quot;
l_string|&quot;movec  %%d0,%%CACR&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;movel  #0x86088400,%%d0&bslash;n&bslash;t&quot;
l_string|&quot;movec  %%d0,%%CACR&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;d0&quot;
comma
l_string|&quot;a0&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_M5407 */
macro_line|#ifdef CONFIG_M5272
id|__asm__
id|__volatile__
(paren
l_string|&quot;movel&t;#0x01000000, %%d0&bslash;n&bslash;t&quot;
l_string|&quot;movec&t;%%d0, %%CACR&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;#0x80000100, %%d0&bslash;n&bslash;t&quot;
l_string|&quot;movec&t;%%d0, %%CACR&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;d0&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_M5272 */
macro_line|#if 0 /* CONFIG_M5249 */
id|__asm__
id|__volatile__
(paren
l_string|&quot;movel&t;#0x01000000, %%d0&bslash;n&bslash;t&quot;
l_string|&quot;movec&t;%%d0, %%CACR&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
l_string|&quot;movel&t;#0xa0000200, %%d0&bslash;n&bslash;t&quot;
l_string|&quot;movec&t;%%d0, %%CACR&bslash;n&bslash;t&quot;
l_string|&quot;nop&bslash;n&bslash;t&quot;
suffix:colon
suffix:colon
suffix:colon
l_string|&quot;d0&quot;
)paren
suffix:semicolon
macro_line|#endif /* CONFIG_M5249 */
)brace
multiline_comment|/*&n; *&t;FIXME: we could do better than an entire flush in most cases.&n; *&t;But this will always work :-)&n; */
DECL|macro|flush_cache_all
mdefine_line|#define&t;flush_cache_all()&t;&t;__flush_cache_all()
DECL|macro|flush_cache_mm
mdefine_line|#define&t;flush_cache_mm(mm)&t;&t;__flush_cache_all()
DECL|macro|flush_cache_range
mdefine_line|#define&t;flush_cache_range(vma,a,b)&t;__flush_cache_all()
DECL|macro|flush_cache_page
mdefine_line|#define&t;flush_cache_page(vma,p)&t;&t;__flush_cache_all()
DECL|macro|flush_page_to_ram
mdefine_line|#define&t;flush_page_to_ram(page)&t;&t;__flush_cache_all()
DECL|macro|flush_dcache_page
mdefine_line|#define&t;flush_dcache_page(page)&t;&t;__flush_cache_all()
DECL|macro|flush_icache
mdefine_line|#define&t;flush_icache()&t;&t;&t;__flush_cache_all()
DECL|macro|flush_icache_page
mdefine_line|#define&t;flush_icache_page(page)&t;&t;__flush_cache_all()
DECL|macro|flush_icache_range
mdefine_line|#define&t;flush_icache_range(start,len)&t;__flush_cache_all()
DECL|macro|cache_push_v
mdefine_line|#define&t;cache_push_v(vaddr,len)&t;&t;__flush_cache_all()
DECL|macro|cache_push
mdefine_line|#define&t;cache_push(paddr,len)&t;&t;__flush_cache_all()
DECL|macro|cache_clear
mdefine_line|#define&t;cache_clear(paddr,len)&t;&t;__flush_cache_all()
DECL|macro|flush_dcache_range
mdefine_line|#define&t;flush_dcache_range(a,b)
DECL|macro|flush_icache_user_range
mdefine_line|#define&t;flush_icache_user_range(vma,page,addr,len)&t;__flush_cache_all()
macro_line|#endif /* _M68KNOMMU_CACHEFLUSH_H */
eof
