multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * Copyright (C) 1994, 95, 96, 97, 98, 99, 2000, 2003 Ralf Baechle&n; * Copyright (C) 1999, 2000, 2001 Silicon Graphics, Inc.&n; */
macro_line|#ifndef _ASM_PGTABLE_64_H
DECL|macro|_ASM_PGTABLE_64_H
mdefine_line|#define _ASM_PGTABLE_64_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/linkage.h&gt;
macro_line|#include &lt;asm/addrspace.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/cachectl.h&gt;
multiline_comment|/*&n; * Each address space has 2 4K pages as its page directory, giving 1024&n; * (== PTRS_PER_PGD) 8 byte pointers to pmd tables. Each pmd table is a&n; * pair of 4K pages, giving 1024 (== PTRS_PER_PMD) 8 byte pointers to&n; * page tables. Each page table is a single 4K page, giving 512 (==&n; * PTRS_PER_PTE) 8 byte ptes. Each pgde is initialized to point to&n; * invalid_pmd_table, each pmde is initialized to point to&n; * invalid_pte_table, each pte is initialized to 0. When memory is low,&n; * and a pmd table or a page table allocation fails, empty_bad_pmd_table&n; * and empty_bad_page_table is returned back to higher layer code, so&n; * that the failure is recognized later on. Linux does not seem to&n; * handle these failures very well though. The empty_bad_page_table has&n; * invalid pte entries in it, to force page faults.&n; *&n; * Kernel mappings: kernel mappings are held in the swapper_pg_table.&n; * The layout is identical to userspace except it&squot;s indexed with the&n; * fault address - VMALLOC_START.&n; */
multiline_comment|/* PMD_SHIFT determines the size of the area a second-level page table can map */
DECL|macro|PMD_SHIFT
mdefine_line|#define PMD_SHIFT&t;(PAGE_SHIFT + (PAGE_SHIFT - 3))
DECL|macro|PMD_SIZE
mdefine_line|#define PMD_SIZE&t;(1UL &lt;&lt; PMD_SHIFT)
DECL|macro|PMD_MASK
mdefine_line|#define PMD_MASK&t;(~(PMD_SIZE-1))
multiline_comment|/* PGDIR_SHIFT determines what a third-level page table entry can map */
DECL|macro|PGDIR_SHIFT
mdefine_line|#define PGDIR_SHIFT&t;(PMD_SHIFT + (PAGE_SHIFT + 1 - 3))
DECL|macro|PGDIR_SIZE
mdefine_line|#define PGDIR_SIZE&t;(1UL &lt;&lt; PGDIR_SHIFT)
DECL|macro|PGDIR_MASK
mdefine_line|#define PGDIR_MASK&t;(~(PGDIR_SIZE-1))
multiline_comment|/*&n; * For 4kB page size we use a 3 level page tree and a 8kB pmd and pgds which&n; * permits us mapping 40 bits of virtual address space.&n; *&n; * We used to implement 41 bits by having an order 1 pmd level but that seemed&n; * rather pointless.&n; *&n; * For 8kB page size we use a 3 level page tree which permits a total of&n; * 8TB of address space.  Alternatively a 33-bit / 8GB organization using&n; * two levels would be easy to implement.&n; *&n; * For 16kB page size we use a 2 level page tree which permits a total of&n; * 36 bits of virtual address space.  We could add a third leve. but it seems&n; * like at the moment there&squot;s no need for this.&n; *&n; * For 64kB page size we use a 2 level page table tree for a total of 42 bits&n; * of virtual address space.&n; */
macro_line|#ifdef CONFIG_PAGE_SIZE_4KB
DECL|macro|PGD_ORDER
mdefine_line|#define PGD_ORDER&t;&t;1
DECL|macro|PMD_ORDER
mdefine_line|#define PMD_ORDER&t;&t;0
DECL|macro|PTE_ORDER
mdefine_line|#define PTE_ORDER&t;&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_PAGE_SIZE_8KB
DECL|macro|PGD_ORDER
mdefine_line|#define PGD_ORDER&t;&t;0
DECL|macro|PMD_ORDER
mdefine_line|#define PMD_ORDER&t;&t;0
DECL|macro|PTE_ORDER
mdefine_line|#define PTE_ORDER&t;&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_PAGE_SIZE_16KB
DECL|macro|PGD_ORDER
mdefine_line|#define PGD_ORDER&t;&t;0
DECL|macro|PMD_ORDER
mdefine_line|#define PMD_ORDER&t;&t;0
DECL|macro|PTE_ORDER
mdefine_line|#define PTE_ORDER&t;&t;0
macro_line|#endif
macro_line|#ifdef CONFIG_PAGE_SIZE_64KB
DECL|macro|PGD_ORDER
mdefine_line|#define PGD_ORDER&t;&t;0
DECL|macro|PMD_ORDER
mdefine_line|#define PMD_ORDER&t;&t;0
DECL|macro|PTE_ORDER
mdefine_line|#define PTE_ORDER&t;&t;0
macro_line|#endif
DECL|macro|PTRS_PER_PGD
mdefine_line|#define PTRS_PER_PGD&t;((PAGE_SIZE &lt;&lt; PGD_ORDER) / sizeof(pgd_t))
DECL|macro|PTRS_PER_PMD
mdefine_line|#define PTRS_PER_PMD&t;((PAGE_SIZE &lt;&lt; PMD_ORDER) / sizeof(pmd_t))
DECL|macro|PTRS_PER_PTE
mdefine_line|#define PTRS_PER_PTE&t;((PAGE_SIZE &lt;&lt; PTE_ORDER) / sizeof(pte_t))
DECL|macro|USER_PTRS_PER_PGD
mdefine_line|#define USER_PTRS_PER_PGD&t;(TASK_SIZE / PGDIR_SIZE)
DECL|macro|FIRST_USER_PGD_NR
mdefine_line|#define FIRST_USER_PGD_NR&t;0
DECL|macro|VMALLOC_START
mdefine_line|#define VMALLOC_START&t;&t;XKSEG
DECL|macro|VMALLOC_END
mdefine_line|#define VMALLOC_END&t;&bslash;&n;&t;(VMALLOC_START + PTRS_PER_PGD * PTRS_PER_PMD * PTRS_PER_PTE * PAGE_SIZE)
DECL|macro|pte_ERROR
mdefine_line|#define pte_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pte %016lx.&bslash;n&quot;, __FILE__, __LINE__, pte_val(e))
DECL|macro|pmd_ERROR
mdefine_line|#define pmd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pmd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pmd_val(e))
DECL|macro|pgd_ERROR
mdefine_line|#define pgd_ERROR(e) &bslash;&n;&t;printk(&quot;%s:%d: bad pgd %016lx.&bslash;n&quot;, __FILE__, __LINE__, pgd_val(e))
r_extern
id|pte_t
id|invalid_pte_table
(braket
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pte_t
)paren
)braket
suffix:semicolon
r_extern
id|pte_t
id|empty_bad_page_table
(braket
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pte_t
)paren
)braket
suffix:semicolon
r_extern
id|pmd_t
id|invalid_pmd_table
(braket
l_int|2
op_star
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pmd_t
)paren
)braket
suffix:semicolon
r_extern
id|pmd_t
id|empty_bad_pmd_table
(braket
l_int|2
op_star
id|PAGE_SIZE
op_div
r_sizeof
(paren
id|pmd_t
)paren
)braket
suffix:semicolon
multiline_comment|/*&n; * Empty pmd entries point to the invalid_pte_table.&n; */
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
multiline_comment|/*&n; * Empty pgd entries point to the invalid_pmd_table.&n; */
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
id|pgd_val
c_func
(paren
id|pgd
)paren
op_eq
(paren
r_int
r_int
)paren
id|invalid_pmd_table
suffix:semicolon
)brace
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;(pgd_val(pgd) &amp;~ PAGE_MASK)
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
id|pgd_val
c_func
(paren
id|pgd
)paren
op_ne
(paren
r_int
r_int
)paren
id|invalid_pmd_table
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
id|pgd_val
c_func
(paren
op_star
id|pgdp
)paren
op_assign
(paren
(paren
r_int
r_int
)paren
id|invalid_pmd_table
)paren
suffix:semicolon
)brace
DECL|macro|pte_page
mdefine_line|#define pte_page(x)&t;&t;pfn_to_page((unsigned long)((pte_val(x) &gt;&gt; PAGE_SHIFT)))
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
DECL|macro|__pgd_offset
mdefine_line|#define __pgd_offset(address)&t;pgd_index(address)
DECL|macro|page_pte
mdefine_line|#define page_pte(page) page_pte_prot(page, __pgprot(0))
multiline_comment|/* to find an entry in a kernel page-table-directory */
DECL|macro|pgd_offset_k
mdefine_line|#define pgd_offset_k(address) pgd_offset(&amp;init_mm, 0)
DECL|macro|pgd_index
mdefine_line|#define pgd_index(address)&t;&t;((address) &gt;&gt; PGDIR_SHIFT)
multiline_comment|/* to find an entry in a page-table-directory */
DECL|macro|pgd_offset
mdefine_line|#define pgd_offset(mm,addr)&t;((mm)-&gt;pgd + pgd_index(addr))
DECL|function|pgd_page
r_static
r_inline
r_int
r_int
id|pgd_page
c_func
(paren
id|pgd_t
id|pgd
)paren
(brace
r_return
id|pgd_val
c_func
(paren
id|pgd
)paren
suffix:semicolon
)brace
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
id|pgd_page
c_func
(paren
op_star
id|dir
)paren
op_plus
(paren
(paren
id|address
op_rshift
id|PMD_SHIFT
)paren
op_amp
(paren
id|PTRS_PER_PMD
op_minus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Find an entry in the third-level page table.. */
DECL|macro|__pte_offset
mdefine_line|#define __pte_offset(address)&t;&t;&t;&t;&t;&t;&bslash;&n;&t;(((address) &gt;&gt; PAGE_SHIFT) &amp; (PTRS_PER_PTE - 1))
DECL|macro|pte_offset
mdefine_line|#define pte_offset(dir, address)&t;&t;&t;&t;&t;&bslash;&n;&t;((pte_t *) (pmd_page_kernel(*dir)) + __pte_offset(address))
DECL|macro|pte_offset_kernel
mdefine_line|#define pte_offset_kernel(dir, address)&t;&t;&t;&t;&t;&bslash;&n;&t;((pte_t *) pmd_page_kernel(*(dir)) +  __pte_offset(address))
DECL|macro|pte_offset_map
mdefine_line|#define pte_offset_map(dir, address)&t;&t;&t;&t;&t;&bslash;&n;&t;((pte_t *)page_address(pmd_page(*(dir))) + __pte_offset(address))
DECL|macro|pte_offset_map_nested
mdefine_line|#define pte_offset_map_nested(dir, address)&t;&t;&t;&t;&bslash;&n;&t;((pte_t *)page_address(pmd_page(*(dir))) + __pte_offset(address))
DECL|macro|pte_unmap
mdefine_line|#define pte_unmap(pte) ((void)(pte))
DECL|macro|pte_unmap_nested
mdefine_line|#define pte_unmap_nested(pte) ((void)(pte))
multiline_comment|/*&n; * Initialize a new pgd / pmd table with invalid pointers.&n; */
r_extern
r_void
id|pgd_init
c_func
(paren
r_int
r_int
id|page
)paren
suffix:semicolon
r_extern
r_void
id|pmd_init
c_func
(paren
r_int
r_int
id|page
comma
r_int
r_int
id|pagetable
)paren
suffix:semicolon
multiline_comment|/*&n; * Non-present pages:  high 24 bits are offset, next 8 bits type,&n; * low 32 bits zero.&n; */
DECL|function|mk_swap_pte
r_static
r_inline
id|pte_t
id|mk_swap_pte
c_func
(paren
r_int
r_int
id|type
comma
r_int
r_int
id|offset
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
id|type
op_lshift
l_int|32
)paren
op_or
(paren
id|offset
op_lshift
l_int|40
)paren
suffix:semicolon
r_return
id|pte
suffix:semicolon
)brace
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;(((x).val &gt;&gt; 32) &amp; 0xff)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;((x).val &gt;&gt; 40)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(type,offset) ((swp_entry_t) { pte_val(mk_swap_pte((type),(offset))) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val })
multiline_comment|/*&n; * Bits 0, 1, 2, 7 and 8 are taken, split up the 32 bits of offset&n; * into this range:&n; */
DECL|macro|PTE_FILE_MAX_BITS
mdefine_line|#define PTE_FILE_MAX_BITS&t;32
DECL|macro|pte_to_pgoff
mdefine_line|#define pte_to_pgoff(_pte) &bslash;&n;&t;((((_pte).pte &gt;&gt; 3) &amp; 0x1f ) + (((_pte).pte &gt;&gt; 9) &lt;&lt; 6 ))
DECL|macro|pgoff_to_pte
mdefine_line|#define pgoff_to_pte(off) &bslash;&n;&t;((pte_t) { (((off) &amp; 0x1f) &lt;&lt; 3) + (((off) &gt;&gt; 6) &lt;&lt; 9) + _PAGE_FILE })
macro_line|#endif /* _ASM_PGTABLE_64_H */
eof
