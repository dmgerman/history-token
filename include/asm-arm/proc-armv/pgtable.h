multiline_comment|/*&n; *  linux/include/asm-arm/proc-armv/pgtable.h&n; *&n; *  Copyright (C) 1995-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; *&n; *  12-Jan-1997&t;RMK&t;Altered flushing routines to use function pointers&n; *&t;&t;&t;now possible to combine ARM6, ARM7 and StrongARM versions.&n; *  17-Apr-1999&t;RMK&t;Now pass an area size to clean_cache_area and&n; *&t;&t;&t;flush_icache_area.&n; */
macro_line|#ifndef __ASM_PROC_PGTABLE_H
DECL|macro|__ASM_PROC_PGTABLE_H
mdefine_line|#define __ASM_PROC_PGTABLE_H
multiline_comment|/*&n; * We pull a couple of tricks here:&n; *  1. We wrap the PMD into the PGD.&n; *  2. We lie about the size of the PTE and PGD.&n; * Even though we have 256 PTE entries and 4096 PGD entries, we tell&n; * Linux that we actually have 512 PTE entries and 2048 PGD entries.&n; * Each &quot;Linux&quot; PGD entry is made up of two hardware PGD entries, and&n; * each PTE table is actually two hardware PTE tables.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;&t;512
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;&t;1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;&t;2048
multiline_comment|/*&n; * Hardware page table definitions.&n; *&n; * + Level 1 descriptor (PMD)&n; *   - common&n; */
DECL|macro|PMD_TYPE_MASK
mdefine_line|#define PMD_TYPE_MASK&t;&t;(3 &lt;&lt; 0)
DECL|macro|PMD_TYPE_FAULT
mdefine_line|#define PMD_TYPE_FAULT&t;&t;(0 &lt;&lt; 0)
DECL|macro|PMD_TYPE_TABLE
mdefine_line|#define PMD_TYPE_TABLE&t;&t;(1 &lt;&lt; 0)
DECL|macro|PMD_TYPE_SECT
mdefine_line|#define PMD_TYPE_SECT&t;&t;(2 &lt;&lt; 0)
DECL|macro|PMD_BIT4
mdefine_line|#define PMD_BIT4&t;&t;(1 &lt;&lt; 4)
DECL|macro|PMD_DOMAIN
mdefine_line|#define PMD_DOMAIN(x)&t;&t;((x) &lt;&lt; 5)
DECL|macro|PMD_PROTECTION
mdefine_line|#define PMD_PROTECTION&t;&t;(1 &lt;&lt; 9)&t;/* v5 */
multiline_comment|/*&n; *   - section&n; */
DECL|macro|PMD_SECT_BUFFERABLE
mdefine_line|#define PMD_SECT_BUFFERABLE&t;(1 &lt;&lt; 2)
DECL|macro|PMD_SECT_CACHEABLE
mdefine_line|#define PMD_SECT_CACHEABLE&t;(1 &lt;&lt; 3)
DECL|macro|PMD_SECT_AP_WRITE
mdefine_line|#define PMD_SECT_AP_WRITE&t;(1 &lt;&lt; 10)
DECL|macro|PMD_SECT_AP_READ
mdefine_line|#define PMD_SECT_AP_READ&t;(1 &lt;&lt; 11)
DECL|macro|PMD_SECT_TEX
mdefine_line|#define PMD_SECT_TEX(x)&t;&t;((x) &lt;&lt; 12)&t;/* v5 */
DECL|macro|PMD_SECT_APX
mdefine_line|#define PMD_SECT_APX&t;&t;(1 &lt;&lt; 15)&t;/* v6 */
DECL|macro|PMD_SECT_S
mdefine_line|#define PMD_SECT_S&t;&t;(1 &lt;&lt; 16)&t;/* v6 */
DECL|macro|PMD_SECT_nG
mdefine_line|#define PMD_SECT_nG&t;&t;(1 &lt;&lt; 17)&t;/* v6 */
DECL|macro|PMD_SECT_UNCACHED
mdefine_line|#define PMD_SECT_UNCACHED&t;(0)
DECL|macro|PMD_SECT_BUFFERED
mdefine_line|#define PMD_SECT_BUFFERED&t;(PMD_SECT_BUFFERABLE)
DECL|macro|PMD_SECT_WT
mdefine_line|#define PMD_SECT_WT&t;&t;(PMD_SECT_CACHEABLE)
DECL|macro|PMD_SECT_WB
mdefine_line|#define PMD_SECT_WB&t;&t;(PMD_SECT_CACHEABLE | PMD_SECT_BUFFERABLE)
DECL|macro|PMD_SECT_MINICACHE
mdefine_line|#define PMD_SECT_MINICACHE&t;(PMD_SECT_TEX(1) | PMD_SECT_CACHEABLE)
DECL|macro|PMD_SECT_WBWA
mdefine_line|#define PMD_SECT_WBWA&t;&t;(PMD_SECT_TEX(1) | PMD_SECT_CACHEABLE | PMD_SECT_BUFFERABLE)
multiline_comment|/*&n; *   - coarse table (not used)&n; */
multiline_comment|/*&n; * + Level 2 descriptor (PTE)&n; *   - common&n; */
DECL|macro|PTE_TYPE_MASK
mdefine_line|#define PTE_TYPE_MASK&t;&t;(3 &lt;&lt; 0)
DECL|macro|PTE_TYPE_FAULT
mdefine_line|#define PTE_TYPE_FAULT&t;&t;(0 &lt;&lt; 0)
DECL|macro|PTE_TYPE_LARGE
mdefine_line|#define PTE_TYPE_LARGE&t;&t;(1 &lt;&lt; 0)
DECL|macro|PTE_TYPE_SMALL
mdefine_line|#define PTE_TYPE_SMALL&t;&t;(2 &lt;&lt; 0)
DECL|macro|PTE_TYPE_EXT
mdefine_line|#define PTE_TYPE_EXT&t;&t;(3 &lt;&lt; 0)&t;/* v5 */
DECL|macro|PTE_BUFFERABLE
mdefine_line|#define PTE_BUFFERABLE&t;&t;(1 &lt;&lt; 2)
DECL|macro|PTE_CACHEABLE
mdefine_line|#define PTE_CACHEABLE&t;&t;(1 &lt;&lt; 3)
multiline_comment|/*&n; *   - extended small page/tiny page&n; */
DECL|macro|PTE_EXT_AP_UNO_SRO
mdefine_line|#define PTE_EXT_AP_UNO_SRO&t;(0 &lt;&lt; 4)
DECL|macro|PTE_EXT_AP_UNO_SRW
mdefine_line|#define PTE_EXT_AP_UNO_SRW&t;(1 &lt;&lt; 4)
DECL|macro|PTE_EXT_AP_URO_SRW
mdefine_line|#define PTE_EXT_AP_URO_SRW&t;(2 &lt;&lt; 4)
DECL|macro|PTE_EXT_AP_URW_SRW
mdefine_line|#define PTE_EXT_AP_URW_SRW&t;(3 &lt;&lt; 4)
DECL|macro|PTE_EXT_TEX
mdefine_line|#define PTE_EXT_TEX(x)&t;&t;((x) &lt;&lt; 6)&t;/* v5 */
multiline_comment|/*&n; *   - small page&n; */
DECL|macro|PTE_SMALL_AP_UNO_SRO
mdefine_line|#define PTE_SMALL_AP_UNO_SRO&t;(0x00 &lt;&lt; 4)
DECL|macro|PTE_SMALL_AP_UNO_SRW
mdefine_line|#define PTE_SMALL_AP_UNO_SRW&t;(0x55 &lt;&lt; 4)
DECL|macro|PTE_SMALL_AP_URO_SRW
mdefine_line|#define PTE_SMALL_AP_URO_SRW&t;(0xaa &lt;&lt; 4)
DECL|macro|PTE_SMALL_AP_URW_SRW
mdefine_line|#define PTE_SMALL_AP_URW_SRW&t;(0xff &lt;&lt; 4)
DECL|macro|PTE_AP_READ
mdefine_line|#define PTE_AP_READ&t;&t;PTE_SMALL_AP_URO_SRW
DECL|macro|PTE_AP_WRITE
mdefine_line|#define PTE_AP_WRITE&t;&t;PTE_SMALL_AP_UNO_SRW
multiline_comment|/*&n; * &quot;Linux&quot; PTE definitions.&n; *&n; * We keep two sets of PTEs - the hardware and the linux version.&n; * This allows greater flexibility in the way we map the Linux bits&n; * onto the hardware tables, and allows us to have YOUNG and DIRTY&n; * bits.&n; *&n; * The PTE table pointer refers to the hardware entries; the &quot;Linux&quot;&n; * entries are stored 1024 bytes below.&n; */
DECL|macro|L_PTE_PRESENT
mdefine_line|#define L_PTE_PRESENT&t;&t;(1 &lt;&lt; 0)
DECL|macro|L_PTE_FILE
mdefine_line|#define L_PTE_FILE&t;&t;(1 &lt;&lt; 1)&t;/* only when !PRESENT */
DECL|macro|L_PTE_YOUNG
mdefine_line|#define L_PTE_YOUNG&t;&t;(1 &lt;&lt; 1)
DECL|macro|L_PTE_BUFFERABLE
mdefine_line|#define L_PTE_BUFFERABLE&t;(1 &lt;&lt; 2)&t;/* matches PTE */
DECL|macro|L_PTE_CACHEABLE
mdefine_line|#define L_PTE_CACHEABLE&t;&t;(1 &lt;&lt; 3)&t;/* matches PTE */
DECL|macro|L_PTE_USER
mdefine_line|#define L_PTE_USER&t;&t;(1 &lt;&lt; 4)
DECL|macro|L_PTE_WRITE
mdefine_line|#define L_PTE_WRITE&t;&t;(1 &lt;&lt; 5)
DECL|macro|L_PTE_EXEC
mdefine_line|#define L_PTE_EXEC&t;&t;(1 &lt;&lt; 6)
DECL|macro|L_PTE_DIRTY
mdefine_line|#define L_PTE_DIRTY&t;&t;(1 &lt;&lt; 7)
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/proc/domain.h&gt;
DECL|macro|_PAGE_USER_TABLE
mdefine_line|#define _PAGE_USER_TABLE&t;(PMD_TYPE_TABLE | PMD_BIT4 | PMD_DOMAIN(DOMAIN_USER))
DECL|macro|_PAGE_KERNEL_TABLE
mdefine_line|#define _PAGE_KERNEL_TABLE&t;(PMD_TYPE_TABLE | PMD_BIT4 | PMD_DOMAIN(DOMAIN_KERNEL))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;(pmd_val(pmd) &amp; 2)
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdp,pmd)&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;&t;*pmdp = pmd;&t;&t;&bslash;&n;&t;&t;flush_pmd_entry(pmdp);&t;&bslash;&n;&t;} while (0)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmdp)&t;&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;&t;pmdp[0] = __pmd(0);&t;&bslash;&n;&t;&t;pmdp[1] = __pmd(0);&t;&bslash;&n;&t;&t;clean_pmd_entry(pmdp);&t;&bslash;&n;&t;} while (0)
DECL|function|pmd_page_kernel
r_static
r_inline
id|pte_t
op_star
id|pmd_page_kernel
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_int
r_int
id|ptr
suffix:semicolon
id|ptr
op_assign
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
op_complement
(paren
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
r_void
op_star
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|ptr
op_add_assign
id|PTRS_PER_PTE
op_star
r_sizeof
(paren
r_void
op_star
)paren
suffix:semicolon
r_return
id|__va
c_func
(paren
id|ptr
)paren
suffix:semicolon
)brace
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) virt_to_page(__va(pmd_val(pmd)))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir,addr)&t;(pmd_page_kernel(*(dir)) + __pte_index(addr))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir,addr)&t;(pmd_page_kernel(*(dir)) + __pte_index(addr))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir,addr)&t;(pmd_page_kernel(*(dir)) + __pte_index(addr))
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte)&t;&t;&t;do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte)&t;&t;do { } while (0)
DECL|macro|set_pte
mdefine_line|#define set_pte(ptep, pte)&t;cpu_set_pte(ptep,pte)
multiline_comment|/*&n; * The following macros handle the cache and bufferable bits...&n; */
DECL|macro|_L_PTE_DEFAULT
mdefine_line|#define _L_PTE_DEFAULT&t;L_PTE_PRESENT | L_PTE_YOUNG
DECL|macro|_L_PTE_READ
mdefine_line|#define _L_PTE_READ&t;L_PTE_USER | L_PTE_EXEC | L_PTE_CACHEABLE | L_PTE_BUFFERABLE
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE       __pgprot(_L_PTE_DEFAULT)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_L_PTE_DEFAULT | _L_PTE_READ)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_L_PTE_DEFAULT | _L_PTE_READ | L_PTE_WRITE)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_L_PTE_DEFAULT | _L_PTE_READ)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL     __pgprot(_L_PTE_DEFAULT | L_PTE_CACHEABLE | L_PTE_BUFFERABLE | L_PTE_DIRTY | L_PTE_WRITE | L_PTE_EXEC)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | L_PTE_DIRTY | L_PTE_YOUNG)
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;&t;(pte_val(pte) &amp; L_PTE_PRESENT)
DECL|macro|pte_read
mdefine_line|#define pte_read(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_USER)
DECL|macro|pte_write
mdefine_line|#define pte_write(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_WRITE)
DECL|macro|pte_exec
mdefine_line|#define pte_exec(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_EXEC)
DECL|macro|pte_dirty
mdefine_line|#define pte_dirty(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_DIRTY)
DECL|macro|pte_young
mdefine_line|#define pte_young(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_YOUNG)
DECL|macro|pte_file
mdefine_line|#define pte_file(pte)&t;&t;&t;(pte_val(pte) &amp; L_PTE_FILE)
DECL|macro|PTE_BIT_FUNC
mdefine_line|#define PTE_BIT_FUNC(fn,op)&t;&t;&t;&bslash;&n;static inline pte_t pte_##fn(pte_t pte) { pte_val(pte) op; return pte; }
multiline_comment|/*PTE_BIT_FUNC(rdprotect, &amp;= ~L_PTE_USER);*/
multiline_comment|/*PTE_BIT_FUNC(mkread,    |= L_PTE_USER);*/
id|PTE_BIT_FUNC
c_func
(paren
id|wrprotect
comma
op_and_assign
op_complement
id|L_PTE_WRITE
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkwrite
comma
op_or_assign
id|L_PTE_WRITE
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|exprotect
comma
op_and_assign
op_complement
id|L_PTE_EXEC
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkexec
comma
op_or_assign
id|L_PTE_EXEC
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkclean
comma
op_and_assign
op_complement
id|L_PTE_DIRTY
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkdirty
comma
op_or_assign
id|L_PTE_DIRTY
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkold
comma
op_and_assign
op_complement
id|L_PTE_YOUNG
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkyoung
comma
op_or_assign
id|L_PTE_YOUNG
)paren
suffix:semicolon
multiline_comment|/*&n; * Mark the prot value as uncacheable and unbufferable.&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached(prot)&t;__pgprot(pgprot_val(prot) &amp; ~(L_PTE_CACHEABLE | L_PTE_BUFFERABLE))
DECL|macro|pgprot_writecombine
mdefine_line|#define pgprot_writecombine(prot) __pgprot(pgprot_val(prot) &amp; ~L_PTE_CACHEABLE)
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init() do { } while (0)
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(x)&t;(pte_val(x) &gt;&gt; 2)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(x)&t;__pte(((x) &lt;&lt; 2) | L_PTE_FILE)
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;30
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* __ASM_PROC_PGTABLE_H */
eof
