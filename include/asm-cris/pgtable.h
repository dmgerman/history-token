multiline_comment|/* CRIS pgtable.h - macros and functions to manipulate page tables&n; *&n; * HISTORY:&n; *&n; * $Log: pgtable.h,v $&n; * Revision 1.14  2001/12/10 03:08:50  bjornw&n; * Added pgtable_cache_init dummy&n; *&n; * Revision 1.13  2001/11/12 18:05:38  pkj&n; * Added declaration of paging_init().&n; *&n; * Revision 1.12  2001/08/11 00:28:00  bjornw&n; * PAGE_CHG_MASK and PAGE_NONE had somewhat untraditional values&n; *&n; * Revision 1.11  2001/04/04 14:38:36  bjornw&n; * Removed bad_pagetable handling and the _kernel functions&n; *&n; * Revision 1.10  2001/03/23 07:46:42  starvik&n; * Corrected according to review remarks&n; *&n; * Revision 1.9  2000/11/22 14:57:53  bjornw&n; * * extern inline -&gt; static inline&n; * * include asm-generic/pgtable.h&n; *&n; * Revision 1.8  2000/11/21 13:56:16  bjornw&n; * Use CONFIG_CRIS_LOW_MAP for the low VM map instead of explicit CPU type&n; *&n; * Revision 1.7  2000/10/06 15:05:32  bjornw&n; * VMALLOC area changed in memory mapping change&n; *&n; * Revision 1.6  2000/10/04 16:59:14  bjornw&n; * Changed comments&n; *&n; * Revision 1.5  2000/09/13 14:39:53  bjornw&n; * New macros&n; *&n; * Revision 1.4  2000/08/17 15:38:48  bjornw&n; * 2.4.0-test6 modifications:&n; *   * flush_dcache_page added&n; *   * MAP_NR removed&n; *   * virt_to_page added&n; *&n; * Plus some comments and type-clarifications.&n; *&n; * Revision 1.3  2000/08/15 16:33:35  bjornw&n; * pmd_bad should recognize both kernel and user page-tables&n; *&n; * Revision 1.2  2000/07/10 17:06:01  bjornw&n; * Fixed warnings&n; *&n; * Revision 1.1.1.1  2000/07/10 16:32:31  bjornw&n; * CRIS architecture, working draft&n; *&n; *&n; * Revision 1.11  2000/05/29 14:55:56  bjornw&n; * Small tweaks of pte_mk routines&n; *&n; * Revision 1.10  2000/01/27 01:49:06  bjornw&n; * * Ooops. The physical frame number in a PTE entry needs to point to the&n; *   DRAM directly, not to what the kernel thinks is DRAM (due to KSEG mapping).&n; *   Hence we need to strip bit 31 so 0xcXXXXXXX -&gt; 0x4XXXXXXX.&n; *&n; * Revision 1.9  2000/01/26 16:25:50  bjornw&n; * Fixed PAGE_KERNEL bits&n; *&n; * Revision 1.8  2000/01/23 22:53:22  bjornw&n; * Correct flush_tlb_* macros and externs&n; *&n; * Revision 1.7  2000/01/18 16:22:55  bjornw&n; * Use PAGE_MASK instead of PFN_MASK.&n; *&n; * Revision 1.6  2000/01/17 02:42:53  bjornw&n; * Added the pmd_set macro.&n; *&n; * Revision 1.5  2000/01/16 19:53:42  bjornw&n; * Removed VMALLOC_OFFSET. Changed definitions of swapper_pg_dir and zero_page.&n; *&n; * Revision 1.4  2000/01/14 16:38:20  bjornw&n; * PAGE_DIRTY -&gt; PAGE_SILENT_WRITE, removed PAGE_COW from PAGE_COPY.&n; *&n; * Revision 1.3  1999/12/04 20:12:21  bjornw&n; * * PTE bits have moved to asm/mmu.h&n; * * Fixed definitions of the higher level page protection bits&n; * * Added the pte_* functions, including dirty/accessed SW simulation&n; *   (these are exactly the same as for the MIPS port)&n; *&n; * Revision 1.2  1999/12/04 00:41:54  bjornw&n; * * Fixed page table offsets, sizes and shifts&n; * * Removed reference to i386 SMP stuff&n; * * Added stray comments about Linux/CRIS mm design&n; * * Include asm/mmu.h which will contain MMU details&n; *&n; * Revision 1.1  1999/12/03 15:04:02  bjornw&n; * Copied from include/asm-etrax100. For the new CRIS architecture.&n; */
macro_line|#ifndef _CRIS_PGTABLE_H
DECL|macro|_CRIS_PGTABLE_H
mdefine_line|#define _CRIS_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/mmu.h&gt;
multiline_comment|/*&n; * The Linux memory management assumes a three-level page table setup. On&n; * CRIS, we use that, but &quot;fold&quot; the mid level into the top-level page&n; * table. Since the MMU TLB is software loaded through an interrupt, it&n; * supports any page table structure, so we could have used a three-level&n; * setup, but for the amounts of memory we normally use, a two-level is&n; * probably more efficient.&n; *&n; * This file contains the functions and defines necessary to modify and use&n; * the CRIS page table tree.&n; */
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/* The cache doesn&squot;t need to be flushed when TLB entries change because &n; * the cache is mapped to physical memory, not virtual memory&n; */
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
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)                 do { } while (0)
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)          do { } while (0)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma,pg)               do { } while (0)
multiline_comment|/*&n; * TLB flushing (implemented in arch/cris/mm/tlb.c):&n; *&n; *  - flush_tlb() flushes the current mm struct TLBs&n; *  - flush_tlb_all() flushes all processes TLBs&n; *  - flush_tlb_mm(mm) flushes the specified mm context TLB&squot;s&n; *  - flush_tlb_page(vma, vmaddr) flushes one page&n; *  - flush_tlb_range(vma, start, end) flushes a range of pages&n; *&n; */
r_extern
r_void
id|flush_tlb_all
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_page
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
id|flush_tlb_range
c_func
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
suffix:semicolon
DECL|function|flush_tlb_pgtables
r_static
r_inline
r_void
id|flush_tlb_pgtables
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|start
comma
r_int
r_int
id|end
)paren
(brace
multiline_comment|/* CRIS does not keep any page table caches in TLB */
)brace
DECL|function|flush_tlb
r_static
r_inline
r_void
id|flush_tlb
c_func
(paren
r_void
)paren
(brace
id|flush_tlb_mm
c_func
(paren
id|current-&gt;mm
)paren
suffix:semicolon
)brace
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|macro|set_pte
mdefine_line|#define set_pte(pteptr, pteval) ((*(pteptr)) = (pteval))
multiline_comment|/*&n; * (pmds are folded into pgds so this doesnt get actually called,&n; * but the define is needed for a generic inline function.)&n; */
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
multiline_comment|/*&n; * Kernels own virtual memory area. &n; */
macro_line|#ifdef CONFIG_CRIS_LOW_MAP
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START     KSEG_7
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END       KSEG_8
macro_line|#else
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START     KSEG_D
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END       KSEG_E
macro_line|#endif
multiline_comment|/* Define some higher level generic page attributes. The PTE bits are&n; * defined in asm-cris/mmu.h, and these are just combinations of those.&n; */
DECL|macro|__READABLE
mdefine_line|#define __READABLE      (_PAGE_READ | _PAGE_SILENT_READ | _PAGE_ACCESSED)
DECL|macro|__WRITEABLE
mdefine_line|#define __WRITEABLE     (_PAGE_WRITE | _PAGE_SILENT_WRITE | _PAGE_MODIFIED)
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE     (_PAGE_PRESENT | __READABLE | __WRITEABLE)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_ACCESSED | _PAGE_MODIFIED)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE       __pgprot(_PAGE_PRESENT | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_PAGE_PRESENT | __READABLE | _PAGE_WRITE | &bslash;&n;&t;&t;&t;&t; _PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_PAGE_PRESENT | __READABLE)  
singleline_comment|// | _PAGE_COW
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_PAGE_PRESENT | __READABLE)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL     __pgprot(_PAGE_GLOBAL | _PAGE_KERNEL | &bslash;&n;&t;&t;&t;&t; _PAGE_PRESENT | __READABLE | __WRITEABLE)
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE   (_PAGE_TABLE | _PAGE_KERNEL)
multiline_comment|/*&n; * CRIS can&squot;t do page protection for execute, and considers read the same.&n; * Also, write permissions imply read permissions. This is the closest we can&n; * get..&n; */
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
multiline_comment|/* zero page used for uninitialized stuff */
r_extern
r_int
r_int
id|empty_zero_page
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
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
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|function|pgd_none
r_static
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
r_static
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
r_static
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
r_static
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
id|_PAGE_MODIFIED
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
r_static
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
multiline_comment|/* pte_val refers to a page in the 0x4xxxxxxx physical DRAM interval&n; * __pte_page(pte_val) refers to the &quot;virtual&quot; DRAM interval&n; * pte_pagenr refers to the page-number counted starting from the virtual DRAM start&n; */
DECL|function|__pte_page
r_static
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
DECL|macro|page_address
mdefine_line|#define page_address(page)      ((page)-&gt;virtual)
DECL|macro|__page_address
mdefine_line|#define __page_address(page)    (PAGE_OFFSET + (((page) - mem_map) &lt;&lt; PAGE_SHIFT))
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)           (mem_map+pte_pagenr(pte))
multiline_comment|/* only the pte&squot;s themselves need to point to physical DRAM (see above)&n; * the pagetable links are purely handled within the kernel SW and thus&n; * don&squot;t need the __pa and __va transformations.&n; */
DECL|function|pmd_page
r_static
r_inline
r_int
r_int
id|pmd_page
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
id|pmd_val
c_func
(paren
id|pmd
)paren
op_amp
id|PAGE_MASK
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
multiline_comment|/* to find an entry in a page-table-directory. */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) ((address &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD-1))
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
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
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
id|dir
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|function|pte_offset
r_static
r_inline
id|pte_t
op_star
id|pte_offset
c_func
(paren
id|pmd_t
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
id|pte_t
op_star
)paren
id|pmd_page
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
r_static
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
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(x)                     (((x).val &gt;&gt; 5) &amp; 0x7f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(x)                   ((x).val &gt;&gt; 12)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type, offset)         ((swp_entry_t) { ((type) &lt;&lt; 5) | ((offset) &lt;&lt; 12) })
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)           ((swp_entry_t) { pte_val(pte) })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)             ((pte_t) { (x).val })
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|PageSkip
mdefine_line|#define PageSkip(page)          (0)
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)   (1)
macro_line|#include &lt;asm-generic/pgtable.h&gt;
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()   do { } while (0)
macro_line|#endif /* _CRIS_PGTABLE_H */
eof
