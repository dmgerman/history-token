macro_line|#include &lt;linux/highmem.h&gt;
DECL|function|kmap
r_void
op_star
id|kmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
id|might_sleep
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
r_return
id|kmap_high
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
DECL|function|kunmap
r_void
id|kunmap
c_func
(paren
r_struct
id|page
op_star
id|page
)paren
(brace
r_if
c_cond
(paren
id|in_interrupt
c_func
(paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
r_return
suffix:semicolon
id|kunmap_high
c_func
(paren
id|page
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * kmap_atomic/kunmap_atomic is significantly faster than kmap/kunmap because&n; * no global lock is needed and because the kmap code must perform a global TLB&n; * invalidation when the kmap pool wraps.&n; *&n; * However when holding an atomic kmap is is not legal to sleep, so atomic&n; * kmaps are appropriate for short, tight code paths only.&n; */
DECL|function|kmap_atomic
r_void
op_star
id|kmap_atomic
c_func
(paren
r_struct
id|page
op_star
id|page
comma
r_enum
id|km_type
id|type
)paren
(brace
r_enum
id|fixed_addresses
id|idx
suffix:semicolon
r_int
r_int
id|vaddr
suffix:semicolon
multiline_comment|/* even !CONFIG_PREEMPT needs this, for in_atomic in do_page_fault */
id|inc_preempt_count
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|PageHighMem
c_func
(paren
id|page
)paren
)paren
r_return
id|page_address
c_func
(paren
id|page
)paren
suffix:semicolon
id|idx
op_assign
id|type
op_plus
id|KM_TYPE_NR
op_star
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
id|vaddr
op_assign
id|__fix_to_virt
c_func
(paren
id|FIX_KMAP_BEGIN
op_plus
id|idx
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_DEBUG_HIGHMEM
r_if
c_cond
(paren
op_logical_neg
id|pte_none
c_func
(paren
op_star
(paren
id|kmap_pte
op_minus
id|idx
)paren
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
macro_line|#endif
id|set_pte
c_func
(paren
id|kmap_pte
op_minus
id|idx
comma
id|mk_pte
c_func
(paren
id|page
comma
id|kmap_prot
)paren
)paren
suffix:semicolon
id|__flush_tlb_one
c_func
(paren
id|vaddr
)paren
suffix:semicolon
r_return
(paren
r_void
op_star
)paren
id|vaddr
suffix:semicolon
)brace
DECL|function|kunmap_atomic
r_void
id|kunmap_atomic
c_func
(paren
r_void
op_star
id|kvaddr
comma
r_enum
id|km_type
id|type
)paren
(brace
macro_line|#ifdef CONFIG_DEBUG_HIGHMEM
r_int
r_int
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|kvaddr
op_amp
id|PAGE_MASK
suffix:semicolon
r_enum
id|fixed_addresses
id|idx
op_assign
id|type
op_plus
id|KM_TYPE_NR
op_star
id|smp_processor_id
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|vaddr
OL
id|FIXADDR_START
)paren
(brace
singleline_comment|// FIXME
id|dec_preempt_count
c_func
(paren
)paren
suffix:semicolon
id|preempt_check_resched
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_if
c_cond
(paren
id|vaddr
op_ne
id|__fix_to_virt
c_func
(paren
id|FIX_KMAP_BEGIN
op_plus
id|idx
)paren
)paren
id|BUG
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * force other mappings to Oops if they&squot;ll try to access&n;&t; * this pte without first remap it&n;&t; */
id|pte_clear
c_func
(paren
op_amp
id|init_mm
comma
id|vaddr
comma
id|kmap_pte
op_minus
id|idx
)paren
suffix:semicolon
id|__flush_tlb_one
c_func
(paren
id|vaddr
)paren
suffix:semicolon
macro_line|#endif
id|dec_preempt_count
c_func
(paren
)paren
suffix:semicolon
id|preempt_check_resched
c_func
(paren
)paren
suffix:semicolon
)brace
DECL|function|kmap_atomic_to_page
r_struct
id|page
op_star
id|kmap_atomic_to_page
c_func
(paren
r_void
op_star
id|ptr
)paren
(brace
r_int
r_int
id|idx
comma
id|vaddr
op_assign
(paren
r_int
r_int
)paren
id|ptr
suffix:semicolon
id|pte_t
op_star
id|pte
suffix:semicolon
r_if
c_cond
(paren
id|vaddr
OL
id|FIXADDR_START
)paren
r_return
id|virt_to_page
c_func
(paren
id|ptr
)paren
suffix:semicolon
id|idx
op_assign
id|virt_to_fix
c_func
(paren
id|vaddr
)paren
suffix:semicolon
id|pte
op_assign
id|kmap_pte
op_minus
(paren
id|idx
op_minus
id|FIX_KMAP_BEGIN
)paren
suffix:semicolon
r_return
id|pte_page
c_func
(paren
op_star
id|pte
)paren
suffix:semicolon
)brace
eof
