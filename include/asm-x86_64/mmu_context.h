macro_line|#ifndef __X86_64_MMU_CONTEXT_H
DECL|macro|__X86_64_MMU_CONTEXT_H
mdefine_line|#define __X86_64_MMU_CONTEXT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pda.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * possibly do the LDT unload here?&n; */
r_int
id|init_new_context
c_func
(paren
r_struct
id|task_struct
op_star
id|tsk
comma
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
r_void
id|destroy_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
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
comma
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
id|read_pda
c_func
(paren
id|mmu_state
)paren
op_eq
id|TLBSTATE_OK
)paren
id|write_pda
c_func
(paren
id|mmu_state
comma
id|TLBSTATE_LAZY
)paren
suffix:semicolon
)brace
macro_line|#else
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
comma
r_int
id|cpu
)paren
(brace
)brace
macro_line|#endif
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
comma
r_int
id|cpu
)paren
(brace
r_if
c_cond
(paren
id|likely
c_func
(paren
id|prev
op_ne
id|next
)paren
)paren
(brace
multiline_comment|/* stop flush ipis for the previous mm */
id|clear_bit
c_func
(paren
id|cpu
comma
op_amp
id|prev-&gt;cpu_vm_mask
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|write_pda
c_func
(paren
id|mmu_state
comma
id|TLBSTATE_OK
)paren
suffix:semicolon
id|write_pda
c_func
(paren
id|active_mm
comma
id|next
)paren
suffix:semicolon
macro_line|#endif
id|set_bit
c_func
(paren
id|cpu
comma
op_amp
id|next-&gt;cpu_vm_mask
)paren
suffix:semicolon
multiline_comment|/* Re-load page tables */
op_star
id|read_pda
c_func
(paren
id|level4_pgt
)paren
op_assign
id|__pa
c_func
(paren
id|next-&gt;pgd
)paren
op_or
id|_PAGE_TABLE
suffix:semicolon
id|__flush_tlb
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|next-&gt;context.ldt
op_ne
id|prev-&gt;context.ldt
)paren
)paren
id|load_LDT_nolock
c_func
(paren
op_amp
id|next-&gt;context
comma
id|cpu
)paren
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_else
(brace
id|write_pda
c_func
(paren
id|mmu_state
comma
id|TLBSTATE_OK
)paren
suffix:semicolon
r_if
c_cond
(paren
id|read_pda
c_func
(paren
id|active_mm
)paren
op_ne
id|next
)paren
id|out_of_line_bug
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|test_and_set_bit
c_func
(paren
id|cpu
comma
op_amp
id|next-&gt;cpu_vm_mask
)paren
)paren
(brace
multiline_comment|/* We were in lazy tlb mode and leave_mm disabled &n;&t;&t;&t; * tlb flush IPI delivery. We must flush our tlb.&n;&t;&t;&t; */
id|local_flush_tlb
c_func
(paren
)paren
suffix:semicolon
id|load_LDT_nolock
c_func
(paren
op_amp
id|next-&gt;context
comma
id|cpu
)paren
suffix:semicolon
)brace
)brace
macro_line|#endif
)brace
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(tsk,mm)&t;do { &bslash;&n;&t;load_gs_index(0); &bslash;&n;&t;asm volatile(&quot;movl %0,%%fs&quot;::&quot;r&quot;(0));  &bslash;&n;} while(0)
DECL|macro|activate_mm
mdefine_line|#define activate_mm(prev, next) &bslash;&n;&t;switch_mm((prev),(next),NULL,smp_processor_id())
macro_line|#endif
eof
