macro_line|#ifndef _SUN3_PGTABLE_H
DECL|macro|_SUN3_PGTABLE_H
mdefine_line|#define _SUN3_PGTABLE_H
macro_line|#include &lt;asm/sun3mmu.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/virtconvert.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
multiline_comment|/*&n; * This file contains all the things which change drastically for the sun3&n; * pagetable stuff, to avoid making too much of a mess of the generic m68k&n; * `pgtable.h&squot;; this should only be included from the generic file. --m&n; */
multiline_comment|/* For virtual address to physical address conversion */
DECL|macro|VTOP
mdefine_line|#define VTOP(addr)&t;__pa(addr)
DECL|macro|PTOV
mdefine_line|#define PTOV(addr)&t;__va(addr)
macro_line|#endif&t;/* !__ASSEMBLY__ */
multiline_comment|/* These need to be defined for compatibility although the sun3 doesn&squot;t use them */
DECL|macro|_PAGE_NOCACHE030
mdefine_line|#define _PAGE_NOCACHE030 0x040
DECL|macro|_CACHEMASK040
mdefine_line|#define _CACHEMASK040   (~0x060)
DECL|macro|_PAGE_NOCACHE_S
mdefine_line|#define _PAGE_NOCACHE_S 0x040
multiline_comment|/* Page protection values within PTE. */
DECL|macro|SUN3_PAGE_VALID
mdefine_line|#define SUN3_PAGE_VALID     (0x80000000)
DECL|macro|SUN3_PAGE_WRITEABLE
mdefine_line|#define SUN3_PAGE_WRITEABLE (0x40000000)
DECL|macro|SUN3_PAGE_SYSTEM
mdefine_line|#define SUN3_PAGE_SYSTEM    (0x20000000)
DECL|macro|SUN3_PAGE_NOCACHE
mdefine_line|#define SUN3_PAGE_NOCACHE   (0x10000000)
DECL|macro|SUN3_PAGE_ACCESSED
mdefine_line|#define SUN3_PAGE_ACCESSED  (0x02000000)
DECL|macro|SUN3_PAGE_MODIFIED
mdefine_line|#define SUN3_PAGE_MODIFIED  (0x01000000)
multiline_comment|/* Externally used page protection values. */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;(SUN3_PAGE_VALID)
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;(SUN3_PAGE_ACCESSED)
multiline_comment|/* Compound page protection values. */
singleline_comment|//todo: work out which ones *should* have SUN3_PAGE_NOCACHE and fix...
singleline_comment|// is it just PAGE_KERNEL and PAGE_SHARED?
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(SUN3_PAGE_VALID &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_ACCESSED &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_NOCACHE)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(SUN3_PAGE_VALID &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_WRITEABLE &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_ACCESSED &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_NOCACHE)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(SUN3_PAGE_VALID &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_ACCESSED &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_NOCACHE)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(SUN3_PAGE_VALID &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_ACCESSED &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_NOCACHE)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(SUN3_PAGE_VALID &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_WRITEABLE &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_SYSTEM &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_NOCACHE &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_ACCESSED &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_MODIFIED)
DECL|macro|PAGE_INIT
mdefine_line|#define PAGE_INIT&t;__pgprot(SUN3_PAGE_VALID &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_WRITEABLE &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_SYSTEM &bslash;&n;&t;&t;&t;&t; | SUN3_PAGE_NOCACHE)
multiline_comment|/*&n; * Page protections for initialising protection_map. The sun3 has only two&n; * protection settings, valid (implying read and execute) and writeable. These&n; * are as close as we can get...&n; */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100&t;PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101&t;PAGE_READONLY
DECL|macro|__P110
mdefine_line|#define __P110&t;PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111&t;PAGE_COPY
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100&t;PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101&t;PAGE_READONLY
DECL|macro|__S110
mdefine_line|#define __S110&t;PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111&t;PAGE_SHARED
multiline_comment|/* Use these fake page-protections on PMDs. */
DECL|macro|SUN3_PMD_VALID
mdefine_line|#define SUN3_PMD_VALID&t;(0x00000001)
DECL|macro|SUN3_PMD_MASK
mdefine_line|#define SUN3_PMD_MASK&t;(0x0000003F)
DECL|macro|SUN3_PMD_MAGIC
mdefine_line|#define SUN3_PMD_MAGIC&t;(0x0000002B)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|__mk_pte
mdefine_line|#define __mk_pte(page, pgprot) &bslash;&n;({ pte_t __pte; pte_val(__pte) = (__pa(page) &gt;&gt; PAGE_SHIFT) | pgprot_val(pgprot); __pte; })
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot) __mk_pte(page_address(page), (pgprot))
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage, pgprot) &bslash;&n;({ pte_t __pte; pte_val(__pte) = ((physpage) &gt;&gt; PAGE_SHIFT) | pgprot_val(pgprot); __pte; })
DECL|function|pte_modify
r_extern
r_inline
id|pte_t
id|pte_modify
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
id|SUN3_PAGE_CHG_MASK
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
DECL|macro|pmd_set
mdefine_line|#define pmd_set(pmdp,ptep) do {} while (0)
DECL|function|pgd_set
r_extern
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
id|virt_to_phys
c_func
(paren
id|pmdp
)paren
suffix:semicolon
)brace
DECL|macro|__pte_page
mdefine_line|#define __pte_page(pte) &bslash;&n;((unsigned long) __va ((pte_val (pte) &amp; SUN3_PAGE_PGNUM_MASK) &lt;&lt; PAGE_SHIFT))
DECL|macro|__pmd_page
mdefine_line|#define __pmd_page(pmd) &bslash;&n;((unsigned long) __va (pmd_val (pmd) &amp; PAGE_MASK))
DECL|function|pte_none
r_extern
r_inline
r_int
id|pte_none
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
id|pte_val
(paren
id|pte
)paren
suffix:semicolon
)brace
DECL|function|pte_present
r_extern
r_inline
r_int
id|pte_present
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_val
(paren
id|pte
)paren
op_amp
id|SUN3_PAGE_VALID
suffix:semicolon
)brace
DECL|function|pte_clear
r_extern
r_inline
r_void
id|pte_clear
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
id|pte_val
(paren
op_star
id|ptep
)paren
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* FIXME: this is only a guess */
DECL|macro|pte_pagenr
mdefine_line|#define pte_pagenr(pte)&t;&t;((__pte_page(pte) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT)
multiline_comment|/* Permanent address of a page. */
DECL|macro|page_address
mdefine_line|#define page_address(page)&t;({ if (!(page)-&gt;virtual) BUG(); (page)-&gt;virtual; })
DECL|macro|__page_address
mdefine_line|#define __page_address(page)&t;(PAGE_OFFSET + (((page) - mem_map) &lt;&lt; PAGE_SHIFT))
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)&t;&t;(mem_map+pte_pagenr(pte))
DECL|function|pmd_none2
r_extern
r_inline
r_int
id|pmd_none2
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
r_return
op_logical_neg
id|pmd_val
(paren
op_star
id|pmd
)paren
suffix:semicolon
)brace
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd) pmd_none2(&amp;(pmd))
singleline_comment|//extern inline int pmd_bad (pmd_t pmd) { return (pmd_val (pmd) &amp; SUN3_PMD_MASK) != SUN3_PMD_MAGIC; }
DECL|function|pmd_bad2
r_extern
r_inline
r_int
id|pmd_bad2
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd) pmd_bad2(&amp;(pmd))
DECL|function|pmd_present2
r_extern
r_inline
r_int
id|pmd_present2
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
r_return
id|pmd_val
(paren
op_star
id|pmd
)paren
op_amp
id|SUN3_PMD_VALID
suffix:semicolon
)brace
multiline_comment|/* #define pmd_present(pmd) pmd_present2(&amp;(pmd)) */
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd) (!pmd_none2(&amp;(pmd)))
DECL|function|pmd_clear
r_extern
r_inline
r_void
id|pmd_clear
(paren
id|pmd_t
op_star
id|pmdp
)paren
(brace
id|pmd_val
(paren
op_star
id|pmdp
)paren
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_none
r_extern
r_inline
r_int
id|pgd_none
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_bad
r_extern
r_inline
r_int
id|pgd_bad
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pgd_present
r_extern
r_inline
r_int
id|pgd_present
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
l_int|1
suffix:semicolon
)brace
DECL|function|pgd_clear
r_extern
r_inline
r_void
id|pgd_clear
(paren
id|pgd_t
op_star
id|pgdp
)paren
(brace
)brace
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %08lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not...&n; * [we have the full set here even if they don&squot;t change from m68k]&n; */
DECL|function|pte_read
r_extern
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
r_extern
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|SUN3_PAGE_WRITEABLE
suffix:semicolon
)brace
DECL|function|pte_exec
r_extern
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
r_extern
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
id|SUN3_PAGE_MODIFIED
suffix:semicolon
)brace
DECL|function|pte_young
r_extern
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
id|SUN3_PAGE_ACCESSED
suffix:semicolon
)brace
DECL|function|pte_wrprotect
r_extern
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
op_and_assign
op_complement
id|SUN3_PAGE_WRITEABLE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_rdprotect
r_extern
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
r_extern
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
r_extern
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
id|SUN3_PAGE_MODIFIED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkold
r_extern
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
id|SUN3_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkwrite
r_extern
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
op_or_assign
id|SUN3_PAGE_WRITEABLE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkread
r_extern
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
r_extern
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
r_extern
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
id|SUN3_PAGE_MODIFIED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mkyoung
r_extern
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
id|SUN3_PAGE_ACCESSED
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mknocache
r_extern
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
op_or_assign
id|SUN3_PAGE_NOCACHE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
singleline_comment|// use this version when caches work...
singleline_comment|//extern inline pte_t pte_mkcache(pte_t pte)&t;{ pte_val(pte) &amp;= SUN3_PAGE_NOCACHE; return pte; }
singleline_comment|// until then, use:
DECL|function|pte_mkcache
r_extern
r_inline
id|pte_t
id|pte_mkcache
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
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
r_extern
id|pgd_t
id|kernel_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
multiline_comment|/* Find an entry in a pagetable directory. */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address)     ((address) &gt;&gt; PGDIR_SHIFT)
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) &bslash;&n;((mm)-&gt;pgd + pgd_index(address))
multiline_comment|/* Find an entry in a kernel pagetable directory. */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* Find an entry in the second-level pagetable. */
DECL|function|pmd_offset
r_extern
r_inline
id|pmd_t
op_star
id|pmd_offset
(paren
id|pgd_t
op_star
id|pgd
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
id|pgd
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level pagetable. */
DECL|macro|pte_offset
mdefine_line|#define pte_offset(pmd, address) &bslash;&n;((pte_t *) __pmd_page (*pmd) + ((address &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE-1)))
multiline_comment|/* Disable caching for page at given kernel virtual address. */
DECL|function|nocache_page
r_static
r_inline
r_void
id|nocache_page
(paren
r_int
r_int
id|vaddr
)paren
(brace
multiline_comment|/* Don&squot;t think this is required on sun3. --m */
)brace
multiline_comment|/* Enable caching for page at given kernel virtual address. */
DECL|function|cache_page
r_static
r_inline
r_void
id|cache_page
(paren
r_int
r_int
id|vaddr
)paren
(brace
multiline_comment|/* Don&squot;t think this is required on sun3. --m */
)brace
macro_line|#endif&t;/* !__ASSEMBLY__ */
macro_line|#endif&t;/* !_SUN3_PGTABLE_H */
eof
