macro_line|#ifndef _M68KNOMMU_CURRENT_H
DECL|macro|_M68KNOMMU_CURRENT_H
mdefine_line|#define _M68KNOMMU_CURRENT_H
multiline_comment|/*&n; *&t;current.h&n; *&t;(C) Copyright 2000, Lineo, David McCullough &lt;davidm@uclinux.org&gt;&n; *&t;(C) Copyright 2002, Greg Ungerer (gerg@snapgear.com)&n; *&n; *&t;rather than dedicate a register (as the m68k source does), we&n; *&t;just keep a global,  we should probably just change it all to be&n; *&t;current and lose _current_task.&n; */
macro_line|#include &lt;asm/thread_info.h&gt;
r_struct
id|task_struct
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
mdefine_line|#define&t;current&t;get_current()
macro_line|#endif /* _M68KNOMMU_CURRENT_H */
eof
