multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000, 2003 Ralf Baechle&n; * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PGTABLE_32_H
DECL|macro|_ASM_PGTABLE_32_H
mdefine_line|#define _ASM_PGTABLE_32_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
macro_line|#include &lt;asm/fixmap.h&gt;
multiline_comment|/*&n; * - add_wired_entry() add a fixed TLB entry, and move wired register&n; */
r_extern
r_void
id|add_wired_entry
c_func
(paren
r_int
r_int
id|entrylo0
comma
r_int
r_int
id|entrylo1
comma
r_int
r_int
id|entryhi
comma
r_int
r_int
id|pagemask
)paren
suffix:semicolon
multiline_comment|/*&n; * - add_temporary_entry() add a temporary TLB entry. We use TLB entries&n; *&t;starting at the top and working down. This is for populating the&n; *&t;TLB before trap_init() puts the TLB miss handler in place. It&n; *&t;should be used only for entries matching the actual page tables,&n; *&t;to prevent inconsistencies.&n; */
r_extern
r_int
id|add_temporary_entry
c_func
(paren
r_int
r_int
id|entrylo0
comma
r_int
r_int
id|entrylo1
comma
r_int
r_int
id|entryhi
comma
r_int
r_int
id|pagemask
)paren
suffix:semicolon
multiline_comment|/* Basically we have the same two-level (which is the logical three level&n; * Linux page table layout folded) page tables as the i386.  Some day&n; * when we have proper page coloring support we can have a 1% quicker&n; * tlb refill handling mechanism, but for now it is a bit slower but&n; * works even with the cache aliasing problem the R4k and above have.&n; */
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
macro_line|#ifdef CONFIG_64BIT_PHYS_ADDR
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;21
macro_line|#else
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;22
macro_line|#endif
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;PMD_SHIFT
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * Entries per page directory level: we use two-level, so&n; * we don&squot;t really have any PMD directory physically.&n; */
macro_line|#ifdef CONFIG_64BIT_PHYS_ADDR
DECL|macro|PGD_ORDER
mdefine_line|#define PGD_ORDER&t;1
DECL|macro|PMD_ORDER
mdefine_line|#define PMD_ORDER&t;0
DECL|macro|PTE_ORDER
mdefine_line|#define PTE_ORDER&t;0
macro_line|#else
DECL|macro|PGD_ORDER
mdefine_line|#define PGD_ORDER&t;0
DECL|macro|PMD_ORDER
mdefine_line|#define PMD_ORDER&t;0
DECL|macro|PTE_ORDER
mdefine_line|#define PTE_ORDER&t;0
macro_line|#endif
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;((PAGE_SIZE &lt;&lt; PGD_ORDER) / sizeof(pgd_t))
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;1
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;((PAGE_SIZE &lt;&lt; PTE_ORDER) / sizeof(pte_t))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(0x80000000UL/PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START     KSEG2
macro_line|#ifdef CONFIG_HIGHMEM
DECL|macro|VMALLOC_END
macro_line|# define VMALLOC_END&t;(PKMAP_BASE-2*PAGE_SIZE)
macro_line|#else
DECL|macro|VMALLOC_END
macro_line|# define VMALLOC_END&t;(FIXADDR_START-2*PAGE_SIZE)
macro_line|#endif
macro_line|#ifdef CONFIG_64BIT_PHYS_ADDR
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %016Lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
macro_line|#else
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %08lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
macro_line|#endif
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %08lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
r_extern
r_void
id|load_pgd
c_func
(paren
r_int
r_int
id|pg_dir
)paren
suffix:semicolon
r_extern
id|pmd_t
id|invalid_pte_table
(braket
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pmd_t
)paren
)braket
suffix:semicolon
multiline_comment|/*&n; * Empty pgd/pmd entries point to the invalid_pte_table.&n; */
DECL|function|pmd_none
r_static
r_inline
r_int
id|pmd_none
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
id|pmd_val
c_func
(paren
id|pmd
)paren
op_eq
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
)brace
DECL|macro|pmd_bad
mdefine_line|#define pmd_bad(pmd)&t;&t;(pmd_val(pmd) &amp; ~PAGE_MASK)
DECL|function|pmd_present
r_static
r_inline
r_int
id|pmd_present
c_func
(paren
id|pmd_t
id|pmd
)paren
(brace
r_return
id|pmd_val
c_func
(paren
id|pmd
)paren
op_ne
(paren
r_int
r_int
)paren
id|invalid_pte_table
suffix:semicolon
)brace
DECL|function|pmd_clear
r_static
r_inline
r_void
id|pmd_clear
c_func
(paren
id|pmd_t
op_star
id|pmdp
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
r_int
r_int
)paren
id|invalid_pte_table
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
macro_line|#if defined(CONFIG_64BIT_PHYS_ADDR) &amp;&amp; defined(CONFIG_CPU_MIPS32)
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;pfn_to_page(pte_pfn(x))
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)&t;&t;((unsigned long)((x).pte_high &gt;&gt; 6))
r_static
r_inline
id|pte_t
DECL|function|pfn_pte
id|pfn_pte
c_func
(paren
r_int
r_int
id|pfn
comma
id|pgprot_t
id|prot
)paren
(brace
id|pte_t
id|pte
suffix:semicolon
id|pte.pte_high
op_assign
(paren
id|pfn
op_lshift
l_int|6
)paren
op_or
(paren
id|pgprot_val
c_func
(paren
id|prot
)paren
op_amp
l_int|0x3f
)paren
suffix:semicolon
id|pte.pte_low
op_assign
id|pgprot_val
c_func
(paren
id|prot
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
macro_line|#else
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;pfn_to_page(pte_pfn(x))
macro_line|#ifdef CONFIG_CPU_VR41XX
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)&t;&t;((unsigned long)((x).pte &gt;&gt; (PAGE_SHIFT + 2)))
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot)&t;__pte(((pfn) &lt;&lt; (PAGE_SHIFT + 2)) | pgprot_val(prot))
macro_line|#else
DECL|macro|pte_pfn
mdefine_line|#define pte_pfn(x)&t;&t;((unsigned long)((x).pte &gt;&gt; PAGE_SHIFT))
DECL|macro|pfn_pte
mdefine_line|#define pfn_pte(pfn, prot)&t;__pte(((pfn) &lt;&lt; PAGE_SHIFT) | pgprot_val(prot))
macro_line|#endif
macro_line|#endif /* defined(CONFIG_64BIT_PHYS_ADDR) &amp;&amp; defined(CONFIG_CPU_MIPS32) */
DECL|macro|__pgd_offset
mdefine_line|#define __pgd_offset(address)&t;pgd_index(address)
DECL|macro|__pmd_offset
mdefine_line|#define __pmd_offset(address)&t;(((address) &gt;&gt; PMD_SHIFT) &amp; (PTRS_PER_PMD-1))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, address)
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address)&t;((address) &gt;&gt; PGDIR_SHIFT)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm,addr)&t;((mm)-&gt;pgd + pgd_index(addr))
multiline_comment|/* Find an entry in the second-level page table.. */
DECL|function|pmd_offset
r_static
r_inline
id|pmd_t
op_star
id|pmd_offset
c_func
(paren
id|pgd_t
op_star
id|dir
comma
r_int
r_int
id|address
)paren
(brace
r_return
(paren
id|pmd_t
op_star
)paren
id|dir
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|__pte_offset
mdefine_line|#define __pte_offset(address)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset
mdefine_line|#define pte_offset(dir, address)&t;&t;&t;&t;&t;&bslash;&n;&t;((pte_t *) (pmd_page_kernel(*dir)) + __pte_offset(address))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address) &bslash;&n;&t;((pte_t *) pmd_page_kernel(*(dir)) +  __pte_offset(address))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address)                                    &bslash;&n;&t;((pte_t *)page_address(pmd_page(*(dir))) + __pte_offset(address))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address)                             &bslash;&n;&t;((pte_t *)page_address(pmd_page(*(dir))) + __pte_offset(address))
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) ((void)(pte))
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) ((void)(pte))
macro_line|#if defined(CONFIG_CPU_R3000) || defined(CONFIG_CPU_TX39XX)
multiline_comment|/* Swap entries must have VALID bit cleared. */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;(((x).val &gt;&gt; 10) &amp; 0x1f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;((x).val &gt;&gt; 15)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type,offset)&t;&bslash;&n;&t;((swp_entry_t) { ((type) &lt;&lt; 10) | ((offset) &lt;&lt; 15) })
multiline_comment|/*&n; * Bits 0, 1, 2, 9 and 10 are taken, split up the 27 bits of offset&n; * into this range:&n; */
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;27
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(_pte) &bslash;&n;&t;((((_pte).pte &gt;&gt; 3) &amp; 0x3f ) + (((_pte).pte &gt;&gt; 11) &lt;&lt; 8 ))
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) &bslash;&n;&t;((pte_t) { (((off) &amp; 0x3f) &lt;&lt; 3) + (((off) &gt;&gt; 8) &lt;&lt; 11) + _PAGE_FILE })
macro_line|#else
multiline_comment|/* Swap entries must have VALID and GLOBAL bits cleared. */
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;(((x).val &gt;&gt; 8) &amp; 0x1f)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;((x).val &gt;&gt; 13)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type,offset)&t;&bslash;&n;&t;&t;((swp_entry_t) { ((type) &lt;&lt; 8) | ((offset) &lt;&lt; 13) })
multiline_comment|/*&n; * Bits 0, 1, 2, 7 and 8 are taken, split up the 27 bits of offset&n; * into this range:&n; */
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;27
macro_line|#if defined(CONFIG_64BIT_PHYS_ADDR) &amp;&amp; defined(CONFIG_CPU_MIPS32)
multiline_comment|/* fixme */
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(_pte) (((_pte).pte_high &gt;&gt; 6) + ((_pte).pte_high &amp; 0x3f))
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) &bslash;&n; &t;((pte_t){(((off) &amp; 0x3f) + ((off) &lt;&lt; 6) + _PAGE_FILE)})
macro_line|#else
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(_pte) &bslash;&n;&t;((((_pte).pte &gt;&gt; 3) &amp; 0x1f ) + (((_pte).pte &gt;&gt; 9) &lt;&lt; 6 ))
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) &bslash;&n;&t;((pte_t) { (((off) &amp; 0x1f) &lt;&lt; 3) + (((off) &gt;&gt; 6) &lt;&lt; 9) + _PAGE_FILE })
macro_line|#endif
macro_line|#endif
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val })
macro_line|#endif /* _ASM_PGTABLE_32_H */
eof
