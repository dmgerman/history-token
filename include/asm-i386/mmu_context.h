macro_line|#ifndef __I386_SCHED_H
DECL|macro|__I386_SCHED_H
mdefine_line|#define __I386_SCHED_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/desc.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/tlbflush.h&gt;
multiline_comment|/*&n; * Used for LDT copy/destruction.&n; */
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
id|cpu_tlbstate
(braket
id|cpu
)braket
dot
id|state
op_eq
id|TLBSTATE_OK
)paren
id|cpu_tlbstate
(braket
id|cpu
)braket
dot
id|state
op_assign
id|TLBSTATE_LAZY
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
id|cpu_tlbstate
(braket
id|cpu
)braket
dot
id|state
op_assign
id|TLBSTATE_OK
suffix:semicolon
id|cpu_tlbstate
(braket
id|cpu
)braket
dot
id|active_mm
op_assign
id|next
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
id|load_cr3
c_func
(paren
id|next-&gt;pgd
)paren
suffix:semicolon
multiline_comment|/*&n;&t;&t; * load the LDT, if the LDT is different:&n;&t;&t; */
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|prev-&gt;context.ldt
op_ne
id|next-&gt;context.ldt
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
id|cpu_tlbstate
(braket
id|cpu
)braket
dot
id|state
op_assign
id|TLBSTATE_OK
suffix:semicolon
r_if
c_cond
(paren
id|cpu_tlbstate
(braket
id|cpu
)braket
dot
id|active_mm
op_ne
id|next
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
multiline_comment|/* We were in lazy tlb mode and leave_mm disabled &n;&t;&t;&t; * tlb flush IPI delivery. We must reload %cr3.&n;&t;&t;&t; */
id|load_cr3
c_func
(paren
id|next-&gt;pgd
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
DECL|macro|activate_mm
mdefine_line|#define activate_mm(prev, next) &bslash;&n;&t;switch_mm((prev),(next),NULL,smp_processor_id())
macro_line|#endif
eof
