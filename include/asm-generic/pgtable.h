macro_line|#ifndef _ASM_GENERIC_PGTABLE_H
DECL|macro|_ASM_GENERIC_PGTABLE_H
mdefine_line|#define _ASM_GENERIC_PGTABLE_H
macro_line|#ifndef __HAVE_ARCH_PTEP_ESTABLISH
multiline_comment|/*&n; * Establish a new mapping:&n; *  - flush the old one&n; *  - update the page tables&n; *  - inform the TLB about the new one&n; *&n; * We hold the mm semaphore for reading and vma-&gt;vm_mm-&gt;page_table_lock.&n; *&n; * Note: the old pte is known to not be writable, so we don&squot;t need to&n; * worry about dirty bits etc getting lost.&n; */
macro_line|#ifndef __HAVE_ARCH_SET_PTE_ATOMIC
DECL|macro|ptep_establish
mdefine_line|#define ptep_establish(__vma, __address, __ptep, __entry)&t;&t;&bslash;&n;do {&t;&t;&t;&t;  &t;&t;&t;&t;&t;&bslash;&n;&t;set_pte_at((__vma)-&gt;vm_mm, (__address), __ptep, __entry);&t;&bslash;&n;&t;flush_tlb_page(__vma, __address);&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#else /* __HAVE_ARCH_SET_PTE_ATOMIC */
DECL|macro|ptep_establish
mdefine_line|#define ptep_establish(__vma, __address, __ptep, __entry)&t;&t;&bslash;&n;do {&t;&t;&t;&t;  &t;&t;&t;&t;&t;&bslash;&n;&t;set_pte_atomic(__ptep, __entry);&t;&t;&t;&t;&bslash;&n;&t;flush_tlb_page(__vma, __address);&t;&t;&t;&t;&bslash;&n;} while (0)
macro_line|#endif /* __HAVE_ARCH_SET_PTE_ATOMIC */
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PTEP_SET_ACCESS_FLAGS
multiline_comment|/*&n; * Largely same as above, but only sets the access flags (dirty,&n; * accessed, and writable). Furthermore, we know it always gets set&n; * to a &quot;more permissive&quot; setting, which allows most architectures&n; * to optimize this.&n; */
DECL|macro|ptep_set_access_flags
mdefine_line|#define ptep_set_access_flags(__vma, __address, __ptep, __entry, __dirty) &bslash;&n;do {&t;&t;&t;&t;  &t;&t;&t;&t;&t;  &bslash;&n;&t;set_pte_at((__vma)-&gt;vm_mm, (__address), __ptep, __entry);&t;  &bslash;&n;&t;flush_tlb_page(__vma, __address);&t;&t;&t;&t;  &bslash;&n;} while (0)
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PTEP_TEST_AND_CLEAR_YOUNG
DECL|macro|ptep_test_and_clear_young
mdefine_line|#define ptep_test_and_clear_young(__vma, __address, __ptep)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t __pte = *(__ptep);&t;&t;&t;&t;&t;&bslash;&n;&t;int r = 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!pte_young(__pte))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;r = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_pte_at((__vma)-&gt;vm_mm, (__address),&t;&t;&t;&bslash;&n;&t;&t;&t;   (__ptep), pte_mkold(__pte));&t;&t;&t;&bslash;&n;&t;r;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PTEP_CLEAR_YOUNG_FLUSH
DECL|macro|ptep_clear_flush_young
mdefine_line|#define ptep_clear_flush_young(__vma, __address, __ptep)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __young;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__young = ptep_test_and_clear_young(__vma, __address, __ptep);&t;&bslash;&n;&t;if (__young)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;flush_tlb_page(__vma, __address);&t;&t;&t;&bslash;&n;&t;__young;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PTEP_TEST_AND_CLEAR_DIRTY
DECL|macro|ptep_test_and_clear_dirty
mdefine_line|#define ptep_test_and_clear_dirty(__vma, __address, __ptep)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t __pte = *__ptep;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int r = 1;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;if (!pte_dirty(__pte))&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;r = 0;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;else&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;set_pte_at((__vma)-&gt;vm_mm, (__address), (__ptep),&t;&bslash;&n;&t;&t;&t;   pte_mkclean(__pte));&t;&t;&t;&t;&bslash;&n;&t;r;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PTEP_CLEAR_DIRTY_FLUSH
DECL|macro|ptep_clear_flush_dirty
mdefine_line|#define ptep_clear_flush_dirty(__vma, __address, __ptep)&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;int __dirty;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__dirty = ptep_test_and_clear_dirty(__vma, __address, __ptep);&t;&bslash;&n;&t;if (__dirty)&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;&t;flush_tlb_page(__vma, __address);&t;&t;&t;&bslash;&n;&t;__dirty;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PTEP_GET_AND_CLEAR
DECL|macro|ptep_get_and_clear
mdefine_line|#define ptep_get_and_clear(__mm, __address, __ptep)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t __pte = *(__ptep);&t;&t;&t;&t;&t;&bslash;&n;&t;pte_clear((__mm), (__address), (__ptep));&t;&t;&t;&bslash;&n;&t;__pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PTEP_CLEAR_FLUSH
DECL|macro|ptep_clear_flush
mdefine_line|#define ptep_clear_flush(__vma, __address, __ptep)&t;&t;&t;&bslash;&n;({&t;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;pte_t __pte;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;&t;__pte = ptep_get_and_clear((__vma)-&gt;vm_mm, __address, __ptep);&t;&bslash;&n;&t;flush_tlb_page(__vma, __address);&t;&t;&t;&t;&bslash;&n;&t;__pte;&t;&t;&t;&t;&t;&t;&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PTEP_SET_WRPROTECT
DECL|function|ptep_set_wrprotect
r_static
r_inline
r_void
id|ptep_set_wrprotect
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_int
r_int
id|address
comma
id|pte_t
op_star
id|ptep
)paren
(brace
id|pte_t
id|old_pte
op_assign
op_star
id|ptep
suffix:semicolon
id|set_pte_at
c_func
(paren
id|mm
comma
id|address
comma
id|ptep
comma
id|pte_wrprotect
c_func
(paren
id|old_pte
)paren
)paren
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PTE_SAME
DECL|macro|pte_same
mdefine_line|#define pte_same(A,B)&t;(pte_val(A) == pte_val(B))
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PAGE_TEST_AND_CLEAR_DIRTY
DECL|macro|page_test_and_clear_dirty
mdefine_line|#define page_test_and_clear_dirty(page) (0)
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PAGE_TEST_AND_CLEAR_YOUNG
DECL|macro|page_test_and_clear_young
mdefine_line|#define page_test_and_clear_young(page) (0)
macro_line|#endif
macro_line|#ifndef __HAVE_ARCH_PGD_OFFSET_GATE
DECL|macro|pgd_offset_gate
mdefine_line|#define pgd_offset_gate(mm, addr)&t;pgd_offset(mm, addr)
macro_line|#endif
multiline_comment|/*&n; * When walking page tables, get the address of the next boundary, or&n; * the end address of the range if that comes earlier.  Although end might&n; * wrap to 0 only in clear_page_range, __boundary may wrap to 0 throughout.&n; */
DECL|macro|pgd_addr_end
mdefine_line|#define pgd_addr_end(addr, end)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;unsigned long __boundary = ((addr) + PGDIR_SIZE) &amp; PGDIR_MASK;&t;&bslash;&n;&t;(__boundary - 1 &lt; (end) - 1)? __boundary: (end);&t;&t;&bslash;&n;})
macro_line|#ifndef pud_addr_end
DECL|macro|pud_addr_end
mdefine_line|#define pud_addr_end(addr, end)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;unsigned long __boundary = ((addr) + PUD_SIZE) &amp; PUD_MASK;&t;&bslash;&n;&t;(__boundary - 1 &lt; (end) - 1)? __boundary: (end);&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifndef pmd_addr_end
DECL|macro|pmd_addr_end
mdefine_line|#define pmd_addr_end(addr, end)&t;&t;&t;&t;&t;&t;&bslash;&n;({&t;unsigned long __boundary = ((addr) + PMD_SIZE) &amp; PMD_MASK;&t;&bslash;&n;&t;(__boundary - 1 &lt; (end) - 1)? __boundary: (end);&t;&t;&bslash;&n;})
macro_line|#endif
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * When walking page tables, we usually want to skip any p?d_none entries;&n; * and any p?d_bad entries - reporting the error before resetting to none.&n; * Do the tests inline, but report and clear the bad entry in mm/memory.c.&n; */
r_void
id|pgd_clear_bad
c_func
(paren
id|pgd_t
op_star
)paren
suffix:semicolon
r_void
id|pud_clear_bad
c_func
(paren
id|pud_t
op_star
)paren
suffix:semicolon
r_void
id|pmd_clear_bad
c_func
(paren
id|pmd_t
op_star
)paren
suffix:semicolon
DECL|function|pgd_none_or_clear_bad
r_static
r_inline
r_int
id|pgd_none_or_clear_bad
c_func
(paren
id|pgd_t
op_star
id|pgd
)paren
(brace
r_if
c_cond
(paren
id|pgd_none
c_func
(paren
op_star
id|pgd
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|pgd_bad
c_func
(paren
op_star
id|pgd
)paren
)paren
)paren
(brace
id|pgd_clear_bad
c_func
(paren
id|pgd
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pud_none_or_clear_bad
r_static
r_inline
r_int
id|pud_none_or_clear_bad
c_func
(paren
id|pud_t
op_star
id|pud
)paren
(brace
r_if
c_cond
(paren
id|pud_none
c_func
(paren
op_star
id|pud
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|pud_bad
c_func
(paren
op_star
id|pud
)paren
)paren
)paren
(brace
id|pud_clear_bad
c_func
(paren
id|pud
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|pmd_none_or_clear_bad
r_static
r_inline
r_int
id|pmd_none_or_clear_bad
c_func
(paren
id|pmd_t
op_star
id|pmd
)paren
(brace
r_if
c_cond
(paren
id|pmd_none
c_func
(paren
op_star
id|pmd
)paren
)paren
r_return
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|pmd_bad
c_func
(paren
op_star
id|pmd
)paren
)paren
)paren
(brace
id|pmd_clear_bad
c_func
(paren
id|pmd
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif /* !__ASSEMBLY__ */
macro_line|#endif /* _ASM_GENERIC_PGTABLE_H */
eof
