macro_line|#ifndef _PPC64_PGTABLE_H
DECL|macro|_PPC64_PGTABLE_H
mdefine_line|#define _PPC64_PGTABLE_H
multiline_comment|/*&n; * This file contains the functions and defines necessary to modify and use&n; * the ppc64 hashed page table.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;asm/processor.h&gt;&t;&t;/* For TASK_SIZE */
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* Certain architectures need to do special things when pte&squot;s&n; * within a page table are directly modified.  Thus, the following&n; * hook is made available.&n; */
multiline_comment|/* PMD_SHIFT determines what a second-level page table entry can map */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;(PAGE_SHIFT + PAGE_SHIFT - 3)
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;(PAGE_SHIFT + (PAGE_SHIFT - 3) + (PAGE_SHIFT - 2))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * Entries per page directory level.  The PTE level must use a 64b record&n; * for each page table entry.  The PMD and PGD level use a 32b record for &n; * each entry by assuming that each entry is page aligned.&n; */
DECL|macro|PTE_INDEX_SIZE
mdefine_line|#define PTE_INDEX_SIZE  9
DECL|macro|PMD_INDEX_SIZE
mdefine_line|#define PMD_INDEX_SIZE  10
DECL|macro|PGD_INDEX_SIZE
mdefine_line|#define PGD_INDEX_SIZE  10
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;(1 &lt;&lt; PTE_INDEX_SIZE)
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;(1 &lt;&lt; PMD_INDEX_SIZE)
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;(1 &lt;&lt; PGD_INDEX_SIZE)
macro_line|#if 0
multiline_comment|/* DRENG / PPPBBB This is a compiler bug!!! */
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE / PGDIR_SIZE)
macro_line|#else
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(1024)
macro_line|#endif
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|EADDR_SIZE
mdefine_line|#define EADDR_SIZE (PTE_INDEX_SIZE + PMD_INDEX_SIZE + &bslash;&n;                    PGD_INDEX_SIZE + PAGE_SHIFT) 
multiline_comment|/*&n; * Define the address range of the vmalloc VM area.&n; */
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START (0xD000000000000000)
DECL|macro|VMALLOC_VMADDR
mdefine_line|#define VMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END   (VMALLOC_START + VALID_EA_BITS)
multiline_comment|/*&n; * Define the address range of the imalloc VM area.&n; * (used for ioremap)&n; */
DECL|macro|IMALLOC_START
mdefine_line|#define IMALLOC_START (ioremap_bot)
DECL|macro|IMALLOC_VMADDR
mdefine_line|#define IMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|IMALLOC_BASE
mdefine_line|#define IMALLOC_BASE  (0xE000000000000000)
DECL|macro|IMALLOC_END
mdefine_line|#define IMALLOC_END   (IMALLOC_BASE + VALID_EA_BITS)
multiline_comment|/*&n; * Define the address range mapped virt &lt;-&gt; physical&n; */
DECL|macro|KRANGE_START
mdefine_line|#define KRANGE_START KERNELBASE
DECL|macro|KRANGE_END
mdefine_line|#define KRANGE_END   (KRANGE_START + VALID_EA_BITS)
multiline_comment|/*&n; * Define the user address range&n; */
DECL|macro|USER_START
mdefine_line|#define USER_START (0UL)
DECL|macro|USER_END
mdefine_line|#define USER_END   (USER_START + VALID_EA_BITS)
multiline_comment|/*&n; * Bits in a linux-style PTE.  These match the bits in the&n; * (hardware-defined) PowerPC PTE as closely as possible.&n; */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x001UL&t;/* software: pte contains a translation */
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x002UL&t;/* matches one of the PP bits */
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW&t;0x004UL&t;/* software: user write access allowed */
DECL|macro|_PAGE_GUARDED
mdefine_line|#define _PAGE_GUARDED&t;0x008UL
DECL|macro|_PAGE_COHERENT
mdefine_line|#define _PAGE_COHERENT&t;0x010UL&t;/* M: enforce memory coherence (SMP systems) */
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define _PAGE_NO_CACHE&t;0x020UL&t;/* I: cache inhibit */
DECL|macro|_PAGE_WRITETHRU
mdefine_line|#define _PAGE_WRITETHRU&t;0x040UL&t;/* W: cache write-through */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x080UL&t;/* C: page changed */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x100UL&t;/* R: page referenced */
macro_line|#if 0
mdefine_line|#define _PAGE_HPTENOIX&t;0x200UL /* software: pte HPTE slot unknown */
macro_line|#endif
DECL|macro|_PAGE_HASHPTE
mdefine_line|#define _PAGE_HASHPTE&t;0x400UL&t;/* software: pte has an associated HPTE */
DECL|macro|_PAGE_EXEC
mdefine_line|#define _PAGE_EXEC&t;0x800UL&t;/* software: i-cache coherence required */
DECL|macro|_PAGE_SECONDARY
mdefine_line|#define _PAGE_SECONDARY 0x8000UL /* software: HPTE is in secondary group */
DECL|macro|_PAGE_GROUP_IX
mdefine_line|#define _PAGE_GROUP_IX  0x7000UL /* software: HPTE index within group */
multiline_comment|/* Bits 0x7000 identify the index within an HPT Group */
DECL|macro|_PAGE_HPTEFLAGS
mdefine_line|#define _PAGE_HPTEFLAGS (_PAGE_HASHPTE | _PAGE_SECONDARY | _PAGE_GROUP_IX)
multiline_comment|/* PAGE_MASK gives the right answer below, but only by accident */
multiline_comment|/* It should be preserving the high 48 bits and then specifically */
multiline_comment|/* preserving _PAGE_SECONDARY | _PAGE_GROUP_IX */
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY | _PAGE_HPTEFLAGS)
DECL|macro|_PAGE_BASE
mdefine_line|#define _PAGE_BASE&t;_PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_COHERENT
DECL|macro|_PAGE_WRENABLE
mdefine_line|#define _PAGE_WRENABLE&t;_PAGE_RW | _PAGE_DIRTY 
multiline_comment|/* __pgprot defined in asm-ppc64/page.h */
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(_PAGE_BASE | _PAGE_RW | _PAGE_USER)
DECL|macro|PAGE_SHARED_X
mdefine_line|#define PAGE_SHARED_X&t;__pgprot(_PAGE_BASE | _PAGE_RW | _PAGE_USER | _PAGE_EXEC)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(_PAGE_BASE | _PAGE_USER)
DECL|macro|PAGE_COPY_X
mdefine_line|#define PAGE_COPY_X&t;__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(_PAGE_BASE | _PAGE_USER)
DECL|macro|PAGE_READONLY_X
mdefine_line|#define PAGE_READONLY_X&t;__pgprot(_PAGE_BASE | _PAGE_USER | _PAGE_EXEC)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(_PAGE_BASE | _PAGE_WRENABLE)
DECL|macro|PAGE_KERNEL_CI
mdefine_line|#define PAGE_KERNEL_CI&t;__pgprot(_PAGE_PRESENT | _PAGE_ACCESSED | &bslash;&n;&t;&t;&t;       _PAGE_WRENABLE | _PAGE_NO_CACHE | _PAGE_GUARDED)
multiline_comment|/*&n; * The PowerPC can only do execute protection on a segment (256MB) basis,&n; * not on a page basis.  So we consider execute permission the same as read.&n; * Also, write permissions imply read permissions.&n; * This is the closest we can get..&n; */
DECL|macro|__P000
mdefine_line|#define __P000&t;PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001&t;PAGE_READONLY_X
DECL|macro|__P010
mdefine_line|#define __P010&t;PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011&t;PAGE_COPY_X
DECL|macro|__P100
mdefine_line|#define __P100&t;PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101&t;PAGE_READONLY_X
DECL|macro|__P110
mdefine_line|#define __P110&t;PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111&t;PAGE_COPY_X
DECL|macro|__S000
mdefine_line|#define __S000&t;PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001&t;PAGE_READONLY_X
DECL|macro|__S010
mdefine_line|#define __S010&t;PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011&t;PAGE_SHARED_X
DECL|macro|__S100
mdefine_line|#define __S100&t;PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101&t;PAGE_READONLY_X
DECL|macro|__S110
mdefine_line|#define __S110&t;PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111&t;PAGE_SHARED_X
macro_line|#ifndef __ASSEMBLY__
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
mdefine_line|#define ZERO_PAGE(vaddr) (mem_map + MAP_NR(empty_zero_page))
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* shift to put page number into pte */
DECL|macro|PTE_SHIFT
mdefine_line|#define PTE_SHIFT (16)
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; *&n; * mk_pte_phys takes a physical address as input &n; *&n; * mk_pte takes a (struct page *) as input&n; */
DECL|macro|mk_pte_phys
mdefine_line|#define mk_pte_phys(physpage,pgprot)                                      &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;pte_t pte;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;pte_val(pte) = (((physpage)&lt;&lt;(PTE_SHIFT-PAGE_SHIFT)) | pgprot_val(pgprot)); &bslash;&n;&t;pte;&t;&t;&t;&t;&t;&t;&t;          &bslash;&n;})
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page,pgprot)                                               &bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;pte_t pte;&t;&t;&t;&t;&t;&t;&t;  &bslash;&n;&t;pte_val(pte) = ((unsigned long)((page) - mem_map) &lt;&lt; PTE_SHIFT) |   &bslash;&n;                        pgprot_val(pgprot);                               &bslash;&n;&t;pte;&t;&t;&t;&t;&t;&t;&t;          &bslash;&n;})
DECL|macro|pte_modify
mdefine_line|#define pte_modify(_pte, newprot) &bslash;&n;  (__pte((pte_val(_pte) &amp; _PAGE_CHG_MASK) | pgprot_val(newprot)))
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)&t;&t;((pte_val(pte) &amp; ~_PAGE_HPTEFLAGS) == 0)
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;(pte_val(pte) &amp; _PAGE_PRESENT)
multiline_comment|/* pte_clear moved to later in this file */
DECL|macro|pte_pagenr
mdefine_line|#define pte_pagenr(x)&t;&t;((unsigned long)((pte_val(x) &gt;&gt; PTE_SHIFT)))
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;(mem_map+pte_pagenr(x))
DECL|macro|pmd_set
mdefine_line|#define pmd_set(pmdp, ptep) &t;(pmd_val(*(pmdp)) = (__ba_to_bpn(ptep)))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(pmd)&t;&t;((pmd_val(pmd)) == 0)
DECL|macro|pmd_present
mdefine_line|#define&t;pmd_present(pmd)&t;((pmd_val(pmd)) != 0)
DECL|macro|pmd_clear
mdefine_line|#define&t;pmd_clear(pmdp)&t;&t;(pmd_val(*(pmdp)) = 0)
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd)&t;(__bpn_to_ba(pmd_val(pmd)))
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)&t;&t;virt_to_page(pmd_page_kernel(pmd))
DECL|macro|pgd_set
mdefine_line|#define pgd_set(pgdp, pmdp)&t;(pgd_val(*(pgdp)) = (__ba_to_bpn(pmdp)))
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(!pgd_val(pgd))
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;((pgd_val(pgd)) == 0)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(pgd_val(pgd) != 0UL)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)&t;&t;(pgd_val(*(pgdp)) = 0UL)
DECL|macro|pgd_page
mdefine_line|#define pgd_page(pgd)&t;&t;(__bpn_to_ba(pgd_val(pgd))) 
multiline_comment|/* &n; * Find an entry in a page-table-directory.  We combine the address region &n; * (the high order N bits) and the pgd portion of the address.&n; */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) (((address) &gt;&gt; (PGDIR_SHIFT)) &amp; (PTRS_PER_PGD -1))
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, address)&t; ((mm)-&gt;pgd + pgd_index(address))
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir,addr) &bslash;&n;  ((pmd_t *) pgd_page(*(dir)) + (((addr) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD - 1)))
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir,addr) &bslash;&n;  ((pte_t *) pmd_page_kernel(*(dir)) + (((addr) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1)))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir,addr)&t;pte_offset_kernel((dir), (addr))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir,addr)&t;pte_offset_kernel((dir), (addr))
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte)&t;&t;&t;do { } while(0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte)&t;&t;do { } while(0)
multiline_comment|/* to find an entry in a kernel page-table-directory */
multiline_comment|/* This now only contains the vmalloc pages */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
multiline_comment|/* to find an entry in the ioremap page-table-directory */
DECL|macro|pgd_offset_i
mdefine_line|#define pgd_offset_i(address) (ioremap_pgd + pgd_index(address))
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x)&t;&t;((x) &gt;&gt; (20-PAGE_SHIFT))
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
id|_PAGE_USER
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
id|_PAGE_RW
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
DECL|function|pte_uncache
r_static
r_inline
r_void
id|pte_uncache
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
id|_PAGE_NO_CACHE
suffix:semicolon
)brace
DECL|function|pte_cache
r_static
r_inline
r_void
id|pte_cache
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
id|_PAGE_NO_CACHE
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
id|_PAGE_RW
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
id|_PAGE_DIRTY
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
id|_PAGE_ACCESSED
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
id|pte_val
c_func
(paren
id|pte
)paren
op_or_assign
id|_PAGE_USER
op_or
id|_PAGE_EXEC
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
multiline_comment|/* Atomic PTE updates */
DECL|function|pte_update
r_static
r_inline
r_int
r_int
id|pte_update
c_func
(paren
id|pte_t
op_star
id|p
comma
r_int
r_int
id|clr
comma
r_int
r_int
id|set
)paren
(brace
r_int
r_int
id|old
comma
id|tmp
suffix:semicolon
id|__asm__
id|__volatile__
c_func
(paren
l_string|&quot;&bslash;n&bslash;&n;1:&t;ldarx&t;%0,0,%3&t;&bslash;n&bslash;&n;&t;andc&t;%1,%0,%4 &bslash;n&bslash;&n;&t;or&t;%1,%1,%5 &bslash;n&bslash;&n;&t;stdcx.&t;%1,0,%3 &bslash;n&bslash;&n;&t;bne-&t;1b&quot;
suffix:colon
l_string|&quot;=&amp;r&quot;
(paren
id|old
)paren
comma
l_string|&quot;=&amp;r&quot;
(paren
id|tmp
)paren
comma
l_string|&quot;=m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|p
)paren
comma
l_string|&quot;r&quot;
(paren
id|clr
)paren
comma
l_string|&quot;r&quot;
(paren
id|set
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|old
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
(paren
id|pte_update
c_func
(paren
id|ptep
comma
id|_PAGE_ACCESSED
comma
l_int|0
)paren
op_amp
id|_PAGE_ACCESSED
)paren
op_ne
l_int|0
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
(paren
id|pte_update
c_func
(paren
id|ptep
comma
id|_PAGE_DIRTY
comma
l_int|0
)paren
op_amp
id|_PAGE_DIRTY
)paren
op_ne
l_int|0
suffix:semicolon
)brace
DECL|function|ptep_get_and_clear
r_static
r_inline
id|pte_t
id|ptep_get_and_clear
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_return
id|__pte
c_func
(paren
id|pte_update
c_func
(paren
id|ptep
comma
op_complement
id|_PAGE_HPTEFLAGS
comma
l_int|0
)paren
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
id|pte_update
c_func
(paren
id|ptep
comma
id|_PAGE_RW
comma
l_int|0
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
id|pte_update
c_func
(paren
id|ptep
comma
l_int|0
comma
id|_PAGE_DIRTY
)paren
suffix:semicolon
)brace
DECL|macro|pte_same
mdefine_line|#define pte_same(A,B)&t;(((pte_val(A) ^ pte_val(B)) &amp; ~_PAGE_HPTEFLAGS) == 0)
multiline_comment|/*&n; * set_pte stores a linux PTE into the linux page table.&n; * On machines which use an MMU hash table we avoid changing the&n; * _PAGE_HASHPTE bit.&n; */
DECL|function|set_pte
r_static
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
id|pte
)paren
(brace
id|pte_update
c_func
(paren
id|ptep
comma
op_complement
id|_PAGE_HPTEFLAGS
comma
id|pte_val
c_func
(paren
id|pte
)paren
op_amp
op_complement
id|_PAGE_HPTEFLAGS
)paren
suffix:semicolon
)brace
DECL|function|pte_clear
r_static
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
id|pte_update
c_func
(paren
id|ptep
comma
op_complement
id|_PAGE_HPTEFLAGS
comma
l_int|0
)paren
suffix:semicolon
)brace
r_extern
r_int
r_int
id|va_to_phys
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
id|pte_t
op_star
id|va_to_pte
c_func
(paren
r_int
r_int
id|address
)paren
suffix:semicolon
r_extern
r_int
r_int
id|ioremap_bot
comma
id|ioremap_base
suffix:semicolon
DECL|macro|USER_PGD_PTRS
mdefine_line|#define USER_PGD_PTRS (PAGE_OFFSET &gt;&gt; PGDIR_SHIFT)
DECL|macro|KERNEL_PGD_PTRS
mdefine_line|#define KERNEL_PGD_PTRS (PTRS_PER_PGD-USER_PGD_PTRS)
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %016lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08x.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08x.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
l_int|1024
)braket
suffix:semicolon
r_extern
id|pgd_t
id|ioremap_dir
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
multiline_comment|/*&n; * This gets called at the end of handling a page fault, when&n; * the kernel has put a new PTE into the page table for the process.&n; * We use it to put a corresponding HPTE into the hash table&n; * ahead of time, instead of waiting for the inevitable extra&n; * hash-table miss exception.&n; */
r_extern
r_void
id|update_mmu_cache
c_func
(paren
r_struct
id|vm_area_struct
op_star
comma
r_int
r_int
comma
id|pte_t
)paren
suffix:semicolon
multiline_comment|/* Encode and de-code a swap entry */
DECL|macro|SWP_TYPE
mdefine_line|#define SWP_TYPE(entry)&t;&t;&t;(((entry).val &gt;&gt; 1) &amp; 0x3f)
DECL|macro|SWP_OFFSET
mdefine_line|#define SWP_OFFSET(entry)&t;&t;((entry).val &gt;&gt; 8)
DECL|macro|SWP_ENTRY
mdefine_line|#define SWP_ENTRY(type, offset)&t;&t;((swp_entry_t) { ((type) &lt;&lt; 1) | ((offset) &lt;&lt; 8) })
DECL|macro|pte_to_swp_entry
mdefine_line|#define pte_to_swp_entry(pte)&t;&t;((swp_entry_t) { pte_val(pte) &gt;&gt; PTE_SHIFT })
DECL|macro|swp_entry_to_pte
mdefine_line|#define swp_entry_to_pte(x)&t;&t;((pte_t) { (x).val &lt;&lt; PTE_SHIFT })
multiline_comment|/*&n; * kern_addr_valid is intended to indicate whether an address is a valid&n; * kernel address.  Most 32-bit archs define it as always true (like this)&n; * but most 64-bit archs actually perform a test.  What should we do here?&n; * The only use is in fs/ncpfs/dir.c&n; */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range remap_page_range 
multiline_comment|/*&n; * No page table caches to initialise&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
r_extern
r_void
id|updateBoltedHptePP
c_func
(paren
r_int
r_int
id|newpp
comma
r_int
r_int
id|ea
)paren
suffix:semicolon
r_extern
r_void
id|hpte_init_pSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hpte_init_iSeries
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|make_pte
c_func
(paren
id|HPTE
op_star
id|htab
comma
r_int
r_int
id|va
comma
r_int
r_int
id|pa
comma
r_int
id|mode
comma
r_int
r_int
id|hash_mask
comma
r_int
id|large
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
macro_line|#endif /* _PPC64_PGTABLE_H */
eof
