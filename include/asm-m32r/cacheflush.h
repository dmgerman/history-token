macro_line|#ifndef _ASM_M32R_CACHEFLUSH_H
DECL|macro|_ASM_M32R_CACHEFLUSH_H
mdefine_line|#define _ASM_M32R_CACHEFLUSH_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
r_extern
r_void
id|_flush_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|_flush_cache_copyback_all
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_CHIP_M32700) || defined(CONFIG_CHIP_OPSP)
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
macro_line|#ifndef CONFIG_SMP
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;_flush_cache_copyback_all()
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)&t;&t;_flush_cache_copyback_all()
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,pg,adr,len)&t;_flush_cache_copyback_all()
DECL|macro|flush_cache_sigtramp
mdefine_line|#define flush_cache_sigtramp(addr)&t;&t;_flush_cache_copyback_all()
macro_line|#else&t;/* CONFIG_SMP */
r_extern
r_void
id|smp_flush_cache_all
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;&t;smp_flush_cache_all()
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)&t;&t;smp_flush_cache_all()
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,pg,adr,len)&t;smp_flush_cache_all()
DECL|macro|flush_cache_sigtramp
mdefine_line|#define flush_cache_sigtramp(addr)&t;&t;_flush_cache_copyback_all()
macro_line|#endif&t;/* CONFIG_SMP */
macro_line|#elif defined(CONFIG_CHIP_M32102)
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
mdefine_line|#define flush_icache_range(start, end)&t;&t;_flush_cache_all()
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)&t;&t;_flush_cache_all()
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma,pg,adr,len)&t;_flush_cache_all()
DECL|macro|flush_cache_sigtramp
mdefine_line|#define flush_cache_sigtramp(addr)&t;&t;_flush_cache_all()
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
mdefine_line|#define flush_cache_sigtramp(addr)&t;&t;do { } while (0)
macro_line|#endif&t;/* CONFIG_CHIP_* */
DECL|macro|flush_cache_vmap
mdefine_line|#define flush_cache_vmap(start, end)&t;do { } while (0)
DECL|macro|flush_cache_vunmap
mdefine_line|#define flush_cache_vunmap(start, end)&t;do { } while (0)
DECL|macro|copy_to_user_page
mdefine_line|#define copy_to_user_page(vma, page, vaddr, dst, src, len)&t;&bslash;&n;do {&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;memcpy(dst, src, len);&t;&t;&t;&t;&t;&bslash;&n;&t;flush_icache_user_range(vma, page, vaddr, len);&t;&t;&bslash;&n;} while (0)
DECL|macro|copy_from_user_page
mdefine_line|#define copy_from_user_page(vma, page, vaddr, dst, src, len)&t;&bslash;&n;&t;memcpy(dst, src, len)
macro_line|#endif /* _ASM_M32R_CACHEFLUSH_H */
eof
