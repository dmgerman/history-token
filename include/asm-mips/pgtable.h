multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000 by Ralf Baechle at alii&n; * Copyright (C) 1999 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PGTABLE_H
DECL|macro|_ASM_PGTABLE_H
mdefine_line|#define _ASM_PGTABLE_H
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#ifndef _LANGUAGE_ASSEMBLY
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/* Cache flushing:&n; *&n; *  - flush_cache_all() flushes entire cache&n; *  - flush_cache_mm(mm) flushes the specified mm context&squot;s cache lines&n; *  - flush_cache_page(mm, vmaddr) flushes a single page&n; *  - flush_cache_range(vma, start, end) flushes a range of pages&n; *  - flush_page_to_ram(page) write back kernel page to ram&n; *  - flush_icache_range(start, end) flush a range of instructions&n; */
r_extern
r_void
(paren
op_star
id|_flush_cache_all
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|___flush_cache_all
)paren
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_flush_cache_mm
)paren
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_flush_cache_range
)paren
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
r_extern
r_void
(paren
op_star
id|_flush_cache_page
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_int
r_int
id|page
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_flush_cache_sigtramp
)paren
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_flush_page_to_ram
)paren
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
r_extern
r_void
(paren
op_star
id|_flush_icache_range
)paren
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
r_extern
r_void
(paren
op_star
id|_flush_icache_page
)paren
(paren
r_struct
id|vm_area_struct
op_star
id|vma
comma
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
DECL|macro|flush_dcache_page
mdefine_line|#define flush_dcache_page(page)&t;&t;&t;do { } while (0)
DECL|macro|flush_cache_all
mdefine_line|#define flush_cache_all()&t;&t;_flush_cache_all()
DECL|macro|__flush_cache_all
mdefine_line|#define __flush_cache_all()&t;&t;___flush_cache_all()
DECL|macro|flush_cache_mm
mdefine_line|#define flush_cache_mm(mm)&t;&t;_flush_cache_mm(mm)
DECL|macro|flush_cache_range
mdefine_line|#define flush_cache_range(vma,start,end) _flush_cache_range(vma,start,end)
DECL|macro|flush_cache_page
mdefine_line|#define flush_cache_page(vma,page)&t;_flush_cache_page(vma, page)
DECL|macro|flush_cache_sigtramp
mdefine_line|#define flush_cache_sigtramp(addr)&t;_flush_cache_sigtramp(addr)
DECL|macro|flush_page_to_ram
mdefine_line|#define flush_page_to_ram(page)&t;&t;_flush_page_to_ram(page)
DECL|macro|flush_icache_range
mdefine_line|#define flush_icache_range(start, end)&t;_flush_icache_range(start,end)
DECL|macro|flush_icache_page
mdefine_line|#define flush_icache_page(vma, page) &t;_flush_icache_page(vma, page)
DECL|macro|flush_icache_user_range
mdefine_line|#define flush_icache_user_range(vma, page, addr, len)&t;&bslash;&n;&t;&t;&t;&t;&t;_flush_icache_page((vma), (page))
multiline_comment|/*&n; * - add_wired_entry() add a fixed TLB entry, and move wired register&n; */
r_extern
r_void
id|add_wired_entry
c_func
(paren
r_int
r_int
id|entrylo0
comma
r_int
r_int
id|entrylo1
comma
r_int
r_int
id|entryhi
comma
r_int
r_int
id|pagemask
)paren
suffix:semicolon
multiline_comment|/*&n; * - add_temporary_entry() add a temporary TLB entry. We use TLB entries&n; *&t;starting at the top and working down. This is for populating the&n; *&t;TLB before trap_init() puts the TLB miss handler in place. It &n; *&t;should be used only for entries matching the actual page tables,&n; *&t;to prevent inconsistencies.&n; */
r_extern
r_int
id|add_temporary_entry
c_func
(paren
r_int
r_int
id|entrylo0
comma
r_int
r_int
id|entrylo1
comma
r_int
r_int
id|entryhi
comma
r_int
r_int
id|pagemask
)paren
suffix:semicolon
multiline_comment|/* Basically we have the same two-level (which is the logical three level&n; * Linux page table layout folded) page tables as the i386.  Some day&n; * when we have proper page coloring support we can have a 1% quicker&n; * tlb refill handling mechanism, but for now it is a bit slower but&n; * works even with the cache aliasing problem the R4k and above have.&n; */
macro_line|#endif /* !defined (_LANGUAGE_ASSEMBLY) */
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;22
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;22
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/* Entries per page directory level: we use two-level, so&n; * we don&squot;t really have any PMD directory physically.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;1024
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;1024
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE/PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START     KSEG2
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END       KSEG3
multiline_comment|/* Note that we shift the lower 32bits of each EntryLo[01] entry&n; * 6 bits to the left. That way we can convert the PFN into the&n; * physical address by a single &squot;and&squot; operation and gain 6 additional&n; * bits for storing information which isn&squot;t present in a normal&n; * MIPS page table.&n; *&n; * Similar to the Alpha port, we need to keep track of the ref&n; * and mod bits in software.  We have a software &quot;yeah you can read&n; * from this page&quot; bit, and a hardware one which actually lets the&n; * process read from the page.  On the same token we have a software&n; * writable bit and the real hardware one which actually lets the&n; * process write to the page, this keeps a mod bit via the hardware&n; * dirty bit.&n; *&n; * Certain revisions of the R4000 and R5000 have a bug where if a&n; * certain sequence occurs in the last 3 instructions of an executable&n; * page, and the following page is not mapped, the cpu can do&n; * unpredictable things.  The code (when it is written) to deal with&n; * this problem will be in the update_mmu_cache() code for the r4k.&n; */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT               (1&lt;&lt;0)  /* implemented in software */
DECL|macro|_PAGE_READ
mdefine_line|#define _PAGE_READ                  (1&lt;&lt;1)  /* implemented in software */
DECL|macro|_PAGE_WRITE
mdefine_line|#define _PAGE_WRITE                 (1&lt;&lt;2)  /* implemented in software */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED              (1&lt;&lt;3)  /* implemented in software */
DECL|macro|_PAGE_MODIFIED
mdefine_line|#define _PAGE_MODIFIED              (1&lt;&lt;4)  /* implemented in software */
macro_line|#if defined(CONFIG_CPU_R3000)
DECL|macro|_PAGE_GLOBAL
mdefine_line|#define _PAGE_GLOBAL                (1&lt;&lt;8)
DECL|macro|_PAGE_VALID
mdefine_line|#define _PAGE_VALID                 (1&lt;&lt;9)
DECL|macro|_PAGE_SILENT_READ
mdefine_line|#define _PAGE_SILENT_READ           (1&lt;&lt;9)  /* synonym                 */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY                 (1&lt;&lt;10) /* The MIPS dirty bit      */
DECL|macro|_PAGE_SILENT_WRITE
mdefine_line|#define _PAGE_SILENT_WRITE          (1&lt;&lt;10)
DECL|macro|_CACHE_UNCACHED
mdefine_line|#define _CACHE_UNCACHED             (1&lt;&lt;11) /* R4[0246]00              */
DECL|macro|_CACHE_MASK
mdefine_line|#define _CACHE_MASK                 (1&lt;&lt;11)
DECL|macro|_CACHE_CACHABLE_NONCOHERENT
mdefine_line|#define _CACHE_CACHABLE_NONCOHERENT 0
macro_line|#else
DECL|macro|_PAGE_R4KBUG
mdefine_line|#define _PAGE_R4KBUG                (1&lt;&lt;5)  /* workaround for r4k bug  */
DECL|macro|_PAGE_GLOBAL
mdefine_line|#define _PAGE_GLOBAL                (1&lt;&lt;6)
DECL|macro|_PAGE_VALID
mdefine_line|#define _PAGE_VALID                 (1&lt;&lt;7)
DECL|macro|_PAGE_SILENT_READ
mdefine_line|#define _PAGE_SILENT_READ           (1&lt;&lt;7)  /* synonym                 */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY                 (1&lt;&lt;8)  /* The MIPS dirty bit      */
DECL|macro|_PAGE_SILENT_WRITE
mdefine_line|#define _PAGE_SILENT_WRITE          (1&lt;&lt;8)
DECL|macro|_CACHE_MASK
mdefine_line|#define _CACHE_MASK                 (7&lt;&lt;9)
macro_line|#if defined(CONFIG_CPU_SB1)
multiline_comment|/* No penalty for being coherent on the SB1, so just&n;   use it for &quot;noncoherent&quot; spaces, too.  Shouldn&squot;t hurt. */
DECL|macro|_CACHE_UNCACHED
mdefine_line|#define _CACHE_UNCACHED             (2&lt;&lt;9)  
DECL|macro|_CACHE_CACHABLE_COW
mdefine_line|#define _CACHE_CACHABLE_COW         (5&lt;&lt;9)  
DECL|macro|_CACHE_CACHABLE_NONCOHERENT
mdefine_line|#define _CACHE_CACHABLE_NONCOHERENT (5&lt;&lt;9)  
macro_line|#else
DECL|macro|_CACHE_CACHABLE_NO_WA
mdefine_line|#define _CACHE_CACHABLE_NO_WA       (0&lt;&lt;9)  /* R4600 only              */
DECL|macro|_CACHE_CACHABLE_WA
mdefine_line|#define _CACHE_CACHABLE_WA          (1&lt;&lt;9)  /* R4600 only              */
DECL|macro|_CACHE_UNCACHED
mdefine_line|#define _CACHE_UNCACHED             (2&lt;&lt;9)  /* R4[0246]00              */
DECL|macro|_CACHE_CACHABLE_NONCOHERENT
mdefine_line|#define _CACHE_CACHABLE_NONCOHERENT (3&lt;&lt;9)  /* R4[0246]00              */
DECL|macro|_CACHE_CACHABLE_CE
mdefine_line|#define _CACHE_CACHABLE_CE          (4&lt;&lt;9)  /* R4[04]00 only           */
DECL|macro|_CACHE_CACHABLE_COW
mdefine_line|#define _CACHE_CACHABLE_COW         (5&lt;&lt;9)  /* R4[04]00 only           */
DECL|macro|_CACHE_CACHABLE_CUW
mdefine_line|#define _CACHE_CACHABLE_CUW         (6&lt;&lt;9)  /* R4[04]00 only           */
DECL|macro|_CACHE_CACHABLE_ACCELERATED
mdefine_line|#define _CACHE_CACHABLE_ACCELERATED (7&lt;&lt;9)  /* R10000 only             */
macro_line|#endif
macro_line|#endif
DECL|macro|__READABLE
mdefine_line|#define __READABLE&t;(_PAGE_READ | _PAGE_SILENT_READ | _PAGE_ACCESSED)
DECL|macro|__WRITEABLE
mdefine_line|#define __WRITEABLE&t;(_PAGE_WRITE | _PAGE_SILENT_WRITE | _PAGE_MODIFIED)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_ACCESSED | _PAGE_MODIFIED | _CACHE_MASK)
macro_line|#ifdef CONFIG_MIPS_UNCACHED
DECL|macro|PAGE_CACHABLE_DEFAULT
mdefine_line|#define PAGE_CACHABLE_DEFAULT&t;_CACHE_UNCACHED
macro_line|#else
macro_line|#ifdef CONFIG_CPU_SB1
DECL|macro|PAGE_CACHABLE_DEFAULT
mdefine_line|#define PAGE_CACHABLE_DEFAULT&t;_CACHE_CACHABLE_COW
macro_line|#else
DECL|macro|PAGE_CACHABLE_DEFAULT
mdefine_line|#define PAGE_CACHABLE_DEFAULT&t;_CACHE_CACHABLE_NONCOHERENT
macro_line|#endif
macro_line|#endif
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PRESENT | _CACHE_CACHABLE_NONCOHERENT)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_PAGE_PRESENT | _PAGE_READ | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_PAGE_PRESENT | _PAGE_READ | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_PRESENT | __READABLE | __WRITEABLE | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_USERIO
mdefine_line|#define PAGE_USERIO     __pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_WRITE | &bslash;&n;&t;&t;&t;PAGE_CACHABLE_DEFAULT)
DECL|macro|PAGE_KERNEL_UNCACHED
mdefine_line|#define PAGE_KERNEL_UNCACHED __pgprot(_PAGE_PRESENT | __READABLE | __WRITEABLE | &bslash;&n;&t;&t;&t;_CACHE_UNCACHED)
multiline_comment|/*&n; * MIPS can&squot;t do page protection for execute, and considers that the same like&n; * read. Also, write permissions imply read permissions. This is the closest&n; * we can get by reasonable means..&n; */
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
macro_line|#if !defined (_LANGUAGE_ASSEMBLY)
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %016lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
r_extern
r_int
r_int
id|empty_zero_page
suffix:semicolon
r_extern
r_int
r_int
id|zero_page_mask
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) &bslash;&n;&t;(virt_to_page(empty_zero_page + (((unsigned long)(vaddr)) &amp; zero_page_mask)))
multiline_comment|/* number of bits that fit into a memory pointer */
DECL|macro|BITS_PER_PTR
mdefine_line|#define BITS_PER_PTR&t;&t;&t;(8*sizeof(unsigned long))
multiline_comment|/* to align the pointer to a pointer address */
DECL|macro|PTR_MASK
mdefine_line|#define PTR_MASK&t;&t;&t;(~(sizeof(void*)-1))
multiline_comment|/*&n; * sizeof(void*) == (1 &lt;&lt; SIZEOF_PTR_LOG2)&n; */
DECL|macro|SIZEOF_PTR_LOG2
mdefine_line|#define SIZEOF_PTR_LOG2&t;&t;&t;2
multiline_comment|/* to find an entry in a page-table */
DECL|macro|PAGE_PTR
mdefine_line|#define PAGE_PTR(address) &bslash;&n;((unsigned long)(address)&gt;&gt;(PAGE_SHIFT-SIZEOF_PTR_LOG2)&amp;PTR_MASK&amp;~PAGE_MASK)
r_extern
r_void
id|load_pgd
c_func
(paren
r_int
r_int
id|pg_dir
)paren
suffix:semicolon
r_extern
id|pmd_t
id|invalid_pte_table
(braket
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pmd_t
)paren
)braket
suffix:semicolon
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|function|pmd_page
r_extern
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
suffix:semicolon
)brace
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
(paren
(paren
(paren
r_int
r_int
)paren
id|ptep
)paren
op_amp
id|PAGE_MASK
)paren
suffix:semicolon
)brace
DECL|function|pte_none
r_extern
r_inline
r_int
id|pte_none
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
op_logical_neg
id|pte_val
c_func
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
id|_PAGE_PRESENT
suffix:semicolon
)brace
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
DECL|function|set_pte
r_extern
r_inline
r_void
id|set_pte
c_func
(paren
id|pte_t
op_star
id|ptep
comma
id|pte_t
id|pteval
)paren
(brace
op_star
id|ptep
op_assign
id|pteval
suffix:semicolon
)brace
DECL|function|pte_clear
r_extern
r_inline
r_void
id|pte_clear
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
id|set_pte
c_func
(paren
id|ptep
comma
id|__pte
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * (pmds are folded into pgds so this doesnt get actually called,&n; * but the define is needed for a generic inline function.)&n; */
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdptr, pmdval) (*(pmdptr) = pmdval)
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgdptr, pgdval) (*(pgdptr) = pgdval)
multiline_comment|/*&n; * Empty pgd/pmd entries point to the invalid_pte_table.&n; */
DECL|function|pmd_none
r_extern
r_inline
r_int
id|pmd_none
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
op_eq
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
)brace
DECL|function|pmd_bad
r_extern
r_inline
r_int
id|pmd_bad
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
(paren
(paren
id|pmd_page
c_func
(paren
id|pmd
)paren
OG
(paren
r_int
r_int
)paren
id|high_memory
)paren
op_logical_or
(paren
id|pmd_page
c_func
(paren
id|pmd
)paren
OL
id|PAGE_OFFSET
)paren
)paren
suffix:semicolon
)brace
DECL|function|pmd_present
r_extern
r_inline
r_int
id|pmd_present
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
(paren
id|pmd_val
c_func
(paren
id|pmd
)paren
op_ne
(paren
r_int
r_int
)paren
id|invalid_pte_table
)paren
suffix:semicolon
)brace
DECL|function|pmd_clear
r_extern
r_inline
r_void
id|pmd_clear
c_func
(paren
id|pmd_t
op_star
id|pmdp
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|pmdp
)paren
op_assign
(paren
(paren
r_int
r_int
)paren
id|invalid_pte_table
)paren
suffix:semicolon
)brace
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
macro_line|#ifdef CONFIG_CPU_VR41XX
DECL|macro|pte_page
mdefine_line|#define pte_page(x)             (mem_map+(unsigned long)((pte_val(x) &gt;&gt; (PAGE_SHIFT + 2))))
macro_line|#else
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;(mem_map+(unsigned long)((pte_val(x) &gt;&gt; PAGE_SHIFT)))
macro_line|#endif
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
multiline_comment|/*&n; * Macro to make mark a page protection value as &quot;uncacheable&quot;.  Note&n; * that &quot;protection&quot; is really a misnomer here as the protection value&n; * contains the memory attribute bits, dirty bits, and various other&n; * bits as well.&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached pgprot_noncached
DECL|function|pgprot_noncached
r_static
r_inline
id|pgprot_t
id|pgprot_noncached
c_func
(paren
id|pgprot_t
id|_prot
)paren
(brace
r_int
r_int
id|prot
op_assign
id|pgprot_val
c_func
(paren
id|_prot
)paren
suffix:semicolon
id|prot
op_assign
(paren
id|prot
op_amp
op_complement
id|_CACHE_MASK
)paren
op_or
id|_CACHE_UNCACHED
suffix:semicolon
r_return
id|__pgprot
c_func
(paren
id|prot
)paren
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
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
macro_line|#ifdef CONFIG_CPU_VR41XX
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)                                            &bslash;&n;({                                                                      &bslash;&n;        pte_t   __pte;                                                  &bslash;&n;                                                                        &bslash;&n;        pte_val(__pte) = ((unsigned long)(page - mem_map) &lt;&lt; (PAGE_SHIFT + 2)) | &bslash;&n;                         pgprot_val(pgprot);                            &bslash;&n;                                                                        &bslash;&n;        __pte;                                                          &bslash;&n;})
macro_line|#else
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t   __pte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_val(__pte) = ((unsigned long)(page - mem_map) &lt;&lt; PAGE_SHIFT) | &bslash;&n;&t;                 pgprot_val(pgprot);&t;&t;&t;&t;&bslash;&n;&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
DECL|function|mk_pte_phys
r_extern
r_inline
id|pte_t
id|mk_pte_phys
c_func
(paren
r_int
r_int
id|physpage
comma
id|pgprot_t
id|pgprot
)paren
(brace
macro_line|#ifdef CONFIG_CPU_VR41XX
r_return
id|__pte
c_func
(paren
(paren
id|physpage
op_lshift
l_int|2
)paren
op_or
id|pgprot_val
c_func
(paren
id|pgprot
)paren
)paren
suffix:semicolon
macro_line|#else
r_return
id|__pte
c_func
(paren
id|physpage
op_or
id|pgprot_val
c_func
(paren
id|pgprot
)paren
)paren
suffix:semicolon
macro_line|#endif
)brace
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
r_return
id|__pte
c_func
(paren
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
)paren
suffix:semicolon
)brace
DECL|macro|page_pte
mdefine_line|#define page_pte(page) page_pte_prot(page, __pgprot(0))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address)&t;((address) &gt;&gt; PGDIR_SHIFT)
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
DECL|function|pte_offset
r_extern
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
(paren
id|pmd_page
c_func
(paren
op_star
id|dir
)paren
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
r_extern
r_int
id|do_check_pgt_cache
c_func
(paren
r_int
comma
r_int
)paren
suffix:semicolon
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
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
suffix:semicolon
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;(((x).val &gt;&gt; 1) &amp; 0x3f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;((x).val &gt;&gt; 8)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type,offset) ((swp_entry_t) { ((type) &lt;&lt; 1) | ((offset) &lt;&lt; 8) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val })
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
multiline_comment|/* TLB operations. */
DECL|function|tlb_probe
r_extern
r_inline
r_void
id|tlb_probe
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;tlbp&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
)paren
suffix:semicolon
)brace
DECL|function|tlb_read
r_extern
r_inline
r_void
id|tlb_read
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;tlbr&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
)paren
suffix:semicolon
)brace
DECL|function|tlb_write_indexed
r_extern
r_inline
r_void
id|tlb_write_indexed
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;tlbwi&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
)paren
suffix:semicolon
)brace
DECL|function|tlb_write_random
r_extern
r_inline
r_void
id|tlb_write_random
c_func
(paren
r_void
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;tlbwr&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/* Dealing with various CP0 mmu/cache related registers. */
multiline_comment|/* CP0_PAGEMASK register */
DECL|function|get_pagemask
r_extern
r_inline
r_int
r_int
id|get_pagemask
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0 %0, $5&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|set_pagemask
r_extern
r_inline
r_void
id|set_pagemask
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0 %z0, $5&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* CP0_ENTRYLO0 and CP0_ENTRYLO1 registers */
DECL|function|get_entrylo0
r_extern
r_inline
r_int
r_int
id|get_entrylo0
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0 %0, $2&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|set_entrylo0
r_extern
r_inline
r_void
id|set_entrylo0
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0 %z0, $2&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_entrylo1
r_extern
r_inline
r_int
r_int
id|get_entrylo1
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0 %0, $3&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|set_entrylo1
r_extern
r_inline
r_void
id|set_entrylo1
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0 %z0, $3&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* CP0_ENTRYHI register */
DECL|function|get_entryhi
r_extern
r_inline
r_int
r_int
id|get_entryhi
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0 %0, $10&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|set_entryhi
r_extern
r_inline
r_void
id|set_entryhi
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0 %z0, $10&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* CP0_INDEX register */
DECL|function|get_index
r_extern
r_inline
r_int
r_int
id|get_index
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0 %0, $0&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|set_index
r_extern
r_inline
r_void
id|set_index
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0 %z0, $0&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* CP0_WIRED register */
DECL|function|get_wired
r_extern
r_inline
r_int
r_int
id|get_wired
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0 %0, $6&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|set_wired
r_extern
r_inline
r_void
id|set_wired
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0 %z0, $6&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_info
r_extern
r_inline
r_int
r_int
id|get_info
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__asm__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0 %0, $7&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
multiline_comment|/* CP0_TAGLO and CP0_TAGHI registers */
DECL|function|get_taglo
r_extern
r_inline
r_int
r_int
id|get_taglo
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0 %0, $28&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|set_taglo
r_extern
r_inline
r_void
id|set_taglo
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0 %z0, $28&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
DECL|function|get_taghi
r_extern
r_inline
r_int
r_int
id|get_taghi
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0 %0, $29&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|set_taghi
r_extern
r_inline
r_void
id|set_taghi
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0 %z0, $29&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* CP0_CONTEXT register */
DECL|function|get_context
r_extern
r_inline
r_int
r_int
id|get_context
c_func
(paren
r_void
)paren
(brace
r_int
r_int
id|val
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mfc0 %0, $4&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
l_string|&quot;=r&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
r_return
id|val
suffix:semicolon
)brace
DECL|function|set_context
r_extern
r_inline
r_void
id|set_context
c_func
(paren
r_int
r_int
id|val
)paren
(brace
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;.set push&bslash;n&bslash;t&quot;
l_string|&quot;.set reorder&bslash;n&bslash;t&quot;
l_string|&quot;mtc0 %z0, $4&bslash;n&bslash;t&quot;
l_string|&quot;.set pop&quot;
suffix:colon
suffix:colon
l_string|&quot;Jr&quot;
(paren
id|val
)paren
)paren
suffix:semicolon
)brace
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#endif /* !defined (_LANGUAGE_ASSEMBLY) */
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range remap_page_range
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
macro_line|#endif /* _ASM_PGTABLE_H */
eof
