macro_line|#ifndef _PPC64_PGTABLE_H
DECL|macro|_PPC64_PGTABLE_H
mdefine_line|#define _PPC64_PGTABLE_H
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
multiline_comment|/*&n; * This file contains the functions and defines necessary to modify and use&n; * the ppc64 hashed page table.&n; */
macro_line|#ifndef __ASSEMBLY__
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/stddef.h&gt;
macro_line|#include &lt;asm/processor.h&gt;&t;&t;/* For TASK_SIZE */
macro_line|#include &lt;asm/mmu.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
macro_line|#endif /* __ASSEMBLY__ */
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
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(1024)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|EADDR_SIZE
mdefine_line|#define EADDR_SIZE (PTE_INDEX_SIZE + PMD_INDEX_SIZE + &bslash;&n;                    PGD_INDEX_SIZE + PAGE_SHIFT) 
multiline_comment|/*&n; * Size of EA range mapped by our pagetables.&n; */
DECL|macro|PGTABLE_EA_BITS
mdefine_line|#define PGTABLE_EA_BITS&t;41
DECL|macro|PGTABLE_EA_MASK
mdefine_line|#define PGTABLE_EA_MASK&t;((1UL&lt;&lt;PGTABLE_EA_BITS)-1)
multiline_comment|/*&n; * Define the address range of the vmalloc VM area.&n; */
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START (0xD000000000000000ul)
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END   (VMALLOC_START + PGTABLE_EA_MASK)
multiline_comment|/*&n; * Define the address range of the imalloc VM area.&n; * (used for ioremap)&n; */
DECL|macro|IMALLOC_START
mdefine_line|#define IMALLOC_START     (ioremap_bot)
DECL|macro|IMALLOC_VMADDR
mdefine_line|#define IMALLOC_VMADDR(x) ((unsigned long)(x))
DECL|macro|PHBS_IO_BASE
mdefine_line|#define PHBS_IO_BASE  &t;  (0xE000000000000000ul)&t;/* Reserve 2 gigs for PHBs */
DECL|macro|IMALLOC_BASE
mdefine_line|#define IMALLOC_BASE      (0xE000000080000000ul)  
DECL|macro|IMALLOC_END
mdefine_line|#define IMALLOC_END       (IMALLOC_BASE + PGTABLE_EA_MASK)
multiline_comment|/*&n; * Define the user address range&n; */
DECL|macro|USER_START
mdefine_line|#define USER_START (0UL)
DECL|macro|USER_END
mdefine_line|#define USER_END   (USER_START + PGTABLE_EA_MASK)
multiline_comment|/*&n; * Bits in a linux-style PTE.  These match the bits in the&n; * (hardware-defined) PowerPC PTE as closely as possible.&n; */
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT&t;0x0001 /* software: pte contains a translation */
DECL|macro|_PAGE_USER
mdefine_line|#define _PAGE_USER&t;0x0002 /* matches one of the PP bits */
DECL|macro|_PAGE_FILE
mdefine_line|#define _PAGE_FILE&t;0x0002 /* (!present only) software: pte holds file offset */
DECL|macro|_PAGE_RW
mdefine_line|#define _PAGE_RW&t;0x0004 /* software: user write access allowed */
DECL|macro|_PAGE_GUARDED
mdefine_line|#define _PAGE_GUARDED&t;0x0008
DECL|macro|_PAGE_COHERENT
mdefine_line|#define _PAGE_COHERENT&t;0x0010 /* M: enforce memory coherence (SMP systems) */
DECL|macro|_PAGE_NO_CACHE
mdefine_line|#define _PAGE_NO_CACHE&t;0x0020 /* I: cache inhibit */
DECL|macro|_PAGE_WRITETHRU
mdefine_line|#define _PAGE_WRITETHRU&t;0x0040 /* W: cache write-through */
DECL|macro|_PAGE_DIRTY
mdefine_line|#define _PAGE_DIRTY&t;0x0080 /* C: page changed */
DECL|macro|_PAGE_ACCESSED
mdefine_line|#define _PAGE_ACCESSED&t;0x0100 /* R: page referenced */
DECL|macro|_PAGE_EXEC
mdefine_line|#define _PAGE_EXEC&t;0x0200 /* software: i-cache coherence required */
DECL|macro|_PAGE_HASHPTE
mdefine_line|#define _PAGE_HASHPTE&t;0x0400 /* software: pte has an associated HPTE */
DECL|macro|_PAGE_BUSY
mdefine_line|#define _PAGE_BUSY&t;0x0800 /* software: PTE &amp; hash are busy */ 
DECL|macro|_PAGE_SECONDARY
mdefine_line|#define _PAGE_SECONDARY 0x8000 /* software: HPTE is in secondary group */
DECL|macro|_PAGE_GROUP_IX
mdefine_line|#define _PAGE_GROUP_IX  0x7000 /* software: HPTE index within group */
DECL|macro|_PAGE_HUGE
mdefine_line|#define _PAGE_HUGE&t;0x10000 /* 16MB page */
multiline_comment|/* Bits 0x7000 identify the index within an HPT Group */
DECL|macro|_PAGE_HPTEFLAGS
mdefine_line|#define _PAGE_HPTEFLAGS (_PAGE_BUSY | _PAGE_HASHPTE | _PAGE_SECONDARY | _PAGE_GROUP_IX)
multiline_comment|/* PAGE_MASK gives the right answer below, but only by accident */
multiline_comment|/* It should be preserving the high 48 bits and then specifically */
multiline_comment|/* preserving _PAGE_SECONDARY | _PAGE_GROUP_IX */
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK&t;(PAGE_MASK | _PAGE_ACCESSED | _PAGE_DIRTY | _PAGE_HPTEFLAGS)
DECL|macro|_PAGE_BASE
mdefine_line|#define _PAGE_BASE&t;(_PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_COHERENT)
DECL|macro|_PAGE_WRENABLE
mdefine_line|#define _PAGE_WRENABLE&t;(_PAGE_RW | _PAGE_DIRTY)
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
mdefine_line|#define ZERO_PAGE(vaddr) (virt_to_page(empty_zero_page))
macro_line|#endif /* __ASSEMBLY__ */
multiline_comment|/* shift to put page number into pte */
DECL|macro|PTE_SHIFT
mdefine_line|#define PTE_SHIFT (17)
multiline_comment|/* We allow 2^41 bytes of real memory, so we need 29 bits in the PMD&n; * to give the PTE page number.  The bottom two bits are for flags. */
DECL|macro|PMD_TO_PTEPAGE_SHIFT
mdefine_line|#define PMD_TO_PTEPAGE_SHIFT (2)
macro_line|#ifdef CONFIG_HUGETLB_PAGE
macro_line|#ifndef __ASSEMBLY__
r_int
id|hash_huge_page
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|access
comma
r_int
r_int
id|ea
comma
r_int
r_int
id|vsid
comma
r_int
id|local
)paren
suffix:semicolon
r_void
id|hugetlb_mm_free_pgd
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
macro_line|#endif /* __ASSEMBLY__ */
DECL|macro|HAVE_ARCH_UNMAPPED_AREA
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA
DECL|macro|HAVE_ARCH_UNMAPPED_AREA_TOPDOWN
mdefine_line|#define HAVE_ARCH_UNMAPPED_AREA_TOPDOWN
macro_line|#else
DECL|macro|hash_huge_page
mdefine_line|#define hash_huge_page(mm,a,ea,vsid,local)&t;-1
DECL|macro|hugetlb_mm_free_pgd
mdefine_line|#define hugetlb_mm_free_pgd(mm)&t;&t;&t;do {} while (0)
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; *&n; * mk_pte takes a (struct page *) as input&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page, pgprot)&t;pfn_pte(page_to_pfn(page), (pgprot))
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn,pgprot)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t pte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_val(pte) = ((unsigned long)(pfn) &lt;&lt; PTE_SHIFT) |   &t;&t;&bslash;&n;                        pgprot_val(pgprot);&t;&t;&t;&t;&bslash;&n;&t;pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|pte_modify
mdefine_line|#define pte_modify(_pte, newprot) &bslash;&n;  (__pte((pte_val(_pte) &amp; _PAGE_CHG_MASK) | pgprot_val(newprot)))
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)&t;&t;((pte_val(pte) &amp; ~_PAGE_HPTEFLAGS) == 0)
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)&t;(pte_val(pte) &amp; _PAGE_PRESENT)
multiline_comment|/* pte_clear moved to later in this file */
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)&t;&t;((unsigned long)((pte_val(x) &gt;&gt; PTE_SHIFT)))
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;pfn_to_page(pte_pfn(x))
DECL|macro|pmd_set
mdefine_line|#define pmd_set(pmdp, ptep) &t;&bslash;&n;&t;(pmd_val(*(pmdp)) = (__ba_to_bpn(ptep) &lt;&lt; PMD_TO_PTEPAGE_SHIFT))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_bad
mdefine_line|#define&t;pmd_bad(pmd)&t;&t;(pmd_val(pmd) == 0)
DECL|macro|pmd_present
mdefine_line|#define&t;pmd_present(pmd)&t;(pmd_val(pmd) != 0)
DECL|macro|pmd_clear
mdefine_line|#define&t;pmd_clear(pmdp)&t;&t;(pmd_val(*(pmdp)) = 0)
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd)&t;&bslash;&n;&t;(__bpn_to_ba(pmd_val(pmd) &gt;&gt; PMD_TO_PTEPAGE_SHIFT))
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
multiline_comment|/* to avoid overflow in free_pgtables we don&squot;t use PTRS_PER_PGD here */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address) (((address) &gt;&gt; (PGDIR_SHIFT)) &amp; 0x7ff)
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
DECL|function|pte_huge
r_static
r_inline
r_int
id|pte_huge
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
id|_PAGE_HUGE
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
DECL|function|pte_mkhuge
r_static
r_inline
id|pte_t
id|pte_mkhuge
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
id|_PAGE_HUGE
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
l_string|&quot;1:&t;ldarx&t;%0,0,%3&t;&t;# pte_update&bslash;n&bslash;&n;&t;andi.&t;%1,%0,%6&bslash;n&bslash;&n;&t;bne-&t;1b &bslash;n&bslash;&n;&t;andc&t;%1,%0,%4 &bslash;n&bslash;&n;&t;stdcx.&t;%1,0,%3 &bslash;n&bslash;&n;&t;bne-&t;1b&quot;
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
l_string|&quot;m&quot;
(paren
op_star
id|p
)paren
comma
l_string|&quot;i&quot;
(paren
id|_PAGE_BUSY
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
r_return
id|old
suffix:semicolon
)brace
multiline_comment|/* PTE updating functions, this function puts the PTE in the&n; * batch, doesn&squot;t actually triggers the hash flush immediately,&n; * you need to call flush_tlb_pending() to do that.&n; */
r_extern
r_void
id|hpte_update
c_func
(paren
id|pte_t
op_star
id|ptep
comma
r_int
r_int
id|pte
comma
r_int
id|wrprot
)paren
suffix:semicolon
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
r_int
r_int
id|old
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
(paren
id|_PAGE_ACCESSED
op_or
id|_PAGE_HASHPTE
)paren
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|old
op_assign
id|pte_update
c_func
(paren
id|ptep
comma
id|_PAGE_ACCESSED
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
op_amp
id|_PAGE_HASHPTE
)paren
(brace
id|hpte_update
c_func
(paren
id|ptep
comma
id|old
comma
l_int|0
)paren
suffix:semicolon
id|flush_tlb_pending
c_func
(paren
)paren
suffix:semicolon
)brace
r_return
(paren
id|old
op_amp
id|_PAGE_ACCESSED
)paren
op_ne
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * On RW/DIRTY bit transitions we can avoid flushing the hpte. For the&n; * moment we always flush but we need to fix hpte_update and test if the&n; * optimisation is worth it.&n; */
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
r_int
r_int
id|old
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
id|_PAGE_DIRTY
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
id|old
op_assign
id|pte_update
c_func
(paren
id|ptep
comma
id|_PAGE_DIRTY
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
op_amp
id|_PAGE_HASHPTE
)paren
id|hpte_update
c_func
(paren
id|ptep
comma
id|old
comma
l_int|0
)paren
suffix:semicolon
r_return
(paren
id|old
op_amp
id|_PAGE_DIRTY
)paren
op_ne
l_int|0
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
r_int
r_int
id|old
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pte_val
c_func
(paren
op_star
id|ptep
)paren
op_amp
id|_PAGE_RW
)paren
op_eq
l_int|0
)paren
r_return
suffix:semicolon
id|old
op_assign
id|pte_update
c_func
(paren
id|ptep
comma
id|_PAGE_RW
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
op_amp
id|_PAGE_HASHPTE
)paren
id|hpte_update
c_func
(paren
id|ptep
comma
id|old
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * We currently remove entries from the hashtable regardless of whether&n; * the entry was young or dirty. The generic routines only flush if the&n; * entry was young or dirty which is not good enough.&n; *&n; * We should be more intelligent about this but for the moment we override&n; * these functions and force a tlb flush unconditionally&n; */
DECL|macro|__HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
mdefine_line|#define __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
DECL|macro|ptep_clear_flush_young
mdefine_line|#define ptep_clear_flush_young(__vma, __address, __ptep)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __young = ptep_test_and_clear_young(__ptep);&t;&t;&bslash;&n;&t;__young;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
DECL|macro|__HAVE_ARCH_PTEP_CLEAR_DIRTY_FLUSH
mdefine_line|#define __HAVE_ARCH_PTEP_CLEAR_DIRTY_FLUSH
DECL|macro|ptep_clear_flush_dirty
mdefine_line|#define ptep_clear_flush_dirty(__vma, __address, __ptep)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __dirty = ptep_test_and_clear_dirty(__ptep);&t;&t;&bslash;&n;&t;flush_tlb_page(__vma, __address);&t;&t;&t;&t;&bslash;&n;&t;__dirty;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
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
r_int
r_int
id|old
op_assign
id|pte_update
c_func
(paren
id|ptep
comma
op_complement
l_int|0UL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
op_amp
id|_PAGE_HASHPTE
)paren
id|hpte_update
c_func
(paren
id|ptep
comma
id|old
comma
l_int|0
)paren
suffix:semicolon
r_return
id|__pte
c_func
(paren
id|old
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
r_int
r_int
id|old
op_assign
id|pte_update
c_func
(paren
id|ptep
comma
op_complement
l_int|0UL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|old
op_amp
id|_PAGE_HASHPTE
)paren
id|hpte_update
c_func
(paren
id|ptep
comma
id|old
comma
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * set_pte stores a linux PTE into the linux page table.&n; */
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
r_if
c_cond
(paren
id|pte_present
c_func
(paren
op_star
id|ptep
)paren
)paren
(brace
id|pte_clear
c_func
(paren
id|ptep
)paren
suffix:semicolon
id|flush_tlb_pending
c_func
(paren
)paren
suffix:semicolon
)brace
op_star
id|ptep
op_assign
id|__pte
c_func
(paren
id|pte_val
c_func
(paren
id|pte
)paren
)paren
op_amp
op_complement
id|_PAGE_HPTEFLAGS
suffix:semicolon
)brace
multiline_comment|/* Set the dirty and/or accessed bits atomically in a linux PTE, this&n; * function doesn&squot;t need to flush the hash entry&n; */
DECL|macro|__HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
mdefine_line|#define __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
DECL|function|__ptep_set_access_flags
r_static
r_inline
r_void
id|__ptep_set_access_flags
c_func
(paren
id|pte_t
op_star
id|ptep
comma
id|pte_t
id|entry
comma
r_int
id|dirty
)paren
(brace
r_int
r_int
id|bits
op_assign
id|pte_val
c_func
(paren
id|entry
)paren
op_amp
(paren
id|_PAGE_DIRTY
op_or
id|_PAGE_ACCESSED
op_or
id|_PAGE_RW
)paren
suffix:semicolon
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
l_string|&quot;1:&t;ldarx&t;%0,0,%4&bslash;n&bslash;&n;&t;&t;andi.&t;%1,%0,%6&bslash;n&bslash;&n;&t;&t;bne-&t;1b &bslash;n&bslash;&n;&t;&t;or&t;%0,%3,%0&bslash;n&bslash;&n;&t;&t;stdcx.&t;%0,0,%4&bslash;n&bslash;&n;&t;&t;bne-&t;1b&quot;
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
id|ptep
)paren
suffix:colon
l_string|&quot;r&quot;
(paren
id|bits
)paren
comma
l_string|&quot;r&quot;
(paren
id|ptep
)paren
comma
l_string|&quot;m&quot;
(paren
op_star
id|ptep
)paren
comma
l_string|&quot;i&quot;
(paren
id|_PAGE_BUSY
)paren
suffix:colon
l_string|&quot;cc&quot;
)paren
suffix:semicolon
)brace
DECL|macro|ptep_set_access_flags
mdefine_line|#define  ptep_set_access_flags(__vma, __address, __ptep, __entry, __dirty) &bslash;&n;&t;do {&t;&t;&t;&t;&t;&t;&t;&t;   &bslash;&n;&t;&t;__ptep_set_access_flags(__ptep, __entry, __dirty);&t;   &bslash;&n;&t;&t;flush_tlb_page_nohash(__vma, __address);&t;       &t;   &bslash;&n;&t;} while(0)
multiline_comment|/*&n; * Macro to mark a page protection value as &quot;uncacheable&quot;.&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached(prot)&t;(__pgprot(pgprot_val(prot) | _PAGE_NO_CACHE | _PAGE_GUARDED))
DECL|macro|pte_same
mdefine_line|#define pte_same(A,B)&t;(((pte_val(A) ^ pte_val(B)) &amp; ~_PAGE_HPTEFLAGS) == 0)
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
r_struct
id|mmu_gather
suffix:semicolon
r_void
id|hugetlb_free_pgtables
c_func
(paren
r_struct
id|mmu_gather
op_star
id|tlb
comma
r_struct
id|vm_area_struct
op_star
id|prev
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
multiline_comment|/*&n; * This gets called at the end of handling a page fault, when&n; * the kernel has put a new PTE into the page table for the process.&n; * We use it to put a corresponding HPTE into the hash table&n; * ahead of time, instead of waiting for the inevitable extra&n; * hash-table miss exception.&n; */
r_struct
id|vm_area_struct
suffix:semicolon
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
DECL|macro|__swp_type
mdefine_line|#define __swp_type(entry)&t;(((entry).val &gt;&gt; 1) &amp; 0x3f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(entry)&t;((entry).val &gt;&gt; 8)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type, offset) ((swp_entry_t) { ((type) &lt;&lt; 1) | ((offset) &lt;&lt; 8) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) &gt;&gt; PTE_SHIFT })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val &lt;&lt; PTE_SHIFT })
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(pte)&t;(pte_val(pte) &gt;&gt; PTE_SHIFT)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off)&t;((pte_t) {((off) &lt;&lt; PTE_SHIFT)|_PAGE_FILE})
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;(BITS_PER_LONG - PTE_SHIFT)
multiline_comment|/*&n; * kern_addr_valid is intended to indicate whether an address is a valid&n; * kernel address.  Most 32-bit archs define it as always true (like this)&n; * but most 64-bit archs actually perform a test.  What should we do here?&n; * The only use is in fs/ncpfs/dir.c&n; */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma, vaddr, paddr, size, prot)&t;&t;&bslash;&n;&t;&t;remap_pfn_range(vma, vaddr, (paddr) &gt;&gt; PAGE_SHIFT, size, prot)
r_void
id|pgtable_cache_init
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hpte_init_native
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|hpte_init_lpar
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
multiline_comment|/* imalloc region types */
DECL|macro|IM_REGION_UNUSED
mdefine_line|#define IM_REGION_UNUSED&t;0x1
DECL|macro|IM_REGION_SUBSET
mdefine_line|#define IM_REGION_SUBSET&t;0x2
DECL|macro|IM_REGION_EXISTS
mdefine_line|#define IM_REGION_EXISTS&t;0x4
DECL|macro|IM_REGION_OVERLAP
mdefine_line|#define IM_REGION_OVERLAP&t;0x8
DECL|macro|IM_REGION_SUPERSET
mdefine_line|#define IM_REGION_SUPERSET&t;0x10
r_extern
r_struct
id|vm_struct
op_star
id|im_get_free_area
c_func
(paren
r_int
r_int
id|size
)paren
suffix:semicolon
r_extern
r_struct
id|vm_struct
op_star
id|im_get_area
c_func
(paren
r_int
r_int
id|v_addr
comma
r_int
r_int
id|size
comma
r_int
id|region_type
)paren
suffix:semicolon
r_int
r_int
id|im_free
c_func
(paren
r_void
op_star
id|addr
)paren
suffix:semicolon
r_extern
r_int
id|pSeries_lpar_hpte_insert
c_func
(paren
r_int
r_int
id|hpte_group
comma
r_int
r_int
id|va
comma
r_int
r_int
id|prpn
comma
r_int
id|secondary
comma
r_int
r_int
id|hpteflags
comma
r_int
id|bolted
comma
r_int
id|large
)paren
suffix:semicolon
r_extern
r_int
id|native_hpte_insert
c_func
(paren
r_int
r_int
id|hpte_group
comma
r_int
r_int
id|va
comma
r_int
r_int
id|prpn
comma
r_int
id|secondary
comma
r_int
r_int
id|hpteflags
comma
r_int
id|bolted
comma
r_int
id|large
)paren
suffix:semicolon
multiline_comment|/*&n; * find_linux_pte returns the address of a linux pte for a given &n; * effective address and directory.  If not found, it returns zero.&n; */
DECL|function|find_linux_pte
r_static
r_inline
id|pte_t
op_star
id|find_linux_pte
c_func
(paren
id|pgd_t
op_star
id|pgdir
comma
r_int
r_int
id|ea
)paren
(brace
id|pgd_t
op_star
id|pg
suffix:semicolon
id|pmd_t
op_star
id|pm
suffix:semicolon
id|pte_t
op_star
id|pt
op_assign
l_int|NULL
suffix:semicolon
id|pte_t
id|pte
suffix:semicolon
id|pg
op_assign
id|pgdir
op_plus
id|pgd_index
c_func
(paren
id|ea
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pgd_none
c_func
(paren
op_star
id|pg
)paren
)paren
(brace
id|pm
op_assign
id|pmd_offset
c_func
(paren
id|pg
comma
id|ea
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pmd_present
c_func
(paren
op_star
id|pm
)paren
)paren
(brace
id|pt
op_assign
id|pte_offset_kernel
c_func
(paren
id|pm
comma
id|ea
)paren
suffix:semicolon
id|pte
op_assign
op_star
id|pt
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|pte_present
c_func
(paren
id|pte
)paren
)paren
id|pt
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_return
id|pt
suffix:semicolon
)brace
macro_line|#endif /* __ASSEMBLY__ */
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
macro_line|#endif /* _PPC64_PGTABLE_H */
eof
