macro_line|#ifndef _I386_PGTABLE_H
DECL|macro|_I386_PGTABLE_H
mdefine_line|#define _I386_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n; * The Linux memory management assumes a three-level page table setup. On&n; * the i386, we use that, but &quot;fold&quot; the mid level into the top-level page&n; * table, so that we physically have the same two-level page table as the&n; * i386 mmu expects.&n; *&n; * This file contains the functions and defines necessary to modify and use&n; * the i386 page table tree.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#ifndef _I386_BITOPS_H
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#endif
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
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/*&n; * The Linux x86 paging architecture is &squot;compile-time dual-mode&squot;, it&n; * implements both the traditional 2-level x86 page tables and the&n; * newer 3-level PAE-mode page tables.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#if CONFIG_X86_PAE
macro_line|# include &lt;asm/pgtable-3level.h&gt;
multiline_comment|/*&n; * Need to initialise the X86 PAE caches&n; */
r_extern
r_void
id|pgtable_cache_init
c_func
(paren
r_void
)paren
suffix:semicolon
macro_line|#else
macro_line|# include &lt;asm/pgtable-2level.h&gt;
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
macro_line|#endif
macro_line|#endif
DECL|macro|__beep
mdefine_line|#define __beep() asm(&quot;movb $0x3,%al; outb %al,$0x61&quot;)
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE/PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|USER_PGD_PTRS
mdefine_line|#define USER_PGD_PTRS (PAGE_OFFSET &gt;&gt; PGDIR_SHIFT)
DECL|macro|KERNEL_PGD_PTRS
mdefine_line|#define KERNEL_PGD_PTRS (PTRS_PER_PGD-USER_PGD_PTRS)
DECL|macro|TWOLEVEL_PGDIR_SHIFT
mdefine_line|#define TWOLEVEL_PGDIR_SHIFT&t;22
DECL|macro|BOOT_USER_PGD_PTRS
mdefine_line|#define BOOT_USER_PGD_PTRS (__PAGE_OFFSET &gt;&gt; TWOLEVEL_PGDIR_SHIFT)
DECL|macro|BOOT_KERNEL_PGD_PTRS
mdefine_line|#define BOOT_KERNEL_PGD_PTRS (1024-BOOT_USER_PGD_PTRS)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;(8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;(((unsigned long) high_memory + 2*VMALLOC_OFFSET-1) &amp; &bslash;&n;&t;&t;&t;&t;&t;&t;~(VMALLOC_OFFSET-1))
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
macro_line|#if CONFIG_HIGHMEM
DECL|macro|VMALLOC_END
macro_line|# define VMALLOC_END&t;(PKMAP_BASE-2*PAGE_SIZE)
macro_line|#else
DECL|macro|VMALLOC_END
macro_line|# define VMALLOC_END&t;(FIXADDR_START-2*PAGE_SIZE)
macro_line|#endif
multiline_comment|/*&n; * The 4MB page is guessing..  Detailed in the infamous &quot;Chapter H&quot;&n; * of the Pentium details, but assuming intel did the straightforward&n; * thing, this bit set in the page directory entry just means that&n; * the page directory entry points directly to a 4MB-aligned block of&n; * memory. &n; */
DECL|macro|_PAGE_BIT_PRESENT
mdefine_line|#define _PAGE_BIT_PRESENT&t;0
DECL|macro|_PAGE_BIT_RW
mdefine_line|#define _PAGE_BIT_RW&t;&t;1
DECL|macro|_PAGE_BIT_USER
mdefine_line|#define _PAGE_BIT_USER&t;&t;2
DECL|macro|_PAGE_BIT_PWT
mdefine_line|#define _PAGE_BIT_PWT&t;&t;3
DECL|macro|_PAGE_BIT_PCD
mdefine_line|#define _PAGE_BIT_PCD&t;&t;4
DECL|macro|_PAGE_BIT_ACCESSED
mdefine_line|#define _PAGE_BIT_ACCESSED&t;5
DECL|macro|_PAGE_BIT_DIRTY
mdefine_line|#define _PAGE_BIT_DIRTY&t;&t;6
DECL|macro|_PAGE_BIT_PSE
mdefine_line|#define _PAGE_BIT_PSE&t;&t;7&t;/* 4 MB (or 2MB) page, Pentium+, if present.. */
DECL|macro|_PAGE_BIT_GLOBAL
mdefine_line|#define _PAGE_BIT_GLOBAL&t;8&t;/* Global TLB entry PPro+ */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x001
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW&t;0x002
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x004
DECL|macro|_PAGE_PWT
mdefine_line|#define _PAGE_PWT&t;0x008
DECL|macro|_PAGE_PCD
mdefine_line|#define _PAGE_PCD&t;0x010
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x020
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x040
DECL|macro|_PAGE_PSE
mdefine_line|#define _PAGE_PSE&t;0x080&t;/* 4 MB (or 2MB) page, Pentium+, if present.. */
DECL|macro|_PAGE_GLOBAL
mdefine_line|#define _PAGE_GLOBAL&t;0x100&t;/* Global TLB entry PPro+ */
DECL|macro|_PAGE_PROTNONE
mdefine_line|#define _PAGE_PROTNONE&t;0x080&t;/* If not present */
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PTE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PROTNONE | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|_PAGE_KERNEL
mdefine_line|#define _PAGE_KERNEL &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_ACCESSED)
r_extern
r_int
r_int
id|__PAGE_KERNEL
suffix:semicolon
DECL|macro|__PAGE_KERNEL_RO
mdefine_line|#define __PAGE_KERNEL_RO&t;(__PAGE_KERNEL &amp; ~_PAGE_RW)
DECL|macro|__PAGE_KERNEL_NOCACHE
mdefine_line|#define __PAGE_KERNEL_NOCACHE&t;(__PAGE_KERNEL | _PAGE_PCD)
DECL|macro|__PAGE_KERNEL_LARGE
mdefine_line|#define __PAGE_KERNEL_LARGE&t;(__PAGE_KERNEL | _PAGE_PSE)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;&t;__pgprot(__PAGE_KERNEL)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO&t;&t;__pgprot(__PAGE_KERNEL_RO)
DECL|macro|PAGE_KERNEL_NOCACHE
mdefine_line|#define PAGE_KERNEL_NOCACHE&t;__pgprot(__PAGE_KERNEL_NOCACHE)
DECL|macro|PAGE_KERNEL_LARGE
mdefine_line|#define PAGE_KERNEL_LARGE&t;__pgprot(__PAGE_KERNEL_LARGE)
multiline_comment|/*&n; * The i386 can&squot;t do page protection for execute, and considers that&n; * the same are read. Also, write permissions imply read permissions.&n; * This is the closest we can get..&n; */
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
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;((x).pte_low &amp; (_PAGE_PRESENT | _PAGE_PROTNONE))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(xp)&t;do { set_pte(xp, __pte(0)); } while (0)
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!pmd_val(x))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(x)&t;(pmd_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(xp)&t;do { set_pmd(xp, __pmd(0)); } while (0)
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(x)&t;((pmd_val(x) &amp; (~PAGE_MASK &amp; ~_PAGE_USER)) != _KERNPG_TABLE)
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x) ((x) &gt;&gt; (20-PAGE_SHIFT))
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
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_USER
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
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_USER
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
(paren
id|pte
)paren
dot
id|pte_low
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
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_ACCESSED
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
(paren
id|pte
)paren
dot
id|pte_low
op_amp
id|_PAGE_RW
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
(paren
id|pte
)paren
dot
id|pte_low
op_and_assign
op_complement
id|_PAGE_USER
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
(paren
id|pte
)paren
dot
id|pte_low
op_and_assign
op_complement
id|_PAGE_USER
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
(paren
id|pte
)paren
dot
id|pte_low
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
(paren
id|pte
)paren
dot
id|pte_low
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
(paren
id|pte
)paren
dot
id|pte_low
op_and_assign
op_complement
id|_PAGE_RW
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
(paren
id|pte
)paren
dot
id|pte_low
op_or_assign
id|_PAGE_USER
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
(paren
id|pte
)paren
dot
id|pte_low
op_or_assign
id|_PAGE_USER
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
(paren
id|pte
)paren
dot
id|pte_low
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
(paren
id|pte
)paren
dot
id|pte_low
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
(paren
id|pte
)paren
dot
id|pte_low
op_or_assign
id|_PAGE_RW
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|function|ptep_test_and_clear_dirty
r_static
r_inline
r_int
id|ptep_test_and_clear_dirty
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_return
id|test_and_clear_bit
c_func
(paren
id|_PAGE_BIT_DIRTY
comma
op_amp
id|ptep-&gt;pte_low
)paren
suffix:semicolon
)brace
DECL|function|ptep_test_and_clear_young
r_static
r_inline
r_int
id|ptep_test_and_clear_young
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_return
id|test_and_clear_bit
c_func
(paren
id|_PAGE_BIT_ACCESSED
comma
op_amp
id|ptep-&gt;pte_low
)paren
suffix:semicolon
)brace
DECL|function|ptep_set_wrprotect
r_static
r_inline
r_void
id|ptep_set_wrprotect
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
id|clear_bit
c_func
(paren
id|_PAGE_BIT_RW
comma
op_amp
id|ptep-&gt;pte_low
)paren
suffix:semicolon
)brace
DECL|function|ptep_mkdirty
r_static
r_inline
r_void
id|ptep_mkdirty
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
id|set_bit
c_func
(paren
id|_PAGE_BIT_DIRTY
comma
op_amp
id|ptep-&gt;pte_low
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;pfn_pte(page_to_pfn(page), (pgprot))
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
id|pte.pte_low
op_and_assign
id|_PAGE_CHG_MASK
suffix:semicolon
id|pte.pte_low
op_or_assign
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
DECL|macro|page_pte
mdefine_line|#define page_pte(page) page_pte_prot(page, __pgprot(0))
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd) &bslash;&n;((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd) &bslash;&n;&t;(mem_map + (pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
multiline_comment|/* to find an entry in a page-table-directory. */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) ((address &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD-1))
DECL|macro|__pgd_offset
mdefine_line|#define __pgd_offset(address) pgd_index(address)
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) ((mm)-&gt;pgd+pgd_index(address))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
DECL|macro|__pmd_offset
mdefine_line|#define __pmd_offset(address) &bslash;&n;&t;&t;(((address) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD-1))
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|__pte_offset
mdefine_line|#define __pte_offset(address) &bslash;&n;&t;&t;((address &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address) &bslash;&n;&t;((pte_t *) pmd_page_kernel(*(dir)) +  __pte_offset(address))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address) &bslash;&n;&t;((pte_t *)kmap_atomic(pmd_page(*(dir)),KM_PTE0) + __pte_offset(address))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address) &bslash;&n;&t;((pte_t *)kmap_atomic(pmd_page(*(dir)),KM_PTE1) + __pte_offset(address))
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) kunmap_atomic(pte, KM_PTE0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) kunmap_atomic(pte, KM_PTE1)
multiline_comment|/*&n; * The i386 doesn&squot;t have any external MMU info: the kernel page&n; * tables contain all the necessary information.&n; */
DECL|macro|update_mmu_cache
mdefine_line|#define update_mmu_cache(vma,address,pte) do { } while (0)
multiline_comment|/* Encode and de-code a swap entry */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;&t;(((x).val &gt;&gt; 1) &amp; 0x3f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;&t;((x).val &gt;&gt; 8)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset)&t;((swp_entry_t) { ((type) &lt;&lt; 1) | ((offset) &lt;&lt; 8) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { (pte).pte_low })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range remap_page_range
macro_line|#endif /* _I386_PGTABLE_H */
eof
