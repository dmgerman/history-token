macro_line|#ifndef __H8300_MMU_CONTEXT_H
DECL|macro|__H8300_MMU_CONTEXT_H
mdefine_line|#define __H8300_MMU_CONTEXT_H
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;asm/setup.h&gt;
macro_line|#include &lt;asm/page.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
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
r_extern
r_inline
r_int
DECL|function|init_new_context
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
(brace
singleline_comment|// mm-&gt;context = virt_to_phys(mm-&gt;pgd);
r_return
l_int|0
suffix:semicolon
)brace
DECL|macro|destroy_context
mdefine_line|#define destroy_context(mm)&t;&t;do { } while(0)
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(tsk,mm)           do { } while(0)
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
)brace
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
id|prev_mm
comma
r_struct
id|mm_struct
op_star
id|next_mm
)paren
(brace
)brace
macro_line|#endif
eof
