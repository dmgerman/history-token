macro_line|#ifndef _X86_64_PGTABLE_H
DECL|macro|_X86_64_PGTABLE_H
mdefine_line|#define _X86_64_PGTABLE_H
multiline_comment|/*&n; * This file contains the functions and defines necessary to modify and use&n; * the x86-64 page table tree.&n; */
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
r_extern
id|pud_t
id|level3_kernel_pgt
(braket
l_int|512
)braket
suffix:semicolon
r_extern
id|pud_t
id|level3_physmem_pgt
(braket
l_int|512
)braket
suffix:semicolon
r_extern
id|pud_t
id|level3_ident_pgt
(braket
l_int|512
)braket
suffix:semicolon
r_extern
id|pmd_t
id|level2_kernel_pgt
(braket
l_int|512
)braket
suffix:semicolon
r_extern
id|pgd_t
id|init_level4_pgt
(braket
)braket
suffix:semicolon
r_extern
r_int
r_int
id|__supported_pte_mask
suffix:semicolon
DECL|macro|swapper_pg_dir
mdefine_line|#define swapper_pg_dir init_level4_pgt
r_extern
r_void
id|nonx_setup
c_func
(paren
r_const
r_char
op_star
id|str
)paren
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
id|clear_kernel_mapping
c_func
(paren
r_int
r_int
id|addr
comma
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_int
r_int
id|pgkern_mask
suffix:semicolon
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_int
r_int
id|empty_zero_page
(braket
id|PAGE_SIZE
op_div
r_sizeof
(paren
r_int
r_int
)paren
)braket
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
multiline_comment|/*&n; * PGDIR_SHIFT determines what a top-level page table entry can map&n; */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;39
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;512
multiline_comment|/*&n; * 3rd level page&n; */
DECL|macro|PUD_SHIFT
mdefine_line|#define PUD_SHIFT&t;30
DECL|macro|PTRS_PER_PUD
mdefine_line|#define PTRS_PER_PUD&t;512
multiline_comment|/*&n; * PMD_SHIFT determines the size of the area a middle-level&n; * page table can map&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;21
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;512
multiline_comment|/*&n; * entries per page directory level&n; */
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;512
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %p(%016lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %p(%016lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pmd_val(e))
DECL|macro|pud_ERROR
mdefine_line|#define pud_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pud %p(%016lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pud_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %p(%016lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pgd_val(e))
DECL|macro|pgd_none
mdefine_line|#define pgd_none(x)&t;(!pgd_val(x))
DECL|macro|pud_none
mdefine_line|#define pud_none(x)&t;(!pud_val(x))
DECL|function|set_pte
r_static
r_inline
r_void
id|set_pte
c_func
(paren
id|pte_t
op_star
id|dst
comma
id|pte_t
id|val
)paren
(brace
id|pte_val
c_func
(paren
op_star
id|dst
)paren
op_assign
id|pte_val
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
DECL|function|set_pmd
r_static
r_inline
r_void
id|set_pmd
c_func
(paren
id|pmd_t
op_star
id|dst
comma
id|pmd_t
id|val
)paren
(brace
id|pmd_val
c_func
(paren
op_star
id|dst
)paren
op_assign
id|pmd_val
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
DECL|function|set_pud
r_static
r_inline
r_void
id|set_pud
c_func
(paren
id|pud_t
op_star
id|dst
comma
id|pud_t
id|val
)paren
(brace
id|pud_val
c_func
(paren
op_star
id|dst
)paren
op_assign
id|pud_val
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
DECL|function|pud_clear
r_extern
r_inline
r_void
id|pud_clear
(paren
id|pud_t
op_star
id|pud
)paren
(brace
id|set_pud
c_func
(paren
id|pud
comma
id|__pud
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
DECL|function|set_pgd
r_static
r_inline
r_void
id|set_pgd
c_func
(paren
id|pgd_t
op_star
id|dst
comma
id|pgd_t
id|val
)paren
(brace
id|pgd_val
c_func
(paren
op_star
id|dst
)paren
op_assign
id|pgd_val
c_func
(paren
id|val
)paren
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
id|pgd
)paren
(brace
id|set_pgd
c_func
(paren
id|pgd
comma
id|__pgd
c_func
(paren
l_int|0
)paren
)paren
suffix:semicolon
)brace
DECL|macro|pud_page
mdefine_line|#define pud_page(pud) &bslash;&n;((unsigned long) __va(pud_val(pud) &amp; PHYSICAL_PAGE_MASK))
DECL|macro|ptep_get_and_clear
mdefine_line|#define ptep_get_and_clear(xp)&t;__pte(xchg(&amp;(xp)-&gt;pte, 0))
DECL|macro|pte_same
mdefine_line|#define pte_same(a, b)&t;&t;((a).pte == (b).pte)
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
DECL|macro|PUD_SIZE
mdefine_line|#define PUD_SIZE&t;(1UL &lt;&lt; PUD_SHIFT)
DECL|macro|PUD_MASK
mdefine_line|#define PUD_MASK&t;(~(PUD_SIZE-1))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE/PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
macro_line|#ifndef __ASSEMBLY__
DECL|macro|MAXMEM
mdefine_line|#define MAXMEM&t;&t; 0x3fffffffffffUL
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START    0xffffc20000000000UL
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END      0xffffe1ffffffffffUL
DECL|macro|MODULES_VADDR
mdefine_line|#define MODULES_VADDR    0xffffffff88000000
DECL|macro|MODULES_END
mdefine_line|#define MODULES_END      0xfffffffffff00000
DECL|macro|MODULES_LEN
mdefine_line|#define MODULES_LEN   (MODULES_END - MODULES_VADDR)
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
mdefine_line|#define _PAGE_BIT_PSE&t;&t;7&t;/* 4 MB (or 2MB) page */
DECL|macro|_PAGE_BIT_GLOBAL
mdefine_line|#define _PAGE_BIT_GLOBAL&t;8&t;/* Global TLB entry PPro+ */
DECL|macro|_PAGE_BIT_NX
mdefine_line|#define _PAGE_BIT_NX           63       /* No execute: only valid after cpuid check */
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
mdefine_line|#define _PAGE_PSE&t;0x080&t;/* 2MB page */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;0x040&t;/* set:pagecache, unset:swap */
DECL|macro|_PAGE_GLOBAL
mdefine_line|#define _PAGE_GLOBAL&t;0x100&t;/* Global TLB entry */
DECL|macro|_PAGE_PROTNONE
mdefine_line|#define _PAGE_PROTNONE&t;0x080&t;/* If not present */
DECL|macro|_PAGE_NX
mdefine_line|#define _PAGE_NX        (1UL&lt;&lt;_PAGE_BIT_NX)
DECL|macro|_PAGE_TABLE
mdefine_line|#define _PAGE_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_KERNPG_TABLE
mdefine_line|#define _KERNPG_TABLE&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PTE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PROTNONE | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED | _PAGE_NX)
DECL|macro|PAGE_SHARED_EXEC
mdefine_line|#define PAGE_SHARED_EXEC __pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY_NOEXEC
mdefine_line|#define PAGE_COPY_NOEXEC __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED | _PAGE_NX)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY PAGE_COPY_NOEXEC
DECL|macro|PAGE_COPY_EXEC
mdefine_line|#define PAGE_COPY_EXEC __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED | _PAGE_NX)
DECL|macro|PAGE_READONLY_EXEC
mdefine_line|#define PAGE_READONLY_EXEC __pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|__PAGE_KERNEL
mdefine_line|#define __PAGE_KERNEL &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_ACCESSED | _PAGE_NX)
DECL|macro|__PAGE_KERNEL_EXEC
mdefine_line|#define __PAGE_KERNEL_EXEC &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_ACCESSED)
DECL|macro|__PAGE_KERNEL_NOCACHE
mdefine_line|#define __PAGE_KERNEL_NOCACHE &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_PCD | _PAGE_ACCESSED | _PAGE_NX)
DECL|macro|__PAGE_KERNEL_RO
mdefine_line|#define __PAGE_KERNEL_RO &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_DIRTY | _PAGE_ACCESSED | _PAGE_NX)
DECL|macro|__PAGE_KERNEL_VSYSCALL
mdefine_line|#define __PAGE_KERNEL_VSYSCALL &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|__PAGE_KERNEL_VSYSCALL_NOCACHE
mdefine_line|#define __PAGE_KERNEL_VSYSCALL_NOCACHE &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED | _PAGE_PCD)
DECL|macro|__PAGE_KERNEL_LARGE
mdefine_line|#define __PAGE_KERNEL_LARGE &bslash;&n;&t;(__PAGE_KERNEL | _PAGE_PSE)
DECL|macro|MAKE_GLOBAL
mdefine_line|#define MAKE_GLOBAL(x) __pgprot((x) | _PAGE_GLOBAL)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL MAKE_GLOBAL(__PAGE_KERNEL)
DECL|macro|PAGE_KERNEL_EXEC
mdefine_line|#define PAGE_KERNEL_EXEC MAKE_GLOBAL(__PAGE_KERNEL_EXEC)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO MAKE_GLOBAL(__PAGE_KERNEL_RO)
DECL|macro|PAGE_KERNEL_NOCACHE
mdefine_line|#define PAGE_KERNEL_NOCACHE MAKE_GLOBAL(__PAGE_KERNEL_NOCACHE)
DECL|macro|PAGE_KERNEL_VSYSCALL
mdefine_line|#define PAGE_KERNEL_VSYSCALL MAKE_GLOBAL(__PAGE_KERNEL_VSYSCALL)
DECL|macro|PAGE_KERNEL_LARGE
mdefine_line|#define PAGE_KERNEL_LARGE MAKE_GLOBAL(__PAGE_KERNEL_LARGE)
DECL|macro|PAGE_KERNEL_VSYSCALL_NOCACHE
mdefine_line|#define PAGE_KERNEL_VSYSCALL_NOCACHE MAKE_GLOBAL(__PAGE_KERNEL_VSYSCALL_NOCACHE)
multiline_comment|/*         xwr */
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
DECL|function|pgd_bad
r_static
r_inline
r_int
r_int
id|pgd_bad
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_int
r_int
id|val
op_assign
id|pgd_val
c_func
(paren
id|pgd
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|PTE_MASK
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
id|_PAGE_USER
op_or
id|_PAGE_DIRTY
)paren
suffix:semicolon
r_return
id|val
op_amp
op_complement
(paren
id|_PAGE_PRESENT
op_or
id|_PAGE_RW
op_or
id|_PAGE_ACCESSED
)paren
suffix:semicolon
)brace
DECL|function|pud_bad
r_static
r_inline
r_int
r_int
id|pud_bad
c_func
(paren
id|pud_t
id|pud
)paren
(brace
r_int
r_int
id|val
op_assign
id|pud_val
c_func
(paren
id|pud
)paren
suffix:semicolon
id|val
op_and_assign
op_complement
id|PTE_MASK
suffix:semicolon
id|val
op_and_assign
op_complement
(paren
id|_PAGE_USER
op_or
id|_PAGE_DIRTY
)paren
suffix:semicolon
r_return
id|val
op_amp
op_complement
(paren
id|_PAGE_PRESENT
op_or
id|_PAGE_RW
op_or
id|_PAGE_ACCESSED
)paren
suffix:semicolon
)brace
DECL|macro|pte_none
mdefine_line|#define pte_none(x)&t;(!pte_val(x))
DECL|macro|pte_present
mdefine_line|#define pte_present(x)&t;(pte_val(x) &amp; (_PAGE_PRESENT | _PAGE_PROTNONE))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(xp)&t;do { set_pte(xp, __pte(0)); } while (0)
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x) ((x) &gt;&gt; (20-PAGE_SHIFT))&t;/* FIXME: is this&n;&t;&t;&t;&t;&t;&t;   right? */
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;pfn_to_page(pte_pfn(x))
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)  ((pte_val(x) &gt;&gt; PAGE_SHIFT) &amp; __PHYSICAL_MASK)
DECL|function|pfn_pte
r_static
r_inline
id|pte_t
id|pfn_pte
c_func
(paren
r_int
r_int
id|page_nr
comma
id|pgprot_t
id|pgprot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
(paren
id|page_nr
op_lshift
id|PAGE_SHIFT
)paren
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|pgprot_val
c_func
(paren
id|pgprot
)paren
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
id|__supported_pte_mask
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
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
id|_PAGE_USER
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
id|_PAGE_USER
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
id|_PAGE_DIRTY
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
id|_PAGE_RW
suffix:semicolon
)brace
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_USER
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_USER
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_DIRTY
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_ACCESSED
)paren
)paren
suffix:semicolon
r_return
id|pte
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_RW
)paren
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or
id|_PAGE_USER
)paren
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or
id|_PAGE_USER
)paren
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or
id|_PAGE_DIRTY
)paren
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or
id|_PAGE_ACCESSED
)paren
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
id|set_pte
c_func
(paren
op_amp
id|pte
comma
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
op_or
id|_PAGE_RW
)paren
)paren
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
id|_PAGE_BIT_RW
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
multiline_comment|/*&n; * Macro to mark a page protection value as &quot;uncacheable&quot;.&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached(prot)&t;(__pgprot(pgprot_val(prot) | _PAGE_PCD | _PAGE_PWT))
DECL|macro|__LARGE_PTE
mdefine_line|#define __LARGE_PTE (_PAGE_PSE|_PAGE_PRESENT) 
DECL|function|pmd_large
r_static
r_inline
r_int
id|pmd_large
c_func
(paren
id|pmd_t
id|pte
)paren
(brace
r_return
(paren
id|pmd_val
c_func
(paren
id|pte
)paren
op_amp
id|__LARGE_PTE
)paren
op_eq
id|__LARGE_PTE
suffix:semicolon
)brace
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|page_pte
mdefine_line|#define page_pte(page) page_pte_prot(page, __pgprot(0))
multiline_comment|/*&n; * Level 4 access.&n; */
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd) ((unsigned long) __va((unsigned long)pgd_val(pgd) &amp; PTE_MASK))
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) (((address) &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD-1))
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, addr) ((mm)-&gt;pgd + pgd_index(addr))
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) (init_level4_pgt + pgd_index(address))
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd) (pgd_val(pgd) &amp; _PAGE_PRESENT)
DECL|macro|mk_kernel_pgd
mdefine_line|#define mk_kernel_pgd(address) ((pgd_t){ (address) | _KERNPG_TABLE })
multiline_comment|/* PUD - Level3 access */
multiline_comment|/* to find an entry in a page-table-directory. */
DECL|macro|pud_index
mdefine_line|#define pud_index(address) (((address) &gt;&gt; PUD_SHIFT) &amp; (PTRS_PER_PUD-1))
DECL|macro|pud_offset
mdefine_line|#define pud_offset(pgd, address) ((pud_t *) pgd_page(*(pgd)) + pud_index(address))
DECL|macro|pud_offset_k
mdefine_line|#define pud_offset_k(pgd, addr) pud_offset(pgd, addr)
DECL|macro|pud_present
mdefine_line|#define pud_present(pud) (pud_val(pud) &amp; _PAGE_PRESENT)
DECL|function|__pud_offset_k
r_static
r_inline
id|pud_t
op_star
id|__pud_offset_k
c_func
(paren
id|pud_t
op_star
id|pud
comma
r_int
r_int
id|address
)paren
(brace
r_return
id|pud
op_plus
id|pud_index
c_func
(paren
id|address
)paren
suffix:semicolon
)brace
multiline_comment|/* PMD  - Level 2 access */
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd) ((unsigned long) __va(pmd_val(pmd) &amp; PTE_MASK))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;(pfn_to_page(pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
DECL|macro|pmd_index
mdefine_line|#define pmd_index(address) (((address) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD-1))
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir, address) ((pmd_t *) pud_page(*(dir)) + &bslash;&n;&t;&t;&t;pmd_index(address))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!pmd_val(x))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(x)&t;(pmd_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(xp)&t;do { set_pmd(xp, __pmd(0)); } while (0)
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(x)&t;((pmd_val(x) &amp; (~PTE_MASK &amp; ~_PAGE_USER)) != _KERNPG_TABLE )
DECL|macro|pfn_pmd
mdefine_line|#define pfn_pmd(nr,prot) (__pmd(((nr) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot)))
DECL|macro|pmd_pfn
mdefine_line|#define pmd_pfn(x)  ((pmd_val(x) &gt;&gt; PAGE_SHIFT) &amp; __PHYSICAL_MASK)
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(pte) ((pte_val(pte) &amp; PHYSICAL_PAGE_MASK) &gt;&gt; PAGE_SHIFT)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) ((pte_t) { ((off) &lt;&lt; PAGE_SHIFT) | _PAGE_FILE })
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS __PHYSICAL_MASK_SHIFT
multiline_comment|/* PTE - Level 1 access. */
multiline_comment|/* page, protection -&gt; pte */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;pfn_pte(page_to_pfn(page), (pgprot))
DECL|macro|mk_pte_huge
mdefine_line|#define mk_pte_huge(entry) (pte_val(entry) |= _PAGE_PRESENT | _PAGE_PSE)
multiline_comment|/* physical address -&gt; PTE */
DECL|function|mk_pte_phys
r_static
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
id|pte_t
id|pte
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_assign
id|physpage
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
multiline_comment|/* Change flags of a PTE */
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
op_and_assign
id|_PAGE_CHG_MASK
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|pgprot_val
c_func
(paren
id|newprot
)paren
suffix:semicolon
id|pte_val
c_func
(paren
id|pte
)paren
op_and_assign
id|__supported_pte_mask
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|pte_index
mdefine_line|#define pte_index(address) &bslash;&n;&t;&t;((address &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address) ((pte_t *) pmd_page_kernel(*(dir)) + &bslash;&n;&t;&t;&t;pte_index(address))
multiline_comment|/* x86-64 always has all page tables mapped. */
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir,address) pte_offset_kernel(dir,address)
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir,address) pte_offset_kernel(dir,address)
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) /* NOP */
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) /* NOP */ 
DECL|macro|update_mmu_cache
mdefine_line|#define update_mmu_cache(vma,address,pte) do { } while (0)
multiline_comment|/* We only update the dirty/accessed state if we set&n; * the dirty bit by hand in the kernel, since the hardware&n; * will do the accessed bit for us, and we don&squot;t want to&n; * race with other CPU&squot;s that might be updating the dirty&n; * bit at the same time. */
DECL|macro|__HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
mdefine_line|#define  __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
DECL|macro|ptep_set_access_flags
mdefine_line|#define ptep_set_access_flags(__vma, __address, __ptep, __entry, __dirty) &bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;if (__dirty) {&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;&t;&t;set_pte(__ptep, __entry);&t;&t;&t;  &bslash;&n;&t;&t;&t;flush_tlb_page(__vma, __address);&t;&t;  &bslash;&n;&t;&t;}&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;} while (0)
multiline_comment|/* Encode and de-code a swap entry */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;&t;(((x).val &gt;&gt; 1) &amp; 0x3f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;&t;((x).val &gt;&gt; 8)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset)&t;((swp_entry_t) { ((type) &lt;&lt; 1) | ((offset) &lt;&lt; 8) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
macro_line|#endif /* !__ASSEMBLY__ */
r_extern
r_int
id|kern_addr_valid
c_func
(paren
r_int
r_int
id|addr
)paren
suffix:semicolon
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma, vaddr, paddr, size, prot)&t;&t;&bslash;&n;&t;&t;remap_pfn_range(vma, vaddr, (paddr) &gt;&gt; PAGE_SHIFT, size, prot)
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()   do { } while (0)
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()      do { } while (0)
DECL|macro|PAGE_AGP
mdefine_line|#define PAGE_AGP    PAGE_KERNEL_NOCACHE
DECL|macro|HAVE_PAGE_AGP
mdefine_line|#define HAVE_PAGE_AGP 1
multiline_comment|/* fs/proc/kcore.c */
DECL|macro|kc_vaddr_to_offset
mdefine_line|#define&t;kc_vaddr_to_offset(v) ((v) &amp; __VIRTUAL_MASK)
DECL|macro|kc_offset_to_vaddr
mdefine_line|#define&t;kc_offset_to_vaddr(o) &bslash;&n;   (((o) &amp; (1UL &lt;&lt; (__VIRTUAL_MASK_SHIFT-1))) ? ((o) | (~__VIRTUAL_MASK)) : (o))
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
macro_line|#endif /* _X86_64_PGTABLE_H */
eof
