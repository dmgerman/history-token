multiline_comment|/*&n; *  linux/include/asm-arm/pgtable.h&n; *&n; *  Copyright (C) 2000-2002 Russell King&n; *&n; * This program is free software; you can redistribute it and/or modify&n; * it under the terms of the GNU General Public License version 2 as&n; * published by the Free Software Foundation.&n; */
macro_line|#ifndef _ASMARM_PGTABLE_H
DECL|macro|_ASMARM_PGTABLE_H
mdefine_line|#define _ASMARM_PGTABLE_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/memory.h&gt;
macro_line|#include &lt;asm/proc-fns.h&gt;
macro_line|#include &lt;asm/arch/vmalloc.h&gt;
multiline_comment|/*&n; * PMD_SHIFT determines the size of the area a second-level page table can map&n; * PGDIR_SHIFT determines what a third-level page table entry can map&n; */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;&t;20
macro_line|#ifdef CONFIG_CPU_32
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;&t;21
macro_line|#else
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;&t;20
macro_line|#endif
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
macro_line|#endif /* !__ASSEMBLY__ */
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;&t;(~(PMD_SIZE-1))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;&t;(~(PGDIR_SIZE-1))
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;1
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;((TASK_SIZE/PGDIR_SIZE) - FIRST_USER_PGD_NR)
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
macro_line|#ifndef __ASSEMBLY__
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
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn,prot)&t;(__pte(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot)))
DECL|macro|pte_none
mdefine_line|#define pte_none(pte)&t;&t;(!pte_val(pte))
DECL|macro|pte_clear
mdefine_line|#define pte_clear(ptep)&t;&t;set_pte((ptep), __pte(0))
DECL|macro|pte_page
mdefine_line|#define pte_page(pte)&t;&t;(pfn_to_page(pte_pfn(pte)))
DECL|macro|pmd_none
mdefine_line|#define pmd_none(pmd)&t;&t;(!pmd_val(pmd))
DECL|macro|pmd_present
mdefine_line|#define pmd_present(pmd)&t;(pmd_val(pmd))
multiline_comment|/*&n; * Permanent address of a page. We never have highmem, so this is trivial.&n; */
DECL|macro|pages_to_mb
mdefine_line|#define pages_to_mb(x)&t;&t;((x) &gt;&gt; (20 - PAGE_SHIFT))
multiline_comment|/*&n; * Conversion functions: convert a page and protection to a page entry,&n; * and a page entry and page directory to the page they refer to.&n; */
DECL|macro|mk_pte
mdefine_line|#define mk_pte(page,prot)&t;pfn_pte(page_to_pfn(page),prot)
multiline_comment|/*&n; * The &quot;pgd_xxx()&quot; functions here are trivial for a folded two-level&n; * setup: the pgd is never bad, and a pmd always exists (as it&squot;s folded&n; * into the pgd entry)&n; */
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(0)
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;(0)
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(1)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)&t;&t;do { } while (0)
DECL|macro|set_pgd
mdefine_line|#define set_pgd(pgd,pgdp)&t;do { } while (0)
DECL|macro|page_pte_prot
mdefine_line|#define page_pte_prot(page,prot)&t;mk_pte(page, prot)
DECL|macro|page_pte
mdefine_line|#define page_pte(page)&t;&t;mk_pte(page, __pgprot(0))
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_index
mdefine_line|#define pgd_index(addr)&t;&t;((addr) &gt;&gt; PGDIR_SHIFT)
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm, addr)&t;((mm)-&gt;pgd+pgd_index(addr))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(addr)&t;pgd_offset(&amp;init_mm, addr)
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|macro|pmd_offset
mdefine_line|#define pmd_offset(dir, addr)&t;((pmd_t *)(dir))
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|__pte_index
mdefine_line|#define __pte_index(addr)&t;(((addr) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
macro_line|#include &lt;asm/proc/pgtable.h&gt;
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
macro_line|#include &lt;asm-generic/pgtable.h&gt;
multiline_comment|/*&n; * remap a physical address `phys&squot; of size `size&squot; with page protection `prot&squot;&n; * into virtual address `from&squot;&n; */
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range(vma,from,phys,size,prot) &bslash;&n;&t;&t;remap_page_range(vma,from,phys,size,prot)
DECL|typedef|pte_addr_t
r_typedef
id|pte_t
op_star
id|pte_addr_t
suffix:semicolon
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASMARM_PGTABLE_H */
eof
