multiline_comment|/*&n; * CRIS pgtable.h - macros and functions to manipulate page tables.&n; */
macro_line|#ifndef _CRIS_PGTABLE_H
DECL|macro|_CRIS_PGTABLE_H
mdefine_line|#define _CRIS_PGTABLE_H
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#endif
macro_line|#include &lt;asm/arch/pgtable.h&gt;
multiline_comment|/*&n; * The Linux memory management assumes a three-level page table setup. On&n; * CRIS, we use that, but &quot;fold&quot; the mid level into the top-level page&n; * table. Since the MMU TLB is software loaded through an interrupt, it&n; * supports any page table structure, so we could have used a three-level&n; * setup, but for the amounts of memory we normally use, a two-level is&n; * probably more efficient.&n; *&n; * This file contains the functions and defines necessary to modify and use&n; * the CRIS page table tree.&n; */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval) ((*(pteptr)) = (pteval))
multiline_comment|/*&n; * (pmds are folded into pgds so this doesn&squot;t get actually called,&n; * but the define is needed for a generic inline function.)&n; */
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdptr, pmdval) (*(pmdptr) = pmdval)
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgdptr, pgdval) (*(pgdptr) = pgdval)
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can&n; * map. It is equal to the page size times the number of PTE&squot;s that fit in&n; * a PMD page. A PTE is 4-bytes in CRIS. Hence the following number.&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;(PAGE_SHIFT + (PAGE_SHIFT-2))
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map.&n; * Since we fold into a two-level structure, this is the same as PMD_SHIFT.&n; */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;PMD_SHIFT
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * entries per page directory level: we use a two-level, so&n; * we don&squot;t really have any PMD directory physically.&n; * pointers are 4 bytes so we can use the page size and &n; * divide it by 4 (shift by 2).&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;(1UL &lt;&lt; (PAGE_SHIFT-2))
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;(1UL &lt;&lt; (PAGE_SHIFT-2))
multiline_comment|/* calculate how many PGD entries a user-level program can use&n; * the first mappable virtual address is 0&n; * (TASK_SIZE is the maximum virtual address space)&n; */
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD       (TASK_SIZE/PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR       0
multiline_comment|/* zero page used for uninitialized stuff */
macro_line|#ifndef __ASSEMBLY__
r_extern
r_int
r_int
id|empty_zero_page
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
macro_line|#endif
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR&t;&t;&t;(8*sizeof(unsigned long))
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK&t;&t;&t;(~(sizeof(void*)-1))
multiline_comment|/* sizeof(void*)==1&lt;&lt;SIZEOF_PTR_LOG2 */
multiline_comment|/* 64-bit machines, beware!  SRB. */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2&t;&t;&t;2
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address) &bslash;&n;((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
multiline_comment|/* to set the page-dir */
DECL|macro|SET_PAGE_DIR
mdefine_line|#define SET_PAGE_DIR(tsk,pgdir)
DECL|macro|pte_none
mdefine_line|#define pte_none(x)&t;(!pte_val(x))
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;(pte_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pte_clear
mdefine_line|#define pte_clear(xp)&t;do { pte_val(*(xp)) = 0; } while (0)
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!pmd_val(x))
multiline_comment|/* by removing the _PAGE_KERNEL bit from the comparision, the same pmd_bad&n; * works for both _PAGE_TABLE and _KERNPG_TABLE pmd entries.&n; */
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(x)&t;((pmd_val(x) &amp; (~PAGE_MASK &amp; ~_PAGE_KERNEL)) != _PAGE_TABLE)
DECL|macro|pmd_present
mdefine_line|#define pmd_present(x)&t;(pmd_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(xp)&t;do { pmd_val(*(xp)) = 0; } while (0)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|function|pgd_none
r_extern
r_inline
r_int
id|pgd_none
c_func
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
c_func
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
c_func
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
c_func
(paren
id|pgd_t
op_star
id|pgdp
)paren
(brace
)brace
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_READ
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
id|_PAGE_WRITE
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_READ
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
id|_PAGE_MODIFIED
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
id|_PAGE_ACCESSED
suffix:semicolon
)brace
DECL|function|pte_file
r_extern
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
(paren
id|_PAGE_WRITE
op_or
id|_PAGE_SILENT_WRITE
)paren
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
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
(paren
id|_PAGE_READ
op_or
id|_PAGE_SILENT_READ
)paren
suffix:semicolon
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
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
(paren
id|_PAGE_READ
op_or
id|_PAGE_SILENT_READ
)paren
suffix:semicolon
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
(paren
id|_PAGE_MODIFIED
op_or
id|_PAGE_SILENT_WRITE
)paren
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
(paren
id|_PAGE_ACCESSED
op_or
id|_PAGE_SILENT_READ
)paren
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
id|_PAGE_WRITE
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_MODIFIED
)paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_SILENT_WRITE
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
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_READ
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_ACCESSED
)paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_SILENT_READ
suffix:semicolon
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
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_READ
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_ACCESSED
)paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_SILENT_READ
suffix:semicolon
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
id|_PAGE_MODIFIED
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_WRITE
)paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_SILENT_WRITE
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
id|_PAGE_ACCESSED
suffix:semicolon
r_if
c_cond
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_READ
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_SILENT_READ
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
(paren
id|_PAGE_WRITE
op_or
id|_PAGE_MODIFIED
)paren
)paren
op_eq
(paren
id|_PAGE_WRITE
op_or
id|_PAGE_MODIFIED
)paren
)paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_SILENT_WRITE
suffix:semicolon
)brace
r_return
id|pte
suffix:semicolon
)brace
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
multiline_comment|/* What actually goes as arguments to the various functions is less than&n; * obvious, but a rule of thumb is that struct page&squot;s goes as struct page *,&n; * really physical DRAM addresses are unsigned long&squot;s, and DRAM &quot;virtual&quot;&n; * addresses (the 0xc0xxxxxx&squot;s) goes as void *&squot;s.&n; */
DECL|function|__mk_pte
r_extern
r_inline
id|pte_t
id|__mk_pte
c_func
(paren
r_void
op_star
id|page
comma
id|pgprot_t
id|pgprot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
multiline_comment|/* the PTE needs a physical address */
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
id|__pa
c_func
(paren
id|page
)paren
op_or
id|pgprot_val
c_func
(paren
id|pgprot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot) __mk_pte(page_address(page), (pgprot))
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage, pgprot) &bslash;&n;({                                                                      &bslash;&n;        pte_t __pte;                                                    &bslash;&n;                                                                        &bslash;&n;        pte_val(__pte) = (physpage) + pgprot_val(pgprot);               &bslash;&n;        __pte;                                                          &bslash;&n;})
DECL|function|pte_modify
r_extern
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
multiline_comment|/* pte_val refers to a page in the 0x4xxxxxxx physical DRAM interval&n; * __pte_page(pte_val) refers to the &quot;virtual&quot; DRAM interval&n; * pte_pagenr refers to the page-number counted starting from the virtual DRAM start&n; */
DECL|function|__pte_page
r_extern
r_inline
r_int
r_int
id|__pte_page
c_func
(paren
id|pte_t
id|pte
)paren
(brace
multiline_comment|/* the PTE contains a physical address */
r_return
(paren
r_int
r_int
)paren
id|__va
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
)brace
DECL|macro|pte_pagenr
mdefine_line|#define pte_pagenr(pte)         ((__pte_page(pte) - PAGE_OFFSET) &gt;&gt; PAGE_SHIFT)
multiline_comment|/* permanent address of a page */
DECL|macro|__page_address
mdefine_line|#define __page_address(page)    (PAGE_OFFSET + (((page) - mem_map) &lt;&lt; PAGE_SHIFT))
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)           (mem_map+pte_pagenr(pte))
multiline_comment|/* only the pte&squot;s themselves need to point to physical DRAM (see above)&n; * the pagetable links are purely handled within the kernel SW and thus&n; * don&squot;t need the __pa and __va transformations.&n; */
DECL|function|pmd_set
r_extern
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
id|pmd_val
c_func
(paren
op_star
id|pmdp
)paren
op_assign
id|_PAGE_TABLE
op_or
(paren
r_int
r_int
)paren
id|ptep
suffix:semicolon
)brace
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;(pfn_to_page(pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd)&t;((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
multiline_comment|/* to find an entry in a page-table-directory. */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) ((address &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD-1))
multiline_comment|/* to find an entry in a page-table-directory */
DECL|function|pgd_offset
r_extern
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
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|function|pmd_offset
r_extern
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
id|dir
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|__pte_offset
mdefine_line|#define __pte_offset(address) &bslash;&n;&t;(((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address) &bslash;&n;&t;((pte_t *) pmd_page_kernel(*(dir)) +  __pte_offset(address))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address) &bslash;&n;&t;((pte_t *)page_address(pmd_page(*(dir))) + __pte_offset(address))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address) pte_offset_map(dir, address)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) do { } while (0)
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)&t;&t;((unsigned long)(__va((x).pte)) &gt;&gt; PAGE_SHIFT)
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot)&t;__pte((__pa((pfn) &lt;&lt; PAGE_SHIFT)) | pgprot_val(prot))
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;        printk(&quot;%s:%d: bad pte %p(%08lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;        printk(&quot;%s:%d: bad pmd %p(%08lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;        printk(&quot;%s:%d: bad pgd %p(%08lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pgd_val(e))
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
multiline_comment|/* defined in head.S */
multiline_comment|/*&n; * CRIS doesn&squot;t have any external MMU info: the kernel page&n; * tables contain all the necessary information.&n; * &n; * Actually I am not sure on what this could be used for.&n; */
DECL|function|update_mmu_cache
r_extern
r_inline
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|address
comma
id|pte_t
id|pte
)paren
(brace
)brace
multiline_comment|/* Encode and de-code a swap entry (must be !pte_none(e) &amp;&amp; !pte_present(e)) */
multiline_comment|/* Since the PAGE_PRESENT bit is bit 4, we can use the bits above */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;&t;(((x).val &gt;&gt; 5) &amp; 0x7f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;&t;((x).val &gt;&gt; 12)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset)&t;((swp_entry_t) { ((type) &lt;&lt; 5) | ((offset) &lt;&lt; 12) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)   (1)
macro_line|#include &lt;asm-generic/pgtable.h&gt;
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()   do { } while (0)
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(x)&t;(pte_val(x) &gt;&gt; 6)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(x)&t;__pte(((x) &lt;&lt; 6) | _PAGE_FILE)
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _CRIS_PGTABLE_H */
eof
