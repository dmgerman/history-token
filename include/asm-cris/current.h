macro_line|#ifndef _CRIS_CURRENT_H
DECL|macro|_CRIS_CURRENT_H
mdefine_line|#define _CRIS_CURRENT_H
macro_line|#include &lt;linux/thread_info.h&gt;
r_struct
id|task_struct
suffix:semicolon
DECL|function|get_current
r_extern
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
mdefine_line|#define current get_current()
macro_line|#endif /* !(_CRIS_CURRENT_H) */
eof
