multiline_comment|/**&n; * @file backtrace.c&n; *&n; * @remark Copyright 2002 OProfile authors&n; * @remark Read the file COPYING&n; *&n; * @author John Levon&n; * @author David Smith&n; */
macro_line|#include &lt;linux/oprofile.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/mm.h&gt;
macro_line|#include &lt;asm/ptrace.h&gt;
DECL|struct|frame_head
r_struct
id|frame_head
(brace
DECL|member|ebp
r_struct
id|frame_head
op_star
id|ebp
suffix:semicolon
DECL|member|ret
r_int
r_int
id|ret
suffix:semicolon
)brace
id|__attribute__
c_func
(paren
(paren
id|packed
)paren
)paren
suffix:semicolon
r_static
r_struct
id|frame_head
op_star
DECL|function|dump_backtrace
id|dump_backtrace
c_func
(paren
r_struct
id|frame_head
op_star
id|head
)paren
(brace
id|oprofile_add_trace
c_func
(paren
id|head-&gt;ret
)paren
suffix:semicolon
multiline_comment|/* frame pointers should strictly progress back up the stack&n;&t; * (towards higher addresses) */
r_if
c_cond
(paren
id|head
op_ge
id|head-&gt;ebp
)paren
r_return
l_int|NULL
suffix:semicolon
r_return
id|head-&gt;ebp
suffix:semicolon
)brace
multiline_comment|/* check that the page(s) containing the frame head are present */
DECL|function|pages_present
r_static
r_int
id|pages_present
c_func
(paren
r_struct
id|frame_head
op_star
id|head
)paren
(brace
r_struct
id|mm_struct
op_star
id|mm
op_assign
id|current-&gt;mm
suffix:semicolon
multiline_comment|/* FIXME: only necessary once per page */
r_if
c_cond
(paren
op_logical_neg
id|check_user_page_readable
c_func
(paren
id|mm
comma
(paren
r_int
r_int
)paren
id|head
)paren
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|check_user_page_readable
c_func
(paren
id|mm
comma
(paren
r_int
r_int
)paren
(paren
id|head
op_plus
l_int|1
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * |             | /&bslash; Higher addresses&n; * |             |&n; * --------------- stack base (address of current_thread_info)&n; * | thread info |&n; * .             .&n; * |    stack    |&n; * --------------- saved regs-&gt;ebp value if valid (frame_head address)&n; * .             .&n; * --------------- struct pt_regs stored on stack (struct pt_regs *)&n; * |             |&n; * .             .&n; * |             |&n; * --------------- %esp&n; * |             |&n; * |             | &bslash;/ Lower addresses&n; *&n; * Thus, &amp;pt_regs &lt;-&gt; stack base restricts the valid(ish) ebp values&n; */
macro_line|#ifdef CONFIG_FRAME_POINTER
DECL|function|valid_kernel_stack
r_static
r_int
id|valid_kernel_stack
c_func
(paren
r_struct
id|frame_head
op_star
id|head
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_int
r_int
id|headaddr
op_assign
(paren
r_int
r_int
)paren
id|head
suffix:semicolon
r_int
r_int
id|stack
op_assign
(paren
r_int
r_int
)paren
id|regs
suffix:semicolon
r_int
r_int
id|stack_base
op_assign
(paren
id|stack
op_amp
op_complement
(paren
id|THREAD_SIZE
op_minus
l_int|1
)paren
)paren
op_plus
id|THREAD_SIZE
suffix:semicolon
r_return
id|headaddr
OG
id|stack
op_logical_and
id|headaddr
OL
id|stack_base
suffix:semicolon
)brace
macro_line|#else
multiline_comment|/* without fp, it&squot;s just junk */
DECL|function|valid_kernel_stack
r_static
r_int
id|valid_kernel_stack
c_func
(paren
r_struct
id|frame_head
op_star
id|head
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
r_void
DECL|function|x86_backtrace
id|x86_backtrace
c_func
(paren
r_struct
id|pt_regs
op_star
r_const
id|regs
comma
r_int
r_int
id|depth
)paren
(brace
r_struct
id|frame_head
op_star
id|head
suffix:semicolon
macro_line|#ifdef CONFIG_X86_64
id|head
op_assign
(paren
r_struct
id|frame_head
op_star
)paren
id|regs-&gt;rbp
suffix:semicolon
macro_line|#else
id|head
op_assign
(paren
r_struct
id|frame_head
op_star
)paren
id|regs-&gt;ebp
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
op_logical_neg
id|user_mode
c_func
(paren
id|regs
)paren
)paren
(brace
r_while
c_loop
(paren
id|depth
op_decrement
op_logical_and
id|valid_kernel_stack
c_func
(paren
id|head
comma
id|regs
)paren
)paren
id|head
op_assign
id|dump_backtrace
c_func
(paren
id|head
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef CONFIG_SMP
r_if
c_cond
(paren
op_logical_neg
id|spin_trylock
c_func
(paren
op_amp
id|current-&gt;mm-&gt;page_table_lock
)paren
)paren
r_return
suffix:semicolon
macro_line|#endif
r_while
c_loop
(paren
id|depth
op_decrement
op_logical_and
id|head
op_logical_and
id|pages_present
c_func
(paren
id|head
)paren
)paren
id|head
op_assign
id|dump_backtrace
c_func
(paren
id|head
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_SMP
id|spin_unlock
c_func
(paren
op_amp
id|current-&gt;mm-&gt;page_table_lock
)paren
suffix:semicolon
macro_line|#endif
)brace
eof
