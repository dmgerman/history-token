multiline_comment|/*&n; *  linux/include/asm-arm26/pgtable.h&n; *&n; *  Copyright (C) 2000-2002 Russell King&n; *  Copyright (C) 2003 Ian Molton&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _ASMARM_PGTABLE_H
DECL|macro|_ASMARM_PGTABLE_H
mdefine_line|#define _ASMARM_PGTABLE_H
macro_line|#include &lt;asm-generic/4level-fixup.h&gt;
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
multiline_comment|/*&n; * The table below defines the page protection levels that we insert into our&n; * Linux page table version.  These get translated into the best that the&n; * architecture can perform.  Note that on most ARM hardware:&n; *  1) We cannot do execute protection&n; *  2) If we could do execute protection, then read is implied&n; *  3) write implies read permissions&n; */
DECL|macro|__P000
mdefine_line|#define __P000  PAGE_NONE
DECL|macro|__P001
mdefine_line|#define __P001  PAGE_READONLY
DECL|macro|__P010
mdefine_line|#define __P010  PAGE_COPY
DECL|macro|__P011
mdefine_line|#define __P011  PAGE_COPY
DECL|macro|__P100
mdefine_line|#define __P100  PAGE_READONLY
DECL|macro|__P101
mdefine_line|#define __P101  PAGE_READONLY
DECL|macro|__P110
mdefine_line|#define __P110  PAGE_COPY
DECL|macro|__P111
mdefine_line|#define __P111  PAGE_COPY
DECL|macro|__S000
mdefine_line|#define __S000  PAGE_NONE
DECL|macro|__S001
mdefine_line|#define __S001  PAGE_READONLY
DECL|macro|__S010
mdefine_line|#define __S010  PAGE_SHARED
DECL|macro|__S011
mdefine_line|#define __S011  PAGE_SHARED
DECL|macro|__S100
mdefine_line|#define __S100  PAGE_READONLY
DECL|macro|__S101
mdefine_line|#define __S101  PAGE_READONLY
DECL|macro|__S110
mdefine_line|#define __S110  PAGE_SHARED
DECL|macro|__S111
mdefine_line|#define __S111  PAGE_SHARED
multiline_comment|/*&n; * PMD_SHIFT determines the size of the area a second-level page table can map&n; * PGDIR_SHIFT determines what a third-level page table entry can map&n; */
DECL|macro|PGD_SHIFT
mdefine_line|#define PGD_SHIFT&t;&t;25
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;&t;20
DECL|macro|PGD_SIZE
mdefine_line|#define PGD_SIZE                (1UL &lt;&lt; PGD_SHIFT)
DECL|macro|PGD_MASK
mdefine_line|#define PGD_MASK                (~(PGD_SIZE-1))
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE                (1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK                (~(PMD_SIZE-1))
multiline_comment|/* The kernel likes to use these names for the above (ick) */
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE PGD_SIZE
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK PGD_MASK
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD            32
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD            1
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE            32
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR       1
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD       ((TASK_SIZE/PGD_SIZE) - FIRST_USER_PGD_NR)
singleline_comment|// FIXME - WTF?
DECL|macro|LIBRARY_TEXT_START
mdefine_line|#define LIBRARY_TEXT_START&t;0x0c000000
macro_line|#ifndef __ASSEMBLY__
r_extern
r_void
id|__pte_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_void
id|__pmd_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
suffix:semicolon
r_extern
r_void
id|__pgd_error
c_func
(paren
r_const
r_char
op_star
id|file
comma
r_int
id|line
comma
r_int
r_int
id|val
)paren
suffix:semicolon
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(pte)&t;&t;__pte_error(__FILE__, __LINE__, pte_val(pte))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(pmd)&t;&t;__pmd_error(__FILE__, __LINE__, pmd_val(pmd))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(pgd)&t;&t;__pgd_error(__FILE__, __LINE__, pgd_val(pgd))
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
r_extern
r_struct
id|page
op_star
id|empty_zero_page
suffix:semicolon
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;(empty_zero_page)
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(pte)&t;&t;(pte_val(pte) &gt;&gt; PAGE_SHIFT)
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)           (pfn_to_page(pte_pfn(pte)))
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn,prot)&t;(__pte(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot)))
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x)&t;&t;((x) &gt;&gt; (20 - PAGE_SHIFT))
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page,prot)&t;pfn_pte(page_to_pfn(page),prot)
DECL|macro|page_pte_prot
mdefine_line|#define page_pte_prot(page,prot)&t;mk_pte(page, prot)
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;&t;mk_pte(page, __pgprot(0))
multiline_comment|/*&n; * Terminology: PGD = Page Directory, PMD = Page Middle Directory,&n; *              PTE = Page Table Entry&n; *&n; * on arm26 we have no 2nd level page table. we simulate this by removing the&n; * PMD.&n; *&n; * pgd_none is 0 to prevernt pmd_alloc() calling __pmd_alloc(). This causes it&n; * to return pmd_offset(pgd,addr) which is a pointer to the pgd (IOW, a no-op).&n; *&n; * however, to work this way, whilst we are allocating 32 pgds, containing 32&n; * PTEs, the actual work is done on the PMDs, thus:&n; *&n; * instead of  mm-&gt;pgd-&gt;pmd-&gt;pte&n; * we have     mm-&gt;pgdpmd-&gt;pte&n; *&n; * IOW, think of PGD operations and PMD ones as being the same thing, just&n; * that PGD stuff deals with the mm_struct side of things, wheras PMD stuff&n; * deals with the pte side of things.&n; *&n; * additionally, we store some bits in the PGD and PTE pointers: &n; * PGDs:&n; *   o The lowest (1) bit of the PGD is to determine if it is present or swap.&n; *   o The 2nd bit of the PGD is unused and must be zero.&n; *   o The top 6 bits of the PGD must be zero. &n; * PTEs:&n; *   o The lower 5 bits of a pte are flags. bit 1 is the &squot;present&squot; flag. The&n; *     others determine the pages attributes.&n; *&n; * the pgd_val, pmd_val, and pte_val macros seem to be private to our code.&n; * They get the RAW value of the PGD/PMD/PTE entry, including our flags&n; * encoded into the pointers.&n; * &n; * The pgd_offset, pmd_offset, and pte_offset macros are used by the kernel,&n; * so they shouldnt have our flags attached.&n; *&n; * If you understood that, feel free to explain it to me...&n; *&n; */
DECL|macro|_PMD_PRESENT
mdefine_line|#define _PMD_PRESENT     (0x01)
multiline_comment|/* These definitions allow us to optimise out stuff like pmd_alloc() */
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(0) 
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;(0)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(1)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)&t;&t;do { } while (0)
multiline_comment|/* Whilst these handle our actual &squot;page directory&squot; (the agglomeration of pgd and pmd)&n; */
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)           (!pmd_val(pmd))
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)            ((pmd_val(pmd) &amp; 0xfc000002))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd)        (pmd_val(pmd) &amp; _PMD_PRESENT)
DECL|macro|set_pmd
mdefine_line|#define set_pmd(pmd_ptr, pmd)   ((*(pmd_ptr)) = (pmd))
DECL|macro|pmd_clear
mdefine_line|#define pmd_clear(pmdp)         set_pmd(pmdp, __pmd(0))
multiline_comment|/* and these handle our pte tables */
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)           (!pte_val(pte))
DECL|macro|pte_present
mdefine_line|#define pte_present(pte)        (pte_val(pte) &amp; _PAGE_PRESENT)
DECL|macro|set_pte
mdefine_line|#define set_pte(pte_ptr, pte)   ((*(pte_ptr)) = (pte))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(ptep)         set_pte((ptep), __pte(0))
multiline_comment|/* macros to ease the getting of pointers to stuff... */
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, addr)&t;((pgd_t *)(mm)-&gt;pgd        + __pgd_index(addr))
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(pgd, addr)&t;((pmd_t *)(pgd))
DECL|macro|pte_offset
mdefine_line|#define pte_offset(pmd, addr)   ((pte_t *)pmd_page(*(pmd)) + __pte_index(addr))
multiline_comment|/* there is no __pmd_index as we dont use pmds */
DECL|macro|__pgd_index
mdefine_line|#define __pgd_index(addr)&t;((addr) &gt;&gt; PGD_SHIFT)
DECL|macro|__pte_index
mdefine_line|#define __pte_index(addr)&t;(((addr) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
multiline_comment|/* Keep the kernel happy */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(addr)         __pgd_index(addr)
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(addr)&t;(pgd_offset(&amp;init_mm, addr))
multiline_comment|/*&n; * The vmalloc() routines leaves a hole of 4kB between each vmalloced&n; * area for the same reason. ;) FIXME: surely 1 page not 4k ?&n; */
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START     0x01a00000
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END       0x01c00000
multiline_comment|/* Is pmd_page supposed to return a pointer to a page in some arches? ours seems to&n; * return a pointer to memory (no special alignment)&n; */
DECL|macro|pmd_page
mdefine_line|#define pmd_page(pmd)  ((struct page *)(pmd_val((pmd)) &amp; ~_PMD_PRESENT))
DECL|macro|pmd_page_kernel
mdefine_line|#define pmd_page_kernel(pmd) ((pte_t *)(pmd_val((pmd)) &amp; ~_PMD_PRESENT))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir,addr)     (pmd_page_kernel(*(dir)) + __pte_index(addr))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir,addr)        (pmd_page_kernel(*(dir)) + __pte_index(addr))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir,addr) (pmd_page_kernel(*(dir)) + __pte_index(addr))
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte)                  do { } while (0)
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte)           do { } while (0)
DECL|macro|_PAGE_PRESENT
mdefine_line|#define _PAGE_PRESENT   0x01
DECL|macro|_PAGE_READONLY
mdefine_line|#define _PAGE_READONLY  0x02
DECL|macro|_PAGE_NOT_USER
mdefine_line|#define _PAGE_NOT_USER  0x04
DECL|macro|_PAGE_OLD
mdefine_line|#define _PAGE_OLD       0x08
DECL|macro|_PAGE_CLEAN
mdefine_line|#define _PAGE_CLEAN     0x10
singleline_comment|// an old page has never been read.
singleline_comment|// a clean page has never been written.
multiline_comment|/*                               -- present --   -- !dirty --  --- !write ---   ---- !user --- */
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE       __pgprot(_PAGE_PRESENT | _PAGE_CLEAN | _PAGE_READONLY | _PAGE_NOT_USER)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED     __pgprot(_PAGE_PRESENT | _PAGE_CLEAN                                  )
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY       __pgprot(_PAGE_PRESENT | _PAGE_CLEAN | _PAGE_READONLY                 )
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY   __pgprot(_PAGE_PRESENT | _PAGE_CLEAN | _PAGE_READONLY                 )
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL     __pgprot(_PAGE_PRESENT                                | _PAGE_NOT_USER)
DECL|macro|_PAGE_CHG_MASK
mdefine_line|#define _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_OLD | _PAGE_CLEAN)
multiline_comment|/*&n; * The following only work if pte_present() is true.&n; * Undefined behaviour if not..&n; */
DECL|macro|pte_read
mdefine_line|#define pte_read(pte)                   (!(pte_val(pte) &amp; _PAGE_NOT_USER))
DECL|macro|pte_write
mdefine_line|#define pte_write(pte)                  (!(pte_val(pte) &amp; _PAGE_READONLY))
DECL|macro|pte_exec
mdefine_line|#define pte_exec(pte)                   (!(pte_val(pte) &amp; _PAGE_NOT_USER))
DECL|macro|pte_dirty
mdefine_line|#define pte_dirty(pte)                  (!(pte_val(pte) &amp; _PAGE_CLEAN))
DECL|macro|pte_young
mdefine_line|#define pte_young(pte)                  (!(pte_val(pte) &amp; _PAGE_OLD))
singleline_comment|//ONLY when !pte_present() I think. nicked from arm32 (FIXME!)
DECL|macro|pte_file
mdefine_line|#define pte_file(pte)                   (!(pte_val(pte) &amp; _PAGE_OLD))
DECL|macro|PTE_BIT_FUNC
mdefine_line|#define PTE_BIT_FUNC(fn,op)                     &bslash;&n;static inline pte_t pte_##fn(pte_t pte) { pte_val(pte) op; return pte; }
id|PTE_BIT_FUNC
c_func
(paren
id|wrprotect
comma
op_or_assign
id|_PAGE_READONLY
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkwrite
comma
op_and_assign
op_complement
id|_PAGE_READONLY
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|exprotect
comma
op_or_assign
id|_PAGE_NOT_USER
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkexec
comma
op_and_assign
op_complement
id|_PAGE_NOT_USER
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkclean
comma
op_or_assign
id|_PAGE_CLEAN
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkdirty
comma
op_and_assign
op_complement
id|_PAGE_CLEAN
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkold
comma
op_or_assign
id|_PAGE_OLD
)paren
suffix:semicolon
id|PTE_BIT_FUNC
c_func
(paren
id|mkyoung
comma
op_and_assign
op_complement
id|_PAGE_OLD
)paren
suffix:semicolon
multiline_comment|/*&n; * We don&squot;t store cache state bits in the page table here. FIXME - or do we?&n; */
DECL|macro|pgprot_noncached
mdefine_line|#define pgprot_noncached(prot)  (prot)
DECL|macro|pgprot_writecombine
mdefine_line|#define pgprot_writecombine(prot) (prot) 
singleline_comment|//FIXME - is a no-op?
r_extern
r_void
id|pgtable_cache_init
c_func
(paren
r_void
)paren
suffix:semicolon
singleline_comment|//FIXME - nicked from arm32 and brutally hacked. probably wrong.
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(x) (pte_val(x) &gt;&gt; 2)
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(x) __pte(((x) &lt;&lt; 2) &amp; ~_PAGE_OLD)
singleline_comment|//FIXME - next line borrowed from arm32. is it right?
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS       30
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
r_extern
id|pgd_t
id|swapper_pg_dir
(braket
id|PTRS_PER_PGD
)braket
suffix:semicolon
multiline_comment|/* Encode and decode a swap entry.&n; *&n; * We support up to 32GB of swap on 4k machines&n; */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;(((x).val &gt;&gt; 2) &amp; 0x7f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;((x).val &gt;&gt; 9)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type,offset) ((swp_entry_t) { ((type) &lt;&lt; 2) | ((offset) &lt;&lt; 9) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(swp)&t;((pte_t) { (swp).val })
multiline_comment|/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
multiline_comment|/* FIXME: this is not correct */
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
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
macro_line|#include &lt;asm-generic/pgtable.h&gt;
multiline_comment|/*&n; * remap a physical address `phys&squot; of size `size&squot; with page protection `prot&squot;&n; * into virtual address `from&squot;&n; */
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma,from,phys,size,prot) &bslash;&n;&t;&t;remap_pfn_range(vma, from, (phys) &gt;&gt; PAGE_SHIFT, size, prot)
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASMARM_PGTABLE_H */
eof
