macro_line|#ifndef _MOTOROLA_PGTABLE_H
DECL|macro|_MOTOROLA_PGTABLE_H
mdefine_line|#define _MOTOROLA_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * Definitions for MMU descriptors&n; */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x001
DECL|macro|_PAGE_SHORT
mdefine_line|#define _PAGE_SHORT&t;0x002
DECL|macro|_PAGE_RONLY
mdefine_line|#define _PAGE_RONLY&t;0x004
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x008
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x010
DECL|macro|_PAGE_SUPER
mdefine_line|#define _PAGE_SUPER&t;0x080&t;/* 68040 supervisor only */
DECL|macro|_PAGE_GLOBAL040
mdefine_line|#define _PAGE_GLOBAL040&t;0x400&t;/* 68040 global bit, used for kva descs */
DECL|macro|_PAGE_NOCACHE030
mdefine_line|#define _PAGE_NOCACHE030 0x040&t;/* 68030 no-cache mode */
DECL|macro|_PAGE_NOCACHE
mdefine_line|#define _PAGE_NOCACHE&t;0x060&t;/* 68040 cache mode, non-serialized */
DECL|macro|_PAGE_NOCACHE_S
mdefine_line|#define _PAGE_NOCACHE_S&t;0x040&t;/* 68040 no-cache mode, serialized */
DECL|macro|_PAGE_CACHE040
mdefine_line|#define _PAGE_CACHE040&t;0x020&t;/* 68040 cache mode, cachable, copyback */
DECL|macro|_PAGE_CACHE040W
mdefine_line|#define _PAGE_CACHE040W&t;0x000&t;/* 68040 cache mode, cachable, write-through */
DECL|macro|_DESCTYPE_MASK
mdefine_line|#define _DESCTYPE_MASK&t;0x003
DECL|macro|_CACHEMASK040
mdefine_line|#define _CACHEMASK040&t;(~0x060)
DECL|macro|_TABLE_MASK
mdefine_line|#define _TABLE_MASK&t;(0xfffffe00)
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_SHORT)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY | _PAGE_NOCACHE)
DECL|macro|_PAGE_PROTNONE
mdefine_line|#define _PAGE_PROTNONE&t;0x004
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;0x008&t;/* pagecache or swap? */
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* This is the cache mode to be used for pages containing page descriptors for&n; * processors &gt;= &squot;040. It is in pte_mknocache(), and the variable is defined&n; * and initialized in head.S */
r_extern
r_int
id|m68k_pgtable_cachemode
suffix:semicolon
multiline_comment|/* This is the cache mode for normal pages, for supervisor access on&n; * processors &gt;= &squot;040. It is used in pte_mkcache(), and the variable is&n; * defined and initialized in head.S */
macro_line|#if defined(CPU_M68060_ONLY) &amp;&amp; defined(CONFIG_060_WRITETHROUGH)
DECL|macro|m68k_supervisor_cachemode
mdefine_line|#define m68k_supervisor_cachemode _PAGE_CACHE040W
macro_line|#elif defined(CPU_M68040_OR_M68060_ONLY)
DECL|macro|m68k_supervisor_cachemode
mdefine_line|#define m68k_supervisor_cachemode _PAGE_CACHE040
macro_line|#elif defined(CPU_M68020_OR_M68030_ONLY)
DECL|macro|m68k_supervisor_cachemode
mdefine_line|#define m68k_supervisor_cachemode 0
macro_line|#else
r_extern
r_int
id|m68k_supervisor_cachemode
suffix:semicolon
macro_line|#endif
macro_line|#if defined(CPU_M68040_OR_M68060_ONLY)
DECL|macro|mm_cachebits
mdefine_line|#define mm_cachebits _PAGE_CACHE040
macro_line|#elif defined(CPU_M68020_OR_M68030_ONLY)
DECL|macro|mm_cachebits
mdefine_line|#define mm_cachebits 0
macro_line|#else
r_extern
r_int
r_int
id|mm_cachebits
suffix:semicolon
macro_line|#endif
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PROTNONE | _PAGE_ACCESSED | mm_cachebits)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | mm_cachebits)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED | mm_cachebits)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED | mm_cachebits)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_PRESENT | _PAGE_DIRTY | _PAGE_ACCESSED | mm_cachebits)
multiline_comment|/* Alternate definitions that are compile time constants, for&n;   initializing protection_map.  The cachebits are fixed later.  */
DECL|macro|PAGE_NONE_C
mdefine_line|#define PAGE_NONE_C&t;__pgprot(_PAGE_PROTNONE | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED_C
mdefine_line|#define PAGE_SHARED_C&t;__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY_C
mdefine_line|#define PAGE_COPY_C&t;__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED)
DECL|macro|PAGE_READONLY_C
mdefine_line|#define PAGE_READONLY_C&t;__pgprot(_PAGE_PRESENT | _PAGE_RONLY | _PAGE_ACCESSED)
multiline_comment|/*&n; * The m68k can&squot;t do page protection for execute, and considers that the same are read.&n; * Also, write permissions imply read permissions. This is the closest we can get..&n; */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE_C
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY_C
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_COPY_C
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_COPY_C
DECL|macro|__P100
mdefine_line|#define __P100&t;PAGE_READONLY_C
DECL|macro|__P101
mdefine_line|#define __P101&t;PAGE_READONLY_C
DECL|macro|__P110
mdefine_line|#define __P110&t;PAGE_COPY_C
DECL|macro|__P111
mdefine_line|#define __P111&t;PAGE_COPY_C
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE_C
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY_C
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED_C
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED_C
DECL|macro|__S100
mdefine_line|#define __S100&t;PAGE_READONLY_C
DECL|macro|__S101
mdefine_line|#define __S101&t;PAGE_READONLY_C
DECL|macro|__S110
mdefine_line|#define __S110&t;PAGE_SHARED_C
DECL|macro|__S111
mdefine_line|#define __S111&t;PAGE_SHARED_C
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot) pfn_pte(page_to_pfn(page), (pgprot))
DECL|function|pte_modify
r_static
r_inline
id|pte_t
id|pte_modify
c_func
(paren
id|pte_t
id|pte
comma
id|pgprot_t
id|newprot
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_CHG_MASK
)paren
op_or
id|pgprot_val
c_func
(paren
id|newprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pmd_set
r_static
r_inline
r_void
id|pmd_set
c_func
(paren
id|pmd_t
op_star
id|pmdp
comma
id|pte_t
op_star
id|ptep
)paren
(brace
r_int
r_int
id|ptbl
op_assign
id|virt_to_phys
c_func
(paren
id|ptep
)paren
op_or
id|_PAGE_TABLE
op_or
id|_PAGE_ACCESSED
suffix:semicolon
r_int
r_int
op_star
id|ptr
op_assign
id|pmdp-&gt;pmd
suffix:semicolon
r_int
id|i
op_assign
l_int|16
suffix:semicolon
r_while
c_loop
(paren
op_decrement
id|i
op_ge
l_int|0
)paren
(brace
op_star
id|ptr
op_increment
op_assign
id|ptbl
suffix:semicolon
id|ptbl
op_add_assign
(paren
r_sizeof
(paren
id|pte_t
)paren
op_star
id|PTRS_PER_PTE
op_div
l_int|16
)paren
suffix:semicolon
)brace
)brace
DECL|function|pgd_set
r_static
r_inline
r_void
id|pgd_set
c_func
(paren
id|pgd_t
op_star
id|pgdp
comma
id|pmd_t
op_star
id|pmdp
)paren
(brace
id|pgd_val
c_func
(paren
op_star
id|pgdp
)paren
op_assign
id|_PAGE_TABLE
op_or
id|_PAGE_ACCESSED
op_or
id|__pa
c_func
(paren
id|pmdp
)paren
suffix:semicolon
)brace
DECL|macro|__pte_page
mdefine_line|#define __pte_page(pte) ((unsigned long)__va(pte_val(pte) &amp; PAGE_MASK))
DECL|macro|__pmd_page
mdefine_line|#define __pmd_page(pmd) ((unsigned long)__va(pmd_val(pmd) &amp; _TABLE_MASK))
DECL|macro|__pgd_page
mdefine_line|#define __pgd_page(pgd) ((unsigned long)__va(pgd_val(pgd) &amp; _TABLE_MASK))
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)&t;&t;(!pte_val(pte))
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;(pte_val(pte) &amp; (_PAGE_PRESENT | _PAGE_PROTNONE))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(mm,addr,ptep)&t;&t;({ pte_val(*(ptep)) = 0; })
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)&t;&t;(mem_map + ((unsigned long)(__va(pte_val(pte)) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT))
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(pte)&t;&t;(pte_val(pte) &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot)&t;__pte(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;((pmd_val(pmd) &amp; _DESCTYPE_MASK) != _PAGE_TABLE)
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd)&t;(pmd_val(pmd) &amp; _PAGE_TABLE)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmdp) ({&t;&t;&t;&bslash;&n;&t;unsigned long *__ptr = pmdp-&gt;pmd;&t;&bslash;&n;&t;short __i = 16;&t;&t;&t;&t;&bslash;&n;&t;while (--__i &gt;= 0)&t;&t;&t;&bslash;&n;&t;&t;*__ptr++ = 0;&t;&t;&t;&bslash;&n;})
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;(mem_map + ((unsigned long)(__va(pmd_val(pmd)) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT))
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(!pgd_val(pgd))
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;((pgd_val(pgd) &amp; _DESCTYPE_MASK) != _PAGE_TABLE)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(pgd_val(pgd) &amp; _PAGE_TABLE)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)&t;&t;({ pgd_val(*pgdp) = 0; })
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %08lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|function|pte_read
r_static
r_inline
r_int
id|pte_read
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pte_write
r_static
r_inline
r_int
id|pte_write
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_RONLY
)paren
suffix:semicolon
)brace
DECL|function|pte_exec
r_static
r_inline
r_int
id|pte_exec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pte_dirty
r_static
r_inline
r_int
id|pte_dirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_DIRTY
suffix:semicolon
)brace
DECL|function|pte_young
r_static
r_inline
r_int
id|pte_young
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_ACCESSED
suffix:semicolon
)brace
DECL|function|pte_file
r_static
r_inline
r_int
id|pte_file
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_FILE
suffix:semicolon
)brace
DECL|function|pte_wrprotect
r_static
r_inline
id|pte_t
id|pte_wrprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_RONLY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_rdprotect
r_static
r_inline
id|pte_t
id|pte_rdprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_exprotect
r_static
r_inline
id|pte_t
id|pte_exprotect
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkclean
r_static
r_inline
id|pte_t
id|pte_mkclean
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_DIRTY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkold
r_static
r_inline
id|pte_t
id|pte_mkold
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkwrite
r_static
r_inline
id|pte_t
id|pte_mkwrite
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_RONLY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkread
r_static
r_inline
id|pte_t
id|pte_mkread
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkexec
r_static
r_inline
id|pte_t
id|pte_mkexec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkdirty
r_static
r_inline
id|pte_t
id|pte_mkdirty
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_DIRTY
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkyoung
r_static
r_inline
id|pte_t
id|pte_mkyoung
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mknocache
r_static
r_inline
id|pte_t
id|pte_mknocache
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_CACHEMASK040
)paren
op_or
id|m68k_pgtable_cachemode
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkcache
r_static
r_inline
id|pte_t
id|pte_mkcache
c_func
(paren
id|pte_t
id|pte
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_CACHEMASK040
)paren
op_or
id|m68k_supervisor_cachemode
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|PAGE_DIR_OFFSET
mdefine_line|#define PAGE_DIR_OFFSET(tsk,address) pgd_offset((tsk),(address))
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address)     ((address) &gt;&gt; PGDIR_SHIFT)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|function|pgd_offset
r_static
r_inline
id|pgd_t
op_star
id|pgd_offset
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|mm-&gt;pgd
op_plus
id|pgd_index
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
DECL|macro|swapper_pg_dir
mdefine_line|#define swapper_pg_dir kernel_pg_dir
r_extern
id|pgd_t
id|kernel_pg_dir
(braket
l_int|128
)braket
suffix:semicolon
DECL|function|pgd_offset_k
r_static
r_inline
id|pgd_t
op_star
id|pgd_offset_k
c_func
(paren
r_int
r_int
id|address
)paren
(brace
r_return
id|kernel_pg_dir
op_plus
(paren
id|address
op_rshift
id|PGDIR_SHIFT
)paren
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|function|pmd_offset
r_static
r_inline
id|pmd_t
op_star
id|pmd_offset
c_func
(paren
id|pgd_t
op_star
id|dir
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
id|__pgd_page
c_func
(paren
op_star
id|dir
)paren
op_plus
(paren
(paren
id|address
op_rshift
id|PMD_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PMD
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|function|pte_offset_kernel
r_static
r_inline
id|pte_t
op_star
id|pte_offset_kernel
c_func
(paren
id|pmd_t
op_star
id|pmdp
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pte_t
op_star
)paren
id|__pmd_page
c_func
(paren
op_star
id|pmdp
)paren
op_plus
(paren
(paren
id|address
op_rshift
id|PAGE_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PTE
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(pmdp,address) ((pte_t *)kmap(pmd_page(*pmdp)) + ((address &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1)))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(pmdp, address) pte_offset_map(pmdp, address)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) kunmap(pte)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) kunmap(pte)
multiline_comment|/*&n; * Allocate and free page tables. The xxx_kernel() versions are&n; * used to allocate a kernel page table - this turns on ASN bits&n; * if any.&n; */
multiline_comment|/* Prior to calling these routines, the page should have been flushed&n; * from both the cache and ATC, or the CPU might not notice that the&n; * cache setting for the page has been changed. -jskov&n; */
DECL|function|nocache_page
r_static
r_inline
r_void
id|nocache_page
c_func
(paren
r_void
op_star
id|vaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|vaddr
suffix:semicolon
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
id|dir
op_assign
id|pgd_offset_k
c_func
(paren
id|addr
)paren
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|addr
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmdp
comma
id|addr
)paren
suffix:semicolon
op_star
id|ptep
op_assign
id|pte_mknocache
c_func
(paren
op_star
id|ptep
)paren
suffix:semicolon
)brace
)brace
DECL|function|cache_page
r_static
r_inline
r_void
id|cache_page
c_func
(paren
r_void
op_star
id|vaddr
)paren
(brace
r_int
r_int
id|addr
op_assign
(paren
r_int
r_int
)paren
id|vaddr
suffix:semicolon
r_if
c_cond
(paren
id|CPU_IS_040_OR_060
)paren
(brace
id|pgd_t
op_star
id|dir
suffix:semicolon
id|pmd_t
op_star
id|pmdp
suffix:semicolon
id|pte_t
op_star
id|ptep
suffix:semicolon
id|dir
op_assign
id|pgd_offset_k
c_func
(paren
id|addr
)paren
suffix:semicolon
id|pmdp
op_assign
id|pmd_offset
c_func
(paren
id|dir
comma
id|addr
)paren
suffix:semicolon
id|ptep
op_assign
id|pte_offset_kernel
c_func
(paren
id|pmdp
comma
id|addr
)paren
suffix:semicolon
op_star
id|ptep
op_assign
id|pte_mkcache
c_func
(paren
op_star
id|ptep
)paren
suffix:semicolon
)brace
)brace
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;28
DECL|function|pte_to_pgoff
r_static
r_inline
r_int
r_int
id|pte_to_pgoff
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte.pte
op_rshift
l_int|4
suffix:semicolon
)brace
DECL|function|pgoff_to_pte
r_static
r_inline
id|pte_t
id|pgoff_to_pte
c_func
(paren
r_int
id|off
)paren
(brace
id|pte_t
id|pte
op_assign
(brace
(paren
id|off
op_lshift
l_int|4
)paren
op_plus
id|_PAGE_FILE
)brace
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/* Encode and de-code a swap entry (must be !pte_none(e) &amp;&amp; !pte_present(e)) */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;(((x).val &gt;&gt; 4) &amp; 0xff)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;((x).val &gt;&gt; 12)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset) ((swp_entry_t) { ((type) &lt;&lt; 4) | ((offset) &lt;&lt; 12) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val })
macro_line|#endif&t;/* !__ASSEMBLY__ */
macro_line|#endif /* _MOTOROLA_PGTABLE_H */
eof
