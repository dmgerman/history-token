macro_line|#ifndef _ARMV_RMAP_H
DECL|macro|_ARMV_RMAP_H
mdefine_line|#define _ARMV_RMAP_H
multiline_comment|/*&n; * linux/include/asm-arm/proc-armv/rmap.h&n; *&n; * Architecture dependant parts of the reverse mapping code,&n; *&n; * ARM is different since hardware page tables are smaller than&n; * the page size and Linux uses a &quot;duplicate&quot; one with extra info.&n; * For rmap this means that the first 2 kB of a page are the hardware&n; * page tables and the last 2 kB are the software page tables.&n; */
DECL|function|pgtable_add_rmap
r_static
r_inline
r_void
id|pgtable_add_rmap
c_func
(paren
id|pte_t
op_star
id|ptep
comma
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|ptep
)paren
suffix:semicolon
id|page-&gt;mm
op_assign
id|mm
suffix:semicolon
id|page-&gt;index
op_assign
id|address
op_amp
op_complement
(paren
(paren
id|PTRS_PER_PTE
op_star
id|PAGE_SIZE
)paren
op_minus
l_int|1
)paren
suffix:semicolon
id|inc_page_state
c_func
(paren
id|nr_page_table_pages
)paren
suffix:semicolon
)brace
DECL|function|pgtable_remove_rmap
r_static
r_inline
r_void
id|pgtable_remove_rmap
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|ptep
)paren
suffix:semicolon
id|page-&gt;mm
op_assign
l_int|NULL
suffix:semicolon
id|page-&gt;index
op_assign
l_int|0
suffix:semicolon
id|dec_page_state
c_func
(paren
id|nr_page_table_pages
)paren
suffix:semicolon
)brace
DECL|function|ptep_to_mm
r_static
r_inline
r_struct
id|mm_struct
op_star
id|ptep_to_mm
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|ptep
)paren
suffix:semicolon
r_return
id|page-&gt;mm
suffix:semicolon
)brace
multiline_comment|/* The page table takes half of the page */
DECL|macro|PTE_MASK
mdefine_line|#define PTE_MASK  ((PAGE_SIZE / 2) - 1)
DECL|function|ptep_to_address
r_static
r_inline
r_int
r_int
id|ptep_to_address
c_func
(paren
id|pte_t
op_star
id|ptep
)paren
(brace
r_struct
id|page
op_star
id|page
op_assign
id|virt_to_page
c_func
(paren
id|ptep
)paren
suffix:semicolon
r_int
r_int
id|low_bits
suffix:semicolon
id|low_bits
op_assign
(paren
(paren
r_int
r_int
)paren
id|ptep
op_amp
id|PTE_MASK
)paren
op_star
id|PTRS_PER_PTE
suffix:semicolon
r_return
id|page-&gt;index
op_plus
id|low_bits
suffix:semicolon
)brace
macro_line|#endif /* _ARMV_RMAP_H */
eof