macro_line|#ifndef __SPARC_MMU_CONTEXT_H
DECL|macro|__SPARC_MMU_CONTEXT_H
mdefine_line|#define __SPARC_MMU_CONTEXT_H
macro_line|#include &lt;asm/btfixup.h&gt;
macro_line|#ifndef __ASSEMBLY__
multiline_comment|/*&n; * Every architecture must define this function. It&squot;s the fastest&n; * way of searching a 168-bit bitmap where the first 128 bits are&n; * unlikely to be clear. It&squot;s guaranteed that at least one of the 168&n; * bits is cleared.&n; */
macro_line|#if MAX_RT_PRIO != 128 || MAX_PRIO != 168
macro_line|# error update this function.
macro_line|#endif
DECL|function|sched_find_first_zero_bit
r_static
r_inline
r_int
id|sched_find_first_zero_bit
c_func
(paren
r_int
r_int
op_star
id|b
)paren
(brace
r_int
r_int
id|rt
suffix:semicolon
id|rt
op_assign
id|b
(braket
l_int|0
)braket
op_amp
id|b
(braket
l_int|1
)braket
op_amp
id|b
(braket
l_int|2
)braket
op_amp
id|b
(braket
l_int|3
)braket
suffix:semicolon
r_if
c_cond
(paren
id|unlikely
c_func
(paren
id|rt
op_ne
l_int|0xffffffff
)paren
)paren
r_return
id|find_first_zero_bit
c_func
(paren
id|b
comma
id|MAX_RT_PRIO
)paren
suffix:semicolon
r_if
c_cond
(paren
id|b
(braket
l_int|4
)braket
op_ne
op_complement
l_int|0
)paren
r_return
id|ffz
c_func
(paren
id|b
(braket
l_int|4
)braket
)paren
op_plus
id|MAX_RT_PRIO
suffix:semicolon
r_return
id|ffz
c_func
(paren
id|b
(braket
l_int|5
)braket
)paren
op_plus
l_int|32
op_plus
id|MAX_RT_PRIO
suffix:semicolon
)brace
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
multiline_comment|/*&n; * Initialize a new mmu context.  This is invoked when a new&n; * address space instance (unique or shared) is instantiated.&n; */
DECL|macro|init_new_context
mdefine_line|#define init_new_context(tsk, mm) (((mm)-&gt;context = NO_CONTEXT), 0)
multiline_comment|/*&n; * Destroy a dead context.  This occurs when mmput drops the&n; * mm_users count to zero, the mmaps have been released, and&n; * all the page tables have been flushed.  Our job is to destroy&n; * any remaining processor-specific state.&n; */
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|destroy_context
comma
r_struct
id|mm_struct
op_star
)paren
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm) BTFIXUP_CALL(destroy_context)(mm)
multiline_comment|/* Switch the current MM context. */
id|BTFIXUPDEF_CALL
c_func
(paren
r_void
comma
id|switch_mm
comma
r_struct
id|mm_struct
op_star
comma
r_struct
id|mm_struct
op_star
comma
r_struct
id|task_struct
op_star
comma
r_int
)paren
DECL|macro|switch_mm
mdefine_line|#define switch_mm(old_mm, mm, tsk, cpu) BTFIXUP_CALL(switch_mm)(old_mm, mm, tsk, cpu)
multiline_comment|/* Activate a new MM instance for the current task. */
DECL|macro|activate_mm
mdefine_line|#define activate_mm(active_mm, mm) switch_mm((active_mm), (mm), NULL, smp_processor_id())
macro_line|#endif /* !(__ASSEMBLY__) */
macro_line|#endif /* !(__SPARC_MMU_CONTEXT_H) */
eof
