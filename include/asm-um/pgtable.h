multiline_comment|/* &n; * Copyright (C) 2000, 2001, 2002 Jeff Dike (jdike@karaya.com)&n; * Derived from include/asm-i386/pgtable.h&n; * Licensed under the GPL&n; */
macro_line|#ifndef __UM_PGTABLE_H
DECL|macro|__UM_PGTABLE_H
mdefine_line|#define __UM_PGTABLE_H
macro_line|#include &quot;linux/sched.h&quot;
macro_line|#include &quot;asm/processor.h&quot;
macro_line|#include &quot;asm/page.h&quot;
macro_line|#include &quot;asm/fixmap.h&quot;
r_extern
r_void
op_star
id|um_virt_to_phys
c_func
(paren
r_struct
id|task_struct
op_star
id|task
comma
r_int
r_int
id|virt
comma
id|pte_t
op_star
id|pte_out
)paren
suffix:semicolon
multiline_comment|/* zero page used for uninitialized stuff */
r_extern
r_int
r_int
op_star
id|empty_zero_page
suffix:semicolon
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init() do ; while (0)
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
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
multiline_comment|/*&n; * entries per page directory level: the i386 is two-level, so&n; * we don&squot;t really have any PMD directory physically.&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;1024
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;1
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;1024
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR       0
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;        printk(&quot;%s:%d: bad pte %08lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;        printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;        printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
multiline_comment|/*&n; * pgd entries used up by user/kernel:&n; */
DECL|macro|USER_PGD_PTRS
mdefine_line|#define USER_PGD_PTRS (TASK_SIZE &gt;&gt; PGDIR_SHIFT)
DECL|macro|KERNEL_PGD_PTRS
mdefine_line|#define KERNEL_PGD_PTRS (PTRS_PER_PGD-USER_PGD_PTRS)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
r_extern
r_int
r_int
id|end_iomem
suffix:semicolon
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;(__va_space)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;((end_iomem + VMALLOC_OFFSET) &amp; ~(VMALLOC_OFFSET-1))
macro_line|#ifdef CONFIG_HIGHMEM
DECL|macro|VMALLOC_END
macro_line|# define VMALLOC_END&t;(PKMAP_BASE-2*PAGE_SIZE)
macro_line|#else
DECL|macro|VMALLOC_END
macro_line|# define VMALLOC_END&t;(FIXADDR_START-2*PAGE_SIZE)
macro_line|#endif
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x001
DECL|macro|_PAGE_NEWPAGE
mdefine_line|#define _PAGE_NEWPAGE&t;0x002
DECL|macro|_PAGE_NEWPROT
mdefine_line|#define _PAGE_NEWPROT   0x004
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;0x008   /* set:pagecache unset:swap */
DECL|macro|_PAGE_PROTNONE
mdefine_line|#define _PAGE_PROTNONE&t;0x010&t;/* If not present */
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW&t;0x020
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x040
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x080
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x100
DECL|macro|REGION_MASK
mdefine_line|#define REGION_MASK&t;0xf0000000
DECL|macro|REGION_SHIFT
mdefine_line|#define REGION_SHIFT&t;28
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PROTNONE | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_ACCESSED)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO&t;__pgprot(_PAGE_PRESENT | _PAGE_DIRTY | _PAGE_ACCESSED)
multiline_comment|/*&n; * The i386 can&squot;t do page protection for execute, and considers that the same are read.&n; * Also, write permissions imply read permissions. This is the closest we can get..&n; */
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
multiline_comment|/*&n; * Define this if things work differently on an i386 and an i486:&n; * it will (on an i486) warn about kernel memory accesses that are&n; * done without a &squot;verify_area(VERIFY_WRITE,..)&squot;&n; */
DECL|macro|TEST_VERIFY_AREA
macro_line|#undef TEST_VERIFY_AREA
multiline_comment|/* page table for 0-4MB for everybody */
r_extern
r_int
r_int
id|pg0
(braket
l_int|1024
)braket
suffix:semicolon
multiline_comment|/*&n; * BAD_PAGETABLE is used when we need a bogus page-table, while&n; * BAD_PAGE is used for a bogus page.&n; *&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
id|pte_t
id|__bad_page
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|__bad_pagetable
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|BAD_PAGETABLE
mdefine_line|#define BAD_PAGETABLE __bad_pagetable()
DECL|macro|BAD_PAGE
mdefine_line|#define BAD_PAGE __bad_page()
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) virt_to_page(empty_zero_page)
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
DECL|macro|pte_none
mdefine_line|#define pte_none(x)&t;!(pte_val(x) &amp; ~_PAGE_NEWPAGE)
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;(pte_val(x) &amp; (_PAGE_PRESENT | _PAGE_PROTNONE))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(xp)&t;do { pte_val(*(xp)) = _PAGE_NEWPAGE; } while (0)
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!(pmd_val(x) &amp; ~_PAGE_NEWPAGE))
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(x)&t;((pmd_val(x) &amp; (~PAGE_MASK &amp; ~_PAGE_USER)) != _KERNPG_TABLE)
DECL|macro|pmd_present
mdefine_line|#define pmd_present(x)&t;(pmd_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(xp)&t;do { pmd_val(*(xp)) = _PAGE_NEWPAGE; } while (0)
DECL|macro|pmd_newpage
mdefine_line|#define pmd_newpage(x)  (pmd_val(x) &amp; _PAGE_NEWPAGE)
DECL|macro|pmd_mkuptodate
mdefine_line|#define pmd_mkuptodate(x) (pmd_val(x) &amp;= ~_PAGE_NEWPAGE)
DECL|macro|pud_newpage
mdefine_line|#define pud_newpage(x)  (pud_val(x) &amp; _PAGE_NEWPAGE)
DECL|macro|pud_mkuptodate
mdefine_line|#define pud_mkuptodate(x) (pud_val(x) &amp;= ~_PAGE_NEWPAGE)
DECL|function|__pud_alloc
r_static
r_inline
id|pud_t
op_star
id|__pud_alloc
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
id|pgd_t
op_star
id|pgd
comma
r_int
r_int
id|addr
)paren
(brace
id|BUG
c_func
(paren
)paren
suffix:semicolon
)brace
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
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x) ((x) &gt;&gt; (20-PAGE_SHIFT))
DECL|macro|pte_page
mdefine_line|#define pte_page(pte) phys_to_page(pte_val(pte))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) phys_to_page(pmd_val(pmd) &amp; PAGE_MASK)
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x) phys_to_pfn(pte_val(x))
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot) __pte(pfn_to_phys(pfn) | pgprot_val(prot))
r_extern
r_struct
id|page
op_star
id|phys_to_page
c_func
(paren
r_const
r_int
r_int
id|phys
)paren
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|__virt_to_page
c_func
(paren
r_const
r_int
r_int
id|virt
)paren
suffix:semicolon
DECL|macro|virt_to_page
mdefine_line|#define virt_to_page(addr) __virt_to_page((const unsigned long) addr)
multiline_comment|/*&n; * Bits 0 through 3 are taken&n; */
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;28
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(pte) ((pte).pte_low &gt;&gt; 4)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) &bslash;&n;&t;((pte_t) { ((off) &lt;&lt; 4) + _PAGE_FILE })
DECL|function|pte_mknewprot
r_static
r_inline
id|pte_t
id|pte_mknewprot
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
id|_PAGE_NEWPROT
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|pte_mknewpage
r_static
r_inline
id|pte_t
id|pte_mknewpage
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
id|_PAGE_NEWPAGE
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|set_pte
r_static
r_inline
r_void
id|set_pte
c_func
(paren
id|pte_t
op_star
id|pteptr
comma
id|pte_t
id|pteval
)paren
(brace
multiline_comment|/* If it&squot;s a swap entry, it needs to be marked _PAGE_NEWPAGE so&n;&t; * fix_range knows to unmap it.  _PAGE_NEWPROT is specific to&n;&t; * mapped pages.&n;&t; */
op_star
id|pteptr
op_assign
id|pte_mknewpage
c_func
(paren
id|pteval
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pte_present
c_func
(paren
op_star
id|pteptr
)paren
)paren
(brace
op_star
id|pteptr
op_assign
id|pte_mknewprot
c_func
(paren
op_star
id|pteptr
)paren
suffix:semicolon
)brace
)brace
multiline_comment|/*&n; * (pmds are folded into pgds so this doesn&squot;t get actually called,&n; * but the define is needed for a generic inline function.)&n; */
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmdptr, pmdval) (*(pmdptr) = pmdval)
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgdptr, pgdval) (*(pgdptr) = pgdval)
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|function|pte_user
r_static
r_inline
r_int
id|pte_user
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_USER
)paren
op_logical_and
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_PROTNONE
)paren
suffix:semicolon
)brace
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
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_USER
)paren
op_logical_and
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_PROTNONE
)paren
suffix:semicolon
)brace
DECL|function|pte_exec
r_static
r_inline
r_int
(def_block
id|pte_exec
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_USER
)paren
op_logical_and
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_PROTNONE
)paren
suffix:semicolon
)brace
)def_block
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
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_RW
)paren
op_logical_and
op_logical_neg
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_PROTNONE
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * The following only works if pte_present() is not true.&n; */
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
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_FILE
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
DECL|function|pte_newpage
r_static
r_inline
r_int
id|pte_newpage
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
id|_PAGE_NEWPAGE
suffix:semicolon
)brace
DECL|function|pte_newprot
r_static
r_inline
r_int
id|pte_newprot
c_func
(paren
id|pte_t
id|pte
)paren
(brace
r_return
id|pte_present
c_func
(paren
id|pte
)paren
op_logical_and
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_NEWPROT
)paren
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
id|_PAGE_USER
suffix:semicolon
r_return
id|pte_mknewprot
c_func
(paren
id|pte
)paren
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
id|_PAGE_USER
suffix:semicolon
r_return
id|pte_mknewprot
c_func
(paren
id|pte
)paren
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
id|_PAGE_RW
suffix:semicolon
r_return
id|pte_mknewprot
c_func
(paren
id|pte
)paren
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
id|_PAGE_USER
suffix:semicolon
r_return
id|pte_mknewprot
c_func
(paren
id|pte
)paren
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
id|_PAGE_USER
suffix:semicolon
r_return
id|pte_mknewprot
c_func
(paren
id|pte
)paren
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
id|_PAGE_RW
suffix:semicolon
r_return
id|pte_mknewprot
c_func
(paren
id|pte
)paren
suffix:semicolon
)brace
DECL|function|pte_mkuptodate
r_static
r_inline
id|pte_t
id|pte_mkuptodate
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
id|_PAGE_NEWPAGE
suffix:semicolon
r_if
c_cond
(paren
id|pte_present
c_func
(paren
id|pte
)paren
)paren
(brace
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
op_complement
id|_PAGE_NEWPROT
suffix:semicolon
)brace
r_return
id|pte
suffix:semicolon
)brace
r_extern
r_int
r_int
id|page_to_phys
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
suffix:semicolon
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
r_extern
id|pte_t
id|mk_pte
c_func
(paren
r_struct
id|page
op_star
id|page
comma
id|pgprot_t
id|pgprot
)paren
suffix:semicolon
DECL|macro|pte_set_val
mdefine_line|#define pte_set_val(p, phys, prot) pte_val(p) = (phys | pgprot_val(prot))
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
r_if
c_cond
(paren
id|pte_present
c_func
(paren
id|pte
)paren
)paren
(brace
id|pte
op_assign
id|pte_mknewpage
c_func
(paren
id|pte_mknewprot
c_func
(paren
id|pte
)paren
)paren
suffix:semicolon
)brace
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd) ((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
multiline_comment|/*&n; * the pgd page can be thought of an array like this: pgd_t[PTRS_PER_PGD]&n; *&n; * this macro returns the index of the entry in the pgd page which would&n; * control the given virtual address&n; */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) (((address) &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD-1))
DECL|macro|pgd_index_k
mdefine_line|#define pgd_index_k(addr) pgd_index(addr)
multiline_comment|/*&n; * pgd_offset() returns a (pgd_t *)&n; * pgd_index() is used get the offset into the pgd page&squot;s array of pgd_t&squot;s;&n; */
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) ((mm)-&gt;pgd+pgd_index(address))
multiline_comment|/*&n; * a shortcut which implies the use of the kernel&squot;s pgd, instead&n; * of a process&squot;s&n; */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/*&n; * the pmd page can be thought of an array like this: pmd_t[PTRS_PER_PMD]&n; *&n; * this macro returns the index of the entry in the pmd page which would&n; * control the given virtual address&n; */
DECL|macro|pmd_index
mdefine_line|#define pmd_index(address) &bslash;&n;&t;&t;(((address) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD-1))
multiline_comment|/*&n; * the pte page can be thought of an array like this: pte_t[PTRS_PER_PTE]&n; *&n; * this macro returns the index of the entry in the pte page which would&n; * control the given virtual address&n; */
DECL|macro|pte_index
mdefine_line|#define pte_index(address) (((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address) &bslash;&n;&t;((pte_t *) pmd_page_kernel(*(dir)) +  pte_index(address))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address) &bslash;&n;&t;((pte_t *)page_address(pmd_page(*(dir))) + pte_index(address))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address) pte_offset_map(dir, address)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) do { } while (0)
DECL|macro|update_mmu_cache
mdefine_line|#define update_mmu_cache(vma,address,pte) do ; while (0)
multiline_comment|/* Encode and de-code a swap entry */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;&t;(((x).val &gt;&gt; 4) &amp; 0x3f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;&t;((x).val &gt;&gt; 11)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset) &bslash;&n;&t;((swp_entry_t) { ((type) &lt;&lt; 4) | ((offset) &lt;&lt; 11) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte) &bslash;&n;&t;((swp_entry_t) { pte_val(pte_mkuptodate(pte)) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr) (1)
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#include &lt;asm-um/pgtable-nopud.h&gt;
macro_line|#endif
macro_line|#endif
multiline_comment|/*&n; * Overrides for Emacs so that we follow Linus&squot;s tabbing style.&n; * Emacs will notice this stuff at the end of the file and automatically&n; * adjust the settings for this buffer only.  This must remain at the end&n; * of the file.&n; * ---------------------------------------------------------------------------&n; * Local variables:&n; * c-file-style: &quot;linux&quot;&n; * End:&n; */
eof
