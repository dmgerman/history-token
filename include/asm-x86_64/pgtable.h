macro_line|#ifndef _X86_64_PGTABLE_H
DECL|macro|_X86_64_PGTABLE_H
mdefine_line|#define _X86_64_PGTABLE_H
multiline_comment|/*&n; * This file contains the functions and defines necessary to modify and use&n; * the x86-64 page table tree.&n; * &n; * x86-64 has a 4 level table setup. Generic linux MM only supports&n; * three levels. The fourth level is currently a single static page that&n; * is shared by everybody and just contains a pointer to the current&n; * three level page setup on the beginning and some kernel mappings at &n; * the end. For more details see Documentation/x86_64/mm.txt&n; */
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;linux/threads.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
r_extern
id|pgd_t
id|level3_kernel_pgt
(braket
l_int|512
)braket
suffix:semicolon
r_extern
id|pgd_t
id|level3_physmem_pgt
(braket
l_int|512
)braket
suffix:semicolon
r_extern
id|pgd_t
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
id|pml4_t
id|init_level4_pgt
(braket
)braket
suffix:semicolon
r_extern
id|pgd_t
id|boot_vmalloc_pgt
(braket
)braket
suffix:semicolon
DECL|macro|swapper_pg_dir
mdefine_line|#define swapper_pg_dir NULL
r_extern
r_void
id|paging_init
c_func
(paren
r_void
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
l_int|1024
)braket
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
DECL|macro|PML4_SHIFT
mdefine_line|#define PML4_SHIFT&t;39
DECL|macro|PTRS_PER_PML4
mdefine_line|#define PTRS_PER_PML4&t;512
multiline_comment|/*&n; * PGDIR_SHIFT determines what a top-level page table entry can map&n; */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;30
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;512
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
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %p(%016lx).&bslash;n&quot;, __FILE__, __LINE__, &amp;(e), pgd_val(e))
DECL|macro|pml4_none
mdefine_line|#define pml4_none(x)&t;(!pml4_val(x))
DECL|macro|pgd_none
mdefine_line|#define pgd_none(x)&t;(!pgd_val(x))
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
op_logical_neg
id|pgd_none
c_func
(paren
id|pgd
)paren
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
DECL|function|set_pml4
r_static
r_inline
r_void
id|set_pml4
c_func
(paren
id|pml4_t
op_star
id|dst
comma
id|pml4_t
id|val
)paren
(brace
id|pml4_val
c_func
(paren
op_star
id|dst
)paren
op_assign
id|pml4_val
c_func
(paren
id|val
)paren
suffix:semicolon
)brace
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd) &bslash;&n;((unsigned long) __va(pgd_val(pgd) &amp; PAGE_MASK))
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir, address) ((pmd_t *) pgd_page(*(dir)) + &bslash;&n;&t;&t;&t;__pmd_offset(address))
DECL|macro|ptep_get_and_clear
mdefine_line|#define ptep_get_and_clear(xp)&t;__pte(xchg(&amp;(xp)-&gt;pte, 0))
DECL|macro|pte_same
mdefine_line|#define pte_same(a, b)&t;&t;((a).pte == (b).pte)
DECL|macro|__mk_pte
mdefine_line|#define __mk_pte(page_nr,pgprot) __pte(((page_nr) &lt;&lt; PAGE_SHIFT) | pgprot_val(pgprot))
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
mdefine_line|#define TWOLEVEL_PGDIR_SHIFT&t;20
DECL|macro|BOOT_USER_L4_PTRS
mdefine_line|#define BOOT_USER_L4_PTRS 1
DECL|macro|BOOT_KERNEL_L4_PTRS
mdefine_line|#define BOOT_KERNEL_L4_PTRS 511&t;/* But we will do it in 4rd level */
macro_line|#ifndef __ASSEMBLY__
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START    0xffffff0000000000
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END      0xffffff7fffffffff
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|MODULES_VADDR
mdefine_line|#define MODULES_VADDR    0xffffffffa0000000
DECL|macro|MODULES_END
mdefine_line|#define MODULES_END      0xffffffffafffffff
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
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|__PAGE_KERNEL
mdefine_line|#define __PAGE_KERNEL &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_ACCESSED)
DECL|macro|__PAGE_KERNEL_NOCACHE
mdefine_line|#define __PAGE_KERNEL_NOCACHE &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_RW | _PAGE_DIRTY | _PAGE_PCD | _PAGE_ACCESSED)
DECL|macro|__PAGE_KERNEL_RO
mdefine_line|#define __PAGE_KERNEL_RO &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_DIRTY | _PAGE_ACCESSED)
DECL|macro|__PAGE_KERNEL_VSYSCALL
mdefine_line|#define __PAGE_KERNEL_VSYSCALL &bslash;&n;&t;(_PAGE_PRESENT | _PAGE_USER | _PAGE_ACCESSED)
DECL|macro|MAKE_GLOBAL
mdefine_line|#define MAKE_GLOBAL(x) __pgprot((x) | _PAGE_GLOBAL)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL MAKE_GLOBAL(__PAGE_KERNEL)
DECL|macro|PAGE_KERNEL_RO
mdefine_line|#define PAGE_KERNEL_RO MAKE_GLOBAL(__PAGE_KERNEL_RO)
DECL|macro|PAGE_KERNEL_NOCACHE
mdefine_line|#define PAGE_KERNEL_NOCACHE MAKE_GLOBAL(__PAGE_KERNEL_NOCACHE)
DECL|macro|PAGE_KERNEL_VSYSCALL
mdefine_line|#define PAGE_KERNEL_VSYSCALL MAKE_GLOBAL(__PAGE_KERNEL_VSYSCALL)
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
id|PAGE_MASK
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
DECL|macro|pmd_none
mdefine_line|#define pmd_none(x)&t;(!pmd_val(x))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(x)&t;(pmd_val(x) &amp; _PAGE_PRESENT)
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(xp)&t;do { set_pmd(xp, __pmd(0)); } while (0)
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(x)&t;((pmd_val(x) &amp; (~PAGE_MASK &amp; ~_PAGE_USER)) != _KERNPG_TABLE )
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x) ((x) &gt;&gt; (20-PAGE_SHIFT))&t;/* FIXME: is this&n;&t;&t;&t;&t;&t;&t;   right? */
DECL|macro|pte_page
mdefine_line|#define pte_page(x) (mem_map+((unsigned long)((pte_val(x) &gt;&gt; PAGE_SHIFT))))
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
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|page_pte
mdefine_line|#define page_pte(page) page_pte_prot(page, __pgprot(0))
multiline_comment|/*&n; * Level 4 access.&n; * Never use these in the common code.&n; */
DECL|macro|pml4_page
mdefine_line|#define pml4_page(pml4) ((unsigned long) __va(pml4_val(pml4) &amp; PAGE_MASK))
DECL|macro|pml4_index
mdefine_line|#define pml4_index(address) ((address &gt;&gt; PML4_SHIFT) &amp; (PTRS_PER_PML4-1))
DECL|macro|pml4_offset_k
mdefine_line|#define pml4_offset_k(address) (init_level4_pgt + pml4_index(address))
DECL|macro|mk_kernel_pml4
mdefine_line|#define mk_kernel_pml4(address) ((pml4_t){ (address) | _KERNPG_TABLE })
DECL|macro|level3_offset_k
mdefine_line|#define level3_offset_k(dir, address) ((pgd_t *) pml4_page(*(dir)) + pgd_index(address))
multiline_comment|/* PGD - Level3 access */
DECL|macro|__pgd_offset_k
mdefine_line|#define __pgd_offset_k(pgd, address) ((pgd) + pgd_index(address))
multiline_comment|/* to find an entry in a page-table-directory. */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) ((address &gt;&gt; PGDIR_SHIFT) &amp; (PTRS_PER_PGD-1))
DECL|macro|current_pgd_offset_k
mdefine_line|#define current_pgd_offset_k(address) &bslash;&n;       __pgd_offset_k((pgd_t *)read_pda(level4_pgt), address)
multiline_comment|/* This accesses the reference page table of the boot cpu. &n;   Other CPUs get synced lazily via the page fault handler. */
DECL|function|pgd_offset_k
r_static
r_inline
id|pgd_t
op_star
id|pgd_offset_k
c_func
(paren
r_int
r_int
id|address
)paren
(brace
id|pml4_t
id|pml4
suffix:semicolon
id|pml4
op_assign
id|init_level4_pgt
(braket
id|pml4_index
c_func
(paren
id|address
)paren
)braket
suffix:semicolon
r_return
id|__pgd_offset_k
c_func
(paren
id|__va
c_func
(paren
id|pml4_val
c_func
(paren
id|pml4
)paren
op_amp
id|PAGE_MASK
)paren
comma
id|address
)paren
suffix:semicolon
)brace
DECL|macro|__pgd_offset
mdefine_line|#define __pgd_offset(address) pgd_index(address)
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address) ((mm)-&gt;pgd+pgd_index(address))
multiline_comment|/* PMD  - Level 2 access */
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd) ((unsigned long) __va(pmd_val(pmd) &amp; PAGE_MASK))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)        (mem_map + (pmd_val(pmd) &gt;&gt; PAGE_SHIFT))
DECL|macro|__pmd_offset
mdefine_line|#define __pmd_offset(address) &bslash;&n;&t;&t;(((address) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD-1))
multiline_comment|/* PTE - Level 1 access. */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page,pgprot) &bslash;&n;({                                                                     &bslash;&n;       pte_t __pte;                                                    &bslash;&n;                                                                       &bslash;&n;       set_pte(&amp;__pte, __pte(((page)-mem_map) *                        &bslash;&n;               (unsigned long long)PAGE_SIZE + pgprot_val(pgprot)));   &bslash;&n;       __pte;                                                          &bslash;&n;})
multiline_comment|/* This takes a physical page address that is used by the remapping functions */
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
id|__pte
suffix:semicolon
id|set_pte
c_func
(paren
op_amp
id|__pte
comma
id|__pte
c_func
(paren
id|physpage
op_plus
id|pgprot_val
c_func
(paren
id|pgprot
)paren
)paren
)paren
suffix:semicolon
r_return
id|__pte
suffix:semicolon
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
DECL|macro|__pte_offset
mdefine_line|#define __pte_offset(address) &bslash;&n;&t;&t;((address &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address) ((pte_t *) pmd_page_kernel(*(dir)) + &bslash;&n;&t;&t;&t;__pte_offset(address))
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
multiline_comment|/* Encode and de-code a swap entry */
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(x)&t;&t;&t;(((x).val &gt;&gt; 1) &amp; 0x3f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(x)&t;&t;&t;((x).val &gt;&gt; 8)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type, offset)&t;&t;((swp_entry_t) { ((type) &lt;&lt; 1) | ((offset) &lt;&lt; 8) })
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val })
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range remap_page_range
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()   do { } while (0)
DECL|macro|check_pgt_cache
mdefine_line|#define check_pgt_cache()      do { } while (0)
macro_line|#endif /* _X86_64_PGTABLE_H */
eof
