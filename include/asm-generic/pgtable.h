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
macro_line|#endif /* _ASM_GENERIC_PGTABLE_H */
eof
