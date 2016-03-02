macro_line|#ifndef _M68KNOMMU_PGTABLE_H
DECL|macro|_M68KNOMMU_PGTABLE_H
mdefine_line|#define _M68KNOMMU_PGTABLE_H
multiline_comment|/*&n; * (C) Copyright 2000-2002, Greg Ungerer &lt;gerg@snapgear.com&gt;&n; */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/slab.h&gt;
macro_line|#include &lt;asm/processor.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/io.h&gt;
DECL|typedef|pte_addr_t
r_typedef
id|pte_t
op_star
id|pte_addr_t
suffix:semicolon
multiline_comment|/*&n; * Trivial page table functions.&n; */
DECL|macro|pgd_present
mdefine_line|#define pgd_present(pgd)&t;(1)
DECL|macro|pgd_none
mdefine_line|#define pgd_none(pgd)&t;&t;(0)
DECL|macro|pgd_bad
mdefine_line|#define pgd_bad(pgd)&t;&t;(0)
DECL|macro|pgd_clear
mdefine_line|#define pgd_clear(pgdp)
DECL|macro|kern_addr_valid
mdefine_line|#define kern_addr_valid(addr)&t;(1)
DECL|macro|pmd_offset
mdefine_line|#define&t;pmd_offset(a, b)&t;((void *)0)
DECL|macro|PAGE_NONE
mdefine_line|#define PAGE_NONE&t;__pgprot(0)
DECL|macro|PAGE_SHARED
mdefine_line|#define PAGE_SHARED&t;__pgprot(0)
DECL|macro|PAGE_COPY
mdefine_line|#define PAGE_COPY&t;__pgprot(0)
DECL|macro|PAGE_READONLY
mdefine_line|#define PAGE_READONLY&t;__pgprot(0)
DECL|macro|PAGE_KERNEL
mdefine_line|#define PAGE_KERNEL&t;__pgprot(0)
r_extern
r_void
id|paging_init
c_func
(paren
r_void
)paren
suffix:semicolon
DECL|macro|swapper_pg_dir
mdefine_line|#define swapper_pg_dir ((pgd_t *) 0)
DECL|macro|__swp_type
mdefine_line|#define __swp_type(x)&t;&t;(0)
DECL|macro|__swp_offset
mdefine_line|#define __swp_offset(x)&t;&t;(0)
DECL|macro|__swp_entry
mdefine_line|#define __swp_entry(typ,off)&t;((swp_entry_t) { ((typ) | ((off) &lt;&lt; 7)) })
DECL|macro|__pte_to_swp_entry
mdefine_line|#define __pte_to_swp_entry(pte)&t;((swp_entry_t) { pte_val(pte) })
DECL|macro|__swp_entry_to_pte
mdefine_line|#define __swp_entry_to_pte(x)&t;((pte_t) { (x).val })
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
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * ZERO_PAGE is a global shared page that is always zero: used&n; * for zero-mapped memory areas etc..&n; */
DECL|macro|ZERO_PAGE
mdefine_line|#define ZERO_PAGE(vaddr)&t;(virt_to_page(0))
multiline_comment|/*&n; * These would be in other places but having them here reduces the diffs.&n; */
r_extern
r_int
r_int
id|kobjsize
c_func
(paren
r_const
r_void
op_star
id|objp
)paren
suffix:semicolon
r_extern
r_int
id|is_in_rom
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
multiline_comment|/*&n; * No page table caches to initialise.&n; */
DECL|macro|pgtable_cache_init
mdefine_line|#define pgtable_cache_init()&t;do { } while (0)
DECL|macro|io_remap_page_range
mdefine_line|#define io_remap_page_range&t;remap_page_range
multiline_comment|/*&n; * All 32bit addresses are effectively valid for vmalloc...&n; * Sort of meaningless for non-VM targets.&n; */
DECL|macro|VMALLOC_START
mdefine_line|#define&t;VMALLOC_START&t;0
DECL|macro|VMALLOC_END
mdefine_line|#define&t;VMALLOC_END&t;0xffffffff
macro_line|#endif /* _M68KNOMMU_PGTABLE_H */
eof
