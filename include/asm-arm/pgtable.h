multiline_comment|/*&n; *  linux/include/asm-arm/pgtable.h&n; *&n; *  Copyright (C) 1995-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _ASMARM_PGTABLE_H
DECL|macro|_ASMARM_PGTABLE_H
mdefine_line|#define _ASMARM_PGTABLE_H
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/proc-fns.h&gt;
macro_line|#include &lt;asm/arch/vmalloc.h&gt;
multiline_comment|/*&n; * Hardware-wise, we have a two level page table structure, where the first&n; * level has 4096 entries, and the second level has 256 entries.  Each entry&n; * is one 32-bit word.  Most of the bits in the second level entry are used&n; * by hardware, and there aren&squot;t any &quot;accessed&quot; and &quot;dirty&quot; bits.&n; *&n; * Linux on the other hand has a three level page table structure, which can&n; * be wrapped to fit a two level page table structure easily - using the PGD&n; * and PTE only.  However, Linux also expects one &quot;PTE&quot; table per page, and&n; * at least a &quot;dirty&quot; bit.&n; *&n; * Therefore, we tweak the implementation slightly - we tell Linux that we&n; * have 2048 entries in the first level, each of which is 8 bytes (iow, two&n; * hardware pointers to the second level.)  The second level contains two&n; * hardware PTE tables arranged contiguously, followed by Linux versions&n; * which contain the state information Linux needs.  We, therefore, end up&n; * with 512 entries in the &quot;PTE&quot; level.&n; *&n; * This leads to the page tables having the following layout:&n; *&n; *    pgd             pte&n; * |        |&n; * +--------+ +0&n; * |        |-----&gt; +------------+ +0&n; * +- - - - + +4    |  h/w pt 0  |&n; * |        |-----&gt; +------------+ +1024&n; * +--------+ +8    |  h/w pt 1  |&n; * |        |       +------------+ +2048&n; * +- - - - +       | Linux pt 0 |&n; * |        |       +------------+ +3072&n; * +--------+       | Linux pt 1 |&n; * |        |       +------------+ +4096&n; *&n; * See L_PTE_xxx below for definitions of bits in the &quot;Linux pt&quot;, and&n; * PTE_xxx for definitions of bits appearing in the &quot;h/w pt&quot;.&n; *&n; * PMD_xxx definitions refer to bits in the first level page table.&n; *&n; * The &quot;dirty&quot; bit is emulated by only granting hardware write permission&n; * iff the page is marked &quot;writable&quot; and &quot;dirty&quot; in the Linux PTE.  This&n; * means that a write to a clean page will cause a permission fault, and&n; * the Linux MM layer will mark the page dirty via handle_pte_fault().&n; * For the hardware to notice the permission change, the TLB entry must&n; * be flushed, and ptep_establish() does that for us.&n; *&n; * The &quot;accessed&quot; or &quot;young&quot; bit is emulated by a similar method; we only&n; * allow accesses to the page if the &quot;young&quot; bit is set.  Accesses to the&n; * page will cause a fault, and handle_pte_fault() will set the young bit&n; * for us as long as the page is marked present in the corresponding Linux&n; * PTE entry.  Again, ptep_establish() will ensure that the TLB is up to&n; * date.&n; *&n; * However, when the &quot;young&quot; bit is cleared, we deny access to the page&n; * by clearing the hardware PTE.  Currently Linux does not flush the TLB&n; * for us in this case, which means the TLB will retain the transation&n; * until either the TLB entry is evicted under pressure, or a context&n; * switch which changes the user space mapping occurs.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;&t;512
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;&t;1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;&t;2048
multiline_comment|/*&n; * PMD_SHIFT determines the size of the area a second-level page table can map&n; * PGDIR_SHIFT determines what a third-level page table entry can map&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;&t;21
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;&t;21
DECL|macro|LIBRARY_TEXT_START
mdefine_line|#define LIBRARY_TEXT_START&t;0x0c000000
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|__pte_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_void
id|__pmd_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_void
id|__pgd_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(pte)&t;&t;__pte_error(__FILE__, __LINE__, pte_val(pte))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(pmd)&t;&t;__pmd_error(__FILE__, __LINE__, pmd_val(pmd))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(pgd)&t;&t;__pgd_error(__FILE__, __LINE__, pgd_val(pgd))
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;&t;(~(PMD_SIZE-1))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;&t;(~(PGDIR_SIZE-1))
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;1
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;((TASK_SIZE/PGDIR_SIZE) - FIRST_USER_PGD_NR)
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
DECL|macro|PTE_EXT_AP_MASK
mdefine_line|#define PTE_EXT_AP_MASK&t;&t;(3 &lt;&lt; 4)
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
DECL|macro|PTE_SMALL_AP_MASK
mdefine_line|#define PTE_SMALL_AP_MASK&t;(0xff &lt;&lt; 4)
DECL|macro|PTE_SMALL_AP_UNO_SRO
mdefine_line|#define PTE_SMALL_AP_UNO_SRO&t;(0x00 &lt;&lt; 4)
DECL|macro|PTE_SMALL_AP_UNO_SRW
mdefine_line|#define PTE_SMALL_AP_UNO_SRW&t;(0x55 &lt;&lt; 4)
DECL|macro|PTE_SMALL_AP_URO_SRW
mdefine_line|#define PTE_SMALL_AP_URO_SRW&t;(0xaa &lt;&lt; 4)
DECL|macro|PTE_SMALL_AP_URW_SRW
mdefine_line|#define PTE_SMALL_AP_URW_SRW&t;(0xff &lt;&lt; 4)
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
macro_line|#include &lt;asm/domain.h&gt;
DECL|macro|_PAGE_USER_TABLE
mdefine_line|#define _PAGE_USER_TABLE&t;(PMD_TYPE_TABLE | PMD_BIT4 | PMD_DOMAIN(DOMAIN_USER))
DECL|macro|_PAGE_KERNEL_TABLE
mdefine_line|#define _PAGE_KERNEL_TABLE&t;(PMD_TYPE_TABLE | PMD_BIT4 | PMD_DOMAIN(DOMAIN_KERNEL))
multiline_comment|/*&n; * The following macros handle the cache and bufferable bits...&n; */
DECL|macro|_L_PTE_DEFAULT
mdefine_line|#define _L_PTE_DEFAULT&t;L_PTE_PRESENT | L_PTE_YOUNG | L_PTE_CACHEABLE | L_PTE_BUFFERABLE
DECL|macro|_L_PTE_READ
mdefine_line|#define _L_PTE_READ&t;L_PTE_USER | L_PTE_EXEC
r_extern
id|pgprot_t
id|pgprot_kernel
suffix:semicolon
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE       __pgprot(_L_PTE_DEFAULT)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_L_PTE_DEFAULT | _L_PTE_READ)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_L_PTE_DEFAULT | _L_PTE_READ | L_PTE_WRITE)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_L_PTE_DEFAULT | _L_PTE_READ)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;pgprot_kernel
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/*&n; * The table below defines the page protection levels that we insert into our&n; * Linux page table version.  These get translated into the best that the&n; * architecture can perform.  Note that on most ARM hardware:&n; *  1) We cannot do execute protection&n; *  2) If we could do execute protection, then read is implied&n; *  3) write implies read permissions&n; */
DECL|macro|__P000
mdefine_line|#define __P000  PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001  PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010  PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011  PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100  PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101  PAGE_READONLY
DECL|macro|__P110
mdefine_line|#define __P110  PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111  PAGE_COPY
DECL|macro|__S000
mdefine_line|#define __S000  PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001  PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010  PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011  PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100  PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101  PAGE_READONLY
DECL|macro|__S110
mdefine_line|#define __S110  PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111  PAGE_SHARED
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_struct
id|page
op_star
id|empty_zero_page
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;(empty_zero_page)
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(pte)&t;&t;(pte_val(pte) &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn,prot)&t;(__pte(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot)))
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)&t;&t;(!pte_val(pte))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(ptep)&t;&t;set_pte((ptep), __pte(0))
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)&t;&t;(pfn_to_page(pte_pfn(pte)))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir,addr)&t;(pmd_page_kernel(*(dir)) + __pte_index(addr))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir,addr)&t;(pmd_page_kernel(*(dir)) + __pte_index(addr))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir,addr)&t;(pmd_page_kernel(*(dir)) + __pte_index(addr))
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte)&t;&t;do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte)&t;do { } while (0)
DECL|macro|set_pte
mdefine_line|#define set_pte(ptep, pte)&t;cpu_set_pte(ptep,pte)
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;(pte_val(pte) &amp; L_PTE_PRESENT)
DECL|macro|pte_read
mdefine_line|#define pte_read(pte)&t;&t;(pte_val(pte) &amp; L_PTE_USER)
DECL|macro|pte_write
mdefine_line|#define pte_write(pte)&t;&t;(pte_val(pte) &amp; L_PTE_WRITE)
DECL|macro|pte_exec
mdefine_line|#define pte_exec(pte)&t;&t;(pte_val(pte) &amp; L_PTE_EXEC)
DECL|macro|pte_dirty
mdefine_line|#define pte_dirty(pte)&t;&t;(pte_val(pte) &amp; L_PTE_DIRTY)
DECL|macro|pte_young
mdefine_line|#define pte_young(pte)&t;&t;(pte_val(pte) &amp; L_PTE_YOUNG)
multiline_comment|/*&n; * The following only works if pte_present() is not true.&n; */
DECL|macro|pte_file
mdefine_line|#define pte_file(pte)&t;&t;(pte_val(pte) &amp; L_PTE_FILE)
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(x)&t;&t;(pte_val(x) &gt;&gt; 2)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(x)&t;&t;__pte(((x) &lt;&lt; 2) | L_PTE_FILE)
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;30
DECL|macro|PTE_BIT_FUNC
mdefine_line|#define PTE_BIT_FUNC(fn,op) &bslash;&n;static inline pte_t pte_##fn(pte_t pte) { pte_val(pte) op; return pte; }
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
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd)&t;(pmd_val(pmd))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;(pmd_val(pmd) &amp; 2)
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdp,pmd)&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;&t;*(pmdp) = pmd;&t;&t;&bslash;&n;&t;&t;flush_pmd_entry(pmdp);&t;&bslash;&n;&t;} while (0)
DECL|macro|copy_pmd
mdefine_line|#define copy_pmd(pmdpd,pmdps)&t;&t;&bslash;&n;&t;do {&t;&t;&t;&t;&bslash;&n;&t;&t;pmdpd[0] = pmdps[0];&t;&bslash;&n;&t;&t;pmdpd[1] = pmdps[1];&t;&bslash;&n;&t;&t;flush_pmd_entry(pmdpd);&t;&bslash;&n;&t;} while (0)
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
multiline_comment|/*&n; * Permanent address of a page. We never have highmem, so this is trivial.&n; */
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x)&t;&t;((x) &gt;&gt; (20 - PAGE_SHIFT))
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page,prot)&t;pfn_pte(page_to_pfn(page),prot)
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(0)
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;(0)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(1)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)&t;&t;do { } while (0)
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgd,pgdp)&t;do { } while (0)
DECL|macro|page_pte_prot
mdefine_line|#define page_pte_prot(page,prot)&t;mk_pte(page, prot)
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;&t;mk_pte(page, __pgprot(0))
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(addr)&t;&t;((addr) &gt;&gt; PGDIR_SHIFT)
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, addr)&t;((mm)-&gt;pgd+pgd_index(addr))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(addr)&t;pgd_offset(&amp;init_mm, addr)
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir, addr)&t;((pmd_t *)(dir))
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|__pte_index
mdefine_line|#define __pte_index(addr)&t;(((addr) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
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
r_const
r_int
r_int
id|mask
op_assign
id|L_PTE_EXEC
op_or
id|L_PTE_WRITE
op_or
id|L_PTE_USER
suffix:semicolon
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
op_complement
id|mask
)paren
op_or
(paren
id|pgprot_val
c_func
(paren
id|newprot
)paren
op_amp
id|mask
)paren
suffix:semicolon
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
multiline_comment|/* Encode and decode a swap entry.&n; *&n; * We support up to 32GB of swap on 4k machines&n; */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;(((x).val &gt;&gt; 2) &amp; 0x7f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;((x).val &gt;&gt; 9)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type,offset) ((swp_entry_t) { ((type) &lt;&lt; 2) | ((offset) &lt;&lt; 9) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(swp)&t;((pte_t) { (swp).val })
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
multiline_comment|/* FIXME: this is not correct */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
macro_line|#include &lt;asm-generic/pgtable.h&gt;
multiline_comment|/*&n; * We provide our own arch_get_unmapped_area to cope with VIPT caches.&n; */
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
multiline_comment|/*&n; * remap a physical address `phys&squot; of size `size&squot; with page protection `prot&squot;&n; * into virtual address `from&squot;&n; */
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma,from,phys,size,prot) &bslash;&n;&t;&t;remap_pfn_range(vma, from, (phys) &gt;&gt; PAGE_SHIFT, size, prot)
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init() do { } while (0)
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASMARM_PGTABLE_H */
eof
