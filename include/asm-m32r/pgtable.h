macro_line|#ifndef _ASM_M32R_PGTABLE_H
DECL|macro|_ASM_M32R_PGTABLE_H
mdefine_line|#define _ASM_M32R_PGTABLE_H
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
macro_line|#ifdef __KERNEL__
multiline_comment|/*&n; * The Linux memory management assumes a three-level page table setup. On&n; * the M32R, we use that, but &quot;fold&quot; the mid level into the top-level page&n; * table, so that we physically have the same two-level page table as the&n; * M32R mmu expects.&n; *&n; * This file contains the functions and defines necessary to modify and use&n; * the M32R page table tree.&n; */
multiline_comment|/* CAUTION!: If you change macro definitions in this file, you might have to&n; * change arch/m32r/mmu.S manually.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/page.h&gt;
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
mdefine_line|#define ZERO_PAGE(vaddr)&t;(virt_to_page(empty_zero_page))
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/pgtable-2level.h&gt;
macro_line|#endif
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE - 1))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE - 1))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE / PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;KSEG2
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;&t;KSEG3
multiline_comment|/*&n; *     M32R TLB format&n; *&n; *     [0]    [1:19]           [20:23]       [24:31]&n; *     +-----------------------+----+-------------+&n; *     |          VPN          |0000|    ASID     |&n; *     +-----------------------+----+-------------+&n; *     +-+---------------------+----+-+---+-+-+-+-+&n; *     |0         PPN          |0000|N|AC |L|G|V| |&n; *     +-+---------------------+----+-+---+-+-+-+-+&n; *                                     RWX&n; */
DECL|macro|_PAGE_BIT_DIRTY
mdefine_line|#define _PAGE_BIT_DIRTY&t;&t;0&t;/* software: page changed */
DECL|macro|_PAGE_BIT_FILE
mdefine_line|#define _PAGE_BIT_FILE&t;&t;0&t;/* when !present: nonlinear file&n;&t;&t;&t;&t;&t;   mapping */
DECL|macro|_PAGE_BIT_PRESENT
mdefine_line|#define _PAGE_BIT_PRESENT&t;1&t;/* Valid: page is valid */
DECL|macro|_PAGE_BIT_GLOBAL
mdefine_line|#define _PAGE_BIT_GLOBAL&t;2&t;/* Global */
DECL|macro|_PAGE_BIT_LARGE
mdefine_line|#define _PAGE_BIT_LARGE&t;&t;3&t;/* Large */
DECL|macro|_PAGE_BIT_EXEC
mdefine_line|#define _PAGE_BIT_EXEC&t;&t;4&t;/* Execute */
DECL|macro|_PAGE_BIT_WRITE
mdefine_line|#define _PAGE_BIT_WRITE&t;&t;5&t;/* Write */
DECL|macro|_PAGE_BIT_READ
mdefine_line|#define _PAGE_BIT_READ&t;&t;6&t;/* Read */
DECL|macro|_PAGE_BIT_NONCACHABLE
mdefine_line|#define _PAGE_BIT_NONCACHABLE&t;7&t;/* Non cachable */
DECL|macro|_PAGE_BIT_USER
mdefine_line|#define _PAGE_BIT_USER&t;&t;8&t;/* software: user space access&n;&t;&t;&t;&t;&t;   allowed */
DECL|macro|_PAGE_BIT_ACCESSED
mdefine_line|#define _PAGE_BIT_ACCESSED&t;9&t;/* software: page referenced */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;&t;(1UL &lt;&lt; _PAGE_BIT_DIRTY)
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;&t;(1UL &lt;&lt; _PAGE_BIT_FILE)
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;&t;(1UL &lt;&lt; _PAGE_BIT_PRESENT)
DECL|macro|_PAGE_GLOBAL
mdefine_line|#define _PAGE_GLOBAL&t;&t;(1UL &lt;&lt; _PAGE_BIT_GLOBAL)
DECL|macro|_PAGE_LARGE
mdefine_line|#define _PAGE_LARGE&t;&t;(1UL &lt;&lt; _PAGE_BIT_LARGE)
DECL|macro|_PAGE_EXEC
mdefine_line|#define _PAGE_EXEC&t;&t;(1UL &lt;&lt; _PAGE_BIT_EXEC)
DECL|macro|_PAGE_WRITE
mdefine_line|#define _PAGE_WRITE&t;&t;(1UL &lt;&lt; _PAGE_BIT_WRITE)
DECL|macro|_PAGE_READ
mdefine_line|#define _PAGE_READ&t;&t;(1UL &lt;&lt; _PAGE_BIT_READ)
DECL|macro|_PAGE_NONCACHABLE
mdefine_line|#define _PAGE_NONCACHABLE&t;(1UL &lt;&lt; _PAGE_BIT_NONCACHABLE)
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;&t;(1UL &lt;&lt; _PAGE_BIT_USER)
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;&t;(1UL &lt;&lt; _PAGE_BIT_ACCESSED)
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;&bslash;&n;&t;( _PAGE_PRESENT | _PAGE_WRITE | _PAGE_READ | _PAGE_USER &bslash;&n;&t;| _PAGE_ACCESSED | _PAGE_DIRTY )
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE&t;&bslash;&n;&t;( _PAGE_PRESENT | _PAGE_WRITE | _PAGE_READ | _PAGE_ACCESSED &bslash;&n;&t;| _PAGE_DIRTY )
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;&bslash;&n;&t;( PTE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY )
macro_line|#ifdef CONFIG_MMU
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;&bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;&bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_WRITE | _PAGE_READ | _PAGE_USER &bslash;&n;&t;&t;| _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED_EXEC
mdefine_line|#define PAGE_SHARED_EXEC &bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_EXEC | _PAGE_WRITE | _PAGE_READ &bslash;&n;&t;&t;| _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;&bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY_EXEC
mdefine_line|#define PAGE_COPY_EXEC&t;&bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_EXEC | _PAGE_READ | _PAGE_USER &bslash;&n;&t;&t;| _PAGE_ACCESSED)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;&bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_READ | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_READONLY_EXEC
mdefine_line|#define PAGE_READONLY_EXEC &bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_EXEC | _PAGE_READ | _PAGE_USER &bslash;&n;&t;&t;| _PAGE_ACCESSED)
DECL|macro|__PAGE_KERNEL
mdefine_line|#define __PAGE_KERNEL&t;&bslash;&n;&t;( _PAGE_PRESENT | _PAGE_EXEC | _PAGE_WRITE | _PAGE_READ | _PAGE_DIRTY &bslash;&n;&t;| _PAGE_ACCESSED )
DECL|macro|__PAGE_KERNEL_RO
mdefine_line|#define __PAGE_KERNEL_RO&t;( __PAGE_KERNEL &amp; ~_PAGE_WRITE )
DECL|macro|__PAGE_KERNEL_NOCACHE
mdefine_line|#define __PAGE_KERNEL_NOCACHE&t;( __PAGE_KERNEL | _PAGE_NONCACHABLE)
DECL|macro|MAKE_GLOBAL
mdefine_line|#define MAKE_GLOBAL(x)&t;__pgprot((x) | _PAGE_GLOBAL)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;&t;MAKE_GLOBAL(__PAGE_KERNEL)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO&t;&t;MAKE_GLOBAL(__PAGE_KERNEL_RO)
DECL|macro|PAGE_KERNEL_NOCACHE
mdefine_line|#define PAGE_KERNEL_NOCACHE&t;MAKE_GLOBAL(__PAGE_KERNEL_NOCACHE)
macro_line|#else
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;&t;__pgprot(0)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;&t;__pgprot(0)
DECL|macro|PAGE_SHARED_EXEC
mdefine_line|#define PAGE_SHARED_EXEC&t;__pgprot(0)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;&t;__pgprot(0)
DECL|macro|PAGE_COPY_EXEC
mdefine_line|#define PAGE_COPY_EXEC&t;&t;__pgprot(0)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;&t;__pgprot(0)
DECL|macro|PAGE_READONLY_EXEC
mdefine_line|#define PAGE_READONLY_EXEC&t;__pgprot(0)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;&t;__pgprot(0)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO&t;&t;__pgprot(0)
DECL|macro|PAGE_KERNEL_NOCACHE
mdefine_line|#define PAGE_KERNEL_NOCACHE&t;__pgprot(0)
macro_line|#endif /* CONFIG_MMU */
multiline_comment|/* xwr */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100&t;PAGE_READONLY_EXEC
DECL|macro|__P101
mdefine_line|#define __P101&t;PAGE_READONLY_EXEC
DECL|macro|__P110
mdefine_line|#define __P110&t;PAGE_COPY_EXEC
DECL|macro|__P111
mdefine_line|#define __P111&t;PAGE_COPY_EXEC
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100&t;PAGE_READONLY_EXEC
DECL|macro|__S101
mdefine_line|#define __S101&t;PAGE_READONLY_EXEC
DECL|macro|__S110
mdefine_line|#define __S110&t;PAGE_SHARED_EXEC
DECL|macro|__S111
mdefine_line|#define __S111&t;PAGE_SHARED_EXEC
multiline_comment|/* page table for 0-4MB for everybody */
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;(pte_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pte_clear
mdefine_line|#define pte_clear(xp)&t;do { set_pte(xp, __pte(0)); } while (0)
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!pmd_val(x))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(x)&t;(pmd_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(xp)&t;do { set_pmd(xp, __pmd(0)); } while (0)
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(x)&t;((pmd_val(x) &amp; (~PAGE_MASK &amp; ~_PAGE_USER)) &bslash;&n;&t;!= _KERNPG_TABLE)
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x)&t;((x) &gt;&gt; (20 - PAGE_SHIFT))
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_USER
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_READ
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
id|_PAGE_EXEC
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
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
id|_PAGE_FILE
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
id|_PAGE_READ
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
id|_PAGE_EXEC
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
id|_PAGE_WRITE
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
id|_PAGE_EXEC
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
id|_PAGE_WRITE
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
id|ptep
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
id|ptep
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
id|_PAGE_BIT_WRITE
comma
id|ptep
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
id|ptep
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Macro and implementation to make a page protection as uncachable.&n; */
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
op_or_assign
id|_PAGE_NONCACHABLE
suffix:semicolon
r_return
id|__pgprot
c_func
(paren
id|prot
)paren
suffix:semicolon
)brace
DECL|macro|pgprot_writecombine
mdefine_line|#define pgprot_writecombine(prot) pgprot_noncached(prot)
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;pfn_pte(page_to_pfn(page), pgprot)
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
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
"&bslash;"
op_or
id|pgprot_val
c_func
(paren
id|newprot
)paren
)paren
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;page_pte_prot(page, __pgprot(0))
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
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
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd)&t;&bslash;&n;&t;((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;(mem_map + ((pmd_val(pmd) &gt;&gt; PAGE_SHIFT) - PFN_BASE))
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
multiline_comment|/* to find an entry in a page-table-directory. */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address)&t;&bslash;&n;&t;(((address) &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD - 1))
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address)&t;((mm)-&gt;pgd + pgd_index(address))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address)&t;pgd_offset(&amp;init_mm, address)
DECL|macro|pmd_index
mdefine_line|#define pmd_index(address)&t;&bslash;&n;&t;(((address) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD - 1))
DECL|macro|pte_index
mdefine_line|#define pte_index(address)&t;&bslash;&n;&t;(((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address)&t;&bslash;&n;&t;((pte_t *)pmd_page_kernel(*(dir)) + pte_index(address))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address)&t;&bslash;&n;&t;((pte_t *)page_address(pmd_page(*(dir))) + pte_index(address))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address)&t;pte_offset_map(dir, address)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte)&t;&t;do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte)&t;do { } while (0)
multiline_comment|/* Encode and de-code a swap entry */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;&t;(((x).val &gt;&gt; 1) &amp; 0x3f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;&t;((x).val &gt;&gt; 8)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset)&t;&bslash;&n;&t;((swp_entry_t) { ((type) &lt;&lt; 1) | ((offset) &lt;&lt; 8) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
macro_line|#endif /* !__ASSEMBLY__ */
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma, vaddr, paddr, size, prot)&t;&bslash;&n;&t;remap_pfn_range(vma, vaddr, (paddr) &gt;&gt; PAGE_SHIFT, size, prot)
DECL|macro|__HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
mdefine_line|#define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
DECL|macro|__HAVE_ARCH_PTEP_TEST_AND_CLEAR_DIRTY
mdefine_line|#define __HAVE_ARCH_PTEP_TEST_AND_CLEAR_DIRTY
DECL|macro|__HAVE_ARCH_PTEP_GET_AND_CLEAR
mdefine_line|#define __HAVE_ARCH_PTEP_GET_AND_CLEAR
DECL|macro|__HAVE_ARCH_PTEP_SET_WRPROTECT
mdefine_line|#define __HAVE_ARCH_PTEP_SET_WRPROTECT
DECL|macro|__HAVE_ARCH_PTEP_MKDIRTY
mdefine_line|#define __HAVE_ARCH_PTEP_MKDIRTY
DECL|macro|__HAVE_ARCH_PTE_SAME
mdefine_line|#define __HAVE_ARCH_PTE_SAME
macro_line|#include &lt;asm-generic/pgtable.h&gt;
macro_line|#endif /* __KERNEL__ */
macro_line|#endif /* _ASM_M32R_PGTABLE_H */
eof
