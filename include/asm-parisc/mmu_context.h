macro_line|#ifndef __PARISC_MMU_CONTEXT_H
DECL|macro|__PARISC_MMU_CONTEXT_H
mdefine_line|#define __PARISC_MMU_CONTEXT_H
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/atomic.h&gt;
macro_line|#include &lt;asm/pgalloc.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
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
multiline_comment|/* on PA-RISC, we actually have enough contexts to justify an allocator&n; * for them.  prumpf */
r_extern
r_int
r_int
id|alloc_sid
c_func
(paren
r_void
)paren
suffix:semicolon
r_extern
r_void
id|free_sid
c_func
(paren
r_int
r_int
)paren
suffix:semicolon
r_static
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
id|BUG_ON
c_func
(paren
id|atomic_read
c_func
(paren
op_amp
id|mm-&gt;mm_users
)paren
op_ne
l_int|1
)paren
suffix:semicolon
id|mm-&gt;context
op_assign
id|alloc_sid
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|destroy_context
id|destroy_context
c_func
(paren
r_struct
id|mm_struct
op_star
id|mm
)paren
(brace
id|free_sid
c_func
(paren
id|mm-&gt;context
)paren
suffix:semicolon
id|mm-&gt;context
op_assign
l_int|0
suffix:semicolon
)brace
DECL|function|load_context
r_static
r_inline
r_void
id|load_context
c_func
(paren
id|mm_context_t
id|context
)paren
(brace
id|mtsp
c_func
(paren
id|context
comma
l_int|3
)paren
suffix:semicolon
macro_line|#if SPACEID_SHIFT == 0
id|mtctl
c_func
(paren
id|context
op_lshift
l_int|1
comma
l_int|8
)paren
suffix:semicolon
macro_line|#else
id|mtctl
c_func
(paren
id|context
op_rshift
(paren
id|SPACEID_SHIFT
op_minus
l_int|1
)paren
comma
l_int|8
)paren
suffix:semicolon
macro_line|#endif
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
r_if
c_cond
(paren
id|prev
op_ne
id|next
)paren
(brace
id|mtctl
c_func
(paren
id|__pa
c_func
(paren
id|next-&gt;pgd
)paren
comma
l_int|25
)paren
suffix:semicolon
id|load_context
c_func
(paren
id|next-&gt;context
)paren
suffix:semicolon
)brace
)brace
DECL|macro|deactivate_mm
mdefine_line|#define deactivate_mm(tsk,mm)&t;do { } while (0)
DECL|function|activate_mm
r_static
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
multiline_comment|/*&n;&t; * Activate_mm is our one chance to allocate a space id&n;&t; * for a new mm created in the exec path. There&squot;s also&n;&t; * some lazy tlb stuff, which is currently dead code, but&n;&t; * we only allocate a space id if one hasn&squot;t been allocated&n;&t; * already, so we should be OK.&n;&t; */
id|BUG_ON
c_func
(paren
id|next
op_eq
op_amp
id|init_mm
)paren
suffix:semicolon
multiline_comment|/* Should never happen */
r_if
c_cond
(paren
id|next-&gt;context
op_eq
l_int|0
)paren
id|next-&gt;context
op_assign
id|alloc_sid
c_func
(paren
)paren
suffix:semicolon
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
