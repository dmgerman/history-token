macro_line|#ifndef __ASM_SH64_CURRENT_H
DECL|macro|__ASM_SH64_CURRENT_H
mdefine_line|#define __ASM_SH64_CURRENT_H
multiline_comment|/*&n; * This file is subject to the terms and conditions of the GNU General Public&n; * License.  See the file &quot;COPYING&quot; in the main directory of this archive&n; * for more details.&n; *&n; * include/asm-sh64/current.h&n; *&n; * Copyright (C) 2000, 2001  Paolo Alberelli&n; * Copyright (C) 2003  Paul Mundt&n; *&n; */
macro_line|#include &lt;linux/thread_info.h&gt;
r_struct
id|task_struct
suffix:semicolon
DECL|function|get_current
r_static
id|__inline__
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
macro_line|#endif /* __ASM_SH64_CURRENT_H */
eof
