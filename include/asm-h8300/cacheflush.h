multiline_comment|/*&n; * (C) Copyright 2002, Yoshinori Sato &lt;ysato@users.sourceforge.jp&gt;&n; */
macro_line|#ifndef _ASM_H8300_CACHEFLUSH_H
DECL|macro|_AMS_H8300_CACHEFLUSH_H
mdefine_line|#define _AMS_H8300_CACHEFLUSH_H
multiline_comment|/*&n; * Cache handling functions&n; * No Cache memory all dummy functions&n; */
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()
DECL|macro|flush_cache_mm
mdefine_line|#define&t;flush_cache_mm(mm)
DECL|macro|flush_cache_range
mdefine_line|#define&t;flush_cache_range(vma,a,b)
DECL|macro|flush_cache_page
mdefine_line|#define&t;flush_cache_page(vma,p)
DECL|macro|flush_page_to_ram
mdefine_line|#define&t;flush_page_to_ram(page)
DECL|macro|flush_dcache_page
mdefine_line|#define&t;flush_dcache_page(page)
DECL|macro|flush_icache
mdefine_line|#define&t;flush_icache()
DECL|macro|flush_icache_page
mdefine_line|#define&t;flush_icache_page(vma,page)
DECL|macro|flush_icache_range
mdefine_line|#define&t;flush_icache_range(start,len)
DECL|macro|flush_cache_vmap
mdefine_line|#define flush_cache_vmap(start, end)
DECL|macro|flush_cache_vunmap
mdefine_line|#define flush_cache_vunmap(start, end)
DECL|macro|cache_push_v
mdefine_line|#define&t;cache_push_v(vaddr,len)
DECL|macro|cache_push
mdefine_line|#define&t;cache_push(paddr,len)
DECL|macro|cache_clear
mdefine_line|#define&t;cache_clear(paddr,len)
DECL|macro|flush_dcache_range
mdefine_line|#define&t;flush_dcache_range(a,b)
DECL|macro|flush_icache_user_range
mdefine_line|#define&t;flush_icache_user_range(vma,page,addr,len)
DECL|macro|copy_to_user_page
mdefine_line|#define copy_to_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;memcpy(dst, src, len)
DECL|macro|copy_from_user_page
mdefine_line|#define copy_from_user_page(vma, page, vaddr, dst, src, len) &bslash;&n;&t;memcpy(dst, src, len)
macro_line|#endif /* _ASM_H8300_CACHEFLUSH_H */
eof
