multiline_comment|/*&n; *  include/asm-s390/mmu_context.h&n; *&n; *  S390 version&n; *&n; *  Derived from &quot;include/asm-i386/mmu_context.h&quot;&n; */
macro_line|#ifndef __S390_MMU_CONTEXT_H
DECL|macro|__S390_MMU_CONTEXT_H
mdefine_line|#define __S390_MMU_CONTEXT_H
multiline_comment|/*&n; * get a new mmu context.. S390 don&squot;t know about contexts.&n; */
DECL|macro|init_new_context
mdefine_line|#define init_new_context(tsk,mm)        0
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)             flush_tlb_mm(mm)
DECL|function|enter_lazy_tlb
r_static
r_inline
r_void
id|enter_lazy_tlb
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
)brace
DECL|function|switch_mm
r_static
r_inline
r_void
id|switch_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev
comma
r_struct
id|mm_struct
op_star
id|next
comma
r_struct
id|task_struct
op_star
id|tsk
)paren
(brace
r_int
r_int
id|pgd
suffix:semicolon
r_if
c_cond
(paren
id|prev
op_ne
id|next
)paren
(brace
macro_line|#ifndef __s390x__
id|pgd
op_assign
(paren
id|__pa
c_func
(paren
id|next-&gt;pgd
)paren
op_amp
id|PAGE_MASK
)paren
op_or
(paren
id|_SEGMENT_TABLE
op_or
id|USER_STD_MASK
)paren
suffix:semicolon
multiline_comment|/* Load page tables */
id|asm
r_volatile
(paren
l_string|&quot;    lctl  7,7,%0&bslash;n&quot;
multiline_comment|/* secondary space */
l_string|&quot;    lctl  13,13,%0&bslash;n&quot;
multiline_comment|/* home space */
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|pgd
)paren
)paren
suffix:semicolon
macro_line|#else /* __s390x__ */
id|pgd
op_assign
(paren
id|__pa
c_func
(paren
id|next-&gt;pgd
)paren
op_amp
id|PAGE_MASK
)paren
op_or
(paren
id|_REGION_TABLE
op_or
id|USER_STD_MASK
)paren
suffix:semicolon
multiline_comment|/* Load page tables */
id|asm
r_volatile
(paren
l_string|&quot;    lctlg 7,7,%0&bslash;n&quot;
multiline_comment|/* secondary space */
l_string|&quot;    lctlg 13,13,%0&bslash;n&quot;
multiline_comment|/* home space */
suffix:colon
suffix:colon
l_string|&quot;m&quot;
(paren
id|pgd
)paren
)paren
suffix:semicolon
macro_line|#endif /* __s390x__ */
)brace
id|cpu_set
c_func
(paren
id|smp_processor_id
c_func
(paren
)paren
comma
id|next-&gt;cpu_vm_mask
)paren
suffix:semicolon
)brace
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(tsk,mm)&t;do { } while (0)
DECL|function|activate_mm
r_extern
r_inline
r_void
id|activate_mm
c_func
(paren
r_struct
id|mm_struct
op_star
id|prev
comma
r_struct
id|mm_struct
op_star
id|next
)paren
(brace
id|switch_mm
c_func
(paren
id|prev
comma
id|next
comma
id|current
)paren
suffix:semicolon
)brace
macro_line|#endif
eof
