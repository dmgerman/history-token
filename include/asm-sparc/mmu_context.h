macro_line|#ifndef __SPARC_MMU_CONTEXT_H
DECL|macro|__SPARC_MMU_CONTEXT_H
mdefine_line|#define __SPARC_MMU_CONTEXT_H
macro_line|#include &lt;asm/btfixup.h&gt;
macro_line|#ifndef __ASSEMBLY__
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
