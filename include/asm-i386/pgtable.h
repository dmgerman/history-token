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
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;linux/list.h&gt;
macro_line|#include &lt;linux/spinlock.h&gt;
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
r_extern
r_int
r_int
id|empty_zero_page
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|pgd_cache
suffix:semicolon
r_extern
id|kmem_cache_t
op_star
id|pmd_cache
suffix:semicolon
r_extern
id|spinlock_t
id|pgd_lock
suffix:semicolon
r_extern
r_struct
id|page
op_star
id|pgd_list
suffix:semicolon
r_void
id|pmd_ctor
c_func
(paren
r_void
op_star
comma
id|kmem_cache_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|pgd_ctor
c_func
(paren
r_void
op_star
comma
id|kmem_cache_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|pgd_dtor
c_func
(paren
r_void
op_star
comma
id|kmem_cache_t
op_star
comma
r_int
r_int
)paren
suffix:semicolon
r_void
id|pgtable_cache_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
multiline_comment|/*&n; * The Linux x86 paging architecture is &squot;compile-time dual-mode&squot;, it&n; * implements both the traditional 2-level x86 page tables and the&n; * newer 3-level PAE-mode page tables.&n; */
macro_line|#ifdef CONFIG_X86_PAE
macro_line|# include &lt;asm/pgtable-3level-defs.h&gt;
DECL|macro|PMD_SIZE
macro_line|# define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
macro_line|# define PMD_MASK&t;(~(PMD_SIZE-1))
macro_line|#else
macro_line|# include &lt;asm/pgtable-2level-defs.h&gt;
macro_line|#endif
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
multiline_comment|/* Just any arbitrary offset to the start of the vmalloc VM area: the&n; * current 8MB value just means that there will be a 8MB &quot;hole&quot; after the&n; * physical memory until the kernel virtual memory starts.  That means that&n; * any out-of-bounds memory accesses will hopefully be caught.&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;)&n; */
DECL|macro|VMALLOC_OFFSET
mdefine_line|#define VMALLOC_OFFSET&t;(8*1024*1024)
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;(((unsigned long) high_memory + vmalloc_earlyreserve + &bslash;&n;&t;&t;&t;2*VMALLOC_OFFSET-1) &amp; ~(VMALLOC_OFFSET-1))
macro_line|#ifdef CONFIG_HIGHMEM
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
DECL|macro|_PAGE_BIT_UNUSED1
mdefine_line|#define _PAGE_BIT_UNUSED1&t;9&t;/* available for programmer */
DECL|macro|_PAGE_BIT_UNUSED2
mdefine_line|#define _PAGE_BIT_UNUSED2&t;10
DECL|macro|_PAGE_BIT_UNUSED3
mdefine_line|#define _PAGE_BIT_UNUSED3&t;11
DECL|macro|_PAGE_BIT_NX
mdefine_line|#define _PAGE_BIT_NX&t;&t;63
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
DECL|macro|_PAGE_UNUSED1
mdefine_line|#define _PAGE_UNUSED1&t;0x200&t;/* available for programmer */
DECL|macro|_PAGE_UNUSED2
mdefine_line|#define _PAGE_UNUSED2&t;0x400
DECL|macro|_PAGE_UNUSED3
mdefine_line|#define _PAGE_UNUSED3&t;0x800
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;0x040&t;/* set:pagecache unset:swap */
DECL|macro|_PAGE_PROTNONE
mdefine_line|#define _PAGE_PROTNONE&t;0x080&t;/* If not present */
macro_line|#ifdef CONFIG_X86_PAE
DECL|macro|_PAGE_NX
mdefine_line|#define _PAGE_NX&t;(1ULL&lt;&lt;_PAGE_BIT_NX)
macro_line|#else
DECL|macro|_PAGE_NX
mdefine_line|#define _PAGE_NX&t;0
macro_line|#endif
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PTE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE &bslash;&n;&t;__pgprot(_PAGE_PROTNONE | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED &bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED_EXEC
mdefine_line|#define PAGE_SHARED_EXEC &bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY_NOEXEC
mdefine_line|#define PAGE_COPY_NOEXEC &bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED | _PAGE_NX)
DECL|macro|PAGE_COPY_EXEC
mdefine_line|#define PAGE_COPY_EXEC &bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY &bslash;&n;&t;PAGE_COPY_NOEXEC
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY &bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED | _PAGE_NX)
DECL|macro|PAGE_READONLY_EXEC
mdefine_line|#define PAGE_READONLY_EXEC &bslash;&n;&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|_PAGE_KERNEL
mdefine_line|#define _PAGE_KERNEL &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_ACCESSED | _PAGE_NX)
DECL|macro|_PAGE_KERNEL_EXEC
mdefine_line|#define _PAGE_KERNEL_EXEC &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_ACCESSED)
r_extern
r_int
r_int
r_int
id|__PAGE_KERNEL
comma
id|__PAGE_KERNEL_EXEC
suffix:semicolon
DECL|macro|__PAGE_KERNEL_RO
mdefine_line|#define __PAGE_KERNEL_RO&t;&t;(__PAGE_KERNEL &amp; ~_PAGE_RW)
DECL|macro|__PAGE_KERNEL_NOCACHE
mdefine_line|#define __PAGE_KERNEL_NOCACHE&t;&t;(__PAGE_KERNEL | _PAGE_PCD)
DECL|macro|__PAGE_KERNEL_LARGE
mdefine_line|#define __PAGE_KERNEL_LARGE&t;&t;(__PAGE_KERNEL | _PAGE_PSE)
DECL|macro|__PAGE_KERNEL_LARGE_EXEC
mdefine_line|#define __PAGE_KERNEL_LARGE_EXEC&t;(__PAGE_KERNEL_EXEC | _PAGE_PSE)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;&t;__pgprot(__PAGE_KERNEL)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO&t;&t;__pgprot(__PAGE_KERNEL_RO)
DECL|macro|PAGE_KERNEL_EXEC
mdefine_line|#define PAGE_KERNEL_EXEC&t;__pgprot(__PAGE_KERNEL_EXEC)
DECL|macro|PAGE_KERNEL_NOCACHE
mdefine_line|#define PAGE_KERNEL_NOCACHE&t;__pgprot(__PAGE_KERNEL_NOCACHE)
DECL|macro|PAGE_KERNEL_LARGE
mdefine_line|#define PAGE_KERNEL_LARGE&t;__pgprot(__PAGE_KERNEL_LARGE)
DECL|macro|PAGE_KERNEL_LARGE_EXEC
mdefine_line|#define PAGE_KERNEL_LARGE_EXEC&t;__pgprot(__PAGE_KERNEL_LARGE_EXEC)
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
multiline_comment|/*&n; * Define this if things work differently on an i386 and an i486:&n; * it will (on an i486) warn about kernel memory accesses that are&n; * done without a &squot;verify_area(VERIFY_WRITE,..)&squot;&n; */
DECL|macro|TEST_VERIFY_AREA
macro_line|#undef TEST_VERIFY_AREA
multiline_comment|/* The boot page tables (all created as a single array) */
r_extern
r_int
r_int
id|pg0
(braket
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
id|pte
)paren
dot
id|pte_low
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
macro_line|#ifdef CONFIG_X86_PAE
macro_line|# include &lt;asm/pgtable-3level.h&gt;
macro_line|#else
macro_line|# include &lt;asm/pgtable-2level.h&gt;
macro_line|#endif
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
r_if
c_cond
(paren
op_logical_neg
id|pte_dirty
c_func
(paren
op_star
id|ptep
)paren
)paren
r_return
l_int|0
suffix:semicolon
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
r_if
c_cond
(paren
op_logical_neg
id|pte_young
c_func
(paren
op_star
id|ptep
)paren
)paren
r_return
l_int|0
suffix:semicolon
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
multiline_comment|/*&n; * Macro to mark a page protection value as &quot;uncacheable&quot;.  On processors which do not support&n; * it, this is a no-op.&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached(prot)&t;((boot_cpu_data.x86 &gt; 3)&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;&t;&t; ? (__pgprot(pgprot_val(prot) | _PAGE_PCD | _PAGE_PWT)) : (prot))
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;pfn_pte(page_to_pfn(page), (pgprot))
DECL|macro|mk_pte_huge
mdefine_line|#define mk_pte_huge(entry) ((entry).pte_low |= _PAGE_PRESENT | _PAGE_PSE)
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
macro_line|#ifdef CONFIG_X86_PAE
multiline_comment|/*&n;&t; * Chop off the NX bit (if present), and add the NX portion of&n;&t; * the newprot (if present):&n;&t; */
id|pte.pte_high
op_and_assign
op_complement
(paren
l_int|1
op_lshift
(paren
id|_PAGE_BIT_NX
op_minus
l_int|32
)paren
)paren
suffix:semicolon
id|pte.pte_high
op_or_assign
(paren
id|pgprot_val
c_func
(paren
id|newprot
)paren
op_rshift
l_int|32
)paren
op_amp
"&bslash;"
(paren
id|__supported_pte_mask
op_rshift
l_int|32
)paren
suffix:semicolon
macro_line|#endif
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|page_pte
mdefine_line|#define page_pte(page) page_pte_prot(page, __pgprot(0))
DECL|macro|pmd_large
mdefine_line|#define pmd_large(pmd) &bslash;&n;((pmd_val(pmd) &amp; (_PAGE_PSE|_PAGE_PRESENT)) == (_PAGE_PSE|_PAGE_PRESENT))
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
mdefine_line|#define pte_index(address) &bslash;&n;&t;&t;(((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address) &bslash;&n;&t;((pte_t *) pmd_page_kernel(*(dir)) +  pte_index(address))
multiline_comment|/*&n; * Helper function that returns the kernel pagetable entry controlling&n; * the virtual address &squot;address&squot;. NULL means no pagetable entry present.&n; * NOTE: the return type is pte_t but if the pmd is PSE then we return it&n; * as a pte too.&n; */
r_extern
id|pte_t
op_star
id|lookup_address
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
multiline_comment|/*&n; * Make a given kernel text page executable/non-executable.&n; * Returns the previous executability setting of that page (which&n; * is used to restore the previous state). Used by the SMP bootup code.&n; * NOTE: this is an __init function for security reasons.&n; */
macro_line|#ifdef CONFIG_X86_PAE
r_extern
r_int
id|set_kernel_exec
c_func
(paren
r_int
r_int
id|vaddr
comma
r_int
id|enable
)paren
suffix:semicolon
macro_line|#else
DECL|function|set_kernel_exec
r_static
r_inline
r_int
id|set_kernel_exec
c_func
(paren
r_int
r_int
id|vaddr
comma
r_int
id|enable
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_extern
r_void
id|noexec_setup
c_func
(paren
r_const
r_char
op_star
id|str
)paren
suffix:semicolon
macro_line|#if defined(CONFIG_HIGHPTE)
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address) &bslash;&n;&t;((pte_t *)kmap_atomic(pmd_page(*(dir)),KM_PTE0) + pte_index(address))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address) &bslash;&n;&t;((pte_t *)kmap_atomic(pmd_page(*(dir)),KM_PTE1) + pte_index(address))
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) kunmap_atomic(pte, KM_PTE0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) kunmap_atomic(pte, KM_PTE1)
macro_line|#else
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address) &bslash;&n;&t;((pte_t *)page_address(pmd_page(*(dir))) + pte_index(address))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address) pte_offset_map(dir, address)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) do { } while (0)
macro_line|#endif
multiline_comment|/*&n; * The i386 doesn&squot;t have any external MMU info: the kernel page&n; * tables contain all the necessary information.&n; *&n; * Also, we only update the dirty/accessed state if we set&n; * the dirty bit by hand in the kernel, since the hardware&n; * will do the accessed bit for us, and we don&squot;t want to&n; * race with other CPU&squot;s that might be updating the dirty&n; * bit at the same time.&n; */
DECL|macro|update_mmu_cache
mdefine_line|#define update_mmu_cache(vma,address,pte) do { } while (0)
DECL|macro|__HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
mdefine_line|#define  __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
DECL|macro|ptep_set_access_flags
mdefine_line|#define ptep_set_access_flags(__vma, __address, __ptep, __entry, __dirty) &bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;if (__dirty) {&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;&t;(__ptep)-&gt;pte_low = (__entry).pte_low;&t;  &t;  &bslash;&n;&t;&t;&t;flush_tlb_page(__vma, __address);&t;&t;  &bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;} while (0)
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#ifndef CONFIG_DISCONTIGMEM
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
macro_line|#endif /* !CONFIG_DISCONTIGMEM */
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma, vaddr, paddr, size, prot)&t;&t;&bslash;&n;&t;&t;remap_pfn_range(vma, vaddr, (paddr) &gt;&gt; PAGE_SHIFT, size, prot)
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
macro_line|#endif /* _I386_PGTABLE_H */
eof
