macro_line|#ifndef _ASMARM_CURRENT_H
DECL|macro|_ASMARM_CURRENT_H
mdefine_line|#define _ASMARM_CURRENT_H
macro_line|#include &lt;asm/thread_info.h&gt;
r_static
r_inline
r_struct
id|task_struct
op_star
id|get_current
c_func
(paren
r_void
)paren
id|__attribute__
(paren
(paren
id|__const__
)paren
)paren
suffix:semicolon
DECL|function|get_current
r_static
r_inline
r_struct
id|task_struct
op_star
id|get_current
c_func
(paren
r_void
)paren
(brace
r_return
id|current_thread_info
c_func
(paren
)paren
op_member_access_from_pointer
id|task
suffix:semicolon
)brace
DECL|macro|current
mdefine_line|#define current (get_current())
macro_line|#endif /* _ASMARM_CURRENT_H */
eof
